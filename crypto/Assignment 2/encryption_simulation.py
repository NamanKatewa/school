from Crypto.Cipher import DES,DES3,AES
from Crypto.Util.Padding import pad #For Padding the key and the plaintext to 8 byte Blocks
import time # To measure time taken to encrypt
from utils import format_time,formatted_print


key_raw:bytes = b"Sample" #Key in Bytes
plaintext_raw:bytes = b"Confidential Transaction" #Plain text in bytes

with open("input.txt","rb") as f:
    plaintext_file = f.read()

def encrypt_des(plaintext,key):
    key:bytes=pad(key,8) #Key after padding
    plaintext_padded:bytes=pad(plaintext,8) #Plain text after padding

    des= DES.new(key=key,mode=DES.MODE_ECB) # Initilaizing Cipher object with mode ECB

    start_des = time.time()
    ciphertext = des.encrypt(plaintext=plaintext_padded) 
    end_des = time.time()

    time_des = format_time(start_des,end_des) # Difference and then conversion to miliseconds and rounding

    ciphertext = ciphertext.hex() # Converting bytes to hexadecimal for easier reading format

    formatted_print("DES",plaintext,ciphertext,time_des)

def encrypt_des3(plaintext,key):
    key = pad(key,16)
    plaintext_padded = pad(plaintext,8)
    
    des3 = DES3.new(key=key,mode=DES3.MODE_ECB)
    
    start_des3 = time.time()
    ciphertext = des3.encrypt(plaintext=plaintext_padded)
    end_des3 = time.time()
    
    time_des3 = format_time(start_des3,end_des3)
    
    ciphertext = ciphertext.hex()
    
    formatted_print("3DES",plaintext,ciphertext,time_des3)
    
def encrypt_aes(plaintext,key,mode):
    key = pad(key,16)
    plaintext_padded = pad(plaintext,16)
    
    aes = AES.new(key=key,mode=mode)
    
    start_aes = time.time()
    ciphertext = aes.encrypt(plaintext=plaintext_padded)
    end_aes = time.time()
    
    time_aes = format_time(start_aes,end_aes)
    
    ciphertext = ciphertext.hex()
    
    formatted_print("AES "+str(mode),plaintext,ciphertext,time_aes)
    
encrypt_des(plaintext_raw,key_raw)
encrypt_des(plaintext_file,key_raw)

encrypt_des3(plaintext_raw,key_raw)
encrypt_des3(plaintext_file,key_raw)

encrypt_aes(plaintext_raw,key_raw,AES.MODE_ECB)
encrypt_aes(plaintext_file,key_raw,AES.MODE_ECB)

encrypt_aes(plaintext_raw,key_raw,AES.MODE_CBC)
encrypt_aes(plaintext_file,key_raw,AES.MODE_CBC)

encrypt_aes(plaintext_raw,key_raw,AES.MODE_CFB)
encrypt_aes(plaintext_file,key_raw,AES.MODE_CFB)

encrypt_aes(plaintext_raw,key_raw,AES.MODE_OFB)
encrypt_aes(plaintext_file,key_raw,AES.MODE_OFB)

encrypt_aes(plaintext_raw,key_raw,AES.MODE_CTR)
encrypt_aes(plaintext_file,key_raw,AES.MODE_CTR)