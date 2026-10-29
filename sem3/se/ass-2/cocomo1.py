import math

# Constants for Basic and Intermediate COCOMO
# Format: { 'Type': (Basic_a, Basic_b, Inter_a, Inter_b, c, d) }
COCOMO_CONSTANTS = {
    "Organic": (2.4, 1.05, 3.2, 1.05, 2.5, 0.38),
    "Semi-detached": (3.0, 1.12, 3.0, 1.12, 2.5, 0.35),
    "Embedded": (3.6, 1.20, 2.8, 1.20, 2.5, 0.32)
}

# Mapping: 1=Very Low, 2=Low, 3=Nominal, 4=High, 5=Very High, 6=Extra High
# Missing extremes in Boehm's original model are mapped to the nearest valid value.
COST_DRIVERS_TABLE = {
    "RELY": {1: 0.75, 2: 0.88, 3: 1.00, 4: 1.15, 5: 1.40, 6: 1.40},
    "DATA": {1: 0.94, 2: 0.94, 3: 1.00, 4: 1.08, 5: 1.16, 6: 1.16},
    "CPLX": {1: 0.70, 2: 0.85, 3: 1.00, 4: 1.15, 5: 1.30, 6: 1.65},
    "TIME": {1: 1.00, 2: 1.00, 3: 1.00, 4: 1.11, 5: 1.30, 6: 1.66},
    "STOR": {1: 1.00, 2: 1.00, 3: 1.00, 4: 1.06, 5: 1.21, 6: 1.56},
    "VIRT": {1: 0.87, 2: 0.87, 3: 1.00, 4: 1.15, 5: 1.30, 6: 1.30},
    "TURN": {1: 0.87, 2: 0.87, 3: 1.00, 4: 1.07, 5: 1.15, 6: 1.15},
    "ACAP": {1: 1.46, 2: 1.19, 3: 1.00, 4: 0.86, 5: 0.71, 6: 0.71},
    "AEXP": {1: 1.29, 2: 1.13, 3: 1.00, 4: 0.91, 5: 0.82, 6: 0.82},
    "PCAP": {1: 1.42, 2: 1.17, 3: 1.00, 4: 0.86, 5: 0.70, 6: 0.70},
    "VEXP": {1: 1.21, 2: 1.10, 3: 1.00, 4: 0.90, 5: 0.90, 6: 0.90},
    "LEXP": {1: 1.14, 2: 1.07, 3: 1.00, 4: 0.95, 5: 0.95, 6: 0.95},
    "MODP": {1: 1.24, 2: 1.10, 3: 1.00, 4: 0.91, 5: 0.82, 6: 0.82},
    "TOOL": {1: 1.24, 2: 1.10, 3: 1.00, 4: 0.91, 5: 0.83, 6: 0.83},
    "SCED": {1: 1.23, 2: 1.08, 3: 1.00, 4: 1.04, 5: 1.10, 6: 1.10},
}

COST_DRIVER_PROMPTS = [
    ("1. Required Software Reliability (RELY)", "RELY"),
    ("2. Data Base Size (DATA)", "DATA"),
    ("3. Product Complexity (CPLX)", "CPLX"),
    ("4. Execution Time Constraint (TIME)", "TIME"),
    ("5. Main Storage Constraint (STOR)", "STOR"),
    ("6. Virtual Machine Volatility (VIRT)", "VIRT"),
    ("7. Computer Turnaround Time (TURN)", "TURN"),
    ("8. Analyst Capability (ACAP)", "ACAP"),
    ("9. Applications Experience (AEXP)", "AEXP"),
    ("10. Programmer Capability (PCAP)", "PCAP"),
    ("11. Virtual Machine Experience (VEXP)", "VEXP"),
    ("12. Programming Language Experience (LEXP)", "LEXP"),
    ("13. Modern Programming Practices (MODP)", "MODP"),
    ("14. Use of Software Tools (TOOL)", "TOOL"),
    ("15. Required Development Schedule (SCED)", "SCED")
]

def determine_project_type(kloc):
    if kloc <= 50:
        return "Organic"
    elif kloc <= 300:
        return "Semi-detached"
    else:
        return "Embedded"

def calculate_eaf():
    print("\n--- Enter Cost Driver Ratings ---")
    print("Scale:")
    print("1 = Very Low | 2 = Low | 3 = Nominal | 4 = High | 5 = Very High | 6 = Extra High")
    print("(Press Enter without typing a number to default to 3 - Nominal)")

    eaf = 1.0
    for display_name, dict_key in COST_DRIVER_PROMPTS:
        while True:
            val_input = input(f"{display_name}: ").strip()

            if val_input == "":
                val = 3
            else:
                try:
                    val = int(val_input)
                except ValueError:
                    print("  -> Invalid input. Please enter a number between 1 and 6.")
                    continue

            if 1 <= val <= 6:
                multiplier = COST_DRIVERS_TABLE[dict_key][val]
                eaf *= multiplier
                break
            else:
                print("  -> Out of range. Please enter a number between 1 and 6.")

    return eaf

def basic_cocomo_menu():
    try:
        loc = float(input("\nEnter total Lines of Code (LOC): "))
    except ValueError:
        print("Invalid input. Returning to main menu.")
        return

    kloc = loc / 1000.0
    proj_type = determine_project_type(kloc)
    a, b, _, _, c, d = COCOMO_CONSTANTS[proj_type]

    effort = a * (kloc ** b)
    time = c * (effort ** d)
    people = effort / time

    print(f"\n[+] Project Size: {kloc:.2f} KLOC")
    print(f"[+] Determined Project Type: {proj_type}")

    while True:
        print("\n--- Basic COCOMO Sub-Menu ---")
        print("a) Determine the Effort")
        print("b) Determine the Time")
        print("c) Determine the Number of People")
        print("d) Return to Main Menu")

        choice = input("Select an option (a-d): ").lower()

        if choice == 'a':
            print(f"\n-> Estimated Effort: {effort:.2f} Person-Months")
        elif choice == 'b':
            print(f"\n-> Estimated Time (Duration): {time:.2f} Months")
        elif choice == 'c':
            print(f"\n-> Estimated Number of People: {people:.2f} Persons (~{math.ceil(people)} Developers)")
        elif choice == 'd':
            break
        else:
            print("Invalid choice.")

def intermediate_cocomo_menu():
    try:
        loc = float(input("\nEnter total Lines of Code (LOC): "))
    except ValueError:
        print("Invalid input. Returning to main menu.")
        return

    kloc = loc / 1000.0
    proj_type = determine_project_type(kloc)
    _, _, a, b, c, d = COCOMO_CONSTANTS[proj_type]

    print(f"\n[+] Project Size: {kloc:.2f} KLOC")
    print(f"[+] Determined Project Type: {proj_type}")

    eaf = calculate_eaf()

    effort = a * (kloc ** b) * eaf
    time = c * (effort ** d)
    people = effort / time

    while True:
        print("\n--- Intermediate COCOMO Sub-Menu ---")
        print("a) Determine the Effort")
        print("b) Determine the Time")
        print("c) Determine the Number of People")
        print("d) View the Effort Adjustment Factor (EAF)")
        print("e) Return to Main Menu")

        choice = input("Select an option (a-e): ").lower()

        if choice == 'a':
            print(f"\n-> Estimated Effort: {effort:.2f} Person-Months")
        elif choice == 'b':
            print(f"\n-> Estimated Time (Duration): {time:.2f} Months")
        elif choice == 'c':
            print(f"\n-> Estimated Number of People: {people:.2f} Persons (~{math.ceil(people)} Developers)")
        elif choice == 'd':
            print(f"\n-> Calculated EAF: {eaf:.4f}")
        elif choice == 'e':
            break
        else:
            print("Invalid choice.")

def main():
    while True:
        print("\n" + "="*40)
        print("       COCOMO I ESTIMATION MODEL")
        print("="*40)
        print("1. Basic COCOMO")
        print("2. Intermediate COCOMO")
        print("3. Exit")

        choice = input("Enter your choice (1-3): ")

        if choice == '1':
            basic_cocomo_menu()
        elif choice == '2':
            intermediate_cocomo_menu()
        elif choice == '3':
            print("\nExiting program.")
            break
        else:
            print("Invalid choice. Please select 1, 2, or 3.")

if __name__ == "__main__":
    main()
