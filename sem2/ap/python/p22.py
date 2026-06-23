import cProfile
import math
import pstats


def find_triples_naive(n: int) -> list[tuple[int, int, int]]:
    # N^3
    triples = []
    for a in range(1, n + 1):
        for b in range(a, n + 1):
            for c in range(b, n + 1):
                if a**2 + b**2 == c**2:
                    triples.append((a, b, c))
    return triples


def find_triples_optimized(n: int) -> list[tuple[int, int, int]]:
    # N^2
    triples = []
    for a in range(1, n + 1):
        for b in range(a, n + 1):
            c_squared = a**2 + b**2
            c = math.isqrt(c_squared)  # Integer square root
            if c <= n and c**2 == c_squared:
                triples.append((a, b, c))
    return triples


if __name__ == "__main__":
    N = 300

    p1 = cProfile.Profile()
    p2 = cProfile.Profile()

    print(f"Profiling find_triples_naive and find_triplets_optimized with N={N}...")
    p1.enable()

    res1 = find_triples_naive(N)

    p1.disable()

    p2.enable()

    res2 = find_triples_optimized(N)

    p2.disable()

    print(f"Found {len(res1)} triples.\n")
    print(f"Found {len(res2)} triples.\n")

    stat1 = pstats.Stats(p1).sort_stats("cumulative")
    stat1.print_stats()

    stat2 = pstats.Stats(p2).sort_stats("cumulative")
    stat2.print_stats()
