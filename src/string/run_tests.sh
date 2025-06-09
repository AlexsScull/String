#!/bin/bash

# Проверяем, что тестовые программы существуют
if [ ! -f "./test_memory" ] || [ ! -f "./test_string" ] || [ ! -f "./test_sprintf" ] || 
   [ ! -f "./test_sscanf" ] || [ ! -f "./test_extended" ] || [ ! -f "./test_error" ]; then
    echo "Ошибка: Не все тестовые программы найдены. Сначала выполните 'make test' (или 'make all' или 'make rebuild')"
    exit 1
fi

# Массив с именами тестов
tests=("Memory" "String" "Sprintf" "Sscanf" "Extended" "Error")

# Массив с командами для запуска
commands=(
    "./test_memory"
    "./test_string"
    "./test_sprintf"
    "./test_sscanf"
    "./test_extended"
    "./test_error"
)

# Переменная для хранения общего результата
all_success=true

# Проверяем режим вывода
verbose_mode=false
if [ "$1" == "+" ]; then
    verbose_mode=true
fi

echo "Запуск всех тестов..."
echo "----------------------------------------"

# Временный файл для хранения вывода тестов
temp_file=$(mktemp)

# Запускаем каждый тест по очереди
for i in "${!tests[@]}"; do
    echo "Тестируем ${tests[$i]} функции..."
    echo "----------------------------------------"
    
    # Запускаем тест, перенаправляя вывод во временный файл
    ${commands[$i]} > "$temp_file" 2>&1
    test_result=$?
    
    # Проверяем результат выполнения теста
    if [ $test_result -eq 0 ]; then
        echo -e "\e[32mТест ${tests[$i]} пройден успешно\e[0m"
    else
        echo -e "\e[31mТест ${tests[$i]} завершился с ошибкой\e[0m"
        all_success=false
    fi
    
    # Если включен подробный режим, выводим информацию о прохождении отдельных проверок
    if $verbose_mode; then
        echo "----------------------------------------"
        echo "Детали теста:"
        # Читаем временный файл и подсвечиваем FAIL
        while IFS= read -r line; do
            if [[ "$line" == *"FAIL:"* ]]; then
                echo -e "\e[31m$line\e[0m"
            elif [[ "$line" == *"PASS:"* ]]; then
                echo "$line"
            fi
        done < "$temp_file"
    fi
    
    echo "----------------------------------------"
    echo ""
    echo ""
done

# Удаляем временный файл
rm -f "$temp_file"

# Выводим общий результат
if $all_success; then
    echo -e "\e[42m\e[30m ВСЕ ТЕСТЫ УСПЕШНО ПРОЙДЕНЫ \e[0m"
else
    echo -e "\e[41m\e[30m НЕКОТОРЫЕ ТЕСТЫ НЕ ПРОЙДЕНЫ \e[0m"
    exit 1
fi

exit 0
























