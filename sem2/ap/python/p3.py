from itertools import compress


class NumberStream:
    def __init__(self):
        self.current = 1

    def __iter__(self):
        return self

    def __next__(self):
        val = self.current
        self.current += 1
        return val


def print_numbers():
    even_selector = [False, True] * 10
    odd_selector = [True, False] * 10

    stream_for_evens = NumberStream()
    even_numbers = list(compress(stream_for_evens, even_selector))
    print("First 10 Even Numbers:")
    print(even_numbers)

    stream_for_odds = NumberStream()
    odd_numbers = list(compress(stream_for_odds, odd_selector))
    print("First 10 Odd Numbers:")
    print(odd_numbers)


print_numbers()
