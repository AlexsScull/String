string/
├── include/
│   └── string.h        # Основной заголовочный файл
├── src/
│   ├── memory_functions.c        # Функции работы с памятью
│   ├── string_functions.c        # Основные строковые функции
│   ├── sprintf_functions.c       # Форматированный вывод
│   ├── sscanf_functions.c        # Форматированный ввод
│   ├── extended_functions.c      # Специальные функции (to_upper, insert и др.)
│   └── error_functions.c         # Обработка ошибок (strerror)
├── tests/              # Тесты для всех функций
│   ├── test_memory.c        # Функции работы с памятью
│   ├── test_string.c        # Основные строковые функции
│   ├── test_sprintf.c       # Форматированный вывод
│   ├── test_sscanf.c        # Форматированный ввод
│   ├── test_extended.c      # Специальные функции (to_upper, insert и др.)
│   └── test_error.c         # Обработка ошибок (strerror)
└── Makefile            # Сборка проекта


    