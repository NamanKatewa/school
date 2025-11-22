#!/usr/bin/env python3
# q1_2_transposition_analysis.py

import string
from itertools import permutations

ALPH = string.ascii_uppercase


def normalize(text):
    return ''.join(ch for ch in text.upper() if ch in ALPH)


# ---------- Rail Fence ----------

def rail_fence_decrypt(ciphertext, rails):
    ciphertext = normalize(ciphertext)
    n = len(ciphertext)
    if rails <= 1 or rails >= n:
        return ciphertext

    pattern = list(range(rails)) + list(range(rails - 2, 0, -1))
    row_for_pos = [pattern[i % len(pattern)] for i in range(n)]
    counts = [row_for_pos.count(r) for r in range(rails)]

    rails_data = []
    k = 0
    for r in range(rails):
        rails_data.append(list(ciphertext[k:k + counts[r]]))
        k += counts[r]

    idx = [0] * rails
    pt = []
    for r in row_for_pos:
        pt.append(rails_data[r][idx[r]])
        idx[r] += 1
    return ''.join(pt)


def try_rail_fence(ciphertext, max_rails=9):
    print("=== Rail Fence trials ===")
    for r in range(2, max_rails + 1):
        print(f"Rails={r}: {rail_fence_decrypt(ciphertext, r)}")


# ---------- Columnar Transposition ----------

def decrypt_columnar_given_perm(ct, cols, perm):
    ct = normalize(ct)
    n = len(ct)
    rows = (n + cols - 1) // cols
    empty = cols * rows - n

    col_len = [rows] * cols
    for j in range(cols - empty, cols):
        if empty > 0:
            col_len[j] = rows - 1

    matrix_cols = [None] * cols
    k = 0
    for pj in perm:
        L = col_len[pj]
        matrix_cols[pj] = list(ct[k:k + L])
        k += L

    rows_data = []
    for i in range(rows):
        row = []
        for j in range(cols):
            if i < len(matrix_cols[j]):
                row.append(matrix_cols[j][i])
        rows_data.append(''.join(row))
    return ''.join(rows_data)


def score_english(text):
    t = text
    s = sum(t.count(v) for v in "AEIOU")
    for dg in ["TH", "HE", "ER", "IN", "AN", "RE", "ON", "AT", "EN", "ND"]:
        s += 2 * t.count(dg)
    for w in ["THE", "AND", "TO", "IN", "OF", "IS"]:
        s += 5 * t.count(w)
    return s


def columnar_bruteforce(ct, min_cols=2, max_cols=9, top_n=30):
    print("\n=== Columnar trials (best candidates) ===")
    ct = normalize(ct)
    candidates = []
    for c in range(min_cols, max_cols + 1):
        for perm in permutations(range(c)):
            pt = decrypt_columnar_given_perm(ct, c, perm)
            s = score_english(pt)
            candidates.append((s, c, perm, pt))
    candidates.sort(reverse=True)
    for s, c, perm, pt in candidates[:top_n]:
        print(f"score={s:2}, cols={c}, perm={perm}, pt={pt}")


def main():
    ct = "MRHRGHTNIIEOUETEACD"
    print("Ciphertext:", ct)

    # 1) Rail Fence trials
    try_rail_fence(ct, max_rails=9)

    # 2) Columnar brute-force trials
    columnar_bruteforce(ct, min_cols=2, max_cols=9, top_n=40)


if __name__ == "__main__":
    main()
