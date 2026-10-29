import re

KEYWORDS = {"if", "for", "while", "int", "float", "char"}
OPERATORS = {"+", "-", "*", "/", "=", "<", ">"}
SYMBOLS = {",", "(", ")", ";", "?", "\"", "{", "}", "[", "]"}


def classify_token(token):
    if token in KEYWORDS:
        return "Keyword"

    if token in OPERATORS:
        return "Operator"

    if token in SYMBOLS:
        return "Symbol"

    if token.isdigit():
        value = int(token)

        if 1 <= value <= 999:
            return "Constant"
        else:
            return f"Error: Invalid constant '{token}' (must be between 1 and 999)"

    if re.fullmatch(r"[A-Za-z][A-Za-z0-9_]*", token):
        if len(token) <= 8:
            return "Identifier"
        else:
            return f"Error: Invalid identifier '{token}' (maximum 8 characters)"

    return f"Error: Invalid token '{token}'"


def tokenize(program):
    tokens = []
    i = 0

    while i < len(program):

        if program[i].isspace():
            i += 1
            continue

        if program[i] in OPERATORS or program[i] in SYMBOLS:
            tokens.append(program[i])
            i += 1
            continue

        start = i

        while (i < len(program)
               and not program[i].isspace()
               and program[i] not in OPERATORS
               and program[i] not in SYMBOLS):
            i += 1

        tokens.append(program[start:i])

    return tokens


def lexical_analyzer(program):
    tokens = tokenize(program)

    print("\nToken Classification")
    print("-" * 50)

    for token in tokens:
        classification = classify_token(token)

        print(f"{token:<20} -> {classification}")


def main():
    program = input("Enter a C statement:\n")

    lexical_analyzer(program)


if __name__ == "__main__":
    main()
