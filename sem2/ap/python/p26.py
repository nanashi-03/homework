def matrix_multiply(A, B):
    """Multiplies two matrices using pure Python nested loops."""
    rows_A = len(A)
    cols_A = len(A[0])
    rows_B = len(B)
    cols_B = len(B[0])

    if cols_A != rows_B:
        raise ValueError("Columns of A must match rows of B.")

    result = [[0 for _ in range(cols_B)] for _ in range(rows_A)]

    for i in range(rows_A):
        for j in range(cols_B):
            for k in range(cols_A):
                result[i][j] += A[i][k] * B[k][j]

    return result


matrix_a = [[1, 2], [3, 4]]

matrix_b = [[5, 6], [7, 8]]

print("Result :")
print(matrix_multiply(matrix_a, matrix_b))
