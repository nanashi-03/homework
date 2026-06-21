def prime_generator(limit):
    if limit < 2:
        return

    primes = [2]
    yield 2

    for num in range(3, limit + 1, 2):
        is_prime = True

        for p in primes:
            if p * p > num:
                break

            if num % p == 0:
                is_prime = False
                break

        if is_prime:
            primes.append(num)
            yield num


print("Primes up to 50:")
for prime in prime_generator(50):
    print(prime, end=" ")
