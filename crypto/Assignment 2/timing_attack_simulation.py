import time, secrets,statistics

secret = b"Sample Secret"

def insecure_compare(probe,secret):
    
    for a,b in zip(probe,secret):
        if a!=b:
            return False
        
        time.sleep(0.002)
    return len(probe) == len(secret)

def secure_compare(probe,secret):
    
    if len(probe) != len(secret):
        
        maxlen = max(len(probe),len(secret))
        result = 0
        
        for i in range(maxlen):
            a = probe[i] if i<len(probe) else 0
            b = secret[i] if i<len(probe) else 0
            result = a^b
            time.sleep(0.0001)
        
        return False

    result = 0
    
    for a,b in zip(probe,secret):
        result |= a ^b
        time.sleep(0.0001)

    return result ==0

def recover_secret_using_timing(secret_len: int, rounds_per_guess: int = 8):
    recovered = bytearray(b"\x00" * secret_len)
    
    for pos in range(secret_len):
        best_byte = None
        best_time = -1
        
        for guess in range(256):
            
            recovered[pos] = guess
            probe = bytes(recovered[: pos + 1])
            
            timings = []
            
            for _ in range(rounds_per_guess):
                
                start = time.perf_counter_ns()
                insecure_compare(probe, secret)
                end = time.perf_counter_ns()
                
                timings.append(end - start)
                
            avg = statistics.mean(timings)
            
            if avg > best_time:
                best_time = avg
                best_byte = guess
                
        recovered[pos] = best_byte
        
        print(f"pos {pos}: got {best_byte} ({chr(best_byte) if 32<=best_byte<127 else best_byte}), avg_time_ns={best_time:.0f}")
    return bytes(recovered)

print("Starting simulation (insecure compare)...")

recovered = recover_secret_using_timing(len(secret), rounds_per_guess=12)

print("Recovered (timing):", recovered)

print("\nDemonstrate secure compare takes uniform time:")

for probe in [secret, secret[:-1] + b'X']:
    times = []
    
    for _ in range(30):
        
        t0 = time.perf_counter_ns()
        secure_compare(probe, secret)
        t1 = time.perf_counter_ns()
        
        times.append(t1 - t0)
        
    print(f"probe={probe!r}, mean_ns={statistics.mean(times):.0f}, stdev={statistics.stdev(times):.0f}")