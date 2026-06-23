import pytest


def compute_power(base: float, exponent: float) -> float:
    if base == 0 and exponent < 0:
        raise ZeroDivisionError("Cannot raise zero to a negative power.")
    return base**exponent


@pytest.mark.parametrize(
    "base, exponent, expected",
    [
        (2, 2, 4),
        (2, 3, 8),
        (1, 9, 1),
        (0, 9, 0),
    ],
)
def test_compute_power_success(base, exponent, expected):
    assert compute_power(base, exponent) == expected


@pytest.mark.parametrize(
    "base, exponent, expected_exception",
    [
        (0, -1, ZeroDivisionError),
    ],
)
def test_compute_power_errors(base, exponent, expected_exception):
    with pytest.raises(expected_exception):
        compute_power(base, exponent)
