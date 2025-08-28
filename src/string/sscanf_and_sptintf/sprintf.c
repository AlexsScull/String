#include "../include/s21_string.h"
#include "parse.h"


#define DEFAULT_PRECISION 6  ///< Точность по умолчанию
#define MAX_BUFFER_SIZE 65  ///< Максимальный размер буфера

// ==================== ОБРАБОТКА ТИПОВ ДАННЫХ ====================
static bool process_format_conversion(char *str, int *str_idx,
                                      FormatParams params, va_list args);

static void handle_integer(char *str, int *idx, FormatParams params,
                           va_list args);

static void handle_unsigned(char *str, int *idx, FormatParams params,
                            va_list args);

static void handle_float(char *str, int *idx, FormatParams params,
                         va_list args);

static void handle_char(char *str, int *idx, FormatParams params, va_list args);

static void handle_string(char *str, int *idx, FormatParams params,
                          va_list args);

static int handle_wchar(char *str, int *idx, FormatParams params, va_list args);

static int handle_wstring(char *str, int *idx, FormatParams params,
                          va_list args);

static void handle_pointer(char *str, int *idx, FormatParams params,
                           va_list args);

static void handle_count(char *str, int *idx, FormatParams params,
                         va_list args);

static void handle_percent(char *str, int *idx);

static void convert_char_to_buffer(char *buffer, int *idx_buffer, char c);

static void convert_string_to_buffer(char *buffer, int *idx_buffer,
                                     const char *s);
static void convert_uint_to_buffer(char *buf, int *idx_buf,
                                   unsigned long long value,
                                   FormatParams params);

static const char *determine_sign(bool negative, FormatParams params);

static void format_integer_output(char *str, int *idx, long long value,
                                  FormatParams params);

static void format_unsigned_output(char *str, int *idx,
                                   unsigned long long value,
                                   FormatParams params);

static void format_pointer_output(char *str, int *idx, void *ptr,
                                  FormatParams params);

static bool format_special_float_output(char *str, int *idx, long double value,
                                        FormatParams params);

static void format_float_output(char *str, int *idx, long double dval,
                                FormatParams params);
static void format_zero(char *buffer, int *buf_idx, long double dval,
                        int precision, FormatParams params);
static void format_g(char *buffer, int *buf_idx, long double dval,
                     int precision, FormatParams params);
static void format_f(char *buf, int *idx_buf, long double value, int precision,
                     FormatParams params);
static void format_e(char *buf, int *idx_buf, long double value, int precision,
                     FormatParams params);
static void format_fractional_part(char *buf, int *idx_buf, long double frac,
                                   int precision, FormatParams params);

static void format_exponent(char *buf, int *idx_buf, int exp,
                            FormatParams params);

static void write_output(char *buffer, const char *sign_char, char *str,
                         int *idx, const FormatParams params);
;
static void str_error(char *buffer, int *idx_buffer, FormatParams params);

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

      FormatParams params = init_format_params();
      if (!error) error = parse_format_spr(format, &i, &params, args);
      if (!error) error = process_format_conversion(str, &idx, params, args);

      if (error == PARSE_ERROR_END_OF_FORMAT)
        str_error(str, &idx, params), error = PARSE_SUCCESS;
    } else {
      str[idx++] = format[i++];
    }
  }

  str[idx] = '\0';
  va_end(args);
  return error ? -1 : idx;
}

static void str_error(char *buffer, int *idx_buffer, FormatParams params) {
  convert_char_to_buffer(buffer, idx_buffer, '%');
  if (params.flag_hash) convert_char_to_buffer(buffer, idx_buffer, '#');
  if (params.flag_minus) convert_char_to_buffer(buffer, idx_buffer, '-');
  if (params.flag_plus) convert_char_to_buffer(buffer, idx_buffer, '+');
  convert_char_to_buffer(
      buffer, idx_buffer,
      params.uppercase ? params.specifier : toupper(params.specifier));
}

// ==================== ОБРАБОТКА ТИПОВ ДАННЫХ ====================
static bool process_format_conversion(char *str, int *str_idx,
                                      FormatParams params, va_list args) {
  bool result = PARSE_SUCCESS;

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

// ==================== ЦЕЛОЧИСЛЕННЫЕ ТИПЫ ====================
static void handle_integer(char *str, int *idx, FormatParams params,
                           va_list args) {
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

  format_integer_output(str, idx, val, params);
}

static void handle_unsigned(char *str, int *idx, FormatParams params,
                            va_list args) {
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

  format_unsigned_output(str, idx, val, params);
}

// ==================== ВЕЩЕСТВЕННЫЕ ТИПЫ ====================
static void handle_float(char *str, int *idx, FormatParams params,
                         va_list args) {
  long double val;
  if (params.type == TYPE_FLOAT)
    val = va_arg(args, double);
  else
    val = va_arg(args, long double);

  if (!format_special_float_output(str, idx, val, params)) {
    format_float_output(str, idx, val, params);
  }
}

// ==================== СИМВОЛЫ И СТРОКИ ====================
static void handle_char(char *str, int *idx, FormatParams params,
                        va_list args) {
  char c = (char)va_arg(args, int);
  char buffer[2] = {c, '\0'};
  // convert_string_buffer_to_str(str, idx, buffer, params);
}

static void handle_string(char *str, int *idx, FormatParams params,
                          va_list args) {
  char *s = va_arg(args, char *);
  // convert_string_buffer_to_str(str, idx, s, params);
}

static int handle_wchar(char *str, int *idx, FormatParams params,
                        va_list args) {
  wchar_t wcval = va_arg(args, wchar_t);
  return PARSE_ERROR_END_OF_FORMAT;
}

static int handle_wstring(char *str, int *idx, FormatParams params,
                          va_list args) {
  wchar_t *wsval = va_arg(args, wchar_t *);
  return PARSE_ERROR_END_OF_FORMAT;
}

// ==================== СПЕЦИАЛЬНЫЕ ТИПЫ ====================
static void handle_pointer(char *str, int *idx, FormatParams params,
                           va_list args) {
  void *ptr = va_arg(args, void *);
}

static void handle_count(char *str, int *idx, FormatParams params,
                         va_list args) {
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

static void handle_percent(char *str, int *idx) {
  convert_char_to_buffer(str, idx, '%');
}

// ==================== ВСПОМОГАТЕЛЬНЫЕ ФУНКЦИИ ====================
static void convert_char_to_buffer(char *buffer, int *idx_buffer, char c) {
  buffer[(*idx_buffer)++] = c;
}

static void convert_string_to_buffer(char *buffer, int *idx_buffer,
                                     const char *s) {
  for (; *s; s++) {
    convert_char_to_buffer(buffer, idx_buffer, *s);
  }
}

static void convert_uint_to_buffer(char *buf, int *idx_buf,
                                   unsigned long long value,
                                   FormatParams params) {
  char buffer[MAX_BUFFER_SIZE];
  const char *digits =
      params.uppercase ? "0123456789ABCDEF" : "0123456789abcdef";
  int i = 0;

  do {
    buffer[i++] = digits[value % params.base];
    value /= params.base;
  } while (value > 0);

  int start_index = *idx_buf;
  for (int j = i - 1; j >= 0; j--) {
    buf[start_index++] = buffer[j];
  }
  *idx_buf = start_index;
  buf[*idx_buf] = '\0';
}

static const char *determine_sign(bool negative, FormatParams params) {
  static char result[3] = {0};
  result[0] = '\0';
  int pos = 0;

  // Добавляем знак
  if (negative) {
    result[pos++] = '-';
  } else if (params.flag_plus) {
    result[pos++] = '+';
  } else if (params.flag_space) {
    result[pos++] = ' ';
  }

  // Добавляем префиксы для восьмеричной и шестнадцатеричной систем
  if (params.flag_hash) {
    if (params.base == BaseOctal && !negative) {  // Для восьмеричной системы
      result[pos++] = '0';
    } else if (params.base ==
               BaseHexadecimal) {  // Для шестнадцатеричной системы
      result[pos++] = '0';
      result[pos++] = params.uppercase ? 'X' : 'x';
    }
  }

  result[pos] = '\0';
  return result;
}

static void convert_num_len_pad_char_to_str(char *str, int *idx, int num_len,
                                            char pad_char) {
  for (int i = 0; i < num_len; i++) {
    convert_char_to_buffer(str, idx, pad_char);
  }
}
// ==================== ФОРМАТИРОВАНИЕ ЧИСЕЛ ====================
static void format_integer_output(char *str, int *idx, long long value,
                                  FormatParams params) {
  char buffer[MAX_BUFFER_SIZE] = {0};
  int num_len = 0;
  const char *prefix = determine_sign(value < 0, params);
  unsigned long long abs_value = llabs(value);

  convert_uint_to_buffer(buffer, &num_len, abs_value, params);
  write_output(buffer, prefix, str, idx, params);
}

static void format_unsigned_output(char *str, int *idx,
                                   unsigned long long value,
                                   FormatParams params) {
  char buffer[MAX_BUFFER_SIZE] = {0};
  int num_len = 0;
  const char *prefix = determine_sign(0, params);

  convert_uint_to_buffer(buffer, &num_len, value, params);
  write_output(buffer, prefix, str, idx, params);
}

static void format_pointer_output(char *str, int *idx, void *ptr,
                                  FormatParams params) {
  if (ptr == NULL) {
    reset_flags_for_null_inf(&params);
    write_output("nil", 0, str, idx, params);
    return;
  }

  char buffer[MAX_BUFFER_SIZE] = {0};
  int num_len = 0;
  const char *prefix = determine_sign(0, params);

  convert_uint_to_buffer(buffer, &num_len, (unsigned long long)ptr, params);
  write_output(buffer, prefix, str, idx, params);
}

static bool format_special_float_output(char *str, int *idx, long double value,
                                        FormatParams params) {
  if (!isnan(value) && !isinf(value)) return false;

  reset_flags_for_null_inf(&params);
  const char *prefix = determine_sign(value < 0, params);

  char *special_str = isnan(value) ? (params.uppercase ? "NAN" : "nan")
                                   : (params.uppercase ? "INF" : "inf");

  write_output(special_str, prefix, str, idx, params);
  return true;
}

static void format_float_output(char *str, int *idx, long double dval,
                                FormatParams params) {
  char buffer[MAX_BUFFER_SIZE] = {0};
  int buf_idx = 0;
  int precision =
      (params.precision_type == true) ? params.precision_value : DEFAULT_PRECISION;
//   if (params.flag_hash && params.spec_char == CHAR_G) precision -= 1;

  const char *prefix = determine_sign(signbit(dval), params);
  dval = fabsl(dval);

  if (dval == 0.0L)
    format_zero(buffer, &buf_idx, dval, precision, params);
  else {
    if (params.spec_char == CHAR_G) {
      format_g(buffer, &buf_idx, dval, precision, params);
    } else if (params.spec_char == CHAR_F) {
      format_f(buffer, &buf_idx, dval, precision, params);
    } else if (params.spec_char == CHAR_E) {
      format_e(buffer, &buf_idx, dval, precision, params);
    }
  }

  write_output(buffer, prefix, str, idx, params);
}

// ======== ВСПОМОГАТЕЛЬНЫЕ ФУНКЦИИ ФОРМАТИРОВАНИЯ ВЕЩЕСТВЕННЫХ ЧИСЕЛ ========

static void format_zero(char *buffer, int *buf_idx, long double dval,
                        int precision, FormatParams params) {
//   if (params.spec_char == CHAR_G) {
//     convert_char_to_buffer(buffer, buf_idx, '0');
//     format_fractional_part(buffer, buf_idx, 0.0L, precision, params);
//   } else if (params.spec_char == CHAR_F) {
//     format_f(buffer, buf_idx, dval, precision, params);
//   } else if (params.spec_char == CHAR_E) {
//     format_e(buffer, buf_idx, dval, precision, params);
//   }

    if (params.spec_char == CHAR_G) {
    convert_char_to_buffer(buffer, buf_idx, '0');
  } else if (params.spec_char == CHAR_F) {
    convert_char_to_buffer(buffer, buf_idx, '0');
  } else if (params.spec_char == CHAR_E) {
    format_e(buffer, buf_idx, dval, precision, params);
  }
}

static void format_g(char *buffer, int *buf_idx, long double dval,
                     int precision, FormatParams params) {
  int exponent = (dval == 0.0L) ? 0 : (int)log10l(dval);

  if (exponent >= -4 && exponent < precision) {
    precision -= (exponent + 1);
    format_f(buffer, buf_idx, dval, precision, params);
  } else {
    format_e(buffer, buf_idx, dval, precision, params);
  }
}
static void format_f(char *buf, int *idx_buf, long double value, int precision,
                     FormatParams params) {
  long double rounding = 0.5L * powl(10.0L, -precision);
  value += rounding;

  long double int_part;
  long double frac_part = modfl(value, &int_part);
  convert_uint_to_buffer(buf, idx_buf, (long long)int_part, params);
  format_fractional_part(buf, idx_buf, frac_part, precision, params);
}

static void format_e(char *buf, int *idx_buf, long double value, int precision,
                     FormatParams params) {
  int exp = 0;
  if (value != 0.0L) exp = (int)floorl(log10l(value));
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
  format_fractional_part(buf, idx_buf, frac_part, precision, params);
  format_exponent(buf, idx_buf, exp, params);
}

static void format_fractional_part(char *buf, int *idx_buf, long double frac,
                                   int precision, FormatParams params) {
//   if (precision <= 0 && !params.flag_hash) return;
  if (precision <= 0) return;

  convert_char_to_buffer(buf, idx_buf, '.');

  for (int i = 0; i < precision; i++) {
    frac *= 10.0L;
    int digit = (int)frac;
    convert_char_to_buffer(buf, idx_buf, '0' + digit);
    frac -= digit;
  }
}

static void format_exponent(char *buf, int *idx_buf, int exp,
                            FormatParams params) {
  buf[(*idx_buf)++] = params.uppercase ? 'E' : 'e';
  buf[(*idx_buf)++] = exp >= 0 ? '+' : '-';

  exp = abs(exp);
  if (exp < 10) buf[(*idx_buf)++] = '0';

  convert_uint_to_buffer(buf, idx_buf, (unsigned long long)exp, params);
}

// ========================================================================

static void write_output(char *buffer, const char *sign_char, char *str,
                         int *idx, const FormatParams params) {
  int num_len = strlen(buffer);
  int sign_len = strlen(sign_char);

  int width = params.width_value;
  width = abs(width);

  int precision = params.precision_value;
  precision = (precision > num_len) ? precision - num_len : 0;

  width = width - (precision + num_len + sign_len);

  if (!params.flag_minus) {
    if (sign_len != 0) convert_string_to_buffer(str, idx, sign_char);
    convert_num_len_pad_char_to_str(str, idx, width, '0');
    sign_len = 0;
  }

  if (sign_len != 0) convert_string_to_buffer(str, idx, sign_char);
  convert_num_len_pad_char_to_str(str, idx, precision, '0');

  convert_string_to_buffer(str, idx, buffer);

  if (params.flag_minus) {
    convert_num_len_pad_char_to_str(str, idx, width, ' ');
  }
}

// static void convert_buffer_to_str(char *buffer, char sign_char, int num_len,
//                                   char *str, int *idx, int params[]) {
//   int width = params[PARAM_WIDTH_ASTERISK_VALUE];
//   bool left_align = params[FLAG_MINUS];
//   width = abs(width);

//   int precision = params[PARAM_PRECISION_ASTERISK_VALUE];
//   precision = (precision > num_len) ? precision - num_len : 0;

//   int sign_len = (sign_char != 0) ? 1 : 0;

//   int hash = 0;
//   if (params[FLAG_HASH]) {
//     if (params[PARAM_SPECIFIER] == 'o') {
//       if (precision == 0)
//         hash = 1;  // Префикс "0"
//       else
//         params[FLAG_ZERO] = true;
//     } else if (params[PARAM_SPECIFIER] == 'x' ||
//                params[PARAM_SPECIFIER] == 'X') {
//       hash = 2;  // Префикс "0x" или "0X"
//     }
//   }

//   width = width - (sign_len + num_len + precision + hash);

//   if (!left_align) {
//     if (params[FLAG_ZERO] && precision == 0 && params[PARAM_PRECISION] == -1)
//     {
//       if (hash) convert_hash_to_buffer(params, &hash, str, idx);
//       if (sign_len) convert_char_to_buffer(str, idx, sign_char);
//       convert_num_len_pad_char_to_str(str, idx, width, '0');
//       sign_len = 0;
//     } else {
//       convert_num_len_pad_char_to_str(str, idx, width, ' ');
//     }
//   }

//   if (hash) convert_hash_to_buffer(params, &hash, str, idx);
//   if (sign_len) convert_char_to_buffer(str, idx, sign_char);
//   convert_num_len_pad_char_to_str(str, idx, precision, '0');

//   convert_string_to_buffer(str, idx, buffer);

//   if (left_align) {
//     convert_num_len_pad_char_to_str(str, idx, width, ' ');
//   }
// }

// static void convert_hash_to_buffer(int params[], int *hash, char *str,
//                                    int *idx) {
//   if (params[PARAM_SPECIFIER] == 'o') {
//     convert_char_to_buffer(str, idx, '0');
//   } else {
//     convert_string_to_buffer(str, idx, params[PARAM_UPPERCASE] ? "0X" :
//     "0x");
//   }
//   *hash = 0;
// }

// static void convert_string_buffer_to_str(char *str, int *idx,
//                                          const char *buffer, int params[]) {
//   int width = params[PARAM_WIDTH_ASTERISK_VALUE];
//   int precision = params[PARAM_PRECISION_ASTERISK_VALUE];

//   bool left_align = params[FLAG_MINUS];
//   if (width < 0) width = -width;

//   int output_len;
//   if (params[TYPE] == TYPE_CHAR) {
//     output_len = 1;  // Для символа всегда длина 1
//   } else {
//     // Для строки: длина либо до \0, либо ограничена точностью
//     output_len = strlen(buffer);
//     if (params[PARAM_PRECISION] != -1 && precision < output_len)
//       output_len = precision;
//   }

//   int padding = width - output_len;
//   if (padding < 0) padding = 0;

//   if (!left_align) {
//     convert_num_len_pad_char_to_str(str, idx, padding, ' ');
//   }

//   if (params[TYPE] == TYPE_CHAR) {
//     convert_char_to_buffer(str, idx, buffer[0]);
//   } else {
//     for (int i = 0; i < output_len; i++) {
//       convert_char_to_buffer(str, idx, buffer[i]);
//     }
//   }

//   if (left_align) {
//     convert_num_len_pad_char_to_str(str, idx, padding, ' ');
//   }
// }

// static void convert_float_buffer_to_str(char *buffer, char sign_char,
//                                         int num_len, char *str, int *idx,
//                                         int params[]) {
//   int width = params[PARAM_WIDTH_ASTERISK_VALUE];
//   int precision = params[PARAM_PRECISION_ASTERISK_VALUE];
//   int sign_len = (sign_char != 0) ? 1 : 0;

//   bool left_align = params[FLAG_MINUS];
//   if (width < 0) width = -width;

//   int padding = width - (num_len + sign_len);
//   if (padding < 0) padding = 0;

//   if (!left_align) {
//     if (params[FLAG_ZERO]) {
//       if (sign_len) convert_char_to_buffer(str, idx, sign_char);
//       convert_num_len_pad_char_to_str(str, idx, padding, '0');
//       sign_len = 0;
//     } else
//       convert_num_len_pad_char_to_str(str, idx, padding, ' ');
//   }

//   if (sign_len) convert_char_to_buffer(str, idx, sign_char);
//   convert_string_to_buffer(str, idx, buffer);

//   if (left_align) {
//     convert_num_len_pad_char_to_str(str, idx, padding, ' ');
//   }
// }
