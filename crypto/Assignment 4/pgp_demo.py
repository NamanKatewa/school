import gnupg
from pathlib import Path

GPG_HOME = "./gpg_home"
Path(GPG_HOME).mkdir(exist_ok=True)

gpg = gnupg.GPG(gnupghome=GPG_HOME)

def generate_key_pair(name_email: str, passphrase: str):
    input_data = gpg.gen_key_input(
        name_email=name_email,
        key_type="RSA",
        key_length=2048,
        passphrase=passphrase,
    )
    key = gpg.gen_key(input_data)
    print(f"[+] Generated key for {name_email}: {key.fingerprint}")
    return key


def encrypt_message(recipient_fpr: str, plaintext: str) -> str:
    encrypted = gpg.encrypt(plaintext, recipients=[recipient_fpr])
    if not encrypted.ok:
        raise RuntimeError(f"Encrypt failed: {encrypted.status}")
    return str(encrypted)


def decrypt_message(ciphertext: str, passphrase: str) -> str:
    decrypted = gpg.decrypt(ciphertext, passphrase=passphrase)
    if not decrypted.ok:
        raise RuntimeError(f"Decrypt failed: {decrypted.status}")
    return str(decrypted)


def sign_message(plaintext: str, signer_fpr: str, passphrase: str) -> str:
    signed = gpg.sign(
        plaintext,
        keyid=signer_fpr,
        passphrase=passphrase,
        detach=True,  # detached signature
    )
    if not signed:
        raise RuntimeError("Sign failed")
    return str(signed)


def verify_signature(plaintext: str, signature: str):
    verified = gpg.verify_data(signature.encode(), plaintext.encode())
    print(f"[+] Signature valid: {verified.valid}, signer: {verified.key_id}")


if __name__ == "__main__":
    sender_pass = "sender-pass"
    receiver_pass = "receiver-pass"

    sender_key = generate_key_pair("Alice <alice@example.com>", sender_pass)
    receiver_key = generate_key_pair("Bob <bob@example.com>", receiver_pass)

    email_body = "Hi Bob,\nThis is a confidential email.\nRegards,\nAlice"

    # Encrypt for Bob
    ciphertext = encrypt_message(receiver_key.fingerprint, email_body)
    print("\n[Encrypted message]\n", ciphertext)

    # Bob decrypts
    decrypted = decrypt_message(ciphertext, receiver_pass)
    print("\n[Bob decrypted]\n", decrypted)

    # Alice signs the original plaintext
    signature = sign_message(email_body, sender_key.fingerprint, sender_pass)
    print("\n[Detached signature]\n", signature)

    # Bob verifies Alice's signature
    verify_signature(email_body, signature)
