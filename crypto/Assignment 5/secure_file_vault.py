import sys
from cryptography.fernet import Fernet
import hashlib  # extra SHA-256 hash of ciphertext


def save_key(path: str):
    key = Fernet.generate_key()
    with open(path, "wb") as f:
        f.write(key)
    print("Key saved to", path)


def load_key(path: str) -> bytes:
    with open(path, "rb") as f:
        return f.read()


def encrypt_file(key_path: str, in_path: str, out_path: str, hash_path: str):
    key = load_key(key_path)
    fernet = Fernet(key)
    data = open(in_path, "rb").read()
    ct = fernet.encrypt(data)
    open(out_path, "wb").write(ct)
    h = hashlib.sha256(ct).hexdigest()
    open(hash_path, "w").write(h)
    print("Encrypted ->", out_path)
    print("Ciphertext SHA-256 ->", hash_path)


def decrypt_file(key_path: str, in_path: str, out_path: str, hash_path: str):
    key = load_key(key_path)
    fernet = Fernet(key)
    ct = open(in_path, "rb").read()
    stored_hash = open(hash_path, "r").read().strip()
    calc_hash = hashlib.sha256(ct).hexdigest()
    if stored_hash != calc_hash:
        print("WARNING: Ciphertext hash mismatch! Possible tampering.")
    pt = fernet.decrypt(ct)
    open(out_path, "wb").write(pt)
    print("Decrypted ->", out_path)


if __name__ == "__main__":
    if len(sys.argv) < 2:
        print("Usage:")
        print("  python secure_file_vault.py genkey keyfile")
        print("  python secure_file_vault.py enc keyfile in_file enc_file hash.txt")
        print("  python secure_file_vault.py dec keyfile enc_file out_file hash.txt")
        sys.exit(0)

    mode = sys.argv[1]
    if mode == "genkey":
        save_key(sys.argv[2])
    elif mode == "enc":
        _, _, k, inf, outf, hf = sys.argv
        encrypt_file(k, inf, outf, hf)
    elif mode == "dec":
        _, _, k, inf, outf, hf = sys.argv
        decrypt_file(k, inf, outf, hf)
    else:
        print("Unknown mode")
