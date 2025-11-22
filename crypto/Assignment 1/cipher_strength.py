import math


def caesar_keyspace():
    # For 26 letters, shifts 1..25 are non-trivial
    return 25


def vigenere_keyspace(max_key_len):
    # sum_{L=1..max_key_len} 26^L
    return sum(26 ** L for L in range(1, max_key_len + 1))


def permutations(n):
    # Number of permutations n! for n columns in transposition
    return math.factorial(n)


def main():
    print("Caesar effective keyspace:", caesar_keyspace())
    for L in [4, 6, 8]:
        print(f"Vigenere keyspace (keys of length <= {L}): {vigenere_keyspace(L)}")
    for cols in [4, 6, 8]:
        print(f"Transposition keyspace (permutations for {cols} columns = {cols}!): {permutations(cols)}")

    # Scale of modern symmetric keys
    print("AES-128 keyspace: 2^128 ≈", 2 ** 128)


if __name__ == "__main__":
    main()
