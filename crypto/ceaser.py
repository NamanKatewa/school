def alpha_to_num(ch: str)->int:
    return ord(ch)-ord('a')

def num_to_alpha(num:int)->str:
    return chr(ord('a')+num)

def encrypt(plaintext:str, key:int)->str:
    cleaned_plaintext:str = plaintext.strip().lower()
    ciphertext:str = ""
    for x in cleaned_plaintext:
        if(x==" "):
            continue
        ciphertext += num_to_alpha((alpha_to_num(x)+3)%26)
    return ciphertext

def decrypt(ciphertext:str, key:int)->str:
    cleaned_ciphertext:str = ciphertext.strip().lower()
    plaintext = ""
    for x in cleaned_ciphertext:
        if(x==" "):
            continue
        plaintext += num_to_alpha((alpha_to_num(x)-3)%26)
    return plaintext

print("---CEASER CIPHER---")

while True:
    print("1 - Encrpyt")
    print("2 - Decrypt")
    print("3 - Exit")
    
    choice:int = int(input("Enter your choice: "))
    
    match choice:
        case 1:
            plaintext: str = input("Enter the text you want to encrypt: ")
            key:int = int(input("Enter key: "))
            ciphertext: str = encrypt(plaintext,key)
            print("Cipher Text: "+ ciphertext)
        case 2:
            ciphertext: str = input("Enter the text you want to decrypt: ")
            key:int = int(input("Enter key: "))
            plaintext: str = decrypt(ciphertext,key)
            print("Plain Text: "+ plaintext)
        case 3:
            break
        case _:
            print("Invalid Choice")
