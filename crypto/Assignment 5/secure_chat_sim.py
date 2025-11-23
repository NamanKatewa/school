from cryptography.fernet import Fernet
import time
import json


class SecureChannel:
    def __init__(self):
        self.key = Fernet.generate_key()
        self.f = Fernet(self.key)
        self.send_counter = 0
        self.recv_seen = set()

    def pack(self, sender: str, msg: str) -> bytes:
        self.send_counter += 1
        payload = {
            "sender": sender,
            "msg": msg,
            "ts": time.time(),
            "ctr": self.send_counter,
        }
        token = self.f.encrypt(json.dumps(payload).encode())
        return token

    def unpack(self, token: bytes):
        data = json.loads(self.f.decrypt(token).decode())
        ctr = data["ctr"]
        if ctr in self.recv_seen:
            raise ValueError("Replay detected (counter reused)")
        self.recv_seen.add(ctr)
        return data


if __name__ == "__main__":
    chan = SecureChannel()

    # Alice sends to Bob
    t1 = chan.pack("Alice", "Hello Bob")
    print("Wire token 1:", t1)
    d1 = chan.unpack(t1)
    print("Received:", d1)

    # Replay attempt (attacker re-sends same token)
    try:
        chan.unpack(t1)
    except Exception as e:
        print("Replay blocked:", e)
