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

////////////////////////////////////////////////////////////
//                 Перечисления и константы               //
////////////////////////////////////////////////////////////

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
  FLAG_MINUS,                  ///< '-' (left-justify)
  FLAG_PLUS,                   ///< '+' (show plus sign)
  FLAG_SPACE,                  ///< ' ' (space for positive numbers)
  FLAG_HASH,                   ///< '#' (alternate form)
  FLAG_ZERO,                   ///< '0' (zero-padding)
  PARAM_WIDTH,                 ///< Тип ширины
  PARAM_PRECISION,             ///< Тип точности
  PARAM_WIDTH_ASTERISK_VALUE,  ///< Значение ширины для '*'
  PARAM_PRECISION_ASTERISK_VALUE,  ///< Значение точности для '.*'
  PARAM_MODIFIER,                  ///< Модификатор длины
  PARAM_SPECIFIER,                 ///< Спецификатор типа
  TYPE,                            ///< Тип данных
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
#define DefaultPrecision 6  ///< Точность по умолчанию
#define MaxBufferSize 65  ///< Максимальный размер буфера
#define MaxUtf8Bytes 4    ///< Макс. байт на UTF-8 символ
#define MaxMbLen 1024  ///< Макс. длина многобайтовой строки
#define BaseDecimal 10  ///< Десятичное основание
#define BaseOctal 8     ///< Восьмеричное основание
#define BaseHexadecimal 16  ///< Шестнадцатеричное основание

// Константы Unicode
#define UnicodeMax 0x10FFFF    ///< Макс. код Unicode
#define SurrogateStart 0xD800  ///< Начало суррогатных пар
#define SurrogateEnd 0xDFFF    ///< Конец суррогатных пар
#define Utf8OneByteBound 0x80  ///< Граница 1-байтовых символов
#define Utf8TwoByteBound 0x800  ///< Граница 2-байтовых символов
#define Utf8ThreeByteBound 0x1000  ///< Граница 3-байтовых символов
#define Utf8FourByteBound 0x110000
////////////////////////////////////////////////////////////
//                   Обявление функций                    //
////////////////////////////////////////////////////////////

static int parse_number(const char *format, int *i);
static void parse_flag(const char *format, int *i, int params[]);
static void parse_width(const char *format, int *i, int params[], va_list args);
static void parse_precision(const char *format, int *i, int params[],
                            va_list args);
static void parse_modifier(const char *format, int *i, int *modifier);
static void parse_specifier(const char *format, int *i, int params[]);
static void parse_integer_specifier(int params[]);
static void parse_unsigned_specifier(int params[], char specifier);
static void parse_float_specifier(int params[], char specifier);
static int convert_format(char *str, int *str_idx, int params[], va_list args);
static void handle_integer(char *str, int *idx, int params[], va_list args);
static void handle_unsigned(char *str, int *idx, int params[], va_list args);
static void handle_float(char *str, int *idx, int params[], va_list args);
static void handle_char(char *str, int *idx, int params[], va_list args);
static void handle_string(char *str, int *idx, int params[], va_list args);
static int handle_wchar(char *str, int *idx, int params[], va_list args);
static int handle_wstring(char *str, int *idx, int params[], va_list args);
static void handle_pointer(char *str, int *idx, int params[], va_list args);
static void handle_count(char *str, int *idx, int params[], va_list args);
static void handle_percent(char *str, int *idx);
static int add_sign(char *buf, bool negative, int params[]);
static void convert_uint_to_buffer(char *buf, int *idx_buf,
                                   unsigned long long value, int params[]);
static void convert_num_len_pad_char_to_str(char *str, int *idx, int num_len,
                                            char pad_char);
static void convert_int_to_str(char *str, int *idx, long long value,
                               int params[]);
static void convert_uint_to_str(char *str, int *idx, unsigned long long value,
                                int params[]);
static void convert_string_buffer_to_str(char *str, int *idx,
                                         const char *buffer, int params[]);
static void convert_buffer_to_str(char *buffer, char ch, int num_len, char *str,
                                  int *idx, int params[]);
static void convert_hash_to_buffer(int params[], int *hash, char *str,
                                   int *idx);
static void convert_float_buffer_to_str(char *buffer, char sign_char,
                                        int num_len, char *str, int *idx,
                                        int params[]);
static void convert_char_to_buffer(char *buffer, int *idx_buffer, char c);
static void convert_string_to_buffer(char *buffer, int *idx_buffer,
                                     const char *s);
static int wchar_to_utf8(char *dest, wchar_t wc);
static bool convert_special_float(char *str, int *idx, long double value,
                                  int params[]);
static void convert_float_to_str(char *str, int *idx, long double dval,
                                 int params[]);
static int format_g(long double dval, int *precision, int params[]);
static void format_f(char *buf, int *idx_buf, long double value, int precision,
                     int params[]);
static void format_e(char *buf, int *idx_buf, long double value, int precision,
                     int params[]);
static void format_fractional_part(char *buf, int *idx_buf, long double frac,
                                   int precision, int params[]);
static void format_fractional_partG(char *buf, int *idx_buf, long double frac,
                                    int precision, int params[]);
static void format_exponent(char *buf, int *idx_buf, int exp, int params[]);
static void format_float_value(char *buf, int *idx_buf, long double frac_part,
                               int precision, int params[]);

////////////////////////////////////////////////////////////
//                Основная функция sprintf                //
////////////////////////////////////////////////////////////

static int parse_format(const char *format, int *i, int params[],
                        va_list args) {
  parse_flag(format, i, params);
  parse_width(format, i, params, args);
  parse_precision(format, i, params, args);
  parse_modifier(format, i, &params[PARAM_MODIFIER]);
  parse_specifier(format, i, params);
}

int s21_sprintf(char *str, const char *format, ...) {
  if (!str || !format) return -1;
  if (!setlocale(LC_ALL, "en_US.UTF-8")) {
    setlocale(LC_ALL, "C.UTF-8");
  }

  va_list args;
  va_start(args, format);
  int idx = 0;
  bool error = false;

  for (int i = 0; format[i] && !error;) {
    if (format[i] == '%') {
      i++;
      if (format[i] == '\0') {
        error = true;
        continue;
      }

      int params[PARAM_COUNT] = {[FLAG_MINUS] = false,
                                 [FLAG_PLUS] = false,
                                 [FLAG_SPACE] = false,
                                 [FLAG_HASH] = false,
                                 [FLAG_ZERO] = false,
                                 [PARAM_WIDTH] = -1,
                                 [PARAM_PRECISION] = -1,
                                 [PARAM_WIDTH_ASTERISK_VALUE] = 0,
                                 [PARAM_PRECISION_ASTERISK_VALUE] = 0,
                                 [PARAM_MODIFIER] = LENGTH_NULL,
                                 [PARAM_SPECIFIER] = -1,
                                 [TYPE] = -1,
                                 [PARAM_UPPERCASE] = false,
                                 [PARAM_BASE] = BaseDecimal,
                                 [PARAM_SPEC_CHAR] = -1};

      parse_format(format, &i, params, args);
      error = convert_format(str, &idx, params, args);

    } else
      str[idx++] = format[i], i++;
  }

  str[idx] = '\0';
  va_end(args);
  return error ? -1 : idx;
}

////////////////////////////////////////////////////////////
//             Функции парсинга формата                   //
////////////////////////////////////////////////////////////

static int parse_number(const char *format, int *i) {
  int num = 0;
  while (isdigit(format[*i])) {
    num = num * BaseDecimal + (format[*i] - '0');
    (*i)++;
  }
  return num;
}

static void parse_flag(const char *format, int *i, int params[]) {
  typedef struct {
    char symbol;
    int *flag_ptr;
  } FlagMapping;

  FlagMapping mappings[] = {{'-', &params[FLAG_MINUS]},
                            {'+', &params[FLAG_PLUS]},
                            {' ', &params[FLAG_SPACE]},
                            {'#', &params[FLAG_HASH]},
                            {'0', &params[FLAG_ZERO]}};

  size_t num_mappings = sizeof(mappings) / sizeof(mappings[0]);

  bool continue_parsing = true;
  while (continue_parsing) {
    bool flag_found = false;

    for (size_t j = 0; j < num_mappings && !flag_found; j++) {
      if (format[*i] == mappings[j].symbol && !(*mappings[j].flag_ptr)) {
        *mappings[j].flag_ptr = true;
        (*i)++;
        flag_found = true;
      }
    }
    continue_parsing = flag_found;
  }
}

static void parse_width(const char *format, int *i, int params[],
                        va_list args) {
  if (format[*i] == '*')
    params[PARAM_WIDTH] = true,
    params[PARAM_WIDTH_ASTERISK_VALUE] = abs(va_arg(args, int)), (*i)++;
  else if (isdigit(format[*i]))
    params[PARAM_WIDTH] = true,
    params[PARAM_WIDTH_ASTERISK_VALUE] = parse_number(format, i);
}

static void parse_precision(const char *format, int *i, int params[],
                            va_list args) {
  if (format[*i] != '.') return;
  (*i)++;
  params[PARAM_PRECISION] = true;
  if (format[*i] == '*')
    params[PARAM_PRECISION] = true,
    params[PARAM_PRECISION_ASTERISK_VALUE] = abs(va_arg(args, int)), (*i)++;
  else if (isdigit(format[*i]))
    params[PARAM_PRECISION] = true,
    params[PARAM_PRECISION_ASTERISK_VALUE] = parse_number(format, i);
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

static void parse_specifier(const char *format, int *i, int params[]) {
  char spec = params[PARAM_SPECIFIER] = format[*i];
  if (isupper(spec)) params[PARAM_UPPERCASE] = true;
  spec = tolower(spec);

  if (spec == 'd' || spec == 'i')
    parse_integer_specifier(params);
  else if (spec == 'u' || spec == 'o' || spec == 'x')
    parse_unsigned_specifier(params, spec);
  else if (spec == 'f' || spec == 'e' || spec == 'g')
    parse_float_specifier(params, spec);
  else if (spec == 'c')
    params[TYPE] =
        (params[PARAM_MODIFIER] == LENGTH_L) ? TYPE_WCHAR : TYPE_CHAR;
  else if (spec == 's')
    params[TYPE] =
        (params[PARAM_MODIFIER] == LENGTH_L) ? TYPE_WSTRING : TYPE_STRING;
  else if (spec == 'p')
    params[TYPE] = TYPE_POINTER, params[PARAM_BASE] = BaseHexadecimal;
  else if (spec == '%')
    params[TYPE] = TYPE_PERCENT;
  else if (spec == 'n')
    params[TYPE] = TYPE_PTR;

  (*i)++;
}

static void parse_integer_specifier(int params[]) {
  if (params[PARAM_MODIFIER] == LENGTH_LL)
    params[TYPE] = TYPE_LONGLONG;
  else if (params[PARAM_MODIFIER] == LENGTH_L)
    params[TYPE] = TYPE_LONG;
  else
    params[TYPE] = TYPE_INT;
}

static void parse_unsigned_specifier(int params[], char specifier) {
  if (params[PARAM_MODIFIER] == LENGTH_LL)
    params[TYPE] = TYPE_ULONGLONG;
  else if (params[PARAM_MODIFIER] == LENGTH_L)
    params[TYPE] = TYPE_ULONG;
  else
    params[TYPE] = TYPE_UINT;

  if (specifier == 'o') {
    params[PARAM_BASE] = BaseOctal;
  } else if (specifier == 'x') {
    params[PARAM_BASE] = BaseHexadecimal;
  }
}

static void parse_float_specifier(int params[], char specifier) {
  if (params[PARAM_MODIFIER] == LENGTH_CAP_L)
    params[TYPE] = TYPE_LONGDOUBLE;
  else
    params[TYPE] = TYPE_FLOAT;

  if (specifier == 'e') {
    params[PARAM_SPEC_CHAR] = CHAR_E;
  } else if (specifier == 'g') {
    params[PARAM_SPEC_CHAR] = CHAR_G;
  } else if (specifier == 'f') {
    params[PARAM_SPEC_CHAR] = CHAR_F;
  }
}

static int convert_format(char *str, int *str_idx, int params[], va_list args) {
  switch (params[TYPE]) {
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
      if (handle_wchar(str, str_idx, params, args) == -1) return -1;
      break;
    case TYPE_STRING:
      handle_string(str, str_idx, params, args);
      break;
    case TYPE_WSTRING:
      if (handle_wstring(str, str_idx, params, args) == -1) return -1;
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
  switch (params[TYPE]) {
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
  switch (params[TYPE]) {
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

  convert_uint_to_str(str, idx, val, params);
}

static void handle_float(char *str, int *idx, int params[], va_list args) {
  long double val = (params[TYPE] == TYPE_FLOAT)
                        ? (long double)va_arg(args, double)
                        : va_arg(args, long double);

  if (!convert_special_float(str, idx, val, params)) {
    convert_float_to_str(str, idx, val, params);
  }
}

static void handle_char(char *str, int *idx, int params[], va_list args) {
  char c = (char)va_arg(args, int);
  char buffer[2] = {c, '\0'};
  convert_string_buffer_to_str(str, idx, buffer, params);
}

static void handle_string(char *str, int *idx, int params[], va_list args) {
  char *s = va_arg(args, char *);
  char *null = "(null)\0";
  if (params[PARAM_PRECISION] < 6 &&
      params[PARAM_PRECISION_ASTERISK_VALUE] != 0)
    null = "\0";
  convert_string_buffer_to_str(str, idx, s ? s : null, params);
}

static int handle_wchar(char *str, int *idx, int params[], va_list args) {
  wchar_t wcval = va_arg(args, wchar_t);
  char utf8_buffer[MaxUtf8Bytes + 1] = {0};
  int utf8_len = wchar_to_utf8(utf8_buffer, wcval);

  if (utf8_len == -1) {
    return -1;
  }

  if (utf8_len == 0) {
    return 0;
  }

  int width_value = 0;
  if (params[PARAM_WIDTH] != -1) {
    width_value = params[PARAM_WIDTH_ASTERISK_VALUE];
  }
  bool left_align = (params[FLAG_MINUS]);
  if (width_value < 0) {
    left_align = true;
    width_value = -width_value;
  }

  int padding = width_value - utf8_len;
  if (padding < 0) padding = 0;

  if (!left_align) {
    char pad_char = ' ';
    for (int i = 0; i < padding; i++) {
      str[(*idx)++] = pad_char;
    }
  }

  for (int i = 0; i < utf8_len; i++) {
    str[(*idx)++] = utf8_buffer[i];
  }

  if (left_align) {
    for (int i = 0; i < padding; i++) {
      str[(*idx)++] = ' ';
    }
  }
}

static int handle_wstring(char *str, int *idx, int params[], va_list args) {
  wchar_t *wsval = va_arg(args, wchar_t *);
  int precision = (params[PARAM_PRECISION] != -1)
                      ? params[PARAM_PRECISION_ASTERISK_VALUE]
                      : -1;
  int width_value = 0;
  if (params[PARAM_WIDTH] != -1) {
    width_value = params[PARAM_WIDTH_ASTERISK_VALUE];
  }
  bool left_align = (params[FLAG_MINUS]);
  if (width_value < 0) {
    left_align = true;
    width_value = -width_value;
  }

  if (wsval == NULL) {
    const char *null_str = (params[PARAM_PRECISION] != -1) ? "" : "(null)";
    int null_len = strlen(null_str);
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    if (precision >= 0 && precision < null_len) {
      null_len = precision;
    }
    int padding = width_value - null_len;
    if (padding < 0) padding = 0;

    if (!left_align) {
      for (int i = 0; i < padding; i++) {
        str[(*idx)++] = ' ';
      }
    }
    for (int i = 0; i < null_len; i++) {
      str[(*idx)++] = null_str[i];
    }
    if (left_align) {
      for (int i = 0; i < padding; i++) {
        str[(*idx)++] = ' ';
      }
    }
    return 0;
  }

  int total_bytes = 0;
  const wchar_t *p = wsval;
  while (*p) {
    char utf8_buf[MaxUtf8Bytes];
    int len = wchar_to_utf8(utf8_buf, *p);

    if (len == -1) {
      return -1;
    }

    if (len == 0) {
      p++;
      continue;
    }

    if (precision != -1 && total_bytes + len > precision) {
      break;
    }

    total_bytes += len;
    p++;
  }

  int padding = width_value - total_bytes;
  if (padding < 0) padding = 0;

  if (!left_align) {
    char pad_char = ' ';
    for (int i = 0; i < padding; i++) {
      str[(*idx)++] = pad_char;
    }
  }

  int bytes_written = 0;
  p = wsval;
  while (*p) {
    char utf8_buf[MaxUtf8Bytes];
    int len = wchar_to_utf8(utf8_buf, *p);
    if (len == 0) {
      p++;
      continue;
    }

    if (precision != -1 && bytes_written + len > precision) {
      break;
    }

    for (int j = 0; j < len; j++) {
      str[(*idx)++] = utf8_buf[j];
    }
    bytes_written += len;
    p++;
  }

  if (left_align) {
    for (int i = 0; i < padding; i++) {
      str[(*idx)++] = ' ';
    }
  }

  return 0;
}

static void handle_pointer(char *str, int *idx, int params[], va_list args) {
  void *ptr = va_arg(args, void *);
  if (ptr == NULL) {
    params[FLAG_HASH] = false;
    params[FLAG_ZERO] = false;
    params[PARAM_PRECISION] = -1;
    params[PARAM_PRECISION_ASTERISK_VALUE] = 0;
    convert_buffer_to_str("(nil)", 0, strlen("(nil)"), str, idx, params);
  } else {
    char buffer[MaxBufferSize];
    int num_len = 0;
    buffer[num_len++] = '0';
    buffer[num_len++] = 'x';

    char sign_char = 0;
    add_sign(&sign_char, ptr < 0, params);
    unsigned long long positive = (unsigned long long)ptr;

    convert_uint_to_buffer(buffer, &num_len, positive, params);
    convert_buffer_to_str(buffer, sign_char, num_len, str, idx, params);
  }
}

static void handle_count(char *str, int *idx, int params[], va_list args) {
  int *ptr = va_arg(args, int *);
  *ptr = *idx;
}

static void handle_percent(char *str, int *idx) {
  convert_char_to_buffer(str, idx, '%');
}

////////////////////////////////////////////////////////////
//             Функции конвертации данных                 //
////////////////////////////////////////////////////////////

static int add_sign(char *buf, bool negative, int params[]) {
  if (negative) {
    *buf = '-';
  } else {
    if (params[FLAG_PLUS]) {
      *buf = '+';
    } else if (params[FLAG_SPACE]) {
      *buf = ' ';
    } else
      return 0;
  }
  return 1;
}

static void convert_uint_to_buffer(char *buf, int *idx_buf,
                                   unsigned long long value, int params[]) {
  char buffer[MaxBufferSize];
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

  int start_index = *idx_buf;
  for (int j = 0; j < i; j++) {
    buf[start_index + j] = buffer[i - j - 1];
  }
  *idx_buf += i;
  buf[*idx_buf] = '\0';
}

static void convert_num_len_pad_char_to_str(char *str, int *idx, int num_len,
                                            char pad_char) {
  for (int i = 0; i < num_len; i++) {
    convert_char_to_buffer(str, idx, pad_char);
  }
}

static void convert_int_to_str(char *str, int *idx, long long value,
                               int params[]) {
  char buffer[MaxBufferSize] = {0};
  int num_len = 0;
  char sign_char = 0;

  add_sign(&sign_char, value < 0, params);

  unsigned long long positive;
  if (value < 0) {
    positive = (value == LLONG_MIN) ? (unsigned long long)LLONG_MAX + 1
                                    : (unsigned long long)(-value);
  } else {
    positive = value;
  }

  if (positive == 0 && params[PARAM_PRECISION_ASTERISK_VALUE] == 0 &&
      params[PARAM_PRECISION] != -1) {
  } else {
    convert_uint_to_buffer(buffer, &num_len, positive, params);
  }
  convert_buffer_to_str(buffer, sign_char, num_len, str, idx, params);
}

static void convert_uint_to_str(char *str, int *idx, unsigned long long value,
                                int params[]) {
  char buffer[MaxBufferSize] = {0};
  int num_len = 0;

  if (value == 0 && params[PARAM_PRECISION_ASTERISK_VALUE] == 0 &&
      params[PARAM_PRECISION] != -1) {
    if (params[FLAG_HASH] && params[PARAM_SPECIFIER] == 'o')
      convert_char_to_buffer(buffer, &num_len, '0');
  } else {
    convert_uint_to_buffer(buffer, &num_len, value, params);
  }

  if (value == 0) params[FLAG_HASH] = false;

  convert_buffer_to_str(buffer, LENGTH_NULL, num_len, str, idx, params);
}

static void convert_buffer_to_str(char *buffer, char sign_char, int num_len,
                                  char *str, int *idx, int params[]) {
  int width = params[PARAM_WIDTH_ASTERISK_VALUE];
  bool left_align = params[FLAG_MINUS];
  width = abs(width);

  int precision = params[PARAM_PRECISION_ASTERISK_VALUE];
  precision = (precision > num_len) ? precision - num_len : 0;

  int sign_len = (sign_char != 0) ? 1 : 0;

  int hash = 0;
  if (params[FLAG_HASH]) {
    if (params[PARAM_SPECIFIER] == 'o') {
      if (precision == 0)
        hash = 1;  // Префикс "0"
      else
        params[FLAG_ZERO] = true;
    } else if (params[PARAM_SPECIFIER] == 'x' ||
               params[PARAM_SPECIFIER] == 'X') {
      hash = 2;  // Префикс "0x" или "0X"
    }
  }

  width = width - (sign_len + num_len + precision + hash);

  if (!left_align) {
    if (params[FLAG_ZERO] && precision == 0 && params[PARAM_PRECISION] == -1) {
      if (hash) convert_hash_to_buffer(params, &hash, str, idx);
      if (sign_len) convert_char_to_buffer(str, idx, sign_char);
      convert_num_len_pad_char_to_str(str, idx, width, '0');
      sign_len = 0;
    } else {
      convert_num_len_pad_char_to_str(str, idx, width, ' ');
    }
  }

  if (hash) convert_hash_to_buffer(params, &hash, str, idx);
  if (sign_len) convert_char_to_buffer(str, idx, sign_char);
  convert_num_len_pad_char_to_str(str, idx, precision, '0');

  convert_string_to_buffer(str, idx, buffer);

  if (left_align) {
    convert_num_len_pad_char_to_str(str, idx, width, ' ');
  }
}

static void convert_hash_to_buffer(int params[], int *hash, char *str,
                                   int *idx) {
  if (params[PARAM_SPECIFIER] == 'o') {
    convert_char_to_buffer(str, idx, '0');
  } else {
    convert_string_to_buffer(str, idx, params[PARAM_UPPERCASE] ? "0X" : "0x");
  }
  *hash = 0;
}

static void convert_string_buffer_to_str(char *str, int *idx,
                                         const char *buffer, int params[]) {
  int width = params[PARAM_WIDTH_ASTERISK_VALUE];
  int precision = params[PARAM_PRECISION_ASTERISK_VALUE];

  bool left_align = params[FLAG_MINUS];
  if (width < 0) width = -width;

  int output_len;
  if (params[TYPE] == TYPE_CHAR) {
    output_len = 1;  // Для символа всегда длина 1
  } else {
    // Для строки: длина либо до \0, либо ограничена точностью
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    output_len = strlen(buffer);
    if (params[PARAM_PRECISION] != -1 && precision < output_len)
      output_len = precision;
  }

  int padding = width - output_len;
  if (padding < 0) padding = 0;

  if (!left_align) {
    convert_num_len_pad_char_to_str(str, idx, padding, ' ');
  }

  if (params[TYPE] == TYPE_CHAR) {
    convert_char_to_buffer(str, idx, buffer[0]);
  } else {
    for (int i = 0; i < output_len; i++) {
      convert_char_to_buffer(str, idx, buffer[i]);
    }
  }

  if (left_align) {
    convert_num_len_pad_char_to_str(str, idx, padding, ' ');
  }
}

static void convert_float_buffer_to_str(char *buffer, char sign_char,
                                        int num_len, char *str, int *idx,
                                        int params[]) {
  int width = params[PARAM_WIDTH_ASTERISK_VALUE];
  int precision = params[PARAM_PRECISION_ASTERISK_VALUE];
  int sign_len = (sign_char != 0) ? 1 : 0;

  bool left_align = params[FLAG_MINUS];
  if (width < 0) width = -width;

  int padding = width - (num_len + sign_len);
  if (padding < 0) padding = 0;

  if (!left_align) {
    if (params[FLAG_ZERO]) {
      if (sign_len) convert_char_to_buffer(str, idx, sign_char);
      convert_num_len_pad_char_to_str(str, idx, padding, '0');
      sign_len = 0;
    } else
      convert_num_len_pad_char_to_str(str, idx, padding, ' ');
  }

  if (sign_len) convert_char_to_buffer(str, idx, sign_char);
  convert_string_to_buffer(str, idx, buffer);

  if (left_align) {
    convert_num_len_pad_char_to_str(str, idx, padding, ' ');
  }
}

static void convert_char_to_buffer(char *buffer, int *idx_buffer, char c) {
  buffer[(*idx_buffer)++] = c;
}

static void convert_string_to_buffer(char *buffer, int *idx_buffer,
                                     const char *s) {
  if (s == NULL) return;

  while (*s) {
    convert_char_to_buffer(buffer, idx_buffer, *s++);
  }
}

static int wchar_to_utf8(char *dest, wchar_t wc) {
  uint32_t code = (uint32_t)wc;
  if (code > UnicodeMax || (code >= SurrogateStart && code <= SurrogateEnd) ||
      wc < 0) {
    return -1;
  }

  if ((wc >= 0xD800 && wc <= 0xDFFF) || wc > 0x10FFFF) {
    return 0;
  }

  if (wc < 0x80) {
    dest[0] = (char)wc;
    return 1;
  } else if (wc < 0x800) {
    dest[0] = 0xC0 | (wc >> 6);
    dest[1] = 0x80 | (wc & 0x3F);
    return 2;
  } else if (wc < 0x10000) {
    dest[0] = 0xE0 | (wc >> 12);
    dest[1] = 0x80 | ((wc >> 6) & 0x3F);
    dest[2] = 0x80 | (wc & 0x3F);
    return 3;
  } else {
    dest[0] = 0xF0 | (wc >> 18);
    dest[1] = 0x80 | ((wc >> 12) & 0x3F);
    dest[2] = 0x80 | ((wc >> 6) & 0x3F);
    dest[3] = 0x80 | (wc & 0x3F);
    return 4;
  }
}

////////////////////////////////////////////////////////////
//          Функции работы с числами с плавающей точкой   //
////////////////////////////////////////////////////////////

static bool convert_special_float(char *str, int *idx, long double value,
                                  int params[]) {
  char sign_char = 0;
  int num_len = strlen("nan");
  bool fl = false;

  add_sign(&sign_char, value < 0, params);

  if (isnanl(value)) {
    params[FLAG_HASH] = false;
    params[FLAG_ZERO] = false;
    params[PARAM_PRECISION] = -1;
    params[PARAM_PRECISION_ASTERISK_VALUE] = 0;
    convert_buffer_to_str(params[PARAM_UPPERCASE] ? "NAN" : "nan", sign_char,
                          strlen("nan"), str, idx, params);
    fl = true;
  } else if (isinfl(value)) {
    params[FLAG_HASH] = false;
    params[FLAG_ZERO] = false;
    params[PARAM_PRECISION] = -1;
    params[PARAM_PRECISION_ASTERISK_VALUE] = 0;
    convert_buffer_to_str(params[PARAM_UPPERCASE] ? "INF" : "inf", sign_char,
                          strlen("inf"), str, idx, params);
    fl = true;
  }

  return fl;
}

static void convert_float_to_str(char *str, int *idx, long double dval,
                                 int params[]) {
  char buffer[MaxBufferSize];
  int idx_buffer = 0;

  int precision = (params[PARAM_PRECISION] >= 0)
                      ? params[PARAM_PRECISION_ASTERISK_VALUE]
                      : DefaultPrecision;

  char ch = 0;
  add_sign(&ch, signbit(dval), params);
  dval = fabsl(dval);

  int format_G = CHAR_G;
  if (params[PARAM_SPEC_CHAR] == CHAR_G) {
    if (dval == 0.0L) {
      if (params[FLAG_HASH]) precision -= 1;
      convert_char_to_buffer(buffer, &idx_buffer, '0');
      format_fractional_partG(buffer, &idx_buffer, 0.0L, precision, params);
    } else
      format_G = format_g(dval, &precision, params);
  }

  if (params[PARAM_SPEC_CHAR] == CHAR_F || format_G == CHAR_F) {
    format_f(buffer, &idx_buffer, dval, precision, params);
  } else if (params[PARAM_SPEC_CHAR] == CHAR_E || format_G == CHAR_E) {
    format_e(buffer, &idx_buffer, dval, precision, params);
  }

  if (idx_buffer < MaxBufferSize) {
    buffer[idx_buffer] = '\0';
  } else {
    buffer[MaxBufferSize - 1] = '\0';
  }

  convert_float_buffer_to_str(buffer, ch, idx_buffer, str, idx, params);
}

static int format_g(long double dval, int *precision, int params[]) {
  int exp =
      (dval == 0.0L) ? 0 : (int)floorl(log10l(dval));  // Расчёт экспоненты
  if (exp >= -4 && exp < *precision) {
    *precision = *precision - (exp + 1);
    if (*precision < 0) *precision = 0;
    return CHAR_F;
  } else {
    *precision = (*precision > 0) ? *precision - 1 : 0;
    return CHAR_E;
  }
}

static void format_f(char *buf, int *idx_buf, long double value, int precision,
                     int params[]) {
  long double rounding = 0.5L * powl(10.0L, -precision);
  value += rounding;

  long double int_part;
  long double frac_part = modfl(value, &int_part);
  convert_uint_to_buffer(buf, idx_buf, (long long)int_part, params);

  if (params[PARAM_SPEC_CHAR] == CHAR_G)
    format_fractional_partG(buf, idx_buf, frac_part, precision, params);
  else
    format_fractional_part(buf, idx_buf, frac_part, precision, params);
}

static void format_e(char *buf, int *idx_buf, long double value, int precision,
                     int params[]) {
  int exp = 0;
  if (value != 0.0L) exp = (int)floorl(log10l(fabsl(value)));
  value *= powl(10.0L, -exp);

  long double rounding = 0.5L * powl(10.0L, -precision);
  value += rounding;

  if (fabsl(value) >= 10.0L) {
    value /= 10.0L;
    exp++;
  }

  long double int_part;
  long double frac_part = modfl(value, &int_part);
  convert_uint_to_buffer(buf, idx_buf, (long long)int_part, params);

  if (params[PARAM_SPEC_CHAR] == CHAR_G)
    format_fractional_partG(buf, idx_buf, frac_part, precision, params);
  else {
    format_fractional_part(buf, idx_buf, frac_part, precision, params);
  }

  format_exponent(buf, idx_buf, exp, params);
}

static void format_fractional_part(char *buf, int *idx_buf, long double frac,
                                   int precision, int params[]) {
  if (precision > 0) {
    convert_char_to_buffer(buf, idx_buf, '.');

    for (int i = 0; i < precision; i++) {
      frac *= 10.0L;
      int digit = (int)frac;
      convert_char_to_buffer(buf, idx_buf, '0' + digit);
      frac -= digit;
    }
  } else if (params[FLAG_HASH])
    convert_char_to_buffer(buf, idx_buf, '.');
}

static void format_fractional_partG(char *buf, int *idx_buf, long double frac,
                                    int precision, int params[]) {
  if (precision > 0) {
    char temp[precision + 1];
    int temp_idx = 0;

    for (int i = 0; i < precision; i++) {
      frac *= 10.0L;
      int digit = (int)frac;
      temp[temp_idx++] = '0' + digit;
      frac -= digit;
    }
    temp[temp_idx] = '\0';

    // Удаляем хвостовые нули, если G (только если не установлен флаг #)
    if (!params[FLAG_HASH]) {
      while (temp_idx > 0 && temp[temp_idx - 1] == '0') {
        temp_idx--;
      }
    }

    if (temp_idx > 0 || params[FLAG_HASH]) buf[(*idx_buf)++] = '.';

    // Копируем цифры в основной буфер
    for (int i = 0; i < temp_idx; i++) {
      buf[(*idx_buf)++] = temp[i];
    }
  } else if (params[FLAG_HASH])
    convert_char_to_buffer(buf, idx_buf, '.');
}

static void format_exponent(char *buf, int *idx_buf, int exp, int params[]) {
  buf[(*idx_buf)++] = params[PARAM_UPPERCASE] ? 'E' : 'e';
  buf[(*idx_buf)++] = exp >= 0 ? '+' : '-';

  exp = abs(exp);
  if (exp < 10) {
    buf[(*idx_buf)++] = '0';
  }
  convert_uint_to_buffer(buf, idx_buf, (unsigned long long)exp, params);
}