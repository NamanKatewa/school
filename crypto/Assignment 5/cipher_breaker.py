from collections import Counter
import string

ALPHABET = string.ascii_uppercase


def norm(t: str) -> str:
    return "".join(ch for ch in t.upper() if ch in ALPHABET)


def caesar_enc(t: str, k: int) -> str:
    t = norm(t)
    return "".join(ALPHABET[(ALPHABET.index(c) + k) % 26] for c in t)


def caesar_dec(t: str, k: int) -> str:
    return caesar_enc(t, -k)


def brute_force(t: str):
    t = norm(t)
    for k in range(26):
        print(f"k={k:2}: {caesar_dec(t, k)}")


def freq(t: str):
    t = norm(t)
    c = Counter(t)
    total = sum(c.values())
    for ch, cnt in c.most_common():
        print(f"{ch}: {cnt:3} ({cnt/total:.2%})")


if __name__ == "__main__":
    text = input("Plaintext: ")
    key = int(input("Key (0-25): "))
    cipher = caesar_enc(text, key)
    print("Cipher:", cipher)

    print("\n[Brute-force guesses]")
    brute_force(cipher)

    print("\n[Frequency of cipher]")
    freq(cipher)
