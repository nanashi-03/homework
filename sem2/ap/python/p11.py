all_combinations = [
    (a, b, c) for a in range(1, 10) for b in range(1, 10) for c in range(1, 16)
]

pythagorean_triplets = list(
    filter(
        lambda triplet: triplet[0] ** 2 + triplet[1] ** 2 == triplet[2] ** 2,
        all_combinations,
    )
)

print(f"Found {len(pythagorean_triplets)} Pythagorean Triplets:")
for triplet in pythagorean_triplets:
    print(f"Side a: {triplet[0]}, Side b: {triplet[1]} -> Hypotenuse c: {triplet[2]}")
