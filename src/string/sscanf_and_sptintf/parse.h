#ifndef PARSE_H_
#define PARSE_H_

#include <ctype.h>
#include <limits.h>
#include <locale.h>
#include <math.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include <wchar.h>

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
  TYPE_INT,       ///< %d, %i
  TYPE_SHORT,     ///< %hd, %hi
  TYPE_SCHAR,     ///< %hhd, %hhi
  TYPE_LONG,      ///< %ld, %li
  TYPE_LONGLONG,  ///< %lld, %lli

  // Целочисленные беззнаковые
  TYPE_UINT,       ///< %u, %o, %x, %X
  TYPE_USHORT,     ///< %hu, %ho, %hx, %hX
  TYPE_UCHAR,      ///< %hhu, %hho, %hhx, %hhX
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

  TYPE_N_INT,      ///< %n (int*)
  TYPE_N_SCHAR,    ///< %hn (short*)
  TYPE_N_SHORT,    ///< %hhn
  TYPE_N_LONG,     ///< %ln (long*)
  TYPE_N_LONGLONG  ///< %lln (long long*)
};

/** Символы формата чисел с плавающей точкой */
enum FormatChar {
  CHAR_F,  ///< Формат 'f'
  CHAR_E,  ///< Формат 'e'
  CHAR_G   ///< Формат 'g'
};

enum ParseErrorCode {
  PARSE_ERROR_END_OF_FORMAT = -2,  // Конец строки формата (критическая ошибка)
  PARSE_ERROR_INVALID_SPEC = -1,  // Некор. спецификатор (продолжение работы)
  PARSE_SUCCESS = 0,  // Успешное выполнение
};

typedef struct {
  bool flag_minus;      ///< '-' (left-justify)
  bool flag_plus;       ///< '+' (show plus sign)
  bool flag_space;      ///< ' ' (space for positive numbers)
  bool flag_hash;       ///< '#' (alternate form)
  bool flag_zero;       ///< '0' (zero-padding)
  bool width_type;      ///< Тип ширины
  int width_value;      ///< Значение ширины
  bool precision_type;  ///< Тип точности
  int precision_value;  ///< Значение точности
  int modifier;         ///< Модификатор длины
  int specifier;        ///< Спецификатор типа
  int type;             ///< Тип данных
  bool uppercase;       ///< Флаг верхнего регистра
  int base;       ///< Основание системы счисления
  int spec_char;  ///< Специальный символ формата
} FormatParams;

typedef struct {
  const char symbol;
  int *flag;
} FlagMapping;

typedef struct {
  const char *str;
  int mod;
} ModifierMapping;

typedef struct {
  char specifier;
  void (*handler)(FormatParams *);
} SpecifierMapping;

#define ARRAY_SIZE(arr) (sizeof(arr) / sizeof((arr)[0]))

// Константы форматирования
#define BaseDecimal 10  ///< Десятичное основание
#define BaseOctal 8     ///< Восьмеричное основание
#define BaseHexadecimal 16  ///< Шестнадцатеричное основание

// Функции инициализации
extern FormatParams init_format_params(void);

// Функции парсинга
extern int parse_format_spr(const char *format, int *i, FormatParams *params,
                            va_list args);
extern int parse_format_ssc(const char *format, int *i, FormatParams *params);

// Функции парсинга для sprintf
static void parse_flags_spr(const char *format, int *i, FormatParams *params);
static void parse_width_spr(const char *format, int *i, FormatParams *p,
                            va_list args);
static void parse_precision_spr(const char *format, int *i, FormatParams *p,
                                va_list args);

// Функции парсинга для sscanf
static void parse_width_ssc(const char *format, int *i, FormatParams *p);

// Общие функции парсинга
static int parse_number(const char *format, int *i);
static void parse_numeric_value_spr(const char *format, int *i, va_list args,
                                    bool *type_flag, int *value);
static void parse_numeric_value_ssc(const char *format, int *i, bool *type_flag,
                                    int *value);
static void parse_modifier(const char *format, int *idx, FormatParams *params);
static int parse_specifier(const char *format, int *i, FormatParams *params);

// Обработчики спецификаторов
static void handle_di_specifier(FormatParams *params);
static void handle_u_specifier(FormatParams *params);
static void handle_o_specifier(FormatParams *params);
static void handle_x_specifier(FormatParams *params);
static void handle_f_specifier(FormatParams *params);
static void handle_e_specifier(FormatParams *params);
static void handle_g_specifier(FormatParams *params);
static void handle_c_specifier(FormatParams *params);
static void handle_s_specifier(FormatParams *params);
static void handle_p_specifier(FormatParams *params);
static void handle_percent_specifier(FormatParams *params);
static void handle_n_specifier(FormatParams *params);

// Функции установки типа
static void set_signed_type(FormatParams *params);
static void set_unsigned_type(FormatParams *params);
static void set_float_type(FormatParams *params);
static void set_n_type(FormatParams *params);

// Функции сброса лишних флагов
void reset_flags_for_char_string(FormatParams *params);
void reset_flags_for_integer(FormatParams *params);
void reset_flags_for_unsigned(FormatParams *params);
void reset_flags_for_pointer(FormatParams *params);

#endif  // PARSE_H_