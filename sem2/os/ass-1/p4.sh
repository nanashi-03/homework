#!/bin/bash

read -p "Enter the directory path to scan (leave blank for current): " target_dir
target_dir=${target_dir:-.}

if [[ ! -d "$target_dir" ]]; then
    echo "Error: Directory '$target_dir' does not exist."
    exit 1
fi

echo "Scanning: $(realpath "$target_dir")"
echo "----------------------------------------"

files_list=$(find "$target_dir" -maxdepth 1 -type f)
dirs_list=$(find "$target_dir" -maxdepth 1 -type d ! -path "$target_dir")

file_count=$(echo "$files_list" | grep -c '^' || echo 0)
dir_count=$(echo "$dirs_list" | grep -c '^' || echo 0)
total_count=$((file_count + dir_count))

echo "--- DIRECTORIES ($dir_count) ---"
if [ "$dir_count" -gt 0 ]; then
    echo "$dirs_list" | xargs -n 1 basename
else
    echo "No sub-directories found."
fi

echo ""
echo "--- FILES ($file_count) ---"
if [ "$file_count" -gt 0 ]; then
    echo "$files_list" | xargs -n 1 basename
else
    echo "No files found."
fi

echo ""
echo "Total item count: $total_count"
echo ""
echo "----------------------------------------"

echo "--- RECENT ACTIVITY (Past 7 Days) ---"

recent_size=$(find "$target_dir" -type f -mtime -7 -print0 | xargs -0 du -ch 2>/dev/null | tail -n 1 | cut -f 1)

if [[ -z "$recent_size" || "$recent_size" == "0" ]]; then
    echo "Total size of files created in past week: 0B"
else
    echo "Total size of files created in past week: $recent_size"
fi
echo "----------------------------------------"
