#include "../include/s21_string.h"
#include "parse.h"

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

static void handle_integer(const char *str, int *idx, FormatParams params,
                           va_list args) {
  if (params.type == TYPE_INT) {
    int *val_ptr = va_arg(args, int *);
    // *val_ptr = (int)fun(...)
  } else if (params.type == TYPE_SHORT) {
    short *val_ptr = va_arg(args, short *);
    // ...
  } else if (params.type == TYPE_SCHAR) {
    signed char *val_ptr = va_arg(args, signed char *);
    // ...
  } else if (params.type == TYPE_LONG) {
    long *val_ptr = va_arg(args, long *);
    // ...
  } else if (params.type == TYPE_LONGLONG) {
    long long *val_ptr = va_arg(args, long long *);
    // ...
  }
}

static void handle_unsigned(const char *str, int *idx, FormatParams params,
                            va_list args) {
  if (params.type == TYPE_UINT) {
    unsigned int *val_ptr = va_arg(args, unsigned int *);
    // ...
  } else if (params.type == TYPE_USHORT) {
    unsigned short *val_ptr = va_arg(args, unsigned short *);
    // ...
  } else if (params.type == TYPE_UCHAR) {
    unsigned char *val_ptr = va_arg(args, unsigned char *);
    // ...
  } else if (params.type == TYPE_ULONG) {
    unsigned long *val_ptr = va_arg(args, unsigned long *);
    // ...
  } else if (params.type == TYPE_ULONGLONG) {
    unsigned long long *val_ptr = va_arg(args, unsigned long long *);
    // ...
  }
}

static void handle_float(const char *str, int *idx, FormatParams params,
                         va_list args) {
  if (params.type == TYPE_FLOAT) {
    float *val_ptr = va_arg(args, float *);
    // ...
  } else if (params.type == TYPE_LONGDOUBLE) {
    long double *val_ptr = va_arg(args, long double *);
    // ...
  }
}

static void handle_char(const char *str, int *idx, FormatParams params,
                        va_list args) {
  if (params.type == TYPE_CHAR) {
    char *c_ptr = va_arg(args, char *);
    // ...
  }
}

static int handle_wchar(const char *str, int *idx, FormatParams params,
                        va_list args) {
  if (params.type == TYPE_WCHAR) {
    wchar_t *wc_ptr = va_arg(args, wchar_t *);
    // ...
  }
  return 0;
}

static void handle_string(const char *str, int *idx, FormatParams params,
                          va_list args) {
  if (params.type == TYPE_STRING) {
    char *s_ptr = va_arg(args, char *);
    // ...
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
    *count_ptr = *idx;
  } else if (params.type == TYPE_N_SHORT) {
    short *count_ptr = va_arg(args, short *);
    *count_ptr = *idx;
  } else if (params.type == TYPE_N_SCHAR) {
    signed char *count_ptr = va_arg(args, signed char *);
    *count_ptr = *idx;
  } else if (params.type == TYPE_N_LONG) {
    long *count_ptr = va_arg(args, long *);
    *count_ptr = *idx;
  } else if (params.type == TYPE_N_LONGLONG) {
    long long *count_ptr = va_arg(args, long long *);
    *count_ptr = *idx;
  }
}

static void handle_percent(char *str, int *idx) {
  // ???
}