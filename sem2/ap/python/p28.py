def sort_five_numbers(
    *, n1: float, n2: float, n3: float, n4: float, n5: float, reverse: bool = False
) -> list[float]:
    numbers_list = [n1, n2, n3, n4, n5]
    return sorted(numbers_list, reverse=reverse)


sorted_result = sort_five_numbers(n1=42, n2=7, n3=105, n4=23, n5=1)
print("Ascending order: ", sorted_result)

descending_result = sort_five_numbers(n5=1, n4=23, n3=105, n2=7, n1=42, reverse=True)
print("Descending order:", descending_result)
