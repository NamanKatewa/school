def encrypt(plaintext:str,key:int)->str:
    cleaned_plaintext = plaintext.strip().lower()
    matrix:list[list[str]]=[[]for _ in range(key)]
    
    row:int=0
    direction:int=1
    
    for x in cleaned_plaintext:
        if(x == " "):
            continue
        matrix[row].append(x)
        
        if(row==0):
            direction=1
        elif(row==key-1):
            direction=-1
        
        row+=direction
    
    return "".join("".join(r) for r in matrix)

def decrypt(ciphertext:str,key:int)->str:
    cleaned_ciphertext = ciphertext.strip().lower()
    matrix:list[list[str | None]] = [[]for _ in range(key)]
    
    
    row:int=0
    direction:int=1
    
    for x in cleaned_ciphertext:
        if(x == " "):
            continue
        matrix[row].append("")
        
        if(row==0):
            direction=1
        elif(row==key-1):
            direction=-1
            
        row+=direction
    
    return ciphertext

print("---RALIFENCE CIPHER---")

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
