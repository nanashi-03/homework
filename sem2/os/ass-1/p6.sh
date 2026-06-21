#!/bin/bash

echo "-------------------------------------------------------------------------------"
printf "%-15s %-20s %s\n" "PERMISSIONS" "MODIFIED ON" "DIRECTORY PATH"
echo "-------------------------------------------------------------------------------"
IFS=':' read -ra PATH_DIRS <<< "$PATH"

for dir in "${PATH_DIRS[@]}"; do
    if [ -d "$dir" ]; then
        # Use 'stat' for formatted output
        # %A = Permissions (human-readable)
        # %y = Last modification time (human-readable)
        # %n = File name (the directory path)
        ls -ld "$dir" | awk '{print $1, $6, $7, $8, $9}'
    fi
done

echo "-------------------------------------------------------------------------------"
