import re


class TextAnalyzer:
    def __init__(self, words: list[str]):
        self.words = words

    @classmethod
    def from_raw_text(cls, raw_text: str):
        cleaned_text = re.sub(r"[^\w\s]", "", raw_text.lower())
        words = cleaned_text.split()
        return cls(words)

    def find_palindromes(self) -> set[str]:
        return {word for word in self.words if word == word[::-1] and len(word) > 1}

    def find_unique_words(self) -> set[str]:
        return {word for word in self.words if self.words.count(word) == 1}


# --- Example Usage ---
raw_text = "The racecar was fast. Madam, that is a unique kayak!"
analyzer = TextAnalyzer.from_raw_text(raw_text)

print("--- Class Method Approach ---")
print("Palindromes:", analyzer.find_palindromes())
print("Unique Words:", analyzer.find_unique_words())
