import string

lowercase_letters = string.ascii_lowercase

enumerated_letters = list(enumerate(lowercase_letters, start=1))

print("Sequence of lowercase ASCII letters:")
for position, letter in enumerated_letters:
    print(f"Letter {position:02d}: {letter}")
