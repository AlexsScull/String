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

////////////////////////////////////////////////////////////
//                 Перечисления и константы               //
////////////////////////////////////////////////////////////

/** Типы флагов форматирования */
enum FlagType {
  FLAG_MINUS,  ///< '-' (left-justify)
  FLAG_PLUS,   ///< '+' (show plus sign)
  FLAG_SPACE,  ///< ' ' (space for positive numbers)
  FLAG_HASH,   ///< '#' (alternate form)
  FLAG_ZERO    ///< '0' (zero-padding)
};

/** Типы ширины форматирования */
enum WidthType {
  WIDTH_NUMBER,   ///< (number) for width
  WIDTH_ASTERISK  ///< '*' for width
};

/** Типы точности форматирования */
enum PrecisionType {
  PRECISION_NUMBER,   ///< (number) for precision
  PRECISION_ASTERISK  ///< '.*' for precision
};

/** Модификаторы длины */
enum ModifierType {
  LENGTH_NULL,  ///< ' '
  LENGTH_H,     ///< 'h' (short)
  LENGTH_HH,    ///< 'hh'
  LENGTH_L,     ///< 'l' (long)
  LENGTH_LL,    ///< 'll'
  LENGTH_CAP_L  ///< 'L' (long double)
};

/** Спецификаторы формата */
enum SpecifierType {
  // Целочисленные знаковые
  TYPE_INT,       ///< %d, %i, %hd, %hhd
  TYPE_LONG,      ///< %ld, %li
  TYPE_LONGLONG,  ///< %lld, %lli

  // Целочисленные беззнаковые
  TYPE_UINT,       ///< %u, %o, %x, %X, %hu, %hhu
  TYPE_ULONG,      ///< %lu, %lo, %lx, %lX
  TYPE_ULONGLONG,  ///< %llu, %llo, %llx, %llX

  // Плавающая точка
  TYPE_FLOAT,       ///< %f, %e, %E, %g, %G (float/double)
  TYPE_LONGDOUBLE,  ///< %Lf, %Le, %LE, %Lg, %LG

  // Символы и строки
  TYPE_CHAR,     ///< %c (char)
  TYPE_WCHAR,    ///< %lc (wchar_t)
  TYPE_STRING,   ///< %s (const char*)
  TYPE_WSTRING,  ///< %ls (const wchar_t*)

  // Специальные типы
  TYPE_POINTER,  ///< %p (void*)
  TYPE_PERCENT,  ///< %%
  TYPE_PTR,      ///< %n (int*)
};

/** Индексы параметров форматирования */
enum ParamIndex {
  PARAM_FLAG,                  ///< Флаг форматирования
  PARAM_WIDTH,                 ///< Тип ширины
  PARAM_PRECISION,             ///< Тип точности
  PARAM_WIDTH_ASTERISK_VALUE,  ///< Значение ширины для '*'
  PARAM_PRECISION_ASTERISK_VALUE,  ///< Значение точности для '.*'
  PARAM_MODIFIER,                  ///< Модификатор длины
  PARAM_SPECIFIER,                 ///< Спецификатор типа
  PARAM_UPPERCASE,  ///< Флаг верхнего регистра
  PARAM_BASE,       ///< Основание системы счисления
  PARAM_SPEC_CHAR,  ///< Специальный символ формата
  PARAM_COUNT       ///< Количество параметров
};

/** Символы формата чисел с плавающей точкой */
enum FormatChar {
  CHAR_F,  ///< Формат 'f'
  CHAR_E,  ///< Формат 'e'
  CHAR_G   ///< Формат 'g'
};

// Константы форматирования
const int kDefaultPrecision = 6;  ///< Точность по умолчанию
const int kMaxBufferSize = 65;  ///< Максимальный размер буфера
const int kMaxUtf8Bytes = 4;  ///< Макс. байт на UTF-8 символ
const int kMaxMbLen = 1024;  ///< Макс. длина многобайтовой строки
const int kBaseDecimal = 10;  ///< Десятичное основание
const int kBaseOctal = 8;     ///< Восьмеричное основание
const int kBaseHexadecimal = 16;  ///< Шестнадцатеричное основание

// Константы Unicode
const uint32_t kUnicodeMax = 0x10FFFF;  ///< Макс. код Unicode
const uint32_t kSurrogateStart = 0xD800;  ///< Начало суррогатных пар
const uint32_t kSurrogateEnd = 0xDFFF;  ///< Конец суррогатных пар
const uint8_t kUtf8OneByteBound = 0x80;  ///< Граница 1-байтовых символов
const uint8_t kUtf8TwoByteBound = 0x800;  ///< Граница 2-байтовых символов
const uint8_t kUtf8ThreeByteBound = 0x10000;  ///< Граница 3-байтовых символов

////////////////////////////////////////////////////////////
//                   Обявление функций                    //
////////////////////////////////////////////////////////////

static void parse_flag(const char *format, int *i, int *flag);
static void parse_width(const char *format, int *i, int params[], va_list args);
static void parse_precision(const char *format, int *i, int params[],
                            va_list args);
static void parse_modifier(const char *format, int *i, int *modifier);
static void parse_specifier(const char *format, int *i, int params[]);
static void parse_integer_specifier(int params[]);
static void parse_unsigned_specifier(int params[], char specifier);
static void parse_float_specifier(int params[], char specifier);

static int convert_format(char *str, int *str_idx, int params[], va_list args);
// Обработчики специфичных типов данных
static void handle_integer(char *str, int *idx, int params[], va_list args);
static void handle_unsigned(char *str, int *idx, int params[], va_list args);
static void handle_float(char *str, int *idx, int params[], va_list args);
static void handle_char(char *str, int *idx, int params[], va_list args);
static void handle_wchar(char *str, int *idx, int params[], va_list args);
static void handle_string(char *str, int *idx, int params[], va_list args);
static void handle_wstring(char *str, int *idx, int params[], va_list args);
static void handle_pointer(char *str, int *idx, int params[], va_list args);
static void handle_count(char *str, int *idx, int params[], va_list args);
static void handle_percent(char *str, int *idx);

static void add_sign(char *ch, bool b, int params[]);
static void convert_int_to_str(char *str, int *idx, long long value,
                               int params[]);
static void convert_uint_to_str(char *str, int *idx, unsigned long long value,
                                char ch, int params[]);
static void convert_char_to_str(char *str, int *idx, char c);
static void convert_string_to_str(char *str, int *idx, const char *s);
static void convert_pointer_prefix(char *str, int *idx);
static bool convert_wchar_to_str(char *str, int *idx, wchar_t wc);
static bool convert_wstring_to_str(char *str, int *idx, const wchar_t *ws);
static bool convert_special_float(char *str, int *idx, long double value,
                                  int params[]);
static void convert_float_to_str(char *str, int *idx, long double dval,
                                 int params[]);
static void format_g(long double dval, int *precision, int params[]);
static void format_f(char *str, int *idx, long double value, int precision,
                     int params[]);
static void format_e(char *str, int *idx, long double value, int precision,
                     int params[]);
static void format_fractional_part(char *str, int *idx, long double frac,
                                   int precision);
static void format_exponent(char *str, int *idx, int exp, int params[]);
static void format_float_value(char *str, int *idx, long double value,
                               int precision, int params[]);
static int parse_number(const char *format, int *i);

////////////////////////////////////////////////////////////
//                Основная функция sprintf                //
////////////////////////////////////////////////////////////

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
      if (format[i] == '\0') break;

      int params[PARAM_COUNT] = {[PARAM_FLAG] = -1,
                                 [PARAM_WIDTH] = -1,
                                 [PARAM_PRECISION] = -1,
                                 [PARAM_WIDTH_ASTERISK_VALUE] = 0,
                                 [PARAM_PRECISION_ASTERISK_VALUE] = 0,
                                 [PARAM_MODIFIER] = LENGTH_NULL,
                                 [PARAM_SPECIFIER] = -1,
                                 [PARAM_UPPERCASE] = false,
                                 [PARAM_BASE] = kBaseDecimal,
                                 [PARAM_SPEC_CHAR] = -1};

      parse_flag(format, &i, &params[PARAM_FLAG]);
      parse_width(format, &i, params, args);
      parse_precision(format, &i, params, args);
      parse_modifier(format, &i, &params[PARAM_MODIFIER]);
      parse_specifier(format, &i, params);

      if (convert_format(str, &idx, params, args) == -1) {
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

////////////////////////////////////////////////////////////
//             Функции парсинга формата                   //
////////////////////////////////////////////////////////////

static int parse_number(const char *format, int *i) {
  int num = 0;
  while (isdigit(format[*i])) {
    num = num * kBaseDecimal + (format[*i] - '0');
    (*i)++;
  }
  return num;
}

static void parse_flag(const char *format, int *i, int *flag) {
  switch (format[*i]) {
    case '-':
      *flag = FLAG_MINUS;
      (*i)++;
      break;
    case '+':
      *flag = FLAG_PLUS;
      (*i)++;
      break;
    case ' ':
      *flag = FLAG_SPACE;
      (*i)++;
      break;
    case '#':
      *flag = FLAG_HASH;
      (*i)++;
      break;
    case '0':
      *flag = FLAG_ZERO;
      (*i)++;
      break;
    default:
      *flag = -1;  // если не нашли флаг, оставляем -1
      break;
  }
}

static void parse_width(const char *format, int *i, int params[],
                        va_list args) {
  if (format[*i] == '*') {
    params[PARAM_WIDTH] = WIDTH_ASTERISK;
    params[PARAM_WIDTH_ASTERISK_VALUE] = va_arg(args, int);
    (*i)++;
  } else if (isdigit(format[*i])) {
    bool b = false;
    if (format[*i - 1] == '-') {
      params[PARAM_FLAG] = -1;
      b = true;
    }
    params[PARAM_WIDTH] = WIDTH_NUMBER;
    params[PARAM_WIDTH_ASTERISK_VALUE] = parse_number(format, i);
    if (b) params[PARAM_WIDTH_ASTERISK_VALUE] *= -1;
  }
}

static void parse_precision(const char *format, int *i, int params[],
                            va_list args) {
  if (format[*i] == '.') {
    (*i)++;
    if (format[*i] == '*') {
      params[PARAM_PRECISION] = PRECISION_ASTERISK;
      params[PARAM_PRECISION_ASTERISK_VALUE] = va_arg(args, int);
      (*i)++;
    } else if (isdigit(format[*i])) {
      params[PARAM_PRECISION] = PRECISION_NUMBER;
      params[PARAM_PRECISION_ASTERISK_VALUE] = parse_number(format, i);
      if (params[PARAM_PRECISION_ASTERISK_VALUE] < 0)
        params[PARAM_PRECISION_ASTERISK_VALUE] = 0;
    }
  }
}

static void parse_modifier(const char *format, int *i, int *modifier) {
  *modifier = LENGTH_NULL;
  if (format[*i] == 'h') {
    *modifier = (format[*i + 1] == 'h') ? LENGTH_HH : LENGTH_H;
    *i += (*modifier == LENGTH_HH) ? 2 : 1;
  } else if (format[*i] == 'l') {
    *modifier = (format[*i + 1] == 'l') ? LENGTH_LL : LENGTH_L;
    *i += (*modifier == LENGTH_LL) ? 2 : 1;
  } else if (format[*i] == 'L') {
    *modifier = LENGTH_CAP_L;
    (*i)++;
  }
}

static void parse_specifier(const char *format, int *i, int params[]) {
  switch (format[*i]) {
    case 'd':
    case 'i':
      parse_integer_specifier(params);
      break;
    case 'u':
    case 'o':
    case 'x':
    case 'X':
      parse_unsigned_specifier(params, format[*i]);
      break;
    case 'f':
    case 'e':
    case 'E':
    case 'g':
    case 'G':
      parse_float_specifier(params, format[*i]);
      break;
    case 'c':
      params[PARAM_SPECIFIER] =
          (params[PARAM_MODIFIER] == LENGTH_L) ? TYPE_WCHAR : TYPE_CHAR;
      break;
    case 's':
      params[PARAM_SPECIFIER] =
          (params[PARAM_MODIFIER] == LENGTH_L) ? TYPE_WSTRING : TYPE_STRING;
      break;
    case 'p':
      params[PARAM_SPECIFIER] = TYPE_POINTER;
      params[PARAM_BASE] = kBaseHexadecimal;
      break;
    case '%':
      params[PARAM_SPECIFIER] = TYPE_PERCENT;
      break;
    case 'n':
      params[PARAM_SPECIFIER] = TYPE_PTR;
      break;
  }
}

static void parse_integer_specifier(int params[]) {
  if (params[PARAM_MODIFIER] == LENGTH_LL)
    params[PARAM_SPECIFIER] = TYPE_LONGLONG;
  else if (params[PARAM_MODIFIER] == LENGTH_L)
    params[PARAM_SPECIFIER] = TYPE_LONG;
  else
    params[PARAM_SPECIFIER] = TYPE_INT;
}

static void parse_unsigned_specifier(int params[], char specifier) {
  if (params[PARAM_MODIFIER] == LENGTH_LL)
    params[PARAM_SPECIFIER] = TYPE_ULONGLONG;
  else if (params[PARAM_MODIFIER] == LENGTH_L)
    params[PARAM_SPECIFIER] = TYPE_ULONG;
  else
    params[PARAM_SPECIFIER] = TYPE_UINT;

  if (specifier == 'o') {
    params[PARAM_BASE] = kBaseOctal;
  } else if (specifier == 'x' || specifier == 'X') {
    params[PARAM_BASE] = kBaseHexadecimal;
    if (specifier == 'X') {
      params[PARAM_UPPERCASE] = true;
    }
  }
}

static void parse_float_specifier(int params[], char specifier) {
  if (params[PARAM_MODIFIER] == LENGTH_CAP_L)
    params[PARAM_SPECIFIER] = TYPE_LONGDOUBLE;
  else
    params[PARAM_SPECIFIER] = TYPE_FLOAT;

  char base_char = tolower(specifier);
  if (base_char == 'e') {
    params[PARAM_SPEC_CHAR] = CHAR_E;
  } else if (base_char == 'g') {
    params[PARAM_SPEC_CHAR] = CHAR_G;
  } else {
    params[PARAM_SPEC_CHAR] = CHAR_F;
  }

  if (isupper(specifier)) {
    params[PARAM_UPPERCASE] = true;
  }
}

static int convert_format(char *str, int *str_idx, int params[], va_list args) {
  switch (params[PARAM_SPECIFIER]) {
    case TYPE_INT:
    case TYPE_LONG:
    case TYPE_LONGLONG:
      handle_integer(str, str_idx, params, args);
      break;
    case TYPE_UINT:
    case TYPE_ULONG:
    case TYPE_ULONGLONG:
      handle_unsigned(str, str_idx, params, args);
      break;
    case TYPE_FLOAT:
    case TYPE_LONGDOUBLE:
      handle_float(str, str_idx, params, args);
      break;
    case TYPE_CHAR:
      handle_char(str, str_idx, params, args);
      break;
    case TYPE_WCHAR:
      handle_wchar(str, str_idx, params, args);
      break;
    case TYPE_STRING:
      handle_string(str, str_idx, params, args);
      break;
    case TYPE_WSTRING:
      handle_wstring(str, str_idx, params, args);
      break;
    case TYPE_POINTER:
      handle_pointer(str, str_idx, params, args);
      break;
    case TYPE_PTR:
      handle_count(str, str_idx, params, args);
      break;
    case TYPE_PERCENT:
      handle_percent(str, str_idx);
      break;
  }
  return 0;
}

////////////////////////////////////////////////////////////
//             Обработчики типов данных                   //
////////////////////////////////////////////////////////////

static void handle_integer(char *str, int *idx, int params[], va_list args) {
  long long val;
  switch (params[PARAM_SPECIFIER]) {
    case TYPE_INT:
      val = (long long)va_arg(args, int);
      break;
    case TYPE_LONG:
      val = (long long)va_arg(args, long);
      break;
    default:
      val = va_arg(args, long long);
      break;
  }
  convert_int_to_str(str, idx, val, params);
}

static void handle_unsigned(char *str, int *idx, int params[], va_list args) {
  unsigned long long val;
  switch (params[PARAM_SPECIFIER]) {
    case TYPE_UINT:
      val = (unsigned long long)va_arg(args, unsigned int);
      break;
    case TYPE_ULONG:
      val = (unsigned long long)va_arg(args, unsigned long);
      break;
    default:
      val = va_arg(args, unsigned long long);
      break;
  }
  convert_uint_to_str(str, idx, val, LENGTH_NULL, params);
}

static void handle_float(char *str, int *idx, int params[], va_list args) {
  long double val = (params[PARAM_SPECIFIER] == TYPE_FLOAT)
                        ? (long double)va_arg(args, double)
                        : va_arg(args, long double);

  if (!convert_special_float(str, idx, val, params)) {
    convert_float_to_str(str, idx, val, params);
  }
}

static void handle_char(char *str, int *idx, int params[], va_list args) {
  char c = (char)va_arg(args, int);
  convert_char_to_str(str, idx, c);
}

static void handle_wchar(char *str, int *idx, int params[], va_list args) {
  wchar_t wcval = va_arg(args, wchar_t);
  if (!convert_wchar_to_str(str, idx, wcval)) {
    *idx = -1;
  }
}

static void handle_string(char *str, int *idx, int params[], va_list args) {
  char *s = va_arg(args, char *);
  convert_string_to_str(str, idx, s);
}

static void handle_wstring(char *str, int *idx, int params[], va_list args) {
  wchar_t *wsval = va_arg(args, wchar_t *);
  if (!convert_wstring_to_str(str, idx, wsval)) {
    *idx = -1;
  }
}

static void handle_pointer(char *str, int *idx, int params[], va_list args) {
  void *ptr = va_arg(args, void *);
  if (ptr == NULL) {
    convert_string_to_str(str, idx, "(nil)");
  } else {
    convert_pointer_prefix(str, idx);
    convert_uint_to_str(str, idx, (uintptr_t)ptr, LENGTH_NULL, params);
  }
}

static void handle_count(char *str, int *idx, int params[], va_list args) {
  int *ptr = va_arg(args, int *);
  *ptr = *idx;
}

static void handle_percent(char *str, int *idx) {
  convert_char_to_str(str, idx, '%');
}

////////////////////////////////////////////////////////////
//             Функции конвертации данных                 //
////////////////////////////////////////////////////////////

static void add_sign(char *ch, bool b, int params[]) {
  if (b) {
    *ch = '-';
  } else {
    if (params[PARAM_FLAG] == FLAG_PLUS) {
      *ch = '+';
    } else if (params[PARAM_FLAG] == FLAG_SPACE) {
      *ch = ' ';
    }
  }
}

static int convert_uint_to_buffer(char *buf, unsigned long long value,
                                  int params[]) {
  char buffer[kMaxBufferSize];
  const char *digits =
      params[PARAM_UPPERCASE] ? "0123456789ABCDEF" : "0123456789abcdef";
  int i = 0;

  if (value == 0) {
    buffer[i++] = '0';
  } else {
    while (value) {
      buffer[i++] = digits[value % params[PARAM_BASE]];
      value /= params[PARAM_BASE];
    }
  }

  for (int j = 0; j < i; j++) {
    buf[j] = buffer[i - j - 1];
  }
  buf[i] = '\0';
  return i;
}

static void convert_num_len_pad_char_to_str(char *str, int *idx, int num_len,
                                            char pad_char) {
  for (int i = 0; i < num_len; i++) {
    convert_char_to_str(str, idx, pad_char);
  }
}

static void convert_PARAM_WIDTH_to_str(char *str, int *idx, int params[]) {
  if (params[PARAM_FLAG] == FLAG_ZERO)
    convert_num_len_pad_char_to_str(str, idx,
                                    params[PARAM_WIDTH_ASTERISK_VALUE], '0');
  else
    convert_num_len_pad_char_to_str(str, idx,
                                    params[PARAM_WIDTH_ASTERISK_VALUE], ' ');
}
static void convert_PARAM_PRECISION_to_str(char *str, int *idx, int params[]) {
  convert_num_len_pad_char_to_str(str, idx,
                                  params[PARAM_PRECISION_ASTERISK_VALUE], '0');
}
static void convert_PARAM_WIDTH_to_str_and(char *str, int *idx, int params[]) {
  convert_num_len_pad_char_to_str(str, idx, params[PARAM_WIDTH_ASTERISK_VALUE],
                                  ' ');
}

static void convert_int_to_str(char *str, int *idx, long long value,
                               int params[]) {
  char ch = LENGTH_NULL;

  add_sign(&ch, value < 0, params);
  if (value < 0) {
    unsigned long long positive = (value == LLONG_MIN)
                                      ? (unsigned long long)LLONG_MAX + 1
                                      : (unsigned long long)(-value);
    convert_uint_to_str(str, idx, positive, ch, params);
  } else {
    convert_uint_to_str(str, idx, value, ch, params);
  }
}

static void convert_uint_to_str(char *str, int *idx, unsigned long long value,
                                char ch, int params[]) {
  char buffer[kMaxBufferSize];

  int num_len = convert_uint_to_buffer(buffer, value, params);
  if (ch != LENGTH_NULL) num_len++;

  bool x = params[PARAM_WIDTH_ASTERISK_VALUE] > 0 ? true : false;

  if ((params[PARAM_PRECISION_ASTERISK_VALUE] -= num_len) < 0)
    params[PARAM_PRECISION_ASTERISK_VALUE] = 0;
  params[PARAM_WIDTH_ASTERISK_VALUE] = abs(params[PARAM_WIDTH_ASTERISK_VALUE]);
  params[PARAM_WIDTH_ASTERISK_VALUE] -= num_len;
  params[PARAM_WIDTH_ASTERISK_VALUE] -= params[PARAM_PRECISION_ASTERISK_VALUE];

  if (x) convert_PARAM_WIDTH_to_str(str, idx, params);
  convert_PARAM_PRECISION_to_str(str, idx, params);

  if (value == 0 && params[PARAM_PRECISION_ASTERISK_VALUE] == 0 &&
      params[PARAM_PRECISION] != -1) {
  } else {
    if (ch != LENGTH_NULL) {
      convert_char_to_str(str, idx, ch);
    }
    convert_string_to_str(str, idx, buffer);
  }

  if (!x) convert_PARAM_WIDTH_to_str_and(str, idx, params);
}

static void convert_char_to_str(char *str, int *idx, char c) {
  str[(*idx)++] = c;
}

static void convert_string_to_str(char *str, int *idx, const char *s) {
  if (s == NULL) {
    convert_string_to_str(str, idx, "(null)");
  } else {
    while (*s) {
      str[(*idx)++] = *s++;
    }
  }
}

static void convert_pointer_prefix(char *str, int *idx) {
  convert_char_to_str(str, idx, '0');
  convert_char_to_str(str, idx, 'x');
}

static bool convert_wchar_to_str(char *str, int *idx, wchar_t wc) {
  uint32_t code = (uint32_t)wc;

  if (code > kUnicodeMax ||
      (code >= kSurrogateStart && code <= kSurrogateEnd) || wc < 0) {
    return false;
  }

  if (code < kUtf8OneByteBound) {
    str[(*idx)++] = (char)code;
  } else if (code < kUtf8TwoByteBound) {
    str[(*idx)++] = 0xC0 | (code >> 6);
    str[(*idx)++] = 0x80 | (code & 0x3F);
  } else if (code < kUtf8ThreeByteBound) {
    str[(*idx)++] = 0xE0 | (code >> 12);
    str[(*idx)++] = 0x80 | ((code >> 6) & 0x3F);
    str[(*idx)++] = 0x80 | (code & 0x3F);
  } else {
    str[(*idx)++] = 0xF0 | (code >> 18);
    str[(*idx)++] = 0x80 | ((code >> 12) & 0x3F);
    str[(*idx)++] = 0x80 | ((code >> 6) & 0x3F);
    str[(*idx)++] = 0x80 | (code & 0x3F);
  }

  return true;
}

static bool convert_wstring_to_str(char *str, int *idx, const wchar_t *ws) {
  if (ws == NULL) {
    convert_string_to_str(str, idx, "(null)");
    return true;
  }

  int start_index = *idx;
  bool success = true;

  for (const wchar_t *tmp = ws; *tmp; tmp++) {
    if (!convert_wchar_to_str(str, idx, (*tmp))) {
      *idx = start_index;
      success = false;
      break;
    }
  }

  return success;
}

////////////////////////////////////////////////////////////
//          Функции работы с числами с плавающей точкой   //
////////////////////////////////////////////////////////////

static bool convert_special_float(char *str, int *idx, long double value,
                                  int params[]) {
  if (isnanl(value)) {
    convert_string_to_str(str, idx, params[PARAM_UPPERCASE] ? "NAN" : "nan");
    return true;
  } else if (isinfl(value)) {
    if (signbit(value)) {
      convert_string_to_str(str, idx,
                            params[PARAM_UPPERCASE] ? "-INF" : "-inf");
    } else {
      convert_string_to_str(str, idx, params[PARAM_UPPERCASE] ? "INF" : "inf");
    }
    return true;
  }
  return false;
}

static void add_sign2(char *str, int *idx, bool negative, int params[]) {
  if (negative) {
    str[(*idx)++] = '-';
  } else {
    if (params[PARAM_FLAG] == FLAG_PLUS) {
      str[(*idx)++] = '+';
    } else if (params[PARAM_FLAG] == FLAG_SPACE) {
      str[(*idx)++] = ' ';
    }
  }
}

static void convert_float_to_str(char *str, int *idx, long double dval,
                                 int params[]) {
  int precision = (params[PARAM_PRECISION] >= 0)
                      ? params[PARAM_PRECISION_ASTERISK_VALUE]
                      : kDefaultPrecision;
  add_sign2(str, idx, signbit(dval), params);
  dval = fabsl(dval);
  if (params[PARAM_SPEC_CHAR] == CHAR_G) {
    format_g(dval, &precision, params);
  }

  if (params[PARAM_SPEC_CHAR] == CHAR_F) {
    format_f(str, idx, dval, precision, params);
  } else if (params[PARAM_SPEC_CHAR] == CHAR_E) {
    format_e(str, idx, dval, precision, params);
  }
}

static void format_g(long double dval, int *precision, int params[]) {
  int exp =
      (dval == 0.0L) ? 0 : (int)floorl(log10l(dval));  // Расчёт экспоненты
  if (exp >= -4 && exp < *precision) {
    *precision = *precision - (exp + 1);
    if (*precision < 0) *precision = 0;
    if (exp == 0) *precision = 0;
    params[PARAM_SPEC_CHAR] = CHAR_F;
  } else {
    *precision = (*precision > 0) ? *precision - 1 : 0;
    params[PARAM_SPEC_CHAR] = CHAR_E;
  }
}

static void format_f(char *str, int *idx, long double value, int precision,
                     int params[]) {
  long double rounding = 0.5L * powl(10.0L, -precision);
  format_float_value(str, idx, value + rounding, precision, params);
}

static void format_e(char *str, int *idx, long double value, int precision,
                     int params[]) {
  int exp = 0;
  if (value != 0.0L) {
    exp = (int)floorl(log10l(fabsl(value)));
    value *= powl(10.0L, -exp);
  }

  long double rounding = 0.5L * powl(10.0L, -precision);
  value += rounding;

  // Коррекция экспоненты после округления
  if (fabsl(value) >= 10.0L) {
    value /= 10.0L;
    exp++;
  }

  format_float_value(str, idx, value, precision, params);
  format_exponent(str, idx, exp, params);
}

static void format_fractional_part(char *str, int *idx, long double frac,
                                   int precision) {
  if (precision <= 0) return;

  convert_char_to_str(str, idx, '.');

  for (int i = 0; i < precision; i++) {
    frac *= 10.0L;
    int digit = (int)frac;
    convert_char_to_str(str, idx, '0' + digit);
    frac -= digit;
  }
}

static void format_exponent(char *str, int *idx, int exp, int params[]) {
  convert_char_to_str(str, idx, params[PARAM_UPPERCASE] ? 'E' : 'e');
  convert_char_to_str(str, idx, exp >= 0 ? '+' : '-');

  exp = abs(exp);
  if (exp < 10) {
    convert_char_to_str(str, idx, '0');
  }
  convert_int_to_str(str, idx, exp, params);
}

static void format_float_value(char *str, int *idx, long double value,
                               int precision, int params[]) {
  long double int_part;
  long double frac_part = modfl(value, &int_part);

  convert_int_to_str(str, idx, (long long)int_part, params);
  format_fractional_part(str, idx, frac_part, precision);
}