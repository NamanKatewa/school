import time
import secrets
from cryptography.hazmat.primitives.asymmetric import ec
from cryptography.hazmat.primitives import serialization

print("\n=== Classic Diffie-Hellman ===")

# -------------------------------------------
# Classic Diffie-Hellman (Using Manual Math)
# -------------------------------------------

def classic_dh_key_exchange():
    # A large prime (for demonstration, we use a smaller one)
    p = 0xFFFFFFFFFFFFFFFFC90FDAA22168C234C4C6628B80DC1CD1
    g = 2

    # Alice private and public
    a = secrets.randbelow(p)
    A = pow(g, a, p)

    # Bob private and public
    b = secrets.randbelow(p)
    B = pow(g, b, p)

    # Shared secrets
    shared_A = pow(B, a, p)
    shared_B = pow(A, b, p)

    return shared_A, shared_B

start_dh = time.time()
sA, sB = classic_dh_key_exchange()
end_dh = time.time()

print("Classic DH Shared Secrets Match:", sA == sB)
print("Time taken (Classic DH):", (end_dh - start_dh), "seconds")


print("\n=== Elliptic Curve Diffie-Hellman (ECDH) ===")

# -------------------------------------------
# Elliptic Curve Diffie-Hellman
# -------------------------------------------

def ecdh_key_exchange():
    # Using curve secp256r1
    alice_private = ec.generate_private_key(ec.SECP256R1())
    bob_private   = ec.generate_private_key(ec.SECP256R1())

    alice_public = alice_private.public_key()
    bob_public   = bob_private.public_key()

    # Exchange and compute shared secret
    shared_A = alice_private.exchange(ec.ECDH(), bob_public)
    shared_B = bob_private.exchange(ec.ECDH(), alice_public)

    return shared_A, shared_B

start_ecdh = time.time()
sA_ec, sB_ec = ecdh_key_exchange()
end_ecdh = time.time()

print("ECDH Shared Secrets Match:", sA_ec == sB_ec)
print("Time taken (ECDH):", (end_ecdh - start_ecdh), "seconds")
