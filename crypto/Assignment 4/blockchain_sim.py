import hashlib
import time
from dataclasses import dataclass, field
from typing import List

from cryptography.hazmat.primitives.asymmetric import ed25519
from cryptography.hazmat.primitives import serialization


def sha256(data: bytes) -> str:
    return hashlib.sha256(data).hexdigest()


@dataclass
class Block:
    index: int
    timestamp: float
    data: str
    prev_hash: str
    signer_public: bytes
    signature: bytes
    hash: str = field(init=False)

    def __post_init__(self):
        header = f"{self.index}|{self.timestamp}|{self.data}|{self.prev_hash}".encode()
        self.hash = sha256(header)


class SimpleBlockchain:
    def __init__(self, pub_key: ed25519.Ed25519PublicKey):
        self.pub_key = pub_key
        self.chain: List[Block] = [self.create_genesis_block()]

    def create_genesis_block(self) -> Block:
        dummy_pub = self.pub_key.public_bytes(
            encoding=serialization.Encoding.Raw,
            format=serialization.PublicFormat.Raw,
        )
        return Block(
            index=0,
            timestamp=time.time(),
            data="Genesis Block",
            prev_hash="0" * 64,
            signer_public=dummy_pub,
            signature=b"",
        )

    def add_block(self, data: str, signer_priv: ed25519.Ed25519PrivateKey):
        prev = self.chain[-1]
        timestamp = time.time()
        header = f"{len(self.chain)}|{timestamp}|{data}|{prev.hash}".encode()
        block_hash = sha256(header)

        signature = signer_priv.sign(block_hash.encode())
        signer_pub = signer_priv.public_key().public_bytes(
            encoding=serialization.Encoding.Raw,
            format=serialization.PublicFormat.Raw,
        )

        block = Block(
            index=len(self.chain),
            timestamp=timestamp,
            data=data,
            prev_hash=prev.hash,
            signer_public=signer_pub,
            signature=signature,
        )
        self.chain.append(block)

    def is_valid(self) -> bool:
        for i in range(1, len(self.chain)):
            cur = self.chain[i]
            prev = self.chain[i - 1]

            header = f"{cur.index}|{cur.timestamp}|{cur.data}|{cur.prev_hash}".encode()
            if cur.hash != sha256(header):
                return False

            if cur.prev_hash != prev.hash:
                return False

            pub = ed25519.Ed25519PublicKey.from_public_bytes(cur.signer_public)
            try:
                pub.verify(cur.signature, cur.hash.encode())
            except Exception:
                return False

        return True


if __name__ == "__main__":
    priv = ed25519.Ed25519PrivateKey.generate()
    pub = priv.public_key()

    bc = SimpleBlockchain(pub)
    bc.add_block("Alice pays Bob 5 coins", priv)
    bc.add_block("Bob pays Carol 2 coins", priv)

    for b in bc.chain:
        print(f"Index: {b.index}, Hash: {b.hash}, Prev: {b.prev_hash}")

    print("Valid chain?", bc.is_valid())

    # Try tampering
    bc.chain[1].data = "Alice pays Bob 500 coins"
    print("Valid after tamper?", bc.is_valid())
