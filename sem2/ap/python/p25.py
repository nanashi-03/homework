import itertools

sequence = "ABCDE"

permutations_iter = itertools.permutations(sequence)

print("First 10 permutations of ABCDE:")

total_count = 0

for index, perm in enumerate(permutations_iter, start=1):
    clean_string = "".join(perm)

    if index <= 10:
        print(f"{index:02d}: {clean_string}")

    total_count = index

print(f"Total permutations generated: {total_count}")
