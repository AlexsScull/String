АРХИТЕКТУРА ПРОЭКТА

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
│   ├── test_memory.c        # Тесты для функций работы с памятью     
│   ├── test_string.c        # Тесты для основных строковых функций          
│   ├── test_sprintf.c       # Тесты для форматированного вывода        
│   ├── test_sscanf.c        # Тесты для форматированного ввода     
│   ├── test_extended.c      # Тесты для специальных функций (to_upper, insert и др.)  
│   └── test_error.c         # Тесты для strerror     
└── Makefile            # Сборка проекта        


    