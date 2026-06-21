def fibonacci_generator():
    a, b = 0, 1
    while True:
        yield a
        a, b = b, a + b


fib_gen = fibonacci_generator()

print("First 7 Fibonacci numbers:")
for _ in range(7):
    print(next(fib_gen), end=" ")
