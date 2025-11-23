from cryptography.hazmat.primitives.asymmetric import rsa, padding
from cryptography.hazmat.primitives import hashes, serialization
from cryptography.exceptions import InvalidSignature


def generate_keys():
    priv = rsa.generate_private_key(public_exponent=65537, key_size=2048)
    pub = priv.public_key()
    with open("rsa_private.pem", "wb") as f:
        f.write(
            priv.private_bytes(
                encoding=serialization.Encoding.PEM,
                format=serialization.PrivateFormat.PKCS8,
                encryption_algorithm=serialization.NoEncryption(),
            )
        )
    with open("rsa_public.pem", "wb") as f:
        f.write(
            pub.public_bytes(
                encoding=serialization.Encoding.PEM,
                format=serialization.PublicFormat.SubjectPublicKeyInfo,
            )
        )
    print("Keys saved to rsa_private.pem and rsa_public.pem")


def load_private():
    return serialization.load_pem_private_key(
        open("rsa_private.pem", "rb").read(), password=None
    )


def load_public():
    return serialization.load_pem_public_key(open("rsa_public.pem", "rb").read())


def sign_message(msg: bytes) -> bytes:
    priv = load_private()
    sig = priv.sign(
        msg,
        padding.PSS(
            mgf=padding.MGF1(hashes.SHA256()),
            salt_length=padding.PSS.MAX_LENGTH,
        ),
        hashes.SHA256(),
    )
    return sig


def verify_message(msg: bytes, sig: bytes) -> bool:
    pub = load_public()
    try:
        pub.verify(
            sig,
            msg,
            padding.PSS(
                mgf=padding.MGF1(hashes.SHA256()),
                salt_length=padding.PSS.MAX_LENGTH,
            ),
            hashes.SHA256(),
        )
        return True
    except InvalidSignature:
        return False


if __name__ == "__main__":
    import sys, base64

    if len(sys.argv) < 2:
        print("Usage:")
        print("  python rsa_sign_system.py genkeys")
        print("  python rsa_sign_system.py sign \"message\"")
        print("  python rsa_sign_system.py verify \"message\" base64_signature")
        sys.exit(0)

    cmd = sys.argv[1]
    if cmd == "genkeys":
        generate_keys()
    elif cmd == "sign":
        msg = sys.argv[2].encode()
        sig = sign_message(msg)
        print("Signature (base64):", base64.b64encode(sig).decode())
    elif cmd == "verify":
        msg = sys.argv[2].encode()
        sig_b64 = sys.argv[3]
        sig = base64.b64decode(sig_b64)
        print("Valid:", verify_message(msg, sig))
