# crypto_explorer.py
# Classical cipher explorer: Caesar + Vigenere + brute-force + freq analysis.

import string
from collections import Counter

ALPHABET = string.ascii_uppercase


def normalize(text: str) -> str:
    return "".join(ch for ch in text.upper() if ch in ALPHABET)


def caesar_shift(text: str, key: int, decrypt: bool = False) -> str:
    text = normalize(text)
    if decrypt:
        key = -key
    res = []
    for ch in text:
        idx = (ALPHABET.index(ch) + key) % 26
        res.append(ALPHABET[idx])
    return "".join(res)


def vigenere(text: str, key: str, decrypt: bool = False) -> str:
    text = normalize(text)
    key = normalize(key)
    res = []
    for i, ch in enumerate(text):
        k = ALPHABET.index(key[i % len(key)])
        if decrypt:
            k = -k
        idx = (ALPHABET.index(ch) + k) % 26
        res.append(ALPHABET[idx])
    return "".join(res)


def brute_force_caesar(cipher: str):
    cipher = normalize(cipher)
    for k in range(26):
        print(f"Key {k:2}: {caesar_shift(cipher, k, decrypt=True)}")


def freq_analysis(text: str):
    text = normalize(text)
    c = Counter(text)
    total = sum(c.values())
    for ch, cnt in c.most_common():
        print(f"{ch}: {cnt:3} ({cnt/total:.2%})")


def menu():
    while True:
        print("\n[1] Caesar encrypt")
        print("[2] Caesar decrypt")
        print("[3] Vigenere encrypt")
        print("[4] Vigenere decrypt")
        print("[5] Caesar brute-force attack")
        print("[6] Frequency analysis")
        print("[0] Exit")
        choice = input("Choice: ").strip()
        if choice == "0":
            break
        text = input("Text: ")
        if choice in {"1", "2"}:
            key = int(input("Key (0-25): "))
            dec = choice == "2"
            print("Result:", caesar_shift(text, key, decrypt=dec))
        elif choice in {"3", "4"}:
            key = input("Key word: ")
            dec = choice == "4"
            print("Result:", vigenere(text, key, decrypt=dec))
        elif choice == "5":
            brute_force_caesar(text)
        elif choice == "6":
            freq_analysis(text)
        else:
            print("Invalid choice")


if __name__ == "__main__":
    menu()
