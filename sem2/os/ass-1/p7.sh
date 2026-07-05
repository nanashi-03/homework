#!/bin/bash

# check if /proc/cpuinfo is a file or exists
if [ ! -f /proc/cpuinfo ]; then
    exit 1
fi

while true; do
    clear

    echo "--- Live Processor Information ---"
    echo "Press [CTRL+C] to exit"
    echo "----------------------------------"

    # extract the current info for all cores
    grep -E "processor|vendor_id|model name|cpu MHz|cache size" /proc/cpuinfo

    echo "----------------------------------"

    sleep 1
done
