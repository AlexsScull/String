#!/bin/bash

if [ $# -eq 0 ]; then
    echo "Usage: $0 <test_file.c>" >&2
    exit 1
fi

if [ ! -f "$1" ]; then
    echo "Error: File '$1' not found" >&2
    exit 1
fi

# Обработка каждой строки с START_TEST
grep 'START_TEST(' "$1" | while IFS= read -r line; do
    # Извлекаем имя теста с помощью параметрического расширения
    temp="${line#*START_TEST(}"
    test_name="${temp%%)*}"
    echo "    tcase_add_test(tc, $test_name);"
done