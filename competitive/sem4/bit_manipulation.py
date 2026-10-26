def decimalToBin(num):
    return bin(num)[2:]

def binaryToDec(num):
    return int(num,base=2)

def bitwiseAnd(a,b):
    return a & b

def bitwiseOr(a,b):
    return a | b

def bitwiseXor(a,b):
    return a ^ b

def bitwiseNot(a):
    return ~a

def bitwiseLeftShift(a,k):
    return a << k

def bitwiseRightShift(a,k):
    return a >> k

def checkSetBit(num,k):
    num2 = 1 << k
    result = num & num2
    
    if(result==0):
        return False
    else:
        return True

def setBit(num,k):
    num2 = 1<<k
    result = num | num2
    return result

def clearBit(num,k):
    num2 = 1<<k
    res = num2 & num
    return res

def toggleBit(num,k):
    num2 = 1<<k
    result = num ^ num2
    return result

def isEven(n):
    if(n & 1 ==0):
        return True
    return False

def isOdd(n):
    if(n & 1 ==1):
        return True
    return False

def countSetBits(num):
    count = num.count("1")
    return count

def checkPowerOf2(num):
    count = countSetBits(num)
    
    if(count ==1):
        return True
    return False

def findUniqueElement(nums):
    res = 0
    for x in nums:
        res^=x
    return res
    

nums = [4,4,1,3,4,3,1]
print(findUniqueElement(nums))