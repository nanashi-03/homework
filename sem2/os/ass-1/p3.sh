#!/bin/bash

read -p "Enter a four-digit integer: " num

if [[ ! $num =~ ^[0-9]{4}$ ]]; then
    echo "Error: You must enter exactly four digits (e.g., 7890)."
    exit 1
fi

d1=${num:0:1}
d2=${num:1:1}
d3=${num:2:1}
d4=${num:3:1}

sum=$((d1 + d2 + d3 + d4))

reverse="${d4}${d3}${d2}${d1}"

echo "------------------------------"
echo "Results for Number: $num"
echo "------------------------------"
echo "Sum of the digits   : $sum"
echo "Reversed integer    : $reverse"
echo "------------------------------"
