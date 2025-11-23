# key_distribution.py
#
# Simple symmetric-key KDC demo (educational, not secure for real use).

import secrets
from dataclasses import dataclass, field
from typing import Dict, Tuple


def xor_bytes(data: bytes, key: bytes) -> bytes:
    # Very simplistic "encryption" using XOR (for demo only).
    k = (key * (len(data) // len(key) + 1))[: len(data)]
    return bytes(a ^ b for a, b in zip(data, k))


@dataclass
class KDC:
    # Each user has a long-term symmetric key shared with the KDC.
    master_keys: Dict[str, bytes] = field(default_factory=dict)

    def register_user(self, name: str) -> bytes:
        key = secrets.token_bytes(16)  # 128-bit random key
        self.master_keys[name] = key
        print(f"[KDC] Registered {name}, master key: {key.hex()}")
        return key

    def issue_session_key(self, user_a: str, user_b: str) -> Tuple[bytes, bytes]:
        if user_a not in self.master_keys or user_b not in self.master_keys:
            raise ValueError("Both users must be registered with the KDC.")

        session_key = secrets.token_bytes(16)
        print(f"[KDC] New session key for {user_a} and {user_b}: {session_key.hex()}")

        enc_for_a = xor_bytes(session_key, self.master_keys[user_a])
        enc_for_b = xor_bytes(session_key, self.master_keys[user_b])

        return enc_for_a, enc_for_b


class User:
    def __init__(self, name: str, master_key: bytes):
        self.name = name
        self.master_key = master_key
        self.session_keys: Dict[str, bytes] = {}

    def receive_session_key(self, peer: str, enc_session_key: bytes):
        session_key = xor_bytes(enc_session_key, self.master_key)
        self.session_keys[peer] = session_key
        print(f"[{self.name}] Session key with {peer}: {session_key.hex()}")

    def send_secure(self, peer: str, plaintext: str) -> bytes:
        key = self.session_keys[peer]
        data = plaintext.encode()
        return xor_bytes(data, key)

    def recv_secure(self, peer: str, ciphertext: bytes) -> str:
        key = self.session_keys[peer]
        data = xor_bytes(ciphertext, key)
        return data.decode()


if __name__ == "__main__":
    # Setup
    kdc = KDC()
    alice_master = kdc.register_user("Alice")
    bob_master = kdc.register_user("Bob")

    alice = User("Alice", alice_master)
    bob = User("Bob", bob_master)

    # KDC issues a fresh session key for Alice–Bob
    enc_for_alice, enc_for_bob = kdc.issue_session_key("Alice", "Bob")

    # Each side recovers the same session key
    alice.receive_session_key("Bob", enc_for_alice)
    bob.receive_session_key("Alice", enc_for_bob)

    # Test secure message
    msg = "Hello Bob, this is Alice."
    ct = alice.send_secure("Bob", msg)
    print(f"[Wire] Ciphertext: {ct.hex()}")
    recovered = bob.recv_secure("Alice", ct)
    print(f"[Bob] Decrypted: {recovered}")
