
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

void parse_flags(const char *format, int *i, int *modifier);
void parse_width(const char *format, int *i, int params[], va_list args);
void parse_precision(const char *format, int *i, int params[], va_list args);
void parsing_flags_modifier(const char *format, int *i, int *modifier);
void parse_specifier(const char *format, int *i, int params[]);
int parse_format(char *str, int *str_idx, int params[], va_list args);
void s21_int_to_str(char *str, int *idx, long long value, int params[]);
void s21_uint_to_str(char *str, int *idx, unsigned long long value, int params[]);
void s21_char_to_str(char *str, int *idx, const char c);
void s21_str_to_str(char *str, int *idx, const char *s);
void s21_ptr_to_str(char *str, int *idx);
bool s21_wchar_to_str(char *str, int *idx, wchar_t wc);
bool s21_wstr_to_str(char *str, int *idx, const wchar_t *ws);
bool s21_float_is_special(char *str, int *idx, long double value, int params[]);
void s21_double_to_str(char *str, int *idx, long double dval, int params[]);
static void FormatG(long double dval, int *precision, int params[]);
static void FormatFractionalPart(char *str, int *idx, long double frac,
                                 int precision);
static void FormatExponent(char *str, int *idx, int exp, int params[]);
static void FormatFloat(char *str, int *idx, long double value, int precision, int params[]);
static void FormatScientific(char *str, int *idx, long double value,
                             int precision, int params[]);

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

enum ParamsFormat {
    flag, // -1;   FLAG_MINUS; FLAG_PLUS; FLAG_SPACE; FLAG_HASH; FLAG_ZERO
    width, // -1; WIDTH_NUMBER; WIDTH_ASTERISK
    precision, // -1; PRECISION_NUMBER; PRECISION_ASTERISK
    width_asterisk, // -1; numder
    precision_asterisk, // -1; numder
    modifier, // -1; LENGTH_...
    specifier, // -1; TYPE_...
    uppercase, // 0 - doun; 1 - up
    base, // 10; 8; 16;
    spec_char // g,e,f
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
      i++;

      int params[10] = {-1,-1,-1,-1,-1,-1,-1,0,10,0};
      if (format[i] == '\0') break;
            
      parse_flags(format, &i, &params[flag]);
      parse_width(format, &i, params, args);
      parse_precision(format, &i, params, args);
      parsing_flags_modifier(format, &i, &params[modifier]);
      parse_specifier(format, &i, params);

      if (parse_format(str, &idx, params, args) == -1) {
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

void parse_flags(const char *format, int *i, int *modifier){
    if (format[*i] == '-') *modifier = FLAG_MINUS;
    else if (format[*i] == '+') *modifier = FLAG_PLUS;
    else if (format[*i] == ' ') *modifier = FLAG_SPACE;
    else if (format[*i] == '#') *modifier = FLAG_HASH;
    else if (format[*i] == '0') *modifier = FLAG_ZERO;
    else return;
    (*i)++;
}
void parse_width(const char *format, int *i, int params[], va_list args) {
  if (format[*i] == '*') {
    params[width] = WIDTH_ASTERISK;
    params[width_asterisk] = va_arg(args, int);
    (*i)++;
  } else if (isdigit(format[*i])) {
    params[width] = WIDTH_NUMBER;
    int num = 0;
    while (isdigit(format[*i])) {
      num = num * 10 + (format[*i] - '0');
      (*i)++;
    }
    params[width_asterisk] = num;
  }
}
void parse_precision(const char *format, int *i, int params[], va_list args) {
  if (format[*i] == '.') {
    (*i)++;
    if (format[*i] == '*') {
      params[precision] = PRECISION_ASTERISK;
      params[precision_asterisk] = va_arg(args, int);
      (*i)++;
    } else if (isdigit(format[*i])) {
      params[precision] = PRECISION_NUMBER;
      int num = 0;
      while (isdigit(format[*i])) {
        num = num * 10 + (format[*i] - '0');
        (*i)++;
      }
      params[precision_asterisk] = num;
    } else {
      params[precision] = PRECISION_NUMBER;
      params[precision_asterisk] = 0;
    }
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

void parse_specifier(const char *format, int *i, int params[]) {
  switch (format[*i]) {
    case 'd': case 'i':
      if (params[modifier] == LENGTH_LL) params[specifier] = TYPE_LONGLONG;
      else if (params[modifier] == LENGTH_L) params[specifier] = TYPE_LONG;
      else params[specifier] = TYPE_INT;
      break;

    case 'u': case 'o': case 'x': case 'X':
      if (params[modifier] == LENGTH_LL) params[specifier] = TYPE_ULONGLONG;
      else if (params[modifier] == LENGTH_L) params[specifier] = TYPE_ULONG;
      else params[specifier] = TYPE_UINT;
      break;

    case 'f': case 'e': case 'E': case 'g': case 'G':
      if (params[modifier] == LENGTH_CAP_L) params[specifier] = TYPE_LONGDOUBLE;
      else params[specifier] = TYPE_FLOAT;
      break;

    case 'c':
      params[specifier] = (params[modifier] == LENGTH_L) ? TYPE_WCHAR : TYPE_CHAR;
      break;

    case 's':
      params[specifier] = (params[modifier] == LENGTH_L) ? TYPE_WSTRING : TYPE_STRING;
      break;

    case 'p':
      params[specifier] = TYPE_POINTER;
      break;

    case '%':
      params[specifier] = TYPE_PERCENT;
      break;

    case 'n':
      params[specifier] = TYPE_PTR;
      break;
  }
  
  if (format[*i] == 'X' || format[*i] == 'G' || format[*i] == 'E') {
    params[uppercase] = 1; // up
  }
  
  if (format[*i] == 'o') params[base] = 8;
  else if (format[*i] == 'x' || format[*i] == 'X' || format[*i] == 'p') params[base] = 16;
  else params[base] = 10;

  if (format[*i] == 'E' || format[*i] == 'e') params[spec_char] = 'e';
  else if (format[*i] == 'G' || format[*i] == 'g') params[spec_char] = 'g';
  else if (format[*i] == 'f') params[spec_char] = 'f';

  // (*i)++;
}


int parse_format(char *str, int *str_idx, int params[], va_list args) {
  switch (params[specifier]) {
    case TYPE_INT: case TYPE_LONG: case TYPE_LONGLONG: {
      long long val;
      if (params[specifier] == TYPE_INT) val = (long long)va_arg(args, int);
      else if (params[specifier] == TYPE_LONG) val = (long long)va_arg(args, long);
      else val = va_arg(args, long long);
      s21_int_to_str(str, str_idx, val, params);
      break;
    }
    case TYPE_UINT: case TYPE_ULONG: case TYPE_ULONGLONG: {
      unsigned long long val;
      if (params[specifier] == TYPE_UINT) val = (unsigned long long)va_arg(args, unsigned int);
      else if (params[specifier] == TYPE_ULONG) val = (unsigned long long)va_arg(args, unsigned long);
      else val = va_arg(args, unsigned long long);
      s21_uint_to_str(str, str_idx, val, params);
      break;
    }
    case TYPE_FLOAT: case TYPE_LONGDOUBLE: {
      long double val = (params[specifier] == TYPE_FLOAT) ? 
                       (long double)va_arg(args, double) : 
                       va_arg(args, long double);
      if (!s21_float_is_special(str, str_idx, val, params))
        s21_double_to_str(str, str_idx, val, params);
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
        s21_ptr_to_str(str, str_idx);
        s21_uint_to_str(str, str_idx, (uintptr_t)ptr, params);
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

void s21_int_to_str(char *str, int *idx, long long value, int params[]) {
  if (value < 0) {
    str[(*idx)++] = '-';
    unsigned long long positive = (value == LLONG_MIN) ? 
                                 (unsigned long long)LLONG_MAX + 1 : 
                                 (unsigned long long)(-value);
    s21_uint_to_str(str, idx, positive, params);
  } else {
    if (params[flag] == FLAG_PLUS) {
      str[(*idx)++] = '+';
    } else if (params[flag] == FLAG_SPACE) {
      str[(*idx)++] = ' ';
    }
    s21_uint_to_str(str, idx, value, params);
  }
}

void s21_uint_to_str(char *str, int *idx, unsigned long long value, int params[]) {
  char buffer[65];
  const char *digits = params[uppercase] ? "0123456789ABCDEF" : "0123456789abcdef";
  int i = 0;

  if (value == 0) {
    buffer[i++] = '0';
  } else {
    while (value) {
      buffer[i++] = digits[value % params[base]];
      value /= params[base];
    }
  }

  while (--i >= 0) {
    str[(*idx)++] = buffer[i];
  }
}


void s21_char_to_str(char *str, int *idx, const char c) { 
  str[(*idx)++] = c; 
}

void s21_str_to_str(char *str, int *idx, const char *s) {
  if (s == NULL) {
    s21_str_to_str(str, idx, "(null)");
  } else {
    while (*s) {
      str[(*idx)++] = *s++;
    }
  }
}

void s21_ptr_to_str(char *str, int *idx) {
  s21_char_to_str(str, idx, '0');
  s21_char_to_str(str, idx, 'x');
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


bool s21_float_is_special(char *str, int *idx, long double value, int params[]) {
  if (isnanl(value)) {
    s21_str_to_str(str, idx, params[uppercase] ? "NAN" : "nan");
    return true;
  } else if (isinfl(value)) {
    if (signbit(value)) {
      s21_str_to_str(str, idx, params[uppercase] ? "-INF" : "-inf");
    } else {
      s21_str_to_str(str, idx, params[uppercase] ? "INF" : "inf");
    }
    return true;
  }
  return false;
}


void s21_double_to_str(char *str, int *idx, long double dval, int params[]) {
  int precision = 6;

 bool is_negative = signbit(dval);
  if (is_negative) {
    str[(*idx)++] = '-';
    dval = fabsl(dval);
  } else if (params[flag] == FLAG_PLUS) {
    str[(*idx)++] = '+';
  } else if (params[flag] == FLAG_SPACE) {
    str[(*idx)++] = ' ';
  }
  // Обработка спецификатора 'g/G'
  if (params[spec_char] == 'g') {
    FormatG(dval, &precision, params);  // g -> f || e
  }

  // Выбор формата вывода
  if (params[spec_char] =='f' ) {
    FormatFloat(str, idx, dval, precision, params);
  } else if (params[spec_char] == 'e' ) {
    FormatScientific(str, idx, dval, precision, params);
  }
}

static void FormatG(long double dval, int *precision, int params[]) {
  int exp =
      (dval == 0.0L) ? 0 : (int)floorl(log10l(dval));  // Расчёт экспоненты
  if (exp >= -4 && exp < *precision) {
    *precision = *precision - (exp + 1);
    if (*precision < 0) *precision = 0;
    if (exp == 0) *precision = 0;
    params[spec_char] = 'f';
  } else {
    *precision = (*precision > 0) ? *precision - 1 : 0;
    params[spec_char] = 'e';
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

static void FormatExponent(char *str, int *idx, int exp, int params[]) {
  s21_char_to_str(str, idx, params[uppercase] ? 'E' : 'e');
  s21_char_to_str(str, idx, exp >= 0 ? '+' : '-');

  exp = abs(exp);
  if (exp < 10) s21_char_to_str(str, idx, '0');
  s21_int_to_str(str, idx, exp, params);
}

static void FormatFloat(char *str, int *idx, long double value, int precision, int params[]) {
  long double rounding = 0.5L * powl(10.0L, -precision);
  value += rounding;  // Округление
  long double int_part;
  long double frac_part =
      modfl(value, &int_part);  // Разбивает на целую и дробную часть

  s21_int_to_str(str, idx, (long long)int_part, params);
  FormatFractionalPart(str, idx, frac_part, precision);
}

static void FormatScientific(char *str, int *idx, long double value,
                             int precision, int params[]) {
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

  s21_int_to_str(str, idx, (long long)int_part, params);
  FormatFractionalPart(str, idx, frac_part, precision);
  FormatExponent(str, idx, exp, params);
}