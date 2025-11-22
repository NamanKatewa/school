import string
from collections import Counter

ALPH = string.ascii_uppercase


def normalize(text):
    return ''.join(ch for ch in text.upper() if ch in ALPH)


def vigenere_decrypt(ciphertext, key):
    ciphertext = ciphertext.upper()
    key = key.upper()
    res = []
    key_idx = [ALPH.index(k) for k in key]
    j = 0
    for ch in ciphertext:
        if ch in ALPH:
            c = ALPH.index(ch)
            k = key_idx[j % len(key)]
            p = (c - k) % 26
            res.append(ALPH[p])
            j += 1
        else:
            res.append(ch)
    return ''.join(res)


def index_of_coincidence(text):
    text = normalize(text)
    N = len(text)
    if N <= 1:
        return 0.0
    freqs = Counter(text)
    num = sum(f * (f - 1) for f in freqs.values())
    den = N * (N - 1)
    return num / den


def guess_key_length_ic(ct, max_len=6):
    ct = normalize(ct)
    print("Key-length guess via Index of Coincidence:")
    for m in range(1, max_len + 1):
        ics = []
        for i in range(m):
            chunk = ct[i::m]
            if len(chunk) > 1:
                ics.append(index_of_coincidence(chunk))
        avg_ic = sum(ics) / len(ics) if ics else 0
        print(f"m={m}, avg_IC={avg_ic:.4f}")


def main():
    ct = "LXFOPVEFRNHR"
    print("Ciphertext:", ct)

    # 1) IC-based key-length hints (educational, text is short)
    guess_key_length_ic(ct, max_len=6)

    # 2) Decrypt with known textbook key 'LEMON'
    key = "LEMON"
    pt = vigenere_decrypt(ct, key)
    print("\nUsing key:", key)
    print("Plaintext:", pt)


if __name__ == "__main__":
    main()