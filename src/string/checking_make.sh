echo "Запуск всех тестов..."
echo "----------------------------------------"
# -------------------------------------------------------

# Стандартная сборка
echo -e "\e[32mmake all\e[0m"
make clean
make all
echo "----------------------------------------"
# -------------------------------------------------------

# Сборка с пересозданием всех файлов
echo -e "\e[32mmake rebuild\e[0m"
make rebuild
echo "----------------------------------------"
# -------------------------------------------------------

# Сборка всех тестов
echo -e "\e[32mmake test\e[0m"
make clean
make test
echo "----------------------------------------"
# -------------------------------------------------------

# Проверки на стиль
echo -e "\e[32mmake style_fix\e[0m"
make style_fix

echo -e "\e[32mmake style\e[0m"
make style

# echo -e "\e[32mmake cppcheck\e[0m"
# make cppcheck

echo "----------------------------------------"
# -------------------------------------------------------

# Проверка утечек памяти с Valgrind (только Linux)
echo -e "\e[32mmake valgrind\e[0m"
make valgrind
echo "----------------------------------------"
# -------------------------------------------------------

# Проверка утечек памяти с leaks (macOS)
echo -e "\e[32mmake leaks\e[0m"
make leaks
echo "----------------------------------------"
# -------------------------------------------------------

# Сгенерировать отчет о покрытии
echo -e "\e[32mmake gcov_report\e[0m"
make clean
make gcov_report
echo "----------------------------------------"
# -------------------------------------------------------