def format_time(start,end):
    return round((end - start) * 1000,4)

def formatted_print(type,pt,ct,time):
    
    BOLD = "\033[1m"
    RESET = "\033[0m"
    BLUE = "\033[94m"
    GREEN = "\033[92m"
    YELLOW = "\033[93m"

    pt = pt[:300] + (b"..." if len(pt) > 300 else b"")
    ct = ct[:300] + ("..." if len(ct) > 300 else "")
    print(f"\n\n{BOLD}{BLUE}---{type} encryption---{RESET}\n\n\n{BOLD}{GREEN}Plain Text:{RESET} {pt}\n\n{BOLD}{GREEN}Cipher Text:{RESET} {ct}\n\nThe time taken to encrypt DES is {YELLOW}{time}ms{RESET}\n\n")