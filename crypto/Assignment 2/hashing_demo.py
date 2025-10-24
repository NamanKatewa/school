from Crypto.Hash import MD5,SHA1,SHA256

with open("input.txt","rb") as f:
    plaintext_file = f.read()

def hash_md5(plaintext):
    md5 = MD5.new()
    md5.update(plaintext)
    hash_value = md5.hexdigest()
    print(f"MD5 Hashed Value: {hash_value}")

def hash_sha1(plaintext):
    sha1 = SHA1.new()
    sha1.update(plaintext)
    hash_value = sha1.hexdigest()
    print(f"SHA-1 Hashed Value: {hash_value}")

def hash_sha256(plaintext):
    sha256 = SHA256.new()
    sha256.update(plaintext)
    hash_value = sha256.hexdigest()
    print(f"SHA-256 Hashed Value: {hash_value}")
    
hash_md5(plaintext_file)
hash_sha1(plaintext_file)
hash_sha256(plaintext_file)
    