#!/bin/bash

# Проверяем, передан ли файл как аргумент
if [ $# -eq 0 ]; then
    echo "Usage: $0 filename"
    exit 1
fi

# Проверяем существование файла
if [ ! -f "$1" ]; then
    echo "Error: File $1 not found"
    exit 1
fi

# Выполняем замену и выводим результат
sed 's/TEST_SPRINTF_FORMAT/TEST_SPRINTF/g' "$1"