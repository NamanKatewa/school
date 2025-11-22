import string
from collections import Counter

ALPH = string.ascii_uppercase


def normalize(text):
    return ''.join(ch for ch in text.upper() if ch in ALPH)


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


def caesar_bruteforce(text):
    text = text.upper()
    for s in range(26):
        pt = caesar_decrypt(text, s)
        print(f"Shift {s:2}: {pt}")


def letter_freq(text):
    text = normalize(text)
    c = Counter(text)
    return {ch: c.get(ch, 0) for ch in ALPH}


def print_freq_table(freq_dict):
    total = sum(freq_dict.values())
    print("Letter  Count  Percent")
    for ch in ALPH:
        cnt = freq_dict[ch]
        pct = (cnt / total * 100) if total > 0 else 0.0
        print(f"{ch:>3}  {cnt:>5}  {pct:6.2f}%")


def main():
    ct = "WKH TXLFN EURZQ IRA MXPSV RYHU WKH ODCB GRJ"
    print("Ciphertext:", ct)

    print("\n=== Brute-force Caesar shifts ===")
    caesar_bruteforce(ct)

    print("\n=== Ciphertext letter frequencies ===")
    freq = letter_freq(ct)
    print_freq_table(freq)


if __name__ == "__main__":
    main()
