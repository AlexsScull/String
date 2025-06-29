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
  int modifier_format[4] = {0};    // [h l L null]
  int specifier_format[15] = {0};  // [%d, %i %u, %x %f, %e %c, %s %p %n %% ]
  int spec_format[8] = {0};        // [- + ' ' # 0] [(number) *] [.number .*]

  va_list args;
  va_start(args, format);
  s21_size_t iterator = 0;
  s21_size_t str_iterator = 0;

  for (; format[iterator] != '\0'; ++iterator) {
    if (format[iterator] == '%') {
      parsing_flags_modifier(format, &iterator, modifier_format);
      parsing_flags_specifier(format, &iterator, modifier_format,
                              specifier_format);
    } else {
      str[str_iterator] = format[iterator], &modifier_format;
      str_iterator++;
    }
  }
  va_end(args);
  str[str_iterator] = '\0';
  return str_iterator;
}

void parsing_flags_modifier(const char *format, s21_size_t *iterator,
                            int *modifier_format) {
  switch (format[*iterator]) {
    case 'h':
      modifier_format[LENGTH_H] = 1;
      break;
    case 'l':
      modifier_format[LENGTH_L] = 1;
      break;
    case 'L':
      modifier_format[LENGTH_CAP_L] = 1;
      break;
  }
  (*iterator)++;

  if (modifier_format[LENGTH_H] == 0 && modifier_format[LENGTH_L] == 0 &&
      modifier_format[LENGTH_CAP_L] == 0) {
    modifier_format[LENGTH_NULL] = 1;
  }
}

void parsing_flags_specifier(const char *format, s21_size_t *iterator,
                             const int *modifier_format,
                             int *specifier_format) {
  switch (format[*iterator]) {
    case 'd':
    case 'i':
      //  TYPE_SHORT,      %hd, %hi
      if (modifier_format[LENGTH_H] == 1) {
        specifier_format[TYPE_SHORT] = 1;
      }
      //  TYPE_INT,        %d, %i
      else if (modifier_format[LENGTH_NULL] == 1) {
        specifier_format[TYPE_INT] = 1;
      }
      //  TYPE_LONG,       %ld, %li
      else if (modifier_format[LENGTH_L] == 1) {
        specifier_format[TYPE_LONG] = 1;
      }
      //  Error
      else {
      }
      break;
    case 'o':
    case 'u':
    case 'x':
    case 'X':
      //  TYPE_USHORT,      %hu, %ho, %hx, %hX
      if (modifier_format[LENGTH_H] == 1) {
        specifier_format[TYPE_USHORT] = 1;
      }
      //  TYPE_UINT,        %u, %o, %x, %X
      else if (modifier_format[LENGTH_NULL] == 1) {
        specifier_format[TYPE_UINT] = 1;
      }
      //  TYPE_ULONG,       %lu, %lo, %lx, %lX
      else if (modifier_format[LENGTH_L] == 1) {
        specifier_format[TYPE_ULONG] = 1;
      }
      //  Error
      else {
      }
      break;
    case 'e':
    case 'E':
    case 'f':
    case 'g':
    case 'G':
      // TYPE_FLOAT, %f, %e, %E, %g, %G (float/double)
      if (modifier_format[LENGTH_NULL] == 1) {
        specifier_format[TYPE_FLOAT] = 1;
      }
      // TYPE_LONGDOUBLE, %Lf, %Le, %LE, %Lg, %LG
      else if (modifier_format[LENGTH_CAP_L] == 1) {
        specifier_format[TYPE_LONGDOUBLE] = 1;
      }
      //  Error
      else {
      }
      break;
    case 'c':
      // TYPE_CHAR %c (char)
      if (modifier_format[LENGTH_NULL] == 1) {
        specifier_format[TYPE_CHAR] = 1;
      }
      // TYPE_WCHAR  %lc (wchar_t)
      else if (modifier_format[LENGTH_L] == 1) {
        specifier_format[TYPE_WCHAR] = 1;
      }
      //  Error
      else {
      }
      break;
    case 's':
      // TYPE_STRING %s (const char*)
      if (modifier_format[LENGTH_NULL] == 1) {
        specifier_format[TYPE_STRING] = 1;
      }
      // TYPE_WSTRING  %ls (const wchar_t*)
      else if (modifier_format[LENGTH_L] == 1) {
        specifier_format[TYPE_WSTRING] = 1;
      }
      //  Error
      else {
      }
      break;
    case 'p':
      //  TYPE_POINTER
      if (modifier_format[LENGTH_NULL] == 1) {
        specifier_format[TYPE_POINTER] = 1;
      }
      //  Error
      else {
      }
      break;
    case 'n':
      //  TYPE_PTR
      if (modifier_format[LENGTH_NULL] == 1) {
        specifier_format[TYPE_PTR] = 1;
      }
      //  Error
      else {
      }
      break;
    case '%':
      //  TYPE_PERCENT
      if (modifier_format[LENGTH_NULL] == 1) {
        specifier_format[TYPE_PERCENT] = 1;
      }
      //  Error
      else {
      }
      break;
  }
  (*iterator)++;
}

typedef enum {
  // Целочисленные знаковые
  TYPE_SHORT,  // %hd, %hi
  TYPE_INT,    // %d, %i
  TYPE_LONG,   // %ld, %li

  // Целочисленные беззнаковые
  TYPE_USHORT,  // %hu, %ho, %hx, %hX
  TYPE_UINT,    // %u, %o, %x, %X
  TYPE_ULONG,   // %lu, %lo, %lx, %lX

  // Плавающая точка
  TYPE_FLOAT,       // %f, %e, %E, %g, %G (float/double)
  TYPE_LONGDOUBLE,  // %Lf, %Le, %LE, %Lg, %LG

  // Символы и строки
  TYPE_CHAR,     // %c (char)
  TYPE_WCHAR,    // %lc (wchar_t)
  TYPE_STRING,   // %s (const char*)
  TYPE_WSTRING,  // %ls (const wchar_t*)

  // Специальные типы
  TYPE_POINTER,  // %p (void*)
  TYPE_PERCENT,  // %%
  TYPE_PTR,      // %n (int*)
} NumType;

enum ModifierFormat {
  LENGTH_H,      // 'h' (short)
  LENGTH_L,      // 'l' (long)
  LENGTH_CAP_L,  // 'L' (long double)
  LENGTH_NULL    // ' '
};

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
