#include <check.h>
#include <float.h>
#include <limits.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/s21_string.h"

// Макрос для создания тестов с одним аргументом
#define TEST_SPRINTF_1(test_name, format_str, value, type) \
  START_TEST(test_name) {                                  \
    char str1[200] = {0};                                  \
    char str2[200] = {0};                                  \
    type val = (value);                                    \
    int res1 = sprintf(str1, format_str, val);             \
    int res2 = s21_sprintf(str2, format_str, val);         \
    ck_assert_str_eq(str1, str2);                          \
    ck_assert_int_eq(res1, res2);                          \
  }                                                        \
  END_TEST

// ================================================================
// Целочисленные типы без модификаторов
// ================================================================

// %d - int
TEST_SPRINTF_1(test_s21_sprintf_d, "int: %d", 123, int)
TEST_SPRINTF_1(test_s21_sprintf_d_min, "int: %d", INT_MIN, int)
TEST_SPRINTF_1(test_s21_sprintf_d_min_pl, "int: %d", INT_MIN - 1, int)
TEST_SPRINTF_1(test_s21_sprintf_d_max, "int: %d", INT_MAX, int)
TEST_SPRINTF_1(test_s21_sprintf_d_max_pl, "int: %d", INT_MAX + 1, int)
TEST_SPRINTF_1(test_s21_sprintf_d_false_tupe, "int: %d", 'A', double)
TEST_SPRINTF_1(test_s21_sprintf_d_null, "int: %d", NULL, int)

// %i - int
TEST_SPRINTF_1(test_s21_sprintf_i, "int: %i", 123, int)
TEST_SPRINTF_1(test_s21_sprintf_i_min, "int: %i", INT_MIN, int)
TEST_SPRINTF_1(test_s21_sprintf_i_min_pl, "int: %i", INT_MIN - 1, int)
TEST_SPRINTF_1(test_s21_sprintf_i_max, "int: %i", INT_MAX, int)
TEST_SPRINTF_1(test_s21_sprintf_i_max_pl, "int: %i", INT_MAX + 1, int)
TEST_SPRINTF_1(test_s21_sprintf_i_false_tupe, "int: %i", 'A', double)
TEST_SPRINTF_1(test_s21_sprintf_i_null, "int: %i", NULL, int)

// %o - unsigned int
TEST_SPRINTF_1(test_s21_sprintf_o, "unsigned int: %o", 123, unsigned int)
TEST_SPRINTF_1(test_s21_sprintf_o_min, "unsigned int: %o", 0, unsigned int)
TEST_SPRINTF_1(test_s21_sprintf_o_min_pl, "unsigned int: %o", 0 - 1,
               unsigned int)
TEST_SPRINTF_1(test_s21_sprintf_o_max, "unsigned int: %o", UINT_MAX,
               unsigned int)
TEST_SPRINTF_1(test_s21_sprintf_o_max_pl, "unsigned int: %o", UINT_MAX + 1,
               unsigned int)
TEST_SPRINTF_1(test_s21_sprintf_o_false_tupe, "unsigned int: %o", 'A', double)
TEST_SPRINTF_1(test_s21_sprintf_o_null, "unsigned int: %o", NULL, unsigned int)

// %u - unsigned int
TEST_SPRINTF_1(test_s21_sprintf_u, "unsigned int: %u", 123, unsigned int)
TEST_SPRINTF_1(test_s21_sprintf_u_min, "unsigned int: %u", 0, unsigned int)
TEST_SPRINTF_1(test_s21_sprintf_u_min_pl, "unsigned int: %u", 0 - 1,
               unsigned int)
TEST_SPRINTF_1(test_s21_sprintf_u_max, "unsigned int: %u", UINT_MAX,
               unsigned int)
TEST_SPRINTF_1(test_s21_sprintf_u_max_pl, "unsigned int: %u", UINT_MAX + 1,
               unsigned int)
TEST_SPRINTF_1(test_s21_sprintf_u_false_tupe, "unsigned int: %u", 'A', double)
TEST_SPRINTF_1(test_s21_sprintf_u_null, "unsigned int: %u", NULL, unsigned int)

// %x - unsigned int
TEST_SPRINTF_1(test_s21_sprintf_x, "unsigned int: %x", 123, unsigned int)
TEST_SPRINTF_1(test_s21_sprintf_x_min, "unsigned int: %x", 0, unsigned int)
TEST_SPRINTF_1(test_s21_sprintf_x_min_pl, "unsigned int: %x", 0 - 1,
               unsigned int)
TEST_SPRINTF_1(test_s21_sprintf_x_max, "unsigned int: %x", UINT_MAX,
               unsigned int)
TEST_SPRINTF_1(test_s21_sprintf_x_max_pl, "unsigned int: %x", UINT_MAX + 1,
               unsigned int)
TEST_SPRINTF_1(test_s21_sprintf_x_false_tupe, "unsigned int: %x", 'A', double)
TEST_SPRINTF_1(test_s21_sprintf_x_null, "unsigned int: %x", NULL, unsigned int)

// %X - unsigned int
TEST_SPRINTF_1(test_s21_sprintf_X, "unsigned int: %X", 123, unsigned int)
TEST_SPRINTF_1(test_s21_sprintf_X_min, "unsigned int: %X", 0, unsigned int)
TEST_SPRINTF_1(test_s21_sprintf_X_min_pl, "unsigned int: %X", 0 - 1,
               unsigned int)
TEST_SPRINTF_1(test_s21_sprintf_X_max, "unsigned int: %X", UINT_MAX,
               unsigned int)
TEST_SPRINTF_1(test_s21_sprintf_X_max_pl, "unsigned int: %X", UINT_MAX + 1,
               unsigned int)
TEST_SPRINTF_1(test_s21_sprintf_X_false_tupe, "unsigned int: %X", 'A', double)
TEST_SPRINTF_1(test_s21_sprintf_X_null, "unsigned int: %X", NULL, unsigned int)

// ================================================================
// Модификатор h (short)
// ================================================================

// %hd - short
TEST_SPRINTF_1(test_s21_sprintf_hd, "short: %hd", 123, short)
TEST_SPRINTF_1(test_s21_sprintf_hd_min, "short: %hd", SHRT_MIN, short)
TEST_SPRINTF_1(test_s21_sprintf_hd_min_pl, "short: %hd", SHRT_MIN - 1, short)
TEST_SPRINTF_1(test_s21_sprintf_hd_max, "short: %hd", SHRT_MAX, short)
TEST_SPRINTF_1(test_s21_sprintf_hd_max_pl, "short: %hd", SHRT_MAX + 1, short)
TEST_SPRINTF_1(test_s21_sprintf_hd_false_tupe, "short: %hd", 'A', double)
TEST_SPRINTF_1(test_s21_sprintf_hd_null, "short: %hd", NULL, short)

// %hi - short
TEST_SPRINTF_1(test_s21_sprintf_hi, "short: %hi", 123, short)
TEST_SPRINTF_1(test_s21_sprintf_hi_min, "short: %hi", SHRT_MIN, short)
TEST_SPRINTF_1(test_s21_sprintf_hi_min_pl, "short: %hi", SHRT_MIN - 1, short)
TEST_SPRINTF_1(test_s21_sprintf_hi_max, "short: %hi", SHRT_MAX, short)
TEST_SPRINTF_1(test_s21_sprintf_hi_max_pl, "short: %hi", SHRT_MAX + 1, short)
TEST_SPRINTF_1(test_s21_sprintf_hi_false_tupe, "short: %hi", 'A', double)
TEST_SPRINTF_1(test_s21_sprintf_hi_null, "short: %hi", NULL, short)

// %ho - unsigned short
TEST_SPRINTF_1(test_s21_sprintf_ho, "unsigned short: %ho", 123, unsigned short)
TEST_SPRINTF_1(test_s21_sprintf_ho_min, "unsigned short: %ho", 0,
               unsigned short)
TEST_SPRINTF_1(test_s21_sprintf_ho_min_pl, "unsigned short : %ho", 0 - 1,
               unsigned short)
TEST_SPRINTF_1(test_s21_sprintf_ho_max, "unsigned short : %ho", USHRT_MAX,
               unsigned short)
TEST_SPRINTF_1(test_s21_sprintf_ho_max_pl, "unsigned short : %ho",
               USHRT_MAX + 1, unsigned short)
TEST_SPRINTF_1(test_s21_sprintf_ho_false_tupe, "unsigned short : %ho", 'A',
               double)
TEST_SPRINTF_1(test_s21_sprintf_ho_null, "unsigned short : %ho", NULL,
               unsigned short)

// %hu - unsigned short
TEST_SPRINTF_1(test_s21_sprintf_hu, "unsigned short : %hu", 123, unsigned short)
TEST_SPRINTF_1(test_s21_sprintf_hu_min, "unsigned short : %hu", 0,
               unsigned short)
TEST_SPRINTF_1(test_s21_sprintf_hu_min_pl, "unsigned short : %hu", 0 - 1,
               unsigned short)
TEST_SPRINTF_1(test_s21_sprintf_hu_max, "unsigned short : %hu", USHRT_MAX,
               unsigned short)
TEST_SPRINTF_1(test_s21_sprintf_hu_max_pl, "unsigned short : %hu",
               USHRT_MAX + 1, unsigned short)
TEST_SPRINTF_1(test_s21_sprintf_hu_false_tupe, "unsigned short : %hu", 'A',
               double)
TEST_SPRINTF_1(test_s21_sprintf_hu_null, "unsigned short : %hu", NULL,
               unsigned short)

// %hx - unsigned short
TEST_SPRINTF_1(test_s21_sprintf_hx, "unsigned short : %hx", 123, unsigned short)
TEST_SPRINTF_1(test_s21_sprintf_hx_min, "unsigned short : %hx", 0,
               unsigned short)
TEST_SPRINTF_1(test_s21_sprintf_hx_min_pl, "unsigned short : %hx", 0 - 1,
               unsigned short)
TEST_SPRINTF_1(test_s21_sprintf_hx_max, "unsigned short : %hx", USHRT_MAX,
               unsigned short)
TEST_SPRINTF_1(test_s21_sprintf_hx_max_pl, "unsigned short : %hx",
               USHRT_MAX + 1, unsigned short)
TEST_SPRINTF_1(test_s21_sprintf_hx_false_tupe, "unsigned short : %hx", 'A',
               double)
TEST_SPRINTF_1(test_s21_sprintf_hx_null, "unsigned short : %hx", NULL,
               unsigned short)

// %hX - unsigned short
TEST_SPRINTF_1(test_s21_sprintf_hX, "unsigned short : %hX", 123, unsigned short)
TEST_SPRINTF_1(test_s21_sprintf_hX_min, "unsigned short : %hX", 0,
               unsigned short)
TEST_SPRINTF_1(test_s21_sprintf_hX_min_pl, "unsigned short : %hX", 0 - 1,
               unsigned short)
TEST_SPRINTF_1(test_s21_sprintf_hX_max, "unsigned short : %hX", USHRT_MAX,
               unsigned short)
TEST_SPRINTF_1(test_s21_sprintf_hX_max_pl, "unsigned short : %hX",
               USHRT_MAX + 1, unsigned short)
TEST_SPRINTF_1(test_s21_sprintf_hX_false_tupe, "unsigned short : %hX", 'A',
               double)
TEST_SPRINTF_1(test_s21_sprintf_hX_null, "unsigned short : %hX", NULL,
               unsigned short)

// ================================================================
// Модификатор hh (char)
// ================================================================

// %hhd - signed char
TEST_SPRINTF_1(test_s21_sprintf_hhd, "signed char: %hhd", 123, signed char)
TEST_SPRINTF_1(test_s21_sprintf_hhd_min, "signed char: %hhd", SCHAR_MIN,
               signed char)
TEST_SPRINTF_1(test_s21_sprintf_hhd_min_pl, "signed char: %hhd", SCHAR_MIN - 1,
               signed char)
TEST_SPRINTF_1(test_s21_sprintf_hhd_max, "signed char: %hhd", SCHAR_MAX,
               signed char)
TEST_SPRINTF_1(test_s21_sprintf_hhd_max_pl, "signed char: %hhd", SCHAR_MAX + 1,
               signed char)
TEST_SPRINTF_1(test_s21_sprintf_hhd_false_tupe, "signed char: %hhd", 'A',
               double)
TEST_SPRINTF_1(test_s21_sprintf_hhd_null, "signed char: %hhd", NULL,
               signed char)

// %hhi - signed char
TEST_SPRINTF_1(test_s21_sprintf_hhi, "signed char: %hhi", 123, signed char)
TEST_SPRINTF_1(test_s21_sprintf_hhi_min, "signed char: %hhi", SCHAR_MIN,
               signed char)
TEST_SPRINTF_1(test_s21_sprintf_hhi_min_pl, "signed char: %hhi", SCHAR_MIN - 1,
               signed char)
TEST_SPRINTF_1(test_s21_sprintf_hhi_max, "signed char: %hhi", SCHAR_MAX,
               signed char)
TEST_SPRINTF_1(test_s21_sprintf_hhi_max_pl, "signed char: %hhi", SCHAR_MAX + 1,
               signed char)
TEST_SPRINTF_1(test_s21_sprintf_hhi_false_tupe, "signed char: %hhi", 'A',
               double)
TEST_SPRINTF_1(test_s21_sprintf_hhi_null, "signed char: %hhi", NULL,
               signed char)

// %hho - unsigned char
TEST_SPRINTF_1(test_s21_sprintf_hho, "unsigned char: %hho", 123, unsigned char)
TEST_SPRINTF_1(test_s21_sprintf_hho_min, "unsigned char: %hho", 0,
               unsigned char)
TEST_SPRINTF_1(test_s21_sprintf_hho_min_pl, "unsigned char : %hho", 0 - 1,
               unsigned char)
TEST_SPRINTF_1(test_s21_sprintf_hho_max, "unsigned char : %hho", UCHAR_MAX,
               unsigned char)
TEST_SPRINTF_1(test_s21_sprintf_hho_max_pl, "unsigned char : %hho",
               UCHAR_MAX + 1, unsigned char)
TEST_SPRINTF_1(test_s21_sprintf_hho_false_tupe, "unsigned char : %hho", 'A',
               double)
TEST_SPRINTF_1(test_s21_sprintf_hho_null, "unsigned char : %hho", NULL,
               unsigned char)

// %hhu - unsigned char
TEST_SPRINTF_1(test_s21_sprintf_hhu, "unsigned char : %hhu", 123, unsigned char)
TEST_SPRINTF_1(test_s21_sprintf_hhu_min, "unsigned char : %hhu", 0,
               unsigned char)
TEST_SPRINTF_1(test_s21_sprintf_hhu_min_pl, "unsigned char : %hhu", 0 - 1,
               unsigned char)
TEST_SPRINTF_1(test_s21_sprintf_hhu_max, "unsigned char : %hhu", UCHAR_MAX,
               unsigned char)
TEST_SPRINTF_1(test_s21_sprintf_hhu_max_pl, "unsigned char : %hhu",
               UCHAR_MAX + 1, unsigned char)
TEST_SPRINTF_1(test_s21_sprintf_hhu_false_tupe, "unsigned char : %hhu", 'A',
               double)
TEST_SPRINTF_1(test_s21_sprintf_hhu_null, "unsigned char : %hhu", NULL,
               unsigned char)

// %hhx - unsigned char
TEST_SPRINTF_1(test_s21_sprintf_hhx, "unsigned char : %hhx", 123, unsigned char)
TEST_SPRINTF_1(test_s21_sprintf_hhx_min, "unsigned char : %hhx", 0,
               unsigned char)
TEST_SPRINTF_1(test_s21_sprintf_hhx_min_pl, "unsigned char : %hhx", 0 - 1,
               unsigned char)
TEST_SPRINTF_1(test_s21_sprintf_hhx_max, "unsigned char : %hhx", UCHAR_MAX,
               unsigned char)
TEST_SPRINTF_1(test_s21_sprintf_hhx_max_pl, "unsigned char : %hhx",
               UCHAR_MAX + 1, unsigned char)
TEST_SPRINTF_1(test_s21_sprintf_hhx_false_tupe, "unsigned char : %hhx", 'A',
               double)
TEST_SPRINTF_1(test_s21_sprintf_hhx_null, "unsigned char : %hhx", NULL,
               unsigned char)

// %hhX - unsigned char
TEST_SPRINTF_1(test_s21_sprintf_hhX, "unsigned char : %hhX", 123, unsigned char)
TEST_SPRINTF_1(test_s21_sprintf_hhX_min, "unsigned char : %hhX", 0,
               unsigned char)
TEST_SPRINTF_1(test_s21_sprintf_hhX_min_pl, "unsigned char : %hhX", 0 - 1,
               unsigned char)
TEST_SPRINTF_1(test_s21_sprintf_hhX_max, "unsigned char : %hhX", UCHAR_MAX,
               unsigned char)
TEST_SPRINTF_1(test_s21_sprintf_hhX_max_pl, "unsigned char : %hhX",
               UCHAR_MAX + 1, unsigned char)
TEST_SPRINTF_1(test_s21_sprintf_hhX_false_tupe, "unsigned char : %hhX", 'A',
               double)
TEST_SPRINTF_1(test_s21_sprintf_hhX_null, "unsigned char : %hhX", NULL,
               unsigned char)

// ================================================================
// Модификатор l (long)
// ================================================================

// %ld - long
TEST_SPRINTF_1(test_s21_sprintf_ld, "long: %ld", 123, long)
TEST_SPRINTF_1(test_s21_sprintf_ld_min, "long: %ld", LONG_MIN, long)
TEST_SPRINTF_1(test_s21_sprintf_ld_min_pl, "long: %ld", LONG_MIN - 1, long)
TEST_SPRINTF_1(test_s21_sprintf_ld_max, "long: %ld", LONG_MAX, long)
TEST_SPRINTF_1(test_s21_sprintf_ld_max_pl, "long: %ld", LONG_MAX + 1, long)
TEST_SPRINTF_1(test_s21_sprintf_ld_false_tupe, "long: %ld", 'A', double)
TEST_SPRINTF_1(test_s21_sprintf_ld_null, "long: %ld", NULL, long)

// %li - long
TEST_SPRINTF_1(test_s21_sprintf_li, "long: %li", 123, long)
TEST_SPRINTF_1(test_s21_sprintf_li_min, "long: %li", LONG_MIN, long)
TEST_SPRINTF_1(test_s21_sprintf_li_min_pl, "long: %li", LONG_MIN - 1, long)
TEST_SPRINTF_1(test_s21_sprintf_li_max, "long: %li", LONG_MAX, long)
TEST_SPRINTF_1(test_s21_sprintf_li_max_pl, "long: %li", LONG_MAX + 1, long)
TEST_SPRINTF_1(test_s21_sprintf_li_false_tupe, "long: %li", 'A', double)
TEST_SPRINTF_1(test_s21_sprintf_li_null, "long: %li", NULL, long)

// %lo - unsigned long
TEST_SPRINTF_1(test_s21_sprintf_lo, "unsigned long: %lo", 123, unsigned long)
TEST_SPRINTF_1(test_s21_sprintf_lo_min, "unsigned long: %lo", 0, unsigned long)
TEST_SPRINTF_1(test_s21_sprintf_lo_min_pl, "unsigned long : %lo", 0 - 1,
               unsigned long)
TEST_SPRINTF_1(test_s21_sprintf_lo_max, "unsigned long : %lo", ULONG_MAX,
               unsigned long)
TEST_SPRINTF_1(test_s21_sprintf_lo_max_pl, "unsigned long : %lo", ULONG_MAX + 1,
               unsigned long)
TEST_SPRINTF_1(test_s21_sprintf_lo_false_tupe, "unsigned long : %lo", 'A',
               double)
TEST_SPRINTF_1(test_s21_sprintf_lo_null, "unsigned long : %lo", NULL,
               unsigned long)

// %lu - unsigned long
TEST_SPRINTF_1(test_s21_sprintf_lu, "unsigned long : %lu", 123, unsigned long)
TEST_SPRINTF_1(test_s21_sprintf_lu_min, "unsigned long : %lu", 0, unsigned long)
TEST_SPRINTF_1(test_s21_sprintf_lu_min_pl, "unsigned long : %lu", 0 - 1,
               unsigned long)
TEST_SPRINTF_1(test_s21_sprintf_lu_max, "unsigned long : %lu", ULONG_MAX,
               unsigned long)
TEST_SPRINTF_1(test_s21_sprintf_lu_max_pl, "unsigned long : %lu", ULONG_MAX + 1,
               unsigned long)
TEST_SPRINTF_1(test_s21_sprintf_lu_false_tupe, "unsigned long : %lu", 'A',
               double)
TEST_SPRINTF_1(test_s21_sprintf_lu_null, "unsigned long : %lu", NULL,
               unsigned long)

// %lx - unsigned long
TEST_SPRINTF_1(test_s21_sprintf_lx, "unsigned long : %lx", 123, unsigned long)
TEST_SPRINTF_1(test_s21_sprintf_lx_min, "unsigned long : %lx", 0, unsigned long)
TEST_SPRINTF_1(test_s21_sprintf_lx_min_pl, "unsigned long : %lx", 0 - 1,
               unsigned long)
TEST_SPRINTF_1(test_s21_sprintf_lx_max, "unsigned long : %lx", ULONG_MAX,
               unsigned long)
TEST_SPRINTF_1(test_s21_sprintf_lx_max_pl, "unsigned long : %lx", ULONG_MAX + 1,
               unsigned long)
TEST_SPRINTF_1(test_s21_sprintf_lx_false_tupe, "unsigned long : %lx", 'A',
               double)
TEST_SPRINTF_1(test_s21_sprintf_lx_null, "unsigned long : %lx", NULL,
               unsigned long)

// %lX - unsigned long
TEST_SPRINTF_1(test_s21_sprintf_lX, "unsigned long : %lX", 123, unsigned long)
TEST_SPRINTF_1(test_s21_sprintf_lX_min, "unsigned long : %lX", 0, unsigned long)
TEST_SPRINTF_1(test_s21_sprintf_lX_min_pl, "unsigned long : %lX", 0 - 1,
               unsigned long)
TEST_SPRINTF_1(test_s21_sprintf_lX_max, "unsigned long : %lX", USHRT_MAX,
               unsigned long)
TEST_SPRINTF_1(test_s21_sprintf_lX_max_pl, "unsigned long : %lX", USHRT_MAX + 1,
               unsigned long)
TEST_SPRINTF_1(test_s21_sprintf_lX_false_tupe, "unsigned long : %lX", 'A',
               double)
TEST_SPRINTF_1(test_s21_sprintf_lX_null, "unsigned long : %lX", NULL,
               unsigned long)

// ================================================================
// Модификатор ll (long long)
// ================================================================

// %lld - long long
TEST_SPRINTF_1(test_s21_sprintf_lld, "long long: %lld", 123, long long)
TEST_SPRINTF_1(test_s21_sprintf_lld_min, "long long: %lld", LLONG_MIN,
               long long)
TEST_SPRINTF_1(test_s21_sprintf_lld_min_pl, "long long: %lld", LLONG_MIN - 1,
               long long)
TEST_SPRINTF_1(test_s21_sprintf_lld_max, "long long: %lld", LLONG_MAX,
               long long)
TEST_SPRINTF_1(test_s21_sprintf_lld_max_pl, "long long: %lld", LLONG_MAX + 1,
               long long)
TEST_SPRINTF_1(test_s21_sprintf_lld_false_tupe, "long long: %lld", 'A', double)
TEST_SPRINTF_1(test_s21_sprintf_lld_null, "long long: %lld", NULL, long long)

// %lli - long long
TEST_SPRINTF_1(test_s21_sprintf_lli, "long long: %lli", 123, long long)
TEST_SPRINTF_1(test_s21_sprintf_lli_min, "long long: %lli", LLONG_MIN,
               long long)
TEST_SPRINTF_1(test_s21_sprintf_lli_min_pl, "long long: %lli", LLONG_MIN - 1,
               long long)
TEST_SPRINTF_1(test_s21_sprintf_lli_max, "long long: %lli", LLONG_MAX,
               long long)
TEST_SPRINTF_1(test_s21_sprintf_lli_max_pl, "long long: %lli", LLONG_MAX + 1,
               long long)
TEST_SPRINTF_1(test_s21_sprintf_lli_false_tupe, "long long: %lli", 'A', double)
TEST_SPRINTF_1(test_s21_sprintf_lli_null, "long long: %lli", NULL, long long)

// %llo - unsigned long long
TEST_SPRINTF_1(test_s21_sprintf_llo, "unsigned long long: %llo", 123,
               unsigned long long)
TEST_SPRINTF_1(test_s21_sprintf_llo_min, "unsigned long long: %llo", 0,
               unsigned long long)
TEST_SPRINTF_1(test_s21_sprintf_llo_min_pl, "unsigned long long: %llo", 0 - 1,
               unsigned long long)
TEST_SPRINTF_1(test_s21_sprintf_llo_max, "unsigned long long: %llo", ULLONG_MAX,
               unsigned long long)
TEST_SPRINTF_1(test_s21_sprintf_llo_max_pl, "unsigned long long: %llo",
               ULLONG_MAX + 1, unsigned long long)
TEST_SPRINTF_1(test_s21_sprintf_llo_false_tupe, "unsigned long long: %llo", 'A',
               double)
TEST_SPRINTF_1(test_s21_sprintf_llo_null, "unsigned long long: %llo", NULL,
               unsigned long long)

// %llu - unsigned long long
TEST_SPRINTF_1(test_s21_sprintf_llu, "unsigned long long: %llu", 123,
               unsigned long long)
TEST_SPRINTF_1(test_s21_sprintf_llu_min, "unsigned long long: %llu", 0,
               unsigned long long)
TEST_SPRINTF_1(test_s21_sprintf_llu_min_pl, "unsigned long long: %llu", 0 - 1,
               unsigned long long)
TEST_SPRINTF_1(test_s21_sprintf_llu_max, "unsigned long long: %llu", ULLONG_MAX,
               unsigned long long)
TEST_SPRINTF_1(test_s21_sprintf_llu_max_pl, "unsigned long long: %llu",
               ULLONG_MAX + 1, unsigned long long)
TEST_SPRINTF_1(test_s21_sprintf_llu_false_tupe, "unsigned long long: %llu", 'A',
               double)
TEST_SPRINTF_1(test_s21_sprintf_llu_null, "unsigned long long: %llu", NULL,
               unsigned long long)

// %llx - unsigned long long
TEST_SPRINTF_1(test_s21_sprintf_llx, "unsigned long long: %llx", 123,
               unsigned long long)
TEST_SPRINTF_1(test_s21_sprintf_llx_min, "unsigned long long: %llx", 0,
               unsigned long long)
TEST_SPRINTF_1(test_s21_sprintf_llx_min_pl, "unsigned long long: %llx", 0 - 1,
               unsigned long long)
TEST_SPRINTF_1(test_s21_sprintf_llx_max, "unsigned long long: %llx", ULLONG_MAX,
               unsigned long long)
TEST_SPRINTF_1(test_s21_sprintf_llx_max_pl, "unsigned long long: %llx",
               ULLONG_MAX + 1, unsigned long long)
TEST_SPRINTF_1(test_s21_sprintf_llx_false_tupe, "unsigned long long: %llx", 'A',
               double)
TEST_SPRINTF_1(test_s21_sprintf_llx_null, "unsigned long long: %llx", NULL,
               unsigned long long)

// %llX - unsigned long long
TEST_SPRINTF_1(test_s21_sprintf_llX, "unsigned long long: %llX", 123,
               unsigned long long)
TEST_SPRINTF_1(test_s21_sprintf_llX_min, "unsigned long long: %llX", 0,
               unsigned long long)
TEST_SPRINTF_1(test_s21_sprintf_llX_min_pl, "unsigned long long: %llX", 0 - 1,
               unsigned long long)
TEST_SPRINTF_1(test_s21_sprintf_llX_max, "unsigned long long: %llX", ULLONG_MAX,
               unsigned long long)
TEST_SPRINTF_1(test_s21_sprintf_llX_max_pl, "unsigned long long: %llX",
               ULLONG_MAX + 1, unsigned long long)
TEST_SPRINTF_1(test_s21_sprintf_llX_false_tupe, "unsigned long long: %llX", 'A',
               double)
TEST_SPRINTF_1(test_s21_sprintf_llX_null, "unsigned long long: %llX", NULL,
               unsigned long long)

// ================================================================
// Строковые типы
// ================================================================

// %c - char
TEST_SPRINTF_1(test_s21_sprintf_c, "Char: %c", 'A', char)
TEST_SPRINTF_1(test_s21_sprintf_c_min, "Char: %c", -128, char)
TEST_SPRINTF_1(test_s21_sprintf_c_min_pl, "Char: %c", -128 - 1, char)
TEST_SPRINTF_1(test_s21_sprintf_c_max, "Char: %c", 127, char)
TEST_SPRINTF_1(test_s21_sprintf_c_max_pl, "Char: %c", 127 + 1, char)
TEST_SPRINTF_1(test_s21_sprintf_c_false_tupe, "Char: %c", 'A', double)
TEST_SPRINTF_1(test_s21_sprintf_c_null, "Char: %c", NULL, char)
TEST_SPRINTF_1(test_s21_sprintf_c_nonprint, "Char: %c", '\x01', char)
TEST_SPRINTF_1(test_s21_sprintf_c_zero, "Char: %c", 0, char)
TEST_SPRINTF_1(test_s21_sprintf_c_newline, "Char: %c", '\n', char)
TEST_SPRINTF_1(test_s21_sprintf_c_tab, "Char: %c", '\t', char)
TEST_SPRINTF_1(test_s21_sprintf_c_null_char, "Char: %c", '\0', char)

// %s - string
TEST_SPRINTF_1(test_s21_sprintf_s, "String: %s", "Hello, world!", char *)
TEST_SPRINTF_1(test_s21_sprintf_s_special, "String: %s", "Hello\tWorld\n",
               char *)
TEST_SPRINTF_1(test_s21_sprintf_s_special_chars, "String: %s",
               "Line1\nLine2\tTab\x01", char *)
TEST_SPRINTF_1(test_s21_sprintf_s_unicode, "String: %s", "Привет мир!", char *)
TEST_SPRINTF_1(test_s21_sprintf_s_false_tupe, "Char: %s", 234.6, double)
TEST_SPRINTF_1(test_s21_sprintf_s_null, "String: %s", NULL, char *)
TEST_SPRINTF_1(test_s21_sprintf_s_empty, "String: %s", "", char *)

// %lc - wide char
START_TEST(test_s21_sprintf_lc) {
  char str1[200] = {0};
  char str2[200] = {0};
  wchar_t wc = L'Я';
  int res1 = sprintf(str1, "Wide char: %lc", wc);
  int res2 = s21_sprintf(str2, "Wide char: %lc", wc);
  ck_assert_str_eq(str1, str2);
  ck_assert_int_eq(res1, res2);
}
END_TEST

// %ls - wide string
START_TEST(test_s21_sprintf_ls) {
  char str1[200] = {0};
  char str2[200] = {0};
  wchar_t *ws = L"Привет, мир!";
  int res1 = sprintf(str1, "Wide string: %ls", ws);
  int res2 = s21_sprintf(str2, "Wide string: %ls", ws);
  ck_assert_str_eq(str1, str2);
  ck_assert_int_eq(res1, res2);
}
END_TEST

// ================================================================
// Вещественные типы
// ================================================================

// %e - double
TEST_SPRINTF_1(test_s21_sprintf_e, "double: %e", 123.456, double)
TEST_SPRINTF_1(test_s21_sprintf_e_neg, "double: %e", -123.456, double)
TEST_SPRINTF_1(test_s21_sprintf_e_zero, "double: %e", 0.0, double)
TEST_SPRINTF_1(test_s21_sprintf_e_big, "double: %e", 1e308, double)
TEST_SPRINTF_1(test_s21_sprintf_e_small, "double: %e", 1e-308, double)
// %E - double
TEST_SPRINTF_1(test_s21_sprintf_E, "double: %E", 123.456, double)
TEST_SPRINTF_1(test_s21_sprintf_E_neg, "double: %E", -123.456, double)
TEST_SPRINTF_1(test_s21_sprintf_E_zero, "double: %E", 0.0, double)

// %f - double
TEST_SPRINTF_1(test_s21_sprintf_f, "double: %f", 123.456, double)
TEST_SPRINTF_1(test_s21_sprintf_f_neg, "double: %f", -123.456, double)
TEST_SPRINTF_1(test_s21_sprintf_f_zero, "double: %f", 0.0, double)
TEST_SPRINTF_1(test_s21_sprintf_f_big, "double: %f", 1e20, double)
// %g - double
TEST_SPRINTF_1(test_s21_sprintf_g_switch_to_e, "double: %g", 0.0000123456,
               double)
TEST_SPRINTF_1(test_s21_sprintf_g_switch_to_f, "double: %g", 123.456, double)
TEST_SPRINTF_1(test_s21_sprintf_g_switch, "double: %g", 123456789.0, double)

// %G - double
TEST_SPRINTF_1(test_s21_sprintf_G_switch_to_e, "double: %G", 0.0000123456,
               double)
TEST_SPRINTF_1(test_s21_sprintf_G_switch_to_f, "double: %G", 123.456, double)
TEST_SPRINTF_1(test_s21_sprintf_G_switch, "double: %G", 123456789.0, double)

// %le - double (long)
TEST_SPRINTF_1(test_s21_sprintf_le, "double: %le", 123.456, double)
TEST_SPRINTF_1(test_s21_sprintf_le_small, "double: %le", 1e-308, double)

// %lE - double (long)
TEST_SPRINTF_1(test_s21_sprintf_lE, "double: %lE", 123.456, double)

// %lf - double (long)
TEST_SPRINTF_1(test_s21_sprintf_lf, "double: %lf", 123.456, double)

// %lg - double (long)
TEST_SPRINTF_1(test_s21_sprintf_lg, "double: %lg", 123456789.0, double)
TEST_SPRINTF_1(test_s21_sprintf_lg_small, "double: %lg", 0.0000123456, double)

// %lG - double (long)
TEST_SPRINTF_1(test_s21_sprintf_lG, "double: %lG", 123.456, double)

// %Le - long double
TEST_SPRINTF_1(test_s21_sprintf_Le, "long double: %Le", 123.456L, long double)
TEST_SPRINTF_1(test_s21_sprintf_Le_neg, "long double: %Le", -123.456L,
               long double)

// %LE - long double
TEST_SPRINTF_1(test_s21_sprintf_LE, "long double: %LE", 123.456L, long double)
TEST_SPRINTF_1(test_s21_sprintf_LE_neg, "long double: %LE", -123.456L,
               long double)

// %Lf - long double
TEST_SPRINTF_1(test_s21_sprintf_Lf, "long double: %Lf", 123.456L, long double)
TEST_SPRINTF_1(test_s21_sprintf_Lf_neg, "long double: %Lf", -123.456L,
               long double)

// %Lg - long double
TEST_SPRINTF_1(test_s21_sprintf_Lg, "long double: %Lg", 123.456L, long double)
TEST_SPRINTF_1(test_s21_sprintf_Lg_small, "long double: %Lg", 0.0000123456L,
               long double)

// %LG - long double
TEST_SPRINTF_1(test_s21_sprintf_LG, "long double: %LG", 123.456L, long double)
TEST_SPRINTF_1(test_s21_sprintf_LG_small, "long double: %LG", 0.0000123456L,
               long double)

// ================================================================
// Вещественные типы: NaN и INFINITY
// ================================================================

// %e - double
TEST_SPRINTF_1(test_s21_sprintf_e_nan, "double: %e", NAN, double)
TEST_SPRINTF_1(test_s21_sprintf_e_inf, "double: %e", INFINITY, double)
TEST_SPRINTF_1(test_s21_sprintf_e_neg_inf, "double: %e", -INFINITY, double)

// %E - double
TEST_SPRINTF_1(test_s21_sprintf_E_nan, "double: %E", NAN, double)
TEST_SPRINTF_1(test_s21_sprintf_E_inf, "double: %E", INFINITY, double)
TEST_SPRINTF_1(test_s21_sprintf_E_neg_inf, "double: %E", -INFINITY, double)

// %f - double
TEST_SPRINTF_1(test_s21_sprintf_f_nan, "double: %f", NAN, double)
TEST_SPRINTF_1(test_s21_sprintf_f_inf, "double: %f", INFINITY, double)
TEST_SPRINTF_1(test_s21_sprintf_f_neg_inf, "double: %f", -INFINITY, double)

// %g - double
TEST_SPRINTF_1(test_s21_sprintf_g_nan, "double: %g", NAN, double)
TEST_SPRINTF_1(test_s21_sprintf_g_inf, "double: %g", INFINITY, double)
TEST_SPRINTF_1(test_s21_sprintf_g_neg_inf, "double: %g", -INFINITY, double)

// %G - double
TEST_SPRINTF_1(test_s21_sprintf_G_nan, "double: %G", NAN, double)
TEST_SPRINTF_1(test_s21_sprintf_G_inf, "double: %G", INFINITY, double)
TEST_SPRINTF_1(test_s21_sprintf_G_neg_inf, "double: %G", -INFINITY, double)

// %le - double (long)
TEST_SPRINTF_1(test_s21_sprintf_le_nan, "double: %le", NAN, double)
TEST_SPRINTF_1(test_s21_sprintf_le_inf, "double: %le", INFINITY, double)
TEST_SPRINTF_1(test_s21_sprintf_le_neg_inf, "double: %le", -INFINITY, double)

// %lE - double (long)
TEST_SPRINTF_1(test_s21_sprintf_lE_nan, "double: %lE", NAN, double)
TEST_SPRINTF_1(test_s21_sprintf_lE_inf, "double: %lE", INFINITY, double)
TEST_SPRINTF_1(test_s21_sprintf_lE_neg_inf, "double: %lE", -INFINITY, double)

// %lf - double (long)
TEST_SPRINTF_1(test_s21_sprintf_lf_nan, "double: %lf", NAN, double)
TEST_SPRINTF_1(test_s21_sprintf_lf_inf, "double: %lf", INFINITY, double)
TEST_SPRINTF_1(test_s21_sprintf_lf_neg_inf, "double: %lf", -INFINITY, double)

// %lg - double (long)
TEST_SPRINTF_1(test_s21_sprintf_lg_nan, "double: %lg", NAN, double)
TEST_SPRINTF_1(test_s21_sprintf_lg_inf, "double: %lg", INFINITY, double)
TEST_SPRINTF_1(test_s21_sprintf_lg_neg_inf, "double: %lg", -INFINITY, double)

// %lG - double (long)
TEST_SPRINTF_1(test_s21_sprintf_lG_nan, "double: %lG", NAN, double)
TEST_SPRINTF_1(test_s21_sprintf_lG_inf, "double: %lG", INFINITY, double)
TEST_SPRINTF_1(test_s21_sprintf_lG_neg_inf, "double: %lG", -INFINITY, double)

// %Le - long double
TEST_SPRINTF_1(test_s21_sprintf_Le_nan, "long double: %Le", (long double)NAN,
               long double)
TEST_SPRINTF_1(test_s21_sprintf_Le_inf, "long double: %Le",
               (long double)INFINITY, long double)
TEST_SPRINTF_1(test_s21_sprintf_Le_neg_inf, "long double: %Le",
               (long double)(-INFINITY), long double)

// %LE - long double
TEST_SPRINTF_1(test_s21_sprintf_LE_nan, "long double: %LE", (long double)NAN,
               long double)
TEST_SPRINTF_1(test_s21_sprintf_LE_inf, "long double: %LE",
               (long double)INFINITY, long double)
TEST_SPRINTF_1(test_s21_sprintf_LE_neg_inf, "long double: %LE",
               (long double)(-INFINITY), long double)

// %Lf - long double
TEST_SPRINTF_1(test_s21_sprintf_Lf_nan, "long double: %Lf", (long double)NAN,
               long double)
TEST_SPRINTF_1(test_s21_sprintf_Lf_inf, "long double: %Lf",
               (long double)INFINITY, long double)
TEST_SPRINTF_1(test_s21_sprintf_Lf_neg_inf, "long double: %Lf",
               (long double)(-INFINITY), long double)

// %Lg - long double
TEST_SPRINTF_1(test_s21_sprintf_Lg_nan, "long double: %Lg", (long double)NAN,
               long double)
TEST_SPRINTF_1(test_s21_sprintf_Lg_inf, "long double: %Lg",
               (long double)INFINITY, long double)
TEST_SPRINTF_1(test_s21_sprintf_Lg_neg_inf, "long double: %Lg",
               (long double)(-INFINITY), long double)

// %LG - long double
TEST_SPRINTF_1(test_s21_sprintf_LG_nan, "long double: %LG", (long double)NAN,
               long double)
TEST_SPRINTF_1(test_s21_sprintf_LG_inf, "long double: %LG",
               (long double)INFINITY, long double)
TEST_SPRINTF_1(test_s21_sprintf_LG_neg_inf, "long double: %LG",
               (long double)(-INFINITY), long double)

// ================================================================
// Особые типы
// ================================================================

// %p - pointer
TEST_SPRINTF_1(test_s21_sprintf_p, "Pointer: %p", (void *)0x1234abcd, void *)
TEST_SPRINTF_1(test_s21_sprintf_p_int, "Pointer: %p", (int *)0x1234abcd, int *)
TEST_SPRINTF_1(test_s21_sprintf_p_unsigned_int, "Pointer: %p",
               (unsigned int *)0x1234abcd, unsigned int *)
TEST_SPRINTF_1(test_s21_sprintf_p_double, "Pointer: %p", (double *)0x1234abcd,
               double *)
TEST_SPRINTF_1(test_s21_sprintf_p_null, "Pointer: %p", NULL, void *)

// %% - percent sign
START_TEST(test_s21_sprintf_double_percent) {
  char str1[200] = {0};
  char str2[200] = {0};
  int res1 = sprintf(str1, "100%% complete: %% %%%%");
  int res2 = s21_sprintf(str2, "100%% complete: %% %%%%");
  ck_assert_str_eq(str1, str2);
  ck_assert_int_eq(res1, res2);
}
END_TEST

START_TEST(test_s21_sprintf_percent_combined) {
  char str1[200];
  char str2[200];
  int a = 5;
  int res1 = sprintf(str1, "%%d: %d%%", a);
  int res2 = s21_sprintf(str2, "%%d: %d%%", a);
  ck_assert_str_eq(str1, str2);
  ck_assert_int_eq(res1, res2);
}
END_TEST

// %n - write count
START_TEST(test_s21_sprintf_n) {
  char str1[200] = {0};
  char str2[200] = {0};
  int n1 = 0, n2 = 0;

  sprintf(str1, "Test%n string", &n1);
  s21_sprintf(str2, "Test%n string", &n2);

  ck_assert_str_eq(str1, str2);
  ck_assert_int_eq(n1, n2);
}
END_TEST

START_TEST(test_s21_sprintf_n_middle) {
  char str1[200] = {0};
  char str2[200] = {0};
  int n1 = -1, n2 = -1;
  sprintf(str1, "Test%d%n", 123, &n1);
  s21_sprintf(str2, "Test%d%n", 123, &n2);
  ck_assert_str_eq(str1, str2);
  ck_assert_int_eq(n1, n2);
}
END_TEST

// %hn - short count
START_TEST(test_s21_sprintf_hn) {
  char str1[200] = {0};
  char str2[200] = {0};
  short n1 = 0, n2 = 0;
  sprintf(str1, "Test%hn string", &n1);
  s21_sprintf(str2, "Test%hn string", &n2);
  ck_assert_str_eq(str1, str2);
  ck_assert_int_eq(n1, n2);
}
END_TEST

// %hhn - char count
START_TEST(test_s21_sprintf_hhn) {
  char str1[200] = {0};
  char str2[200] = {0};
  signed char n1 = 0, n2 = 0;
  sprintf(str1, "Test%hhn string", &n1);
  s21_sprintf(str2, "Test%hhn string", &n2);
  ck_assert_str_eq(str1, str2);
  ck_assert_int_eq(n1, n2);
}
END_TEST

// %ln - long count
START_TEST(test_s21_sprintf_ln) {
  char str1[200] = {0};
  char str2[200] = {0};
  long n1 = 0, n2 = 0;
  sprintf(str1, "Test%ln string", &n1);
  s21_sprintf(str2, "Test%ln string", &n2);
  ck_assert_str_eq(str1, str2);
  ck_assert_int_eq(n1, n2);
}
END_TEST

// %lln - long long count
START_TEST(test_s21_sprintf_lln) {
  char str1[200] = {0};
  char str2[200] = {0};
  long long n1 = 0, n2 = 0;
  sprintf(str1, "Test%lln string", &n1);
  s21_sprintf(str2, "Test%lln string", &n2);
  ck_assert_str_eq(str1, str2);
  ck_assert_int_eq(n1, n2);
}
END_TEST

// %p - special cases
START_TEST(test_s21_sprintf_p_null_int) {
  char str1[200];
  char str2[200];
  int *p = NULL;
  int res1 = sprintf(str1, "Null ptr: %p", p);
  int res2 = s21_sprintf(str2, "Null ptr: %p", p);
  ck_assert_str_eq(str1, str2);
  ck_assert_int_eq(res1, res2);
}
END_TEST

START_TEST(test_s21_sprintf_p_struct) {
  char str1[200];
  char str2[200];
  struct {
    int a;
  } s = {0};
  int res1 = sprintf(str1, "Struct: %p", &s);
  int res2 = s21_sprintf(str2, "Struct: %p", &s);
  ck_assert_str_eq(str1, str2);
  ck_assert_int_eq(res1, res2);
}
END_TEST

// Function pointer test
void test_func() { 2 + 3; }

START_TEST(test_s21_sprintf_p_func) {
  char str1[200] = {0};
  char str2[200] = {0};
  void (*func_ptr)() = test_func;
  int res1 = sprintf(str1, "Func pointer: %p", func_ptr);
  int res2 = s21_sprintf(str2, "Func pointer: %p", func_ptr);
  ck_assert_str_eq(str1, str2);
  ck_assert_int_eq(res1, res2);
}
END_TEST

// ================================================================
// Test suite
// ================================================================

Suite *s21_sprintf_suite(void) {
  Suite *s = suite_create("s21_sprintf");
  TCase *tc = tcase_create("Core");

  tcase_add_test(tc, test_s21_sprintf_d);
  tcase_add_test(tc, test_s21_sprintf_d_min);
  tcase_add_test(tc, test_s21_sprintf_d_min_pl);
  tcase_add_test(tc, test_s21_sprintf_d_max);
  tcase_add_test(tc, test_s21_sprintf_d_max_pl);
  tcase_add_test(tc, test_s21_sprintf_d_false_tupe);
  tcase_add_test(tc, test_s21_sprintf_d_null);
  tcase_add_test(tc, test_s21_sprintf_i);
  tcase_add_test(tc, test_s21_sprintf_i_min);
  tcase_add_test(tc, test_s21_sprintf_i_min_pl);
  tcase_add_test(tc, test_s21_sprintf_i_max);
  tcase_add_test(tc, test_s21_sprintf_i_max_pl);
  tcase_add_test(tc, test_s21_sprintf_i_false_tupe);
  tcase_add_test(tc, test_s21_sprintf_i_null);
  tcase_add_test(tc, test_s21_sprintf_o);
  tcase_add_test(tc, test_s21_sprintf_o_min);
  tcase_add_test(tc, test_s21_sprintf_o_min_pl);
  tcase_add_test(tc, test_s21_sprintf_o_max);
  tcase_add_test(tc, test_s21_sprintf_o_max_pl);
  tcase_add_test(tc, test_s21_sprintf_o_false_tupe);
  tcase_add_test(tc, test_s21_sprintf_o_null);
  tcase_add_test(tc, test_s21_sprintf_u);
  tcase_add_test(tc, test_s21_sprintf_u_min);
  tcase_add_test(tc, test_s21_sprintf_u_min_pl);
  tcase_add_test(tc, test_s21_sprintf_u_max);
  tcase_add_test(tc, test_s21_sprintf_u_max_pl);
  tcase_add_test(tc, test_s21_sprintf_u_false_tupe);
  tcase_add_test(tc, test_s21_sprintf_u_null);
  tcase_add_test(tc, test_s21_sprintf_x);
  tcase_add_test(tc, test_s21_sprintf_x_min);
  tcase_add_test(tc, test_s21_sprintf_x_min_pl);
  tcase_add_test(tc, test_s21_sprintf_x_max);
  tcase_add_test(tc, test_s21_sprintf_x_max_pl);
  tcase_add_test(tc, test_s21_sprintf_x_false_tupe);
  tcase_add_test(tc, test_s21_sprintf_x_null);
  tcase_add_test(tc, test_s21_sprintf_X);
  tcase_add_test(tc, test_s21_sprintf_X_min);
  tcase_add_test(tc, test_s21_sprintf_X_min_pl);
  tcase_add_test(tc, test_s21_sprintf_X_max);
  tcase_add_test(tc, test_s21_sprintf_X_max_pl);
  tcase_add_test(tc, test_s21_sprintf_X_false_tupe);
  tcase_add_test(tc, test_s21_sprintf_X_null);
  tcase_add_test(tc, test_s21_sprintf_hd);
  tcase_add_test(tc, test_s21_sprintf_hd_min);
  tcase_add_test(tc, test_s21_sprintf_hd_min_pl);
  tcase_add_test(tc, test_s21_sprintf_hd_max);
  tcase_add_test(tc, test_s21_sprintf_hd_max_pl);
  tcase_add_test(tc, test_s21_sprintf_hd_false_tupe);
  tcase_add_test(tc, test_s21_sprintf_hd_null);
  tcase_add_test(tc, test_s21_sprintf_hi);
  tcase_add_test(tc, test_s21_sprintf_hi_min);
  tcase_add_test(tc, test_s21_sprintf_hi_min_pl);
  tcase_add_test(tc, test_s21_sprintf_hi_max);
  tcase_add_test(tc, test_s21_sprintf_hi_max_pl);
  tcase_add_test(tc, test_s21_sprintf_hi_false_tupe);
  tcase_add_test(tc, test_s21_sprintf_hi_null);
  tcase_add_test(tc, test_s21_sprintf_ho);
  tcase_add_test(tc, test_s21_sprintf_ho_min);
  tcase_add_test(tc, test_s21_sprintf_ho_min_pl);
  tcase_add_test(tc, test_s21_sprintf_ho_max);
  tcase_add_test(tc, test_s21_sprintf_ho_max_pl);
  tcase_add_test(tc, test_s21_sprintf_ho_false_tupe);
  tcase_add_test(tc, test_s21_sprintf_ho_null);
  tcase_add_test(tc, test_s21_sprintf_hu);
  tcase_add_test(tc, test_s21_sprintf_hu_min);
  tcase_add_test(tc, test_s21_sprintf_hu_min_pl);
  tcase_add_test(tc, test_s21_sprintf_hu_max);
  tcase_add_test(tc, test_s21_sprintf_hu_max_pl);
  tcase_add_test(tc, test_s21_sprintf_hu_false_tupe);
  tcase_add_test(tc, test_s21_sprintf_hu_null);
  tcase_add_test(tc, test_s21_sprintf_hx);
  tcase_add_test(tc, test_s21_sprintf_hx_min);
  tcase_add_test(tc, test_s21_sprintf_hx_min_pl);
  tcase_add_test(tc, test_s21_sprintf_hx_max);
  tcase_add_test(tc, test_s21_sprintf_hx_max_pl);
  tcase_add_test(tc, test_s21_sprintf_hx_false_tupe);
  tcase_add_test(tc, test_s21_sprintf_hx_null);
  tcase_add_test(tc, test_s21_sprintf_hX);
  tcase_add_test(tc, test_s21_sprintf_hX_min);
  tcase_add_test(tc, test_s21_sprintf_hX_min_pl);
  tcase_add_test(tc, test_s21_sprintf_hX_max);
  tcase_add_test(tc, test_s21_sprintf_hX_max_pl);
  tcase_add_test(tc, test_s21_sprintf_hX_false_tupe);
  tcase_add_test(tc, test_s21_sprintf_hX_null);
  tcase_add_test(tc, test_s21_sprintf_hhd);
  tcase_add_test(tc, test_s21_sprintf_hhd_min);
  tcase_add_test(tc, test_s21_sprintf_hhd_min_pl);
  tcase_add_test(tc, test_s21_sprintf_hhd_max);
  tcase_add_test(tc, test_s21_sprintf_hhd_max_pl);
  tcase_add_test(tc, test_s21_sprintf_hhd_false_tupe);
  tcase_add_test(tc, test_s21_sprintf_hhd_null);
  tcase_add_test(tc, test_s21_sprintf_hhi);
  tcase_add_test(tc, test_s21_sprintf_hhi_min);
  tcase_add_test(tc, test_s21_sprintf_hhi_min_pl);
  tcase_add_test(tc, test_s21_sprintf_hhi_max);
  tcase_add_test(tc, test_s21_sprintf_hhi_max_pl);
  tcase_add_test(tc, test_s21_sprintf_hhi_false_tupe);
  tcase_add_test(tc, test_s21_sprintf_hhi_null);
  tcase_add_test(tc, test_s21_sprintf_hho);
  tcase_add_test(tc, test_s21_sprintf_hho_min);
  tcase_add_test(tc, test_s21_sprintf_hho_min_pl);
  tcase_add_test(tc, test_s21_sprintf_hho_max);
  tcase_add_test(tc, test_s21_sprintf_hho_max_pl);
  tcase_add_test(tc, test_s21_sprintf_hho_false_tupe);
  tcase_add_test(tc, test_s21_sprintf_hho_null);
  tcase_add_test(tc, test_s21_sprintf_hhu);
  tcase_add_test(tc, test_s21_sprintf_hhu_min);
  tcase_add_test(tc, test_s21_sprintf_hhu_min_pl);
  tcase_add_test(tc, test_s21_sprintf_hhu_max);
  tcase_add_test(tc, test_s21_sprintf_hhu_max_pl);
  tcase_add_test(tc, test_s21_sprintf_hhu_false_tupe);
  tcase_add_test(tc, test_s21_sprintf_hhu_null);
  tcase_add_test(tc, test_s21_sprintf_hhx);
  tcase_add_test(tc, test_s21_sprintf_hhx_min);
  tcase_add_test(tc, test_s21_sprintf_hhx_min_pl);
  tcase_add_test(tc, test_s21_sprintf_hhx_max);
  tcase_add_test(tc, test_s21_sprintf_hhx_max_pl);
  tcase_add_test(tc, test_s21_sprintf_hhx_false_tupe);
  tcase_add_test(tc, test_s21_sprintf_hhx_null);
  tcase_add_test(tc, test_s21_sprintf_hhX);
  tcase_add_test(tc, test_s21_sprintf_hhX_min);
  tcase_add_test(tc, test_s21_sprintf_hhX_min_pl);
  tcase_add_test(tc, test_s21_sprintf_hhX_max);
  tcase_add_test(tc, test_s21_sprintf_hhX_max_pl);
  tcase_add_test(tc, test_s21_sprintf_hhX_false_tupe);
  tcase_add_test(tc, test_s21_sprintf_hhX_null);
  tcase_add_test(tc, test_s21_sprintf_ld);
  tcase_add_test(tc, test_s21_sprintf_ld_min);
  tcase_add_test(tc, test_s21_sprintf_ld_min_pl);
  tcase_add_test(tc, test_s21_sprintf_ld_max);
  tcase_add_test(tc, test_s21_sprintf_ld_max_pl);
  tcase_add_test(tc, test_s21_sprintf_ld_false_tupe);
  tcase_add_test(tc, test_s21_sprintf_ld_null);
  tcase_add_test(tc, test_s21_sprintf_li);
  tcase_add_test(tc, test_s21_sprintf_li_min);
  tcase_add_test(tc, test_s21_sprintf_li_min_pl);
  tcase_add_test(tc, test_s21_sprintf_li_max);
  tcase_add_test(tc, test_s21_sprintf_li_max_pl);
  tcase_add_test(tc, test_s21_sprintf_li_false_tupe);
  tcase_add_test(tc, test_s21_sprintf_li_null);
  tcase_add_test(tc, test_s21_sprintf_lo);
  tcase_add_test(tc, test_s21_sprintf_lo_min);
  tcase_add_test(tc, test_s21_sprintf_lo_min_pl);
  tcase_add_test(tc, test_s21_sprintf_lo_max);
  tcase_add_test(tc, test_s21_sprintf_lo_max_pl);
  tcase_add_test(tc, test_s21_sprintf_lo_false_tupe);
  tcase_add_test(tc, test_s21_sprintf_lo_null);
  tcase_add_test(tc, test_s21_sprintf_lu);
  tcase_add_test(tc, test_s21_sprintf_lu_min);
  tcase_add_test(tc, test_s21_sprintf_lu_min_pl);
  tcase_add_test(tc, test_s21_sprintf_lu_max);
  tcase_add_test(tc, test_s21_sprintf_lu_max_pl);
  tcase_add_test(tc, test_s21_sprintf_lu_false_tupe);
  tcase_add_test(tc, test_s21_sprintf_lu_null);
  tcase_add_test(tc, test_s21_sprintf_lx);
  tcase_add_test(tc, test_s21_sprintf_lx_min);
  tcase_add_test(tc, test_s21_sprintf_lx_min_pl);
  tcase_add_test(tc, test_s21_sprintf_lx_max);
  tcase_add_test(tc, test_s21_sprintf_lx_max_pl);
  tcase_add_test(tc, test_s21_sprintf_lx_false_tupe);
  tcase_add_test(tc, test_s21_sprintf_lx_null);
  tcase_add_test(tc, test_s21_sprintf_lX);
  tcase_add_test(tc, test_s21_sprintf_lX_min);
  tcase_add_test(tc, test_s21_sprintf_lX_min_pl);
  tcase_add_test(tc, test_s21_sprintf_lX_max);
  tcase_add_test(tc, test_s21_sprintf_lX_max_pl);
  tcase_add_test(tc, test_s21_sprintf_lX_false_tupe);
  tcase_add_test(tc, test_s21_sprintf_lX_null);
  tcase_add_test(tc, test_s21_sprintf_lld);
  tcase_add_test(tc, test_s21_sprintf_lld_min);
  tcase_add_test(tc, test_s21_sprintf_lld_min_pl);
  tcase_add_test(tc, test_s21_sprintf_lld_max);
  tcase_add_test(tc, test_s21_sprintf_lld_max_pl);
  tcase_add_test(tc, test_s21_sprintf_lld_false_tupe);
  tcase_add_test(tc, test_s21_sprintf_lld_null);
  tcase_add_test(tc, test_s21_sprintf_lli);
  tcase_add_test(tc, test_s21_sprintf_lli_min);
  tcase_add_test(tc, test_s21_sprintf_lli_min_pl);
  tcase_add_test(tc, test_s21_sprintf_lli_max);
  tcase_add_test(tc, test_s21_sprintf_lli_max_pl);
  tcase_add_test(tc, test_s21_sprintf_lli_false_tupe);
  tcase_add_test(tc, test_s21_sprintf_lli_null);
  tcase_add_test(tc, test_s21_sprintf_llo);
  tcase_add_test(tc, test_s21_sprintf_llo_min);
  tcase_add_test(tc, test_s21_sprintf_llo_min_pl);
  tcase_add_test(tc, test_s21_sprintf_llo_max);
  tcase_add_test(tc, test_s21_sprintf_llo_max_pl);
  tcase_add_test(tc, test_s21_sprintf_llo_false_tupe);
  tcase_add_test(tc, test_s21_sprintf_llo_null);
  tcase_add_test(tc, test_s21_sprintf_llu);
  tcase_add_test(tc, test_s21_sprintf_llu_min);
  tcase_add_test(tc, test_s21_sprintf_llu_min_pl);
  tcase_add_test(tc, test_s21_sprintf_llu_max);
  tcase_add_test(tc, test_s21_sprintf_llu_max_pl);
  tcase_add_test(tc, test_s21_sprintf_llu_false_tupe);
  tcase_add_test(tc, test_s21_sprintf_llu_null);
  tcase_add_test(tc, test_s21_sprintf_llx);
  tcase_add_test(tc, test_s21_sprintf_llx_min);
  tcase_add_test(tc, test_s21_sprintf_llx_min_pl);
  tcase_add_test(tc, test_s21_sprintf_llx_max);
  tcase_add_test(tc, test_s21_sprintf_llx_max_pl);
  tcase_add_test(tc, test_s21_sprintf_llx_false_tupe);
  tcase_add_test(tc, test_s21_sprintf_llx_null);
  tcase_add_test(tc, test_s21_sprintf_llX);
  tcase_add_test(tc, test_s21_sprintf_llX_min);
  tcase_add_test(tc, test_s21_sprintf_llX_min_pl);
  tcase_add_test(tc, test_s21_sprintf_llX_max);
  tcase_add_test(tc, test_s21_sprintf_llX_max_pl);
  tcase_add_test(tc, test_s21_sprintf_llX_false_tupe);
  tcase_add_test(tc, test_s21_sprintf_llX_null);
  tcase_add_test(tc, test_s21_sprintf_c);
  tcase_add_test(tc, test_s21_sprintf_c_min);
  tcase_add_test(tc, test_s21_sprintf_c_min_pl);
  tcase_add_test(tc, test_s21_sprintf_c_max);
  tcase_add_test(tc, test_s21_sprintf_c_max_pl);
  tcase_add_test(tc, test_s21_sprintf_c_false_tupe);
  tcase_add_test(tc, test_s21_sprintf_c_null);
  tcase_add_test(tc, test_s21_sprintf_c_nonprint);
  tcase_add_test(tc, test_s21_sprintf_c_zero);
  tcase_add_test(tc, test_s21_sprintf_c_newline);
  tcase_add_test(tc, test_s21_sprintf_c_tab);
  tcase_add_test(tc, test_s21_sprintf_c_null_char);
  tcase_add_test(tc, test_s21_sprintf_s);
  tcase_add_test(tc, test_s21_sprintf_s_special);
  tcase_add_test(tc, test_s21_sprintf_s_special_chars);
  tcase_add_test(tc, test_s21_sprintf_s_unicode);
  tcase_add_test(tc, test_s21_sprintf_s_false_tupe);
  tcase_add_test(tc, test_s21_sprintf_s_null);
  tcase_add_test(tc, test_s21_sprintf_s_empty);
  tcase_add_test(tc, test_s21_sprintf_lc);
  tcase_add_test(tc, test_s21_sprintf_ls);
  tcase_add_test(tc, test_s21_sprintf_e);
  tcase_add_test(tc, test_s21_sprintf_e_neg);
  tcase_add_test(tc, test_s21_sprintf_e_zero);
  tcase_add_test(tc, test_s21_sprintf_e_big);
  tcase_add_test(tc, test_s21_sprintf_e_small);
  tcase_add_test(tc, test_s21_sprintf_E);
  tcase_add_test(tc, test_s21_sprintf_E_neg);
  tcase_add_test(tc, test_s21_sprintf_E_zero);
  tcase_add_test(tc, test_s21_sprintf_f);
  tcase_add_test(tc, test_s21_sprintf_f_neg);
  tcase_add_test(tc, test_s21_sprintf_f_zero);
  tcase_add_test(tc, test_s21_sprintf_f_big);
  tcase_add_test(tc, test_s21_sprintf_g_switch_to_e);
  tcase_add_test(tc, test_s21_sprintf_g_switch_to_f);
  tcase_add_test(tc, test_s21_sprintf_g_switch);
  tcase_add_test(tc, test_s21_sprintf_G_switch_to_e);
  tcase_add_test(tc, test_s21_sprintf_G_switch_to_f);
  tcase_add_test(tc, test_s21_sprintf_G_switch);
  tcase_add_test(tc, test_s21_sprintf_le);
  tcase_add_test(tc, test_s21_sprintf_le_small);
  tcase_add_test(tc, test_s21_sprintf_lE);
  tcase_add_test(tc, test_s21_sprintf_lf);
  tcase_add_test(tc, test_s21_sprintf_lg);
  tcase_add_test(tc, test_s21_sprintf_lg_small);
  tcase_add_test(tc, test_s21_sprintf_lG);
  tcase_add_test(tc, test_s21_sprintf_Le);
  tcase_add_test(tc, test_s21_sprintf_Le_neg);
  tcase_add_test(tc, test_s21_sprintf_LE);
  tcase_add_test(tc, test_s21_sprintf_LE_neg);
  tcase_add_test(tc, test_s21_sprintf_Lf);
  tcase_add_test(tc, test_s21_sprintf_Lf_neg);
  tcase_add_test(tc, test_s21_sprintf_Lg);
  tcase_add_test(tc, test_s21_sprintf_Lg_small);
  tcase_add_test(tc, test_s21_sprintf_LG);
  tcase_add_test(tc, test_s21_sprintf_LG_small);
  tcase_add_test(tc, test_s21_sprintf_e_nan);
  tcase_add_test(tc, test_s21_sprintf_e_inf);
  tcase_add_test(tc, test_s21_sprintf_e_neg_inf);
  tcase_add_test(tc, test_s21_sprintf_E_nan);
  tcase_add_test(tc, test_s21_sprintf_E_inf);
  tcase_add_test(tc, test_s21_sprintf_E_neg_inf);
  tcase_add_test(tc, test_s21_sprintf_f_nan);
  tcase_add_test(tc, test_s21_sprintf_f_inf);
  tcase_add_test(tc, test_s21_sprintf_f_neg_inf);
  tcase_add_test(tc, test_s21_sprintf_g_nan);
  tcase_add_test(tc, test_s21_sprintf_g_inf);
  tcase_add_test(tc, test_s21_sprintf_g_neg_inf);
  tcase_add_test(tc, test_s21_sprintf_G_nan);
  tcase_add_test(tc, test_s21_sprintf_G_inf);
  tcase_add_test(tc, test_s21_sprintf_G_neg_inf);
  tcase_add_test(tc, test_s21_sprintf_le_nan);
  tcase_add_test(tc, test_s21_sprintf_le_inf);
  tcase_add_test(tc, test_s21_sprintf_le_neg_inf);
  tcase_add_test(tc, test_s21_sprintf_lE_nan);
  tcase_add_test(tc, test_s21_sprintf_lE_inf);
  tcase_add_test(tc, test_s21_sprintf_lE_neg_inf);
  tcase_add_test(tc, test_s21_sprintf_lf_nan);
  tcase_add_test(tc, test_s21_sprintf_lf_inf);
  tcase_add_test(tc, test_s21_sprintf_lf_neg_inf);
  tcase_add_test(tc, test_s21_sprintf_lg_nan);
  tcase_add_test(tc, test_s21_sprintf_lg_inf);
  tcase_add_test(tc, test_s21_sprintf_lg_neg_inf);
  tcase_add_test(tc, test_s21_sprintf_lG_nan);
  tcase_add_test(tc, test_s21_sprintf_lG_inf);
  tcase_add_test(tc, test_s21_sprintf_lG_neg_inf);
  tcase_add_test(tc, test_s21_sprintf_Le_nan);
  tcase_add_test(tc, test_s21_sprintf_Le_inf);
  tcase_add_test(tc, test_s21_sprintf_Le_neg_inf);
  tcase_add_test(tc, test_s21_sprintf_LE_nan);
  tcase_add_test(tc, test_s21_sprintf_LE_inf);
  tcase_add_test(tc, test_s21_sprintf_LE_neg_inf);
  tcase_add_test(tc, test_s21_sprintf_Lf_nan);
  tcase_add_test(tc, test_s21_sprintf_Lf_inf);
  tcase_add_test(tc, test_s21_sprintf_Lf_neg_inf);
  tcase_add_test(tc, test_s21_sprintf_Lg_nan);
  tcase_add_test(tc, test_s21_sprintf_Lg_inf);
  tcase_add_test(tc, test_s21_sprintf_Lg_neg_inf);
  tcase_add_test(tc, test_s21_sprintf_LG_nan);
  tcase_add_test(tc, test_s21_sprintf_LG_inf);
  tcase_add_test(tc, test_s21_sprintf_LG_neg_inf);
  tcase_add_test(tc, test_s21_sprintf_p);
  tcase_add_test(tc, test_s21_sprintf_p_int);
  tcase_add_test(tc, test_s21_sprintf_p_unsigned_int);
  tcase_add_test(tc, test_s21_sprintf_p_double);
  tcase_add_test(tc, test_s21_sprintf_p_null);
  tcase_add_test(tc, test_s21_sprintf_double_percent);
  tcase_add_test(tc, test_s21_sprintf_percent_combined);
  tcase_add_test(tc, test_s21_sprintf_n);
  tcase_add_test(tc, test_s21_sprintf_n_middle);
  tcase_add_test(tc, test_s21_sprintf_hn);
  tcase_add_test(tc, test_s21_sprintf_hhn);
  tcase_add_test(tc, test_s21_sprintf_ln);
  tcase_add_test(tc, test_s21_sprintf_lln);
  tcase_add_test(tc, test_s21_sprintf_p_null_int);
  tcase_add_test(tc, test_s21_sprintf_p_struct);
  tcase_add_test(tc, test_s21_sprintf_p_func);

  suite_add_tcase(s, tc);
  return s;
}

int main(int argc, char **argv) {
  int failed = 0;
  Suite *s = s21_sprintf_suite();
  SRunner *runner = srunner_create(s);

  if (argc > 1 && strcmp(argv[1], "+") == 0) {
    srunner_run_all(runner, CK_VERBOSE);
  } else {
    srunner_run_all(runner, CK_NORMAL);
  }

  failed = srunner_ntests_failed(runner);
  srunner_free(runner);

  return (failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}