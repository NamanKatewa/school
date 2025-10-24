from Crypto.Hash import HMAC,SHA256

with open("input.txt","rb") as f:
    plaintext_file1 = f.read()
    
with open("input_modified.txt","rb") as f:
    plaintext_file2 = f.read()

key = b"Sample Key"

def hmac(plaintext,key):
    hmac = HMAC.new(key=key,digestmod=SHA256)
    hmac.update(plaintext)
    hash_value = hmac.hexdigest()
    
    print(f"Hashed Value: {hash_value}")

hmac(plaintext_file1,key)
hmac(plaintext_file2,key)
