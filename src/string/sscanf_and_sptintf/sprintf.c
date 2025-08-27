

#include "../include/s21_string.h"
#include "parse.h"

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

  convert_int_to_str(str, idx, val, params);
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

  convert_uint_to_str(str, idx, val, params);
}

static void handle_float(char *str, int *idx, FormatParams params,
                         va_list args) {
  long double val;
  if (params.type == TYPE_FLOAT)
    val = va_arg(args, double);
  else
    val = va_arg(args, long double);

  convert_float_to_str(str, idx, val, params);
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
