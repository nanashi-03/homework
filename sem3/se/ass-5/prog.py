import math
import re
import sys


class HalsteadMetrics:
    """Calculates Halstead Structural Complexity Metrics for C Program Code."""

    def __init__(self, c_code: str):
        self.c_code = c_code
        self.operators, self.operands = self._parse_c_code(c_code)

        self.eta1 = len(set(self.operators))
        self.eta2 = len(set(self.operands))
        self.N1 = len(self.operators)
        self.N2 = len(self.operands)

        self.eta = self.eta1 + self.eta2
        self.N = self.N1 + self.N2

    def _parse_c_code(self, code_str: str):
        """Lexical analyzer to strip comments/preprocessors and extract operators & operands."""

        code_clean = re.sub(r"//.*?\n", "\n", code_str)
        code_clean = re.sub(r"/\*.*?\*/", "", code_clean, flags=re.DOTALL)


        strings = re.findall(r'"(?:\\.|[^"\\])*"', code_clean)
        code_clean = re.sub(r'"(?:\\.|[^"\\])*"', " STR_LITERAL ", code_clean)

        chars = re.findall(r"'(?:\\.|[^'\\])'", code_clean)
        code_clean = re.sub(r"'(?:\\.|[^'\\])'", " CHAR_LITERAL ", code_clean)


        code_clean = re.sub(r"#.*?\n", "\n", code_clean)


        c_operators = {
            "==",
            "!=",
            "<=",
            ">=",
            "&&",
            "||",
            "++",
            "--",
            "->",
            "<<",
            ">>",
            "+=",
            "-=",
            "*=",
            "/=",
            "%=",
            "&=",
            "|=",
            "^=",
            "+",
            "-",
            "*",
            "/",
            "%",
            "=",
            "<",
            ">",
            "!",
            "&",
            "|",
            "^",
            "~",
            "?",
            ":",
            ".",
            ",",
            ";",
            "(",
            ")",
            "[",
            "]",
            "{",
            "}",
        }


        c_keyword_operators = {
            "if",
            "else",
            "for",
            "while",
            "do",
            "switch",
            "case",
            "default",
            "return",
            "break",
            "continue",
            "goto",
            "sizeof",
            "typedef",
            "struct",
            "union",
            "enum",
        }


        token_pattern = re.compile(
            r"==|!=|<=|>=|&&|\|\||\+\+|--|->|<<|>>|"
            r"\+=|-=|\*=|/=|%=|&=|\|=|\^=|"
            r"[a-zA-Z_]\w*|"
            r"\d+(?:\.\d+)?|"
            r"[+\-*/%=<>!&|^~?:.,;()\[\]{}]"
        )

        tokens = token_pattern.findall(code_clean)

        operators = []
        operands = []

        str_idx, char_idx = 0, 0
        for token in tokens:
            if token == "STR_LITERAL":
                if str_idx < len(strings):
                    operands.append(strings[str_idx])
                    str_idx += 1
                else:
                    operands.append('""')
            elif token == "CHAR_LITERAL":
                if char_idx < len(chars):
                    operands.append(chars[char_idx])
                    char_idx += 1
                else:
                    operands.append("''")
            elif token in c_operators or token in c_keyword_operators:
                operators.append(token)
            elif re.match(r"(^\d+(\.\d+)?$|^[a-zA-Z_]\w*$)", token):
                operands.append(token)
            else:
                operators.append(token)

        return operators, operands


    def get_unique_counts(self):
        """(i) Unique number of operators (n1) and operands (n2)"""
        return self.eta1, self.eta2

    def get_total_counts(self):
        """(ii) Total number of operators (N1) and operands (N2)"""
        return self.N1, self.N2

    def actual_length(self):
        """(iii) Actual Program Length (N = N1 + N2)"""
        return self.N

    def expected_length(self):
        """(iv) Expected Program Length (N_hat = n1 log2 n1 + n2 log2 n2)"""
        if self.eta1 <= 0 or self.eta2 <= 0:
            return 0.0
        return (self.eta1 * math.log2(self.eta1)) + (
            self.eta2 * math.log2(self.eta2)
        )

    def program_volume(self):
        """(v) Program Volume (V = N log2 eta)"""
        if self.eta <= 0:
            return 0.0
        return self.N * math.log2(self.eta)

    def program_level(self):
        """(vii) Program Level (L = (2 / n1) * (n2 / N2))"""
        if self.eta1 == 0 or self.N2 == 0:
            return 0.0
        return (2.0 / self.eta1) * (self.eta2 / self.N2)

    def critical_volume(self):
        """(vi) Program Critical / Potential Volume (V* = L * V)"""
        return self.program_level() * self.program_volume()

    def effort(self):
        """(viii) Effort to develop Program (E = V / L)"""
        L = self.program_level()
        if L == 0:
            return 0.0
        return self.program_volume() / L



DEFAULT_C_CODE = """
#include <stdio.h>

int main() {
    int a, b, max;
    a = 10;
    b = 20;
    if (a > b) {
        max = a;
    } else {
        max = b;
    }
    printf("Maximum value is: %d\\n", max);
    return 0;
}
"""


def display_menu():
    print("\n" + "=" * 65)
    print("      HALSTEAD STRUCTURAL COMPLEXITY ANALYSIS MENU")
    print("=" * 65)
    print(" 1. (i)   Unique number of operands and operators (η1, η2)")
    print(" 2. (ii)  Total number of operands and operators (N1, N2)")
    print(" 3. (iii) Actual Program Length (N)")
    print(" 4. (iv)  Expected Program Length (N̂)")
    print(" 5. (v)   Program Volume (V)")
    print(" 6. (vi)  Program Critical / Potential Volume (V*)")
    print(" 7. (vii) Program Level (L)")
    print(" 8. (viii) Effort to Develop Program (E)")
    print(" 9. (ix)  Program Time (T) [Stroud number S = 18/sec]")
    print("10. (x)   Number of People Engaged (P) [Duration = 5 months]")
    print("11. [ALL] Display Comprehensive Complexity Report")
    print("12. [NEW] Enter / Load a New C Program")
    print(" 0. Exit")
    print("=" * 65)


def get_c_program_input():
    print("\nSelect C Program Input Method:")
    print("1. Use Default Sample C Program")
    print("2. Paste C Code directly into Terminal")
    print("3. Load C Code from a .c file")

    choice = input("Enter choice (1-3): ").strip()

    if choice == "2":
        print(
            "\nPaste your C Code below (Enter 'END' on a new line to finish):"
        )
        lines = []
        while True:
            line = input()
            if line.strip() == "END":
                break
            lines.append(line)
        return "\n".join(lines)
    elif choice == "3":
        filepath = input("Enter file path (e.g. program.c): ").strip()
        try:
            with open(filepath, "r") as f:
                return f.read()
        except FileNotFoundError as e:
            print(f"Error reading file: {e}. Falling back to default sample.")
            return DEFAULT_C_CODE
    else:
        print("\nUsing default C sample program.")
        return DEFAULT_C_CODE


def main():
    c_code = get_c_program_input()
    metrics = HalsteadMetrics(c_code)

    while True:
        display_menu()
        choice = input("Enter your selection (0-12): ").strip()

        if choice == "1":
            u_ops, u_opnds = metrics.get_unique_counts()
            print("\n--- (i) Unique Operators and Operands ---")
            print(f"Unique Operators (η1 / n1) : {u_ops}")
            print(f"Unique Operands  (η2 / n2) : {u_opnds}")
            print(f"Total Vocabulary (η = η1 + η2): {metrics.eta}")

        elif choice == "2":
            t_ops, t_opnds = metrics.get_total_counts()
            print("\n--- (ii) Total Operators and Operands ---")
            print(f"Total Operators (N1) : {t_ops}")
            print(f"Total Operands  (N2) : {t_opnds}")

        elif choice == "3":
            print("\n--- (iii) Actual Program Length ---")
            print("Formula: N = N1 + N2")
            print(f"Calculation: {metrics.N1} + {metrics.N2}")
            print(f"Actual Program Length (N) = {metrics.actual_length()}")

        elif choice == "4":
            print("\n--- (iv) Expected Program Length ---")
            print("Formula: N̂ = η1 log2(η1) + η2 log2(η2)")
            print(
                f"Expected Program Length (N̂) = {metrics.expected_length():.4f}"
            )

        elif choice == "5":
            print("\n--- (v) Program Volume ---")
            print("Formula: V = N * log2(η1 + η2)")
            print(
                f"Program Volume (V) = {metrics.program_volume():.4f} bits"
            )

        elif choice == "6":
            print("\n--- (vi) Program Critical / Potential Volume ---")
            print("Formula: V* = L * V")
            print(
                f"Program Critical Volume (V*) = {metrics.critical_volume():.4f} bits"
            )

        elif choice == "7":
            print("\n--- (vii) Program Level ---")
            print("Formula: L = (2 / η1) * (η2 / N2)")
            print(f"Program Level (L) = {metrics.program_level():.6f}")

        elif choice == "8":
            print("\n--- (viii) Effort to Develop Program ---")
            print("Formula: E = V / L")
            print(
                f"Effort (E) = {metrics.effort():.4f} elementary mental discriminations"
            )

        elif choice == "11":
            print("\n" + "=" * 65)
            print("         COMPREHENSIVE HALSTEAD METRICS REPORT")
            print("=" * 65)
            print(
                f" (i)   Unique Operators (η1)      : {metrics.eta1}"
            )
            print(
                f"       Unique Operands (η2)       : {metrics.eta2}"
            )
            print(
                f" (ii)  Total Operators (N1)       : {metrics.N1}"
            )
            print(
                f"       Total Operands (N2)        : {metrics.N2}"
            )
            print(
                f" (iii) Actual Program Length (N)  : {metrics.actual_length()}"
            )
            print(
                f" (iv)  Expected Length (N̂)        : {metrics.expected_length():.4f}"
            )
            print(
                f" (v)   Program Volume (V)         : {metrics.program_volume():.4f} bits"
            )
            print(
                f" (vi)  Critical Volume (V*)       : {metrics.critical_volume():.4f} bits"
            )
            print(
                f" (vii) Program Level (L)          : {metrics.program_level():.6f}"
            )
            print(
                f" (viii)Effort (E)                 : {metrics.effort():.4f} discriminations"
            )
            print("=" * 65)

        elif choice == "12":
            c_code = get_c_program_input()
            metrics = HalsteadMetrics(c_code)
            print("\nNew program loaded and metrics updated successfully!")

        elif choice == "0":
            print("\nExiting program. Goodbye!")
            sys.exit(0)

        else:
            print("Invalid choice. Please enter a number from 0 to 12.")


if __name__ == "__main__":
    main()
