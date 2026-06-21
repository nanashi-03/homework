#!/bin/bash

# Check if /proc/cpuinfo exists
if [ ! -f /proc/cpuinfo ]; then
    exit 1
fi

while true; do
    # Clear the terminal screen to overwrite previous data
    clear
    
    echo "=== Live Processor Information ==="
    echo "Press [CTRL+C] to exit"
    echo "----------------------------------"
    
    # Extract the info for all cores in real-time
    grep -E "processor|vendor_id|model name|cpu MHz|cache size" /proc/cpuinfo
    
    echo "----------------------------------"
    
    # Wait for 1 second before updating again
    sleep 1
done