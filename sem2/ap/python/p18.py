import heapq
from typing import Any, Iterable


def get_extreme_numbers(
    collection: Iterable[Any], n: int, finding: str = "largest"
) -> list[Any]:
    if finding.lower() == "largest":
        return heapq.nlargest(n, collection)
    elif finding.lower() == "smallest":
        return heapq.nsmallest(n, collection)
    else:
        raise ValueError(
            "The 'finding' parameter must be either 'largest' or 'smallest'."
        )


numbers = [42, 1, 17, 99, 4, 23, 88, 12, 105, 55]

three_largest = get_extreme_numbers(numbers, n=3, finding="largest")
print(f"The 3 largest numbers:  {three_largest}")

three_smallest = get_extreme_numbers(numbers, n=3, finding="smallest")
print(f"The 3 smallest numbers: {three_smallest}")
