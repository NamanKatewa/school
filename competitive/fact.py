def factorial(n:int):
    if n == 0:
        return 1
    elif n ==1:
        return 1
    else:
        return factorial(n-1) * n
    
res = factorial(3)
print(res)