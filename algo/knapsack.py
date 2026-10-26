def zero_one(w, val, cap):
    n = len(w)
    dp = [[0 for _ in range(cap + 1)] for _ in range(n + 1)]

    for i in range(1, n + 1):
        for j in range(cap + 1):
            if w[i - 1] > j:
                dp[i][j] = dp[i - 1][j]
            else:
                dp[i][j] = max(dp[i - 1][j], val[i - 1] + dp[i - 1][j - w[i - 1]])

    print_matrix(dp)
    return dp[n][cap]


def print_matrix(matrix):
    print(f"Matrix {len(matrix)} x {len(matrix[0])}")
    for row in matrix:
        print(" ".join(str(v) for v in row))


def fractional(w,val,cap):
    items = []
    
    for w,v in zip(w,val):
        ratio = v/w
        items.append((ratio,w,v))
    
    items.sort(reverse=True)
    print(items)
    
    total = 0
    
    for ratio,weight,value in items:
        if cap == 0:
            break
        
        if weight <= cap:
            total += value
            cap -= weight

        else:
            fraction = cap/weight
            total += value*fraction
            cap = 0
    return total


weights  = [10, 20, 22, 45]
values   = [11,  5,  7,  3]
capacity = 36

result = fractional(weights, values, capacity)
print("Best value:", result)