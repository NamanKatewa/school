from cryptography.hazmat.primitives.asymmetric import rsa, padding
from cryptography.hazmat.primitives import hashes


def dh_example():
    # small demo values
    p = 23
    g = 5
    a = 6  # Alice secret
    b = 15  # Bob secret

    A = pow(g, a, p)
    B = pow(g, b, p)

    s_alice = pow(B, a, p)
    s_bob = pow(A, b, p)
    print("[DH] Shared (Alice):", s_alice)
    print("[DH] Shared (Bob)  :", s_bob)


def rsa_kem_example():
    # Alice generates RSA keypair; Bob wants to send a random secret.
    priv = rsa.generate_private_key(public_exponent=65537, key_size=2048)
    pub = priv.public_key()
    secret = b"session-key-123"
    ct = pub.encrypt(
        secret,
        padding.OAEP(
            mgf=padding.MGF1(hashes.SHA256()),
            algorithm=hashes.SHA256(),
            label=None,
        ),
    )
    pt = priv.decrypt(
        ct,
        padding.OAEP(
            mgf=padding.MGF1(hashes.SHA256()),
            algorithm=hashes.SHA256(),
            label=None,
        ),
    )
    print("[RSA-KEM] Original:", secret)
    print("[RSA-KEM] Decrypted:", pt)


if __name__ == "__main__":
    print("=== Diffie-Hellman Demo ===")
    dh_example()
    print("\n=== RSA Key Transport Demo ===")
    rsa_kem_example()
