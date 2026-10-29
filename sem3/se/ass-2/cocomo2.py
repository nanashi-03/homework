import math

A_COCOMO_II = 2.94
B_COCOMO_II = 0.91

# Mapping: 1=Very Low, 2=Low, 3=Nominal, 4=High, 5=Very High, 6=Extra High
# Scale Factors (SF)
SCALE_FACTORS = {
    'PREC': {1: 6.20, 2: 4.96, 3: 3.72, 4: 2.48, 5: 1.24, 6: 0.00},
    'FLEX': {1: 5.07, 2: 4.05, 3: 3.04, 4: 2.03, 5: 1.01, 6: 0.00},
    'RESL': {1: 7.07, 2: 5.65, 3: 4.24, 4: 2.83, 5: 1.41, 6: 0.00},
    'TEAM': {1: 5.48, 2: 4.38, 3: 3.29, 4: 2.19, 5: 1.10, 6: 0.00},
    'PMAT': {1: 7.80, 2: 6.24, 3: 4.68, 4: 3.12, 5: 1.56, 6: 0.00}
}

# Early Design Cost Drivers
EARLY_DESIGN_EM = {
    'RCPX': {1: 0.49, 2: 0.60, 3: 0.83, 4: 1.00, 5: 1.33, 6: 1.91},
    'RUSE': {1: 0.95, 2: 0.95, 3: 1.00, 4: 1.07, 5: 1.15, 6: 1.24},
    'PDIF': {1: 0.87, 2: 0.87, 3: 1.00, 4: 1.29, 5: 1.81, 6: 2.61},
    'PERS': {1: 2.12, 2: 1.62, 3: 1.26, 4: 1.00, 5: 0.83, 6: 0.63},
    'PREX': {1: 1.59, 2: 1.33, 3: 1.12, 4: 1.00, 5: 0.87, 6: 0.71},
    'FCIL': {1: 1.43, 2: 1.30, 3: 1.10, 4: 1.00, 5: 0.87, 6: 0.73},
    'SCED': {1: 1.43, 2: 1.14, 3: 1.00, 4: 1.00, 5: 1.00, 6: 1.00}
}

# Post Architecture Cost Drivers
POST_ARCH_EM = {
    'RELY': {1: 0.82, 2: 0.92, 3: 1.00, 4: 1.10, 5: 1.26, 6: 1.26},
    'DATA': {1: 0.90, 2: 0.90, 3: 1.00, 4: 1.14, 5: 1.28, 6: 1.28},
    'CPLX': {1: 0.73, 2: 0.87, 3: 1.00, 4: 1.17, 5: 1.34, 6: 1.74},
    'RUSE': {1: 0.95, 2: 0.95, 3: 1.00, 4: 1.07, 5: 1.15, 6: 1.24},
    'DOCU': {1: 0.81, 2: 0.91, 3: 1.00, 4: 1.11, 5: 1.23, 6: 1.23},
    'TIME': {1: 1.00, 2: 1.00, 3: 1.00, 4: 1.11, 5: 1.29, 6: 1.63},
    'STOR': {1: 1.00, 2: 1.00, 3: 1.00, 4: 1.05, 5: 1.17, 6: 1.46},
    'PVOL': {1: 0.87, 2: 0.87, 3: 1.00, 4: 1.15, 5: 1.30, 6: 1.30},
    'ACAP': {1: 1.42, 2: 1.19, 3: 1.00, 4: 0.85, 5: 0.71, 6: 0.71},
    'PCAP': {1: 1.34, 2: 1.15, 3: 1.00, 4: 0.88, 5: 0.76, 6: 0.76},
    'PCON': {1: 1.29, 2: 1.12, 3: 1.00, 4: 0.90, 5: 0.81, 6: 0.81},
    'AEXP': {1: 1.22, 2: 1.10, 3: 1.00, 4: 0.88, 5: 0.81, 6: 0.81},
    'PEXP': {1: 1.19, 2: 1.09, 3: 1.00, 4: 0.91, 5: 0.85, 6: 0.85},
    'LTEX': {1: 1.20, 2: 1.09, 3: 1.00, 4: 0.91, 5: 0.84, 6: 0.84},
    'TOOL': {1: 1.17, 2: 1.09, 3: 1.00, 4: 0.90, 5: 0.78, 6: 0.78},
    'SITE': {1: 1.22, 2: 1.09, 3: 1.00, 4: 0.93, 5: 0.86, 6: 0.80},
    'SCED': {1: 1.43, 2: 1.14, 3: 1.00, 4: 1.00, 5: 1.00, 6: 1.00}
}

def get_user_input(prompt_text, default_val):
    val = input(prompt_text).strip()
    if val == "":
        return default_val
    return float(val)

def calculate_scale_factors():
    print("\n--- Enter Scale Factors (1=V.Low to 6=E.High) ---")
    print("(Press Enter to default to Nominal = 3)")
    sf_sum = 0
    for sf in SCALE_FACTORS:
        val = int(get_user_input(f"{sf}: ", 3))
        val = max(1, min(6, val))
        sf_sum += SCALE_FACTORS[sf][val]
    return sf_sum

def calculate_cost_drivers(driver_dict):
    print("\n--- Enter Cost Drivers (1=V.Low to 6=E.High) ---")
    print("(Press Enter to default to Nominal = 3)")
    em_product = 1.0
    for driver in driver_dict:
        val = int(get_user_input(f"{driver}: ", 3))
        val = max(1, min(6, val))
        em_product *= driver_dict[driver][val]
    return em_product

def application_composition_menu():
    print("\n" + "="*35)
    print("   Application Composition Model")
    print("="*35)
    print("Using default values provided in prompt.")

    screens_simple = get_user_input("Enter SIMPLE Screens (Default: 5): ", 5)
    screens_avg = get_user_input("Enter AVERAGE Screens (Default: 5): ", 5)
    screens_complex = get_user_input("Enter COMPLEX Screens (Default: 4): ", 4)

    reports_simple = get_user_input("Enter SIMPLE Reports (Default: 2): ", 2)
    reports_avg = get_user_input("Enter AVERAGE Reports (Default: 2): ", 2)
    reports_complex = get_user_input("Enter COMPLEX Reports (Default: 2): ", 2)

    components = get_user_input("Enter 3GL Components (Default: 10): ", 10)

    reuse_percent = get_user_input("Enter Reuse Percentage (Default: 90): ", 90)
    prod = get_user_input("Enter Productivity NOP/month (Default: 25): ", 25)
    labor_rate = get_user_input("Enter Labor Rate $/month (Default: 1500): ", 1500)

    # Weights: Screens (1, 2, 3), Reports (2, 5, 8), Components (10)
    op_screens = (screens_simple * 1) + (screens_avg * 2) + (screens_complex * 3)
    op_reports = (reports_simple * 2) + (reports_avg * 5) + (reports_complex * 8)
    op_components = components * 10

    total_op = op_screens + op_reports + op_components
    nop = (total_op * (100 - reuse_percent)) / 100.0
    effort = nop / prod
    total_cost = effort * labor_rate

    while True:
        print("\n--- App Composition Sub-Menu ---")
        print("e) Determine the Object Point")
        print("f) Determine the New Object Point")
        print("g) Determine the Effort")
        print("h) Determine the Total Project Cost")
        print("i) Return to Main Menu")

        choice = input("Select an option (e-i): ").lower()
        if choice == 'e':
            print(f"\n-> Object Points (OP): {total_op}")
        elif choice == 'f':
            print(f"\n-> New Object Points (NOP): {nop:.2f}")
        elif choice == 'g':
            print(f"\n-> Estimated Effort: {effort:.2f} Person-Months")
        elif choice == 'h':
            print(f"\n-> Total Project Cost: ${total_cost:,.2f}")
        elif choice == 'i':
            break
        else:
            print("Invalid choice.")

def early_design_menu():
    print("\n" + "="*35)
    print("      Early Design Stage Model")
    print("="*35)

    kloc = get_user_input("Enter total Size in KLOC (e.g., 50): ", 50)
    duration_years = 5
    duration_months = duration_years * 12

    sf_sum = calculate_scale_factors()
    exponent_e = B_COCOMO_II + (0.01 * sf_sum)

    em_product = calculate_cost_drivers(EARLY_DESIGN_EM)

    effort = A_COCOMO_II * (kloc ** exponent_e) * em_product
    people = effort / duration_months

    while True:
        print("\n--- Early Design Sub-Menu ---")
        print("a) Determine the Effort")
        print("b) Determine the Number of People (Duration = 5 Years)")
        print("c) Return to Main Menu")

        choice = input("Select an option (a-c): ").lower()
        if choice == 'a':
            print(f"\n-> Estimated Effort: {effort:.2f} Person-Months")
        elif choice == 'b':
            print(f"\n-> Number of People Engaged: {people:.2f} Persons (~{math.ceil(people)} Developers)")
        elif choice == 'c':
            break
        else:
            print("Invalid choice.")

def post_architecture_menu():
    print("\n" + "="*35)
    print("   Post Architecture Stage Model")
    print("="*35)

    kloc = get_user_input("Enter total Size in KLOC (e.g., 50): ", 50)
    duration_years = 5
    duration_months = duration_years * 12

    sf_sum = calculate_scale_factors()
    exponent_e = B_COCOMO_II + (0.01 * sf_sum)

    em_product = calculate_cost_drivers(POST_ARCH_EM)

    effort = A_COCOMO_II * (kloc ** exponent_e) * em_product
    people = effort / duration_months

    while True:
        print("\n--- Post Architecture Sub-Menu ---")
        print("a) Determine the Effort")
        print("b) Determine the Number of People (Duration = 5 Years)")
        print("c) Return to Main Menu")

        choice = input("Select an option (a-c): ").lower()
        if choice == 'a':
            print(f"\n-> Estimated Effort: {effort:.2f} Person-Months")
        elif choice == 'b':
            print(f"\n-> Number of People Engaged: {people:.2f} Persons (~{math.ceil(people)} Developers)")
        elif choice == 'c':
            break
        else:
            print("Invalid choice.")

def main():
    while True:
        print("\n" + "="*40)
        print("       COCOMO II ESTIMATION MODEL")
        print("="*40)
        print("1. Application Composition Model")
        print("2. Early Design Stage Model")
        print("3. Post Architecture Stage Model")
        print("4. Exit")

        choice = input("Enter your choice (1-4): ")

        if choice == '1':
            application_composition_menu()
        elif choice == '2':
            early_design_menu()
        elif choice == '3':
            post_architecture_menu()
        elif choice == '4':
            print("\nExiting program. Goodbye!")
            break
        else:
            print("Invalid choice. Please select 1, 2, 3, or 4.")

if __name__ == "__main__":
    main()
