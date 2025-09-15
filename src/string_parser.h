#ifndef S21_STRING_PARSER_H_
#define S21_STRING_PARSER_H_

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
  TYPE_DOUBLE,      ///< %lf, %le, %lE, %lg, %lG (float/double)
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
  PARSE_ERROR = -5,                // Критическая ошибка
  PARSE_ERROR_END_OF_STRING = -4,  // Достигнут конец строки
  PARSE_ERROR_INVALID_DATA = -3,   // Неверные данные
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
  bool ssc_ignore;      ///< Тип ширины
  bool precision_type;  ///< Тип точности
  int precision_value;  ///< Значение точности
  int modifier;         ///< Модификатор длины
  int specifier;        ///< Спецификатор типа
  int type;             ///< Тип данных
  bool uppercase;       ///< Флаг верхнего регистра
  int base;       ///< Основание системы счисления
  int spec_char;  ///< Специальный символ формата
} FormatParams;

#define ARRAY_SIZE(arr) (sizeof(arr) / sizeof((arr)[0]))

// Константы форматирования
#define BaseDecimal 10  ///< Десятичное основание
#define BaseOctal 8     ///< Восьмеричное основание
#define BaseHexadecimal 16  ///< Шестнадцатеричное основание

// Функции инициализации
FormatParams s21_init_format_params(void);

// Функции парсинга
int s21_parse_format_spr(const char *format, int *i, FormatParams *params,
                         va_list *args);
int s21_parse_format_ssc(const char *format, int *i, FormatParams *params);

// Функции сброса лишних флагов
void s21_reset_flags_for_char_string(FormatParams *params);
void s21_reset_flags_for_u_integer(FormatParams *params);
void s21_reset_flags_for_pointer(FormatParams *params);
void s21_reset_flags_for_special(FormatParams *params);
void s21_reset_flags_for_zero(FormatParams *params);
#endif  // S21_STRING_PARSER_H_
