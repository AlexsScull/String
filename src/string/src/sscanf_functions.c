#include <ctype.h>
#include <limits.h>
#include <locale.h>
#include <math.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <wchar.h>

#include "../include/s21_string.h"

////////////////////////////////////////////////////////////
//      Перечисления и константы, Нужно поправить!!!      //
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
  PARAM_WIDTH,                 ///< Тип ширины
  PARAM_WIDTH_ASTERISK_VALUE,  ///< Значение ширины для '*'
  PARAM_MODIFIER,                  ///< Модификатор длины
  PARAM_SPECIFIER,                 ///< Спецификатор типа
  TYPE,                            ///< Тип данных
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

#define MaxUtf8Bytes 4    ///< Макс. байт на UTF-8 символ
#define MaxBufferSize 65  ///< Максимальный размер буфера
#define BaseDecimal 10  ///< Десятичное основание
#define BaseOctal 8     ///< Восьмеричное основание
#define BaseHexadecimal 16  ///< Шестнадцатеричное основание

////////////////////////////////////////////////////////////
//                   Обявление функций                    //
////////////////////////////////////////////////////////////

static int parse_number(const char *format, int *i);
static void parse_width(const char *format, int *i, int params[],
                        va_list args);
static void parse_modifier(const char *format, int *i, int *modifier) ;
static void parse_specifier(const char *format, int *i, int params[]) ;
static void parse_integer_specifier(int params[]);
static void parse_unsigned_specifier(int params[], char specifier) ;
static void parse_float_specifier(int params[], char specifier);
static int convert_format(const char *str, int *str_idx, int params[], va_list args);
static void handle_integer(const char *str, int *idx, int params[], va_list args);
static void handle_unsigned(const char *str, int *idx, int params[], va_list args);
static void handle_float(const char *str, int *idx, int params[], va_list args);
static void handle_char(const char *str, int *idx, int params[], va_list args) ;
static void handle_string(const char *str, int *idx, int params[], va_list args);
static int handle_wchar(const char *str, int *idx, int params[], va_list args);
static int handle_wstring(const char *str, int *idx, int params[], va_list args);
static void handle_pointer(const char *str, int *idx, int params[], va_list args);
static void handle_count(const char *str, int *idx, int params[], va_list args) ;
static void handle_percent(const char *str, int *idx, va_list args);

static int convert_str_to_int(const char *str, int *idx, long long *val, int params[]);


////////////////////////////////////////////////////////////
//                Основная функция sprintf                //
////////////////////////////////////////////////////////////

int s21_sscanf(const char *str, const char *format, ...){
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

      int params[PARAM_COUNT] = {
                                 [PARAM_WIDTH] = -1,
                                 [PARAM_WIDTH_ASTERISK_VALUE] = 0,
                                 [PARAM_MODIFIER] = LENGTH_NULL,
                                 [PARAM_SPECIFIER] = -1,
                                 [TYPE] = -1,
                                 [PARAM_UPPERCASE] = false,
                                 [PARAM_BASE] = BaseDecimal,
                                 [PARAM_SPEC_CHAR] = -1};

      parse_width(format, &i, params, args);
      parse_modifier(format, &i, &params[PARAM_MODIFIER]);
      parse_specifier(format, &i, params);

      if (convert_format(str, &idx, params, args) == -1) {
        va_end(args);
        return -1;
      }
    }
  }

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


static void parse_width(const char *format, int *i, int params[],
                        va_list args) {
  if (format[*i] == '*') {
    params[PARAM_WIDTH] = WIDTH_ASTERISK;
    params[PARAM_WIDTH_ASTERISK_VALUE] = va_arg(args, int);
    (*i)++;
  } else if (isdigit(format[*i])) {
    bool b = false;
    params[PARAM_WIDTH] = WIDTH_NUMBER;
    params[PARAM_WIDTH_ASTERISK_VALUE] = parse_number(format, i);
    if (b) params[PARAM_WIDTH_ASTERISK_VALUE] *= -1;
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
  params[PARAM_SPECIFIER] = format[*i];
  switch (params[PARAM_SPECIFIER]) {
    case 'd':
    case 'i':
      parse_integer_specifier(params);
      break;
    case 'u':
    case 'o':
    case 'x':
    case 'X':
      parse_unsigned_specifier(params, params[PARAM_SPECIFIER]);
      break;
    case 'f':
    case 'e':
    case 'E':
    case 'g':
    case 'G':
      parse_float_specifier(params, params[PARAM_SPECIFIER]);
      break;
    case 'c':
      params[TYPE] =
          (params[PARAM_MODIFIER] == LENGTH_L) ? TYPE_WCHAR : TYPE_CHAR;
      break;
    case 's':
      params[TYPE] =
          (params[PARAM_MODIFIER] == LENGTH_L) ? TYPE_WSTRING : TYPE_STRING;
      break;
    case 'p':
      params[TYPE] = TYPE_POINTER;
      params[PARAM_BASE] = BaseHexadecimal;
      break;
    case '%':
      params[TYPE] = TYPE_PERCENT;
      break;
    case 'n':
      params[TYPE] = TYPE_PTR;
      break;
  }
}

static void parse_integer_specifier(int params[]) {
  if (params[PARAM_MODIFIER] == LENGTH_LL)
    params[TYPE] = TYPE_LONGLONG;
  else if (params[PARAM_MODIFIER] == LENGTH_L)
    params[TYPE] = TYPE_LONG;
  else
    params[TYPE] = TYPE_INT;
}

static void parse_unsigned_specifier(int params[], char specifier) {
  if (params[PARAM_MODIFIER] == LENGTH_LL)
    params[TYPE] = TYPE_ULONGLONG;
  else if (params[PARAM_MODIFIER] == LENGTH_L)
    params[TYPE] = TYPE_ULONG;
  else
    params[TYPE] = TYPE_UINT;

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
    params[TYPE] = TYPE_LONGDOUBLE;
  else
    params[TYPE] = TYPE_FLOAT;

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

static int convert_format(const char *str, int *str_idx, int params[], va_list args) {
  switch (params[TYPE]) {
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
      handle_wchar(str, str_idx, params, args);
      break;
    case TYPE_STRING:
      handle_string(str, str_idx, params, args);
      break;
    case TYPE_WSTRING:
      handle_wstring(str, str_idx, params, args);
      break;
    case TYPE_POINTER:
      handle_pointer(str, str_idx, params, args);
      break;
    case TYPE_PTR:
      handle_count(str, str_idx, params, args);
      break;
    case TYPE_PERCENT:
      handle_percent(str, str_idx, args);
      break;
  }
  return 0;
}

////////////////////////////////////////////////////////////
//             Обработчики типов данных                   //
////////////////////////////////////////////////////////////

static void handle_integer(const char *str, int *idx, int params[], va_list args) {
  long long *val;
  switch (params[TYPE]) {
    case TYPE_INT:
      val = (long long*)va_arg(args, int*);
      break;
    case TYPE_LONG:
      val = (long long*)va_arg(args, long*);
      break;
    default:
      val = va_arg(args, long long *);
      break;
  }
  convert_str_to_int(str, idx, val, params);
}

static void handle_unsigned(const char *str, int *idx, int params[], va_list args) {
  unsigned long long *val;
  switch (params[TYPE]) {
    case TYPE_UINT:
      val = (unsigned long long*)va_arg(args, unsigned int*);
      break;
    case TYPE_ULONG:
      val = (unsigned long long*)va_arg(args, unsigned long*);
      break;
    default:
      val = va_arg(args, unsigned long long*);
      break;
  }

//   convert_uint_to_str(str, idx, val, params);
}

static void handle_float(const char *str, int *idx, int params[], va_list args) {
  long double *val = (params[TYPE] == TYPE_FLOAT)
                        ? (long double*)va_arg(args, double*)
                        : va_arg(args, long double*);

//   if (!convert_special_float(str, idx, val, params)) {
    // convert_float_to_str(str, idx, val, params);
//   }
}

static void handle_char(const char *str, int *idx, int params[], va_list args) {
  char *c = (char*)va_arg(args, int*);
  char buffer[2] = {*c, '\0'};
//   convert_string_buffer_to_str(str, idx, buffer, params);
}

static void handle_string(const char *str, int *idx, int params[], va_list args) {
  char *s = va_arg(args, char *);
  
}

static int handle_wchar(const char *str, int *idx, int params[], va_list args) {
  wchar_t wcval = va_arg(args, wchar_t);
  char utf8_buffer[MaxUtf8Bytes + 1] = {0};
//   int utf8_len = wchar_to_utf8(utf8_buffer, wcval);
}

static int handle_wstring(const char *str, int *idx, int params[], va_list args) {
  wchar_t *wsval = va_arg(args, wchar_t *);
}

static void handle_pointer(const char *str, int *idx, int params[], va_list args) {
  void *ptr = va_arg(args, void *);
}

static void handle_count(const char *str, int *idx, int params[], va_list args) {
  int *ptr = va_arg(args, int *);
  *ptr = *idx;
}

static void handle_percent(const char *str, int *idx, va_list args) {
//   convert_char_to_buffer(str, idx, '%');
}

static int convert_str_to_int(const char *str, int *idx, long long *val, int params[]){
  for (int i = 0; str[i] != '\0'; i++){
        printf("%c", str[i]);
    }

}


