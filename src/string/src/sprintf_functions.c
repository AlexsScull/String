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
static int handle_wchar(char *str, int *idx, int params[], va_list args);
static void handle_string(char *str, int *idx, int params[], va_list args);
static int handle_wstring(char *str, int *idx, int params[], va_list args);
static void handle_pointer(char *str, int *idx, int params[], va_list args);
static void handle_count(char *str, int *idx, int params[], va_list args);
static void handle_percent(char *str, int *idx);

static void add_sign(char *buf, int *idx_buf, bool negative, int params[]);
static void convert_uint_to_buffer(char *buf, int *idx_buf,
                                   unsigned long long value, int params[]);
static void convert_buffer_to_str(char *buffer, int num_len, char *str,
                                  int *idx, int params[]);
static void convert_string_buffer_to_str(char *str, int *idx,
                                         const char *buffer, int params[]);
static void convert_int_to_str(char *str, int *idx, long long value,
                               int params[]);
static void convert_uint_to_str(char *str, int *idx, unsigned long long value,
                                int params[]);
static void convert_char_to_buffer(char *str, int *idx, char c);
static void convert_string_to_buffer(char *str, int *idx, const char *s);
static void convert_pointer_prefix(char *str, int *idx);
static bool convert_wchar_to_str(char *str, int *idx, wchar_t wc);
static bool convert_wstring_to_str(char *str, int *idx, const wchar_t *ws);
static int utf8_char_length(wchar_t wc);
static int utf8_string_length(const wchar_t *ws, int char_limit);

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
static void convert_num_len_pad_char_to_str(char *str, int *idx, int num_len,
                                            char pad_char);
static int wchar_to_utf8(char *dest, wchar_t wc);
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
                                 [PARAM_UPPERCASE] = false,
                                 [PARAM_BASE] = BaseDecimal,
                                 [PARAM_SPEC_CHAR] = -1};

      parse_flag(format, &i, params);
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
    num = num * BaseDecimal + (format[*i] - '0');
    (*i)++;
  }
  return num;
}

static void parse_flag(const char *format, int *i, int params[]) {
  bool b = true;
  while (b) {
    if (format[*i] == '-' && !params[FLAG_MINUS]) {
      params[FLAG_MINUS] = true;
      (*i)++;
    } else if (format[*i] == '+' && !params[FLAG_PLUS]) {
      params[FLAG_PLUS] = true;
      (*i)++;
    } else if (format[*i] == ' ' && !params[FLAG_SPACE]) {
      params[FLAG_SPACE] = true;
      (*i)++;
    } else if (format[*i] == '#' && !params[FLAG_HASH]) {
      params[FLAG_HASH] = true;
      (*i)++;
    } else if (format[*i] == '0' && !params[FLAG_ZERO]) {
      params[FLAG_ZERO] = true;
      (*i)++;
    } else
      b = false;
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
      params[FLAG_MINUS] = false;
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
      params[PARAM_BASE] = BaseHexadecimal;
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
    params[PARAM_BASE] = BaseOctal;
  } else if (specifier == 'x' || specifier == 'X') {
    params[PARAM_BASE] = BaseHexadecimal;
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
      if (handle_wchar(str, str_idx, params, args) == -1)
      return -1;
      break;
    case TYPE_STRING:
      handle_string(str, str_idx, params, args);
      break;
    case TYPE_WSTRING:
      if (handle_wstring(str, str_idx, params, args) == -1)
      return -1;
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
  if (val == 0 && params[PARAM_PRECISION_ASTERISK_VALUE] == 0 &&
      params[PARAM_PRECISION] != -1) {
  } else {
    convert_int_to_str(str, idx, val, params);
  }
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

  if (val == 0 && params[PARAM_PRECISION_ASTERISK_VALUE] == 0 &&
      params[PARAM_PRECISION] != -1) {
  } else {
    convert_uint_to_str(str, idx, val, params);
  }
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
  char buffer[2] = {c, '\0'};
  convert_string_buffer_to_str(str, idx, buffer, params);
}

static void handle_string(char *str, int *idx, int params[], va_list args) {
  char *s = va_arg(args, char *);
  if (!s && params[PARAM_PRECISION] != -1) {
  } else
    convert_string_buffer_to_str(str, idx, s ? s : "(null)", params);
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
        char pad_char =  ' ';
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
    int precision = (params[PARAM_PRECISION] != -1) ? params[PARAM_PRECISION_ASTERISK_VALUE] : -1;
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
        const char *null_str = (params[PARAM_PRECISION] != -1)? "" : "(null)";
        int null_len = s21_strlen(null_str);
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
        return;
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
    convert_string_to_buffer(str, idx, "(nil)");
  } else {
    char buffer[MaxBufferSize];
    int num_len = 0;
    buffer[num_len++] = '0';
    buffer[num_len++] = 'x';

    unsigned long long positive = (unsigned long long)ptr;

    convert_uint_to_buffer(buffer, &num_len, positive, params);
    convert_buffer_to_str(buffer, num_len, str, idx, params);
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

static void add_sign(char *buf, int *idx_buf, bool negative, int params[]) {
  if (negative) {
    buf[(*idx_buf)++] = '-';
  } else {
    if (params[FLAG_PLUS]) {
      buf[(*idx_buf)++] = '+';
    } else if (params[FLAG_SPACE]) {
      buf[(*idx_buf)++] = ' ';
    }
  }
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
  char buffer[MaxBufferSize];
  int num_len = 0;  

  add_sign(buffer, &num_len, value < 0, params);

  unsigned long long positive;
  if (value < 0) {
    positive = (value == LLONG_MIN) ? (unsigned long long)LLONG_MAX + 1
                                    : (unsigned long long)(-value);
  } else {
    positive = value;
  }

  convert_uint_to_buffer(buffer, &num_len, positive, params);
  convert_buffer_to_str(buffer, num_len, str, idx, params);
}

static void convert_uint_to_str(char *str, int *idx, unsigned long long value,
                                int params[]) {
  char buffer[MaxBufferSize];
  int num_len = 0; 

  convert_uint_to_buffer(buffer, &num_len, value, params);
  convert_buffer_to_str(buffer, num_len, str, idx, params);
}

static void convert_string_buffer_to_str(char *str, int *idx,
                                         const char *buffer, int params[]) {
  int width = params[PARAM_WIDTH_ASTERISK_VALUE];
  int precision = params[PARAM_PRECISION_ASTERISK_VALUE];

  bool left_align = (width < 0);
  if (width < 0) width = -width;

  int output_len;
  if (params[PARAM_SPECIFIER] == TYPE_CHAR) {
    output_len = 1;  // Для символа всегда длина 1
  } else {
    // Для строки: длина либо до \0, либо ограничена точностью
    output_len = s21_strlen(buffer);
    if (params[PARAM_PRECISION] != -1 && precision < output_len) {
      output_len = precision;
    }
  }

  int padding = width - output_len;
  if (padding < 0) padding = 0;

  if (!left_align) {
    convert_num_len_pad_char_to_str(str, idx, padding, ' ');
  }

  if (params[PARAM_SPECIFIER] == TYPE_CHAR) {
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

static void convert_buffer_to_str(char *buffer, int num_len, char *str,
                                  int *idx, int params[]) {
  int width = params[PARAM_WIDTH_ASTERISK_VALUE];
  int precision = params[PARAM_PRECISION_ASTERISK_VALUE];

  bool left_align = (width < 0);
  if (width < 0) width = -width;

  if (params[FLAG_MINUS]) left_align = true;
  int required_precision = (precision > num_len) ? precision - num_len : 0;
  int total_len = num_len + required_precision;

  int padding = width - total_len;
  if (padding < 0) padding = 0;

  if (!left_align) {
    if (params[FLAG_ZERO])
      convert_num_len_pad_char_to_str(str, idx, padding, '0');
    else
      convert_num_len_pad_char_to_str(str, idx, padding, ' ');
  }

  convert_num_len_pad_char_to_str(str, idx, required_precision, '0');

  convert_string_to_buffer(str, idx, buffer);

  if (left_align) {
    convert_num_len_pad_char_to_str(str, idx, padding, ' ');
  }
}

static void convert_float_buffer_to_str(char *buffer, int num_len, char *str,
                                        int *idx, int params[]) {
  int width = params[PARAM_WIDTH_ASTERISK_VALUE];
  int precision = params[PARAM_PRECISION_ASTERISK_VALUE];

  bool left_align = (width < 0);
  if (width < 0) width = -width;

  int padding = width - num_len;
  if (padding < 0) padding = 0;

  if (!left_align) {
    if (params[FLAG_ZERO])
      convert_num_len_pad_char_to_str(str, idx, padding, '0');
    else
      convert_num_len_pad_char_to_str(str, idx, padding, ' ');
  }

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
  if (s == NULL) {
    convert_string_to_buffer(buffer, idx_buffer, "(null)");
  } else {
    while (*s) {
      buffer[(*idx_buffer)++] = *s++;
    }
  }
}

static int wchar_to_utf8(char *dest, wchar_t wc) {
  uint32_t code = (uint32_t)wc;
  if (code > UnicodeMax ||
      (code >= SurrogateStart && code <= SurrogateEnd) || wc < 0) {
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
  if (isnanl(value)) {
    convert_string_to_buffer(str, idx, params[PARAM_UPPERCASE] ? "NAN" : "nan");
    return true;
  } else if (isinfl(value)) {
    if (signbit(value)) {
      convert_string_to_buffer(str, idx,
                               params[PARAM_UPPERCASE] ? "-INF" : "-inf");
    } else {
      convert_string_to_buffer(str, idx,
                               params[PARAM_UPPERCASE] ? "INF" : "inf");
    }
    return true;
  }
  return false;
}

static void convert_float_to_str(char *str, int *idx, long double dval,
                                 int params[]) {
  char buffer[MaxBufferSize];
  int idx_buffer = 0;

  int precision = (params[PARAM_PRECISION] >= 0)
                      ? params[PARAM_PRECISION_ASTERISK_VALUE]
                      : DefaultPrecision;

  add_sign(buffer, &idx_buffer, signbit(dval), params);
  dval = fabsl(dval);

  if (params[PARAM_SPEC_CHAR] == CHAR_G) {
    format_g(dval, &precision, params);
    if (dval == 0.0L) {
      convert_char_to_buffer(buffer, &idx_buffer, '0');
    }
  }

  if (params[PARAM_SPEC_CHAR] == CHAR_F) {
    format_f(buffer, &idx_buffer, dval, precision, params);
  } else if (params[PARAM_SPEC_CHAR] == CHAR_E) {
    format_e(buffer, &idx_buffer, dval, precision, params);
  }

  if (idx_buffer < MaxBufferSize) {
    buffer[idx_buffer] = '\0';
  } else {
    buffer[MaxBufferSize - 1] = '\0';
  }

  convert_float_buffer_to_str(buffer, idx_buffer, str, idx, params);
}

static void format_g(long double dval, int *precision, int params[]) {
  if (dval == 0.0L) return 0;

  int exp =
      (dval == 0.0L) ? 0 : (int)floorl(log10l(dval));  // Расчёт экспоненты
  if (exp >= -4 && exp < *precision) {
    *precision = *precision - (exp + 1);
    if (*precision < 0 || exp == 0) *precision = 0;
    params[PARAM_SPEC_CHAR] = CHAR_F;
  } else {
    *precision = (*precision > 0) ? *precision - 1 : 0;
    params[PARAM_SPEC_CHAR] = CHAR_E;
  }
}

static void format_f(char *buf, int *idx_buf, long double value, int precision,
                     int params[]) {
  long double rounding = 0.5L * powl(10.0L, -precision);
  format_float_value(buf, idx_buf, value + rounding, precision, params);
}

static void format_e(char *buf, int *idx_buf, long double value, int precision,
                     int params[]) {
  int exp = 0;
  if (value != 0.0L) {
    exp = (int)floorl(log10l(fabsl(value)));
    value *= powl(10.0L, -exp);
  }

  long double rounding = 0.5L * powl(10.0L, -precision);
  value += rounding;

  if (fabsl(value) >= 10.0L) {
    value /= 10.0L;
    exp++;
  }

  format_float_value(buf, idx_buf, value, precision, params);
  format_exponent(buf, idx_buf, exp, params);
}

static void format_fractional_part(char *buf, int *idx_buf, long double frac,
                                   int precision) {
  for (int i = 0; i < precision; i++) {
    frac *= 10.0L;
    int digit = (int)frac;
    buf[(*idx_buf)++] = '0' + digit;
    frac -= digit;
  }
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

static void format_float_value(char *buf, int *idx_buf, long double value,
                               int precision, int params[]) {
  long double int_part;
  long double frac_part = modfl(value, &int_part);

  convert_uint_to_buffer(buf, idx_buf, (long long)int_part, params);

  buf[(*idx_buf)++] = '.';

  if (precision > 0) format_fractional_part(buf, idx_buf, frac_part, precision);
}