#!/bin/bash

while true; do
    echo "--- New Operation ---"
    read -p "Enter value for userv1: " userv1
    read -p "Enter value for userv2: " userv2

    num_regex="^-?[0-9]*\.?[0-9]+$"

    if [[ $userv1 =~ $num_regex ]] && [[ $userv2 =~ $num_regex ]]; then
        sum=$(echo "$userv1 + $userv2" | bc -l)
        diff=$(echo "$userv1 - $userv2" | bc -l)
        prod=$(echo "$userv1 * $userv2" | bc -l)

        echo "the sum of '$userv1' and '$userv2' is $sum"
        echo "the subtraction of '$userv1' and '$userv2' is $diff"
        echo "the multiplication of '$userv1' and '$userv2' is $prod"

        # Check for division by zero
        if (( $(echo "$userv2 == 0" | bc -l) )); then
            echo "Error: Division by zero is not allowed."
        else
            div=$(echo "$userv1 / $userv2" | bc -l)
            echo "the division of '$userv1' and '$userv2' is $div"
        fi
    else
        echo "Error: Arithmetic operations cannot be performed on non-numeric characters."
    fi

    echo "----------------------"
    read -p "Do you want to perform another operation? (y/n): " choice
    if [[ "$choice" != "y" ]]; then
        echo "Goodbye!"
        break
    fi
done
