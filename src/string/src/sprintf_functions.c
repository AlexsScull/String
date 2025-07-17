
#include <ctype.h>
#include <limits.h>
#include <locale.h>
#include <math.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <wchar.h>

#include "../include/s21_string.h"

void parsing_flags(const char *format, int *i, int *modifier);
void parsing_flags_modifier(const char *format, int *i, int *modifier);

void parsing_flags_specifier(const char *format, int *i, const int modifier,
                             int *specifier_format);
int parse_format(char *str, int *str_idx, int flag, int specifier, char spec_char,
                 va_list args);

void s21_int_to_str(char *str, int *idx, long long value, int base,
                    int uppercase, int flag);
void s21_uint_to_str(char *str, int *idx, unsigned long long value, int base,
                     int uppercase);
void s21_char_to_str(char *str, int *idx, char c);
void s21_str_to_str(char *str, int *idx, const char *s);
void s21_ptr_to_str(char *str, int *idx, void *ptr);

bool s21_wchar_to_str(char *str, int *idx, wchar_t wc);
bool s21_wstr_to_str(char *str, int *idx, const wchar_t *ws);
int get_base(char spec);
int is_upper(char spec);

bool s21_float_is_special(long double value, char spec, char *str, int *idx);

void s21_double_to_str(char *str, char spec, int *idx, long double dval);

static void FormatG(long double dval, int *precision, char *spec,
                    bool uppercase);

static void FormatFractionalPart(char *str, int *idx, long double frac,
                                 int precision);

static void FormatExponent(char *str, int *idx, int exp, bool uppercase);

static void FormatFloat(char *str, int *idx, long double value, int precision);
static void FormatScientific(char *str, int *idx, long double value,
                             int precision, bool uppercase);

// Сигнальное значение NaN	nan(snan)
//  Неопределенное значение NaN	nan(ind)

enum SpecifierFormat {
  // Целочисленные знаковые
  TYPE_INT,       // %d, %i, %hd, %hhd
  TYPE_LONG,      // %ld, %li
  TYPE_LONGLONG,  // %lld, %lli

  // Целочисленные беззнаковые
  TYPE_UINT,       // %u, %o, %x, %X, %hu, %hhu
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
  LENGTH_NULL,  // ' '
  LENGTH_H,     // 'h' (short)
  LENGTH_HH,    // 'hh'
  LENGTH_L,     // 'l' (long)
  LENGTH_LL,    // 'll'
  LENGTH_CAP_L  // 'L' (long double)
};

#define MB_LEN_MAX 1024

int s21_sprintf(char *str, const char *format, ...) {
  if (!str) return -1;
  if (!setlocale(LC_ALL, "en_US.UTF-8")) {
    setlocale(LC_ALL, "C.UTF-8");
  }

  va_list args;
  va_start(args, format);
  int idx = 0;

  for (int i = 0; format[i]; i++) {
    if (format[i] == '%') {
      i++; // Пропускаем '%'

      // Если после '%' сразу конец строки
      if (format[i] == '\0') {
        str[idx++] = '%'; // Выводим '%' и выходим
        break;
      }

      int flag = -1;
      parsing_flags(format, &i, &flag);

      int modifier = LENGTH_NULL;
      parsing_flags_modifier(format, &i, &modifier);

      int specifier = -1;
      char spec_char = format[i];
      parsing_flags_specifier(format, &i, modifier, &specifier);

      if (parse_format(str, &idx, flag, specifier, spec_char, args) == -1) {
        str[idx] = '\0';
        va_end(args);
        return -1;
      }
    } else {
      str[idx++] = format[i];
    }
  }

  str[idx] = '\0';
  va_end(args);
  return idx;
}

void parsing_flags(const char *format, int *i, int *modifier) {
  if (format[*i] == '-') {
    *modifier = FLAG_MINUS;
    (*i) += 1;
  }
  if (format[*i] == '+') {
    *modifier = FLAG_PLUS;
    (*i) += 1;
  }
  if (format[*i] == ' ') {
    *modifier = FLAG_SPACE;
    (*i) += 1;
  }
  if (format[*i] == '#') {
    *modifier = FLAG_HASH;
    (*i) += 1;
  }
  if (format[*i] == '0') {
    *modifier = FLAG_ZERO;
    (*i) += 1;
  }

  if (format[*i] == '.') {
    (*i) += 1;

    if (format[*i] == '*') {
      *modifier = PRECISION_ASTERISK;
      (*i) += 1;
    } else if (format[*i] >= '0' && format[*i] <= '9') {
      *modifier = PRECISION_NUMBER;
      (*i) += 1;
    }
  }

  if (format[*i] == '*') {
    *modifier = WIDTH_ASTERISK;
    (*i) += 1;
  } else if (format[*i] >= '0' && format[*i] <= '9') {
    *modifier = WIDTH_NUMBER;
    (*i) += 1;
  }
}

void parsing_flags_modifier(const char *format, int *i, int *modifier) {
  *modifier = LENGTH_NULL;

  if (format[*i] == 'h') {
    if (format[*i + 1] == 'h') {
      *modifier = LENGTH_HH;
      (*i) += 2;
    } else {
      *modifier = LENGTH_H;
      (*i) += 1;
    }
  } else if (format[*i] == 'l') {
    if (format[*i + 1] == 'l') {
      *modifier = LENGTH_LL;
      (*i) += 2;
    } else {
      *modifier = LENGTH_L;
      (*i) += 1;
    }
  } else if (format[*i] == 'L') {
    *modifier = LENGTH_CAP_L;
    (*i) += 1;
  }
}

void parsing_flags_specifier(const char *format, int *i, const int modifier,
                             int *specifier_format) {
  *specifier_format = -1;  // Значение по умолчанию (ошибка)

  switch (format[*i]) {
    case 'd':
    case 'i':
      if (modifier == LENGTH_LL)
        *specifier_format = TYPE_LONGLONG;
      else if (modifier == LENGTH_L)
        *specifier_format = TYPE_LONG;
      else
        *specifier_format = TYPE_INT;
      break;

    case 'u':
    case 'o':
    case 'x':
    case 'X':
      if (modifier == LENGTH_LL)
        *specifier_format = TYPE_ULONGLONG;
      else if (modifier == LENGTH_L)
        *specifier_format = TYPE_ULONG;
      else
        *specifier_format = TYPE_UINT;
      break;

    case 'f':
    case 'e':
    case 'E':
    case 'g':
    case 'G':
      if (modifier == LENGTH_CAP_L)
        *specifier_format = TYPE_LONGDOUBLE;
      else
        *specifier_format = TYPE_FLOAT;
      break;

    case 'c':
      *specifier_format = (modifier == LENGTH_L) ? TYPE_WCHAR : TYPE_CHAR;
      break;

    case 's':
      *specifier_format = (modifier == LENGTH_L) ? TYPE_WSTRING : TYPE_STRING;
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
}

int parse_format(char *str, int *str_idx, int flag, int specifier, char spec_char,
                 va_list args) {
  switch (specifier) {
      // Обработка всех знаковых целых
    case TYPE_INT:
    case TYPE_LONG:
    case TYPE_LONGLONG: {
      long long val;
      if (specifier == TYPE_INT)
        val = (long long)va_arg(args, int);
      else if (specifier == TYPE_LONG)
        val = (long long)va_arg(args, long);
      else
        val = va_arg(args, long long);
      s21_int_to_str(str, str_idx, val, 10, 0, flag);
      break;
    }
      // Обработка всех беззнаковых целых
    case TYPE_UINT:
    case TYPE_ULONG:
    case TYPE_ULONGLONG: {
      unsigned long long val;
      if (specifier == TYPE_UINT)
        val = (unsigned long long)va_arg(args, unsigned int);
      else if (specifier == TYPE_ULONG)
        val = (unsigned long long)va_arg(args, unsigned long);
      else
        val = va_arg(args, unsigned long long);
      s21_uint_to_str(str, str_idx, val, get_base(spec_char),
                      isupper(spec_char));
      break;
    }
    // Обработка вещественных чисел
    case TYPE_FLOAT:
    case TYPE_LONGDOUBLE: {
      long double val = (specifier == TYPE_FLOAT)
                            ? (long double)va_arg(args, double)
                            : va_arg(args, long double);
      if (!s21_float_is_special(val, spec_char, str, str_idx))
        s21_double_to_str(str, spec_char, str_idx, val);
      break;
    }
    case TYPE_CHAR: {
      char c = (char)va_arg(args, int);
      s21_char_to_str(str, str_idx, c);
      break;
    }
    case TYPE_WCHAR: {
      wchar_t wcval = va_arg(args, wchar_t);
      if (!s21_wchar_to_str(str, str_idx, wcval)) return -1;
      break;
    }
    case TYPE_STRING: {
      char *s = va_arg(args, char *);
      s21_str_to_str(str, str_idx, s);
      break;
    }
    case TYPE_WSTRING: {
      wchar_t *wsval = va_arg(args, wchar_t *);
      if (!s21_wstr_to_str(str, str_idx, wsval)) return -1;
      break;
    }
    case TYPE_POINTER: {
      void *ptr = va_arg(args, void *);
      if (ptr == NULL) {
        s21_str_to_str(str, str_idx, "(nil)");
      } else {
        s21_ptr_to_str(str, str_idx, ptr);
      }
      break;
    }
    case TYPE_PTR: {
      int *ptr = va_arg(args, int *);
      *ptr = *str_idx;
      break;
    }
    case TYPE_PERCENT:
      s21_char_to_str(str, str_idx, '%');
      break;
  }
  return 0;
}

void s21_int_to_str(char *str, int *idx, long long value, int base,
                    int uppercase, int flag) {
  if (value < 0) {
    str[(*idx)++] = '-';
    unsigned long long positive = (value == LLONG_MIN)
                                      ? (unsigned long long)LLONG_MAX + 1
                                      : (unsigned long long)(-value);
    s21_uint_to_str(str, idx, positive, base, uppercase);
  } else {
    if (flag == FLAG_PLUS) {
      str[(*idx)++] = '+';
    } else if (flag == FLAG_SPACE) {
      str[(*idx)++] = ' ';
    }
    s21_uint_to_str(str, idx, value, base, uppercase);
  }
}

void s21_uint_to_str(char *str, int *idx, unsigned long long value, int base,
                     int uppercase) {
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

void s21_char_to_str(char *str, int *idx, const char c) { str[(*idx)++] = c; }

void s21_str_to_str(char *str, int *idx, const char *s) {
  if (s == NULL) {
    s21_str_to_str(str, idx, "(null)");
  } else {
    while (*s) {
      s21_char_to_str(str, idx, *s++);
    }
  }
}

void s21_ptr_to_str(char *str, int *idx, void *ptr) {
  s21_char_to_str(str, idx, '0');
  s21_char_to_str(str, idx, 'x');
  s21_uint_to_str(str, idx, (uintptr_t)ptr, 16, 0);
}

bool s21_wchar_to_str(char *str, int *idx, wchar_t wc) {
  uint32_t code = (uint32_t)wc;

  // Корректная проверка диапазона Unicode
  if (code > 0x10FFFF || (code >= 0xD800 && code <= 0xDFFF) || wc < 0) {
    return false;  // Убрано изменение индекса
  }

  // Определение количества байт с исправленными границами
  int bytes_count;
  if (code < 0x80)
    bytes_count = 1;
  else if (code < 0x800)
    bytes_count = 2;
  else if (code < 0x10000)
    bytes_count = 3;
  else
    bytes_count = 4;

  // Запись с гарантированным маскированием битов
  switch (bytes_count) {
    case 1:
      str[(*idx)++] = (char)code;
      break;
    case 2:
      str[(*idx)++] = 0xC0 | (code >> 6);
      str[(*idx)++] = 0x80 | (code & 0x3F);
      break;
    case 3:
      str[(*idx)++] = 0xE0 | (code >> 12);
      str[(*idx)++] = 0x80 | ((code >> 6) & 0x3F);
      str[(*idx)++] = 0x80 | (code & 0x3F);
      break;
    case 4:
      str[(*idx)++] = 0xF0 | (code >> 18);
      str[(*idx)++] = 0x80 | ((code >> 12) & 0x3F);
      str[(*idx)++] = 0x80 | ((code >> 6) & 0x3F);
      str[(*idx)++] = 0x80 | (code & 0x3F);
      break;
  }

  return true;
}

bool s21_wstr_to_str(char *str, int *idx, const wchar_t *ws) {
  if (ws == NULL) {
    s21_str_to_str(str, idx, "(null)");
    return true;
  }

  int start_index = *idx;  // Сохраняем начальный индекс
  int total_bytes = 0;  // Общее количество байт для UTF-8 строки
  const wchar_t *tmp = ws;  // Указатель для обхода широкой строки
  char char_buffer[4];  // Буфер для одного символа UTF-8 (макс. 4 байта)
  int temp_idx;  // Временный индекс для записи в буфер

  // Первый проход: проверка символов и подсчёт длины
  while (*tmp) {
    temp_idx = 0;
    if (!s21_wchar_to_str(char_buffer, &temp_idx, *tmp)) {
      return false;  // Убрано изменение индекса
    }
    total_bytes += temp_idx;  // Увеличиваем общий размер
    tmp++;
  }

  // Если строка пустая, сразу возвращаем успех
  if (total_bytes == 0) {
    return true;
  }

  // Выделяем буфер для всей строки
  char *buffer = (char *)malloc(total_bytes);
  if (buffer == NULL) {
    *idx = -1;  // Ошибка выделения памяти
    return false;
  }

  int buf_index = 0;  // Индекс в выделенном буфере
  tmp = ws;  // Сбрасываем указатель на начало строки

  // Второй проход: запись символов во временный буфер
  while (*tmp) {
    if (!s21_wchar_to_str(buffer, &buf_index, *tmp)) {
      free(buffer);
      *idx = -1;  // Ошибка (не должна возникать после проверки)
      return false;
    }
    tmp++;
  }

  // Копируем данные из временного буфера в целевую строку
  for (int i = 0; i < total_bytes; i++) {
    str[start_index + i] = buffer[i];
  }
  *idx = start_index + total_bytes;  // Обновляем индекс

  free(buffer);  // Освобождаем временный буфер
  return true;
}

////////////////////////////////////////////
//                                        //
//        Вспомогательные функции         //
//                                        //
////////////////////////////////////////////

int get_base(char spec) {
  if (spec == 'o') return 8;
  if (spec == 'x' || spec == 'X' || spec == 'p') return 16;
  return 10;
}

int is_upper(char spec) { return (spec == 'X'); }

bool s21_float_is_special(long double value, char spec, char *str, int *idx) {
  bool uppercase = (spec == 'E' || spec == 'G');
  if (isnanl(value)) {
    s21_str_to_str(str, idx, uppercase ? "NAN" : "nan");
    return true;
  } else if (isinfl(value)) {
    if (signbit(value)) {
      s21_str_to_str(str, idx, uppercase ? "-INF" : "-inf");
    } else {
      s21_str_to_str(str, idx, uppercase ? "INF" : "inf");
    }
    return true;
  }
  return false;
}

void s21_double_to_str(char *str, char spec, int *idx, long double dval) {
  int precision = 6;
  bool uppercase = false;

  // Определение регистра и знака
  if (spec == 'E' || spec == 'G') uppercase = true;
  if (signbit(dval)) {
    s21_char_to_str(str, idx, '-');
    dval = fabsl(dval);
  }

  // Обработка спецификатора 'g/G'
  if (spec == 'g' || spec == 'G') {
    FormatG(dval, &precision, &spec, uppercase);  // g -> f || e
  }

  // Выбор формата вывода
  if (spec == 'f' || spec == 'F') {
    FormatFloat(str, idx, dval, precision);
  } else if (spec == 'e' || spec == 'E') {
    FormatScientific(str, idx, dval, precision, uppercase);
  }
}

static void FormatG(long double dval, int *precision, char *spec,
                    bool uppercase) {
  int exp =
      (dval == 0.0L) ? 0 : (int)floorl(log10l(dval));  // Расчёт экспоненты
  if (exp >= -4 && exp < *precision) {
    *precision = *precision - (exp + 1);
    if (*precision < 0) *precision = 0;
    if (exp == 0) *precision = 0;
    *spec = 'f';
  } else {
    *precision = (*precision > 0) ? *precision - 1 : 0;
    *spec = uppercase ? 'E' : 'e';
  }
}

static void FormatFractionalPart(char *str, int *idx, long double frac,
                                 int precision) {
  if (precision <= 0) return;

  s21_char_to_str(str, idx, '.');

  for (int i = 0; i < precision; i++) {
    frac *= 10.0L;
    int digit = (int)frac;
    s21_char_to_str(str, idx, '0' + digit);
    frac -= digit;
  }
}

static void FormatExponent(char *str, int *idx, int exp, bool uppercase) {
  s21_char_to_str(str, idx, uppercase ? 'E' : 'e');
  s21_char_to_str(str, idx, exp >= 0 ? '+' : '-');

  exp = abs(exp);
  if (exp < 10) s21_char_to_str(str, idx, '0');
  s21_int_to_str(str, idx, exp, 10, 0, 0);
}

static void FormatFloat(char *str, int *idx, long double value, int precision) {
  long double rounding = 0.5L * powl(10.0L, -precision);
  value += rounding;  // Округление
  long double int_part;
  long double frac_part =
      modfl(value, &int_part);  // Разбивает на целую и дробную часть

  s21_int_to_str(str, idx, (long long)int_part, 10, 0, 0);
  FormatFractionalPart(str, idx, frac_part, precision);
}

static void FormatScientific(char *str, int *idx, long double value,
                             int precision, bool uppercase) {
  int exp = 0;
  if (value != 0.0L) {
    while (value >= 10.0L) {
      value /= 10.0L;
      exp++;
    }
    while (value < 1.0L) {
      value *= 10.0L;
      exp--;
    }
  }

  long double rounding = 0.5L * powl(10.0L, -precision);
  value += rounding;  // Округление
  if (value >= 10.0L) {
    value /= 10.0L;
    exp++;
  }

  long double int_part;
  long double frac_part =
      modfl(value, &int_part);  // Разбивает на целую и дробную часть

  s21_int_to_str(str, idx, (long long)int_part, 10, 0, 0);
  FormatFractionalPart(str, idx, frac_part, precision);
  FormatExponent(str, idx, exp, uppercase);
}