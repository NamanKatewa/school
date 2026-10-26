def josephus(n, k):
    if n == 1:
        return 1
    return (josephus(n - 1, k) + k - 1) % n + 1

n, k = 5, 2
print(f"The last standing for {n} people and step {k} is: {josephus(n, k)}")
