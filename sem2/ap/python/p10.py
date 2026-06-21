numbers = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10]
odd_squares = list(filter(lambda x: x % 2 != 0, map(lambda x: x**2, numbers)))

print("Original Numbers:", numbers)
print("Only Odd Squares:", odd_squares)
