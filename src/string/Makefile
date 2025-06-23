# Определение операционной системы
OS := $(shell uname)

# Компилятор и флаги
CC := gcc
CFLAGS := -Wall -Wextra -Werror -std=c11
GCOV_FLAGS := -fprofile-arcs -ftest-coverage

# Имя библиотеки
LIB := s21_string.a

# Флаги для линковки с библиотеками
LIB_FLAGS := -lcheck -lm -lgcov
ifeq ($(OS), Linux)
  LIB_FLAGS += -lsubunit -lpthread
endif

# Директории
SRC_DIR := src
OBJ_DIR := obj
TEST_DIR := tests
TEST_OUT_DIR := obj_tests
COV_DIR := coverage_report

# Автоматическое определение исходных файлов
SRC := $(wildcard $(SRC_DIR)/*.c)
OBJ := $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRC))
TEST_SRCS := $(wildcard $(TEST_DIR)/*.c)
TEST_EXES := $(patsubst $(TEST_DIR)/%.c,$(TEST_OUT_DIR)/%,$(TEST_SRCS))

# Основные цели
.PHONY: all clean test gcov_report rebuild style style_fix cppcheck leaks valgrind

# Стандартная сборка
all: $(LIB)

# Сборка с пересозданием всех файлов
rebuild: clean all

# Сборка библиотеки
$(LIB): $(OBJ)
	ar rcs $@ $^
	ranlib $@

# Компиляция объектных файлов
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) $(if $(findstring gcov_report,$(MAKECMDGOALS)),$(GCOV_FLAGS)) -c $< -o $@

# Создание директорий
$(OBJ_DIR) $(TEST_OUT_DIR) $(COV_DIR):
	mkdir -p $@

# Правило для сборки тестов
$(TEST_OUT_DIR)/%: $(TEST_DIR)/%.c $(LIB) | $(TEST_OUT_DIR)
	$(CC) $< $(LIB) -o $@ $(LIB_FLAGS) $(if $(findstring gcov_report,$(MAKECMDGOALS)),$(GCOV_FLAGS))

# Сборка и запуск всех тестов
test: $(TEST_EXES)
	for test in $(TEST_EXES); do \
		$$test || exit 1; \
	done

# Генерация отчета о покрытии кода
# Генерация отчета о покрытии кода
gcov_report: CFLAGS += $(GCOV_FLAGS)
gcov_report: LIB_FLAGS += -lgcov
gcov_report: clean $(LIB) $(TEST_EXES) | $(COV_DIR)
	for test in $(TEST_EXES); do \
		$$test || true; \
	done
	
	lcov --capture --directory $(OBJ_DIR) --output-file $(COV_DIR)/coverage.info --branch-coverage
	lcov --remove $(COV_DIR)/coverage.info '/usr/include/*' '/tmp/*' '*/tests/*' --output-file $(COV_DIR)/coverage_filtered.info || true
	genhtml $(COV_DIR)/coverage_filtered.info --output-directory $(COV_DIR) --branch-coverage --legend
	
# Стиль кода
style:
	clang-format --style=Google -n */*.c */*.h

style_fix:
	clang-format --style=Google -i */*.c */*.h

cppcheck:
	cppcheck --enable=all --suppress=missingIncludeSystem */*.c */*.h

# Проверка утечек (macOS)
leaks: test
ifeq ($(OS), Darwin)
	for test in $(TEST_EXES); do \
		leaks --atExit -- $$test || exit 1; \
	done
else
	@echo "Leaks check is only available on macOS"
endif

# Проверка утечек (Linux)
valgrind: test
ifeq ($(OS), Linux)
	for test in $(TEST_EXES); do \
		valgrind --leak-check=full --track-origins=yes -s $$test || exit 1; \
	done
else
	echo "Valgrind is only available on Linux"
endif

# Очистка
clean:
	rm -rf $(OBJ_DIR) $(TEST_OUT_DIR) $(COV_DIR) $(LIB)