

#include "../include/s21_string.h"
#include "parse.h"

#define DEFAULT_PRECISION 6  ///< Точность по умолчанию
#define MAX_BUFFER_SIZE 65  ///< Максимальный размер буфера

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

    } else
      str[idx++] = format[i], i++;
  }

  str[idx] = '\0';
  va_end(args);
  return error ? -1 : idx;
}

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

static void handle_char(char *str, int *idx, FormatParams params,
                        va_list args) {
  char c = (char)va_arg(args, int);
  char buffer[2] = {c, '\0'};
  convert_string_buffer_to_str(str, idx, buffer, params);
}

static void handle_string(char *str, int *idx, FormatParams params,
                          va_list args) {
  char *s = va_arg(args, char *);

  convert_string_buffer_to_str(str, idx, s, params);
}

static int handle_wchar(char *str, int *idx, FormatParams params,
                        va_list args) {
  wchar_t wcval = va_arg(args, wchar_t);

  return 0;
}

static int handle_wstring(char *str, int *idx, FormatParams params,
                          va_list args) {
  wchar_t *wsval = va_arg(args, wchar_t *);

  return 0;
}

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

static char determine_sign(bool negative, FormatParams params) {
  if (negative) return '-';
  if (params.flag_plus) return '+';
  if (params.flag_space) return ' ';
  return 0;
}

static void format_integer_output(char *str, int *idx, long long value,
                                  FormatParams params) {
  char buffer[MAX_BUFFER_SIZE] = {0};
  int num_len = 0;
  char sign = determine_sign(value < 0, params);
  unsigned long long abs_value = llabs(value);

  convert_uint_to_buffer(buffer, &num_len, abs_value, params);
  write_output(str, idx, buffer, sign, num_len, params);
}

static void format_unsigned_output(char *str, int *idx,
                                   unsigned long long value,
                                   FormatParams params) {
  char buffer[MAX_BUFFER_SIZE] = {0};
  int num_len = 0;

  convert_uint_to_buffer(buffer, &num_len, value, params);
  write_output(str, idx, buffer, 0, num_len, params);
}

static bool format_special_float_output(char *str, int *idx, long double value,
                                        FormatParams params) {
  if (!isnan(value) && !isinf(value)) return false;

  const char *special_str = isnan(value) ? (params.uppercase ? "NAN" : "nan")
                                         : (params.uppercase ? "INF" : "inf");

  char sign = determine_sign(value < 0, params);
  write_output(str, idx, special_str, sign, strlen(special_str), params);
  return true;
}

static void format_float_output(char *str, int *idx, long double dval,
                                FormatParams params) {
  char buffer[MAX_BUFFER_SIZE] = {0};
  int buf_idx = 0;
  int precision =
      params.precision_value >= 0 ? params.precision_value : DEFAULT_PRECISION;

  char sign = determine_sign(dval < 0, params);
  dval = fabsl(dval);

  if (params.spec_char == CHAR_G) {
    format_g_float(buffer, &buf_idx, dval, precision, params);
  } else if (params.spec_char == CHAR_F) {
    format_decimal_float(buffer, &buf_idx, dval, precision, params);
  } else if (params.spec_char == CHAR_E) {
    format_scientific_float(buffer, &buf_idx, dval, precision, params);
  }

  write_output(str, idx, buffer, sign, buf_idx, params);
}

static void format_g_float(char *buf, int *idx_buf, long double dval,
                           int precision, FormatParams params) {
  int exp = (dval == 0.0L) ? 0 : (int)floorl(log10l(dval));

  if (exp >= -4 && exp < precision) {
    precision = precision - (exp + 1);
    if (precision < 0) precision = 0;

    format_decimal_float(buf, &idx_buf, dval, precision, params);
  } else {
    precision = (precision > 0) ? precision - 1 : 0;

    format_scientific_float(buf, &idx_buf, dval, precision, params);
  }
}

static void format_f(char *buf, int *idx_buf, long double value, int precision,
                     FormatParams params) {
  long double rounding = 0.5L * powl(10.0L, -precision);
  value += rounding;

  long double int_part;
  long double frac_part = modfl(value, &int_part);
  convert_uint_to_buffer(buf, idx_buf, (long long)int_part, params);

  if (params.spec_char == CHAR_G)
    format_fractional_partG(buf, idx_buf, frac_part, precision, params);
  else
    format_fractional_part(buf, idx_buf, frac_part, precision, params);
}

static void format_e(char *buf, int *idx_buf, long double value, int precision,
                     FormatParams params) {
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

  if (params.spec_char == CHAR_G)
    format_fractional_partG(buf, idx_buf, frac_part, precision, params);
  else {
    format_fractional_part(buf, idx_buf, frac_part, precision, params);
  }

  format_exponent(buf, idx_buf, exp, params);
}

static void format_fractional_part(char *buf, int *idx_buf, long double frac,
                                   int precision, FormatParams params) {
  if (precision <= 0) return;

  convert_char_to_buffer(buf, idx_buf, '.');

  for (int i = 0; i < precision; i++) {
    frac *= 10.0L;
    int digit = (int)frac;
    convert_char_to_buffer(buf, idx_buf, '0' + digit);
    frac -= digit;
  }
}

static void format_fractional_partG(char *buf, int *idx_buf, long double frac,
                                    int precision, FormatParams params) {
  if (precision <= 0) return;

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
  while (temp_idx > 0 && temp[temp_idx - 1] == '0') {
    temp_idx--;
  }

  if (temp_idx > 0) buf[(*idx_buf)++] = '.';

  // Копируем цифры в основной буфер
  for (int i = 0; i < temp_idx; i++) {
    buf[(*idx_buf)++] = temp[i];
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