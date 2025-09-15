#include <float.h>
#include <limits.h>
#include <stdint.h>
#include <stdlib.h>
#include <wchar.h>

// В начале sprintf_functions.c, после include
#ifndef LDBL_HAS_INFINITY
// Проверяем, поддерживает ли система infinity для long double
#if defined(INFINITY) || defined(HUGE_VALL) || \
    (defined(__STDC_IEC_559__) && __STDC_IEC_559__)
#define LDBL_HAS_INFINITY 1
#else
#define LDBL_HAS_INFINITY 0
#endif
#endif

// Макрос для проверки переполнения long double
#ifndef IS_LDBL_OVERFLOW
#if LDBL_HAS_INFINITY
// Система поддерживает infinity, поэтому переполнения не будет
#define IS_LDBL_OVERFLOW(x) (0)
#else
#define IS_LDBL_OVERFLOW(x) ((x) > LDBL_MAX || (x) < -LDBL_MAX)
#endif
#endif

#include "s21_string.h"
#include "string_parser.h"

#define DEFAULT_PRECISION 6
#define MAX_BUFFER_SIZE 65
#define TEMP_BUFFER_SIZE 4096
#define MAX_UTF8_BYTES 4
#define UNICODE_MAX 0x10FFFF
#define SURROGATE_START 0xD800
#define SURROGATE_END 0xDFFF
#define UTF8_1_BYTE_LIMIT 0x80
#define UTF8_2_BYTE_LIMIT 0x800
#define UTF8_3_BYTE_LIMIT 0x10000

#define STR_NULL "(null)"
#define PTR_NULL "(nil)"

#define NAN_LOWERCASE "nan"
#define INF_LOWERCASE "inf"
#define NAN_UPPERCASE "NAN"
#define INF_UPPERCASE "INF"

#ifndef isnanl
#define isnanl(x) (x != x)
#endif

#ifndef isinfl
#define isinfl(x) (x == 1.0L / 0.0L || x == -1.0L / 0.0L)
#endif

// ==================== ВСПОМОГАТЕЛЬНЫЕ ФУНКЦИИ ====================
static void s21_str_error(char *buffer, int *idx_buffer, FormatParams params);
static bool s21_process_format_conversion(char *str, int *str_idx,
                                          FormatParams params, va_list args);
static void s21_handle_integer(char *str, int *idx, FormatParams params,
                               va_list args);
static void s21_handle_unsigned(char *str, int *idx, FormatParams params,
                                va_list args);
static void s21_handle_float(char *str, int *idx, FormatParams params,
                             va_list args);
static void s21_handle_char(char *str, int *idx, FormatParams params,
                            va_list args);
static void s21_handle_string(char *str, int *idx, FormatParams params,
                              va_list args);
static int s21_handle_null_wchar(char *str, int *idx, FormatParams params);
static int s21_handle_wchar(char *str, int *idx, FormatParams params,
                            va_list args);
static int s21_handle_wstring(char *str, int *idx, FormatParams params,
                              va_list args);
static void s21_handle_pointer(char *str, int *idx, FormatParams params,
                               va_list args);
static void s21_handle_count(const char *str, const int *idx,
                             FormatParams params, va_list args);
static void s21_handle_percent(char *str, int *idx);
static void s21_format_integer_output(char *str, int *idx, long long value,
                                      FormatParams params);
static void s21_format_unsigned_output(char *str, int *idx,
                                       unsigned long long value,
                                       FormatParams params);
static void s21_format_char_output(char *str, int *idx, const char *c,
                                   FormatParams params);
static void s21_format_string_output(char *str, int *idx, const char *s,
                                     FormatParams params);
static void s21_format_pointer_output(char *str, int *idx, void *ptr,
                                      FormatParams params);
static void s21_format_null_output(char *str, int *idx, const char *null_str,
                                   FormatParams params);
static bool s21_format_special_float_output(char *str, int *idx,
                                            long double value,
                                            FormatParams params);
static void s21_format_float_output(char *str, int *idx, long double dval,
                                    FormatParams params);
static void s21_convert_char_to_buffer(char *buffer, int *idx_buffer, char c);
static void s21_convert_string_to_buffer(char *buffer, int *idx_buffer,
                                         const char *s);
static void s21_convert_uint_to_buffer(char *buf, int *idx_buf,
                                       unsigned long long value,
                                       FormatParams params);
static void s21_determine_sign(char *result, s21_size_t size, bool val,
                               FormatParams params);
static void s21_pref_sign(char *result, s21_size_t size, int val,
                          FormatParams params);
static int s21_wchar_to_utf8(char *dest, wchar_t wc);
static void s21_format_zero_g(char *buffer, int *buf_idx, int precision,
                              FormatParams params);
static void s21_format_g(char *buf, int *idx_buf, long double dval,
                         int precision, const FormatParams params);
static void s21_format_f(char *buf, int *idx_buf, long double value,
                         int precision, const FormatParams params);
static void s21_format_e(char *buf, int *idx_buf, long double value,
                         int precision, const FormatParams params);
static void s21_format_fractional_part(char *buf, int *idx_buf,
                                       long double frac, int precision,
                                       const FormatParams params);
static void s21_format_fractional_part_g(const char *buf, int *idx_buf);
static void s21_format_exponent(char *buf, int *idx_buf, int exp,
                                const FormatParams params);
static void s21_convert_num_len_pad_char_to_str(char *str, int *idx,
                                                int num_len, char pad_char);
static void s21_calculate_output_params(const char *buffer,
                                        const char *sign_char,
                                        const char *pref_char,
                                        FormatParams params, int *num_len,
                                        int *sign_len, int *pref_len,
                                        int *width, int *precision);
static void s21_write_output(const char *buffer, const char *sign_char,
                             const char *pref_char, char *str, int *idx,
                             const FormatParams params);

// ==================== ОСНОВНАЯ ФУНКЦИЯ ====================
int s21_sprintf(char *str, const char *format, ...) {
  if (!str || !format) return -1;

  va_list args;
  va_start(args, format);
  int idx = 0;
  int error = PARSE_SUCCESS;

  for (int i = 0; format[i] && !error;) {
    if (format[i] == '%') {
      if (format[++i] == '\0') error = PARSE_ERROR_INVALID_SPEC;

      FormatParams params = s21_init_format_params();
      if (!error) error = s21_parse_format_spr(format, &i, &params, &args);
      if (!error)
        error = s21_process_format_conversion(str, &idx, params, args);

      if (error == PARSE_ERROR_END_OF_FORMAT)
        s21_str_error(str, &idx, params), error = PARSE_SUCCESS;
    } else {
      str[idx++] = format[i++];
    }
  }

  str[idx] = '\0';
  va_end(args);
  return error ? -1 : idx;
}

/**
 * @brief Обрабатывает ошибки формата
 */
static void s21_str_error(char *buffer, int *idx_buffer, FormatParams params) {
  if (!buffer || !idx_buffer) return;

  s21_convert_char_to_buffer(buffer, idx_buffer, '%');
  if (params.flag_hash) s21_convert_char_to_buffer(buffer, idx_buffer, '#');
  if (params.flag_minus) s21_convert_char_to_buffer(buffer, idx_buffer, '-');
  if (params.flag_plus) s21_convert_char_to_buffer(buffer, idx_buffer, '+');
  s21_convert_char_to_buffer(
      buffer, idx_buffer,
      params.uppercase ? toupper(params.specifier) : params.specifier);
}

// ==================== ОБРАБОТКА ТИПОВ ДАННЫХ ====================
/**
 * @brief Выбирает обработчик для конкретного типа данных
 */
static bool s21_process_format_conversion(char *str, int *str_idx,
                                          FormatParams params, va_list args) {
  bool result = PARSE_SUCCESS;

  if (!str || !str_idx) return true;

  if (params.type <= TYPE_LONGLONG)
    s21_handle_integer(str, str_idx, params, args);
  else if (params.type <= TYPE_ULONGLONG)
    s21_handle_unsigned(str, str_idx, params, args);
  else if (params.type <= TYPE_LONGDOUBLE)
    s21_handle_float(str, str_idx, params, args);
  else if (params.type == TYPE_CHAR)
    s21_handle_char(str, str_idx, params, args);
  else if (params.type == TYPE_WCHAR)
    result = s21_handle_wchar(str, str_idx, params, args);
  else if (params.type == TYPE_STRING)
    s21_handle_string(str, str_idx, params, args);
  else if (params.type == TYPE_WSTRING)
    result = s21_handle_wstring(str, str_idx, params, args);
  else if (params.type == TYPE_POINTER)
    s21_handle_pointer(str, str_idx, params, args);
  else if (params.type == TYPE_PERCENT)
    s21_handle_percent(str, str_idx);
  else if (params.type <= TYPE_N_LONGLONG)
    s21_handle_count(str, str_idx, params, args);

  return result;
}

// ==================== ЦЕЛОЧИСЛЕННЫЕ ТИПЫ ====================
/**
 * @brief Обрабатывает целочисленные типы данных
 */
static void s21_handle_integer(char *str, int *idx, FormatParams params,
                               va_list args) {
  if (!str || !idx) return;

  long long val;
  if (params.type == TYPE_INT)
    val = va_arg(args, int);
  else if (params.type == TYPE_SHORT)
    val = (short)va_arg(args, int);
  else if (params.type == TYPE_SCHAR)
    val = (signed char)va_arg(args, int);
  else if (params.type == TYPE_LONG)
    val = va_arg(args, long);
  else
    val = va_arg(args, long long);

  s21_format_integer_output(str, idx, val, params);
}

/**
 * @brief Обрабатывает беззнаковые целочисленные типы
 */
static void s21_handle_unsigned(char *str, int *idx, FormatParams params,
                                va_list args) {
  if (!str || !idx) return;

  unsigned long long val;
  if (params.type == TYPE_UINT)
    val = va_arg(args, unsigned int);
  else if (params.type == TYPE_USHORT)
    val = (unsigned short)va_arg(args, unsigned int);
  else if (params.type == TYPE_UCHAR)
    val = (unsigned char)va_arg(args, unsigned int);
  else if (params.type == TYPE_ULONG)
    val = va_arg(args, unsigned long);
  else
    val = va_arg(args, unsigned long long);

  s21_format_unsigned_output(str, idx, val, params);
}

// ==================== ВЕЩЕСТВЕННЫЕ ТИПЫ ====================
/**
 * @brief Обрабатывает вещественные типы данных
 */
static void s21_handle_float(char *str, int *idx, FormatParams params,
                             va_list args) {
  if (!str || !idx) return;

  long double val;
  if (params.type == TYPE_FLOAT || params.type == TYPE_DOUBLE)
    val = va_arg(args, double);
  else
    val = va_arg(args, long double);

  if (!s21_format_special_float_output(str, idx, val, params)) {
    s21_format_float_output(str, idx, val, params);
  }
}

// ==================== СИМВОЛЫ И СТРОКИ ====================
/**
 * @brief Обрабатывает символьный тип данных
 */
static void s21_handle_char(char *str, int *idx, FormatParams params,
                            va_list args) {
  if (!str || !idx) return;

  char c = (char)va_arg(args, int);
  s21_format_char_output(str, idx, &c, params);
}

/**
 * @brief Обрабатывает строковый тип данных
 */
static void s21_handle_string(char *str, int *idx, FormatParams params,
                              va_list args) {
  if (!str || !idx) return;

  const char *s = va_arg(args, char *);
  if (s == S21_NULL) {
    s21_format_null_output(str, idx, STR_NULL, params);
  } else
    s21_format_string_output(str, idx, s, params);
}

/**
 * @brief Обрабатывает нулевой широкий символ
 */
static int s21_handle_null_wchar(char *str, int *idx, FormatParams params) {
  const int width = params.width_value;
  const int sign_len = 0;
  const int pref_len = 0;
  const int num_len = 1;
  const int precision = 0;
  int padding = width - (num_len + sign_len + pref_len + precision);
  if (padding < 0) padding = 0;

  if (!params.flag_minus) {
    const char pad_char = params.flag_zero ? '0' : ' ';
    for (int i = 0; i < padding; ++i) {
      s21_convert_char_to_buffer(str, idx, pad_char);
    }
  }

  s21_convert_char_to_buffer(str, idx, 0);

  if (params.flag_minus) {
    for (int i = 0; i < padding; ++i) {
      s21_convert_char_to_buffer(str, idx, ' ');
    }
  }
  return PARSE_SUCCESS;
}

/**
 * @brief Обрабатывает широкий символ
 */
static int s21_handle_wchar(char *str, int *idx, FormatParams params,
                            va_list args) {
  if (!str || !idx) return PARSE_ERROR_INVALID_SPEC;

  wchar_t wcval = va_arg(args, wchar_t);

  if (wcval == 0) {
    return s21_handle_null_wchar(str, idx, params);
  }

  char utf8_buffer[MAX_UTF8_BYTES + 1] = {0};
  int utf8_len = s21_wchar_to_utf8(utf8_buffer, wcval);

  if (utf8_len == -1) {
    return PARSE_ERROR_END_OF_FORMAT;
  }

  FormatParams local_params = params;
  local_params.precision_type = false;
  s21_format_string_output(str, idx, utf8_buffer, local_params);
  return PARSE_SUCCESS;
}

/**
 * @brief Обрабатывает широкую строку
 */
static int s21_handle_wstring(char *str, int *idx, FormatParams params,
                              va_list args) {
  if (!str || !idx) return PARSE_ERROR_INVALID_SPEC;

  const wchar_t *wsval = va_arg(args, wchar_t *);
  if (wsval == S21_NULL) {
    s21_format_null_output(str, idx, STR_NULL, params);
    return PARSE_SUCCESS;
  }

  int max_chars = INT_MAX;
  if (params.precision_type) {
    max_chars = params.precision_value;
    if (max_chars < 0) max_chars = INT_MAX;
  }

  int wlen = 0;
  while (wlen < max_chars && wsval[wlen] != 0) {
    ++wlen;
  }

  char temp_buffer[TEMP_BUFFER_SIZE] = {0};
  int bytes_written = 0;

  for (int i = 0; i < wlen && bytes_written < TEMP_BUFFER_SIZE - MAX_UTF8_BYTES;
       ++i) {
    char utf8_buf[MAX_UTF8_BYTES];
    int len = s21_wchar_to_utf8(utf8_buf, wsval[i]);
    if (len == -1) {
      continue;
    }
    if (bytes_written + len >= TEMP_BUFFER_SIZE) {
      break;
    }
    for (int j = 0; j < len; ++j) {
      temp_buffer[bytes_written++] = utf8_buf[j];
    }
  }
  temp_buffer[bytes_written] = '\0';

  FormatParams local_params = params;
  local_params.precision_type = false;
  s21_format_string_output(str, idx, temp_buffer, local_params);
  return PARSE_SUCCESS;
}

// ==================== СПЕЦИАЛЬНЫЕ ТИПЫ ====================
/**
 * @brief Обрабатывает указатели
 */
static void s21_handle_pointer(char *str, int *idx, FormatParams params,
                               va_list args) {
  if (!str || !idx) return;

  void *ptr = va_arg(args, void *);

  if (ptr == S21_NULL)
    s21_format_null_output(str, idx, PTR_NULL, params);
  else
    s21_format_pointer_output(str, idx, ptr, params);
}

/**
 * @brief Обрабатывает счетчик символов
 */
static void s21_handle_count(const char *str, const int *idx,
                             FormatParams params, va_list args) {
  if (!str || !idx) return;

  if (params.type == TYPE_N_INT)
    *va_arg(args, int *) = *idx;
  else if (params.type == TYPE_N_SHORT)
    *va_arg(args, short *) = *idx;
  else if (params.type == TYPE_N_SCHAR)
    *va_arg(args, signed char *) = *idx;
  else if (params.type == TYPE_N_LONG)
    *va_arg(args, long *) = *idx;
  else
    *va_arg(args, long long *) = *idx;
}

/**
 * @brief Обрабатывает символ процента
 */
static void s21_handle_percent(char *str, int *idx) {
  if (!str || !idx) return;

  s21_convert_char_to_buffer(str, idx, '%');
}

// ==================== ФОРМАТИРОВАНИЕ ====================
/**
 * @brief Форматирует вывод целого числа
 */
static void s21_format_integer_output(char *str, int *idx, long long value,
                                      FormatParams params) {
  if (!str || !idx) return;

  if (value == 0 && params.precision_value == 0) {
    char sign_char[4] = {0};
    s21_determine_sign(sign_char, sizeof(sign_char), false, params);
    s21_write_output("", sign_char, "", str, idx, params);
    return;
  }
  if (value == 0) s21_reset_flags_for_zero(&params);

  char buffer[MAX_BUFFER_SIZE] = {0};
  int num_len = 0;
  char sign_char[4] = {0};
  s21_determine_sign(sign_char, sizeof(sign_char), value < 0, params);
  unsigned long long abs_value = llabs(value);

  s21_convert_uint_to_buffer(buffer, &num_len, abs_value, params);
  s21_write_output(buffer, sign_char, "", str, idx, params);
}

/**
 * @brief Форматирует вывод беззнакового числа
 */
static void s21_format_unsigned_output(char *str, int *idx,
                                       unsigned long long value,
                                       FormatParams params) {
  if (!str || !idx) return;

  if (value == 0 && params.precision_value == 0) {
    char pref_char[4] = {0};
    s21_pref_sign(pref_char, sizeof(pref_char), value, params);

    s21_reset_flags_for_zero(&params);
    s21_write_output("", "", pref_char, str, idx, params);
    return;
  }

  if (value == 0) {
    s21_reset_flags_for_zero(&params);
  }

  char buffer[MAX_BUFFER_SIZE] = {0};
  int num_len = 0;
  char sign_char[4] = {0};
  s21_determine_sign(sign_char, sizeof(sign_char), false, params);
  char pref_char[4] = {0};
  s21_pref_sign(pref_char, sizeof(pref_char), value, params);

  s21_convert_uint_to_buffer(buffer, &num_len, value, params);
  s21_write_output(buffer, sign_char, pref_char, str, idx, params);
}

/**
 * @brief Форматирует вывод символа
 */
static void s21_format_char_output(char *str, int *idx, const char *c,
                                   FormatParams params) {
  if (!str || !idx || !c) return;

  const char buffer[2] = {*c, '\0'};
  s21_write_output(buffer, "", "", str, idx, params);
}

/**
 * @brief Форматирует вывод строки
 */
static void s21_format_string_output(char *str, int *idx, const char *s,
                                     FormatParams params) {
  if (!str || !idx) return;

  s21_write_output(s, "", "", str, idx, params);
}

/**
 * @brief Форматирует вывод указателя
 */
static void s21_format_pointer_output(char *str, int *idx, void *ptr,
                                      FormatParams params) {
  if (!str || !idx) return;

  char buffer[MAX_BUFFER_SIZE] = {0};
  int num_len = 0;
  char sign_char[4] = {0};
  s21_determine_sign(sign_char, sizeof(sign_char), false, params);

  s21_convert_uint_to_buffer(buffer, &num_len, (unsigned long long)ptr, params);
  s21_write_output(buffer, sign_char, "0x", str, idx, params);
}

/**
 * @brief Обрабатывает вывод null-значений для строк и указателей
 */
static void s21_format_null_output(char *str, int *idx, const char *null_str,
                                   FormatParams params) {
  if (!str || !idx || !null_str) return;

  if (params.precision_type &&
      params.precision_value < (int)s21_strlen(null_str)) {
    s21_reset_flags_for_special(&params);
    s21_write_output("", "", "", str, idx, params);
  } else {
    s21_write_output(null_str, "", "", str, idx, params);
  }
}

/**
 * @brief Обрабатывает специальные значения float
 */
static bool s21_format_special_float_output(char *str, int *idx,
                                            long double value,
                                            FormatParams params) {
  if (!str || !idx) return false;

  // Используем макрос для проверки переполнения
  int is_overflow = IS_LDBL_OVERFLOW(value);

  // Используем правильные функции для long double
  int is_nan = isnanl(value);
  int is_inf = isinfl(value);

  if (!is_nan && !is_inf && !is_overflow) return false;

  s21_reset_flags_for_special(&params);
  char sign_char[4] = {0};
  s21_determine_sign(sign_char, sizeof(sign_char), signbit(value), params);

  const char *special_str;
  if (is_nan) {
    special_str = params.uppercase ? NAN_UPPERCASE : NAN_LOWERCASE;
  } else if (is_inf || is_overflow) {
    special_str = params.uppercase ? INF_UPPERCASE : INF_LOWERCASE;
  } else {
    return false;
  }

  s21_write_output(special_str, sign_char, "", str, idx, params);
  return true;
}

/**
 * @brief Форматирует вывод вещественного числа
 */
static void s21_format_float_output(char *str, int *idx, long double dval,
                                    FormatParams params) {
  if (!str || !idx) return;

  char buffer[MAX_BUFFER_SIZE] = {0};
  int buf_idx = 0;
  int precision =
      params.precision_type ? params.precision_value : DEFAULT_PRECISION;

  char sign_char[4] = {0};
  s21_determine_sign(sign_char, sizeof(sign_char), signbit(dval), params);
  dval = fabsl(dval);

  if (dval == 0.0L && params.spec_char == CHAR_G) {
    s21_format_zero_g(buffer, &buf_idx, precision, params);
  } else {
    if (params.spec_char == CHAR_G) {
      s21_format_g(buffer, &buf_idx, dval, precision, params);
    } else if (params.spec_char == CHAR_F) {
      s21_format_f(buffer, &buf_idx, dval, precision, params);
    } else if (params.spec_char == CHAR_E) {
      s21_format_e(buffer, &buf_idx, dval, precision, params);
    }
  }

  buffer[buf_idx] = '\0';
  s21_write_output(buffer, sign_char, "", str, idx, params);
}

// ==================== ВСПОМОГАТЕЛЬНЫЕ ФУНКЦИИ ====================
/**
 * @brief Добавляет символ в буфер
 */
static void s21_convert_char_to_buffer(char *buffer, int *idx_buffer, char c) {
  if (!buffer || !idx_buffer || *idx_buffer < 0) return;
  buffer[(*idx_buffer)++] = c;
}

/**
 * @brief Добавляет строку в буфер
 */
static void s21_convert_string_to_buffer(char *buffer, int *idx_buffer,
                                         const char *s) {
  if (!buffer || !idx_buffer || !s || *idx_buffer < 0) return;

  for (; *s; ++s) {
    if (*idx_buffer >= MAX_BUFFER_SIZE - 1) break;  // Защита от переполнения
    s21_convert_char_to_buffer(buffer, idx_buffer, *s);
  }
}

/**
 * @brief Конвертирует беззнаковое число в строку
 */
static void s21_convert_uint_to_buffer(char *buf, int *idx_buf,
                                       unsigned long long value,
                                       FormatParams params) {
  if (!buf || !idx_buf) return;

  char buffer[MAX_BUFFER_SIZE];
  const char *digits =
      params.uppercase ? "0123456789ABCDEF" : "0123456789abcdef";
  int i = 0;

  do {
    if (i >= MAX_BUFFER_SIZE - 1) break;
    buffer[i++] = digits[value % params.base];
    value /= params.base;
  } while (value != 0);

  int start_index = *idx_buf;
  for (int j = i - 1; j >= 0; --j) {
    if (start_index >= MAX_BUFFER_SIZE - 1) break;
    buf[start_index++] = buffer[j];
  }
  *idx_buf = start_index;
  if (*idx_buf < MAX_BUFFER_SIZE) {
    buf[*idx_buf] = '\0';
  } else if (MAX_BUFFER_SIZE > 0) {
    buf[MAX_BUFFER_SIZE - 1] = '\0';
    *idx_buf = MAX_BUFFER_SIZE - 1;
  }
}

/**
 * @brief Определяет знак числа
 */
static void s21_determine_sign(char *result, s21_size_t size, bool val,
                               FormatParams params) {
  if (!result || size < 4) return;

  result[0] = '\0';
  int pos = 0;

  if (val) {
    result[pos++] = '-';
  } else if (params.flag_plus) {
    result[pos++] = '+';
  } else if (params.flag_space) {
    result[pos++] = ' ';
  }

  result[pos] = '\0';
}

/**
 * @brief Добавляет префикс для числа
 */
static void s21_pref_sign(char *result, s21_size_t size, int val,
                          FormatParams params) {
  if (!result || size < 4) return;

  result[0] = '\0';
  int pos = 0;

  if (params.flag_hash) {
    if (params.base == BaseOctal) {
      result[pos++] = '0';
    } else if (params.base == BaseHexadecimal && val != 0) {
      result[pos++] = '0';
      result[pos++] = params.uppercase ? 'X' : 'x';
    }
  }

  result[pos] = '\0';
}

// ======== ВСПОМОГАТЕЛЬНЫЕ ФУНКЦИИ ФОРМАТИРОВАНИЯ ДЛИННОГО СИМВОЛА ========

/**
 * @brief Конвертирует широкий символ в UTF-8
 */
static int s21_wchar_to_utf8(char *dest, wchar_t wc) {
  if (!dest) return -1;

  uint32_t code = (uint32_t)wc;
  // Проверка на валидность Unicode
  if (code > UNICODE_MAX ||
      (code >= SURROGATE_START && code <= SURROGATE_END) || wc < 0) {
    return -1;
  }

  // Конвертация в UTF-8
  if (wc < UTF8_1_BYTE_LIMIT) {
    dest[0] = (char)wc;
    return 1;
  } else if (wc < UTF8_2_BYTE_LIMIT) {
    dest[0] = 0xC0 | (wc >> 6);
    dest[1] = 0x80 | (wc & 0x3F);
    return 2;
  } else if (wc < UTF8_3_BYTE_LIMIT) {
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

// ======== ВСПОМОГАТЕЛЬНЫЕ ФУНКЦИИ ФОРМАТИРОВАНИЯ ВЕЩЕСТВЕННЫХ ЧИСЕЛ ========
/**
 * @brief Форматирует нулевое значение для спецификатора G
 */
static void s21_format_zero_g(char *buffer, int *buf_idx, int precision,
                              FormatParams params) {
  if (!buffer || !buf_idx) return;

  if (params.flag_hash) precision = precision > 0 ? precision - 1 : 0;
  s21_format_f(buffer, buf_idx, 0.0L, precision, params);
  s21_reset_flags_for_special(&params);
}

/**
 * @brief Форматирует число для спецификатора G
 */
static void s21_format_g(char *buf, int *idx_buf, long double dval,
                         int precision, const FormatParams params) {
  if (!buf || !idx_buf) return;

  int exponent = (dval == 0.0L) ? 0 : (int)floorl(log10l(dval));

  if (exponent >= -4 && exponent < precision) {
    precision -= (exponent + 1);
    if (precision < 0) precision = 0;
    s21_format_f(buf, idx_buf, dval, precision, params);
  } else {
    precision = (precision > 0) ? precision - 1 : 0;
    s21_format_e(buf, idx_buf, dval, precision, params);
  }
}

/**
 * @brief Форматирует число для спецификатора F
 */
static void s21_format_f(char *buf, int *idx_buf, long double value,
                         int precision, const FormatParams params) {
  if (!buf || !idx_buf) return;

  long double rounding = 0.5L * powl(10.0L, -precision);
  value += rounding;

  long double int_part;
  long double frac_part = modfl(value, &int_part);
  s21_convert_uint_to_buffer(buf, idx_buf, (long long)int_part, params);
  s21_format_fractional_part(buf, idx_buf, frac_part, precision, params);
}

/**
 * @brief Форматирует число для спецификатора E
 */
static void s21_format_e(char *buf, int *idx_buf, long double value,
                         int precision, const FormatParams params) {
  if (!buf || !idx_buf) return;

  int exp = 0;
  if (value != 0.0L) exp = (int)floorl(log10l(value));
  value *= powl(10.0L, -exp);

  long double rounding = 0.5L * powl(10.0L, -precision);
  value += rounding;

  if (value >= 10.0L) {
    value /= 10.0L;
    ++exp;
  }

  long double int_part;
  long double frac_part = modfl(value, &int_part);
  s21_convert_uint_to_buffer(buf, idx_buf, (long long)int_part, params);
  s21_format_fractional_part(buf, idx_buf, frac_part, precision, params);
  s21_format_exponent(buf, idx_buf, exp, params);
}

/**
 * @brief Форматирует дробную часть числа
 */
static void s21_format_fractional_part(char *buf, int *idx_buf,
                                       long double frac, int precision,
                                       const FormatParams params) {
  if (!buf || !idx_buf) return;

  if (precision <= 0) {
    if (params.flag_hash) s21_convert_char_to_buffer(buf, idx_buf, '.');
    return;
  }

  s21_convert_char_to_buffer(buf, idx_buf, '.');

  for (int i = 0; i < precision; ++i) {
    frac *= 10.0L;
    int digit = (int)frac;
    s21_convert_char_to_buffer(buf, idx_buf, '0' + digit);
    frac -= digit;
  }
  if (params.spec_char == CHAR_G && !params.flag_hash) {
    s21_format_fractional_part_g(buf, idx_buf);
  }
}

/**
 * @brief Убирает незначащие нули для спецификатора G
 */
static void s21_format_fractional_part_g(const char *buf, int *idx_buf) {
  if (!buf || !idx_buf) return;

  while (*idx_buf > 0 && buf[*idx_buf - 1] == '0') {
    (*idx_buf)--;
  }

  if (*idx_buf > 0 && buf[*idx_buf - 1] == '.') {
    (*idx_buf)--;
  }
}

/**
 * @brief Форматирует экспоненциальную часть
 */
static void s21_format_exponent(char *buf, int *idx_buf, int exp,
                                const FormatParams params) {
  if (!buf || !idx_buf) return;

  buf[(*idx_buf)++] = params.uppercase ? 'E' : 'e';
  buf[(*idx_buf)++] = exp >= 0 ? '+' : '-';

  exp = abs(exp);
  if (exp < 10) buf[(*idx_buf)++] = '0';

  s21_convert_uint_to_buffer(buf, idx_buf, (unsigned long long)exp, params);
}

// ============================= ВЫВОД В СТРОКУ =============================

/**
 * @brief Добавляет заполняющие символы
 */
static void s21_convert_num_len_pad_char_to_str(char *str, int *idx,
                                                int num_len, char pad_char) {
  if (!str || !idx) return;

  for (int i = 0; i < num_len; ++i) {
    s21_convert_char_to_buffer(str, idx, pad_char);
  }
}

/**
 * @brief Вычисляет параметры вывода
 */
static void s21_calculate_output_params(const char *buffer,
                                        const char *sign_char,
                                        const char *pref_char,
                                        FormatParams params, int *num_len,
                                        int *sign_len, int *pref_len,
                                        int *width, int *precision) {
  *num_len = buffer ? s21_strlen(buffer) : 0;
  *sign_len = sign_char ? s21_strlen(sign_char) : 0;
  *pref_len = pref_char ? s21_strlen(pref_char) : 0;

  *width = params.width_value;
  *precision = params.precision_value;

  if (params.type == TYPE_CHAR) {
    *num_len = 1;
  } else if (params.type == TYPE_STRING && params.precision_type &&
             *precision < *num_len) {
    *num_len = *precision;
  }

  if (*precision < 0) *precision = 0;
  if (*width < 0) *width = 0;

  if (params.type == TYPE_FLOAT || params.type == TYPE_DOUBLE ||
      params.type == TYPE_LONGDOUBLE) {
    *precision = 0;
  } else {
    *precision = (*precision > *num_len) ? *precision - *num_len : 0;
  }

  if (*precision != 0 && params.base == BaseOctal) *pref_len = 0;

  *width -= (*precision + *num_len + *sign_len + *pref_len);
  if (*width < 0) *width = 0;
}

/**
 * @brief Записывает отформатированный вывод в буфер
 */
static void s21_write_output(const char *buffer, const char *sign_char,
                             const char *pref_char, char *str, int *idx,
                             const FormatParams params) {
  if (!str || !idx) return;

  int num_len, sign_len, pref_len, width, precision;
  s21_calculate_output_params(buffer, sign_char, pref_char, params, &num_len,
                              &sign_len, &pref_len, &width, &precision);

  if (!params.flag_minus) {
    if (params.flag_zero &&
        (!params.precision_type || params.type == TYPE_FLOAT ||
         params.type == TYPE_DOUBLE || params.type == TYPE_LONGDOUBLE)) {
      if (pref_len) s21_convert_string_to_buffer(str, idx, pref_char);
      if (sign_len) s21_convert_string_to_buffer(str, idx, sign_char);

      s21_convert_num_len_pad_char_to_str(str, idx, width, '0');
      sign_len = pref_len = 0;
    } else {
      s21_convert_num_len_pad_char_to_str(str, idx, width, ' ');
    }
  }

  if (pref_len) s21_convert_string_to_buffer(str, idx, pref_char);
  if (sign_len) s21_convert_string_to_buffer(str, idx, sign_char);

  if (params.type != TYPE_STRING && params.type != TYPE_FLOAT &&
      params.type != TYPE_DOUBLE && params.type != TYPE_LONGDOUBLE)
    s21_convert_num_len_pad_char_to_str(str, idx, precision, '0');

  if (params.type == TYPE_CHAR) {
    s21_convert_char_to_buffer(str, idx, buffer[0]);
  } else if (params.type == TYPE_STRING)
    for (int i = 0; i < num_len; ++i) {
      s21_convert_char_to_buffer(str, idx, buffer[i]);
    }
  else
    s21_convert_string_to_buffer(str, idx, buffer);

  if (params.flag_minus) {
    s21_convert_num_len_pad_char_to_str(str, idx, width, ' ');
  }
}