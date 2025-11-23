import json
import os
import getpass
import hashlib
from base64 import urlsafe_b64encode
from cryptography.fernet import Fernet
from cryptography.hazmat.primitives.kdf.pbkdf2 import PBKDF2HMAC
from cryptography.hazmat.primitives import hashes


DB_FILE = "vault.enc"
META_FILE = "vault.meta"


def derive_key(master: str, salt: bytes) -> bytes:
    kdf = PBKDF2HMAC(
        algorithm=hashes.SHA256(), length=32, salt=salt, iterations=200_000
    )
    return urlsafe_b64encode(kdf.derive(master.encode()))


def init_vault():
    master = getpass.getpass("Set master password: ")
    salt = os.urandom(16)
    key = derive_key(master, salt)
    f = Fernet(key)
    empty_db = {}
    ct = f.encrypt(json.dumps(empty_db).encode())
    open(DB_FILE, "wb").write(ct)
    meta = {
        "salt": salt.hex(),
        "master_hash": hashlib.sha256(master.encode()).hexdigest(),
    }
    open(META_FILE, "w").write(json.dumps(meta))
    print("Vault initialized.")


def open_vault():
    meta = json.loads(open(META_FILE).read())
    master = getpass.getpass("Master password: ")
    if hashlib.sha256(master.encode()).hexdigest() != meta["master_hash"]:
        raise ValueError("Wrong master password")
    salt = bytes.fromhex(meta["salt"])
    key = derive_key(master, salt)
    f = Fernet(key)
    ct = open(DB_FILE, "rb").read()
    data = json.loads(f.decrypt(ct).decode())
    return data, f


def save_vault(data, f: Fernet):
    ct = f.encrypt(json.dumps(data).encode())
    open(DB_FILE, "wb").write(ct)


def main():
    if not os.path.exists(DB_FILE):
        init_vault()

    data, f = open_vault()

    while True:
        print("\n[1] List entries\n[2] Add / update\n[3] Get password\n[0] Exit")
        c = input("Choice: ").strip()
        if c == "0":
            save_vault(data, f)
            break
        elif c == "1":
            for site in data:
                print(site)
        elif c == "2":
            site = input("Site: ")
            user = input("Username: ")
            pwd = getpass.getpass("Password: ")
            data[site] = {"user": user, "pwd": pwd}
        elif c == "3":
            site = input("Site: ")
            print(data.get(site, "Not found"))


if __name__ == "__main__":
    main()
