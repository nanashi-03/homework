import re
from collections import Counter


class TextRepeater:
    def __init__(self, text: str):
        self.text = text
        self.words = re.sub(r"[^\w\s]", "", text.lower()).split()
        self.word_counts = Counter(self.words)

    def __len__(self) -> int:
        repetitive_words = [
            word for word, count in self.word_counts.items() if count > 1
        ]

        if not repetitive_words:
            return len(self.text)

        total_rep_length = sum(
            len(word) * self.word_counts[word] for word in repetitive_words
        )
        return total_rep_length

    def get_most_common(self, n: int = 1) -> list[tuple[str, int]]:
        return self.word_counts.most_common(n)


text_with_repeats = "The blue sky is blue and the sun is bright."
doc1 = TextRepeater(text_with_repeats)

print("--- Case 1: With Repetitions ---")
print(f"Original Text: '{text_with_repeats}'")
print(f"Most common words: {doc1.get_most_common(3)}")
print(f"Overloaded len() output: {len(doc1)}\n")


text_unique = "Python is great."
doc2 = TextRepeater(text_unique)

print("--- Case 2: Without Repetitions ---")
print(f"Original Text: '{text_unique}'")
print(f"Most common words: {doc2.get_most_common(1)}")
print(f"Overloaded len() output: {len(doc2)}")
