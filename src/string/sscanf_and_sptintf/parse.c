#include "parse.h"

#include <ctype.h>
#include <stdlib.h>
#include <string.h>

#include "parse.h"

// Статический массив для модификаторов
static const ModifierMapping modifiers[] = {{"hh", LENGTH_HH},
                                            {"ll", LENGTH_LL},
                                            {"h", LENGTH_H},
                                            {"l", LENGTH_L},
                                            {"L", LENGTH_CAP_L}};

// Статический массив для спецификаторов
static const SpecifierMapping specifier_mappings[] = {
    {'d', handle_di_specifier}, {'i', handle_di_specifier},
    {'u', handle_u_specifier},  {'o', handle_o_specifier},
    {'x', handle_x_specifier},  {'f', handle_f_specifier},
    {'e', handle_e_specifier},  {'g', handle_g_specifier},
    {'c', handle_c_specifier},  {'s', handle_s_specifier},
    {'p', handle_p_specifier},  {'%', handle_percent_specifier},
    {'n', handle_n_specifier}};

FormatParams init_format_params() {
  FormatParams params = {.flag_minus = false,
                         .flag_plus = false,
                         .flag_space = false,
                         .flag_hash = false,
                         .flag_zero = false,
                         .width_type = false,
                         .width_value = 0,
                         .precision_type = false,
                         .precision_value = 0,
                         .modifier = LENGTH_NULL,
                         .specifier = -1,
                         .type = -1,
                         .uppercase = false,
                         .base = BaseDecimal,
                         .spec_char = -1};
  return params;
}

int parse_format_spr(const char *format, int *i, FormatParams *params,
                     va_list args) {
  if (!format || !i || !params) return PARSE_ERROR_INVALID_SPEC;

  int error = PARSE_SUCCESS;
  parse_flags_spr(format, i, params);
  parse_width_spr(format, i, params, args);
  parse_precision_spr(format, i, params, args);
  parse_modifier(format, i, params);
  error = parse_specifier(format, i, params);
  return error;
}

int parse_format_ssc(const char *format, int *i, FormatParams *params) {
  int error = PARSE_SUCCESS;
  parse_width_ssc(format, i, params);
  parse_modifier(format, i, params);
  error = parse_specifier(format, i, params);
  return error;
}

static int parse_number(const char *format, int *i) {
  int num = 0;
  while (isdigit(format[*i])) {
    num = num * BaseDecimal + (format[*i] - '0');
    (*i)++;
  }
  return num;
}

static void parse_flags_spr(const char *format, int *i, FormatParams *params) {
  FlagMapping mappings[] = {{'-', &params->flag_minus},
                            {'+', &params->flag_plus},
                            {' ', &params->flag_space},
                            {'#', &params->flag_hash},
                            {'0', &params->flag_zero}};

  bool continue_parsing = true;
  while (continue_parsing) {
    bool flag_found = false;

    for (size_t j = 0; j < ARRAY_SIZE(mappings) && !flag_found; j++) {
      if (format[*i] == mappings[j].symbol && !(*mappings[j].flag)) {
        *mappings[j].flag = true;
        (*i)++;
        flag_found = true;
      }
    }
    continue_parsing = flag_found;
  }
}

static void parse_numeric_value_spr(const char *format, int *i, va_list args,
                                    bool *type_flag, int *value) {
  if (format[*i] == '*') {
    *type_flag = true;
    *value = abs(va_arg(args, int));
    (*i)++;
  } else if (isdigit(format[*i])) {
    *type_flag = true;
    *value = parse_number(format, i);
  }
}

static void parse_numeric_value_ssc(const char *format, int *i, bool *type_flag,
                                    int *value) {
  if (format[*i] == '*') {
    *type_flag = true;
    *value = 0, (*i)++;
  } else if (isdigit(format[*i])) {
    *type_flag = true;
    *value = parse_number(format, i);
  }
}

static void parse_width_ssc(const char *format, int *i, FormatParams *p) {
  parse_numeric_value_ssc(format, i, &p->width_type, &p->width_value);
}

static void parse_width_spr(const char *format, int *i, FormatParams *p,
                            va_list args) {
  parse_numeric_value_spr(format, i, args, &p->width_type, &p->width_value);
}

static void parse_precision_spr(const char *format, int *i, FormatParams *p,
                                va_list args) {
  if (format[*i] != '.') return;

  (*i)++;
  p->precision_type = true;  // При "%.[type]" точность по умолчанию -> 0
  parse_numeric_value_spr(format, i, args, &p->precision_type,
                          &p->precision_value);
}

static void parse_modifier(const char *format, int *idx, FormatParams *params) {
  for (size_t i = 0; i < ARRAY_SIZE(modifiers); i++) {
    size_t len = strlen(modifiers[i].str);
    if (strncmp(format + *idx, modifiers[i].str, len) == 0) {
      params->modifier = modifiers[i].mod;
      *idx += len;
      return;
    }
  }
}

static int parse_specifier(const char *format, int *i, FormatParams *params) {
  if (format[*i] == '\0') return PARSE_ERROR_INVALID_SPEC;

  char original_spec = format[*i];
  params->specifier = original_spec;
  params->uppercase = isupper(original_spec);
  char spec = tolower(original_spec);

  bool found = false;
  for (size_t idx = 0; idx < ARRAY_SIZE(specifier_mappings) && !found; idx++) {
    if (specifier_mappings[idx].specifier == spec) {
      specifier_mappings[idx].handler(params);
      found = true;
    }
  }

  (*i)++;

  return found ? PARSE_SUCCESS : PARSE_ERROR_END_OF_FORMAT;
}

static void handle_di_specifier(FormatParams *params) {
  set_signed_type(params);
  reset_flags_for_integer(params);
}
static void handle_u_specifier(FormatParams *params) {
  set_unsigned_type(params);
  params->base = BaseDecimal;
  reset_flags_for_unsigned(params);
}
static void handle_o_specifier(FormatParams *params) {
  set_unsigned_type(params);
  params->base = BaseOctal;
}
static void handle_x_specifier(FormatParams *params) {
  set_unsigned_type(params);
  params->base = BaseHexadecimal;
}
static void handle_f_specifier(FormatParams *params) {
  set_float_type(params);
  params->spec_char = CHAR_F;
}
static void handle_e_specifier(FormatParams *params) {
  set_float_type(params);
  params->spec_char = CHAR_E;
}
static void handle_g_specifier(FormatParams *params) {
  set_float_type(params);
  params->spec_char = CHAR_G;
}
static void handle_c_specifier(FormatParams *params) {
  params->type = (params->modifier == LENGTH_L) ? TYPE_WCHAR : TYPE_CHAR;
  reset_flags_for_char_string(params);
}
static void handle_s_specifier(FormatParams *params) {
  params->type = (params->modifier == LENGTH_L) ? TYPE_WSTRING : TYPE_STRING;
  reset_flags_for_char_string(params);
}
static void handle_p_specifier(FormatParams *params) {
  params->type = TYPE_POINTER;
  params->base = BaseHexadecimal;
  reset_flags_for_pointer(params);
}
static void handle_percent_specifier(FormatParams *params) {
  params->type = TYPE_PERCENT;
}
static void handle_n_specifier(FormatParams *params) { set_n_type(params); }

static void set_signed_type(FormatParams *params) {
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
static void set_unsigned_type(FormatParams *params) {
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
static void set_float_type(FormatParams *params) {
  if (params->modifier == LENGTH_CAP_L)
    params->type = TYPE_LONGDOUBLE;
  else
    params->type = TYPE_FLOAT;
}
static void set_n_type(FormatParams *params) {
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

void reset_flags_for_char_string(FormatParams *params) {
  params->flag_plus = 0;
  params->flag_space = 0;
  params->flag_zero = 0;
  params->flag_hash = 0;
}

void reset_flags_for_integer(FormatParams *params) { params->flag_hash = 0; }

void reset_flags_for_unsigned(FormatParams *params) {
  if (params->base != 8 && params->base != 16) {
    params->flag_hash = 0;
  }
}

void reset_flags_for_pointer(FormatParams *params) {
  params->flag_plus = 0;
  params->flag_space = 0;
  params->flag_hash = 0;
}