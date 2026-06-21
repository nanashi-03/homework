import datetime

daily_coupons = {
    0: {"code": "MONSLASH", "rate": 0.10},
    1: {"code": "TUESTREAT", "rate": 0.12},
    2: {"code": "MIDWEEK", "rate": 0.15},
    3: {"code": "THURSTREAT", "rate": 0.12},
    4: {"code": "TGIF", "rate": 0.20},
    5: {"code": "WEEKEND25", "rate": 0.25},
    6: {"code": "SUNSAVER", "rate": 0.25},
}


def calculate_discount(cart_total, user_code):
    current_day = datetime.datetime.now().weekday()

    todays_coupon = daily_coupons[current_day]

    print(f"Today's valid coupon is: {todays_coupon['code']}")

    if user_code.upper() == todays_coupon["code"]:
        discount_amount = cart_total * todays_coupon["rate"]
        final_total = cart_total - discount_amount
        print("Coupon applied successfully!")
        return discount_amount, final_total
    else:
        print("Invalid coupon code for today.")
        return 0.0, cart_total


cart_value = int(input("Enter Cart Value: "))
current_day_index = datetime.datetime.now().weekday()
correct_code_for_today = daily_coupons[current_day_index]["code"]

print(f"Cart Total: ${cart_value:.2f}")
print(f"Entering coupon: {correct_code_for_today}")

discount, total = calculate_discount(cart_value, correct_code_for_today)

print(f"Discount: ${discount:.2f}")
print(f"Final Total: ${total:.2f}")
