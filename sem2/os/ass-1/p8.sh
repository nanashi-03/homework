#!/bin/bash

if [ $# -ne 1 ]; then
    echo "Usage: $0 <number>"
    echo "Example: $0 7"
    exit 1
fi

num=$1
if ! [[ "$num" =~ ^-?[0-9]+$ ]]; then
    echo "Error: '$num' is not a valid integer."
    exit 1
fi

echo "--- Multiplication Table for $num ---"
echo "-------------------------------------"

for i in {1..10}; do
    result=$((num * i))
    echo "$num x $i = $result"
done

echo "-------------------------------------"
