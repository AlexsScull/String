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
  if (!str) return -1;

  int modifier_format = 0;   // [h l L null]
  int specifier_format = 0;  //
  int spec_format[8] = {0};  // [- + ' ' # 0] [(number) *] [.number .*]

  va_list args;
  va_start(args, format);
  s21_size_t idx = 0;

  for (s21_size_t i = 0; format[i]; i++) {
    if (format[i] == '%') {
      int modifier = LENGTH_NULL;
      parsing_flags_modifier(format, &i, &modifier);
      
      int specifier = -1;
      char spec_char = format[i+1];
      parsing_flags_specifier(format, &i, modifier, &specifier);
      
      if (specifier != -1) {
        parse_format(str, &idx, specifier, spec_char, args);
      }
    } else {
      str[idx++] = format[i];
    }
  }

  str[idx] = '\0';
  va_end(args);
  return idx;
}

void parsing_flags_modifier(const char *format, s21_size_t *i, int *modifier) {
  *modifier = LENGTH_NULL;
  
  if (format[*i + 1] == 'h') {
    if (format[*i + 2] == 'h') {
      *modifier = LENGTH_HH;
      (*i) += 2;
    } else {
      *modifier = LENGTH_H;
      (*i) += 1;
    }
  } else if (format[*i + 1] == 'l') {
    if (format[*i + 2] == 'l') {
      *modifier = LENGTH_LL;
      (*i) += 2;
    } else {
      *modifier = LENGTH_L;
      (*i) += 1;
    }
  } else if (format[*i + 1] == 'L') {
    *modifier = LENGTH_CAP_L;
    (*i) += 1;
  }
}

void parsing_flags_specifier(const char *format, s21_size_t *i,
                             const int modifier, int *specifier_format) {
  *specifier_format = -1;  // Значение по умолчанию (ошибка)

  switch (format[*i + 1]) {
    case 'd':
    case 'i':
      if (modifier == LENGTH_HH) *specifier_format = TYPE_CHAR;
      else if (modifier == LENGTH_H) *specifier_format = TYPE_SHORT;
      else if (modifier == LENGTH_L) *specifier_format = TYPE_LONG;
      else if (modifier == LENGTH_LL) *specifier_format = TYPE_LONGLONG;
      else *specifier_format = TYPE_INT;
      break;

    case 'u':
    case 'o':
    case 'x':
    case 'X':
      if (modifier == LENGTH_HH) *specifier_format = TYPE_UCHAR;
      else if (modifier == LENGTH_H) *specifier_format = TYPE_USHORT;
      else if (modifier == LENGTH_L) *specifier_format = TYPE_ULONG;
      else if (modifier == LENGTH_LL) *specifier_format = TYPE_ULONGLONG;
      else *specifier_format = TYPE_UINT;
      break;

    case 'f':
    case 'e':
    case 'E':
    case 'g':
    case 'G':
      if (modifier == LENGTH_CAP_L) *specifier_format = TYPE_LONGDOUBLE;
      else *specifier_format = TYPE_FLOAT;
      break;
      
    case 'c':
      if (modifier == LENGTH_L)
        *specifier_format = TYPE_WCHAR;
      else
        *specifier_format = TYPE_CHAR;
      break;

    case 's':
      if (modifier == LENGTH_L)
        *specifier_format = TYPE_WSTRING;
      else
        *specifier_format = TYPE_STRING;
      break;

    case 'p':
      *specifier_format = TYPE_POINTER;
      break;
      
    case '%':
      *specifier_format = TYPE_PERCENT;
      break;
      
    case 'n':
      *specifier_format = TYPE_PTR;
      break;
  }
  (*i)++;  // Переходим к следующему символу после %
}

void parse_format(char *str, s21_size_t *str_idx, int specifier, 
                 char spec_char, va_list args) {
  switch (specifier) {
        // Обработка знаковых целых
    case TYPE_SHORT:  // short извлекается как int
    case TYPE_INT: {
      int val = va_arg(args, int);
      s21_int_to_str(str, str_idx, val, 10, 0);
      break;
    }
    case TYPE_LONG: {
      long val = va_arg(args, long);
      s21_int_to_str(str, str_idx, val, 10, 0);
      break;
    }
    case TYPE_LONGLONG: {
      long long val = va_arg(args, long long);
      s21_int_to_str(str, str_idx, val, 10, 0);
      break;
    }
      // Обработка беззнаковых целых
    case TYPE_UCHAR: {
      unsigned char val = (unsigned char)va_arg(args, unsigned int);
      s21_uint_to_str(str, str_idx, val, get_base(spec_char), isupper(spec_char));
      break;
    }
    case TYPE_USHORT: 
    case TYPE_UINT: {
      unsigned int val = va_arg(args, unsigned int);
      s21_uint_to_str(str, str_idx, val, get_base(spec_char), isupper(spec_char));
      break;
    }
    case TYPE_ULONG: {
      unsigned long val = va_arg(args, unsigned long);
      s21_uint_to_str(str, str_idx, val, get_base(spec_char), isupper(spec_char));
      break;
    }
    case TYPE_ULONGLONG: {
      unsigned long long val = va_arg(args, unsigned long long);
      s21_uint_to_str(str, str_idx, val, get_base(spec_char), isupper(spec_char));
      break;
    }
    // Обработка float
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
      char c = (char)va_arg(args, int);
      s21_char_to_str(str, str_idx, c);
      break;
    }
    case TYPE_WCHAR: {
      wchar_t wcval = va_arg(args, wchar_t);
      // Обработка wchar_t
      break;
    }
    case TYPE_STRING: {
      char *s = va_arg(args, char*);
      s21_str_to_str(str, str_idx, s);
      break;
    }
    case TYPE_WSTRING: {
      wchar_t *wsval = va_arg(args, wchar_t *);
      // Обработка wchar_t*
      break;
    }
    case TYPE_POINTER:
      void *ptr = va_arg(args, void*);
      s21_ptr_to_str(str, str_idx, ptr);
      break;
    case TYPE_PTR: {
      s21_int_to_str(str, str_idx, str_idx, 10, 0);
      break;
    }
    case TYPE_PERCENT:
       s21_char_to_str(str, str_idx, '%');
      break;
  }
}

////////////////////////////////////////////
//                                        //
//        Вспомогательные функции         //
//                                        //
////////////////////////////////////////////

void s21_int_to_str(char *str, s21_size_t *idx, long long value, int base, int uppercase) {
  if (value < 0) {
    str[(*idx)++] = '-';
    s21_uint_to_str(str, idx, -value, base, uppercase);
  } else {
    s21_uint_to_str(str, idx, value, base, uppercase);
  }
}

void s21_uint_to_str(char *str, s21_size_t *idx, unsigned long long value, int base, int uppercase) {
  char buffer[65];
  const char *digits = uppercase ? "0123456789ABCDEF" : "0123456789abcdef";
  int i = 0;
  
  if (value == 0) {
    buffer[i++] = '0';
  } else {
    while (value) {
      buffer[i++] = digits[value % base];
      value /= base;
    }
  }
  
  // Запись в обратном порядке
  while (--i >= 0) {
    str[(*idx)++] = buffer[i];
  }
}

void s21_char_to_str(char *str, s21_size_t *idx, char c) {
  str[(*idx)++] = c;
}

void s21_str_to_str(char *str, s21_size_t *idx, const char *s) {
  while (*s) {
    str[(*idx)++] = *s++;
  }
}

void s21_ptr_to_str(char *str, s21_size_t *idx, void *ptr) {
  str[(*idx)++] = '0';
  str[(*idx)++] = 'x';
  s21_uint_to_str(str, idx, (uintptr_t)ptr, 16, 0);
}

int get_base(char spec) {
  if (spec == 'o') return 8;
  if (spec == 'x' || spec == 'X' || spec == 'p') return 16;
  return 10;
}

int is_upper(char spec) {
  return (spec == 'X');
}
