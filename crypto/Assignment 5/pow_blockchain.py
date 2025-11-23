import hashlib
import time
from dataclasses import dataclass, field
from typing import List


def sha256(b: bytes) -> str:
    return hashlib.sha256(b).hexdigest()


@dataclass
class Block:
    index: int
    timestamp: float
    data: str
    prev_hash: str
    nonce: int = 0
    hash: str = field(init=False)

    def compute_hash(self):
        header = f"{self.index}|{self.timestamp}|{self.data}|{self.prev_hash}|{self.nonce}".encode()
        return sha256(header)


class Blockchain:
    def __init__(self, difficulty: int = 3):
        self.difficulty = difficulty
        self.chain: List[Block] = [self.genesis_block()]

    def genesis_block(self) -> Block:
        b = Block(0, time.time(), "Genesis", "0" * 64)
        b.hash = b.compute_hash()
        return b

    def add_block(self, data: str):
        prev = self.chain[-1]
        b = Block(len(self.chain), time.time(), data, prev.hash)
        prefix = "0" * self.difficulty
        while True:
            h = b.compute_hash()
            if h.startswith(prefix):
                b.hash = h
                break
            b.nonce += 1
        self.chain.append(b)
        print(f"Added block {b.index} with hash {b.hash}")

    def is_valid(self) -> bool:
        prefix = "0" * self.difficulty
        for i in range(1, len(self.chain)):
            c = self.chain[i]
            p = self.chain[i - 1]
            if c.prev_hash != p.hash:
                return False
            if not c.hash.startswith(prefix):
                return False
            if c.hash != c.compute_hash():
                return False
        return True


if __name__ == "__main__":
    bc = Blockchain(difficulty=3)
    bc.add_block("Alice pays Bob 5")
    bc.add_block("Bob pays Carol 2")

    for b in bc.chain:
        print(b.index, b.prev_hash[:8], "->", b.hash[:8], "nonce", b.nonce)

    print("Valid?", bc.is_valid())
