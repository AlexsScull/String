

#include <ctype.h>
#include <stdarg.h>
#include <stdint.h>
#include <wchar.h>

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
Парсинг модификатора [hh, h, l, ll, L]
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
  TYPE_SHORT,     // %hd, %hi
  TYPE_INT,       // %d, %i
  TYPE_LONG,      // %ld, %li
  TYPE_LONGLONG,  // %lld, %lli

  // Целочисленные беззнаковые
  TYPE_USHORT,     // %hu, %ho, %hx, %hX
  TYPE_UCHAR,      // %hhu, %hho, %hhx, %hhX
  TYPE_UINT,       // %u, %o, %x, %X
  TYPE_ULONG,      // %lu, %lo, %lx, %lX
  TYPE_ULONGLONG,  // %llu, %llo, %llx, %llX

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
  LENGTH_HH,
  LENGTH_L,  // 'l' (long)
  LENGTH_LL,
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
  if (str == NULL) return 0;

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

      parse_format(str, &str_iterator, specifier_format, args);
    } else {
      str[str_iterator++] = format[i];
    }
  }
  va_end(args);
  str[str_iterator] = '\0';
  return str_iterator;
}

void parsing_flags_modifier(const char *format, s21_size_t *i, int *modifier) {
  if (format[*i] == 'h') {
    if (format[*i + 1] == 'h') {
      *modifier = LENGTH_HH;
      (*i) += 2;  // Пропускаем два символа
    } else {
      *modifier = LENGTH_H;
      (*i)++;  // Пропускаем один символ
    }
  } else if (format[*i] == 'l') {
    if (format[*i + 1] == 'l') {
      *modifier = LENGTH_LL;
      (*i) += 2;  // Пропускаем два символа
    } else {
      *modifier = LENGTH_L;
      (*i)++;  // Пропускаем один символ
    }
  } else if (format[*i] == 'L') {
    *modifier = LENGTH_CAP_L;
    (*i)++;  // Пропускаем один символ
  } else {
    *modifier = LENGTH_NULL;
  }
}

void parsing_flags_specifier(const char *format, s21_size_t *i,
                             const int modifier, int *specifier_format) {
  int x = -1;  // Значение по умолчанию (ошибка)

  switch (format[*i]) {
    case 'd':
    case 'i':
      if (modifier == LENGTH_HH)
        x = TYPE_CHAR;
      else if (modifier == LENGTH_H)
        x = TYPE_SHORT;
      else if (modifier == LENGTH_L)
        x = TYPE_LONG;
      else if (modifier == LENGTH_LL)
        x = TYPE_LONGLONG;
      else
        x = TYPE_INT;
      break;

    case 'u':
    case 'o':
    case 'x':
    case 'X':
      if (modifier == LENGTH_HH)
        x = TYPE_UCHAR;
      else if (modifier == LENGTH_H)
        x = TYPE_USHORT;
      else if (modifier == LENGTH_L)
        x = TYPE_ULONG;
      else if (modifier == LENGTH_LL)
        x = TYPE_ULONGLONG;
      else
        x = TYPE_UINT;
      break;

    case 'e':
    case 'E':
    case 'f':
    case 'g':
    case 'G':
      if (modifier == LENGTH_CAP_L)
        x = TYPE_LONGDOUBLE;
      else
        x = TYPE_FLOAT;  // Обрабатываем float/double
      break;

    case 'c':
      if (modifier == LENGTH_L)
        x = TYPE_WCHAR;
      else
        x = TYPE_CHAR;
      break;

    case 's':
      if (modifier == LENGTH_L)
        x = TYPE_WSTRING;
      else
        x = TYPE_STRING;
      break;

    case 'p':
      x = TYPE_POINTER;
      break;

    case 'n':
      x = TYPE_PTR;
      break;

    case '%':
      x = TYPE_PERCENT;
      break;
  }

  *specifier_format = x;
  (*i)++;
}

void parse_format(char *str, s21_size_t *i, const int specifier_format,
                  va_list args) {
  switch (specifier_format) {
    case TYPE_SHORT:  // short извлекается как int
    case TYPE_INT: {
      int value = va_arg(args, int);
      int_to_string(value, i, str);
      break;
    }
    case TYPE_LONG: {
      long value = va_arg(args, long);
      int_to_string(value, i, str);
      break;
    }
    case TYPE_LONGLONG: {
      long long value = va_arg(args, long long);
      int_to_string(value, i, str);
      break;
    }
    case TYPE_USHORT: {
      unsigned short value = (unsigned short)va_arg(args, unsigned int);
      uint_to_string(value, i, str);
      break;
    }
    case TYPE_UCHAR: {
      unsigned char value = (unsigned char)va_arg(args, unsigned int);
      char_to_string(value, i, str);
      break;
    }
    case TYPE_UINT: {
      unsigned int value = va_arg(args, unsigned int);
      uint_to_string(value, i, str);
      break;
    }
    case TYPE_ULONG: {
      unsigned long value = va_arg(args, unsigned long);
      uint_to_string(value, i, str);
      break;
    }
    case TYPE_ULONGLONG: {
      unsigned long long value = va_arg(args, unsigned long long);
      uint_to_string(value, i, str);
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
      char_to_string(cval, i, str);
      break;
    }
    case TYPE_WCHAR: {
      wchar_t wcval = va_arg(args, wchar_t);
      // Обработка wchar_t
      break;
    }
    case TYPE_STRING: {
      char *sval = va_arg(args, char *);
      string_to_string(sval, i, str);
      break;
    }
    case TYPE_WSTRING: {
      wchar_t *wsval = va_arg(args, wchar_t *);
      // Обработка wchar_t*
      break;
    }
    case TYPE_POINTER:
      pointer_to_string(i, str);
      break;
    case TYPE_PTR: {
      void *ptrval = va_arg(args, void *);
      ptr_to_string(ptrval, i, str);
      break;
    }
    case TYPE_PERCENT:
      percent_to_string(i, str);
      break;
    default: {
      // Обработка неизвестного спецификатора
      break;
    }
  }
  (*i)++;
}

void percent_to_string(s21_size_t *i, char *str) {
  char_to_string('%', i, str);
}

void pointer_to_string(s21_size_t *i, char *str) { uint_to_string(*i, i, str); }

void ptr_to_string(void *ptrval, s21_size_t *i, char *str) {
  uintptr_t addr = (uintptr_t)ptrval;
  str[(*i)++] = '0';
  str[(*i)++] = 'x';
  uint_to_string(addr, i, str);
}

void int_to_string(intmax_t value, s21_size_t *i, char *str) {
  if (value < 0) {
    str[(*i)++] = '-';
    // Безопасное преобразование для INTMAX_MIN
    uint_to_string((uintmax_t)(-(value + 1)) + 1, i, str);
  } else {
    uint_to_string((uintmax_t)value, i, str);
  }
}
void uint_to_string(uintmax_t value, s21_size_t *i, char *str) {
  // (беззнаковые типы всегда ≥ 0)
  const char* digit = "0123456789abcdef";
  char buffer[40];  // Достаточно для 128-битных чисел
  int x = 0;

  if (value == 0) {
    buffer[x++] = '0';
  } else {
    while (value != 0) {
      buffer[x++] = digit[value % 10];
      value /= 10;
    }
  }
  for (int j = x - 1; j >= 0; j--) {
    str[(*i)++] = buffer[j];
  }
}

void char_to_string(int cval, s21_size_t *i, char *str) {
  str[(*i)++] = (char)cval;
}

void string_to_string(char *sval, s21_size_t *i, char *str) {
  int x = 0;
  while (sval[x] != '\0') {
    str[(*i)++] = sval[x++];
  }
}