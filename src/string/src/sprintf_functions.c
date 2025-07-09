#include <ctype.h>
#include <limits.h>
#include <math.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <wchar.h>

#include "../include/s21_string.h"

int get_base(char spec);
void s21_int_to_str(char *str, s21_size_t *idx, long long value, int base,
                    int uppercase);

void s21_uint_to_str(char *str, s21_size_t *idx, unsigned long long value,
                     int base, int uppercase);
void s21_char_to_str(char *str, s21_size_t *idx, char c);
void s21_str_to_str(char *str, s21_size_t *idx, const char *s);

void s21_ptr_to_str(char *str, s21_size_t *idx, void *ptr);

void s21_wchar_to_str(char *str, s21_size_t *idx, wchar_t wc);

void s21_wstr_to_str(char *str, s21_size_t *idx, const wchar_t *ws);
bool s21_null_to_str(bool flag, char *str, s21_size_t *idx);
bool s21_float_is_special(const long double  dval, char spec, char *str,
                            s21_size_t *idx);


static void FormatG(long double  dval, int *precision, char* spec,  bool  uppercase);
static void FormatFractionalPart(char *str, s21_size_t *idx, long double  fractional, int precision);

static void FormatExponent(char *str, s21_size_t *idx, int exp, bool uppercase);

static void FormatFloat(char *str, s21_size_t *idx, long double  value, int precision);

static void FormatScientific(char *str, s21_size_t *idx, long double  value, 
                            int precision, bool uppercase);

enum SpecifierFormat {
  // Целочисленные знаковые
  TYPE_SHORT,     // %hd, %hi
  TYPE_INT,       // %d, %i
  TYPE_LONG,      // %ld, %li
  TYPE_LONGLONG,  // %lld, %lli
  TYPE_SCHAR,     // %hhd, %hhi

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
  LENGTH_HH,    // 'hh'
  LENGTH_L,     // 'l' (long)
  LENGTH_LL,    // 'll'
  LENGTH_CAP_L  // 'L' (long double)
};

#define MB_LEN_MAX 1024

int s21_sprintf(char *str, const char *format, ...) {
  if (!str) return -1;

  int modifier_format = 0;  // [h l L null]
  int specifier_format = 0;

  va_list args;
  va_start(args, format);
  s21_size_t idx = 0;

  for (s21_size_t i = 0; format[i]; i++) {
    if (format[i] == '%') {
      int modifier = LENGTH_NULL;
      parsing_flags_modifier(format, &i, &modifier);

      int specifier = -1;
      char spec_char = format[i + 1];
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
      if (modifier == LENGTH_HH)
        *specifier_format = TYPE_SCHAR;
      else if (modifier == LENGTH_H)
        *specifier_format = TYPE_SHORT;
      else if (modifier == LENGTH_L)
        *specifier_format = TYPE_LONG;
      else if (modifier == LENGTH_LL)
        *specifier_format = TYPE_LONGLONG;
      else
        *specifier_format = TYPE_INT;
      break;

    case 'u':
    case 'o':
    case 'x':
    case 'X':
      if (modifier == LENGTH_HH)
        *specifier_format = TYPE_UCHAR;
      else if (modifier == LENGTH_H)
        *specifier_format = TYPE_USHORT;
      else if (modifier == LENGTH_L)
        *specifier_format = TYPE_ULONG;
      else if (modifier == LENGTH_LL)
        *specifier_format = TYPE_ULONGLONG;
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
      else if (modifier == LENGTH_L || modifier == LENGTH_NULL)
        *specifier_format = TYPE_FLOAT;
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

void parse_format(char *str, s21_size_t *str_idx, int specifier, char spec_char,
                  va_list args) {
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
    case TYPE_SCHAR: {
      signed char val = va_arg(args, int);
      s21_int_to_str(str, str_idx, val, 10, 0);
      break;
    }
      // Обработка беззнаковых целых
    case TYPE_UCHAR: {
      unsigned char val = (unsigned char)va_arg(args, unsigned int);
      s21_uint_to_str(str, str_idx, val, get_base(spec_char),
                      isupper(spec_char));
      break;
    }
    case TYPE_USHORT:
    case TYPE_UINT: {
      unsigned int val = va_arg(args, unsigned int);
      s21_uint_to_str(str, str_idx, val, get_base(spec_char),
                      isupper(spec_char));
      break;
    }
    case TYPE_ULONG: {
      unsigned long val = va_arg(args, unsigned long);
      s21_uint_to_str(str, str_idx, val, get_base(spec_char),
                      isupper(spec_char));
      break;
    }
    case TYPE_ULONGLONG: {
      unsigned long long val = va_arg(args, unsigned long long);
      s21_uint_to_str(str, str_idx, val, get_base(spec_char),
                      isupper(spec_char));
      break;
    }
    // Обработка float (автоматически повышается до double)
    case TYPE_FLOAT: {
      long double dval = (long double)va_arg(args, double);
      if (!s21_float_is_special(dval, spec_char, str, str_idx))
        s21_double_to_str(str, spec_char, str_idx, dval);
      break;
    }
    case TYPE_LONGDOUBLE: {
      long double ldval = va_arg(args, long double);
      if (!s21_float_is_special(ldval, spec_char, str, str_idx))
        s21_double_to_str(str, spec_char, str_idx, ldval);
      break;
    }
    case TYPE_CHAR: {
      char c = (char)va_arg(args, int);
      s21_char_to_str(str, str_idx, c);
      break;
    }
    case TYPE_WCHAR: {
      wchar_t wcval = va_arg(args, wchar_t);
      s21_wchar_to_str(str, str_idx, wcval);
      break;
    }
    case TYPE_STRING: {
      char *s = va_arg(args, char *);
      s21_str_to_str(str, str_idx, s);
      break;
    }
    case TYPE_WSTRING: {
      wchar_t *wsval = va_arg(args, wchar_t *);
      s21_wstr_to_str(str, str_idx, wsval);
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
}

void s21_int_to_str(char *str, s21_size_t *idx, long long value, int base,
                    int uppercase) {
  if (value < 0) {
    str[(*idx)++] = '-';
    unsigned long long positive = (value == LLONG_MIN)
                                      ? (unsigned long long)LLONG_MAX + 1
                                      : (unsigned long long)(-value);
    s21_uint_to_str(str, idx, positive, base, uppercase);
  } else {
    s21_uint_to_str(str, idx, value, base, uppercase);
  }
}
void s21_uint_to_str(char *str, s21_size_t *idx, unsigned long long value,
                     int base, int uppercase) {
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

void s21_char_to_str(char *str, s21_size_t *idx, char c) { str[(*idx)++] = c; }

void s21_str_to_str(char *str, s21_size_t *idx, const char *s) {
  while (*s) {
    s21_char_to_str(str, idx, *s++);
  }
}

void s21_ptr_to_str(char *str, s21_size_t *idx, void *ptr) {
  s21_char_to_str(str, idx, '0');
  s21_char_to_str(str, idx, 'x');
  s21_uint_to_str(str, idx, (uintptr_t)ptr, 16, 0);
}

void s21_wchar_to_str(char *str, s21_size_t *idx, wchar_t wc) {
  // Преобразуем широкий символ в многобайтовую последовательность
  char buffer[MB_LEN_MAX];
  mbstate_t state = {0};
  size_t bytes = wcrtomb(buffer, wc, &state);

  if (bytes == (size_t)-1) {
    // Ошибка преобразования: заменяем на '?'
    buffer[0] = '?';
    bytes = 1;
  }

  // Копируем результат в целевую строку
  for (size_t i = 0; i < bytes; i++) {
    str[(*idx)++] = buffer[i];
  }
}

void s21_wstr_to_str(char *str, s21_size_t *idx, const wchar_t *ws) {
  char buffer[MB_LEN_MAX];
  mbstate_t state = {0};

  while (*ws) {
    // Конвертируем каждый символ
    size_t bytes = wcrtomb(buffer, *ws, &state);

    if (bytes == (size_t)-1) {
      buffer[0] = '?';
      bytes = 1;
    }

    // Копируем байты в выходную строку
    for (size_t i = 0; i < bytes; i++) {
      str[(*idx)++] = buffer[i];
    }
    ws++;
  }
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

bool s21_float_is_special(long double value, char spec, char *str, s21_size_t *idx) {
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

void s21_double_to_str(char *str, char spec, s21_size_t *idx, long double  dval) {
    int precision = 6;
    bool uppercase = false;

    // Определение регистра и знака
    if (spec == 'E' || spec == 'G') uppercase = true;
    if (signbit(dval)) {
        s21_char_to_str(str, idx, '-');
        dval = fabs(dval);
    }

    // Обработка спецификатора 'g/G'
    if (spec == 'g' || spec == 'G') { 
      FormatG( dval, &precision, & spec, uppercase); // g -> f || e
    }

    // Выбор формата вывода
    if (spec == 'f' || spec == 'F') {
        FormatFloat(str, idx, dval, precision);
    } else if (spec == 'e' || spec == 'E') {
        FormatScientific(str, idx, dval, precision, uppercase);
    }
}

static void FormatG(long double  dval, int *precision, char* spec,  bool  uppercase) {
        int exp = (dval == 0.0) ? 0 : (int)floor(log10(dval)); // Расчёт экспоненты
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

static void FormatFractionalPart(char *str, s21_size_t *idx, long double  frac, int precision) {
    if (precision <= 0) return;
    
    s21_char_to_str(str, idx, '.');
    
    for (int i = 0; i < precision; i++) {
        frac *= 10.0;
        s21_char_to_str(str, idx, '0' + (int)frac);
        frac -= (int)frac;
    }
}

static void FormatExponent(char *str, s21_size_t *idx, int exp, bool uppercase) {
    s21_char_to_str(str, idx, uppercase ? 'E' : 'e');
    s21_char_to_str(str, idx, exp >= 0 ? '+' : '-');
    
    exp = abs(exp);
    if (exp < 10) s21_char_to_str(str, idx, '0');
    s21_int_to_str(str, idx, exp, 10, 0);
}

static void FormatFloat(char *str, s21_size_t *idx, long double  value, int precision) {
    value += 0.5 * pow(10, -precision); // Округление
    double int_part;
    double frac_part = modf(value, &int_part); // Разбивает на целую и дробную часть
    
    s21_int_to_str(str, idx, int_part, 10, 0);
    FormatFractionalPart(str, idx, frac_part, precision);
}

static void FormatScientific(char *str, s21_size_t *idx, long double  value, 
                            int precision, bool uppercase) {
    int exp = 0;
    if (value != 0.0) {
        while (value >= 10.0) { value /= 10.0; exp++; }
        while (value < 1.0)   { value *= 10.0; exp--; }
    }

    value += 0.5 * pow(10, -precision); // Округление 
    if (value >= 10.0) { value /= 10.0; exp++; }

    double int_part;
    double frac_part = modf(value, &int_part); // Разбивает на целую и дробную часть

    s21_int_to_str(str, idx, int_part, 10, 0);
    FormatFractionalPart(str, idx, frac_part, precision);
    FormatExponent(str, idx, exp, uppercase);
}

