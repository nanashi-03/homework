import re


def regex_replace(text, pattern, replacement):
    try:
        regex = re.compile(pattern)
    except re.error as err:
        raise ValueError(f"invalid regex pattern: {err}")

    return regex.sub(replacement, text)


def manual_replace(text, pattern, replacement):
    if len(pattern) == 0:
        return text, 0

    result = []
    match_count = 0

    n_text = len(text)
    n_pat = len(pattern)

    i = 0

    while i <= n_text - n_pat:
        if text[i:i + n_pat] == pattern:
            result.append(replacement)
            match_count += 1
            i += n_pat
        else:
            result.append(text[i])
            i += 1

    if i < n_text:
        result.append(text[i:])

    return "".join(result), match_count


def main():
    sample_text = (
        "One morning, when Gregor Samsa woke from troubled dreams, "
        "he found himself transformed in his bed into a horrible vermin. "
        "He lay on his armour-like back, and if he lifted his head a "
        "little he could see his brown belly, slightly domed and divided "
        "by arches into stiff sections."
    )

    print("Original Text:")
    print(sample_text)
    print("-" * 60)

    # Manual replacement
    exact_pattern = "he"
    exact_replacement = "[redacted]"

    manual_result, count = manual_replace(
        sample_text,
        exact_pattern,
        exact_replacement
    )

    print(
        f'Manual Algorithm ("{exact_pattern}" -> '
        f'"{exact_replacement}", Matches found: {count}):'
    )
    print(manual_result)
    print("-" * 60)

    regex_pattern = r"\b[lhb]\w{2}\b"
    regex_replacement = "[redacted]"

    try:
        regex_result = regex_replace(
            sample_text,
            regex_pattern,
            regex_replacement
        )
    except ValueError as err:
        print(f"Regex Error: {err}")
        return

    print(
        f'Regex Replace (Pattern: "{regex_pattern}" '
        f'(A three letter word starting with l, h, or b) '
        f'-> "{regex_replacement}") :'
    )
    print(regex_result)


if __name__ == "__main__":
    main()
