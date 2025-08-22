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
  bool width_type;       ///< Тип ширины
  int width_value;      ///< Тип точности
  bool precision_type;   ///< Значение ширины для '*'
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

      parse_flags(format, &i, &params);
      parse_width(format, &i, params, args);
      parse_precision(format, &i, params, args);
      parse_modifier(format, &i, &params.modifier);
      parse_specifier(format, &i, params);

      if (process_format_conversion(str, &idx, params, args) == -1) {
        str[idx] = '\0';
        va_end(args);
        return -1;
      }
    } else {
      str[idx++] = format[i++];
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

static void parse_flags(const char *format, int *i, FormatParams *params) {
  typedef struct {
    char symbol;
    bool *flag;
  } FlagMapping;

  FlagMapping mappings[] = {{'-', &params->flag_minus},
                            {'+', &params->flag_plus},
                            {' ', &params->flag_space},
                            {'#', &params->flag_hash},
                            {'0', &params->flag_zero}};
  size_t num_mappings = sizeof(mappings) / sizeof(mappings[0]);

  bool continue_parsing = true;
  while (continue_parsing) {
    bool flag_found = false;

    for (size_t j = 0; j < num_mappings && !flag_found; j++) {
      if (format[*i] == mappings[j].symbol && !(*mappings[j].flag)) {
        *mappings[j].flag = true;
        (*i)++;
        flag_found = true;
      }
    }

    continue_parsing = flag_found;
  }
}

static void parse_width(const char *format, int *i, FormatParams params,
                        va_list args) {
  if (format[*i] == '*')
    params.width_type = true, params.width_value = abs(va_arg(args, int)),
    (*i)++;
  else if (isdigit(format[*i]))
    params.width_type = true, params.width_value = parse_number(format, i);
}

static void parse_precision(const char *format, int *i, FormatParams params,
                            va_list args) {
  if (format[*i] != '.') return;
  (*i)++;
  if (format[*i] == '*')
    params.precision_type = true,
    params.precision_value = abs(va_arg(args, int)), (*i)++;
  else if (isdigit(format[*i]))
    params.precision_type = true,
    params.precision_value = parse_number(format, i);
}

static void parse_modifier(const char *format, int *i, int *modifier) {
  char c = format[*i];
  char n = format[*i + 1];

  if (c == 'h')
    *modifier = (n == 'h') ? (*i += 2, LENGTH_HH) : (*i += 1, LENGTH_H);
  else if (c == 'l')
    *modifier = (n == 'l') ? (*i += 2, LENGTH_LL) : (*i += 1, LENGTH_L);
  else if (c == 'L')
    *modifier = LENGTH_CAP_L, (*i)++;
}

static void parse_specifier(const char *format, int *i, FormatParams params) {
  char spec = params.specifier = format[*i];
  if (isupper(spec)) params.uppercase = true;
  spec = tolower(spec);

  if (spec == 'd' || spec == 'i')
    parse_integer_specifier(params);
  else if (spec == 'u' || spec == 'o' || spec == 'x')
    parse_unsigned_specifier(params, spec);
  else if (spec == 'f' || spec == 'e' || spec == 'g')
    parse_float_specifier(params, spec);
  else if (spec == 'c')
    params.type = (params.modifier == LENGTH_L) ? TYPE_WCHAR : TYPE_CHAR;
  else if (spec == 's')
    params.type = (params.modifier == LENGTH_L) ? TYPE_WSTRING : TYPE_STRING;
  else if (spec == 'p')
    params.type = TYPE_POINTER, params.base = BaseHexadecimal;
  else if (spec == '%')
    params.type = TYPE_PERCENT;
  else if (spec == 'n')
    params.type = TYPE_PTR;

  (*i)++;
}

static int parse_number(const char *format, int *i) {
  int num = 0;
  while (isdigit(format[*i])) {
    num = num * BaseDecimal + (format[*i] - '0');
    (*i)++;
  }
  return num;
}

static void determine_integer_type(FormatParams params) {
  if (params.modifier == LENGTH_LL)
    params.type = TYPE_LONGLONG;
  else if (params.modifier == LENGTH_L)
    params.type = TYPE_LONG;
  else
    params.type = TYPE_INT;
}

static void determine_unsigned_type(FormatParams params, char specifier) {
  if (params.modifier == LENGTH_LL)
    params.type = TYPE_ULONGLONG;
  else if (params.modifier == LENGTH_L)
    params.type = TYPE_ULONG;
  else
    params.type = TYPE_UINT;

  if (specifier == 'o') {
    params.base = BaseOctal;
  } else if (specifier == 'x') {
    params.base = BaseHexadecimal;
  }
}

static void determine_float_type(FormatParams params, char specifier) {
  if (params.modifier == LENGTH_CAP_L)
    params.type = TYPE_LONGDOUBLE;
  else
    params.type = TYPE_FLOAT;

  if (specifier == 'e') {
    params.spec_char = CHAR_E;
  } else if (specifier == 'g') {
    params.spec_char = CHAR_G;
  } else if (specifier == 'f') {
    params.spec_char = CHAR_F;
  }
}

static int process_format_conversion(char *str, int *str_idx,
                                     FormatParams params, va_list args) {
  int result = 0;

  if (params.type <= TYPE_LONGLONG)
    handle_integer(str, str_idx, params, args);
  else if (params.type <= TYPE_ULONGLONG)
    handle_unsigned(str, str_idx, params, args);
  else if (params.type <= TYPE_LONGDOUBLE)
    handle_float(str, str_idx, params, args);
  else if (params.type == TYPE_CHAR)
    handle_char(str, str_idx, params, args);
  else if (params.type == TYPE_WCHAR)
    result = handle_wchar(str, str_idx, params, args);
  else if (params.type == TYPE_STRING)
    handle_string(str, str_idx, params, args);
  else if (params.type == TYPE_WSTRING)
    result = handle_wstring(str, str_idx, params, args);
  else if (params.type == TYPE_POINTER)
    handle_pointer(str, str_idx, params, args);
  else if (params.type == TYPE_PTR)
    handle_count(str, str_idx, params, args);
  else if (params.type == TYPE_PERCENT)
    handle_percent(str, str_idx);

  return result;
}






static void handle_integer_conversion(char *str, int *idx, FormatParams params,
                                      va_list args) {}

static void handle_unsigned_conversion(char *str, int *idx, FormatParams params,
                                       va_list args) {}

static void handle_float_conversion(char *str, int *idx, FormatParams params,
                                    va_list args) {}

static void handle_char_conversion(char *str, int *idx, FormatParams params,
                                   va_list args) {}

static void handle_string_conversion(char *str, int *idx, FormatParams params,
                                     va_list args) {}

static int handle_wide_char_conversion(char *str, int *idx, FormatParams params,
                                       va_list args) {}

static int handle_wide_string_conversion(char *str, int *idx,
                                         FormatParams params, va_list args) {}

static void handle_pointer_conversion(char *str, int *idx, FormatParams params,
                                      va_list args) {}

static void handle_count_conversion(char *str, int *idx, FormatParams params,
                                    va_list args) {}

static void handle_percent_conversion(char *str, int *idx) {}

static int parse_number(const char *format, int *i) {}

// static int add_sign_prefix(char *buf, bool negative, FormatParams params) {}

// static void convert_unsigned_to_buffer(char *buf, int *idx_buf, unsigned long
// long value, FormatParams params) {}

// static void add_padding_chars(char *str, int *idx, int num_len, char
// pad_char) {}

// static void convert_integer_to_string(char *str, int *idx, long long value,
// FormatParams params) {}

// static void convert_unsigned_to_string(char *str, int *idx, unsigned long
// long value, FormatParams params) {}

// static void apply_formatting_to_buffer(char *buffer, char sign_char, int
// num_len, char *str, int *idx, FormatParams params) {}

// static void add_base_prefix(FormatParams params, int *hash, char *str, int
// *idx) {}

// static void apply_string_formatting(char *str, int *idx, const char *buffer,
// FormatParams params) {}

// static void apply_float_formatting(char *buffer, char sign_char, int num_len,
// char *str, int *idx, FormatParams params) {}

// static void append_char_to_buffer(char *buffer, int *idx_buffer, char c) {}

// static void append_string_to_buffer(char *buffer, int *idx_buffer, const char
// *s) {}

// static int convert_wchar_to_utf8(char *dest, wchar_t wc) {}

// static bool handle_special_float_cases(char *str, int *idx, long double
// value, FormatParams params) {}

// static void convert_float_to_string(char *str, int *idx, long double dval,
// FormatParams params) {}

// static int determine_float_format(long double dval, int *precision,
// FormatParams params) {}

// static void format_float_fixed(char *buf, int *idx_buf, long double value,
// int precision, FormatParams params) {}

// static void format_float_scientific(char *buf, int *idx_buf, long double
// value, int precision, FormatParams params) {}

// static void format_fraction_part(char *buf, int *idx_buf, long double frac,
// int precision, FormatParams params) {}

// static void format_fraction_part_general(char *buf, int *idx_buf, long double
// frac, int precision, FormatParams params) {}

// static void format_exponent_part(char *buf, int *idx_buf, int exp,
// FormatParams params) {}