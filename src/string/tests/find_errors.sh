#!/bin/bash

if [ $# -ne 2 ]; then
    echo "Usage: $0 <error_file> <source_file>"
    exit 1
fi

error_file="$1"
source_file="$2"

grep -E "^${source_file}:[0-9]+:[0-9]+:" "$error_file" | \
awk -F: '{print $2}' | \
sort -un