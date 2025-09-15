#include <ctype.h>
#include <stdlib.h>

#include "s21_string.h"
#include "string_parser.h"

// Функции парсинга для sprintf
static void s21_parse_flags_spr(const char *format, int *i,
                                FormatParams *params);
static void s21_parse_width_spr(const char *format, int *i, FormatParams *p,
                                va_list *args);
static void s21_parse_precision_spr(const char *format, int *i, FormatParams *p,
                                    va_list *args);

// Функции парсинга для sscanf
static void s21_parse_width_ssc(const char *format, int *i, FormatParams *p);

// Общие функции парсинга
static int s21_parse_number(const char *format, int *i);
static void s21_parse_numeric_value_spr(const char *format, int *i,
                                        va_list *args, bool *type_flag,
                                        int *value);
static void s21_parse_numeric_value_ssc(const char *format, int *i,
                                        bool *type_flag, int *value,
                                        bool *ignore);
static void s21_parse_modifier(const char *format, int *idx,
                               FormatParams *params);
static int s21_parse_specifier(const char *format, int *i,
                               FormatParams *params);

// Обработчики спецификаторов
static void s21_handle_di_specifier(FormatParams *params);
static void s21_handle_u_specifier(FormatParams *params);
static void s21_handle_o_specifier(FormatParams *params);
static void s21_handle_x_specifier(FormatParams *params);
static void s21_handle_f_specifier(FormatParams *params);
static void s21_handle_e_specifier(FormatParams *params);
static void s21_handle_g_specifier(FormatParams *params);
static void s21_handle_c_specifier(FormatParams *params);
static void s21_handle_s_specifier(FormatParams *params);
static void s21_handle_p_specifier(FormatParams *params);
static void s21_handle_percent_specifier(FormatParams *params);
static void s21_handle_n_specifier(FormatParams *params);

// Функции установки типа
static void s21_set_signed_type(FormatParams *params);
static void s21_set_unsigned_type(FormatParams *params);
static void s21_set_float_type(FormatParams *params);
static void s21_set_n_type(FormatParams *params);

typedef struct {
  const char symbol;
  bool *flag;
} FlagMapping;

typedef struct {
  const char *str;
  int mod;
} ModifierMapping;

typedef struct {
  char specifier;
  void (*handler)(FormatParams *);
} SpecifierMapping;

// Статический массив для модификаторов
static const ModifierMapping modifiers[] = {{"hh", LENGTH_HH},
                                            {"ll", LENGTH_LL},
                                            {"h", LENGTH_H},
                                            {"l", LENGTH_L},
                                            {"L", LENGTH_CAP_L}};

// Статический массив для спецификаторов
static const SpecifierMapping specifier_mappings[] = {
    {'d', s21_handle_di_specifier}, {'i', s21_handle_di_specifier},
    {'u', s21_handle_u_specifier},  {'o', s21_handle_o_specifier},
    {'x', s21_handle_x_specifier},  {'f', s21_handle_f_specifier},
    {'e', s21_handle_e_specifier},  {'g', s21_handle_g_specifier},
    {'c', s21_handle_c_specifier},  {'s', s21_handle_s_specifier},
    {'p', s21_handle_p_specifier},  {'%', s21_handle_percent_specifier},
    {'n', s21_handle_n_specifier}};

FormatParams s21_init_format_params() {
  FormatParams params = {.flag_minus = false,
                         .flag_plus = false,
                         .flag_space = false,
                         .flag_hash = false,
                         .flag_zero = false,
                         .width_type = false,
                         .width_value = -1,
                         .ssc_ignore = false,
                         .precision_type = false,
                         .precision_value = -1,
                         .modifier = LENGTH_NULL,
                         .specifier = -1,
                         .type = -1,
                         .uppercase = false,
                         .base = BaseDecimal,
                         .spec_char = -1};
  return params;
}

int s21_parse_format_spr(const char *format, int *i, FormatParams *params,
                         va_list *args) {
  if (!format || !i || !params) return PARSE_ERROR_INVALID_SPEC;

  int error = PARSE_SUCCESS;
  s21_parse_flags_spr(format, i, params);
  s21_parse_width_spr(format, i, params, args);
  s21_parse_precision_spr(format, i, params, args);
  s21_parse_modifier(format, i, params);
  error = s21_parse_specifier(format, i, params);
  return error;
}

int s21_parse_format_ssc(const char *format, int *i, FormatParams *params) {
  int error = PARSE_SUCCESS;
  s21_parse_width_ssc(format, i, params);
  s21_parse_modifier(format, i, params);
  error = s21_parse_specifier(format, i, params);
  return error;
}

static int s21_parse_number(const char *format, int *i) {
  int num = 0;
  while (isdigit(format[*i])) {
    num = num * BaseDecimal + (format[*i] - '0');
    (*i)++;
  }
  return num;
}

static void s21_parse_flags_spr(const char *format, int *i,
                                FormatParams *params) {
  FlagMapping mappings[] = {{'-', &params->flag_minus},
                            {'+', &params->flag_plus},
                            {' ', &params->flag_space},
                            {'#', &params->flag_hash},
                            {'0', &params->flag_zero}};

  bool continue_parsing = true;
  while (continue_parsing) {
    bool flag_found = false;

    for (s21_size_t j = 0; j < ARRAY_SIZE(mappings) && !flag_found; j++) {
      if (format[*i] == mappings[j].symbol && !(*mappings[j].flag)) {
        *mappings[j].flag = true;
        (*i)++;
        flag_found = true;
      }
    }
    continue_parsing = flag_found;
  }
}

static void s21_parse_numeric_value_spr(const char *format, int *i,
                                        va_list *args, bool *type_flag,
                                        int *value) {
  if (format[*i] == '*') {
    *type_flag = true;
    *value = abs(va_arg(*args, int));
    (*i)++;
  } else if (isdigit(format[*i])) {
    *type_flag = true;
    *value = s21_parse_number(format, i);
  }
}

static void s21_parse_numeric_value_ssc(const char *format, int *i,
                                        bool *type_flag, int *value,
                                        bool *ignore) {
  if (format[*i] == '*') {
    *ignore = true;
    (*i)++;
  } else if (isdigit(format[*i])) {
    *type_flag = true;
    *value = s21_parse_number(format, i);
  }
}

static void s21_parse_width_ssc(const char *format, int *i, FormatParams *p) {
  s21_parse_numeric_value_ssc(format, i, &p->width_type, &p->width_value,
                              &p->ssc_ignore);
}

static void s21_parse_width_spr(const char *format, int *i, FormatParams *p,
                                va_list *args) {
  s21_parse_numeric_value_spr(format, i, args, &p->width_type, &p->width_value);
}

static void s21_parse_precision_spr(const char *format, int *i, FormatParams *p,
                                    va_list *args) {
  if (format[*i] != '.') return;

  (*i)++;
  p->precision_type = true;  // При "%.[type]" точность по умолчанию -> 0
  s21_parse_numeric_value_spr(format, i, args, &p->precision_type,
                              &p->precision_value);
}

static void s21_parse_modifier(const char *format, int *idx,
                               FormatParams *params) {
  for (s21_size_t i = 0; i < ARRAY_SIZE(modifiers); i++) {
    s21_size_t len = s21_strlen(modifiers[i].str);
    if (s21_strncmp(format + *idx, modifiers[i].str, len) == 0) {
      params->modifier = modifiers[i].mod;
      *idx += len;
      return;
    }
  }
}

static int s21_parse_specifier(const char *format, int *i,
                               FormatParams *params) {
  if (format[*i] == '\0') return PARSE_ERROR_INVALID_SPEC;

  char original_spec = format[*i];
  params->specifier = original_spec;
  params->uppercase = isupper(original_spec);
  char spec = tolower(original_spec);

  bool found = false;
  for (s21_size_t idx = 0; idx < ARRAY_SIZE(specifier_mappings) && !found;
       idx++) {
    if (specifier_mappings[idx].specifier == spec) {
      specifier_mappings[idx].handler(params);
      found = true;
    }
  }

  (*i)++;

  return found ? PARSE_SUCCESS : PARSE_ERROR_END_OF_FORMAT;
}

static void s21_handle_di_specifier(FormatParams *params) {
  s21_set_signed_type(params);
  s21_reset_flags_for_u_integer(params);
}
static void s21_handle_u_specifier(FormatParams *params) {
  s21_set_unsigned_type(params);
  params->base = BaseDecimal;
  s21_reset_flags_for_u_integer(params);
}
static void s21_handle_o_specifier(FormatParams *params) {
  s21_set_unsigned_type(params);
  params->base = BaseOctal;
  s21_reset_flags_for_u_integer(params);
}
static void s21_handle_x_specifier(FormatParams *params) {
  s21_set_unsigned_type(params);
  params->base = BaseHexadecimal;
  s21_reset_flags_for_u_integer(params);
}
static void s21_handle_f_specifier(FormatParams *params) {
  s21_set_float_type(params);
  params->spec_char = CHAR_F;
}
static void s21_handle_e_specifier(FormatParams *params) {
  s21_set_float_type(params);
  params->spec_char = CHAR_E;
}
static void s21_handle_g_specifier(FormatParams *params) {
  s21_set_float_type(params);
  params->spec_char = CHAR_G;
}
static void s21_handle_c_specifier(FormatParams *params) {
  params->type = (params->modifier == LENGTH_L) ? TYPE_WCHAR : TYPE_CHAR;
  s21_reset_flags_for_char_string(params);
}
static void s21_handle_s_specifier(FormatParams *params) {
  params->type = (params->modifier == LENGTH_L) ? TYPE_WSTRING : TYPE_STRING;
  s21_reset_flags_for_char_string(params);
}
static void s21_handle_p_specifier(FormatParams *params) {
  params->type = TYPE_POINTER;
  params->base = BaseHexadecimal;
  s21_reset_flags_for_pointer(params);
}
static void s21_handle_percent_specifier(FormatParams *params) {
  params->type = TYPE_PERCENT;
}
static void s21_handle_n_specifier(FormatParams *params) {
  s21_set_n_type(params);
}

static void s21_set_signed_type(FormatParams *params) {
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
static void s21_set_unsigned_type(FormatParams *params) {
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
static void s21_set_float_type(FormatParams *params) {
  if (params->modifier == LENGTH_CAP_L)
    params->type = TYPE_LONGDOUBLE;
  else if (params->modifier == LENGTH_L)
    params->type = TYPE_DOUBLE;
  else
    params->type = TYPE_FLOAT;
}
static void s21_set_n_type(FormatParams *params) {
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

void s21_reset_flags_for_char_string(FormatParams *params) {
  params->flag_plus = false;
  params->flag_space = false;
  params->flag_zero = false;
  params->flag_hash = false;
}

void s21_reset_flags_for_u_integer(FormatParams *params) {
  if (params->base != BaseOctal && params->base != BaseHexadecimal)
    params->flag_hash = false;
}

void s21_reset_flags_for_pointer(FormatParams *params) {
  params->flag_plus = false;
  params->flag_space = false;
  params->flag_hash = false;
}

void s21_reset_flags_for_special(FormatParams *params) {
  params->flag_zero = false;
  params->flag_hash = false;
  params->precision_type = false;
  params->precision_value = -1;
}

void s21_reset_flags_for_zero(FormatParams *params) {
  params->flag_hash = false;
}