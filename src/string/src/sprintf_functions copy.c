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
  TYPE_INT,  ///< %d, %i, %hd, %hhd
  TYPE_SHORT,
  TYPE_SCHAR,
  TYPE_LONG,      ///< %ld, %li
  TYPE_LONGLONG,  ///< %lld, %lli

  // Целочисленные беззнаковые
  TYPE_UINT,  ///< %u, %o, %x, %X, %hu, %hhu
  TYPE_USHORT,
  TYPE_UCHAR,
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
  TYPE_N_INT,    ///< %n (int*)
  TYPE_N_SCHAR,
  TYPE_N_SHORT,
  TYPE_N_LONG,
  TYPE_N_LONGLONG
};

typedef struct {
  bool flag_minus;      ///< '-' (left-justify)
  bool flag_plus;       ///< '+' (show plus sign)
  bool flag_space;      ///< ' ' (space for positive numbers)
  bool flag_hash;       ///< '#' (alternate form)
  bool flag_zero;       ///< '0' (zero-padding)
  bool width_type;      ///< Тип ширины
  int width_value;      ///< Тип точности
  bool precision_type;  ///< Значение ширины для '*'
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

typedef struct {
  const char symbol;
  int *flag;
} FlagMapping;

typedef struct {
  const char *str;
  int mod;
} ModifierMapping;

typedef struct {
  char specifier;
  void (*handler)(FormatParams *);
} SpecifierMapping;

#define ARRAY_SIZE(arr) (sizeof(arr) / sizeof((arr)[0]))

// Константы форматирования
#define BaseDecimal 10  ///< Десятичное основание
#define BaseOctal 8     ///< Восьмеричное основание
#define BaseHexadecimal 16  ///< Шестнадцатеричное основание

#define PRIMARY_LOCALE "en_US.UTF-8"
#define FALLBACK_LOCALE "C.UTF-8"

int s21_sprintf(char *str, const char *format, ...) {
  if (!str || !format) return -1;
  setlocale(LC_ALL, PRIMARY_LOCALE) || setlocale(LC_ALL, FALLBACK_LOCALE);

  va_list args;
  va_start(args, format);
  int idx = 0;
  bool error = false;

  for (int i = 0; format[i] && !error;) {
    if (format[i] == '%') {
      if (format[i++] == '\0') {
        error = true;
        continue;
      }

      FormatParams params = init_format_params();
      parse_format(format, &i, &params, args);
      error = process_format_conversion(str, &idx, params, args);

    } else
      str[idx++] = format[i], i++;
  }

  str[idx] = '\0';
  va_end(args);
  return error ? -1 : idx;
}

static FormatParams init_format_params() {
  FormatParams params = {.flag_minus = false,
                         .flag_plus = false,
                         .flag_space = false,
                         .flag_hash = false,
                         .flag_zero = false,
                         .width_type = false,
                         .width_value = 0,
                         .precision_type = false,
                         .precision_value = 0,
                         .modifier = LENGTH_NULL,
                         .specifier = -1,
                         .type = -1,
                         .uppercase = false,
                         .base = BaseDecimal,
                         .spec_char = -1};
  return params;
}

static void parse_format(const char *format, int *i, FormatParams *params,
                         va_list args) {
  parse_flags(format, i, params);
  parse_width(format, i, params, args);
  parse_precision(format, i, params, args);
  parse_modifier(format, i, params);
  parse_specifier(format, i, params);
}

static void parse_flags(const char *format, int *i, FormatParams *params) {
  FlagMapping mappings[] = {{'-', &params->flag_minus},
                            {'+', &params->flag_plus},
                            {' ', &params->flag_space},
                            {'#', &params->flag_hash},
                            {'0', &params->flag_zero}};

  bool continue_parsing = true;
  while (continue_parsing) {
    bool flag_found = false;

    for (size_t j = 0; j < ARRAY_SIZE(mappings) && !flag_found; j++) {
      if (format[*i] == mappings[j].symbol && !(*mappings[j].flag)) {
        *mappings[j].flag = true;
        (*i)++;
        flag_found = true;
      }
    }
    continue_parsing = flag_found;
  }
}

static int parse_number(const char *format, int *i) {
  int num = 0;
  while (isdigit(format[*i])) {
    num = num * BaseDecimal + (format[*i] - '0');
    (*i)++;
  }
  return num;
}

static void parse_numeric_value(const char *format, int *i, va_list args,
                                bool *type_flag, int *value) {
  if (format[*i] == '*')
    *type_flag = true, *value = abs(va_arg(args, int)), (*i)++;
  else if (isdigit(format[*i]))
    *type_flag = true, *value = parse_number(format, i);
}

static void parse_width(const char *format, int *i, FormatParams *p,
                        va_list args) {
  parse_numeric_value(format, i, args, &p->width_type, &p->width_value);
}

static void parse_precision(const char *format, int *i, FormatParams *p,
                            va_list args) {
  if (format[*i] != '.') return;
  (*i)++;
  p->precision_type = true;  // При "%.[type]" точность по умолчанию -> 0
  parse_numeric_value(format, i, args, &p->precision_type, &p->precision_value);
}

static void parse_modifier(const char *format, int *idx, FormatParams *params) {
  ModifierMapping modifiers[] = {{"hh", LENGTH_HH},
                                 {"h", LENGTH_H},
                                 {"ll", LENGTH_LL},
                                 {"l", LENGTH_L},
                                 {"L", LENGTH_CAP_L}};

  for (size_t i = 0; i < ARRAY_SIZE(modifiers); i++) {
    size_t len = strlen(modifiers[i].str);
    if (strncmp(format + *idx, modifiers[i].str, len) == 0) {
      params->modifier = modifiers[i].mod;
      *idx += len;
      return;
    }
  }
}

static void parse_specifier(const char *format, int *i, FormatParams *params) {
  char original_spec = format[*i];
  params->specifier = original_spec;
  params->uppercase = isupper(original_spec);
  char spec = tolower(original_spec);

  SpecifierMapping mappings[] = {
      {'d', handle_di_specifier}, {'i', handle_di_specifier},
      {'u', handle_u_specifier},  {'o', handle_o_specifier},
      {'x', handle_x_specifier},  {'f', handle_f_specifier},
      {'e', handle_e_specifier},  {'g', handle_g_specifier},
      {'c', handle_c_specifier},  {'s', handle_s_specifier},
      {'p', handle_p_specifier},  {'%', handle_percent_specifier},
      {'n', handle_n_specifier}};

  bool found = false;

  for (size_t idx = 0; idx < ARRAY_SIZE(mappings) && !found; idx++) {
    if (mappings[idx].specifier == spec) {
      mappings[idx].handler(params);
      found = true;
    }
  }

  if (found) (*i)++;
}

static void handle_di_specifier(FormatParams *params) {
  set_signed_type(params);
}
static void handle_u_specifier(FormatParams *params) {
  set_unsigned_type(params);
  params->base = BaseDecimal;
}
static void handle_o_specifier(FormatParams *params) {
  set_unsigned_type(params);
  params->base = BaseOctal;
}
static void handle_x_specifier(FormatParams *params) {
  set_unsigned_type(params);
  params->base = BaseHexadecimal;
}
static void handle_f_specifier(FormatParams *params) {
  set_float_type(params);
  params->spec_char = CHAR_F;
}
static void handle_e_specifier(FormatParams *params) {
  set_float_type(params);
  params->spec_char = CHAR_E;
}
static void handle_g_specifier(FormatParams *params) {
  set_float_type(params);
  params->spec_char = CHAR_G;
}
static void handle_c_specifier(FormatParams *params) {
  params->type = (params->modifier == LENGTH_L) ? TYPE_WCHAR : TYPE_CHAR;
}
static void handle_s_specifier(FormatParams *params) {
  params->type = (params->modifier == LENGTH_L) ? TYPE_WSTRING : TYPE_STRING;
}
static void handle_p_specifier(FormatParams *params) {
  params->type = TYPE_POINTER;
  params->base = BaseHexadecimal;
}
static void handle_percent_specifier(FormatParams *params) {
  params->type = TYPE_PERCENT;
}
static void handle_n_specifier(FormatParams *params) {
  handle_n_specifier(params);
}
static void set_signed_type(FormatParams *params) {
  if (params->modifier == LENGTH_LL)
    params->type = TYPE_LONGLONG;
  else if (params->modifier == LENGTH_L)
    params->type = TYPE_LONG;
  else if (params->modifier == LENGTH_H)
    params->type = TYPE_SHORT;
  else if (params->modifier == LENGTH_HH)
    params->type = TYPE_SCHAR;
  else
    params->type = TYPE_INT;
}
static void set_unsigned_type(FormatParams *params) {
  if (params->modifier == LENGTH_LL)
    params->type = TYPE_ULONGLONG;
  else if (params->modifier == LENGTH_L)
    params->type = TYPE_ULONG;
  else if (params->modifier == LENGTH_H)
    params->type = TYPE_USHORT;
  else if (params->modifier == LENGTH_HH)
    params->type = TYPE_UCHAR;
  else
    params->type = TYPE_UINT;
}
static void set_float_type(FormatParams *params) {
  if (params->modifier == LENGTH_CAP_L)
    params->type = TYPE_LONGDOUBLE;
  else
    params->type = TYPE_FLOAT;
}
static void handle_n_specifier(FormatParams *params) {
  if (params->modifier == LENGTH_HH)
    params->type = TYPE_N_SCHAR;
  else if (params->modifier == LENGTH_H)
    params->type = TYPE_N_SHORT;
  else if (params->modifier == LENGTH_L)
    params->type = TYPE_N_LONG;
  else if (params->modifier == LENGTH_LL)
    params->type = TYPE_N_LONGLONG;
  else
    params->type = TYPE_N_INT;
}

static bool process_format_conversion(char *str, int *str_idx,
                                     FormatParams params, va_list args) {
  bool result = true;

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
  else if (params.type == TYPE_PERCENT)
    handle_percent(str, str_idx);
  else if (params.type <= TYPE_N_LONGLONG)
    handle_count(str, str_idx, params, args);

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