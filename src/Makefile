# Определение операционной системы
OS := $(shell uname)

# Компилятор и флаги
CC := gcc
CFLAGS := -std=c11 -Wall -Wextra -Werror
GCOV_FLAGS := -fprofile-arcs -ftest-coverage 

# Флаги для линковки с библиотеками
LIB_FLAGS := -lcheck -lm -lgcov
ifeq ($(OS), Linux)
  LIB_FLAGS += -lsubunit -lpthread
endif

# Имя библиотеки
LIB := s21_string.a

# Директории
SRC_DIR := .
TEST_DIR := tests
OBJ_DIR := obj
TEST_OUT_DIR := obj_tests
COVERAGE_DIR := coverage_report

# Исходные файлы библиотеки
SRC_FILES := memory_functions.c string_functions.c error_functions.c \
             extended_functions.c sprintf_functions.c sscanf_functions.c \
             format_parser.c
SRC := $(addprefix $(SRC_DIR)/, $(SRC_FILES))

# Object files
OBJ := $(addprefix $(OBJ_DIR)/, $(SRC_FILES:.c=.o))

# Test files
TEST := $(wildcard $(TEST_DIR)/*.c)
TEST_TARGETS := $(addprefix $(TEST_OUT_DIR)/, $(notdir $(TEST:.c=)))

# Основные цели
.PHONY: all $(LIB) test gcov_report style_check style_fix cppcheck leaks valgrind clean rebuild joke

# Стандартная сборка
all: $(LIB)

# Сборка библиотеки
$(LIB): $(OBJ)
	ar rcs $@ $^
	ranlib $@

# Компиляция объектных файлов
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Правило для сборки тестов
$(TEST_OUT_DIR)/%: $(TEST_DIR)/%.c $(LIB)
	@mkdir -p $(TEST_OUT_DIR)
	$(CC) $(CFLAGS) $< $(LIB) $(LIB_FLAGS) -o $@

# Сборка и запуск всех тестов
test: $(TEST_TARGETS)
	@for test in $^; do \
		echo "Running $${test}..."; \
		./$${test}; \
	done

# Генерация отчета о покрытии кода
gcov_report: CFLAGS += $(GCOV_FLAGS)
gcov_report: clean $(LIB)
	@mkdir -p $(COVERAGE_DIR)
	@mkdir -p $(TEST_OUT_DIR)
	# Компилируем все тесты с покрытием
	@for test_file in $(TEST); do \
		test_name=$$(basename $$test_file .c); \
		echo "Compiling $$test_name..."; \
		$(CC) $(CFLAGS) $$test_file $(LIB) $(LIB_FLAGS) -o $(TEST_OUT_DIR)/$$test_name; \
	done
	# Запускаем все тесты для генерации данных покрытия
	@for test in $(notdir $(TEST:.c=)); do \
		echo "Running $${test}..."; \
		./$(TEST_OUT_DIR)/$${test}; \
	done
	# Собираем данные покрытия из obj/ (библиотека)
	lcov -t "gcov_report" -o $(COVERAGE_DIR)/coverage.info -c -d $(OBJ_DIR)
	# Удаляем из отчета системные файлы (игнорируем ошибку unused)
	lcov --remove $(COVERAGE_DIR)/coverage.info "/usr/*" --ignore-errors unused -o $(COVERAGE_DIR)/coverage_filtered.info
	# Генерируем HTML-отчет
	genhtml -o $(COVERAGE_DIR) $(COVERAGE_DIR)/coverage_filtered.info
	# Отчет сгенерирован

# Style check
style_check:
	find . -name "*.c" -o -name "*.h" | xargs clang-format -n

# Style fix
style_fix:
	find . -name "*.c" -o -name "*.h" | xargs clang-format -i

# Анализ кода (только файлы библиотеки, исключая тесты)
cppcheck:
	cppcheck --enable=warning,performance,portability,style \
	         --suppress=missingIncludeSystem \
	         --inline-suppr \
	         --error-exitcode=1 \
	         $(SRC_FILES) *.h 2>&1 | grep -E "(error|warning|note|$$)" || echo "No issues found"

# Проверка утечек (macOS)
leaks: $(TEST_TARGETS)
ifeq ($(OS), Darwin)
	@for test in $(TEST_TARGETS); do \
		echo "================================================"; \
		echo "Checking $${test} for leaks..."; \
		echo "================================================"; \
		leaks -atExit -- $$test 2>/dev/null | grep -E "(Process|leaks Report Version|total leaked bytes|LEAK)" | grep -v "0 leaks" || echo "No leaks detected"; \
		echo ""; \
	done
else
	@echo "Leaks check is only available on macOS"
	@echo "Use 'make valgrind' for Linux"
endif

# Проверка утечек (Linux)
valgrind: $(TEST_TARGETS)
ifeq ($(OS), Linux)

	@for test in $(filter-out $(TEST_OUT_DIR)/test_sprintf, $(TEST_TARGETS)); do \
		echo "================================================"; \
		echo "Running valgrind on $${test}..."; \
		echo "================================================"; \
		valgrind --leak-check=full \
		         --show-leak-kinds=definite \
		         --error-exitcode=1 \
		         --quiet \
		         $$test || echo "Valgrind found errors!"; \
		echo ""; \
	done
	
	@if [ -f "$(TEST_OUT_DIR)/test_sprintf" ]; then \
		echo "================================================"; \
		echo "Running valgrind on $(TEST_OUT_DIR)/test_sprintf..."; \
		echo "================================================"; \
		valgrind --leak-check=full \
		         --show-leak-kinds=definite \
		         --error-exitcode=1 \
		         --quiet \
		         $(TEST_OUT_DIR)/test_sprintf || echo "Valgrind found errors!"; \
		echo ""; \
	fi
else
	@echo "Valgrind is only available on Linux"
	@echo "Use 'make leaks' for macOS"
endif

# Очистка
clean:
	rm -rf $(OBJ_DIR) $(TEST_OUT_DIR) $(COVERAGE_DIR) $(LIB)

# Сборка с пересозданием всех файлов
rebuild: clean all



# Cравнение оригинального sprintf и нашей реализации
joke: $(LIB)
	@echo "=================================================================================="
	@echo "   ТЕСТИРОВАНИЕ ОРИГИНАЛЬНОЙ SPRINTF РЕАЛИЗАЦИИ"
	@echo "=================================================================================="
	gcc joke/test_orig_sprintf.c s21_string.a -lcheck -lsubunit -lpthread -lm -o joke_orig
	
	@echo ""
	@echo "══════════════════════════════════════════════════════════════════════════════════"
	@echo "   ПРОВЕРКА УТЕЧЕК ПАМЯТИ (VALGRIND) - ОРИГИНАЛЬНАЯ ФУНКЦИЯ"
	@echo "══════════════════════════════════════════════════════════════════════════════════"
	valgrind --leak-check=full --show-leak-kinds=definite -q ./joke_orig || echo "Valgrind found errors!"
	
	@echo ""
	@echo "══════════════════════════════════════════════════════════════════════════════════"
	@echo "   ВЫВОД ОРИГИНАЛЬНОЙ ФУНКЦИИ БЕЗ VALGRIND"
	@echo "══════════════════════════════════════════════════════════════════════════════════"
	./joke_orig
	
	@echo ""
	@echo "=================================================================================="
	@echo "   ТЕСТИРОВАНИЕ НАШЕЙ S21_SPRINTF РЕАЛИЗАЦИИ"
	@echo "=================================================================================="
	gcc joke/test_s21_sprintf.c s21_string.a -lcheck -lsubunit -lpthread -lm -o joke_s21
	
	@echo ""
	@echo "══════════════════════════════════════════════════════════════════════════════════"
	@echo "   ВЫВОД НАШЕЙ ФУНКЦИИ БЕЗ VALGRIND"
	@echo "══════════════════════════════════════════════════════════════════════════════════"
	./joke_s21
	
	@echo ""
	@echo "══════════════════════════════════════════════════════════════════════════════════"
	@echo "   ПРОВЕРКА УТЕЧЕК ПАМЯТИ (VALGRIND) - НАША ФУНКЦИЯ"
	@echo "══════════════════════════════════════════════════════════════════════════════════"
	valgrind --leak-check=full --show-leak-kinds=definite -q ./joke_s21 || echo "Valgrind found errors!"
	
	@echo ""
	@echo "=================================================================================="
	@echo "   ОЧИСТКА ВРЕМЕННЫХ ФАЙЛОВ"
	@echo "=================================================================================="
	rm -f joke_orig joke_s21
	@echo "   Тестовые файлы удалены"
	@echo "=================================================================================="