#include <ctype.h>
#include <limits.h>
#include <locale.h>
#include <math.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include <wchar.h>

#include "../include/s21_string.h"

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

typedef struct {
  bool flag_minus;      ///< '-' (left-justify)
  bool flag_plus;       ///< '+' (show plus sign)
  bool flag_space;      ///< ' ' (space for positive numbers)
  bool flag_hash;       ///< '#' (alternate form)
  bool flag_zero;       ///< '0' (zero-padding)
  int width_type;       ///< Тип ширины
  int width_value;      ///< Тип точности
  int precision_type;   ///< Значение ширины для '*'
  int precision_value;  ///< Значение точности для '.*'
  int modifier;         ///< Модификатор длины
  int specifier;        ///< Спецификатор типа
  int type;             ///< Тип данных
  bool uppercase;       ///< Флаг верхнего регистра
  int base;       ///< Основание системы счисления
  int spec_char;  ///< Специальный символ формата
} FormatParams;

/** Символы формата чисел с плавающей точкой */
enum FormatChar {
  CHAR_F,  ///< Формат 'f'
  CHAR_E,  ///< Формат 'e'
  CHAR_G   ///< Формат 'g'
};

// Константы форматирования
#define BaseDecimal 10  ///< Десятичное основание
#define BaseOctal 8     ///< Восьмеричное основание
#define BaseHexadecimal 16  ///< Шестнадцатеричное основание

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

      FormatParams params = init_format_params();

      parse_flag(format, &i, params);
      parse_width(format, &i, params, args);
      parse_precision(format, &i, params, args);
      parse_modifier(format, &i, &params);
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

static FormatParams init_format_params() {
  FormatParams params = {.flag_minus = false,
                         .flag_plus = false,
                         .flag_space = false,
                         .flag_hash = false,
                         .flag_zero = false,
                         .width_type = -1,
                         .width_value = 0,
                         .precision_type = -1,
                         .precision_value = 0,
                         .modifier = LENGTH_NULL,
                         .specifier = -1,
                         .type = -1,
                         .uppercase = false,
                         .base = BaseDecimal,
                         .spec_char = -1};
  return params;
}

static int parse_number(const char *format, int *i) {}

static void parse_flag(const char *format, int *i, FormatParams params) {}

static void parse_width(const char *format, int *i, FormatParams params,
                        va_list args) {}

static void parse_precision(const char *format, int *i, FormatParams params,
                            va_list args) {}

static void parse_modifier(const char *format, int *i, int *modifier) {}

static void parse_specifier(const char *format, int *i, FormatParams params) {}

static void parse_integer_specifier(FormatParams params) {}

static void parse_unsigned_specifier(FormatParams params, char specifier) {}

static void parse_float_specifier(FormatParams params, char specifier) {}

static int convert_format(char *str, int *str_idx, FormatParams params,
                          va_list args) {}

static void handle_integer(char *str, int *idx, FormatParams params,
                           va_list args) {}

static void handle_unsigned(char *str, int *idx, FormatParams params,
                            va_list args) {}

static void handle_float(char *str, int *idx, FormatParams params,
                         va_list args) {}

static void handle_char(char *str, int *idx, FormatParams params,
                        va_list args) {}

static void handle_string(char *str, int *idx, FormatParams params,
                          va_list args) {}

static int handle_wchar(char *str, int *idx, FormatParams params,
                        va_list args) {}

static int handle_wstring(char *str, int *idx, FormatParams params,
                          va_list args) {}

static void handle_pointer(char *str, int *idx, FormatParams params,
                           va_list args) {}

static void handle_count(char *str, int *idx, FormatParams params,
                         va_list args) {}

static void handle_percent(char *str, int *idx) {}

static int add_sign(char *buf, bool negative, FormatParams params) {}

static void convert_uint_to_buffer(char *buf, int *idx_buf,
                                   unsigned long long value,
                                   FormatParams params) {}

static void convert_num_len_pad_char_to_str(char *str, int *idx, int num_len,
                                            char pad_char) {}

static void convert_int_to_str(char *str, int *idx, long long value,
                               FormatParams params) {}

static void convert_uint_to_str(char *str, int *idx, unsigned long long value,
                                FormatParams params) {}

static void convert_buffer_to_str(char *buffer, char sign_char, int num_len,
                                  char *str, int *idx, FormatParams params) {}

static void convert_hash_to_buffer(FormatParams params, int *hash, char *str,
                                   int *idx) {}

static void convert_string_buffer_to_str(char *str, int *idx,
                                         const char *buffer,
                                         FormatParams params) {}

static void convert_float_buffer_to_str(char *buffer, char sign_char,
                                        int num_len, char *str, int *idx,
                                        FormatParams params) {}

static void convert_char_to_buffer(char *buffer, int *idx_buffer, char c) {}

static void convert_string_to_buffer(char *buffer, int *idx_buffer,
                                     const char *s) {}

static int wchar_to_utf8(char *dest, wchar_t wc) {}

static bool convert_special_float(char *str, int *idx, long double value,
                                  FormatParams params) {}

static void convert_float_to_str(char *str, int *idx, long double dval,
                                 FormatParams params) {}

static int format_g(long double dval, int *precision, FormatParams params) {}

static void format_f(char *buf, int *idx_buf, long double value, int precision,
                     FormatParams params) {}

static void format_e(char *buf, int *idx_buf, long double value, int precision,
                     FormatParams params) {}

static void format_fractional_part(char *buf, int *idx_buf, long double frac,
                                   int precision, FormatParams params) {}

static void format_fractional_partG(char *buf, int *idx_buf, long double frac,
                                    int precision, FormatParams params) {}

static void format_exponent(char *buf, int *idx_buf, int exp,
                            FormatParams params) {}