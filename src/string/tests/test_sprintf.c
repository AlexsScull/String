#include <check.h>
#include <float.h>
#include <limits.h>
#include <locale.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wchar.h>

#include "../include/s21_string.h"

#define TEST_SPRINTF(test_name, format_str, value, type) \
  START_TEST(test_name) {                                \
    char str_sp[200] = {0};                              \
    char str_s21[200] = {0};                             \
    type val = (value);                                  \
    int res_sp = sprintf(str_sp, format_str, val);       \
    int res_s21 = s21_sprintf(str_s21, format_str, val); \
    ck_assert_str_eq(str_sp, str_s21);                   \
    ck_assert_int_eq(res_sp, res_s21);                   \
  }                                                      \
  END_TEST

#define TEST_SPRINTF_2(test_name, format_str, val_for, value, type)    \
  START_TEST(test_name) {                                              \
    char str_sp[200] = {0};                                            \
    char str_s21[200] = {0};                                           \
    type val = (value);                                                \
    int res_sp = sprintf(str_sp, format_str, (int)val_for, val);       \
    int res_s21 = s21_sprintf(str_s21, format_str, (int)val_for, val); \
    ck_assert_str_eq(str_sp, str_s21);                                 \
    ck_assert_int_eq(res_sp, res_s21);                                 \
  }                                                                    \
  END_TEST

#define TEST_SPRINTF_3(test_name, format_str, val_for1, val_for2, value, type) \
  START_TEST(test_name) {                                                      \
    char str_sp[200] = {0};                                                    \
    char str_s21[200] = {0};                                                   \
    type val = (value);                                                        \
    int res_sp =                                                               \
        sprintf(str_sp, format_str, (int)val_for1, (int)val_for2, val);        \
    int res_s21 =                                                              \
        s21_sprintf(str_s21, format_str, (int)val_for1, (int)val_for2, val);   \
    ck_assert_str_eq(str_sp, str_s21);                                         \
    ck_assert_int_eq(res_sp, res_s21);                                         \
  }                                                                            \
  END_TEST

// ================================================================
// Целочисленные типы без модификаторов
// ================================================================

// %d - int
TEST_SPRINTF(d, "int: %d", 123, int)
TEST_SPRINTF(d_min, "int: %d", INT_MIN, int)
TEST_SPRINTF(d_max, "int: %d", INT_MAX, int)

// %i - int
TEST_SPRINTF(i, "int: %i", 123, int)
TEST_SPRINTF(i_min, "int: %i", INT_MIN, int)
TEST_SPRINTF(i_max, "int: %i", INT_MAX, int)

// %o - unsigned int
TEST_SPRINTF(o, "unsigned int: %o", 123, unsigned int)
TEST_SPRINTF(o_min, "unsigned int: %o", 0, unsigned int)
TEST_SPRINTF(o_max, "unsigned int: %o", UINT_MAX, unsigned int)

// %u - unsigned int
TEST_SPRINTF(u, "unsigned int: %u", 123, unsigned int)
TEST_SPRINTF(u_min, "unsigned int: %u", 0, unsigned int)
TEST_SPRINTF(u_max, "unsigned int: %u", UINT_MAX, unsigned int)

// %x - unsigned int
TEST_SPRINTF(x, "unsigned int: %x", 123, unsigned int)
TEST_SPRINTF(x_min, "unsigned int: %x", 0, unsigned int)
TEST_SPRINTF(x_max, "unsigned int: %x", UINT_MAX, unsigned int)

// %X - unsigned int
TEST_SPRINTF(X, "unsigned int: %X", 123, unsigned int)
TEST_SPRINTF(X_min, "unsigned int: %X", 0, unsigned int)
TEST_SPRINTF(X_max, "unsigned int: %X", UINT_MAX, unsigned int)

// ================================================================
// Модификатор h (short)
// ================================================================

// %hd - short
TEST_SPRINTF(hd, "short: %hd", 123, short)
TEST_SPRINTF(hd_min, "short: %hd", SHRT_MIN, short)
TEST_SPRINTF(hd_max, "short: %hd", SHRT_MAX, short)

// %hi - short
TEST_SPRINTF(hi, "short: %hi", 123, short)
TEST_SPRINTF(hi_min, "short: %hi", SHRT_MIN, short)
TEST_SPRINTF(hi_max, "short: %hi", SHRT_MAX, short)

// %ho - unsigned short
TEST_SPRINTF(ho, "unsigned short: %ho", 123, unsigned short)
TEST_SPRINTF(ho_min, "unsigned short: %ho", 0, unsigned short)
TEST_SPRINTF(ho_max, "unsigned short : %ho", USHRT_MAX, unsigned short)

// %hu - unsigned short
TEST_SPRINTF(hu, "unsigned short : %hu", 123, unsigned short)
TEST_SPRINTF(hu_min, "unsigned short : %hu", 0, unsigned short)
TEST_SPRINTF(hu_max, "unsigned short : %hu", USHRT_MAX, unsigned short)

// %hx - unsigned short
TEST_SPRINTF(hx, "unsigned short : %hx", 123, unsigned short)
TEST_SPRINTF(hx_min, "unsigned short : %hx", 0, unsigned short)
TEST_SPRINTF(hx_max, "unsigned short : %hx", USHRT_MAX, unsigned short)

// %hX - unsigned short
TEST_SPRINTF(hX, "unsigned short : %hX", 123, unsigned short)
TEST_SPRINTF(hX_min, "unsigned short : %hX", 0, unsigned short)
TEST_SPRINTF(hX_max, "unsigned short : %hX", USHRT_MAX, unsigned short)

// ================================================================
// Модификатор hh (char)
// ================================================================

// %hhd - signed char
TEST_SPRINTF(hhd, "signed char: %hhd", 123, signed char)
TEST_SPRINTF(hhd_min, "signed char: %hhd", SCHAR_MIN, signed char)
TEST_SPRINTF(hhd_max, "signed char: %hhd", SCHAR_MAX, signed char)

// %hhi - signed char
TEST_SPRINTF(hhi, "signed char: %hhi", 123, signed char)
TEST_SPRINTF(hhi_min, "signed char: %hhi", SCHAR_MIN, signed char)
TEST_SPRINTF(hhi_max, "signed char: %hhi", SCHAR_MAX, signed char)

// %hho - unsigned char
TEST_SPRINTF(hho, "unsigned char: %hho", 123, unsigned char)
TEST_SPRINTF(hho_min, "unsigned char: %hho", 0, unsigned char)
TEST_SPRINTF(hho_max, "unsigned char : %hho", UCHAR_MAX, unsigned char)

// %hhu - unsigned char
TEST_SPRINTF(hhu, "unsigned char : %hhu", 123, unsigned char)
TEST_SPRINTF(hhu_min, "unsigned char : %hhu", 0, unsigned char)
TEST_SPRINTF(hhu_max, "unsigned char : %hhu", UCHAR_MAX, unsigned char)

// %hhx - unsigned char
TEST_SPRINTF(hhx, "unsigned char : %hhx", 123, unsigned char)
TEST_SPRINTF(hhx_min, "unsigned char : %hhx", 0, unsigned char)
TEST_SPRINTF(hhx_max, "unsigned char : %hhx", UCHAR_MAX, unsigned char)

// %hhX - unsigned char
TEST_SPRINTF(hhX, "unsigned char : %hhX", 123, unsigned char)
TEST_SPRINTF(hhX_min, "unsigned char : %hhX", 0, unsigned char)
TEST_SPRINTF(hhX_max, "unsigned char : %hhX", UCHAR_MAX, unsigned char)

// ================================================================
// Модификатор l (long)
// ================================================================

// %ld - long
TEST_SPRINTF(ld, "long: %ld", 123, long)
TEST_SPRINTF(ld_min, "long: %ld", LONG_MIN, long)
TEST_SPRINTF(ld_max, "long: %ld", LONG_MAX, long)

// %li - long
TEST_SPRINTF(li, "long: %li", 123, long)
TEST_SPRINTF(li_min, "long: %li", LONG_MIN, long)
TEST_SPRINTF(li_max, "long: %li", LONG_MAX, long)

// %lo - unsigned long
TEST_SPRINTF(lo, "unsigned long: %lo", 123, unsigned long)
TEST_SPRINTF(lo_min, "unsigned long: %lo", 0, unsigned long)
TEST_SPRINTF(lo_max, "unsigned long : %lo", ULONG_MAX, unsigned long)

// %lu - unsigned long
TEST_SPRINTF(lu, "unsigned long : %lu", 123, unsigned long)
TEST_SPRINTF(lu_min, "unsigned long : %lu", 0, unsigned long)
TEST_SPRINTF(lu_max, "unsigned long : %lu", ULONG_MAX, unsigned long)

// %lx - unsigned long
TEST_SPRINTF(lx, "unsigned long : %lx", 123, unsigned long)
TEST_SPRINTF(lx_min, "unsigned long : %lx", 0, unsigned long)
TEST_SPRINTF(lx_max, "unsigned long : %lx", ULONG_MAX, unsigned long)

// %lX - unsigned long
TEST_SPRINTF(lX, "unsigned long : %lX", 123, unsigned long)
TEST_SPRINTF(lX_min, "unsigned long : %lX", 0, unsigned long)
TEST_SPRINTF(lX_max, "unsigned long : %lX", USHRT_MAX, unsigned long)

// ================================================================
// Модификатор ll (long long)
// ================================================================

// %lld - long long
TEST_SPRINTF(lld, "long long: %lld", 123, long long)
TEST_SPRINTF(lld_min, "long long: %lld", LLONG_MIN, long long)
TEST_SPRINTF(lld_max, "long long: %lld", LLONG_MAX, long long)

// %lli - long long
TEST_SPRINTF(lli, "long long: %lli", 123, long long)
TEST_SPRINTF(lli_min, "long long: %lli", LLONG_MIN, long long)
TEST_SPRINTF(lli_max, "long long: %lli", LLONG_MAX, long long)

// %llo - unsigned long long
TEST_SPRINTF(llo, "unsigned long long: %llo", 123, unsigned long long)
TEST_SPRINTF(llo_min, "unsigned long long: %llo", 0, unsigned long long)
TEST_SPRINTF(llo_max, "unsigned long long: %llo", ULLONG_MAX,
             unsigned long long)

// %llu - unsigned long long
TEST_SPRINTF(llu, "unsigned long long: %llu", 123, unsigned long long)
TEST_SPRINTF(llu_min, "unsigned long long: %llu", 0, unsigned long long)
TEST_SPRINTF(llu_max, "unsigned long long: %llu", ULLONG_MAX,
             unsigned long long)

// %llx - unsigned long long
TEST_SPRINTF(llx, "unsigned long long: %llx", 123, unsigned long long)
TEST_SPRINTF(llx_min, "unsigned long long: %llx", 0, unsigned long long)
TEST_SPRINTF(llx_max, "unsigned long long: %llx", ULLONG_MAX,
             unsigned long long)

// %llX - unsigned long long
TEST_SPRINTF(llX, "unsigned long long: %llX", 123, unsigned long long)
TEST_SPRINTF(llX_min, "unsigned long long: %llX", 0, unsigned long long)
TEST_SPRINTF(llX_max, "unsigned long long: %llX", ULLONG_MAX,
             unsigned long long)

// ================================================================
// Строковые типы
// ================================================================

// %c - char
TEST_SPRINTF(c, "Char: %c", 'A', char)
TEST_SPRINTF(c_min, "Char: %c", -128, char)
TEST_SPRINTF(c_max, "Char: %c", 127, char)
TEST_SPRINTF(c_nonprint, "Char: %c", '\x01', char)
TEST_SPRINTF(c_zero, "Char: %c", 0, char)
TEST_SPRINTF(c_newline, "Char: %c", '\n', char)
TEST_SPRINTF(c_tab, "Char: %c", '\t', char)
TEST_SPRINTF(c_null_char, "Char: %c", '\0', char)

// %s - string
TEST_SPRINTF(s, "String: %s", "Hello, world!", char *)
TEST_SPRINTF(s_special, "String: %s", "Hello\tWorld\n", char *)
TEST_SPRINTF(s_special_chars, "String: %s", "Line1\nLine2\tTab\x01", char *)
TEST_SPRINTF(s_unicode, "String: %s", "Привет мир!", char *)
TEST_SPRINTF(s_null, "String: %s", NULL, char *)
TEST_SPRINTF(s_empty, "String: %s", "", char *)

// ================================================================
// Вещественные типы
// ================================================================

// %e %E %f %g %G
TEST_SPRINTF(e_zero, "double: %e", 0.0, double)
TEST_SPRINTF(e_minus_zero, "double: %e", -0.0, double)
TEST_SPRINTF(E_zero, "double: %E", 0.0, double)
TEST_SPRINTF(E_minus_zero, "double: %E", -0.0, double)
TEST_SPRINTF(f_zero, "double: %f", 0.0, double)
TEST_SPRINTF(f_minus_zero, "double: %f", -0.0, double)
TEST_SPRINTF(g_zero, "double: %g", 0.0, double)
TEST_SPRINTF(g_minus_zero, "double: %g", -0.0, double)
TEST_SPRINTF(G_zero, "double: %G", 0.0, double)
TEST_SPRINTF(G_minus_zero, "double: %G", -0.0, double)
// %le %lE %lf %lg %lG
TEST_SPRINTF(le_zero, "double: %le", 0.0, double)
TEST_SPRINTF(le_minus_zero, "double: %le", -0.0, double)
TEST_SPRINTF(lE_zero, "double: %lE", 0.0, double)
TEST_SPRINTF(lE_minus_zero, "double: %lE", -0.0, double)
TEST_SPRINTF(lf_zero, "double: %lf", 0.0, double)
TEST_SPRINTF(lf_minus_zero, "double: %lf", -0.0, double)
TEST_SPRINTF(lg_zero, "double: %lg", 0.0, double)
TEST_SPRINTF(lg_minus_zero, "double: %lg", -0.0, double)
TEST_SPRINTF(lG_zero, "double: %lG", 0.0, double)
TEST_SPRINTF(lG_minus_zero, "double: %lG", -0.0, double)
// %Le %LE %Lf %Lg %LG
TEST_SPRINTF(Le_zero, "double: %Le", 0.0L, long double)
TEST_SPRINTF(Le_minus_zero, "double: %Le", -0.0L, long double)
TEST_SPRINTF(LE_zero, "double: %LE", 0.0L, long double)
TEST_SPRINTF(LE_minus_zero, "double: %LE", -0.0L, long double)
TEST_SPRINTF(Lf_zero, "double: %Lf", 0.0L, long double)
TEST_SPRINTF(Lf_minus_zero, "double: %Lf", -0.0L, long double)
TEST_SPRINTF(Lg_zero, "double: %Lg", 0.0L, long double)
TEST_SPRINTF(Lg_minus_zero, "double: %Lg", -0.0L, long double)
TEST_SPRINTF(LG_zero, "double: %LG", 0.0L, long double)
TEST_SPRINTF(LG_minus_zero, "double: %LG", -0.0L, long double)

// %e %E %f %g %G
TEST_SPRINTF(e, "double: %e", 123.456, double)
TEST_SPRINTF(e_neg, "double: %e", -123.456, double)
TEST_SPRINTF(e_big, "double: %e", 1e308, double)
TEST_SPRINTF(e_small, "double: %e", 1e-308, double)
TEST_SPRINTF(E, "double: %E", 123.456, double)
TEST_SPRINTF(E_neg, "double: %E", -123.456, double)
TEST_SPRINTF(E_big, "double: %E", 1e308, double)
TEST_SPRINTF(E_small, "double: %E", 1e-308, double)
TEST_SPRINTF(f, "double: %f", 123.456, double)
TEST_SPRINTF(f2, "double: %f", 123.9999996, double)
TEST_SPRINTF(f_neg, "double: %f", -123.456, double)
TEST_SPRINTF(f_small, "double: %f", 1e-308, double)
TEST_SPRINTF(g, "double: %g", 123.456, double)
TEST_SPRINTF(g2, "double: %g", 123.9999996, double)
TEST_SPRINTF(g3, "double: %g", 1.89, double)
TEST_SPRINTF(g_neg, "double: %g", -123.456, double)
TEST_SPRINTF(g_big, "double: %g", 1e308, double)
TEST_SPRINTF(g_small, "double: %g", 1e-308, double)
TEST_SPRINTF(G, "double: %G", 123.456, double)
TEST_SPRINTF(G2, "double: %G", 123.9999996, double)
TEST_SPRINTF(G3, "double: %G", 1.89, double)
TEST_SPRINTF(G_neg, "double: %G", -123.456, double)
TEST_SPRINTF(G_big, "double: %G", 1e308, double)
TEST_SPRINTF(G_small, "double: %G", 1e-308, double)
// %le %lE %lf %lg %lG
TEST_SPRINTF(le, "double: %le", 123.456, double)
TEST_SPRINTF(le_neg, "double: %le", -123.456, double)
TEST_SPRINTF(le_big, "double: %le", 1e308, double)
TEST_SPRINTF(le_small, "double: %le", 1e-308, double)
TEST_SPRINTF(lE, "double: %lE", 123.456, double)
TEST_SPRINTF(lE_neg, "double: %lE", -123.456, double)
TEST_SPRINTF(lE_big, "double: %lE", 1e308, double)
TEST_SPRINTF(lE_small, "double: %lE", 1e-308, double)
TEST_SPRINTF(lf, "double: %lf", 123.456, double)
TEST_SPRINTF(lf2, "double: %lf", 123.9999996, double)
TEST_SPRINTF(lf_neg, "double: %lf", -123.456, double)
TEST_SPRINTF(lf_small, "double: %lf", 1e-308, double)
TEST_SPRINTF(lg, "double: %lg", 123.456, double)
TEST_SPRINTF(lg2, "double: %lg", 123.9999996, double)
TEST_SPRINTF(lg3, "double: %lg", 1.89, double)
TEST_SPRINTF(lg_neg, "double: %lg", -123.456, double)
TEST_SPRINTF(lg_big, "double: %lg", 1e308, double)
TEST_SPRINTF(lg_small, "double: %lg", 1e-308, double)
TEST_SPRINTF(lG, "double: %lG", 123.456, double)
TEST_SPRINTF(lG2, "double: %lG", 123.9999996, double)
TEST_SPRINTF(lG3, "double: %lG", 1.89, double)
TEST_SPRINTF(lG_neg, "double: %lG", -123.456, double)
TEST_SPRINTF(lG_big, "double: %lG", 1e308, double)
TEST_SPRINTF(lG_small, "double: %lG", 1e-308, double)
// %Le %LE %Lf %Lg %LG
TEST_SPRINTF(Le, "double: %Le", 123.456L, long double)
TEST_SPRINTF(Le_neg, "double: %Le", -123.456L, long double)
TEST_SPRINTF(Le_big, "double: %Le", 1e308L, long double)
TEST_SPRINTF(Le_small, "double: %Le", 1e-308L, long double)
TEST_SPRINTF(LE, "double: %LE", 123.456L, long double)
TEST_SPRINTF(LE_neg, "double: %LE", -123.456L, long double)
TEST_SPRINTF(LE_big, "double: %LE", 1e308L, long double)
TEST_SPRINTF(LE_small, "double: %LE", 1e-308L, long double)
TEST_SPRINTF(Lf, "double: %Lf", 123.456L, long double)
TEST_SPRINTF(Lf2, "double: %Lf", 123.9999996L, long double)
TEST_SPRINTF(Lf_neg, "double: %Lf", -123.456L, long double)
TEST_SPRINTF(Lf_small, "double: %Lf", 1e-308L, long double)
TEST_SPRINTF(Lg, "double: %Lg", 123.456L, long double)
TEST_SPRINTF(Lg2, "double: %Lg", 123.9999996L, long double)
TEST_SPRINTF(Lg3, "double: %Lg", 1.89L, long double)
TEST_SPRINTF(Lg_neg, "double: %Lg", -123.456L, long double)
TEST_SPRINTF(Lg_big, "double: %Lg", 1e308L, long double)
TEST_SPRINTF(Lg_small, "double: %Lg", 1e-308L, long double)
TEST_SPRINTF(LG, "double: %LG", 123.456L, long double)
TEST_SPRINTF(LG2, "double: %LG", 123.9999996L, long double)
TEST_SPRINTF(LG3, "double: %LG", 1.89L, long double)
TEST_SPRINTF(LG_neg, "double: %LG", -123.456L, long double)
TEST_SPRINTF(LG_big, "double: %LG", 1e308L, long double)
TEST_SPRINTF(LG_small, "double: %LG", 1e-308L, long double)

// %g - double
TEST_SPRINTF(g_switch_to_e, "double: %g", 0.0000123456, double)
TEST_SPRINTF(g_switch_to_f, "double: %g", 123.456, double)
TEST_SPRINTF(g_switch, "double: %g", 123456789.0, double)
TEST_SPRINTF(G_switch_to_e, "double: %G", 0.0000123456, double)
TEST_SPRINTF(G_switch_to_f, "double: %G", 123.456, double)
TEST_SPRINTF(G_switch, "double: %G", 123456789.0, double)

// ================================================================
// Вещественные типы: NaN и INFINITY
// ================================================================

// %e %E %f %g %G
TEST_SPRINTF(e_nan, "double: %e", NAN, double)
TEST_SPRINTF(e_inf, "double: %e", INFINITY, double)
TEST_SPRINTF(e_neg_inf, "double: %e", -INFINITY, double)
TEST_SPRINTF(E_nan, "double: %E", NAN, double)
TEST_SPRINTF(E_inf, "double: %E", INFINITY, double)
TEST_SPRINTF(E_neg_inf, "double: %E", -INFINITY, double)
TEST_SPRINTF(f_nan, "double: %f", NAN, double)
TEST_SPRINTF(f_inf, "double: %f", INFINITY, double)
TEST_SPRINTF(f_neg_inf, "double: %f", -INFINITY, double)
TEST_SPRINTF(g_nan, "double: %g", NAN, double)
TEST_SPRINTF(g_inf, "double: %g", INFINITY, double)
TEST_SPRINTF(g_neg_inf, "double: %g", -INFINITY, double)
TEST_SPRINTF(G_nan, "double: %G", NAN, double)
TEST_SPRINTF(G_inf, "double: %G", INFINITY, double)
TEST_SPRINTF(G_neg_inf, "double: %G", -INFINITY, double)
// %le %lE %lf %lg %lG
TEST_SPRINTF(le_nan, "double: %le", NAN, double)
TEST_SPRINTF(le_inf, "double: %le", INFINITY, double)
TEST_SPRINTF(le_neg_inf, "double: %le", -INFINITY, double)
TEST_SPRINTF(lE_nan, "double: %lE", NAN, double)
TEST_SPRINTF(lE_inf, "double: %lE", INFINITY, double)
TEST_SPRINTF(lE_neg_inf, "double: %lE", -INFINITY, double)
TEST_SPRINTF(lf_nan, "double: %lf", NAN, double)
TEST_SPRINTF(lf_inf, "double: %lf", INFINITY, double)
TEST_SPRINTF(lf_neg_inf, "double: %lf", -INFINITY, double)
TEST_SPRINTF(lg_nan, "double: %lg", NAN, double)
TEST_SPRINTF(lg_inf, "double: %lg", INFINITY, double)
TEST_SPRINTF(lg_neg_inf, "double: %lg", -INFINITY, double)
TEST_SPRINTF(lG_nan, "double: %lG", NAN, double)
TEST_SPRINTF(lG_inf, "double: %lG", INFINITY, double)
TEST_SPRINTF(lG_neg_inf, "double: %lG", -INFINITY, double)
// %Le %LE %Lf %Lg %LG
TEST_SPRINTF(Le_nan, "long double: %Le", (long double)NAN, long double)
TEST_SPRINTF(Le_inf, "long double: %Le", (long double)INFINITY, long double)
TEST_SPRINTF(Le_neg_inf, "long double: %Le", (long double)(-INFINITY),
             long double)
TEST_SPRINTF(LE_nan, "long double: %LE", (long double)NAN, long double)
TEST_SPRINTF(LE_inf, "long double: %LE", (long double)INFINITY, long double)
TEST_SPRINTF(LE_neg_inf, "long double: %LE", (long double)(-INFINITY),
             long double)
TEST_SPRINTF(Lf_nan, "long double: %Lf", (long double)NAN, long double)
TEST_SPRINTF(Lf_inf, "long double: %Lf", (long double)INFINITY, long double)
TEST_SPRINTF(Lf_neg_inf, "long double: %Lf", (long double)(-INFINITY),
             long double)
TEST_SPRINTF(Lg_nan, "long double: %Lg", (long double)NAN, long double)
TEST_SPRINTF(Lg_inf, "long double: %Lg", (long double)INFINITY, long double)
TEST_SPRINTF(Lg_neg_inf, "long double: %Lg", (long double)(-INFINITY),
             long double)
TEST_SPRINTF(LG_nan, "long double: %LG", (long double)NAN, long double)
TEST_SPRINTF(LG_inf, "long double: %LG", (long double)INFINITY, long double)
TEST_SPRINTF(LG_neg_inf, "long double: %LG", (long double)(-INFINITY),
             long double)

// ================================================================
// Особые типы
// ================================================================

// %p - pointer
TEST_SPRINTF(p, "Pointer: %p", (void *)0x1234abcd, void *)
TEST_SPRINTF(p_int, "Pointer: %p", (int *)0x1234abcd, int *)
TEST_SPRINTF(p_unsigned_int, "Pointer: %p", (unsigned int *)0x1234abcd,
             unsigned int *)
TEST_SPRINTF(p_double, "Pointer: %p", (double *)0x1234abcd, double *)
TEST_SPRINTF(p_null, "Pointer: %p", NULL, void *)

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

START_TEST(test_s21_sprintf_c_all_chars) {
  char str1[100];
  char str2[100];

  for (int c = CHAR_MIN; c <= CHAR_MAX; c++) {
    int res1 = sprintf(str1, "char: %c", c);
    int res2 = s21_sprintf(str2, "char: %c", c);

    // Проверка совпадения строк и возвращаемых значений
    ck_assert_str_eq(str1, str2);
    ck_assert_int_eq(res1, res2);
  }
}
END_TEST

// ==========================================================================================
// Тесты для флагов форматирования (d, i, u, o, x, X) ('-', '+', ' ', '#', '0')
// ==========================================================================================

// Тесты для %d

TEST_SPRINTF(d_minus_negt, "%-d", -123, int)
TEST_SPRINTF(d_minus_post, "%-d", 123, int)
TEST_SPRINTF(d_minus_zero, "%-d", 0, int)
TEST_SPRINTF(d_minus_ng_z, "%-d", -0, int)
TEST_SPRINTF(d_plus_negt, "%+d", -123, int)
TEST_SPRINTF(d_plus_post, "%+d", 123, int)
TEST_SPRINTF(d_plus_zero, "%+d", 0, int)
TEST_SPRINTF(d_plus_ng_z, "%+d", -0, int)
TEST_SPRINTF(d_space_negt, "% d", -123, int)
TEST_SPRINTF(d_space_post, "% d", 123, int)
TEST_SPRINTF(d_space_zero, "% d", 0, int)
TEST_SPRINTF(d_space_ng_z, "% d", -0, int)
TEST_SPRINTF(d_zero_negt, "%0d", -123, int)
TEST_SPRINTF(d_zero_post, "%0d", 123, int)
TEST_SPRINTF(d_zero_zero, "%0d", 0, int)
TEST_SPRINTF(d_zero_ng_z, "%0d", -0, int)

TEST_SPRINTF(d_width_minus_negt, "%-5d", -123, int)
TEST_SPRINTF(d_width_minus_post, "%-5d", 123, int)
TEST_SPRINTF(d_width_minus_zero, "%-5d", 0, int)
TEST_SPRINTF(d_width_minus_ng_z, "%-5d", -0, int)
TEST_SPRINTF(d_width_plus_negt, "%+5d", -123, int)
TEST_SPRINTF(d_width_plus_post, "%+5d", 123, int)
TEST_SPRINTF(d_width_plus_zero, "%+5d", 0, int)
TEST_SPRINTF(d_width_plus_ng_z, "%+5d", -0, int)
TEST_SPRINTF(d_width_space_negt, "% 5d", -123, int)
TEST_SPRINTF(d_width_space_post, "% 5d", 123, int)
TEST_SPRINTF(d_width_space_zero, "% 5d", 0, int)
TEST_SPRINTF(d_width_space_ng_z, "% 5d", -0, int)
TEST_SPRINTF(d_width_zero_negt, "%05d", -123, int)
TEST_SPRINTF(d_width_zero_post, "%05d", 123, int)
TEST_SPRINTF(d_width_zero_zero, "%05d", 0, int)
TEST_SPRINTF(d_width_zero_ng_z, "%05d", -0, int)

TEST_SPRINTF(d_prec_minus_negt, "%-.5d", -123, int)
TEST_SPRINTF(d_prec_minus_post, "%-.5d", 123, int)
TEST_SPRINTF(d_prec_minus_zero, "%-.5d", 0, int)
TEST_SPRINTF(d_prec_minus_ng_z, "%-.5d", -0, int)
TEST_SPRINTF(d_prec_plus_negt, "%+.5d", -123, int)
TEST_SPRINTF(d_prec_plus_post, "%+.5d", 123, int)
TEST_SPRINTF(d_prec_plus_zero, "%+.5d", 0, int)
TEST_SPRINTF(d_prec_plus_ng_z, "%+.5d", -0, int)
TEST_SPRINTF(d_prec_space_negt, "% .5d", -123, int)
TEST_SPRINTF(d_prec_space_post, "% .5d", 123, int)
TEST_SPRINTF(d_prec_space_zero, "% .5d", 0, int)
TEST_SPRINTF(d_prec_space_ng_z, "% .5d", -0, int)

TEST_SPRINTF(d_width_prec_minus_negt, "%-10.5d", -123, int)
TEST_SPRINTF(d_width_prec_minus_post, "%-10.5d", 123, int)
TEST_SPRINTF(d_width_prec_minus_zero, "%-10.5d", 0, int)
TEST_SPRINTF(d_width_prec_minus_ng_z, "%-10.5d", -0, int)
TEST_SPRINTF(d_width_prec_plus_negt, "%+10.5d", -123, int)
TEST_SPRINTF(d_width_prec_plus_post, "%+10.5d", 123, int)
TEST_SPRINTF(d_width_prec_plus_zero, "%+10.5d", 0, int)
TEST_SPRINTF(d_width_prec_plus_ng_z, "%+10.5d", -0, int)
TEST_SPRINTF(d_width_prec_space_negt, "% 10.5d", -123, int)
TEST_SPRINTF(d_width_prec_space_post, "% 10.5d", 123, int)
TEST_SPRINTF(d_width_prec_space_zero, "% 10.5d", 0, int)
TEST_SPRINTF(d_width_prec_space_ng_z, "% 10.5d", -0, int)

TEST_SPRINTF_2(d_dynamic_width, "%*d", 10, 123, int)
TEST_SPRINTF_2(d_dynamic_precision, "%.*d", 5, 123, int)
TEST_SPRINTF_3(d_dynamic_width_precision, "%*.*d", 10, 5, 123, int)

TEST_SPRINTF(d_width_negt, "%5d", -123, int)
TEST_SPRINTF(d_width_post, "%5d", 123, int)
TEST_SPRINTF(d_width_zero, "%5d", 0, int)
TEST_SPRINTF(d_width_ng_z, "%5d", -0, int)
TEST_SPRINTF(d_prec_negt, "%.5d", -123, int)
TEST_SPRINTF(d_prec_post, "%.5d", 123, int)
TEST_SPRINTF(d_prec_zero_, "%.5d", 0, int)
TEST_SPRINTF(d_prec_ng_z, "%.5d", -0, int)
TEST_SPRINTF(d_width_prec_negt, "%10.5d", -123, int)
TEST_SPRINTF(d_width_prec_post, "%10.5d", 123, int)
TEST_SPRINTF(d_width_prec_zero, "%10.5d", 0, int)
TEST_SPRINTF(d_width_prec_ng_z, "%10.5d", -0, int)

TEST_SPRINTF(d_zero_prec_negt, "%.0d", -123, int)
TEST_SPRINTF(d_zero_prec_post, "%.0d", 123, int)
TEST_SPRINTF(d_zero_prec_zero, "%.0d", 0, int)
TEST_SPRINTF(d_zero_prec_ng_z, "%.0d", -0, int)

TEST_SPRINTF(d_zero_zero_negt, "%0d", -123, int)
TEST_SPRINTF(d_zero_zero_post, "%0d", 123, int)
TEST_SPRINTF(d_zero_zero_zero, "%0d", 0, int)
TEST_SPRINTF(d_zero_zero_ng_z, "%0d", -0, int)

TEST_SPRINTF(d_zero_prec_minus_zero, "%-.0d", 0, int)
TEST_SPRINTF(d_zero_prec_plus_zero, "%+.0d", 0, int)
TEST_SPRINTF(d_zero_prec_space_zero, "% .0d", 0, int)

TEST_SPRINTF(d_zero_zero_plus_zero, "%+0d", 0, int)
TEST_SPRINTF(d_zero_zero_space_zero, "% 0d", 0, int)

// Тесты для %i
TEST_SPRINTF(i_minus, "%-10i", 123, int)
TEST_SPRINTF(i_plus, "%+i", -123, int)
TEST_SPRINTF(i_space, "% i", 123, int)
TEST_SPRINTF(i_zero_form, "%05i", 123, int)
TEST_SPRINTF(i_width, "%10i", 123, int)
TEST_SPRINTF(i_precision, "%.5i", 123, int)
TEST_SPRINTF(i_width_precision, "%10.5i", 123, int)
TEST_SPRINTF_2(i_star_width, "%*i", 10, 123, int)
TEST_SPRINTF_2(i_star_precision, "%.*i", 5, 123, int)
TEST_SPRINTF_3(i_star_both, "%*.*i", 10, 5, 123, int)
TEST_SPRINTF(i_neg, "%i", -123, int)
TEST_SPRINTF(i_neg_plus, "%+i", -123, int)
TEST_SPRINTF(i_neg_space, "% i", -123, int)
TEST_SPRINTF(i_zero_prec, "%.0i", 0, int)

// Тесты для %u
TEST_SPRINTF(u_minus_negt, "%-u", -123, unsigned int)
TEST_SPRINTF(u_minus_post, "%-u", 123, unsigned int)
TEST_SPRINTF(u_minus_zero, "%-u", 0, unsigned int)
TEST_SPRINTF(u_minus_ng_z, "%-u", -0, unsigned int)
TEST_SPRINTF(u_zero_negt, "%0u", -123, unsigned int)
TEST_SPRINTF(u_zero_post, "%0u", 123, unsigned int)
TEST_SPRINTF(u_zero_zero, "%0u", 0, unsigned int)
TEST_SPRINTF(u_zero_ng_z, "%0u", -0, unsigned int)
TEST_SPRINTF(u_width_minus_negt, "%-5u", -123, unsigned int)
TEST_SPRINTF(u_width_minus_post, "%-5u", 123, unsigned int)
TEST_SPRINTF(u_width_minus_zero, "%-5u", 0, unsigned int)
TEST_SPRINTF(u_width_minus_ng_z, "%-5u", -0, unsigned int)
TEST_SPRINTF(u_width_zero_negt, "%05u", -123, unsigned int)
TEST_SPRINTF(u_width_zero_post, "%05u", 123, unsigned int)
TEST_SPRINTF(u_width_zero_zero, "%05u", 0, unsigned int)
TEST_SPRINTF(u_width_zero_ng_z, "%05u", -0, unsigned int)
TEST_SPRINTF(u_prec_minus_negt, "%-.5u", -123, unsigned int)
TEST_SPRINTF(u_prec_minus_post, "%-.5u", 123, unsigned int)
TEST_SPRINTF(u_prec_minus_zero, "%-.5u", 0, unsigned int)
TEST_SPRINTF(u_prec_minus_ng_z, "%-.5u", -0, unsigned int)
TEST_SPRINTF(u_width_prec_minus_negt, "%-10.5u", -123, unsigned int)
TEST_SPRINTF(u_width_prec_minus_post, "%-10.5u", 123, unsigned int)
TEST_SPRINTF(u_width_prec_minus_zero, "%-10.5u", 0, unsigned int)
TEST_SPRINTF(u_width_prec_minus_ng_z, "%-10.5u", -0, unsigned int)

TEST_SPRINTF_2(u_dynamic_width, "%*u", 10, 123, unsigned int)
TEST_SPRINTF_2(u_dynamic_precision, "%.*u", 5, 123, unsigned int)
TEST_SPRINTF_3(u_dynamic_width_precision, "%*.*u", 10, 5, 123, unsigned int)

TEST_SPRINTF(u_width_negt, "%5u", -123, unsigned int)
TEST_SPRINTF(u_width_post, "%5u", 123, unsigned int)
TEST_SPRINTF(u_width_zero, "%5u", 0, unsigned int)
TEST_SPRINTF(u_width_ng_z, "%5u", -0, unsigned int)
TEST_SPRINTF(u_prec_negt, "%.5u", -123, unsigned int)
TEST_SPRINTF(u_prec_post, "%.5u", 123, unsigned int)
TEST_SPRINTF(u_prec_zero_, "%.5u", 0, unsigned int)
TEST_SPRINTF(u_prec_ng_z, "%.5u", -0, unsigned int)
TEST_SPRINTF(u_width_prec_negt, "%10.5u", -123, unsigned int)
TEST_SPRINTF(u_width_prec_post, "%10.5u", 123, unsigned int)
TEST_SPRINTF(u_width_prec_zero, "%10.5u", 0, unsigned int)
TEST_SPRINTF(u_width_prec_ng_z, "%10.5u", -0, unsigned int)
TEST_SPRINTF(u_zero_prec_negt, "%.0u", -123, unsigned int)
TEST_SPRINTF(u_zero_prec_post, "%.0u", 123, unsigned int)
TEST_SPRINTF(u_zero_prec_zero, "%.0u", 0, unsigned int)
TEST_SPRINTF(u_zero_prec_ng_z, "%.0u", -0, unsigned int)
TEST_SPRINTF(u_zero_zero_negt, "%0u", -123, unsigned int)
TEST_SPRINTF(u_zero_zero_post, "%0u", 123, unsigned int)
TEST_SPRINTF(u_zero_zero_zero, "%0u", 0, unsigned int)
TEST_SPRINTF(u_zero_zero_ng_z, "%0u", -0, unsigned int)
TEST_SPRINTF(u_zero_prec_minus_zero, "%-.0u", 0, unsigned int)

// Тесты для %o
TEST_SPRINTF(o_minus_negt, "%-o", -123, unsigned int)
TEST_SPRINTF(o_minus_post, "%-o", 123, unsigned int)
TEST_SPRINTF(o_minus_zero, "%-o", 0, unsigned int)
TEST_SPRINTF(o_minus_ng_z, "%-o", -0, unsigned int)
TEST_SPRINTF(o_hash_negt, "%#o", -123, unsigned int)
TEST_SPRINTF(o_hash_post, "%#o", 123, unsigned int)
TEST_SPRINTF(o_hash_zero, "%#o", 0, unsigned int)
TEST_SPRINTF(o_hash_ng_z, "%#o", -0, unsigned int)
TEST_SPRINTF(o_zero_negt, "%0o", -123, unsigned int)
TEST_SPRINTF(o_zero_post, "%0o", 123, unsigned int)
TEST_SPRINTF(o_zero_zero, "%0o", 0, unsigned int)
TEST_SPRINTF(o_zero_ng_z, "%0o", -0, unsigned int)
TEST_SPRINTF(o_width_minus_negt, "%-5o", -123, unsigned int)
TEST_SPRINTF(o_width_minus_post, "%-5o", 123, unsigned int)
TEST_SPRINTF(o_width_minus_zero, "%-5o", 0, unsigned int)
TEST_SPRINTF(o_width_minus_ng_z, "%-5o", -0, unsigned int)
TEST_SPRINTF(o_width_hash_negt, "%#5o", -123, unsigned int)
TEST_SPRINTF(o_width_hash_post, "%#5o", 123, unsigned int)
TEST_SPRINTF(o_width_hash_zero, "%#5o", 0, unsigned int)
TEST_SPRINTF(o_width_hash_ng_z, "%#5o", -0, unsigned int)
TEST_SPRINTF(o_width_zero_negt, "%05o", -123, unsigned int)
TEST_SPRINTF(o_width_zero_post, "%05o", 123, unsigned int)
TEST_SPRINTF(o_width_zero_zero, "%05o", 0, unsigned int)
TEST_SPRINTF(o_width_zero_ng_z, "%05o", -0, unsigned int)
TEST_SPRINTF(o_prec_minus_negt, "%-.5o", -123, unsigned int)
TEST_SPRINTF(o_prec_minus_post, "%-.5o", 123, unsigned int)
TEST_SPRINTF(o_prec_minus_zero, "%-.5o", 0, unsigned int)
TEST_SPRINTF(o_prec_minus_ng_z, "%-.5o", -0, unsigned int)
TEST_SPRINTF(o_prec_hash_negt, "%#.5o", -123, unsigned int)
TEST_SPRINTF(o_prec_hash_post, "%#.5o", 123, unsigned int)
TEST_SPRINTF(o_prec_hash_zero, "%#.5o", 0, unsigned int)
TEST_SPRINTF(o_prec_hash_ng_z, "%#.5o", -0, unsigned int)
TEST_SPRINTF(o_width_prec_minus_negt, "%-10.5o", -123, unsigned int)
TEST_SPRINTF(o_width_prec_minus_post, "%-10.5o", 123, unsigned int)
TEST_SPRINTF(o_width_prec_minus_zero, "%-10.5o", 0, unsigned int)
TEST_SPRINTF(o_width_prec_minus_ng_z, "%-10.5o", -0, unsigned int)
TEST_SPRINTF(o_width_prec_hash_negt, "%#10.5o", -123, unsigned int)
TEST_SPRINTF(o_width_prec_hash_post, "%#10.5o", 123, unsigned int)
TEST_SPRINTF(o_width_prec_hash_zero, "%#10.5o", 0, unsigned int)
TEST_SPRINTF(o_width_prec_hash_ng_z, "%#10.5o", -0, unsigned int)
TEST_SPRINTF_2(o_dynamic_width, "%*o", 10, 123, unsigned int)
TEST_SPRINTF_2(o_dynamic_precision, "%.*o", 5, 123, unsigned int)
TEST_SPRINTF_3(o_dynamic_width_precision, "%*.*o", 10, 5, 123, unsigned int)
TEST_SPRINTF(o_width_negt, "%5o", -123, unsigned int)
TEST_SPRINTF(o_width_post, "%5o", 123, unsigned int)
TEST_SPRINTF(o_width_zero, "%5o", 0, unsigned int)
TEST_SPRINTF(o_width_ng_z, "%5o", -0, unsigned int)
TEST_SPRINTF(o_prec_negt, "%.5o", -123, unsigned int)
TEST_SPRINTF(o_prec_post, "%.5o", 123, unsigned int)
TEST_SPRINTF(o_prec_zero_, "%.5o", 0, unsigned int)
TEST_SPRINTF(o_prec_ng_z, "%.5o", -0, unsigned int)
TEST_SPRINTF(o_width_prec_negt, "%10.5o", -123, unsigned int)
TEST_SPRINTF(o_width_prec_post, "%10.5o", 123, unsigned int)
TEST_SPRINTF(o_width_prec_zero, "%10.5o", 0, unsigned int)
TEST_SPRINTF(o_width_prec_ng_z, "%10.5o", -0, unsigned int)
TEST_SPRINTF(o_zero_prec_negt, "%.0o", -123, unsigned int)
TEST_SPRINTF(o_zero_prec_post, "%.0o", 123, unsigned int)
TEST_SPRINTF(o_zero_prec_zero, "%.0o", 0, unsigned int)
TEST_SPRINTF(o_zero_prec_ng_z, "%.0o", -0, unsigned int)
TEST_SPRINTF(o_zero_zero_negt, "%0o", -123, unsigned int)
TEST_SPRINTF(o_zero_zero_post, "%0o", 123, unsigned int)
TEST_SPRINTF(o_zero_zero_zero, "%0o", 0, unsigned int)
TEST_SPRINTF(o_zero_zero_ng_z, "%0o", -0, unsigned int)
TEST_SPRINTF(o_zero_prec_minus_zero, "%-.0o", 0, unsigned int)
TEST_SPRINTF(o_zero_prec_hash_zero, "%#.0o", 0, unsigned int)
TEST_SPRINTF(o_zero_zero_hash_zero, "%#0o", 0, unsigned int)

// Тесты для %x
TEST_SPRINTF(x_minus_negt, "%-x", -123, unsigned int)
TEST_SPRINTF(x_minus_post, "%-x", 123, unsigned int)
TEST_SPRINTF(x_minus_zero, "%-x", 0, unsigned int)
TEST_SPRINTF(x_minus_ng_z, "%-x", -0, unsigned int)
TEST_SPRINTF(x_hash_negt, "%#x", -123, unsigned int)
TEST_SPRINTF(x_hash_post, "%#x", 123, unsigned int)
TEST_SPRINTF(x_hash_zero, "%#x", 0, unsigned int)
TEST_SPRINTF(x_hash_ng_z, "%#x", -0, unsigned int)
TEST_SPRINTF(x_zero_negt, "%0x", -123, unsigned int)
TEST_SPRINTF(x_zero_post, "%0x", 123, unsigned int)
TEST_SPRINTF(x_zero_zero, "%0x", 0, unsigned int)
TEST_SPRINTF(x_zero_ng_z, "%0x", -0, unsigned int)
TEST_SPRINTF(x_width_minus_negt, "%-5x", -123, unsigned int)
TEST_SPRINTF(x_width_minus_post, "%-5x", 123, unsigned int)
TEST_SPRINTF(x_width_minus_zero, "%-5x", 0, unsigned int)
TEST_SPRINTF(x_width_minus_ng_z, "%-5x", -0, unsigned int)
TEST_SPRINTF(x_width_hash_negt, "%#5x", -123, unsigned int)
TEST_SPRINTF(x_width_hash_post, "%#5x", 123, unsigned int)
TEST_SPRINTF(x_width_hash_zero, "%#5x", 0, unsigned int)
TEST_SPRINTF(x_width_hash_ng_z, "%#5x", -0, unsigned int)
TEST_SPRINTF(x_width_zero_negt, "%05x", -123, unsigned int)
TEST_SPRINTF(x_width_zero_post, "%05x", 123, unsigned int)
TEST_SPRINTF(x_width_zero_zero, "%05x", 0, unsigned int)
TEST_SPRINTF(x_width_zero_ng_z, "%05x", -0, unsigned int)
TEST_SPRINTF(x_prec_minus_negt, "%-.5x", -123, unsigned int)
TEST_SPRINTF(x_prec_minus_post, "%-.5x", 123, unsigned int)
TEST_SPRINTF(x_prec_minus, "%-.5x", 0, unsigned int)
TEST_SPRINTF(x_prec_minus_ng_z, "%-.5x", -0, unsigned int)
TEST_SPRINTF(x_prec_hash_negt, "%#.5x", -123, unsigned int)
TEST_SPRINTF(x_prec_hash_post, "%#.5x", 123, unsigned int)
TEST_SPRINTF(x_prec_hash_zero, "%#.5x", 0, unsigned int)
TEST_SPRINTF(x_prec_hash_ng_z, "%#.5x", -0, unsigned int)
TEST_SPRINTF(x_width_prec_minus_negt, "%-10.5x", -123, unsigned int)
TEST_SPRINTF(x_width_prec_minus_post, "%-10.5x", 123, unsigned int)
TEST_SPRINTF(x_width_prec_minus_zero, "%-10.5x", 0, unsigned int)
TEST_SPRINTF(x_width_prec_minus_ng_z, "%-10.5x", -0, unsigned int)
TEST_SPRINTF(x_width_prec_hash_negt, "%#10.5x", -123, unsigned int)
TEST_SPRINTF(x_width_prec_hash_post, "%#10.5x", 123, unsigned int)
TEST_SPRINTF(x_width_prec_hash_zero, "%#10.5x", 0, unsigned int)
TEST_SPRINTF(x_width_prec_hash_ng_z, "%#10.5x", -0, unsigned int)
TEST_SPRINTF_2(x_dynamic_width, "%*x", 10, 123, unsigned int)
TEST_SPRINTF_2(x_dynamic_precision, "%.*x", 5, 123, unsigned int)
TEST_SPRINTF_3(x_dynamic_width_precision, "%*.*x", 10, 5, 123, unsigned int)
TEST_SPRINTF(x_width_negt, "%5x", -123, unsigned int)
TEST_SPRINTF(x_width_post, "%5x", 123, unsigned int)
TEST_SPRINTF(x_width_zero, "%5x", 0, unsigned int)
TEST_SPRINTF(x_width_ng_z, "%5x", -0, unsigned int)
TEST_SPRINTF(x_prec_negt, "%.5x", -123, unsigned int)
TEST_SPRINTF(x_prec_post, "%.5x", 123, unsigned int)
TEST_SPRINTF(x_prec_zero_, "%.5x", 0, unsigned int)
TEST_SPRINTF(x_prec_ng_z, "%.5x", -0, unsigned int)
TEST_SPRINTF(x_width_prec_negt, "%10.5x", -123, unsigned int)
TEST_SPRINTF(x_width_prec_post, "%10.5x", 123, unsigned int)
TEST_SPRINTF(x_width_prec_zero, "%10.5x", 0, unsigned int)
TEST_SPRINTF(x_width_prec_ng_z, "%10.5x", -0, unsigned int)
TEST_SPRINTF(x_zero_prec_negt, "%.0x", -123, unsigned int)
TEST_SPRINTF(x_zero_prec_post, "%.0x", 123, unsigned int)
TEST_SPRINTF(x_zero_prec_zero, "%.0x", 0, unsigned int)
TEST_SPRINTF(x_zero_prec_ng_z, "%.0x", -0, unsigned int)
TEST_SPRINTF(x_zero_zero_negt, "%0x", -123, unsigned int)
TEST_SPRINTF(x_zero_zero_post, "%0x", 123, unsigned int)
TEST_SPRINTF(x_zero_zero_zero, "%0x", 0, unsigned int)
TEST_SPRINTF(x_zero_zero_ng_z, "%0x", -0, unsigned int)
TEST_SPRINTF(x_zero_prec_minus_zero, "%-.0x", 0, unsigned int)
TEST_SPRINTF(x_zero_prec_hash_zero, "%#.0x", 0, unsigned int)
TEST_SPRINTF(x_zero_zero_hash_zero, "%#0x", 0, unsigned int)

// Тесты для %X
TEST_SPRINTF(X_minus_negt, "%-X", -123, unsigned int)
TEST_SPRINTF(X_minus_post, "%-X", 123, unsigned int)
TEST_SPRINTF(X_minus_zero, "%-X", 0, unsigned int)
TEST_SPRINTF(X_minus_ng_z, "%-X", -0, unsigned int)
TEST_SPRINTF(X_hash_negt, "%#X", -123, unsigned int)
TEST_SPRINTF(X_hash_post, "%#X", 123, unsigned int)
TEST_SPRINTF(X_hash_zero, "%#X", 0, unsigned int)
TEST_SPRINTF(X_hash_ng_z, "%#X", -0, unsigned int)
TEST_SPRINTF(X_zero_negt, "%0X", -123, unsigned int)
TEST_SPRINTF(X_zero_post, "%0X", 123, unsigned int)
TEST_SPRINTF(X_zero_zero, "%0X", 0, unsigned int)
TEST_SPRINTF(X_zero_ng_z, "%0X", -0, unsigned int)
TEST_SPRINTF(X_width_minus_negt, "%-5X", -123, unsigned int)
TEST_SPRINTF(X_width_minus_post, "%-5X", 123, unsigned int)
TEST_SPRINTF(X_width_minus_zero, "%-5X", 0, unsigned int)
TEST_SPRINTF(X_width_minus_ng_z, "%-5X", -0, unsigned int)
TEST_SPRINTF(X_width_hash_negt, "%#5X", -123, unsigned int)
TEST_SPRINTF(X_width_hash_post, "%#5X", 123, unsigned int)
TEST_SPRINTF(X_width_hash_zero, "%#5X", 0, unsigned int)
TEST_SPRINTF(X_width_hash_ng_z, "%#5X", -0, unsigned int)
TEST_SPRINTF(X_width_zero_negt, "%05X", -123, unsigned int)
TEST_SPRINTF(X_width_zero_post, "%05X", 123, unsigned int)
TEST_SPRINTF(X_width_zero_zero, "%05X", 0, unsigned int)
TEST_SPRINTF(X_width_zero_ng_z, "%05X", -0, unsigned int)
TEST_SPRINTF(X_prec_minus_negt, "%-.5X", -123, unsigned int)
TEST_SPRINTF(X_prec_minus_post, "%-.5X", 123, unsigned int)
TEST_SPRINTF(X_prec_minus_zero, "%-.5X", 0, unsigned int)
TEST_SPRINTF(X_prec_minus_ng_z, "%-.5X", -0, unsigned int)
TEST_SPRINTF(X_prec_hash_negt, "%#.5X", -123, unsigned int)
TEST_SPRINTF(X_prec_hash_post, "%#.5X", 123, unsigned int)
TEST_SPRINTF(X_prec_hash_zero, "%#.5X", 0, unsigned int)
TEST_SPRINTF(X_prec_hash_ng_z, "%#.5X", -0, unsigned int)
TEST_SPRINTF(X_width_prec_minus_negt, "%-10.5X", -123, unsigned int)
TEST_SPRINTF(X_width_prec_minus_post, "%-10.5X", 123, unsigned int)
TEST_SPRINTF(X_width_prec_minus_zero, "%-10.5X", 0, unsigned int)
TEST_SPRINTF(X_width_prec_minus_ng_z, "%-10.5X", -0, unsigned int)
TEST_SPRINTF(X_width_prec_hash_negt, "%#10.5X", -123, unsigned int)
TEST_SPRINTF(X_width_prec_hash_post, "%#10.5X", 123, unsigned int)
TEST_SPRINTF(X_width_prec_hash_zero, "%#10.5X", 0, unsigned int)
TEST_SPRINTF(X_width_prec_hash_ng_z, "%#10.5X", -0, unsigned int)
TEST_SPRINTF(X_width_negt, "%5X", -123, unsigned int)
TEST_SPRINTF(X_width_post, "%5X", 123, unsigned int)
TEST_SPRINTF(X_width_zero, "%5X", 0, unsigned int)
TEST_SPRINTF(X_width_ng_z, "%5X", -0, unsigned int)
TEST_SPRINTF(X_prec_negt, "%.5X", -123, unsigned int)
TEST_SPRINTF(X_prec_post, "%.5X", 123, unsigned int)
TEST_SPRINTF(X_prec_zero_, "%.5X", 0, unsigned int)
TEST_SPRINTF(X_prec_ng_z, "%.5X", -0, unsigned int)
TEST_SPRINTF(X_width_prec_negt, "%10.5X", -123, unsigned int)
TEST_SPRINTF(X_width_prec_post, "%10.5X", 123, unsigned int)
TEST_SPRINTF(X_width_prec_zero, "%10.5X", 0, unsigned int)
TEST_SPRINTF(X_width_prec_ng_z, "%10.5X", -0, unsigned int)
TEST_SPRINTF(X_zero_prec_negt, "%.0X", -123, unsigned int)
TEST_SPRINTF(X_zero_prec_post, "%.0X", 123, unsigned int)
TEST_SPRINTF(X_zero_prec_zero, "%.0X", 0, unsigned int)
TEST_SPRINTF(X_zero_prec_ng_z, "%.0X", -0, unsigned int)
TEST_SPRINTF(X_zero_zero_negt, "%0X", -123, unsigned int)
TEST_SPRINTF(X_zero_zero_post, "%0X", 123, unsigned int)
TEST_SPRINTF(X_zero_zero_zero, "%0X", 0, unsigned int)
TEST_SPRINTF(X_zero_zero_ng_z, "%0X", -0, unsigned int)
TEST_SPRINTF(X_zero_prec_minus_zero, "%-.0X", 0, unsigned int)
TEST_SPRINTF(X_zero_prec_hash_zero, "%#.0X", 0, unsigned int)
TEST_SPRINTF(X_zero_zero_hash_zero, "%#0X", 0, unsigned int)

TEST_SPRINTF_2(X_dynamic_width, "%*X", 10, 123, unsigned int)
TEST_SPRINTF_2(X_dynamic_precision, "%.*X", 5, 123, unsigned int)
TEST_SPRINTF_3(X_dynamic_width_precision, "%*.*X", 10, 5, 123, unsigned int)

// Тесты для %hu ho hx hX
TEST_SPRINTF(hu_minus_negt, "%-hu", -123, unsigned short)
TEST_SPRINTF(hu_minus_post, "%-hu", 123, unsigned short)

TEST_SPRINTF(ho_minus_negt, "%-ho", -123, unsigned short)
TEST_SPRINTF(ho_minus_post, "%-ho", 123, unsigned short)
TEST_SPRINTF(hx_minus_negt, "%-hx", -123, unsigned short)
TEST_SPRINTF(hx_minus_post, "%-hx", 123, unsigned short)
TEST_SPRINTF(hX_minus_negt, "%-hX", -123, unsigned short)
TEST_SPRINTF(hX_minus_post, "%-hX", 123, unsigned short)

// ================================================================
// Тесты для флагов форматирования (f, e, E, g, G)
// ================================================================

// Тесты для %f
TEST_SPRINTF(f_minus_negt, "%-f", -123.456, double)
TEST_SPRINTF(f_minus_post, "%-f", 123.456, double)
TEST_SPRINTF(f_minus_zero_, "%-f", 0, double)
TEST_SPRINTF(f_minus_ng_z, "%-f", -0, double)
TEST_SPRINTF(f_plus_negt, "%+f", -123.456, double)
TEST_SPRINTF(f_plus_post, "%+f", 123.456, double)
TEST_SPRINTF(f_plus_zero, "%+f", 0, double)
TEST_SPRINTF(f_plus_ng_z, "%+f", -0, double)
TEST_SPRINTF(f_space_negt, "% f", -123.456, double)
TEST_SPRINTF(f_space_post, "% f", 123.456, double)
TEST_SPRINTF(f_space_zero, "% f", 0, double)
TEST_SPRINTF(f_space_ng_z, "% f", -0, double)
TEST_SPRINTF(f_hash_negt, "%#f", -123.456, double)
TEST_SPRINTF(f_hash_post, "%#f", 123.456, double)
TEST_SPRINTF(f_hash_zero, "%#f", 0, double)
TEST_SPRINTF(f_hash_ng_z, "%#f", -0, double)
TEST_SPRINTF(f_zero_negt, "%0f", -123.456, double)
TEST_SPRINTF(f_zero_post, "%0f", 123.456, double)
TEST_SPRINTF(f_zero_zero, "%0f", 0, double)
TEST_SPRINTF(f_zero_ng_z, "%0f", -0, double)
TEST_SPRINTF(f_width_minus_negt, "%-5f", -123.456, double)
TEST_SPRINTF(f_width_minus_post, "%-5f", 123.456, double)
TEST_SPRINTF(f_width_minus_zero, "%-5f", 0, double)
TEST_SPRINTF(f_width_minus_ng_z, "%-5f", -0, double)
TEST_SPRINTF(f_width_plus_negt, "%+5f", -123.456, double)
TEST_SPRINTF(f_width_plus_post, "%+5f", 123.456, double)
TEST_SPRINTF(f_width_plus_zero, "%+5f", 0, double)
TEST_SPRINTF(f_width_plus_ng_z, "%+5f", -0, double)
TEST_SPRINTF(f_width_space_negt, "% 5f", -123.456, double)
TEST_SPRINTF(f_width_space_post, "% 5f", 123.456, double)
TEST_SPRINTF(f_width_space_zero, "% 5f", 0, double)
TEST_SPRINTF(f_width_space_ng_z, "% 5f", -0, double)
TEST_SPRINTF(f_width_hash_negt, "%#5f", -123.456, double)
TEST_SPRINTF(f_width_hash_post, "%#5f", 123.456, double)
TEST_SPRINTF(f_width_hash_zero, "%#5f", 0, double)
TEST_SPRINTF(f_width_hash_ng_z, "%#5f", -0, double)
TEST_SPRINTF(f_width_zero_negt, "%05f", -123.456, double)
TEST_SPRINTF(f_width_zero_post, "%05f", 123.456, double)
TEST_SPRINTF(f_width_zero_zero, "%05f", 0, double)
TEST_SPRINTF(f_width_zero_ng_z, "%05f", -0, double)
TEST_SPRINTF(f_prec_minus_negt, "%-.5f", -1123.45623, double)
TEST_SPRINTF(f_prec_minus_post, "%-.5f", 123.456, double)
TEST_SPRINTF(f_prec_minus_zero, "%-.5f", 0, double)
TEST_SPRINTF(f_prec_minus_ng_z, "%-.5f", -0, double)
TEST_SPRINTF(f_prec_plus_negt, "%+.5f", -123.456, double)
TEST_SPRINTF(f_prec_plus_post, "%+.5f", 123.456, double)
TEST_SPRINTF(f_prec_plus_zero, "%+.5f", 0, double)
TEST_SPRINTF(f_prec_plus_ng_z, "%+.5f", -0, double)
TEST_SPRINTF(f_prec_space_negt, "% .5f", -123.456, double)
TEST_SPRINTF(f_prec_space_post, "% .5f", 123.456, double)
TEST_SPRINTF(f_prec_space_zero, "% .5f", 0, double)
TEST_SPRINTF(f_prec_space_ng_z, "% .5f", -0, double)
TEST_SPRINTF(f_prec_hash_negt, "%#.5f", -123.456, double)
TEST_SPRINTF(f_prec_hash_post, "%#.5f", 123.456, double)
TEST_SPRINTF(f_prec_hash_zero, "%#.5f", 0, double)
TEST_SPRINTF(f_prec_hash_ng_z, "%#.5f", -0, double)
TEST_SPRINTF(f_prec_zero_negt, "%0.5f", -123.456, double)
TEST_SPRINTF(f_prec_zero_post, "%0.5f", 123.456, double)
TEST_SPRINTF(f_prec_zero_zero, "%0.5f", 0, double)
TEST_SPRINTF(f_prec_zero_ng_z, "%0.5f", -0, double)
TEST_SPRINTF(f_width_prec_minus_negt, "%-10.5f", -123.456, double)
TEST_SPRINTF(f_width_prec_minus_post, "%-10.5f", 123.456, double)
TEST_SPRINTF(f_width_prec_minus_zero, "%-10.5f", 0, double)
TEST_SPRINTF(f_width_prec_minus_ng_z, "%-10.5f", -0, double)
TEST_SPRINTF(f_width_prec_plus_negt, "%+10.5f", -123.456, double)
TEST_SPRINTF(f_width_prec_plus_post, "%+10.5f", 123.456, double)
TEST_SPRINTF(f_width_prec_plus_zero, "%+10.5f", 0, double)
TEST_SPRINTF(f_width_prec_plus_ng_z, "%+10.5f", -0, double)
TEST_SPRINTF(f_width_prec_space_negt, "% 10.5f", -123.456, double)
TEST_SPRINTF(f_width_prec_space_post, "% 10.5f", 123.456, double)
TEST_SPRINTF(f_width_prec_space_zero, "% 10.5f", 0, double)
TEST_SPRINTF(f_width_prec_space_ng_z, "% 10.5f", -0, double)
TEST_SPRINTF(f_width_prec_hash_negt, "%#10.5f", -123.456, double)
TEST_SPRINTF(f_width_prec_hash_post, "%#10.5f", 123.456, double)
TEST_SPRINTF(f_width_prec_hash_zero, "%#10.5f", 0, double)
TEST_SPRINTF(f_width_prec_hash_ng_z, "%#10.5f", -0, double)
TEST_SPRINTF(f_width_prec_zero_negt, "%010.5f", -123.456, double)
TEST_SPRINTF(f_width_prec_zero_post, "%010.5f", 123.456, double)
TEST_SPRINTF(f_width_prec_zero_zero, "%010.5f", 0, double)
TEST_SPRINTF(f_width_prec_zero_ng_z, "%010.5f", -0, double)
TEST_SPRINTF_2(f_dynamic_width, "%*f", 10, 123.456, double)
TEST_SPRINTF_2(f_dynamic_precision, "%.*f", 5, 123.456, double)
TEST_SPRINTF_3(f_dynamic_width_precision, "%*.*f", 10, 5, 123.456, double)
TEST_SPRINTF(f_width_negt, "%5f", -123.456, double)
TEST_SPRINTF(f_width_post, "%5f", 123.456, double)
TEST_SPRINTF(f_width_zero, "%5f", 0, double)
TEST_SPRINTF(f_width_ng_z, "%5f", -0, double)
TEST_SPRINTF(f_prec_negt, "%.5f", -123.456, double)
TEST_SPRINTF(f_prec_post, "%.5f", 123.456, double)
TEST_SPRINTF(f_prec_zero_, "%.5f", 0, double)
TEST_SPRINTF(f_prec_ng_z, "%.5f", -0, double)
TEST_SPRINTF(f_width_prec_negt, "%10.5f", -123.456, double)
TEST_SPRINTF(f_width_prec_post, "%10.5f", 123.456, double)
TEST_SPRINTF(f_width_prec_zero, "%10.5f", 0, double)
TEST_SPRINTF(f_width_prec_ng_z, "%10.5f", -0, double)
TEST_SPRINTF(f_zero_prec_negt, "%.0f", -123.456, double)
TEST_SPRINTF(f_zero_prec_post, "%.0f", 123.456, double)
TEST_SPRINTF(f_zero_prec_zero, "%.0f", 0, double)
TEST_SPRINTF(f_zero_prec_ng_z, "%.0f", -0, double)
TEST_SPRINTF(f_zero_zero_negt, "%0f", -123.456, double)
TEST_SPRINTF(f_zero_zero_post, "%0f", 123.456, double)
TEST_SPRINTF(f_zero_zero_zero, "%0f", 0, double)
TEST_SPRINTF(f_zero_zero_ng_z, "%0f", -0, double)
TEST_SPRINTF(f_zero_prec_zero_negt, "%0.0f", -123.456, double)
TEST_SPRINTF(f_zero_prec_zero_post, "%0.0f", 123.456, double)
TEST_SPRINTF(f_zero_prec_zero_zero, "%0.0f", 0, double)
TEST_SPRINTF(f_zero_prec_zero_ng_z, "%0.0f", -0, double)
TEST_SPRINTF(f_zero_prec_minus_zero, "%-.0f", 0, double)
TEST_SPRINTF(f_zero_prec_plus_zero, "%+.0f", 0, double)
TEST_SPRINTF(f_zero_prec_space_zero, "% .0f", 0, double)
TEST_SPRINTF(f_zero_prec_hash_zero, "%#.0f", 0, double)
TEST_SPRINTF(f_zero_zero_plus_zero, "%+0f", 0, double)
TEST_SPRINTF(f_zero_zero_space_zero, "% 0f", 0, double)
TEST_SPRINTF(f_zero_zero_hash_zero, "%#0f", 0, double)
TEST_SPRINTF(f_zero_prec_zero_plus_zero, "%+0.0f", 0, double)
TEST_SPRINTF(f_zero_prec_zero_space_zero, "% 0.0f", 0, double)
TEST_SPRINTF(f_zero_prec_zero_hash_zero, "%#0.0f", 0, double)

// Тесты для %e
TEST_SPRINTF(e_minus_negt, "%-e", -123.456, double)
TEST_SPRINTF(e_minus_post, "%-e", 123.456, double)
TEST_SPRINTF(e_minus_zero_, "%-e", 0, double)
TEST_SPRINTF(e_minus_ng_z, "%-e", -0, double)
TEST_SPRINTF(e_plus_negt, "%+e", -123.456, double)
TEST_SPRINTF(e_plus_post, "%+e", 123.456, double)
TEST_SPRINTF(e_plus_zero, "%+e", 0, double)
TEST_SPRINTF(e_plus_ng_z, "%+e", -0, double)
TEST_SPRINTF(e_space_negt, "% e", -123.456, double)
TEST_SPRINTF(e_space_post, "% e", 123.456, double)
TEST_SPRINTF(e_space_zero, "% e", 0, double)
TEST_SPRINTF(e_space_ng_z, "% e", -0, double)
TEST_SPRINTF(e_hash_negt, "%#e", -123.456, double)
TEST_SPRINTF(e_hash_post, "%#e", 123.456, double)
TEST_SPRINTF(e_hash_zero, "%#e", 0, double)
TEST_SPRINTF(e_hash_ng_z, "%#e", -0, double)
TEST_SPRINTF(e_zero_negt, "%0e", -123.456, double)
TEST_SPRINTF(e_zero_post, "%0e", 123.456, double)
TEST_SPRINTF(e_zero_zero, "%0e", 0, double)
TEST_SPRINTF(e_zero_ng_z, "%0e", -0, double)
TEST_SPRINTF(e_width_minus_negt, "%-5e", -123.456, double)
TEST_SPRINTF(e_width_minus_post, "%-5e", 123.456, double)
TEST_SPRINTF(e_width_minus_zero, "%-5e", 0, double)
TEST_SPRINTF(e_width_minus_ng_z, "%-5e", -0, double)
TEST_SPRINTF(e_width_plus_negt, "%+5e", -123.456, double)
TEST_SPRINTF(e_width_plus_post, "%+5e", 123.456, double)
TEST_SPRINTF(e_width_plus_zero, "%+5e", 0, double)
TEST_SPRINTF(e_width_plus_ng_z, "%+5e", -0, double)
TEST_SPRINTF(e_width_space_negt, "% 5e", -123.456, double)
TEST_SPRINTF(e_width_space_post, "% 5e", 123.456, double)
TEST_SPRINTF(e_width_space_zero, "% 5e", 0, double)
TEST_SPRINTF(e_width_space_ng_z, "% 5e", -0, double)
TEST_SPRINTF(e_width_hash_negt, "%#5e", -123.456, double)
TEST_SPRINTF(e_width_hash_post, "%#5e", 123.456, double)
TEST_SPRINTF(e_width_hash_zero, "%#5e", 0, double)
TEST_SPRINTF(e_width_hash_ng_z, "%#5e", -0, double)
TEST_SPRINTF(e_width_zero_negt, "%05e", -123.456, double)
TEST_SPRINTF(e_width_zero_post, "%05e", 123.456, double)
TEST_SPRINTF(e_width_zero_zero, "%05e", 0, double)
TEST_SPRINTF(e_width_zero_ng_z, "%05e", -0, double)
TEST_SPRINTF(e_prec_minus_negt, "%-.5e", -1123.45623, double)
TEST_SPRINTF(e_prec_minus_post, "%-.5e", 123.456, double)
TEST_SPRINTF(e_prec_minus_zero, "%-.5e", 0, double)
TEST_SPRINTF(e_prec_minus_ng_z, "%-.5e", -0, double)
TEST_SPRINTF(e_prec_plus_negt, "%+.5e", -123.456, double)
TEST_SPRINTF(e_prec_plus_post, "%+.5e", 123.456, double)
TEST_SPRINTF(e_prec_plus_zero, "%+.5e", 0, double)
TEST_SPRINTF(e_prec_plus_ng_z, "%+.5e", -0, double)
TEST_SPRINTF(e_prec_space_negt, "% .5e", -123.456, double)
TEST_SPRINTF(e_prec_space_post, "% .5e", 123.456, double)
TEST_SPRINTF(e_prec_space_zero, "% .5e", 0, double)
TEST_SPRINTF(e_prec_space_ng_z, "% .5e", -0, double)
TEST_SPRINTF(e_prec_hash_negt, "%#.5e", -123.456, double)
TEST_SPRINTF(e_prec_hash_post, "%#.5e", 123.456, double)
TEST_SPRINTF(e_prec_hash_zero, "%#.5e", 0, double)
TEST_SPRINTF(e_prec_hash_ng_z, "%#.5e", -0, double)
TEST_SPRINTF(e_prec_zero_negt, "%0.5e", -123.456, double)
TEST_SPRINTF(e_prec_zero_post, "%0.5e", 123.456, double)
TEST_SPRINTF(e_prec_zero_zero, "%0.5e", 0, double)
TEST_SPRINTF(e_prec_zero_ng_z, "%0.5e", -0, double)
TEST_SPRINTF(e_width_prec_minus_negt, "%-10.5e", -123.456, double)
TEST_SPRINTF(e_width_prec_minus_post, "%-10.5e", 123.456, double)
TEST_SPRINTF(e_width_prec_minus_zero, "%-10.5e", 0, double)
TEST_SPRINTF(e_width_prec_minus_ng_z, "%-10.5e", -0, double)
TEST_SPRINTF(e_width_prec_plus_negt, "%+10.5e", -123.456, double)
TEST_SPRINTF(e_width_prec_plus_post, "%+10.5e", 123.456, double)
TEST_SPRINTF(e_width_prec_plus_zero, "%+10.5e", 0, double)
TEST_SPRINTF(e_width_prec_plus_ng_z, "%+10.5e", -0, double)
TEST_SPRINTF(e_width_prec_space_negt, "% 10.5e", -123.456, double)
TEST_SPRINTF(e_width_prec_space_post, "% 10.5e", 123.456, double)
TEST_SPRINTF(e_width_prec_space_zero, "% 10.5e", 0, double)
TEST_SPRINTF(e_width_prec_space_ng_z, "% 10.5e", -0, double)
TEST_SPRINTF(e_width_prec_hash_negt, "%#10.5e", -123.456, double)
TEST_SPRINTF(e_width_prec_hash_post, "%#10.5e", 123.456, double)
TEST_SPRINTF(e_width_prec_hash_zero, "%#10.5e", 0, double)
TEST_SPRINTF(e_width_prec_hash_ng_z, "%#10.5e", -0, double)
TEST_SPRINTF(e_width_prec_zero_negt, "%010.5e", -123.456, double)
TEST_SPRINTF(e_width_prec_zero_post, "%010.5e", 123.456, double)
TEST_SPRINTF(e_width_prec_zero_zero, "%010.5e", 0, double)
TEST_SPRINTF(e_width_prec_zero_ng_z, "%010.5e", -0, double)
TEST_SPRINTF_2(e_dynamic_width, "%*e", 10, 123.456, double)
TEST_SPRINTF_2(e_dynamic_precision, "%.*e", 5, 123.456, double)
TEST_SPRINTF_3(e_dynamic_width_precision, "%*.*e", 10, 5, 123.456, double)
TEST_SPRINTF(e_width_negt, "%5e", -123.456, double)
TEST_SPRINTF(e_width_post, "%5e", 123.456, double)
TEST_SPRINTF(e_width_zero, "%5e", 0, double)
TEST_SPRINTF(e_width_ng_z, "%5e", -0, double)
TEST_SPRINTF(e_prec_negt, "%.5e", -123.456, double)
TEST_SPRINTF(e_prec_post, "%.5e", 123.456, double)
TEST_SPRINTF(e_prec_zero_, "%.5e", 0, double)
TEST_SPRINTF(e_prec_ng_z, "%.5e", -0, double)
TEST_SPRINTF(e_width_prec_negt, "%10.5e", -123.456, double)
TEST_SPRINTF(e_width_prec_post, "%10.5e", 123.456, double)
TEST_SPRINTF(e_width_prec_zero, "%10.5e", 0, double)
TEST_SPRINTF(e_width_prec_ng_z, "%10.5e", -0, double)
TEST_SPRINTF(e_zero_prec_negt, "%.0e", -123.456, double)
TEST_SPRINTF(e_zero_prec_post, "%.0e", 123.456, double)
TEST_SPRINTF(e_zero_prec_zero, "%.0e", 0, double)
TEST_SPRINTF(e_zero_prec_ng_z, "%.0e", -0, double)
TEST_SPRINTF(e_zero_zero_negt, "%0e", -123.456, double)
TEST_SPRINTF(e_zero_zero_post, "%0e", 123.456, double)
TEST_SPRINTF(e_zero_zero_zero, "%0e", 0, double)
TEST_SPRINTF(e_zero_zero_ng_z, "%0e", -0, double)
TEST_SPRINTF(e_zero_prec_zero_negt, "%0.0e", -123.456, double)
TEST_SPRINTF(e_zero_prec_zero_post, "%0.0e", 123.456, double)
TEST_SPRINTF(e_zero_prec_zero_zero, "%0.0e", 0, double)
TEST_SPRINTF(e_zero_prec_zero_ng_z, "%0.0e", -0, double)
TEST_SPRINTF(e_zero_prec_minus_zero, "%-.0e", 0, double)
TEST_SPRINTF(e_zero_prec_plus_zero, "%+.0e", 0, double)
TEST_SPRINTF(e_zero_prec_space_zero, "% .0e", 0, double)
TEST_SPRINTF(e_zero_prec_hash_zero, "%#.0e", 0, double)
TEST_SPRINTF(e_zero_zero_plus_zero, "%+0e", 0, double)
TEST_SPRINTF(e_zero_zero_space_zero, "% 0e", 0, double)
TEST_SPRINTF(e_zero_zero_hash_zero, "%#0e", 0, double)
TEST_SPRINTF(e_zero_prec_zero_plus_zero, "%+0.0e", 0, double)
TEST_SPRINTF(e_zero_prec_zero_space_zero, "% 0.0e", 0, double)
TEST_SPRINTF(e_zero_prec_zero_hash_zero, "%#0.0e", 0, double)

// Тесты для %e
TEST_SPRINTF(E_minus_negt, "%-E", -123.456, double)
TEST_SPRINTF(E_minus_post, "%-E", 123.456, double)
TEST_SPRINTF(E_minus_zero_, "%-E", 0, double)
TEST_SPRINTF(E_minus_ng_z, "%-E", -0, double)
TEST_SPRINTF(E_plus_negt, "%+E", -123.456, double)
TEST_SPRINTF(E_plus_post, "%+E", 123.456, double)
TEST_SPRINTF(E_plus_zero, "%+E", 0, double)
TEST_SPRINTF(E_plus_ng_z, "%+E", -0, double)
TEST_SPRINTF(E_space_negt, "% E", -123.456, double)
TEST_SPRINTF(E_space_post, "% E", 123.456, double)
TEST_SPRINTF(E_space_zero, "% E", 0, double)
TEST_SPRINTF(E_space_ng_z, "% E", -0, double)
TEST_SPRINTF(E_hash_negt, "%#E", -123.456, double)
TEST_SPRINTF(E_hash_post, "%#E", 123.456, double)
TEST_SPRINTF(E_hash_zero, "%#E", 0, double)
TEST_SPRINTF(E_hash_ng_z, "%#E", -0, double)
TEST_SPRINTF(E_zero_negt, "%0E", -123.456, double)
TEST_SPRINTF(E_zero_post, "%0E", 123.456, double)
TEST_SPRINTF(E_zero_zero, "%0E", 0, double)
TEST_SPRINTF(E_zero_ng_z, "%0E", -0, double)
TEST_SPRINTF(E_width_minus_negt, "%-5E", -123.456, double)
TEST_SPRINTF(E_width_minus_post, "%-5E", 123.456, double)
TEST_SPRINTF(E_width_minus_zero, "%-5E", 0, double)
TEST_SPRINTF(E_width_minus_ng_z, "%-5E", -0, double)
TEST_SPRINTF(E_width_plus_negt, "%+5E", -123.456, double)
TEST_SPRINTF(E_width_plus_post, "%+5E", 123.456, double)
TEST_SPRINTF(E_width_plus_zero, "%+5E", 0, double)
TEST_SPRINTF(E_width_plus_ng_z, "%+5E", -0, double)
TEST_SPRINTF(E_width_space_negt, "% 5E", -123.456, double)
TEST_SPRINTF(E_width_space_post, "% 5E", 123.456, double)
TEST_SPRINTF(E_width_space_zero, "% 5E", 0, double)
TEST_SPRINTF(E_width_space_ng_z, "% 5E", -0, double)
TEST_SPRINTF(E_width_hash_negt, "%#5E", -123.456, double)
TEST_SPRINTF(E_width_hash_post, "%#5E", 123.456, double)
TEST_SPRINTF(E_width_hash_zero, "%#5E", 0, double)
TEST_SPRINTF(E_width_hash_ng_z, "%#5E", -0, double)
TEST_SPRINTF(E_width_zero_negt, "%05E", -123.456, double)
TEST_SPRINTF(E_width_zero_post, "%05E", 123.456, double)
TEST_SPRINTF(E_width_zero_zero, "%05E", 0, double)
TEST_SPRINTF(E_width_zero_ng_z, "%05E", -0, double)
TEST_SPRINTF(E_prec_minus_negt, "%-.5E", -1123.45623, double)
TEST_SPRINTF(E_prec_minus_post, "%-.5E", 123.456, double)
TEST_SPRINTF(E_prec_minus_zero, "%-.5E", 0, double)
TEST_SPRINTF(E_prec_minus_ng_z, "%-.5E", -0, double)
TEST_SPRINTF(E_prec_plus_negt, "%+.5E", -123.456, double)
TEST_SPRINTF(E_prec_plus_post, "%+.5E", 123.456, double)
TEST_SPRINTF(E_prec_plus_zero, "%+.5E", 0, double)
TEST_SPRINTF(E_prec_plus_ng_z, "%+.5E", -0, double)
TEST_SPRINTF(E_prec_space_negt, "% .5E", -123.456, double)
TEST_SPRINTF(E_prec_space_post, "% .5E", 123.456, double)
TEST_SPRINTF(E_prec_space_zero, "% .5E", 0, double)
TEST_SPRINTF(E_prec_space_ng_z, "% .5E", -0, double)
TEST_SPRINTF(E_prec_hash_negt, "%#.5E", -123.456, double)
TEST_SPRINTF(E_prec_hash_post, "%#.5E", 123.456, double)
TEST_SPRINTF(E_prec_hash_zero, "%#.5E", 0, double)
TEST_SPRINTF(E_prec_hash_ng_z, "%#.5E", -0, double)
TEST_SPRINTF(E_prec_zero_negt, "%0.5E", -123.456, double)
TEST_SPRINTF(E_prec_zero_post, "%0.5E", 123.456, double)
TEST_SPRINTF(E_prec_zero_zero, "%0.5E", 0, double)
TEST_SPRINTF(E_prec_zero_ng_z, "%0.5E", -0, double)
TEST_SPRINTF(E_width_prec_minus_negt, "%-10.5E", -123.456, double)
TEST_SPRINTF(E_width_prec_minus_post, "%-10.5E", 123.456, double)
TEST_SPRINTF(E_width_prec_minus_zero, "%-10.5E", 0, double)
TEST_SPRINTF(E_width_prec_minus_ng_z, "%-10.5E", -0, double)
TEST_SPRINTF(E_width_prec_plus_negt, "%+10.5E", -123.456, double)
TEST_SPRINTF(E_width_prec_plus_post, "%+10.5E", 123.456, double)
TEST_SPRINTF(E_width_prec_plus_zero, "%+10.5E", 0, double)
TEST_SPRINTF(E_width_prec_plus_ng_z, "%+10.5E", -0, double)
TEST_SPRINTF(E_width_prec_space_negt, "% 10.5E", -123.456, double)
TEST_SPRINTF(E_width_prec_space_post, "% 10.5E", 123.456, double)
TEST_SPRINTF(E_width_prec_space_zero, "% 10.5E", 0, double)
TEST_SPRINTF(E_width_prec_space_ng_z, "% 10.5E", -0, double)
TEST_SPRINTF(E_width_prec_hash_negt, "%#10.5E", -123.456, double)
TEST_SPRINTF(E_width_prec_hash_post, "%#10.5E", 123.456, double)
TEST_SPRINTF(E_width_prec_hash_zero, "%#10.5E", 0, double)
TEST_SPRINTF(E_width_prec_hash_ng_z, "%#10.5E", -0, double)
TEST_SPRINTF(E_width_prec_zero_negt, "%010.5E", -123.456, double)
TEST_SPRINTF(E_width_prec_zero_post, "%010.5E", 123.456, double)
TEST_SPRINTF(E_width_prec_zero_zero, "%010.5E", 0, double)
TEST_SPRINTF(E_width_prec_zero_ng_z, "%010.5E", -0, double)
TEST_SPRINTF_2(E_dynamic_width, "%*E", 10, 123.456, double)
TEST_SPRINTF_2(E_dynamic_precision, "%.*E", 5, 123.456, double)
TEST_SPRINTF_3(E_dynamic_width_precision, "%*.*E", 10, 5, 123.456, double)
TEST_SPRINTF(E_width_negt, "%5E", -123.456, double)
TEST_SPRINTF(E_width_post, "%5E", 123.456, double)
TEST_SPRINTF(E_width_zero, "%5E", 0, double)
TEST_SPRINTF(E_width_ng_z, "%5E", -0, double)
TEST_SPRINTF(E_prec_negt, "%.5E", -123.456, double)
TEST_SPRINTF(E_prec_post, "%.5E", 123.456, double)
TEST_SPRINTF(E_prec_zero_, "%.5E", 0, double)
TEST_SPRINTF(E_prec_ng_z, "%.5E", -0, double)
TEST_SPRINTF(E_width_prec_negt, "%10.5E", -123.456, double)
TEST_SPRINTF(E_width_prec_post, "%10.5E", 123.456, double)
TEST_SPRINTF(E_width_prec_zero, "%10.5E", 0, double)
TEST_SPRINTF(E_width_prec_ng_z, "%10.5E", -0, double)
TEST_SPRINTF(E_zero_prec_negt, "%.0E", -123.456, double)
TEST_SPRINTF(E_zero_prec_post, "%.0E", 123.456, double)
TEST_SPRINTF(E_zero_prec_zero, "%.0E", 0, double)
TEST_SPRINTF(E_zero_prec_ng_z, "%.0E", -0, double)
TEST_SPRINTF(E_zero_zero_negt, "%0E", -123.456, double)
TEST_SPRINTF(E_zero_zero_post, "%0E", 123.456, double)
TEST_SPRINTF(E_zero_zero_zero, "%0E", 0, double)
TEST_SPRINTF(E_zero_zero_ng_z, "%0E", -0, double)
TEST_SPRINTF(E_zero_prec_zero_negt, "%0.0E", -123.456, double)
TEST_SPRINTF(E_zero_prec_zero_post, "%0.0E", 123.456, double)
TEST_SPRINTF(E_zero_prec_zero_zero, "%0.0E", 0, double)
TEST_SPRINTF(E_zero_prec_zero_ng_z, "%0.0E", -0, double)
TEST_SPRINTF(E_zero_prec_minus_zero, "%-.0E", 0, double)
TEST_SPRINTF(E_zero_prec_plus_zero, "%+.0E", 0, double)
TEST_SPRINTF(E_zero_prec_space_zero, "% .0E", 0, double)
TEST_SPRINTF(E_zero_prec_hash_zero, "%#.0E", 0, double)
TEST_SPRINTF(E_zero_zero_plus_zero, "%+0E", 0, double)
TEST_SPRINTF(E_zero_zero_space_zero, "% 0E", 0, double)
TEST_SPRINTF(E_zero_zero_hash_zero, "%#0E", 0, double)
TEST_SPRINTF(E_zero_prec_zero_plus_zero, "%+0.0E", 0, double)
TEST_SPRINTF(E_zero_prec_zero_space_zero, "% 0.0E", 0, double)
TEST_SPRINTF(E_zero_prec_zero_hash_zero, "%#0.0E", 0, double)

// Тесты для %e
TEST_SPRINTF(g_minus_negt, "%-g", -123.456, double)
TEST_SPRINTF(g_minus_post, "%-g", 123.456, double)
TEST_SPRINTF(g_minus_zero_, "%-g", 0, double)
TEST_SPRINTF(g_minus_ng_z, "%-g", -0, double)
TEST_SPRINTF(g_plus_negt, "%+g", -123.456, double)
TEST_SPRINTF(g_plus_post, "%+g", 123.456, double)
TEST_SPRINTF(g_plus_zero, "%+g", 0, double)
TEST_SPRINTF(g_plus_ng_z, "%+g", -0, double)
TEST_SPRINTF(g_space_negt, "% g", -123.456, double)
TEST_SPRINTF(g_space_post, "% g", 123.456, double)
TEST_SPRINTF(g_space_zero, "% g", 0, double)
TEST_SPRINTF(g_space_ng_z, "% g", -0, double)
TEST_SPRINTF(g_hash_negt, "%#g", -123.456, double)
TEST_SPRINTF(g_hash_post, "%#g", 123.456, double)
TEST_SPRINTF(g_hash_zero, "%#g", 0, double)
TEST_SPRINTF(g_hash_ng_z, "%#g", -0, double)
TEST_SPRINTF(g_zero_negt, "%0g", -123.456, double)
TEST_SPRINTF(g_zero_post, "%0g", 123.456, double)
TEST_SPRINTF(g_zero_zero, "%0g", 0, double)
TEST_SPRINTF(g_zero_ng_z, "%0g", -0, double)
TEST_SPRINTF(g_width_minus_negt, "%-5g", -123.456, double)
TEST_SPRINTF(g_width_minus_post, "%-5g", 123.456, double)
TEST_SPRINTF(g_width_minus_zero, "%-5g", 0, double)
TEST_SPRINTF(g_width_minus_ng_z, "%-5g", -0, double)
TEST_SPRINTF(g_width_plus_negt, "%+5g", -123.456, double)
TEST_SPRINTF(g_width_plus_post, "%+5g", 123.456, double)
TEST_SPRINTF(g_width_plus_zero, "%+5g", 0, double)
TEST_SPRINTF(g_width_plus_ng_z, "%+5g", -0, double)
TEST_SPRINTF(g_width_space_negt, "% 5g", -123.456, double)
TEST_SPRINTF(g_width_space_post, "% 5g", 123.456, double)
TEST_SPRINTF(g_width_space_zero, "% 5g", 0, double)
TEST_SPRINTF(g_width_space_ng_z, "% 5g", -0, double)
TEST_SPRINTF(g_width_hash_negt, "%#5g", -123.456, double)
TEST_SPRINTF(g_width_hash_post, "%#5g", 123.456, double)
TEST_SPRINTF(g_width_hash_zero, "%#5g", 0, double)
TEST_SPRINTF(g_width_hash_ng_z, "%#5g", -0, double)
TEST_SPRINTF(g_width_zero_negt, "%05g", -123.456, double)
TEST_SPRINTF(g_width_zero_post, "%05g", 123.456, double)
TEST_SPRINTF(g_width_zero_zero, "%05g", 0, double)
TEST_SPRINTF(g_width_zero_ng_z, "%05g", -0, double)
TEST_SPRINTF(g_prec_minus_negt, "%-.5g", -1123.45623, double)
TEST_SPRINTF(g_prec_minus_post, "%-.5g", 123.456, double)
TEST_SPRINTF(g_prec_minus_zero, "%-.5g", 0, double)
TEST_SPRINTF(g_prec_minus_ng_z, "%-.5g", -0, double)
TEST_SPRINTF(g_prec_plus_negt, "%+.5g", -123.456, double)
TEST_SPRINTF(g_prec_plus_post, "%+.5g", 123.456, double)
TEST_SPRINTF(g_prec_plus_zero, "%+.5g", 0, double)
TEST_SPRINTF(g_prec_plus_ng_z, "%+.5g", -0, double)
TEST_SPRINTF(g_prec_space_negt, "% .5g", -123.456, double)
TEST_SPRINTF(g_prec_space_post, "% .5g", 123.456, double)
TEST_SPRINTF(g_prec_space_zero, "% .5g", 0, double)
TEST_SPRINTF(g_prec_space_ng_z, "% .5g", -0, double)
TEST_SPRINTF(g_prec_hash_negt, "%#.5g", -123.456, double)
TEST_SPRINTF(g_prec_hash_post, "%#.5g", 123.456, double)
TEST_SPRINTF(g_prec_hash_zero, "%#.5g", 0, double)
TEST_SPRINTF(g_prec_hash_ng_z, "%#.5g", -0, double)
TEST_SPRINTF(g_prec_zero_negt, "%0.5g", -123.456, double)
TEST_SPRINTF(g_prec_zero_post, "%0.5g", 123.456, double)
TEST_SPRINTF(g_prec_zero_zero, "%0.5g", 0, double)
TEST_SPRINTF(g_prec_zero_ng_z, "%0.5g", -0, double)
TEST_SPRINTF(g_width_prec_minus_negt, "%-10.5g", -123.456, double)
TEST_SPRINTF(g_width_prec_minus_post, "%-10.5g", 123.456, double)
TEST_SPRINTF(g_width_prec_minus_zero, "%-10.5g", 0, double)
TEST_SPRINTF(g_width_prec_minus_ng_z, "%-10.5g", -0, double)
TEST_SPRINTF(g_width_prec_plus_negt, "%+10.5g", -123.456, double)
TEST_SPRINTF(g_width_prec_plus_post, "%+10.5g", 123.456, double)
TEST_SPRINTF(g_width_prec_plus_zero, "%+10.5g", 0, double)
TEST_SPRINTF(g_width_prec_plus_ng_z, "%+10.5g", -0, double)
TEST_SPRINTF(g_width_prec_space_negt, "% 10.5g", -123.456, double)
TEST_SPRINTF(g_width_prec_space_post, "% 10.5g", 123.456, double)
TEST_SPRINTF(g_width_prec_space_zero, "% 10.5g", 0, double)
TEST_SPRINTF(g_width_prec_space_ng_z, "% 10.5g", -0, double)
TEST_SPRINTF(g_width_prec_hash_negt, "%#10.5g", -123.456, double)
TEST_SPRINTF(g_width_prec_hash_post, "%#10.5g", 123.456, double)
TEST_SPRINTF(g_width_prec_hash_zero, "%#10.5g", 0, double)
TEST_SPRINTF(g_width_prec_hash_ng_z, "%#10.5g", -0, double)
TEST_SPRINTF(g_width_prec_zero_negt, "%010.5g", -123.456, double)
TEST_SPRINTF(g_width_prec_zero_post, "%010.5g", 123.456, double)
TEST_SPRINTF(g_width_prec_zero_zero, "%010.5g", 0, double)
TEST_SPRINTF(g_width_prec_zero_ng_z, "%010.5g", -0, double)
TEST_SPRINTF_2(g_dynamic_width, "%*g", 10, 123.456, double)
TEST_SPRINTF_2(g_dynamic_precision, "%.*g", 5, 123.456, double)
TEST_SPRINTF_3(g_dynamic_width_precision, "%*.*g", 10, 5, 123.456, double)
TEST_SPRINTF(g_width_negt, "%5g", -123.456, double)
TEST_SPRINTF(g_width_post, "%5g", 123.456, double)
TEST_SPRINTF(g_width_zero, "%5g", 0, double)
TEST_SPRINTF(g_width_ng_z, "%5g", -0, double)
TEST_SPRINTF(g_prec_negt, "%.5g", -123.456, double)
TEST_SPRINTF(g_prec_post, "%.5g", 123.456, double)
TEST_SPRINTF(g_prec_zero_, "%.5g", 0, double)
TEST_SPRINTF(g_prec_ng_z, "%.5g", -0, double)
TEST_SPRINTF(g_width_prec_negt, "%10.5g", -123.456, double)
TEST_SPRINTF(g_width_prec_post, "%10.5g", 123.456, double)
TEST_SPRINTF(g_width_prec_zero, "%10.5g", 0, double)
TEST_SPRINTF(g_width_prec_ng_z, "%10.5g", -0, double)
TEST_SPRINTF(g_zero_prec_negt, "%.0g", -123.456, double)
TEST_SPRINTF(g_zero_prec_post, "%.0g", 123.456, double)
TEST_SPRINTF(g_zero_prec_zero, "%.0g", 0, double)
TEST_SPRINTF(g_zero_prec_ng_z, "%.0g", -0, double)
TEST_SPRINTF(g_zero_zero_negt, "%0g", -123.456, double)
TEST_SPRINTF(g_zero_zero_post, "%0g", 123.456, double)
TEST_SPRINTF(g_zero_zero_zero, "%0g", 0, double)
TEST_SPRINTF(g_zero_zero_ng_z, "%0g", -0, double)
TEST_SPRINTF(g_zero_prec_zero_negt, "%0.0g", -123.456, double)
TEST_SPRINTF(g_zero_prec_zero_post, "%0.0g", 123.456, double)
TEST_SPRINTF(g_zero_prec_zero_zero, "%0.0g", 0, double)
TEST_SPRINTF(g_zero_prec_zero_ng_z, "%0.0g", -0, double)
TEST_SPRINTF(g_zero_prec_minus_zero, "%-.0g", 0, double)
TEST_SPRINTF(g_zero_prec_plus_zero, "%+.0g", 0, double)
TEST_SPRINTF(g_zero_prec_space_zero, "% .0g", 0, double)
TEST_SPRINTF(g_zero_prec_hash_zero, "%#.0g", 0, double)
TEST_SPRINTF(g_zero_zero_plus_zero, "%+0g", 0, double)
TEST_SPRINTF(g_zero_zero_space_zero, "% 0g", 0, double)
TEST_SPRINTF(g_zero_zero_hash_zero, "%#0g", 0, double)
TEST_SPRINTF(g_zero_prec_zero_plus_zero, "%+0.0g", 0, double)
TEST_SPRINTF(g_zero_prec_zero_space_zero, "% 0.0g", 0, double)
TEST_SPRINTF(g_zero_prec_zero_hash_zero, "%#0.0g", 0, double)

// Тесты для %e
TEST_SPRINTF(G_minus_negt, "%-G", -123.456, double)
TEST_SPRINTF(G_minus_post, "%-G", 123.456, double)
TEST_SPRINTF(G_minus_zero_, "%-G", 0, double)
TEST_SPRINTF(G_minus_ng_z, "%-G", -0, double)
TEST_SPRINTF(G_plus_negt, "%+G", -123.456, double)
TEST_SPRINTF(G_plus_post, "%+G", 123.456, double)
TEST_SPRINTF(G_plus_zero, "%+G", 0, double)
TEST_SPRINTF(G_plus_ng_z, "%+G", -0, double)
TEST_SPRINTF(G_space_negt, "% G", -123.456, double)
TEST_SPRINTF(G_space_post, "% G", 123.456, double)
TEST_SPRINTF(G_space_zero, "% G", 0, double)
TEST_SPRINTF(G_space_ng_z, "% G", -0, double)
TEST_SPRINTF(G_hash_negt, "%#G", -123.456, double)
TEST_SPRINTF(G_hash_post, "%#G", 123.456, double)
TEST_SPRINTF(G_hash_zero, "%#G", 0, double)
TEST_SPRINTF(G_hash_ng_z, "%#G", -0, double)
TEST_SPRINTF(G_zero_negt, "%0G", -123.456, double)
TEST_SPRINTF(G_zero_post, "%0G", 123.456, double)
TEST_SPRINTF(G_zero_zero, "%0G", 0, double)
TEST_SPRINTF(G_zero_ng_z, "%0G", -0, double)
TEST_SPRINTF(G_width_minus_negt, "%-5G", -123.456, double)
TEST_SPRINTF(G_width_minus_post, "%-5G", 123.456, double)
TEST_SPRINTF(G_width_minus_zero, "%-5G", 0, double)
TEST_SPRINTF(G_width_minus_ng_z, "%-5G", -0, double)
TEST_SPRINTF(G_width_plus_negt, "%+5G", -123.456, double)
TEST_SPRINTF(G_width_plus_post, "%+5G", 123.456, double)
TEST_SPRINTF(G_width_plus_zero, "%+5G", 0, double)
TEST_SPRINTF(G_width_plus_ng_z, "%+5G", -0, double)
TEST_SPRINTF(G_width_space_negt, "% 5G", -123.456, double)
TEST_SPRINTF(G_width_space_post, "% 5G", 123.456, double)
TEST_SPRINTF(G_width_space_zero, "% 5G", 0, double)
TEST_SPRINTF(G_width_space_ng_z, "% 5G", -0, double)
TEST_SPRINTF(G_width_hash_negt, "%#5G", -123.456, double)
TEST_SPRINTF(G_width_hash_post, "%#5G", 123.456, double)
TEST_SPRINTF(G_width_hash_zero, "%#5G", 0, double)
TEST_SPRINTF(G_width_hash_ng_z, "%#5G", -0, double)
TEST_SPRINTF(G_width_zero_negt, "%05G", -123.456, double)
TEST_SPRINTF(G_width_zero_post, "%05G", 123.456, double)
TEST_SPRINTF(G_width_zero_zero, "%05G", 0, double)
TEST_SPRINTF(G_width_zero_ng_z, "%05G", -0, double)
TEST_SPRINTF(G_prec_minus_negt, "%-.5G", -1123.45623, double)
TEST_SPRINTF(G_prec_minus_post, "%-.5G", 123.456, double)
TEST_SPRINTF(G_prec_minus_zero, "%-.5G", 0, double)
TEST_SPRINTF(G_prec_minus_ng_z, "%-.5G", -0, double)
TEST_SPRINTF(G_prec_plus_negt, "%+.5G", -123.456, double)
TEST_SPRINTF(G_prec_plus_post, "%+.5G", 123.456, double)
TEST_SPRINTF(G_prec_plus_zero, "%+.5G", 0, double)
TEST_SPRINTF(G_prec_plus_ng_z, "%+.5G", -0, double)
TEST_SPRINTF(G_prec_space_negt, "% .5G", -123.456, double)
TEST_SPRINTF(G_prec_space_post, "% .5G", 123.456, double)
TEST_SPRINTF(G_prec_space_zero, "% .5G", 0, double)
TEST_SPRINTF(G_prec_space_ng_z, "% .5G", -0, double)
TEST_SPRINTF(G_prec_hash_negt, "%#.5G", -123.456, double)
TEST_SPRINTF(G_prec_hash_post, "%#.5G", 123.456, double)
TEST_SPRINTF(G_prec_hash_zero, "%#.5G", 0, double)
TEST_SPRINTF(G_prec_hash_ng_z, "%#.5G", -0, double)
TEST_SPRINTF(G_prec_zero_negt, "%0.5G", -123.456, double)
TEST_SPRINTF(G_prec_zero_post, "%0.5G", 123.456, double)
TEST_SPRINTF(G_prec_zero_zero, "%0.5G", 0, double)
TEST_SPRINTF(G_prec_zero_ng_z, "%0.5G", -0, double)
TEST_SPRINTF(G_width_prec_minus_negt, "%-10.5G", -123.456, double)
TEST_SPRINTF(G_width_prec_minus_post, "%-10.5G", 123.456, double)
TEST_SPRINTF(G_width_prec_minus_zero, "%-10.5G", 0, double)
TEST_SPRINTF(G_width_prec_minus_ng_z, "%-10.5G", -0, double)
TEST_SPRINTF(G_width_prec_plus_negt, "%+10.5G", -123.456, double)
TEST_SPRINTF(G_width_prec_plus_post, "%+10.5G", 123.456, double)
TEST_SPRINTF(G_width_prec_plus_zero, "%+10.5G", 0, double)
TEST_SPRINTF(G_width_prec_plus_ng_z, "%+10.5G", -0, double)
TEST_SPRINTF(G_width_prec_space_negt, "% 10.5G", -123.456, double)
TEST_SPRINTF(G_width_prec_space_post, "% 10.5G", 123.456, double)
TEST_SPRINTF(G_width_prec_space_zero, "% 10.5G", 0, double)
TEST_SPRINTF(G_width_prec_space_ng_z, "% 10.5G", -0, double)
TEST_SPRINTF(G_width_prec_hash_negt, "%#10.5G", -123.456, double)
TEST_SPRINTF(G_width_prec_hash_post, "%#10.5G", 123.456, double)
TEST_SPRINTF(G_width_prec_hash_zero, "%#10.5G", 0, double)
TEST_SPRINTF(G_width_prec_hash_ng_z, "%#10.5G", -0, double)
TEST_SPRINTF(G_width_prec_zero_negt, "%010.5G", -123.456, double)
TEST_SPRINTF(G_width_prec_zero_post, "%010.5G", 123.456, double)
TEST_SPRINTF(G_width_prec_zero_zero, "%010.5G", 0, double)
TEST_SPRINTF(G_width_prec_zero_ng_z, "%010.5G", -0, double)
TEST_SPRINTF_2(G_dynamic_width, "%*G", 10, 123.456, double)
TEST_SPRINTF_2(G_dynamic_precision, "%.*G", 5, 123.456, double)
TEST_SPRINTF_3(G_dynamic_width_precision, "%*.*G", 10, 5, 123.456, double)
TEST_SPRINTF(G_width_negt, "%5G", -123.456, double)
TEST_SPRINTF(G_width_post, "%5G", 123.456, double)
TEST_SPRINTF(G_width_zero, "%5G", 0, double)
TEST_SPRINTF(G_width_ng_z, "%5G", -0, double)
TEST_SPRINTF(G_prec_negt, "%.5G", -123.456, double)
TEST_SPRINTF(G_prec_post, "%.5G", 123.456, double)
TEST_SPRINTF(G_prec_zero_, "%.5G", 0, double)
TEST_SPRINTF(G_prec_ng_z, "%.5G", -0, double)
TEST_SPRINTF(G_width_prec_negt, "%10.5G", -123.456, double)
TEST_SPRINTF(G_width_prec_post, "%10.5G", 123.456, double)
TEST_SPRINTF(G_width_prec_zero, "%10.5G", 0, double)
TEST_SPRINTF(G_width_prec_ng_z, "%10.5G", -0, double)
TEST_SPRINTF(G_zero_prec_negt, "%.0G", -123.456, double)
TEST_SPRINTF(G_zero_prec_post, "%.0G", 123.456, double)
TEST_SPRINTF(G_zero_prec_zero, "%.0G", 0, double)
TEST_SPRINTF(G_zero_prec_ng_z, "%.0G", -0, double)
TEST_SPRINTF(G_zero_zero_negt, "%0G", -123.456, double)
TEST_SPRINTF(G_zero_zero_post, "%0G", 123.456, double)
TEST_SPRINTF(G_zero_zero_zero, "%0G", 0, double)
TEST_SPRINTF(G_zero_zero_ng_z, "%0G", -0, double)
TEST_SPRINTF(G_zero_prec_zero_negt, "%0.0G", -123.456, double)
TEST_SPRINTF(G_zero_prec_zero_post, "%0.0G", 123.456, double)
TEST_SPRINTF(G_zero_prec_zero_zero, "%0.0G", 0, double)
TEST_SPRINTF(G_zero_prec_zero_ng_z, "%0.0G", -0, double)
TEST_SPRINTF(G_zero_prec_minus_zero, "%-.0G", 0, double)
TEST_SPRINTF(G_zero_prec_plus_zero, "%+.0G", 0, double)
TEST_SPRINTF(G_zero_prec_space_zero, "% .0G", 0, double)
TEST_SPRINTF(G_zero_prec_hash_zero, "%#.0G", 0, double)
TEST_SPRINTF(G_zero_zero_plus_zero, "%+0G", 0, double)
TEST_SPRINTF(G_zero_zero_space_zero, "% 0G", 0, double)
TEST_SPRINTF(G_zero_zero_hash_zero, "%#0G", 0, double)
TEST_SPRINTF(G_zero_prec_zero_plus_zero, "%+0.0G", 0, double)
TEST_SPRINTF(G_zero_prec_zero_space_zero, "% 0.0G", 0, double)
TEST_SPRINTF(G_zero_prec_zero_hash_zero, "%#0.0G", 0, double)
// ================================================================
// Тесты для строковых спецификаторов (s, c)
// ================================================================

// Тесты для %s
TEST_SPRINTF(s_minus, "%-20s", "Hello", char *)
TEST_SPRINTF(s_width, "%20s", "Hello", char *)
TEST_SPRINTF(s_precision, "%.5s", "Hello, world!", char *)
TEST_SPRINTF(s_width_precision, "%20.5s", "Hello, world!", char *)
TEST_SPRINTF_2(s_star_width, "%*s", 20, "Hello", char *)
TEST_SPRINTF_2(s_star_precision, "%.*s", 5, "Hello, world!", char *)
TEST_SPRINTF_3(s_star_both, "%*.*s", 20, 5, "Hello, world!", char *)
TEST_SPRINTF(s_null_wish_form, "%.5s", NULL, char *)

TEST_SPRINTF(s_minus_zero_, "%-s", 0, char *)
TEST_SPRINTF(s_width_minus_zero, "%-5s", 0, char *)
TEST_SPRINTF(s_prec_minus_zero, "%-.5s", 0, char *)
TEST_SPRINTF(s_width_prec_minus_zero, "%-10.5s", 0, char *)
TEST_SPRINTF_2(s_dynamic_width, "%*s", 10, 0, char *)
TEST_SPRINTF_2(s_dynamic_precision, "%.*s", 5, 0, char *)
TEST_SPRINTF_3(s_dynamic_width_precision, "%*.*s", 10, 5, 0, char *)
TEST_SPRINTF(s_width_zero, "%5s", 0, char *)
TEST_SPRINTF(s_prec_zero_, "%.5s", 0, char *)
TEST_SPRINTF(s_width_prec_zero, "%10.5s", 0, char *)
TEST_SPRINTF(s_zero_prec_zero, "%.0s", 0, char *)
TEST_SPRINTF(s_zero_prec_minus_zero, "%-.0s", 0, char *)

// Тесты для %c
TEST_SPRINTF(c_minus_zero_, "%-c", 'a', char)
TEST_SPRINTF(c_width_minus_zero, "%-5c", 'a', char)
TEST_SPRINTF_2(c_dynamic_width, "%*c", 10, 'a', char)
TEST_SPRINTF(c_width_zero, "%5c", 'a', char)

// ================================================================
// Тесты для %p
// ================================================================

TEST_SPRINTF(p_minus_zero_, "%-p", (void *)0x1234abcd, void *)
TEST_SPRINTF(p_width_minus_zero, "%-5p", (void *)0x1234abcd, void *)
TEST_SPRINTF_2(p_dynamic_width, "%*p", 10, (void *)0x1234abcd, void *)

START_TEST(test_s21_sprintf_p_format) {
  void *ptr = (void *)0x1234abcd;
  char str1[100];
  char str2[100];

  sprintf(str1, "%-20p", ptr);
  s21_sprintf(str2, "%-20p", ptr);
  ck_assert_str_eq(str1, str2);

  sprintf(str1, "%20p", ptr);
  s21_sprintf(str2, "%20p", ptr);
  ck_assert_str_eq(str1, str2);

  sprintf(str1, "%*p", 20, ptr);
  s21_sprintf(str2, "%*p", 20, ptr);
  ck_assert_str_eq(str1, str2);
}
END_TEST

// ================================================================
// Test suite
// ================================================================

Suite *sprintf_suite(void) {
  Suite *ss = suite_create("test_sprintf");
  TCase *tc = tcase_create("Core");

  tcase_add_test(tc, d);
  tcase_add_test(tc, d_min);
  tcase_add_test(tc, d_max);
  tcase_add_test(tc, i);
  tcase_add_test(tc, i_min);
  tcase_add_test(tc, i_max);
  tcase_add_test(tc, o);
  tcase_add_test(tc, o_min);
  tcase_add_test(tc, o_max);
  tcase_add_test(tc, u);
  tcase_add_test(tc, u_min);
  tcase_add_test(tc, u_max);
  tcase_add_test(tc, x);
  tcase_add_test(tc, x_min);
  tcase_add_test(tc, x_max);
  tcase_add_test(tc, X);
  tcase_add_test(tc, X_min);
  tcase_add_test(tc, X_max);
  tcase_add_test(tc, hd);
  tcase_add_test(tc, hd_min);
  tcase_add_test(tc, hd_max);
  tcase_add_test(tc, hi);
  tcase_add_test(tc, hi_min);
  tcase_add_test(tc, hi_max);
  tcase_add_test(tc, ho);
  tcase_add_test(tc, ho_min);
  tcase_add_test(tc, ho_max);
  tcase_add_test(tc, hu);
  tcase_add_test(tc, hu_min);
  tcase_add_test(tc, hu_max);
  tcase_add_test(tc, hx);
  tcase_add_test(tc, hx_min);
  tcase_add_test(tc, hx_max);
  tcase_add_test(tc, hX);
  tcase_add_test(tc, hX_min);
  tcase_add_test(tc, hX_max);
  tcase_add_test(tc, hhd);
  tcase_add_test(tc, hhd_min);
  tcase_add_test(tc, hhd_max);
  tcase_add_test(tc, hhi);
  tcase_add_test(tc, hhi_min);
  tcase_add_test(tc, hhi_max);
  tcase_add_test(tc, hho);
  tcase_add_test(tc, hho_min);
  tcase_add_test(tc, hho_max);
  tcase_add_test(tc, hhu);
  tcase_add_test(tc, hhu_min);
  tcase_add_test(tc, hhu_max);
  tcase_add_test(tc, hhx);
  tcase_add_test(tc, hhx_min);
  tcase_add_test(tc, hhx_max);
  tcase_add_test(tc, hhX);
  tcase_add_test(tc, hhX_min);
  tcase_add_test(tc, hhX_max);
  tcase_add_test(tc, ld);
  tcase_add_test(tc, ld_min);
  tcase_add_test(tc, ld_max);
  tcase_add_test(tc, li);
  tcase_add_test(tc, li_min);
  tcase_add_test(tc, li_max);
  tcase_add_test(tc, lo);
  tcase_add_test(tc, lo_min);
  tcase_add_test(tc, lo_max);
  tcase_add_test(tc, lu);
  tcase_add_test(tc, lu_min);
  tcase_add_test(tc, lu_max);
  tcase_add_test(tc, lx);
  tcase_add_test(tc, lx_min);
  tcase_add_test(tc, lx_max);
  tcase_add_test(tc, lX);
  tcase_add_test(tc, lX_min);
  tcase_add_test(tc, lX_max);
  tcase_add_test(tc, lld);
  tcase_add_test(tc, lld_min);
  tcase_add_test(tc, lld_max);
  tcase_add_test(tc, lli);
  tcase_add_test(tc, lli_min);
  tcase_add_test(tc, lli_max);
  tcase_add_test(tc, llo);
  tcase_add_test(tc, llo_min);
  tcase_add_test(tc, llo_max);
  tcase_add_test(tc, llu);
  tcase_add_test(tc, llu_min);
  tcase_add_test(tc, llu_max);
  tcase_add_test(tc, llx);
  tcase_add_test(tc, llx_min);
  tcase_add_test(tc, llx_max);
  tcase_add_test(tc, llX);
  tcase_add_test(tc, llX_min);
  tcase_add_test(tc, llX_max);
  tcase_add_test(tc, c);
  tcase_add_test(tc, c_min);
  tcase_add_test(tc, c_max);
  tcase_add_test(tc, c_nonprint);
  tcase_add_test(tc, c_zero);
  tcase_add_test(tc, c_newline);
  tcase_add_test(tc, c_tab);
  tcase_add_test(tc, c_null_char);
  tcase_add_test(tc, s);
  tcase_add_test(tc, s_special);
  tcase_add_test(tc, s_special_chars);
  tcase_add_test(tc, s_unicode);
  tcase_add_test(tc, s_null);
  tcase_add_test(tc, s_empty);
  tcase_add_test(tc, e_zero);
  tcase_add_test(tc, e_minus_zero);
  tcase_add_test(tc, E_zero);
  tcase_add_test(tc, E_minus_zero);
  tcase_add_test(tc, f_zero);
  tcase_add_test(tc, f_minus_zero);
  tcase_add_test(tc, g_zero);
  tcase_add_test(tc, g_minus_zero);
  tcase_add_test(tc, G_zero);
  tcase_add_test(tc, G_minus_zero);
  tcase_add_test(tc, le_zero);
  tcase_add_test(tc, le_minus_zero);
  tcase_add_test(tc, lE_zero);
  tcase_add_test(tc, lE_minus_zero);
  tcase_add_test(tc, lf_zero);
  tcase_add_test(tc, lf_minus_zero);
  tcase_add_test(tc, lg_zero);
  tcase_add_test(tc, lg_minus_zero);
  tcase_add_test(tc, lG_zero);
  tcase_add_test(tc, lG_minus_zero);
  tcase_add_test(tc, Le_zero);
  tcase_add_test(tc, Le_minus_zero);
  tcase_add_test(tc, LE_zero);
  tcase_add_test(tc, LE_minus_zero);
  tcase_add_test(tc, Lf_zero);
  tcase_add_test(tc, Lf_minus_zero);
  tcase_add_test(tc, Lg_zero);
  tcase_add_test(tc, Lg_minus_zero);
  tcase_add_test(tc, LG_zero);
  tcase_add_test(tc, LG_minus_zero);
  tcase_add_test(tc, e);
  tcase_add_test(tc, e_neg);
  tcase_add_test(tc, e_big);
  tcase_add_test(tc, e_small);
  tcase_add_test(tc, E);
  tcase_add_test(tc, E_neg);
  tcase_add_test(tc, E_big);
  tcase_add_test(tc, E_small);
  tcase_add_test(tc, f);
  tcase_add_test(tc, f2);
  tcase_add_test(tc, f_neg);
  tcase_add_test(tc, f_small);
  tcase_add_test(tc, g);
  tcase_add_test(tc, g2);
  tcase_add_test(tc, g3);
  tcase_add_test(tc, g_neg);
  tcase_add_test(tc, g_big);
  tcase_add_test(tc, g_small);
  tcase_add_test(tc, G);
  tcase_add_test(tc, G2);
  tcase_add_test(tc, G3);
  tcase_add_test(tc, G_neg);
  tcase_add_test(tc, G_big);
  tcase_add_test(tc, G_small);
  tcase_add_test(tc, le);
  tcase_add_test(tc, le_neg);
  tcase_add_test(tc, le_big);
  tcase_add_test(tc, le_small);
  tcase_add_test(tc, lE);
  tcase_add_test(tc, lE_neg);
  tcase_add_test(tc, lE_big);
  tcase_add_test(tc, lE_small);
  tcase_add_test(tc, lf);
  tcase_add_test(tc, lf2);
  tcase_add_test(tc, lf_neg);
  tcase_add_test(tc, lf_small);
  tcase_add_test(tc, lg);
  tcase_add_test(tc, lg2);
  tcase_add_test(tc, lg3);
  tcase_add_test(tc, lg_neg);
  tcase_add_test(tc, lg_big);
  tcase_add_test(tc, lg_small);
  tcase_add_test(tc, lG);
  tcase_add_test(tc, lG2);
  tcase_add_test(tc, lG3);
  tcase_add_test(tc, lG_neg);
  tcase_add_test(tc, lG_big);
  tcase_add_test(tc, lG_small);
  tcase_add_test(tc, Le);
  tcase_add_test(tc, Le_neg);
  tcase_add_test(tc, Le_big);
  tcase_add_test(tc, Le_small);
  tcase_add_test(tc, LE);
  tcase_add_test(tc, LE_neg);
  tcase_add_test(tc, LE_big);
  tcase_add_test(tc, LE_small);
  tcase_add_test(tc, Lf);
  tcase_add_test(tc, Lf2);
  tcase_add_test(tc, Lf_neg);
  tcase_add_test(tc, Lf_small);
  tcase_add_test(tc, Lg);
  tcase_add_test(tc, Lg2);
  tcase_add_test(tc, Lg3);
  tcase_add_test(tc, Lg_neg);
  tcase_add_test(tc, Lg_big);
  tcase_add_test(tc, Lg_small);
  tcase_add_test(tc, LG);
  tcase_add_test(tc, LG2);
  tcase_add_test(tc, LG3);
  tcase_add_test(tc, LG_neg);
  tcase_add_test(tc, LG_big);
  tcase_add_test(tc, LG_small);
  tcase_add_test(tc, g_switch_to_e);
  tcase_add_test(tc, g_switch_to_f);
  tcase_add_test(tc, g_switch);
  tcase_add_test(tc, G_switch_to_e);
  tcase_add_test(tc, G_switch_to_f);
  tcase_add_test(tc, G_switch);
  tcase_add_test(tc, e_nan);
  tcase_add_test(tc, e_inf);
  tcase_add_test(tc, e_neg_inf);
  tcase_add_test(tc, E_nan);
  tcase_add_test(tc, E_inf);
  tcase_add_test(tc, E_neg_inf);
  tcase_add_test(tc, f_nan);
  tcase_add_test(tc, f_inf);
  tcase_add_test(tc, f_neg_inf);
  tcase_add_test(tc, g_nan);
  tcase_add_test(tc, g_inf);
  tcase_add_test(tc, g_neg_inf);
  tcase_add_test(tc, G_nan);
  tcase_add_test(tc, G_inf);
  tcase_add_test(tc, G_neg_inf);
  tcase_add_test(tc, le_nan);
  tcase_add_test(tc, le_inf);
  tcase_add_test(tc, le_neg_inf);
  tcase_add_test(tc, lE_nan);
  tcase_add_test(tc, lE_inf);
  tcase_add_test(tc, lE_neg_inf);
  tcase_add_test(tc, lf_nan);
  tcase_add_test(tc, lf_inf);
  tcase_add_test(tc, lf_neg_inf);
  tcase_add_test(tc, lg_nan);
  tcase_add_test(tc, lg_inf);
  tcase_add_test(tc, lg_neg_inf);
  tcase_add_test(tc, lG_nan);
  tcase_add_test(tc, lG_inf);
  tcase_add_test(tc, lG_neg_inf);
  tcase_add_test(tc, Le_nan);
  tcase_add_test(tc, Le_inf);
  tcase_add_test(tc, Le_neg_inf);
  tcase_add_test(tc, LE_nan);
  tcase_add_test(tc, LE_inf);
  tcase_add_test(tc, LE_neg_inf);
  tcase_add_test(tc, Lf_nan);
  tcase_add_test(tc, Lf_inf);
  tcase_add_test(tc, Lf_neg_inf);
  tcase_add_test(tc, Lg_nan);
  tcase_add_test(tc, Lg_inf);
  tcase_add_test(tc, Lg_neg_inf);
  tcase_add_test(tc, LG_nan);
  tcase_add_test(tc, LG_inf);
  tcase_add_test(tc, LG_neg_inf);
  tcase_add_test(tc, p);
  tcase_add_test(tc, p_int);
  tcase_add_test(tc, p_unsigned_int);
  tcase_add_test(tc, p_double);
  tcase_add_test(tc, p_null);
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
  tcase_add_test(tc, test_s21_sprintf_c_all_chars);
  tcase_add_test(tc, d_minus_negt);
  tcase_add_test(tc, d_minus_post);
  tcase_add_test(tc, d_minus_zero);
  tcase_add_test(tc, d_minus_ng_z);
  tcase_add_test(tc, d_plus_negt);
  tcase_add_test(tc, d_plus_post);
  tcase_add_test(tc, d_plus_zero);
  tcase_add_test(tc, d_plus_ng_z);
  tcase_add_test(tc, d_space_negt);
  tcase_add_test(tc, d_space_post);
  tcase_add_test(tc, d_space_zero);
  tcase_add_test(tc, d_space_ng_z);
  tcase_add_test(tc, d_zero_negt);
  tcase_add_test(tc, d_zero_post);
  tcase_add_test(tc, d_zero_zero);
  tcase_add_test(tc, d_zero_ng_z);
  tcase_add_test(tc, d_width_minus_negt);
  tcase_add_test(tc, d_width_minus_post);
  tcase_add_test(tc, d_width_minus_zero);
  tcase_add_test(tc, d_width_minus_ng_z);
  tcase_add_test(tc, d_width_plus_negt);
  tcase_add_test(tc, d_width_plus_post);
  tcase_add_test(tc, d_width_plus_zero);
  tcase_add_test(tc, d_width_plus_ng_z);
  tcase_add_test(tc, d_width_space_negt);
  tcase_add_test(tc, d_width_space_post);
  tcase_add_test(tc, d_width_space_zero);
  tcase_add_test(tc, d_width_space_ng_z);
  tcase_add_test(tc, d_width_zero_negt);
  tcase_add_test(tc, d_width_zero_post);
  tcase_add_test(tc, d_width_zero_zero);
  tcase_add_test(tc, d_width_zero_ng_z);
  tcase_add_test(tc, d_prec_minus_negt);
  tcase_add_test(tc, d_prec_minus_post);
  tcase_add_test(tc, d_prec_minus_zero);
  tcase_add_test(tc, d_prec_minus_ng_z);
  tcase_add_test(tc, d_prec_plus_negt);
  tcase_add_test(tc, d_prec_plus_post);
  tcase_add_test(tc, d_prec_plus_zero);
  tcase_add_test(tc, d_prec_plus_ng_z);
  tcase_add_test(tc, d_prec_space_negt);
  tcase_add_test(tc, d_prec_space_post);
  tcase_add_test(tc, d_prec_space_zero);
  tcase_add_test(tc, d_prec_space_ng_z);
  tcase_add_test(tc, d_width_prec_minus_negt);
  tcase_add_test(tc, d_width_prec_minus_post);
  tcase_add_test(tc, d_width_prec_minus_zero);
  tcase_add_test(tc, d_width_prec_minus_ng_z);
  tcase_add_test(tc, d_width_prec_plus_negt);
  tcase_add_test(tc, d_width_prec_plus_post);
  tcase_add_test(tc, d_width_prec_plus_zero);
  tcase_add_test(tc, d_width_prec_plus_ng_z);
  tcase_add_test(tc, d_width_prec_space_negt);
  tcase_add_test(tc, d_width_prec_space_post);
  tcase_add_test(tc, d_width_prec_space_zero);
  tcase_add_test(tc, d_width_prec_space_ng_z);
  tcase_add_test(tc, d_dynamic_width);
  tcase_add_test(tc, d_dynamic_precision);
  tcase_add_test(tc, d_dynamic_width_precision);
  tcase_add_test(tc, d_width_negt);
  tcase_add_test(tc, d_width_post);
  tcase_add_test(tc, d_width_zero);
  tcase_add_test(tc, d_width_ng_z);
  tcase_add_test(tc, d_prec_negt);
  tcase_add_test(tc, d_prec_post);
  tcase_add_test(tc, d_prec_zero_);
  tcase_add_test(tc, d_prec_ng_z);
  tcase_add_test(tc, d_width_prec_negt);
  tcase_add_test(tc, d_width_prec_post);
  tcase_add_test(tc, d_width_prec_zero);
  tcase_add_test(tc, d_width_prec_ng_z);
  tcase_add_test(tc, d_zero_prec_negt);
  tcase_add_test(tc, d_zero_prec_post);
  tcase_add_test(tc, d_zero_prec_zero);
  tcase_add_test(tc, d_zero_prec_ng_z);
  tcase_add_test(tc, d_zero_zero_negt);
  tcase_add_test(tc, d_zero_zero_post);
  tcase_add_test(tc, d_zero_zero_zero);
  tcase_add_test(tc, d_zero_zero_ng_z);
  tcase_add_test(tc, d_zero_prec_minus_zero);
  tcase_add_test(tc, d_zero_prec_plus_zero);
  tcase_add_test(tc, d_zero_prec_space_zero);
  tcase_add_test(tc, d_zero_zero_plus_zero);
  tcase_add_test(tc, d_zero_zero_space_zero);
  tcase_add_test(tc, i_minus);
  tcase_add_test(tc, i_plus);
  tcase_add_test(tc, i_space);
  tcase_add_test(tc, i_zero_form);
  tcase_add_test(tc, i_width);
  tcase_add_test(tc, i_precision);
  tcase_add_test(tc, i_width_precision);
  tcase_add_test(tc, i_star_width);
  tcase_add_test(tc, i_star_precision);
  tcase_add_test(tc, i_star_both);
  tcase_add_test(tc, i_neg);
  tcase_add_test(tc, i_neg_plus);
  tcase_add_test(tc, i_neg_space);
  tcase_add_test(tc, i_zero_prec);
  tcase_add_test(tc, u_minus_negt);
  tcase_add_test(tc, u_minus_post);
  tcase_add_test(tc, u_minus_zero);
  tcase_add_test(tc, u_minus_ng_z);
  tcase_add_test(tc, u_zero_negt);
  tcase_add_test(tc, u_zero_post);
  tcase_add_test(tc, u_zero_zero);
  tcase_add_test(tc, u_zero_ng_z);
  tcase_add_test(tc, u_width_minus_negt);
  tcase_add_test(tc, u_width_minus_post);
  tcase_add_test(tc, u_width_minus_zero);
  tcase_add_test(tc, u_width_minus_ng_z);
  tcase_add_test(tc, u_width_zero_negt);
  tcase_add_test(tc, u_width_zero_post);
  tcase_add_test(tc, u_width_zero_zero);
  tcase_add_test(tc, u_width_zero_ng_z);
  tcase_add_test(tc, u_prec_minus_negt);
  tcase_add_test(tc, u_prec_minus_post);
  tcase_add_test(tc, u_prec_minus_zero);
  tcase_add_test(tc, u_prec_minus_ng_z);
  tcase_add_test(tc, u_width_prec_minus_negt);
  tcase_add_test(tc, u_width_prec_minus_post);
  tcase_add_test(tc, u_width_prec_minus_zero);
  tcase_add_test(tc, u_width_prec_minus_ng_z);
  tcase_add_test(tc, u_dynamic_width);
  tcase_add_test(tc, u_dynamic_precision);
  tcase_add_test(tc, u_dynamic_width_precision);
  tcase_add_test(tc, u_width_negt);
  tcase_add_test(tc, u_width_post);
  tcase_add_test(tc, u_width_zero);
  tcase_add_test(tc, u_width_ng_z);
  tcase_add_test(tc, u_prec_negt);
  tcase_add_test(tc, u_prec_post);
  tcase_add_test(tc, u_prec_zero_);
  tcase_add_test(tc, u_prec_ng_z);
  tcase_add_test(tc, u_width_prec_negt);
  tcase_add_test(tc, u_width_prec_post);
  tcase_add_test(tc, u_width_prec_zero);
  tcase_add_test(tc, u_width_prec_ng_z);
  tcase_add_test(tc, u_zero_prec_negt);
  tcase_add_test(tc, u_zero_prec_post);
  tcase_add_test(tc, u_zero_prec_zero);
  tcase_add_test(tc, u_zero_prec_ng_z);
  tcase_add_test(tc, u_zero_zero_negt);
  tcase_add_test(tc, u_zero_zero_post);
  tcase_add_test(tc, u_zero_zero_zero);
  tcase_add_test(tc, u_zero_zero_ng_z);
  tcase_add_test(tc, u_zero_prec_minus_zero);
  tcase_add_test(tc, o_minus_negt);
  tcase_add_test(tc, o_minus_post);
  tcase_add_test(tc, o_minus_zero);
  tcase_add_test(tc, o_minus_ng_z);
  tcase_add_test(tc, o_hash_negt);
  tcase_add_test(tc, o_hash_post);
  tcase_add_test(tc, o_hash_zero);
  tcase_add_test(tc, o_hash_ng_z);
  tcase_add_test(tc, o_zero_negt);
  tcase_add_test(tc, o_zero_post);
  tcase_add_test(tc, o_zero_zero);
  tcase_add_test(tc, o_zero_ng_z);
  tcase_add_test(tc, o_width_minus_negt);
  tcase_add_test(tc, o_width_minus_post);
  tcase_add_test(tc, o_width_minus_zero);
  tcase_add_test(tc, o_width_minus_ng_z);
  tcase_add_test(tc, o_width_hash_negt);
  tcase_add_test(tc, o_width_hash_post);
  tcase_add_test(tc, o_width_hash_zero);
  tcase_add_test(tc, o_width_hash_ng_z);
  tcase_add_test(tc, o_width_zero_negt);
  tcase_add_test(tc, o_width_zero_post);
  tcase_add_test(tc, o_width_zero_zero);
  tcase_add_test(tc, o_width_zero_ng_z);
  tcase_add_test(tc, o_prec_minus_negt);
  tcase_add_test(tc, o_prec_minus_post);
  tcase_add_test(tc, o_prec_minus_zero);
  tcase_add_test(tc, o_prec_minus_ng_z);
  tcase_add_test(tc, o_prec_hash_negt);
  tcase_add_test(tc, o_prec_hash_post);
  tcase_add_test(tc, o_prec_hash_zero);
  tcase_add_test(tc, o_prec_hash_ng_z);
  tcase_add_test(tc, o_width_prec_minus_negt);
  tcase_add_test(tc, o_width_prec_minus_post);
  tcase_add_test(tc, o_width_prec_minus_zero);
  tcase_add_test(tc, o_width_prec_minus_ng_z);
  tcase_add_test(tc, o_width_prec_hash_negt);
  tcase_add_test(tc, o_width_prec_hash_post);
  tcase_add_test(tc, o_width_prec_hash_zero);
  tcase_add_test(tc, o_width_prec_hash_ng_z);
  tcase_add_test(tc, o_dynamic_width);
  tcase_add_test(tc, o_dynamic_precision);
  tcase_add_test(tc, o_dynamic_width_precision);
  tcase_add_test(tc, o_width_negt);
  tcase_add_test(tc, o_width_post);
  tcase_add_test(tc, o_width_zero);
  tcase_add_test(tc, o_width_ng_z);
  tcase_add_test(tc, o_prec_negt);
  tcase_add_test(tc, o_prec_post);
  tcase_add_test(tc, o_prec_zero_);
  tcase_add_test(tc, o_prec_ng_z);
  tcase_add_test(tc, o_width_prec_negt);
  tcase_add_test(tc, o_width_prec_post);
  tcase_add_test(tc, o_width_prec_zero);
  tcase_add_test(tc, o_width_prec_ng_z);
  tcase_add_test(tc, o_zero_prec_negt);
  tcase_add_test(tc, o_zero_prec_post);
  tcase_add_test(tc, o_zero_prec_zero);
  tcase_add_test(tc, o_zero_prec_ng_z);
  tcase_add_test(tc, o_zero_zero_negt);
  tcase_add_test(tc, o_zero_zero_post);
  tcase_add_test(tc, o_zero_zero_zero);
  tcase_add_test(tc, o_zero_zero_ng_z);
  tcase_add_test(tc, o_zero_prec_minus_zero);
  tcase_add_test(tc, o_zero_prec_hash_zero);
  tcase_add_test(tc, o_zero_zero_hash_zero);
  tcase_add_test(tc, x_minus_negt);
  tcase_add_test(tc, x_minus_post);
  tcase_add_test(tc, x_minus_zero);
  tcase_add_test(tc, x_minus_ng_z);
  tcase_add_test(tc, x_hash_negt);
  tcase_add_test(tc, x_hash_post);
  tcase_add_test(tc, x_hash_zero);
  tcase_add_test(tc, x_hash_ng_z);
  tcase_add_test(tc, x_zero_negt);
  tcase_add_test(tc, x_zero_post);
  tcase_add_test(tc, x_zero_zero);
  tcase_add_test(tc, x_zero_ng_z);
  tcase_add_test(tc, x_width_minus_negt);
  tcase_add_test(tc, x_width_minus_post);
  tcase_add_test(tc, x_width_minus_zero);
  tcase_add_test(tc, x_width_minus_ng_z);
  tcase_add_test(tc, x_width_hash_negt);
  tcase_add_test(tc, x_width_hash_post);
  tcase_add_test(tc, x_width_hash_zero);
  tcase_add_test(tc, x_width_hash_ng_z);
  tcase_add_test(tc, x_width_zero_negt);
  tcase_add_test(tc, x_width_zero_post);
  tcase_add_test(tc, x_width_zero_zero);
  tcase_add_test(tc, x_width_zero_ng_z);
  tcase_add_test(tc, x_prec_minus_negt);
  tcase_add_test(tc, x_prec_minus_post);
  tcase_add_test(tc, x_prec_minus);
  tcase_add_test(tc, x_prec_minus_ng_z);
  tcase_add_test(tc, x_prec_hash_negt);
  tcase_add_test(tc, x_prec_hash_post);
  tcase_add_test(tc, x_prec_hash_zero);
  tcase_add_test(tc, x_prec_hash_ng_z);
  tcase_add_test(tc, x_width_prec_minus_negt);
  tcase_add_test(tc, x_width_prec_minus_post);
  tcase_add_test(tc, x_width_prec_minus_zero);
  tcase_add_test(tc, x_width_prec_minus_ng_z);
  tcase_add_test(tc, x_width_prec_hash_negt);
  tcase_add_test(tc, x_width_prec_hash_post);
  tcase_add_test(tc, x_width_prec_hash_zero);
  tcase_add_test(tc, x_width_prec_hash_ng_z);
  tcase_add_test(tc, x_dynamic_width);
  tcase_add_test(tc, x_dynamic_precision);
  tcase_add_test(tc, x_dynamic_width_precision);
  tcase_add_test(tc, x_width_negt);
  tcase_add_test(tc, x_width_post);
  tcase_add_test(tc, x_width_zero);
  tcase_add_test(tc, x_width_ng_z);
  tcase_add_test(tc, x_prec_negt);
  tcase_add_test(tc, x_prec_post);
  tcase_add_test(tc, x_prec_zero_);
  tcase_add_test(tc, x_prec_ng_z);
  tcase_add_test(tc, x_width_prec_negt);
  tcase_add_test(tc, x_width_prec_post);
  tcase_add_test(tc, x_width_prec_zero);
  tcase_add_test(tc, x_width_prec_ng_z);
  tcase_add_test(tc, x_zero_prec_negt);
  tcase_add_test(tc, x_zero_prec_post);
  tcase_add_test(tc, x_zero_prec_zero);
  tcase_add_test(tc, x_zero_prec_ng_z);
  tcase_add_test(tc, x_zero_zero_negt);
  tcase_add_test(tc, x_zero_zero_post);
  tcase_add_test(tc, x_zero_zero_zero);
  tcase_add_test(tc, x_zero_zero_ng_z);
  tcase_add_test(tc, x_zero_prec_minus_zero);
  tcase_add_test(tc, x_zero_prec_hash_zero);
  tcase_add_test(tc, x_zero_zero_hash_zero);
  tcase_add_test(tc, X_minus_negt);
  tcase_add_test(tc, X_minus_post);
  tcase_add_test(tc, X_minus_zero);
  tcase_add_test(tc, X_minus_ng_z);
  tcase_add_test(tc, X_hash_negt);
  tcase_add_test(tc, X_hash_post);
  tcase_add_test(tc, X_hash_zero);
  tcase_add_test(tc, X_hash_ng_z);
  tcase_add_test(tc, X_zero_negt);
  tcase_add_test(tc, X_zero_post);
  tcase_add_test(tc, X_zero_zero);
  tcase_add_test(tc, X_zero_ng_z);
  tcase_add_test(tc, X_width_minus_negt);
  tcase_add_test(tc, X_width_minus_post);
  tcase_add_test(tc, X_width_minus_zero);
  tcase_add_test(tc, X_width_minus_ng_z);
  tcase_add_test(tc, X_width_hash_negt);
  tcase_add_test(tc, X_width_hash_post);
  tcase_add_test(tc, X_width_hash_zero);
  tcase_add_test(tc, X_width_hash_ng_z);
  tcase_add_test(tc, X_width_zero_negt);
  tcase_add_test(tc, X_width_zero_post);
  tcase_add_test(tc, X_width_zero_zero);
  tcase_add_test(tc, X_width_zero_ng_z);
  tcase_add_test(tc, X_prec_minus_negt);
  tcase_add_test(tc, X_prec_minus_post);
  tcase_add_test(tc, X_prec_minus_zero);
  tcase_add_test(tc, X_prec_minus_ng_z);
  tcase_add_test(tc, X_prec_hash_negt);
  tcase_add_test(tc, X_prec_hash_post);
  tcase_add_test(tc, X_prec_hash_zero);
  tcase_add_test(tc, X_prec_hash_ng_z);
  tcase_add_test(tc, X_width_prec_minus_negt);
  tcase_add_test(tc, X_width_prec_minus_post);
  tcase_add_test(tc, X_width_prec_minus_zero);
  tcase_add_test(tc, X_width_prec_minus_ng_z);
  tcase_add_test(tc, X_width_prec_hash_negt);
  tcase_add_test(tc, X_width_prec_hash_post);
  tcase_add_test(tc, X_width_prec_hash_zero);
  tcase_add_test(tc, X_width_prec_hash_ng_z);
  tcase_add_test(tc, X_width_negt);
  tcase_add_test(tc, X_width_post);
  tcase_add_test(tc, X_width_zero);
  tcase_add_test(tc, X_width_ng_z);
  tcase_add_test(tc, X_prec_negt);
  tcase_add_test(tc, X_prec_post);
  tcase_add_test(tc, X_prec_zero_);
  tcase_add_test(tc, X_prec_ng_z);
  tcase_add_test(tc, X_width_prec_negt);
  tcase_add_test(tc, X_width_prec_post);
  tcase_add_test(tc, X_width_prec_zero);
  tcase_add_test(tc, X_width_prec_ng_z);
  tcase_add_test(tc, X_zero_prec_negt);
  tcase_add_test(tc, X_zero_prec_post);
  tcase_add_test(tc, X_zero_prec_zero);
  tcase_add_test(tc, X_zero_prec_ng_z);
  tcase_add_test(tc, X_zero_zero_negt);
  tcase_add_test(tc, X_zero_zero_post);
  tcase_add_test(tc, X_zero_zero_zero);
  tcase_add_test(tc, X_zero_zero_ng_z);
  tcase_add_test(tc, X_zero_prec_minus_zero);
  tcase_add_test(tc, X_zero_prec_hash_zero);
  tcase_add_test(tc, X_zero_zero_hash_zero);
  tcase_add_test(tc, X_dynamic_width);
  tcase_add_test(tc, X_dynamic_precision);
  tcase_add_test(tc, X_dynamic_width_precision);
  tcase_add_test(tc, hu_minus_negt);
  tcase_add_test(tc, hu_minus_post);
  tcase_add_test(tc, ho_minus_negt);
  tcase_add_test(tc, ho_minus_post);
  tcase_add_test(tc, hx_minus_negt);
  tcase_add_test(tc, hx_minus_post);
  tcase_add_test(tc, hX_minus_negt);
  tcase_add_test(tc, hX_minus_post);
  tcase_add_test(tc, f_minus_negt);
  tcase_add_test(tc, f_minus_post);
  tcase_add_test(tc, f_minus_zero_);
  tcase_add_test(tc, f_minus_ng_z);
  tcase_add_test(tc, f_plus_negt);
  tcase_add_test(tc, f_plus_post);
  tcase_add_test(tc, f_plus_zero);
  tcase_add_test(tc, f_plus_ng_z);
  tcase_add_test(tc, f_space_negt);
  tcase_add_test(tc, f_space_post);
  tcase_add_test(tc, f_space_zero);
  tcase_add_test(tc, f_space_ng_z);
  tcase_add_test(tc, f_hash_negt);
  tcase_add_test(tc, f_hash_post);
  tcase_add_test(tc, f_hash_zero);
  tcase_add_test(tc, f_hash_ng_z);
  tcase_add_test(tc, f_zero_negt);
  tcase_add_test(tc, f_zero_post);
  tcase_add_test(tc, f_zero_zero);
  tcase_add_test(tc, f_zero_ng_z);
  tcase_add_test(tc, f_width_minus_negt);
  tcase_add_test(tc, f_width_minus_post);
  tcase_add_test(tc, f_width_minus_zero);
  tcase_add_test(tc, f_width_minus_ng_z);
  tcase_add_test(tc, f_width_plus_negt);
  tcase_add_test(tc, f_width_plus_post);
  tcase_add_test(tc, f_width_plus_zero);
  tcase_add_test(tc, f_width_plus_ng_z);
  tcase_add_test(tc, f_width_space_negt);
  tcase_add_test(tc, f_width_space_post);
  tcase_add_test(tc, f_width_space_zero);
  tcase_add_test(tc, f_width_space_ng_z);
  tcase_add_test(tc, f_width_hash_negt);
  tcase_add_test(tc, f_width_hash_post);
  tcase_add_test(tc, f_width_hash_zero);
  tcase_add_test(tc, f_width_hash_ng_z);
  tcase_add_test(tc, f_width_zero_negt);
  tcase_add_test(tc, f_width_zero_post);
  tcase_add_test(tc, f_width_zero_zero);
  tcase_add_test(tc, f_width_zero_ng_z);
  tcase_add_test(tc, f_prec_minus_negt);
  tcase_add_test(tc, f_prec_minus_post);
  tcase_add_test(tc, f_prec_minus_zero);
  tcase_add_test(tc, f_prec_minus_ng_z);
  tcase_add_test(tc, f_prec_plus_negt);
  tcase_add_test(tc, f_prec_plus_post);
  tcase_add_test(tc, f_prec_plus_zero);
  tcase_add_test(tc, f_prec_plus_ng_z);
  tcase_add_test(tc, f_prec_space_negt);
  tcase_add_test(tc, f_prec_space_post);
  tcase_add_test(tc, f_prec_space_zero);
  tcase_add_test(tc, f_prec_space_ng_z);
  tcase_add_test(tc, f_prec_hash_negt);
  tcase_add_test(tc, f_prec_hash_post);
  tcase_add_test(tc, f_prec_hash_zero);
  tcase_add_test(tc, f_prec_hash_ng_z);
  tcase_add_test(tc, f_prec_zero_negt);
  tcase_add_test(tc, f_prec_zero_post);
  tcase_add_test(tc, f_prec_zero_zero);
  tcase_add_test(tc, f_prec_zero_ng_z);
  tcase_add_test(tc, f_width_prec_minus_negt);
  tcase_add_test(tc, f_width_prec_minus_post);
  tcase_add_test(tc, f_width_prec_minus_zero);
  tcase_add_test(tc, f_width_prec_minus_ng_z);
  tcase_add_test(tc, f_width_prec_plus_negt);
  tcase_add_test(tc, f_width_prec_plus_post);
  tcase_add_test(tc, f_width_prec_plus_zero);
  tcase_add_test(tc, f_width_prec_plus_ng_z);
  tcase_add_test(tc, f_width_prec_space_negt);
  tcase_add_test(tc, f_width_prec_space_post);
  tcase_add_test(tc, f_width_prec_space_zero);
  tcase_add_test(tc, f_width_prec_space_ng_z);
  tcase_add_test(tc, f_width_prec_hash_negt);
  tcase_add_test(tc, f_width_prec_hash_post);
  tcase_add_test(tc, f_width_prec_hash_zero);
  tcase_add_test(tc, f_width_prec_hash_ng_z);
  tcase_add_test(tc, f_width_prec_zero_negt);
  tcase_add_test(tc, f_width_prec_zero_post);
  tcase_add_test(tc, f_width_prec_zero_zero);
  tcase_add_test(tc, f_width_prec_zero_ng_z);
  tcase_add_test(tc, f_dynamic_width);
  tcase_add_test(tc, f_dynamic_precision);
  tcase_add_test(tc, f_dynamic_width_precision);
  tcase_add_test(tc, f_width_negt);
  tcase_add_test(tc, f_width_post);
  tcase_add_test(tc, f_width_zero);
  tcase_add_test(tc, f_width_ng_z);
  tcase_add_test(tc, f_prec_negt);
  tcase_add_test(tc, f_prec_post);
  tcase_add_test(tc, f_prec_zero_);
  tcase_add_test(tc, f_prec_ng_z);
  tcase_add_test(tc, f_width_prec_negt);
  tcase_add_test(tc, f_width_prec_post);
  tcase_add_test(tc, f_width_prec_zero);
  tcase_add_test(tc, f_width_prec_ng_z);
  tcase_add_test(tc, f_zero_prec_negt);
  tcase_add_test(tc, f_zero_prec_post);
  tcase_add_test(tc, f_zero_prec_zero);
  tcase_add_test(tc, f_zero_prec_ng_z);
  tcase_add_test(tc, f_zero_zero_negt);
  tcase_add_test(tc, f_zero_zero_post);
  tcase_add_test(tc, f_zero_zero_zero);
  tcase_add_test(tc, f_zero_zero_ng_z);
  tcase_add_test(tc, f_zero_prec_zero_negt);
  tcase_add_test(tc, f_zero_prec_zero_post);
  tcase_add_test(tc, f_zero_prec_zero_zero);
  tcase_add_test(tc, f_zero_prec_zero_ng_z);
  tcase_add_test(tc, f_zero_prec_minus_zero);
  tcase_add_test(tc, f_zero_prec_plus_zero);
  tcase_add_test(tc, f_zero_prec_space_zero);
  tcase_add_test(tc, f_zero_prec_hash_zero);
  tcase_add_test(tc, f_zero_zero_plus_zero);
  tcase_add_test(tc, f_zero_zero_space_zero);
  tcase_add_test(tc, f_zero_zero_hash_zero);
  tcase_add_test(tc, f_zero_prec_zero_plus_zero);
  tcase_add_test(tc, f_zero_prec_zero_space_zero);
  tcase_add_test(tc, f_zero_prec_zero_hash_zero);
  tcase_add_test(tc, e_minus_negt);
  tcase_add_test(tc, e_minus_post);
  tcase_add_test(tc, e_minus_zero_);
  tcase_add_test(tc, e_minus_ng_z);
  tcase_add_test(tc, e_plus_negt);
  tcase_add_test(tc, e_plus_post);
  tcase_add_test(tc, e_plus_zero);
  tcase_add_test(tc, e_plus_ng_z);
  tcase_add_test(tc, e_space_negt);
  tcase_add_test(tc, e_space_post);
  tcase_add_test(tc, e_space_zero);
  tcase_add_test(tc, e_space_ng_z);
  tcase_add_test(tc, e_hash_negt);
  tcase_add_test(tc, e_hash_post);
  tcase_add_test(tc, e_hash_zero);
  tcase_add_test(tc, e_hash_ng_z);
  tcase_add_test(tc, e_zero_negt);
  tcase_add_test(tc, e_zero_post);
  tcase_add_test(tc, e_zero_zero);
  tcase_add_test(tc, e_zero_ng_z);
  tcase_add_test(tc, e_width_minus_negt);
  tcase_add_test(tc, e_width_minus_post);
  tcase_add_test(tc, e_width_minus_zero);
  tcase_add_test(tc, e_width_minus_ng_z);
  tcase_add_test(tc, e_width_plus_negt);
  tcase_add_test(tc, e_width_plus_post);
  tcase_add_test(tc, e_width_plus_zero);
  tcase_add_test(tc, e_width_plus_ng_z);
  tcase_add_test(tc, e_width_space_negt);
  tcase_add_test(tc, e_width_space_post);
  tcase_add_test(tc, e_width_space_zero);
  tcase_add_test(tc, e_width_space_ng_z);
  tcase_add_test(tc, e_width_hash_negt);
  tcase_add_test(tc, e_width_hash_post);
  tcase_add_test(tc, e_width_hash_zero);
  tcase_add_test(tc, e_width_hash_ng_z);
  tcase_add_test(tc, e_width_zero_negt);
  tcase_add_test(tc, e_width_zero_post);
  tcase_add_test(tc, e_width_zero_zero);
  tcase_add_test(tc, e_width_zero_ng_z);
  tcase_add_test(tc, e_prec_minus_negt);
  tcase_add_test(tc, e_prec_minus_post);
  tcase_add_test(tc, e_prec_minus_zero);
  tcase_add_test(tc, e_prec_minus_ng_z);
  tcase_add_test(tc, e_prec_plus_negt);
  tcase_add_test(tc, e_prec_plus_post);
  tcase_add_test(tc, e_prec_plus_zero);
  tcase_add_test(tc, e_prec_plus_ng_z);
  tcase_add_test(tc, e_prec_space_negt);
  tcase_add_test(tc, e_prec_space_post);
  tcase_add_test(tc, e_prec_space_zero);
  tcase_add_test(tc, e_prec_space_ng_z);
  tcase_add_test(tc, e_prec_hash_negt);
  tcase_add_test(tc, e_prec_hash_post);
  tcase_add_test(tc, e_prec_hash_zero);
  tcase_add_test(tc, e_prec_hash_ng_z);
  tcase_add_test(tc, e_prec_zero_negt);
  tcase_add_test(tc, e_prec_zero_post);
  tcase_add_test(tc, e_prec_zero_zero);
  tcase_add_test(tc, e_prec_zero_ng_z);
  tcase_add_test(tc, e_width_prec_minus_negt);
  tcase_add_test(tc, e_width_prec_minus_post);
  tcase_add_test(tc, e_width_prec_minus_zero);
  tcase_add_test(tc, e_width_prec_minus_ng_z);
  tcase_add_test(tc, e_width_prec_plus_negt);
  tcase_add_test(tc, e_width_prec_plus_post);
  tcase_add_test(tc, e_width_prec_plus_zero);
  tcase_add_test(tc, e_width_prec_plus_ng_z);
  tcase_add_test(tc, e_width_prec_space_negt);
  tcase_add_test(tc, e_width_prec_space_post);
  tcase_add_test(tc, e_width_prec_space_zero);
  tcase_add_test(tc, e_width_prec_space_ng_z);
  tcase_add_test(tc, e_width_prec_hash_negt);
  tcase_add_test(tc, e_width_prec_hash_post);
  tcase_add_test(tc, e_width_prec_hash_zero);
  tcase_add_test(tc, e_width_prec_hash_ng_z);
  tcase_add_test(tc, e_width_prec_zero_negt);
  tcase_add_test(tc, e_width_prec_zero_post);
  tcase_add_test(tc, e_width_prec_zero_zero);
  tcase_add_test(tc, e_width_prec_zero_ng_z);
  tcase_add_test(tc, e_dynamic_width);
  tcase_add_test(tc, e_dynamic_precision);
  tcase_add_test(tc, e_dynamic_width_precision);
  tcase_add_test(tc, e_width_negt);
  tcase_add_test(tc, e_width_post);
  tcase_add_test(tc, e_width_zero);
  tcase_add_test(tc, e_width_ng_z);
  tcase_add_test(tc, e_prec_negt);
  tcase_add_test(tc, e_prec_post);
  tcase_add_test(tc, e_prec_zero_);
  tcase_add_test(tc, e_prec_ng_z);
  tcase_add_test(tc, e_width_prec_negt);
  tcase_add_test(tc, e_width_prec_post);
  tcase_add_test(tc, e_width_prec_zero);
  tcase_add_test(tc, e_width_prec_ng_z);
  tcase_add_test(tc, e_zero_prec_negt);
  tcase_add_test(tc, e_zero_prec_post);
  tcase_add_test(tc, e_zero_prec_zero);
  tcase_add_test(tc, e_zero_prec_ng_z);
  tcase_add_test(tc, e_zero_zero_negt);
  tcase_add_test(tc, e_zero_zero_post);
  tcase_add_test(tc, e_zero_zero_zero);
  tcase_add_test(tc, e_zero_zero_ng_z);
  tcase_add_test(tc, e_zero_prec_zero_negt);
  tcase_add_test(tc, e_zero_prec_zero_post);
  tcase_add_test(tc, e_zero_prec_zero_zero);
  tcase_add_test(tc, e_zero_prec_zero_ng_z);
  tcase_add_test(tc, e_zero_prec_minus_zero);
  tcase_add_test(tc, e_zero_prec_plus_zero);
  tcase_add_test(tc, e_zero_prec_space_zero);
  tcase_add_test(tc, e_zero_prec_hash_zero);
  tcase_add_test(tc, e_zero_zero_plus_zero);
  tcase_add_test(tc, e_zero_zero_space_zero);
  tcase_add_test(tc, e_zero_zero_hash_zero);
  tcase_add_test(tc, e_zero_prec_zero_plus_zero);
  tcase_add_test(tc, e_zero_prec_zero_space_zero);
  tcase_add_test(tc, e_zero_prec_zero_hash_zero);
  tcase_add_test(tc, E_minus_negt);
  tcase_add_test(tc, E_minus_post);
  tcase_add_test(tc, E_minus_zero_);
  tcase_add_test(tc, E_minus_ng_z);
  tcase_add_test(tc, E_plus_negt);
  tcase_add_test(tc, E_plus_post);
  tcase_add_test(tc, E_plus_zero);
  tcase_add_test(tc, E_plus_ng_z);
  tcase_add_test(tc, E_space_negt);
  tcase_add_test(tc, E_space_post);
  tcase_add_test(tc, E_space_zero);
  tcase_add_test(tc, E_space_ng_z);
  tcase_add_test(tc, E_hash_negt);
  tcase_add_test(tc, E_hash_post);
  tcase_add_test(tc, E_hash_zero);
  tcase_add_test(tc, E_hash_ng_z);
  tcase_add_test(tc, E_zero_negt);
  tcase_add_test(tc, E_zero_post);
  tcase_add_test(tc, E_zero_zero);
  tcase_add_test(tc, E_zero_ng_z);
  tcase_add_test(tc, E_width_minus_negt);
  tcase_add_test(tc, E_width_minus_post);
  tcase_add_test(tc, E_width_minus_zero);
  tcase_add_test(tc, E_width_minus_ng_z);
  tcase_add_test(tc, E_width_plus_negt);
  tcase_add_test(tc, E_width_plus_post);
  tcase_add_test(tc, E_width_plus_zero);
  tcase_add_test(tc, E_width_plus_ng_z);
  tcase_add_test(tc, E_width_space_negt);
  tcase_add_test(tc, E_width_space_post);
  tcase_add_test(tc, E_width_space_zero);
  tcase_add_test(tc, E_width_space_ng_z);
  tcase_add_test(tc, E_width_hash_negt);
  tcase_add_test(tc, E_width_hash_post);
  tcase_add_test(tc, E_width_hash_zero);
  tcase_add_test(tc, E_width_hash_ng_z);
  tcase_add_test(tc, E_width_zero_negt);
  tcase_add_test(tc, E_width_zero_post);
  tcase_add_test(tc, E_width_zero_zero);
  tcase_add_test(tc, E_width_zero_ng_z);
  tcase_add_test(tc, E_prec_minus_negt);
  tcase_add_test(tc, E_prec_minus_post);
  tcase_add_test(tc, E_prec_minus_zero);
  tcase_add_test(tc, E_prec_minus_ng_z);
  tcase_add_test(tc, E_prec_plus_negt);
  tcase_add_test(tc, E_prec_plus_post);
  tcase_add_test(tc, E_prec_plus_zero);
  tcase_add_test(tc, E_prec_plus_ng_z);
  tcase_add_test(tc, E_prec_space_negt);
  tcase_add_test(tc, E_prec_space_post);
  tcase_add_test(tc, E_prec_space_zero);
  tcase_add_test(tc, E_prec_space_ng_z);
  tcase_add_test(tc, E_prec_hash_negt);
  tcase_add_test(tc, E_prec_hash_post);
  tcase_add_test(tc, E_prec_hash_zero);
  tcase_add_test(tc, E_prec_hash_ng_z);
  tcase_add_test(tc, E_prec_zero_negt);
  tcase_add_test(tc, E_prec_zero_post);
  tcase_add_test(tc, E_prec_zero_zero);
  tcase_add_test(tc, E_prec_zero_ng_z);
  tcase_add_test(tc, E_width_prec_minus_negt);
  tcase_add_test(tc, E_width_prec_minus_post);
  tcase_add_test(tc, E_width_prec_minus_zero);
  tcase_add_test(tc, E_width_prec_minus_ng_z);
  tcase_add_test(tc, E_width_prec_plus_negt);
  tcase_add_test(tc, E_width_prec_plus_post);
  tcase_add_test(tc, E_width_prec_plus_zero);
  tcase_add_test(tc, E_width_prec_plus_ng_z);
  tcase_add_test(tc, E_width_prec_space_negt);
  tcase_add_test(tc, E_width_prec_space_post);
  tcase_add_test(tc, E_width_prec_space_zero);
  tcase_add_test(tc, E_width_prec_space_ng_z);
  tcase_add_test(tc, E_width_prec_hash_negt);
  tcase_add_test(tc, E_width_prec_hash_post);
  tcase_add_test(tc, E_width_prec_hash_zero);
  tcase_add_test(tc, E_width_prec_hash_ng_z);
  tcase_add_test(tc, E_width_prec_zero_negt);
  tcase_add_test(tc, E_width_prec_zero_post);
  tcase_add_test(tc, E_width_prec_zero_zero);
  tcase_add_test(tc, E_width_prec_zero_ng_z);
  tcase_add_test(tc, E_dynamic_width);
  tcase_add_test(tc, E_dynamic_precision);
  tcase_add_test(tc, E_dynamic_width_precision);
  tcase_add_test(tc, E_width_negt);
  tcase_add_test(tc, E_width_post);
  tcase_add_test(tc, E_width_zero);
  tcase_add_test(tc, E_width_ng_z);
  tcase_add_test(tc, E_prec_negt);
  tcase_add_test(tc, E_prec_post);
  tcase_add_test(tc, E_prec_zero_);
  tcase_add_test(tc, E_prec_ng_z);
  tcase_add_test(tc, E_width_prec_negt);
  tcase_add_test(tc, E_width_prec_post);
  tcase_add_test(tc, E_width_prec_zero);
  tcase_add_test(tc, E_width_prec_ng_z);
  tcase_add_test(tc, E_zero_prec_negt);
  tcase_add_test(tc, E_zero_prec_post);
  tcase_add_test(tc, E_zero_prec_zero);
  tcase_add_test(tc, E_zero_prec_ng_z);
  tcase_add_test(tc, E_zero_zero_negt);
  tcase_add_test(tc, E_zero_zero_post);
  tcase_add_test(tc, E_zero_zero_zero);
  tcase_add_test(tc, E_zero_zero_ng_z);
  tcase_add_test(tc, E_zero_prec_zero_negt);
  tcase_add_test(tc, E_zero_prec_zero_post);
  tcase_add_test(tc, E_zero_prec_zero_zero);
  tcase_add_test(tc, E_zero_prec_zero_ng_z);
  tcase_add_test(tc, E_zero_prec_minus_zero);
  tcase_add_test(tc, E_zero_prec_plus_zero);
  tcase_add_test(tc, E_zero_prec_space_zero);
  tcase_add_test(tc, E_zero_prec_hash_zero);
  tcase_add_test(tc, E_zero_zero_plus_zero);
  tcase_add_test(tc, E_zero_zero_space_zero);
  tcase_add_test(tc, E_zero_zero_hash_zero);
  tcase_add_test(tc, E_zero_prec_zero_plus_zero);
  tcase_add_test(tc, E_zero_prec_zero_space_zero);
  tcase_add_test(tc, E_zero_prec_zero_hash_zero);
  tcase_add_test(tc, g_minus_negt);
  tcase_add_test(tc, g_minus_post);
  tcase_add_test(tc, g_minus_zero_);
  tcase_add_test(tc, g_minus_ng_z);
  tcase_add_test(tc, g_plus_negt);
  tcase_add_test(tc, g_plus_post);
  tcase_add_test(tc, g_plus_zero);
  tcase_add_test(tc, g_plus_ng_z);
  tcase_add_test(tc, g_space_negt);
  tcase_add_test(tc, g_space_post);
  tcase_add_test(tc, g_space_zero);
  tcase_add_test(tc, g_space_ng_z);
  tcase_add_test(tc, g_hash_negt);
  tcase_add_test(tc, g_hash_post);
  tcase_add_test(tc, g_hash_zero);
  tcase_add_test(tc, g_hash_ng_z);
  tcase_add_test(tc, g_zero_negt);
  tcase_add_test(tc, g_zero_post);
  tcase_add_test(tc, g_zero_zero);
  tcase_add_test(tc, g_zero_ng_z);
  tcase_add_test(tc, g_width_minus_negt);
  tcase_add_test(tc, g_width_minus_post);
  tcase_add_test(tc, g_width_minus_zero);
  tcase_add_test(tc, g_width_minus_ng_z);
  tcase_add_test(tc, g_width_plus_negt);
  tcase_add_test(tc, g_width_plus_post);
  tcase_add_test(tc, g_width_plus_zero);
  tcase_add_test(tc, g_width_plus_ng_z);
  tcase_add_test(tc, g_width_space_negt);
  tcase_add_test(tc, g_width_space_post);
  tcase_add_test(tc, g_width_space_zero);
  tcase_add_test(tc, g_width_space_ng_z);
  tcase_add_test(tc, g_width_hash_negt);
  tcase_add_test(tc, g_width_hash_post);
  tcase_add_test(tc, g_width_hash_zero);
  tcase_add_test(tc, g_width_hash_ng_z);
  tcase_add_test(tc, g_width_zero_negt);
  tcase_add_test(tc, g_width_zero_post);
  tcase_add_test(tc, g_width_zero_zero);
  tcase_add_test(tc, g_width_zero_ng_z);
  tcase_add_test(tc, g_prec_minus_negt);
  tcase_add_test(tc, g_prec_minus_post);
  tcase_add_test(tc, g_prec_minus_zero);
  tcase_add_test(tc, g_prec_minus_ng_z);
  tcase_add_test(tc, g_prec_plus_negt);
  tcase_add_test(tc, g_prec_plus_post);
  tcase_add_test(tc, g_prec_plus_zero);
  tcase_add_test(tc, g_prec_plus_ng_z);
  tcase_add_test(tc, g_prec_space_negt);
  tcase_add_test(tc, g_prec_space_post);
  tcase_add_test(tc, g_prec_space_zero);
  tcase_add_test(tc, g_prec_space_ng_z);
  tcase_add_test(tc, g_prec_hash_negt);
  tcase_add_test(tc, g_prec_hash_post);
  tcase_add_test(tc, g_prec_hash_zero);
  tcase_add_test(tc, g_prec_hash_ng_z);
  tcase_add_test(tc, g_prec_zero_negt);
  tcase_add_test(tc, g_prec_zero_post);
  tcase_add_test(tc, g_prec_zero_zero);
  tcase_add_test(tc, g_prec_zero_ng_z);
  tcase_add_test(tc, g_width_prec_minus_negt);
  tcase_add_test(tc, g_width_prec_minus_post);
  tcase_add_test(tc, g_width_prec_minus_zero);
  tcase_add_test(tc, g_width_prec_minus_ng_z);
  tcase_add_test(tc, g_width_prec_plus_negt);
  tcase_add_test(tc, g_width_prec_plus_post);
  tcase_add_test(tc, g_width_prec_plus_zero);
  tcase_add_test(tc, g_width_prec_plus_ng_z);
  tcase_add_test(tc, g_width_prec_space_negt);
  tcase_add_test(tc, g_width_prec_space_post);
  tcase_add_test(tc, g_width_prec_space_zero);
  tcase_add_test(tc, g_width_prec_space_ng_z);
  tcase_add_test(tc, g_width_prec_hash_negt);
  tcase_add_test(tc, g_width_prec_hash_post);
  tcase_add_test(tc, g_width_prec_hash_zero);
  tcase_add_test(tc, g_width_prec_hash_ng_z);
  tcase_add_test(tc, g_width_prec_zero_negt);
  tcase_add_test(tc, g_width_prec_zero_post);
  tcase_add_test(tc, g_width_prec_zero_zero);
  tcase_add_test(tc, g_width_prec_zero_ng_z);
  tcase_add_test(tc, g_dynamic_width);
  tcase_add_test(tc, g_dynamic_precision);
  tcase_add_test(tc, g_dynamic_width_precision);
  tcase_add_test(tc, g_width_negt);
  tcase_add_test(tc, g_width_post);
  tcase_add_test(tc, g_width_zero);
  tcase_add_test(tc, g_width_ng_z);
  tcase_add_test(tc, g_prec_negt);
  tcase_add_test(tc, g_prec_post);
  tcase_add_test(tc, g_prec_zero_);
  tcase_add_test(tc, g_prec_ng_z);
  tcase_add_test(tc, g_width_prec_negt);
  tcase_add_test(tc, g_width_prec_post);
  tcase_add_test(tc, g_width_prec_zero);
  tcase_add_test(tc, g_width_prec_ng_z);
  tcase_add_test(tc, g_zero_prec_negt);
  tcase_add_test(tc, g_zero_prec_post);
  tcase_add_test(tc, g_zero_prec_zero);
  tcase_add_test(tc, g_zero_prec_ng_z);
  tcase_add_test(tc, g_zero_zero_negt);
  tcase_add_test(tc, g_zero_zero_post);
  tcase_add_test(tc, g_zero_zero_zero);
  tcase_add_test(tc, g_zero_zero_ng_z);
  tcase_add_test(tc, g_zero_prec_zero_negt);
  tcase_add_test(tc, g_zero_prec_zero_post);
  tcase_add_test(tc, g_zero_prec_zero_zero);
  tcase_add_test(tc, g_zero_prec_zero_ng_z);
  tcase_add_test(tc, g_zero_prec_minus_zero);
  tcase_add_test(tc, g_zero_prec_plus_zero);
  tcase_add_test(tc, g_zero_prec_space_zero);
  tcase_add_test(tc, g_zero_prec_hash_zero);
  tcase_add_test(tc, g_zero_zero_plus_zero);
  tcase_add_test(tc, g_zero_zero_space_zero);
  tcase_add_test(tc, g_zero_zero_hash_zero);
  tcase_add_test(tc, g_zero_prec_zero_plus_zero);
  tcase_add_test(tc, g_zero_prec_zero_space_zero);
  tcase_add_test(tc, g_zero_prec_zero_hash_zero);
  tcase_add_test(tc, G_minus_negt);
  tcase_add_test(tc, G_minus_post);
  tcase_add_test(tc, G_minus_zero_);
  tcase_add_test(tc, G_minus_ng_z);
  tcase_add_test(tc, G_plus_negt);
  tcase_add_test(tc, G_plus_post);
  tcase_add_test(tc, G_plus_zero);
  tcase_add_test(tc, G_plus_ng_z);
  tcase_add_test(tc, G_space_negt);
  tcase_add_test(tc, G_space_post);
  tcase_add_test(tc, G_space_zero);
  tcase_add_test(tc, G_space_ng_z);
  tcase_add_test(tc, G_hash_negt);
  tcase_add_test(tc, G_hash_post);
  tcase_add_test(tc, G_hash_zero);
  tcase_add_test(tc, G_hash_ng_z);
  tcase_add_test(tc, G_zero_negt);
  tcase_add_test(tc, G_zero_post);
  tcase_add_test(tc, G_zero_zero);
  tcase_add_test(tc, G_zero_ng_z);
  tcase_add_test(tc, G_width_minus_negt);
  tcase_add_test(tc, G_width_minus_post);
  tcase_add_test(tc, G_width_minus_zero);
  tcase_add_test(tc, G_width_minus_ng_z);
  tcase_add_test(tc, G_width_plus_negt);
  tcase_add_test(tc, G_width_plus_post);
  tcase_add_test(tc, G_width_plus_zero);
  tcase_add_test(tc, G_width_plus_ng_z);
  tcase_add_test(tc, G_width_space_negt);
  tcase_add_test(tc, G_width_space_post);
  tcase_add_test(tc, G_width_space_zero);
  tcase_add_test(tc, G_width_space_ng_z);
  tcase_add_test(tc, G_width_hash_negt);
  tcase_add_test(tc, G_width_hash_post);
  tcase_add_test(tc, G_width_hash_zero);
  tcase_add_test(tc, G_width_hash_ng_z);
  tcase_add_test(tc, G_width_zero_negt);
  tcase_add_test(tc, G_width_zero_post);
  tcase_add_test(tc, G_width_zero_zero);
  tcase_add_test(tc, G_width_zero_ng_z);
  tcase_add_test(tc, G_prec_minus_negt);
  tcase_add_test(tc, G_prec_minus_post);
  tcase_add_test(tc, G_prec_minus_zero);
  tcase_add_test(tc, G_prec_minus_ng_z);
  tcase_add_test(tc, G_prec_plus_negt);
  tcase_add_test(tc, G_prec_plus_post);
  tcase_add_test(tc, G_prec_plus_zero);
  tcase_add_test(tc, G_prec_plus_ng_z);
  tcase_add_test(tc, G_prec_space_negt);
  tcase_add_test(tc, G_prec_space_post);
  tcase_add_test(tc, G_prec_space_zero);
  tcase_add_test(tc, G_prec_space_ng_z);
  tcase_add_test(tc, G_prec_hash_negt);
  tcase_add_test(tc, G_prec_hash_post);
  tcase_add_test(tc, G_prec_hash_zero);
  tcase_add_test(tc, G_prec_hash_ng_z);
  tcase_add_test(tc, G_prec_zero_negt);
  tcase_add_test(tc, G_prec_zero_post);
  tcase_add_test(tc, G_prec_zero_zero);
  tcase_add_test(tc, G_prec_zero_ng_z);
  tcase_add_test(tc, G_width_prec_minus_negt);
  tcase_add_test(tc, G_width_prec_minus_post);
  tcase_add_test(tc, G_width_prec_minus_zero);
  tcase_add_test(tc, G_width_prec_minus_ng_z);
  tcase_add_test(tc, G_width_prec_plus_negt);
  tcase_add_test(tc, G_width_prec_plus_post);
  tcase_add_test(tc, G_width_prec_plus_zero);
  tcase_add_test(tc, G_width_prec_plus_ng_z);
  tcase_add_test(tc, G_width_prec_space_negt);
  tcase_add_test(tc, G_width_prec_space_post);
  tcase_add_test(tc, G_width_prec_space_zero);
  tcase_add_test(tc, G_width_prec_space_ng_z);
  tcase_add_test(tc, G_width_prec_hash_negt);
  tcase_add_test(tc, G_width_prec_hash_post);
  tcase_add_test(tc, G_width_prec_hash_zero);
  tcase_add_test(tc, G_width_prec_hash_ng_z);
  tcase_add_test(tc, G_width_prec_zero_negt);
  tcase_add_test(tc, G_width_prec_zero_post);
  tcase_add_test(tc, G_width_prec_zero_zero);
  tcase_add_test(tc, G_width_prec_zero_ng_z);
  tcase_add_test(tc, G_dynamic_width);
  tcase_add_test(tc, G_dynamic_precision);
  tcase_add_test(tc, G_dynamic_width_precision);
  tcase_add_test(tc, G_width_negt);
  tcase_add_test(tc, G_width_post);
  tcase_add_test(tc, G_width_zero);
  tcase_add_test(tc, G_width_ng_z);
  tcase_add_test(tc, G_prec_negt);
  tcase_add_test(tc, G_prec_post);
  tcase_add_test(tc, G_prec_zero_);
  tcase_add_test(tc, G_prec_ng_z);
  tcase_add_test(tc, G_width_prec_negt);
  tcase_add_test(tc, G_width_prec_post);
  tcase_add_test(tc, G_width_prec_zero);
  tcase_add_test(tc, G_width_prec_ng_z);
  tcase_add_test(tc, G_zero_prec_negt);
  tcase_add_test(tc, G_zero_prec_post);
  tcase_add_test(tc, G_zero_prec_zero);
  tcase_add_test(tc, G_zero_prec_ng_z);
  tcase_add_test(tc, G_zero_zero_negt);
  tcase_add_test(tc, G_zero_zero_post);
  tcase_add_test(tc, G_zero_zero_zero);
  tcase_add_test(tc, G_zero_zero_ng_z);
  tcase_add_test(tc, G_zero_prec_zero_negt);
  tcase_add_test(tc, G_zero_prec_zero_post);
  tcase_add_test(tc, G_zero_prec_zero_zero);
  tcase_add_test(tc, G_zero_prec_zero_ng_z);
  tcase_add_test(tc, G_zero_prec_minus_zero);
  tcase_add_test(tc, G_zero_prec_plus_zero);
  tcase_add_test(tc, G_zero_prec_space_zero);
  tcase_add_test(tc, G_zero_prec_hash_zero);
  tcase_add_test(tc, G_zero_zero_plus_zero);
  tcase_add_test(tc, G_zero_zero_space_zero);
  tcase_add_test(tc, G_zero_zero_hash_zero);
  tcase_add_test(tc, G_zero_prec_zero_plus_zero);
  tcase_add_test(tc, G_zero_prec_zero_space_zero);
  tcase_add_test(tc, G_zero_prec_zero_hash_zero);
  tcase_add_test(tc, s_minus);
  tcase_add_test(tc, s_width);
  tcase_add_test(tc, s_precision);
  tcase_add_test(tc, s_width_precision);
  tcase_add_test(tc, s_star_width);
  tcase_add_test(tc, s_star_precision);
  tcase_add_test(tc, s_star_both);
  tcase_add_test(tc, s_null_wish_form);
  tcase_add_test(tc, s_minus_zero_);
  tcase_add_test(tc, s_width_minus_zero);
  tcase_add_test(tc, s_prec_minus_zero);
  tcase_add_test(tc, s_width_prec_minus_zero);
  tcase_add_test(tc, s_dynamic_width);
  tcase_add_test(tc, s_dynamic_precision);
  tcase_add_test(tc, s_dynamic_width_precision);
  tcase_add_test(tc, s_width_zero);
  tcase_add_test(tc, s_prec_zero_);
  tcase_add_test(tc, s_width_prec_zero);
  tcase_add_test(tc, s_zero_prec_zero);
  tcase_add_test(tc, s_zero_prec_minus_zero);
  tcase_add_test(tc, c_minus_zero_);
  tcase_add_test(tc, c_width_minus_zero);
  tcase_add_test(tc, c_dynamic_width);
  tcase_add_test(tc, c_width_zero);
  tcase_add_test(tc, p_minus_zero_);
  tcase_add_test(tc, p_width_minus_zero);
  tcase_add_test(tc, p_dynamic_width);
  tcase_add_test(tc, test_s21_sprintf_p_format);

  suite_add_tcase(ss, tc);
  return ss;
}

static void setup_wide(void) {
  if (!setlocale(LC_ALL, "en_US.UTF-8")) {
    setlocale(LC_ALL, "C.UTF-8");
  }
}

// =============================================
//                  TESTS FOR %lc
// =============================================

START_TEST(test_lc_basic) {
  wchar_t wc = L'Я';
  char buf1[32], buf2[32];
  int res1 = s21_sprintf(buf1, "%lc", wc);
  int res2 = sprintf(buf2, "%lc", wc);
  ck_assert_str_eq(buf1, buf2);
  ck_assert_int_eq(res1, res2);
}
END_TEST

START_TEST(test_lc_ascii) {
  wchar_t wc = L'A';
  char buf1[32], buf2[32];
  int res1 = s21_sprintf(buf1, "[%lc]", wc);
  int res2 = sprintf(buf2, "[%lc]", wc);
  ck_assert_str_eq(buf1, buf2);
  ck_assert_int_eq(res1, res2);
}
END_TEST

START_TEST(test_lc_null_char) {
  wchar_t wc = L'\0';
  char buf1[32], buf2[32];
  int res1 = s21_sprintf(buf1, "[%lc]", wc);
  int res2 = sprintf(buf2, "[%lc]", wc);
  ck_assert_str_eq(buf1, buf2);
  ck_assert_int_eq(res1, res2);
}
END_TEST

START_TEST(test_lc_min) {
  wchar_t wc = WCHAR_MIN;
  char buf1[32], buf2[32];
  int res1 = s21_sprintf(buf1, "%lc", wc);
  int res2 = sprintf(buf2, "%lc", wc);
  ck_assert_str_eq(buf1, buf2);
  ck_assert_int_eq(res1, res2);
}
END_TEST

START_TEST(test_lc_max) {
  wchar_t wc = WCHAR_MAX;
  char buf1[32], buf2[32];
  int res1 = s21_sprintf(buf1, "%lc", wc);
  int res2 = sprintf(buf2, "%lc", wc);
  ck_assert_str_eq(buf1, buf2);
  ck_assert_int_eq(res1, res2);
}
END_TEST

START_TEST(test_lc_width) {
  wchar_t wc = L'€';
  char buf1[32], buf2[32];
  int res1 = s21_sprintf(buf1, "%8lc", wc);
  int res2 = sprintf(buf2, "%8lc", wc);
  ck_assert_str_eq(buf1, buf2);
  ck_assert_int_eq(res1, res2);
}
END_TEST

START_TEST(test_lc_width_left_align) {
  wchar_t wc = L'ß';
  char buf1[32], buf2[32];
  int res1 = s21_sprintf(buf1, "%-6lc", wc);
  int res2 = sprintf(buf2, "%-6lc", wc);
  ck_assert_str_eq(buf1, buf2);
  ck_assert_int_eq(res1, res2);
}
END_TEST

// =============================================
//                  TESTS FOR %ls
// =============================================

START_TEST(test_ls_basic) {
  wchar_t *ws = L"Привет, 世界!";
  char buf1[128], buf2[128];
  int res1 = s21_sprintf(buf1, "%ls", ws);
  int res2 = sprintf(buf2, "%ls", ws);
  ck_assert_str_eq(buf1, buf2);
  ck_assert_int_eq(res1, res2);
}
END_TEST

START_TEST(test_ls_ascii) {
  wchar_t *ws = L"ASCII";
  char buf1[32], buf2[32];
  int res1 = s21_sprintf(buf1, "[%ls]", ws);
  int res2 = sprintf(buf2, "[%ls]", ws);
  ck_assert_str_eq(buf1, buf2);
  ck_assert_int_eq(res1, res2);
}
END_TEST

START_TEST(test_ls_null) {
  wchar_t *ws = NULL;
  char buf1[32], buf2[32];
  int res1 = s21_sprintf(buf1, "%ls", ws);
  int res2 = sprintf(buf2, "%ls", ws);
  ck_assert_str_eq(buf1, buf2);
  ck_assert_int_eq(res1, res2);
}
END_TEST

START_TEST(test_ls_empty) {
  wchar_t *ws = L"";
  char buf1[32], buf2[32];
  int res1 = s21_sprintf(buf1, "[%ls]", ws);
  int res2 = sprintf(buf2, "[%ls]", ws);
  ck_assert_str_eq(buf1, buf2);
  ck_assert_int_eq(res1, res2);
}
END_TEST

START_TEST(test_ls_width) {
  wchar_t *ws = L"漢字";
  char buf1[32], buf2[32];
  int res1 = s21_sprintf(buf1, "%10ls", ws);
  int res2 = sprintf(buf2, "%10ls", ws);
  ck_assert_str_eq(buf1, buf2);
  ck_assert_int_eq(res1, res2);
}
END_TEST

START_TEST(test_ls_width_left_align) {
  wchar_t *ws = L"test";
  char buf1[32], buf2[32];
  int res1 = s21_sprintf(buf1, "%-10ls", ws);
  int res2 = sprintf(buf2, "%-10ls", ws);
  ck_assert_str_eq(buf1, buf2);
  ck_assert_int_eq(res1, res2);
}
END_TEST

START_TEST(test_ls_precision) {
  wchar_t *ws = L"абвгд";
  char buf1[32], buf2[32];
  int res1 = s21_sprintf(buf1, "%.2ls", ws);
  int res2 = sprintf(buf2, "%.2ls", ws);
  ck_assert_str_eq(buf1, buf2);
  ck_assert_int_eq(res1, res2);
}
END_TEST

START_TEST(test_ls_precision_zero) {
  wchar_t *ws = L"anything";
  char buf1[32], buf2[32];
  int res1 = s21_sprintf(buf1, "%.0ls", ws);
  int res2 = sprintf(buf2, "%.0ls", ws);
  ck_assert_str_eq(buf1, buf2);
  ck_assert_int_eq(res1, res2);
}
END_TEST

START_TEST(test_ls_precision_large) {
  wchar_t *ws = L"short";
  char buf1[32], buf2[32];
  int res1 = s21_sprintf(buf1, "%.10ls", ws);
  int res2 = sprintf(buf2, "%.10ls", ws);
  ck_assert_str_eq(buf1, buf2);
  ck_assert_int_eq(res1, res2);
}
END_TEST

START_TEST(test_ls_width_precision) {
  wchar_t *ws = L"こんにちは";
  char buf1[64], buf2[64];
  int res1 = s21_sprintf(buf1, "%15.2ls", ws);
  int res2 = sprintf(buf2, "%15.2ls", ws);
  ck_assert_str_eq(buf1, buf2);
  ck_assert_int_eq(res1, res2);
}
END_TEST

START_TEST(test_ls_width_precision_left_align) {
  wchar_t *ws = L"align";
  char buf1[32], buf2[32];
  int res1 = s21_sprintf(buf1, "%-8.3ls", ws);
  int res2 = sprintf(buf2, "%-8.3ls", ws);
  ck_assert_str_eq(buf1, buf2);
  ck_assert_int_eq(res1, res2);
}
END_TEST

START_TEST(test_ls_surrogate_pair) {
  wchar_t ws[] = {0xD83D, 0xDE00, 0};  // 😀
  char buf1[32], buf2[32];
  int res1 = s21_sprintf(buf1, "%ls", ws);
  int res2 = sprintf(buf2, "%ls", ws);
  ck_assert_str_eq(buf1, buf2);
  ck_assert_int_eq(res1, res2);
}
END_TEST

START_TEST(test_ls_mixed_chars) {
  wchar_t *ws = L"ABC\xE0\xF0 日本語";
  char buf1[128], buf2[128];
  int res1 = s21_sprintf(buf1, "[%ls]", ws);
  int res2 = sprintf(buf2, "[%ls]", ws);
  ck_assert_str_eq(buf1, buf2);
  ck_assert_int_eq(res1, res2);
}
END_TEST

// =============================================
//               TEST CASES FOR %ls
// =============================================

START_TEST(test_s21_sprintf_ls_minus) {
  wchar_t *ws = L"Hello";
  char buf1[32], buf2[32];
  int res1 = s21_sprintf(buf1, "%-20ls", ws);
  int res2 = sprintf(buf2, "%-20ls", ws);
  ck_assert_str_eq(buf1, buf2);
  ck_assert_int_eq(res1, res2);
}
END_TEST

START_TEST(test_s21_sprintf_ls_width) {
  wchar_t *ws = L"Hello";
  char buf1[32], buf2[32];
  int res1 = s21_sprintf(buf1, "%20ls", ws);
  int res2 = sprintf(buf2, "%20ls", ws);
  ck_assert_str_eq(buf1, buf2);
  ck_assert_int_eq(res1, res2);
}
END_TEST

START_TEST(test_s21_sprintf_ls_precision) {
  wchar_t *ws = L"Hello, world!";
  char buf1[32], buf2[32];
  int res1 = s21_sprintf(buf1, "%.5ls", ws);
  int res2 = sprintf(buf2, "%.5ls", ws);
  ck_assert_str_eq(buf1, buf2);
  ck_assert_int_eq(res1, res2);
}
END_TEST

START_TEST(test_s21_sprintf_ls_width_precision) {
  wchar_t *ws = L"Hello, world!";
  char buf1[32], buf2[32];
  int res1 = s21_sprintf(buf1, "%20.5ls", ws);
  int res2 = sprintf(buf2, "%20.5ls", ws);
  ck_assert_str_eq(buf1, buf2);
  ck_assert_int_eq(res1, res2);
}
END_TEST

START_TEST(test_s21_sprintf_ls_star_width) {
  wchar_t *ws = L"Hello";
  char buf1[32], buf2[32];
  int res1 = s21_sprintf(buf1, "%*ls", 20, ws);
  int res2 = sprintf(buf2, "%*ls", 20, ws);
  ck_assert_str_eq(buf1, buf2);
  ck_assert_int_eq(res1, res2);
}
END_TEST

START_TEST(test_s21_sprintf_ls_star_precision) {
  wchar_t *ws = L"Hello, world!";
  char buf1[32], buf2[32];
  int res1 = s21_sprintf(buf1, "%.*ls", 5, ws);
  int res2 = sprintf(buf2, "%.*ls", 5, ws);
  ck_assert_str_eq(buf1, buf2);
  ck_assert_int_eq(res1, res2);
}
END_TEST

START_TEST(test_s21_sprintf_ls_star_both) {
  wchar_t *ws = L"Hello, world!";
  char buf1[32], buf2[32];
  int res1 = s21_sprintf(buf1, "%*.*ls", 20, 5, ws);
  int res2 = sprintf(buf2, "%*.*ls", 20, 5, ws);
  ck_assert_str_eq(buf1, buf2);
  ck_assert_int_eq(res1, res2);
}
END_TEST

START_TEST(test_s21_sprintf_ls) {
  wchar_t *ws = L"Hello, world!";
  char buf1[64], buf2[64];
  int res1 = s21_sprintf(buf1, "wchar_t: %ls", ws);
  int res2 = sprintf(buf2, "wchar_t: %ls", ws);
  ck_assert_str_eq(buf1, buf2);
  ck_assert_int_eq(res1, res2);
}
END_TEST

START_TEST(test_s21_sprintf_ls_special) {
  wchar_t *ws = L"Hello\tWorld\n";
  char buf1[64], buf2[64];
  int res1 = s21_sprintf(buf1, "wchar_t: %ls", ws);
  int res2 = sprintf(buf2, "wchar_t: %ls", ws);
  ck_assert_str_eq(buf1, buf2);
  ck_assert_int_eq(res1, res2);
}
END_TEST

START_TEST(test_s21_sprintf_ls_special_chars) {
  wchar_t *ws = L"Line1\nLine2\tTab\x01";
  char buf1[64], buf2[64];
  int res1 = s21_sprintf(buf1, "wchar_t: %ls", ws);
  int res2 = sprintf(buf2, "wchar_t: %ls", ws);
  ck_assert_str_eq(buf1, buf2);
  ck_assert_int_eq(res1, res2);
}
END_TEST

START_TEST(test_s21_sprintf_ls_unicode) {
  wchar_t *ws = L"Привет мир!";
  char buf1[64], buf2[64];
  int res1 = s21_sprintf(buf1, "wchar_t: %ls", ws);
  int res2 = sprintf(buf2, "wchar_t: %ls", ws);
  ck_assert_str_eq(buf1, buf2);
  ck_assert_int_eq(res1, res2);
}
END_TEST

START_TEST(test_s21_sprintf_ls_empty) {
  wchar_t *ws = L"";
  char buf1[64], buf2[64];
  int res1 = s21_sprintf(buf1, "wchar_t: %ls", ws);
  int res2 = sprintf(buf2, "wchar_t: %ls", ws);
  ck_assert_str_eq(buf1, buf2);
  ck_assert_int_eq(res1, res2);
}
END_TEST

// =============================================
//               TEST CASES FOR %lc
// =============================================

START_TEST(test_s21_sprintf_lc_minus) {
  wchar_t wc = L'A';
  char buf1[32], buf2[32];
  int res1 = s21_sprintf(buf1, "%-5lc", wc);
  int res2 = sprintf(buf2, "%-5lc", wc);
  ck_assert_str_eq(buf1, buf2);
  ck_assert_int_eq(res1, res2);
}
END_TEST

START_TEST(test_s21_sprintf_lc_width) {
  wchar_t wc = L'A';
  char buf1[32], buf2[32];
  int res1 = s21_sprintf(buf1, "%5lc", wc);
  int res2 = sprintf(buf2, "%5lc", wc);
  ck_assert_str_eq(buf1, buf2);
  ck_assert_int_eq(res1, res2);
}
END_TEST

START_TEST(test_s21_sprintf_lc_star_width) {
  wchar_t wc = L'A';
  char buf1[32], buf2[32];
  int res1 = s21_sprintf(buf1, "%*lc", 5, wc);
  int res2 = sprintf(buf2, "%*lc", 5, wc);
  ck_assert_str_eq(buf1, buf2);
  ck_assert_int_eq(res1, res2);
}
END_TEST

START_TEST(test_s21_sprintf_lc) {
  wchar_t wc = L'A';
  char buf1[64], buf2[64];
  int res1 = s21_sprintf(buf1, "wchar_t: %lc", wc);
  int res2 = sprintf(buf2, "wchar_t: %lc", wc);
  ck_assert_str_eq(buf1, buf2);
  ck_assert_int_eq(res1, res2);
}
END_TEST

START_TEST(test_s21_sprintf_lc_min) {
  wchar_t wc = -128;
  char buf1[64], buf2[64];
  int res1 = s21_sprintf(buf1, "wchar_t: %lc", wc);
  int res2 = sprintf(buf2, "wchar_t: %lc", wc);
  ck_assert_str_eq(buf1, buf2);
  ck_assert_int_eq(res1, res2);
}
END_TEST

START_TEST(test_s21_sprintf_lc_min_pl) {
  wchar_t wc = -129;
  char buf1[64], buf2[64];
  int res1 = s21_sprintf(buf1, "wchar_t: %lc", wc);
  int res2 = sprintf(buf2, "wchar_t: %lc", wc);
  ck_assert_str_eq(buf1, buf2);
  ck_assert_int_eq(res1, res2);
}
END_TEST

START_TEST(test_s21_sprintf_lc_max) {
  wchar_t wc = 127;
  char buf1[64], buf2[64];
  int res1 = s21_sprintf(buf1, "wchar_t: %lc", wc);
  int res2 = sprintf(buf2, "wchar_t: %lc", wc);
  ck_assert_str_eq(buf1, buf2);
  ck_assert_int_eq(res1, res2);
}
END_TEST

START_TEST(test_s21_sprintf_lc_max_pl) {
  wchar_t wc = 128;
  char buf1[64], buf2[64];
  int res1 = s21_sprintf(buf1, "wchar_t: %lc", wc);
  int res2 = sprintf(buf2, "wchar_t: %lc", wc);
  ck_assert_str_eq(buf1, buf2);
  ck_assert_int_eq(res1, res2);
}
END_TEST

START_TEST(test_s21_sprintf_lc_nonprint) {
  wchar_t wc = L'\x01';
  char buf1[64], buf2[64];
  int res1 = s21_sprintf(buf1, "wchar_t: %lc", wc);
  int res2 = sprintf(buf2, "wchar_t: %lc", wc);
  ck_assert_str_eq(buf1, buf2);
  ck_assert_int_eq(res1, res2);
}
END_TEST

START_TEST(test_s21_sprintf_lc_zero) {
  wchar_t wc = 0;
  char buf1[64], buf2[64];
  int res1 = s21_sprintf(buf1, "wchar_t: %lc", wc);
  int res2 = sprintf(buf2, "wchar_t: %lc", wc);
  ck_assert_str_eq(buf1, buf2);
  ck_assert_int_eq(res1, res2);
}
END_TEST

START_TEST(test_s21_sprintf_lc_newline) {
  wchar_t wc = L'\n';
  char buf1[64], buf2[64];
  int res1 = s21_sprintf(buf1, "wchar_t: %lc", wc);
  int res2 = sprintf(buf2, "wchar_t: %lc", wc);
  ck_assert_str_eq(buf1, buf2);
  ck_assert_int_eq(res1, res2);
}
END_TEST

START_TEST(test_s21_sprintf_lc_tab) {
  wchar_t wc = L'\t';
  char buf1[64], buf2[64];
  int res1 = s21_sprintf(buf1, "wchar_t: %lc", wc);
  int res2 = sprintf(buf2, "wchar_t: %lc", wc);
  ck_assert_str_eq(buf1, buf2);
  ck_assert_int_eq(res1, res2);
}
END_TEST

START_TEST(test_s21_sprintf_lc_null_char) {
  wchar_t wc = L'\0';
  char buf1[64], buf2[64];
  int res1 = s21_sprintf(buf1, "wchar_t: %lc", wc);
  int res2 = sprintf(buf2, "wchar_t: %lc", wc);
  ck_assert_str_eq(buf1, buf2);
  ck_assert_int_eq(res1, res2);
}
END_TEST

START_TEST(test_s21_sprintf_lc_wide_chars) {
  // Сохраняем текущую локаль
  char *old_locale = strdup(setlocale(LC_ALL, NULL));
  setlocale(LC_ALL, "en_US.UTF-8");

  wchar_t test_chars[] = {WCHAR_MIN, 0,    1,      127,     128,      255,
                          256,       1024, 0xFFFF, 0x10000, 0x10FFFF, L'A',
                          L'€',      L'я', L'あ',  L'𐍈',    WCHAR_MAX};
  size_t count = sizeof(test_chars) / sizeof(test_chars[0]);

  for (size_t i = 0; i < count; i++) {
    wchar_t wc = test_chars[i];
    char str1[100];
    char str2[100];

    int res1 = s21_sprintf(str1, "wchar_t: %d: %lc", (int)test_chars[i], wc);
    int res2 = sprintf(str2, "wchar_t: %d: %lc", (int)test_chars[i], wc);

    ck_assert_str_eq(str1, str2);
    ck_assert_int_eq(res1, res2);
  }

  // Проверка всех значений 0-255
  for (int i = 0; i <= 255; i++) {
    wchar_t wc = (wchar_t)i;
    char str1[100];
    char str2[100];

    int res1 = s21_sprintf(str1, "wchar_t: %d: %lc", i, wc);
    int res2 = sprintf(str2, "wchar_t: %d: %lc", i, wc);

    ck_assert_str_eq(str1, str2);
    ck_assert_int_eq(res1, res2);
  }

  // Восстанавливаем исходную локаль
  setlocale(LC_ALL, old_locale);
  free(old_locale);
}
END_TEST

// ================================================================
// Тесты для строковых спецификаторов (s, c)
// ================================================================

// Тесты для %s
TEST_SPRINTF(ls_null_wish_form, "%.5ls", NULL, wchar_t *)

TEST_SPRINTF(ls_minus_zero_, "%-ls", 0, wchar_t *)
TEST_SPRINTF(ls_width_minus_zero, "%-5ls", 0, wchar_t *)
TEST_SPRINTF(ls_prec_minus_zero, "%-.5ls", 0, wchar_t *)
TEST_SPRINTF(ls_width_prec_minus_zero, "%-10.5ls", 0, wchar_t *)
TEST_SPRINTF_2(ls_dynamic_width, "%*ls", 10, 0, wchar_t *)
TEST_SPRINTF_2(ls_dynamic_precision, "%.*ls", 5, 0, wchar_t *)
TEST_SPRINTF_3(ls_dynamic_width_precision, "%*.*ls", 10, 5, 0, wchar_t *)
TEST_SPRINTF(ls_width_zero, "%5ls", 0, wchar_t *)
TEST_SPRINTF(ls_prec_zero_, "%.5ls", 0, wchar_t *)
TEST_SPRINTF(ls_width_prec_zero, "%10.5ls", 0, wchar_t *)
TEST_SPRINTF(ls_zero_prec_zero, "%.0ls", 0, wchar_t *)
TEST_SPRINTF(ls_zero_prec_minus_zero, "%-.0ls", 0, wchar_t *)

// Тесты для %c
TEST_SPRINTF(lc_minus_zero_, "%-lc", 'a', wchar_t)
TEST_SPRINTF(lc_width_minus_zero, "%-5lc", 'a', wchar_t)
TEST_SPRINTF_2(lc_dynamic_width, "%*lc", 10, 'a', wchar_t)
TEST_SPRINTF(lc_width_zero, "%5lc", 'a', wchar_t)

// =============================================
//                  TEST SUITE
// =============================================

Suite *sprintf_suite_lc_and_ls(void) {
  Suite *s = suite_create("test_sprintf_lc_and_ls");

  // Группа тестов для %lc
  TCase *tc = tcase_create("Core");
  tcase_add_checked_fixture(tc, setup_wide, NULL);

  tcase_add_test(tc, test_lc_basic);
  tcase_add_test(tc, test_lc_ascii);
  tcase_add_test(tc, test_lc_null_char);
  tcase_add_test(tc, test_lc_min);
  tcase_add_test(tc, test_lc_max);
  tcase_add_test(tc, test_lc_width);
  tcase_add_test(tc, test_lc_width_left_align);
  tcase_add_test(tc, test_ls_basic);
  tcase_add_test(tc, test_ls_ascii);
  tcase_add_test(tc, test_ls_null);
  tcase_add_test(tc, test_ls_empty);
  tcase_add_test(tc, test_ls_width);
  tcase_add_test(tc, test_ls_width_left_align);
  tcase_add_test(tc, test_ls_precision);
  tcase_add_test(tc, test_ls_precision_zero);
  tcase_add_test(tc, test_ls_precision_large);
  tcase_add_test(tc, test_ls_width_precision);
  tcase_add_test(tc, test_ls_width_precision_left_align);
  tcase_add_test(tc, test_ls_surrogate_pair);
  tcase_add_test(tc, test_ls_mixed_chars);
  tcase_add_test(tc, test_s21_sprintf_ls_minus);
  tcase_add_test(tc, test_s21_sprintf_ls_width);
  tcase_add_test(tc, test_s21_sprintf_ls_precision);
  tcase_add_test(tc, test_s21_sprintf_ls_width_precision);
  tcase_add_test(tc, test_s21_sprintf_ls_star_width);
  tcase_add_test(tc, test_s21_sprintf_ls_star_precision);
  tcase_add_test(tc, test_s21_sprintf_ls_star_both);
  tcase_add_test(tc, test_s21_sprintf_ls);
  tcase_add_test(tc, test_s21_sprintf_ls_special);
  tcase_add_test(tc, test_s21_sprintf_ls_special_chars);
  tcase_add_test(tc, test_s21_sprintf_ls_unicode);
  tcase_add_test(tc, test_s21_sprintf_ls_empty);
  tcase_add_test(tc, test_s21_sprintf_lc_minus);
  tcase_add_test(tc, test_s21_sprintf_lc_width);
  tcase_add_test(tc, test_s21_sprintf_lc_star_width);
  tcase_add_test(tc, test_s21_sprintf_lc);
  tcase_add_test(tc, test_s21_sprintf_lc_min);
  tcase_add_test(tc, test_s21_sprintf_lc_min_pl);
  tcase_add_test(tc, test_s21_sprintf_lc_max);
  tcase_add_test(tc, test_s21_sprintf_lc_max_pl);
  tcase_add_test(tc, test_s21_sprintf_lc_nonprint);
  tcase_add_test(tc, test_s21_sprintf_lc_zero);
  tcase_add_test(tc, test_s21_sprintf_lc_newline);
  tcase_add_test(tc, test_s21_sprintf_lc_tab);
  tcase_add_test(tc, test_s21_sprintf_lc_null_char);
  tcase_add_test(tc, test_s21_sprintf_lc_wide_chars);
  tcase_add_test(tc, ls_null_wish_form);
  tcase_add_test(tc, ls_minus_zero_);
  tcase_add_test(tc, ls_width_minus_zero);
  tcase_add_test(tc, ls_prec_minus_zero);
  tcase_add_test(tc, ls_width_prec_minus_zero);
  tcase_add_test(tc, ls_dynamic_width);
  tcase_add_test(tc, ls_dynamic_precision);
  tcase_add_test(tc, ls_dynamic_width_precision);
  tcase_add_test(tc, ls_width_zero);
  tcase_add_test(tc, ls_prec_zero_);
  tcase_add_test(tc, ls_width_prec_zero);
  tcase_add_test(tc, ls_zero_prec_zero);
  tcase_add_test(tc, ls_zero_prec_minus_zero);
  tcase_add_test(tc, lc_minus_zero_);
  tcase_add_test(tc, lc_width_minus_zero);
  tcase_add_test(tc, lc_dynamic_width);
  tcase_add_test(tc, lc_width_zero);

  suite_add_tcase(s, tc);

  return s;
}

int main(int argc, char **argv) {
  int failed = 0;
  Suite *s = sprintf_suite();
  SRunner *runner = srunner_create(s);

  if (argc > 1 && strcmp(argv[1], "+") == 0) {
    srunner_run_all(runner, CK_VERBOSE);
  } else {
    srunner_run_all(runner, CK_NORMAL);
  }

  failed = srunner_ntests_failed(runner);
  srunner_free(runner);

  int failed2 = 0;
  Suite *s2 = sprintf_suite_lc_and_ls();
  SRunner *runner2 = srunner_create(s2);

  if (argc > 1 && strcmp(argv[1], "+") == 0) {
    srunner_run_all(runner2, CK_VERBOSE);
  } else {
    srunner_run_all(runner2, CK_NORMAL);
  }

  failed2 = srunner_ntests_failed(runner2);
  srunner_free(runner2);

  return (failed == 0 || failed2 == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}