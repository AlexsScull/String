#!/bin/bash

# Проверяем, что тестовые программы существуют
if [ ! -f "./obj_tests/test_memory" ] || [ ! -f "./obj_tests/test_string" ] || [ ! -f "./obj_tests/test_sprintf" ] || 
   [ ! -f "./obj_tests/test_sscanf" ] || [ ! -f "./obj_tests/test_extended" ] || [ ! -f "./obj_tests/test_error" ]; then
    echo "Ошибка: Не все тестовые программы найдены. Сначала выполните 'make test'"
    exit 1
fi

# Массив с именами тестов
tests=("Memory" "String" "Sprintf" "Sscanf" "Extended" "Error")

# Массив с командами для запуска
commands=(
    "./obj_tests/test_memory"
    "./obj_tests/test_string"
    "./obj_tests/test_sprintf"
    "./obj_tests/test_sscanf"
    "./obj_tests/test_extended"
    "./obj_tests/test_error"
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

# Функция для цветного вывода
color_print() {
    local line="$1"
    local line_number="$2"
    
    # Первые две строки вывода - голубые
    if [ "$line_number" -le 2 ]; then
        echo -e "\e[36m$line\e[0m"  # Голубой цвет
    # Строки с "Passed" - серые
    elif [[ "$line" =~ [Pp]assed ]]; then
        echo -e "\e[90m$line\e[0m"  # Серый цвет
    # Остальные строки - красные
    else
        echo -e "\e[31m$line\e[0m"  # Красный цвет
    fi
}

# Запускаем каждый тест по очереди
for i in "${!tests[@]}"; do
    echo "Тестируем ${tests[$i]} функции..."
    echo "----------------------------------------"
    
    # Формируем команду для запуска
    cmd="${commands[$i]}"
    if $verbose_mode; then
        cmd="$cmd +"  # Добавляем + к команде если verbose_mode включен
    fi
    
    # Запускаем тест, перенаправляя вывод во временный файл
    $cmd > "$temp_file" 2>&1
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
        # Читаем временный файл и выводим с цветами
        line_counter=0
        while IFS= read -r line; do
            ((line_counter++))
            color_print "$line" "$line_counter"
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