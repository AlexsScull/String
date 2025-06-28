#include <ctype.h>
#include <stdarg.h>
#include <stdint.h>

#include "../include/s21_string.h"


  /*Задача:

  /*Начало
    │
    ▼
Инициализация:  
- Указатель buf = str (буфер для записи)
- Указатель fmt = format (шаблон)
- Инициализация списка аргументов (va_list)
    │
    ▼
Цикл по каждому символу fmt:  
├── Если символ ≠ '%':  
│     │
│     ▼
│     Копируем символ в buf, buf++
│
└── Если символ == '%':  
      │
      ▼
  Парсинг флагов [-+0 #]
      │
      ▼
  Чтение ширины (число или *)
      │
      ▼
  Чтение точности (.число или .*)
      │
      ▼
  Парсинг модификатора [hh, h, l, ll, L, j, z, t]
      │
      ▼
  Определение типа:
  ├── %d, %i → целое со знаком
  ├── %u, %x → беззнаковое
  ├── %f, %e → вещественное
  ├── %c, %s → символ/строка
  ├── %p     → указатель
  ├── %n     → счётчик символов
  └── %%     → символ %
      │
      ▼
  Валидация типа и аргумента (via va_list)
      │
      ▼
  Преобразование данных:
  ├── Для чисел: вызов внутренних функций (e.g., `int_to_str()`)
  ├── Для строк: копирование/форматирование
  └── Для %n: запись текущей позиции
      │
      ▼
  Запись результата в буфер (sprintf) сдвинуть buf

    │
    ▼
Добавить терминирующий ноль ('\0') в конец buf
    │
    ▼
Вернуть кол-во записанных символов (без учёта '\0')*/




int s21_sprintf(char *str, const char *format, ...) {
  
int modifier_format[3] = {0};  // [h l L]
int specifier_format[3] = {0};  // [%d, %i %u, %x %f, %e %c, %s %p %n %% ]
int spec_format[8] = {0}; // [- + ' ' # 0] [(number) *] [.number .*]


  va_list args;
  va_start(args, format);
  s21_size_t iterator = 0;
  s21_size_t str_iterator = 0;

  for (; format[iterator] != '\0'; ++iterator) {
    if (format[iterator] == '%') {
      parsing_flags(format, &iterator);
    } 
    else {
      str[str_iterator] = format[iterator];
      str_iterator++;
    }
  }
  va_end(args);
  str[str_iterator] = '\0';
  return str_iterator;
}

void parsing_flags(const char *format, s21_size_t *iterator) {

    switch (format[*iterator]) {
        case 'c':
        // char
            break;
        case 'd':
        case 'i':
        // Десятичное число
            break;
        case 'e':
        case 'E':
        // Десятичное число с плавающей точкой или научная нотация (мантисса/экспонента)
            break;
        case 'f':
        case 'g':
        case 'G':
        //Десятичное число с плавающей точкой или научная нотация (мантисса/экспонента)
            break;
        case 'o':
        // Беззнаковое восьмеричное число
            break;
        case 's':
        //Строка символов
            break;
        case 'u':
        // Беззнаковое десятичное целое число
            break;
        case 'x':
        case 'X':
        // Беззнаковое шестнадцатеричное целое число (любые буквы)
            break;
        case 'p':
        //Адрес указателя
        case 'n':
        //Количество символов, считаных до появления %n
      }
      (*iterator)++;
    }



typedef enum {
TYPE_SHOR,     //	%hd, %hi - short	  
TYPE_INT,     //	%d, %i - int	  
TYPE_LONG,     //	%ld, %li - long	 
TYPE_LONGLONG,     //	%lld, %lli - long long	  
TYPE_UCHAR,     //	%hhu, %hho, %hhx %hhX - unsigned char
TYPE_USHORT,     //	%hu, %ho, %hx %hX - unsigned short
TYPE_UINT,     //		%u, %o, %x, %X - unsigned int
TYPE_ULONG,     //	%lu, %lo, %lx %lX - unsigned long
TYPE_ULONGLONG,     //  %llu, %llo, %llx - unsigned long long
TYPE_FLOAT,     //  %f, %e, %E, %g, %a - float/double
TYPE_LONGDOUBLE,     // %Lf, %Le, %La - long double
TYPE_CHAR,     //	%hhd, %hhi %c - char
TYPE_STRING,     // %s - const char*
TYPE_POINTER,     // %p - void*	Адрес в памяти (0x7ffd8a2b)
TYPE_PERCENT,     // %% - Выводит символ %
TYPE_N,     // %n - int*	Сохраняет кол-во символов
} NumType;

enum SpecFormat {
  FLAG_MINUS,          // '-' (left-justify)
  FLAG_PLUS,           // '+' (show plus sign)
  FLAG_SPACE,          // ' ' (space for positive numbers)
  FLAG_HASH,           // '#' (alternate form)
  FLAG_ZERO,           // '0' (zero-padding)
  WIDTH_NUMBER,        // (number) for width
  WIDTH_ASTERISK,      // '*' for width
  PRECISION_NUMBER,    // (number) for precision
  PRECISION_ASTERISK,  // '.*' for precision
};
enum ModifierFormat {
  LENGTH_H,            // 'h' (short)
  LENGTH_L,            // 'l' (long)
  LENGTH_CAP_L         // 'L' (long double)
};

