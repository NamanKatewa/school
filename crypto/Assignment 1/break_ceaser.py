import string

ALPH = string.ascii_uppercase


def caesar_decrypt(text, shift):
    text = text.upper()
    res = []
    for ch in text:
        if ch in ALPH:
            idx = ALPH.index(ch)
            res.append(ALPH[(idx - shift) % 26])
        else:
            res.append(ch)
    return ''.join(res)


def brute_force_caesar(text):
    text = text.upper()
    for s in range(26):
        print(f"Shift {s:2}: {caesar_decrypt(text, s)}")


def main():
    ct = "GUVF VF N FRPERG ZRFFNTR"
    print("Ciphertext:", ct)
    print("\nBrute forcing all Caesar shifts:")
    brute_force_caesar(ct)

    print("\nDirect ROT13 (shift = 13) decryption:")
    pt = caesar_decrypt(ct, 13)
    print("Plaintext:", pt)


if __name__ == "__main__":
    main()
