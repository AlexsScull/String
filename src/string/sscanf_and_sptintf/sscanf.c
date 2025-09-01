#include "../include/s21_string.h"
#include "parse.h"

static long long convert_str_to_int(const char *str, int *idx,
                                    FormatParams params) {
  int res = 0;
  int sign = 1;

  while (*str == ' ' || *str == '\t') {
    str++;
  }
  if (*str == '-') {
    sign = -1;
    str++;
  } else if (*str == '+') {
    str++;
  }
  while (*str && isdigit(*str)) {
    res = res * 10 + (*str - '0');
    str++;
  }
  *idx++;
  return (res * sign);
}

static unsigned long long convert_str_to_unsigned(const char *str, int *idx,
                                                  FormatParams params) {
  int res = 0;

  while (*str == ' ' || *str == '\t' || *str == '-' || *str == '+') {
    str++;
  }
  while (*str && isdigit(*str)) {
    res = res * 10 + (*str - '0');
    str++;
  }
  *idx++;
  return (res);
}

static long double convert_str_to_float(const char *str, int *idx,
                                        FormatParams params) {
  float res = 0.0f;
  float sign = 1.0f;
  float fraction = 0.1f;
  int after_dot = 0;

  while (*str == ' ' || *str == '\t') {
    str++;
  }

  if (*str == '-') {
    sign = -1.0f;
    str++;
  } else if (*str == '+') {
    str++;
  }

  while (*str) {
    if (*str == '.') {
      if (after_dot) break;
      after_dot = 1;
      str++;
      continue;
    }
    if (!isdigit(*str)) break;
    if (!after_dot) {
      res = res * 10.0f + (*str - '0');
    } else {
      res = res + (*str - '0') * fraction;
      fraction *= 0.1f;
    }
    str++;
  }
  *idx++;
  return (sign * res);
}

static char convert_str_to_char(const char *str, int *idx,
                                FormatParams params) {
  char res = '\0';
  while (*str == ' ' || *str == '\t') {
    str++;
  }

  if (*str != '\0') {
    res = *str;
    str++;
    while (*str == ' ' || *str == '\t') {
      str++;
    }
    if (*str != '\0') {
      res = '\0';
    }
  }

  return res;
}

static char convert_str_to_wchar(const char *str, int *idx,
                                 FormatParams params) {
  wchar_t res = L'\0';
  while (*str == L' ' || *str == L'\t') {
    str++;
  }

  if (*str != L'\0') {
    res = *str;
    str++;
    while (*str == L' ' || *str == L'\t') {
      str++;
    }
    if (*str != L'\0') {
      res = L'\0';
    }
  }

  return res;
}

static long long convert_str_to_count(const char *str, int *idx,
                                      FormatParams params) {
  long long result = 0;

  if (str != NULL) {
    while (*str == ' ' || *str == '\t') {
      str++;
    }

    const char *end = str;
    while (*end != '\0') {
      end++;
    }

    while (end > str && (*(end - 1) == ' ' || *(end - 1) == '\t')) {
      end--;
    }

    result = (long long)(end - str);
    return result;
  }
}

static void handle_integer(const char *str, int *idx, FormatParams params,
                           va_list args) {
  if (params.type == TYPE_INT) {
    int *val_ptr = va_arg(args, int *);
    *val_ptr = (int)convert_str_to_int(str, idx, params);
  } else if (params.type == TYPE_SHORT) {
    short *val_ptr = va_arg(args, short *);
    *val_ptr = (short)convert_str_to_int(str, idx, params);
  } else if (params.type == TYPE_SCHAR) {
    signed char *val_ptr = va_arg(args, signed char *);
    *val_ptr = (signed char)convert_str_to_int(str, idx, params);
  } else if (params.type == TYPE_LONG) {
    long *val_ptr = va_arg(args, long *);
    *val_ptr = (long)convert_str_to_int(str, idx, params);
  } else if (params.type == TYPE_LONGLONG) {
    long long *val_ptr = va_arg(args, long long *);
    *val_ptr = (long long)convert_str_to_int(str, idx, params);
  }
}

static void handle_unsigned(const char *str, int *idx, FormatParams params,
                            va_list args) {
  if (params.type == TYPE_UINT) {
    unsigned int *val_ptr = va_arg(args, unsigned int *);
    *val_ptr = (unsigned int)convert_str_to_unsigned(str, idx, params);
  } else if (params.type == TYPE_USHORT) {
    unsigned short *val_ptr = va_arg(args, unsigned short *);
    *val_ptr = (unsigned short)convert_str_to_unsigned(str, idx, params);
  } else if (params.type == TYPE_UCHAR) {
    unsigned char *val_ptr = va_arg(args, unsigned char *);
    *val_ptr = (unsigned char)convert_str_to_unsigned(str, idx, params);
  } else if (params.type == TYPE_ULONG) {
    unsigned long *val_ptr = va_arg(args, unsigned long *);
    *val_ptr = (unsigned long)convert_str_to_unsigned(str, idx, params);
  } else if (params.type == TYPE_ULONGLONG) {
    unsigned long long *val_ptr = va_arg(args, unsigned long long *);
    *val_ptr = (unsigned long long)convert_str_to_unsigned(str, idx, params);
  }
}

static void handle_float(const char *str, int *idx, FormatParams params,
                         va_list args) {
  if (params.type == TYPE_FLOAT) {
    float *val_ptr = va_arg(args, float *);
    *val_ptr = (float)convert_str_to_float(str, idx, params);
  } else if (params.type == TYPE_LONGDOUBLE) {
    long double *val_ptr = va_arg(args, long double *);
    *val_ptr = (long double)convert_str_to_float(str, idx, params);
  }
}

static void handle_char(const char *str, int *idx, FormatParams params,
                        va_list args) {
  if (params.type == TYPE_CHAR) {
    char *c_ptr = va_arg(args, char *);
    *c_ptr = (char)convert_str_to_char(str, idx, params);
  }
}

static int handle_wchar(const char *str, int *idx, FormatParams params,
                        va_list args) {
  if (params.type == TYPE_WCHAR) {
    wchar_t *wc_ptr = va_arg(args, wchar_t *);
    *wc_ptr = (char)convert_str_to_wchar(str, idx, params);
  }
  return 0;
}

static void handle_string(const char *str, int *idx, FormatParams params,
                          va_list args) {
  if (params.type == TYPE_STRING) {
    char *s_ptr = va_arg(args, char *);
    // *s_ptr = (char)convert_str_to_st(str, idx, params);
  }
}

static int handle_wstring(const char *str, int *idx, FormatParams params,
                          va_list args) {
  if (params.type == TYPE_WSTRING) {
    wchar_t *ws_ptr = va_arg(args, wchar_t *);
    // ...
  }
  return 0;
}

static void handle_pointer(const char *str, int *idx, FormatParams params,
                           va_list args) {
  if (params.type == TYPE_POINTER) {
    void **ptr_ptr = va_arg(args, void **);
    // ...
  }
}

static void handle_count(const char *str, int *idx, FormatParams params,
                         va_list args) {
  if (params.type == TYPE_N_INT) {
    int *count_ptr = va_arg(args, int *);
    *count_ptr = (int)convert_str_to_count(str, idx, params);
  } else if (params.type == TYPE_N_SHORT) {
    short *count_ptr = va_arg(args, short *);
    *count_ptr = (short)convert_str_to_count(str, idx, params);
  } else if (params.type == TYPE_N_SCHAR) {
    signed char *count_ptr = va_arg(args, signed char *);
    *count_ptr = (signed char)convert_str_to_count(str, idx, params);
  } else if (params.type == TYPE_N_LONG) {
    long *count_ptr = va_arg(args, long *);
    *count_ptr = (long)convert_str_to_count(str, idx, params);
  } else if (params.type == TYPE_N_LONGLONG) {
    long long *count_ptr = va_arg(args, long long *);
    *count_ptr = (long long)convert_str_to_count(str, idx, params);
  }
}

static void handle_percent(const char *str, int *idx) {
  // ???
}

static bool process_format_conversion(const char *str, int *str_idx,
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

int s21_sscanf(const char *str, const char *format, ...) {
  if (!str || !format) return -1;

  va_list args;
  va_start(args, format);
  int idx = 0;
  bool error = false;

  for (int i = 0; format[i] && !error;) {
    if (format[i] == '%') {
      if (format[++i] == '\0') error = true;

      FormatParams params = init_format_params();
      if (!error) error = parse_format_ssc(format, &i, &params);
      if (!error) error = process_format_conversion(str, &idx, params, args);
    } else {
      if (str[idx] != format[i])
        error = true;
      else
        idx++, i++;
    }
  }

  va_end(args);
  return error ? -1 : idx;
}