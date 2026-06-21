import re

phone_pattern = re.compile(r"^(\+?\d{1,3})?[-.\s]?\(?\d{3}\)?[-.\s]?\d{3}[-.\s]?\d{4}$")

test_numbers = [
    "123-456-7890",
    "(123) 456-7890",
    "+91 123 456 7890",
    "+91 1234567890",
    "+91 123 456 7890",
    "+91 1234 567 890",
    "123.456.7890",
    "1234567890",
    "123-456-789",
    "A23-456-7890",
    "123-456-789012",
]

print("Phone Number Validation Results:")
for number in test_numbers:
    if phone_pattern.match(number):
        print(f"✅ VALID  : {number}")
    else:
        print(f"❌ INVALID: {number}")
