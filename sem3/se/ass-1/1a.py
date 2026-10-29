class JustifyOptions:
    def __init__(self, max_width, indent):
        self.max_width = max_width
        self.indent = indent

class JustificationError(Exception):
    def __init__(self, message: str) -> None:
        self.message = message
        super().__init__(self.message)

def justify_file(file_path, opts):
    try:
        with open(file_path, "r", encoding="utf-8") as file:
            input_text = file.read()
    except FileNotFoundError as err:
        raise JustificationError(f"failed to read file {file_path}: {err}")

    justified_text = justify_text(input_text, opts)

    try:
        with open(file_path, "w", encoding="utf-8") as file:
            file.write(justified_text)
    except FileNotFoundError as err:
        raise JustificationError(f"failed to write back to file {file_path}: {err}")


def justify_text(text, opts):
    if opts.max_width <= 0:
        return ""

    normalized = text.replace("\r\n", "\n")
    raw_paragraphs = normalized.split("\n\n")

    justified_paragraphs = []

    for raw_para in raw_paragraphs:
        trimmed = raw_para.strip()

        if trimmed == "":
            continue

        lines = justify_paragraph(trimmed, opts)
        justified_paragraphs.append("\n".join(lines))

    return "\n\n".join(justified_paragraphs)


def justify_paragraph(para, opts):
    words = para.split()

    if len(words) == 0:
        return []

    lines = []
    i = 0

    while i < len(words):
        current_indent = ""

        line_len = len(current_indent)
        j = i

        while j < len(words):
            word_len = len(words[j])
            min_spaces_needed = j - i

            if line_len + word_len + min_spaces_needed > opts.max_width:
                break

            line_len += word_len
            j += 1

        if j == i:
            j = i + 1

        line_words = words[i:j]
        is_last_line = (j == len(words))

        formatted_line = format_line(
            line_words,
            current_indent,
            opts.max_width,
            is_last_line
        )

        lines.append(formatted_line)
        i = j

    return lines


def format_line(words, indent, max_width, is_last_line):
    result = indent

    num_words = len(words)

    if num_words == 0:
        return result

    word_char_count = sum(len(word) for word in words)
    gaps = num_words - 1

    # Last line or single-word line
    if num_words == 1 or is_last_line:
        result += words[0]

        for word in words[1:]:
            result += " " + word

        if len(result) < max_width:
            result += " " * (max_width - len(result))

        return result

    total_spaces = max_width - len(indent) - word_char_count

    base_spaces = total_spaces // gaps
    extra_spaces = total_spaces % gaps

    for k in range(num_words):
        result += words[k]

        if k < gaps:
            spaces_to_insert = base_spaces

            if k < extra_spaces:
                spaces_to_insert += 1

            result += " " * spaces_to_insert

    return result


def main():
    file_path = "sample.txt"

    opts = JustifyOptions(
        max_width=45,
        indent="    "
    )

    try:
        justify_file(file_path, opts)
    except JustificationError as err:
        print(f"Error formatting file: {err}")
        return

    print("File successfully justified and overwritten!")

    try:
        with open(file_path, "r", encoding="utf-8") as file:
            updated_content = file.read()
    except JustificationError as err:
        print(f"Error reading updated file: {err}")
        return

    print("\nFile Contents After Justification")
    print(updated_content)


if __name__ == "__main__":
    main()
