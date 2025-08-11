#!/bin/bash

if [ $# -ne 2 ]; then
    echo "Usage: $0 <error_lines_file> <source_file>"
    exit 1
fi

error_lines_file="$1"
source_file="$2"

# Проверка существования файлов
if [ ! -f "$error_lines_file" ]; then
    echo "Error: File '$error_lines_file' not found!" >&2
    exit 1
fi

if [ ! -f "$source_file" ]; then
    echo "Error: File '$source_file' not found!" >&2
    exit 1
fi

# Создаем временный файл для команд sed
tmp_script=$(mktemp)

# Генерируем команды для комментирования
while IFS= read -r line_number; do
    # Проверяем, что это число
    if [[ "$line_number" =~ ^[0-9]+$ ]]; then
        echo "${line_number}s/^/\\/\\/ /" >> "$tmp_script"
    fi
done < "$error_lines_file"

# Если есть команды для выполнения, применяем их
if [ -s "$tmp_script" ]; then
    # Создаем резервную копию перед изменением
    cp "$source_file" "${source_file}.bak"
    # Применяем изменения
    sed -f "$tmp_script" "$source_file" > "${source_file}.tmp"
    mv "${source_file}.tmp" "$source_file"
    echo "Commented lines in $source_file. Backup created at ${source_file}.bak"
else
    echo "No valid line numbers found for commenting"
fi

# Удаляем временный файл
rm -f "$tmp_script"