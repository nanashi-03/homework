#!/bin/bash

read -p "Enter the directory path to analyze (leave blank for current): " target_dir
target_dir=${target_dir:-.}

if [[ ! -d "$target_dir" ]]; then
    echo "Error: Directory '$target_dir' does not exist."
    exit 1
fi

total_bytes=$(ls -l "$target_dir" | awk '{sum += $5} END {print sum}')

today=$(date "+%b %e")
today_bytes=$(ls -l "$target_dir" | grep "$today" | awk '{sum += $5} END {print sum}')

total_bytes=${total_bytes:-0}
today_bytes=${today_bytes:-0}

echo "----------------------------------------"
echo "Directory: $(realpath "$target_dir")"
echo "----------------------------------------"
echo "Total bytes used              : $total_bytes"
echo "Total size of files from today: $today_bytes"
echo "----------------------------------------"
