from cryptography.hazmat.primitives.asymmetric import rsa, padding
from cryptography.hazmat.primitives import serialization, hashes
from cryptography.hazmat.primitives.ciphers import Cipher, algorithms, modes
import os

# 1. Generate RSA keys (simulating PGP public/private keys)
private_key = rsa.generate_private_key(public_exponent=65537, key_size=2048)
public_key = private_key.public_key()

# 2. Generate symmetric key (AES)
symmetric_key = os.urandom(32)   # 256-bit AES key
iv = os.urandom(16)

# 3. Encrypt message with symmetric key (like PGP)
message = b"This is a secret message."
cipher = Cipher(algorithms.AES(symmetric_key), modes.CFB(iv))
encryptor = cipher.encryptor()
encrypted_message = encryptor.update(message) + encryptor.finalize()

# 4. Encrypt the symmetric key with RSA public key
encrypted_key = public_key.encrypt(
    symmetric_key,
    padding.OAEP(mgf=padding.MGF1(algorithm=hashes.SHA256()), algorithm=hashes.SHA256(), label=None)
)

print("Encrypted Key:", encrypted_key)
print("Encrypted Message:", encrypted_message)

# 5. Decrypt symmetric key using RSA private key
decrypted_key = private_key.decrypt(
    encrypted_key,
    padding.OAEP(mgf=padding.MGF1(algorithm=hashes.SHA256()), algorithm=hashes.SHA256(), label=None)
)

# 6. Decrypt message using symmetric key
cipher_dec = Cipher(algorithms.AES(decrypted_key), modes.CFB(iv))
decryptor = cipher_dec.decryptor()
decrypted_message = decryptor.update(encrypted_message) + decryptor.finalize()

print("Decrypted Message:", decrypted_message.decode())
