#include <float.h>
#include <math.h>
#include <stdint.h>

#include "s21_string.h"
#include "string_parser.h"

// ==================== ВСПОМОГАТЕЛЬНЫЕ ФУНКЦИИ ====================
static int s21_process_format_conversion(const char *str, int *str_idx,
                                         FormatParams params, va_list args);
static int s21_handle_integer(const char *str, int *idx, FormatParams params,
                              va_list args);
static int s21_handle_unsigned(const char *str, int *idx, FormatParams params,
                               va_list args);
static int s21_handle_float(const char *str, int *idx, FormatParams params,
                            va_list args);
static int s21_handle_char(const char *str, int *idx, FormatParams params,
                           va_list args);
static int s21_handle_string(const char *str, int *idx, FormatParams params,
                             va_list args);
static int s21_handle_pointer(const char *str, int *idx, FormatParams params,
                              va_list args);
static void s21_handle_count(int *idx, FormatParams params, va_list args);
static int s21_handle_percent(const char *str, int *idx);
static int s21_is_digit_in_base(char c, int base);
static int s21_digit_value(char c);
static void s21_skip_whitespaces(const char **ptr, int *consumed,
                                 int max_width);
static int s21_parse_sign(const char **ptr, int *consumed, int max_width);
static int s21_parse_unsigned_number(const char *str, int *idx,
                                     FormatParams params, int *sign,
                                     unsigned long long *res);
static int s21_convert_str_to_int(const char *str, int *idx,
                                  FormatParams params, long long *result);
static int s21_convert_str_to_unsigned(const char *str, int *idx,
                                       FormatParams params,
                                       unsigned long long *result);
static void s21_process_prefix(const char **ptr, int *consumed, int max_width,
                               FormatParams *params);
static int s21_parse_nan_inf(const char **ptr, int *consumed, int max_width,
                             long double *result, int sign);
static int s21_parse_exponent(const char **ptr, int *consumed, int max_width,
                              long double *res);
static int s21_convert_str_to_float(const char *str, int *idx,
                                    FormatParams params, long double *result);
static int s21_convert_str_to_char(const char *str, int *idx,
                                   FormatParams params, char *ch_ptr);
static int s21_convert_str_to_str(const char *str, int *idx,
                                  FormatParams params, char *str_buffer);
static int s21_convert_str_to_pointer(const char *str, int *idx,
                                      FormatParams params, void **result);
// ==================== ОСНОВНАЯ ФУНКЦИЯ ====================
int s21_sscanf(const char *str, const char *format, ...) {
  if (!str || !format) return -1;

  va_list args;
  va_start(args, format);
  int idx = 0;
  int assignments = 0;
  int error = PARSE_SUCCESS;

  for (int i = 0; format[i] && !error;) {
    if (format[i] == '%') {
      if (format[++i] == '\0') error = PARSE_ERROR;

      FormatParams params = s21_init_format_params();
      if (!error) error = s21_parse_format_ssc(format, &i, &params);
      if (!error)
        error = s21_process_format_conversion(str, &idx, params, args);
      // Не увеличиваем assignments для %n и %%
      if (!error && !params.ssc_ignore) {
        if ((params.type < TYPE_N_INT || params.type > TYPE_N_LONGLONG) &&
            params.type != TYPE_PERCENT) {
          assignments++;
        }
      }
      if (error == PARSE_ERROR_INVALID_DATA) error = PARSE_SUCCESS;
    } else if (isspace(format[i])) {
      while (isspace(str[idx])) idx++;
      i++;
    } else {
      if (str[idx] != format[i])
        error = PARSE_ERROR;
      else
        idx++, i++;
    }
  }

  va_end(args);

  if (error == PARSE_ERROR_END_OF_STRING && assignments == 0) {
    return -1;
  } else if (error == PARSE_ERROR_INVALID_DATA ||
             error == PARSE_ERROR_END_OF_STRING) {
    return assignments;
  } else if (error && assignments == 0) {
    return -1;
  } else {
    return assignments;
  }
}

// ==================== ОБРАБОТКА ТИПОВ ДАННЫХ ====================
static int s21_process_format_conversion(const char *str, int *str_idx,
                                         FormatParams params, va_list args) {
  int error = PARSE_SUCCESS;

  if (params.type <= TYPE_LONGLONG)
    error = s21_handle_integer(str, str_idx, params, args);
  else if (params.type <= TYPE_ULONGLONG)
    error = s21_handle_unsigned(str, str_idx, params, args);
  else if (params.type <= TYPE_LONGDOUBLE)
    error = s21_handle_float(str, str_idx, params, args);
  else if (params.type == TYPE_CHAR)
    error = s21_handle_char(str, str_idx, params, args);
  else if (params.type == TYPE_STRING)
    error = s21_handle_string(str, str_idx, params, args);
  else if (params.type == TYPE_POINTER)
    error = s21_handle_pointer(str, str_idx, params, args);
  else if (params.type == TYPE_PERCENT)
    error = s21_handle_percent(str, str_idx);
  else if (params.type <= TYPE_N_LONGLONG)
    s21_handle_count(str_idx, params, args);

  return error;
}

static int s21_handle_integer(const char *str, int *idx, FormatParams params,
                              va_list args) {
  long long int_buf;
  int error = s21_convert_str_to_int(str, idx, params, &int_buf);
  if (!params.ssc_ignore && !error) {
    if (params.type == TYPE_INT) {
      int *val_ptr = va_arg(args, int *);
      *val_ptr = (int)int_buf;
    } else if (params.type == TYPE_SHORT) {
      short *val_ptr = va_arg(args, short *);
      *val_ptr = (short)int_buf;
    } else if (params.type == TYPE_SCHAR) {
      signed char *val_ptr = va_arg(args, signed char *);
      *val_ptr = (signed char)int_buf;
    } else if (params.type == TYPE_LONG) {
      long *val_ptr = va_arg(args, long *);
      *val_ptr = (long)int_buf;
    } else if (params.type == TYPE_LONGLONG) {
      long long *val_ptr = va_arg(args, long long *);
      *val_ptr = (long long)int_buf;
    }
  }
  return error;
}

static int s21_handle_unsigned(const char *str, int *idx, FormatParams params,
                               va_list args) {
  unsigned long long uint_buf;
  int error = s21_convert_str_to_unsigned(str, idx, params, &uint_buf);
  if (!params.ssc_ignore && !error) {
    if (params.type == TYPE_UINT) {
      unsigned int *val_ptr = va_arg(args, unsigned int *);
      *val_ptr = (unsigned int)uint_buf;
    } else if (params.type == TYPE_USHORT) {
      unsigned short *val_ptr = va_arg(args, unsigned short *);
      *val_ptr = (unsigned short)uint_buf;
    } else if (params.type == TYPE_UCHAR) {
      unsigned char *val_ptr = va_arg(args, unsigned char *);
      *val_ptr = (unsigned char)uint_buf;
    } else if (params.type == TYPE_ULONG) {
      unsigned long *val_ptr = va_arg(args, unsigned long *);
      *val_ptr = (unsigned long)uint_buf;
    } else if (params.type == TYPE_ULONGLONG) {
      unsigned long long *val_ptr = va_arg(args, unsigned long long *);
      *val_ptr = (unsigned long long)uint_buf;
    }
  }
  return error;
}

static int s21_handle_float(const char *str, int *idx, FormatParams params,
                            va_list args) {
  long double float_buf;
  int error = s21_convert_str_to_float(str, idx, params, &float_buf);
  if (!params.ssc_ignore && !error) {
    if (params.type == TYPE_FLOAT) {
      float *val_ptr = va_arg(args, float *);
      *val_ptr = (float)float_buf;
    } else if (params.type == TYPE_DOUBLE) {
      double *val_ptr = va_arg(args, double *);
      *val_ptr = (double)float_buf;
    } else if (params.type == TYPE_LONGDOUBLE) {
      long double *val_ptr = va_arg(args, long double *);
      *val_ptr = (long double)float_buf;
    }
  }
  return error;
}

static int s21_handle_char(const char *str, int *idx, FormatParams params,
                           va_list args) {
  char *ch_ptr = S21_NULL;
  if (!params.ssc_ignore) {
    ch_ptr = va_arg(args, char *);
  }
  return s21_convert_str_to_char(str, idx, params, ch_ptr);
}

static int s21_handle_string(const char *str, int *idx, FormatParams params,
                             va_list args) {
  char *s_ptr = S21_NULL;
  if (!params.ssc_ignore) {
    s_ptr = va_arg(args, char *);
  }
  return s21_convert_str_to_str(str, idx, params, s_ptr);
}

static int s21_handle_pointer(const char *str, int *idx, FormatParams params,
                              va_list args) {
  void *ptr_buf;
  int error = s21_convert_str_to_pointer(str, idx, params, &ptr_buf);
  if (!params.ssc_ignore && !error) {
    void **val_ptr = va_arg(args, void **);
    *val_ptr = ptr_buf;
  }
  return error;
}

static void s21_handle_count(int *idx, FormatParams params, va_list args) {
  if (!params.ssc_ignore) {
    if (params.type == TYPE_N_INT) {
      int *count_ptr = va_arg(args, int *);
      *count_ptr = *idx;
    } else if (params.type == TYPE_N_SHORT) {
      short *count_ptr = va_arg(args, short *);
      *count_ptr = (short)*idx;
    } else if (params.type == TYPE_N_SCHAR) {
      signed char *count_ptr = va_arg(args, signed char *);
      *count_ptr = (signed char)*idx;
    } else if (params.type == TYPE_N_LONG) {
      long *count_ptr = va_arg(args, long *);
      *count_ptr = (long)*idx;
    } else if (params.type == TYPE_N_LONGLONG) {
      long long *count_ptr = va_arg(args, long long *);
      *count_ptr = (long long)*idx;
    }
  }
}

static int s21_handle_percent(const char *str, int *idx) {
  if (str[*idx] == '%') {
    (*idx)++;
    return PARSE_SUCCESS;
  }
  return PARSE_ERROR;
}

// ============== ВСПОМОГАТЕЛЬНЫЕ ФУНКЦИИ ДЛЯ СИСТЕМ СЧИСЛЕНИЯ ==============
static int s21_is_digit_in_base(char c, int base) {
  if (base == 10) return isdigit(c);
  if (base == 8) return c >= '0' && c <= '7';
  if (base == 16) return isxdigit(c);
  return 0;
}

static int s21_digit_value(char c) {
  if (c >= '0' && c <= '9') return c - '0';
  if (c >= 'a' && c <= 'f') return c - 'a' + 10;
  if (c >= 'A' && c <= 'F') return c - 'A' + 10;
  return 0;
}

static void s21_skip_whitespaces(const char **ptr, int *consumed,
                                 int max_width) {
  while (*consumed < max_width && (**ptr == ' ' || **ptr == '\t')) {
    (*ptr)++;
    (*consumed)++;
  }
}

static int s21_parse_sign(const char **ptr, int *consumed, int max_width) {
  int sign = 1;
  if (*consumed < max_width && (**ptr == '-' || **ptr == '+')) {
    if (**ptr == '-') sign = -1;
    (*ptr)++;
    (*consumed)++;
  }
  return sign;
}

// ================ ВСПОМОГАТЕЛЬНАЯ ФУНКЦИЯ ДЛЯ ЧТЕНИЯ ЧИСЕЛ ================
static int s21_parse_unsigned_number(const char *str, int *idx,
                                     FormatParams params, int *sign,
                                     unsigned long long *res) {
  if (str == S21_NULL || idx == S21_NULL || sign == S21_NULL || res == S21_NULL)
    return PARSE_ERROR;

  int max_width = params.width_type ? params.width_value : INT_MAX;
  int consumed = 0;
  const char *start = str + *idx;
  const char *ptr = start;
  int error = PARSE_SUCCESS;

  s21_skip_whitespaces(&ptr, &consumed, max_width);
  if (*ptr == '\0') return PARSE_ERROR_END_OF_STRING;

  *sign = s21_parse_sign(&ptr, &consumed, max_width);
  if (*ptr == '\0') return PARSE_ERROR_END_OF_STRING;

  if (params.specifier == 'i' || tolower(params.specifier) == 'x') {
    s21_process_prefix(&ptr, &consumed, max_width, &params);
    if (*ptr == '\0') return PARSE_ERROR_END_OF_STRING;
  }

  if (!s21_is_digit_in_base(*ptr, params.base)) {
    return PARSE_ERROR_INVALID_DATA;
  }

  *res = 0;
  while (consumed < max_width && *ptr != '\0' &&
         s21_is_digit_in_base(*ptr, params.base)) {
    if (*res > ULLONG_MAX / params.base) {
      *res = ULLONG_MAX;
    } else {
      *res *= params.base;
    }

    int digit_val = s21_digit_value(*ptr);
    if (*res > ULLONG_MAX - digit_val) {
      *res = ULLONG_MAX;
    } else {
      *res += digit_val;
    }

    ptr++;
    consumed++;
  }

  *idx += (ptr - start);
  return error;
}

// ==================== КОНВЕРТАЦИЯ ЦЕЛЫХ ЧИСЕЛ ====================
static int s21_convert_str_to_int(const char *str, int *idx,
                                  FormatParams params, long long *result) {
  int sign;
  unsigned long long res;
  int error = PARSE_SUCCESS;
  error = s21_parse_unsigned_number(str, idx, params, &sign, &res);

  if (!error) {
    if (sign == -1) {
      if (res > (unsigned long long)LLONG_MAX + 1) {
        *result = LLONG_MIN;
      } else {
        *result = -((long long)res);
      }
    } else {
      if (res > LLONG_MAX) {
        *result = LLONG_MAX;
      } else {
        *result = (long long)res;
      }
    }
  }

  return error;
}

// ==================== КОНВЕРТАЦИЯ БЕЗЗНАКОВЫХ ЧИСЕЛ ====================
static int s21_convert_str_to_unsigned(const char *str, int *idx,
                                       FormatParams params,
                                       unsigned long long *result) {
  int sign;
  unsigned long long res;
  int error = PARSE_SUCCESS;
  error = s21_parse_unsigned_number(str, idx, params, &sign, &res);

  if (!error) {
    if (sign == -1) {
      if (res == 0) {
        *result = 0;
      } else {
        *result = ULLONG_MAX - res + 1;
      }
    } else {
      *result = res;
    }
  }
  return error;
}

// ================== ОБРАБОТКА ПРЕФИКСОВ СИСТЕМ СЧИСЛЕНИЯ ==================
static void s21_process_prefix(const char **ptr, int *consumed, int max_width,
                               FormatParams *params) {
  if (params->specifier == 'i') {
    if (*consumed + 2 <= max_width && (*ptr)[0] == '0' &&
        tolower((*ptr)[1]) == 'x') {
      if (isxdigit((*ptr)[2])) {
        params->base = 16;
        *ptr += 2;
        *consumed += 2;
      }
    } else if (*consumed + 1 <= max_width && (*ptr)[0] == '0') {
      if (isdigit((*ptr)[1]) && (*ptr)[1] != '8' && (*ptr)[1] != '9') {
        params->base = 8;
        *ptr += 1;
        *consumed += 1;
      }
    }
  } else if (tolower(params->specifier) == 'x') {
    if (*consumed + 2 <= max_width && (*ptr)[0] == '0' &&
        tolower((*ptr)[1]) == 'x' && isxdigit((*ptr)[2])) {
      *ptr += 2;
      *consumed += 2;
    }
  }
}

// ==================== ВСПОМОГАТЕЛЬНЫЕ ФУНКЦИИ ДЛЯ FLOAT ====================
static int s21_parse_nan_inf(const char **ptr, int *consumed, int max_width,
                             long double *result, int sign) {
  const char *p = *ptr;
  int c = *consumed;

  if (c + 2 <= max_width && (p[0] == 'n' || p[0] == 'N') &&
      (p[1] == 'a' || p[1] == 'A') && (p[2] == 'n' || p[2] == 'N')) {
    *result = sign * NAN;
    *ptr += 3;
    *consumed += 3;
    return 1;
  }

  if (c + 2 <= max_width && (p[0] == 'i' || p[0] == 'I') &&
      (p[1] == 'n' || p[1] == 'N') && (p[2] == 'f' || p[2] == 'F')) {
    p += 3;
    c += 3;

    if (c + 4 <= max_width && (p[0] == 'i' || p[0] == 'I') &&
        (p[1] == 'n' || p[1] == 'N') && (p[2] == 'i' || p[2] == 'I') &&
        (p[3] == 't' || p[3] == 'T') && (p[4] == 'y' || p[4] == 'Y')) {
      p += 5;
      c += 5;
    }

    *result = sign * INFINITY;
    *ptr = p;
    *consumed = c;
    return 1;
  }

  return 0;
}

static int s21_parse_exponent(const char **ptr, int *consumed, int max_width,
                              long double *res) {
  if (**ptr != 'e' && **ptr != 'E') return 0;

  (*ptr)++;
  (*consumed)++;
  if (*consumed >= max_width || **ptr == '\0') return 0;

  int exp_sign = 1;
  if (**ptr == '-' || **ptr == '+') {
    if (**ptr == '-') exp_sign = -1;
    (*ptr)++;
    (*consumed)++;
    if (*consumed >= max_width || **ptr == '\0') return 0;
  }

  int exponent = 0;
  int exp_digits = 0;
  while (*consumed < max_width && **ptr != '\0' && isdigit(**ptr)) {
    exponent = exponent * 10 + (**ptr - '0');
    (*ptr)++;
    (*consumed)++;
    exp_digits = 1;
  }

  if (exp_digits) {
    long double exp_base = (exp_sign == 1) ? 10.0L : 0.1L;
    for (int i = 0; i < exponent; i++) {
      *res *= exp_base;
    }
  }

  return 1;
}

// ==================== КОНВЕРТАЦИЯ ДРОБНЫХ ЧИСЕЛ ====================
static int s21_convert_str_to_float(const char *str, int *idx,
                                    FormatParams params, long double *result) {
  if (str == S21_NULL || idx == S21_NULL || result == S21_NULL)
    return PARSE_ERROR;

  int max_width = params.width_type ? params.width_value : INT_MAX;
  int consumed = 0;
  const char *ptr = str + *idx;
  long double res = 0.0L;
  int digits_found = 0;

  s21_skip_whitespaces(&ptr, &consumed, max_width);
  if (*ptr == '\0') return PARSE_ERROR_END_OF_STRING;

  int sign = s21_parse_sign(&ptr, &consumed, max_width);
  if (*ptr == '\0') return PARSE_ERROR_END_OF_STRING;

  long double special_value;
  if (s21_parse_nan_inf(&ptr, &consumed, max_width, &special_value, sign)) {
    *result = special_value;
    *idx += consumed;
    return PARSE_SUCCESS;
  }

  while (consumed < max_width && *ptr != '\0' && isdigit(*ptr)) {
    res = res * 10.0L + (*ptr - '0');
    ptr++;
    consumed++;
    digits_found = 1;
  }

  if (consumed < max_width && *ptr == '.') {
    ptr++;
    consumed++;
    long double fraction = 0.1L;

    while (consumed < max_width && *ptr != '\0' && isdigit(*ptr)) {
      res += (*ptr - '0') * fraction;
      fraction *= 0.1L;
      ptr++;
      consumed++;
      digits_found = 1;
    }
  }

  if (digits_found && consumed < max_width && (*ptr == 'e' || *ptr == 'E')) {
    s21_parse_exponent(&ptr, &consumed, max_width, &res);
  }

  if (!digits_found) return PARSE_ERROR_INVALID_DATA;

  *result = sign * res;
  *idx += consumed;
  return PARSE_SUCCESS;
}

// ==================== ОБРАБОТКА СИМВОЛОВ ====================
static int s21_convert_str_to_char(const char *str, int *idx,
                                   FormatParams params, char *ch_ptr) {
  if (str == S21_NULL || idx == S21_NULL) return PARSE_ERROR;
  if (str[*idx] == '\0') return PARSE_ERROR_END_OF_STRING;

  int width = params.width_type ? params.width_value : 1;
  int i = 0;

  while (i < width && str[*idx + i] != '\0') {
    if (ch_ptr != S21_NULL) {
      ch_ptr[i] = str[*idx + i];
    }
    i++;
  }

  *idx += i;
  return PARSE_SUCCESS;
}

// ==================== ОБРАБОТКА СТРОК ====================
static int s21_convert_str_to_str(const char *str, int *idx,
                                  FormatParams params, char *str_buffer) {
  if (str == S21_NULL || idx == S21_NULL) return PARSE_ERROR;

  while (str[*idx] == ' ') (*idx)++;

  if (str[*idx] == '\0') {
    if (str_buffer != S21_NULL) str_buffer[0] = '\0';
    return PARSE_ERROR_END_OF_STRING;
  }

  int start = *idx;
  int count = 0;
  int max_chars = params.width_type ? params.width_value : INT_MAX;

  while (str[*idx] != '\0' && str[*idx] != ' ' && count < max_chars) {
    (*idx)++;
    count++;
  }

  if (str_buffer != S21_NULL) {
    int length = *idx - start;
    if (length > 0) {
      s21_strncpy(str_buffer, str + start, length);
      str_buffer[length] = '\0';
    } else {
      str_buffer[0] = '\0';
    }
  }

  return PARSE_SUCCESS;
}

// ==================== ОБРАБОТКА УКАЗАТЕЛЕЙ ====================
static int s21_convert_str_to_pointer(const char *str, int *idx,
                                      FormatParams params, void **result) {
  if (str == S21_NULL || idx == S21_NULL || result == S21_NULL)
    return PARSE_ERROR;
  int max_width = params.width_type ? params.width_value : INT_MAX;
  int consumed = 0;
  const char *ptr = str + *idx;
  unsigned long long res = 0;
  int digits_found = 0;

  s21_skip_whitespaces(&ptr, &consumed, max_width);
  if (*ptr == '\0') return PARSE_ERROR_END_OF_STRING;

  if (consumed + 4 <= max_width && s21_strncmp(ptr, "(nil)", 5) == 0) {
    *result = S21_NULL;
    *idx += consumed + 5;
    return PARSE_SUCCESS;
  }

  if (consumed + 2 <= max_width && ptr[0] == '0' &&
      (ptr[1] == 'x' || ptr[1] == 'X')) {
    ptr += 2;
    consumed += 2;
  }

  while (consumed < max_width && *ptr != '\0' && isxdigit(*ptr)) {
    int digit_val = s21_digit_value(*ptr);
    res = res * 16 + digit_val;
    ptr++;
    consumed++;
    digits_found = 1;
  }

  if (!digits_found) return PARSE_ERROR_INVALID_DATA;

  *result = (void *)(uintptr_t)res;
  *idx += consumed;
  return PARSE_SUCCESS;
}