#!/bin/bash

if [ $# -eq 0 ]; then
    echo "Usage: $0 <test_file.c>" >&2
    exit 1
fi

if [ ! -f "$1" ]; then
    echo "Error: File '$1' not found" >&2
    exit 1
fi

# Обработка всех тестов (START_TEST и TEST_SPRINTF_1)
grep -Eo 'START_TEST\([^,)]*\)|TEST_SPRINTF_1\([^,]*' "$1" | 
sed -e 's/START_TEST(//' -e 's/TEST_SPRINTF_1(//' -e 's/[,)].*$//' |
while IFS= read -r test_name; do
    echo "    tcase_add_test(tc, $test_name);"
done