#include <ctype.h>
#include <stdarg.h>
#include <stdint.h>
#include <wchar.h>  // Для wchar_t

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
Запись результата в буфер сдвинуть buf
  │
  ▼
Добавить терминирующий ноль ('\0') в конец buf
  │
  ▼
Вернуть кол-во записанных символов (без учёта '\0')*/

enum SpecifierFormat {
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
};

enum ModifierFormat {
  LENGTH_NULL,  // ' '
  LENGTH_H,     // 'h' (short)
  LENGTH_L,     // 'l' (long)
  LENGTH_CAP_L  // 'L' (long double)
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

int s21_sprintf(char *str, const char *format, ...) {
  int modifier_format = 0;   // [h l L null]
  int specifier_format = 0;  //
  int spec_format[8] = {0};  // [- + ' ' # 0] [(number) *] [.number .*]

  va_list args;
  va_start(args, format);
  s21_size_t str_iterator = 0;

  for (s21_size_t i = 0; format[i] != '\0'; ++i) {
    if (format[i] == '%') {
      parsing_flags_modifier(format, &i, &modifier_format);
      parsing_flags_specifier(format, &i, modifier_format, &specifier_format);

      parse_format(str, &i, specifier_format, args);
    } else {
      str[str_iterator++] = format[i];
    }
  }
  va_end(args);
  str[str_iterator] = '\0';
  return str_iterator;
}

void parsing_flags_modifier(const char *format, s21_size_t *i,
                            int *modifier_format) {
  switch (format[*i]) {
    case 'h':
      *modifier_format = LENGTH_H;
      break;
    case 'l':
      *modifier_format = LENGTH_L;
      break;
    case 'L':
      *modifier_format = LENGTH_CAP_L;
      break;
  }
  (*i)++;
}

void parsing_flags_specifier(const char *format, s21_size_t *i,
                             const int modifier_format, int *specifier_format) {
  switch (format[*i]) {
    case 'd':
    case 'i':
      //  TYPE_SHORT,      %hd, %hi
      if (modifier_format == LENGTH_H) {
        *specifier_format = TYPE_SHORT;
      }
      //  TYPE_INT,        %d, %i
      else if (modifier_format == LENGTH_NULL) {
        *specifier_format = TYPE_INT;
      }
      //  TYPE_LONG,       %ld, %li
      else if (modifier_format == LENGTH_L) {
        *specifier_format = TYPE_LONG;
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
      if (modifier_format == LENGTH_H) {
        *specifier_format = TYPE_USHORT;
      }
      //  TYPE_UINT,        %u, %o, %x, %X
      else if (modifier_format == LENGTH_NULL) {
        *specifier_format = TYPE_UINT;
      }
      //  TYPE_ULONG,       %lu, %lo, %lx, %lX
      else if (modifier_format == LENGTH_L) {
        *specifier_format = TYPE_ULONG;
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
      if (modifier_format == LENGTH_NULL) {
        *specifier_format = TYPE_FLOAT;
      }
      // TYPE_LONGDOUBLE, %Lf, %Le, %LE, %Lg, %LG
      else if (modifier_format == LENGTH_CAP_L) {
        *specifier_format = TYPE_LONGDOUBLE;
      }
      //  Error
      else {
      }
      break;
    case 'c':
      // TYPE_CHAR %c (char)
      if (modifier_format == LENGTH_NULL) {
        *specifier_format = TYPE_CHAR;
      }
      // TYPE_WCHAR  %lc (wchar_t)
      else if (modifier_format == LENGTH_L) {
        *specifier_format = TYPE_WCHAR;
      }
      //  Error
      else {
      }
      break;
    case 's':
      // TYPE_STRING %s (const char*)
      if (modifier_format == LENGTH_NULL) {
        *specifier_format = TYPE_STRING;
      }
      // TYPE_WSTRING  %ls (const wchar_t*)
      else if (modifier_format == LENGTH_L) {
        *specifier_format = TYPE_WSTRING;
      }
      //  Error
      else {
      }
      break;
    case 'p':
      //  TYPE_POINTER
      if (modifier_format == LENGTH_NULL) {
        *specifier_format = TYPE_POINTER;
      }
      //  Error
      else {
      }
      break;
    case 'n':
      //  TYPE_PTR
      if (modifier_format == LENGTH_NULL) {
        *specifier_format = TYPE_PTR;
      }
      //  Error
      else {
      }
      break;
    case '%':
      //  TYPE_PERCENT
      if (modifier_format == LENGTH_NULL) {
        *specifier_format = TYPE_PERCENT;
      }
      //  Error
      else {
      }
      break;
  }
  (*i)++;
}

void parse_format(char *str, s21_size_t *i, const int specifier_format,
       va_list args) {
  switch (specifier_format) {
    case TYPE_SHORT:  // short извлекается как int
    case TYPE_INT: {
      int value = va_arg(args, int);
      *i += int_to_string(value, str);
      break;
    }
    case TYPE_LONG: {
      long value = va_arg(args, long);
      *i += int_to_string(value, str);
      break;
    }
    case TYPE_USHORT: {
      unsigned short value = (unsigned short)va_arg(args, unsigned int);
      *i += uint_to_string(value, str);
      break;
    }
    case TYPE_UINT: {
      unsigned int value = va_arg(args, unsigned int);
      *i += uint_to_string(value, str);
      break;
    }
    case TYPE_ULONG: {
      unsigned long value = va_arg(args, unsigned long);
      *i += uint_to_string(value, str);
      break;
    }
    case TYPE_FLOAT: {
      double dval =
          va_arg(args, double);  // float автоматически повышается до double
      // Обработка float
      break;
    }
    case TYPE_LONGDOUBLE: {
      long double ldval = va_arg(args, long double);
      // Обработка long double
      break;
    }
    case TYPE_CHAR: {
      int cval = va_arg(args, int);  // char извлекается как int
      // Обработка char
      break;
    }
    case TYPE_WCHAR: {
      wchar_t wcval = va_arg(args, wchar_t);
      // Обработка wchar_t
      break;
    }
    case TYPE_STRING: {
      char *sval = va_arg(args, char *);
      // Обработка char*
      break;
    }
    case TYPE_WSTRING: {
      wchar_t *wsval = va_arg(args, wchar_t *);
      // Обработка wchar_t*
      break;
    }
    case TYPE_POINTER:
    case TYPE_PTR: {
      void *ptrval = va_arg(args, void *);
      // Обработка указателя
      break;
    }
    case TYPE_PERCENT: {
      // Не требует аргумента - обрабатываем символ '%'
      break;
    }
    default: {
      // Обработка неизвестного спецификатора
      break;
    }
  }
  (*i)++;
}


int int_to_string(intmax_t value, char* str) {
    if (str == NULL) 
        return 0;

    char *p = str; 
    uintmax_t abs_value;

    if (value < 0) {
        *p++ = '-';
        abs_value = (uintmax_t)(-(value + 1)) + 1;
    } else {
        abs_value = (uintmax_t)value;
    }

    char buffer[40]; // Буфер для цифр (достаточно для 128-битных чисел)
    int num_digits = 0;

    if (abs_value == 0) {
        buffer[num_digits++] = '0';
    } else {
        // Извлекаем цифры в обратном порядке
        while (abs_value != 0) {
            buffer[num_digits++] = '0' + (abs_value % 10);
            abs_value /= 10;
        }
    }

    // Записываем цифры в строку в правильном порядке
    for (int i = num_digits - 1; i >= 0; i--) {
        *p++ = buffer[i];
    }
    return p - str;
}

int uint_to_string(uintmax_t value, char* str) {
    if (str == NULL) 
        return 0;

    // (беззнаковые типы всегда ≥ 0)

    char *p = str;
    char buffer[40]; // Достаточно для 128-битных чисел
    int num_digits = 0;

    // Обработка нуля
    if (value == 0) {
        buffer[num_digits++] = '0';
    } else {
        // Извлекаем цифры
        while (value != 0) {
            buffer[num_digits++] = '0' + (value % 10);
            value /= 10;
        }
    }

    // Переворачиваем цифры
    for (int i = num_digits - 1; i >= 0; i--) {
        *p++ = buffer[i];
    }
    
    return p - str; // Длина строки
}