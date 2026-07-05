import time


def geometric_progression(a, q, limit=100000):
    loop_time = 0
    current_term = a

    while current_term <= limit:
        start_loop = time.perf_counter()

        yield current_term
        current_term *= q

        end_loop = time.perf_counter()
        loop_time += end_loop - start_loop

    return loop_time


a = 2
q = 1.5

total_start = time.perf_counter()

gp = geometric_progression(a, q)

print("Generated Terms:")
while True:
    try:
        term = next(gp)
        print(f"{term:.2f}")
    except StopIteration as e:
        inside_loop_time = e.value
        break

total_end = time.perf_counter()

total_time = total_end - total_start

print("\n--- Timing Results ---")
print(f"Total execution time: {total_time * 1000:.4f} ms")
print(f"Time spent inside the loop: {inside_loop_time * 1000:.4f} ms")
print(
    f"Time spent outside (printing/overhead): {(total_time - inside_loop_time) * 1000:.4f} ms"
)
