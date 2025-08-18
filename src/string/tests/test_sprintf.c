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

// =========================================================================
// МАКРОСЫ
// =========================================================================
#pragma region
#define TEST_SPRINTF_PERSENT(test_name, format_str) \
  START_TEST(test_name) {                           \
    char str_sp[200] = {0};                         \
    char str_s21[200] = {0};                        \
    int res_sp = sprintf(str_sp, format_str);       \
    int res_s21 = s21_sprintf(str_s21, format_str); \
    ck_assert_str_eq(str_sp, str_s21);              \
    ck_assert_int_eq(res_sp, res_s21);              \
  }                                                 \
  END_TEST

#define TEST_SPRINTF_N(test_name, format_str, type)         \
  START_TEST(test_name) {                                   \
    char str_sp[200] = {0};                                 \
    char str_s21[200] = {0};                                \
    type n_sp = 0, n_s21 = 0;                               \
    int res_sp = sprintf(str_sp, format_str, &n_sp);        \
    int res_s21 = s21_sprintf(str_s21, format_str, &n_s21); \
    ck_assert_str_eq(str_sp, str_s21);                      \
    ck_assert_int_eq(n_sp, n_s21);                          \
  }                                                         \
  END_TEST

#define TEST_SP_NULL(test_name, format_str, type)         \
  START_TEST(test_name) {                                 \
    char str_s21[200] = {0};                              \
    int res_s21 = s21_sprintf(str_s21, format_str, NULL); \
    ck_assert_str_eq(NULL, str_s21);                      \
  }                                                       \
  END_TEST

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
#pragma endregion

// ================================================================================================================================
//                                                         БЕЗ СПЕЦИФИКАТОРА
// ================================================================================================================================
// ================================================================================================================================

// =========================================================================
// Целочисленные типы NULL и 0
// =========================================================================
#pragma region
TEST_SPRINTF(d_zero, "%d", 0, int)
TEST_SPRINTF(i_zero, "%i", 0, int)
TEST_SPRINTF(hd_zero, "%hd", 0, short)
TEST_SPRINTF(hi_zero, "%hi", 0, short)
TEST_SPRINTF(hhd_zero, "%hhd", 0, signed char)
TEST_SPRINTF(hhi_zero, "%hhi", 0, signed char)
TEST_SPRINTF(ld_zero, "%ld", 0, long)
TEST_SPRINTF(li_zero, "%li", 0, long)
TEST_SPRINTF(lld_zero, "%lld", 0, long long)
TEST_SPRINTF(lli_zero, "%lli", 0, long long)
#pragma endregion

// =========================================================================
// Целочисленные типы %d %i %o %u %x %X
// =========================================================================
#pragma region
TEST_SPRINTF(d_, "%d", 123, int)
TEST_SPRINTF(d_min, "%d", INT_MIN, int)
TEST_SPRINTF(d_max, "%d", INT_MAX, int)

TEST_SPRINTF(i_, "%i", 123, int)
TEST_SPRINTF(i_min, "%i", INT_MIN, int)
TEST_SPRINTF(i_max, "%i", INT_MAX, int)

TEST_SPRINTF(o_, "%o", 123, unsigned int)
TEST_SPRINTF(o_min, "%o", 0, unsigned int)
TEST_SPRINTF(o_max, "%o", UINT_MAX, unsigned int)
TEST_SPRINTF(o_min_pl, "%o", 0 - 1, unsigned int)
TEST_SPRINTF(o_max_pl, "%o", UINT_MAX + 1, unsigned int)

TEST_SPRINTF(u_, "%u", 123, unsigned int)
TEST_SPRINTF(u_min, "%u", 0, unsigned int)
TEST_SPRINTF(u_max, "%u", UINT_MAX, unsigned int)
TEST_SPRINTF(u_min_pl, "%u", 0 - 1, unsigned int)
TEST_SPRINTF(u_max_pl, "%u", UINT_MAX + 1, unsigned int)

TEST_SPRINTF(x_, "%x", 123, unsigned int)
TEST_SPRINTF(x_min, "%x", 0, unsigned int)
TEST_SPRINTF(x_max, "%x", UINT_MAX, unsigned int)
TEST_SPRINTF(x_min_pl, "%x", 0 - 1, unsigned int)
TEST_SPRINTF(x_max_pl, "%x", UINT_MAX + 1, unsigned int)

TEST_SPRINTF(X_, "%X", 123, unsigned int)
TEST_SPRINTF(X_min, "%X", 0, unsigned int)
TEST_SPRINTF(X_max, "%X", UINT_MAX, unsigned int)
TEST_SPRINTF(X_min_pl, "%X", 0 - 1, unsigned int)
TEST_SPRINTF(X_max_pl, "%X", UINT_MAX + 1, unsigned int)
#pragma endregion

// =========================================================================
// Целочисленные типы модификатор h (short) %hd %hi %ho %hu %hx %hX
// =========================================================================
#pragma region
TEST_SPRINTF(hd_, "%hd", 123, short)
TEST_SPRINTF(hd_min, "%hd", SHRT_MIN, short)
TEST_SPRINTF(hd_max, "%hd", SHRT_MAX, short)
TEST_SPRINTF(hd_max_pl, "%hd", SHRT_MAX + 1, short)

TEST_SPRINTF(hi_, "%hi", 123, short)
TEST_SPRINTF(hi_min, "%hi", SHRT_MIN, short)
TEST_SPRINTF(hi_max, "%hi", SHRT_MAX, short)
TEST_SPRINTF(hi_max_pl, "%hi", SHRT_MAX + 1, short)

TEST_SPRINTF(ho_, "%ho", 123, unsigned short)
TEST_SPRINTF(ho_min, "%ho", 0, unsigned short)
TEST_SPRINTF(ho_max, "%ho", USHRT_MAX, unsigned short)
TEST_SPRINTF(ho_min_pl, "%ho", 0 - 1, unsigned short)

TEST_SPRINTF(hu_, "%hu", 123, unsigned short)
TEST_SPRINTF(hu_min, "%hu", 0, unsigned short)
TEST_SPRINTF(hu_max, "%hu", USHRT_MAX, unsigned short)
TEST_SPRINTF(hu_min_pl, "%hu", 0 - 1, unsigned short)

TEST_SPRINTF(hx_, "%hx", 123, unsigned short)
TEST_SPRINTF(hx_min, "%hx", 0, unsigned short)
TEST_SPRINTF(hx_max, "%hx", USHRT_MAX, unsigned short)
TEST_SPRINTF(hx_min_pl, "%hx", 0 - 1, unsigned short)

TEST_SPRINTF(hX_, "%hX", 123, unsigned short)
TEST_SPRINTF(hX_min, "%hX", 0, unsigned short)
TEST_SPRINTF(hX_max, "%hX", USHRT_MAX, unsigned short)
TEST_SPRINTF(hX_min_pl, "%hX", 0 - 1, unsigned short)
#pragma endregion

// =========================================================================
// Целочисленные типы модификатор hh (char) %hhd %hhi %hho %hhu %hhx %hhX
// =========================================================================
#pragma region
TEST_SPRINTF(hhd_, "%hhd", 123, signed char)
TEST_SPRINTF(hhd_min, "%hhd", SCHAR_MIN, signed char)
TEST_SPRINTF(hhd_max, "%hhd", SCHAR_MAX, signed char)
TEST_SPRINTF(hhd_max_pl, "%hhd", SCHAR_MAX + 1, signed char)

TEST_SPRINTF(hhi_, "%hhi", 123, signed char)
TEST_SPRINTF(hhi_min, "%hhi", SCHAR_MIN, signed char)
TEST_SPRINTF(hhi_max, "%hhi", SCHAR_MAX, signed char)
TEST_SPRINTF(hhi_max_pl, "%hhi", SCHAR_MAX + 1, signed char)

TEST_SPRINTF(hho_, "%hho", 123, unsigned char)
TEST_SPRINTF(hho_min, "%hho", 0, unsigned char)
TEST_SPRINTF(hho_max, "%hho", UCHAR_MAX, unsigned char)
TEST_SPRINTF(hho_min_pl, "%hho", 0 - 1, unsigned char)

TEST_SPRINTF(hhu_, "%hhu", 123, unsigned char)
TEST_SPRINTF(hhu_min, "%hhu", 0, unsigned char)
TEST_SPRINTF(hhu_max, "%hhu", UCHAR_MAX, unsigned char)
TEST_SPRINTF(hhu_min_pl, "%hhu", 0 - 1, unsigned char)

TEST_SPRINTF(hhx_, "%hhx", 123, unsigned char)
TEST_SPRINTF(hhx_min, "%hhx", 0, unsigned char)
TEST_SPRINTF(hhx_max, "%hhx", UCHAR_MAX, unsigned char)
TEST_SPRINTF(hhx_min_pl, "%hhx", 0 - 1, unsigned char)

TEST_SPRINTF(hhX_, "%hhX", 123, unsigned char)
TEST_SPRINTF(hhX_min, "%hhX", 0, unsigned char)
TEST_SPRINTF(hhX_max, "%hhX", UCHAR_MAX, unsigned char)
TEST_SPRINTF(hhX_min_pl, "%hhX", 0 - 1, unsigned char)
#pragma endregion

// =========================================================================
// Целочисленные типы модификатор l (long) %ld %li %lo %lu %lx %lX
// =========================================================================
#pragma region
TEST_SPRINTF(ld_, "%ld", 123, long)
TEST_SPRINTF(ld_min, "%ld", LONG_MIN, long)
TEST_SPRINTF(ld_max, "%ld", LONG_MAX, long)

TEST_SPRINTF(li_, "%li", 123, long)
TEST_SPRINTF(li_min, "%li", LONG_MIN, long)
TEST_SPRINTF(li_max, "%li", LONG_MAX, long)

TEST_SPRINTF(lo_, "%lo", 123, unsigned long)
TEST_SPRINTF(lo_min, "%lo", 0, unsigned long)
TEST_SPRINTF(lo_max, "%lo", ULONG_MAX, unsigned long)
TEST_SPRINTF(lo_min_pl, "%lo", 0 - 1, unsigned long)
TEST_SPRINTF(lo_max_pl, "%lo", ULONG_MAX + 1, unsigned long)

TEST_SPRINTF(lu_, "%lu", 123, unsigned long)
TEST_SPRINTF(lu_min, "%lu", 0, unsigned long)
TEST_SPRINTF(lu_max, "%lu", ULONG_MAX, unsigned long)
TEST_SPRINTF(lu_min_pl, "%lu", 0 - 1, unsigned long)
TEST_SPRINTF(lu_max_pl, "%lu", ULONG_MAX + 1, unsigned long)

TEST_SPRINTF(lx_, "%lx", 123, unsigned long)
TEST_SPRINTF(lx_min, "%lx", 0, unsigned long)
TEST_SPRINTF(lx_max, "%lx", ULONG_MAX, unsigned long)
TEST_SPRINTF(lx_min_pl, "%lx", 0 - 1, unsigned long)
TEST_SPRINTF(lx_max_pl, "%lx", ULONG_MAX + 1, unsigned long)

TEST_SPRINTF(lX_, "%lX", 123, unsigned long)
TEST_SPRINTF(lX_min, "%lX", 0, unsigned long)
TEST_SPRINTF(lX_max, "%lX", ULONG_MAX, unsigned long)
TEST_SPRINTF(lX_min_pl, "%lX", 0 - 1, unsigned long)
TEST_SPRINTF(lX_max_pl, "%lX", ULONG_MAX + 1, unsigned long)
#pragma endregion

// =========================================================================
// Целочисленные типы модификатор ll (long long) %lld %lli %llo %llu %llx %llX
// =========================================================================
#pragma region
TEST_SPRINTF(lld_, "%lld", 123, long long)
TEST_SPRINTF(lld_min, "%lld", LLONG_MIN, long long)
TEST_SPRINTF(lld_max, "%lld", LLONG_MAX, long long)

TEST_SPRINTF(lli_, "%lli", 123, long long)
TEST_SPRINTF(lli_min, "%lli", LLONG_MIN, long long)
TEST_SPRINTF(lli_max, "%lli", LLONG_MAX, long long)

TEST_SPRINTF(llo_, "%llo", 123, unsigned long long)
TEST_SPRINTF(llo_min, "%llo", 0, unsigned long long)
TEST_SPRINTF(llo_max, "%llo", ULLONG_MAX, unsigned long long)
TEST_SPRINTF(llo_min_pl, "%llo", 0 - 1, unsigned long long)
TEST_SPRINTF(llo_max_pl, "%llo", ULLONG_MAX + 1, unsigned long long)

TEST_SPRINTF(llu_, "%llu", 123, unsigned long long)
TEST_SPRINTF(llu_min, "%llu", 0, unsigned long long)
TEST_SPRINTF(llu_max, "%llu", ULLONG_MAX, unsigned long long)
TEST_SPRINTF(llu_min_pl, "%llu", 0 - 1, unsigned long long)
TEST_SPRINTF(llu_max_pl, "%llu", ULLONG_MAX + 1, unsigned long long)

TEST_SPRINTF(llx_, "%llx", 123, unsigned long long)
TEST_SPRINTF(llx_min, "%llx", 0, unsigned long long)
TEST_SPRINTF(llx_max, "%llx", ULLONG_MAX, unsigned long long)
TEST_SPRINTF(llx_min_pl, "%llx", 0 - 1, unsigned long long)
TEST_SPRINTF(llx_max_pl, "%llx", ULLONG_MAX + 1, unsigned long long)

TEST_SPRINTF(llX_, "%llX", 123, unsigned long long)
TEST_SPRINTF(llX_min, "%llX", 0, unsigned long long)
TEST_SPRINTF(llX_max, "%llX", ULLONG_MAX, unsigned long long)
TEST_SPRINTF(llX_min_pl, "%llX", 0 - 1, unsigned long long)
TEST_SPRINTF(llX_max_pl, "%llX", ULLONG_MAX + 1, unsigned long long)
#pragma endregion

// =========================================================================
// Вещественные типы: NaN и INFINITY
// =========================================================================
#pragma region
TEST_SPRINTF(e_nan, "%e", NAN, double)
TEST_SPRINTF(e_inf, "%e", INFINITY, double)
TEST_SPRINTF(e_ng_inf, "%e", -INFINITY, double)

TEST_SPRINTF(E_nan, "%E", NAN, double)
TEST_SPRINTF(E_inf, "%E", INFINITY, double)
TEST_SPRINTF(E_ng_inf, "%E", -INFINITY, double)

TEST_SPRINTF(f_nan, "%g", NAN, double)
TEST_SPRINTF(f_inf, "%g", INFINITY, double)
TEST_SPRINTF(f_ng_inf, "%g", -INFINITY, double)

TEST_SPRINTF(g_nan, "%g", NAN, double)
TEST_SPRINTF(g_inf, "%g", INFINITY, double)
TEST_SPRINTF(g_ng_inf, "%g", -INFINITY, double)

TEST_SPRINTF(G_nan, "%G", NAN, double)
TEST_SPRINTF(G_inf, "%G", INFINITY, double)
TEST_SPRINTF(G_ng_inf, "%G", -INFINITY, double)

TEST_SPRINTF(le_nan, "%le", NAN, double)
TEST_SPRINTF(le_inf, "%le", INFINITY, double)
TEST_SPRINTF(le_ng_inf, "%le", -INFINITY, double)

TEST_SPRINTF(lE_nan, "%lE", NAN, double)
TEST_SPRINTF(lE_inf, "%lE", INFINITY, double)
TEST_SPRINTF(lE_ng_inf, "%lE", -INFINITY, double)

TEST_SPRINTF(lf_nan, "%lg", NAN, double)
TEST_SPRINTF(lf_inf, "%lg", INFINITY, double)
TEST_SPRINTF(lf_ng_inf, "%lg", -INFINITY, double)

TEST_SPRINTF(lg_nan, "%lg", NAN, double)
TEST_SPRINTF(lg_inf, "%lg", INFINITY, double)
TEST_SPRINTF(lg_ng_inf, "%lg", -INFINITY, double)

TEST_SPRINTF(lG_nan, "%lG", NAN, double)
TEST_SPRINTF(lG_inf, "%lG", INFINITY, double)
TEST_SPRINTF(lG_ng_inf, "%lG", -INFINITY, double)

TEST_SPRINTF(Le_nan, "%Le", (long double)NAN, long double)
TEST_SPRINTF(Le_inf, "%Le", (long double)INFINITY, long double)
TEST_SPRINTF(Le_ng_inf, "%Le", -(long double)INFINITY, long double)

TEST_SPRINTF(LE_nan, "%LE", (long double)NAN, long double)
TEST_SPRINTF(LE_inf, "%LE", (long double)INFINITY, long double)
TEST_SPRINTF(LE_ng_inf, "%LE", -(long double)INFINITY, long double)

TEST_SPRINTF(Lf_nan, "%Lg", (long double)NAN, long double)
TEST_SPRINTF(Lf_inf, "%Lg", (long double)INFINITY, long double)
TEST_SPRINTF(Lf_ng_inf, "%Lg", -(long double)INFINITY, long double)

TEST_SPRINTF(Lg_nan, "%Lg", (long double)NAN, long double)
TEST_SPRINTF(Lg_inf, "%Lg", (long double)INFINITY, long double)
TEST_SPRINTF(Lg_ng_inf, "%Lg", -(long double)INFINITY, long double)

TEST_SPRINTF(LG_nan, "%LG", (long double)NAN, long double)
TEST_SPRINTF(LG_inf, "%LG", (long double)INFINITY, long double)
TEST_SPRINTF(LG_ng_inf, "%LG", -(long double)INFINITY, long double)
#pragma endregion

// =========================================================================
// Вещественные типы NULL и 0
// =========================================================================
#pragma region
TEST_SP_NULL(e_null, "%e", double)
TEST_SPRINTF(e_zero, "%e", 0.0, double)
TEST_SPRINTF(e_ng_z, "%e", -0.0, double)

TEST_SP_NULL(E_null, "%E", double)
TEST_SPRINTF(E_zero, "%E", 0.0, double)
TEST_SPRINTF(E_ng_z, "%E", -0.0, double)

TEST_SP_NULL(f_null, "%g", double)
TEST_SPRINTF(f_zero, "%g", 0.0, double)
TEST_SPRINTF(f_ng_z, "%g", -0.0, double)

TEST_SP_NULL(g_null, "%g", double)
TEST_SPRINTF(g_zero, "%g", 0.0, double)
TEST_SPRINTF(g_ng_z, "%g", -0.0, double)

TEST_SP_NULL(G_null, "%G", double)
TEST_SPRINTF(G_zero, "%G", 0.0, double)
TEST_SPRINTF(G_ng_z, "%G", -0.0, double)

TEST_SP_NULL(le_null, "%le", double)
TEST_SPRINTF(le_zero, "%le", 0.0, double)
TEST_SPRINTF(le_ng_z, "%le", -0.0, double)

TEST_SP_NULL(lE_null, "%lE", double)
TEST_SPRINTF(lE_zero, "%lE", 0.0, double)
TEST_SPRINTF(lE_ng_z, "%lE", -0.0, double)

TEST_SP_NULL(lf_null, "%lg", double)
TEST_SPRINTF(lf_zero, "%lg", 0.0, double)
TEST_SPRINTF(lf_ng_z, "%lg", -0.0, double)

TEST_SP_NULL(lg_null, "%lg", double)
TEST_SPRINTF(lg_zero, "%lg", 0.0, double)
TEST_SPRINTF(lg_ng_z, "%lg", -0.0, double)

TEST_SP_NULL(lG_null, "%lG", double)
TEST_SPRINTF(lG_zero, "%lG", 0.0, double)
TEST_SPRINTF(lG_ng_z, "%lG", -0.0, double)

TEST_SP_NULL(Le_null, "%Le", long double)
TEST_SPRINTF(Le_zero, "%Le", 0.0L, long double)
TEST_SPRINTF(Le_ng_z, "%Le", -0.0L, long double)

TEST_SP_NULL(LE_null, "%LE", long double)
TEST_SPRINTF(LE_zero, "%LE", 0.0L, long double)
TEST_SPRINTF(LE_ng_z, "%LE", -0.0L, long double)

TEST_SP_NULL(Lf_null, "%Lg", long double)
TEST_SPRINTF(Lf_zero, "%Lg", 0.0L, long double)
TEST_SPRINTF(Lf_ng_z, "%Lg", -0.0L, long double)

TEST_SP_NULL(Lg_null, "%Lg", long double)
TEST_SPRINTF(Lg_zero, "%Lg", 0.0L, long double)
TEST_SPRINTF(Lg_ng_z, "%Lg", -0.0L, long double)

TEST_SP_NULL(LG_null, "%LG", long double)
TEST_SPRINTF(LG_zero, "%LG", 0.0L, long double)
TEST_SPRINTF(LG_ng_z, "%LG", -0.0L, long double)
#pragma endregion

// =========================================================================
// Вещественные типы %f %e %E %g %G
// =========================================================================
#pragma region
TEST_SPRINTF(e_post_small, "%e", 1.2345, double)
TEST_SPRINTF(e_negt_small, "%e", -1.2345, double)
TEST_SPRINTF(e_post_medium, "%e", 123.456, double)
TEST_SPRINTF(e_negt_medium, "%e", -123.456, double)
TEST_SPRINTF(e_post_int, "%e", 123.0, double)
TEST_SPRINTF(e_negt_int, "%e", -123.0, double)
TEST_SPRINTF(e_post_vsmall, "%e", 0.0000123456, double)
TEST_SPRINTF(e_negt_vsmall, "%e", -0.0000123456, double)
TEST_SPRINTF(e_post_large, "%e", 123456789.0, double)
TEST_SPRINTF(e_negt_large, "%e", -123456789.0, double)
TEST_SPRINTF(e_post_1e6, "%e", 1000000.0, double)
TEST_SPRINTF(e_post_1em6, "%e", 0.000001, double)
TEST_SPRINTF(e_round_to_2, "%e", 1.999, double)
TEST_SPRINTF(e_round_to_10, "%e", 9.999999, double)
TEST_SPRINTF(e_max_exp, "%e", 1e308, double)
TEST_SPRINTF(e_min_exp, "%e", 1e-308, double)

TEST_SPRINTF(E_post_small, "%E", 1.2345, double)
TEST_SPRINTF(E_negt_small, "%E", -1.2345, double)
TEST_SPRINTF(E_post_medium, "%E", 123.456, double)
TEST_SPRINTF(E_negt_medium, "%E", -123.456, double)
TEST_SPRINTF(E_post_int, "%E", 123.0, double)
TEST_SPRINTF(E_negt_int, "%E", -123.0, double)
TEST_SPRINTF(E_post_vsmall, "%E", 0.0000123456, double)
TEST_SPRINTF(E_negt_vsmall, "%E", -0.0000123456, double)
TEST_SPRINTF(E_post_large, "%E", 123456789.0, double)
TEST_SPRINTF(E_negt_large, "%E", -123456789.0, double)
TEST_SPRINTF(E_post_1e6, "%E", 1000000.0, double)
TEST_SPRINTF(E_post_1em6, "%E", 0.000001, double)
TEST_SPRINTF(E_round_to_2, "%E", 1.999, double)
TEST_SPRINTF(E_round_to_10, "%E", 9.999999, double)
TEST_SPRINTF(E_max_exp, "%E", 1e308, double)
TEST_SPRINTF(E_min_exp, "%E", 1e-308, double)

TEST_SPRINTF(f_post_small, "%g", 1.2345, double)
TEST_SPRINTF(f_negt_small, "%g", -1.2345, double)
TEST_SPRINTF(f_post_medium, "%g", 123.456, double)
TEST_SPRINTF(f_negt_medium, "%g", -123.456, double)
TEST_SPRINTF(f_post_int, "%g", 123.0, double)
TEST_SPRINTF(f_negt_int, "%g", -123.0, double)
TEST_SPRINTF(f_post_vsmall, "%g", 0.0000123456, double)
TEST_SPRINTF(f_negt_vsmall, "%g", -0.0000123456, double)
TEST_SPRINTF(f_post_large, "%g", 123456789.0, double)
TEST_SPRINTF(f_negt_large, "%g", -123456789.0, double)
TEST_SPRINTF(f_post_1e6, "%g", 1000000.0, double)
TEST_SPRINTF(f_post_1em6, "%g", 0.000001, double)
TEST_SPRINTF(f_round_to_2, "%g", 1.999, double)
TEST_SPRINTF(f_round_to_10, "%g", 9.999999, double)
TEST_SPRINTF(f_max_exp, "%g", 1e308, double)
TEST_SPRINTF(f_min_exp, "%g", 1e-308, double)

TEST_SPRINTF(g_post_small, "%g", 1.2345, double)
TEST_SPRINTF(g_negt_small, "%g", -1.2345, double)
TEST_SPRINTF(g_post_medium, "%g", 123.456, double)
TEST_SPRINTF(g_negt_medium, "%g", -123.456, double)
TEST_SPRINTF(g_post_int, "%g", 123.0, double)
TEST_SPRINTF(g_negt_int, "%g", -123.0, double)
TEST_SPRINTF(g_post_vsmall, "%g", 0.0000123456, double)
TEST_SPRINTF(g_negt_vsmall, "%g", -0.0000123456, double)
TEST_SPRINTF(g_post_large, "%g", 123456789.0, double)
TEST_SPRINTF(g_negt_large, "%g", -123456789.0, double)
TEST_SPRINTF(g_post_1e6, "%g", 1000000.0, double)
TEST_SPRINTF(g_post_1em6, "%g", 0.000001, double)
TEST_SPRINTF(g_round_to_2, "%g", 1.999, double)
TEST_SPRINTF(g_round_to_10, "%g", 9.999999, double)
TEST_SPRINTF(g_max_exp, "%g", 1e308, double)
TEST_SPRINTF(g_min_exp, "%g", 1e-308, double)

TEST_SPRINTF(G_post_small, "%G", 1.2345, double)
TEST_SPRINTF(G_negt_small, "%G", -1.2345, double)
TEST_SPRINTF(G_post_medium, "%G", 123.456, double)
TEST_SPRINTF(G_negt_medium, "%G", -123.456, double)
TEST_SPRINTF(G_post_int, "%G", 123.0, double)
TEST_SPRINTF(G_negt_int, "%G", -123.0, double)
TEST_SPRINTF(G_post_vsmall, "%G", 0.0000123456, double)
TEST_SPRINTF(G_negt_vsmall, "%G", -0.0000123456, double)
TEST_SPRINTF(G_post_large, "%G", 123456789.0, double)
TEST_SPRINTF(G_negt_large, "%G", -123456789.0, double)
TEST_SPRINTF(G_post_1e6, "%G", 1000000.0, double)
TEST_SPRINTF(G_post_1em6, "%G", 0.000001, double)
TEST_SPRINTF(G_round_to_2, "%G", 1.999, double)
TEST_SPRINTF(G_round_to_10, "%G", 9.999999, double)
TEST_SPRINTF(G_max_exp, "%G", 1e308, double)
TEST_SPRINTF(G_min_exp, "%G", 1e-308, double)
#pragma endregion

// =========================================================================
// Вещественные типы модификатор l (long) %lf %le %lE %lg %lG
// =========================================================================
#pragma region
TEST_SPRINTF(le_post_small, "%le", 1.2345, double)
TEST_SPRINTF(le_negt_small, "%le", -1.2345, double)
TEST_SPRINTF(le_post_medium, "%le", 123.456, double)
TEST_SPRINTF(le_negt_medium, "%le", -123.456, double)
TEST_SPRINTF(le_post_int, "%le", 123.0, double)
TEST_SPRINTF(le_negt_int, "%le", -123.0, double)
TEST_SPRINTF(le_post_vsmall, "%le", 0.0000123456, double)
TEST_SPRINTF(le_negt_vsmall, "%le", -0.0000123456, double)
TEST_SPRINTF(le_post_large, "%le", 123456789.0, double)
TEST_SPRINTF(le_negt_large, "%le", -123456789.0, double)
TEST_SPRINTF(le_post_1e6, "%le", 1000000.0, double)
TEST_SPRINTF(le_post_1em6, "%le", 0.000001, double)
TEST_SPRINTF(le_round_to_2, "%le", 1.999, double)
TEST_SPRINTF(le_round_to_10, "%le", 9.999999, double)
TEST_SPRINTF(le_max_exp, "%le", 1e308, double)
TEST_SPRINTF(le_min_exp, "%le", 1e-308, double)

TEST_SPRINTF(lE_post_small, "%lE", 1.2345, double)
TEST_SPRINTF(lE_negt_small, "%lE", -1.2345, double)
TEST_SPRINTF(lE_post_medium, "%lE", 123.456, double)
TEST_SPRINTF(lE_negt_medium, "%lE", -123.456, double)
TEST_SPRINTF(lE_post_int, "%lE", 123.0, double)
TEST_SPRINTF(lE_negt_int, "%lE", -123.0, double)
TEST_SPRINTF(lE_post_vsmall, "%lE", 0.0000123456, double)
TEST_SPRINTF(lE_negt_vsmall, "%lE", -0.0000123456, double)
TEST_SPRINTF(lE_post_large, "%lE", 123456789.0, double)
TEST_SPRINTF(lE_negt_large, "%lE", -123456789.0, double)
TEST_SPRINTF(lE_post_1e6, "%lE", 1000000.0, double)
TEST_SPRINTF(lE_post_1em6, "%lE", 0.000001, double)
TEST_SPRINTF(lE_round_to_2, "%lE", 1.999, double)
TEST_SPRINTF(lE_round_to_10, "%lE", 9.999999, double)
TEST_SPRINTF(lE_max_exp, "%lE", 1e308, double)
TEST_SPRINTF(lE_min_exp, "%lE", 1e-308, double)

TEST_SPRINTF(lf_post_small, "%lg", 1.2345, double)
TEST_SPRINTF(lf_negt_small, "%lg", -1.2345, double)
TEST_SPRINTF(lf_post_medium, "%lg", 123.456, double)
TEST_SPRINTF(lf_negt_medium, "%lg", -123.456, double)
TEST_SPRINTF(lf_post_int, "%lg", 123.0, double)
TEST_SPRINTF(lf_negt_int, "%lg", -123.0, double)
TEST_SPRINTF(lf_post_vsmall, "%lg", 0.0000123456, double)
TEST_SPRINTF(lf_negt_vsmall, "%lg", -0.0000123456, double)
TEST_SPRINTF(lf_post_large, "%lg", 123456789.0, double)
TEST_SPRINTF(lf_negt_large, "%lg", -123456789.0, double)
TEST_SPRINTF(lf_post_1e6, "%lg", 1000000.0, double)
TEST_SPRINTF(lf_post_1em6, "%lg", 0.000001, double)
TEST_SPRINTF(lf_round_to_2, "%lg", 1.999, double)
TEST_SPRINTF(lf_round_to_10, "%lg", 9.999999, double)
TEST_SPRINTF(lf_max_exp, "%lg", 1e308, double)
TEST_SPRINTF(lf_min_exp, "%lg", 1e-308, double)

TEST_SPRINTF(lg_post_small, "%lg", 1.2345, double)
TEST_SPRINTF(lg_negt_small, "%lg", -1.2345, double)
TEST_SPRINTF(lg_post_medium, "%lg", 123.456, double)
TEST_SPRINTF(lg_negt_medium, "%lg", -123.456, double)
TEST_SPRINTF(lg_post_int, "%lg", 123.0, double)
TEST_SPRINTF(lg_negt_int, "%lg", -123.0, double)
TEST_SPRINTF(lg_post_vsmall, "%lg", 0.0000123456, double)
TEST_SPRINTF(lg_negt_vsmall, "%lg", -0.0000123456, double)
TEST_SPRINTF(lg_post_large, "%lg", 123456789.0, double)
TEST_SPRINTF(lg_negt_large, "%lg", -123456789.0, double)
TEST_SPRINTF(lg_post_1e6, "%lg", 1000000.0, double)
TEST_SPRINTF(lg_post_1em6, "%lg", 0.000001, double)
TEST_SPRINTF(lg_round_to_2, "%lg", 1.999, double)
TEST_SPRINTF(lg_round_to_10, "%lg", 9.999999, double)
TEST_SPRINTF(lg_max_exp, "%lg", 1e308, double)
TEST_SPRINTF(lg_min_exp, "%lg", 1e-308, double)

TEST_SPRINTF(lG_post_small, "%lG", 1.2345, double)
TEST_SPRINTF(lG_negt_small, "%lG", -1.2345, double)
TEST_SPRINTF(lG_post_medium, "%lG", 123.456, double)
TEST_SPRINTF(lG_negt_medium, "%lG", -123.456, double)
TEST_SPRINTF(lG_post_int, "%lG", 123.0, double)
TEST_SPRINTF(lG_negt_int, "%lG", -123.0, double)
TEST_SPRINTF(lG_post_vsmall, "%lG", 0.0000123456, double)
TEST_SPRINTF(lG_negt_vsmall, "%lG", -0.0000123456, double)
TEST_SPRINTF(lG_post_large, "%lG", 123456789.0, double)
TEST_SPRINTF(lG_negt_large, "%lG", -123456789.0, double)
TEST_SPRINTF(lG_post_1e6, "%lG", 1000000.0, double)
TEST_SPRINTF(lG_post_1em6, "%lG", 0.000001, double)
TEST_SPRINTF(lG_round_to_2, "%lG", 1.999, double)
TEST_SPRINTF(lG_round_to_10, "%lG", 9.999999, double)
TEST_SPRINTF(lG_max_exp, "%lG", 1e308, double)
TEST_SPRINTF(lG_min_exp, "%lG", 1e-308, double)
#pragma endregion

// =========================================================================
// Вещественные типы модификатор L (long long) %lf %Le %LE %Lg %LG
// =========================================================================
#pragma region
TEST_SPRINTF(Le_post_small, "%Le", 1.2345L, long double)
TEST_SPRINTF(Le_negt_small, "%Le", -1.2345L, long double)
TEST_SPRINTF(Le_post_medium, "%Le", 123.456L, long double)
TEST_SPRINTF(Le_negt_medium, "%Le", -123.456L, long double)
TEST_SPRINTF(Le_post_int, "%Le", 123.0L, long double)
TEST_SPRINTF(Le_negt_int, "%Le", -123.0L, long double)
TEST_SPRINTF(Le_post_vsmall, "%Le", 0.0000123456L, long double)
TEST_SPRINTF(Le_negt_vsmall, "%Le", -0.0000123456L, long double)
TEST_SPRINTF(Le_post_large, "%Le", 123456789.0L, long double)
TEST_SPRINTF(Le_negt_large, "%Le", -123456789.0L, long double)
TEST_SPRINTF(Le_post_1e6L, "%Le", 1000000.0L, long double)
TEST_SPRINTF(Le_post_1em6L, "%Le", 0.000001L, long double)
TEST_SPRINTF(Le_round_to_2L, "%Le", 1.999L, long double)
TEST_SPRINTF(Le_round_to_10L, "%Le", 9.999999L, long double)
TEST_SPRINTF(Le_max_exp, "%Le", 1e308L, long double)
TEST_SPRINTF(Le_min_exp, "%Le", 1e-308L, long double)

TEST_SPRINTF(LE_post_small, "%LE", 1.2345L, long double)
TEST_SPRINTF(LE_negt_small, "%LE", -1.2345L, long double)
TEST_SPRINTF(LE_post_medium, "%LE", 123.456L, long double)
TEST_SPRINTF(LE_negt_medium, "%LE", -123.456L, long double)
TEST_SPRINTF(LE_post_int, "%LE", 123.0L, long double)
TEST_SPRINTF(LE_negt_int, "%LE", -123.0L, long double)
TEST_SPRINTF(LE_post_vsmall, "%LE", 0.0000123456L, long double)
TEST_SPRINTF(LE_negt_vsmall, "%LE", -0.0000123456L, long double)
TEST_SPRINTF(LE_post_large, "%LE", 123456789.0L, long double)
TEST_SPRINTF(LE_negt_large, "%LE", -123456789.0L, long double)
TEST_SPRINTF(LE_post_1e6L, "%LE", 1000000.0L, long double)
TEST_SPRINTF(LE_post_1em6L, "%LE", 0.000001L, long double)
TEST_SPRINTF(LE_round_to_2L, "%LE", 1.999L, long double)
TEST_SPRINTF(LE_round_to_10L, "%LE", 9.999999L, long double)
TEST_SPRINTF(LE_max_exp, "%LE", 1e308L, long double)
TEST_SPRINTF(LE_min_exp, "%LE", 1e-308L, long double)

TEST_SPRINTF(Lf_post_small, "%Lg", 1.2345L, long double)
TEST_SPRINTF(Lf_negt_small, "%Lg", -1.2345L, long double)
TEST_SPRINTF(Lf_post_medium, "%Lg", 123.456L, long double)
TEST_SPRINTF(Lf_negt_medium, "%Lg", -123.456L, long double)
TEST_SPRINTF(Lf_post_int, "%Lg", 123.0L, long double)
TEST_SPRINTF(Lf_negt_int, "%Lg", -123.0L, long double)
TEST_SPRINTF(Lf_post_vsmall, "%Lg", 0.0000123456L, long double)
TEST_SPRINTF(Lf_negt_vsmall, "%Lg", -0.0000123456L, long double)
TEST_SPRINTF(Lf_post_large, "%Lg", 123456789.0L, long double)
TEST_SPRINTF(Lf_negt_large, "%Lg", -123456789.0L, long double)
TEST_SPRINTF(Lf_post_1e6L, "%Lg", 1000000.0L, long double)
TEST_SPRINTF(Lf_post_1em6L, "%Lg", 0.000001L, long double)
TEST_SPRINTF(Lf_round_to_2L, "%Lg", 1.999L, long double)
TEST_SPRINTF(Lf_round_to_10L, "%Lg", 9.999999L, long double)
TEST_SPRINTF(Lf_max_exp, "%Lg", 1e308L, long double)
TEST_SPRINTF(Lf_min_exp, "%Lg", 1e-308L, long double)

TEST_SPRINTF(Lg_post_small, "%Lg", 1.2345L, long double)
TEST_SPRINTF(Lg_negt_small, "%Lg", -1.2345L, long double)
TEST_SPRINTF(Lg_post_medium, "%Lg", 123.456L, long double)
TEST_SPRINTF(Lg_negt_medium, "%Lg", -123.456L, long double)
TEST_SPRINTF(Lg_post_int, "%Lg", 123.0L, long double)
TEST_SPRINTF(Lg_negt_int, "%Lg", -123.0L, long double)
TEST_SPRINTF(Lg_post_vsmall, "%Lg", 0.0000123456L, long double)
TEST_SPRINTF(Lg_negt_vsmall, "%Lg", -0.0000123456L, long double)
TEST_SPRINTF(Lg_post_large, "%Lg", 123456789.0L, long double)
TEST_SPRINTF(Lg_negt_large, "%Lg", -123456789.0L, long double)
TEST_SPRINTF(Lg_post_1e6L, "%Lg", 1000000.0L, long double)
TEST_SPRINTF(Lg_post_1em6L, "%Lg", 0.000001L, long double)
TEST_SPRINTF(Lg_round_to_2L, "%Lg", 1.999L, long double)
TEST_SPRINTF(Lg_round_to_10L, "%Lg", 9.999999L, long double)
TEST_SPRINTF(Lg_max_exp, "%Lg", 1e308L, long double)
TEST_SPRINTF(Lg_min_exp, "%Lg", 1e-308L, long double)

TEST_SPRINTF(LG_post_small, "%LG", 1.2345L, long double)
TEST_SPRINTF(LG_negt_small, "%LG", -1.2345L, long double)
TEST_SPRINTF(LG_post_medium, "%LG", 123.456L, long double)
TEST_SPRINTF(LG_negt_medium, "%LG", -123.456L, long double)
TEST_SPRINTF(LG_post_int, "%LG", 123.0L, long double)
TEST_SPRINTF(LG_negt_int, "%LG", -123.0L, long double)
TEST_SPRINTF(LG_post_vsmall, "%LG", 0.0000123456L, long double)
TEST_SPRINTF(LG_negt_vsmall, "%LG", -0.0000123456L, long double)
TEST_SPRINTF(LG_post_large, "%LG", 123456789.0L, long double)
TEST_SPRINTF(LG_negt_large, "%LG", -123456789.0L, long double)
TEST_SPRINTF(LG_post_1e6L, "%LG", 1000000.0L, long double)
TEST_SPRINTF(LG_post_1em6L, "%LG", 0.000001L, long double)
TEST_SPRINTF(LG_round_to_2L, "%LG", 1.999L, long double)
TEST_SPRINTF(LG_round_to_10L, "%LG", 9.999999L, long double)
TEST_SPRINTF(LG_max_exp, "%LG", 1e308L, long double)
TEST_SPRINTF(LG_min_exp, "%LG", 1e-308L, long double)
#pragma endregion

// ================================================================
// Тесты для строковых спецификаторов %s %c
// ================================================================
#pragma region
TEST_SPRINTF(c_, "Char: %c", 'A', char)
TEST_SPRINTF(c_min, "Char: %c", -128, char)
TEST_SPRINTF(c_max, "Char: %c", 127, char)
TEST_SPRINTF(c_nonprint, "Char: %c", '\x01', char)
TEST_SPRINTF(c_zero, "Char: %c", 0, char)
TEST_SPRINTF(c_newline, "Char: %c", '\n', char)
TEST_SPRINTF(c_tab, "Char: %c", '\t', char)
TEST_SPRINTF(c_null_char, "Char: %c", '\0', char)
TEST_SPRINTF(c_expression, "Char: %c", 'A' + 1, int)

START_TEST(c_middle_of_string) {
  char str1[200];
  char str2[200];
  int res1 = sprintf(str1, "A%cC", 'B');
  int res2 = s21_sprintf(str2, "A%cC", 'B');
  ck_assert_str_eq(str1, str2);
  ck_assert_int_eq(res1, res2);
}
END_TEST

// ================================================================

TEST_SPRINTF(s_, "String: %s", "Hello, world!", char *)
TEST_SPRINTF(s_null, "String: %s", NULL, char *)
TEST_SPRINTF(s_null_middle, "String: %s", "Hello,\0 world!", char *)
TEST_SPRINTF(s_special, "String: %s", "Hello\tWorld\n", char *)
TEST_SPRINTF(s_special_chars, "String: %s", "Line1\nLine2\tTab\x01", char *)
TEST_SPRINTF(s_unicode, "String: %s", "Привет мир!", char *)
TEST_SPRINTF(s_empty, "String: %s", "", char *)
TEST_SPRINTF(s_escaped, "String: %s", "Quote: \"", char *)
TEST_SPRINTF(s_utf8, "String: %s", "✓ Á à €", char *)
TEST_SPRINTF(s_single_char, "String: %s", "X", char *)
TEST_SPRINTF(s_russian_utf8, "String: %s", "Русский текст", char *)
TEST_SPRINTF(s_chinese, "String: %s", "汉字", char *)
TEST_SPRINTF(s_arabic, "String: %s", "العربية", char *)

START_TEST(s_max_length) {
  char long_str[4096];
  memset(long_str, 'A', 4095);
  long_str[4095] = '\0';

  char str1[5000];
  char str2[5000];
  int res1 = sprintf(str1, "%s", long_str);
  int res2 = s21_sprintf(str2, "%s", long_str);
  ck_assert_str_eq(str1, str2);
  ck_assert_int_eq(res1, res2);
}
END_TEST

START_TEST(s_expression) {
  char str1[200];
  char str2[200];
  const char *parts[] = {"Hello", " ", "World"};
  int res1 = sprintf(str1, "Str: %s", parts[0]);
  int res2 = s21_sprintf(str2, "Str: %s", parts[0]);
  ck_assert_str_eq(str1, str2);
  ck_assert_int_eq(res1, res2);
}
END_TEST
#pragma endregion

// ================================================================
// Тесты для указателя %p
// ================================================================
#pragma region
TEST_SPRINTF(p, "Pointer: %p", (void *)0x1234abcd, void *)
TEST_SPRINTF(p_int, "Pointer: %p", (int *)0x1234abcd, int *)
TEST_SPRINTF(p_unsigned_int, "Pointer: %p", (unsigned int *)0x1234abcd,
             unsigned int *)
TEST_SPRINTF(p_double, "Pointer: %p", (double *)0x1234abcd, double *)

TEST_SPRINTF(p_min, "Min: %p", (void *)0x1, void *)
TEST_SPRINTF(p_max64, "Max64: %p", (void *)(uintptr_t)-1, void *)
TEST_SPRINTF(p_null, "Pointer: %p", NULL, void *)

START_TEST(p_string_pointer) {
  char str1[200];
  char str2[200];
  char *ptr = "test";
  int res1 = sprintf(str1, "Str ptr: %p", ptr);
  int res2 = s21_sprintf(str2, "Str ptr: %p", ptr);
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

START_TEST(p_pointer_to_pointer) {
  char str1[200];
  char str2[200];
  int value = 42;
  int *ptr = &value;
  int res1 = sprintf(str1, "Ptr to ptr: %p", (void **)&ptr);
  int res2 = s21_sprintf(str2, "Ptr to ptr: %p", (void **)&ptr);
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
#pragma endregion

// ================================================================
// Тесты для особых типов %% %n
// ================================================================
#pragma region
TEST_SPRINTF_PERSENT(single_percent, "%%")
TEST_SPRINTF_PERSENT(double_percent, "100%% complete: %% %%%%")
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

START_TEST(percent_with_string) {
  char str1[200];
  char str2[200];
  int res1 = sprintf(str1, "String: %s %%", "test");
  int res2 = s21_sprintf(str2, "String: %s %%", "test");
  ck_assert_str_eq(str1, str2);
  ck_assert_int_eq(res1, res2);
}
END_TEST

// ================================================================

TEST_SPRINTF_N(n_, "Text%n", int)
TEST_SPRINTF_N(hn_, "Text%hn", short)
TEST_SPRINTF_N(hhn_, "Text%hhn", signed char)
TEST_SPRINTF_N(ln_, "Text%ln", long)
TEST_SPRINTF_N(lln_, "Text%lln", long long)

START_TEST(n_beginning) {
  char str1[200] = {0};
  char str2[200] = {0};
  int n1 = -1, n2 = -1;
  sprintf(str1, "%nText", &n1);
  s21_sprintf(str2, "%nText", &n2);
  ck_assert_str_eq(str1, str2);
  ck_assert_int_eq(n1, n2);
  ck_assert_int_eq(n1, 0);
}
END_TEST

START_TEST(n_middle) {
  char str1[200] = {0};
  char str2[200] = {0};
  int n1 = -1, n2 = -1;
  sprintf(str1, "Test%d%n", 123, &n1);
  s21_sprintf(str2, "Test%d%n", 123, &n2);
  ck_assert_str_eq(str1, str2);
  ck_assert_int_eq(n1, n2);
}
END_TEST

START_TEST(n_multiple) {
  char str1[200] = {0};
  char str2[200] = {0};
  int n1a = -1, n1b = -1, n2a = -1, n2b = -1;
  sprintf(str1, "A%nB%nC", &n1a, &n1b);
  s21_sprintf(str2, "A%nB%nC", &n2a, &n2b);
  ck_assert_str_eq(str1, str2);
  ck_assert_int_eq(n1a, n2a);
  ck_assert_int_eq(n1b, n2b);
  ck_assert_int_eq(n1a, 1);
  ck_assert_int_eq(n1b, 2);
}
END_TEST
#pragma endregion

// ================================================================================================================================
//                                                         С СПЕЦИФИКАТОРОМ
// ================================================================================================================================
// ================================================================================================================================

// =========================================================================
// Целочисленные типы NULL и 0
// =========================================================================
#pragma region
TEST_SPRINTF(d_mins_zero, "%-d", 0, int)
TEST_SPRINTF(d_plus_zero, "%+d", 0, int)
TEST_SPRINTF(d_spac_zero, "% d", 0, int)
TEST_SPRINTF(d_fzer_zero, "%0d", 0, int)

TEST_SPRINTF(d_width_zero, "%5d", 0, int)
TEST_SPRINTF(d_zrpc_zero, "%.0d", 0, int)
TEST_SPRINTF(d_prec_zero, "%.5d", 0, int)
TEST_SPRINTF(d_width_prec_zero, "%10.5d", 0, int)

TEST_SPRINTF(d_width_mins_zero, "%-5d", 0, int)
TEST_SPRINTF(d_width_plus_zero, "%+5d", 0, int)
TEST_SPRINTF(d_width_spac_zero, "% 5d", 0, int)
TEST_SPRINTF(d_width_fzer_zero, "%05d", 0, int)

TEST_SPRINTF(d_zrwth_plus_zero, "%+0d", 0, int)
TEST_SPRINTF(d_zrwth_spac_zero, "% 0d", 0, int)

TEST_SPRINTF(d_prec_mins_zero, "%-.5d", 0, int)
TEST_SPRINTF(d_prec_plus_zero, "%+.5d", 0, int)
TEST_SPRINTF(d_prec_spac_zero, "% .5d", 0, int)

TEST_SPRINTF(d_zrpc_mins_zero, "%-.0d", 0, int)
TEST_SPRINTF(d_zrpc_plus_zero, "%+.0d", 0, int)
TEST_SPRINTF(d_zrpc_spac_zero, "% .0d", 0, int)

TEST_SPRINTF(d_width_prec_mins_zero, "%-10.5d", 0, int)
TEST_SPRINTF(d_width_prec_plus_zero, "%+10.5d", 0, int)
TEST_SPRINTF(d_width_prec_spac_zero, "% 10.5d", 0, int)

TEST_SPRINTF_2(d_dynamic_width_zero, "%*d", 10, 0, int)
TEST_SPRINTF_2(d_dynamic_prec_zero, "%.*d", 5, 0, int)
TEST_SPRINTF_3(d_dynamic_width_prec_zero, "%*.*d", 10, 5, 0, int)

// =========================================================================

TEST_SPRINTF(i_mins_zero, "%-i", 0, int)
TEST_SPRINTF(i_plus_zero, "%+i", 0, int)
TEST_SPRINTF(i_spac_zero, "% i", 0, int)
TEST_SPRINTF(i_fzer_zero, "%0i", 0, int)

TEST_SPRINTF(i_width_zero, "%5i", 0, int)
TEST_SPRINTF(i_zrpc_zero, "%.0i", 0, int)
TEST_SPRINTF(i_prec_zero, "%.5i", 0, int)
TEST_SPRINTF(i_width_prec_zero, "%10.5i", 0, int)

TEST_SPRINTF(i_width_mins_zero, "%-5i", 0, int)
TEST_SPRINTF(i_width_plus_zero, "%+5i", 0, int)
TEST_SPRINTF(i_width_spac_zero, "% 5i", 0, int)
TEST_SPRINTF(i_width_fzer_zero, "%05i", 0, int)

TEST_SPRINTF(i_zrwth_plus_zero, "%+0i", 0, int)
TEST_SPRINTF(i_zrwth_spac_zero, "% 0i", 0, int)

TEST_SPRINTF(i_prec_mins_zero, "%-.5i", 0, int)
TEST_SPRINTF(i_prec_plus_zero, "%+.5i", 0, int)
TEST_SPRINTF(i_prec_spac_zero, "% .5i", 0, int)

TEST_SPRINTF(i_zrpc_mins_zero, "%-.0i", 0, int)
TEST_SPRINTF(i_zrpc_plus_zero, "%+.0i", 0, int)
TEST_SPRINTF(i_zrpc_spac_zero, "% .0i", 0, int)

TEST_SPRINTF(i_width_prec_mins_zero, "%-10.5i", 0, int)
TEST_SPRINTF(i_width_prec_plus_zero, "%+10.5i", 0, int)
TEST_SPRINTF(i_width_prec_spac_zero, "% 10.5i", 0, int)

TEST_SPRINTF_2(i_dynamic_width_zero, "%*i", 10, 0, int)
TEST_SPRINTF_2(i_dynamic_prec_zero, "%.*i", 5, 0, int)
TEST_SPRINTF_3(i_dynamic_width_prec_zero, "%*.*i", 10, 5, 0, int)

// =========================================================================

TEST_SPRINTF(o_mins_zero, "%-o", 0, int)
TEST_SPRINTF(o_hash_zero, "%#o", 0, int)
TEST_SPRINTF(o_fzer_zero, "%0o", 0, int)

TEST_SPRINTF(o_width_zero, "%5o", 0, int)
TEST_SPRINTF(o_zrpc_zero, "%.0o", 0, int)
TEST_SPRINTF(o_prec_zero, "%.5o", 0, int)
TEST_SPRINTF(o_width_prec_zero, "%10.5o", 0, int)

TEST_SPRINTF(o_width_mins_zero, "%-5o", 0, int)
TEST_SPRINTF(o_width_hash_zero, "%#5o", 0, int)
TEST_SPRINTF(o_width_fzer_zero, "%05o", 0, int)

TEST_SPRINTF(o_zrwth_hash_zero, "%#0o", 0, int)

TEST_SPRINTF(o_prec_mins_zero, "%-.5o", 0, int)
TEST_SPRINTF(o_prec_hash_zero, "%#.5o", 0, int)

TEST_SPRINTF(o_zrpc_mins_zero, "%-.0o", 0, int)
TEST_SPRINTF(o_zrpc_hash_zero, "%#.0o", 0, int)

TEST_SPRINTF(o_width_prec_mins_zero, "%-10.5o", 0, int)
TEST_SPRINTF(o_width_prec_hash_zero, "%#10.5o", 0, int)

TEST_SPRINTF_2(o_dynamic_width_zero, "%*o", 10, 0, int)
TEST_SPRINTF_2(o_dynamic_prec_zero, "%.*o", 5, 0, int)
TEST_SPRINTF_3(o_dynamic_width_prec_zero, "%*.*o", 10, 5, 0, int)

// =========================================================================

TEST_SPRINTF(u_mins_zero, "%-u", 0, int)
TEST_SPRINTF(u_fzer_zero, "%0u", 0, int)

TEST_SPRINTF(u_width_zero, "%5u", 0, int)
TEST_SPRINTF(u_zrpc_zero, "%.0u", 0, int)
TEST_SPRINTF(u_prec_zero, "%.5u", 0, int)
TEST_SPRINTF(u_width_prec_zero, "%10.5u", 0, int)

TEST_SPRINTF(u_width_mins_zero, "%-5u", 0, int)
TEST_SPRINTF(u_width_fzer_zero, "%05u", 0, int)

TEST_SPRINTF(u_prec_mins_zero, "%-.5u", 0, int)

TEST_SPRINTF(u_zrpc_mins_zero, "%-.0u", 0, int)

TEST_SPRINTF(u_width_prec_mins_zero, "%-10.5u", 0, int)

TEST_SPRINTF_2(u_dynamic_width_zero, "%*u", 10, 0, int)
TEST_SPRINTF_2(u_dynamic_prec_zero, "%.*u", 5, 0, int)
TEST_SPRINTF_3(u_dynamic_width_prec_zero, "%*.*u", 10, 5, 0, int)

// =========================================================================

TEST_SPRINTF(x_mins_zero, "%-x", 0, int)
TEST_SPRINTF(x_hash_zero, "%#x", 0, int)
TEST_SPRINTF(x_fzer_zero, "%0x", 0, int)

TEST_SPRINTF(x_width_zero, "%5x", 0, int)
TEST_SPRINTF(x_zrpc_zero, "%.0x", 0, int)
TEST_SPRINTF(x_prec_zero, "%.5x", 0, int)
TEST_SPRINTF(x_width_prec_zero, "%10.5x", 0, int)

TEST_SPRINTF(x_width_mins_zero, "%-5x", 0, int)
TEST_SPRINTF(x_width_hash_zero, "%#5x", 0, int)
TEST_SPRINTF(x_width_fzer_zero, "%05x", 0, int)

TEST_SPRINTF(x_zrwth_hash_zero, "%#0x", 0, int)

TEST_SPRINTF(x_prec_mins_zero, "%-.5x", 0, int)
TEST_SPRINTF(x_prec_hash_zero, "%#.5x", 0, int)

TEST_SPRINTF(x_zrpc_mins_zero, "%-.0x", 0, int)
TEST_SPRINTF(x_zrpc_hash_zero, "%#.0x", 0, int)

TEST_SPRINTF(x_width_prec_mins_zero, "%-10.5x", 0, int)
TEST_SPRINTF(x_width_prec_hash_zero, "%#10.5x", 0, int)

TEST_SPRINTF_2(x_dynamic_width_zero, "%*x", 10, 0, int)
TEST_SPRINTF_2(x_dynamic_prec_zero, "%.*x", 5, 0, int)
TEST_SPRINTF_3(x_dynamic_width_prec_zero, "%*.*x", 10, 5, 0, int)

// =========================================================================

TEST_SPRINTF(X_mins_zero, "%-X", 0, int)
TEST_SPRINTF(X_hash_zero, "%#X", 0, int)
TEST_SPRINTF(X_fzer_zero, "%0X", 0, int)

TEST_SPRINTF(X_width_zero, "%5X", 0, int)
TEST_SPRINTF(X_zrpc_zero, "%.0X", 0, int)
TEST_SPRINTF(X_prec_zero, "%.5X", 0, int)
TEST_SPRINTF(X_width_prec_zero, "%10.5X", 0, int)

TEST_SPRINTF(X_width_mins_zero, "%-5X", 0, int)
TEST_SPRINTF(X_width_hash_zero, "%#5X", 0, int)
TEST_SPRINTF(X_width_fzer_zero, "%05X", 0, int)

TEST_SPRINTF(X_zrwth_hash_zero, "%#0X", 0, int)

TEST_SPRINTF(X_prec_mins_zero, "%-.5X", 0, int)
TEST_SPRINTF(X_prec_hash_zero, "%#.5X", 0, int)

TEST_SPRINTF(X_zrpc_mins_zero, "%-.0X", 0, int)
TEST_SPRINTF(X_zrpc_hash_zero, "%#.0X", 0, int)

TEST_SPRINTF(X_width_prec_mins_zero, "%-10.5X", 0, int)
TEST_SPRINTF(X_width_prec_hash_zero, "%#10.5X", 0, int)

TEST_SPRINTF_2(X_dynamic_width_zero, "%*X", 10, 0, int)
TEST_SPRINTF_2(X_dynamic_prec_zero, "%.*X", 5, 0, int)
TEST_SPRINTF_3(X_dynamic_width_prec_zero, "%*.*X", 10, 5, 0, int)

// =========================================================================

TEST_SPRINTF(hd_mins_zero, "%-hd", 0, short)
TEST_SPRINTF(hd_plus_zero, "%+hd", 0, short)
TEST_SPRINTF(hd_spac_zero, "% hd", 0, short)
TEST_SPRINTF(hd_fzer_zero, "%0hd", 0, short)

TEST_SPRINTF(hd_width_zero, "%5hd", 0, short)
TEST_SPRINTF(hd_zrpc_zero, "%.0hd", 0, short)
TEST_SPRINTF(hd_prec_zero, "%.5hd", 0, short)
TEST_SPRINTF(hd_width_prec_zero, "%10.5hd", 0, short)

TEST_SPRINTF(hd_width_mins_zero, "%-5hd", 0, short)
TEST_SPRINTF(hd_width_plus_zero, "%+5hd", 0, short)
TEST_SPRINTF(hd_width_spac_zero, "% 5hd", 0, short)
TEST_SPRINTF(hd_width_fzer_zero, "%05hd", 0, short)

TEST_SPRINTF(hd_zrwth_plus_zero, "%+0hd", 0, short)
TEST_SPRINTF(hd_zrwth_spac_zero, "% 0hd", 0, short)

TEST_SPRINTF(hd_prec_mins_zero, "%-.5hd", 0, short)
TEST_SPRINTF(hd_prec_plus_zero, "%+.5hd", 0, short)
TEST_SPRINTF(hd_prec_spac_zero, "% .5hd", 0, short)

TEST_SPRINTF(hd_zrpc_mins_zero, "%-.0hd", 0, short)
TEST_SPRINTF(hd_zrpc_plus_zero, "%+.0hd", 0, short)
TEST_SPRINTF(hd_zrpc_spac_zero, "% .0hd", 0, short)

TEST_SPRINTF(hd_width_prec_mins_zero, "%-10.5hd", 0, short)
TEST_SPRINTF(hd_width_prec_plus_zero, "%+10.5hd", 0, short)
TEST_SPRINTF(hd_width_prec_spac_zero, "% 10.5hd", 0, short)

TEST_SPRINTF_2(hd_dynamic_width_zero, "%*hd", 10, 0, short)
TEST_SPRINTF_2(hd_dynamic_prec_zero, "%.*hd", 5, 0, short)
TEST_SPRINTF_3(hd_dynamic_width_prec_zero, "%*.*hd", 10, 5, 0, short)

// =========================================================================

TEST_SPRINTF(hi_mins_zero, "%-hi", 0, short)
TEST_SPRINTF(hi_plus_zero, "%+hi", 0, short)
TEST_SPRINTF(hi_spac_zero, "% hi", 0, short)
TEST_SPRINTF(hi_fzer_zero, "%0hi", 0, short)

TEST_SPRINTF(hi_width_zero, "%5hi", 0, short)
TEST_SPRINTF(hi_zrpc_zero, "%.0hi", 0, short)
TEST_SPRINTF(hi_prec_zero, "%.5hi", 0, short)
TEST_SPRINTF(hi_width_prec_zero, "%10.5hi", 0, short)

TEST_SPRINTF(hi_width_mins_zero, "%-5hi", 0, short)
TEST_SPRINTF(hi_width_plus_zero, "%+5hi", 0, short)
TEST_SPRINTF(hi_width_spac_zero, "% 5hi", 0, short)
TEST_SPRINTF(hi_width_fzer_zero, "%05hi", 0, short)

TEST_SPRINTF(hi_zrwth_plus_zero, "%+0hi", 0, short)
TEST_SPRINTF(hi_zrwth_spac_zero, "% 0hi", 0, short)

TEST_SPRINTF(hi_prec_mins_zero, "%-.5hi", 0, short)
TEST_SPRINTF(hi_prec_plus_zero, "%+.5hi", 0, short)
TEST_SPRINTF(hi_prec_spac_zero, "% .5hi", 0, short)

TEST_SPRINTF(hi_zrpc_mins_zero, "%-.0hi", 0, short)
TEST_SPRINTF(hi_zrpc_plus_zero, "%+.0hi", 0, short)
TEST_SPRINTF(hi_zrpc_spac_zero, "% .0hi", 0, short)

TEST_SPRINTF(hi_width_prec_mins_zero, "%-10.5hi", 0, short)
TEST_SPRINTF(hi_width_prec_plus_zero, "%+10.5hi", 0, short)
TEST_SPRINTF(hi_width_prec_spac_zero, "% 10.5hi", 0, short)

TEST_SPRINTF_2(hi_dynamic_width_zero, "%*hi", 10, 0, short)
TEST_SPRINTF_2(hi_dynamic_prec_zero, "%.*hi", 5, 0, short)
TEST_SPRINTF_3(hi_dynamic_width_prec_zero, "%*.*hi", 10, 5, 0, short)

// =========================================================================

TEST_SPRINTF(ho_mins_zero, "%-ho", 0, unsigned short)
TEST_SPRINTF(ho_hash_zero, "%#ho", 0, unsigned short)
TEST_SPRINTF(ho_fzer_zero, "%0ho", 0, unsigned short)

TEST_SPRINTF(ho_width_zero, "%5ho", 0, unsigned short)
TEST_SPRINTF(ho_zrpc_zero, "%.0ho", 0, unsigned short)
TEST_SPRINTF(ho_prec_zero, "%.5ho", 0, unsigned short)
TEST_SPRINTF(ho_width_prec_zero, "%10.5ho", 0, unsigned short)

TEST_SPRINTF(ho_width_mins_zero, "%-5ho", 0, unsigned short)
TEST_SPRINTF(ho_width_hash_zero, "%#5ho", 0, unsigned short)
TEST_SPRINTF(ho_width_fzer_zero, "%05ho", 0, unsigned short)

TEST_SPRINTF(ho_zrwth_hash_zero, "%#0ho", 0, unsigned short)

TEST_SPRINTF(ho_prec_mins_zero, "%-.5ho", 0, unsigned short)
TEST_SPRINTF(ho_prec_hash_zero, "%#.5ho", 0, unsigned short)

TEST_SPRINTF(ho_zrpc_mins_zero, "%-.0ho", 0, unsigned short)
TEST_SPRINTF(ho_zrpc_hash_zero, "%#.0ho", 0, unsigned short)

TEST_SPRINTF(ho_width_prec_mins_zero, "%-10.5ho", 0, unsigned short)
TEST_SPRINTF(ho_width_prec_hash_zero, "%#10.5ho", 0, unsigned short)

TEST_SPRINTF_2(ho_dynamic_width_zero, "%*ho", 10, 0, unsigned short)
TEST_SPRINTF_2(ho_dynamic_prec_zero, "%.*ho", 5, 0, unsigned short)
TEST_SPRINTF_3(ho_dynamic_width_prec_zero, "%*.*ho", 10, 5, 0, unsigned short)

// =========================================================================

TEST_SPRINTF(hu_mins_zero, "%-hu", 0, unsigned short)
TEST_SPRINTF(hu_fzer_zero, "%0hu", 0, unsigned short)

TEST_SPRINTF(hu_width_zero, "%5hu", 0, unsigned short)
TEST_SPRINTF(hu_zrpc_zero, "%.0hu", 0, unsigned short)
TEST_SPRINTF(hu_prec_zero, "%.5hu", 0, unsigned short)
TEST_SPRINTF(hu_width_prec_zero, "%10.5hu", 0, unsigned short)

TEST_SPRINTF(hu_width_mins_zero, "%-5hu", 0, unsigned short)
TEST_SPRINTF(hu_width_fzer_zero, "%05hu", 0, unsigned short)

TEST_SPRINTF(hu_prec_mins_zero, "%-.5hu", 0, unsigned short)

TEST_SPRINTF(hu_zrpc_mins_zero, "%-.0hu", 0, unsigned short)

TEST_SPRINTF(hu_width_prec_mins_zero, "%-10.5hu", 0, unsigned short)

TEST_SPRINTF_2(hu_dynamic_width_zero, "%*hu", 10, 0, unsigned short)
TEST_SPRINTF_2(hu_dynamic_prec_zero, "%.*hu", 5, 0, unsigned short)
TEST_SPRINTF_3(hu_dynamic_width_prec_zero, "%*.*hu", 10, 5, 0, unsigned short)

// =========================================================================

TEST_SPRINTF(hx_mins_zero, "%-hx", 0, unsigned short)
TEST_SPRINTF(hx_hash_zero, "%#hx", 0, unsigned short)
TEST_SPRINTF(hx_fzer_zero, "%0hx", 0, unsigned short)

TEST_SPRINTF(hx_width_zero, "%5hx", 0, unsigned short)
TEST_SPRINTF(hx_zrpc_zero, "%.0hx", 0, unsigned short)
TEST_SPRINTF(hx_prec_zero, "%.5hx", 0, unsigned short)
TEST_SPRINTF(hx_width_prec_zero, "%10.5hx", 0, unsigned short)

TEST_SPRINTF(hx_width_mins_zero, "%-5hx", 0, unsigned short)
TEST_SPRINTF(hx_width_hash_zero, "%#5hx", 0, unsigned short)
TEST_SPRINTF(hx_width_fzer_zero, "%05hx", 0, unsigned short)

TEST_SPRINTF(hx_zrwth_hash_zero, "%#0hx", 0, unsigned short)

TEST_SPRINTF(hx_prec_mins_zero, "%-.5hx", 0, unsigned short)
TEST_SPRINTF(hx_prec_hash_zero, "%#.5hx", 0, unsigned short)

TEST_SPRINTF(hx_zrpc_mins_zero, "%-.0hx", 0, unsigned short)
TEST_SPRINTF(hx_zrpc_hash_zero, "%#.0hx", 0, unsigned short)

TEST_SPRINTF(hx_width_prec_mins_zero, "%-10.5hx", 0, unsigned short)
TEST_SPRINTF(hx_width_prec_hash_zero, "%#10.5hx", 0, unsigned short)

TEST_SPRINTF_2(hx_dynamic_width_zero, "%*hx", 10, 0, unsigned short)
TEST_SPRINTF_2(hx_dynamic_prec_zero, "%.*hx", 5, 0, unsigned short)
TEST_SPRINTF_3(hx_dynamic_width_prec_zero, "%*.*hx", 10, 5, 0, unsigned short)

// =========================================================================

TEST_SPRINTF(hX_mins_zero, "%-hX", 0, unsigned short)
TEST_SPRINTF(hX_hash_zero, "%#hX", 0, unsigned short)
TEST_SPRINTF(hX_fzer_zero, "%0hX", 0, unsigned short)

TEST_SPRINTF(hX_width_zero, "%5hX", 0, unsigned short)
TEST_SPRINTF(hX_zrpc_zero, "%.0hX", 0, unsigned short)
TEST_SPRINTF(hX_prec_zero, "%.5hX", 0, unsigned short)
TEST_SPRINTF(hX_width_prec_zero, "%10.5hX", 0, unsigned short)

TEST_SPRINTF(hX_width_mins_zero, "%-5hX", 0, unsigned short)
TEST_SPRINTF(hX_width_hash_zero, "%#5hX", 0, unsigned short)
TEST_SPRINTF(hX_width_fzer_zero, "%05hX", 0, unsigned short)

TEST_SPRINTF(hX_zrwth_hash_zero, "%#0hX", 0, unsigned short)

TEST_SPRINTF(hX_prec_mins_zero, "%-.5hX", 0, unsigned short)
TEST_SPRINTF(hX_prec_hash_zero, "%#.5hX", 0, unsigned short)

TEST_SPRINTF(hX_zrpc_mins_zero, "%-.0hX", 0, unsigned short)
TEST_SPRINTF(hX_zrpc_hash_zero, "%#.0hX", 0, unsigned short)

TEST_SPRINTF(hX_width_prec_mins_zero, "%-10.5hX", 0, unsigned short)
TEST_SPRINTF(hX_width_prec_hash_zero, "%#10.5hX", 0, unsigned short)

TEST_SPRINTF_2(hX_dynamic_width_zero, "%*hX", 10, 0, unsigned short)
TEST_SPRINTF_2(hX_dynamic_prec_zero, "%.*hX", 5, 0, unsigned short)
TEST_SPRINTF_3(hX_dynamic_width_prec_zero, "%*.*hX", 10, 5, 0, unsigned short)

// =========================================================================

TEST_SPRINTF(hhd_mins_zero, "%-hhd", 0, signed char)
TEST_SPRINTF(hhd_plus_zero, "%+hhd", 0, signed char)
TEST_SPRINTF(hhd_spac_zero, "% hhd", 0, signed char)
TEST_SPRINTF(hhd_fzer_zero, "%0hhd", 0, signed char)

TEST_SPRINTF(hhd_width_zero, "%5hhd", 0, signed char)
TEST_SPRINTF(hhd_zrpc_zero, "%.0hhd", 0, signed char)
TEST_SPRINTF(hhd_prec_zero, "%.5hhd", 0, signed char)
TEST_SPRINTF(hhd_width_prec_zero, "%10.5hhd", 0, signed char)

TEST_SPRINTF(hhd_width_mins_zero, "%-5hhd", 0, signed char)
TEST_SPRINTF(hhd_width_plus_zero, "%+5hhd", 0, signed char)
TEST_SPRINTF(hhd_width_spac_zero, "% 5hhd", 0, signed char)
TEST_SPRINTF(hhd_width_fzer_zero, "%05hhd", 0, signed char)

TEST_SPRINTF(hhd_zrwth_plus_zero, "%+0hhd", 0, signed char)
TEST_SPRINTF(hhd_zrwth_spac_zero, "% 0hhd", 0, signed char)

TEST_SPRINTF(hhd_prec_mins_zero, "%-.5hhd", 0, signed char)
TEST_SPRINTF(hhd_prec_plus_zero, "%+.5hhd", 0, signed char)
TEST_SPRINTF(hhd_prec_spac_zero, "% .5hhd", 0, signed char)

TEST_SPRINTF(hhd_zrpc_mins_zero, "%-.0hhd", 0, signed char)
TEST_SPRINTF(hhd_zrpc_plus_zero, "%+.0hhd", 0, signed char)
TEST_SPRINTF(hhd_zrpc_spac_zero, "% .0hhd", 0, signed char)

TEST_SPRINTF(hhd_width_prec_mins_zero, "%-10.5hhd", 0, signed char)
TEST_SPRINTF(hhd_width_prec_plus_zero, "%+10.5hhd", 0, signed char)
TEST_SPRINTF(hhd_width_prec_spac_zero, "% 10.5hhd", 0, signed char)

TEST_SPRINTF_2(hhd_dynamic_width_zero, "%*hhd", 10, 0, signed char)
TEST_SPRINTF_2(hhd_dynamic_prec_zero, "%.*hhd", 5, 0, signed char)
TEST_SPRINTF_3(hhd_dynamic_width_prec_zero, "%*.*hhd", 10, 5, 0, signed char)

// =========================================================================

TEST_SPRINTF(hhi_mins_zero, "%-hhi", 0, signed char)
TEST_SPRINTF(hhi_plus_zero, "%+hhi", 0, signed char)
TEST_SPRINTF(hhi_spac_zero, "% hhi", 0, signed char)
TEST_SPRINTF(hhi_fzer_zero, "%0hhi", 0, signed char)

TEST_SPRINTF(hhi_width_zero, "%5hhi", 0, signed char)
TEST_SPRINTF(hhi_zrpc_zero, "%.0hhi", 0, signed char)
TEST_SPRINTF(hhi_prec_zero, "%.5hhi", 0, signed char)
TEST_SPRINTF(hhi_width_prec_zero, "%10.5hhi", 0, signed char)

TEST_SPRINTF(hhi_width_mins_zero, "%-5hhi", 0, signed char)
TEST_SPRINTF(hhi_width_plus_zero, "%+5hhi", 0, signed char)
TEST_SPRINTF(hhi_width_spac_zero, "% 5hhi", 0, signed char)
TEST_SPRINTF(hhi_width_fzer_zero, "%05hhi", 0, signed char)

TEST_SPRINTF(hhi_zrwth_plus_zero, "%+0hhi", 0, signed char)
TEST_SPRINTF(hhi_zrwth_spac_zero, "% 0hhi", 0, signed char)

TEST_SPRINTF(hhi_prec_mins_zero, "%-.5hhi", 0, signed char)
TEST_SPRINTF(hhi_prec_plus_zero, "%+.5hhi", 0, signed char)
TEST_SPRINTF(hhi_prec_spac_zero, "% .5hhi", 0, signed char)

TEST_SPRINTF(hhi_zrpc_mins_zero, "%-.0hhi", 0, signed char)
TEST_SPRINTF(hhi_zrpc_plus_zero, "%+.0hhi", 0, signed char)
TEST_SPRINTF(hhi_zrpc_spac_zero, "% .0hhi", 0, signed char)

TEST_SPRINTF(hhi_width_prec_mins_zero, "%-10.5hhi", 0, signed char)
TEST_SPRINTF(hhi_width_prec_plus_zero, "%+10.5hhi", 0, signed char)
TEST_SPRINTF(hhi_width_prec_spac_zero, "% 10.5hhi", 0, signed char)

TEST_SPRINTF_2(hhi_dynamic_width_zero, "%*hhi", 10, 0, signed char)
TEST_SPRINTF_2(hhi_dynamic_prec_zero, "%.*hhi", 5, 0, signed char)
TEST_SPRINTF_3(hhi_dynamic_width_prec_zero, "%*.*hhi", 10, 5, 0, signed char)

// =========================================================================

TEST_SPRINTF(hho_mins_zero, "%-hho", 0, unsigned char)
TEST_SPRINTF(hho_hash_zero, "%#hho", 0, unsigned char)
TEST_SPRINTF(hho_fzer_zero, "%0hho", 0, unsigned char)

TEST_SPRINTF(hho_width_zero, "%5hho", 0, unsigned char)
TEST_SPRINTF(hho_zrpc_zero, "%.0hho", 0, unsigned char)
TEST_SPRINTF(hho_prec_zero, "%.5hho", 0, unsigned char)
TEST_SPRINTF(hho_width_prec_zero, "%10.5hho", 0, unsigned char)

TEST_SPRINTF(hho_width_mins_zero, "%-5hho", 0, unsigned char)
TEST_SPRINTF(hho_width_hash_zero, "%#5hho", 0, unsigned char)
TEST_SPRINTF(hho_width_fzer_zero, "%05hho", 0, unsigned char)

TEST_SPRINTF(hho_zrwth_hash_zero, "%#0hho", 0, unsigned char)

TEST_SPRINTF(hho_prec_mins_zero, "%-.5hho", 0, unsigned char)
TEST_SPRINTF(hho_prec_hash_zero, "%#.5hho", 0, unsigned char)

TEST_SPRINTF(hho_zrpc_mins_zero, "%-.0hho", 0, unsigned char)
TEST_SPRINTF(hho_zrpc_hash_zero, "%#.0hho", 0, unsigned char)

TEST_SPRINTF(hho_width_prec_mins_zero, "%-10.5hho", 0, unsigned char)
TEST_SPRINTF(hho_width_prec_hash_zero, "%#10.5hho", 0, unsigned char)

TEST_SPRINTF_2(hho_dynamic_width_zero, "%*hho", 10, 0, unsigned char)
TEST_SPRINTF_2(hho_dynamic_prec_zero, "%.*hho", 5, 0, unsigned char)
TEST_SPRINTF_3(hho_dynamic_width_prec_zero, "%*.*hho", 10, 5, 0, unsigned char)

// =========================================================================

TEST_SPRINTF(hhu_mins_zero, "%-hhu", 0, unsigned char)
TEST_SPRINTF(hhu_fzer_zero, "%0hhu", 0, unsigned char)

TEST_SPRINTF(hhu_width_zero, "%5hhu", 0, unsigned char)
TEST_SPRINTF(hhu_zrpc_zero, "%.0hhu", 0, unsigned char)
TEST_SPRINTF(hhu_prec_zero, "%.5hhu", 0, unsigned char)
TEST_SPRINTF(hhu_width_prec_zero, "%10.5hhu", 0, unsigned char)

TEST_SPRINTF(hhu_width_mins_zero, "%-5hhu", 0, unsigned char)
TEST_SPRINTF(hhu_width_fzer_zero, "%05hhu", 0, unsigned char)

TEST_SPRINTF(hhu_prec_mins_zero, "%-.5hhu", 0, unsigned char)

TEST_SPRINTF(hhu_zrpc_mins_zero, "%-.0hhu", 0, unsigned char)

TEST_SPRINTF(hhu_width_prec_mins_zero, "%-10.5hhu", 0, unsigned char)

TEST_SPRINTF_2(hhu_dynamic_width_zero, "%*hhu", 10, 0, unsigned char)
TEST_SPRINTF_2(hhu_dynamic_prec_zero, "%.*hhu", 5, 0, unsigned char)
TEST_SPRINTF_3(hhu_dynamic_width_prec_zero, "%*.*hhu", 10, 5, 0, unsigned char)

// =========================================================================

TEST_SPRINTF(hhx_mins_zero, "%-hhx", 0, unsigned char)
TEST_SPRINTF(hhx_hash_zero, "%#hhx", 0, unsigned char)
TEST_SPRINTF(hhx_fzer_zero, "%0hhx", 0, unsigned char)

TEST_SPRINTF(hhx_width_zero, "%5hhx", 0, unsigned char)
TEST_SPRINTF(hhx_zrpc_zero, "%.0hhx", 0, unsigned char)
TEST_SPRINTF(hhx_prec_zero, "%.5hhx", 0, unsigned char)
TEST_SPRINTF(hhx_width_prec_zero, "%10.5hhx", 0, unsigned char)

TEST_SPRINTF(hhx_width_mins_zero, "%-5hhx", 0, unsigned char)
TEST_SPRINTF(hhx_width_hash_zero, "%#5hhx", 0, unsigned char)
TEST_SPRINTF(hhx_width_fzer_zero, "%05hhx", 0, unsigned char)

TEST_SPRINTF(hhx_zrwth_hash_zero, "%#0hhx", 0, unsigned char)

TEST_SPRINTF(hhx_prec_mins_zero, "%-.5hhx", 0, unsigned char)
TEST_SPRINTF(hhx_prec_hash_zero, "%#.5hhx", 0, unsigned char)

TEST_SPRINTF(hhx_zrpc_mins_zero, "%-.0hhx", 0, unsigned char)
TEST_SPRINTF(hhx_zrpc_hash_zero, "%#.0hhx", 0, unsigned char)

TEST_SPRINTF(hhx_width_prec_mins_zero, "%-10.5hhx", 0, unsigned char)
TEST_SPRINTF(hhx_width_prec_hash_zero, "%#10.5hhx", 0, unsigned char)

TEST_SPRINTF_2(hhx_dynamic_width_zero, "%*hhx", 10, 0, unsigned char)
TEST_SPRINTF_2(hhx_dynamic_prec_zero, "%.*hhx", 5, 0, unsigned char)
TEST_SPRINTF_3(hhx_dynamic_width_prec_zero, "%*.*hhx", 10, 5, 0, unsigned char)

// =========================================================================

TEST_SPRINTF(hhX_mins_zero, "%-hhX", 0, unsigned char)
TEST_SPRINTF(hhX_hash_zero, "%#hhX", 0, unsigned char)
TEST_SPRINTF(hhX_fzer_zero, "%0hhX", 0, unsigned char)

TEST_SPRINTF(hhX_width_zero, "%5hhX", 0, unsigned char)
TEST_SPRINTF(hhX_zrpc_zero, "%.0hhX", 0, unsigned char)
TEST_SPRINTF(hhX_prec_zero, "%.5hhX", 0, unsigned char)
TEST_SPRINTF(hhX_width_prec_zero, "%10.5hhX", 0, unsigned char)

TEST_SPRINTF(hhX_width_mins_zero, "%-5hhX", 0, unsigned char)
TEST_SPRINTF(hhX_width_hash_zero, "%#5hhX", 0, unsigned char)
TEST_SPRINTF(hhX_width_fzer_zero, "%05hhX", 0, unsigned char)

TEST_SPRINTF(hhX_zrwth_hash_zero, "%#0hhX", 0, unsigned char)

TEST_SPRINTF(hhX_prec_mins_zero, "%-.5hhX", 0, unsigned char)
TEST_SPRINTF(hhX_prec_hash_zero, "%#.5hhX", 0, unsigned char)

TEST_SPRINTF(hhX_zrpc_mins_zero, "%-.0hhX", 0, unsigned char)
TEST_SPRINTF(hhX_zrpc_hash_zero, "%#.0hhX", 0, unsigned char)

TEST_SPRINTF(hhX_width_prec_mins_zero, "%-10.5hhX", 0, unsigned char)
TEST_SPRINTF(hhX_width_prec_hash_zero, "%#10.5hhX", 0, unsigned char)

TEST_SPRINTF_2(hhX_dynamic_width_zero, "%*hhX", 10, 0, unsigned char)
TEST_SPRINTF_2(hhX_dynamic_prec_zero, "%.*hhX", 5, 0, unsigned char)
TEST_SPRINTF_3(hhX_dynamic_width_prec_zero, "%*.*hhX", 10, 5, 0, unsigned char)

// =========================================================================

TEST_SPRINTF(ld_mins_zero, "%-ld", 0, long)
TEST_SPRINTF(ld_plus_zero, "%+ld", 0, long)
TEST_SPRINTF(ld_spac_zero, "% ld", 0, long)
TEST_SPRINTF(ld_fzer_zero, "%0ld", 0, long)

TEST_SPRINTF(ld_width_zero, "%5ld", 0, long)
TEST_SPRINTF(ld_zrpc_zero, "%.0ld", 0, long)
TEST_SPRINTF(ld_prec_zero, "%.5ld", 0, long)
TEST_SPRINTF(ld_width_prec_zero, "%10.5ld", 0, long)

TEST_SPRINTF(ld_width_mins_zero, "%-5ld", 0, long)
TEST_SPRINTF(ld_width_plus_zero, "%+5ld", 0, long)
TEST_SPRINTF(ld_width_spac_zero, "% 5ld", 0, long)
TEST_SPRINTF(ld_width_fzer_zero, "%05ld", 0, long)

TEST_SPRINTF(ld_zrwth_plus_zero, "%+0ld", 0, long)
TEST_SPRINTF(ld_zrwth_spac_zero, "% 0ld", 0, long)

TEST_SPRINTF(ld_prec_mins_zero, "%-.5ld", 0, long)
TEST_SPRINTF(ld_prec_plus_zero, "%+.5ld", 0, long)
TEST_SPRINTF(ld_prec_spac_zero, "% .5ld", 0, long)

TEST_SPRINTF(ld_zrpc_mins_zero, "%-.0ld", 0, long)
TEST_SPRINTF(ld_zrpc_plus_zero, "%+.0ld", 0, long)
TEST_SPRINTF(ld_zrpc_spac_zero, "% .0ld", 0, long)

TEST_SPRINTF(ld_width_prec_mins_zero, "%-10.5ld", 0, long)
TEST_SPRINTF(ld_width_prec_plus_zero, "%+10.5ld", 0, long)
TEST_SPRINTF(ld_width_prec_spac_zero, "% 10.5ld", 0, long)

TEST_SPRINTF_2(ld_dynamic_width_zero, "%*ld", 10, 0, long)
TEST_SPRINTF_2(ld_dynamic_prec_zero, "%.*ld", 5, 0, long)
TEST_SPRINTF_3(ld_dynamic_width_prec_zero, "%*.*ld", 10, 5, 0, long)

// =========================================================================

TEST_SPRINTF(li_mins_zero, "%-li", 0, long)
TEST_SPRINTF(li_plus_zero, "%+li", 0, long)
TEST_SPRINTF(li_spac_zero, "% li", 0, long)
TEST_SPRINTF(li_fzer_zero, "%0li", 0, long)

TEST_SPRINTF(li_width_zero, "%5li", 0, long)
TEST_SPRINTF(li_zrpc_zero, "%.0li", 0, long)
TEST_SPRINTF(li_prec_zero, "%.5li", 0, long)
TEST_SPRINTF(li_width_prec_zero, "%10.5li", 0, long)

TEST_SPRINTF(li_width_mins_zero, "%-5li", 0, long)
TEST_SPRINTF(li_width_plus_zero, "%+5li", 0, long)
TEST_SPRINTF(li_width_spac_zero, "% 5li", 0, long)
TEST_SPRINTF(li_width_fzer_zero, "%05li", 0, long)

TEST_SPRINTF(li_zrwth_plus_zero, "%+0li", 0, long)
TEST_SPRINTF(li_zrwth_spac_zero, "% 0li", 0, long)

TEST_SPRINTF(li_prec_mins_zero, "%-.5li", 0, long)
TEST_SPRINTF(li_prec_plus_zero, "%+.5li", 0, long)
TEST_SPRINTF(li_prec_spac_zero, "% .5li", 0, long)

TEST_SPRINTF(li_zrpc_mins_zero, "%-.0li", 0, long)
TEST_SPRINTF(li_zrpc_plus_zero, "%+.0li", 0, long)
TEST_SPRINTF(li_zrpc_spac_zero, "% .0li", 0, long)

TEST_SPRINTF(li_width_prec_mins_zero, "%-10.5li", 0, long)
TEST_SPRINTF(li_width_prec_plus_zero, "%+10.5li", 0, long)
TEST_SPRINTF(li_width_prec_spac_zero, "% 10.5li", 0, long)

TEST_SPRINTF_2(li_dynamic_width_zero, "%*li", 10, 0, long)
TEST_SPRINTF_2(li_dynamic_prec_zero, "%.*li", 5, 0, long)
TEST_SPRINTF_3(li_dynamic_width_prec_zero, "%*.*li", 10, 5, 0, long)

// =========================================================================

TEST_SPRINTF(lo_mins_zero, "%-lo", 0, unsigned long)
TEST_SPRINTF(lo_hash_zero, "%#lo", 0, unsigned long)
TEST_SPRINTF(lo_fzer_zero, "%0lo", 0, unsigned long)

TEST_SPRINTF(lo_width_zero, "%5lo", 0, unsigned long)
TEST_SPRINTF(lo_zrpc_zero, "%.0lo", 0, unsigned long)
TEST_SPRINTF(lo_prec_zero, "%.5lo", 0, unsigned long)
TEST_SPRINTF(lo_width_prec_zero, "%10.5lo", 0, unsigned long)

TEST_SPRINTF(lo_width_mins_zero, "%-5lo", 0, unsigned long)
TEST_SPRINTF(lo_width_hash_zero, "%#5lo", 0, unsigned long)
TEST_SPRINTF(lo_width_fzer_zero, "%05lo", 0, unsigned long)

TEST_SPRINTF(lo_zrwth_hash_zero, "%#0lo", 0, unsigned long)

TEST_SPRINTF(lo_prec_mins_zero, "%-.5lo", 0, unsigned long)
TEST_SPRINTF(lo_prec_hash_zero, "%#.5lo", 0, unsigned long)

TEST_SPRINTF(lo_zrpc_mins_zero, "%-.0lo", 0, unsigned long)
TEST_SPRINTF(lo_zrpc_hash_zero, "%#.0lo", 0, unsigned long)

TEST_SPRINTF(lo_width_prec_mins_zero, "%-10.5lo", 0, unsigned long)
TEST_SPRINTF(lo_width_prec_hash_zero, "%#10.5lo", 0, unsigned long)

TEST_SPRINTF_2(lo_dynamic_width_zero, "%*lo", 10, 0, unsigned long)
TEST_SPRINTF_2(lo_dynamic_prec_zero, "%.*lo", 5, 0, unsigned long)
TEST_SPRINTF_3(lo_dynamic_width_prec_zero, "%*.*lo", 10, 5, 0, unsigned long)

// =========================================================================

TEST_SPRINTF(lu_mins_zero, "%-lu", 0, unsigned long)
TEST_SPRINTF(lu_fzer_zero, "%0lu", 0, unsigned long)

TEST_SPRINTF(lu_width_zero, "%5lu", 0, unsigned long)
TEST_SPRINTF(lu_zrpc_zero, "%.0lu", 0, unsigned long)
TEST_SPRINTF(lu_prec_zero, "%.5lu", 0, unsigned long)
TEST_SPRINTF(lu_width_prec_zero, "%10.5lu", 0, unsigned long)

TEST_SPRINTF(lu_width_mins_zero, "%-5lu", 0, unsigned long)
TEST_SPRINTF(lu_width_fzer_zero, "%05lu", 0, unsigned long)

TEST_SPRINTF(lu_prec_mins_zero, "%-.5lu", 0, unsigned long)

TEST_SPRINTF(lu_zrpc_mins_zero, "%-.0lu", 0, unsigned long)

TEST_SPRINTF(lu_width_prec_mins_zero, "%-10.5lu", 0, unsigned long)

TEST_SPRINTF_2(lu_dynamic_width_zero, "%*lu", 10, 0, unsigned long)
TEST_SPRINTF_2(lu_dynamic_prec_zero, "%.*lu", 5, 0, unsigned long)
TEST_SPRINTF_3(lu_dynamic_width_prec_zero, "%*.*lu", 10, 5, 0, unsigned long)

// =========================================================================

TEST_SPRINTF(lx_mins_zero, "%-lx", 0, unsigned long)
TEST_SPRINTF(lx_hash_zero, "%#lx", 0, unsigned long)
TEST_SPRINTF(lx_fzer_zero, "%0lx", 0, unsigned long)

TEST_SPRINTF(lx_width_zero, "%5lx", 0, unsigned long)
TEST_SPRINTF(lx_zrpc_zero, "%.0lx", 0, unsigned long)
TEST_SPRINTF(lx_prec_zero, "%.5lx", 0, unsigned long)
TEST_SPRINTF(lx_width_prec_zero, "%10.5lx", 0, unsigned long)

TEST_SPRINTF(lx_width_mins_zero, "%-5lx", 0, unsigned long)
TEST_SPRINTF(lx_width_hash_zero, "%#5lx", 0, unsigned long)
TEST_SPRINTF(lx_width_fzer_zero, "%05lx", 0, unsigned long)

TEST_SPRINTF(lx_zrwth_hash_zero, "%#0lx", 0, unsigned long)

TEST_SPRINTF(lx_prec_mins_zero, "%-.5lx", 0, unsigned long)
TEST_SPRINTF(lx_prec_hash_zero, "%#.5lx", 0, unsigned long)

TEST_SPRINTF(lx_zrpc_mins_zero, "%-.0lx", 0, unsigned long)
TEST_SPRINTF(lx_zrpc_hash_zero, "%#.0lx", 0, unsigned long)

TEST_SPRINTF(lx_width_prec_mins_zero, "%-10.5lx", 0, unsigned long)
TEST_SPRINTF(lx_width_prec_hash_zero, "%#10.5lx", 0, unsigned long)

TEST_SPRINTF_2(lx_dynamic_width_zero, "%*lx", 10, 0, unsigned long)
TEST_SPRINTF_2(lx_dynamic_prec_zero, "%.*lx", 5, 0, unsigned long)
TEST_SPRINTF_3(lx_dynamic_width_prec_zero, "%*.*lx", 10, 5, 0, unsigned long)

// =========================================================================

TEST_SPRINTF(lX_mins_zero, "%-lX", 0, unsigned long)
TEST_SPRINTF(lX_hash_zero, "%#lX", 0, unsigned long)
TEST_SPRINTF(lX_fzer_zero, "%0lX", 0, unsigned long)

TEST_SPRINTF(lX_width_zero, "%5lX", 0, unsigned long)
TEST_SPRINTF(lX_zrpc_zero, "%.0lX", 0, unsigned long)
TEST_SPRINTF(lX_prec_zero, "%.5lX", 0, unsigned long)
TEST_SPRINTF(lX_width_prec_zero, "%10.5lX", 0, unsigned long)

TEST_SPRINTF(lX_width_mins_zero, "%-5lX", 0, unsigned long)
TEST_SPRINTF(lX_width_hash_zero, "%#5lX", 0, unsigned long)
TEST_SPRINTF(lX_width_fzer_zero, "%05lX", 0, unsigned long)

TEST_SPRINTF(lX_zrwth_hash_zero, "%#0lX", 0, unsigned long)

TEST_SPRINTF(lX_prec_mins_zero, "%-.5lX", 0, unsigned long)
TEST_SPRINTF(lX_prec_hash_zero, "%#.5lX", 0, unsigned long)

TEST_SPRINTF(lX_zrpc_mins_zero, "%-.0lX", 0, unsigned long)
TEST_SPRINTF(lX_zrpc_hash_zero, "%#.0lX", 0, unsigned long)

TEST_SPRINTF(lX_width_prec_mins_zero, "%-10.5lX", 0, unsigned long)
TEST_SPRINTF(lX_width_prec_hash_zero, "%#10.5lX", 0, unsigned long)

TEST_SPRINTF_2(lX_dynamic_width_zero, "%*lX", 10, 0, unsigned long)
TEST_SPRINTF_2(lX_dynamic_prec_zero, "%.*lX", 5, 0, unsigned long)
TEST_SPRINTF_3(lX_dynamic_width_prec_zero, "%*.*lX", 10, 5, 0, unsigned long)

// =========================================================================

TEST_SPRINTF(lld_mins_zero, "%-lld", 0, long long)
TEST_SPRINTF(lld_plus_zero, "%+lld", 0, long long)
TEST_SPRINTF(lld_spac_zero, "% lld", 0, long long)
TEST_SPRINTF(lld_fzer_zero, "%0lld", 0, long long)

TEST_SPRINTF(lld_width_zero, "%5lld", 0, long long)
TEST_SPRINTF(lld_zrpc_zero, "%.0lld", 0, long long)
TEST_SPRINTF(lld_prec_zero, "%.5lld", 0, long long)
TEST_SPRINTF(lld_width_prec_zero, "%10.5lld", 0, long long)

TEST_SPRINTF(lld_width_mins_zero, "%-5lld", 0, long long)
TEST_SPRINTF(lld_width_plus_zero, "%+5lld", 0, long long)
TEST_SPRINTF(lld_width_spac_zero, "% 5lld", 0, long long)
TEST_SPRINTF(lld_width_fzer_zero, "%05lld", 0, long long)

TEST_SPRINTF(lld_zrwth_plus_zero, "%+0lld", 0, long long)
TEST_SPRINTF(lld_zrwth_spac_zero, "% 0lld", 0, long long)

TEST_SPRINTF(lld_prec_mins_zero, "%-.5lld", 0, long long)
TEST_SPRINTF(lld_prec_plus_zero, "%+.5lld", 0, long long)
TEST_SPRINTF(lld_prec_spac_zero, "% .5lld", 0, long long)

TEST_SPRINTF(lld_zrpc_mins_zero, "%-.0lld", 0, long long)
TEST_SPRINTF(lld_zrpc_plus_zero, "%+.0lld", 0, long long)
TEST_SPRINTF(lld_zrpc_spac_zero, "% .0lld", 0, long long)

TEST_SPRINTF(lld_width_prec_mins_zero, "%-10.5lld", 0, long long)
TEST_SPRINTF(lld_width_prec_plus_zero, "%+10.5lld", 0, long long)
TEST_SPRINTF(lld_width_prec_spac_zero, "% 10.5lld", 0, long long)

TEST_SPRINTF_2(lld_dynamic_width_zero, "%*lld", 10, 0, long long)
TEST_SPRINTF_2(lld_dynamic_prec_zero, "%.*lld", 5, 0, long long)
TEST_SPRINTF_3(lld_dynamic_width_prec_zero, "%*.*lld", 10, 5, 0, long long)

// =========================================================================

TEST_SPRINTF(lli_mins_zero, "%-lli", 0, long long)
TEST_SPRINTF(lli_plus_zero, "%+lli", 0, long long)
TEST_SPRINTF(lli_spac_zero, "% lli", 0, long long)
TEST_SPRINTF(lli_fzer_zero, "%0lli", 0, long long)

TEST_SPRINTF(lli_width_zero, "%5lli", 0, long long)
TEST_SPRINTF(lli_zrpc_zero, "%.0lli", 0, long long)
TEST_SPRINTF(lli_prec_zero, "%.5lli", 0, long long)
TEST_SPRINTF(lli_width_prec_zero, "%10.5lli", 0, long long)

TEST_SPRINTF(lli_width_mins_zero, "%-5lli", 0, long long)
TEST_SPRINTF(lli_width_plus_zero, "%+5lli", 0, long long)
TEST_SPRINTF(lli_width_spac_zero, "% 5lli", 0, long long)
TEST_SPRINTF(lli_width_fzer_zero, "%05lli", 0, long long)

TEST_SPRINTF(lli_zrwth_plus_zero, "%+0lli", 0, long long)
TEST_SPRINTF(lli_zrwth_spac_zero, "% 0lli", 0, long long)

TEST_SPRINTF(lli_prec_mins_zero, "%-.5lli", 0, long long)
TEST_SPRINTF(lli_prec_plus_zero, "%+.5lli", 0, long long)
TEST_SPRINTF(lli_prec_spac_zero, "% .5lli", 0, long long)

TEST_SPRINTF(lli_zrpc_mins_zero, "%-.0lli", 0, long long)
TEST_SPRINTF(lli_zrpc_plus_zero, "%+.0lli", 0, long long)
TEST_SPRINTF(lli_zrpc_spac_zero, "% .0lli", 0, long long)

TEST_SPRINTF(lli_width_prec_mins_zero, "%-10.5lli", 0, long long)
TEST_SPRINTF(lli_width_prec_plus_zero, "%+10.5lli", 0, long long)
TEST_SPRINTF(lli_width_prec_spac_zero, "% 10.5lli", 0, long long)

TEST_SPRINTF_2(lli_dynamic_width_zero, "%*lli", 10, 0, long long)
TEST_SPRINTF_2(lli_dynamic_prec_zero, "%.*lli", 5, 0, long long)
TEST_SPRINTF_3(lli_dynamic_width_prec_zero, "%*.*lli", 10, 5, 0, long long)

// =========================================================================

TEST_SPRINTF(llo_mins_zero, "%-llo", 0, unsigned long long)
TEST_SPRINTF(llo_hash_zero, "%#llo", 0, unsigned long long)
TEST_SPRINTF(llo_fzer_zero, "%0llo", 0, unsigned long long)

TEST_SPRINTF(llo_width_zero, "%5llo", 0, unsigned long long)
TEST_SPRINTF(llo_zrpc_zero, "%.0llo", 0, unsigned long long)
TEST_SPRINTF(llo_prec_zero, "%.5llo", 0, unsigned long long)
TEST_SPRINTF(llo_width_prec_zero, "%10.5llo", 0, unsigned long long)

TEST_SPRINTF(llo_width_mins_zero, "%-5llo", 0, unsigned long long)
TEST_SPRINTF(llo_width_hash_zero, "%#5llo", 0, unsigned long long)
TEST_SPRINTF(llo_width_fzer_zero, "%05llo", 0, unsigned long long)

TEST_SPRINTF(llo_zrwth_hash_zero, "%#0llo", 0, unsigned long long)

TEST_SPRINTF(llo_prec_mins_zero, "%-.5llo", 0, unsigned long long)
TEST_SPRINTF(llo_prec_hash_zero, "%#.5llo", 0, unsigned long long)

TEST_SPRINTF(llo_zrpc_mins_zero, "%-.0llo", 0, unsigned long long)
TEST_SPRINTF(llo_zrpc_hash_zero, "%#.0llo", 0, unsigned long long)

TEST_SPRINTF(llo_width_prec_mins_zero, "%-10.5llo", 0, unsigned long long)
TEST_SPRINTF(llo_width_prec_hash_zero, "%#10.5llo", 0, unsigned long long)

TEST_SPRINTF_2(llo_dynamic_width_zero, "%*llo", 10, 0, unsigned long long)
TEST_SPRINTF_2(llo_dynamic_prec_zero, "%.*llo", 5, 0, unsigned long long)
TEST_SPRINTF_3(llo_dynamic_width_prec_zero, "%*.*llo", 10, 5, 0,
               unsigned long long)

// =========================================================================

TEST_SPRINTF(llu_mins_zero, "%-llu", 0, unsigned long long)
TEST_SPRINTF(llu_fzer_zero, "%0llu", 0, unsigned long long)

TEST_SPRINTF(llu_width_zero, "%5llu", 0, unsigned long long)
TEST_SPRINTF(llu_zrpc_zero, "%.0llu", 0, unsigned long long)
TEST_SPRINTF(llu_prec_zero, "%.5llu", 0, unsigned long long)
TEST_SPRINTF(llu_width_prec_zero, "%10.5llu", 0, unsigned long long)

TEST_SPRINTF(llu_width_mins_zero, "%-5llu", 0, unsigned long long)
TEST_SPRINTF(llu_width_fzer_zero, "%05llu", 0, unsigned long long)

TEST_SPRINTF(llu_prec_mins_zero, "%-.5llu", 0, unsigned long long)

TEST_SPRINTF(llu_zrpc_mins_zero, "%-.0llu", 0, unsigned long long)

TEST_SPRINTF(llu_width_prec_mins_zero, "%-10.5llu", 0, unsigned long long)

TEST_SPRINTF_2(llu_dynamic_width_zero, "%*llu", 10, 0, unsigned long long)
TEST_SPRINTF_2(llu_dynamic_prec_zero, "%.*llu", 5, 0, unsigned long long)
TEST_SPRINTF_3(llu_dynamic_width_prec_zero, "%*.*llu", 10, 5, 0,
               unsigned long long)

// =========================================================================

TEST_SPRINTF(llx_mins_zero, "%-llx", 0, unsigned long long)
TEST_SPRINTF(llx_hash_zero, "%#llx", 0, unsigned long long)
TEST_SPRINTF(llx_fzer_zero, "%0llx", 0, unsigned long long)

TEST_SPRINTF(llx_width_zero, "%5llx", 0, unsigned long long)
TEST_SPRINTF(llx_zrpc_zero, "%.0llx", 0, unsigned long long)
TEST_SPRINTF(llx_prec_zero, "%.5llx", 0, unsigned long long)
TEST_SPRINTF(llx_width_prec_zero, "%10.5llx", 0, unsigned long long)

TEST_SPRINTF(llx_width_mins_zero, "%-5llx", 0, unsigned long long)
TEST_SPRINTF(llx_width_hash_zero, "%#5llx", 0, unsigned long long)
TEST_SPRINTF(llx_width_fzer_zero, "%05llx", 0, unsigned long long)

TEST_SPRINTF(llx_zrwth_hash_zero, "%#0llx", 0, unsigned long long)

TEST_SPRINTF(llx_prec_mins_zero, "%-.5llx", 0, unsigned long long)
TEST_SPRINTF(llx_prec_hash_zero, "%#.5llx", 0, unsigned long long)

TEST_SPRINTF(llx_zrpc_mins_zero, "%-.0llx", 0, unsigned long long)
TEST_SPRINTF(llx_zrpc_hash_zero, "%#.0llx", 0, unsigned long long)

TEST_SPRINTF(llx_width_prec_mins_zero, "%-10.5llx", 0, unsigned long long)
TEST_SPRINTF(llx_width_prec_hash_zero, "%#10.5llx", 0, unsigned long long)

TEST_SPRINTF_2(llx_dynamic_width_zero, "%*llx", 10, 0, unsigned long long)
TEST_SPRINTF_2(llx_dynamic_prec_zero, "%.*llx", 5, 0, unsigned long long)
TEST_SPRINTF_3(llx_dynamic_width_prec_zero, "%*.*llx", 10, 5, 0,
               unsigned long long)

// =========================================================================

TEST_SPRINTF(llX_mins_zero, "%-llX", 0, unsigned long long)
TEST_SPRINTF(llX_hash_zero, "%#llX", 0, unsigned long long)
TEST_SPRINTF(llX_fzer_zero, "%0llX", 0, unsigned long long)

TEST_SPRINTF(llX_width_zero, "%5llX", 0, unsigned long long)
TEST_SPRINTF(llX_zrpc_zero, "%.0llX", 0, unsigned long long)
TEST_SPRINTF(llX_prec_zero, "%.5llX", 0, unsigned long long)
TEST_SPRINTF(llX_width_prec_zero, "%10.5llX", 0, unsigned long long)

TEST_SPRINTF(llX_width_mins_zero, "%-5llX", 0, unsigned long long)
TEST_SPRINTF(llX_width_hash_zero, "%#5llX", 0, unsigned long long)
TEST_SPRINTF(llX_width_fzer_zero, "%05llX", 0, unsigned long long)

TEST_SPRINTF(llX_zrwth_hash_zero, "%#0llX", 0, unsigned long long)

TEST_SPRINTF(llX_prec_mins_zero, "%-.5llX", 0, unsigned long long)
TEST_SPRINTF(llX_prec_hash_zero, "%#.5llX", 0, unsigned long long)

TEST_SPRINTF(llX_zrpc_mins_zero, "%-.0llX", 0, unsigned long long)
TEST_SPRINTF(llX_zrpc_hash_zero, "%#.0llX", 0, unsigned long long)

TEST_SPRINTF(llX_width_prec_mins_zero, "%-10.5llX", 0, unsigned long long)
TEST_SPRINTF(llX_width_prec_hash_zero, "%#10.5llX", 0, unsigned long long)

TEST_SPRINTF_2(llX_dynamic_width_zero, "%*llX", 10, 0, unsigned long long)
TEST_SPRINTF_2(llX_dynamic_prec_zero, "%.*llX", 5, 0, unsigned long long)
TEST_SPRINTF_3(llX_dynamic_width_prec_zero, "%*.*llX", 10, 5, 0,
               unsigned long long)
#pragma endregion

// =========================================================================
// Целочисленные типы %d %i %o %u %x %X
// =========================================================================
#pragma region
TEST_SPRINTF(d_mins_post, "%-d", 123, int)
TEST_SPRINTF(d_plus_post, "%+d", 123, int)
TEST_SPRINTF(d_spac_post, "% d", 123, int)
TEST_SPRINTF(d_fzer_post, "%0d", 123, int)
TEST_SPRINTF(d_mins_negt, "%-d", -123, int)
TEST_SPRINTF(d_plus_negt, "%+d", -123, int)
TEST_SPRINTF(d_spac_negt, "% d", -123, int)
TEST_SPRINTF(d_fzer_negt, "%0d", -123, int)

TEST_SPRINTF(d_width_post, "%5d", 123, int)
TEST_SPRINTF(d_zrpc_post, "%.0d", 123, int)
TEST_SPRINTF(d_prec_post, "%.5d", 123, int)
TEST_SPRINTF(d_width_prec_post, "%10.5d", 123, int)
TEST_SPRINTF(d_width_negt, "%5d", -123, int)
TEST_SPRINTF(d_zrpc_negt, "%.0d", -123, int)
TEST_SPRINTF(d_prec_negt, "%.5d", -123, int)
TEST_SPRINTF(d_width_prec_negt, "%10.5d", -123, int)

TEST_SPRINTF(d_width_mins_post, "%-5d", 123, int)
TEST_SPRINTF(d_width_plus_post, "%+5d", 123, int)
TEST_SPRINTF(d_width_spac_post, "% 5d", 123, int)
TEST_SPRINTF(d_width_fzer_post, "%05d", 123, int)
TEST_SPRINTF(d_width_mins_negt, "%-5d", -123, int)
TEST_SPRINTF(d_width_plus_negt, "%+5d", -123, int)
TEST_SPRINTF(d_width_spac_negt, "% 5d", -123, int)
TEST_SPRINTF(d_width_fzer_negt, "%05d", -123, int)

TEST_SPRINTF(d_zrwth_plus_post, "%+0d", 123, int)
TEST_SPRINTF(d_zrwth_spac_post, "% 0d", 123, int)
TEST_SPRINTF(d_zrwth_plus_negt, "%+0d", -123, int)
TEST_SPRINTF(d_zrwth_spac_negt, "% 0d", -123, int)

TEST_SPRINTF(d_prec_mins_post, "%-.5d", 123, int)
TEST_SPRINTF(d_prec_plus_post, "%+.5d", 123, int)
TEST_SPRINTF(d_prec_spac_post, "% .5d", 123, int)
TEST_SPRINTF(d_prec_mins_negt, "%-.5d", -123, int)
TEST_SPRINTF(d_prec_plus_negt, "%+.5d", -123, int)
TEST_SPRINTF(d_prec_spac_negt, "% .5d", -123, int)

TEST_SPRINTF(d_zrpc_mins_post, "%-.0d", 123, int)
TEST_SPRINTF(d_zrpc_plus_post, "%+.0d", 123, int)
TEST_SPRINTF(d_zrpc_spac_post, "% .0d", 123, int)
TEST_SPRINTF(d_zrpc_mins_negt, "%-.0d", -123, int)
TEST_SPRINTF(d_zrpc_plus_negt, "%+.0d", -123, int)
TEST_SPRINTF(d_zrpc_spac_negt, "% .0d", -123, int)

TEST_SPRINTF(d_width_prec_mins_post, "%-10.5d", 123, int)
TEST_SPRINTF(d_width_prec_plus_post, "%+10.5d", 123, int)
TEST_SPRINTF(d_width_prec_spac_post, "% 10.5d", 123, int)
TEST_SPRINTF(d_width_prec_mins_negt, "%-10.5d", -123, int)
TEST_SPRINTF(d_width_prec_plus_negt, "%+10.5d", -123, int)
TEST_SPRINTF(d_width_prec_spac_negt, "% 10.5d", -123, int)

TEST_SPRINTF_2(d_dynamic_width_post, "%*d", 10, 123, int)
TEST_SPRINTF_2(d_dynamic_prec_post, "%.*d", 5, 123, int)
TEST_SPRINTF_3(d_dynamic_width_prec_post, "%*.*d", 10, 5, 123, int)
TEST_SPRINTF_2(d_dynamic_width_negt, "%*d", 10, -123, int)
TEST_SPRINTF_2(d_dynamic_prec_negt, "%.*d", 5, -123, int)
TEST_SPRINTF_3(d_dynamic_width_prec_negt, "%*.*d", 10, 5, -123, int)

// =========================================================================

TEST_SPRINTF(i_mins_post, "%-i", 123, int)
TEST_SPRINTF(i_plus_post, "%+i", 123, int)
TEST_SPRINTF(i_spac_post, "% i", 123, int)
TEST_SPRINTF(i_fzer_post, "%0i", 123, int)
TEST_SPRINTF(i_mins_negt, "%-i", -123, int)
TEST_SPRINTF(i_plus_negt, "%+i", -123, int)
TEST_SPRINTF(i_spac_negt, "% i", -123, int)
TEST_SPRINTF(i_fzer_negt, "%0i", -123, int)

TEST_SPRINTF(i_width_post, "%5i", 123, int)
TEST_SPRINTF(i_zrpc_post, "%.0i", 123, int)
TEST_SPRINTF(i_prec_post, "%.5i", 123, int)
TEST_SPRINTF(i_width_prec_post, "%10.5i", 123, int)
TEST_SPRINTF(i_width_negt, "%5i", -123, int)
TEST_SPRINTF(i_zrpc_negt, "%.0i", -123, int)
TEST_SPRINTF(i_prec_negt, "%.5i", -123, int)
TEST_SPRINTF(i_width_prec_negt, "%10.5i", -123, int)

TEST_SPRINTF(i_width_mins_post, "%-5i", 123, int)
TEST_SPRINTF(i_width_plus_post, "%+5i", 123, int)
TEST_SPRINTF(i_width_spac_post, "% 5i", 123, int)
TEST_SPRINTF(i_width_fzer_post, "%05i", 123, int)
TEST_SPRINTF(i_width_mins_negt, "%-5i", -123, int)
TEST_SPRINTF(i_width_plus_negt, "%+5i", -123, int)
TEST_SPRINTF(i_width_spac_negt, "% 5i", -123, int)
TEST_SPRINTF(i_width_fzer_negt, "%05i", -123, int)

TEST_SPRINTF(i_zrwth_plus_post, "%+0i", 123, int)
TEST_SPRINTF(i_zrwth_spac_post, "% 0i", 123, int)
TEST_SPRINTF(i_zrwth_plus_negt, "%+0i", -123, int)
TEST_SPRINTF(i_zrwth_spac_negt, "% 0i", -123, int)

TEST_SPRINTF(i_prec_mins_post, "%-.5i", 123, int)
TEST_SPRINTF(i_prec_plus_post, "%+.5i", 123, int)
TEST_SPRINTF(i_prec_spac_post, "% .5i", 123, int)
TEST_SPRINTF(i_prec_mins_negt, "%-.5i", -123, int)
TEST_SPRINTF(i_prec_plus_negt, "%+.5i", -123, int)
TEST_SPRINTF(i_prec_spac_negt, "% .5i", -123, int)

TEST_SPRINTF(i_zrpc_mins_post, "%-.0i", 123, int)
TEST_SPRINTF(i_zrpc_plus_post, "%+.0i", 123, int)
TEST_SPRINTF(i_zrpc_spac_post, "% .0i", 123, int)
TEST_SPRINTF(i_zrpc_mins_negt, "%-.0i", -123, int)
TEST_SPRINTF(i_zrpc_plus_negt, "%+.0i", -123, int)
TEST_SPRINTF(i_zrpc_spac_negt, "% .0i", -123, int)

TEST_SPRINTF(i_width_prec_mins_post, "%-10.5i", 123, int)
TEST_SPRINTF(i_width_prec_plus_post, "%+10.5i", 123, int)
TEST_SPRINTF(i_width_prec_spac_post, "% 10.5i", 123, int)
TEST_SPRINTF(i_width_prec_mins_negt, "%-10.5i", -123, int)
TEST_SPRINTF(i_width_prec_plus_negt, "%+10.5i", -123, int)
TEST_SPRINTF(i_width_prec_spac_negt, "% 10.5i", -123, int)

TEST_SPRINTF_2(i_dynamic_width_post, "%*i", 10, 123, int)
TEST_SPRINTF_2(i_dynamic_prec_post, "%.*i", 5, 123, int)
TEST_SPRINTF_3(i_dynamic_width_prec_post, "%*.*i", 10, 5, 123, int)
TEST_SPRINTF_2(i_dynamic_width_negt, "%*i", 10, -123, int)
TEST_SPRINTF_2(i_dynamic_prec_negt, "%.*i", 5, -123, int)
TEST_SPRINTF_3(i_dynamic_width_prec_negt, "%*.*i", 10, 5, -123, int)

// =========================================================================

TEST_SPRINTF(o_mins_post, "%-o", 123, int)
TEST_SPRINTF(o_hash_post, "%#o", 123, int)
TEST_SPRINTF(o_fzer_post, "%0o", 123, int)
TEST_SPRINTF(o_mins_negt, "%-o", -123, int)
TEST_SPRINTF(o_hash_negt, "%#o", -123, int)
TEST_SPRINTF(o_fzer_negt, "%0o", -123, int)

TEST_SPRINTF(o_width_post, "%5o", 123, int)
TEST_SPRINTF(o_zrpc_post, "%.0o", 123, int)
TEST_SPRINTF(o_prec_post, "%.5o", 123, int)
TEST_SPRINTF(o_width_prec_post, "%10.5o", 123, int)
TEST_SPRINTF(o_width_negt, "%5o", -123, int)
TEST_SPRINTF(o_zrpc_negt, "%.0o", -123, int)
TEST_SPRINTF(o_prec_negt, "%.5o", -123, int)
TEST_SPRINTF(o_width_prec_negt, "%10.5o", -123, int)

TEST_SPRINTF(o_width_mins_post, "%-5o", 123, int)
TEST_SPRINTF(o_width_hash_post, "%#5o", 123, int)
TEST_SPRINTF(o_width_fzer_post, "%05o", 123, int)
TEST_SPRINTF(o_width_mins_negt, "%-5o", -123, int)
TEST_SPRINTF(o_width_hash_negt, "%#5o", -123, int)
TEST_SPRINTF(o_width_fzer_negt, "%05o", -123, int)

TEST_SPRINTF(o_zrwth_hash_post, "%#0o", 123, int)
TEST_SPRINTF(o_zrwth_hash_negt, "%#0o", -123, int)

TEST_SPRINTF(o_prec_mins_post, "%-.5o", 123, int)
TEST_SPRINTF(o_prec_hash_post, "%#.5o", 123, int)
TEST_SPRINTF(o_prec_mins_negt, "%-.5o", -123, int)
TEST_SPRINTF(o_prec_hash_negt, "%#.5o", -123, int)

TEST_SPRINTF(o_zrpc_mins_post, "%-.0o", 123, int)
TEST_SPRINTF(o_zrpc_hash_post, "%#.0o", 123, int)
TEST_SPRINTF(o_zrpc_mins_negt, "%-.0o", -123, int)
TEST_SPRINTF(o_zrpc_hash_negt, "%#.0o", -123, int)

TEST_SPRINTF(o_width_prec_mins_post, "%-10.5o", 123, int)
TEST_SPRINTF(o_width_prec_hash_post, "%#10.5o", 123, int)
TEST_SPRINTF(o_width_prec_mins_negt, "%-10.5o", -123, int)
TEST_SPRINTF(o_width_prec_hash_negt, "%#10.5o", -123, int)

TEST_SPRINTF_2(o_dynamic_width_post, "%*o", 10, 123, int)
TEST_SPRINTF_2(o_dynamic_prec_post, "%.*o", 5, 123, int)
TEST_SPRINTF_3(o_dynamic_width_prec_post, "%*.*o", 10, 5, 123, int)
TEST_SPRINTF_2(o_dynamic_width_negt, "%*o", 10, -123, int)
TEST_SPRINTF_2(o_dynamic_prec_negt, "%.*o", 5, -123, int)
TEST_SPRINTF_3(o_dynamic_width_prec_negt, "%*.*o", 10, 5, -123, int)

// =========================================================================

TEST_SPRINTF(u_mins_post, "%-u", 123, int)
TEST_SPRINTF(u_fzer_post, "%0u", 123, int)
TEST_SPRINTF(u_mins_negt, "%-u", -123, int)
TEST_SPRINTF(u_fzer_negt, "%0u", -123, int)

TEST_SPRINTF(u_width_post, "%5u", 123, int)
TEST_SPRINTF(u_zrpc_post, "%.0u", 123, int)
TEST_SPRINTF(u_prec_post, "%.5u", 123, int)
TEST_SPRINTF(u_width_prec_post, "%10.5u", 123, int)
TEST_SPRINTF(u_width_negt, "%5u", -123, int)
TEST_SPRINTF(u_zrpc_negt, "%.0u", -123, int)
TEST_SPRINTF(u_prec_negt, "%.5u", -123, int)
TEST_SPRINTF(u_width_prec_negt, "%10.5u", -123, int)

TEST_SPRINTF(u_width_mins_post, "%-5u", 123, int)
TEST_SPRINTF(u_width_fzer_post, "%05u", 123, int)
TEST_SPRINTF(u_width_mins_negt, "%-5u", -123, int)
TEST_SPRINTF(u_width_fzer_negt, "%05u", -123, int)

TEST_SPRINTF(u_prec_mins_post, "%-.5u", 123, int)
TEST_SPRINTF(u_prec_mins_negt, "%-.5u", -123, int)

TEST_SPRINTF(u_zrpc_mins_post, "%-.0u", 123, int)
TEST_SPRINTF(u_zrpc_mins_negt, "%-.0u", -123, int)

TEST_SPRINTF(u_width_prec_mins_post, "%-10.5u", 123, int)
TEST_SPRINTF(u_width_prec_mins_negt, "%-10.5u", -123, int)

TEST_SPRINTF_2(u_dynamic_width_post, "%*u", 10, 123, int)
TEST_SPRINTF_2(u_dynamic_prec_post, "%.*u", 5, 123, int)
TEST_SPRINTF_3(u_dynamic_width_prec_post, "%*.*u", 10, 5, 123, int)
TEST_SPRINTF_2(u_dynamic_width_negt, "%*u", 10, -123, int)
TEST_SPRINTF_2(u_dynamic_prec_negt, "%.*u", 5, -123, int)
TEST_SPRINTF_3(u_dynamic_width_prec_negt, "%*.*u", 10, 5, -123, int)

// =========================================================================

TEST_SPRINTF(x_mins_post, "%-x", 123, int)
TEST_SPRINTF(x_hash_post, "%#x", 123, int)
TEST_SPRINTF(x_fzer_post, "%0x", 123, int)
TEST_SPRINTF(x_mins_negt, "%-x", -123, int)
TEST_SPRINTF(x_hash_negt, "%#x", -123, int)
TEST_SPRINTF(x_fzer_negt, "%0x", -123, int)

TEST_SPRINTF(x_width_post, "%5x", 123, int)
TEST_SPRINTF(x_zrpc_post, "%.0x", 123, int)
TEST_SPRINTF(x_prec_post, "%.5x", 123, int)
TEST_SPRINTF(x_width_prec_post, "%10.5x", 123, int)
TEST_SPRINTF(x_width_negt, "%5x", -123, int)
TEST_SPRINTF(x_zrpc_negt, "%.0x", -123, int)
TEST_SPRINTF(x_prec_negt, "%.5x", -123, int)
TEST_SPRINTF(x_width_prec_negt, "%10.5x", -123, int)

TEST_SPRINTF(x_width_mins_post, "%-5x", 123, int)
TEST_SPRINTF(x_width_hash_post, "%#5x", 123, int)
TEST_SPRINTF(x_width_fzer_post, "%05x", 123, int)
TEST_SPRINTF(x_width_mins_negt, "%-5x", -123, int)
TEST_SPRINTF(x_width_hash_negt, "%#5x", -123, int)
TEST_SPRINTF(x_width_fzer_negt, "%05x", -123, int)

TEST_SPRINTF(x_zrwth_hash_post, "%#0x", 123, int)
TEST_SPRINTF(x_zrwth_hash_negt, "%#0x", -123, int)

TEST_SPRINTF(x_prec_mins_post, "%-.5x", 123, int)
TEST_SPRINTF(x_prec_hash_post, "%#.5x", 123, int)
TEST_SPRINTF(x_prec_mins_negt, "%-.5x", -123, int)
TEST_SPRINTF(x_prec_hash_negt, "%#.5x", -123, int)

TEST_SPRINTF(x_zrpc_mins_post, "%-.0x", 123, int)
TEST_SPRINTF(x_zrpc_hash_post, "%#.0x", 123, int)
TEST_SPRINTF(x_zrpc_mins_negt, "%-.0x", -123, int)
TEST_SPRINTF(x_zrpc_hash_negt, "%#.0x", -123, int)

TEST_SPRINTF(x_width_prec_mins_post, "%-10.5x", 123, int)
TEST_SPRINTF(x_width_prec_hash_post, "%#10.5x", 123, int)
TEST_SPRINTF(x_width_prec_mins_negt, "%-10.5x", -123, int)
TEST_SPRINTF(x_width_prec_hash_negt, "%#10.5x", -123, int)

TEST_SPRINTF_2(x_dynamic_width_post, "%*x", 10, 123, int)
TEST_SPRINTF_2(x_dynamic_prec_post, "%.*x", 5, 123, int)
TEST_SPRINTF_3(x_dynamic_width_prec_post, "%*.*x", 10, 5, 123, int)
TEST_SPRINTF_2(x_dynamic_width_negt, "%*x", 10, -123, int)
TEST_SPRINTF_2(x_dynamic_prec_negt, "%.*x", 5, -123, int)
TEST_SPRINTF_3(x_dynamic_width_prec_negt, "%*.*x", 10, 5, -123, int)

// =========================================================================

TEST_SPRINTF(X_mins_post, "%-X", 123, int)
TEST_SPRINTF(X_hash_post, "%#X", 123, int)
TEST_SPRINTF(X_fzer_post, "%0X", 123, int)
TEST_SPRINTF(X_mins_negt, "%-X", -123, int)
TEST_SPRINTF(X_hash_negt, "%#X", -123, int)
TEST_SPRINTF(X_fzer_negt, "%0X", -123, int)

TEST_SPRINTF(X_width_post, "%5X", 123, int)
TEST_SPRINTF(X_zrpc_post, "%.0X", 123, int)
TEST_SPRINTF(X_prec_post, "%.5X", 123, int)
TEST_SPRINTF(X_width_prec_post, "%10.5X", 123, int)
TEST_SPRINTF(X_width_negt, "%5X", -123, int)
TEST_SPRINTF(X_zrpc_negt, "%.0X", -123, int)
TEST_SPRINTF(X_prec_negt, "%.5X", -123, int)
TEST_SPRINTF(X_width_prec_negt, "%10.5X", -123, int)

TEST_SPRINTF(X_width_mins_post, "%-5X", 123, int)
TEST_SPRINTF(X_width_hash_post, "%#5X", 123, int)
TEST_SPRINTF(X_width_fzer_post, "%05X", 123, int)
TEST_SPRINTF(X_width_mins_negt, "%-5X", -123, int)
TEST_SPRINTF(X_width_hash_negt, "%#5X", -123, int)
TEST_SPRINTF(X_width_fzer_negt, "%05X", -123, int)

TEST_SPRINTF(X_zrwth_hash_post, "%#0X", 123, int)
TEST_SPRINTF(X_zrwth_hash_negt, "%#0X", -123, int)

TEST_SPRINTF(X_prec_mins_post, "%-.5X", 123, int)
TEST_SPRINTF(X_prec_hash_post, "%#.5X", 123, int)
TEST_SPRINTF(X_prec_mins_negt, "%-.5X", -123, int)
TEST_SPRINTF(X_prec_hash_negt, "%#.5X", -123, int)

TEST_SPRINTF(X_zrpc_mins_post, "%-.0X", 123, int)
TEST_SPRINTF(X_zrpc_hash_post, "%#.0X", 123, int)
TEST_SPRINTF(X_zrpc_mins_negt, "%-.0X", -123, int)
TEST_SPRINTF(X_zrpc_hash_negt, "%#.0X", -123, int)

TEST_SPRINTF(X_width_prec_mins_post, "%-10.5X", 123, int)
TEST_SPRINTF(X_width_prec_hash_post, "%#10.5X", 123, int)
TEST_SPRINTF(X_width_prec_mins_negt, "%-10.5X", -123, int)
TEST_SPRINTF(X_width_prec_hash_negt, "%#10.5X", -123, int)

TEST_SPRINTF_2(X_dynamic_width_post, "%*X", 10, 123, int)
TEST_SPRINTF_2(X_dynamic_prec_post, "%.*X", 5, 123, int)
TEST_SPRINTF_3(X_dynamic_width_prec_post, "%*.*X", 10, 5, 123, int)
TEST_SPRINTF_2(X_dynamic_width_negt, "%*X", 10, -123, int)
TEST_SPRINTF_2(X_dynamic_prec_negt, "%.*X", 5, -123, int)
TEST_SPRINTF_3(X_dynamic_width_prec_negt, "%*.*X", 10, 5, -123, int)
#pragma endregion

// =========================================================================
// Целочисленные типы модификатор h (short) %hd %hi %ho %hu %hx %hX
// =========================================================================
#pragma region
TEST_SPRINTF(hd_mins_post, "%-hd", 123, short)
TEST_SPRINTF(hd_plus_post, "%+hd", 123, short)
TEST_SPRINTF(hd_spac_post, "% hd", 123, short)
TEST_SPRINTF(hd_fzer_post, "%0hd", 123, short)
TEST_SPRINTF(hd_mins_negt, "%-hd", -123, short)
TEST_SPRINTF(hd_plus_negt, "%+hd", -123, short)
TEST_SPRINTF(hd_spac_negt, "% hd", -123, short)
TEST_SPRINTF(hd_fzer_negt, "%0hd", -123, short)

TEST_SPRINTF(hd_width_post, "%5hd", 123, short)
TEST_SPRINTF(hd_zrpc_post, "%.0hd", 123, short)
TEST_SPRINTF(hd_prec_post, "%.5hd", 123, short)
TEST_SPRINTF(hd_width_prec_post, "%10.5hd", 123, short)
TEST_SPRINTF(hd_width_negt, "%5hd", -123, short)
TEST_SPRINTF(hd_zrpc_negt, "%.0hd", -123, short)
TEST_SPRINTF(hd_prec_negt, "%.5hd", -123, short)
TEST_SPRINTF(hd_width_prec_negt, "%10.5hd", -123, short)

TEST_SPRINTF(hd_width_mins_post, "%-5hd", 123, short)
TEST_SPRINTF(hd_width_plus_post, "%+5hd", 123, short)
TEST_SPRINTF(hd_width_spac_post, "% 5hd", 123, short)
TEST_SPRINTF(hd_width_fzer_post, "%05hd", 123, short)
TEST_SPRINTF(hd_width_mins_negt, "%-5hd", -123, short)
TEST_SPRINTF(hd_width_plus_negt, "%+5hd", -123, short)
TEST_SPRINTF(hd_width_spac_negt, "% 5hd", -123, short)
TEST_SPRINTF(hd_width_fzer_negt, "%05hd", -123, short)

TEST_SPRINTF(hd_zrwth_plus_post, "%+0hd", 123, short)
TEST_SPRINTF(hd_zrwth_spac_post, "% 0hd", 123, short)
TEST_SPRINTF(hd_zrwth_plus_negt, "%+0hd", -123, short)
TEST_SPRINTF(hd_zrwth_spac_negt, "% 0hd", -123, short)

TEST_SPRINTF(hd_prec_mins_post, "%-.5hd", 123, short)
TEST_SPRINTF(hd_prec_plus_post, "%+.5hd", 123, short)
TEST_SPRINTF(hd_prec_spac_post, "% .5hd", 123, short)
TEST_SPRINTF(hd_prec_mins_negt, "%-.5hd", -123, short)
TEST_SPRINTF(hd_prec_plus_negt, "%+.5hd", -123, short)
TEST_SPRINTF(hd_prec_spac_negt, "% .5hd", -123, short)

TEST_SPRINTF(hd_zrpc_mins_post, "%-.0hd", 123, short)
TEST_SPRINTF(hd_zrpc_plus_post, "%+.0hd", 123, short)
TEST_SPRINTF(hd_zrpc_spac_post, "% .0hd", 123, short)
TEST_SPRINTF(hd_zrpc_mins_negt, "%-.0hd", -123, short)
TEST_SPRINTF(hd_zrpc_plus_negt, "%+.0hd", -123, short)
TEST_SPRINTF(hd_zrpc_spac_negt, "% .0hd", -123, short)

TEST_SPRINTF(hd_width_prec_mins_post, "%-10.5hd", 123, short)
TEST_SPRINTF(hd_width_prec_plus_post, "%+10.5hd", 123, short)
TEST_SPRINTF(hd_width_prec_spac_post, "% 10.5hd", 123, short)
TEST_SPRINTF(hd_width_prec_mins_negt, "%-10.5hd", -123, short)
TEST_SPRINTF(hd_width_prec_plus_negt, "%+10.5hd", -123, short)
TEST_SPRINTF(hd_width_prec_spac_negt, "% 10.5hd", -123, short)

TEST_SPRINTF_2(hd_dynamic_width_post, "%*hd", 10, 123, short)
TEST_SPRINTF_2(hd_dynamic_prec_post, "%.*hd", 5, 123, short)
TEST_SPRINTF_3(hd_dynamic_width_prec_post, "%*.*hd", 10, 5, 123, short)
TEST_SPRINTF_2(hd_dynamic_width_negt, "%*hd", 10, -123, short)
TEST_SPRINTF_2(hd_dynamic_prec_negt, "%.*hd", 5, -123, short)
TEST_SPRINTF_3(hd_dynamic_width_prec_negt, "%*.*hd", 10, 5, -123, short)

// =========================================================================

TEST_SPRINTF(hi_mins_post, "%-hi", 123, short)
TEST_SPRINTF(hi_plus_post, "%+hi", 123, short)
TEST_SPRINTF(hi_spac_post, "% hi", 123, short)
TEST_SPRINTF(hi_fzer_post, "%0hi", 123, short)
TEST_SPRINTF(hi_mins_negt, "%-hi", -123, short)
TEST_SPRINTF(hi_plus_negt, "%+hi", -123, short)
TEST_SPRINTF(hi_spac_negt, "% hi", -123, short)
TEST_SPRINTF(hi_fzer_negt, "%0hi", -123, short)

TEST_SPRINTF(hi_width_post, "%5hi", 123, short)
TEST_SPRINTF(hi_zrpc_post, "%.0hi", 123, short)
TEST_SPRINTF(hi_prec_post, "%.5hi", 123, short)
TEST_SPRINTF(hi_width_prec_post, "%10.5hi", 123, short)
TEST_SPRINTF(hi_width_negt, "%5hi", -123, short)
TEST_SPRINTF(hi_zrpc_negt, "%.0hi", -123, short)
TEST_SPRINTF(hi_prec_negt, "%.5hi", -123, short)
TEST_SPRINTF(hi_width_prec_negt, "%10.5hi", -123, short)

TEST_SPRINTF(hi_width_mins_post, "%-5hi", 123, short)
TEST_SPRINTF(hi_width_plus_post, "%+5hi", 123, short)
TEST_SPRINTF(hi_width_spac_post, "% 5hi", 123, short)
TEST_SPRINTF(hi_width_fzer_post, "%05hi", 123, short)
TEST_SPRINTF(hi_width_mins_negt, "%-5hi", -123, short)
TEST_SPRINTF(hi_width_plus_negt, "%+5hi", -123, short)
TEST_SPRINTF(hi_width_spac_negt, "% 5hi", -123, short)
TEST_SPRINTF(hi_width_fzer_negt, "%05hi", -123, short)

TEST_SPRINTF(hi_zrwth_plus_post, "%+0hi", 123, short)
TEST_SPRINTF(hi_zrwth_spac_post, "% 0hi", 123, short)
TEST_SPRINTF(hi_zrwth_plus_negt, "%+0hi", -123, short)
TEST_SPRINTF(hi_zrwth_spac_negt, "% 0hi", -123, short)

TEST_SPRINTF(hi_prec_mins_post, "%-.5hi", 123, short)
TEST_SPRINTF(hi_prec_plus_post, "%+.5hi", 123, short)
TEST_SPRINTF(hi_prec_spac_post, "% .5hi", 123, short)
TEST_SPRINTF(hi_prec_mins_negt, "%-.5hi", -123, short)
TEST_SPRINTF(hi_prec_plus_negt, "%+.5hi", -123, short)
TEST_SPRINTF(hi_prec_spac_negt, "% .5hi", -123, short)

TEST_SPRINTF(hi_zrpc_mins_post, "%-.0hi", 123, short)
TEST_SPRINTF(hi_zrpc_plus_post, "%+.0hi", 123, short)
TEST_SPRINTF(hi_zrpc_spac_post, "% .0hi", 123, short)
TEST_SPRINTF(hi_zrpc_mins_negt, "%-.0hi", -123, short)
TEST_SPRINTF(hi_zrpc_plus_negt, "%+.0hi", -123, short)
TEST_SPRINTF(hi_zrpc_spac_negt, "% .0hi", -123, short)

TEST_SPRINTF(hi_width_prec_mins_post, "%-10.5hi", 123, short)
TEST_SPRINTF(hi_width_prec_plus_post, "%+10.5hi", 123, short)
TEST_SPRINTF(hi_width_prec_spac_post, "% 10.5hi", 123, short)
TEST_SPRINTF(hi_width_prec_mins_negt, "%-10.5hi", -123, short)
TEST_SPRINTF(hi_width_prec_plus_negt, "%+10.5hi", -123, short)
TEST_SPRINTF(hi_width_prec_spac_negt, "% 10.5hi", -123, short)

TEST_SPRINTF_2(hi_dynamic_width_post, "%*hi", 10, 123, short)
TEST_SPRINTF_2(hi_dynamic_prec_post, "%.*hi", 5, 123, short)
TEST_SPRINTF_3(hi_dynamic_width_prec_post, "%*.*hi", 10, 5, 123, short)
TEST_SPRINTF_2(hi_dynamic_width_negt, "%*hi", 10, -123, short)
TEST_SPRINTF_2(hi_dynamic_prec_negt, "%.*hi", 5, -123, short)
TEST_SPRINTF_3(hi_dynamic_width_prec_negt, "%*.*hi", 10, 5, -123, short)

// =========================================================================

TEST_SPRINTF(ho_mins_post, "%-ho", 123, unsigned short)
TEST_SPRINTF(ho_hash_post, "%#ho", 123, unsigned short)
TEST_SPRINTF(ho_fzer_post, "%0ho", 123, unsigned short)
TEST_SPRINTF(ho_mins_negt, "%-ho", -123, unsigned short)
TEST_SPRINTF(ho_hash_negt, "%#ho", -123, unsigned short)
TEST_SPRINTF(ho_fzer_negt, "%0ho", -123, unsigned short)

TEST_SPRINTF(ho_width_post, "%5ho", 123, unsigned short)
TEST_SPRINTF(ho_zrpc_post, "%.0ho", 123, unsigned short)
TEST_SPRINTF(ho_prec_post, "%.5ho", 123, unsigned short)
TEST_SPRINTF(ho_width_prec_post, "%10.5ho", 123, unsigned short)
TEST_SPRINTF(ho_width_negt, "%5ho", -123, unsigned short)
TEST_SPRINTF(ho_zrpc_negt, "%.0ho", -123, unsigned short)
TEST_SPRINTF(ho_prec_negt, "%.5ho", -123, unsigned short)
TEST_SPRINTF(ho_width_prec_negt, "%10.5ho", -123, unsigned short)

TEST_SPRINTF(ho_width_mins_post, "%-5ho", 123, unsigned short)
TEST_SPRINTF(ho_width_hash_post, "%#5ho", 123, unsigned short)
TEST_SPRINTF(ho_width_fzer_post, "%05ho", 123, unsigned short)
TEST_SPRINTF(ho_width_mins_negt, "%-5ho", -123, unsigned short)
TEST_SPRINTF(ho_width_hash_negt, "%#5ho", -123, unsigned short)
TEST_SPRINTF(ho_width_fzer_negt, "%05ho", -123, unsigned short)

TEST_SPRINTF(ho_zrwth_hash_post, "%#0ho", 123, unsigned short)
TEST_SPRINTF(ho_zrwth_hash_negt, "%#0ho", -123, unsigned short)

TEST_SPRINTF(ho_prec_mins_post, "%-.5ho", 123, unsigned short)
TEST_SPRINTF(ho_prec_hash_post, "%#.5ho", 123, unsigned short)
TEST_SPRINTF(ho_prec_mins_negt, "%-.5ho", -123, unsigned short)
TEST_SPRINTF(ho_prec_hash_negt, "%#.5ho", -123, unsigned short)

TEST_SPRINTF(ho_zrpc_mins_post, "%-.0ho", 123, unsigned short)
TEST_SPRINTF(ho_zrpc_hash_post, "%#.0ho", 123, unsigned short)
TEST_SPRINTF(ho_zrpc_mins_negt, "%-.0ho", -123, unsigned short)
TEST_SPRINTF(ho_zrpc_hash_negt, "%#.0ho", -123, unsigned short)

TEST_SPRINTF(ho_width_prec_mins_post, "%-10.5ho", 123, unsigned short)
TEST_SPRINTF(ho_width_prec_hash_post, "%#10.5ho", 123, unsigned short)
TEST_SPRINTF(ho_width_prec_mins_negt, "%-10.5ho", -123, unsigned short)
TEST_SPRINTF(ho_width_prec_hash_negt, "%#10.5ho", -123, unsigned short)

TEST_SPRINTF_2(ho_dynamic_width_post, "%*ho", 10, 123, unsigned short)
TEST_SPRINTF_2(ho_dynamic_prec_post, "%.*ho", 5, 123, unsigned short)
TEST_SPRINTF_3(ho_dynamic_width_prec_post, "%*.*ho", 10, 5, 123, unsigned short)
TEST_SPRINTF_2(ho_dynamic_width_negt, "%*ho", 10, -123, unsigned short)
TEST_SPRINTF_2(ho_dynamic_prec_negt, "%.*ho", 5, -123, unsigned short)
TEST_SPRINTF_3(ho_dynamic_width_prec_negt, "%*.*ho", 10, 5, -123,
               unsigned short)

// =========================================================================

TEST_SPRINTF(hu_mins_post, "%-hu", 123, unsigned short)
TEST_SPRINTF(hu_fzer_post, "%0hu", 123, unsigned short)
TEST_SPRINTF(hu_mins_negt, "%-hu", -123, unsigned short)
TEST_SPRINTF(hu_fzer_negt, "%0hu", -123, unsigned short)

TEST_SPRINTF(hu_width_post, "%5hu", 123, unsigned short)
TEST_SPRINTF(hu_zrpc_post, "%.0hu", 123, unsigned short)
TEST_SPRINTF(hu_prec_post, "%.5hu", 123, unsigned short)
TEST_SPRINTF(hu_width_prec_post, "%10.5hu", 123, unsigned short)
TEST_SPRINTF(hu_width_negt, "%5hu", -123, unsigned short)
TEST_SPRINTF(hu_zrpc_negt, "%.0hu", -123, unsigned short)
TEST_SPRINTF(hu_prec_negt, "%.5hu", -123, unsigned short)
TEST_SPRINTF(hu_width_prec_negt, "%10.5hu", -123, unsigned short)

TEST_SPRINTF(hu_width_mins_post, "%-5hu", 123, unsigned short)
TEST_SPRINTF(hu_width_fzer_post, "%05hu", 123, unsigned short)
TEST_SPRINTF(hu_width_mins_negt, "%-5hu", -123, unsigned short)
TEST_SPRINTF(hu_width_fzer_negt, "%05hu", -123, unsigned short)

TEST_SPRINTF(hu_prec_mins_post, "%-.5hu", 123, unsigned short)
TEST_SPRINTF(hu_prec_mins_negt, "%-.5hu", -123, unsigned short)

TEST_SPRINTF(hu_zrpc_mins_post, "%-.0hu", 123, unsigned short)
TEST_SPRINTF(hu_zrpc_mins_negt, "%-.0hu", -123, unsigned short)

TEST_SPRINTF(hu_width_prec_mins_post, "%-10.5hu", 123, unsigned short)
TEST_SPRINTF(hu_width_prec_mins_negt, "%-10.5hu", -123, unsigned short)

TEST_SPRINTF_2(hu_dynamic_width_post, "%*hu", 10, 123, unsigned short)
TEST_SPRINTF_2(hu_dynamic_prec_post, "%.*hu", 5, 123, unsigned short)
TEST_SPRINTF_3(hu_dynamic_width_prec_post, "%*.*hu", 10, 5, 123, unsigned short)
TEST_SPRINTF_2(hu_dynamic_width_negt, "%*hu", 10, -123, unsigned short)
TEST_SPRINTF_2(hu_dynamic_prec_negt, "%.*hu", 5, -123, unsigned short)
TEST_SPRINTF_3(hu_dynamic_width_prec_negt, "%*.*hu", 10, 5, -123,
               unsigned short)

// =========================================================================

TEST_SPRINTF(hx_mins_post, "%-hx", 123, unsigned short)
TEST_SPRINTF(hx_hash_post, "%#hx", 123, unsigned short)
TEST_SPRINTF(hx_fzer_post, "%0hx", 123, unsigned short)
TEST_SPRINTF(hx_mins_negt, "%-hx", -123, unsigned short)
TEST_SPRINTF(hx_hash_negt, "%#hx", -123, unsigned short)
TEST_SPRINTF(hx_fzer_negt, "%0hx", -123, unsigned short)

TEST_SPRINTF(hx_width_post, "%5hx", 123, unsigned short)
TEST_SPRINTF(hx_zrpc_post, "%.0hx", 123, unsigned short)
TEST_SPRINTF(hx_prec_post, "%.5hx", 123, unsigned short)
TEST_SPRINTF(hx_width_prec_post, "%10.5hx", 123, unsigned short)
TEST_SPRINTF(hx_width_negt, "%5hx", -123, unsigned short)
TEST_SPRINTF(hx_zrpc_negt, "%.0hx", -123, unsigned short)
TEST_SPRINTF(hx_prec_negt, "%.5hx", -123, unsigned short)
TEST_SPRINTF(hx_width_prec_negt, "%10.5hx", -123, unsigned short)

TEST_SPRINTF(hx_width_mins_post, "%-5hx", 123, unsigned short)
TEST_SPRINTF(hx_width_hash_post, "%#5hx", 123, unsigned short)
TEST_SPRINTF(hx_width_fzer_post, "%05hx", 123, unsigned short)
TEST_SPRINTF(hx_width_mins_negt, "%-5hx", -123, unsigned short)
TEST_SPRINTF(hx_width_hash_negt, "%#5hx", -123, unsigned short)
TEST_SPRINTF(hx_width_fzer_negt, "%05hx", -123, unsigned short)

TEST_SPRINTF(hx_zrwth_hash_post, "%#0hx", 123, unsigned short)
TEST_SPRINTF(hx_zrwth_hash_negt, "%#0hx", -123, unsigned short)

TEST_SPRINTF(hx_prec_mins_post, "%-.5hx", 123, unsigned short)
TEST_SPRINTF(hx_prec_hash_post, "%#.5hx", 123, unsigned short)
TEST_SPRINTF(hx_prec_mins_negt, "%-.5hx", -123, unsigned short)
TEST_SPRINTF(hx_prec_hash_negt, "%#.5hx", -123, unsigned short)

TEST_SPRINTF(hx_zrpc_mins_post, "%-.0hx", 123, unsigned short)
TEST_SPRINTF(hx_zrpc_hash_post, "%#.0hx", 123, unsigned short)
TEST_SPRINTF(hx_zrpc_mins_negt, "%-.0hx", -123, unsigned short)
TEST_SPRINTF(hx_zrpc_hash_negt, "%#.0hx", -123, unsigned short)

TEST_SPRINTF(hx_width_prec_mins_post, "%-10.5hx", 123, unsigned short)
TEST_SPRINTF(hx_width_prec_hash_post, "%#10.5hx", 123, unsigned short)
TEST_SPRINTF(hx_width_prec_mins_negt, "%-10.5hx", -123, unsigned short)
TEST_SPRINTF(hx_width_prec_hash_negt, "%#10.5hx", -123, unsigned short)

TEST_SPRINTF_2(hx_dynamic_width_post, "%*hx", 10, 123, unsigned short)
TEST_SPRINTF_2(hx_dynamic_prec_post, "%.*hx", 5, 123, unsigned short)
TEST_SPRINTF_3(hx_dynamic_width_prec_post, "%*.*hx", 10, 5, 123, unsigned short)
TEST_SPRINTF_2(hx_dynamic_width_negt, "%*hx", 10, -123, unsigned short)
TEST_SPRINTF_2(hx_dynamic_prec_negt, "%.*hx", 5, -123, unsigned short)
TEST_SPRINTF_3(hx_dynamic_width_prec_negt, "%*.*hx", 10, 5, -123,
               unsigned short)

// =========================================================================

TEST_SPRINTF(hX_mins_post, "%-hX", 123, unsigned short)
TEST_SPRINTF(hX_hash_post, "%#hX", 123, unsigned short)
TEST_SPRINTF(hX_fzer_post, "%0hX", 123, unsigned short)
TEST_SPRINTF(hX_mins_negt, "%-hX", -123, unsigned short)
TEST_SPRINTF(hX_hash_negt, "%#hX", -123, unsigned short)
TEST_SPRINTF(hX_fzer_negt, "%0hX", -123, unsigned short)

TEST_SPRINTF(hX_width_post, "%5hX", 123, unsigned short)
TEST_SPRINTF(hX_zrpc_post, "%.0hX", 123, unsigned short)
TEST_SPRINTF(hX_prec_post, "%.5hX", 123, unsigned short)
TEST_SPRINTF(hX_width_prec_post, "%10.5hX", 123, unsigned short)
TEST_SPRINTF(hX_width_negt, "%5hX", -123, unsigned short)
TEST_SPRINTF(hX_zrpc_negt, "%.0hX", -123, unsigned short)
TEST_SPRINTF(hX_prec_negt, "%.5hX", -123, unsigned short)
TEST_SPRINTF(hX_width_prec_negt, "%10.5hX", -123, unsigned short)

TEST_SPRINTF(hX_width_mins_post, "%-5hX", 123, unsigned short)
TEST_SPRINTF(hX_width_hash_post, "%#5hX", 123, unsigned short)
TEST_SPRINTF(hX_width_fzer_post, "%05hX", 123, unsigned short)
TEST_SPRINTF(hX_width_mins_negt, "%-5hX", -123, unsigned short)
TEST_SPRINTF(hX_width_hash_negt, "%#5hX", -123, unsigned short)
TEST_SPRINTF(hX_width_fzer_negt, "%05hX", -123, unsigned short)

TEST_SPRINTF(hX_zrwth_hash_post, "%#0hX", 123, unsigned short)
TEST_SPRINTF(hX_zrwth_hash_negt, "%#0hX", -123, unsigned short)

TEST_SPRINTF(hX_prec_mins_post, "%-.5hX", 123, unsigned short)
TEST_SPRINTF(hX_prec_hash_post, "%#.5hX", 123, unsigned short)
TEST_SPRINTF(hX_prec_mins_negt, "%-.5hX", -123, unsigned short)
TEST_SPRINTF(hX_prec_hash_negt, "%#.5hX", -123, unsigned short)

TEST_SPRINTF(hX_zrpc_mins_post, "%-.0hX", 123, unsigned short)
TEST_SPRINTF(hX_zrpc_hash_post, "%#.0hX", 123, unsigned short)
TEST_SPRINTF(hX_zrpc_mins_negt, "%-.0hX", -123, unsigned short)
TEST_SPRINTF(hX_zrpc_hash_negt, "%#.0hX", -123, unsigned short)

TEST_SPRINTF(hX_width_prec_mins_post, "%-10.5hX", 123, unsigned short)
TEST_SPRINTF(hX_width_prec_hash_post, "%#10.5hX", 123, unsigned short)
TEST_SPRINTF(hX_width_prec_mins_negt, "%-10.5hX", -123, unsigned short)
TEST_SPRINTF(hX_width_prec_hash_negt, "%#10.5hX", -123, unsigned short)

TEST_SPRINTF_2(hX_dynamic_width_post, "%*hX", 10, 123, unsigned short)
TEST_SPRINTF_2(hX_dynamic_prec_post, "%.*hX", 5, 123, unsigned short)
TEST_SPRINTF_3(hX_dynamic_width_prec_post, "%*.*hX", 10, 5, 123, unsigned short)
TEST_SPRINTF_2(hX_dynamic_width_negt, "%*hX", 10, -123, unsigned short)
TEST_SPRINTF_2(hX_dynamic_prec_negt, "%.*hX", 5, -123, unsigned short)
TEST_SPRINTF_3(hX_dynamic_width_prec_negt, "%*.*hX", 10, 5, -123,
               unsigned short)
#pragma endregion

// =========================================================================
// Целочисленные типы модификатор hh (char) %hhd %hhi %hho %hhu %hhx %hhX
// =========================================================================
#pragma region
TEST_SPRINTF(hhd_mins_post, "%-hhd", 123, signed char)
TEST_SPRINTF(hhd_plus_post, "%+hhd", 123, signed char)
TEST_SPRINTF(hhd_spac_post, "% hhd", 123, signed char)
TEST_SPRINTF(hhd_fzer_post, "%0hhd", 123, signed char)
TEST_SPRINTF(hhd_mins_negt, "%-hhd", -123, signed char)
TEST_SPRINTF(hhd_plus_negt, "%+hhd", -123, signed char)
TEST_SPRINTF(hhd_spac_negt, "% hhd", -123, signed char)
TEST_SPRINTF(hhd_fzer_negt, "%0hhd", -123, signed char)

TEST_SPRINTF(hhd_width_post, "%5hhd", 123, signed char)
TEST_SPRINTF(hhd_zrpc_post, "%.0hhd", 123, signed char)
TEST_SPRINTF(hhd_prec_post, "%.5hhd", 123, signed char)
TEST_SPRINTF(hhd_width_prec_post, "%10.5hhd", 123, signed char)
TEST_SPRINTF(hhd_width_negt, "%5hhd", -123, signed char)
TEST_SPRINTF(hhd_zrpc_negt, "%.0hhd", -123, signed char)
TEST_SPRINTF(hhd_prec_negt, "%.5hhd", -123, signed char)
TEST_SPRINTF(hhd_width_prec_negt, "%10.5hhd", -123, signed char)

TEST_SPRINTF(hhd_width_mins_post, "%-5hhd", 123, signed char)
TEST_SPRINTF(hhd_width_plus_post, "%+5hhd", 123, signed char)
TEST_SPRINTF(hhd_width_spac_post, "% 5hhd", 123, signed char)
TEST_SPRINTF(hhd_width_fzer_post, "%05hhd", 123, signed char)
TEST_SPRINTF(hhd_width_mins_negt, "%-5hhd", -123, signed char)
TEST_SPRINTF(hhd_width_plus_negt, "%+5hhd", -123, signed char)
TEST_SPRINTF(hhd_width_spac_negt, "% 5hhd", -123, signed char)
TEST_SPRINTF(hhd_width_fzer_negt, "%05hhd", -123, signed char)

TEST_SPRINTF(hhd_zrwth_plus_post, "%+0hhd", 123, signed char)
TEST_SPRINTF(hhd_zrwth_spac_post, "% 0hhd", 123, signed char)
TEST_SPRINTF(hhd_zrwth_plus_negt, "%+0hhd", -123, signed char)
TEST_SPRINTF(hhd_zrwth_spac_negt, "% 0hhd", -123, signed char)

TEST_SPRINTF(hhd_prec_mins_post, "%-.5hhd", 123, signed char)
TEST_SPRINTF(hhd_prec_plus_post, "%+.5hhd", 123, signed char)
TEST_SPRINTF(hhd_prec_spac_post, "% .5hhd", 123, signed char)
TEST_SPRINTF(hhd_prec_mins_negt, "%-.5hhd", -123, signed char)
TEST_SPRINTF(hhd_prec_plus_negt, "%+.5hhd", -123, signed char)
TEST_SPRINTF(hhd_prec_spac_negt, "% .5hhd", -123, signed char)

TEST_SPRINTF(hhd_zrpc_mins_post, "%-.0hhd", 123, signed char)
TEST_SPRINTF(hhd_zrpc_plus_post, "%+.0hhd", 123, signed char)
TEST_SPRINTF(hhd_zrpc_spac_post, "% .0hhd", 123, signed char)
TEST_SPRINTF(hhd_zrpc_mins_negt, "%-.0hhd", -123, signed char)
TEST_SPRINTF(hhd_zrpc_plus_negt, "%+.0hhd", -123, signed char)
TEST_SPRINTF(hhd_zrpc_spac_negt, "% .0hhd", -123, signed char)

TEST_SPRINTF(hhd_width_prec_mins_post, "%-10.5hhd", 123, signed char)
TEST_SPRINTF(hhd_width_prec_plus_post, "%+10.5hhd", 123, signed char)
TEST_SPRINTF(hhd_width_prec_spac_post, "% 10.5hhd", 123, signed char)
TEST_SPRINTF(hhd_width_prec_mins_negt, "%-10.5hhd", -123, signed char)
TEST_SPRINTF(hhd_width_prec_plus_negt, "%+10.5hhd", -123, signed char)
TEST_SPRINTF(hhd_width_prec_spac_negt, "% 10.5hhd", -123, signed char)

TEST_SPRINTF_2(hhd_dynamic_width_post, "%*hhd", 10, 123, signed char)
TEST_SPRINTF_2(hhd_dynamic_prec_post, "%.*hhd", 5, 123, signed char)
TEST_SPRINTF_3(hhd_dynamic_width_prec_post, "%*.*hhd", 10, 5, 123, signed char)
TEST_SPRINTF_2(hhd_dynamic_width_negt, "%*hhd", 10, -123, signed char)
TEST_SPRINTF_2(hhd_dynamic_prec_negt, "%.*hhd", 5, -123, signed char)
TEST_SPRINTF_3(hhd_dynamic_width_prec_negt, "%*.*hhd", 10, 5, -123, signed char)

// =========================================================================

TEST_SPRINTF(hhi_mins_post, "%-hhi", 123, signed char)
TEST_SPRINTF(hhi_plus_post, "%+hhi", 123, signed char)
TEST_SPRINTF(hhi_spac_post, "% hhi", 123, signed char)
TEST_SPRINTF(hhi_fzer_post, "%0hhi", 123, signed char)
TEST_SPRINTF(hhi_mins_negt, "%-hhi", -123, signed char)
TEST_SPRINTF(hhi_plus_negt, "%+hhi", -123, signed char)
TEST_SPRINTF(hhi_spac_negt, "% hhi", -123, signed char)
TEST_SPRINTF(hhi_fzer_negt, "%0hhi", -123, signed char)

TEST_SPRINTF(hhi_width_post, "%5hhi", 123, signed char)
TEST_SPRINTF(hhi_zrpc_post, "%.0hhi", 123, signed char)
TEST_SPRINTF(hhi_prec_post, "%.5hhi", 123, signed char)
TEST_SPRINTF(hhi_width_prec_post, "%10.5hhi", 123, signed char)
TEST_SPRINTF(hhi_width_negt, "%5hhi", -123, signed char)
TEST_SPRINTF(hhi_zrpc_negt, "%.0hhi", -123, signed char)
TEST_SPRINTF(hhi_prec_negt, "%.5hhi", -123, signed char)
TEST_SPRINTF(hhi_width_prec_negt, "%10.5hhi", -123, signed char)

TEST_SPRINTF(hhi_width_mins_post, "%-5hhi", 123, signed char)
TEST_SPRINTF(hhi_width_plus_post, "%+5hhi", 123, signed char)
TEST_SPRINTF(hhi_width_spac_post, "% 5hhi", 123, signed char)
TEST_SPRINTF(hhi_width_fzer_post, "%05hhi", 123, signed char)
TEST_SPRINTF(hhi_width_mins_negt, "%-5hhi", -123, signed char)
TEST_SPRINTF(hhi_width_plus_negt, "%+5hhi", -123, signed char)
TEST_SPRINTF(hhi_width_spac_negt, "% 5hhi", -123, signed char)
TEST_SPRINTF(hhi_width_fzer_negt, "%05hhi", -123, signed char)

TEST_SPRINTF(hhi_zrwth_plus_post, "%+0hhi", 123, signed char)
TEST_SPRINTF(hhi_zrwth_spac_post, "% 0hhi", 123, signed char)
TEST_SPRINTF(hhi_zrwth_plus_negt, "%+0hhi", -123, signed char)
TEST_SPRINTF(hhi_zrwth_spac_negt, "% 0hhi", -123, signed char)

TEST_SPRINTF(hhi_prec_mins_post, "%-.5hhi", 123, signed char)
TEST_SPRINTF(hhi_prec_plus_post, "%+.5hhi", 123, signed char)
TEST_SPRINTF(hhi_prec_spac_post, "% .5hhi", 123, signed char)
TEST_SPRINTF(hhi_prec_mins_negt, "%-.5hhi", -123, signed char)
TEST_SPRINTF(hhi_prec_plus_negt, "%+.5hhi", -123, signed char)
TEST_SPRINTF(hhi_prec_spac_negt, "% .5hhi", -123, signed char)

TEST_SPRINTF(hhi_zrpc_mins_post, "%-.0hhi", 123, signed char)
TEST_SPRINTF(hhi_zrpc_plus_post, "%+.0hhi", 123, signed char)
TEST_SPRINTF(hhi_zrpc_spac_post, "% .0hhi", 123, signed char)
TEST_SPRINTF(hhi_zrpc_mins_negt, "%-.0hhi", -123, signed char)
TEST_SPRINTF(hhi_zrpc_plus_negt, "%+.0hhi", -123, signed char)
TEST_SPRINTF(hhi_zrpc_spac_negt, "% .0hhi", -123, signed char)

TEST_SPRINTF(hhi_width_prec_mins_post, "%-10.5hhi", 123, signed char)
TEST_SPRINTF(hhi_width_prec_plus_post, "%+10.5hhi", 123, signed char)
TEST_SPRINTF(hhi_width_prec_spac_post, "% 10.5hhi", 123, signed char)
TEST_SPRINTF(hhi_width_prec_mins_negt, "%-10.5hhi", -123, signed char)
TEST_SPRINTF(hhi_width_prec_plus_negt, "%+10.5hhi", -123, signed char)
TEST_SPRINTF(hhi_width_prec_spac_negt, "% 10.5hhi", -123, signed char)

TEST_SPRINTF_2(hhi_dynamic_width_post, "%*hhi", 10, 123, signed char)
TEST_SPRINTF_2(hhi_dynamic_prec_post, "%.*hhi", 5, 123, signed char)
TEST_SPRINTF_3(hhi_dynamic_width_prec_post, "%*.*hhi", 10, 5, 123, signed char)
TEST_SPRINTF_2(hhi_dynamic_width_negt, "%*hhi", 10, -123, signed char)
TEST_SPRINTF_2(hhi_dynamic_prec_negt, "%.*hhi", 5, -123, signed char)
TEST_SPRINTF_3(hhi_dynamic_width_prec_negt, "%*.*hhi", 10, 5, -123, signed char)

// =========================================================================

TEST_SPRINTF(hho_mins_post, "%-hho", 123, unsigned char)
TEST_SPRINTF(hho_hash_post, "%#hho", 123, unsigned char)
TEST_SPRINTF(hho_fzer_post, "%0hho", 123, unsigned char)
TEST_SPRINTF(hho_mins_negt, "%-hho", -123, unsigned char)
TEST_SPRINTF(hho_hash_negt, "%#hho", -123, unsigned char)
TEST_SPRINTF(hho_fzer_negt, "%0hho", -123, unsigned char)

TEST_SPRINTF(hho_width_post, "%5hho", 123, unsigned char)
TEST_SPRINTF(hho_zrpc_post, "%.0hho", 123, unsigned char)
TEST_SPRINTF(hho_prec_post, "%.5hho", 123, unsigned char)
TEST_SPRINTF(hho_width_prec_post, "%10.5hho", 123, unsigned char)
TEST_SPRINTF(hho_width_negt, "%5hho", -123, unsigned char)
TEST_SPRINTF(hho_zrpc_negt, "%.0hho", -123, unsigned char)
TEST_SPRINTF(hho_prec_negt, "%.5hho", -123, unsigned char)
TEST_SPRINTF(hho_width_prec_negt, "%10.5hho", -123, unsigned char)

TEST_SPRINTF(hho_width_mins_post, "%-5hho", 123, unsigned char)
TEST_SPRINTF(hho_width_hash_post, "%#5hho", 123, unsigned char)
TEST_SPRINTF(hho_width_fzer_post, "%05hho", 123, unsigned char)
TEST_SPRINTF(hho_width_mins_negt, "%-5hho", -123, unsigned char)
TEST_SPRINTF(hho_width_hash_negt, "%#5hho", -123, unsigned char)
TEST_SPRINTF(hho_width_fzer_negt, "%05hho", -123, unsigned char)

TEST_SPRINTF(hho_zrwth_hash_post, "%#0hho", 123, unsigned char)
TEST_SPRINTF(hho_zrwth_hash_negt, "%#0hho", -123, unsigned char)

TEST_SPRINTF(hho_prec_mins_post, "%-.5hho", 123, unsigned char)
TEST_SPRINTF(hho_prec_hash_post, "%#.5hho", 123, unsigned char)
TEST_SPRINTF(hho_prec_mins_negt, "%-.5hho", -123, unsigned char)
TEST_SPRINTF(hho_prec_hash_negt, "%#.5hho", -123, unsigned char)

TEST_SPRINTF(hho_zrpc_mins_post, "%-.0hho", 123, unsigned char)
TEST_SPRINTF(hho_zrpc_hash_post, "%#.0hho", 123, unsigned char)
TEST_SPRINTF(hho_zrpc_mins_negt, "%-.0hho", -123, unsigned char)
TEST_SPRINTF(hho_zrpc_hash_negt, "%#.0hho", -123, unsigned char)

TEST_SPRINTF(hho_width_prec_mins_post, "%-10.5hho", 123, unsigned char)
TEST_SPRINTF(hho_width_prec_hash_post, "%#10.5hho", 123, unsigned char)
TEST_SPRINTF(hho_width_prec_mins_negt, "%-10.5hho", -123, unsigned char)
TEST_SPRINTF(hho_width_prec_hash_negt, "%#10.5hho", -123, unsigned char)

TEST_SPRINTF_2(hho_dynamic_width_post, "%*hho", 10, 123, unsigned char)
TEST_SPRINTF_2(hho_dynamic_prec_post, "%.*hho", 5, 123, unsigned char)
TEST_SPRINTF_3(hho_dynamic_width_prec_post, "%*.*hho", 10, 5, 123,
               unsigned char)
TEST_SPRINTF_2(hho_dynamic_width_negt, "%*hho", 10, -123, unsigned char)
TEST_SPRINTF_2(hho_dynamic_prec_negt, "%.*hho", 5, -123, unsigned char)
TEST_SPRINTF_3(hho_dynamic_width_prec_negt, "%*.*hho", 10, 5, -123,
               unsigned char)

// =========================================================================

TEST_SPRINTF(hhu_mins_post, "%-hhu", 123, unsigned char)
TEST_SPRINTF(hhu_fzer_post, "%0hhu", 123, unsigned char)
TEST_SPRINTF(hhu_mins_negt, "%-hhu", -123, unsigned char)
TEST_SPRINTF(hhu_fzer_negt, "%0hhu", -123, unsigned char)

TEST_SPRINTF(hhu_width_post, "%5hhu", 123, unsigned char)
TEST_SPRINTF(hhu_zrpc_post, "%.0hhu", 123, unsigned char)
TEST_SPRINTF(hhu_prec_post, "%.5hhu", 123, unsigned char)
TEST_SPRINTF(hhu_width_prec_post, "%10.5hhu", 123, unsigned char)
TEST_SPRINTF(hhu_width_negt, "%5hhu", -123, unsigned char)
TEST_SPRINTF(hhu_zrpc_negt, "%.0hhu", -123, unsigned char)
TEST_SPRINTF(hhu_prec_negt, "%.5hhu", -123, unsigned char)
TEST_SPRINTF(hhu_width_prec_negt, "%10.5hhu", -123, unsigned char)

TEST_SPRINTF(hhu_width_mins_post, "%-5hhu", 123, unsigned char)
TEST_SPRINTF(hhu_width_fzer_post, "%05hhu", 123, unsigned char)
TEST_SPRINTF(hhu_width_mins_negt, "%-5hhu", -123, unsigned char)
TEST_SPRINTF(hhu_width_fzer_negt, "%05hhu", -123, unsigned char)

TEST_SPRINTF(hhu_prec_mins_post, "%-.5hhu", 123, unsigned char)
TEST_SPRINTF(hhu_prec_mins_negt, "%-.5hhu", -123, unsigned char)

TEST_SPRINTF(hhu_zrpc_mins_post, "%-.0hhu", 123, unsigned char)
TEST_SPRINTF(hhu_zrpc_mins_negt, "%-.0hhu", -123, unsigned char)

TEST_SPRINTF(hhu_width_prec_mins_post, "%-10.5hhu", 123, unsigned char)
TEST_SPRINTF(hhu_width_prec_mins_negt, "%-10.5hhu", -123, unsigned char)

TEST_SPRINTF_2(hhu_dynamic_width_post, "%*hhu", 10, 123, unsigned char)
TEST_SPRINTF_2(hhu_dynamic_prec_post, "%.*hhu", 5, 123, unsigned char)
TEST_SPRINTF_3(hhu_dynamic_width_prec_post, "%*.*hhu", 10, 5, 123,
               unsigned char)
TEST_SPRINTF_2(hhu_dynamic_width_negt, "%*hhu", 10, -123, unsigned char)
TEST_SPRINTF_2(hhu_dynamic_prec_negt, "%.*hhu", 5, -123, unsigned char)
TEST_SPRINTF_3(hhu_dynamic_width_prec_negt, "%*.*hhu", 10, 5, -123,
               unsigned char)

// =========================================================================

TEST_SPRINTF(hhx_mins_post, "%-hhx", 123, unsigned char)
TEST_SPRINTF(hhx_hash_post, "%#hhx", 123, unsigned char)
TEST_SPRINTF(hhx_fzer_post, "%0hhx", 123, unsigned char)
TEST_SPRINTF(hhx_mins_negt, "%-hhx", -123, unsigned char)
TEST_SPRINTF(hhx_hash_negt, "%#hhx", -123, unsigned char)
TEST_SPRINTF(hhx_fzer_negt, "%0hhx", -123, unsigned char)

TEST_SPRINTF(hhx_width_post, "%5hhx", 123, unsigned char)
TEST_SPRINTF(hhx_zrpc_post, "%.0hhx", 123, unsigned char)
TEST_SPRINTF(hhx_prec_post, "%.5hhx", 123, unsigned char)
TEST_SPRINTF(hhx_width_prec_post, "%10.5hhx", 123, unsigned char)
TEST_SPRINTF(hhx_width_negt, "%5hhx", -123, unsigned char)
TEST_SPRINTF(hhx_zrpc_negt, "%.0hhx", -123, unsigned char)
TEST_SPRINTF(hhx_prec_negt, "%.5hhx", -123, unsigned char)
TEST_SPRINTF(hhx_width_prec_negt, "%10.5hhx", -123, unsigned char)

TEST_SPRINTF(hhx_width_mins_post, "%-5hhx", 123, unsigned char)
TEST_SPRINTF(hhx_width_hash_post, "%#5hhx", 123, unsigned char)
TEST_SPRINTF(hhx_width_fzer_post, "%05hhx", 123, unsigned char)
TEST_SPRINTF(hhx_width_mins_negt, "%-5hhx", -123, unsigned char)
TEST_SPRINTF(hhx_width_hash_negt, "%#5hhx", -123, unsigned char)
TEST_SPRINTF(hhx_width_fzer_negt, "%05hhx", -123, unsigned char)

TEST_SPRINTF(hhx_zrwth_hash_post, "%#0hhx", 123, unsigned char)
TEST_SPRINTF(hhx_zrwth_hash_negt, "%#0hhx", -123, unsigned char)

TEST_SPRINTF(hhx_prec_mins_post, "%-.5hhx", 123, unsigned char)
TEST_SPRINTF(hhx_prec_hash_post, "%#.5hhx", 123, unsigned char)
TEST_SPRINTF(hhx_prec_mins_negt, "%-.5hhx", -123, unsigned char)
TEST_SPRINTF(hhx_prec_hash_negt, "%#.5hhx", -123, unsigned char)

TEST_SPRINTF(hhx_zrpc_mins_post, "%-.0hhx", 123, unsigned char)
TEST_SPRINTF(hhx_zrpc_hash_post, "%#.0hhx", 123, unsigned char)
TEST_SPRINTF(hhx_zrpc_mins_negt, "%-.0hhx", -123, unsigned char)
TEST_SPRINTF(hhx_zrpc_hash_negt, "%#.0hhx", -123, unsigned char)

TEST_SPRINTF(hhx_width_prec_mins_post, "%-10.5hhx", 123, unsigned char)
TEST_SPRINTF(hhx_width_prec_hash_post, "%#10.5hhx", 123, unsigned char)
TEST_SPRINTF(hhx_width_prec_mins_negt, "%-10.5hhx", -123, unsigned char)
TEST_SPRINTF(hhx_width_prec_hash_negt, "%#10.5hhx", -123, unsigned char)

TEST_SPRINTF_2(hhx_dynamic_width_post, "%*hhx", 10, 123, unsigned char)
TEST_SPRINTF_2(hhx_dynamic_prec_post, "%.*hhx", 5, 123, unsigned char)
TEST_SPRINTF_3(hhx_dynamic_width_prec_post, "%*.*hhx", 10, 5, 123,
               unsigned char)
TEST_SPRINTF_2(hhx_dynamic_width_negt, "%*hhx", 10, -123, unsigned char)
TEST_SPRINTF_2(hhx_dynamic_prec_negt, "%.*hhx", 5, -123, unsigned char)
TEST_SPRINTF_3(hhx_dynamic_width_prec_negt, "%*.*hhx", 10, 5, -123,
               unsigned char)

// =========================================================================

TEST_SPRINTF(hhX_mins_post, "%-hhX", 123, unsigned char)
TEST_SPRINTF(hhX_hash_post, "%#hhX", 123, unsigned char)
TEST_SPRINTF(hhX_fzer_post, "%0hhX", 123, unsigned char)
TEST_SPRINTF(hhX_mins_negt, "%-hhX", -123, unsigned char)
TEST_SPRINTF(hhX_hash_negt, "%#hhX", -123, unsigned char)
TEST_SPRINTF(hhX_fzer_negt, "%0hhX", -123, unsigned char)

TEST_SPRINTF(hhX_width_post, "%5hhX", 123, unsigned char)
TEST_SPRINTF(hhX_zrpc_post, "%.0hhX", 123, unsigned char)
TEST_SPRINTF(hhX_prec_post, "%.5hhX", 123, unsigned char)
TEST_SPRINTF(hhX_width_prec_post, "%10.5hhX", 123, unsigned char)
TEST_SPRINTF(hhX_width_negt, "%5hhX", -123, unsigned char)
TEST_SPRINTF(hhX_zrpc_negt, "%.0hhX", -123, unsigned char)
TEST_SPRINTF(hhX_prec_negt, "%.5hhX", -123, unsigned char)
TEST_SPRINTF(hhX_width_prec_negt, "%10.5hhX", -123, unsigned char)

TEST_SPRINTF(hhX_width_mins_post, "%-5hhX", 123, unsigned char)
TEST_SPRINTF(hhX_width_hash_post, "%#5hhX", 123, unsigned char)
TEST_SPRINTF(hhX_width_fzer_post, "%05hhX", 123, unsigned char)
TEST_SPRINTF(hhX_width_mins_negt, "%-5hhX", -123, unsigned char)
TEST_SPRINTF(hhX_width_hash_negt, "%#5hhX", -123, unsigned char)
TEST_SPRINTF(hhX_width_fzer_negt, "%05hhX", -123, unsigned char)

TEST_SPRINTF(hhX_zrwth_hash_post, "%#0hhX", 123, unsigned char)
TEST_SPRINTF(hhX_zrwth_hash_negt, "%#0hhX", -123, unsigned char)

TEST_SPRINTF(hhX_prec_mins_post, "%-.5hhX", 123, unsigned char)
TEST_SPRINTF(hhX_prec_hash_post, "%#.5hhX", 123, unsigned char)
TEST_SPRINTF(hhX_prec_mins_negt, "%-.5hhX", -123, unsigned char)
TEST_SPRINTF(hhX_prec_hash_negt, "%#.5hhX", -123, unsigned char)

TEST_SPRINTF(hhX_zrpc_mins_post, "%-.0hhX", 123, unsigned char)
TEST_SPRINTF(hhX_zrpc_hash_post, "%#.0hhX", 123, unsigned char)
TEST_SPRINTF(hhX_zrpc_mins_negt, "%-.0hhX", -123, unsigned char)
TEST_SPRINTF(hhX_zrpc_hash_negt, "%#.0hhX", -123, unsigned char)

TEST_SPRINTF(hhX_width_prec_mins_post, "%-10.5hhX", 123, unsigned char)
TEST_SPRINTF(hhX_width_prec_hash_post, "%#10.5hhX", 123, unsigned char)
TEST_SPRINTF(hhX_width_prec_mins_negt, "%-10.5hhX", -123, unsigned char)
TEST_SPRINTF(hhX_width_prec_hash_negt, "%#10.5hhX", -123, unsigned char)

TEST_SPRINTF_2(hhX_dynamic_width_post, "%*hhX", 10, 123, unsigned char)
TEST_SPRINTF_2(hhX_dynamic_prec_post, "%.*hhX", 5, 123, unsigned char)
TEST_SPRINTF_3(hhX_dynamic_width_prec_post, "%*.*hhX", 10, 5, 123,
               unsigned char)
TEST_SPRINTF_2(hhX_dynamic_width_negt, "%*hhX", 10, -123, unsigned char)
TEST_SPRINTF_2(hhX_dynamic_prec_negt, "%.*hhX", 5, -123, unsigned char)
TEST_SPRINTF_3(hhX_dynamic_width_prec_negt, "%*.*hhX", 10, 5, -123,
               unsigned char)
#pragma endregion

// =========================================================================
// Целочисленные типы модификатор l (long) %ld %li %lo %lu %lx %lX
// =========================================================================
#pragma region
TEST_SPRINTF(ld_mins_post, "%-ld", 123, long)
TEST_SPRINTF(ld_plus_post, "%+ld", 123, long)
TEST_SPRINTF(ld_spac_post, "% ld", 123, long)
TEST_SPRINTF(ld_fzer_post, "%0ld", 123, long)
TEST_SPRINTF(ld_mins_negt, "%-ld", -123, long)
TEST_SPRINTF(ld_plus_negt, "%+ld", -123, long)
TEST_SPRINTF(ld_spac_negt, "% ld", -123, long)
TEST_SPRINTF(ld_fzer_negt, "%0ld", -123, long)

TEST_SPRINTF(ld_width_post, "%5ld", 123, long)
TEST_SPRINTF(ld_zrpc_post, "%.0ld", 123, long)
TEST_SPRINTF(ld_prec_post, "%.5ld", 123, long)
TEST_SPRINTF(ld_width_prec_post, "%10.5ld", 123, long)
TEST_SPRINTF(ld_width_negt, "%5ld", -123, long)
TEST_SPRINTF(ld_zrpc_negt, "%.0ld", -123, long)
TEST_SPRINTF(ld_prec_negt, "%.5ld", -123, long)
TEST_SPRINTF(ld_width_prec_negt, "%10.5ld", -123, long)

TEST_SPRINTF(ld_width_mins_post, "%-5ld", 123, long)
TEST_SPRINTF(ld_width_plus_post, "%+5ld", 123, long)
TEST_SPRINTF(ld_width_spac_post, "% 5ld", 123, long)
TEST_SPRINTF(ld_width_fzer_post, "%05ld", 123, long)
TEST_SPRINTF(ld_width_mins_negt, "%-5ld", -123, long)
TEST_SPRINTF(ld_width_plus_negt, "%+5ld", -123, long)
TEST_SPRINTF(ld_width_spac_negt, "% 5ld", -123, long)
TEST_SPRINTF(ld_width_fzer_negt, "%05ld", -123, long)

TEST_SPRINTF(ld_zrwth_plus_post, "%+0ld", 123, long)
TEST_SPRINTF(ld_zrwth_spac_post, "% 0ld", 123, long)
TEST_SPRINTF(ld_zrwth_plus_negt, "%+0ld", -123, long)
TEST_SPRINTF(ld_zrwth_spac_negt, "% 0ld", -123, long)

TEST_SPRINTF(ld_prec_mins_post, "%-.5ld", 123, long)
TEST_SPRINTF(ld_prec_plus_post, "%+.5ld", 123, long)
TEST_SPRINTF(ld_prec_spac_post, "% .5ld", 123, long)
TEST_SPRINTF(ld_prec_mins_negt, "%-.5ld", -123, long)
TEST_SPRINTF(ld_prec_plus_negt, "%+.5ld", -123, long)
TEST_SPRINTF(ld_prec_spac_negt, "% .5ld", -123, long)

TEST_SPRINTF(ld_zrpc_mins_post, "%-.0ld", 123, long)
TEST_SPRINTF(ld_zrpc_plus_post, "%+.0ld", 123, long)
TEST_SPRINTF(ld_zrpc_spac_post, "% .0ld", 123, long)
TEST_SPRINTF(ld_zrpc_mins_negt, "%-.0ld", -123, long)
TEST_SPRINTF(ld_zrpc_plus_negt, "%+.0ld", -123, long)
TEST_SPRINTF(ld_zrpc_spac_negt, "% .0ld", -123, long)

TEST_SPRINTF(ld_width_prec_mins_post, "%-10.5ld", 123, long)
TEST_SPRINTF(ld_width_prec_plus_post, "%+10.5ld", 123, long)
TEST_SPRINTF(ld_width_prec_spac_post, "% 10.5ld", 123, long)
TEST_SPRINTF(ld_width_prec_mins_negt, "%-10.5ld", -123, long)
TEST_SPRINTF(ld_width_prec_plus_negt, "%+10.5ld", -123, long)
TEST_SPRINTF(ld_width_prec_spac_negt, "% 10.5ld", -123, long)

TEST_SPRINTF_2(ld_dynamic_width_post, "%*ld", 10, 123, long)
TEST_SPRINTF_2(ld_dynamic_prec_post, "%.*ld", 5, 123, long)
TEST_SPRINTF_3(ld_dynamic_width_prec_post, "%*.*ld", 10, 5, 123, long)
TEST_SPRINTF_2(ld_dynamic_width_negt, "%*ld", 10, -123, long)
TEST_SPRINTF_2(ld_dynamic_prec_negt, "%.*ld", 5, -123, long)
TEST_SPRINTF_3(ld_dynamic_width_prec_negt, "%*.*ld", 10, 5, -123, long)

// =========================================================================

TEST_SPRINTF(li_mins_post, "%-li", 123, long)
TEST_SPRINTF(li_plus_post, "%+li", 123, long)
TEST_SPRINTF(li_spac_post, "% li", 123, long)
TEST_SPRINTF(li_fzer_post, "%0li", 123, long)
TEST_SPRINTF(li_mins_negt, "%-li", -123, long)
TEST_SPRINTF(li_plus_negt, "%+li", -123, long)
TEST_SPRINTF(li_spac_negt, "% li", -123, long)
TEST_SPRINTF(li_fzer_negt, "%0li", -123, long)

TEST_SPRINTF(li_width_post, "%5li", 123, long)
TEST_SPRINTF(li_zrpc_post, "%.0li", 123, long)
TEST_SPRINTF(li_prec_post, "%.5li", 123, long)
TEST_SPRINTF(li_width_prec_post, "%10.5li", 123, long)
TEST_SPRINTF(li_width_negt, "%5li", -123, long)
TEST_SPRINTF(li_zrpc_negt, "%.0li", -123, long)
TEST_SPRINTF(li_prec_negt, "%.5li", -123, long)
TEST_SPRINTF(li_width_prec_negt, "%10.5li", -123, long)

TEST_SPRINTF(li_width_mins_post, "%-5li", 123, long)
TEST_SPRINTF(li_width_plus_post, "%+5li", 123, long)
TEST_SPRINTF(li_width_spac_post, "% 5li", 123, long)
TEST_SPRINTF(li_width_fzer_post, "%05li", 123, long)
TEST_SPRINTF(li_width_mins_negt, "%-5li", -123, long)
TEST_SPRINTF(li_width_plus_negt, "%+5li", -123, long)
TEST_SPRINTF(li_width_spac_negt, "% 5li", -123, long)
TEST_SPRINTF(li_width_fzer_negt, "%05li", -123, long)

TEST_SPRINTF(li_zrwth_plus_post, "%+0li", 123, long)
TEST_SPRINTF(li_zrwth_spac_post, "% 0li", 123, long)
TEST_SPRINTF(li_zrwth_plus_negt, "%+0li", -123, long)
TEST_SPRINTF(li_zrwth_spac_negt, "% 0li", -123, long)

TEST_SPRINTF(li_prec_mins_post, "%-.5li", 123, long)
TEST_SPRINTF(li_prec_plus_post, "%+.5li", 123, long)
TEST_SPRINTF(li_prec_spac_post, "% .5li", 123, long)
TEST_SPRINTF(li_prec_mins_negt, "%-.5li", -123, long)
TEST_SPRINTF(li_prec_plus_negt, "%+.5li", -123, long)
TEST_SPRINTF(li_prec_spac_negt, "% .5li", -123, long)

TEST_SPRINTF(li_zrpc_mins_post, "%-.0li", 123, long)
TEST_SPRINTF(li_zrpc_plus_post, "%+.0li", 123, long)
TEST_SPRINTF(li_zrpc_spac_post, "% .0li", 123, long)
TEST_SPRINTF(li_zrpc_mins_negt, "%-.0li", -123, long)
TEST_SPRINTF(li_zrpc_plus_negt, "%+.0li", -123, long)
TEST_SPRINTF(li_zrpc_spac_negt, "% .0li", -123, long)

TEST_SPRINTF(li_width_prec_mins_post, "%-10.5li", 123, long)
TEST_SPRINTF(li_width_prec_plus_post, "%+10.5li", 123, long)
TEST_SPRINTF(li_width_prec_spac_post, "% 10.5li", 123, long)
TEST_SPRINTF(li_width_prec_mins_negt, "%-10.5li", -123, long)
TEST_SPRINTF(li_width_prec_plus_negt, "%+10.5li", -123, long)
TEST_SPRINTF(li_width_prec_spac_negt, "% 10.5li", -123, long)

TEST_SPRINTF_2(li_dynamic_width_post, "%*li", 10, 123, long)
TEST_SPRINTF_2(li_dynamic_prec_post, "%.*li", 5, 123, long)
TEST_SPRINTF_3(li_dynamic_width_prec_post, "%*.*li", 10, 5, 123, long)
TEST_SPRINTF_2(li_dynamic_width_negt, "%*li", 10, -123, long)
TEST_SPRINTF_2(li_dynamic_prec_negt, "%.*li", 5, -123, long)
TEST_SPRINTF_3(li_dynamic_width_prec_negt, "%*.*li", 10, 5, -123, long)

// =========================================================================

TEST_SPRINTF(lo_mins_post, "%-lo", 123, unsigned long)
TEST_SPRINTF(lo_hash_post, "%#lo", 123, unsigned long)
TEST_SPRINTF(lo_fzer_post, "%0lo", 123, unsigned long)
TEST_SPRINTF(lo_mins_negt, "%-lo", -123, unsigned long)
TEST_SPRINTF(lo_hash_negt, "%#lo", -123, unsigned long)
TEST_SPRINTF(lo_fzer_negt, "%0lo", -123, unsigned long)

TEST_SPRINTF(lo_width_post, "%5lo", 123, unsigned long)
TEST_SPRINTF(lo_zrpc_post, "%.0lo", 123, unsigned long)
TEST_SPRINTF(lo_prec_post, "%.5lo", 123, unsigned long)
TEST_SPRINTF(lo_width_prec_post, "%10.5lo", 123, unsigned long)
TEST_SPRINTF(lo_width_negt, "%5lo", -123, unsigned long)
TEST_SPRINTF(lo_zrpc_negt, "%.0lo", -123, unsigned long)
TEST_SPRINTF(lo_prec_negt, "%.5lo", -123, unsigned long)
TEST_SPRINTF(lo_width_prec_negt, "%10.5lo", -123, unsigned long)

TEST_SPRINTF(lo_width_mins_post, "%-5lo", 123, unsigned long)
TEST_SPRINTF(lo_width_hash_post, "%#5lo", 123, unsigned long)
TEST_SPRINTF(lo_width_fzer_post, "%05lo", 123, unsigned long)
TEST_SPRINTF(lo_width_mins_negt, "%-5lo", -123, unsigned long)
TEST_SPRINTF(lo_width_hash_negt, "%#5lo", -123, unsigned long)
TEST_SPRINTF(lo_width_fzer_negt, "%05lo", -123, unsigned long)

TEST_SPRINTF(lo_zrwth_hash_post, "%#0lo", 123, unsigned long)
TEST_SPRINTF(lo_zrwth_hash_negt, "%#0lo", -123, unsigned long)

TEST_SPRINTF(lo_prec_mins_post, "%-.5lo", 123, unsigned long)
TEST_SPRINTF(lo_prec_hash_post, "%#.5lo", 123, unsigned long)
TEST_SPRINTF(lo_prec_mins_negt, "%-.5lo", -123, unsigned long)
TEST_SPRINTF(lo_prec_hash_negt, "%#.5lo", -123, unsigned long)

TEST_SPRINTF(lo_zrpc_mins_post, "%-.0lo", 123, unsigned long)
TEST_SPRINTF(lo_zrpc_hash_post, "%#.0lo", 123, unsigned long)
TEST_SPRINTF(lo_zrpc_mins_negt, "%-.0lo", -123, unsigned long)
TEST_SPRINTF(lo_zrpc_hash_negt, "%#.0lo", -123, unsigned long)

TEST_SPRINTF(lo_width_prec_mins_post, "%-10.5lo", 123, unsigned long)
TEST_SPRINTF(lo_width_prec_hash_post, "%#10.5lo", 123, unsigned long)
TEST_SPRINTF(lo_width_prec_mins_negt, "%-10.5lo", -123, unsigned long)
TEST_SPRINTF(lo_width_prec_hash_negt, "%#10.5lo", -123, unsigned long)

TEST_SPRINTF_2(lo_dynamic_width_post, "%*lo", 10, 123, unsigned long)
TEST_SPRINTF_2(lo_dynamic_prec_post, "%.*lo", 5, 123, unsigned long)
TEST_SPRINTF_3(lo_dynamic_width_prec_post, "%*.*lo", 10, 5, 123, unsigned long)
TEST_SPRINTF_2(lo_dynamic_width_negt, "%*lo", 10, -123, unsigned long)
TEST_SPRINTF_2(lo_dynamic_prec_negt, "%.*lo", 5, -123, unsigned long)
TEST_SPRINTF_3(lo_dynamic_width_prec_negt, "%*.*lo", 10, 5, -123, unsigned long)

// =========================================================================

TEST_SPRINTF(lu_mins_post, "%-lu", 123, unsigned long)
TEST_SPRINTF(lu_fzer_post, "%0lu", 123, unsigned long)
TEST_SPRINTF(lu_mins_negt, "%-lu", -123, unsigned long)
TEST_SPRINTF(lu_fzer_negt, "%0lu", -123, unsigned long)

TEST_SPRINTF(lu_width_post, "%5lu", 123, unsigned long)
TEST_SPRINTF(lu_zrpc_post, "%.0lu", 123, unsigned long)
TEST_SPRINTF(lu_prec_post, "%.5lu", 123, unsigned long)
TEST_SPRINTF(lu_width_prec_post, "%10.5lu", 123, unsigned long)
TEST_SPRINTF(lu_width_negt, "%5lu", -123, unsigned long)
TEST_SPRINTF(lu_zrpc_negt, "%.0lu", -123, unsigned long)
TEST_SPRINTF(lu_prec_negt, "%.5lu", -123, unsigned long)
TEST_SPRINTF(lu_width_prec_negt, "%10.5lu", -123, unsigned long)

TEST_SPRINTF(lu_width_mins_post, "%-5lu", 123, unsigned long)
TEST_SPRINTF(lu_width_fzer_post, "%05lu", 123, unsigned long)
TEST_SPRINTF(lu_width_mins_negt, "%-5lu", -123, unsigned long)
TEST_SPRINTF(lu_width_fzer_negt, "%05lu", -123, unsigned long)

TEST_SPRINTF(lu_prec_mins_post, "%-.5lu", 123, unsigned long)
TEST_SPRINTF(lu_prec_mins_negt, "%-.5lu", -123, unsigned long)

TEST_SPRINTF(lu_zrpc_mins_post, "%-.0lu", 123, unsigned long)
TEST_SPRINTF(lu_zrpc_mins_negt, "%-.0lu", -123, unsigned long)

TEST_SPRINTF(lu_width_prec_mins_post, "%-10.5lu", 123, unsigned long)
TEST_SPRINTF(lu_width_prec_mins_negt, "%-10.5lu", -123, unsigned long)

TEST_SPRINTF_2(lu_dynamic_width_post, "%*lu", 10, 123, unsigned long)
TEST_SPRINTF_2(lu_dynamic_prec_post, "%.*lu", 5, 123, unsigned long)
TEST_SPRINTF_3(lu_dynamic_width_prec_post, "%*.*lu", 10, 5, 123, unsigned long)
TEST_SPRINTF_2(lu_dynamic_width_negt, "%*lu", 10, -123, unsigned long)
TEST_SPRINTF_2(lu_dynamic_prec_negt, "%.*lu", 5, -123, unsigned long)
TEST_SPRINTF_3(lu_dynamic_width_prec_negt, "%*.*lu", 10, 5, -123, unsigned long)

// =========================================================================

TEST_SPRINTF(lx_mins_post, "%-lx", 123, unsigned long)
TEST_SPRINTF(lx_hash_post, "%#lx", 123, unsigned long)
TEST_SPRINTF(lx_fzer_post, "%0lx", 123, unsigned long)
TEST_SPRINTF(lx_mins_negt, "%-lx", -123, unsigned long)
TEST_SPRINTF(lx_hash_negt, "%#lx", -123, unsigned long)
TEST_SPRINTF(lx_fzer_negt, "%0lx", -123, unsigned long)

TEST_SPRINTF(lx_width_post, "%5lx", 123, unsigned long)
TEST_SPRINTF(lx_zrpc_post, "%.0lx", 123, unsigned long)
TEST_SPRINTF(lx_prec_post, "%.5lx", 123, unsigned long)
TEST_SPRINTF(lx_width_prec_post, "%10.5lx", 123, unsigned long)
TEST_SPRINTF(lx_width_negt, "%5lx", -123, unsigned long)
TEST_SPRINTF(lx_zrpc_negt, "%.0lx", -123, unsigned long)
TEST_SPRINTF(lx_prec_negt, "%.5lx", -123, unsigned long)
TEST_SPRINTF(lx_width_prec_negt, "%10.5lx", -123, unsigned long)

TEST_SPRINTF(lx_width_mins_post, "%-5lx", 123, unsigned long)
TEST_SPRINTF(lx_width_hash_post, "%#5lx", 123, unsigned long)
TEST_SPRINTF(lx_width_fzer_post, "%05lx", 123, unsigned long)
TEST_SPRINTF(lx_width_mins_negt, "%-5lx", -123, unsigned long)
TEST_SPRINTF(lx_width_hash_negt, "%#5lx", -123, unsigned long)
TEST_SPRINTF(lx_width_fzer_negt, "%05lx", -123, unsigned long)

TEST_SPRINTF(lx_zrwth_hash_post, "%#0lx", 123, unsigned long)
TEST_SPRINTF(lx_zrwth_hash_negt, "%#0lx", -123, unsigned long)

TEST_SPRINTF(lx_prec_mins_post, "%-.5lx", 123, unsigned long)
TEST_SPRINTF(lx_prec_hash_post, "%#.5lx", 123, unsigned long)
TEST_SPRINTF(lx_prec_mins_negt, "%-.5lx", -123, unsigned long)
TEST_SPRINTF(lx_prec_hash_negt, "%#.5lx", -123, unsigned long)

TEST_SPRINTF(lx_zrpc_mins_post, "%-.0lx", 123, unsigned long)
TEST_SPRINTF(lx_zrpc_hash_post, "%#.0lx", 123, unsigned long)
TEST_SPRINTF(lx_zrpc_mins_negt, "%-.0lx", -123, unsigned long)
TEST_SPRINTF(lx_zrpc_hash_negt, "%#.0lx", -123, unsigned long)

TEST_SPRINTF(lx_width_prec_mins_post, "%-10.5lx", 123, unsigned long)
TEST_SPRINTF(lx_width_prec_hash_post, "%#10.5lx", 123, unsigned long)
TEST_SPRINTF(lx_width_prec_mins_negt, "%-10.5lx", -123, unsigned long)
TEST_SPRINTF(lx_width_prec_hash_negt, "%#10.5lx", -123, unsigned long)

TEST_SPRINTF_2(lx_dynamic_width_post, "%*lx", 10, 123, unsigned long)
TEST_SPRINTF_2(lx_dynamic_prec_post, "%.*lx", 5, 123, unsigned long)
TEST_SPRINTF_3(lx_dynamic_width_prec_post, "%*.*lx", 10, 5, 123, unsigned long)
TEST_SPRINTF_2(lx_dynamic_width_negt, "%*lx", 10, -123, unsigned long)
TEST_SPRINTF_2(lx_dynamic_prec_negt, "%.*lx", 5, -123, unsigned long)
TEST_SPRINTF_3(lx_dynamic_width_prec_negt, "%*.*lx", 10, 5, -123, unsigned long)

// =========================================================================

TEST_SPRINTF(lX_mins_post, "%-lX", 123, unsigned long)
TEST_SPRINTF(lX_hash_post, "%#lX", 123, unsigned long)
TEST_SPRINTF(lX_fzer_post, "%0lX", 123, unsigned long)
TEST_SPRINTF(lX_mins_negt, "%-lX", -123, unsigned long)
TEST_SPRINTF(lX_hash_negt, "%#lX", -123, unsigned long)
TEST_SPRINTF(lX_fzer_negt, "%0lX", -123, unsigned long)

TEST_SPRINTF(lX_width_post, "%5lX", 123, unsigned long)
TEST_SPRINTF(lX_zrpc_post, "%.0lX", 123, unsigned long)
TEST_SPRINTF(lX_prec_post, "%.5lX", 123, unsigned long)
TEST_SPRINTF(lX_width_prec_post, "%10.5lX", 123, unsigned long)
TEST_SPRINTF(lX_width_negt, "%5lX", -123, unsigned long)
TEST_SPRINTF(lX_zrpc_negt, "%.0lX", -123, unsigned long)
TEST_SPRINTF(lX_prec_negt, "%.5lX", -123, unsigned long)
TEST_SPRINTF(lX_width_prec_negt, "%10.5lX", -123, unsigned long)

TEST_SPRINTF(lX_width_mins_post, "%-5lX", 123, unsigned long)
TEST_SPRINTF(lX_width_hash_post, "%#5lX", 123, unsigned long)
TEST_SPRINTF(lX_width_fzer_post, "%05lX", 123, unsigned long)
TEST_SPRINTF(lX_width_mins_negt, "%-5lX", -123, unsigned long)
TEST_SPRINTF(lX_width_hash_negt, "%#5lX", -123, unsigned long)
TEST_SPRINTF(lX_width_fzer_negt, "%05lX", -123, unsigned long)

TEST_SPRINTF(lX_zrwth_hash_post, "%#0lX", 123, unsigned long)
TEST_SPRINTF(lX_zrwth_hash_negt, "%#0lX", -123, unsigned long)

TEST_SPRINTF(lX_prec_mins_post, "%-.5lX", 123, unsigned long)
TEST_SPRINTF(lX_prec_hash_post, "%#.5lX", 123, unsigned long)
TEST_SPRINTF(lX_prec_mins_negt, "%-.5lX", -123, unsigned long)
TEST_SPRINTF(lX_prec_hash_negt, "%#.5lX", -123, unsigned long)

TEST_SPRINTF(lX_zrpc_mins_post, "%-.0lX", 123, unsigned long)
TEST_SPRINTF(lX_zrpc_hash_post, "%#.0lX", 123, unsigned long)
TEST_SPRINTF(lX_zrpc_mins_negt, "%-.0lX", -123, unsigned long)
TEST_SPRINTF(lX_zrpc_hash_negt, "%#.0lX", -123, unsigned long)

TEST_SPRINTF(lX_width_prec_mins_post, "%-10.5lX", 123, unsigned long)
TEST_SPRINTF(lX_width_prec_hash_post, "%#10.5lX", 123, unsigned long)
TEST_SPRINTF(lX_width_prec_mins_negt, "%-10.5lX", -123, unsigned long)
TEST_SPRINTF(lX_width_prec_hash_negt, "%#10.5lX", -123, unsigned long)

TEST_SPRINTF_2(lX_dynamic_width_post, "%*lX", 10, 123, unsigned long)
TEST_SPRINTF_2(lX_dynamic_prec_post, "%.*lX", 5, 123, unsigned long)
TEST_SPRINTF_3(lX_dynamic_width_prec_post, "%*.*lX", 10, 5, 123, unsigned long)
TEST_SPRINTF_2(lX_dynamic_width_negt, "%*lX", 10, -123, unsigned long)
TEST_SPRINTF_2(lX_dynamic_prec_negt, "%.*lX", 5, -123, unsigned long)
TEST_SPRINTF_3(lX_dynamic_width_prec_negt, "%*.*lX", 10, 5, -123, unsigned long)
#pragma endregion

// =========================================================================
// Целочисленные типы модификатор ll (long long) %lld %lli %llo %llu %llx %llX
// =========================================================================
#pragma region
TEST_SPRINTF(lld_mins_post, "%-lld", 123, long long)
TEST_SPRINTF(lld_plus_post, "%+lld", 123, long long)
TEST_SPRINTF(lld_spac_post, "% lld", 123, long long)
TEST_SPRINTF(lld_fzer_post, "%0lld", 123, long long)
TEST_SPRINTF(lld_mins_negt, "%-lld", -123, long long)
TEST_SPRINTF(lld_plus_negt, "%+lld", -123, long long)
TEST_SPRINTF(lld_spac_negt, "% lld", -123, long long)
TEST_SPRINTF(lld_fzer_negt, "%0lld", -123, long long)

TEST_SPRINTF(lld_width_post, "%5lld", 123, long long)
TEST_SPRINTF(lld_zrpc_post, "%.0lld", 123, long long)
TEST_SPRINTF(lld_prec_post, "%.5lld", 123, long long)
TEST_SPRINTF(lld_width_prec_post, "%10.5lld", 123, long long)
TEST_SPRINTF(lld_width_negt, "%5lld", -123, long long)
TEST_SPRINTF(lld_zrpc_negt, "%.0lld", -123, long long)
TEST_SPRINTF(lld_prec_negt, "%.5lld", -123, long long)
TEST_SPRINTF(lld_width_prec_negt, "%10.5lld", -123, long long)

TEST_SPRINTF(lld_width_mins_post, "%-5lld", 123, long long)
TEST_SPRINTF(lld_width_plus_post, "%+5lld", 123, long long)
TEST_SPRINTF(lld_width_spac_post, "% 5lld", 123, long long)
TEST_SPRINTF(lld_width_fzer_post, "%05lld", 123, long long)
TEST_SPRINTF(lld_width_mins_negt, "%-5lld", -123, long long)
TEST_SPRINTF(lld_width_plus_negt, "%+5lld", -123, long long)
TEST_SPRINTF(lld_width_spac_negt, "% 5lld", -123, long long)
TEST_SPRINTF(lld_width_fzer_negt, "%05lld", -123, long long)

TEST_SPRINTF(lld_zrwth_plus_post, "%+0lld", 123, long long)
TEST_SPRINTF(lld_zrwth_spac_post, "% 0lld", 123, long long)
TEST_SPRINTF(lld_zrwth_plus_negt, "%+0lld", -123, long long)
TEST_SPRINTF(lld_zrwth_spac_negt, "% 0lld", -123, long long)

TEST_SPRINTF(lld_prec_mins_post, "%-.5lld", 123, long long)
TEST_SPRINTF(lld_prec_plus_post, "%+.5lld", 123, long long)
TEST_SPRINTF(lld_prec_spac_post, "% .5lld", 123, long long)
TEST_SPRINTF(lld_prec_mins_negt, "%-.5lld", -123, long long)
TEST_SPRINTF(lld_prec_plus_negt, "%+.5lld", -123, long long)
TEST_SPRINTF(lld_prec_spac_negt, "% .5lld", -123, long long)

TEST_SPRINTF(lld_zrpc_mins_post, "%-.0lld", 123, long long)
TEST_SPRINTF(lld_zrpc_plus_post, "%+.0lld", 123, long long)
TEST_SPRINTF(lld_zrpc_spac_post, "% .0lld", 123, long long)
TEST_SPRINTF(lld_zrpc_mins_negt, "%-.0lld", -123, long long)
TEST_SPRINTF(lld_zrpc_plus_negt, "%+.0lld", -123, long long)
TEST_SPRINTF(lld_zrpc_spac_negt, "% .0lld", -123, long long)

TEST_SPRINTF(lld_width_prec_mins_post, "%-10.5lld", 123, long long)
TEST_SPRINTF(lld_width_prec_plus_post, "%+10.5lld", 123, long long)
TEST_SPRINTF(lld_width_prec_spac_post, "% 10.5lld", 123, long long)
TEST_SPRINTF(lld_width_prec_mins_negt, "%-10.5lld", -123, long long)
TEST_SPRINTF(lld_width_prec_plus_negt, "%+10.5lld", -123, long long)
TEST_SPRINTF(lld_width_prec_spac_negt, "% 10.5lld", -123, long long)

TEST_SPRINTF_2(lld_dynamic_width_post, "%*lld", 10, 123, long long)
TEST_SPRINTF_2(lld_dynamic_prec_post, "%.*lld", 5, 123, long long)
TEST_SPRINTF_3(lld_dynamic_width_prec_post, "%*.*lld", 10, 5, 123, long long)
TEST_SPRINTF_2(lld_dynamic_width_negt, "%*lld", 10, -123, long long)
TEST_SPRINTF_2(lld_dynamic_prec_negt, "%.*lld", 5, -123, long long)
TEST_SPRINTF_3(lld_dynamic_width_prec_negt, "%*.*lld", 10, 5, -123, long long)

// =========================================================================

TEST_SPRINTF(lli_mins_post, "%-lli", 123, long long)
TEST_SPRINTF(lli_plus_post, "%+lli", 123, long long)
TEST_SPRINTF(lli_spac_post, "% lli", 123, long long)
TEST_SPRINTF(lli_fzer_post, "%0lli", 123, long long)
TEST_SPRINTF(lli_mins_negt, "%-lli", -123, long long)
TEST_SPRINTF(lli_plus_negt, "%+lli", -123, long long)
TEST_SPRINTF(lli_spac_negt, "% lli", -123, long long)
TEST_SPRINTF(lli_fzer_negt, "%0lli", -123, long long)

TEST_SPRINTF(lli_width_post, "%5lli", 123, long long)
TEST_SPRINTF(lli_zrpc_post, "%.0lli", 123, long long)
TEST_SPRINTF(lli_prec_post, "%.5lli", 123, long long)
TEST_SPRINTF(lli_width_prec_post, "%10.5lli", 123, long long)
TEST_SPRINTF(lli_width_negt, "%5lli", -123, long long)
TEST_SPRINTF(lli_zrpc_negt, "%.0lli", -123, long long)
TEST_SPRINTF(lli_prec_negt, "%.5lli", -123, long long)
TEST_SPRINTF(lli_width_prec_negt, "%10.5lli", -123, long long)

TEST_SPRINTF(lli_width_mins_post, "%-5lli", 123, long long)
TEST_SPRINTF(lli_width_plus_post, "%+5lli", 123, long long)
TEST_SPRINTF(lli_width_spac_post, "% 5lli", 123, long long)
TEST_SPRINTF(lli_width_fzer_post, "%05lli", 123, long long)
TEST_SPRINTF(lli_width_mins_negt, "%-5lli", -123, long long)
TEST_SPRINTF(lli_width_plus_negt, "%+5lli", -123, long long)
TEST_SPRINTF(lli_width_spac_negt, "% 5lli", -123, long long)
TEST_SPRINTF(lli_width_fzer_negt, "%05lli", -123, long long)

TEST_SPRINTF(lli_zrwth_plus_post, "%+0lli", 123, long long)
TEST_SPRINTF(lli_zrwth_spac_post, "% 0lli", 123, long long)
TEST_SPRINTF(lli_zrwth_plus_negt, "%+0lli", -123, long long)
TEST_SPRINTF(lli_zrwth_spac_negt, "% 0lli", -123, long long)

TEST_SPRINTF(lli_prec_mins_post, "%-.5lli", 123, long long)
TEST_SPRINTF(lli_prec_plus_post, "%+.5lli", 123, long long)
TEST_SPRINTF(lli_prec_spac_post, "% .5lli", 123, long long)
TEST_SPRINTF(lli_prec_mins_negt, "%-.5lli", -123, long long)
TEST_SPRINTF(lli_prec_plus_negt, "%+.5lli", -123, long long)
TEST_SPRINTF(lli_prec_spac_negt, "% .5lli", -123, long long)

TEST_SPRINTF(lli_zrpc_mins_post, "%-.0lli", 123, long long)
TEST_SPRINTF(lli_zrpc_plus_post, "%+.0lli", 123, long long)
TEST_SPRINTF(lli_zrpc_spac_post, "% .0lli", 123, long long)
TEST_SPRINTF(lli_zrpc_mins_negt, "%-.0lli", -123, long long)
TEST_SPRINTF(lli_zrpc_plus_negt, "%+.0lli", -123, long long)
TEST_SPRINTF(lli_zrpc_spac_negt, "% .0lli", -123, long long)

TEST_SPRINTF(lli_width_prec_mins_post, "%-10.5lli", 123, long long)
TEST_SPRINTF(lli_width_prec_plus_post, "%+10.5lli", 123, long long)
TEST_SPRINTF(lli_width_prec_spac_post, "% 10.5lli", 123, long long)
TEST_SPRINTF(lli_width_prec_mins_negt, "%-10.5lli", -123, long long)
TEST_SPRINTF(lli_width_prec_plus_negt, "%+10.5lli", -123, long long)
TEST_SPRINTF(lli_width_prec_spac_negt, "% 10.5lli", -123, long long)

TEST_SPRINTF_2(lli_dynamic_width_post, "%*lli", 10, 123, long long)
TEST_SPRINTF_2(lli_dynamic_prec_post, "%.*lli", 5, 123, long long)
TEST_SPRINTF_3(lli_dynamic_width_prec_post, "%*.*lli", 10, 5, 123, long long)
TEST_SPRINTF_2(lli_dynamic_width_negt, "%*lli", 10, -123, long long)
TEST_SPRINTF_2(lli_dynamic_prec_negt, "%.*lli", 5, -123, long long)
TEST_SPRINTF_3(lli_dynamic_width_prec_negt, "%*.*lli", 10, 5, -123, long long)

// =========================================================================

TEST_SPRINTF(llo_mins_post, "%-llo", 123, unsigned long long)
TEST_SPRINTF(llo_hash_post, "%#llo", 123, unsigned long long)
TEST_SPRINTF(llo_fzer_post, "%0llo", 123, unsigned long long)
TEST_SPRINTF(llo_mins_negt, "%-llo", -123, unsigned long long)
TEST_SPRINTF(llo_hash_negt, "%#llo", -123, unsigned long long)
TEST_SPRINTF(llo_fzer_negt, "%0llo", -123, unsigned long long)

TEST_SPRINTF(llo_width_post, "%5llo", 123, unsigned long long)
TEST_SPRINTF(llo_zrpc_post, "%.0llo", 123, unsigned long long)
TEST_SPRINTF(llo_prec_post, "%.5llo", 123, unsigned long long)
TEST_SPRINTF(llo_width_prec_post, "%10.5llo", 123, unsigned long long)
TEST_SPRINTF(llo_width_negt, "%5llo", -123, unsigned long long)
TEST_SPRINTF(llo_zrpc_negt, "%.0llo", -123, unsigned long long)
TEST_SPRINTF(llo_prec_negt, "%.5llo", -123, unsigned long long)
TEST_SPRINTF(llo_width_prec_negt, "%10.5llo", -123, unsigned long long)

TEST_SPRINTF(llo_width_mins_post, "%-5llo", 123, unsigned long long)
TEST_SPRINTF(llo_width_hash_post, "%#5llo", 123, unsigned long long)
TEST_SPRINTF(llo_width_fzer_post, "%05llo", 123, unsigned long long)
TEST_SPRINTF(llo_width_mins_negt, "%-5llo", -123, unsigned long long)
TEST_SPRINTF(llo_width_hash_negt, "%#5llo", -123, unsigned long long)
TEST_SPRINTF(llo_width_fzer_negt, "%05llo", -123, unsigned long long)

TEST_SPRINTF(llo_zrwth_hash_post, "%#0llo", 123, unsigned long long)
TEST_SPRINTF(llo_zrwth_hash_negt, "%#0llo", -123, unsigned long long)

TEST_SPRINTF(llo_prec_mins_post, "%-.5llo", 123, unsigned long long)
TEST_SPRINTF(llo_prec_hash_post, "%#.5llo", 123, unsigned long long)
TEST_SPRINTF(llo_prec_mins_negt, "%-.5llo", -123, unsigned long long)
TEST_SPRINTF(llo_prec_hash_negt, "%#.5llo", -123, unsigned long long)

TEST_SPRINTF(llo_zrpc_mins_post, "%-.0llo", 123, unsigned long long)
TEST_SPRINTF(llo_zrpc_hash_post, "%#.0llo", 123, unsigned long long)
TEST_SPRINTF(llo_zrpc_mins_negt, "%-.0llo", -123, unsigned long long)
TEST_SPRINTF(llo_zrpc_hash_negt, "%#.0llo", -123, unsigned long long)

TEST_SPRINTF(llo_width_prec_mins_post, "%-10.5llo", 123, unsigned long long)
TEST_SPRINTF(llo_width_prec_hash_post, "%#10.5llo", 123, unsigned long long)
TEST_SPRINTF(llo_width_prec_mins_negt, "%-10.5llo", -123, unsigned long long)
TEST_SPRINTF(llo_width_prec_hash_negt, "%#10.5llo", -123, unsigned long long)

TEST_SPRINTF_2(llo_dynamic_width_post, "%*llo", 10, 123, unsigned long long)
TEST_SPRINTF_2(llo_dynamic_prec_post, "%.*llo", 5, 123, unsigned long long)
TEST_SPRINTF_3(llo_dynamic_width_prec_post, "%*.*llo", 10, 5, 123,
               unsigned long long)
TEST_SPRINTF_2(llo_dynamic_width_negt, "%*llo", 10, -123, unsigned long long)
TEST_SPRINTF_2(llo_dynamic_prec_negt, "%.*llo", 5, -123, unsigned long long)
TEST_SPRINTF_3(llo_dynamic_width_prec_negt, "%*.*llo", 10, 5, -123,
               unsigned long long)

// =========================================================================

TEST_SPRINTF(llu_mins_post, "%-llu", 123, unsigned long long)
TEST_SPRINTF(llu_fzer_post, "%0llu", 123, unsigned long long)
TEST_SPRINTF(llu_mins_negt, "%-llu", -123, unsigned long long)
TEST_SPRINTF(llu_fzer_negt, "%0llu", -123, unsigned long long)

TEST_SPRINTF(llu_width_post, "%5llu", 123, unsigned long long)
TEST_SPRINTF(llu_zrpc_post, "%.0llu", 123, unsigned long long)
TEST_SPRINTF(llu_prec_post, "%.5llu", 123, unsigned long long)
TEST_SPRINTF(llu_width_prec_post, "%10.5llu", 123, unsigned long long)
TEST_SPRINTF(llu_width_negt, "%5llu", -123, unsigned long long)
TEST_SPRINTF(llu_zrpc_negt, "%.0llu", -123, unsigned long long)
TEST_SPRINTF(llu_prec_negt, "%.5llu", -123, unsigned long long)
TEST_SPRINTF(llu_width_prec_negt, "%10.5llu", -123, unsigned long long)

TEST_SPRINTF(llu_width_mins_post, "%-5llu", 123, unsigned long long)
TEST_SPRINTF(llu_width_fzer_post, "%05llu", 123, unsigned long long)
TEST_SPRINTF(llu_width_mins_negt, "%-5llu", -123, unsigned long long)
TEST_SPRINTF(llu_width_fzer_negt, "%05llu", -123, unsigned long long)

TEST_SPRINTF(llu_prec_mins_post, "%-.5llu", 123, unsigned long long)
TEST_SPRINTF(llu_prec_mins_negt, "%-.5llu", -123, unsigned long long)

TEST_SPRINTF(llu_zrpc_mins_post, "%-.0llu", 123, unsigned long long)
TEST_SPRINTF(llu_zrpc_mins_negt, "%-.0llu", -123, unsigned long long)

TEST_SPRINTF(llu_width_prec_mins_post, "%-10.5llu", 123, unsigned long long)
TEST_SPRINTF(llu_width_prec_mins_negt, "%-10.5llu", -123, unsigned long long)

TEST_SPRINTF_2(llu_dynamic_width_post, "%*llu", 10, 123, unsigned long long)
TEST_SPRINTF_2(llu_dynamic_prec_post, "%.*llu", 5, 123, unsigned long long)
TEST_SPRINTF_3(llu_dynamic_width_prec_post, "%*.*llu", 10, 5, 123,
               unsigned long long)
TEST_SPRINTF_2(llu_dynamic_width_negt, "%*llu", 10, -123, unsigned long long)
TEST_SPRINTF_2(llu_dynamic_prec_negt, "%.*llu", 5, -123, unsigned long long)
TEST_SPRINTF_3(llu_dynamic_width_prec_negt, "%*.*llu", 10, 5, -123,
               unsigned long long)

// =========================================================================

TEST_SPRINTF(llx_mins_post, "%-llx", 123, unsigned long long)
TEST_SPRINTF(llx_hash_post, "%#llx", 123, unsigned long long)
TEST_SPRINTF(llx_fzer_post, "%0llx", 123, unsigned long long)
TEST_SPRINTF(llx_mins_negt, "%-llx", -123, unsigned long long)
TEST_SPRINTF(llx_hash_negt, "%#llx", -123, unsigned long long)
TEST_SPRINTF(llx_fzer_negt, "%0llx", -123, unsigned long long)

TEST_SPRINTF(llx_width_post, "%5llx", 123, unsigned long long)
TEST_SPRINTF(llx_zrpc_post, "%.0llx", 123, unsigned long long)
TEST_SPRINTF(llx_prec_post, "%.5llx", 123, unsigned long long)
TEST_SPRINTF(llx_width_prec_post, "%10.5llx", 123, unsigned long long)
TEST_SPRINTF(llx_width_negt, "%5llx", -123, unsigned long long)
TEST_SPRINTF(llx_zrpc_negt, "%.0llx", -123, unsigned long long)
TEST_SPRINTF(llx_prec_negt, "%.5llx", -123, unsigned long long)
TEST_SPRINTF(llx_width_prec_negt, "%10.5llx", -123, unsigned long long)

TEST_SPRINTF(llx_width_mins_post, "%-5llx", 123, unsigned long long)
TEST_SPRINTF(llx_width_hash_post, "%#5llx", 123, unsigned long long)
TEST_SPRINTF(llx_width_fzer_post, "%05llx", 123, unsigned long long)
TEST_SPRINTF(llx_width_mins_negt, "%-5llx", -123, unsigned long long)
TEST_SPRINTF(llx_width_hash_negt, "%#5llx", -123, unsigned long long)
TEST_SPRINTF(llx_width_fzer_negt, "%05llx", -123, unsigned long long)

TEST_SPRINTF(llx_zrwth_hash_post, "%#0llx", 123, unsigned long long)
TEST_SPRINTF(llx_zrwth_hash_negt, "%#0llx", -123, unsigned long long)

TEST_SPRINTF(llx_prec_mins_post, "%-.5llx", 123, unsigned long long)
TEST_SPRINTF(llx_prec_hash_post, "%#.5llx", 123, unsigned long long)
TEST_SPRINTF(llx_prec_mins_negt, "%-.5llx", -123, unsigned long long)
TEST_SPRINTF(llx_prec_hash_negt, "%#.5llx", -123, unsigned long long)

TEST_SPRINTF(llx_zrpc_mins_post, "%-.0llx", 123, unsigned long long)
TEST_SPRINTF(llx_zrpc_hash_post, "%#.0llx", 123, unsigned long long)
TEST_SPRINTF(llx_zrpc_mins_negt, "%-.0llx", -123, unsigned long long)
TEST_SPRINTF(llx_zrpc_hash_negt, "%#.0llx", -123, unsigned long long)

TEST_SPRINTF(llx_width_prec_mins_post, "%-10.5llx", 123, unsigned long long)
TEST_SPRINTF(llx_width_prec_hash_post, "%#10.5llx", 123, unsigned long long)
TEST_SPRINTF(llx_width_prec_mins_negt, "%-10.5llx", -123, unsigned long long)
TEST_SPRINTF(llx_width_prec_hash_negt, "%#10.5llx", -123, unsigned long long)

TEST_SPRINTF_2(llx_dynamic_width_post, "%*llx", 10, 123, unsigned long long)
TEST_SPRINTF_2(llx_dynamic_prec_post, "%.*llx", 5, 123, unsigned long long)
TEST_SPRINTF_3(llx_dynamic_width_prec_post, "%*.*llx", 10, 5, 123,
               unsigned long long)
TEST_SPRINTF_2(llx_dynamic_width_negt, "%*llx", 10, -123, unsigned long long)
TEST_SPRINTF_2(llx_dynamic_prec_negt, "%.*llx", 5, -123, unsigned long long)
TEST_SPRINTF_3(llx_dynamic_width_prec_negt, "%*.*llx", 10, 5, -123,
               unsigned long long)

// =========================================================================

TEST_SPRINTF(llX_mins_post, "%-llX", 123, unsigned long long)
TEST_SPRINTF(llX_hash_post, "%#llX", 123, unsigned long long)
TEST_SPRINTF(llX_fzer_post, "%0llX", 123, unsigned long long)
TEST_SPRINTF(llX_mins_negt, "%-llX", -123, unsigned long long)
TEST_SPRINTF(llX_hash_negt, "%#llX", -123, unsigned long long)
TEST_SPRINTF(llX_fzer_negt, "%0llX", -123, unsigned long long)

TEST_SPRINTF(llX_width_post, "%5llX", 123, unsigned long long)
TEST_SPRINTF(llX_zrpc_post, "%.0llX", 123, unsigned long long)
TEST_SPRINTF(llX_prec_post, "%.5llX", 123, unsigned long long)
TEST_SPRINTF(llX_width_prec_post, "%10.5llX", 123, unsigned long long)
TEST_SPRINTF(llX_width_negt, "%5llX", -123, unsigned long long)
TEST_SPRINTF(llX_zrpc_negt, "%.0llX", -123, unsigned long long)
TEST_SPRINTF(llX_prec_negt, "%.5llX", -123, unsigned long long)
TEST_SPRINTF(llX_width_prec_negt, "%10.5llX", -123, unsigned long long)

TEST_SPRINTF(llX_width_mins_post, "%-5llX", 123, unsigned long long)
TEST_SPRINTF(llX_width_hash_post, "%#5llX", 123, unsigned long long)
TEST_SPRINTF(llX_width_fzer_post, "%05llX", 123, unsigned long long)
TEST_SPRINTF(llX_width_mins_negt, "%-5llX", -123, unsigned long long)
TEST_SPRINTF(llX_width_hash_negt, "%#5llX", -123, unsigned long long)
TEST_SPRINTF(llX_width_fzer_negt, "%05llX", -123, unsigned long long)

TEST_SPRINTF(llX_zrwth_hash_post, "%#0llX", 123, unsigned long long)
TEST_SPRINTF(llX_zrwth_hash_negt, "%#0llX", -123, unsigned long long)

TEST_SPRINTF(llX_prec_mins_post, "%-.5llX", 123, unsigned long long)
TEST_SPRINTF(llX_prec_hash_post, "%#.5llX", 123, unsigned long long)
TEST_SPRINTF(llX_prec_mins_negt, "%-.5llX", -123, unsigned long long)
TEST_SPRINTF(llX_prec_hash_negt, "%#.5llX", -123, unsigned long long)

TEST_SPRINTF(llX_zrpc_mins_post, "%-.0llX", 123, unsigned long long)
TEST_SPRINTF(llX_zrpc_hash_post, "%#.0llX", 123, unsigned long long)
TEST_SPRINTF(llX_zrpc_mins_negt, "%-.0llX", -123, unsigned long long)
TEST_SPRINTF(llX_zrpc_hash_negt, "%#.0llX", -123, unsigned long long)

TEST_SPRINTF(llX_width_prec_mins_post, "%-10.5llX", 123, unsigned long long)
TEST_SPRINTF(llX_width_prec_hash_post, "%#10.5llX", 123, unsigned long long)
TEST_SPRINTF(llX_width_prec_mins_negt, "%-10.5llX", -123, unsigned long long)
TEST_SPRINTF(llX_width_prec_hash_negt, "%#10.5llX", -123, unsigned long long)

TEST_SPRINTF_2(llX_dynamic_width_post, "%*llX", 10, 123, unsigned long long)
TEST_SPRINTF_2(llX_dynamic_prec_post, "%.*llX", 5, 123, unsigned long long)
TEST_SPRINTF_3(llX_dynamic_width_prec_post, "%*.*llX", 10, 5, 123,
               unsigned long long)
TEST_SPRINTF_2(llX_dynamic_width_negt, "%*llX", 10, -123, unsigned long long)
TEST_SPRINTF_2(llX_dynamic_prec_negt, "%.*llX", 5, -123, unsigned long long)
TEST_SPRINTF_3(llX_dynamic_width_prec_negt, "%*.*llX", 10, 5, -123,
               unsigned long long)
#pragma endregion

// =========================================================================
// Вещественные типы: NaN и INFINITY
// =========================================================================
#pragma region
TEST_SPRINTF(e_mins_nan, "%-e", NAN, double)
TEST_SPRINTF(e_plus_nan, "%+e", NAN, double)
TEST_SPRINTF(e_spac_nan, "% e", NAN, double)
TEST_SPRINTF(e_hash_nan, "%#e", NAN, double)
TEST_SPRINTF(e_fzer_nan, "%0e", NAN, double)
TEST_SPRINTF(e_mins_inf, "%-e", INFINITY, double)
TEST_SPRINTF(e_plus_inf, "%+e", INFINITY, double)
TEST_SPRINTF(e_spac_inf, "% e", INFINITY, double)
TEST_SPRINTF(e_hash_inf, "%#e", INFINITY, double)
TEST_SPRINTF(e_fzer_inf, "%0e", INFINITY, double)
TEST_SPRINTF(e_mins_ng_inf, "%-e", -INFINITY, double)
TEST_SPRINTF(e_plus_ng_inf, "%+e", -INFINITY, double)
TEST_SPRINTF(e_spac_ng_inf, "% e", -INFINITY, double)
TEST_SPRINTF(e_hash_ng_inf, "%#e", -INFINITY, double)
TEST_SPRINTF(e_fzer_ng_inf, "%0e", -INFINITY, double)

TEST_SPRINTF(e_width_nan, "%5e", NAN, double)
TEST_SPRINTF(e_zrpc_nan, "%.0e", NAN, double)
TEST_SPRINTF(e_prec_nan, "%.5e", NAN, double)
TEST_SPRINTF(e_width_inf, "%5e", INFINITY, double)
TEST_SPRINTF(e_zrpc_inf, "%.0e", INFINITY, double)
TEST_SPRINTF(e_prec_inf, "%.5e", INFINITY, double)
TEST_SPRINTF(e_width_ng_inf, "%5e", -INFINITY, double)
TEST_SPRINTF(e_zrpc_ng_inf, "%.0e", -INFINITY, double)
TEST_SPRINTF(e_prec_ng_inf, "%.5e", -INFINITY, double)

TEST_SPRINTF(e_width_prec_nan, "%10.5e", NAN, double)
TEST_SPRINTF(e_width_prec_inf, "%10.5e", INFINITY, double)
TEST_SPRINTF(e_width_prec_ng_inf, "%10.5e", -INFINITY, double)

TEST_SPRINTF(e_width_mins_nan, "%-5e", NAN, double)
TEST_SPRINTF(e_width_plus_nan, "%+5e", NAN, double)
TEST_SPRINTF(e_width_spac_nan, "% 5e", NAN, double)
TEST_SPRINTF(e_width_hash_nan, "%#5e", NAN, double)
TEST_SPRINTF(e_width_fzer_nan, "%05e", NAN, double)
TEST_SPRINTF(e_width_mins_inf, "%-5e", INFINITY, double)
TEST_SPRINTF(e_width_plus_inf, "%+5e", INFINITY, double)
TEST_SPRINTF(e_width_spac_inf, "% 5e", INFINITY, double)
TEST_SPRINTF(e_width_hash_inf, "%#5e", INFINITY, double)
TEST_SPRINTF(e_width_fzer_inf, "%05e", INFINITY, double)
TEST_SPRINTF(e_width_mins_ng_inf, "%-5e", -INFINITY, double)
TEST_SPRINTF(e_width_plus_ng_inf, "%+5e", -INFINITY, double)
TEST_SPRINTF(e_width_spac_ng_inf, "% 5e", -INFINITY, double)
TEST_SPRINTF(e_width_hash_ng_inf, "%#5e", -INFINITY, double)
TEST_SPRINTF(e_width_fzer_ng_inf, "%05e", -INFINITY, double)

TEST_SPRINTF(e_zrwth_plus_nan, "%+0e", NAN, double)
TEST_SPRINTF(e_zrwth_spac_nan, "% 0e", NAN, double)
TEST_SPRINTF(e_zrwth_hash_nan, "%#0e", NAN, double)
TEST_SPRINTF(e_zrwth_plus_inf, "%+0e", INFINITY, double)
TEST_SPRINTF(e_zrwth_spac_inf, "% 0e", INFINITY, double)
TEST_SPRINTF(e_zrwth_hash_inf, "%#0e", INFINITY, double)
TEST_SPRINTF(e_zrwth_plus_ng_inf, "%+0e", -INFINITY, double)
TEST_SPRINTF(e_zrwth_spac_ng_inf, "% 0e", -INFINITY, double)
TEST_SPRINTF(e_zrwth_hash_ng_inf, "%#0e", -INFINITY, double)

TEST_SPRINTF(e_prec_mins_nan, "%-.5e", NAN, double)
TEST_SPRINTF(e_prec_plus_nan, "%+.5e", NAN, double)
TEST_SPRINTF(e_prec_spac_nan, "% .5e", NAN, double)
TEST_SPRINTF(e_prec_hash_nan, "%#.5e", NAN, double)
TEST_SPRINTF(e_prec_fzer_nan, "%0.5e", NAN, double)
TEST_SPRINTF(e_prec_mins_inf, "%-.5e", INFINITY, double)
TEST_SPRINTF(e_prec_plus_inf, "%+.5e", INFINITY, double)
TEST_SPRINTF(e_prec_spac_inf, "% .5e", INFINITY, double)
TEST_SPRINTF(e_prec_hash_inf, "%#.5e", INFINITY, double)
TEST_SPRINTF(e_prec_fzer_inf, "%0.5e", INFINITY, double)
TEST_SPRINTF(e_prec_mins_ng_inf, "%-.5e", -INFINITY, double)
TEST_SPRINTF(e_prec_plus_ng_inf, "%+.5e", -INFINITY, double)
TEST_SPRINTF(e_prec_spac_ng_inf, "% .5e", -INFINITY, double)
TEST_SPRINTF(e_prec_hash_ng_inf, "%#.5e", -INFINITY, double)
TEST_SPRINTF(e_prec_fzer_ng_inf, "%0.5e", -INFINITY, double)

TEST_SPRINTF(e_zrpc_mins_nan, "%-.0e", NAN, double)
TEST_SPRINTF(e_zrpc_plus_nan, "%+.0e", NAN, double)
TEST_SPRINTF(e_zrpc_spac_nan, "% .0e", NAN, double)
TEST_SPRINTF(e_zrpc_hash_nan, "%#.0e", NAN, double)
TEST_SPRINTF(e_zrpc_fzer_nan, "%0.0e", NAN, double)
TEST_SPRINTF(e_zrpc_mins_inf, "%-.0e", INFINITY, double)
TEST_SPRINTF(e_zrpc_plus_inf, "%+.0e", INFINITY, double)
TEST_SPRINTF(e_zrpc_spac_inf, "% .0e", INFINITY, double)
TEST_SPRINTF(e_zrpc_hash_inf, "%#.0e", INFINITY, double)
TEST_SPRINTF(e_zrpc_fzer_inf, "%0.0e", INFINITY, double)
TEST_SPRINTF(e_zrpc_mins_ng_inf, "%-.0e", -INFINITY, double)
TEST_SPRINTF(e_zrpc_plus_ng_inf, "%+.0e", -INFINITY, double)
TEST_SPRINTF(e_zrpc_spac_ng_inf, "% .0e", -INFINITY, double)
TEST_SPRINTF(e_zrpc_hash_ng_inf, "%#.0e", -INFINITY, double)
TEST_SPRINTF(e_zrpc_fzer_ng_inf, "%0.0e", -INFINITY, double)

TEST_SPRINTF(e_width_prec_mins_nan, "%-10.5e", NAN, double)
TEST_SPRINTF(e_width_prec_plus_nan, "%+10.5e", NAN, double)
TEST_SPRINTF(e_width_prec_spac_nan, "% 10.5e", NAN, double)
TEST_SPRINTF(e_width_prec_hash_nan, "%#10.5e", NAN, double)
TEST_SPRINTF(e_width_prec_fzer_nan, "%010.5e", NAN, double)
TEST_SPRINTF(e_width_prec_mins_inf, "%-10.5e", INFINITY, double)
TEST_SPRINTF(e_width_prec_plus_inf, "%+10.5e", INFINITY, double)
TEST_SPRINTF(e_width_prec_spac_inf, "% 10.5e", INFINITY, double)
TEST_SPRINTF(e_width_prec_hash_inf, "%#10.5e", INFINITY, double)
TEST_SPRINTF(e_width_prec_fzer_inf, "%010.5e", INFINITY, double)
TEST_SPRINTF(e_width_prec_mins_ng_inf, "%-10.5e", -INFINITY, double)
TEST_SPRINTF(e_width_prec_plus_ng_inf, "%+10.5e", -INFINITY, double)
TEST_SPRINTF(e_width_prec_spac_ng_inf, "% 10.5e", -INFINITY, double)
TEST_SPRINTF(e_width_prec_hash_ng_inf, "%#10.5e", -INFINITY, double)
TEST_SPRINTF(e_width_prec_fzer_ng_inf, "%010.5e", -INFINITY, double)

TEST_SPRINTF(e_zrwth_zrpc_plus_nan, "%+0.0e", NAN, double)
TEST_SPRINTF(e_zrwth_zrpc_spac_nan, "% 0.0e", NAN, double)
TEST_SPRINTF(e_zrwth_zrpc_hash_nan, "%#0.0e", NAN, double)
TEST_SPRINTF(e_zrwth_zrpc_plus_inf, "%+0.0e", INFINITY, double)
TEST_SPRINTF(e_zrwth_zrpc_spac_inf, "% 0.0e", INFINITY, double)
TEST_SPRINTF(e_zrwth_zrpc_hash_inf, "%#0.0e", INFINITY, double)
TEST_SPRINTF(e_zrwth_zrpc_plus_ng_inf, "%+0.0e", -INFINITY, double)
TEST_SPRINTF(e_zrwth_zrpc_spac_ng_inf, "% 0.0e", -INFINITY, double)
TEST_SPRINTF(e_zrwth_zrpc_hash_ng_inf, "%#0.0e", -INFINITY, double)

TEST_SPRINTF_2(e_dynamic_prec_nan, "%.*e", 5, NAN, double)
TEST_SPRINTF_2(e_dynamic_prec_inf, "%.*e", 5, INFINITY, double)
TEST_SPRINTF_2(e_dynamic_prec_ng_inf, "%.*e", 5, -INFINITY, double)

TEST_SPRINTF_2(e_dynamic_width_nan, "%*e", 10, NAN, double)
TEST_SPRINTF_2(e_dynamic_width_inf, "%*e", 10, INFINITY, double)
TEST_SPRINTF_2(e_dynamic_width_ng_inf, "%*e", 10, -INFINITY, double)

TEST_SPRINTF_3(e_dynamic_width_prec_nan, "%*.*e", 10, 5, NAN, double)
TEST_SPRINTF_3(e_dynamic_width_prec_inf, "%*.*e", 10, 5, INFINITY, double)
TEST_SPRINTF_3(e_dynamic_width_prec_ng_inf, "%*.*e", 10, 5, -INFINITY, double)

// =========================================================================

TEST_SPRINTF(E_mins_nan, "%-E", NAN, double)
TEST_SPRINTF(E_plus_nan, "%+E", NAN, double)
TEST_SPRINTF(E_spac_nan, "% E", NAN, double)
TEST_SPRINTF(E_hash_nan, "%#E", NAN, double)
TEST_SPRINTF(E_fzer_nan, "%0E", NAN, double)
TEST_SPRINTF(E_mins_inf, "%-E", INFINITY, double)
TEST_SPRINTF(E_plus_inf, "%+E", INFINITY, double)
TEST_SPRINTF(E_spac_inf, "% E", INFINITY, double)
TEST_SPRINTF(E_hash_inf, "%#E", INFINITY, double)
TEST_SPRINTF(E_fzer_inf, "%0E", INFINITY, double)
TEST_SPRINTF(E_mins_ng_inf, "%-E", -INFINITY, double)
TEST_SPRINTF(E_plus_ng_inf, "%+E", -INFINITY, double)
TEST_SPRINTF(E_spac_ng_inf, "% E", -INFINITY, double)
TEST_SPRINTF(E_hash_ng_inf, "%#E", -INFINITY, double)
TEST_SPRINTF(E_fzer_ng_inf, "%0E", -INFINITY, double)

TEST_SPRINTF(E_width_nan, "%5E", NAN, double)
TEST_SPRINTF(E_zrpc_nan, "%.0E", NAN, double)
TEST_SPRINTF(E_prec_nan, "%.5E", NAN, double)
TEST_SPRINTF(E_width_inf, "%5E", INFINITY, double)
TEST_SPRINTF(E_zrpc_inf, "%.0E", INFINITY, double)
TEST_SPRINTF(E_prec_inf, "%.5E", INFINITY, double)
TEST_SPRINTF(E_width_ng_inf, "%5E", -INFINITY, double)
TEST_SPRINTF(E_zrpc_ng_inf, "%.0E", -INFINITY, double)
TEST_SPRINTF(E_prec_ng_inf, "%.5E", -INFINITY, double)

TEST_SPRINTF(E_width_prec_nan, "%10.5E", NAN, double)
TEST_SPRINTF(E_width_prec_inf, "%10.5E", INFINITY, double)
TEST_SPRINTF(E_width_prec_ng_inf, "%10.5E", -INFINITY, double)

TEST_SPRINTF(E_width_mins_nan, "%-5E", NAN, double)
TEST_SPRINTF(E_width_plus_nan, "%+5E", NAN, double)
TEST_SPRINTF(E_width_spac_nan, "% 5E", NAN, double)
TEST_SPRINTF(E_width_hash_nan, "%#5E", NAN, double)
TEST_SPRINTF(E_width_fzer_nan, "%05E", NAN, double)
TEST_SPRINTF(E_width_mins_inf, "%-5E", INFINITY, double)
TEST_SPRINTF(E_width_plus_inf, "%+5E", INFINITY, double)
TEST_SPRINTF(E_width_spac_inf, "% 5E", INFINITY, double)
TEST_SPRINTF(E_width_hash_inf, "%#5E", INFINITY, double)
TEST_SPRINTF(E_width_fzer_inf, "%05E", INFINITY, double)
TEST_SPRINTF(E_width_mins_ng_inf, "%-5E", -INFINITY, double)
TEST_SPRINTF(E_width_plus_ng_inf, "%+5E", -INFINITY, double)
TEST_SPRINTF(E_width_spac_ng_inf, "% 5E", -INFINITY, double)
TEST_SPRINTF(E_width_hash_ng_inf, "%#5E", -INFINITY, double)
TEST_SPRINTF(E_width_fzer_ng_inf, "%05E", -INFINITY, double)

TEST_SPRINTF(E_zrwth_plus_nan, "%+0E", NAN, double)
TEST_SPRINTF(E_zrwth_spac_nan, "% 0E", NAN, double)
TEST_SPRINTF(E_zrwth_hash_nan, "%#0E", NAN, double)
TEST_SPRINTF(E_zrwth_plus_inf, "%+0E", INFINITY, double)
TEST_SPRINTF(E_zrwth_spac_inf, "% 0E", INFINITY, double)
TEST_SPRINTF(E_zrwth_hash_inf, "%#0E", INFINITY, double)
TEST_SPRINTF(E_zrwth_plus_ng_inf, "%+0E", -INFINITY, double)
TEST_SPRINTF(E_zrwth_spac_ng_inf, "% 0E", -INFINITY, double)
TEST_SPRINTF(E_zrwth_hash_ng_inf, "%#0E", -INFINITY, double)

TEST_SPRINTF(E_prec_mins_nan, "%-.5E", NAN, double)
TEST_SPRINTF(E_prec_plus_nan, "%+.5E", NAN, double)
TEST_SPRINTF(E_prec_spac_nan, "% .5E", NAN, double)
TEST_SPRINTF(E_prec_hash_nan, "%#.5E", NAN, double)
TEST_SPRINTF(E_prec_fzer_nan, "%0.5E", NAN, double)
TEST_SPRINTF(E_prec_mins_inf, "%-.5E", INFINITY, double)
TEST_SPRINTF(E_prec_plus_inf, "%+.5E", INFINITY, double)
TEST_SPRINTF(E_prec_spac_inf, "% .5E", INFINITY, double)
TEST_SPRINTF(E_prec_hash_inf, "%#.5E", INFINITY, double)
TEST_SPRINTF(E_prec_fzer_inf, "%0.5E", INFINITY, double)
TEST_SPRINTF(E_prec_mins_ng_inf, "%-.5E", -INFINITY, double)
TEST_SPRINTF(E_prec_plus_ng_inf, "%+.5E", -INFINITY, double)
TEST_SPRINTF(E_prec_spac_ng_inf, "% .5E", -INFINITY, double)
TEST_SPRINTF(E_prec_hash_ng_inf, "%#.5E", -INFINITY, double)
TEST_SPRINTF(E_prec_fzer_ng_inf, "%0.5E", -INFINITY, double)

TEST_SPRINTF(E_zrpc_mins_nan, "%-.0E", NAN, double)
TEST_SPRINTF(E_zrpc_plus_nan, "%+.0E", NAN, double)
TEST_SPRINTF(E_zrpc_spac_nan, "% .0E", NAN, double)
TEST_SPRINTF(E_zrpc_hash_nan, "%#.0E", NAN, double)
TEST_SPRINTF(E_zrpc_fzer_nan, "%0.0E", NAN, double)
TEST_SPRINTF(E_zrpc_mins_inf, "%-.0E", INFINITY, double)
TEST_SPRINTF(E_zrpc_plus_inf, "%+.0E", INFINITY, double)
TEST_SPRINTF(E_zrpc_spac_inf, "% .0E", INFINITY, double)
TEST_SPRINTF(E_zrpc_hash_inf, "%#.0E", INFINITY, double)
TEST_SPRINTF(E_zrpc_fzer_inf, "%0.0E", INFINITY, double)
TEST_SPRINTF(E_zrpc_mins_ng_inf, "%-.0E", -INFINITY, double)
TEST_SPRINTF(E_zrpc_plus_ng_inf, "%+.0E", -INFINITY, double)
TEST_SPRINTF(E_zrpc_spac_ng_inf, "% .0E", -INFINITY, double)
TEST_SPRINTF(E_zrpc_hash_ng_inf, "%#.0E", -INFINITY, double)
TEST_SPRINTF(E_zrpc_fzer_ng_inf, "%0.0E", -INFINITY, double)

TEST_SPRINTF(E_width_prec_mins_nan, "%-10.5E", NAN, double)
TEST_SPRINTF(E_width_prec_plus_nan, "%+10.5E", NAN, double)
TEST_SPRINTF(E_width_prec_spac_nan, "% 10.5E", NAN, double)
TEST_SPRINTF(E_width_prec_hash_nan, "%#10.5E", NAN, double)
TEST_SPRINTF(E_width_prec_fzer_nan, "%010.5E", NAN, double)
TEST_SPRINTF(E_width_prec_mins_inf, "%-10.5E", INFINITY, double)
TEST_SPRINTF(E_width_prec_plus_inf, "%+10.5E", INFINITY, double)
TEST_SPRINTF(E_width_prec_spac_inf, "% 10.5E", INFINITY, double)
TEST_SPRINTF(E_width_prec_hash_inf, "%#10.5E", INFINITY, double)
TEST_SPRINTF(E_width_prec_fzer_inf, "%010.5E", INFINITY, double)
TEST_SPRINTF(E_width_prec_mins_ng_inf, "%-10.5E", -INFINITY, double)
TEST_SPRINTF(E_width_prec_plus_ng_inf, "%+10.5E", -INFINITY, double)
TEST_SPRINTF(E_width_prec_spac_ng_inf, "% 10.5E", -INFINITY, double)
TEST_SPRINTF(E_width_prec_hash_ng_inf, "%#10.5E", -INFINITY, double)
TEST_SPRINTF(E_width_prec_fzer_ng_inf, "%010.5E", -INFINITY, double)

TEST_SPRINTF(E_zrwth_zrpc_plus_nan, "%+0.0E", NAN, double)
TEST_SPRINTF(E_zrwth_zrpc_spac_nan, "% 0.0E", NAN, double)
TEST_SPRINTF(E_zrwth_zrpc_hash_nan, "%#0.0E", NAN, double)
TEST_SPRINTF(E_zrwth_zrpc_plus_inf, "%+0.0E", INFINITY, double)
TEST_SPRINTF(E_zrwth_zrpc_spac_inf, "% 0.0E", INFINITY, double)
TEST_SPRINTF(E_zrwth_zrpc_hash_inf, "%#0.0E", INFINITY, double)
TEST_SPRINTF(E_zrwth_zrpc_plus_ng_inf, "%+0.0E", -INFINITY, double)
TEST_SPRINTF(E_zrwth_zrpc_spac_ng_inf, "% 0.0E", -INFINITY, double)
TEST_SPRINTF(E_zrwth_zrpc_hash_ng_inf, "%#0.0E", -INFINITY, double)

TEST_SPRINTF_2(E_dynamic_prec_nan, "%.*E", 5, NAN, double)
TEST_SPRINTF_2(E_dynamic_prec_inf, "%.*E", 5, INFINITY, double)
TEST_SPRINTF_2(E_dynamic_prec_ng_inf, "%.*E", 5, -INFINITY, double)

TEST_SPRINTF_2(E_dynamic_width_nan, "%*E", 10, NAN, double)
TEST_SPRINTF_2(E_dynamic_width_inf, "%*E", 10, INFINITY, double)
TEST_SPRINTF_2(E_dynamic_width_ng_inf, "%*E", 10, -INFINITY, double)

TEST_SPRINTF_3(E_dynamic_width_prec_nan, "%*.*E", 10, 5, NAN, double)
TEST_SPRINTF_3(E_dynamic_width_prec_inf, "%*.*E", 10, 5, INFINITY, double)
TEST_SPRINTF_3(E_dynamic_width_prec_ng_inf, "%*.*E", 10, 5, -INFINITY, double)

// =========================================================================

TEST_SPRINTF(f_mins_nan, "%-f", NAN, double)
TEST_SPRINTF(f_plus_nan, "%+f", NAN, double)
TEST_SPRINTF(f_spac_nan, "% f", NAN, double)
TEST_SPRINTF(f_hash_nan, "%#f", NAN, double)
TEST_SPRINTF(f_fzer_nan, "%0f", NAN, double)
TEST_SPRINTF(f_mins_inf, "%-f", INFINITY, double)
TEST_SPRINTF(f_plus_inf, "%+f", INFINITY, double)
TEST_SPRINTF(f_spac_inf, "% f", INFINITY, double)
TEST_SPRINTF(f_hash_inf, "%#f", INFINITY, double)
TEST_SPRINTF(f_fzer_inf, "%0f", INFINITY, double)
TEST_SPRINTF(f_mins_ng_inf, "%-f", -INFINITY, double)
TEST_SPRINTF(f_plus_ng_inf, "%+f", -INFINITY, double)
TEST_SPRINTF(f_spac_ng_inf, "% f", -INFINITY, double)
TEST_SPRINTF(f_hash_ng_inf, "%#f", -INFINITY, double)
TEST_SPRINTF(f_fzer_ng_inf, "%0f", -INFINITY, double)

TEST_SPRINTF(f_width_nan, "%5f", NAN, double)
TEST_SPRINTF(f_zrpc_nan, "%.0f", NAN, double)
TEST_SPRINTF(f_prec_nan, "%.5f", NAN, double)
TEST_SPRINTF(f_width_inf, "%5f", INFINITY, double)
TEST_SPRINTF(f_zrpc_inf, "%.0f", INFINITY, double)
TEST_SPRINTF(f_prec_inf, "%.5f", INFINITY, double)
TEST_SPRINTF(f_width_ng_inf, "%5f", -INFINITY, double)
TEST_SPRINTF(f_zrpc_ng_inf, "%.0f", -INFINITY, double)
TEST_SPRINTF(f_prec_ng_inf, "%.5f", -INFINITY, double)

TEST_SPRINTF(f_width_prec_nan, "%10.5f", NAN, double)
TEST_SPRINTF(f_width_prec_inf, "%10.5f", INFINITY, double)
TEST_SPRINTF(f_width_prec_ng_inf, "%10.5f", -INFINITY, double)

TEST_SPRINTF(f_width_mins_nan, "%-5f", NAN, double)
TEST_SPRINTF(f_width_plus_nan, "%+5f", NAN, double)
TEST_SPRINTF(f_width_spac_nan, "% 5f", NAN, double)
TEST_SPRINTF(f_width_hash_nan, "%#5f", NAN, double)
TEST_SPRINTF(f_width_fzer_nan, "%05f", NAN, double)
TEST_SPRINTF(f_width_mins_inf, "%-5f", INFINITY, double)
TEST_SPRINTF(f_width_plus_inf, "%+5f", INFINITY, double)
TEST_SPRINTF(f_width_spac_inf, "% 5f", INFINITY, double)
TEST_SPRINTF(f_width_hash_inf, "%#5f", INFINITY, double)
TEST_SPRINTF(f_width_fzer_inf, "%05f", INFINITY, double)
TEST_SPRINTF(f_width_mins_ng_inf, "%-5f", -INFINITY, double)
TEST_SPRINTF(f_width_plus_ng_inf, "%+5f", -INFINITY, double)
TEST_SPRINTF(f_width_spac_ng_inf, "% 5f", -INFINITY, double)
TEST_SPRINTF(f_width_hash_ng_inf, "%#5f", -INFINITY, double)
TEST_SPRINTF(f_width_fzer_ng_inf, "%05f", -INFINITY, double)

TEST_SPRINTF(f_zrwth_plus_nan, "%+0f", NAN, double)
TEST_SPRINTF(f_zrwth_spac_nan, "% 0f", NAN, double)
TEST_SPRINTF(f_zrwth_hash_nan, "%#0f", NAN, double)
TEST_SPRINTF(f_zrwth_plus_inf, "%+0f", INFINITY, double)
TEST_SPRINTF(f_zrwth_spac_inf, "% 0f", INFINITY, double)
TEST_SPRINTF(f_zrwth_hash_inf, "%#0f", INFINITY, double)
TEST_SPRINTF(f_zrwth_plus_ng_inf, "%+0f", -INFINITY, double)
TEST_SPRINTF(f_zrwth_spac_ng_inf, "% 0f", -INFINITY, double)
TEST_SPRINTF(f_zrwth_hash_ng_inf, "%#0f", -INFINITY, double)

TEST_SPRINTF(f_prec_mins_nan, "%-.5f", NAN, double)
TEST_SPRINTF(f_prec_plus_nan, "%+.5f", NAN, double)
TEST_SPRINTF(f_prec_spac_nan, "% .5f", NAN, double)
TEST_SPRINTF(f_prec_hash_nan, "%#.5f", NAN, double)
TEST_SPRINTF(f_prec_fzer_nan, "%0.5f", NAN, double)
TEST_SPRINTF(f_prec_mins_inf, "%-.5f", INFINITY, double)
TEST_SPRINTF(f_prec_plus_inf, "%+.5f", INFINITY, double)
TEST_SPRINTF(f_prec_spac_inf, "% .5f", INFINITY, double)
TEST_SPRINTF(f_prec_hash_inf, "%#.5f", INFINITY, double)
TEST_SPRINTF(f_prec_fzer_inf, "%0.5f", INFINITY, double)
TEST_SPRINTF(f_prec_mins_ng_inf, "%-.5f", -INFINITY, double)
TEST_SPRINTF(f_prec_plus_ng_inf, "%+.5f", -INFINITY, double)
TEST_SPRINTF(f_prec_spac_ng_inf, "% .5f", -INFINITY, double)
TEST_SPRINTF(f_prec_hash_ng_inf, "%#.5f", -INFINITY, double)
TEST_SPRINTF(f_prec_fzer_ng_inf, "%0.5f", -INFINITY, double)

TEST_SPRINTF(f_zrpc_mins_nan, "%-.0f", NAN, double)
TEST_SPRINTF(f_zrpc_plus_nan, "%+.0f", NAN, double)
TEST_SPRINTF(f_zrpc_spac_nan, "% .0f", NAN, double)
TEST_SPRINTF(f_zrpc_hash_nan, "%#.0f", NAN, double)
TEST_SPRINTF(f_zrpc_fzer_nan, "%0.0f", NAN, double)
TEST_SPRINTF(f_zrpc_mins_inf, "%-.0f", INFINITY, double)
TEST_SPRINTF(f_zrpc_plus_inf, "%+.0f", INFINITY, double)
TEST_SPRINTF(f_zrpc_spac_inf, "% .0f", INFINITY, double)
TEST_SPRINTF(f_zrpc_hash_inf, "%#.0f", INFINITY, double)
TEST_SPRINTF(f_zrpc_fzer_inf, "%0.0f", INFINITY, double)
TEST_SPRINTF(f_zrpc_mins_ng_inf, "%-.0f", -INFINITY, double)
TEST_SPRINTF(f_zrpc_plus_ng_inf, "%+.0f", -INFINITY, double)
TEST_SPRINTF(f_zrpc_spac_ng_inf, "% .0f", -INFINITY, double)
TEST_SPRINTF(f_zrpc_hash_ng_inf, "%#.0f", -INFINITY, double)
TEST_SPRINTF(f_zrpc_fzer_ng_inf, "%0.0f", -INFINITY, double)

TEST_SPRINTF(f_width_prec_mins_nan, "%-10.5f", NAN, double)
TEST_SPRINTF(f_width_prec_plus_nan, "%+10.5f", NAN, double)
TEST_SPRINTF(f_width_prec_spac_nan, "% 10.5f", NAN, double)
TEST_SPRINTF(f_width_prec_hash_nan, "%#10.5f", NAN, double)
TEST_SPRINTF(f_width_prec_fzer_nan, "%010.5f", NAN, double)
TEST_SPRINTF(f_width_prec_mins_inf, "%-10.5f", INFINITY, double)
TEST_SPRINTF(f_width_prec_plus_inf, "%+10.5f", INFINITY, double)
TEST_SPRINTF(f_width_prec_spac_inf, "% 10.5f", INFINITY, double)
TEST_SPRINTF(f_width_prec_hash_inf, "%#10.5f", INFINITY, double)
TEST_SPRINTF(f_width_prec_fzer_inf, "%010.5f", INFINITY, double)
TEST_SPRINTF(f_width_prec_mins_ng_inf, "%-10.5f", -INFINITY, double)
TEST_SPRINTF(f_width_prec_plus_ng_inf, "%+10.5f", -INFINITY, double)
TEST_SPRINTF(f_width_prec_spac_ng_inf, "% 10.5f", -INFINITY, double)
TEST_SPRINTF(f_width_prec_hash_ng_inf, "%#10.5f", -INFINITY, double)
TEST_SPRINTF(f_width_prec_fzer_ng_inf, "%010.5f", -INFINITY, double)

TEST_SPRINTF(f_zrwth_zrpc_plus_nan, "%+0.0f", NAN, double)
TEST_SPRINTF(f_zrwth_zrpc_spac_nan, "% 0.0f", NAN, double)
TEST_SPRINTF(f_zrwth_zrpc_hash_nan, "%#0.0f", NAN, double)
TEST_SPRINTF(f_zrwth_zrpc_plus_inf, "%+0.0f", INFINITY, double)
TEST_SPRINTF(f_zrwth_zrpc_spac_inf, "% 0.0f", INFINITY, double)
TEST_SPRINTF(f_zrwth_zrpc_hash_inf, "%#0.0f", INFINITY, double)
TEST_SPRINTF(f_zrwth_zrpc_plus_ng_inf, "%+0.0f", -INFINITY, double)
TEST_SPRINTF(f_zrwth_zrpc_spac_ng_inf, "% 0.0f", -INFINITY, double)
TEST_SPRINTF(f_zrwth_zrpc_hash_ng_inf, "%#0.0f", -INFINITY, double)

TEST_SPRINTF_2(f_dynamic_prec_nan, "%.*f", 5, NAN, double)
TEST_SPRINTF_2(f_dynamic_prec_inf, "%.*f", 5, INFINITY, double)
TEST_SPRINTF_2(f_dynamic_prec_ng_inf, "%.*f", 5, -INFINITY, double)

TEST_SPRINTF_2(f_dynamic_width_nan, "%*f", 10, NAN, double)
TEST_SPRINTF_2(f_dynamic_width_inf, "%*f", 10, INFINITY, double)
TEST_SPRINTF_2(f_dynamic_width_ng_inf, "%*f", 10, -INFINITY, double)

TEST_SPRINTF_3(f_dynamic_width_prec_nan, "%*.*f", 10, 5, NAN, double)
TEST_SPRINTF_3(f_dynamic_width_prec_inf, "%*.*f", 10, 5, INFINITY, double)
TEST_SPRINTF_3(f_dynamic_width_prec_ng_inf, "%*.*f", 10, 5, -INFINITY, double)

// =========================================================================

TEST_SPRINTF(g_mins_nan, "%-g", NAN, double)
TEST_SPRINTF(g_plus_nan, "%+g", NAN, double)
TEST_SPRINTF(g_spac_nan, "% g", NAN, double)
TEST_SPRINTF(g_hash_nan, "%#g", NAN, double)
TEST_SPRINTF(g_fzer_nan, "%0g", NAN, double)
TEST_SPRINTF(g_mins_inf, "%-g", INFINITY, double)
TEST_SPRINTF(g_plus_inf, "%+g", INFINITY, double)
TEST_SPRINTF(g_spac_inf, "% g", INFINITY, double)
TEST_SPRINTF(g_hash_inf, "%#g", INFINITY, double)
TEST_SPRINTF(g_fzer_inf, "%0g", INFINITY, double)
TEST_SPRINTF(g_mins_ng_inf, "%-g", -INFINITY, double)
TEST_SPRINTF(g_plus_ng_inf, "%+g", -INFINITY, double)
TEST_SPRINTF(g_spac_ng_inf, "% g", -INFINITY, double)
TEST_SPRINTF(g_hash_ng_inf, "%#g", -INFINITY, double)
TEST_SPRINTF(g_fzer_ng_inf, "%0g", -INFINITY, double)

TEST_SPRINTF(g_width_nan, "%5g", NAN, double)
TEST_SPRINTF(g_zrpc_nan, "%.0g", NAN, double)
TEST_SPRINTF(g_prec_nan, "%.5g", NAN, double)
TEST_SPRINTF(g_width_inf, "%5g", INFINITY, double)
TEST_SPRINTF(g_zrpc_inf, "%.0g", INFINITY, double)
TEST_SPRINTF(g_prec_inf, "%.5g", INFINITY, double)
TEST_SPRINTF(g_width_ng_inf, "%5g", -INFINITY, double)
TEST_SPRINTF(g_zrpc_ng_inf, "%.0g", -INFINITY, double)
TEST_SPRINTF(g_prec_ng_inf, "%.5g", -INFINITY, double)

TEST_SPRINTF(g_width_prec_nan, "%10.5g", NAN, double)
TEST_SPRINTF(g_width_prec_inf, "%10.5g", INFINITY, double)
TEST_SPRINTF(g_width_prec_ng_inf, "%10.5g", -INFINITY, double)

TEST_SPRINTF(g_width_mins_nan, "%-5g", NAN, double)
TEST_SPRINTF(g_width_plus_nan, "%+5g", NAN, double)
TEST_SPRINTF(g_width_spac_nan, "% 5g", NAN, double)
TEST_SPRINTF(g_width_hash_nan, "%#5g", NAN, double)
TEST_SPRINTF(g_width_fzer_nan, "%05g", NAN, double)
TEST_SPRINTF(g_width_mins_inf, "%-5g", INFINITY, double)
TEST_SPRINTF(g_width_plus_inf, "%+5g", INFINITY, double)
TEST_SPRINTF(g_width_spac_inf, "% 5g", INFINITY, double)
TEST_SPRINTF(g_width_hash_inf, "%#5g", INFINITY, double)
TEST_SPRINTF(g_width_fzer_inf, "%05g", INFINITY, double)
TEST_SPRINTF(g_width_mins_ng_inf, "%-5g", -INFINITY, double)
TEST_SPRINTF(g_width_plus_ng_inf, "%+5g", -INFINITY, double)
TEST_SPRINTF(g_width_spac_ng_inf, "% 5g", -INFINITY, double)
TEST_SPRINTF(g_width_hash_ng_inf, "%#5g", -INFINITY, double)
TEST_SPRINTF(g_width_fzer_ng_inf, "%05g", -INFINITY, double)

TEST_SPRINTF(g_zrwth_plus_nan, "%+0g", NAN, double)
TEST_SPRINTF(g_zrwth_spac_nan, "% 0g", NAN, double)
TEST_SPRINTF(g_zrwth_hash_nan, "%#0g", NAN, double)
TEST_SPRINTF(g_zrwth_plus_inf, "%+0g", INFINITY, double)
TEST_SPRINTF(g_zrwth_spac_inf, "% 0g", INFINITY, double)
TEST_SPRINTF(g_zrwth_hash_inf, "%#0g", INFINITY, double)
TEST_SPRINTF(g_zrwth_plus_ng_inf, "%+0g", -INFINITY, double)
TEST_SPRINTF(g_zrwth_spac_ng_inf, "% 0g", -INFINITY, double)
TEST_SPRINTF(g_zrwth_hash_ng_inf, "%#0g", -INFINITY, double)

TEST_SPRINTF(g_prec_mins_nan, "%-.5g", NAN, double)
TEST_SPRINTF(g_prec_plus_nan, "%+.5g", NAN, double)
TEST_SPRINTF(g_prec_spac_nan, "% .5g", NAN, double)
TEST_SPRINTF(g_prec_hash_nan, "%#.5g", NAN, double)
TEST_SPRINTF(g_prec_fzer_nan, "%0.5g", NAN, double)
TEST_SPRINTF(g_prec_mins_inf, "%-.5g", INFINITY, double)
TEST_SPRINTF(g_prec_plus_inf, "%+.5g", INFINITY, double)
TEST_SPRINTF(g_prec_spac_inf, "% .5g", INFINITY, double)
TEST_SPRINTF(g_prec_hash_inf, "%#.5g", INFINITY, double)
TEST_SPRINTF(g_prec_fzer_inf, "%0.5g", INFINITY, double)
TEST_SPRINTF(g_prec_mins_ng_inf, "%-.5g", -INFINITY, double)
TEST_SPRINTF(g_prec_plus_ng_inf, "%+.5g", -INFINITY, double)
TEST_SPRINTF(g_prec_spac_ng_inf, "% .5g", -INFINITY, double)
TEST_SPRINTF(g_prec_hash_ng_inf, "%#.5g", -INFINITY, double)
TEST_SPRINTF(g_prec_fzer_ng_inf, "%0.5g", -INFINITY, double)

TEST_SPRINTF(g_zrpc_mins_nan, "%-.0g", NAN, double)
TEST_SPRINTF(g_zrpc_plus_nan, "%+.0g", NAN, double)
TEST_SPRINTF(g_zrpc_spac_nan, "% .0g", NAN, double)
TEST_SPRINTF(g_zrpc_hash_nan, "%#.0g", NAN, double)
TEST_SPRINTF(g_zrpc_fzer_nan, "%0.0g", NAN, double)
TEST_SPRINTF(g_zrpc_mins_inf, "%-.0g", INFINITY, double)
TEST_SPRINTF(g_zrpc_plus_inf, "%+.0g", INFINITY, double)
TEST_SPRINTF(g_zrpc_spac_inf, "% .0g", INFINITY, double)
TEST_SPRINTF(g_zrpc_hash_inf, "%#.0g", INFINITY, double)
TEST_SPRINTF(g_zrpc_fzer_inf, "%0.0g", INFINITY, double)
TEST_SPRINTF(g_zrpc_mins_ng_inf, "%-.0g", -INFINITY, double)
TEST_SPRINTF(g_zrpc_plus_ng_inf, "%+.0g", -INFINITY, double)
TEST_SPRINTF(g_zrpc_spac_ng_inf, "% .0g", -INFINITY, double)
TEST_SPRINTF(g_zrpc_hash_ng_inf, "%#.0g", -INFINITY, double)
TEST_SPRINTF(g_zrpc_fzer_ng_inf, "%0.0g", -INFINITY, double)

TEST_SPRINTF(g_width_prec_mins_nan, "%-10.5g", NAN, double)
TEST_SPRINTF(g_width_prec_plus_nan, "%+10.5g", NAN, double)
TEST_SPRINTF(g_width_prec_spac_nan, "% 10.5g", NAN, double)
TEST_SPRINTF(g_width_prec_hash_nan, "%#10.5g", NAN, double)
TEST_SPRINTF(g_width_prec_fzer_nan, "%010.5g", NAN, double)
TEST_SPRINTF(g_width_prec_mins_inf, "%-10.5g", INFINITY, double)
TEST_SPRINTF(g_width_prec_plus_inf, "%+10.5g", INFINITY, double)
TEST_SPRINTF(g_width_prec_spac_inf, "% 10.5g", INFINITY, double)
TEST_SPRINTF(g_width_prec_hash_inf, "%#10.5g", INFINITY, double)
TEST_SPRINTF(g_width_prec_fzer_inf, "%010.5g", INFINITY, double)
TEST_SPRINTF(g_width_prec_mins_ng_inf, "%-10.5g", -INFINITY, double)
TEST_SPRINTF(g_width_prec_plus_ng_inf, "%+10.5g", -INFINITY, double)
TEST_SPRINTF(g_width_prec_spac_ng_inf, "% 10.5g", -INFINITY, double)
TEST_SPRINTF(g_width_prec_hash_ng_inf, "%#10.5g", -INFINITY, double)
TEST_SPRINTF(g_width_prec_fzer_ng_inf, "%010.5g", -INFINITY, double)

TEST_SPRINTF(g_zrwth_zrpc_plus_nan, "%+0.0g", NAN, double)
TEST_SPRINTF(g_zrwth_zrpc_spac_nan, "% 0.0g", NAN, double)
TEST_SPRINTF(g_zrwth_zrpc_hash_nan, "%#0.0g", NAN, double)
TEST_SPRINTF(g_zrwth_zrpc_plus_inf, "%+0.0g", INFINITY, double)
TEST_SPRINTF(g_zrwth_zrpc_spac_inf, "% 0.0g", INFINITY, double)
TEST_SPRINTF(g_zrwth_zrpc_hash_inf, "%#0.0g", INFINITY, double)
TEST_SPRINTF(g_zrwth_zrpc_plus_ng_inf, "%+0.0g", -INFINITY, double)
TEST_SPRINTF(g_zrwth_zrpc_spac_ng_inf, "% 0.0g", -INFINITY, double)
TEST_SPRINTF(g_zrwth_zrpc_hash_ng_inf, "%#0.0g", -INFINITY, double)

TEST_SPRINTF_2(g_dynamic_prec_nan, "%.*g", 5, NAN, double)
TEST_SPRINTF_2(g_dynamic_prec_inf, "%.*g", 5, INFINITY, double)
TEST_SPRINTF_2(g_dynamic_prec_ng_inf, "%.*g", 5, -INFINITY, double)

TEST_SPRINTF_2(g_dynamic_width_nan, "%*g", 10, NAN, double)
TEST_SPRINTF_2(g_dynamic_width_inf, "%*g", 10, INFINITY, double)
TEST_SPRINTF_2(g_dynamic_width_ng_inf, "%*g", 10, -INFINITY, double)

TEST_SPRINTF_3(g_dynamic_width_prec_nan, "%*.*g", 10, 5, NAN, double)
TEST_SPRINTF_3(g_dynamic_width_prec_inf, "%*.*g", 10, 5, INFINITY, double)
TEST_SPRINTF_3(g_dynamic_width_prec_ng_inf, "%*.*g", 10, 5, -INFINITY, double)

// =========================================================================

TEST_SPRINTF(G_mins_nan, "%-G", NAN, double)
TEST_SPRINTF(G_plus_nan, "%+G", NAN, double)
TEST_SPRINTF(G_spac_nan, "% G", NAN, double)
TEST_SPRINTF(G_hash_nan, "%#G", NAN, double)
TEST_SPRINTF(G_fzer_nan, "%0G", NAN, double)
TEST_SPRINTF(G_mins_inf, "%-G", INFINITY, double)
TEST_SPRINTF(G_plus_inf, "%+G", INFINITY, double)
TEST_SPRINTF(G_spac_inf, "% G", INFINITY, double)
TEST_SPRINTF(G_hash_inf, "%#G", INFINITY, double)
TEST_SPRINTF(G_fzer_inf, "%0G", INFINITY, double)
TEST_SPRINTF(G_mins_ng_inf, "%-G", -INFINITY, double)
TEST_SPRINTF(G_plus_ng_inf, "%+G", -INFINITY, double)
TEST_SPRINTF(G_spac_ng_inf, "% G", -INFINITY, double)
TEST_SPRINTF(G_hash_ng_inf, "%#G", -INFINITY, double)
TEST_SPRINTF(G_fzer_ng_inf, "%0G", -INFINITY, double)

TEST_SPRINTF(G_width_nan, "%5G", NAN, double)
TEST_SPRINTF(G_zrpc_nan, "%.0G", NAN, double)
TEST_SPRINTF(G_prec_nan, "%.5G", NAN, double)
TEST_SPRINTF(G_width_inf, "%5G", INFINITY, double)
TEST_SPRINTF(G_zrpc_inf, "%.0G", INFINITY, double)
TEST_SPRINTF(G_prec_inf, "%.5G", INFINITY, double)
TEST_SPRINTF(G_width_ng_inf, "%5G", -INFINITY, double)
TEST_SPRINTF(G_zrpc_ng_inf, "%.0G", -INFINITY, double)
TEST_SPRINTF(G_prec_ng_inf, "%.5G", -INFINITY, double)

TEST_SPRINTF(G_width_prec_nan, "%10.5G", NAN, double)
TEST_SPRINTF(G_width_prec_inf, "%10.5G", INFINITY, double)
TEST_SPRINTF(G_width_prec_ng_inf, "%10.5G", -INFINITY, double)

TEST_SPRINTF(G_width_mins_nan, "%-5G", NAN, double)
TEST_SPRINTF(G_width_plus_nan, "%+5G", NAN, double)
TEST_SPRINTF(G_width_spac_nan, "% 5G", NAN, double)
TEST_SPRINTF(G_width_hash_nan, "%#5G", NAN, double)
TEST_SPRINTF(G_width_fzer_nan, "%05G", NAN, double)
TEST_SPRINTF(G_width_mins_inf, "%-5G", INFINITY, double)
TEST_SPRINTF(G_width_plus_inf, "%+5G", INFINITY, double)
TEST_SPRINTF(G_width_spac_inf, "% 5G", INFINITY, double)
TEST_SPRINTF(G_width_hash_inf, "%#5G", INFINITY, double)
TEST_SPRINTF(G_width_fzer_inf, "%05G", INFINITY, double)
TEST_SPRINTF(G_width_mins_ng_inf, "%-5G", -INFINITY, double)
TEST_SPRINTF(G_width_plus_ng_inf, "%+5G", -INFINITY, double)
TEST_SPRINTF(G_width_spac_ng_inf, "% 5G", -INFINITY, double)
TEST_SPRINTF(G_width_hash_ng_inf, "%#5G", -INFINITY, double)
TEST_SPRINTF(G_width_fzer_ng_inf, "%05G", -INFINITY, double)

TEST_SPRINTF(G_zrwth_plus_nan, "%+0G", NAN, double)
TEST_SPRINTF(G_zrwth_spac_nan, "% 0G", NAN, double)
TEST_SPRINTF(G_zrwth_hash_nan, "%#0G", NAN, double)
TEST_SPRINTF(G_zrwth_plus_inf, "%+0G", INFINITY, double)
TEST_SPRINTF(G_zrwth_spac_inf, "% 0G", INFINITY, double)
TEST_SPRINTF(G_zrwth_hash_inf, "%#0G", INFINITY, double)
TEST_SPRINTF(G_zrwth_plus_ng_inf, "%+0G", -INFINITY, double)
TEST_SPRINTF(G_zrwth_spac_ng_inf, "% 0G", -INFINITY, double)
TEST_SPRINTF(G_zrwth_hash_ng_inf, "%#0G", -INFINITY, double)

TEST_SPRINTF(G_prec_mins_nan, "%-.5G", NAN, double)
TEST_SPRINTF(G_prec_plus_nan, "%+.5G", NAN, double)
TEST_SPRINTF(G_prec_spac_nan, "% .5G", NAN, double)
TEST_SPRINTF(G_prec_hash_nan, "%#.5G", NAN, double)
TEST_SPRINTF(G_prec_fzer_nan, "%0.5G", NAN, double)
TEST_SPRINTF(G_prec_mins_inf, "%-.5G", INFINITY, double)
TEST_SPRINTF(G_prec_plus_inf, "%+.5G", INFINITY, double)
TEST_SPRINTF(G_prec_spac_inf, "% .5G", INFINITY, double)
TEST_SPRINTF(G_prec_hash_inf, "%#.5G", INFINITY, double)
TEST_SPRINTF(G_prec_fzer_inf, "%0.5G", INFINITY, double)
TEST_SPRINTF(G_prec_mins_ng_inf, "%-.5G", -INFINITY, double)
TEST_SPRINTF(G_prec_plus_ng_inf, "%+.5G", -INFINITY, double)
TEST_SPRINTF(G_prec_spac_ng_inf, "% .5G", -INFINITY, double)
TEST_SPRINTF(G_prec_hash_ng_inf, "%#.5G", -INFINITY, double)
TEST_SPRINTF(G_prec_fzer_ng_inf, "%0.5G", -INFINITY, double)

TEST_SPRINTF(G_zrpc_mins_nan, "%-.0G", NAN, double)
TEST_SPRINTF(G_zrpc_plus_nan, "%+.0G", NAN, double)
TEST_SPRINTF(G_zrpc_spac_nan, "% .0G", NAN, double)
TEST_SPRINTF(G_zrpc_hash_nan, "%#.0G", NAN, double)
TEST_SPRINTF(G_zrpc_fzer_nan, "%0.0G", NAN, double)
TEST_SPRINTF(G_zrpc_mins_inf, "%-.0G", INFINITY, double)
TEST_SPRINTF(G_zrpc_plus_inf, "%+.0G", INFINITY, double)
TEST_SPRINTF(G_zrpc_spac_inf, "% .0G", INFINITY, double)
TEST_SPRINTF(G_zrpc_hash_inf, "%#.0G", INFINITY, double)
TEST_SPRINTF(G_zrpc_fzer_inf, "%0.0G", INFINITY, double)
TEST_SPRINTF(G_zrpc_mins_ng_inf, "%-.0G", -INFINITY, double)
TEST_SPRINTF(G_zrpc_plus_ng_inf, "%+.0G", -INFINITY, double)
TEST_SPRINTF(G_zrpc_spac_ng_inf, "% .0G", -INFINITY, double)
TEST_SPRINTF(G_zrpc_hash_ng_inf, "%#.0G", -INFINITY, double)
TEST_SPRINTF(G_zrpc_fzer_ng_inf, "%0.0G", -INFINITY, double)

TEST_SPRINTF(G_width_prec_mins_nan, "%-10.5G", NAN, double)
TEST_SPRINTF(G_width_prec_plus_nan, "%+10.5G", NAN, double)
TEST_SPRINTF(G_width_prec_spac_nan, "% 10.5G", NAN, double)
TEST_SPRINTF(G_width_prec_hash_nan, "%#10.5G", NAN, double)
TEST_SPRINTF(G_width_prec_fzer_nan, "%010.5G", NAN, double)
TEST_SPRINTF(G_width_prec_mins_inf, "%-10.5G", INFINITY, double)
TEST_SPRINTF(G_width_prec_plus_inf, "%+10.5G", INFINITY, double)
TEST_SPRINTF(G_width_prec_spac_inf, "% 10.5G", INFINITY, double)
TEST_SPRINTF(G_width_prec_hash_inf, "%#10.5G", INFINITY, double)
TEST_SPRINTF(G_width_prec_fzer_inf, "%010.5G", INFINITY, double)
TEST_SPRINTF(G_width_prec_mins_ng_inf, "%-10.5G", -INFINITY, double)
TEST_SPRINTF(G_width_prec_plus_ng_inf, "%+10.5G", -INFINITY, double)
TEST_SPRINTF(G_width_prec_spac_ng_inf, "% 10.5G", -INFINITY, double)
TEST_SPRINTF(G_width_prec_hash_ng_inf, "%#10.5G", -INFINITY, double)
TEST_SPRINTF(G_width_prec_fzer_ng_inf, "%010.5G", -INFINITY, double)

TEST_SPRINTF(G_zrwth_zrpc_plus_nan, "%+0.0G", NAN, double)
TEST_SPRINTF(G_zrwth_zrpc_spac_nan, "% 0.0G", NAN, double)
TEST_SPRINTF(G_zrwth_zrpc_hash_nan, "%#0.0G", NAN, double)
TEST_SPRINTF(G_zrwth_zrpc_plus_inf, "%+0.0G", INFINITY, double)
TEST_SPRINTF(G_zrwth_zrpc_spac_inf, "% 0.0G", INFINITY, double)
TEST_SPRINTF(G_zrwth_zrpc_hash_inf, "%#0.0G", INFINITY, double)
TEST_SPRINTF(G_zrwth_zrpc_plus_ng_inf, "%+0.0G", -INFINITY, double)
TEST_SPRINTF(G_zrwth_zrpc_spac_ng_inf, "% 0.0G", -INFINITY, double)
TEST_SPRINTF(G_zrwth_zrpc_hash_ng_inf, "%#0.0G", -INFINITY, double)

TEST_SPRINTF_2(G_dynamic_prec_nan, "%.*G", 5, NAN, double)
TEST_SPRINTF_2(G_dynamic_prec_inf, "%.*G", 5, INFINITY, double)
TEST_SPRINTF_2(G_dynamic_prec_ng_inf, "%.*G", 5, -INFINITY, double)

TEST_SPRINTF_2(G_dynamic_width_nan, "%*G", 10, NAN, double)
TEST_SPRINTF_2(G_dynamic_width_inf, "%*G", 10, INFINITY, double)
TEST_SPRINTF_2(G_dynamic_width_ng_inf, "%*G", 10, -INFINITY, double)

TEST_SPRINTF_3(G_dynamic_width_prec_nan, "%*.*G", 10, 5, NAN, double)
TEST_SPRINTF_3(G_dynamic_width_prec_inf, "%*.*G", 10, 5, INFINITY, double)
TEST_SPRINTF_3(G_dynamic_width_prec_ng_inf, "%*.*G", 10, 5, -INFINITY, double)

// =========================================================================

TEST_SPRINTF(le_mins_nan, "%-le", NAN, double)
TEST_SPRINTF(le_plus_nan, "%+le", NAN, double)
TEST_SPRINTF(le_spac_nan, "% le", NAN, double)
TEST_SPRINTF(le_hash_nan, "%#le", NAN, double)
TEST_SPRINTF(le_fzer_nan, "%0le", NAN, double)
TEST_SPRINTF(le_mins_inf, "%-le", INFINITY, double)
TEST_SPRINTF(le_plus_inf, "%+le", INFINITY, double)
TEST_SPRINTF(le_spac_inf, "% le", INFINITY, double)
TEST_SPRINTF(le_hash_inf, "%#le", INFINITY, double)
TEST_SPRINTF(le_fzer_inf, "%0le", INFINITY, double)
TEST_SPRINTF(le_mins_ng_inf, "%-le", -INFINITY, double)
TEST_SPRINTF(le_plus_ng_inf, "%+le", -INFINITY, double)
TEST_SPRINTF(le_spac_ng_inf, "% le", -INFINITY, double)
TEST_SPRINTF(le_hash_ng_inf, "%#le", -INFINITY, double)
TEST_SPRINTF(le_fzer_ng_inf, "%0le", -INFINITY, double)

TEST_SPRINTF(le_width_nan, "%5le", NAN, double)
TEST_SPRINTF(le_zrpc_nan, "%.0le", NAN, double)
TEST_SPRINTF(le_prec_nan, "%.5le", NAN, double)
TEST_SPRINTF(le_width_inf, "%5le", INFINITY, double)
TEST_SPRINTF(le_zrpc_inf, "%.0le", INFINITY, double)
TEST_SPRINTF(le_prec_inf, "%.5le", INFINITY, double)
TEST_SPRINTF(le_width_ng_inf, "%5le", -INFINITY, double)
TEST_SPRINTF(le_zrpc_ng_inf, "%.0le", -INFINITY, double)
TEST_SPRINTF(le_prec_ng_inf, "%.5le", -INFINITY, double)

TEST_SPRINTF(le_width_prec_nan, "%10.5le", NAN, double)
TEST_SPRINTF(le_width_prec_inf, "%10.5le", INFINITY, double)
TEST_SPRINTF(le_width_prec_ng_inf, "%10.5le", -INFINITY, double)

TEST_SPRINTF(le_width_mins_nan, "%-5le", NAN, double)
TEST_SPRINTF(le_width_plus_nan, "%+5le", NAN, double)
TEST_SPRINTF(le_width_spac_nan, "% 5le", NAN, double)
TEST_SPRINTF(le_width_hash_nan, "%#5le", NAN, double)
TEST_SPRINTF(le_width_fzer_nan, "%05le", NAN, double)
TEST_SPRINTF(le_width_mins_inf, "%-5le", INFINITY, double)
TEST_SPRINTF(le_width_plus_inf, "%+5le", INFINITY, double)
TEST_SPRINTF(le_width_spac_inf, "% 5le", INFINITY, double)
TEST_SPRINTF(le_width_hash_inf, "%#5le", INFINITY, double)
TEST_SPRINTF(le_width_fzer_inf, "%05le", INFINITY, double)
TEST_SPRINTF(le_width_mins_ng_inf, "%-5le", -INFINITY, double)
TEST_SPRINTF(le_width_plus_ng_inf, "%+5le", -INFINITY, double)
TEST_SPRINTF(le_width_spac_ng_inf, "% 5le", -INFINITY, double)
TEST_SPRINTF(le_width_hash_ng_inf, "%#5le", -INFINITY, double)
TEST_SPRINTF(le_width_fzer_ng_inf, "%05le", -INFINITY, double)

TEST_SPRINTF(le_zrwth_plus_nan, "%+0le", NAN, double)
TEST_SPRINTF(le_zrwth_spac_nan, "% 0le", NAN, double)
TEST_SPRINTF(le_zrwth_hash_nan, "%#0le", NAN, double)
TEST_SPRINTF(le_zrwth_plus_inf, "%+0le", INFINITY, double)
TEST_SPRINTF(le_zrwth_spac_inf, "% 0le", INFINITY, double)
TEST_SPRINTF(le_zrwth_hash_inf, "%#0le", INFINITY, double)
TEST_SPRINTF(le_zrwth_plus_ng_inf, "%+0le", -INFINITY, double)
TEST_SPRINTF(le_zrwth_spac_ng_inf, "% 0le", -INFINITY, double)
TEST_SPRINTF(le_zrwth_hash_ng_inf, "%#0le", -INFINITY, double)

TEST_SPRINTF(le_prec_mins_nan, "%-.5le", NAN, double)
TEST_SPRINTF(le_prec_plus_nan, "%+.5le", NAN, double)
TEST_SPRINTF(le_prec_spac_nan, "% .5le", NAN, double)
TEST_SPRINTF(le_prec_hash_nan, "%#.5le", NAN, double)
TEST_SPRINTF(le_prec_fzer_nan, "%0.5le", NAN, double)
TEST_SPRINTF(le_prec_mins_inf, "%-.5le", INFINITY, double)
TEST_SPRINTF(le_prec_plus_inf, "%+.5le", INFINITY, double)
TEST_SPRINTF(le_prec_spac_inf, "% .5le", INFINITY, double)
TEST_SPRINTF(le_prec_hash_inf, "%#.5le", INFINITY, double)
TEST_SPRINTF(le_prec_fzer_inf, "%0.5le", INFINITY, double)
TEST_SPRINTF(le_prec_mins_ng_inf, "%-.5le", -INFINITY, double)
TEST_SPRINTF(le_prec_plus_ng_inf, "%+.5le", -INFINITY, double)
TEST_SPRINTF(le_prec_spac_ng_inf, "% .5le", -INFINITY, double)
TEST_SPRINTF(le_prec_hash_ng_inf, "%#.5le", -INFINITY, double)
TEST_SPRINTF(le_prec_fzer_ng_inf, "%0.5le", -INFINITY, double)

TEST_SPRINTF(le_zrpc_mins_nan, "%-.0le", NAN, double)
TEST_SPRINTF(le_zrpc_plus_nan, "%+.0le", NAN, double)
TEST_SPRINTF(le_zrpc_spac_nan, "% .0le", NAN, double)
TEST_SPRINTF(le_zrpc_hash_nan, "%#.0le", NAN, double)
TEST_SPRINTF(le_zrpc_fzer_nan, "%0.0le", NAN, double)
TEST_SPRINTF(le_zrpc_mins_inf, "%-.0le", INFINITY, double)
TEST_SPRINTF(le_zrpc_plus_inf, "%+.0le", INFINITY, double)
TEST_SPRINTF(le_zrpc_spac_inf, "% .0le", INFINITY, double)
TEST_SPRINTF(le_zrpc_hash_inf, "%#.0le", INFINITY, double)
TEST_SPRINTF(le_zrpc_fzer_inf, "%0.0le", INFINITY, double)
TEST_SPRINTF(le_zrpc_mins_ng_inf, "%-.0le", -INFINITY, double)
TEST_SPRINTF(le_zrpc_plus_ng_inf, "%+.0le", -INFINITY, double)
TEST_SPRINTF(le_zrpc_spac_ng_inf, "% .0le", -INFINITY, double)
TEST_SPRINTF(le_zrpc_hash_ng_inf, "%#.0le", -INFINITY, double)
TEST_SPRINTF(le_zrpc_fzer_ng_inf, "%0.0le", -INFINITY, double)

TEST_SPRINTF(le_width_prec_mins_nan, "%-10.5le", NAN, double)
TEST_SPRINTF(le_width_prec_plus_nan, "%+10.5le", NAN, double)
TEST_SPRINTF(le_width_prec_spac_nan, "% 10.5le", NAN, double)
TEST_SPRINTF(le_width_prec_hash_nan, "%#10.5le", NAN, double)
TEST_SPRINTF(le_width_prec_fzer_nan, "%010.5le", NAN, double)
TEST_SPRINTF(le_width_prec_mins_inf, "%-10.5le", INFINITY, double)
TEST_SPRINTF(le_width_prec_plus_inf, "%+10.5le", INFINITY, double)
TEST_SPRINTF(le_width_prec_spac_inf, "% 10.5le", INFINITY, double)
TEST_SPRINTF(le_width_prec_hash_inf, "%#10.5le", INFINITY, double)
TEST_SPRINTF(le_width_prec_fzer_inf, "%010.5le", INFINITY, double)
TEST_SPRINTF(le_width_prec_mins_ng_inf, "%-10.5le", -INFINITY, double)
TEST_SPRINTF(le_width_prec_plus_ng_inf, "%+10.5le", -INFINITY, double)
TEST_SPRINTF(le_width_prec_spac_ng_inf, "% 10.5le", -INFINITY, double)
TEST_SPRINTF(le_width_prec_hash_ng_inf, "%#10.5le", -INFINITY, double)
TEST_SPRINTF(le_width_prec_fzer_ng_inf, "%010.5le", -INFINITY, double)

TEST_SPRINTF(le_zrwth_zrpc_plus_nan, "%+0.0le", NAN, double)
TEST_SPRINTF(le_zrwth_zrpc_spac_nan, "% 0.0le", NAN, double)
TEST_SPRINTF(le_zrwth_zrpc_hash_nan, "%#0.0le", NAN, double)
TEST_SPRINTF(le_zrwth_zrpc_plus_inf, "%+0.0le", INFINITY, double)
TEST_SPRINTF(le_zrwth_zrpc_spac_inf, "% 0.0le", INFINITY, double)
TEST_SPRINTF(le_zrwth_zrpc_hash_inf, "%#0.0le", INFINITY, double)
TEST_SPRINTF(le_zrwth_zrpc_plus_ng_inf, "%+0.0le", -INFINITY, double)
TEST_SPRINTF(le_zrwth_zrpc_spac_ng_inf, "% 0.0le", -INFINITY, double)
TEST_SPRINTF(le_zrwth_zrpc_hash_ng_inf, "%#0.0le", -INFINITY, double)

TEST_SPRINTF_2(le_dynamic_prec_nan, "%.*le", 5, NAN, double)
TEST_SPRINTF_2(le_dynamic_prec_inf, "%.*le", 5, INFINITY, double)
TEST_SPRINTF_2(le_dynamic_prec_ng_inf, "%.*le", 5, -INFINITY, double)

TEST_SPRINTF_2(le_dynamic_width_nan, "%*le", 10, NAN, double)
TEST_SPRINTF_2(le_dynamic_width_inf, "%*le", 10, INFINITY, double)
TEST_SPRINTF_2(le_dynamic_width_ng_inf, "%*le", 10, -INFINITY, double)

TEST_SPRINTF_3(le_dynamic_width_prec_nan, "%*.*le", 10, 5, NAN, double)
TEST_SPRINTF_3(le_dynamic_width_prec_inf, "%*.*le", 10, 5, INFINITY, double)
TEST_SPRINTF_3(le_dynamic_width_prec_ng_inf, "%*.*le", 10, 5, -INFINITY, double)

// =========================================================================

TEST_SPRINTF(lE_mins_nan, "%-lE", NAN, double)
TEST_SPRINTF(lE_plus_nan, "%+lE", NAN, double)
TEST_SPRINTF(lE_spac_nan, "% lE", NAN, double)
TEST_SPRINTF(lE_hash_nan, "%#lE", NAN, double)
TEST_SPRINTF(lE_fzer_nan, "%0lE", NAN, double)
TEST_SPRINTF(lE_mins_inf, "%-lE", INFINITY, double)
TEST_SPRINTF(lE_plus_inf, "%+lE", INFINITY, double)
TEST_SPRINTF(lE_spac_inf, "% lE", INFINITY, double)
TEST_SPRINTF(lE_hash_inf, "%#lE", INFINITY, double)
TEST_SPRINTF(lE_fzer_inf, "%0lE", INFINITY, double)
TEST_SPRINTF(lE_mins_ng_inf, "%-lE", -INFINITY, double)
TEST_SPRINTF(lE_plus_ng_inf, "%+lE", -INFINITY, double)
TEST_SPRINTF(lE_spac_ng_inf, "% lE", -INFINITY, double)
TEST_SPRINTF(lE_hash_ng_inf, "%#lE", -INFINITY, double)
TEST_SPRINTF(lE_fzer_ng_inf, "%0lE", -INFINITY, double)

TEST_SPRINTF(lE_width_nan, "%5lE", NAN, double)
TEST_SPRINTF(lE_zrpc_nan, "%.0lE", NAN, double)
TEST_SPRINTF(lE_prec_nan, "%.5lE", NAN, double)
TEST_SPRINTF(lE_width_inf, "%5lE", INFINITY, double)
TEST_SPRINTF(lE_zrpc_inf, "%.0lE", INFINITY, double)
TEST_SPRINTF(lE_prec_inf, "%.5lE", INFINITY, double)
TEST_SPRINTF(lE_width_ng_inf, "%5lE", -INFINITY, double)
TEST_SPRINTF(lE_zrpc_ng_inf, "%.0lE", -INFINITY, double)
TEST_SPRINTF(lE_prec_ng_inf, "%.5lE", -INFINITY, double)

TEST_SPRINTF(lE_width_prec_nan, "%10.5lE", NAN, double)
TEST_SPRINTF(lE_width_prec_inf, "%10.5lE", INFINITY, double)
TEST_SPRINTF(lE_width_prec_ng_inf, "%10.5lE", -INFINITY, double)

TEST_SPRINTF(lE_width_mins_nan, "%-5lE", NAN, double)
TEST_SPRINTF(lE_width_plus_nan, "%+5lE", NAN, double)
TEST_SPRINTF(lE_width_spac_nan, "% 5lE", NAN, double)
TEST_SPRINTF(lE_width_hash_nan, "%#5lE", NAN, double)
TEST_SPRINTF(lE_width_fzer_nan, "%05lE", NAN, double)
TEST_SPRINTF(lE_width_mins_inf, "%-5lE", INFINITY, double)
TEST_SPRINTF(lE_width_plus_inf, "%+5lE", INFINITY, double)
TEST_SPRINTF(lE_width_spac_inf, "% 5lE", INFINITY, double)
TEST_SPRINTF(lE_width_hash_inf, "%#5lE", INFINITY, double)
TEST_SPRINTF(lE_width_fzer_inf, "%05lE", INFINITY, double)
TEST_SPRINTF(lE_width_mins_ng_inf, "%-5lE", -INFINITY, double)
TEST_SPRINTF(lE_width_plus_ng_inf, "%+5lE", -INFINITY, double)
TEST_SPRINTF(lE_width_spac_ng_inf, "% 5lE", -INFINITY, double)
TEST_SPRINTF(lE_width_hash_ng_inf, "%#5lE", -INFINITY, double)
TEST_SPRINTF(lE_width_fzer_ng_inf, "%05lE", -INFINITY, double)

TEST_SPRINTF(lE_zrwth_plus_nan, "%+0lE", NAN, double)
TEST_SPRINTF(lE_zrwth_spac_nan, "% 0lE", NAN, double)
TEST_SPRINTF(lE_zrwth_hash_nan, "%#0lE", NAN, double)
TEST_SPRINTF(lE_zrwth_plus_inf, "%+0lE", INFINITY, double)
TEST_SPRINTF(lE_zrwth_spac_inf, "% 0lE", INFINITY, double)
TEST_SPRINTF(lE_zrwth_hash_inf, "%#0lE", INFINITY, double)
TEST_SPRINTF(lE_zrwth_plus_ng_inf, "%+0lE", -INFINITY, double)
TEST_SPRINTF(lE_zrwth_spac_ng_inf, "% 0lE", -INFINITY, double)
TEST_SPRINTF(lE_zrwth_hash_ng_inf, "%#0lE", -INFINITY, double)

TEST_SPRINTF(lE_prec_mins_nan, "%-.5lE", NAN, double)
TEST_SPRINTF(lE_prec_plus_nan, "%+.5lE", NAN, double)
TEST_SPRINTF(lE_prec_spac_nan, "% .5lE", NAN, double)
TEST_SPRINTF(lE_prec_hash_nan, "%#.5lE", NAN, double)
TEST_SPRINTF(lE_prec_fzer_nan, "%0.5lE", NAN, double)
TEST_SPRINTF(lE_prec_mins_inf, "%-.5lE", INFINITY, double)
TEST_SPRINTF(lE_prec_plus_inf, "%+.5lE", INFINITY, double)
TEST_SPRINTF(lE_prec_spac_inf, "% .5lE", INFINITY, double)
TEST_SPRINTF(lE_prec_hash_inf, "%#.5lE", INFINITY, double)
TEST_SPRINTF(lE_prec_fzer_inf, "%0.5lE", INFINITY, double)
TEST_SPRINTF(lE_prec_mins_ng_inf, "%-.5lE", -INFINITY, double)
TEST_SPRINTF(lE_prec_plus_ng_inf, "%+.5lE", -INFINITY, double)
TEST_SPRINTF(lE_prec_spac_ng_inf, "% .5lE", -INFINITY, double)
TEST_SPRINTF(lE_prec_hash_ng_inf, "%#.5lE", -INFINITY, double)
TEST_SPRINTF(lE_prec_fzer_ng_inf, "%0.5lE", -INFINITY, double)

TEST_SPRINTF(lE_zrpc_mins_nan, "%-.0lE", NAN, double)
TEST_SPRINTF(lE_zrpc_plus_nan, "%+.0lE", NAN, double)
TEST_SPRINTF(lE_zrpc_spac_nan, "% .0lE", NAN, double)
TEST_SPRINTF(lE_zrpc_hash_nan, "%#.0lE", NAN, double)
TEST_SPRINTF(lE_zrpc_fzer_nan, "%0.0lE", NAN, double)
TEST_SPRINTF(lE_zrpc_mins_inf, "%-.0lE", INFINITY, double)
TEST_SPRINTF(lE_zrpc_plus_inf, "%+.0lE", INFINITY, double)
TEST_SPRINTF(lE_zrpc_spac_inf, "% .0lE", INFINITY, double)
TEST_SPRINTF(lE_zrpc_hash_inf, "%#.0lE", INFINITY, double)
TEST_SPRINTF(lE_zrpc_fzer_inf, "%0.0lE", INFINITY, double)
TEST_SPRINTF(lE_zrpc_mins_ng_inf, "%-.0lE", -INFINITY, double)
TEST_SPRINTF(lE_zrpc_plus_ng_inf, "%+.0lE", -INFINITY, double)
TEST_SPRINTF(lE_zrpc_spac_ng_inf, "% .0lE", -INFINITY, double)
TEST_SPRINTF(lE_zrpc_hash_ng_inf, "%#.0lE", -INFINITY, double)
TEST_SPRINTF(lE_zrpc_fzer_ng_inf, "%0.0lE", -INFINITY, double)

TEST_SPRINTF(lE_width_prec_mins_nan, "%-10.5lE", NAN, double)
TEST_SPRINTF(lE_width_prec_plus_nan, "%+10.5lE", NAN, double)
TEST_SPRINTF(lE_width_prec_spac_nan, "% 10.5lE", NAN, double)
TEST_SPRINTF(lE_width_prec_hash_nan, "%#10.5lE", NAN, double)
TEST_SPRINTF(lE_width_prec_fzer_nan, "%010.5lE", NAN, double)
TEST_SPRINTF(lE_width_prec_mins_inf, "%-10.5lE", INFINITY, double)
TEST_SPRINTF(lE_width_prec_plus_inf, "%+10.5lE", INFINITY, double)
TEST_SPRINTF(lE_width_prec_spac_inf, "% 10.5lE", INFINITY, double)
TEST_SPRINTF(lE_width_prec_hash_inf, "%#10.5lE", INFINITY, double)
TEST_SPRINTF(lE_width_prec_fzer_inf, "%010.5lE", INFINITY, double)
TEST_SPRINTF(lE_width_prec_mins_ng_inf, "%-10.5lE", -INFINITY, double)
TEST_SPRINTF(lE_width_prec_plus_ng_inf, "%+10.5lE", -INFINITY, double)
TEST_SPRINTF(lE_width_prec_spac_ng_inf, "% 10.5lE", -INFINITY, double)
TEST_SPRINTF(lE_width_prec_hash_ng_inf, "%#10.5lE", -INFINITY, double)
TEST_SPRINTF(lE_width_prec_fzer_ng_inf, "%010.5lE", -INFINITY, double)

TEST_SPRINTF(lE_zrwth_zrpc_plus_nan, "%+0.0lE", NAN, double)
TEST_SPRINTF(lE_zrwth_zrpc_spac_nan, "% 0.0lE", NAN, double)
TEST_SPRINTF(lE_zrwth_zrpc_hash_nan, "%#0.0lE", NAN, double)
TEST_SPRINTF(lE_zrwth_zrpc_plus_inf, "%+0.0lE", INFINITY, double)
TEST_SPRINTF(lE_zrwth_zrpc_spac_inf, "% 0.0lE", INFINITY, double)
TEST_SPRINTF(lE_zrwth_zrpc_hash_inf, "%#0.0lE", INFINITY, double)
TEST_SPRINTF(lE_zrwth_zrpc_plus_ng_inf, "%+0.0lE", -INFINITY, double)
TEST_SPRINTF(lE_zrwth_zrpc_spac_ng_inf, "% 0.0lE", -INFINITY, double)
TEST_SPRINTF(lE_zrwth_zrpc_hash_ng_inf, "%#0.0lE", -INFINITY, double)

TEST_SPRINTF_2(lE_dynamic_prec_nan, "%.*lE", 5, NAN, double)
TEST_SPRINTF_2(lE_dynamic_prec_inf, "%.*lE", 5, INFINITY, double)
TEST_SPRINTF_2(lE_dynamic_prec_ng_inf, "%.*lE", 5, -INFINITY, double)

TEST_SPRINTF_2(lE_dynamic_width_nan, "%*lE", 10, NAN, double)
TEST_SPRINTF_2(lE_dynamic_width_inf, "%*lE", 10, INFINITY, double)
TEST_SPRINTF_2(lE_dynamic_width_ng_inf, "%*lE", 10, -INFINITY, double)

TEST_SPRINTF_3(lE_dynamic_width_prec_nan, "%*.*lE", 10, 5, NAN, double)
TEST_SPRINTF_3(lE_dynamic_width_prec_inf, "%*.*lE", 10, 5, INFINITY, double)
TEST_SPRINTF_3(lE_dynamic_width_prec_ng_inf, "%*.*lE", 10, 5, -INFINITY, double)

// =========================================================================

TEST_SPRINTF(lf_mins_nan, "%-lf", NAN, double)
TEST_SPRINTF(lf_plus_nan, "%+lf", NAN, double)
TEST_SPRINTF(lf_spac_nan, "% lf", NAN, double)
TEST_SPRINTF(lf_hash_nan, "%#lf", NAN, double)
TEST_SPRINTF(lf_fzer_nan, "%0lf", NAN, double)
TEST_SPRINTF(lf_mins_inf, "%-lf", INFINITY, double)
TEST_SPRINTF(lf_plus_inf, "%+lf", INFINITY, double)
TEST_SPRINTF(lf_spac_inf, "% lf", INFINITY, double)
TEST_SPRINTF(lf_hash_inf, "%#lf", INFINITY, double)
TEST_SPRINTF(lf_fzer_inf, "%0lf", INFINITY, double)
TEST_SPRINTF(lf_mins_ng_inf, "%-lf", -INFINITY, double)
TEST_SPRINTF(lf_plus_ng_inf, "%+lf", -INFINITY, double)
TEST_SPRINTF(lf_spac_ng_inf, "% lf", -INFINITY, double)
TEST_SPRINTF(lf_hash_ng_inf, "%#lf", -INFINITY, double)
TEST_SPRINTF(lf_fzer_ng_inf, "%0lf", -INFINITY, double)

TEST_SPRINTF(lf_width_nan, "%5lf", NAN, double)
TEST_SPRINTF(lf_zrpc_nan, "%.0lf", NAN, double)
TEST_SPRINTF(lf_prec_nan, "%.5lf", NAN, double)
TEST_SPRINTF(lf_width_inf, "%5lf", INFINITY, double)
TEST_SPRINTF(lf_zrpc_inf, "%.0lf", INFINITY, double)
TEST_SPRINTF(lf_prec_inf, "%.5lf", INFINITY, double)
TEST_SPRINTF(lf_width_ng_inf, "%5lf", -INFINITY, double)
TEST_SPRINTF(lf_zrpc_ng_inf, "%.0lf", -INFINITY, double)
TEST_SPRINTF(lf_prec_ng_inf, "%.5lf", -INFINITY, double)

TEST_SPRINTF(lf_width_prec_nan, "%10.5lf", NAN, double)
TEST_SPRINTF(lf_width_prec_inf, "%10.5lf", INFINITY, double)
TEST_SPRINTF(lf_width_prec_ng_inf, "%10.5lf", -INFINITY, double)

TEST_SPRINTF(lf_width_mins_nan, "%-5lf", NAN, double)
TEST_SPRINTF(lf_width_plus_nan, "%+5lf", NAN, double)
TEST_SPRINTF(lf_width_spac_nan, "% 5lf", NAN, double)
TEST_SPRINTF(lf_width_hash_nan, "%#5lf", NAN, double)
TEST_SPRINTF(lf_width_fzer_nan, "%05lf", NAN, double)
TEST_SPRINTF(lf_width_mins_inf, "%-5lf", INFINITY, double)
TEST_SPRINTF(lf_width_plus_inf, "%+5lf", INFINITY, double)
TEST_SPRINTF(lf_width_spac_inf, "% 5lf", INFINITY, double)
TEST_SPRINTF(lf_width_hash_inf, "%#5lf", INFINITY, double)
TEST_SPRINTF(lf_width_fzer_inf, "%05lf", INFINITY, double)
TEST_SPRINTF(lf_width_mins_ng_inf, "%-5lf", -INFINITY, double)
TEST_SPRINTF(lf_width_plus_ng_inf, "%+5lf", -INFINITY, double)
TEST_SPRINTF(lf_width_spac_ng_inf, "% 5lf", -INFINITY, double)
TEST_SPRINTF(lf_width_hash_ng_inf, "%#5lf", -INFINITY, double)
TEST_SPRINTF(lf_width_fzer_ng_inf, "%05lf", -INFINITY, double)

TEST_SPRINTF(lf_zrwth_plus_nan, "%+0lf", NAN, double)
TEST_SPRINTF(lf_zrwth_spac_nan, "% 0lf", NAN, double)
TEST_SPRINTF(lf_zrwth_hash_nan, "%#0lf", NAN, double)
TEST_SPRINTF(lf_zrwth_plus_inf, "%+0lf", INFINITY, double)
TEST_SPRINTF(lf_zrwth_spac_inf, "% 0lf", INFINITY, double)
TEST_SPRINTF(lf_zrwth_hash_inf, "%#0lf", INFINITY, double)
TEST_SPRINTF(lf_zrwth_plus_ng_inf, "%+0lf", -INFINITY, double)
TEST_SPRINTF(lf_zrwth_spac_ng_inf, "% 0lf", -INFINITY, double)
TEST_SPRINTF(lf_zrwth_hash_ng_inf, "%#0lf", -INFINITY, double)

TEST_SPRINTF(lf_prec_mins_nan, "%-.5lf", NAN, double)
TEST_SPRINTF(lf_prec_plus_nan, "%+.5lf", NAN, double)
TEST_SPRINTF(lf_prec_spac_nan, "% .5lf", NAN, double)
TEST_SPRINTF(lf_prec_hash_nan, "%#.5lf", NAN, double)
TEST_SPRINTF(lf_prec_fzer_nan, "%0.5lf", NAN, double)
TEST_SPRINTF(lf_prec_mins_inf, "%-.5lf", INFINITY, double)
TEST_SPRINTF(lf_prec_plus_inf, "%+.5lf", INFINITY, double)
TEST_SPRINTF(lf_prec_spac_inf, "% .5lf", INFINITY, double)
TEST_SPRINTF(lf_prec_hash_inf, "%#.5lf", INFINITY, double)
TEST_SPRINTF(lf_prec_fzer_inf, "%0.5lf", INFINITY, double)
TEST_SPRINTF(lf_prec_mins_ng_inf, "%-.5lf", -INFINITY, double)
TEST_SPRINTF(lf_prec_plus_ng_inf, "%+.5lf", -INFINITY, double)
TEST_SPRINTF(lf_prec_spac_ng_inf, "% .5lf", -INFINITY, double)
TEST_SPRINTF(lf_prec_hash_ng_inf, "%#.5lf", -INFINITY, double)
TEST_SPRINTF(lf_prec_fzer_ng_inf, "%0.5lf", -INFINITY, double)

TEST_SPRINTF(lf_zrpc_mins_nan, "%-.0lf", NAN, double)
TEST_SPRINTF(lf_zrpc_plus_nan, "%+.0lf", NAN, double)
TEST_SPRINTF(lf_zrpc_spac_nan, "% .0lf", NAN, double)
TEST_SPRINTF(lf_zrpc_hash_nan, "%#.0lf", NAN, double)
TEST_SPRINTF(lf_zrpc_fzer_nan, "%0.0lf", NAN, double)
TEST_SPRINTF(lf_zrpc_mins_inf, "%-.0lf", INFINITY, double)
TEST_SPRINTF(lf_zrpc_plus_inf, "%+.0lf", INFINITY, double)
TEST_SPRINTF(lf_zrpc_spac_inf, "% .0lf", INFINITY, double)
TEST_SPRINTF(lf_zrpc_hash_inf, "%#.0lf", INFINITY, double)
TEST_SPRINTF(lf_zrpc_fzer_inf, "%0.0lf", INFINITY, double)
TEST_SPRINTF(lf_zrpc_mins_ng_inf, "%-.0lf", -INFINITY, double)
TEST_SPRINTF(lf_zrpc_plus_ng_inf, "%+.0lf", -INFINITY, double)
TEST_SPRINTF(lf_zrpc_spac_ng_inf, "% .0lf", -INFINITY, double)
TEST_SPRINTF(lf_zrpc_hash_ng_inf, "%#.0lf", -INFINITY, double)
TEST_SPRINTF(lf_zrpc_fzer_ng_inf, "%0.0lf", -INFINITY, double)

TEST_SPRINTF(lf_width_prec_mins_nan, "%-10.5lf", NAN, double)
TEST_SPRINTF(lf_width_prec_plus_nan, "%+10.5lf", NAN, double)
TEST_SPRINTF(lf_width_prec_spac_nan, "% 10.5lf", NAN, double)
TEST_SPRINTF(lf_width_prec_hash_nan, "%#10.5lf", NAN, double)
TEST_SPRINTF(lf_width_prec_fzer_nan, "%010.5lf", NAN, double)
TEST_SPRINTF(lf_width_prec_mins_inf, "%-10.5lf", INFINITY, double)
TEST_SPRINTF(lf_width_prec_plus_inf, "%+10.5lf", INFINITY, double)
TEST_SPRINTF(lf_width_prec_spac_inf, "% 10.5lf", INFINITY, double)
TEST_SPRINTF(lf_width_prec_hash_inf, "%#10.5lf", INFINITY, double)
TEST_SPRINTF(lf_width_prec_fzer_inf, "%010.5lf", INFINITY, double)
TEST_SPRINTF(lf_width_prec_mins_ng_inf, "%-10.5lf", -INFINITY, double)
TEST_SPRINTF(lf_width_prec_plus_ng_inf, "%+10.5lf", -INFINITY, double)
TEST_SPRINTF(lf_width_prec_spac_ng_inf, "% 10.5lf", -INFINITY, double)
TEST_SPRINTF(lf_width_prec_hash_ng_inf, "%#10.5lf", -INFINITY, double)
TEST_SPRINTF(lf_width_prec_fzer_ng_inf, "%010.5lf", -INFINITY, double)

TEST_SPRINTF(lf_zrwth_zrpc_plus_nan, "%+0.0lf", NAN, double)
TEST_SPRINTF(lf_zrwth_zrpc_spac_nan, "% 0.0lf", NAN, double)
TEST_SPRINTF(lf_zrwth_zrpc_hash_nan, "%#0.0lf", NAN, double)
TEST_SPRINTF(lf_zrwth_zrpc_plus_inf, "%+0.0lf", INFINITY, double)
TEST_SPRINTF(lf_zrwth_zrpc_spac_inf, "% 0.0lf", INFINITY, double)
TEST_SPRINTF(lf_zrwth_zrpc_hash_inf, "%#0.0lf", INFINITY, double)
TEST_SPRINTF(lf_zrwth_zrpc_plus_ng_inf, "%+0.0lf", -INFINITY, double)
TEST_SPRINTF(lf_zrwth_zrpc_spac_ng_inf, "% 0.0lf", -INFINITY, double)
TEST_SPRINTF(lf_zrwth_zrpc_hash_ng_inf, "%#0.0lf", -INFINITY, double)

TEST_SPRINTF_2(lf_dynamic_prec_nan, "%.*lf", 5, NAN, double)
TEST_SPRINTF_2(lf_dynamic_prec_inf, "%.*lf", 5, INFINITY, double)
TEST_SPRINTF_2(lf_dynamic_prec_ng_inf, "%.*lf", 5, -INFINITY, double)

TEST_SPRINTF_2(lf_dynamic_width_nan, "%*lf", 10, NAN, double)
TEST_SPRINTF_2(lf_dynamic_width_inf, "%*lf", 10, INFINITY, double)
TEST_SPRINTF_2(lf_dynamic_width_ng_inf, "%*lf", 10, -INFINITY, double)

TEST_SPRINTF_3(lf_dynamic_width_prec_nan, "%*.*lf", 10, 5, NAN, double)
TEST_SPRINTF_3(lf_dynamic_width_prec_inf, "%*.*lf", 10, 5, INFINITY, double)
TEST_SPRINTF_3(lf_dynamic_width_prec_ng_inf, "%*.*lf", 10, 5, -INFINITY, double)

// =========================================================================

TEST_SPRINTF(lg_mins_nan, "%-lg", NAN, double)
TEST_SPRINTF(lg_plus_nan, "%+lg", NAN, double)
TEST_SPRINTF(lg_spac_nan, "% lg", NAN, double)
TEST_SPRINTF(lg_hash_nan, "%#lg", NAN, double)
TEST_SPRINTF(lg_fzer_nan, "%0lg", NAN, double)
TEST_SPRINTF(lg_mins_inf, "%-lg", INFINITY, double)
TEST_SPRINTF(lg_plus_inf, "%+lg", INFINITY, double)
TEST_SPRINTF(lg_spac_inf, "% lg", INFINITY, double)
TEST_SPRINTF(lg_hash_inf, "%#lg", INFINITY, double)
TEST_SPRINTF(lg_fzer_inf, "%0lg", INFINITY, double)
TEST_SPRINTF(lg_mins_ng_inf, "%-lg", -INFINITY, double)
TEST_SPRINTF(lg_plus_ng_inf, "%+lg", -INFINITY, double)
TEST_SPRINTF(lg_spac_ng_inf, "% lg", -INFINITY, double)
TEST_SPRINTF(lg_hash_ng_inf, "%#lg", -INFINITY, double)
TEST_SPRINTF(lg_fzer_ng_inf, "%0lg", -INFINITY, double)

TEST_SPRINTF(lg_width_nan, "%5lg", NAN, double)
TEST_SPRINTF(lg_zrpc_nan, "%.0lg", NAN, double)
TEST_SPRINTF(lg_prec_nan, "%.5lg", NAN, double)
TEST_SPRINTF(lg_width_inf, "%5lg", INFINITY, double)
TEST_SPRINTF(lg_zrpc_inf, "%.0lg", INFINITY, double)
TEST_SPRINTF(lg_prec_inf, "%.5lg", INFINITY, double)
TEST_SPRINTF(lg_width_ng_inf, "%5lg", -INFINITY, double)
TEST_SPRINTF(lg_zrpc_ng_inf, "%.0lg", -INFINITY, double)
TEST_SPRINTF(lg_prec_ng_inf, "%.5lg", -INFINITY, double)

TEST_SPRINTF(lg_width_prec_nan, "%10.5lg", NAN, double)
TEST_SPRINTF(lg_width_prec_inf, "%10.5lg", INFINITY, double)
TEST_SPRINTF(lg_width_prec_ng_inf, "%10.5lg", -INFINITY, double)

TEST_SPRINTF(lg_width_mins_nan, "%-5lg", NAN, double)
TEST_SPRINTF(lg_width_plus_nan, "%+5lg", NAN, double)
TEST_SPRINTF(lg_width_spac_nan, "% 5lg", NAN, double)
TEST_SPRINTF(lg_width_hash_nan, "%#5lg", NAN, double)
TEST_SPRINTF(lg_width_fzer_nan, "%05lg", NAN, double)
TEST_SPRINTF(lg_width_mins_inf, "%-5lg", INFINITY, double)
TEST_SPRINTF(lg_width_plus_inf, "%+5lg", INFINITY, double)
TEST_SPRINTF(lg_width_spac_inf, "% 5lg", INFINITY, double)
TEST_SPRINTF(lg_width_hash_inf, "%#5lg", INFINITY, double)
TEST_SPRINTF(lg_width_fzer_inf, "%05lg", INFINITY, double)
TEST_SPRINTF(lg_width_mins_ng_inf, "%-5lg", -INFINITY, double)
TEST_SPRINTF(lg_width_plus_ng_inf, "%+5lg", -INFINITY, double)
TEST_SPRINTF(lg_width_spac_ng_inf, "% 5lg", -INFINITY, double)
TEST_SPRINTF(lg_width_hash_ng_inf, "%#5lg", -INFINITY, double)
TEST_SPRINTF(lg_width_fzer_ng_inf, "%05lg", -INFINITY, double)

TEST_SPRINTF(lg_zrwth_plus_nan, "%+0lg", NAN, double)
TEST_SPRINTF(lg_zrwth_spac_nan, "% 0lg", NAN, double)
TEST_SPRINTF(lg_zrwth_hash_nan, "%#0lg", NAN, double)
TEST_SPRINTF(lg_zrwth_plus_inf, "%+0lg", INFINITY, double)
TEST_SPRINTF(lg_zrwth_spac_inf, "% 0lg", INFINITY, double)
TEST_SPRINTF(lg_zrwth_hash_inf, "%#0lg", INFINITY, double)
TEST_SPRINTF(lg_zrwth_plus_ng_inf, "%+0lg", -INFINITY, double)
TEST_SPRINTF(lg_zrwth_spac_ng_inf, "% 0lg", -INFINITY, double)
TEST_SPRINTF(lg_zrwth_hash_ng_inf, "%#0lg", -INFINITY, double)

TEST_SPRINTF(lg_prec_mins_nan, "%-.5lg", NAN, double)
TEST_SPRINTF(lg_prec_plus_nan, "%+.5lg", NAN, double)
TEST_SPRINTF(lg_prec_spac_nan, "% .5lg", NAN, double)
TEST_SPRINTF(lg_prec_hash_nan, "%#.5lg", NAN, double)
TEST_SPRINTF(lg_prec_fzer_nan, "%0.5lg", NAN, double)
TEST_SPRINTF(lg_prec_mins_inf, "%-.5lg", INFINITY, double)
TEST_SPRINTF(lg_prec_plus_inf, "%+.5lg", INFINITY, double)
TEST_SPRINTF(lg_prec_spac_inf, "% .5lg", INFINITY, double)
TEST_SPRINTF(lg_prec_hash_inf, "%#.5lg", INFINITY, double)
TEST_SPRINTF(lg_prec_fzer_inf, "%0.5lg", INFINITY, double)
TEST_SPRINTF(lg_prec_mins_ng_inf, "%-.5lg", -INFINITY, double)
TEST_SPRINTF(lg_prec_plus_ng_inf, "%+.5lg", -INFINITY, double)
TEST_SPRINTF(lg_prec_spac_ng_inf, "% .5lg", -INFINITY, double)
TEST_SPRINTF(lg_prec_hash_ng_inf, "%#.5lg", -INFINITY, double)
TEST_SPRINTF(lg_prec_fzer_ng_inf, "%0.5lg", -INFINITY, double)

TEST_SPRINTF(lg_zrpc_mins_nan, "%-.0lg", NAN, double)
TEST_SPRINTF(lg_zrpc_plus_nan, "%+.0lg", NAN, double)
TEST_SPRINTF(lg_zrpc_spac_nan, "% .0lg", NAN, double)
TEST_SPRINTF(lg_zrpc_hash_nan, "%#.0lg", NAN, double)
TEST_SPRINTF(lg_zrpc_fzer_nan, "%0.0lg", NAN, double)
TEST_SPRINTF(lg_zrpc_mins_inf, "%-.0lg", INFINITY, double)
TEST_SPRINTF(lg_zrpc_plus_inf, "%+.0lg", INFINITY, double)
TEST_SPRINTF(lg_zrpc_spac_inf, "% .0lg", INFINITY, double)
TEST_SPRINTF(lg_zrpc_hash_inf, "%#.0lg", INFINITY, double)
TEST_SPRINTF(lg_zrpc_fzer_inf, "%0.0lg", INFINITY, double)
TEST_SPRINTF(lg_zrpc_mins_ng_inf, "%-.0lg", -INFINITY, double)
TEST_SPRINTF(lg_zrpc_plus_ng_inf, "%+.0lg", -INFINITY, double)
TEST_SPRINTF(lg_zrpc_spac_ng_inf, "% .0lg", -INFINITY, double)
TEST_SPRINTF(lg_zrpc_hash_ng_inf, "%#.0lg", -INFINITY, double)
TEST_SPRINTF(lg_zrpc_fzer_ng_inf, "%0.0lg", -INFINITY, double)

TEST_SPRINTF(lg_width_prec_mins_nan, "%-10.5lg", NAN, double)
TEST_SPRINTF(lg_width_prec_plus_nan, "%+10.5lg", NAN, double)
TEST_SPRINTF(lg_width_prec_spac_nan, "% 10.5lg", NAN, double)
TEST_SPRINTF(lg_width_prec_hash_nan, "%#10.5lg", NAN, double)
TEST_SPRINTF(lg_width_prec_fzer_nan, "%010.5lg", NAN, double)
TEST_SPRINTF(lg_width_prec_mins_inf, "%-10.5lg", INFINITY, double)
TEST_SPRINTF(lg_width_prec_plus_inf, "%+10.5lg", INFINITY, double)
TEST_SPRINTF(lg_width_prec_spac_inf, "% 10.5lg", INFINITY, double)
TEST_SPRINTF(lg_width_prec_hash_inf, "%#10.5lg", INFINITY, double)
TEST_SPRINTF(lg_width_prec_fzer_inf, "%010.5lg", INFINITY, double)
TEST_SPRINTF(lg_width_prec_mins_ng_inf, "%-10.5lg", -INFINITY, double)
TEST_SPRINTF(lg_width_prec_plus_ng_inf, "%+10.5lg", -INFINITY, double)
TEST_SPRINTF(lg_width_prec_spac_ng_inf, "% 10.5lg", -INFINITY, double)
TEST_SPRINTF(lg_width_prec_hash_ng_inf, "%#10.5lg", -INFINITY, double)
TEST_SPRINTF(lg_width_prec_fzer_ng_inf, "%010.5lg", -INFINITY, double)

TEST_SPRINTF(lg_zrwth_zrpc_plus_nan, "%+0.0lg", NAN, double)
TEST_SPRINTF(lg_zrwth_zrpc_spac_nan, "% 0.0lg", NAN, double)
TEST_SPRINTF(lg_zrwth_zrpc_hash_nan, "%#0.0lg", NAN, double)
TEST_SPRINTF(lg_zrwth_zrpc_plus_inf, "%+0.0lg", INFINITY, double)
TEST_SPRINTF(lg_zrwth_zrpc_spac_inf, "% 0.0lg", INFINITY, double)
TEST_SPRINTF(lg_zrwth_zrpc_hash_inf, "%#0.0lg", INFINITY, double)
TEST_SPRINTF(lg_zrwth_zrpc_plus_ng_inf, "%+0.0lg", -INFINITY, double)
TEST_SPRINTF(lg_zrwth_zrpc_spac_ng_inf, "% 0.0lg", -INFINITY, double)
TEST_SPRINTF(lg_zrwth_zrpc_hash_ng_inf, "%#0.0lg", -INFINITY, double)

TEST_SPRINTF_2(lg_dynamic_prec_nan, "%.*lg", 5, NAN, double)
TEST_SPRINTF_2(lg_dynamic_prec_inf, "%.*lg", 5, INFINITY, double)
TEST_SPRINTF_2(lg_dynamic_prec_ng_inf, "%.*lg", 5, -INFINITY, double)

TEST_SPRINTF_2(lg_dynamic_width_nan, "%*lg", 10, NAN, double)
TEST_SPRINTF_2(lg_dynamic_width_inf, "%*lg", 10, INFINITY, double)
TEST_SPRINTF_2(lg_dynamic_width_ng_inf, "%*lg", 10, -INFINITY, double)

TEST_SPRINTF_3(lg_dynamic_width_prec_nan, "%*.*lg", 10, 5, NAN, double)
TEST_SPRINTF_3(lg_dynamic_width_prec_inf, "%*.*lg", 10, 5, INFINITY, double)
TEST_SPRINTF_3(lg_dynamic_width_prec_ng_inf, "%*.*lg", 10, 5, -INFINITY, double)

// =========================================================================

TEST_SPRINTF(lG_mins_nan, "%-lG", NAN, double)
TEST_SPRINTF(lG_plus_nan, "%+lG", NAN, double)
TEST_SPRINTF(lG_spac_nan, "% lG", NAN, double)
TEST_SPRINTF(lG_hash_nan, "%#lG", NAN, double)
TEST_SPRINTF(lG_fzer_nan, "%0lG", NAN, double)
TEST_SPRINTF(lG_mins_inf, "%-lG", INFINITY, double)
TEST_SPRINTF(lG_plus_inf, "%+lG", INFINITY, double)
TEST_SPRINTF(lG_spac_inf, "% lG", INFINITY, double)
TEST_SPRINTF(lG_hash_inf, "%#lG", INFINITY, double)
TEST_SPRINTF(lG_fzer_inf, "%0lG", INFINITY, double)
TEST_SPRINTF(lG_mins_ng_inf, "%-lG", -INFINITY, double)
TEST_SPRINTF(lG_plus_ng_inf, "%+lG", -INFINITY, double)
TEST_SPRINTF(lG_spac_ng_inf, "% lG", -INFINITY, double)
TEST_SPRINTF(lG_hash_ng_inf, "%#lG", -INFINITY, double)
TEST_SPRINTF(lG_fzer_ng_inf, "%0lG", -INFINITY, double)

TEST_SPRINTF(lG_width_nan, "%5lG", NAN, double)
TEST_SPRINTF(lG_zrpc_nan, "%.0lG", NAN, double)
TEST_SPRINTF(lG_prec_nan, "%.5lG", NAN, double)
TEST_SPRINTF(lG_width_inf, "%5lG", INFINITY, double)
TEST_SPRINTF(lG_zrpc_inf, "%.0lG", INFINITY, double)
TEST_SPRINTF(lG_prec_inf, "%.5lG", INFINITY, double)
TEST_SPRINTF(lG_width_ng_inf, "%5lG", -INFINITY, double)
TEST_SPRINTF(lG_zrpc_ng_inf, "%.0lG", -INFINITY, double)
TEST_SPRINTF(lG_prec_ng_inf, "%.5lG", -INFINITY, double)

TEST_SPRINTF(lG_width_prec_nan, "%10.5lG", NAN, double)
TEST_SPRINTF(lG_width_prec_inf, "%10.5lG", INFINITY, double)
TEST_SPRINTF(lG_width_prec_ng_inf, "%10.5lG", -INFINITY, double)

TEST_SPRINTF(lG_width_mins_nan, "%-5lG", NAN, double)
TEST_SPRINTF(lG_width_plus_nan, "%+5lG", NAN, double)
TEST_SPRINTF(lG_width_spac_nan, "% 5lG", NAN, double)
TEST_SPRINTF(lG_width_hash_nan, "%#5lG", NAN, double)
TEST_SPRINTF(lG_width_fzer_nan, "%05lG", NAN, double)
TEST_SPRINTF(lG_width_mins_inf, "%-5lG", INFINITY, double)
TEST_SPRINTF(lG_width_plus_inf, "%+5lG", INFINITY, double)
TEST_SPRINTF(lG_width_spac_inf, "% 5lG", INFINITY, double)
TEST_SPRINTF(lG_width_hash_inf, "%#5lG", INFINITY, double)
TEST_SPRINTF(lG_width_fzer_inf, "%05lG", INFINITY, double)
TEST_SPRINTF(lG_width_mins_ng_inf, "%-5lG", -INFINITY, double)
TEST_SPRINTF(lG_width_plus_ng_inf, "%+5lG", -INFINITY, double)
TEST_SPRINTF(lG_width_spac_ng_inf, "% 5lG", -INFINITY, double)
TEST_SPRINTF(lG_width_hash_ng_inf, "%#5lG", -INFINITY, double)
TEST_SPRINTF(lG_width_fzer_ng_inf, "%05lG", -INFINITY, double)

TEST_SPRINTF(lG_zrwth_plus_nan, "%+0lG", NAN, double)
TEST_SPRINTF(lG_zrwth_spac_nan, "% 0lG", NAN, double)
TEST_SPRINTF(lG_zrwth_hash_nan, "%#0lG", NAN, double)
TEST_SPRINTF(lG_zrwth_plus_inf, "%+0lG", INFINITY, double)
TEST_SPRINTF(lG_zrwth_spac_inf, "% 0lG", INFINITY, double)
TEST_SPRINTF(lG_zrwth_hash_inf, "%#0lG", INFINITY, double)
TEST_SPRINTF(lG_zrwth_plus_ng_inf, "%+0lG", -INFINITY, double)
TEST_SPRINTF(lG_zrwth_spac_ng_inf, "% 0lG", -INFINITY, double)
TEST_SPRINTF(lG_zrwth_hash_ng_inf, "%#0lG", -INFINITY, double)

TEST_SPRINTF(lG_prec_mins_nan, "%-.5lG", NAN, double)
TEST_SPRINTF(lG_prec_plus_nan, "%+.5lG", NAN, double)
TEST_SPRINTF(lG_prec_spac_nan, "% .5lG", NAN, double)
TEST_SPRINTF(lG_prec_hash_nan, "%#.5lG", NAN, double)
TEST_SPRINTF(lG_prec_fzer_nan, "%0.5lG", NAN, double)
TEST_SPRINTF(lG_prec_mins_inf, "%-.5lG", INFINITY, double)
TEST_SPRINTF(lG_prec_plus_inf, "%+.5lG", INFINITY, double)
TEST_SPRINTF(lG_prec_spac_inf, "% .5lG", INFINITY, double)
TEST_SPRINTF(lG_prec_hash_inf, "%#.5lG", INFINITY, double)
TEST_SPRINTF(lG_prec_fzer_inf, "%0.5lG", INFINITY, double)
TEST_SPRINTF(lG_prec_mins_ng_inf, "%-.5lG", -INFINITY, double)
TEST_SPRINTF(lG_prec_plus_ng_inf, "%+.5lG", -INFINITY, double)
TEST_SPRINTF(lG_prec_spac_ng_inf, "% .5lG", -INFINITY, double)
TEST_SPRINTF(lG_prec_hash_ng_inf, "%#.5lG", -INFINITY, double)
TEST_SPRINTF(lG_prec_fzer_ng_inf, "%0.5lG", -INFINITY, double)

TEST_SPRINTF(lG_zrpc_mins_nan, "%-.0lG", NAN, double)
TEST_SPRINTF(lG_zrpc_plus_nan, "%+.0lG", NAN, double)
TEST_SPRINTF(lG_zrpc_spac_nan, "% .0lG", NAN, double)
TEST_SPRINTF(lG_zrpc_hash_nan, "%#.0lG", NAN, double)
TEST_SPRINTF(lG_zrpc_fzer_nan, "%0.0lG", NAN, double)
TEST_SPRINTF(lG_zrpc_mins_inf, "%-.0lG", INFINITY, double)
TEST_SPRINTF(lG_zrpc_plus_inf, "%+.0lG", INFINITY, double)
TEST_SPRINTF(lG_zrpc_spac_inf, "% .0lG", INFINITY, double)
TEST_SPRINTF(lG_zrpc_hash_inf, "%#.0lG", INFINITY, double)
TEST_SPRINTF(lG_zrpc_fzer_inf, "%0.0lG", INFINITY, double)
TEST_SPRINTF(lG_zrpc_mins_ng_inf, "%-.0lG", -INFINITY, double)
TEST_SPRINTF(lG_zrpc_plus_ng_inf, "%+.0lG", -INFINITY, double)
TEST_SPRINTF(lG_zrpc_spac_ng_inf, "% .0lG", -INFINITY, double)
TEST_SPRINTF(lG_zrpc_hash_ng_inf, "%#.0lG", -INFINITY, double)
TEST_SPRINTF(lG_zrpc_fzer_ng_inf, "%0.0lG", -INFINITY, double)

TEST_SPRINTF(lG_width_prec_mins_nan, "%-10.5lG", NAN, double)
TEST_SPRINTF(lG_width_prec_plus_nan, "%+10.5lG", NAN, double)
TEST_SPRINTF(lG_width_prec_spac_nan, "% 10.5lG", NAN, double)
TEST_SPRINTF(lG_width_prec_hash_nan, "%#10.5lG", NAN, double)
TEST_SPRINTF(lG_width_prec_fzer_nan, "%010.5lG", NAN, double)
TEST_SPRINTF(lG_width_prec_mins_inf, "%-10.5lG", INFINITY, double)
TEST_SPRINTF(lG_width_prec_plus_inf, "%+10.5lG", INFINITY, double)
TEST_SPRINTF(lG_width_prec_spac_inf, "% 10.5lG", INFINITY, double)
TEST_SPRINTF(lG_width_prec_hash_inf, "%#10.5lG", INFINITY, double)
TEST_SPRINTF(lG_width_prec_fzer_inf, "%010.5lG", INFINITY, double)
TEST_SPRINTF(lG_width_prec_mins_ng_inf, "%-10.5lG", -INFINITY, double)
TEST_SPRINTF(lG_width_prec_plus_ng_inf, "%+10.5lG", -INFINITY, double)
TEST_SPRINTF(lG_width_prec_spac_ng_inf, "% 10.5lG", -INFINITY, double)
TEST_SPRINTF(lG_width_prec_hash_ng_inf, "%#10.5lG", -INFINITY, double)
TEST_SPRINTF(lG_width_prec_fzer_ng_inf, "%010.5lG", -INFINITY, double)

TEST_SPRINTF(lG_zrwth_zrpc_plus_nan, "%+0.0lG", NAN, double)
TEST_SPRINTF(lG_zrwth_zrpc_spac_nan, "% 0.0lG", NAN, double)
TEST_SPRINTF(lG_zrwth_zrpc_hash_nan, "%#0.0lG", NAN, double)
TEST_SPRINTF(lG_zrwth_zrpc_plus_inf, "%+0.0lG", INFINITY, double)
TEST_SPRINTF(lG_zrwth_zrpc_spac_inf, "% 0.0lG", INFINITY, double)
TEST_SPRINTF(lG_zrwth_zrpc_hash_inf, "%#0.0lG", INFINITY, double)
TEST_SPRINTF(lG_zrwth_zrpc_plus_ng_inf, "%+0.0lG", -INFINITY, double)
TEST_SPRINTF(lG_zrwth_zrpc_spac_ng_inf, "% 0.0lG", -INFINITY, double)
TEST_SPRINTF(lG_zrwth_zrpc_hash_ng_inf, "%#0.0lG", -INFINITY, double)

TEST_SPRINTF_2(lG_dynamic_prec_nan, "%.*lG", 5, NAN, double)
TEST_SPRINTF_2(lG_dynamic_prec_inf, "%.*lG", 5, INFINITY, double)
TEST_SPRINTF_2(lG_dynamic_prec_ng_inf, "%.*lG", 5, -INFINITY, double)

TEST_SPRINTF_2(lG_dynamic_width_nan, "%*lG", 10, NAN, double)
TEST_SPRINTF_2(lG_dynamic_width_inf, "%*lG", 10, INFINITY, double)
TEST_SPRINTF_2(lG_dynamic_width_ng_inf, "%*lG", 10, -INFINITY, double)

TEST_SPRINTF_3(lG_dynamic_width_prec_nan, "%*.*lG", 10, 5, NAN, double)
TEST_SPRINTF_3(lG_dynamic_width_prec_inf, "%*.*lG", 10, 5, INFINITY, double)
TEST_SPRINTF_3(lG_dynamic_width_prec_ng_inf, "%*.*lG", 10, 5, -INFINITY, double)

// =========================================================================

TEST_SPRINTF(Le_mins_nan, "%-Le", (long double)NAN, long double)
TEST_SPRINTF(Le_plus_nan, "%+Le", (long double)NAN, long double)
TEST_SPRINTF(Le_spac_nan, "% Le", (long double)NAN, long double)
TEST_SPRINTF(Le_hash_nan, "%#Le", (long double)NAN, long double)
TEST_SPRINTF(Le_fzer_nan, "%0Le", (long double)NAN, long double)
TEST_SPRINTF(Le_mins_inf, "%-Le", (long double)INFINITY, long double)
TEST_SPRINTF(Le_plus_inf, "%+Le", (long double)INFINITY, long double)
TEST_SPRINTF(Le_spac_inf, "% Le", (long double)INFINITY, long double)
TEST_SPRINTF(Le_hash_inf, "%#Le", (long double)INFINITY, long double)
TEST_SPRINTF(Le_fzer_inf, "%0Le", (long double)INFINITY, long double)
TEST_SPRINTF(Le_mins_ng_inf, "%-Le", (long double)(-INFINITY), long double)
TEST_SPRINTF(Le_plus_ng_inf, "%+Le", (long double)(-INFINITY), long double)
TEST_SPRINTF(Le_spac_ng_inf, "% Le", (long double)(-INFINITY), long double)
TEST_SPRINTF(Le_hash_ng_inf, "%#Le", (long double)(-INFINITY), long double)
TEST_SPRINTF(Le_fzer_ng_inf, "%0Le", (long double)(-INFINITY), long double)

TEST_SPRINTF(Le_width_nan, "%5Le", (long double)NAN, long double)
TEST_SPRINTF(Le_zrpc_nan, "%.0Le", (long double)NAN, long double)
TEST_SPRINTF(Le_prec_nan, "%.5Le", (long double)NAN, long double)
TEST_SPRINTF(Le_width_inf, "%5Le", (long double)INFINITY, long double)
TEST_SPRINTF(Le_zrpc_inf, "%.0Le", (long double)INFINITY, long double)
TEST_SPRINTF(Le_prec_inf, "%.5Le", (long double)INFINITY, long double)
TEST_SPRINTF(Le_width_ng_inf, "%5Le", (long double)(-INFINITY), long double)
TEST_SPRINTF(Le_zrpc_ng_inf, "%.0Le", (long double)(-INFINITY), long double)
TEST_SPRINTF(Le_prec_ng_inf, "%.5Le", (long double)(-INFINITY), long double)

TEST_SPRINTF(Le_width_prec_nan, "%10.5Le", (long double)NAN, long double)
TEST_SPRINTF(Le_width_prec_inf, "%10.5Le", (long double)INFINITY, long double)
TEST_SPRINTF(Le_width_prec_ng_inf, "%10.5Le", (long double)(-INFINITY),
             long double)

TEST_SPRINTF(Le_width_mins_nan, "%-5Le", (long double)NAN, long double)
TEST_SPRINTF(Le_width_plus_nan, "%+5Le", (long double)NAN, long double)
TEST_SPRINTF(Le_width_spac_nan, "% 5Le", (long double)NAN, long double)
TEST_SPRINTF(Le_width_hash_nan, "%#5Le", (long double)NAN, long double)
TEST_SPRINTF(Le_width_fzer_nan, "%05Le", (long double)NAN, long double)
TEST_SPRINTF(Le_width_mins_inf, "%-5Le", (long double)INFINITY, long double)
TEST_SPRINTF(Le_width_plus_inf, "%+5Le", (long double)INFINITY, long double)
TEST_SPRINTF(Le_width_spac_inf, "% 5Le", (long double)INFINITY, long double)
TEST_SPRINTF(Le_width_hash_inf, "%#5Le", (long double)INFINITY, long double)
TEST_SPRINTF(Le_width_fzer_inf, "%05Le", (long double)INFINITY, long double)
TEST_SPRINTF(Le_width_mins_ng_inf, "%-5Le", (long double)(-INFINITY),
             long double)
TEST_SPRINTF(Le_width_plus_ng_inf, "%+5Le", (long double)(-INFINITY),
             long double)
TEST_SPRINTF(Le_width_spac_ng_inf, "% 5Le", (long double)(-INFINITY),
             long double)
TEST_SPRINTF(Le_width_hash_ng_inf, "%#5Le", (long double)(-INFINITY),
             long double)
TEST_SPRINTF(Le_width_fzer_ng_inf, "%05Le", (long double)(-INFINITY),
             long double)

TEST_SPRINTF(Le_zrwth_plus_nan, "%+0Le", (long double)NAN, long double)
TEST_SPRINTF(Le_zrwth_spac_nan, "% 0Le", (long double)NAN, long double)
TEST_SPRINTF(Le_zrwth_hash_nan, "%#0Le", (long double)NAN, long double)
TEST_SPRINTF(Le_zrwth_plus_inf, "%+0Le", (long double)INFINITY, long double)
TEST_SPRINTF(Le_zrwth_spac_inf, "% 0Le", (long double)INFINITY, long double)
TEST_SPRINTF(Le_zrwth_hash_inf, "%#0Le", (long double)INFINITY, long double)
TEST_SPRINTF(Le_zrwth_plus_ng_inf, "%+0Le", (long double)(-INFINITY),
             long double)
TEST_SPRINTF(Le_zrwth_spac_ng_inf, "% 0Le", (long double)(-INFINITY),
             long double)
TEST_SPRINTF(Le_zrwth_hash_ng_inf, "%#0Le", (long double)(-INFINITY),
             long double)

TEST_SPRINTF(Le_prec_mins_nan, "%-.5Le", (long double)NAN, long double)
TEST_SPRINTF(Le_prec_plus_nan, "%+.5Le", (long double)NAN, long double)
TEST_SPRINTF(Le_prec_spac_nan, "% .5Le", (long double)NAN, long double)
TEST_SPRINTF(Le_prec_hash_nan, "%#.5Le", (long double)NAN, long double)
TEST_SPRINTF(Le_prec_fzer_nan, "%0.5Le", (long double)NAN, long double)
TEST_SPRINTF(Le_prec_mins_inf, "%-.5Le", (long double)INFINITY, long double)
TEST_SPRINTF(Le_prec_plus_inf, "%+.5Le", (long double)INFINITY, long double)
TEST_SPRINTF(Le_prec_spac_inf, "% .5Le", (long double)INFINITY, long double)
TEST_SPRINTF(Le_prec_hash_inf, "%#.5Le", (long double)INFINITY, long double)
TEST_SPRINTF(Le_prec_fzer_inf, "%0.5Le", (long double)INFINITY, long double)
TEST_SPRINTF(Le_prec_mins_ng_inf, "%-.5Le", (long double)(-INFINITY),
             long double)
TEST_SPRINTF(Le_prec_plus_ng_inf, "%+.5Le", (long double)(-INFINITY),
             long double)
TEST_SPRINTF(Le_prec_spac_ng_inf, "% .5Le", (long double)(-INFINITY),
             long double)
TEST_SPRINTF(Le_prec_hash_ng_inf, "%#.5Le", (long double)(-INFINITY),
             long double)
TEST_SPRINTF(Le_prec_fzer_ng_inf, "%0.5Le", (long double)(-INFINITY),
             long double)

TEST_SPRINTF(Le_zrpc_mins_nan, "%-.0Le", (long double)NAN, long double)
TEST_SPRINTF(Le_zrpc_plus_nan, "%+.0Le", (long double)NAN, long double)
TEST_SPRINTF(Le_zrpc_spac_nan, "% .0Le", (long double)NAN, long double)
TEST_SPRINTF(Le_zrpc_hash_nan, "%#.0Le", (long double)NAN, long double)
TEST_SPRINTF(Le_zrpc_fzer_nan, "%0.0Le", (long double)NAN, long double)
TEST_SPRINTF(Le_zrpc_mins_inf, "%-.0Le", (long double)INFINITY, long double)
TEST_SPRINTF(Le_zrpc_plus_inf, "%+.0Le", (long double)INFINITY, long double)
TEST_SPRINTF(Le_zrpc_spac_inf, "% .0Le", (long double)INFINITY, long double)
TEST_SPRINTF(Le_zrpc_hash_inf, "%#.0Le", (long double)INFINITY, long double)
TEST_SPRINTF(Le_zrpc_fzer_inf, "%0.0Le", (long double)INFINITY, long double)
TEST_SPRINTF(Le_zrpc_mins_ng_inf, "%-.0Le", (long double)(-INFINITY),
             long double)
TEST_SPRINTF(Le_zrpc_plus_ng_inf, "%+.0Le", (long double)(-INFINITY),
             long double)
TEST_SPRINTF(Le_zrpc_spac_ng_inf, "% .0Le", (long double)(-INFINITY),
             long double)
TEST_SPRINTF(Le_zrpc_hash_ng_inf, "%#.0Le", (long double)(-INFINITY),
             long double)
TEST_SPRINTF(Le_zrpc_fzer_ng_inf, "%0.0Le", (long double)(-INFINITY),
             long double)

TEST_SPRINTF(Le_width_prec_mins_nan, "%-10.5Le", (long double)NAN, long double)
TEST_SPRINTF(Le_width_prec_plus_nan, "%+10.5Le", (long double)NAN, long double)
TEST_SPRINTF(Le_width_prec_spac_nan, "% 10.5Le", (long double)NAN, long double)
TEST_SPRINTF(Le_width_prec_hash_nan, "%#10.5Le", (long double)NAN, long double)
TEST_SPRINTF(Le_width_prec_fzer_nan, "%010.5Le", (long double)NAN, long double)
TEST_SPRINTF(Le_width_prec_mins_inf, "%-10.5Le", (long double)INFINITY,
             long double)
TEST_SPRINTF(Le_width_prec_plus_inf, "%+10.5Le", (long double)INFINITY,
             long double)
TEST_SPRINTF(Le_width_prec_spac_inf, "% 10.5Le", (long double)INFINITY,
             long double)
TEST_SPRINTF(Le_width_prec_hash_inf, "%#10.5Le", (long double)INFINITY,
             long double)
TEST_SPRINTF(Le_width_prec_fzer_inf, "%010.5Le", (long double)INFINITY,
             long double)
TEST_SPRINTF(Le_width_prec_mins_ng_inf, "%-10.5Le", (long double)(-INFINITY),
             long double)
TEST_SPRINTF(Le_width_prec_plus_ng_inf, "%+10.5Le", (long double)(-INFINITY),
             long double)
TEST_SPRINTF(Le_width_prec_spac_ng_inf, "% 10.5Le", (long double)(-INFINITY),
             long double)
TEST_SPRINTF(Le_width_prec_hash_ng_inf, "%#10.5Le", (long double)(-INFINITY),
             long double)
TEST_SPRINTF(Le_width_prec_fzer_ng_inf, "%010.5Le", (long double)(-INFINITY),
             long double)

TEST_SPRINTF(Le_zrwth_zrpc_plus_nan, "%+0.0Le", (long double)NAN, long double)
TEST_SPRINTF(Le_zrwth_zrpc_spac_nan, "% 0.0Le", (long double)NAN, long double)
TEST_SPRINTF(Le_zrwth_zrpc_hash_nan, "%#0.0Le", (long double)NAN, long double)
TEST_SPRINTF(Le_zrwth_zrpc_plus_inf, "%+0.0Le", (long double)INFINITY,
             long double)
TEST_SPRINTF(Le_zrwth_zrpc_spac_inf, "% 0.0Le", (long double)INFINITY,
             long double)
TEST_SPRINTF(Le_zrwth_zrpc_hash_inf, "%#0.0Le", (long double)INFINITY,
             long double)
TEST_SPRINTF(Le_zrwth_zrpc_plus_ng_inf, "%+0.0Le", (long double)(-INFINITY),
             long double)
TEST_SPRINTF(Le_zrwth_zrpc_spac_ng_inf, "% 0.0Le", (long double)(-INFINITY),
             long double)
TEST_SPRINTF(Le_zrwth_zrpc_hash_ng_inf, "%#0.0Le", (long double)(-INFINITY),
             long double)

TEST_SPRINTF_2(Le_dynamic_prec_nan, "%.*Le", 5, (long double)NAN, long double)
TEST_SPRINTF_2(Le_dynamic_prec_inf, "%.*Le", 5, (long double)INFINITY,
               long double)
TEST_SPRINTF_2(Le_dynamic_prec_ng_inf, "%.*Le", 5, (long double)(-INFINITY),
               long double)

TEST_SPRINTF_2(Le_dynamic_width_nan, "%*Le", 10, (long double)NAN, long double)
TEST_SPRINTF_2(Le_dynamic_width_inf, "%*Le", 10, (long double)INFINITY,
               long double)
TEST_SPRINTF_2(Le_dynamic_width_ng_inf, "%*Le", 10, (long double)(-INFINITY),
               long double)

TEST_SPRINTF_3(Le_dynamic_width_prec_nan, "%*.*Le", 10, 5, (long double)NAN,
               long double)
TEST_SPRINTF_3(Le_dynamic_width_prec_inf, "%*.*Le", 10, 5,
               (long double)INFINITY, long double)
TEST_SPRINTF_3(Le_dynamic_width_prec_ng_inf, "%*.*Le", 10, 5,
               (long double)(-INFINITY), long double)

// =========================================================================

TEST_SPRINTF(LE_mins_nan, "%-LE", (long double)NAN, long double)
TEST_SPRINTF(LE_plus_nan, "%+LE", (long double)NAN, long double)
TEST_SPRINTF(LE_spac_nan, "% LE", (long double)NAN, long double)
TEST_SPRINTF(LE_hash_nan, "%#LE", (long double)NAN, long double)
TEST_SPRINTF(LE_fzer_nan, "%0LE", (long double)NAN, long double)
TEST_SPRINTF(LE_mins_inf, "%-LE", (long double)INFINITY, long double)
TEST_SPRINTF(LE_plus_inf, "%+LE", (long double)INFINITY, long double)
TEST_SPRINTF(LE_spac_inf, "% LE", (long double)INFINITY, long double)
TEST_SPRINTF(LE_hash_inf, "%#LE", (long double)INFINITY, long double)
TEST_SPRINTF(LE_fzer_inf, "%0LE", (long double)INFINITY, long double)
TEST_SPRINTF(LE_mins_ng_inf, "%-LE", (long double)(-INFINITY), long double)
TEST_SPRINTF(LE_plus_ng_inf, "%+LE", (long double)(-INFINITY), long double)
TEST_SPRINTF(LE_spac_ng_inf, "% LE", (long double)(-INFINITY), long double)
TEST_SPRINTF(LE_hash_ng_inf, "%#LE", (long double)(-INFINITY), long double)
TEST_SPRINTF(LE_fzer_ng_inf, "%0LE", (long double)(-INFINITY), long double)

TEST_SPRINTF(LE_width_nan, "%5LE", (long double)NAN, long double)
TEST_SPRINTF(LE_zrpc_nan, "%.0LE", (long double)NAN, long double)
TEST_SPRINTF(LE_prec_nan, "%.5LE", (long double)NAN, long double)
TEST_SPRINTF(LE_width_inf, "%5LE", (long double)INFINITY, long double)
TEST_SPRINTF(LE_zrpc_inf, "%.0LE", (long double)INFINITY, long double)
TEST_SPRINTF(LE_prec_inf, "%.5LE", (long double)INFINITY, long double)
TEST_SPRINTF(LE_width_ng_inf, "%5LE", (long double)(-INFINITY), long double)
TEST_SPRINTF(LE_zrpc_ng_inf, "%.0LE", (long double)(-INFINITY), long double)
TEST_SPRINTF(LE_prec_ng_inf, "%.5LE", (long double)(-INFINITY), long double)

TEST_SPRINTF(LE_width_prec_nan, "%10.5LE", (long double)NAN, long double)
TEST_SPRINTF(LE_width_prec_inf, "%10.5LE", (long double)INFINITY, long double)
TEST_SPRINTF(LE_width_prec_ng_inf, "%10.5LE", (long double)(-INFINITY),
             long double)

TEST_SPRINTF(LE_width_mins_nan, "%-5LE", (long double)NAN, long double)
TEST_SPRINTF(LE_width_plus_nan, "%+5LE", (long double)NAN, long double)
TEST_SPRINTF(LE_width_spac_nan, "% 5LE", (long double)NAN, long double)
TEST_SPRINTF(LE_width_hash_nan, "%#5LE", (long double)NAN, long double)
TEST_SPRINTF(LE_width_fzer_nan, "%05LE", (long double)NAN, long double)
TEST_SPRINTF(LE_width_mins_inf, "%-5LE", (long double)INFINITY, long double)
TEST_SPRINTF(LE_width_plus_inf, "%+5LE", (long double)INFINITY, long double)
TEST_SPRINTF(LE_width_spac_inf, "% 5LE", (long double)INFINITY, long double)
TEST_SPRINTF(LE_width_hash_inf, "%#5LE", (long double)INFINITY, long double)
TEST_SPRINTF(LE_width_fzer_inf, "%05LE", (long double)INFINITY, long double)
TEST_SPRINTF(LE_width_mins_ng_inf, "%-5LE", (long double)(-INFINITY),
             long double)
TEST_SPRINTF(LE_width_plus_ng_inf, "%+5LE", (long double)(-INFINITY),
             long double)
TEST_SPRINTF(LE_width_spac_ng_inf, "% 5LE", (long double)(-INFINITY),
             long double)
TEST_SPRINTF(LE_width_hash_ng_inf, "%#5LE", (long double)(-INFINITY),
             long double)
TEST_SPRINTF(LE_width_fzer_ng_inf, "%05LE", (long double)(-INFINITY),
             long double)

TEST_SPRINTF(LE_zrwth_plus_nan, "%+0LE", (long double)NAN, long double)
TEST_SPRINTF(LE_zrwth_spac_nan, "% 0LE", (long double)NAN, long double)
TEST_SPRINTF(LE_zrwth_hash_nan, "%#0LE", (long double)NAN, long double)
TEST_SPRINTF(LE_zrwth_plus_inf, "%+0LE", (long double)INFINITY, long double)
TEST_SPRINTF(LE_zrwth_spac_inf, "% 0LE", (long double)INFINITY, long double)
TEST_SPRINTF(LE_zrwth_hash_inf, "%#0LE", (long double)INFINITY, long double)
TEST_SPRINTF(LE_zrwth_plus_ng_inf, "%+0LE", (long double)(-INFINITY),
             long double)
TEST_SPRINTF(LE_zrwth_spac_ng_inf, "% 0LE", (long double)(-INFINITY),
             long double)
TEST_SPRINTF(LE_zrwth_hash_ng_inf, "%#0LE", (long double)(-INFINITY),
             long double)

TEST_SPRINTF(LE_prec_mins_nan, "%-.5LE", (long double)NAN, long double)
TEST_SPRINTF(LE_prec_plus_nan, "%+.5LE", (long double)NAN, long double)
TEST_SPRINTF(LE_prec_spac_nan, "% .5LE", (long double)NAN, long double)
TEST_SPRINTF(LE_prec_hash_nan, "%#.5LE", (long double)NAN, long double)
TEST_SPRINTF(LE_prec_fzer_nan, "%0.5LE", (long double)NAN, long double)
TEST_SPRINTF(LE_prec_mins_inf, "%-.5LE", (long double)INFINITY, long double)
TEST_SPRINTF(LE_prec_plus_inf, "%+.5LE", (long double)INFINITY, long double)
TEST_SPRINTF(LE_prec_spac_inf, "% .5LE", (long double)INFINITY, long double)
TEST_SPRINTF(LE_prec_hash_inf, "%#.5LE", (long double)INFINITY, long double)
TEST_SPRINTF(LE_prec_fzer_inf, "%0.5LE", (long double)INFINITY, long double)
TEST_SPRINTF(LE_prec_mins_ng_inf, "%-.5LE", (long double)(-INFINITY),
             long double)
TEST_SPRINTF(LE_prec_plus_ng_inf, "%+.5LE", (long double)(-INFINITY),
             long double)
TEST_SPRINTF(LE_prec_spac_ng_inf, "% .5LE", (long double)(-INFINITY),
             long double)
TEST_SPRINTF(LE_prec_hash_ng_inf, "%#.5LE", (long double)(-INFINITY),
             long double)
TEST_SPRINTF(LE_prec_fzer_ng_inf, "%0.5LE", (long double)(-INFINITY),
             long double)

TEST_SPRINTF(LE_zrpc_mins_nan, "%-.0LE", (long double)NAN, long double)
TEST_SPRINTF(LE_zrpc_plus_nan, "%+.0LE", (long double)NAN, long double)
TEST_SPRINTF(LE_zrpc_spac_nan, "% .0LE", (long double)NAN, long double)
TEST_SPRINTF(LE_zrpc_hash_nan, "%#.0LE", (long double)NAN, long double)
TEST_SPRINTF(LE_zrpc_fzer_nan, "%0.0LE", (long double)NAN, long double)
TEST_SPRINTF(LE_zrpc_mins_inf, "%-.0LE", (long double)INFINITY, long double)
TEST_SPRINTF(LE_zrpc_plus_inf, "%+.0LE", (long double)INFINITY, long double)
TEST_SPRINTF(LE_zrpc_spac_inf, "% .0LE", (long double)INFINITY, long double)
TEST_SPRINTF(LE_zrpc_hash_inf, "%#.0LE", (long double)INFINITY, long double)
TEST_SPRINTF(LE_zrpc_fzer_inf, "%0.0LE", (long double)INFINITY, long double)
TEST_SPRINTF(LE_zrpc_mins_ng_inf, "%-.0LE", (long double)(-INFINITY),
             long double)
TEST_SPRINTF(LE_zrpc_plus_ng_inf, "%+.0LE", (long double)(-INFINITY),
             long double)
TEST_SPRINTF(LE_zrpc_spac_ng_inf, "% .0LE", (long double)(-INFINITY),
             long double)
TEST_SPRINTF(LE_zrpc_hash_ng_inf, "%#.0LE", (long double)(-INFINITY),
             long double)
TEST_SPRINTF(LE_zrpc_fzer_ng_inf, "%0.0LE", (long double)(-INFINITY),
             long double)

TEST_SPRINTF(LE_width_prec_mins_nan, "%-10.5LE", (long double)NAN, long double)
TEST_SPRINTF(LE_width_prec_plus_nan, "%+10.5LE", (long double)NAN, long double)
TEST_SPRINTF(LE_width_prec_spac_nan, "% 10.5LE", (long double)NAN, long double)
TEST_SPRINTF(LE_width_prec_hash_nan, "%#10.5LE", (long double)NAN, long double)
TEST_SPRINTF(LE_width_prec_fzer_nan, "%010.5LE", (long double)NAN, long double)
TEST_SPRINTF(LE_width_prec_mins_inf, "%-10.5LE", (long double)INFINITY,
             long double)
TEST_SPRINTF(LE_width_prec_plus_inf, "%+10.5LE", (long double)INFINITY,
             long double)
TEST_SPRINTF(LE_width_prec_spac_inf, "% 10.5LE", (long double)INFINITY,
             long double)
TEST_SPRINTF(LE_width_prec_hash_inf, "%#10.5LE", (long double)INFINITY,
             long double)
TEST_SPRINTF(LE_width_prec_fzer_inf, "%010.5LE", (long double)INFINITY,
             long double)
TEST_SPRINTF(LE_width_prec_mins_ng_inf, "%-10.5LE", (long double)(-INFINITY),
             long double)
TEST_SPRINTF(LE_width_prec_plus_ng_inf, "%+10.5LE", (long double)(-INFINITY),
             long double)
TEST_SPRINTF(LE_width_prec_spac_ng_inf, "% 10.5LE", (long double)(-INFINITY),
             long double)
TEST_SPRINTF(LE_width_prec_hash_ng_inf, "%#10.5LE", (long double)(-INFINITY),
             long double)
TEST_SPRINTF(LE_width_prec_fzer_ng_inf, "%010.5LE", (long double)(-INFINITY),
             long double)

TEST_SPRINTF(LE_zrwth_zrpc_plus_nan, "%+0.0LE", (long double)NAN, long double)
TEST_SPRINTF(LE_zrwth_zrpc_spac_nan, "% 0.0LE", (long double)NAN, long double)
TEST_SPRINTF(LE_zrwth_zrpc_hash_nan, "%#0.0LE", (long double)NAN, long double)
TEST_SPRINTF(LE_zrwth_zrpc_plus_inf, "%+0.0LE", (long double)INFINITY,
             long double)
TEST_SPRINTF(LE_zrwth_zrpc_spac_inf, "% 0.0LE", (long double)INFINITY,
             long double)
TEST_SPRINTF(LE_zrwth_zrpc_hash_inf, "%#0.0LE", (long double)INFINITY,
             long double)
TEST_SPRINTF(LE_zrwth_zrpc_plus_ng_inf, "%+0.0LE", (long double)(-INFINITY),
             long double)
TEST_SPRINTF(LE_zrwth_zrpc_spac_ng_inf, "% 0.0LE", (long double)(-INFINITY),
             long double)
TEST_SPRINTF(LE_zrwth_zrpc_hash_ng_inf, "%#0.0LE", (long double)(-INFINITY),
             long double)

TEST_SPRINTF_2(LE_dynamic_prec_nan, "%.*LE", 5, (long double)NAN, long double)
TEST_SPRINTF_2(LE_dynamic_prec_inf, "%.*LE", 5, (long double)INFINITY,
               long double)
TEST_SPRINTF_2(LE_dynamic_prec_ng_inf, "%.*LE", 5, (long double)(-INFINITY),
               long double)

TEST_SPRINTF_2(LE_dynamic_width_nan, "%*LE", 10, (long double)NAN, long double)
TEST_SPRINTF_2(LE_dynamic_width_inf, "%*LE", 10, (long double)INFINITY,
               long double)
TEST_SPRINTF_2(LE_dynamic_width_ng_inf, "%*LE", 10, (long double)(-INFINITY),
               long double)

TEST_SPRINTF_3(LE_dynamic_width_prec_nan, "%*.*LE", 10, 5, (long double)NAN,
               long double)
TEST_SPRINTF_3(LE_dynamic_width_prec_inf, "%*.*LE", 10, 5,
               (long double)INFINITY, long double)
TEST_SPRINTF_3(LE_dynamic_width_prec_ng_inf, "%*.*LE", 10, 5,
               (long double)(-INFINITY), long double)

// =========================================================================

TEST_SPRINTF(Lf_mins_nan, "%-Lf", (long double)NAN, long double)
TEST_SPRINTF(Lf_plus_nan, "%+Lf", (long double)NAN, long double)
TEST_SPRINTF(Lf_spac_nan, "% Lf", (long double)NAN, long double)
TEST_SPRINTF(Lf_hash_nan, "%#Lf", (long double)NAN, long double)
TEST_SPRINTF(Lf_fzer_nan, "%0Lf", (long double)NAN, long double)
TEST_SPRINTF(Lf_mins_inf, "%-Lf", (long double)INFINITY, long double)
TEST_SPRINTF(Lf_plus_inf, "%+Lf", (long double)INFINITY, long double)
TEST_SPRINTF(Lf_spac_inf, "% Lf", (long double)INFINITY, long double)
TEST_SPRINTF(Lf_hash_inf, "%#Lf", (long double)INFINITY, long double)
TEST_SPRINTF(Lf_fzer_inf, "%0Lf", (long double)INFINITY, long double)
TEST_SPRINTF(Lf_mins_ng_inf, "%-Lf", (long double)(-INFINITY), long double)
TEST_SPRINTF(Lf_plus_ng_inf, "%+Lf", (long double)(-INFINITY), long double)
TEST_SPRINTF(Lf_spac_ng_inf, "% Lf", (long double)(-INFINITY), long double)
TEST_SPRINTF(Lf_hash_ng_inf, "%#Lf", (long double)(-INFINITY), long double)
TEST_SPRINTF(Lf_fzer_ng_inf, "%0Lf", (long double)(-INFINITY), long double)

TEST_SPRINTF(Lf_width_nan, "%5Lf", (long double)NAN, long double)
TEST_SPRINTF(Lf_zrpc_nan, "%.0Lf", (long double)NAN, long double)
TEST_SPRINTF(Lf_prec_nan, "%.5Lf", (long double)NAN, long double)
TEST_SPRINTF(Lf_width_inf, "%5Lf", (long double)INFINITY, long double)
TEST_SPRINTF(Lf_zrpc_inf, "%.0Lf", (long double)INFINITY, long double)
TEST_SPRINTF(Lf_prec_inf, "%.5Lf", (long double)INFINITY, long double)
TEST_SPRINTF(Lf_width_ng_inf, "%5Lf", (long double)(-INFINITY), long double)
TEST_SPRINTF(Lf_zrpc_ng_inf, "%.0Lf", (long double)(-INFINITY), long double)
TEST_SPRINTF(Lf_prec_ng_inf, "%.5Lf", (long double)(-INFINITY), long double)

TEST_SPRINTF(Lf_width_prec_nan, "%10.5Lf", (long double)NAN, long double)
TEST_SPRINTF(Lf_width_prec_inf, "%10.5Lf", (long double)INFINITY, long double)
TEST_SPRINTF(Lf_width_prec_ng_inf, "%10.5Lf", (long double)(-INFINITY),
             long double)

TEST_SPRINTF(Lf_width_mins_nan, "%-5Lf", (long double)NAN, long double)
TEST_SPRINTF(Lf_width_plus_nan, "%+5Lf", (long double)NAN, long double)
TEST_SPRINTF(Lf_width_spac_nan, "% 5Lf", (long double)NAN, long double)
TEST_SPRINTF(Lf_width_hash_nan, "%#5Lf", (long double)NAN, long double)
TEST_SPRINTF(Lf_width_fzer_nan, "%05Lf", (long double)NAN, long double)
TEST_SPRINTF(Lf_width_mins_inf, "%-5Lf", (long double)INFINITY, long double)
TEST_SPRINTF(Lf_width_plus_inf, "%+5Lf", (long double)INFINITY, long double)
TEST_SPRINTF(Lf_width_spac_inf, "% 5Lf", (long double)INFINITY, long double)
TEST_SPRINTF(Lf_width_hash_inf, "%#5Lf", (long double)INFINITY, long double)
TEST_SPRINTF(Lf_width_fzer_inf, "%05Lf", (long double)INFINITY, long double)
TEST_SPRINTF(Lf_width_mins_ng_inf, "%-5Lf", (long double)(-INFINITY),
             long double)
TEST_SPRINTF(Lf_width_plus_ng_inf, "%+5Lf", (long double)(-INFINITY),
             long double)
TEST_SPRINTF(Lf_width_spac_ng_inf, "% 5Lf", (long double)(-INFINITY),
             long double)
TEST_SPRINTF(Lf_width_hash_ng_inf, "%#5Lf", (long double)(-INFINITY),
             long double)
TEST_SPRINTF(Lf_width_fzer_ng_inf, "%05Lf", (long double)(-INFINITY),
             long double)

TEST_SPRINTF(Lf_zrwth_plus_nan, "%+0Lf", (long double)NAN, long double)
TEST_SPRINTF(Lf_zrwth_spac_nan, "% 0Lf", (long double)NAN, long double)
TEST_SPRINTF(Lf_zrwth_hash_nan, "%#0Lf", (long double)NAN, long double)
TEST_SPRINTF(Lf_zrwth_plus_inf, "%+0Lf", (long double)INFINITY, long double)
TEST_SPRINTF(Lf_zrwth_spac_inf, "% 0Lf", (long double)INFINITY, long double)
TEST_SPRINTF(Lf_zrwth_hash_inf, "%#0Lf", (long double)INFINITY, long double)
TEST_SPRINTF(Lf_zrwth_plus_ng_inf, "%+0Lf", (long double)(-INFINITY),
             long double)
TEST_SPRINTF(Lf_zrwth_spac_ng_inf, "% 0Lf", (long double)(-INFINITY),
             long double)
TEST_SPRINTF(Lf_zrwth_hash_ng_inf, "%#0Lf", (long double)(-INFINITY),
             long double)

TEST_SPRINTF(Lf_prec_mins_nan, "%-.5Lf", (long double)NAN, long double)
TEST_SPRINTF(Lf_prec_plus_nan, "%+.5Lf", (long double)NAN, long double)
TEST_SPRINTF(Lf_prec_spac_nan, "% .5Lf", (long double)NAN, long double)
TEST_SPRINTF(Lf_prec_hash_nan, "%#.5Lf", (long double)NAN, long double)
TEST_SPRINTF(Lf_prec_fzer_nan, "%0.5Lf", (long double)NAN, long double)
TEST_SPRINTF(Lf_prec_mins_inf, "%-.5Lf", (long double)INFINITY, long double)
TEST_SPRINTF(Lf_prec_plus_inf, "%+.5Lf", (long double)INFINITY, long double)
TEST_SPRINTF(Lf_prec_spac_inf, "% .5Lf", (long double)INFINITY, long double)
TEST_SPRINTF(Lf_prec_hash_inf, "%#.5Lf", (long double)INFINITY, long double)
TEST_SPRINTF(Lf_prec_fzer_inf, "%0.5Lf", (long double)INFINITY, long double)
TEST_SPRINTF(Lf_prec_mins_ng_inf, "%-.5Lf", (long double)(-INFINITY),
             long double)
TEST_SPRINTF(Lf_prec_plus_ng_inf, "%+.5Lf", (long double)(-INFINITY),
             long double)
TEST_SPRINTF(Lf_prec_spac_ng_inf, "% .5Lf", (long double)(-INFINITY),
             long double)
TEST_SPRINTF(Lf_prec_hash_ng_inf, "%#.5Lf", (long double)(-INFINITY),
             long double)
TEST_SPRINTF(Lf_prec_fzer_ng_inf, "%0.5Lf", (long double)(-INFINITY),
             long double)

TEST_SPRINTF(Lf_zrpc_mins_nan, "%-.0Lf", (long double)NAN, long double)
TEST_SPRINTF(Lf_zrpc_plus_nan, "%+.0Lf", (long double)NAN, long double)
TEST_SPRINTF(Lf_zrpc_spac_nan, "% .0Lf", (long double)NAN, long double)
TEST_SPRINTF(Lf_zrpc_hash_nan, "%#.0Lf", (long double)NAN, long double)
TEST_SPRINTF(Lf_zrpc_fzer_nan, "%0.0Lf", (long double)NAN, long double)
TEST_SPRINTF(Lf_zrpc_mins_inf, "%-.0Lf", (long double)INFINITY, long double)
TEST_SPRINTF(Lf_zrpc_plus_inf, "%+.0Lf", (long double)INFINITY, long double)
TEST_SPRINTF(Lf_zrpc_spac_inf, "% .0Lf", (long double)INFINITY, long double)
TEST_SPRINTF(Lf_zrpc_hash_inf, "%#.0Lf", (long double)INFINITY, long double)
TEST_SPRINTF(Lf_zrpc_fzer_inf, "%0.0Lf", (long double)INFINITY, long double)
TEST_SPRINTF(Lf_zrpc_mins_ng_inf, "%-.0Lf", (long double)(-INFINITY),
             long double)
TEST_SPRINTF(Lf_zrpc_plus_ng_inf, "%+.0Lf", (long double)(-INFINITY),
             long double)
TEST_SPRINTF(Lf_zrpc_spac_ng_inf, "% .0Lf", (long double)(-INFINITY),
             long double)
TEST_SPRINTF(Lf_zrpc_hash_ng_inf, "%#.0Lf", (long double)(-INFINITY),
             long double)
TEST_SPRINTF(Lf_zrpc_fzer_ng_inf, "%0.0Lf", (long double)(-INFINITY),
             long double)

TEST_SPRINTF(Lf_width_prec_mins_nan, "%-10.5Lf", (long double)NAN, long double)
TEST_SPRINTF(Lf_width_prec_plus_nan, "%+10.5Lf", (long double)NAN, long double)
TEST_SPRINTF(Lf_width_prec_spac_nan, "% 10.5Lf", (long double)NAN, long double)
TEST_SPRINTF(Lf_width_prec_hash_nan, "%#10.5Lf", (long double)NAN, long double)
TEST_SPRINTF(Lf_width_prec_fzer_nan, "%010.5Lf", (long double)NAN, long double)
TEST_SPRINTF(Lf_width_prec_mins_inf, "%-10.5Lf", (long double)INFINITY,
             long double)
TEST_SPRINTF(Lf_width_prec_plus_inf, "%+10.5Lf", (long double)INFINITY,
             long double)
TEST_SPRINTF(Lf_width_prec_spac_inf, "% 10.5Lf", (long double)INFINITY,
             long double)
TEST_SPRINTF(Lf_width_prec_hash_inf, "%#10.5Lf", (long double)INFINITY,
             long double)
TEST_SPRINTF(Lf_width_prec_fzer_inf, "%010.5Lf", (long double)INFINITY,
             long double)
TEST_SPRINTF(Lf_width_prec_mins_ng_inf, "%-10.5Lf", (long double)(-INFINITY),
             long double)
TEST_SPRINTF(Lf_width_prec_plus_ng_inf, "%+10.5Lf", (long double)(-INFINITY),
             long double)
TEST_SPRINTF(Lf_width_prec_spac_ng_inf, "% 10.5Lf", (long double)(-INFINITY),
             long double)
TEST_SPRINTF(Lf_width_prec_hash_ng_inf, "%#10.5Lf", (long double)(-INFINITY),
             long double)
TEST_SPRINTF(Lf_width_prec_fzer_ng_inf, "%010.5Lf", (long double)(-INFINITY),
             long double)

TEST_SPRINTF(Lf_zrwth_zrpc_plus_nan, "%+0.0Lf", (long double)NAN, long double)
TEST_SPRINTF(Lf_zrwth_zrpc_spac_nan, "% 0.0Lf", (long double)NAN, long double)
TEST_SPRINTF(Lf_zrwth_zrpc_hash_nan, "%#0.0Lf", (long double)NAN, long double)
TEST_SPRINTF(Lf_zrwth_zrpc_plus_inf, "%+0.0Lf", (long double)INFINITY,
             long double)
TEST_SPRINTF(Lf_zrwth_zrpc_spac_inf, "% 0.0Lf", (long double)INFINITY,
             long double)
TEST_SPRINTF(Lf_zrwth_zrpc_hash_inf, "%#0.0Lf", (long double)INFINITY,
             long double)
TEST_SPRINTF(Lf_zrwth_zrpc_plus_ng_inf, "%+0.0Lf", (long double)(-INFINITY),
             long double)
TEST_SPRINTF(Lf_zrwth_zrpc_spac_ng_inf, "% 0.0Lf", (long double)(-INFINITY),
             long double)
TEST_SPRINTF(Lf_zrwth_zrpc_hash_ng_inf, "%#0.0Lf", (long double)(-INFINITY),
             long double)

TEST_SPRINTF_2(Lf_dynamic_prec_nan, "%.*Lf", 5, (long double)NAN, long double)
TEST_SPRINTF_2(Lf_dynamic_prec_inf, "%.*Lf", 5, (long double)INFINITY,
               long double)
TEST_SPRINTF_2(Lf_dynamic_prec_ng_inf, "%.*Lf", 5, (long double)(-INFINITY),
               long double)

TEST_SPRINTF_2(Lf_dynamic_width_nan, "%*Lf", 10, (long double)NAN, long double)
TEST_SPRINTF_2(Lf_dynamic_width_inf, "%*Lf", 10, (long double)INFINITY,
               long double)
TEST_SPRINTF_2(Lf_dynamic_width_ng_inf, "%*Lf", 10, (long double)(-INFINITY),
               long double)

TEST_SPRINTF_3(Lf_dynamic_width_prec_nan, "%*.*Lf", 10, 5, (long double)NAN,
               long double)
TEST_SPRINTF_3(Lf_dynamic_width_prec_inf, "%*.*Lf", 10, 5,
               (long double)INFINITY, long double)
TEST_SPRINTF_3(Lf_dynamic_width_prec_ng_inf, "%*.*Lf", 10, 5,
               (long double)(-INFINITY), long double)

// =========================================================================

TEST_SPRINTF(Lg_mins_nan, "%-Lg", (long double)NAN, long double)
TEST_SPRINTF(Lg_plus_nan, "%+Lg", (long double)NAN, long double)
TEST_SPRINTF(Lg_spac_nan, "% Lg", (long double)NAN, long double)
TEST_SPRINTF(Lg_hash_nan, "%#Lg", (long double)NAN, long double)
TEST_SPRINTF(Lg_fzer_nan, "%0Lg", (long double)NAN, long double)
TEST_SPRINTF(Lg_mins_inf, "%-Lg", (long double)INFINITY, long double)
TEST_SPRINTF(Lg_plus_inf, "%+Lg", (long double)INFINITY, long double)
TEST_SPRINTF(Lg_spac_inf, "% Lg", (long double)INFINITY, long double)
TEST_SPRINTF(Lg_hash_inf, "%#Lg", (long double)INFINITY, long double)
TEST_SPRINTF(Lg_fzer_inf, "%0Lg", (long double)INFINITY, long double)
TEST_SPRINTF(Lg_mins_ng_inf, "%-Lg", (long double)(-INFINITY), long double)
TEST_SPRINTF(Lg_plus_ng_inf, "%+Lg", (long double)(-INFINITY), long double)
TEST_SPRINTF(Lg_spac_ng_inf, "% Lg", (long double)(-INFINITY), long double)
TEST_SPRINTF(Lg_hash_ng_inf, "%#Lg", (long double)(-INFINITY), long double)
TEST_SPRINTF(Lg_fzer_ng_inf, "%0Lg", (long double)(-INFINITY), long double)

TEST_SPRINTF(Lg_width_nan, "%5Lg", (long double)NAN, long double)
TEST_SPRINTF(Lg_zrpc_nan, "%.0Lg", (long double)NAN, long double)
TEST_SPRINTF(Lg_prec_nan, "%.5Lg", (long double)NAN, long double)
TEST_SPRINTF(Lg_width_inf, "%5Lg", (long double)INFINITY, long double)
TEST_SPRINTF(Lg_zrpc_inf, "%.0Lg", (long double)INFINITY, long double)
TEST_SPRINTF(Lg_prec_inf, "%.5Lg", (long double)INFINITY, long double)
TEST_SPRINTF(Lg_width_ng_inf, "%5Lg", (long double)(-INFINITY), long double)
TEST_SPRINTF(Lg_zrpc_ng_inf, "%.0Lg", (long double)(-INFINITY), long double)
TEST_SPRINTF(Lg_prec_ng_inf, "%.5Lg", (long double)(-INFINITY), long double)

TEST_SPRINTF(Lg_width_prec_nan, "%10.5Lg", (long double)NAN, long double)
TEST_SPRINTF(Lg_width_prec_inf, "%10.5Lg", (long double)INFINITY, long double)
TEST_SPRINTF(Lg_width_prec_ng_inf, "%10.5Lg", (long double)(-INFINITY),
             long double)

TEST_SPRINTF(Lg_width_mins_nan, "%-5Lg", (long double)NAN, long double)
TEST_SPRINTF(Lg_width_plus_nan, "%+5Lg", (long double)NAN, long double)
TEST_SPRINTF(Lg_width_spac_nan, "% 5Lg", (long double)NAN, long double)
TEST_SPRINTF(Lg_width_hash_nan, "%#5Lg", (long double)NAN, long double)
TEST_SPRINTF(Lg_width_fzer_nan, "%05Lg", (long double)NAN, long double)
TEST_SPRINTF(Lg_width_mins_inf, "%-5Lg", (long double)INFINITY, long double)
TEST_SPRINTF(Lg_width_plus_inf, "%+5Lg", (long double)INFINITY, long double)
TEST_SPRINTF(Lg_width_spac_inf, "% 5Lg", (long double)INFINITY, long double)
TEST_SPRINTF(Lg_width_hash_inf, "%#5Lg", (long double)INFINITY, long double)
TEST_SPRINTF(Lg_width_fzer_inf, "%05Lg", (long double)INFINITY, long double)
TEST_SPRINTF(Lg_width_mins_ng_inf, "%-5Lg", (long double)(-INFINITY),
             long double)
TEST_SPRINTF(Lg_width_plus_ng_inf, "%+5Lg", (long double)(-INFINITY),
             long double)
TEST_SPRINTF(Lg_width_spac_ng_inf, "% 5Lg", (long double)(-INFINITY),
             long double)
TEST_SPRINTF(Lg_width_hash_ng_inf, "%#5Lg", (long double)(-INFINITY),
             long double)
TEST_SPRINTF(Lg_width_fzer_ng_inf, "%05Lg", (long double)(-INFINITY),
             long double)

TEST_SPRINTF(Lg_zrwth_plus_nan, "%+0Lg", (long double)NAN, long double)
TEST_SPRINTF(Lg_zrwth_spac_nan, "% 0Lg", (long double)NAN, long double)
TEST_SPRINTF(Lg_zrwth_hash_nan, "%#0Lg", (long double)NAN, long double)
TEST_SPRINTF(Lg_zrwth_plus_inf, "%+0Lg", (long double)INFINITY, long double)
TEST_SPRINTF(Lg_zrwth_spac_inf, "% 0Lg", (long double)INFINITY, long double)
TEST_SPRINTF(Lg_zrwth_hash_inf, "%#0Lg", (long double)INFINITY, long double)
TEST_SPRINTF(Lg_zrwth_plus_ng_inf, "%+0Lg", (long double)(-INFINITY),
             long double)
TEST_SPRINTF(Lg_zrwth_spac_ng_inf, "% 0Lg", (long double)(-INFINITY),
             long double)
TEST_SPRINTF(Lg_zrwth_hash_ng_inf, "%#0Lg", (long double)(-INFINITY),
             long double)

TEST_SPRINTF(Lg_prec_mins_nan, "%-.5Lg", (long double)NAN, long double)
TEST_SPRINTF(Lg_prec_plus_nan, "%+.5Lg", (long double)NAN, long double)
TEST_SPRINTF(Lg_prec_spac_nan, "% .5Lg", (long double)NAN, long double)
TEST_SPRINTF(Lg_prec_hash_nan, "%#.5Lg", (long double)NAN, long double)
TEST_SPRINTF(Lg_prec_fzer_nan, "%0.5Lg", (long double)NAN, long double)
TEST_SPRINTF(Lg_prec_mins_inf, "%-.5Lg", (long double)INFINITY, long double)
TEST_SPRINTF(Lg_prec_plus_inf, "%+.5Lg", (long double)INFINITY, long double)
TEST_SPRINTF(Lg_prec_spac_inf, "% .5Lg", (long double)INFINITY, long double)
TEST_SPRINTF(Lg_prec_hash_inf, "%#.5Lg", (long double)INFINITY, long double)
TEST_SPRINTF(Lg_prec_fzer_inf, "%0.5Lg", (long double)INFINITY, long double)
TEST_SPRINTF(Lg_prec_mins_ng_inf, "%-.5Lg", (long double)(-INFINITY),
             long double)
TEST_SPRINTF(Lg_prec_plus_ng_inf, "%+.5Lg", (long double)(-INFINITY),
             long double)
TEST_SPRINTF(Lg_prec_spac_ng_inf, "% .5Lg", (long double)(-INFINITY),
             long double)
TEST_SPRINTF(Lg_prec_hash_ng_inf, "%#.5Lg", (long double)(-INFINITY),
             long double)
TEST_SPRINTF(Lg_prec_fzer_ng_inf, "%0.5Lg", (long double)(-INFINITY),
             long double)

TEST_SPRINTF(Lg_zrpc_mins_nan, "%-.0Lg", (long double)NAN, long double)
TEST_SPRINTF(Lg_zrpc_plus_nan, "%+.0Lg", (long double)NAN, long double)
TEST_SPRINTF(Lg_zrpc_spac_nan, "% .0Lg", (long double)NAN, long double)
TEST_SPRINTF(Lg_zrpc_hash_nan, "%#.0Lg", (long double)NAN, long double)
TEST_SPRINTF(Lg_zrpc_fzer_nan, "%0.0Lg", (long double)NAN, long double)
TEST_SPRINTF(Lg_zrpc_mins_inf, "%-.0Lg", (long double)INFINITY, long double)
TEST_SPRINTF(Lg_zrpc_plus_inf, "%+.0Lg", (long double)INFINITY, long double)
TEST_SPRINTF(Lg_zrpc_spac_inf, "% .0Lg", (long double)INFINITY, long double)
TEST_SPRINTF(Lg_zrpc_hash_inf, "%#.0Lg", (long double)INFINITY, long double)
TEST_SPRINTF(Lg_zrpc_fzer_inf, "%0.0Lg", (long double)INFINITY, long double)
TEST_SPRINTF(Lg_zrpc_mins_ng_inf, "%-.0Lg", (long double)(-INFINITY),
             long double)
TEST_SPRINTF(Lg_zrpc_plus_ng_inf, "%+.0Lg", (long double)(-INFINITY),
             long double)
TEST_SPRINTF(Lg_zrpc_spac_ng_inf, "% .0Lg", (long double)(-INFINITY),
             long double)
TEST_SPRINTF(Lg_zrpc_hash_ng_inf, "%#.0Lg", (long double)(-INFINITY),
             long double)
TEST_SPRINTF(Lg_zrpc_fzer_ng_inf, "%0.0Lg", (long double)(-INFINITY),
             long double)

TEST_SPRINTF(Lg_width_prec_mins_nan, "%-10.5Lg", (long double)NAN, long double)
TEST_SPRINTF(Lg_width_prec_plus_nan, "%+10.5Lg", (long double)NAN, long double)
TEST_SPRINTF(Lg_width_prec_spac_nan, "% 10.5Lg", (long double)NAN, long double)
TEST_SPRINTF(Lg_width_prec_hash_nan, "%#10.5Lg", (long double)NAN, long double)
TEST_SPRINTF(Lg_width_prec_fzer_nan, "%010.5Lg", (long double)NAN, long double)
TEST_SPRINTF(Lg_width_prec_mins_inf, "%-10.5Lg", (long double)INFINITY,
             long double)
TEST_SPRINTF(Lg_width_prec_plus_inf, "%+10.5Lg", (long double)INFINITY,
             long double)
TEST_SPRINTF(Lg_width_prec_spac_inf, "% 10.5Lg", (long double)INFINITY,
             long double)
TEST_SPRINTF(Lg_width_prec_hash_inf, "%#10.5Lg", (long double)INFINITY,
             long double)
TEST_SPRINTF(Lg_width_prec_fzer_inf, "%010.5Lg", (long double)INFINITY,
             long double)
TEST_SPRINTF(Lg_width_prec_mins_ng_inf, "%-10.5Lg", (long double)(-INFINITY),
             long double)
TEST_SPRINTF(Lg_width_prec_plus_ng_inf, "%+10.5Lg", (long double)(-INFINITY),
             long double)
TEST_SPRINTF(Lg_width_prec_spac_ng_inf, "% 10.5Lg", (long double)(-INFINITY),
             long double)
TEST_SPRINTF(Lg_width_prec_hash_ng_inf, "%#10.5Lg", (long double)(-INFINITY),
             long double)
TEST_SPRINTF(Lg_width_prec_fzer_ng_inf, "%010.5Lg", (long double)(-INFINITY),
             long double)

TEST_SPRINTF(Lg_zrwth_zrpc_plus_nan, "%+0.0Lg", (long double)NAN, long double)
TEST_SPRINTF(Lg_zrwth_zrpc_spac_nan, "% 0.0Lg", (long double)NAN, long double)
TEST_SPRINTF(Lg_zrwth_zrpc_hash_nan, "%#0.0Lg", (long double)NAN, long double)
TEST_SPRINTF(Lg_zrwth_zrpc_plus_inf, "%+0.0Lg", (long double)INFINITY,
             long double)
TEST_SPRINTF(Lg_zrwth_zrpc_spac_inf, "% 0.0Lg", (long double)INFINITY,
             long double)
TEST_SPRINTF(Lg_zrwth_zrpc_hash_inf, "%#0.0Lg", (long double)INFINITY,
             long double)
TEST_SPRINTF(Lg_zrwth_zrpc_plus_ng_inf, "%+0.0Lg", (long double)(-INFINITY),
             long double)
TEST_SPRINTF(Lg_zrwth_zrpc_spac_ng_inf, "% 0.0Lg", (long double)(-INFINITY),
             long double)
TEST_SPRINTF(Lg_zrwth_zrpc_hash_ng_inf, "%#0.0Lg", (long double)(-INFINITY),
             long double)

TEST_SPRINTF_2(Lg_dynamic_prec_nan, "%.*Lg", 5, (long double)NAN, long double)
TEST_SPRINTF_2(Lg_dynamic_prec_inf, "%.*Lg", 5, (long double)INFINITY,
               long double)
TEST_SPRINTF_2(Lg_dynamic_prec_ng_inf, "%.*Lg", 5, (long double)(-INFINITY),
               long double)

TEST_SPRINTF_2(Lg_dynamic_width_nan, "%*Lg", 10, (long double)NAN, long double)
TEST_SPRINTF_2(Lg_dynamic_width_inf, "%*Lg", 10, (long double)INFINITY,
               long double)
TEST_SPRINTF_2(Lg_dynamic_width_ng_inf, "%*Lg", 10, (long double)(-INFINITY),
               long double)

TEST_SPRINTF_3(Lg_dynamic_width_prec_nan, "%*.*Lg", 10, 5, (long double)NAN,
               long double)
TEST_SPRINTF_3(Lg_dynamic_width_prec_inf, "%*.*Lg", 10, 5,
               (long double)INFINITY, long double)
TEST_SPRINTF_3(Lg_dynamic_width_prec_ng_inf, "%*.*Lg", 10, 5,
               (long double)(-INFINITY), long double)

// =========================================================================

TEST_SPRINTF(LG_mins_nan, "%-LG", (long double)NAN, long double)
TEST_SPRINTF(LG_plus_nan, "%+LG", (long double)NAN, long double)
TEST_SPRINTF(LG_spac_nan, "% LG", (long double)NAN, long double)
TEST_SPRINTF(LG_hash_nan, "%#LG", (long double)NAN, long double)
TEST_SPRINTF(LG_fzer_nan, "%0LG", (long double)NAN, long double)
TEST_SPRINTF(LG_mins_inf, "%-LG", (long double)INFINITY, long double)
TEST_SPRINTF(LG_plus_inf, "%+LG", (long double)INFINITY, long double)
TEST_SPRINTF(LG_spac_inf, "% LG", (long double)INFINITY, long double)
TEST_SPRINTF(LG_hash_inf, "%#LG", (long double)INFINITY, long double)
TEST_SPRINTF(LG_fzer_inf, "%0LG", (long double)INFINITY, long double)
TEST_SPRINTF(LG_mins_ng_inf, "%-LG", (long double)(-INFINITY), long double)
TEST_SPRINTF(LG_plus_ng_inf, "%+LG", (long double)(-INFINITY), long double)
TEST_SPRINTF(LG_spac_ng_inf, "% LG", (long double)(-INFINITY), long double)
TEST_SPRINTF(LG_hash_ng_inf, "%#LG", (long double)(-INFINITY), long double)
TEST_SPRINTF(LG_fzer_ng_inf, "%0LG", (long double)(-INFINITY), long double)

TEST_SPRINTF(LG_width_nan, "%5LG", (long double)NAN, long double)
TEST_SPRINTF(LG_zrpc_nan, "%.0LG", (long double)NAN, long double)
TEST_SPRINTF(LG_prec_nan, "%.5LG", (long double)NAN, long double)
TEST_SPRINTF(LG_width_inf, "%5LG", (long double)INFINITY, long double)
TEST_SPRINTF(LG_zrpc_inf, "%.0LG", (long double)INFINITY, long double)
TEST_SPRINTF(LG_prec_inf, "%.5LG", (long double)INFINITY, long double)
TEST_SPRINTF(LG_width_ng_inf, "%5LG", (long double)(-INFINITY), long double)
TEST_SPRINTF(LG_zrpc_ng_inf, "%.0LG", (long double)(-INFINITY), long double)
TEST_SPRINTF(LG_prec_ng_inf, "%.5LG", (long double)(-INFINITY), long double)

TEST_SPRINTF(LG_width_prec_nan, "%10.5LG", (long double)NAN, long double)
TEST_SPRINTF(LG_width_prec_inf, "%10.5LG", (long double)INFINITY, long double)
TEST_SPRINTF(LG_width_prec_ng_inf, "%10.5LG", (long double)(-INFINITY),
             long double)

TEST_SPRINTF(LG_width_mins_nan, "%-5LG", (long double)NAN, long double)
TEST_SPRINTF(LG_width_plus_nan, "%+5LG", (long double)NAN, long double)
TEST_SPRINTF(LG_width_spac_nan, "% 5LG", (long double)NAN, long double)
TEST_SPRINTF(LG_width_hash_nan, "%#5LG", (long double)NAN, long double)
TEST_SPRINTF(LG_width_fzer_nan, "%05LG", (long double)NAN, long double)
TEST_SPRINTF(LG_width_mins_inf, "%-5LG", (long double)INFINITY, long double)
TEST_SPRINTF(LG_width_plus_inf, "%+5LG", (long double)INFINITY, long double)
TEST_SPRINTF(LG_width_spac_inf, "% 5LG", (long double)INFINITY, long double)
TEST_SPRINTF(LG_width_hash_inf, "%#5LG", (long double)INFINITY, long double)
TEST_SPRINTF(LG_width_fzer_inf, "%05LG", (long double)INFINITY, long double)
TEST_SPRINTF(LG_width_mins_ng_inf, "%-5LG", (long double)(-INFINITY),
             long double)
TEST_SPRINTF(LG_width_plus_ng_inf, "%+5LG", (long double)(-INFINITY),
             long double)
TEST_SPRINTF(LG_width_spac_ng_inf, "% 5LG", (long double)(-INFINITY),
             long double)
TEST_SPRINTF(LG_width_hash_ng_inf, "%#5LG", (long double)(-INFINITY),
             long double)
TEST_SPRINTF(LG_width_fzer_ng_inf, "%05LG", (long double)(-INFINITY),
             long double)

TEST_SPRINTF(LG_zrwth_plus_nan, "%+0LG", (long double)NAN, long double)
TEST_SPRINTF(LG_zrwth_spac_nan, "% 0LG", (long double)NAN, long double)
TEST_SPRINTF(LG_zrwth_hash_nan, "%#0LG", (long double)NAN, long double)
TEST_SPRINTF(LG_zrwth_plus_inf, "%+0LG", (long double)INFINITY, long double)
TEST_SPRINTF(LG_zrwth_spac_inf, "% 0LG", (long double)INFINITY, long double)
TEST_SPRINTF(LG_zrwth_hash_inf, "%#0LG", (long double)INFINITY, long double)
TEST_SPRINTF(LG_zrwth_plus_ng_inf, "%+0LG", (long double)(-INFINITY),
             long double)
TEST_SPRINTF(LG_zrwth_spac_ng_inf, "% 0LG", (long double)(-INFINITY),
             long double)
TEST_SPRINTF(LG_zrwth_hash_ng_inf, "%#0LG", (long double)(-INFINITY),
             long double)

TEST_SPRINTF(LG_prec_mins_nan, "%-.5LG", (long double)NAN, long double)
TEST_SPRINTF(LG_prec_plus_nan, "%+.5LG", (long double)NAN, long double)
TEST_SPRINTF(LG_prec_spac_nan, "% .5LG", (long double)NAN, long double)
TEST_SPRINTF(LG_prec_hash_nan, "%#.5LG", (long double)NAN, long double)
TEST_SPRINTF(LG_prec_fzer_nan, "%0.5LG", (long double)NAN, long double)
TEST_SPRINTF(LG_prec_mins_inf, "%-.5LG", (long double)INFINITY, long double)
TEST_SPRINTF(LG_prec_plus_inf, "%+.5LG", (long double)INFINITY, long double)
TEST_SPRINTF(LG_prec_spac_inf, "% .5LG", (long double)INFINITY, long double)
TEST_SPRINTF(LG_prec_hash_inf, "%#.5LG", (long double)INFINITY, long double)
TEST_SPRINTF(LG_prec_fzer_inf, "%0.5LG", (long double)INFINITY, long double)
TEST_SPRINTF(LG_prec_mins_ng_inf, "%-.5LG", (long double)(-INFINITY),
             long double)
TEST_SPRINTF(LG_prec_plus_ng_inf, "%+.5LG", (long double)(-INFINITY),
             long double)
TEST_SPRINTF(LG_prec_spac_ng_inf, "% .5LG", (long double)(-INFINITY),
             long double)
TEST_SPRINTF(LG_prec_hash_ng_inf, "%#.5LG", (long double)(-INFINITY),
             long double)
TEST_SPRINTF(LG_prec_fzer_ng_inf, "%0.5LG", (long double)(-INFINITY),
             long double)

TEST_SPRINTF(LG_zrpc_mins_nan, "%-.0LG", (long double)NAN, long double)
TEST_SPRINTF(LG_zrpc_plus_nan, "%+.0LG", (long double)NAN, long double)
TEST_SPRINTF(LG_zrpc_spac_nan, "% .0LG", (long double)NAN, long double)
TEST_SPRINTF(LG_zrpc_hash_nan, "%#.0LG", (long double)NAN, long double)
TEST_SPRINTF(LG_zrpc_fzer_nan, "%0.0LG", (long double)NAN, long double)
TEST_SPRINTF(LG_zrpc_mins_inf, "%-.0LG", (long double)INFINITY, long double)
TEST_SPRINTF(LG_zrpc_plus_inf, "%+.0LG", (long double)INFINITY, long double)
TEST_SPRINTF(LG_zrpc_spac_inf, "% .0LG", (long double)INFINITY, long double)
TEST_SPRINTF(LG_zrpc_hash_inf, "%#.0LG", (long double)INFINITY, long double)
TEST_SPRINTF(LG_zrpc_fzer_inf, "%0.0LG", (long double)INFINITY, long double)
TEST_SPRINTF(LG_zrpc_mins_ng_inf, "%-.0LG", (long double)(-INFINITY),
             long double)
TEST_SPRINTF(LG_zrpc_plus_ng_inf, "%+.0LG", (long double)(-INFINITY),
             long double)
TEST_SPRINTF(LG_zrpc_spac_ng_inf, "% .0LG", (long double)(-INFINITY),
             long double)
TEST_SPRINTF(LG_zrpc_hash_ng_inf, "%#.0LG", (long double)(-INFINITY),
             long double)
TEST_SPRINTF(LG_zrpc_fzer_ng_inf, "%0.0LG", (long double)(-INFINITY),
             long double)

TEST_SPRINTF(LG_width_prec_mins_nan, "%-10.5LG", (long double)NAN, long double)
TEST_SPRINTF(LG_width_prec_plus_nan, "%+10.5LG", (long double)NAN, long double)
TEST_SPRINTF(LG_width_prec_spac_nan, "% 10.5LG", (long double)NAN, long double)
TEST_SPRINTF(LG_width_prec_hash_nan, "%#10.5LG", (long double)NAN, long double)
TEST_SPRINTF(LG_width_prec_fzer_nan, "%010.5LG", (long double)NAN, long double)
TEST_SPRINTF(LG_width_prec_mins_inf, "%-10.5LG", (long double)INFINITY,
             long double)
TEST_SPRINTF(LG_width_prec_plus_inf, "%+10.5LG", (long double)INFINITY,
             long double)
TEST_SPRINTF(LG_width_prec_spac_inf, "% 10.5LG", (long double)INFINITY,
             long double)
TEST_SPRINTF(LG_width_prec_hash_inf, "%#10.5LG", (long double)INFINITY,
             long double)
TEST_SPRINTF(LG_width_prec_fzer_inf, "%010.5LG", (long double)INFINITY,
             long double)
TEST_SPRINTF(LG_width_prec_mins_ng_inf, "%-10.5LG", (long double)(-INFINITY),
             long double)
TEST_SPRINTF(LG_width_prec_plus_ng_inf, "%+10.5LG", (long double)(-INFINITY),
             long double)
TEST_SPRINTF(LG_width_prec_spac_ng_inf, "% 10.5LG", (long double)(-INFINITY),
             long double)
TEST_SPRINTF(LG_width_prec_hash_ng_inf, "%#10.5LG", (long double)(-INFINITY),
             long double)
TEST_SPRINTF(LG_width_prec_fzer_ng_inf, "%010.5LG", (long double)(-INFINITY),
             long double)

TEST_SPRINTF(LG_zrwth_zrpc_plus_nan, "%+0.0LG", (long double)NAN, long double)
TEST_SPRINTF(LG_zrwth_zrpc_spac_nan, "% 0.0LG", (long double)NAN, long double)
TEST_SPRINTF(LG_zrwth_zrpc_hash_nan, "%#0.0LG", (long double)NAN, long double)
TEST_SPRINTF(LG_zrwth_zrpc_plus_inf, "%+0.0LG", (long double)INFINITY,
             long double)
TEST_SPRINTF(LG_zrwth_zrpc_spac_inf, "% 0.0LG", (long double)INFINITY,
             long double)
TEST_SPRINTF(LG_zrwth_zrpc_hash_inf, "%#0.0LG", (long double)INFINITY,
             long double)
TEST_SPRINTF(LG_zrwth_zrpc_plus_ng_inf, "%+0.0LG", (long double)(-INFINITY),
             long double)
TEST_SPRINTF(LG_zrwth_zrpc_spac_ng_inf, "% 0.0LG", (long double)(-INFINITY),
             long double)
TEST_SPRINTF(LG_zrwth_zrpc_hash_ng_inf, "%#0.0LG", (long double)(-INFINITY),
             long double)

TEST_SPRINTF_2(LG_dynamic_prec_nan, "%.*LG", 5, (long double)NAN, long double)
TEST_SPRINTF_2(LG_dynamic_prec_inf, "%.*LG", 5, (long double)INFINITY,
               long double)
TEST_SPRINTF_2(LG_dynamic_prec_ng_inf, "%.*LG", 5, (long double)(-INFINITY),
               long double)

TEST_SPRINTF_2(LG_dynamic_width_nan, "%*LG", 10, (long double)NAN, long double)
TEST_SPRINTF_2(LG_dynamic_width_inf, "%*LG", 10, (long double)INFINITY,
               long double)
TEST_SPRINTF_2(LG_dynamic_width_ng_inf, "%*LG", 10, (long double)(-INFINITY),
               long double)

TEST_SPRINTF_3(LG_dynamic_width_prec_nan, "%*.*LG", 10, 5, (long double)NAN,
               long double)
TEST_SPRINTF_3(LG_dynamic_width_prec_inf, "%*.*LG", 10, 5,
               (long double)INFINITY, long double)
TEST_SPRINTF_3(LG_dynamic_width_prec_ng_inf, "%*.*LG", 10, 5,
               (long double)(-INFINITY), long double)
#pragma endregion

// =========================================================================
// Вещественные типы 0
// =========================================================================
#pragma region
TEST_SPRINTF(e_mins_zero, "%-e", 0.0, double)
TEST_SPRINTF(e_plus_zero, "%+e", 0.0, double)
TEST_SPRINTF(e_spac_zero, "% e", 0.0, double)
TEST_SPRINTF(e_hash_zero, "%#e", 0.0, double)
TEST_SPRINTF(e_fzer_zero, "%0e", 0.0, double)

TEST_SPRINTF(e_width_zero, "%5e", 0.0, double)
TEST_SPRINTF(e_zrpc_zero, "%.0e", 0.0, double)
TEST_SPRINTF(e_prec_zero, "%.5e", 0.0, double)
TEST_SPRINTF(e_width_prec_zero, "%10.5e", 0.0, double)

TEST_SPRINTF(e_width_mins_zero, "%-5e", 0.0, double)
TEST_SPRINTF(e_width_plus_zero, "%+5e", 0.0, double)
TEST_SPRINTF(e_width_spac_zero, "% 5e", 0.0, double)
TEST_SPRINTF(e_width_hash_zero, "%#5e", 0.0, double)
TEST_SPRINTF(e_width_fzer_zero, "%05e", 0.0, double)

TEST_SPRINTF(e_zrwth_plus_zero, "%+0e", 0.0, double)
TEST_SPRINTF(e_zrwth_spac_zero, "% 0e", 0.0, double)
TEST_SPRINTF(e_zrwth_hash_zero, "%#0e", 0.0, double)

TEST_SPRINTF(e_prec_mins_zero, "%-.5e", 0.0, double)
TEST_SPRINTF(e_prec_plus_zero, "%+.5e", 0.0, double)
TEST_SPRINTF(e_prec_spac_zero, "% .5e", 0.0, double)
TEST_SPRINTF(e_prec_hash_zero, "%#.5e", 0.0, double)
TEST_SPRINTF(e_prec_fzer_zero, "%0.5e", 0.0, double)

TEST_SPRINTF(e_zrpc_mins_zero, "%-.0e", 0.0, double)
TEST_SPRINTF(e_zrpc_plus_zero, "%+.0e", 0.0, double)
TEST_SPRINTF(e_zrpc_spac_zero, "% .0e", 0.0, double)
TEST_SPRINTF(e_zrpc_hash_zero, "%#.0e", 0.0, double)
TEST_SPRINTF(e_zrpc_fzer_zero, "%0.0e", 0.0, double)

TEST_SPRINTF(e_width_prec_mins_zero, "%-10.5e", 0.0, double)
TEST_SPRINTF(e_width_prec_plus_zero, "%+10.5e", 0.0, double)
TEST_SPRINTF(e_width_prec_spac_zero, "% 10.5e", 0.0, double)
TEST_SPRINTF(e_width_prec_hash_zero, "%#10.5e", 0.0, double)
TEST_SPRINTF(e_width_prec_fzer_zero, "%010.5e", 0.0, double)

TEST_SPRINTF(e_zrwth_zrpc_plus_zero, "%+0.0e", 0.0, double)
TEST_SPRINTF(e_zrwth_zrpc_spac_zero, "% 0.0e", 0.0, double)
TEST_SPRINTF(e_zrwth_zrpc_hash_zero, "%#0.0e", 0.0, double)

TEST_SPRINTF_2(e_dynamic_width_zero, "%*e", 10, 0.0, double)
TEST_SPRINTF_2(e_dynamic_prec_zero, "%.*e", 5, 0.0, double)
TEST_SPRINTF_3(e_dynamic_width_prec_zero, "%*.*e", 10, 5, 0.0, double)

// =========================================================================

TEST_SPRINTF(E_mins_zero, "%-E", 0.0, double)
TEST_SPRINTF(E_plus_zero, "%+E", 0.0, double)
TEST_SPRINTF(E_spac_zero, "% E", 0.0, double)
TEST_SPRINTF(E_hash_zero, "%#E", 0.0, double)
TEST_SPRINTF(E_fzer_zero, "%0E", 0.0, double)

TEST_SPRINTF(E_width_zero, "%5E", 0.0, double)
TEST_SPRINTF(E_zrpc_zero, "%.0E", 0.0, double)
TEST_SPRINTF(E_prec_zero, "%.5E", 0.0, double)
TEST_SPRINTF(E_width_prec_zero, "%10.5E", 0.0, double)

TEST_SPRINTF(E_width_mins_zero, "%-5E", 0.0, double)
TEST_SPRINTF(E_width_plus_zero, "%+5E", 0.0, double)
TEST_SPRINTF(E_width_spac_zero, "% 5E", 0.0, double)
TEST_SPRINTF(E_width_hash_zero, "%#5E", 0.0, double)
TEST_SPRINTF(E_width_fzer_zero, "%05E", 0.0, double)

TEST_SPRINTF(E_zrwth_plus_zero, "%+0E", 0.0, double)
TEST_SPRINTF(E_zrwth_spac_zero, "% 0E", 0.0, double)
TEST_SPRINTF(E_zrwth_hash_zero, "%#0E", 0.0, double)

TEST_SPRINTF(E_prec_mins_zero, "%-.5E", 0.0, double)
TEST_SPRINTF(E_prec_plus_zero, "%+.5E", 0.0, double)
TEST_SPRINTF(E_prec_spac_zero, "% .5E", 0.0, double)
TEST_SPRINTF(E_prec_hash_zero, "%#.5E", 0.0, double)
TEST_SPRINTF(E_prec_fzer_zero, "%0.5E", 0.0, double)

TEST_SPRINTF(E_zrpc_mins_zero, "%-.0E", 0.0, double)
TEST_SPRINTF(E_zrpc_plus_zero, "%+.0E", 0.0, double)
TEST_SPRINTF(E_zrpc_spac_zero, "% .0E", 0.0, double)
TEST_SPRINTF(E_zrpc_hash_zero, "%#.0E", 0.0, double)
TEST_SPRINTF(E_zrpc_fzer_zero, "%0.0E", 0.0, double)

TEST_SPRINTF(E_width_prec_mins_zero, "%-10.5E", 0.0, double)
TEST_SPRINTF(E_width_prec_plus_zero, "%+10.5E", 0.0, double)
TEST_SPRINTF(E_width_prec_spac_zero, "% 10.5E", 0.0, double)
TEST_SPRINTF(E_width_prec_hash_zero, "%#10.5E", 0.0, double)
TEST_SPRINTF(E_width_prec_fzer_zero, "%010.5E", 0.0, double)

TEST_SPRINTF(E_zrwth_zrpc_plus_zero, "%+0.0E", 0.0, double)
TEST_SPRINTF(E_zrwth_zrpc_spac_zero, "% 0.0E", 0.0, double)
TEST_SPRINTF(E_zrwth_zrpc_hash_zero, "%#0.0E", 0.0, double)

TEST_SPRINTF_2(E_dynamic_width_zero, "%*E", 10, 0.0, double)
TEST_SPRINTF_2(E_dynamic_prec_zero, "%.*E", 5, 0.0, double)
TEST_SPRINTF_3(E_dynamic_width_prec_zero, "%*.*E", 10, 5, 0.0, double)

// =========================================================================

TEST_SPRINTF(f_mins_zero, "%-f", 0.0, double)
TEST_SPRINTF(f_plus_zero, "%+f", 0.0, double)
TEST_SPRINTF(f_spac_zero, "% f", 0.0, double)
TEST_SPRINTF(f_hash_zero, "%#f", 0.0, double)
TEST_SPRINTF(f_fzer_zero, "%0f", 0.0, double)

TEST_SPRINTF(f_width_zero, "%5f", 0.0, double)
TEST_SPRINTF(f_zrpc_zero, "%.0f", 0.0, double)
TEST_SPRINTF(f_prec_zero, "%.5f", 0.0, double)
TEST_SPRINTF(f_width_prec_zero, "%10.5f", 0.0, double)

TEST_SPRINTF(f_width_mins_zero, "%-5f", 0.0, double)
TEST_SPRINTF(f_width_plus_zero, "%+5f", 0.0, double)
TEST_SPRINTF(f_width_spac_zero, "% 5f", 0.0, double)
TEST_SPRINTF(f_width_hash_zero, "%#5f", 0.0, double)
TEST_SPRINTF(f_width_fzer_zero, "%05f", 0.0, double)

TEST_SPRINTF(f_zrwth_plus_zero, "%+0f", 0.0, double)
TEST_SPRINTF(f_zrwth_spac_zero, "% 0f", 0.0, double)
TEST_SPRINTF(f_zrwth_hash_zero, "%#0f", 0.0, double)

TEST_SPRINTF(f_prec_mins_zero, "%-.5f", 0.0, double)
TEST_SPRINTF(f_prec_plus_zero, "%+.5f", 0.0, double)
TEST_SPRINTF(f_prec_spac_zero, "% .5f", 0.0, double)
TEST_SPRINTF(f_prec_hash_zero, "%#.5f", 0.0, double)
TEST_SPRINTF(f_prec_fzer_zero, "%0.5f", 0.0, double)

TEST_SPRINTF(f_zrpc_mins_zero, "%-.0f", 0.0, double)
TEST_SPRINTF(f_zrpc_plus_zero, "%+.0f", 0.0, double)
TEST_SPRINTF(f_zrpc_spac_zero, "% .0f", 0.0, double)
TEST_SPRINTF(f_zrpc_hash_zero, "%#.0f", 0.0, double)
TEST_SPRINTF(f_zrpc_fzer_zero, "%0.0f", 0.0, double)

TEST_SPRINTF(f_width_prec_mins_zero, "%-10.5f", 0.0, double)
TEST_SPRINTF(f_width_prec_plus_zero, "%+10.5f", 0.0, double)
TEST_SPRINTF(f_width_prec_spac_zero, "% 10.5f", 0.0, double)
TEST_SPRINTF(f_width_prec_hash_zero, "%#10.5f", 0.0, double)
TEST_SPRINTF(f_width_prec_fzer_zero, "%010.5f", 0.0, double)

TEST_SPRINTF(f_zrwth_zrpc_plus_zero, "%+0.0f", 0.0, double)
TEST_SPRINTF(f_zrwth_zrpc_spac_zero, "% 0.0f", 0.0, double)
TEST_SPRINTF(f_zrwth_zrpc_hash_zero, "%#0.0f", 0.0, double)

TEST_SPRINTF_2(f_dynamic_width_zero, "%*f", 10, 0.0, double)
TEST_SPRINTF_2(f_dynamic_prec_zero, "%.*f", 5, 0.0, double)
TEST_SPRINTF_3(f_dynamic_width_prec_zero, "%*.*f", 10, 5, 0.0, double)

// =========================================================================

TEST_SPRINTF(g_mins_zero, "%-g", 0.0, double)
TEST_SPRINTF(g_plus_zero, "%+g", 0.0, double)
TEST_SPRINTF(g_spac_zero, "% g", 0.0, double)
TEST_SPRINTF(g_hash_zero, "%#g", 0.0, double)
TEST_SPRINTF(g_fzer_zero, "%0g", 0.0, double)

TEST_SPRINTF(g_width_zero, "%5g", 0.0, double)
TEST_SPRINTF(g_zrpc_zero, "%.0g", 0.0, double)
TEST_SPRINTF(g_prec_zero, "%.5g", 0.0, double)
TEST_SPRINTF(g_width_prec_zero, "%10.5g", 0.0, double)

TEST_SPRINTF(g_width_mins_zero, "%-5g", 0.0, double)
TEST_SPRINTF(g_width_plus_zero, "%+5g", 0.0, double)
TEST_SPRINTF(g_width_spac_zero, "% 5g", 0.0, double)
TEST_SPRINTF(g_width_hash_zero, "%#5g", 0.0, double)
TEST_SPRINTF(g_width_fzer_zero, "%05g", 0.0, double)

TEST_SPRINTF(g_zrwth_plus_zero, "%+0g", 0.0, double)
TEST_SPRINTF(g_zrwth_spac_zero, "% 0g", 0.0, double)
TEST_SPRINTF(g_zrwth_hash_zero, "%#0g", 0.0, double)

TEST_SPRINTF(g_prec_mins_zero, "%-.5g", 0.0, double)
TEST_SPRINTF(g_prec_plus_zero, "%+.5g", 0.0, double)
TEST_SPRINTF(g_prec_spac_zero, "% .5g", 0.0, double)
TEST_SPRINTF(g_prec_hash_zero, "%#.5g", 0.0, double)
TEST_SPRINTF(g_prec_fzer_zero, "%0.5g", 0.0, double)

TEST_SPRINTF(g_zrpc_mins_zero, "%-.0g", 0.0, double)
TEST_SPRINTF(g_zrpc_plus_zero, "%+.0g", 0.0, double)
TEST_SPRINTF(g_zrpc_spac_zero, "% .0g", 0.0, double)
TEST_SPRINTF(g_zrpc_hash_zero, "%#.0g", 0.0, double)
TEST_SPRINTF(g_zrpc_fzer_zero, "%0.0g", 0.0, double)

TEST_SPRINTF(g_width_prec_mins_zero, "%-10.5g", 0.0, double)
TEST_SPRINTF(g_width_prec_plus_zero, "%+10.5g", 0.0, double)
TEST_SPRINTF(g_width_prec_spac_zero, "% 10.5g", 0.0, double)
TEST_SPRINTF(g_width_prec_hash_zero, "%#10.5g", 0.0, double)
TEST_SPRINTF(g_width_prec_fzer_zero, "%010.5g", 0.0, double)

TEST_SPRINTF(g_zrwth_zrpc_plus_zero, "%+0.0g", 0.0, double)
TEST_SPRINTF(g_zrwth_zrpc_spac_zero, "% 0.0g", 0.0, double)
TEST_SPRINTF(g_zrwth_zrpc_hash_zero, "%#0.0g", 0.0, double)

TEST_SPRINTF_2(g_dynamic_width_zero, "%*g", 10, 0.0, double)
TEST_SPRINTF_2(g_dynamic_prec_zero, "%.*g", 5, 0.0, double)
TEST_SPRINTF_3(g_dynamic_width_prec_zero, "%*.*g", 10, 5, 0.0, double)

// =========================================================================

TEST_SPRINTF(G_mins_zero, "%-G", 0.0, double)
TEST_SPRINTF(G_plus_zero, "%+G", 0.0, double)
TEST_SPRINTF(G_spac_zero, "% G", 0.0, double)
TEST_SPRINTF(G_hash_zero, "%#G", 0.0, double)
TEST_SPRINTF(G_fzer_zero, "%0G", 0.0, double)

TEST_SPRINTF(G_width_zero, "%5G", 0.0, double)
TEST_SPRINTF(G_zrpc_zero, "%.0G", 0.0, double)
TEST_SPRINTF(G_prec_zero, "%.5G", 0.0, double)
TEST_SPRINTF(G_width_prec_zero, "%10.5G", 0.0, double)

TEST_SPRINTF(G_width_mins_zero, "%-5G", 0.0, double)
TEST_SPRINTF(G_width_plus_zero, "%+5G", 0.0, double)
TEST_SPRINTF(G_width_spac_zero, "% 5G", 0.0, double)
TEST_SPRINTF(G_width_hash_zero, "%#5G", 0.0, double)
TEST_SPRINTF(G_width_fzer_zero, "%05G", 0.0, double)

TEST_SPRINTF(G_zrwth_plus_zero, "%+0G", 0.0, double)
TEST_SPRINTF(G_zrwth_spac_zero, "% 0G", 0.0, double)
TEST_SPRINTF(G_zrwth_hash_zero, "%#0G", 0.0, double)

TEST_SPRINTF(G_prec_mins_zero, "%-.5G", 0.0, double)
TEST_SPRINTF(G_prec_plus_zero, "%+.5G", 0.0, double)
TEST_SPRINTF(G_prec_spac_zero, "% .5G", 0.0, double)
TEST_SPRINTF(G_prec_hash_zero, "%#.5G", 0.0, double)
TEST_SPRINTF(G_prec_fzer_zero, "%0.5G", 0.0, double)

TEST_SPRINTF(G_zrpc_mins_zero, "%-.0G", 0.0, double)
TEST_SPRINTF(G_zrpc_plus_zero, "%+.0G", 0.0, double)
TEST_SPRINTF(G_zrpc_spac_zero, "% .0G", 0.0, double)
TEST_SPRINTF(G_zrpc_hash_zero, "%#.0G", 0.0, double)
TEST_SPRINTF(G_zrpc_fzer_zero, "%0.0G", 0.0, double)

TEST_SPRINTF(G_width_prec_mins_zero, "%-10.5G", 0.0, double)
TEST_SPRINTF(G_width_prec_plus_zero, "%+10.5G", 0.0, double)
TEST_SPRINTF(G_width_prec_spac_zero, "% 10.5G", 0.0, double)
TEST_SPRINTF(G_width_prec_hash_zero, "%#10.5G", 0.0, double)
TEST_SPRINTF(G_width_prec_fzer_zero, "%010.5G", 0.0, double)

TEST_SPRINTF(G_zrwth_zrpc_plus_zero, "%+0.0G", 0.0, double)
TEST_SPRINTF(G_zrwth_zrpc_spac_zero, "% 0.0G", 0.0, double)
TEST_SPRINTF(G_zrwth_zrpc_hash_zero, "%#0.0G", 0.0, double)

TEST_SPRINTF_2(G_dynamic_width_zero, "%*G", 10, 0.0, double)
TEST_SPRINTF_2(G_dynamic_prec_zero, "%.*G", 5, 0.0, double)
TEST_SPRINTF_3(G_dynamic_width_prec_zero, "%*.*G", 10, 5, 0.0, double)

// =========================================================================

TEST_SPRINTF(le_mins_zero, "%-le", 0.0, double)
TEST_SPRINTF(le_plus_zero, "%+le", 0.0, double)
TEST_SPRINTF(le_spac_zero, "% le", 0.0, double)
TEST_SPRINTF(le_hash_zero, "%#le", 0.0, double)
TEST_SPRINTF(le_fzer_zero, "%0le", 0.0, double)

TEST_SPRINTF(le_width_zero, "%5le", 0.0, double)
TEST_SPRINTF(le_zrpc_zero, "%.0le", 0.0, double)
TEST_SPRINTF(le_prec_zero, "%.5le", 0.0, double)
TEST_SPRINTF(le_width_prec_zero, "%10.5le", 0.0, double)

TEST_SPRINTF(le_width_mins_zero, "%-5le", 0.0, double)
TEST_SPRINTF(le_width_plus_zero, "%+5le", 0.0, double)
TEST_SPRINTF(le_width_spac_zero, "% 5le", 0.0, double)
TEST_SPRINTF(le_width_hash_zero, "%#5le", 0.0, double)
TEST_SPRINTF(le_width_fzer_zero, "%05le", 0.0, double)

TEST_SPRINTF(le_zrwth_plus_zero, "%+0le", 0.0, double)
TEST_SPRINTF(le_zrwth_spac_zero, "% 0le", 0.0, double)
TEST_SPRINTF(le_zrwth_hash_zero, "%#0le", 0.0, double)

TEST_SPRINTF(le_prec_mins_zero, "%-.5le", 0.0, double)
TEST_SPRINTF(le_prec_plus_zero, "%+.5le", 0.0, double)
TEST_SPRINTF(le_prec_spac_zero, "% .5le", 0.0, double)
TEST_SPRINTF(le_prec_hash_zero, "%#.5le", 0.0, double)
TEST_SPRINTF(le_prec_fzer_zero, "%0.5le", 0.0, double)

TEST_SPRINTF(le_zrpc_mins_zero, "%-.0le", 0.0, double)
TEST_SPRINTF(le_zrpc_plus_zero, "%+.0le", 0.0, double)
TEST_SPRINTF(le_zrpc_spac_zero, "% .0le", 0.0, double)
TEST_SPRINTF(le_zrpc_hash_zero, "%#.0le", 0.0, double)
TEST_SPRINTF(le_zrpc_fzer_zero, "%0.0le", 0.0, double)

TEST_SPRINTF(le_width_prec_mins_zero, "%-10.5le", 0.0, double)
TEST_SPRINTF(le_width_prec_plus_zero, "%+10.5le", 0.0, double)
TEST_SPRINTF(le_width_prec_spac_zero, "% 10.5le", 0.0, double)
TEST_SPRINTF(le_width_prec_hash_zero, "%#10.5le", 0.0, double)
TEST_SPRINTF(le_width_prec_fzer_zero, "%010.5le", 0.0, double)

TEST_SPRINTF(le_zrwth_zrpc_plus_zero, "%+0.0le", 0.0, double)
TEST_SPRINTF(le_zrwth_zrpc_spac_zero, "% 0.0le", 0.0, double)
TEST_SPRINTF(le_zrwth_zrpc_hash_zero, "%#0.0le", 0.0, double)

TEST_SPRINTF_2(le_dynamic_width_zero, "%*le", 10, 0.0, double)
TEST_SPRINTF_2(le_dynamic_prec_zero, "%.*le", 5, 0.0, double)
TEST_SPRINTF_3(le_dynamic_width_prec_zero, "%*.*le", 10, 5, 0.0, double)

// =========================================================================

TEST_SPRINTF(lE_mins_zero, "%-lE", 0.0, double)
TEST_SPRINTF(lE_plus_zero, "%+lE", 0.0, double)
TEST_SPRINTF(lE_spac_zero, "% lE", 0.0, double)
TEST_SPRINTF(lE_hash_zero, "%#lE", 0.0, double)
TEST_SPRINTF(lE_fzer_zero, "%0lE", 0.0, double)

TEST_SPRINTF(lE_width_zero, "%5lE", 0.0, double)
TEST_SPRINTF(lE_zrpc_zero, "%.0lE", 0.0, double)
TEST_SPRINTF(lE_prec_zero, "%.5lE", 0.0, double)
TEST_SPRINTF(lE_width_prec_zero, "%10.5lE", 0.0, double)

TEST_SPRINTF(lE_width_mins_zero, "%-5lE", 0.0, double)
TEST_SPRINTF(lE_width_plus_zero, "%+5lE", 0.0, double)
TEST_SPRINTF(lE_width_spac_zero, "% 5lE", 0.0, double)
TEST_SPRINTF(lE_width_hash_zero, "%#5lE", 0.0, double)
TEST_SPRINTF(lE_width_fzer_zero, "%05lE", 0.0, double)

TEST_SPRINTF(lE_zrwth_plus_zero, "%+0lE", 0.0, double)
TEST_SPRINTF(lE_zrwth_spac_zero, "% 0lE", 0.0, double)
TEST_SPRINTF(lE_zrwth_hash_zero, "%#0lE", 0.0, double)

TEST_SPRINTF(lE_prec_mins_zero, "%-.5lE", 0.0, double)
TEST_SPRINTF(lE_prec_plus_zero, "%+.5lE", 0.0, double)
TEST_SPRINTF(lE_prec_spac_zero, "% .5lE", 0.0, double)
TEST_SPRINTF(lE_prec_hash_zero, "%#.5lE", 0.0, double)
TEST_SPRINTF(lE_prec_fzer_zero, "%0.5lE", 0.0, double)

TEST_SPRINTF(lE_zrpc_mins_zero, "%-.0lE", 0.0, double)
TEST_SPRINTF(lE_zrpc_plus_zero, "%+.0lE", 0.0, double)
TEST_SPRINTF(lE_zrpc_spac_zero, "% .0lE", 0.0, double)
TEST_SPRINTF(lE_zrpc_hash_zero, "%#.0lE", 0.0, double)
TEST_SPRINTF(lE_zrpc_fzer_zero, "%0.0lE", 0.0, double)

TEST_SPRINTF(lE_width_prec_mins_zero, "%-10.5lE", 0.0, double)
TEST_SPRINTF(lE_width_prec_plus_zero, "%+10.5lE", 0.0, double)
TEST_SPRINTF(lE_width_prec_spac_zero, "% 10.5lE", 0.0, double)
TEST_SPRINTF(lE_width_prec_hash_zero, "%#10.5lE", 0.0, double)
TEST_SPRINTF(lE_width_prec_fzer_zero, "%010.5lE", 0.0, double)

TEST_SPRINTF(lE_zrwth_zrpc_plus_zero, "%+0.0lE", 0.0, double)
TEST_SPRINTF(lE_zrwth_zrpc_spac_zero, "% 0.0lE", 0.0, double)
TEST_SPRINTF(lE_zrwth_zrpc_hash_zero, "%#0.0lE", 0.0, double)

TEST_SPRINTF_2(lE_dynamic_width_zero, "%*lE", 10, 0.0, double)
TEST_SPRINTF_2(lE_dynamic_prec_zero, "%.*lE", 5, 0.0, double)
TEST_SPRINTF_3(lE_dynamic_width_prec_zero, "%*.*lE", 10, 5, 0.0, double)

// =========================================================================

TEST_SPRINTF(lf_mins_zero, "%-lf", 0.0, double)
TEST_SPRINTF(lf_plus_zero, "%+lf", 0.0, double)
TEST_SPRINTF(lf_spac_zero, "% lf", 0.0, double)
TEST_SPRINTF(lf_hash_zero, "%#lf", 0.0, double)
TEST_SPRINTF(lf_fzer_zero, "%0lf", 0.0, double)

TEST_SPRINTF(lf_width_zero, "%5lf", 0.0, double)
TEST_SPRINTF(lf_zrpc_zero, "%.0lf", 0.0, double)
TEST_SPRINTF(lf_prec_zero, "%.5lf", 0.0, double)
TEST_SPRINTF(lf_width_prec_zero, "%10.5lf", 0.0, double)

TEST_SPRINTF(lf_width_mins_zero, "%-5lf", 0.0, double)
TEST_SPRINTF(lf_width_plus_zero, "%+5lf", 0.0, double)
TEST_SPRINTF(lf_width_spac_zero, "% 5lf", 0.0, double)
TEST_SPRINTF(lf_width_hash_zero, "%#5lf", 0.0, double)
TEST_SPRINTF(lf_width_fzer_zero, "%05lf", 0.0, double)

TEST_SPRINTF(lf_zrwth_plus_zero, "%+0lf", 0.0, double)
TEST_SPRINTF(lf_zrwth_spac_zero, "% 0lf", 0.0, double)
TEST_SPRINTF(lf_zrwth_hash_zero, "%#0lf", 0.0, double)

TEST_SPRINTF(lf_prec_mins_zero, "%-.5lf", 0.0, double)
TEST_SPRINTF(lf_prec_plus_zero, "%+.5lf", 0.0, double)
TEST_SPRINTF(lf_prec_spac_zero, "% .5lf", 0.0, double)
TEST_SPRINTF(lf_prec_hash_zero, "%#.5lf", 0.0, double)
TEST_SPRINTF(lf_prec_fzer_zero, "%0.5lf", 0.0, double)

TEST_SPRINTF(lf_zrpc_mins_zero, "%-.0lf", 0.0, double)
TEST_SPRINTF(lf_zrpc_plus_zero, "%+.0lf", 0.0, double)
TEST_SPRINTF(lf_zrpc_spac_zero, "% .0lf", 0.0, double)
TEST_SPRINTF(lf_zrpc_hash_zero, "%#.0lf", 0.0, double)
TEST_SPRINTF(lf_zrpc_fzer_zero, "%0.0lf", 0.0, double)

TEST_SPRINTF(lf_width_prec_mins_zero, "%-10.5lf", 0.0, double)
TEST_SPRINTF(lf_width_prec_plus_zero, "%+10.5lf", 0.0, double)
TEST_SPRINTF(lf_width_prec_spac_zero, "% 10.5lf", 0.0, double)
TEST_SPRINTF(lf_width_prec_hash_zero, "%#10.5lf", 0.0, double)
TEST_SPRINTF(lf_width_prec_fzer_zero, "%010.5lf", 0.0, double)

TEST_SPRINTF(lf_zrwth_zrpc_plus_zero, "%+0.0lf", 0.0, double)
TEST_SPRINTF(lf_zrwth_zrpc_spac_zero, "% 0.0lf", 0.0, double)
TEST_SPRINTF(lf_zrwth_zrpc_hash_zero, "%#0.0lf", 0.0, double)

TEST_SPRINTF_2(lf_dynamic_width_zero, "%*lf", 10, 0.0, double)
TEST_SPRINTF_2(lf_dynamic_prec_zero, "%.*lf", 5, 0.0, double)
TEST_SPRINTF_3(lf_dynamic_width_prec_zero, "%*.*lf", 10, 5, 0.0, double)

// =========================================================================

TEST_SPRINTF(lg_mins_zero, "%-lg", 0.0, double)
TEST_SPRINTF(lg_plus_zero, "%+lg", 0.0, double)
TEST_SPRINTF(lg_spac_zero, "% lg", 0.0, double)
TEST_SPRINTF(lg_hash_zero, "%#lg", 0.0, double)
TEST_SPRINTF(lg_fzer_zero, "%0lg", 0.0, double)

TEST_SPRINTF(lg_width_zero, "%5lg", 0.0, double)
TEST_SPRINTF(lg_zrpc_zero, "%.0lg", 0.0, double)
TEST_SPRINTF(lg_prec_zero, "%.5lg", 0.0, double)
TEST_SPRINTF(lg_width_prec_zero, "%10.5lg", 0.0, double)

TEST_SPRINTF(lg_width_mins_zero, "%-5lg", 0.0, double)
TEST_SPRINTF(lg_width_plus_zero, "%+5lg", 0.0, double)
TEST_SPRINTF(lg_width_spac_zero, "% 5lg", 0.0, double)
TEST_SPRINTF(lg_width_hash_zero, "%#5lg", 0.0, double)
TEST_SPRINTF(lg_width_fzer_zero, "%05lg", 0.0, double)

TEST_SPRINTF(lg_zrwth_plus_zero, "%+0lg", 0.0, double)
TEST_SPRINTF(lg_zrwth_spac_zero, "% 0lg", 0.0, double)
TEST_SPRINTF(lg_zrwth_hash_zero, "%#0lg", 0.0, double)

TEST_SPRINTF(lg_prec_mins_zero, "%-.5lg", 0.0, double)
TEST_SPRINTF(lg_prec_plus_zero, "%+.5lg", 0.0, double)
TEST_SPRINTF(lg_prec_spac_zero, "% .5lg", 0.0, double)
TEST_SPRINTF(lg_prec_hash_zero, "%#.5lg", 0.0, double)
TEST_SPRINTF(lg_prec_fzer_zero, "%0.5lg", 0.0, double)

TEST_SPRINTF(lg_zrpc_mins_zero, "%-.0lg", 0.0, double)
TEST_SPRINTF(lg_zrpc_plus_zero, "%+.0lg", 0.0, double)
TEST_SPRINTF(lg_zrpc_spac_zero, "% .0lg", 0.0, double)
TEST_SPRINTF(lg_zrpc_hash_zero, "%#.0lg", 0.0, double)
TEST_SPRINTF(lg_zrpc_fzer_zero, "%0.0lg", 0.0, double)

TEST_SPRINTF(lg_width_prec_mins_zero, "%-10.5lg", 0.0, double)
TEST_SPRINTF(lg_width_prec_plus_zero, "%+10.5lg", 0.0, double)
TEST_SPRINTF(lg_width_prec_spac_zero, "% 10.5lg", 0.0, double)
TEST_SPRINTF(lg_width_prec_hash_zero, "%#10.5lg", 0.0, double)
TEST_SPRINTF(lg_width_prec_fzer_zero, "%010.5lg", 0.0, double)

TEST_SPRINTF(lg_zrwth_zrpc_plus_zero, "%+0.0lg", 0.0, double)
TEST_SPRINTF(lg_zrwth_zrpc_spac_zero, "% 0.0lg", 0.0, double)
TEST_SPRINTF(lg_zrwth_zrpc_hash_zero, "%#0.0lg", 0.0, double)

TEST_SPRINTF_2(lg_dynamic_width_zero, "%*lg", 10, 0.0, double)
TEST_SPRINTF_2(lg_dynamic_prec_zero, "%.*lg", 5, 0.0, double)
TEST_SPRINTF_3(lg_dynamic_width_prec_zero, "%*.*lg", 10, 5, 0.0, double)

// =========================================================================

TEST_SPRINTF(lG_mins_zero, "%-lG", 0.0, double)
TEST_SPRINTF(lG_plus_zero, "%+lG", 0.0, double)
TEST_SPRINTF(lG_spac_zero, "% lG", 0.0, double)
TEST_SPRINTF(lG_hash_zero, "%#lG", 0.0, double)
TEST_SPRINTF(lG_fzer_zero, "%0lG", 0.0, double)

TEST_SPRINTF(lG_width_zero, "%5lG", 0.0, double)
TEST_SPRINTF(lG_zrpc_zero, "%.0lG", 0.0, double)
TEST_SPRINTF(lG_prec_zero, "%.5lG", 0.0, double)
TEST_SPRINTF(lG_width_prec_zero, "%10.5lG", 0.0, double)

TEST_SPRINTF(lG_width_mins_zero, "%-5lG", 0.0, double)
TEST_SPRINTF(lG_width_plus_zero, "%+5lG", 0.0, double)
TEST_SPRINTF(lG_width_spac_zero, "% 5lG", 0.0, double)
TEST_SPRINTF(lG_width_hash_zero, "%#5lG", 0.0, double)
TEST_SPRINTF(lG_width_fzer_zero, "%05lG", 0.0, double)

TEST_SPRINTF(lG_zrwth_plus_zero, "%+0lG", 0.0, double)
TEST_SPRINTF(lG_zrwth_spac_zero, "% 0lG", 0.0, double)
TEST_SPRINTF(lG_zrwth_hash_zero, "%#0lG", 0.0, double)

TEST_SPRINTF(lG_prec_mins_zero, "%-.5lG", 0.0, double)
TEST_SPRINTF(lG_prec_plus_zero, "%+.5lG", 0.0, double)
TEST_SPRINTF(lG_prec_spac_zero, "% .5lG", 0.0, double)
TEST_SPRINTF(lG_prec_hash_zero, "%#.5lG", 0.0, double)
TEST_SPRINTF(lG_prec_fzer_zero, "%0.5lG", 0.0, double)

TEST_SPRINTF(lG_zrpc_mins_zero, "%-.0lG", 0.0, double)
TEST_SPRINTF(lG_zrpc_plus_zero, "%+.0lG", 0.0, double)
TEST_SPRINTF(lG_zrpc_spac_zero, "% .0lG", 0.0, double)
TEST_SPRINTF(lG_zrpc_hash_zero, "%#.0lG", 0.0, double)
TEST_SPRINTF(lG_zrpc_fzer_zero, "%0.0lG", 0.0, double)

TEST_SPRINTF(lG_width_prec_mins_zero, "%-10.5lG", 0.0, double)
TEST_SPRINTF(lG_width_prec_plus_zero, "%+10.5lG", 0.0, double)
TEST_SPRINTF(lG_width_prec_spac_zero, "% 10.5lG", 0.0, double)
TEST_SPRINTF(lG_width_prec_hash_zero, "%#10.5lG", 0.0, double)
TEST_SPRINTF(lG_width_prec_fzer_zero, "%010.5lG", 0.0, double)

TEST_SPRINTF(lG_zrwth_zrpc_plus_zero, "%+0.0lG", 0.0, double)
TEST_SPRINTF(lG_zrwth_zrpc_spac_zero, "% 0.0lG", 0.0, double)
TEST_SPRINTF(lG_zrwth_zrpc_hash_zero, "%#0.0lG", 0.0, double)

TEST_SPRINTF_2(lG_dynamic_width_zero, "%*lG", 10, 0.0, double)
TEST_SPRINTF_2(lG_dynamic_prec_zero, "%.*lG", 5, 0.0, double)
TEST_SPRINTF_3(lG_dynamic_width_prec_zero, "%*.*lG", 10, 5, 0.0, double)

// =========================================================================

TEST_SPRINTF(Le_mins_zero, "%-Le", 0.0L, long double)
TEST_SPRINTF(Le_plus_zero, "%+Le", 0.0L, long double)
TEST_SPRINTF(Le_spac_zero, "% Le", 0.0L, long double)
TEST_SPRINTF(Le_hash_zero, "%#Le", 0.0L, long double)
TEST_SPRINTF(Le_fzer_zero, "%0Le", 0.0L, long double)

TEST_SPRINTF(Le_width_zero, "%5Le", 0.0L, long double)
TEST_SPRINTF(Le_zrpc_zero, "%.0Le", 0.0L, long double)
TEST_SPRINTF(Le_prec_zero, "%.5Le", 0.0L, long double)
TEST_SPRINTF(Le_width_prec_zero, "%10.5Le", 0.0L, long double)

TEST_SPRINTF(Le_width_mins_zero, "%-5Le", 0.0L, long double)
TEST_SPRINTF(Le_width_plus_zero, "%+5Le", 0.0L, long double)
TEST_SPRINTF(Le_width_spac_zero, "% 5Le", 0.0L, long double)
TEST_SPRINTF(Le_width_hash_zero, "%#5Le", 0.0L, long double)
TEST_SPRINTF(Le_width_fzer_zero, "%05Le", 0.0L, long double)

TEST_SPRINTF(Le_zrwth_plus_zero, "%+0Le", 0.0L, long double)
TEST_SPRINTF(Le_zrwth_spac_zero, "% 0Le", 0.0L, long double)
TEST_SPRINTF(Le_zrwth_hash_zero, "%#0Le", 0.0L, long double)

TEST_SPRINTF(Le_prec_mins_zero, "%-.5Le", 0.0L, long double)
TEST_SPRINTF(Le_prec_plus_zero, "%+.5Le", 0.0L, long double)
TEST_SPRINTF(Le_prec_spac_zero, "% .5Le", 0.0L, long double)
TEST_SPRINTF(Le_prec_hash_zero, "%#.5Le", 0.0L, long double)
TEST_SPRINTF(Le_prec_fzer_zero, "%0.5Le", 0.0L, long double)

TEST_SPRINTF(Le_zrpc_mins_zero, "%-.0Le", 0.0L, long double)
TEST_SPRINTF(Le_zrpc_plus_zero, "%+.0Le", 0.0L, long double)
TEST_SPRINTF(Le_zrpc_spac_zero, "% .0Le", 0.0L, long double)
TEST_SPRINTF(Le_zrpc_hash_zero, "%#.0Le", 0.0L, long double)
TEST_SPRINTF(Le_zrpc_fzer_zero, "%0.0Le", 0.0L, long double)

TEST_SPRINTF(Le_width_prec_mins_zero, "%-10.5Le", 0.0L, long double)
TEST_SPRINTF(Le_width_prec_plus_zero, "%+10.5Le", 0.0L, long double)
TEST_SPRINTF(Le_width_prec_spac_zero, "% 10.5Le", 0.0L, long double)
TEST_SPRINTF(Le_width_prec_hash_zero, "%#10.5Le", 0.0L, long double)
TEST_SPRINTF(Le_width_prec_fzer_zero, "%010.5Le", 0.0L, long double)

TEST_SPRINTF(Le_zrwth_zrpc_plus_zero, "%+0.0Le", 0.0L, long double)
TEST_SPRINTF(Le_zrwth_zrpc_spac_zero, "% 0.0Le", 0.0L, long double)
TEST_SPRINTF(Le_zrwth_zrpc_hash_zero, "%#0.0Le", 0.0L, long double)

TEST_SPRINTF_2(Le_dynamic_width_zero, "%*Le", 10, 0.0L, long double)
TEST_SPRINTF_2(Le_dynamic_prec_zero, "%.*Le", 5, 0.0L, long double)
TEST_SPRINTF_3(Le_dynamic_width_prec_zero, "%*.*Le", 10, 5, 0.0L, long double)

// =========================================================================

TEST_SPRINTF(LE_mins_zero, "%-LE", 0.0L, long double)
TEST_SPRINTF(LE_plus_zero, "%+LE", 0.0L, long double)
TEST_SPRINTF(LE_spac_zero, "% LE", 0.0L, long double)
TEST_SPRINTF(LE_hash_zero, "%#LE", 0.0L, long double)
TEST_SPRINTF(LE_fzer_zero, "%0LE", 0.0L, long double)

TEST_SPRINTF(LE_width_zero, "%5LE", 0.0L, long double)
TEST_SPRINTF(LE_zrpc_zero, "%.0LE", 0.0L, long double)
TEST_SPRINTF(LE_prec_zero, "%.5LE", 0.0L, long double)
TEST_SPRINTF(LE_width_prec_zero, "%10.5LE", 0.0L, long double)

TEST_SPRINTF(LE_width_mins_zero, "%-5LE", 0.0L, long double)
TEST_SPRINTF(LE_width_plus_zero, "%+5LE", 0.0L, long double)
TEST_SPRINTF(LE_width_spac_zero, "% 5LE", 0.0L, long double)
TEST_SPRINTF(LE_width_hash_zero, "%#5LE", 0.0L, long double)
TEST_SPRINTF(LE_width_fzer_zero, "%05LE", 0.0L, long double)

TEST_SPRINTF(LE_zrwth_plus_zero, "%+0LE", 0.0L, long double)
TEST_SPRINTF(LE_zrwth_spac_zero, "% 0LE", 0.0L, long double)
TEST_SPRINTF(LE_zrwth_hash_zero, "%#0LE", 0.0L, long double)

TEST_SPRINTF(LE_prec_mins_zero, "%-.5LE", 0.0L, long double)
TEST_SPRINTF(LE_prec_plus_zero, "%+.5LE", 0.0L, long double)
TEST_SPRINTF(LE_prec_spac_zero, "% .5LE", 0.0L, long double)
TEST_SPRINTF(LE_prec_hash_zero, "%#.5LE", 0.0L, long double)
TEST_SPRINTF(LE_prec_fzer_zero, "%0.5LE", 0.0L, long double)

TEST_SPRINTF(LE_zrpc_mins_zero, "%-.0LE", 0.0L, long double)
TEST_SPRINTF(LE_zrpc_plus_zero, "%+.0LE", 0.0L, long double)
TEST_SPRINTF(LE_zrpc_spac_zero, "% .0LE", 0.0L, long double)
TEST_SPRINTF(LE_zrpc_hash_zero, "%#.0LE", 0.0L, long double)
TEST_SPRINTF(LE_zrpc_fzer_zero, "%0.0LE", 0.0L, long double)

TEST_SPRINTF(LE_width_prec_mins_zero, "%-10.5LE", 0.0L, long double)
TEST_SPRINTF(LE_width_prec_plus_zero, "%+10.5LE", 0.0L, long double)
TEST_SPRINTF(LE_width_prec_spac_zero, "% 10.5LE", 0.0L, long double)
TEST_SPRINTF(LE_width_prec_hash_zero, "%#10.5LE", 0.0L, long double)
TEST_SPRINTF(LE_width_prec_fzer_zero, "%010.5LE", 0.0L, long double)

TEST_SPRINTF(LE_zrwth_zrpc_plus_zero, "%+0.0LE", 0.0L, long double)
TEST_SPRINTF(LE_zrwth_zrpc_spac_zero, "% 0.0LE", 0.0L, long double)
TEST_SPRINTF(LE_zrwth_zrpc_hash_zero, "%#0.0LE", 0.0L, long double)

TEST_SPRINTF_2(LE_dynamic_width_zero, "%*LE", 10, 0.0L, long double)
TEST_SPRINTF_2(LE_dynamic_prec_zero, "%.*LE", 5, 0.0L, long double)
TEST_SPRINTF_3(LE_dynamic_width_prec_zero, "%*.*LE", 10, 5, 0.0L, long double)

// =========================================================================

TEST_SPRINTF(Lf_mins_zero, "%-Lf", 0.0L, long double)
TEST_SPRINTF(Lf_plus_zero, "%+Lf", 0.0L, long double)
TEST_SPRINTF(Lf_spac_zero, "% Lf", 0.0L, long double)
TEST_SPRINTF(Lf_hash_zero, "%#Lf", 0.0L, long double)
TEST_SPRINTF(Lf_fzer_zero, "%0Lf", 0.0L, long double)

TEST_SPRINTF(Lf_width_zero, "%5Lf", 0.0L, long double)
TEST_SPRINTF(Lf_zrpc_zero, "%.0Lf", 0.0L, long double)
TEST_SPRINTF(Lf_prec_zero, "%.5Lf", 0.0L, long double)
TEST_SPRINTF(Lf_width_prec_zero, "%10.5Lf", 0.0L, long double)

TEST_SPRINTF(Lf_width_mins_zero, "%-5Lf", 0.0L, long double)
TEST_SPRINTF(Lf_width_plus_zero, "%+5Lf", 0.0L, long double)
TEST_SPRINTF(Lf_width_spac_zero, "% 5Lf", 0.0L, long double)
TEST_SPRINTF(Lf_width_hash_zero, "%#5Lf", 0.0L, long double)
TEST_SPRINTF(Lf_width_fzer_zero, "%05Lf", 0.0L, long double)

TEST_SPRINTF(Lf_zrwth_plus_zero, "%+0Lf", 0.0L, long double)
TEST_SPRINTF(Lf_zrwth_spac_zero, "% 0Lf", 0.0L, long double)
TEST_SPRINTF(Lf_zrwth_hash_zero, "%#0Lf", 0.0L, long double)

TEST_SPRINTF(Lf_prec_mins_zero, "%-.5Lf", 0.0L, long double)
TEST_SPRINTF(Lf_prec_plus_zero, "%+.5Lf", 0.0L, long double)
TEST_SPRINTF(Lf_prec_spac_zero, "% .5Lf", 0.0L, long double)
TEST_SPRINTF(Lf_prec_hash_zero, "%#.5Lf", 0.0L, long double)
TEST_SPRINTF(Lf_prec_fzer_zero, "%0.5Lf", 0.0L, long double)

TEST_SPRINTF(Lf_zrpc_mins_zero, "%-.0Lf", 0.0L, long double)
TEST_SPRINTF(Lf_zrpc_plus_zero, "%+.0Lf", 0.0L, long double)
TEST_SPRINTF(Lf_zrpc_spac_zero, "% .0Lf", 0.0L, long double)
TEST_SPRINTF(Lf_zrpc_hash_zero, "%#.0Lf", 0.0L, long double)
TEST_SPRINTF(Lf_zrpc_fzer_zero, "%0.0Lf", 0.0L, long double)

TEST_SPRINTF(Lf_width_prec_mins_zero, "%-10.5Lf", 0.0L, long double)
TEST_SPRINTF(Lf_width_prec_plus_zero, "%+10.5Lf", 0.0L, long double)
TEST_SPRINTF(Lf_width_prec_spac_zero, "% 10.5Lf", 0.0L, long double)
TEST_SPRINTF(Lf_width_prec_hash_zero, "%#10.5Lf", 0.0L, long double)
TEST_SPRINTF(Lf_width_prec_fzer_zero, "%010.5Lf", 0.0L, long double)

TEST_SPRINTF(Lf_zrwth_zrpc_plus_zero, "%+0.0Lf", 0.0L, long double)
TEST_SPRINTF(Lf_zrwth_zrpc_spac_zero, "% 0.0Lf", 0.0L, long double)
TEST_SPRINTF(Lf_zrwth_zrpc_hash_zero, "%#0.0Lf", 0.0L, long double)

TEST_SPRINTF_2(Lf_dynamic_width_zero, "%*Lf", 10, 0.0L, long double)
TEST_SPRINTF_2(Lf_dynamic_prec_zero, "%.*Lf", 5, 0.0L, long double)
TEST_SPRINTF_3(Lf_dynamic_width_prec_zero, "%*.*Lf", 10, 5, 0.0L, long double)

// =========================================================================

TEST_SPRINTF(Lg_mins_zero, "%-Lg", 0.0L, long double)
TEST_SPRINTF(Lg_plus_zero, "%+Lg", 0.0L, long double)
TEST_SPRINTF(Lg_spac_zero, "% Lg", 0.0L, long double)
TEST_SPRINTF(Lg_hash_zero, "%#Lg", 0.0L, long double)
TEST_SPRINTF(Lg_fzer_zero, "%0Lg", 0.0L, long double)

TEST_SPRINTF(Lg_width_zero, "%5Lg", 0.0L, long double)
TEST_SPRINTF(Lg_zrpc_zero, "%.0Lg", 0.0L, long double)
TEST_SPRINTF(Lg_prec_zero, "%.5Lg", 0.0L, long double)
TEST_SPRINTF(Lg_width_prec_zero, "%10.5Lg", 0.0L, long double)

TEST_SPRINTF(Lg_width_mins_zero, "%-5Lg", 0.0L, long double)
TEST_SPRINTF(Lg_width_plus_zero, "%+5Lg", 0.0L, long double)
TEST_SPRINTF(Lg_width_spac_zero, "% 5Lg", 0.0L, long double)
TEST_SPRINTF(Lg_width_hash_zero, "%#5Lg", 0.0L, long double)
TEST_SPRINTF(Lg_width_fzer_zero, "%05Lg", 0.0L, long double)

TEST_SPRINTF(Lg_zrwth_plus_zero, "%+0Lg", 0.0L, long double)
TEST_SPRINTF(Lg_zrwth_spac_zero, "% 0Lg", 0.0L, long double)
TEST_SPRINTF(Lg_zrwth_hash_zero, "%#0Lg", 0.0L, long double)

TEST_SPRINTF(Lg_prec_mins_zero, "%-.5Lg", 0.0L, long double)
TEST_SPRINTF(Lg_prec_plus_zero, "%+.5Lg", 0.0L, long double)
TEST_SPRINTF(Lg_prec_spac_zero, "% .5Lg", 0.0L, long double)
TEST_SPRINTF(Lg_prec_hash_zero, "%#.5Lg", 0.0L, long double)
TEST_SPRINTF(Lg_prec_fzer_zero, "%0.5Lg", 0.0L, long double)

TEST_SPRINTF(Lg_zrpc_mins_zero, "%-.0Lg", 0.0L, long double)
TEST_SPRINTF(Lg_zrpc_plus_zero, "%+.0Lg", 0.0L, long double)
TEST_SPRINTF(Lg_zrpc_spac_zero, "% .0Lg", 0.0L, long double)
TEST_SPRINTF(Lg_zrpc_hash_zero, "%#.0Lg", 0.0L, long double)
TEST_SPRINTF(Lg_zrpc_fzer_zero, "%0.0Lg", 0.0L, long double)

TEST_SPRINTF(Lg_width_prec_mins_zero, "%-10.5Lg", 0.0L, long double)
TEST_SPRINTF(Lg_width_prec_plus_zero, "%+10.5Lg", 0.0L, long double)
TEST_SPRINTF(Lg_width_prec_spac_zero, "% 10.5Lg", 0.0L, long double)
TEST_SPRINTF(Lg_width_prec_hash_zero, "%#10.5Lg", 0.0L, long double)
TEST_SPRINTF(Lg_width_prec_fzer_zero, "%010.5Lg", 0.0L, long double)

TEST_SPRINTF(Lg_zrwth_zrpc_plus_zero, "%+0.0Lg", 0.0L, long double)
TEST_SPRINTF(Lg_zrwth_zrpc_spac_zero, "% 0.0Lg", 0.0L, long double)
TEST_SPRINTF(Lg_zrwth_zrpc_hash_zero, "%#0.0Lg", 0.0L, long double)

TEST_SPRINTF_2(Lg_dynamic_width_zero, "%*Lg", 10, 0.0L, long double)
TEST_SPRINTF_2(Lg_dynamic_prec_zero, "%.*Lg", 5, 0.0L, long double)
TEST_SPRINTF_3(Lg_dynamic_width_prec_zero, "%*.*Lg", 10, 5, 0.0L, long double)

// =========================================================================

TEST_SPRINTF(LG_mins_zero, "%-LG", 0.0L, long double)
TEST_SPRINTF(LG_plus_zero, "%+LG", 0.0L, long double)
TEST_SPRINTF(LG_spac_zero, "% LG", 0.0L, long double)
TEST_SPRINTF(LG_hash_zero, "%#LG", 0.0L, long double)
TEST_SPRINTF(LG_fzer_zero, "%0LG", 0.0L, long double)

TEST_SPRINTF(LG_width_zero, "%5LG", 0.0L, long double)
TEST_SPRINTF(LG_zrpc_zero, "%.0LG", 0.0L, long double)
TEST_SPRINTF(LG_prec_zero, "%.5LG", 0.0L, long double)
TEST_SPRINTF(LG_width_prec_zero, "%10.5LG", 0.0L, long double)

TEST_SPRINTF(LG_width_mins_zero, "%-5LG", 0.0L, long double)
TEST_SPRINTF(LG_width_plus_zero, "%+5LG", 0.0L, long double)
TEST_SPRINTF(LG_width_spac_zero, "% 5LG", 0.0L, long double)
TEST_SPRINTF(LG_width_hash_zero, "%#5LG", 0.0L, long double)
TEST_SPRINTF(LG_width_fzer_zero, "%05LG", 0.0L, long double)

TEST_SPRINTF(LG_zrwth_plus_zero, "%+0LG", 0.0L, long double)
TEST_SPRINTF(LG_zrwth_spac_zero, "% 0LG", 0.0L, long double)
TEST_SPRINTF(LG_zrwth_hash_zero, "%#0LG", 0.0L, long double)

TEST_SPRINTF(LG_prec_mins_zero, "%-.5LG", 0.0L, long double)
TEST_SPRINTF(LG_prec_plus_zero, "%+.5LG", 0.0L, long double)
TEST_SPRINTF(LG_prec_spac_zero, "% .5LG", 0.0L, long double)
TEST_SPRINTF(LG_prec_hash_zero, "%#.5LG", 0.0L, long double)
TEST_SPRINTF(LG_prec_fzer_zero, "%0.5LG", 0.0L, long double)

TEST_SPRINTF(LG_zrpc_mins_zero, "%-.0LG", 0.0L, long double)
TEST_SPRINTF(LG_zrpc_plus_zero, "%+.0LG", 0.0L, long double)
TEST_SPRINTF(LG_zrpc_spac_zero, "% .0LG", 0.0L, long double)
TEST_SPRINTF(LG_zrpc_hash_zero, "%#.0LG", 0.0L, long double)
TEST_SPRINTF(LG_zrpc_fzer_zero, "%0.0LG", 0.0L, long double)

TEST_SPRINTF(LG_width_prec_mins_zero, "%-10.5LG", 0.0L, long double)
TEST_SPRINTF(LG_width_prec_plus_zero, "%+10.5LG", 0.0L, long double)
TEST_SPRINTF(LG_width_prec_spac_zero, "% 10.5LG", 0.0L, long double)
TEST_SPRINTF(LG_width_prec_hash_zero, "%#10.5LG", 0.0L, long double)
TEST_SPRINTF(LG_width_prec_fzer_zero, "%010.5LG", 0.0L, long double)

TEST_SPRINTF(LG_zrwth_zrpc_plus_zero, "%+0.0LG", 0.0L, long double)
TEST_SPRINTF(LG_zrwth_zrpc_spac_zero, "% 0.0LG", 0.0L, long double)
TEST_SPRINTF(LG_zrwth_zrpc_hash_zero, "%#0.0LG", 0.0L, long double)

TEST_SPRINTF_2(LG_dynamic_width_zero, "%*LG", 10, 0.0L, long double)
TEST_SPRINTF_2(LG_dynamic_prec_zero, "%.*LG", 5, 0.0L, long double)
TEST_SPRINTF_3(LG_dynamic_width_prec_zero, "%*.*LG", 10, 5, 0.0L, long double)
#pragma endregion

// =========================================================================
// Вещественные типы %f %e %E %g %G
// =========================================================================
#pragma region
TEST_SPRINTF(e_mins_post, "%-e", 123.456, double)
TEST_SPRINTF(e_plus_post, "%+e", 123.456, double)
TEST_SPRINTF(e_spac_post, "% e", 123.456, double)
TEST_SPRINTF(e_hash_post, "%#e", 123.456, double)
TEST_SPRINTF(e_fzer_post, "%0e", 123.456, double)
TEST_SPRINTF(e_mins_negt, "%-e", -123.456, double)
TEST_SPRINTF(e_plus_negt, "%+e", -123.456, double)
TEST_SPRINTF(e_spac_negt, "% e", -123.456, double)
TEST_SPRINTF(e_hash_negt, "%#e", -123.456, double)
TEST_SPRINTF(e_fzer_negt, "%0e", -123.456, double)
TEST_SPRINTF(e_mins_small, "%-e", -0.0000123456, double)
TEST_SPRINTF(e_plus_small, "%+e", -0.0000123456, double)
TEST_SPRINTF(e_spac_small, "% e", -0.0000123456, double)
TEST_SPRINTF(e_hash_small, "%#e", -0.0000123456, double)
TEST_SPRINTF(e_fzer_small, "%0e", -0.0000123456, double)
TEST_SPRINTF(e_mins_large, "%-e", 123456789.0, double)
TEST_SPRINTF(e_plus_large, "%+e", 123456789.0, double)
TEST_SPRINTF(e_spac_large, "% e", 123456789.0, double)
TEST_SPRINTF(e_hash_large, "%#e", 123456789.0, double)
TEST_SPRINTF(e_fzer_large, "%0e", 123456789.0, double)

TEST_SPRINTF(e_width_post, "%5e", 123.456, double)
TEST_SPRINTF(e_zrpc_post, "%.0e", 123.456, double)
TEST_SPRINTF(e_prec_post, "%.5e", 123.456, double)
TEST_SPRINTF(e_width_negt, "%5e", -123.456, double)
TEST_SPRINTF(e_zrpc_negt, "%.0e", -123.456, double)
TEST_SPRINTF(e_prec_negt, "%.5e", -123.456, double)
TEST_SPRINTF(e_width_small, "%5e", -0.0000123456, double)
TEST_SPRINTF(e_zrpc_small, "%.0e", -0.0000123456, double)
TEST_SPRINTF(e_prec_small, "%.5e", -0.0000123456, double)
TEST_SPRINTF(e_width_large, "%5e", 123456789.0, double)
TEST_SPRINTF(e_zrpc_large, "%.0e", 123456789.0, double)
TEST_SPRINTF(e_prec_large, "%.5e", 123456789.0, double)

TEST_SPRINTF(e_width_prec_post, "%10.5e", 123.456, double)
TEST_SPRINTF(e_width_prec_negt, "%10.5e", -123.456, double)
TEST_SPRINTF(e_width_prec_small, "%10.5e", -0.0000123456, double)
TEST_SPRINTF(e_width_prec_large, "%10.5e", 123456789.0, double)

TEST_SPRINTF(e_width_mins_post, "%-5e", 123.456, double)
TEST_SPRINTF(e_width_plus_post, "%+5e", 123.456, double)
TEST_SPRINTF(e_width_spac_post, "% 5e", 123.456, double)
TEST_SPRINTF(e_width_hash_post, "%#5e", 123.456, double)
TEST_SPRINTF(e_width_fzer_post, "%05e", 123.456, double)
TEST_SPRINTF(e_width_mins_negt, "%-5e", -123.456, double)
TEST_SPRINTF(e_width_plus_negt, "%+5e", -123.456, double)
TEST_SPRINTF(e_width_spac_negt, "% 5e", -123.456, double)
TEST_SPRINTF(e_width_hash_negt, "%#5e", -123.456, double)
TEST_SPRINTF(e_width_fzer_negt, "%05e", -123.456, double)
TEST_SPRINTF(e_width_mins_small, "%-5e", -0.0000123456, double)
TEST_SPRINTF(e_width_plus_small, "%+5e", -0.0000123456, double)
TEST_SPRINTF(e_width_spac_small, "% 5e", -0.0000123456, double)
TEST_SPRINTF(e_width_hash_small, "%#5e", -0.0000123456, double)
TEST_SPRINTF(e_width_fzer_small, "%05e", -0.0000123456, double)
TEST_SPRINTF(e_width_mins_large, "%-5e", 123456789.0, double)
TEST_SPRINTF(e_width_plus_large, "%+5e", 123456789.0, double)
TEST_SPRINTF(e_width_spac_large, "% 5e", 123456789.0, double)
TEST_SPRINTF(e_width_hash_large, "%#5e", 123456789.0, double)
TEST_SPRINTF(e_width_fzer_large, "%05e", 123456789.0, double)

TEST_SPRINTF(e_zrwth_plus_post, "%+0e", 123.456, double)
TEST_SPRINTF(e_zrwth_spac_post, "% 0e", 123.456, double)
TEST_SPRINTF(e_zrwth_hash_post, "%#0e", 123.456, double)
TEST_SPRINTF(e_zrwth_plus_negt, "%+0e", -123.456, double)
TEST_SPRINTF(e_zrwth_spac_negt, "% 0e", -123.456, double)
TEST_SPRINTF(e_zrwth_hash_negt, "%#0e", -123.456, double)
TEST_SPRINTF(e_zrwth_plus_small, "%+0e", -0.0000123456, double)
TEST_SPRINTF(e_zrwth_spac_small, "% 0e", -0.0000123456, double)
TEST_SPRINTF(e_zrwth_hash_small, "%#0e", -0.0000123456, double)
TEST_SPRINTF(e_zrwth_plus_large, "%+0e", 123456789.0, double)
TEST_SPRINTF(e_zrwth_spac_large, "% 0e", 123456789.0, double)
TEST_SPRINTF(e_zrwth_hash_large, "%#0e", 123456789.0, double)

TEST_SPRINTF(e_prec_mins_post, "%-.5e", 123.456, double)
TEST_SPRINTF(e_prec_plus_post, "%+.5e", 123.456, double)
TEST_SPRINTF(e_prec_spac_post, "% .5e", 123.456, double)
TEST_SPRINTF(e_prec_hash_post, "%#.5e", 123.456, double)
TEST_SPRINTF(e_prec_fzer_post, "%0.5e", 123.456, double)
TEST_SPRINTF(e_prec_mins_negt, "%-.5e", -123.456, double)
TEST_SPRINTF(e_prec_plus_negt, "%+.5e", -123.456, double)
TEST_SPRINTF(e_prec_spac_negt, "% .5e", -123.456, double)
TEST_SPRINTF(e_prec_hash_negt, "%#.5e", -123.456, double)
TEST_SPRINTF(e_prec_fzer_negt, "%0.5e", -123.456, double)
TEST_SPRINTF(e_prec_mins_small, "%-.5e", -0.0000123456, double)
TEST_SPRINTF(e_prec_plus_small, "%+.5e", -0.0000123456, double)
TEST_SPRINTF(e_prec_spac_small, "% .5e", -0.0000123456, double)
TEST_SPRINTF(e_prec_hash_small, "%#.5e", -0.0000123456, double)
TEST_SPRINTF(e_prec_fzer_small, "%0.5e", -0.0000123456, double)
TEST_SPRINTF(e_prec_mins_large, "%-.5e", 123456789.0, double)
TEST_SPRINTF(e_prec_plus_large, "%+.5e", 123456789.0, double)
TEST_SPRINTF(e_prec_spac_large, "% .5e", 123456789.0, double)
TEST_SPRINTF(e_prec_hash_large, "%#.5e", 123456789.0, double)
TEST_SPRINTF(e_prec_fzer_large, "%0.5e", 123456789.0, double)

TEST_SPRINTF(e_zrpc_mins_post, "%-.0e", 123.456, double)
TEST_SPRINTF(e_zrpc_plus_post, "%+.0e", 123.456, double)
TEST_SPRINTF(e_zrpc_spac_post, "% .0e", 123.456, double)
TEST_SPRINTF(e_zrpc_hash_post, "%#.0e", 123.456, double)
TEST_SPRINTF(e_zrpc_fzer_post, "%0.0e", 123.456, double)
TEST_SPRINTF(e_zrpc_mins_negt, "%-.0e", -123.456, double)
TEST_SPRINTF(e_zrpc_plus_negt, "%+.0e", -123.456, double)
TEST_SPRINTF(e_zrpc_spac_negt, "% .0e", -123.456, double)
TEST_SPRINTF(e_zrpc_hash_negt, "%#.0e", -123.456, double)
TEST_SPRINTF(e_zrpc_fzer_negt, "%0.0e", -123.456, double)
TEST_SPRINTF(e_zrpc_mins_small, "%-.0e", -0.0000123456, double)
TEST_SPRINTF(e_zrpc_plus_small, "%+.0e", -0.0000123456, double)
TEST_SPRINTF(e_zrpc_spac_small, "% .0e", -0.0000123456, double)
TEST_SPRINTF(e_zrpc_hash_small, "%#.0e", -0.0000123456, double)
TEST_SPRINTF(e_zrpc_fzer_small, "%0.0e", -0.0000123456, double)
TEST_SPRINTF(e_zrpc_mins_large, "%-.0e", 123456789.0, double)
TEST_SPRINTF(e_zrpc_plus_large, "%+.0e", 123456789.0, double)
TEST_SPRINTF(e_zrpc_spac_large, "% .0e", 123456789.0, double)
TEST_SPRINTF(e_zrpc_hash_large, "%#.0e", 123456789.0, double)
TEST_SPRINTF(e_zrpc_fzer_large, "%0.0e", 123456789.0, double)

TEST_SPRINTF(e_width_prec_mins_post, "%-10.5e", 123.456, double)
TEST_SPRINTF(e_width_prec_plus_post, "%+10.5e", 123.456, double)
TEST_SPRINTF(e_width_prec_spac_post, "% 10.5e", 123.456, double)
TEST_SPRINTF(e_width_prec_hash_post, "%#10.5e", 123.456, double)
TEST_SPRINTF(e_width_prec_fzer_post, "%010.5e", 123.456, double)
TEST_SPRINTF(e_width_prec_mins_negt, "%-10.5e", -123.456, double)
TEST_SPRINTF(e_width_prec_plus_negt, "%+10.5e", -123.456, double)
TEST_SPRINTF(e_width_prec_spac_negt, "% 10.5e", -123.456, double)
TEST_SPRINTF(e_width_prec_hash_negt, "%#10.5e", -123.456, double)
TEST_SPRINTF(e_width_prec_fzer_negt, "%010.5e", -123.456, double)
TEST_SPRINTF(e_width_prec_mins_small, "%-10.5e", -0.0000123456, double)
TEST_SPRINTF(e_width_prec_plus_small, "%+10.5e", -0.0000123456, double)
TEST_SPRINTF(e_width_prec_spac_small, "% 10.5e", -0.0000123456, double)
TEST_SPRINTF(e_width_prec_hash_small, "%#10.5e", -0.0000123456, double)
TEST_SPRINTF(e_width_prec_fzer_small, "%010.5e", -0.0000123456, double)
TEST_SPRINTF(e_width_prec_mins_large, "%-10.5e", 123456789.0, double)
TEST_SPRINTF(e_width_prec_plus_large, "%+10.5e", 123456789.0, double)
TEST_SPRINTF(e_width_prec_spac_large, "% 10.5e", 123456789.0, double)
TEST_SPRINTF(e_width_prec_hash_large, "%#10.5e", 123456789.0, double)
TEST_SPRINTF(e_width_prec_fzer_large, "%010.5e", 123456789.0, double)

TEST_SPRINTF(e_zrwth_zrpc_plus_post, "%+0.0e", 123.456, double)
TEST_SPRINTF(e_zrwth_zrpc_spac_post, "% 0.0e", 123.456, double)
TEST_SPRINTF(e_zrwth_zrpc_hash_post, "%#0.0e", 123.456, double)
TEST_SPRINTF(e_zrwth_zrpc_plus_negt, "%+0.0e", -123.456, double)
TEST_SPRINTF(e_zrwth_zrpc_spac_negt, "% 0.0e", -123.456, double)
TEST_SPRINTF(e_zrwth_zrpc_hash_negt, "%#0.0e", -123.456, double)
TEST_SPRINTF(e_zrwth_zrpc_plus_small, "%+0.0e", -0.0000123456, double)
TEST_SPRINTF(e_zrwth_zrpc_spac_small, "% 0.0e", -0.0000123456, double)
TEST_SPRINTF(e_zrwth_zrpc_hash_small, "%#0.0e", -0.0000123456, double)
TEST_SPRINTF(e_zrwth_zrpc_plus_large, "%+0.0e", 123456789.0, double)
TEST_SPRINTF(e_zrwth_zrpc_spac_large, "% 0.0e", 123456789.0, double)
TEST_SPRINTF(e_zrwth_zrpc_hash_large, "%#0.0e", 123456789.0, double)

TEST_SPRINTF_2(e_dynamic_width_post, "%*e", 10, 123.456, double)
TEST_SPRINTF_2(e_dynamic_width_negt, "%*e", 10, -123.456, double)
TEST_SPRINTF_2(e_dynamic_width_small, "%*e", 10, -0.0000123456, double)
TEST_SPRINTF_2(e_dynamic_width_large, "%*e", 10, 123456789.0, double)

TEST_SPRINTF_2(e_dynamic_prec_post, "%.*e", 5, 123.456, double)
TEST_SPRINTF_2(e_dynamic_prec_negt, "%.*e", 5, -123.456, double)
TEST_SPRINTF_2(e_dynamic_prec_small, "%.*e", 5, -0.0000123456, double)
TEST_SPRINTF_2(e_dynamic_prec_large, "%.*e", 5, 123456789.0, double)

TEST_SPRINTF_3(e_dynamic_width_prec_post, "%*.*e", 10, 5, 123.456, double)
TEST_SPRINTF_3(e_dynamic_width_prec_negt, "%*.*e", 10, 5, -123.456, double)
TEST_SPRINTF_3(e_dynamic_width_prec_small, "%*.*e", 10, 5, -0.0000123456,
               double)
TEST_SPRINTF_3(e_dynamic_width_prec_large, "%*.*e", 10, 5, 123456789.0, double)

// =========================================================================

TEST_SPRINTF(E_mins_post, "%-E", 123.456, double)
TEST_SPRINTF(E_plus_post, "%+E", 123.456, double)
TEST_SPRINTF(E_spac_post, "% E", 123.456, double)
TEST_SPRINTF(E_hash_post, "%#E", 123.456, double)
TEST_SPRINTF(E_fzer_post, "%0E", 123.456, double)
TEST_SPRINTF(E_mins_negt, "%-E", -123.456, double)
TEST_SPRINTF(E_plus_negt, "%+E", -123.456, double)
TEST_SPRINTF(E_spac_negt, "% E", -123.456, double)
TEST_SPRINTF(E_hash_negt, "%#E", -123.456, double)
TEST_SPRINTF(E_fzer_negt, "%0E", -123.456, double)
TEST_SPRINTF(E_mins_small, "%-E", -0.0000123456, double)
TEST_SPRINTF(E_plus_small, "%+E", -0.0000123456, double)
TEST_SPRINTF(E_spac_small, "% E", -0.0000123456, double)
TEST_SPRINTF(E_hash_small, "%#E", -0.0000123456, double)
TEST_SPRINTF(E_fzer_small, "%0E", -0.0000123456, double)
TEST_SPRINTF(E_mins_large, "%-E", 123456789.0, double)
TEST_SPRINTF(E_plus_large, "%+E", 123456789.0, double)
TEST_SPRINTF(E_spac_large, "% E", 123456789.0, double)
TEST_SPRINTF(E_hash_large, "%#E", 123456789.0, double)
TEST_SPRINTF(E_fzer_large, "%0E", 123456789.0, double)

TEST_SPRINTF(E_width_post, "%5E", 123.456, double)
TEST_SPRINTF(E_zrpc_post, "%.0E", 123.456, double)
TEST_SPRINTF(E_prec_post, "%.5E", 123.456, double)
TEST_SPRINTF(E_width_negt, "%5E", -123.456, double)
TEST_SPRINTF(E_zrpc_negt, "%.0E", -123.456, double)
TEST_SPRINTF(E_prec_negt, "%.5E", -123.456, double)
TEST_SPRINTF(E_width_small, "%5E", -0.0000123456, double)
TEST_SPRINTF(E_zrpc_small, "%.0E", -0.0000123456, double)
TEST_SPRINTF(E_prec_small, "%.5E", -0.0000123456, double)
TEST_SPRINTF(E_width_large, "%5E", 123456789.0, double)
TEST_SPRINTF(E_zrpc_large, "%.0E", 123456789.0, double)
TEST_SPRINTF(E_prec_large, "%.5E", 123456789.0, double)

TEST_SPRINTF(E_width_prec_post, "%10.5E", 123.456, double)
TEST_SPRINTF(E_width_prec_negt, "%10.5E", -123.456, double)
TEST_SPRINTF(E_width_prec_small, "%10.5E", -0.0000123456, double)
TEST_SPRINTF(E_width_prec_large, "%10.5E", 123456789.0, double)

TEST_SPRINTF(E_width_mins_post, "%-5E", 123.456, double)
TEST_SPRINTF(E_width_plus_post, "%+5E", 123.456, double)
TEST_SPRINTF(E_width_spac_post, "% 5E", 123.456, double)
TEST_SPRINTF(E_width_hash_post, "%#5E", 123.456, double)
TEST_SPRINTF(E_width_fzer_post, "%05E", 123.456, double)
TEST_SPRINTF(E_width_mins_negt, "%-5E", -123.456, double)
TEST_SPRINTF(E_width_plus_negt, "%+5E", -123.456, double)
TEST_SPRINTF(E_width_spac_negt, "% 5E", -123.456, double)
TEST_SPRINTF(E_width_hash_negt, "%#5E", -123.456, double)
TEST_SPRINTF(E_width_fzer_negt, "%05E", -123.456, double)
TEST_SPRINTF(E_width_mins_small, "%-5E", -0.0000123456, double)
TEST_SPRINTF(E_width_plus_small, "%+5E", -0.0000123456, double)
TEST_SPRINTF(E_width_spac_small, "% 5E", -0.0000123456, double)
TEST_SPRINTF(E_width_hash_small, "%#5E", -0.0000123456, double)
TEST_SPRINTF(E_width_fzer_small, "%05E", -0.0000123456, double)
TEST_SPRINTF(E_width_mins_large, "%-5E", 123456789.0, double)
TEST_SPRINTF(E_width_plus_large, "%+5E", 123456789.0, double)
TEST_SPRINTF(E_width_spac_large, "% 5E", 123456789.0, double)
TEST_SPRINTF(E_width_hash_large, "%#5E", 123456789.0, double)
TEST_SPRINTF(E_width_fzer_large, "%05E", 123456789.0, double)

TEST_SPRINTF(E_zrwth_plus_post, "%+0E", 123.456, double)
TEST_SPRINTF(E_zrwth_spac_post, "% 0E", 123.456, double)
TEST_SPRINTF(E_zrwth_hash_post, "%#0E", 123.456, double)
TEST_SPRINTF(E_zrwth_plus_negt, "%+0E", -123.456, double)
TEST_SPRINTF(E_zrwth_spac_negt, "% 0E", -123.456, double)
TEST_SPRINTF(E_zrwth_hash_negt, "%#0E", -123.456, double)
TEST_SPRINTF(E_zrwth_plus_small, "%+0E", -0.0000123456, double)
TEST_SPRINTF(E_zrwth_spac_small, "% 0E", -0.0000123456, double)
TEST_SPRINTF(E_zrwth_hash_small, "%#0E", -0.0000123456, double)
TEST_SPRINTF(E_zrwth_plus_large, "%+0E", 123456789.0, double)
TEST_SPRINTF(E_zrwth_spac_large, "% 0E", 123456789.0, double)
TEST_SPRINTF(E_zrwth_hash_large, "%#0E", 123456789.0, double)

TEST_SPRINTF(E_prec_mins_post, "%-.5E", 123.456, double)
TEST_SPRINTF(E_prec_plus_post, "%+.5E", 123.456, double)
TEST_SPRINTF(E_prec_spac_post, "% .5E", 123.456, double)
TEST_SPRINTF(E_prec_hash_post, "%#.5E", 123.456, double)
TEST_SPRINTF(E_prec_fzer_post, "%0.5E", 123.456, double)
TEST_SPRINTF(E_prec_mins_negt, "%-.5E", -123.456, double)
TEST_SPRINTF(E_prec_plus_negt, "%+.5E", -123.456, double)
TEST_SPRINTF(E_prec_spac_negt, "% .5E", -123.456, double)
TEST_SPRINTF(E_prec_hash_negt, "%#.5E", -123.456, double)
TEST_SPRINTF(E_prec_fzer_negt, "%0.5E", -123.456, double)
TEST_SPRINTF(E_prec_mins_small, "%-.5E", -0.0000123456, double)
TEST_SPRINTF(E_prec_plus_small, "%+.5E", -0.0000123456, double)
TEST_SPRINTF(E_prec_spac_small, "% .5E", -0.0000123456, double)
TEST_SPRINTF(E_prec_hash_small, "%#.5E", -0.0000123456, double)
TEST_SPRINTF(E_prec_fzer_small, "%0.5E", -0.0000123456, double)
TEST_SPRINTF(E_prec_mins_large, "%-.5E", 123456789.0, double)
TEST_SPRINTF(E_prec_plus_large, "%+.5E", 123456789.0, double)
TEST_SPRINTF(E_prec_spac_large, "% .5E", 123456789.0, double)
TEST_SPRINTF(E_prec_hash_large, "%#.5E", 123456789.0, double)
TEST_SPRINTF(E_prec_fzer_large, "%0.5E", 123456789.0, double)

TEST_SPRINTF(E_zrpc_mins_post, "%-.0E", 123.456, double)
TEST_SPRINTF(E_zrpc_plus_post, "%+.0E", 123.456, double)
TEST_SPRINTF(E_zrpc_spac_post, "% .0E", 123.456, double)
TEST_SPRINTF(E_zrpc_hash_post, "%#.0E", 123.456, double)
TEST_SPRINTF(E_zrpc_fzer_post, "%0.0E", 123.456, double)
TEST_SPRINTF(E_zrpc_mins_negt, "%-.0E", -123.456, double)
TEST_SPRINTF(E_zrpc_plus_negt, "%+.0E", -123.456, double)
TEST_SPRINTF(E_zrpc_spac_negt, "% .0E", -123.456, double)
TEST_SPRINTF(E_zrpc_hash_negt, "%#.0E", -123.456, double)
TEST_SPRINTF(E_zrpc_fzer_negt, "%0.0E", -123.456, double)
TEST_SPRINTF(E_zrpc_mins_small, "%-.0E", -0.0000123456, double)
TEST_SPRINTF(E_zrpc_plus_small, "%+.0E", -0.0000123456, double)
TEST_SPRINTF(E_zrpc_spac_small, "% .0E", -0.0000123456, double)
TEST_SPRINTF(E_zrpc_hash_small, "%#.0E", -0.0000123456, double)
TEST_SPRINTF(E_zrpc_fzer_small, "%0.0E", -0.0000123456, double)
TEST_SPRINTF(E_zrpc_mins_large, "%-.0E", 123456789.0, double)
TEST_SPRINTF(E_zrpc_plus_large, "%+.0E", 123456789.0, double)
TEST_SPRINTF(E_zrpc_spac_large, "% .0E", 123456789.0, double)
TEST_SPRINTF(E_zrpc_hash_large, "%#.0E", 123456789.0, double)
TEST_SPRINTF(E_zrpc_fzer_large, "%0.0E", 123456789.0, double)

TEST_SPRINTF(E_width_prec_mins_post, "%-10.5E", 123.456, double)
TEST_SPRINTF(E_width_prec_plus_post, "%+10.5E", 123.456, double)
TEST_SPRINTF(E_width_prec_spac_post, "% 10.5E", 123.456, double)
TEST_SPRINTF(E_width_prec_hash_post, "%#10.5E", 123.456, double)
TEST_SPRINTF(E_width_prec_fzer_post, "%010.5E", 123.456, double)
TEST_SPRINTF(E_width_prec_mins_negt, "%-10.5E", -123.456, double)
TEST_SPRINTF(E_width_prec_plus_negt, "%+10.5E", -123.456, double)
TEST_SPRINTF(E_width_prec_spac_negt, "% 10.5E", -123.456, double)
TEST_SPRINTF(E_width_prec_hash_negt, "%#10.5E", -123.456, double)
TEST_SPRINTF(E_width_prec_fzer_negt, "%010.5E", -123.456, double)
TEST_SPRINTF(E_width_prec_mins_small, "%-10.5E", -0.0000123456, double)
TEST_SPRINTF(E_width_prec_plus_small, "%+10.5E", -0.0000123456, double)
TEST_SPRINTF(E_width_prec_spac_small, "% 10.5E", -0.0000123456, double)
TEST_SPRINTF(E_width_prec_hash_small, "%#10.5E", -0.0000123456, double)
TEST_SPRINTF(E_width_prec_fzer_small, "%010.5E", -0.0000123456, double)
TEST_SPRINTF(E_width_prec_mins_large, "%-10.5E", 123456789.0, double)
TEST_SPRINTF(E_width_prec_plus_large, "%+10.5E", 123456789.0, double)
TEST_SPRINTF(E_width_prec_spac_large, "% 10.5E", 123456789.0, double)
TEST_SPRINTF(E_width_prec_hash_large, "%#10.5E", 123456789.0, double)
TEST_SPRINTF(E_width_prec_fzer_large, "%010.5E", 123456789.0, double)

TEST_SPRINTF(E_zrwth_zrpc_plus_post, "%+0.0E", 123.456, double)
TEST_SPRINTF(E_zrwth_zrpc_spac_post, "% 0.0E", 123.456, double)
TEST_SPRINTF(E_zrwth_zrpc_hash_post, "%#0.0E", 123.456, double)
TEST_SPRINTF(E_zrwth_zrpc_plus_negt, "%+0.0E", -123.456, double)
TEST_SPRINTF(E_zrwth_zrpc_spac_negt, "% 0.0E", -123.456, double)
TEST_SPRINTF(E_zrwth_zrpc_hash_negt, "%#0.0E", -123.456, double)
TEST_SPRINTF(E_zrwth_zrpc_plus_small, "%+0.0E", -0.0000123456, double)
TEST_SPRINTF(E_zrwth_zrpc_spac_small, "% 0.0E", -0.0000123456, double)
TEST_SPRINTF(E_zrwth_zrpc_hash_small, "%#0.0E", -0.0000123456, double)
TEST_SPRINTF(E_zrwth_zrpc_plus_large, "%+0.0E", 123456789.0, double)
TEST_SPRINTF(E_zrwth_zrpc_spac_large, "% 0.0E", 123456789.0, double)
TEST_SPRINTF(E_zrwth_zrpc_hash_large, "%#0.0E", 123456789.0, double)

TEST_SPRINTF_2(E_dynamic_width_post, "%*E", 10, 123.456, double)
TEST_SPRINTF_2(E_dynamic_width_negt, "%*E", 10, -123.456, double)
TEST_SPRINTF_2(E_dynamic_width_small, "%*E", 10, -0.0000123456, double)
TEST_SPRINTF_2(E_dynamic_width_large, "%*E", 10, 123456789.0, double)

TEST_SPRINTF_2(E_dynamic_prec_post, "%.*E", 5, 123.456, double)
TEST_SPRINTF_2(E_dynamic_prec_negt, "%.*E", 5, -123.456, double)
TEST_SPRINTF_2(E_dynamic_prec_small, "%.*E", 5, -0.0000123456, double)
TEST_SPRINTF_2(E_dynamic_prec_large, "%.*E", 5, 123456789.0, double)

TEST_SPRINTF_3(E_dynamic_width_prec_post, "%*.*E", 10, 5, 123.456, double)
TEST_SPRINTF_3(E_dynamic_width_prec_negt, "%*.*E", 10, 5, -123.456, double)
TEST_SPRINTF_3(E_dynamic_width_prec_small, "%*.*E", 10, 5, -0.0000123456,
               double)
TEST_SPRINTF_3(E_dynamic_width_prec_large, "%*.*E", 10, 5, 123456789.0, double)

// =========================================================================

TEST_SPRINTF(f_mins_post, "%-f", 123.456, double)
TEST_SPRINTF(f_plus_post, "%+f", 123.456, double)
TEST_SPRINTF(f_spac_post, "% f", 123.456, double)
TEST_SPRINTF(f_hash_post, "%#f", 123.456, double)
TEST_SPRINTF(f_fzer_post, "%0f", 123.456, double)
TEST_SPRINTF(f_mins_negt, "%-f", -123.456, double)
TEST_SPRINTF(f_plus_negt, "%+f", -123.456, double)
TEST_SPRINTF(f_spac_negt, "% f", -123.456, double)
TEST_SPRINTF(f_hash_negt, "%#f", -123.456, double)
TEST_SPRINTF(f_fzer_negt, "%0f", -123.456, double)
TEST_SPRINTF(f_mins_small, "%-f", -0.0000123456, double)
TEST_SPRINTF(f_plus_small, "%+f", -0.0000123456, double)
TEST_SPRINTF(f_spac_small, "% f", -0.0000123456, double)
TEST_SPRINTF(f_hash_small, "%#f", -0.0000123456, double)
TEST_SPRINTF(f_fzer_small, "%0f", -0.0000123456, double)
TEST_SPRINTF(f_mins_large, "%-f", 123456789.0, double)
TEST_SPRINTF(f_plus_large, "%+f", 123456789.0, double)
TEST_SPRINTF(f_spac_large, "% f", 123456789.0, double)
TEST_SPRINTF(f_hash_large, "%#f", 123456789.0, double)
TEST_SPRINTF(f_fzer_large, "%0f", 123456789.0, double)

TEST_SPRINTF(f_width_post, "%5f", 123.456, double)
TEST_SPRINTF(f_zrpc_post, "%.0f", 123.456, double)
TEST_SPRINTF(f_prec_post, "%.5f", 123.456, double)
TEST_SPRINTF(f_width_negt, "%5f", -123.456, double)
TEST_SPRINTF(f_zrpc_negt, "%.0f", -123.456, double)
TEST_SPRINTF(f_prec_negt, "%.5f", -123.456, double)
TEST_SPRINTF(f_width_small, "%5f", -0.0000123456, double)
TEST_SPRINTF(f_zrpc_small, "%.0f", -0.0000123456, double)
TEST_SPRINTF(f_prec_small, "%.5f", -0.0000123456, double)
TEST_SPRINTF(f_width_large, "%5f", 123456789.0, double)
TEST_SPRINTF(f_zrpc_large, "%.0f", 123456789.0, double)
TEST_SPRINTF(f_prec_large, "%.5f", 123456789.0, double)

TEST_SPRINTF(f_width_prec_post, "%10.5f", 123.456, double)
TEST_SPRINTF(f_width_prec_negt, "%10.5f", -123.456, double)
TEST_SPRINTF(f_width_prec_small, "%10.5f", -0.0000123456, double)
TEST_SPRINTF(f_width_prec_large, "%10.5f", 123456789.0, double)

TEST_SPRINTF(f_width_mins_post, "%-5f", 123.456, double)
TEST_SPRINTF(f_width_plus_post, "%+5f", 123.456, double)
TEST_SPRINTF(f_width_spac_post, "% 5f", 123.456, double)
TEST_SPRINTF(f_width_hash_post, "%#5f", 123.456, double)
TEST_SPRINTF(f_width_fzer_post, "%05f", 123.456, double)
TEST_SPRINTF(f_width_mins_negt, "%-5f", -123.456, double)
TEST_SPRINTF(f_width_plus_negt, "%+5f", -123.456, double)
TEST_SPRINTF(f_width_spac_negt, "% 5f", -123.456, double)
TEST_SPRINTF(f_width_hash_negt, "%#5f", -123.456, double)
TEST_SPRINTF(f_width_fzer_negt, "%05f", -123.456, double)
TEST_SPRINTF(f_width_mins_small, "%-5f", -0.0000123456, double)
TEST_SPRINTF(f_width_plus_small, "%+5f", -0.0000123456, double)
TEST_SPRINTF(f_width_spac_small, "% 5f", -0.0000123456, double)
TEST_SPRINTF(f_width_hash_small, "%#5f", -0.0000123456, double)
TEST_SPRINTF(f_width_fzer_small, "%05f", -0.0000123456, double)
TEST_SPRINTF(f_width_mins_large, "%-5f", 123456789.0, double)
TEST_SPRINTF(f_width_plus_large, "%+5f", 123456789.0, double)
TEST_SPRINTF(f_width_spac_large, "% 5f", 123456789.0, double)
TEST_SPRINTF(f_width_hash_large, "%#5f", 123456789.0, double)
TEST_SPRINTF(f_width_fzer_large, "%05f", 123456789.0, double)

TEST_SPRINTF(f_zrwth_plus_post, "%+0f", 123.456, double)
TEST_SPRINTF(f_zrwth_spac_post, "% 0f", 123.456, double)
TEST_SPRINTF(f_zrwth_hash_post, "%#0f", 123.456, double)
TEST_SPRINTF(f_zrwth_plus_negt, "%+0f", -123.456, double)
TEST_SPRINTF(f_zrwth_spac_negt, "% 0f", -123.456, double)
TEST_SPRINTF(f_zrwth_hash_negt, "%#0f", -123.456, double)
TEST_SPRINTF(f_zrwth_plus_small, "%+0f", -0.0000123456, double)
TEST_SPRINTF(f_zrwth_spac_small, "% 0f", -0.0000123456, double)
TEST_SPRINTF(f_zrwth_hash_small, "%#0f", -0.0000123456, double)
TEST_SPRINTF(f_zrwth_plus_large, "%+0f", 123456789.0, double)
TEST_SPRINTF(f_zrwth_spac_large, "% 0f", 123456789.0, double)
TEST_SPRINTF(f_zrwth_hash_large, "%#0f", 123456789.0, double)

TEST_SPRINTF(f_prec_mins_post, "%-.5f", 123.456, double)
TEST_SPRINTF(f_prec_plus_post, "%+.5f", 123.456, double)
TEST_SPRINTF(f_prec_spac_post, "% .5f", 123.456, double)
TEST_SPRINTF(f_prec_hash_post, "%#.5f", 123.456, double)
TEST_SPRINTF(f_prec_fzer_post, "%0.5f", 123.456, double)
TEST_SPRINTF(f_prec_mins_negt, "%-.5f", -123.456, double)
TEST_SPRINTF(f_prec_plus_negt, "%+.5f", -123.456, double)
TEST_SPRINTF(f_prec_spac_negt, "% .5f", -123.456, double)
TEST_SPRINTF(f_prec_hash_negt, "%#.5f", -123.456, double)
TEST_SPRINTF(f_prec_fzer_negt, "%0.5f", -123.456, double)
TEST_SPRINTF(f_prec_mins_small, "%-.5f", -0.0000123456, double)
TEST_SPRINTF(f_prec_plus_small, "%+.5f", -0.0000123456, double)
TEST_SPRINTF(f_prec_spac_small, "% .5f", -0.0000123456, double)
TEST_SPRINTF(f_prec_hash_small, "%#.5f", -0.0000123456, double)
TEST_SPRINTF(f_prec_fzer_small, "%0.5f", -0.0000123456, double)
TEST_SPRINTF(f_prec_mins_large, "%-.5f", 123456789.0, double)
TEST_SPRINTF(f_prec_plus_large, "%+.5f", 123456789.0, double)
TEST_SPRINTF(f_prec_spac_large, "% .5f", 123456789.0, double)
TEST_SPRINTF(f_prec_hash_large, "%#.5f", 123456789.0, double)
TEST_SPRINTF(f_prec_fzer_large, "%0.5f", 123456789.0, double)

TEST_SPRINTF(f_zrpc_mins_post, "%-.0f", 123.456, double)
TEST_SPRINTF(f_zrpc_plus_post, "%+.0f", 123.456, double)
TEST_SPRINTF(f_zrpc_spac_post, "% .0f", 123.456, double)
TEST_SPRINTF(f_zrpc_hash_post, "%#.0f", 123.456, double)
TEST_SPRINTF(f_zrpc_fzer_post, "%0.0f", 123.456, double)
TEST_SPRINTF(f_zrpc_mins_negt, "%-.0f", -123.456, double)
TEST_SPRINTF(f_zrpc_plus_negt, "%+.0f", -123.456, double)
TEST_SPRINTF(f_zrpc_spac_negt, "% .0f", -123.456, double)
TEST_SPRINTF(f_zrpc_hash_negt, "%#.0f", -123.456, double)
TEST_SPRINTF(f_zrpc_fzer_negt, "%0.0f", -123.456, double)
TEST_SPRINTF(f_zrpc_mins_small, "%-.0f", -0.0000123456, double)
TEST_SPRINTF(f_zrpc_plus_small, "%+.0f", -0.0000123456, double)
TEST_SPRINTF(f_zrpc_spac_small, "% .0f", -0.0000123456, double)
TEST_SPRINTF(f_zrpc_hash_small, "%#.0f", -0.0000123456, double)
TEST_SPRINTF(f_zrpc_fzer_small, "%0.0f", -0.0000123456, double)
TEST_SPRINTF(f_zrpc_mins_large, "%-.0f", 123456789.0, double)
TEST_SPRINTF(f_zrpc_plus_large, "%+.0f", 123456789.0, double)
TEST_SPRINTF(f_zrpc_spac_large, "% .0f", 123456789.0, double)
TEST_SPRINTF(f_zrpc_hash_large, "%#.0f", 123456789.0, double)
TEST_SPRINTF(f_zrpc_fzer_large, "%0.0f", 123456789.0, double)

TEST_SPRINTF(f_width_prec_mins_post, "%-10.5f", 123.456, double)
TEST_SPRINTF(f_width_prec_plus_post, "%+10.5f", 123.456, double)
TEST_SPRINTF(f_width_prec_spac_post, "% 10.5f", 123.456, double)
TEST_SPRINTF(f_width_prec_hash_post, "%#10.5f", 123.456, double)
TEST_SPRINTF(f_width_prec_fzer_post, "%010.5f", 123.456, double)
TEST_SPRINTF(f_width_prec_mins_negt, "%-10.5f", -123.456, double)
TEST_SPRINTF(f_width_prec_plus_negt, "%+10.5f", -123.456, double)
TEST_SPRINTF(f_width_prec_spac_negt, "% 10.5f", -123.456, double)
TEST_SPRINTF(f_width_prec_hash_negt, "%#10.5f", -123.456, double)
TEST_SPRINTF(f_width_prec_fzer_negt, "%010.5f", -123.456, double)
TEST_SPRINTF(f_width_prec_mins_small, "%-10.5f", -0.0000123456, double)
TEST_SPRINTF(f_width_prec_plus_small, "%+10.5f", -0.0000123456, double)
TEST_SPRINTF(f_width_prec_spac_small, "% 10.5f", -0.0000123456, double)
TEST_SPRINTF(f_width_prec_hash_small, "%#10.5f", -0.0000123456, double)
TEST_SPRINTF(f_width_prec_fzer_small, "%010.5f", -0.0000123456, double)
TEST_SPRINTF(f_width_prec_mins_large, "%-10.5f", 123456789.0, double)
TEST_SPRINTF(f_width_prec_plus_large, "%+10.5f", 123456789.0, double)
TEST_SPRINTF(f_width_prec_spac_large, "% 10.5f", 123456789.0, double)
TEST_SPRINTF(f_width_prec_hash_large, "%#10.5f", 123456789.0, double)
TEST_SPRINTF(f_width_prec_fzer_large, "%010.5f", 123456789.0, double)

TEST_SPRINTF(f_zrwth_zrpc_plus_post, "%+0.0f", 123.456, double)
TEST_SPRINTF(f_zrwth_zrpc_spac_post, "% 0.0f", 123.456, double)
TEST_SPRINTF(f_zrwth_zrpc_hash_post, "%#0.0f", 123.456, double)
TEST_SPRINTF(f_zrwth_zrpc_plus_negt, "%+0.0f", -123.456, double)
TEST_SPRINTF(f_zrwth_zrpc_spac_negt, "% 0.0f", -123.456, double)
TEST_SPRINTF(f_zrwth_zrpc_hash_negt, "%#0.0f", -123.456, double)
TEST_SPRINTF(f_zrwth_zrpc_plus_small, "%+0.0f", -0.0000123456, double)
TEST_SPRINTF(f_zrwth_zrpc_spac_small, "% 0.0f", -0.0000123456, double)
TEST_SPRINTF(f_zrwth_zrpc_hash_small, "%#0.0f", -0.0000123456, double)
TEST_SPRINTF(f_zrwth_zrpc_plus_large, "%+0.0f", 123456789.0, double)
TEST_SPRINTF(f_zrwth_zrpc_spac_large, "% 0.0f", 123456789.0, double)
TEST_SPRINTF(f_zrwth_zrpc_hash_large, "%#0.0f", 123456789.0, double)

TEST_SPRINTF_2(f_dynamic_width_post, "%*f", 10, 123.456, double)
TEST_SPRINTF_2(f_dynamic_width_negt, "%*f", 10, -123.456, double)
TEST_SPRINTF_2(f_dynamic_width_small, "%*f", 10, -0.0000123456, double)
TEST_SPRINTF_2(f_dynamic_width_large, "%*f", 10, 123456789.0, double)

TEST_SPRINTF_2(f_dynamic_prec_post, "%.*f", 5, 123.456, double)
TEST_SPRINTF_2(f_dynamic_prec_negt, "%.*f", 5, -123.456, double)
TEST_SPRINTF_2(f_dynamic_prec_small, "%.*f", 5, -0.0000123456, double)
TEST_SPRINTF_2(f_dynamic_prec_large, "%.*f", 5, 123456789.0, double)

TEST_SPRINTF_3(f_dynamic_width_prec_post, "%*.*f", 10, 5, 123.456, double)
TEST_SPRINTF_3(f_dynamic_width_prec_negt, "%*.*f", 10, 5, -123.456, double)
TEST_SPRINTF_3(f_dynamic_width_prec_small, "%*.*f", 10, 5, -0.0000123456,
               double)
TEST_SPRINTF_3(f_dynamic_width_prec_large, "%*.*f", 10, 5, 123456789.0, double)

// =========================================================================

TEST_SPRINTF(g_mins_post, "%-g", 123.456, double)
TEST_SPRINTF(g_plus_post, "%+g", 123.456, double)
TEST_SPRINTF(g_spac_post, "% g", 123.456, double)
TEST_SPRINTF(g_hash_post, "%#g", 123.456, double)
TEST_SPRINTF(g_fzer_post, "%0g", 123.456, double)
TEST_SPRINTF(g_mins_negt, "%-g", -123.456, double)
TEST_SPRINTF(g_plus_negt, "%+g", -123.456, double)
TEST_SPRINTF(g_spac_negt, "% g", -123.456, double)
TEST_SPRINTF(g_hash_negt, "%#g", -123.456, double)
TEST_SPRINTF(g_fzer_negt, "%0g", -123.456, double)
TEST_SPRINTF(g_mins_small, "%-g", -0.0000123456, double)
TEST_SPRINTF(g_plus_small, "%+g", -0.0000123456, double)
TEST_SPRINTF(g_spac_small, "% g", -0.0000123456, double)
TEST_SPRINTF(g_hash_small, "%#g", -0.0000123456, double)
TEST_SPRINTF(g_fzer_small, "%0g", -0.0000123456, double)
TEST_SPRINTF(g_mins_large, "%-g", 123456789.0, double)
TEST_SPRINTF(g_plus_large, "%+g", 123456789.0, double)
TEST_SPRINTF(g_spac_large, "% g", 123456789.0, double)
TEST_SPRINTF(g_hash_large, "%#g", 123456789.0, double)
TEST_SPRINTF(g_fzer_large, "%0g", 123456789.0, double)

TEST_SPRINTF(g_width_post, "%5g", 123.456, double)
TEST_SPRINTF(g_zrpc_post, "%.0g", 123.456, double)
TEST_SPRINTF(g_prec_post, "%.5g", 123.456, double)
TEST_SPRINTF(g_width_negt, "%5g", -123.456, double)
TEST_SPRINTF(g_zrpc_negt, "%.0g", -123.456, double)
TEST_SPRINTF(g_prec_negt, "%.5g", -123.456, double)
TEST_SPRINTF(g_width_small, "%5g", -0.0000123456, double)
TEST_SPRINTF(g_zrpc_small, "%.0g", -0.0000123456, double)
TEST_SPRINTF(g_prec_small, "%.5g", -0.0000123456, double)
TEST_SPRINTF(g_width_large, "%5g", 123456789.0, double)
TEST_SPRINTF(g_zrpc_large, "%.0g", 123456789.0, double)
TEST_SPRINTF(g_prec_large, "%.5g", 123456789.0, double)

TEST_SPRINTF(g_width_prec_post, "%10.5g", 123.456, double)
TEST_SPRINTF(g_width_prec_negt, "%10.5g", -123.456, double)
TEST_SPRINTF(g_width_prec_small, "%10.5g", -0.0000123456, double)
TEST_SPRINTF(g_width_prec_large, "%10.5g", 123456789.0, double)

TEST_SPRINTF(g_width_mins_post, "%-5g", 123.456, double)
TEST_SPRINTF(g_width_plus_post, "%+5g", 123.456, double)
TEST_SPRINTF(g_width_spac_post, "% 5g", 123.456, double)
TEST_SPRINTF(g_width_hash_post, "%#5g", 123.456, double)
TEST_SPRINTF(g_width_fzer_post, "%05g", 123.456, double)
TEST_SPRINTF(g_width_mins_negt, "%-5g", -123.456, double)
TEST_SPRINTF(g_width_plus_negt, "%+5g", -123.456, double)
TEST_SPRINTF(g_width_spac_negt, "% 5g", -123.456, double)
TEST_SPRINTF(g_width_hash_negt, "%#5g", -123.456, double)
TEST_SPRINTF(g_width_fzer_negt, "%05g", -123.456, double)
TEST_SPRINTF(g_width_mins_small, "%-5g", -0.0000123456, double)
TEST_SPRINTF(g_width_plus_small, "%+5g", -0.0000123456, double)
TEST_SPRINTF(g_width_spac_small, "% 5g", -0.0000123456, double)
TEST_SPRINTF(g_width_hash_small, "%#5g", -0.0000123456, double)
TEST_SPRINTF(g_width_fzer_small, "%05g", -0.0000123456, double)
TEST_SPRINTF(g_width_mins_large, "%-5g", 123456789.0, double)
TEST_SPRINTF(g_width_plus_large, "%+5g", 123456789.0, double)
TEST_SPRINTF(g_width_spac_large, "% 5g", 123456789.0, double)
TEST_SPRINTF(g_width_hash_large, "%#5g", 123456789.0, double)
TEST_SPRINTF(g_width_fzer_large, "%05g", 123456789.0, double)

TEST_SPRINTF(g_zrwth_plus_post, "%+0g", 123.456, double)
TEST_SPRINTF(g_zrwth_spac_post, "% 0g", 123.456, double)
TEST_SPRINTF(g_zrwth_hash_post, "%#0g", 123.456, double)
TEST_SPRINTF(g_zrwth_plus_negt, "%+0g", -123.456, double)
TEST_SPRINTF(g_zrwth_spac_negt, "% 0g", -123.456, double)
TEST_SPRINTF(g_zrwth_hash_negt, "%#0g", -123.456, double)
TEST_SPRINTF(g_zrwth_plus_small, "%+0g", -0.0000123456, double)
TEST_SPRINTF(g_zrwth_spac_small, "% 0g", -0.0000123456, double)
TEST_SPRINTF(g_zrwth_hash_small, "%#0g", -0.0000123456, double)
TEST_SPRINTF(g_zrwth_plus_large, "%+0g", 123456789.0, double)
TEST_SPRINTF(g_zrwth_spac_large, "% 0g", 123456789.0, double)
TEST_SPRINTF(g_zrwth_hash_large, "%#0g", 123456789.0, double)

TEST_SPRINTF(g_prec_mins_post, "%-.5g", 123.456, double)
TEST_SPRINTF(g_prec_plus_post, "%+.5g", 123.456, double)
TEST_SPRINTF(g_prec_spac_post, "% .5g", 123.456, double)
TEST_SPRINTF(g_prec_hash_post, "%#.5g", 123.456, double)
TEST_SPRINTF(g_prec_fzer_post, "%0.5g", 123.456, double)
TEST_SPRINTF(g_prec_mins_negt, "%-.5g", -123.456, double)
TEST_SPRINTF(g_prec_plus_negt, "%+.5g", -123.456, double)
TEST_SPRINTF(g_prec_spac_negt, "% .5g", -123.456, double)
TEST_SPRINTF(g_prec_hash_negt, "%#.5g", -123.456, double)
TEST_SPRINTF(g_prec_fzer_negt, "%0.5g", -123.456, double)
TEST_SPRINTF(g_prec_mins_small, "%-.5g", -0.0000123456, double)
TEST_SPRINTF(g_prec_plus_small, "%+.5g", -0.0000123456, double)
TEST_SPRINTF(g_prec_spac_small, "% .5g", -0.0000123456, double)
TEST_SPRINTF(g_prec_hash_small, "%#.5g", -0.0000123456, double)
TEST_SPRINTF(g_prec_fzer_small, "%0.5g", -0.0000123456, double)
TEST_SPRINTF(g_prec_mins_large, "%-.5g", 123456789.0, double)
TEST_SPRINTF(g_prec_plus_large, "%+.5g", 123456789.0, double)
TEST_SPRINTF(g_prec_spac_large, "% .5g", 123456789.0, double)
TEST_SPRINTF(g_prec_hash_large, "%#.5g", 123456789.0, double)
TEST_SPRINTF(g_prec_fzer_large, "%0.5g", 123456789.0, double)

TEST_SPRINTF(g_zrpc_mins_post, "%-.0g", 123.456, double)
TEST_SPRINTF(g_zrpc_plus_post, "%+.0g", 123.456, double)
TEST_SPRINTF(g_zrpc_spac_post, "% .0g", 123.456, double)
TEST_SPRINTF(g_zrpc_hash_post, "%#.0g", 123.456, double)
TEST_SPRINTF(g_zrpc_fzer_post, "%0.0g", 123.456, double)
TEST_SPRINTF(g_zrpc_mins_negt, "%-.0g", -123.456, double)
TEST_SPRINTF(g_zrpc_plus_negt, "%+.0g", -123.456, double)
TEST_SPRINTF(g_zrpc_spac_negt, "% .0g", -123.456, double)
TEST_SPRINTF(g_zrpc_hash_negt, "%#.0g", -123.456, double)
TEST_SPRINTF(g_zrpc_fzer_negt, "%0.0g", -123.456, double)
TEST_SPRINTF(g_zrpc_mins_small, "%-.0g", -0.0000123456, double)
TEST_SPRINTF(g_zrpc_plus_small, "%+.0g", -0.0000123456, double)
TEST_SPRINTF(g_zrpc_spac_small, "% .0g", -0.0000123456, double)
TEST_SPRINTF(g_zrpc_hash_small, "%#.0g", -0.0000123456, double)
TEST_SPRINTF(g_zrpc_fzer_small, "%0.0g", -0.0000123456, double)
TEST_SPRINTF(g_zrpc_mins_large, "%-.0g", 123456789.0, double)
TEST_SPRINTF(g_zrpc_plus_large, "%+.0g", 123456789.0, double)
TEST_SPRINTF(g_zrpc_spac_large, "% .0g", 123456789.0, double)
TEST_SPRINTF(g_zrpc_hash_large, "%#.0g", 123456789.0, double)
TEST_SPRINTF(g_zrpc_fzer_large, "%0.0g", 123456789.0, double)

TEST_SPRINTF(g_width_prec_mins_post, "%-10.5g", 123.456, double)
TEST_SPRINTF(g_width_prec_plus_post, "%+10.5g", 123.456, double)
TEST_SPRINTF(g_width_prec_spac_post, "% 10.5g", 123.456, double)
TEST_SPRINTF(g_width_prec_hash_post, "%#10.5g", 123.456, double)
TEST_SPRINTF(g_width_prec_fzer_post, "%010.5g", 123.456, double)
TEST_SPRINTF(g_width_prec_mins_negt, "%-10.5g", -123.456, double)
TEST_SPRINTF(g_width_prec_plus_negt, "%+10.5g", -123.456, double)
TEST_SPRINTF(g_width_prec_spac_negt, "% 10.5g", -123.456, double)
TEST_SPRINTF(g_width_prec_hash_negt, "%#10.5g", -123.456, double)
TEST_SPRINTF(g_width_prec_fzer_negt, "%010.5g", -123.456, double)
TEST_SPRINTF(g_width_prec_mins_small, "%-10.5g", -0.0000123456, double)
TEST_SPRINTF(g_width_prec_plus_small, "%+10.5g", -0.0000123456, double)
TEST_SPRINTF(g_width_prec_spac_small, "% 10.5g", -0.0000123456, double)
TEST_SPRINTF(g_width_prec_hash_small, "%#10.5g", -0.0000123456, double)
TEST_SPRINTF(g_width_prec_fzer_small, "%010.5g", -0.0000123456, double)
TEST_SPRINTF(g_width_prec_mins_large, "%-10.5g", 123456789.0, double)
TEST_SPRINTF(g_width_prec_plus_large, "%+10.5g", 123456789.0, double)
TEST_SPRINTF(g_width_prec_spac_large, "% 10.5g", 123456789.0, double)
TEST_SPRINTF(g_width_prec_hash_large, "%#10.5g", 123456789.0, double)
TEST_SPRINTF(g_width_prec_fzer_large, "%010.5g", 123456789.0, double)

TEST_SPRINTF(g_zrwth_zrpc_plus_post, "%+0.0g", 123.456, double)
TEST_SPRINTF(g_zrwth_zrpc_spac_post, "% 0.0g", 123.456, double)
TEST_SPRINTF(g_zrwth_zrpc_hash_post, "%#0.0g", 123.456, double)
TEST_SPRINTF(g_zrwth_zrpc_plus_negt, "%+0.0g", -123.456, double)
TEST_SPRINTF(g_zrwth_zrpc_spac_negt, "% 0.0g", -123.456, double)
TEST_SPRINTF(g_zrwth_zrpc_hash_negt, "%#0.0g", -123.456, double)
TEST_SPRINTF(g_zrwth_zrpc_plus_small, "%+0.0g", -0.0000123456, double)
TEST_SPRINTF(g_zrwth_zrpc_spac_small, "% 0.0g", -0.0000123456, double)
TEST_SPRINTF(g_zrwth_zrpc_hash_small, "%#0.0g", -0.0000123456, double)
TEST_SPRINTF(g_zrwth_zrpc_plus_large, "%+0.0g", 123456789.0, double)
TEST_SPRINTF(g_zrwth_zrpc_spac_large, "% 0.0g", 123456789.0, double)
TEST_SPRINTF(g_zrwth_zrpc_hash_large, "%#0.0g", 123456789.0, double)

TEST_SPRINTF_2(g_dynamic_width_post, "%*g", 10, 123.456, double)
TEST_SPRINTF_2(g_dynamic_width_negt, "%*g", 10, -123.456, double)
TEST_SPRINTF_2(g_dynamic_width_small, "%*g", 10, -0.0000123456, double)
TEST_SPRINTF_2(g_dynamic_width_large, "%*g", 10, 123456789.0, double)

TEST_SPRINTF_2(g_dynamic_prec_post, "%.*g", 5, 123.456, double)
TEST_SPRINTF_2(g_dynamic_prec_negt, "%.*g", 5, -123.456, double)
TEST_SPRINTF_2(g_dynamic_prec_small, "%.*g", 5, -0.0000123456, double)
TEST_SPRINTF_2(g_dynamic_prec_large, "%.*g", 5, 123456789.0, double)

TEST_SPRINTF_3(g_dynamic_width_prec_post, "%*.*g", 10, 5, 123.456, double)
TEST_SPRINTF_3(g_dynamic_width_prec_negt, "%*.*g", 10, 5, -123.456, double)
TEST_SPRINTF_3(g_dynamic_width_prec_small, "%*.*g", 10, 5, -0.0000123456,
               double)
TEST_SPRINTF_3(g_dynamic_width_prec_large, "%*.*g", 10, 5, 123456789.0, double)

// =========================================================================

TEST_SPRINTF(G_mins_post, "%-G", 123.456, double)
TEST_SPRINTF(G_plus_post, "%+G", 123.456, double)
TEST_SPRINTF(G_spac_post, "% G", 123.456, double)
TEST_SPRINTF(G_hash_post, "%#G", 123.456, double)
TEST_SPRINTF(G_fzer_post, "%0G", 123.456, double)
TEST_SPRINTF(G_mins_negt, "%-G", -123.456, double)
TEST_SPRINTF(G_plus_negt, "%+G", -123.456, double)
TEST_SPRINTF(G_spac_negt, "% G", -123.456, double)
TEST_SPRINTF(G_hash_negt, "%#G", -123.456, double)
TEST_SPRINTF(G_fzer_negt, "%0G", -123.456, double)
TEST_SPRINTF(G_mins_small, "%-G", -0.0000123456, double)
TEST_SPRINTF(G_plus_small, "%+G", -0.0000123456, double)
TEST_SPRINTF(G_spac_small, "% G", -0.0000123456, double)
TEST_SPRINTF(G_hash_small, "%#G", -0.0000123456, double)
TEST_SPRINTF(G_fzer_small, "%0G", -0.0000123456, double)
TEST_SPRINTF(G_mins_large, "%-G", 123456789.0, double)
TEST_SPRINTF(G_plus_large, "%+G", 123456789.0, double)
TEST_SPRINTF(G_spac_large, "% G", 123456789.0, double)
TEST_SPRINTF(G_hash_large, "%#G", 123456789.0, double)
TEST_SPRINTF(G_fzer_large, "%0G", 123456789.0, double)

TEST_SPRINTF(G_width_post, "%5G", 123.456, double)
TEST_SPRINTF(G_zrpc_post, "%.0G", 123.456, double)
TEST_SPRINTF(G_prec_post, "%.5G", 123.456, double)
TEST_SPRINTF(G_width_negt, "%5G", -123.456, double)
TEST_SPRINTF(G_zrpc_negt, "%.0G", -123.456, double)
TEST_SPRINTF(G_prec_negt, "%.5G", -123.456, double)
TEST_SPRINTF(G_width_small, "%5G", -0.0000123456, double)
TEST_SPRINTF(G_zrpc_small, "%.0G", -0.0000123456, double)
TEST_SPRINTF(G_prec_small, "%.5G", -0.0000123456, double)
TEST_SPRINTF(G_width_large, "%5G", 123456789.0, double)
TEST_SPRINTF(G_zrpc_large, "%.0G", 123456789.0, double)
TEST_SPRINTF(G_prec_large, "%.5G", 123456789.0, double)

TEST_SPRINTF(G_width_prec_post, "%10.5G", 123.456, double)
TEST_SPRINTF(G_width_prec_negt, "%10.5G", -123.456, double)
TEST_SPRINTF(G_width_prec_small, "%10.5G", -0.0000123456, double)
TEST_SPRINTF(G_width_prec_large, "%10.5G", 123456789.0, double)

TEST_SPRINTF(G_width_mins_post, "%-5G", 123.456, double)
TEST_SPRINTF(G_width_plus_post, "%+5G", 123.456, double)
TEST_SPRINTF(G_width_spac_post, "% 5G", 123.456, double)
TEST_SPRINTF(G_width_hash_post, "%#5G", 123.456, double)
TEST_SPRINTF(G_width_fzer_post, "%05G", 123.456, double)
TEST_SPRINTF(G_width_mins_negt, "%-5G", -123.456, double)
TEST_SPRINTF(G_width_plus_negt, "%+5G", -123.456, double)
TEST_SPRINTF(G_width_spac_negt, "% 5G", -123.456, double)
TEST_SPRINTF(G_width_hash_negt, "%#5G", -123.456, double)
TEST_SPRINTF(G_width_fzer_negt, "%05G", -123.456, double)
TEST_SPRINTF(G_width_mins_small, "%-5G", -0.0000123456, double)
TEST_SPRINTF(G_width_plus_small, "%+5G", -0.0000123456, double)
TEST_SPRINTF(G_width_spac_small, "% 5G", -0.0000123456, double)
TEST_SPRINTF(G_width_hash_small, "%#5G", -0.0000123456, double)
TEST_SPRINTF(G_width_fzer_small, "%05G", -0.0000123456, double)
TEST_SPRINTF(G_width_mins_large, "%-5G", 123456789.0, double)
TEST_SPRINTF(G_width_plus_large, "%+5G", 123456789.0, double)
TEST_SPRINTF(G_width_spac_large, "% 5G", 123456789.0, double)
TEST_SPRINTF(G_width_hash_large, "%#5G", 123456789.0, double)
TEST_SPRINTF(G_width_fzer_large, "%05G", 123456789.0, double)

TEST_SPRINTF(G_zrwth_plus_post, "%+0G", 123.456, double)
TEST_SPRINTF(G_zrwth_spac_post, "% 0G", 123.456, double)
TEST_SPRINTF(G_zrwth_hash_post, "%#0G", 123.456, double)
TEST_SPRINTF(G_zrwth_plus_negt, "%+0G", -123.456, double)
TEST_SPRINTF(G_zrwth_spac_negt, "% 0G", -123.456, double)
TEST_SPRINTF(G_zrwth_hash_negt, "%#0G", -123.456, double)
TEST_SPRINTF(G_zrwth_plus_small, "%+0G", -0.0000123456, double)
TEST_SPRINTF(G_zrwth_spac_small, "% 0G", -0.0000123456, double)
TEST_SPRINTF(G_zrwth_hash_small, "%#0G", -0.0000123456, double)
TEST_SPRINTF(G_zrwth_plus_large, "%+0G", 123456789.0, double)
TEST_SPRINTF(G_zrwth_spac_large, "% 0G", 123456789.0, double)
TEST_SPRINTF(G_zrwth_hash_large, "%#0G", 123456789.0, double)

TEST_SPRINTF(G_prec_mins_post, "%-.5G", 123.456, double)
TEST_SPRINTF(G_prec_plus_post, "%+.5G", 123.456, double)
TEST_SPRINTF(G_prec_spac_post, "% .5G", 123.456, double)
TEST_SPRINTF(G_prec_hash_post, "%#.5G", 123.456, double)
TEST_SPRINTF(G_prec_fzer_post, "%0.5G", 123.456, double)
TEST_SPRINTF(G_prec_mins_negt, "%-.5G", -123.456, double)
TEST_SPRINTF(G_prec_plus_negt, "%+.5G", -123.456, double)
TEST_SPRINTF(G_prec_spac_negt, "% .5G", -123.456, double)
TEST_SPRINTF(G_prec_hash_negt, "%#.5G", -123.456, double)
TEST_SPRINTF(G_prec_fzer_negt, "%0.5G", -123.456, double)
TEST_SPRINTF(G_prec_mins_small, "%-.5G", -0.0000123456, double)
TEST_SPRINTF(G_prec_plus_small, "%+.5G", -0.0000123456, double)
TEST_SPRINTF(G_prec_spac_small, "% .5G", -0.0000123456, double)
TEST_SPRINTF(G_prec_hash_small, "%#.5G", -0.0000123456, double)
TEST_SPRINTF(G_prec_fzer_small, "%0.5G", -0.0000123456, double)
TEST_SPRINTF(G_prec_mins_large, "%-.5G", 123456789.0, double)
TEST_SPRINTF(G_prec_plus_large, "%+.5G", 123456789.0, double)
TEST_SPRINTF(G_prec_spac_large, "% .5G", 123456789.0, double)
TEST_SPRINTF(G_prec_hash_large, "%#.5G", 123456789.0, double)
TEST_SPRINTF(G_prec_fzer_large, "%0.5G", 123456789.0, double)

TEST_SPRINTF(G_zrpc_mins_post, "%-.0G", 123.456, double)
TEST_SPRINTF(G_zrpc_plus_post, "%+.0G", 123.456, double)
TEST_SPRINTF(G_zrpc_spac_post, "% .0G", 123.456, double)
TEST_SPRINTF(G_zrpc_hash_post, "%#.0G", 123.456, double)
TEST_SPRINTF(G_zrpc_fzer_post, "%0.0G", 123.456, double)
TEST_SPRINTF(G_zrpc_mins_negt, "%-.0G", -123.456, double)
TEST_SPRINTF(G_zrpc_plus_negt, "%+.0G", -123.456, double)
TEST_SPRINTF(G_zrpc_spac_negt, "% .0G", -123.456, double)
TEST_SPRINTF(G_zrpc_hash_negt, "%#.0G", -123.456, double)
TEST_SPRINTF(G_zrpc_fzer_negt, "%0.0G", -123.456, double)
TEST_SPRINTF(G_zrpc_mins_small, "%-.0G", -0.0000123456, double)
TEST_SPRINTF(G_zrpc_plus_small, "%+.0G", -0.0000123456, double)
TEST_SPRINTF(G_zrpc_spac_small, "% .0G", -0.0000123456, double)
TEST_SPRINTF(G_zrpc_hash_small, "%#.0G", -0.0000123456, double)
TEST_SPRINTF(G_zrpc_fzer_small, "%0.0G", -0.0000123456, double)
TEST_SPRINTF(G_zrpc_mins_large, "%-.0G", 123456789.0, double)
TEST_SPRINTF(G_zrpc_plus_large, "%+.0G", 123456789.0, double)
TEST_SPRINTF(G_zrpc_spac_large, "% .0G", 123456789.0, double)
TEST_SPRINTF(G_zrpc_hash_large, "%#.0G", 123456789.0, double)
TEST_SPRINTF(G_zrpc_fzer_large, "%0.0G", 123456789.0, double)

TEST_SPRINTF(G_width_prec_mins_post, "%-10.5G", 123.456, double)
TEST_SPRINTF(G_width_prec_plus_post, "%+10.5G", 123.456, double)
TEST_SPRINTF(G_width_prec_spac_post, "% 10.5G", 123.456, double)
TEST_SPRINTF(G_width_prec_hash_post, "%#10.5G", 123.456, double)
TEST_SPRINTF(G_width_prec_fzer_post, "%010.5G", 123.456, double)
TEST_SPRINTF(G_width_prec_mins_negt, "%-10.5G", -123.456, double)
TEST_SPRINTF(G_width_prec_plus_negt, "%+10.5G", -123.456, double)
TEST_SPRINTF(G_width_prec_spac_negt, "% 10.5G", -123.456, double)
TEST_SPRINTF(G_width_prec_hash_negt, "%#10.5G", -123.456, double)
TEST_SPRINTF(G_width_prec_fzer_negt, "%010.5G", -123.456, double)
TEST_SPRINTF(G_width_prec_mins_small, "%-10.5G", -0.0000123456, double)
TEST_SPRINTF(G_width_prec_plus_small, "%+10.5G", -0.0000123456, double)
TEST_SPRINTF(G_width_prec_spac_small, "% 10.5G", -0.0000123456, double)
TEST_SPRINTF(G_width_prec_hash_small, "%#10.5G", -0.0000123456, double)
TEST_SPRINTF(G_width_prec_fzer_small, "%010.5G", -0.0000123456, double)
TEST_SPRINTF(G_width_prec_mins_large, "%-10.5G", 123456789.0, double)
TEST_SPRINTF(G_width_prec_plus_large, "%+10.5G", 123456789.0, double)
TEST_SPRINTF(G_width_prec_spac_large, "% 10.5G", 123456789.0, double)
TEST_SPRINTF(G_width_prec_hash_large, "%#10.5G", 123456789.0, double)
TEST_SPRINTF(G_width_prec_fzer_large, "%010.5G", 123456789.0, double)

TEST_SPRINTF(G_zrwth_zrpc_plus_post, "%+0.0G", 123.456, double)
TEST_SPRINTF(G_zrwth_zrpc_spac_post, "% 0.0G", 123.456, double)
TEST_SPRINTF(G_zrwth_zrpc_hash_post, "%#0.0G", 123.456, double)
TEST_SPRINTF(G_zrwth_zrpc_plus_negt, "%+0.0G", -123.456, double)
TEST_SPRINTF(G_zrwth_zrpc_spac_negt, "% 0.0G", -123.456, double)
TEST_SPRINTF(G_zrwth_zrpc_hash_negt, "%#0.0G", -123.456, double)
TEST_SPRINTF(G_zrwth_zrpc_plus_small, "%+0.0G", -0.0000123456, double)
TEST_SPRINTF(G_zrwth_zrpc_spac_small, "% 0.0G", -0.0000123456, double)
TEST_SPRINTF(G_zrwth_zrpc_hash_small, "%#0.0G", -0.0000123456, double)
TEST_SPRINTF(G_zrwth_zrpc_plus_large, "%+0.0G", 123456789.0, double)
TEST_SPRINTF(G_zrwth_zrpc_spac_large, "% 0.0G", 123456789.0, double)
TEST_SPRINTF(G_zrwth_zrpc_hash_large, "%#0.0G", 123456789.0, double)

TEST_SPRINTF_2(G_dynamic_width_post, "%*G", 10, 123.456, double)
TEST_SPRINTF_2(G_dynamic_width_negt, "%*G", 10, -123.456, double)
TEST_SPRINTF_2(G_dynamic_width_small, "%*G", 10, -0.0000123456, double)
TEST_SPRINTF_2(G_dynamic_width_large, "%*G", 10, 123456789.0, double)

TEST_SPRINTF_2(G_dynamic_prec_post, "%.*G", 5, 123.456, double)
TEST_SPRINTF_2(G_dynamic_prec_negt, "%.*G", 5, -123.456, double)
TEST_SPRINTF_2(G_dynamic_prec_small, "%.*G", 5, -0.0000123456, double)
TEST_SPRINTF_2(G_dynamic_prec_large, "%.*G", 5, 123456789.0, double)

TEST_SPRINTF_3(G_dynamic_width_prec_post, "%*.*G", 10, 5, 123.456, double)
TEST_SPRINTF_3(G_dynamic_width_prec_negt, "%*.*G", 10, 5, -123.456, double)
TEST_SPRINTF_3(G_dynamic_width_prec_small, "%*.*G", 10, 5, -0.0000123456,
               double)
TEST_SPRINTF_3(G_dynamic_width_prec_large, "%*.*G", 10, 5, 123456789.0, double)
#pragma endregion

// =========================================================================
// Вещественные типы модификатор l (long) %lf %le %lE %lg %lG
// =========================================================================
#pragma region
TEST_SPRINTF(le_mins_post, "%-le", 123.456, double)
TEST_SPRINTF(le_plus_post, "%+le", 123.456, double)
TEST_SPRINTF(le_spac_post, "% le", 123.456, double)
TEST_SPRINTF(le_hash_post, "%#le", 123.456, double)
TEST_SPRINTF(le_fzer_post, "%0le", 123.456, double)
TEST_SPRINTF(le_mins_negt, "%-le", -123.456, double)
TEST_SPRINTF(le_plus_negt, "%+le", -123.456, double)
TEST_SPRINTF(le_spac_negt, "% le", -123.456, double)
TEST_SPRINTF(le_hash_negt, "%#le", -123.456, double)
TEST_SPRINTF(le_fzer_negt, "%0le", -123.456, double)
TEST_SPRINTF(le_mins_small, "%-le", -0.0000123456, double)
TEST_SPRINTF(le_plus_small, "%+le", -0.0000123456, double)
TEST_SPRINTF(le_spac_small, "% le", -0.0000123456, double)
TEST_SPRINTF(le_hash_small, "%#le", -0.0000123456, double)
TEST_SPRINTF(le_fzer_small, "%0le", -0.0000123456, double)
TEST_SPRINTF(le_mins_large, "%-le", 123456789.0, double)
TEST_SPRINTF(le_plus_large, "%+le", 123456789.0, double)
TEST_SPRINTF(le_spac_large, "% le", 123456789.0, double)
TEST_SPRINTF(le_hash_large, "%#le", 123456789.0, double)
TEST_SPRINTF(le_fzer_large, "%0le", 123456789.0, double)

TEST_SPRINTF(le_width_post, "%5le", 123.456, double)
TEST_SPRINTF(le_zrpc_post, "%.0le", 123.456, double)
TEST_SPRINTF(le_prec_post, "%.5le", 123.456, double)
TEST_SPRINTF(le_width_negt, "%5le", -123.456, double)
TEST_SPRINTF(le_zrpc_negt, "%.0le", -123.456, double)
TEST_SPRINTF(le_prec_negt, "%.5le", -123.456, double)
TEST_SPRINTF(le_width_small, "%5le", -0.0000123456, double)
TEST_SPRINTF(le_zrpc_small, "%.0le", -0.0000123456, double)
TEST_SPRINTF(le_prec_small, "%.5le", -0.0000123456, double)
TEST_SPRINTF(le_width_large, "%5le", 123456789.0, double)
TEST_SPRINTF(le_zrpc_large, "%.0le", 123456789.0, double)
TEST_SPRINTF(le_prec_large, "%.5le", 123456789.0, double)

TEST_SPRINTF(le_width_prec_post, "%10.5le", 123.456, double)
TEST_SPRINTF(le_width_prec_negt, "%10.5le", -123.456, double)
TEST_SPRINTF(le_width_prec_small, "%10.5le", -0.0000123456, double)
TEST_SPRINTF(le_width_prec_large, "%10.5le", 123456789.0, double)

TEST_SPRINTF(le_width_mins_post, "%-5le", 123.456, double)
TEST_SPRINTF(le_width_plus_post, "%+5le", 123.456, double)
TEST_SPRINTF(le_width_spac_post, "% 5le", 123.456, double)
TEST_SPRINTF(le_width_hash_post, "%#5le", 123.456, double)
TEST_SPRINTF(le_width_fzer_post, "%05le", 123.456, double)
TEST_SPRINTF(le_width_mins_negt, "%-5le", -123.456, double)
TEST_SPRINTF(le_width_plus_negt, "%+5le", -123.456, double)
TEST_SPRINTF(le_width_spac_negt, "% 5le", -123.456, double)
TEST_SPRINTF(le_width_hash_negt, "%#5le", -123.456, double)
TEST_SPRINTF(le_width_fzer_negt, "%05le", -123.456, double)
TEST_SPRINTF(le_width_mins_small, "%-5le", -0.0000123456, double)
TEST_SPRINTF(le_width_plus_small, "%+5le", -0.0000123456, double)
TEST_SPRINTF(le_width_spac_small, "% 5le", -0.0000123456, double)
TEST_SPRINTF(le_width_hash_small, "%#5le", -0.0000123456, double)
TEST_SPRINTF(le_width_fzer_small, "%05le", -0.0000123456, double)
TEST_SPRINTF(le_width_mins_large, "%-5le", 123456789.0, double)
TEST_SPRINTF(le_width_plus_large, "%+5le", 123456789.0, double)
TEST_SPRINTF(le_width_spac_large, "% 5le", 123456789.0, double)
TEST_SPRINTF(le_width_hash_large, "%#5le", 123456789.0, double)
TEST_SPRINTF(le_width_fzer_large, "%05le", 123456789.0, double)

TEST_SPRINTF(le_zrwth_plus_post, "%+0le", 123.456, double)
TEST_SPRINTF(le_zrwth_spac_post, "% 0le", 123.456, double)
TEST_SPRINTF(le_zrwth_hash_post, "%#0le", 123.456, double)
TEST_SPRINTF(le_zrwth_plus_negt, "%+0le", -123.456, double)
TEST_SPRINTF(le_zrwth_spac_negt, "% 0le", -123.456, double)
TEST_SPRINTF(le_zrwth_hash_negt, "%#0le", -123.456, double)
TEST_SPRINTF(le_zrwth_plus_small, "%+0le", -0.0000123456, double)
TEST_SPRINTF(le_zrwth_spac_small, "% 0le", -0.0000123456, double)
TEST_SPRINTF(le_zrwth_hash_small, "%#0le", -0.0000123456, double)
TEST_SPRINTF(le_zrwth_plus_large, "%+0le", 123456789.0, double)
TEST_SPRINTF(le_zrwth_spac_large, "% 0le", 123456789.0, double)
TEST_SPRINTF(le_zrwth_hash_large, "%#0le", 123456789.0, double)

TEST_SPRINTF(le_prec_mins_post, "%-.5le", 123.456, double)
TEST_SPRINTF(le_prec_plus_post, "%+.5le", 123.456, double)
TEST_SPRINTF(le_prec_spac_post, "% .5le", 123.456, double)
TEST_SPRINTF(le_prec_hash_post, "%#.5le", 123.456, double)
TEST_SPRINTF(le_prec_fzer_post, "%0.5le", 123.456, double)
TEST_SPRINTF(le_prec_mins_negt, "%-.5le", -123.456, double)
TEST_SPRINTF(le_prec_plus_negt, "%+.5le", -123.456, double)
TEST_SPRINTF(le_prec_spac_negt, "% .5le", -123.456, double)
TEST_SPRINTF(le_prec_hash_negt, "%#.5le", -123.456, double)
TEST_SPRINTF(le_prec_fzer_negt, "%0.5le", -123.456, double)
TEST_SPRINTF(le_prec_mins_small, "%-.5le", -0.0000123456, double)
TEST_SPRINTF(le_prec_plus_small, "%+.5le", -0.0000123456, double)
TEST_SPRINTF(le_prec_spac_small, "% .5le", -0.0000123456, double)
TEST_SPRINTF(le_prec_hash_small, "%#.5le", -0.0000123456, double)
TEST_SPRINTF(le_prec_fzer_small, "%0.5le", -0.0000123456, double)
TEST_SPRINTF(le_prec_mins_large, "%-.5le", 123456789.0, double)
TEST_SPRINTF(le_prec_plus_large, "%+.5le", 123456789.0, double)
TEST_SPRINTF(le_prec_spac_large, "% .5le", 123456789.0, double)
TEST_SPRINTF(le_prec_hash_large, "%#.5le", 123456789.0, double)
TEST_SPRINTF(le_prec_fzer_large, "%0.5le", 123456789.0, double)

TEST_SPRINTF(le_zrpc_mins_post, "%-.0le", 123.456, double)
TEST_SPRINTF(le_zrpc_plus_post, "%+.0le", 123.456, double)
TEST_SPRINTF(le_zrpc_spac_post, "% .0le", 123.456, double)
TEST_SPRINTF(le_zrpc_hash_post, "%#.0le", 123.456, double)
TEST_SPRINTF(le_zrpc_fzer_post, "%0.0le", 123.456, double)
TEST_SPRINTF(le_zrpc_mins_negt, "%-.0le", -123.456, double)
TEST_SPRINTF(le_zrpc_plus_negt, "%+.0le", -123.456, double)
TEST_SPRINTF(le_zrpc_spac_negt, "% .0le", -123.456, double)
TEST_SPRINTF(le_zrpc_hash_negt, "%#.0le", -123.456, double)
TEST_SPRINTF(le_zrpc_fzer_negt, "%0.0le", -123.456, double)
TEST_SPRINTF(le_zrpc_mins_small, "%-.0le", -0.0000123456, double)
TEST_SPRINTF(le_zrpc_plus_small, "%+.0le", -0.0000123456, double)
TEST_SPRINTF(le_zrpc_spac_small, "% .0le", -0.0000123456, double)
TEST_SPRINTF(le_zrpc_hash_small, "%#.0le", -0.0000123456, double)
TEST_SPRINTF(le_zrpc_fzer_small, "%0.0le", -0.0000123456, double)
TEST_SPRINTF(le_zrpc_mins_large, "%-.0le", 123456789.0, double)
TEST_SPRINTF(le_zrpc_plus_large, "%+.0le", 123456789.0, double)
TEST_SPRINTF(le_zrpc_spac_large, "% .0le", 123456789.0, double)
TEST_SPRINTF(le_zrpc_hash_large, "%#.0le", 123456789.0, double)
TEST_SPRINTF(le_zrpc_fzer_large, "%0.0le", 123456789.0, double)

TEST_SPRINTF(le_width_prec_mins_post, "%-10.5le", 123.456, double)
TEST_SPRINTF(le_width_prec_plus_post, "%+10.5le", 123.456, double)
TEST_SPRINTF(le_width_prec_spac_post, "% 10.5le", 123.456, double)
TEST_SPRINTF(le_width_prec_hash_post, "%#10.5le", 123.456, double)
TEST_SPRINTF(le_width_prec_fzer_post, "%010.5le", 123.456, double)
TEST_SPRINTF(le_width_prec_mins_negt, "%-10.5le", -123.456, double)
TEST_SPRINTF(le_width_prec_plus_negt, "%+10.5le", -123.456, double)
TEST_SPRINTF(le_width_prec_spac_negt, "% 10.5le", -123.456, double)
TEST_SPRINTF(le_width_prec_hash_negt, "%#10.5le", -123.456, double)
TEST_SPRINTF(le_width_prec_fzer_negt, "%010.5le", -123.456, double)
TEST_SPRINTF(le_width_prec_mins_small, "%-10.5le", -0.0000123456, double)
TEST_SPRINTF(le_width_prec_plus_small, "%+10.5le", -0.0000123456, double)
TEST_SPRINTF(le_width_prec_spac_small, "% 10.5le", -0.0000123456, double)
TEST_SPRINTF(le_width_prec_hash_small, "%#10.5le", -0.0000123456, double)
TEST_SPRINTF(le_width_prec_fzer_small, "%010.5le", -0.0000123456, double)
TEST_SPRINTF(le_width_prec_mins_large, "%-10.5le", 123456789.0, double)
TEST_SPRINTF(le_width_prec_plus_large, "%+10.5le", 123456789.0, double)
TEST_SPRINTF(le_width_prec_spac_large, "% 10.5le", 123456789.0, double)
TEST_SPRINTF(le_width_prec_hash_large, "%#10.5le", 123456789.0, double)
TEST_SPRINTF(le_width_prec_fzer_large, "%010.5le", 123456789.0, double)

TEST_SPRINTF(le_zrwth_zrpc_plus_post, "%+0.0le", 123.456, double)
TEST_SPRINTF(le_zrwth_zrpc_spac_post, "% 0.0le", 123.456, double)
TEST_SPRINTF(le_zrwth_zrpc_hash_post, "%#0.0le", 123.456, double)
TEST_SPRINTF(le_zrwth_zrpc_plus_negt, "%+0.0le", -123.456, double)
TEST_SPRINTF(le_zrwth_zrpc_spac_negt, "% 0.0le", -123.456, double)
TEST_SPRINTF(le_zrwth_zrpc_hash_negt, "%#0.0le", -123.456, double)
TEST_SPRINTF(le_zrwth_zrpc_plus_small, "%+0.0le", -0.0000123456, double)
TEST_SPRINTF(le_zrwth_zrpc_spac_small, "% 0.0le", -0.0000123456, double)
TEST_SPRINTF(le_zrwth_zrpc_hash_small, "%#0.0le", -0.0000123456, double)
TEST_SPRINTF(le_zrwth_zrpc_plus_large, "%+0.0le", 123456789.0, double)
TEST_SPRINTF(le_zrwth_zrpc_spac_large, "% 0.0le", 123456789.0, double)
TEST_SPRINTF(le_zrwth_zrpc_hash_large, "%#0.0le", 123456789.0, double)

TEST_SPRINTF_2(le_dynamic_width_post, "%*le", 10, 123.456, double)
TEST_SPRINTF_2(le_dynamic_width_negt, "%*le", 10, -123.456, double)
TEST_SPRINTF_2(le_dynamic_width_small, "%*le", 10, -0.0000123456, double)
TEST_SPRINTF_2(le_dynamic_width_large, "%*le", 10, 123456789.0, double)

TEST_SPRINTF_2(le_dynamic_prec_post, "%.*le", 5, 123.456, double)
TEST_SPRINTF_2(le_dynamic_prec_negt, "%.*le", 5, -123.456, double)
TEST_SPRINTF_2(le_dynamic_prec_small, "%.*le", 5, -0.0000123456, double)
TEST_SPRINTF_2(le_dynamic_prec_large, "%.*le", 5, 123456789.0, double)

TEST_SPRINTF_3(le_dynamic_width_prec_post, "%*.*le", 10, 5, 123.456, double)
TEST_SPRINTF_3(le_dynamic_width_prec_negt, "%*.*le", 10, 5, -123.456, double)
TEST_SPRINTF_3(le_dynamic_width_prec_small, "%*.*le", 10, 5, -0.0000123456,
               double)
TEST_SPRINTF_3(le_dynamic_width_prec_large, "%*.*le", 10, 5, 123456789.0,
               double)

// =========================================================================

TEST_SPRINTF(lE_mins_post, "%-lE", 123.456, double)
TEST_SPRINTF(lE_plus_post, "%+lE", 123.456, double)
TEST_SPRINTF(lE_spac_post, "% lE", 123.456, double)
TEST_SPRINTF(lE_hash_post, "%#lE", 123.456, double)
TEST_SPRINTF(lE_fzer_post, "%0lE", 123.456, double)
TEST_SPRINTF(lE_mins_negt, "%-lE", -123.456, double)
TEST_SPRINTF(lE_plus_negt, "%+lE", -123.456, double)
TEST_SPRINTF(lE_spac_negt, "% lE", -123.456, double)
TEST_SPRINTF(lE_hash_negt, "%#lE", -123.456, double)
TEST_SPRINTF(lE_fzer_negt, "%0lE", -123.456, double)
TEST_SPRINTF(lE_mins_small, "%-lE", -0.0000123456, double)
TEST_SPRINTF(lE_plus_small, "%+lE", -0.0000123456, double)
TEST_SPRINTF(lE_spac_small, "% lE", -0.0000123456, double)
TEST_SPRINTF(lE_hash_small, "%#lE", -0.0000123456, double)
TEST_SPRINTF(lE_fzer_small, "%0lE", -0.0000123456, double)
TEST_SPRINTF(lE_mins_large, "%-lE", 123456789.0, double)
TEST_SPRINTF(lE_plus_large, "%+lE", 123456789.0, double)
TEST_SPRINTF(lE_spac_large, "% lE", 123456789.0, double)
TEST_SPRINTF(lE_hash_large, "%#lE", 123456789.0, double)
TEST_SPRINTF(lE_fzer_large, "%0lE", 123456789.0, double)

TEST_SPRINTF(lE_width_post, "%5lE", 123.456, double)
TEST_SPRINTF(lE_zrpc_post, "%.0lE", 123.456, double)
TEST_SPRINTF(lE_prec_post, "%.5lE", 123.456, double)
TEST_SPRINTF(lE_width_negt, "%5lE", -123.456, double)
TEST_SPRINTF(lE_zrpc_negt, "%.0lE", -123.456, double)
TEST_SPRINTF(lE_prec_negt, "%.5lE", -123.456, double)
TEST_SPRINTF(lE_width_small, "%5lE", -0.0000123456, double)
TEST_SPRINTF(lE_zrpc_small, "%.0lE", -0.0000123456, double)
TEST_SPRINTF(lE_prec_small, "%.5lE", -0.0000123456, double)
TEST_SPRINTF(lE_width_large, "%5lE", 123456789.0, double)
TEST_SPRINTF(lE_zrpc_large, "%.0lE", 123456789.0, double)
TEST_SPRINTF(lE_prec_large, "%.5lE", 123456789.0, double)

TEST_SPRINTF(lE_width_prec_post, "%10.5lE", 123.456, double)
TEST_SPRINTF(lE_width_prec_negt, "%10.5lE", -123.456, double)
TEST_SPRINTF(lE_width_prec_small, "%10.5lE", -0.0000123456, double)
TEST_SPRINTF(lE_width_prec_large, "%10.5lE", 123456789.0, double)

TEST_SPRINTF(lE_width_mins_post, "%-5lE", 123.456, double)
TEST_SPRINTF(lE_width_plus_post, "%+5lE", 123.456, double)
TEST_SPRINTF(lE_width_spac_post, "% 5lE", 123.456, double)
TEST_SPRINTF(lE_width_hash_post, "%#5lE", 123.456, double)
TEST_SPRINTF(lE_width_fzer_post, "%05lE", 123.456, double)
TEST_SPRINTF(lE_width_mins_negt, "%-5lE", -123.456, double)
TEST_SPRINTF(lE_width_plus_negt, "%+5lE", -123.456, double)
TEST_SPRINTF(lE_width_spac_negt, "% 5lE", -123.456, double)
TEST_SPRINTF(lE_width_hash_negt, "%#5lE", -123.456, double)
TEST_SPRINTF(lE_width_fzer_negt, "%05lE", -123.456, double)
TEST_SPRINTF(lE_width_mins_small, "%-5lE", -0.0000123456, double)
TEST_SPRINTF(lE_width_plus_small, "%+5lE", -0.0000123456, double)
TEST_SPRINTF(lE_width_spac_small, "% 5lE", -0.0000123456, double)
TEST_SPRINTF(lE_width_hash_small, "%#5lE", -0.0000123456, double)
TEST_SPRINTF(lE_width_fzer_small, "%05lE", -0.0000123456, double)
TEST_SPRINTF(lE_width_mins_large, "%-5lE", 123456789.0, double)
TEST_SPRINTF(lE_width_plus_large, "%+5lE", 123456789.0, double)
TEST_SPRINTF(lE_width_spac_large, "% 5lE", 123456789.0, double)
TEST_SPRINTF(lE_width_hash_large, "%#5lE", 123456789.0, double)
TEST_SPRINTF(lE_width_fzer_large, "%05lE", 123456789.0, double)

TEST_SPRINTF(lE_zrwth_plus_post, "%+0lE", 123.456, double)
TEST_SPRINTF(lE_zrwth_spac_post, "% 0lE", 123.456, double)
TEST_SPRINTF(lE_zrwth_hash_post, "%#0lE", 123.456, double)
TEST_SPRINTF(lE_zrwth_plus_negt, "%+0lE", -123.456, double)
TEST_SPRINTF(lE_zrwth_spac_negt, "% 0lE", -123.456, double)
TEST_SPRINTF(lE_zrwth_hash_negt, "%#0lE", -123.456, double)
TEST_SPRINTF(lE_zrwth_plus_small, "%+0lE", -0.0000123456, double)
TEST_SPRINTF(lE_zrwth_spac_small, "% 0lE", -0.0000123456, double)
TEST_SPRINTF(lE_zrwth_hash_small, "%#0lE", -0.0000123456, double)
TEST_SPRINTF(lE_zrwth_plus_large, "%+0lE", 123456789.0, double)
TEST_SPRINTF(lE_zrwth_spac_large, "% 0lE", 123456789.0, double)
TEST_SPRINTF(lE_zrwth_hash_large, "%#0lE", 123456789.0, double)

TEST_SPRINTF(lE_prec_mins_post, "%-.5lE", 123.456, double)
TEST_SPRINTF(lE_prec_plus_post, "%+.5lE", 123.456, double)
TEST_SPRINTF(lE_prec_spac_post, "% .5lE", 123.456, double)
TEST_SPRINTF(lE_prec_hash_post, "%#.5lE", 123.456, double)
TEST_SPRINTF(lE_prec_fzer_post, "%0.5lE", 123.456, double)
TEST_SPRINTF(lE_prec_mins_negt, "%-.5lE", -123.456, double)
TEST_SPRINTF(lE_prec_plus_negt, "%+.5lE", -123.456, double)
TEST_SPRINTF(lE_prec_spac_negt, "% .5lE", -123.456, double)
TEST_SPRINTF(lE_prec_hash_negt, "%#.5lE", -123.456, double)
TEST_SPRINTF(lE_prec_fzer_negt, "%0.5lE", -123.456, double)
TEST_SPRINTF(lE_prec_mins_small, "%-.5lE", -0.0000123456, double)
TEST_SPRINTF(lE_prec_plus_small, "%+.5lE", -0.0000123456, double)
TEST_SPRINTF(lE_prec_spac_small, "% .5lE", -0.0000123456, double)
TEST_SPRINTF(lE_prec_hash_small, "%#.5lE", -0.0000123456, double)
TEST_SPRINTF(lE_prec_fzer_small, "%0.5lE", -0.0000123456, double)
TEST_SPRINTF(lE_prec_mins_large, "%-.5lE", 123456789.0, double)
TEST_SPRINTF(lE_prec_plus_large, "%+.5lE", 123456789.0, double)
TEST_SPRINTF(lE_prec_spac_large, "% .5lE", 123456789.0, double)
TEST_SPRINTF(lE_prec_hash_large, "%#.5lE", 123456789.0, double)
TEST_SPRINTF(lE_prec_fzer_large, "%0.5lE", 123456789.0, double)

TEST_SPRINTF(lE_zrpc_mins_post, "%-.0lE", 123.456, double)
TEST_SPRINTF(lE_zrpc_plus_post, "%+.0lE", 123.456, double)
TEST_SPRINTF(lE_zrpc_spac_post, "% .0lE", 123.456, double)
TEST_SPRINTF(lE_zrpc_hash_post, "%#.0lE", 123.456, double)
TEST_SPRINTF(lE_zrpc_fzer_post, "%0.0lE", 123.456, double)
TEST_SPRINTF(lE_zrpc_mins_negt, "%-.0lE", -123.456, double)
TEST_SPRINTF(lE_zrpc_plus_negt, "%+.0lE", -123.456, double)
TEST_SPRINTF(lE_zrpc_spac_negt, "% .0lE", -123.456, double)
TEST_SPRINTF(lE_zrpc_hash_negt, "%#.0lE", -123.456, double)
TEST_SPRINTF(lE_zrpc_fzer_negt, "%0.0lE", -123.456, double)
TEST_SPRINTF(lE_zrpc_mins_small, "%-.0lE", -0.0000123456, double)
TEST_SPRINTF(lE_zrpc_plus_small, "%+.0lE", -0.0000123456, double)
TEST_SPRINTF(lE_zrpc_spac_small, "% .0lE", -0.0000123456, double)
TEST_SPRINTF(lE_zrpc_hash_small, "%#.0lE", -0.0000123456, double)
TEST_SPRINTF(lE_zrpc_fzer_small, "%0.0lE", -0.0000123456, double)
TEST_SPRINTF(lE_zrpc_mins_large, "%-.0lE", 123456789.0, double)
TEST_SPRINTF(lE_zrpc_plus_large, "%+.0lE", 123456789.0, double)
TEST_SPRINTF(lE_zrpc_spac_large, "% .0lE", 123456789.0, double)
TEST_SPRINTF(lE_zrpc_hash_large, "%#.0lE", 123456789.0, double)
TEST_SPRINTF(lE_zrpc_fzer_large, "%0.0lE", 123456789.0, double)

TEST_SPRINTF(lE_width_prec_mins_post, "%-10.5lE", 123.456, double)
TEST_SPRINTF(lE_width_prec_plus_post, "%+10.5lE", 123.456, double)
TEST_SPRINTF(lE_width_prec_spac_post, "% 10.5lE", 123.456, double)
TEST_SPRINTF(lE_width_prec_hash_post, "%#10.5lE", 123.456, double)
TEST_SPRINTF(lE_width_prec_fzer_post, "%010.5lE", 123.456, double)
TEST_SPRINTF(lE_width_prec_mins_negt, "%-10.5lE", -123.456, double)
TEST_SPRINTF(lE_width_prec_plus_negt, "%+10.5lE", -123.456, double)
TEST_SPRINTF(lE_width_prec_spac_negt, "% 10.5lE", -123.456, double)
TEST_SPRINTF(lE_width_prec_hash_negt, "%#10.5lE", -123.456, double)
TEST_SPRINTF(lE_width_prec_fzer_negt, "%010.5lE", -123.456, double)
TEST_SPRINTF(lE_width_prec_mins_small, "%-10.5lE", -0.0000123456, double)
TEST_SPRINTF(lE_width_prec_plus_small, "%+10.5lE", -0.0000123456, double)
TEST_SPRINTF(lE_width_prec_spac_small, "% 10.5lE", -0.0000123456, double)
TEST_SPRINTF(lE_width_prec_hash_small, "%#10.5lE", -0.0000123456, double)
TEST_SPRINTF(lE_width_prec_fzer_small, "%010.5lE", -0.0000123456, double)
TEST_SPRINTF(lE_width_prec_mins_large, "%-10.5lE", 123456789.0, double)
TEST_SPRINTF(lE_width_prec_plus_large, "%+10.5lE", 123456789.0, double)
TEST_SPRINTF(lE_width_prec_spac_large, "% 10.5lE", 123456789.0, double)
TEST_SPRINTF(lE_width_prec_hash_large, "%#10.5lE", 123456789.0, double)
TEST_SPRINTF(lE_width_prec_fzer_large, "%010.5lE", 123456789.0, double)

TEST_SPRINTF(lE_zrwth_zrpc_plus_post, "%+0.0lE", 123.456, double)
TEST_SPRINTF(lE_zrwth_zrpc_spac_post, "% 0.0lE", 123.456, double)
TEST_SPRINTF(lE_zrwth_zrpc_hash_post, "%#0.0lE", 123.456, double)
TEST_SPRINTF(lE_zrwth_zrpc_plus_negt, "%+0.0lE", -123.456, double)
TEST_SPRINTF(lE_zrwth_zrpc_spac_negt, "% 0.0lE", -123.456, double)
TEST_SPRINTF(lE_zrwth_zrpc_hash_negt, "%#0.0lE", -123.456, double)
TEST_SPRINTF(lE_zrwth_zrpc_plus_small, "%+0.0lE", -0.0000123456, double)
TEST_SPRINTF(lE_zrwth_zrpc_spac_small, "% 0.0lE", -0.0000123456, double)
TEST_SPRINTF(lE_zrwth_zrpc_hash_small, "%#0.0lE", -0.0000123456, double)
TEST_SPRINTF(lE_zrwth_zrpc_plus_large, "%+0.0lE", 123456789.0, double)
TEST_SPRINTF(lE_zrwth_zrpc_spac_large, "% 0.0lE", 123456789.0, double)
TEST_SPRINTF(lE_zrwth_zrpc_hash_large, "%#0.0lE", 123456789.0, double)

TEST_SPRINTF_2(lE_dynamic_width_post, "%*lE", 10, 123.456, double)
TEST_SPRINTF_2(lE_dynamic_width_negt, "%*lE", 10, -123.456, double)
TEST_SPRINTF_2(lE_dynamic_width_small, "%*lE", 10, -0.0000123456, double)
TEST_SPRINTF_2(lE_dynamic_width_large, "%*lE", 10, 123456789.0, double)

TEST_SPRINTF_2(lE_dynamic_prec_post, "%.*lE", 5, 123.456, double)
TEST_SPRINTF_2(lE_dynamic_prec_negt, "%.*lE", 5, -123.456, double)
TEST_SPRINTF_2(lE_dynamic_prec_small, "%.*lE", 5, -0.0000123456, double)
TEST_SPRINTF_2(lE_dynamic_prec_large, "%.*lE", 5, 123456789.0, double)

TEST_SPRINTF_3(lE_dynamic_width_prec_post, "%*.*lE", 10, 5, 123.456, double)
TEST_SPRINTF_3(lE_dynamic_width_prec_negt, "%*.*lE", 10, 5, -123.456, double)
TEST_SPRINTF_3(lE_dynamic_width_prec_small, "%*.*lE", 10, 5, -0.0000123456,
               double)
TEST_SPRINTF_3(lE_dynamic_width_prec_large, "%*.*lE", 10, 5, 123456789.0,
               double)

// =========================================================================

TEST_SPRINTF(lf_mins_post, "%-lf", 123.456, double)
TEST_SPRINTF(lf_plus_post, "%+lf", 123.456, double)
TEST_SPRINTF(lf_spac_post, "% lf", 123.456, double)
TEST_SPRINTF(lf_hash_post, "%#lf", 123.456, double)
TEST_SPRINTF(lf_fzer_post, "%0lf", 123.456, double)
TEST_SPRINTF(lf_mins_negt, "%-lf", -123.456, double)
TEST_SPRINTF(lf_plus_negt, "%+lf", -123.456, double)
TEST_SPRINTF(lf_spac_negt, "% lf", -123.456, double)
TEST_SPRINTF(lf_hash_negt, "%#lf", -123.456, double)
TEST_SPRINTF(lf_fzer_negt, "%0lf", -123.456, double)
TEST_SPRINTF(lf_mins_small, "%-lf", -0.0000123456, double)
TEST_SPRINTF(lf_plus_small, "%+lf", -0.0000123456, double)
TEST_SPRINTF(lf_spac_small, "% lf", -0.0000123456, double)
TEST_SPRINTF(lf_hash_small, "%#lf", -0.0000123456, double)
TEST_SPRINTF(lf_fzer_small, "%0lf", -0.0000123456, double)
TEST_SPRINTF(lf_mins_large, "%-lf", 123456789.0, double)
TEST_SPRINTF(lf_plus_large, "%+lf", 123456789.0, double)
TEST_SPRINTF(lf_spac_large, "% lf", 123456789.0, double)
TEST_SPRINTF(lf_hash_large, "%#lf", 123456789.0, double)
TEST_SPRINTF(lf_fzer_large, "%0lf", 123456789.0, double)

TEST_SPRINTF(lf_width_post, "%5lf", 123.456, double)
TEST_SPRINTF(lf_zrpc_post, "%.0lf", 123.456, double)
TEST_SPRINTF(lf_prec_post, "%.5lf", 123.456, double)
TEST_SPRINTF(lf_width_negt, "%5lf", -123.456, double)
TEST_SPRINTF(lf_zrpc_negt, "%.0lf", -123.456, double)
TEST_SPRINTF(lf_prec_negt, "%.5lf", -123.456, double)
TEST_SPRINTF(lf_width_small, "%5lf", -0.0000123456, double)
TEST_SPRINTF(lf_zrpc_small, "%.0lf", -0.0000123456, double)
TEST_SPRINTF(lf_prec_small, "%.5lf", -0.0000123456, double)
TEST_SPRINTF(lf_width_large, "%5lf", 123456789.0, double)
TEST_SPRINTF(lf_zrpc_large, "%.0lf", 123456789.0, double)
TEST_SPRINTF(lf_prec_large, "%.5lf", 123456789.0, double)

TEST_SPRINTF(lf_width_prec_post, "%10.5lf", 123.456, double)
TEST_SPRINTF(lf_width_prec_negt, "%10.5lf", -123.456, double)
TEST_SPRINTF(lf_width_prec_small, "%10.5lf", -0.0000123456, double)
TEST_SPRINTF(lf_width_prec_large, "%10.5lf", 123456789.0, double)

TEST_SPRINTF(lf_width_mins_post, "%-5lf", 123.456, double)
TEST_SPRINTF(lf_width_plus_post, "%+5lf", 123.456, double)
TEST_SPRINTF(lf_width_spac_post, "% 5lf", 123.456, double)
TEST_SPRINTF(lf_width_hash_post, "%#5lf", 123.456, double)
TEST_SPRINTF(lf_width_fzer_post, "%05lf", 123.456, double)
TEST_SPRINTF(lf_width_mins_negt, "%-5lf", -123.456, double)
TEST_SPRINTF(lf_width_plus_negt, "%+5lf", -123.456, double)
TEST_SPRINTF(lf_width_spac_negt, "% 5lf", -123.456, double)
TEST_SPRINTF(lf_width_hash_negt, "%#5lf", -123.456, double)
TEST_SPRINTF(lf_width_fzer_negt, "%05lf", -123.456, double)
TEST_SPRINTF(lf_width_mins_small, "%-5lf", -0.0000123456, double)
TEST_SPRINTF(lf_width_plus_small, "%+5lf", -0.0000123456, double)
TEST_SPRINTF(lf_width_spac_small, "% 5lf", -0.0000123456, double)
TEST_SPRINTF(lf_width_hash_small, "%#5lf", -0.0000123456, double)
TEST_SPRINTF(lf_width_fzer_small, "%05lf", -0.0000123456, double)
TEST_SPRINTF(lf_width_mins_large, "%-5lf", 123456789.0, double)
TEST_SPRINTF(lf_width_plus_large, "%+5lf", 123456789.0, double)
TEST_SPRINTF(lf_width_spac_large, "% 5lf", 123456789.0, double)
TEST_SPRINTF(lf_width_hash_large, "%#5lf", 123456789.0, double)
TEST_SPRINTF(lf_width_fzer_large, "%05lf", 123456789.0, double)

TEST_SPRINTF(lf_zrwth_plus_post, "%+0lf", 123.456, double)
TEST_SPRINTF(lf_zrwth_spac_post, "% 0lf", 123.456, double)
TEST_SPRINTF(lf_zrwth_hash_post, "%#0lf", 123.456, double)
TEST_SPRINTF(lf_zrwth_plus_negt, "%+0lf", -123.456, double)
TEST_SPRINTF(lf_zrwth_spac_negt, "% 0lf", -123.456, double)
TEST_SPRINTF(lf_zrwth_hash_negt, "%#0lf", -123.456, double)
TEST_SPRINTF(lf_zrwth_plus_small, "%+0lf", -0.0000123456, double)
TEST_SPRINTF(lf_zrwth_spac_small, "% 0lf", -0.0000123456, double)
TEST_SPRINTF(lf_zrwth_hash_small, "%#0lf", -0.0000123456, double)
TEST_SPRINTF(lf_zrwth_plus_large, "%+0lf", 123456789.0, double)
TEST_SPRINTF(lf_zrwth_spac_large, "% 0lf", 123456789.0, double)
TEST_SPRINTF(lf_zrwth_hash_large, "%#0lf", 123456789.0, double)

TEST_SPRINTF(lf_prec_mins_post, "%-.5lf", 123.456, double)
TEST_SPRINTF(lf_prec_plus_post, "%+.5lf", 123.456, double)
TEST_SPRINTF(lf_prec_spac_post, "% .5lf", 123.456, double)
TEST_SPRINTF(lf_prec_hash_post, "%#.5lf", 123.456, double)
TEST_SPRINTF(lf_prec_fzer_post, "%0.5lf", 123.456, double)
TEST_SPRINTF(lf_prec_mins_negt, "%-.5lf", -123.456, double)
TEST_SPRINTF(lf_prec_plus_negt, "%+.5lf", -123.456, double)
TEST_SPRINTF(lf_prec_spac_negt, "% .5lf", -123.456, double)
TEST_SPRINTF(lf_prec_hash_negt, "%#.5lf", -123.456, double)
TEST_SPRINTF(lf_prec_fzer_negt, "%0.5lf", -123.456, double)
TEST_SPRINTF(lf_prec_mins_small, "%-.5lf", -0.0000123456, double)
TEST_SPRINTF(lf_prec_plus_small, "%+.5lf", -0.0000123456, double)
TEST_SPRINTF(lf_prec_spac_small, "% .5lf", -0.0000123456, double)
TEST_SPRINTF(lf_prec_hash_small, "%#.5lf", -0.0000123456, double)
TEST_SPRINTF(lf_prec_fzer_small, "%0.5lf", -0.0000123456, double)
TEST_SPRINTF(lf_prec_mins_large, "%-.5lf", 123456789.0, double)
TEST_SPRINTF(lf_prec_plus_large, "%+.5lf", 123456789.0, double)
TEST_SPRINTF(lf_prec_spac_large, "% .5lf", 123456789.0, double)
TEST_SPRINTF(lf_prec_hash_large, "%#.5lf", 123456789.0, double)
TEST_SPRINTF(lf_prec_fzer_large, "%0.5lf", 123456789.0, double)

TEST_SPRINTF(lf_zrpc_mins_post, "%-.0lf", 123.456, double)
TEST_SPRINTF(lf_zrpc_plus_post, "%+.0lf", 123.456, double)
TEST_SPRINTF(lf_zrpc_spac_post, "% .0lf", 123.456, double)
TEST_SPRINTF(lf_zrpc_hash_post, "%#.0lf", 123.456, double)
TEST_SPRINTF(lf_zrpc_fzer_post, "%0.0lf", 123.456, double)
TEST_SPRINTF(lf_zrpc_mins_negt, "%-.0lf", -123.456, double)
TEST_SPRINTF(lf_zrpc_plus_negt, "%+.0lf", -123.456, double)
TEST_SPRINTF(lf_zrpc_spac_negt, "% .0lf", -123.456, double)
TEST_SPRINTF(lf_zrpc_hash_negt, "%#.0lf", -123.456, double)
TEST_SPRINTF(lf_zrpc_fzer_negt, "%0.0lf", -123.456, double)
TEST_SPRINTF(lf_zrpc_mins_small, "%-.0lf", -0.0000123456, double)
TEST_SPRINTF(lf_zrpc_plus_small, "%+.0lf", -0.0000123456, double)
TEST_SPRINTF(lf_zrpc_spac_small, "% .0lf", -0.0000123456, double)
TEST_SPRINTF(lf_zrpc_hash_small, "%#.0lf", -0.0000123456, double)
TEST_SPRINTF(lf_zrpc_fzer_small, "%0.0lf", -0.0000123456, double)
TEST_SPRINTF(lf_zrpc_mins_large, "%-.0lf", 123456789.0, double)
TEST_SPRINTF(lf_zrpc_plus_large, "%+.0lf", 123456789.0, double)
TEST_SPRINTF(lf_zrpc_spac_large, "% .0lf", 123456789.0, double)
TEST_SPRINTF(lf_zrpc_hash_large, "%#.0lf", 123456789.0, double)
TEST_SPRINTF(lf_zrpc_fzer_large, "%0.0lf", 123456789.0, double)

TEST_SPRINTF(lf_width_prec_mins_post, "%-10.5lf", 123.456, double)
TEST_SPRINTF(lf_width_prec_plus_post, "%+10.5lf", 123.456, double)
TEST_SPRINTF(lf_width_prec_spac_post, "% 10.5lf", 123.456, double)
TEST_SPRINTF(lf_width_prec_hash_post, "%#10.5lf", 123.456, double)
TEST_SPRINTF(lf_width_prec_fzer_post, "%010.5lf", 123.456, double)
TEST_SPRINTF(lf_width_prec_mins_negt, "%-10.5lf", -123.456, double)
TEST_SPRINTF(lf_width_prec_plus_negt, "%+10.5lf", -123.456, double)
TEST_SPRINTF(lf_width_prec_spac_negt, "% 10.5lf", -123.456, double)
TEST_SPRINTF(lf_width_prec_hash_negt, "%#10.5lf", -123.456, double)
TEST_SPRINTF(lf_width_prec_fzer_negt, "%010.5lf", -123.456, double)
TEST_SPRINTF(lf_width_prec_mins_small, "%-10.5lf", -0.0000123456, double)
TEST_SPRINTF(lf_width_prec_plus_small, "%+10.5lf", -0.0000123456, double)
TEST_SPRINTF(lf_width_prec_spac_small, "% 10.5lf", -0.0000123456, double)
TEST_SPRINTF(lf_width_prec_hash_small, "%#10.5lf", -0.0000123456, double)
TEST_SPRINTF(lf_width_prec_fzer_small, "%010.5lf", -0.0000123456, double)
TEST_SPRINTF(lf_width_prec_mins_large, "%-10.5lf", 123456789.0, double)
TEST_SPRINTF(lf_width_prec_plus_large, "%+10.5lf", 123456789.0, double)
TEST_SPRINTF(lf_width_prec_spac_large, "% 10.5lf", 123456789.0, double)
TEST_SPRINTF(lf_width_prec_hash_large, "%#10.5lf", 123456789.0, double)
TEST_SPRINTF(lf_width_prec_fzer_large, "%010.5lf", 123456789.0, double)

TEST_SPRINTF(lf_zrwth_zrpc_plus_post, "%+0.0lf", 123.456, double)
TEST_SPRINTF(lf_zrwth_zrpc_spac_post, "% 0.0lf", 123.456, double)
TEST_SPRINTF(lf_zrwth_zrpc_hash_post, "%#0.0lf", 123.456, double)
TEST_SPRINTF(lf_zrwth_zrpc_plus_negt, "%+0.0lf", -123.456, double)
TEST_SPRINTF(lf_zrwth_zrpc_spac_negt, "% 0.0lf", -123.456, double)
TEST_SPRINTF(lf_zrwth_zrpc_hash_negt, "%#0.0lf", -123.456, double)
TEST_SPRINTF(lf_zrwth_zrpc_plus_small, "%+0.0lf", -0.0000123456, double)
TEST_SPRINTF(lf_zrwth_zrpc_spac_small, "% 0.0lf", -0.0000123456, double)
TEST_SPRINTF(lf_zrwth_zrpc_hash_small, "%#0.0lf", -0.0000123456, double)
TEST_SPRINTF(lf_zrwth_zrpc_plus_large, "%+0.0lf", 123456789.0, double)
TEST_SPRINTF(lf_zrwth_zrpc_spac_large, "% 0.0lf", 123456789.0, double)
TEST_SPRINTF(lf_zrwth_zrpc_hash_large, "%#0.0lf", 123456789.0, double)

TEST_SPRINTF_2(lf_dynamic_width_post, "%*lf", 10, 123.456, double)
TEST_SPRINTF_2(lf_dynamic_width_negt, "%*lf", 10, -123.456, double)
TEST_SPRINTF_2(lf_dynamic_width_small, "%*lf", 10, -0.0000123456, double)
TEST_SPRINTF_2(lf_dynamic_width_large, "%*lf", 10, 123456789.0, double)

TEST_SPRINTF_2(lf_dynamic_prec_post, "%.*lf", 5, 123.456, double)
TEST_SPRINTF_2(lf_dynamic_prec_negt, "%.*lf", 5, -123.456, double)
TEST_SPRINTF_2(lf_dynamic_prec_small, "%.*lf", 5, -0.0000123456, double)
TEST_SPRINTF_2(lf_dynamic_prec_large, "%.*lf", 5, 123456789.0, double)

TEST_SPRINTF_3(lf_dynamic_width_prec_post, "%*.*lf", 10, 5, 123.456, double)
TEST_SPRINTF_3(lf_dynamic_width_prec_negt, "%*.*lf", 10, 5, -123.456, double)
TEST_SPRINTF_3(lf_dynamic_width_prec_small, "%*.*lf", 10, 5, -0.0000123456,
               double)
TEST_SPRINTF_3(lf_dynamic_width_prec_large, "%*.*lf", 10, 5, 123456789.0,
               double)

// =========================================================================

TEST_SPRINTF(lg_mins_post, "%-lg", 123.456, double)
TEST_SPRINTF(lg_plus_post, "%+lg", 123.456, double)
TEST_SPRINTF(lg_spac_post, "% lg", 123.456, double)
TEST_SPRINTF(lg_hash_post, "%#lg", 123.456, double)
TEST_SPRINTF(lg_fzer_post, "%0lg", 123.456, double)
TEST_SPRINTF(lg_mins_negt, "%-lg", -123.456, double)
TEST_SPRINTF(lg_plus_negt, "%+lg", -123.456, double)
TEST_SPRINTF(lg_spac_negt, "% lg", -123.456, double)
TEST_SPRINTF(lg_hash_negt, "%#lg", -123.456, double)
TEST_SPRINTF(lg_fzer_negt, "%0lg", -123.456, double)
TEST_SPRINTF(lg_mins_small, "%-lg", -0.0000123456, double)
TEST_SPRINTF(lg_plus_small, "%+lg", -0.0000123456, double)
TEST_SPRINTF(lg_spac_small, "% lg", -0.0000123456, double)
TEST_SPRINTF(lg_hash_small, "%#lg", -0.0000123456, double)
TEST_SPRINTF(lg_fzer_small, "%0lg", -0.0000123456, double)
TEST_SPRINTF(lg_mins_large, "%-lg", 123456789.0, double)
TEST_SPRINTF(lg_plus_large, "%+lg", 123456789.0, double)
TEST_SPRINTF(lg_spac_large, "% lg", 123456789.0, double)
TEST_SPRINTF(lg_hash_large, "%#lg", 123456789.0, double)
TEST_SPRINTF(lg_fzer_large, "%0lg", 123456789.0, double)

TEST_SPRINTF(lg_width_post, "%5lg", 123.456, double)
TEST_SPRINTF(lg_zrpc_post, "%.0lg", 123.456, double)
TEST_SPRINTF(lg_prec_post, "%.5lg", 123.456, double)
TEST_SPRINTF(lg_width_negt, "%5lg", -123.456, double)
TEST_SPRINTF(lg_zrpc_negt, "%.0lg", -123.456, double)
TEST_SPRINTF(lg_prec_negt, "%.5lg", -123.456, double)
TEST_SPRINTF(lg_width_small, "%5lg", -0.0000123456, double)
TEST_SPRINTF(lg_zrpc_small, "%.0lg", -0.0000123456, double)
TEST_SPRINTF(lg_prec_small, "%.5lg", -0.0000123456, double)
TEST_SPRINTF(lg_width_large, "%5lg", 123456789.0, double)
TEST_SPRINTF(lg_zrpc_large, "%.0lg", 123456789.0, double)
TEST_SPRINTF(lg_prec_large, "%.5lg", 123456789.0, double)

TEST_SPRINTF(lg_width_prec_post, "%10.5lg", 123.456, double)
TEST_SPRINTF(lg_width_prec_negt, "%10.5lg", -123.456, double)
TEST_SPRINTF(lg_width_prec_small, "%10.5lg", -0.0000123456, double)
TEST_SPRINTF(lg_width_prec_large, "%10.5lg", 123456789.0, double)

TEST_SPRINTF(lg_width_mins_post, "%-5lg", 123.456, double)
TEST_SPRINTF(lg_width_plus_post, "%+5lg", 123.456, double)
TEST_SPRINTF(lg_width_spac_post, "% 5lg", 123.456, double)
TEST_SPRINTF(lg_width_hash_post, "%#5lg", 123.456, double)
TEST_SPRINTF(lg_width_fzer_post, "%05lg", 123.456, double)
TEST_SPRINTF(lg_width_mins_negt, "%-5lg", -123.456, double)
TEST_SPRINTF(lg_width_plus_negt, "%+5lg", -123.456, double)
TEST_SPRINTF(lg_width_spac_negt, "% 5lg", -123.456, double)
TEST_SPRINTF(lg_width_hash_negt, "%#5lg", -123.456, double)
TEST_SPRINTF(lg_width_fzer_negt, "%05lg", -123.456, double)
TEST_SPRINTF(lg_width_mins_small, "%-5lg", -0.0000123456, double)
TEST_SPRINTF(lg_width_plus_small, "%+5lg", -0.0000123456, double)
TEST_SPRINTF(lg_width_spac_small, "% 5lg", -0.0000123456, double)
TEST_SPRINTF(lg_width_hash_small, "%#5lg", -0.0000123456, double)
TEST_SPRINTF(lg_width_fzer_small, "%05lg", -0.0000123456, double)
TEST_SPRINTF(lg_width_mins_large, "%-5lg", 123456789.0, double)
TEST_SPRINTF(lg_width_plus_large, "%+5lg", 123456789.0, double)
TEST_SPRINTF(lg_width_spac_large, "% 5lg", 123456789.0, double)
TEST_SPRINTF(lg_width_hash_large, "%#5lg", 123456789.0, double)
TEST_SPRINTF(lg_width_fzer_large, "%05lg", 123456789.0, double)

TEST_SPRINTF(lg_zrwth_plus_post, "%+0lg", 123.456, double)
TEST_SPRINTF(lg_zrwth_spac_post, "% 0lg", 123.456, double)
TEST_SPRINTF(lg_zrwth_hash_post, "%#0lg", 123.456, double)
TEST_SPRINTF(lg_zrwth_plus_negt, "%+0lg", -123.456, double)
TEST_SPRINTF(lg_zrwth_spac_negt, "% 0lg", -123.456, double)
TEST_SPRINTF(lg_zrwth_hash_negt, "%#0lg", -123.456, double)
TEST_SPRINTF(lg_zrwth_plus_small, "%+0lg", -0.0000123456, double)
TEST_SPRINTF(lg_zrwth_spac_small, "% 0lg", -0.0000123456, double)
TEST_SPRINTF(lg_zrwth_hash_small, "%#0lg", -0.0000123456, double)
TEST_SPRINTF(lg_zrwth_plus_large, "%+0lg", 123456789.0, double)
TEST_SPRINTF(lg_zrwth_spac_large, "% 0lg", 123456789.0, double)
TEST_SPRINTF(lg_zrwth_hash_large, "%#0lg", 123456789.0, double)

TEST_SPRINTF(lg_prec_mins_post, "%-.5lg", 123.456, double)
TEST_SPRINTF(lg_prec_plus_post, "%+.5lg", 123.456, double)
TEST_SPRINTF(lg_prec_spac_post, "% .5lg", 123.456, double)
TEST_SPRINTF(lg_prec_hash_post, "%#.5lg", 123.456, double)
TEST_SPRINTF(lg_prec_fzer_post, "%0.5lg", 123.456, double)
TEST_SPRINTF(lg_prec_mins_negt, "%-.5lg", -123.456, double)
TEST_SPRINTF(lg_prec_plus_negt, "%+.5lg", -123.456, double)
TEST_SPRINTF(lg_prec_spac_negt, "% .5lg", -123.456, double)
TEST_SPRINTF(lg_prec_hash_negt, "%#.5lg", -123.456, double)
TEST_SPRINTF(lg_prec_fzer_negt, "%0.5lg", -123.456, double)
TEST_SPRINTF(lg_prec_mins_small, "%-.5lg", -0.0000123456, double)
TEST_SPRINTF(lg_prec_plus_small, "%+.5lg", -0.0000123456, double)
TEST_SPRINTF(lg_prec_spac_small, "% .5lg", -0.0000123456, double)
TEST_SPRINTF(lg_prec_hash_small, "%#.5lg", -0.0000123456, double)
TEST_SPRINTF(lg_prec_fzer_small, "%0.5lg", -0.0000123456, double)
TEST_SPRINTF(lg_prec_mins_large, "%-.5lg", 123456789.0, double)
TEST_SPRINTF(lg_prec_plus_large, "%+.5lg", 123456789.0, double)
TEST_SPRINTF(lg_prec_spac_large, "% .5lg", 123456789.0, double)
TEST_SPRINTF(lg_prec_hash_large, "%#.5lg", 123456789.0, double)
TEST_SPRINTF(lg_prec_fzer_large, "%0.5lg", 123456789.0, double)

TEST_SPRINTF(lg_zrpc_mins_post, "%-.0lg", 123.456, double)
TEST_SPRINTF(lg_zrpc_plus_post, "%+.0lg", 123.456, double)
TEST_SPRINTF(lg_zrpc_spac_post, "% .0lg", 123.456, double)
TEST_SPRINTF(lg_zrpc_hash_post, "%#.0lg", 123.456, double)
TEST_SPRINTF(lg_zrpc_fzer_post, "%0.0lg", 123.456, double)
TEST_SPRINTF(lg_zrpc_mins_negt, "%-.0lg", -123.456, double)
TEST_SPRINTF(lg_zrpc_plus_negt, "%+.0lg", -123.456, double)
TEST_SPRINTF(lg_zrpc_spac_negt, "% .0lg", -123.456, double)
TEST_SPRINTF(lg_zrpc_hash_negt, "%#.0lg", -123.456, double)
TEST_SPRINTF(lg_zrpc_fzer_negt, "%0.0lg", -123.456, double)
TEST_SPRINTF(lg_zrpc_mins_small, "%-.0lg", -0.0000123456, double)
TEST_SPRINTF(lg_zrpc_plus_small, "%+.0lg", -0.0000123456, double)
TEST_SPRINTF(lg_zrpc_spac_small, "% .0lg", -0.0000123456, double)
TEST_SPRINTF(lg_zrpc_hash_small, "%#.0lg", -0.0000123456, double)
TEST_SPRINTF(lg_zrpc_fzer_small, "%0.0lg", -0.0000123456, double)
TEST_SPRINTF(lg_zrpc_mins_large, "%-.0lg", 123456789.0, double)
TEST_SPRINTF(lg_zrpc_plus_large, "%+.0lg", 123456789.0, double)
TEST_SPRINTF(lg_zrpc_spac_large, "% .0lg", 123456789.0, double)
TEST_SPRINTF(lg_zrpc_hash_large, "%#.0lg", 123456789.0, double)
TEST_SPRINTF(lg_zrpc_fzer_large, "%0.0lg", 123456789.0, double)

TEST_SPRINTF(lg_width_prec_mins_post, "%-10.5lg", 123.456, double)
TEST_SPRINTF(lg_width_prec_plus_post, "%+10.5lg", 123.456, double)
TEST_SPRINTF(lg_width_prec_spac_post, "% 10.5lg", 123.456, double)
TEST_SPRINTF(lg_width_prec_hash_post, "%#10.5lg", 123.456, double)
TEST_SPRINTF(lg_width_prec_fzer_post, "%010.5lg", 123.456, double)
TEST_SPRINTF(lg_width_prec_mins_negt, "%-10.5lg", -123.456, double)
TEST_SPRINTF(lg_width_prec_plus_negt, "%+10.5lg", -123.456, double)
TEST_SPRINTF(lg_width_prec_spac_negt, "% 10.5lg", -123.456, double)
TEST_SPRINTF(lg_width_prec_hash_negt, "%#10.5lg", -123.456, double)
TEST_SPRINTF(lg_width_prec_fzer_negt, "%010.5lg", -123.456, double)
TEST_SPRINTF(lg_width_prec_mins_small, "%-10.5lg", -0.0000123456, double)
TEST_SPRINTF(lg_width_prec_plus_small, "%+10.5lg", -0.0000123456, double)
TEST_SPRINTF(lg_width_prec_spac_small, "% 10.5lg", -0.0000123456, double)
TEST_SPRINTF(lg_width_prec_hash_small, "%#10.5lg", -0.0000123456, double)
TEST_SPRINTF(lg_width_prec_fzer_small, "%010.5lg", -0.0000123456, double)
TEST_SPRINTF(lg_width_prec_mins_large, "%-10.5lg", 123456789.0, double)
TEST_SPRINTF(lg_width_prec_plus_large, "%+10.5lg", 123456789.0, double)
TEST_SPRINTF(lg_width_prec_spac_large, "% 10.5lg", 123456789.0, double)
TEST_SPRINTF(lg_width_prec_hash_large, "%#10.5lg", 123456789.0, double)
TEST_SPRINTF(lg_width_prec_fzer_large, "%010.5lg", 123456789.0, double)

TEST_SPRINTF(lg_zrwth_zrpc_plus_post, "%+0.0lg", 123.456, double)
TEST_SPRINTF(lg_zrwth_zrpc_spac_post, "% 0.0lg", 123.456, double)
TEST_SPRINTF(lg_zrwth_zrpc_hash_post, "%#0.0lg", 123.456, double)
TEST_SPRINTF(lg_zrwth_zrpc_plus_negt, "%+0.0lg", -123.456, double)
TEST_SPRINTF(lg_zrwth_zrpc_spac_negt, "% 0.0lg", -123.456, double)
TEST_SPRINTF(lg_zrwth_zrpc_hash_negt, "%#0.0lg", -123.456, double)
TEST_SPRINTF(lg_zrwth_zrpc_plus_small, "%+0.0lg", -0.0000123456, double)
TEST_SPRINTF(lg_zrwth_zrpc_spac_small, "% 0.0lg", -0.0000123456, double)
TEST_SPRINTF(lg_zrwth_zrpc_hash_small, "%#0.0lg", -0.0000123456, double)
TEST_SPRINTF(lg_zrwth_zrpc_plus_large, "%+0.0lg", 123456789.0, double)
TEST_SPRINTF(lg_zrwth_zrpc_spac_large, "% 0.0lg", 123456789.0, double)
TEST_SPRINTF(lg_zrwth_zrpc_hash_large, "%#0.0lg", 123456789.0, double)

TEST_SPRINTF_2(lg_dynamic_width_post, "%*lg", 10, 123.456, double)
TEST_SPRINTF_2(lg_dynamic_width_negt, "%*lg", 10, -123.456, double)
TEST_SPRINTF_2(lg_dynamic_width_small, "%*lg", 10, -0.0000123456, double)
TEST_SPRINTF_2(lg_dynamic_width_large, "%*lg", 10, 123456789.0, double)

TEST_SPRINTF_2(lg_dynamic_prec_post, "%.*lg", 5, 123.456, double)
TEST_SPRINTF_2(lg_dynamic_prec_negt, "%.*lg", 5, -123.456, double)
TEST_SPRINTF_2(lg_dynamic_prec_small, "%.*lg", 5, -0.0000123456, double)
TEST_SPRINTF_2(lg_dynamic_prec_large, "%.*lg", 5, 123456789.0, double)

TEST_SPRINTF_3(lg_dynamic_width_prec_post, "%*.*lg", 10, 5, 123.456, double)
TEST_SPRINTF_3(lg_dynamic_width_prec_negt, "%*.*lg", 10, 5, -123.456, double)
TEST_SPRINTF_3(lg_dynamic_width_prec_small, "%*.*lg", 10, 5, -0.0000123456,
               double)
TEST_SPRINTF_3(lg_dynamic_width_prec_large, "%*.*lg", 10, 5, 123456789.0,
               double)

// =========================================================================

TEST_SPRINTF(lG_mins_post, "%-lG", 123.456, double)
TEST_SPRINTF(lG_plus_post, "%+lG", 123.456, double)
TEST_SPRINTF(lG_spac_post, "% lG", 123.456, double)
TEST_SPRINTF(lG_hash_post, "%#lG", 123.456, double)
TEST_SPRINTF(lG_fzer_post, "%0lG", 123.456, double)
TEST_SPRINTF(lG_mins_negt, "%-lG", -123.456, double)
TEST_SPRINTF(lG_plus_negt, "%+lG", -123.456, double)
TEST_SPRINTF(lG_spac_negt, "% lG", -123.456, double)
TEST_SPRINTF(lG_hash_negt, "%#lG", -123.456, double)
TEST_SPRINTF(lG_fzer_negt, "%0lG", -123.456, double)
TEST_SPRINTF(lG_mins_small, "%-lG", -0.0000123456, double)
TEST_SPRINTF(lG_plus_small, "%+lG", -0.0000123456, double)
TEST_SPRINTF(lG_spac_small, "% lG", -0.0000123456, double)
TEST_SPRINTF(lG_hash_small, "%#lG", -0.0000123456, double)
TEST_SPRINTF(lG_fzer_small, "%0lG", -0.0000123456, double)
TEST_SPRINTF(lG_mins_large, "%-lG", 123456789.0, double)
TEST_SPRINTF(lG_plus_large, "%+lG", 123456789.0, double)
TEST_SPRINTF(lG_spac_large, "% lG", 123456789.0, double)
TEST_SPRINTF(lG_hash_large, "%#lG", 123456789.0, double)
TEST_SPRINTF(lG_fzer_large, "%0lG", 123456789.0, double)

TEST_SPRINTF(lG_width_post, "%5lG", 123.456, double)
TEST_SPRINTF(lG_zrpc_post, "%.0lG", 123.456, double)
TEST_SPRINTF(lG_prec_post, "%.5lG", 123.456, double)
TEST_SPRINTF(lG_width_negt, "%5lG", -123.456, double)
TEST_SPRINTF(lG_zrpc_negt, "%.0lG", -123.456, double)
TEST_SPRINTF(lG_prec_negt, "%.5lG", -123.456, double)
TEST_SPRINTF(lG_width_small, "%5lG", -0.0000123456, double)
TEST_SPRINTF(lG_zrpc_small, "%.0lG", -0.0000123456, double)
TEST_SPRINTF(lG_prec_small, "%.5lG", -0.0000123456, double)
TEST_SPRINTF(lG_width_large, "%5lG", 123456789.0, double)
TEST_SPRINTF(lG_zrpc_large, "%.0lG", 123456789.0, double)
TEST_SPRINTF(lG_prec_large, "%.5lG", 123456789.0, double)

TEST_SPRINTF(lG_width_prec_post, "%10.5lG", 123.456, double)
TEST_SPRINTF(lG_width_prec_negt, "%10.5lG", -123.456, double)
TEST_SPRINTF(lG_width_prec_small, "%10.5lG", -0.0000123456, double)
TEST_SPRINTF(lG_width_prec_large, "%10.5lG", 123456789.0, double)

TEST_SPRINTF(lG_width_mins_post, "%-5lG", 123.456, double)
TEST_SPRINTF(lG_width_plus_post, "%+5lG", 123.456, double)
TEST_SPRINTF(lG_width_spac_post, "% 5lG", 123.456, double)
TEST_SPRINTF(lG_width_hash_post, "%#5lG", 123.456, double)
TEST_SPRINTF(lG_width_fzer_post, "%05lG", 123.456, double)
TEST_SPRINTF(lG_width_mins_negt, "%-5lG", -123.456, double)
TEST_SPRINTF(lG_width_plus_negt, "%+5lG", -123.456, double)
TEST_SPRINTF(lG_width_spac_negt, "% 5lG", -123.456, double)
TEST_SPRINTF(lG_width_hash_negt, "%#5lG", -123.456, double)
TEST_SPRINTF(lG_width_fzer_negt, "%05lG", -123.456, double)
TEST_SPRINTF(lG_width_mins_small, "%-5lG", -0.0000123456, double)
TEST_SPRINTF(lG_width_plus_small, "%+5lG", -0.0000123456, double)
TEST_SPRINTF(lG_width_spac_small, "% 5lG", -0.0000123456, double)
TEST_SPRINTF(lG_width_hash_small, "%#5lG", -0.0000123456, double)
TEST_SPRINTF(lG_width_fzer_small, "%05lG", -0.0000123456, double)
TEST_SPRINTF(lG_width_mins_large, "%-5lG", 123456789.0, double)
TEST_SPRINTF(lG_width_plus_large, "%+5lG", 123456789.0, double)
TEST_SPRINTF(lG_width_spac_large, "% 5lG", 123456789.0, double)
TEST_SPRINTF(lG_width_hash_large, "%#5lG", 123456789.0, double)
TEST_SPRINTF(lG_width_fzer_large, "%05lG", 123456789.0, double)

TEST_SPRINTF(lG_zrwth_plus_post, "%+0lG", 123.456, double)
TEST_SPRINTF(lG_zrwth_spac_post, "% 0lG", 123.456, double)
TEST_SPRINTF(lG_zrwth_hash_post, "%#0lG", 123.456, double)
TEST_SPRINTF(lG_zrwth_plus_negt, "%+0lG", -123.456, double)
TEST_SPRINTF(lG_zrwth_spac_negt, "% 0lG", -123.456, double)
TEST_SPRINTF(lG_zrwth_hash_negt, "%#0lG", -123.456, double)
TEST_SPRINTF(lG_zrwth_plus_small, "%+0lG", -0.0000123456, double)
TEST_SPRINTF(lG_zrwth_spac_small, "% 0lG", -0.0000123456, double)
TEST_SPRINTF(lG_zrwth_hash_small, "%#0lG", -0.0000123456, double)
TEST_SPRINTF(lG_zrwth_plus_large, "%+0lG", 123456789.0, double)
TEST_SPRINTF(lG_zrwth_spac_large, "% 0lG", 123456789.0, double)
TEST_SPRINTF(lG_zrwth_hash_large, "%#0lG", 123456789.0, double)

TEST_SPRINTF(lG_prec_mins_post, "%-.5lG", 123.456, double)
TEST_SPRINTF(lG_prec_plus_post, "%+.5lG", 123.456, double)
TEST_SPRINTF(lG_prec_spac_post, "% .5lG", 123.456, double)
TEST_SPRINTF(lG_prec_hash_post, "%#.5lG", 123.456, double)
TEST_SPRINTF(lG_prec_fzer_post, "%0.5lG", 123.456, double)
TEST_SPRINTF(lG_prec_mins_negt, "%-.5lG", -123.456, double)
TEST_SPRINTF(lG_prec_plus_negt, "%+.5lG", -123.456, double)
TEST_SPRINTF(lG_prec_spac_negt, "% .5lG", -123.456, double)
TEST_SPRINTF(lG_prec_hash_negt, "%#.5lG", -123.456, double)
TEST_SPRINTF(lG_prec_fzer_negt, "%0.5lG", -123.456, double)
TEST_SPRINTF(lG_prec_mins_small, "%-.5lG", -0.0000123456, double)
TEST_SPRINTF(lG_prec_plus_small, "%+.5lG", -0.0000123456, double)
TEST_SPRINTF(lG_prec_spac_small, "% .5lG", -0.0000123456, double)
TEST_SPRINTF(lG_prec_hash_small, "%#.5lG", -0.0000123456, double)
TEST_SPRINTF(lG_prec_fzer_small, "%0.5lG", -0.0000123456, double)
TEST_SPRINTF(lG_prec_mins_large, "%-.5lG", 123456789.0, double)
TEST_SPRINTF(lG_prec_plus_large, "%+.5lG", 123456789.0, double)
TEST_SPRINTF(lG_prec_spac_large, "% .5lG", 123456789.0, double)
TEST_SPRINTF(lG_prec_hash_large, "%#.5lG", 123456789.0, double)
TEST_SPRINTF(lG_prec_fzer_large, "%0.5lG", 123456789.0, double)

TEST_SPRINTF(lG_zrpc_mins_post, "%-.0lG", 123.456, double)
TEST_SPRINTF(lG_zrpc_plus_post, "%+.0lG", 123.456, double)
TEST_SPRINTF(lG_zrpc_spac_post, "% .0lG", 123.456, double)
TEST_SPRINTF(lG_zrpc_hash_post, "%#.0lG", 123.456, double)
TEST_SPRINTF(lG_zrpc_fzer_post, "%0.0lG", 123.456, double)
TEST_SPRINTF(lG_zrpc_mins_negt, "%-.0lG", -123.456, double)
TEST_SPRINTF(lG_zrpc_plus_negt, "%+.0lG", -123.456, double)
TEST_SPRINTF(lG_zrpc_spac_negt, "% .0lG", -123.456, double)
TEST_SPRINTF(lG_zrpc_hash_negt, "%#.0lG", -123.456, double)
TEST_SPRINTF(lG_zrpc_fzer_negt, "%0.0lG", -123.456, double)
TEST_SPRINTF(lG_zrpc_mins_small, "%-.0lG", -0.0000123456, double)
TEST_SPRINTF(lG_zrpc_plus_small, "%+.0lG", -0.0000123456, double)
TEST_SPRINTF(lG_zrpc_spac_small, "% .0lG", -0.0000123456, double)
TEST_SPRINTF(lG_zrpc_hash_small, "%#.0lG", -0.0000123456, double)
TEST_SPRINTF(lG_zrpc_fzer_small, "%0.0lG", -0.0000123456, double)
TEST_SPRINTF(lG_zrpc_mins_large, "%-.0lG", 123456789.0, double)
TEST_SPRINTF(lG_zrpc_plus_large, "%+.0lG", 123456789.0, double)
TEST_SPRINTF(lG_zrpc_spac_large, "% .0lG", 123456789.0, double)
TEST_SPRINTF(lG_zrpc_hash_large, "%#.0lG", 123456789.0, double)
TEST_SPRINTF(lG_zrpc_fzer_large, "%0.0lG", 123456789.0, double)

TEST_SPRINTF(lG_width_prec_mins_post, "%-10.5lG", 123.456, double)
TEST_SPRINTF(lG_width_prec_plus_post, "%+10.5lG", 123.456, double)
TEST_SPRINTF(lG_width_prec_spac_post, "% 10.5lG", 123.456, double)
TEST_SPRINTF(lG_width_prec_hash_post, "%#10.5lG", 123.456, double)
TEST_SPRINTF(lG_width_prec_fzer_post, "%010.5lG", 123.456, double)
TEST_SPRINTF(lG_width_prec_mins_negt, "%-10.5lG", -123.456, double)
TEST_SPRINTF(lG_width_prec_plus_negt, "%+10.5lG", -123.456, double)
TEST_SPRINTF(lG_width_prec_spac_negt, "% 10.5lG", -123.456, double)
TEST_SPRINTF(lG_width_prec_hash_negt, "%#10.5lG", -123.456, double)
TEST_SPRINTF(lG_width_prec_fzer_negt, "%010.5lG", -123.456, double)
TEST_SPRINTF(lG_width_prec_mins_small, "%-10.5lG", -0.0000123456, double)
TEST_SPRINTF(lG_width_prec_plus_small, "%+10.5lG", -0.0000123456, double)
TEST_SPRINTF(lG_width_prec_spac_small, "% 10.5lG", -0.0000123456, double)
TEST_SPRINTF(lG_width_prec_hash_small, "%#10.5lG", -0.0000123456, double)
TEST_SPRINTF(lG_width_prec_fzer_small, "%010.5lG", -0.0000123456, double)
TEST_SPRINTF(lG_width_prec_mins_large, "%-10.5lG", 123456789.0, double)
TEST_SPRINTF(lG_width_prec_plus_large, "%+10.5lG", 123456789.0, double)
TEST_SPRINTF(lG_width_prec_spac_large, "% 10.5lG", 123456789.0, double)
TEST_SPRINTF(lG_width_prec_hash_large, "%#10.5lG", 123456789.0, double)
TEST_SPRINTF(lG_width_prec_fzer_large, "%010.5lG", 123456789.0, double)

TEST_SPRINTF(lG_zrwth_zrpc_plus_post, "%+0.0lG", 123.456, double)
TEST_SPRINTF(lG_zrwth_zrpc_spac_post, "% 0.0lG", 123.456, double)
TEST_SPRINTF(lG_zrwth_zrpc_hash_post, "%#0.0lG", 123.456, double)
TEST_SPRINTF(lG_zrwth_zrpc_plus_negt, "%+0.0lG", -123.456, double)
TEST_SPRINTF(lG_zrwth_zrpc_spac_negt, "% 0.0lG", -123.456, double)
TEST_SPRINTF(lG_zrwth_zrpc_hash_negt, "%#0.0lG", -123.456, double)
TEST_SPRINTF(lG_zrwth_zrpc_plus_small, "%+0.0lG", -0.0000123456, double)
TEST_SPRINTF(lG_zrwth_zrpc_spac_small, "% 0.0lG", -0.0000123456, double)
TEST_SPRINTF(lG_zrwth_zrpc_hash_small, "%#0.0lG", -0.0000123456, double)
TEST_SPRINTF(lG_zrwth_zrpc_plus_large, "%+0.0lG", 123456789.0, double)
TEST_SPRINTF(lG_zrwth_zrpc_spac_large, "% 0.0lG", 123456789.0, double)
TEST_SPRINTF(lG_zrwth_zrpc_hash_large, "%#0.0lG", 123456789.0, double)

TEST_SPRINTF_2(lG_dynamic_width_post, "%*lG", 10, 123.456, double)
TEST_SPRINTF_2(lG_dynamic_width_negt, "%*lG", 10, -123.456, double)
TEST_SPRINTF_2(lG_dynamic_width_small, "%*lG", 10, -0.0000123456, double)
TEST_SPRINTF_2(lG_dynamic_width_large, "%*lG", 10, 123456789.0, double)

TEST_SPRINTF_2(lG_dynamic_prec_post, "%.*lG", 5, 123.456, double)
TEST_SPRINTF_2(lG_dynamic_prec_negt, "%.*lG", 5, -123.456, double)
TEST_SPRINTF_2(lG_dynamic_prec_small, "%.*lG", 5, -0.0000123456, double)
TEST_SPRINTF_2(lG_dynamic_prec_large, "%.*lG", 5, 123456789.0, double)

TEST_SPRINTF_3(lG_dynamic_width_prec_post, "%*.*lG", 10, 5, 123.456, double)
TEST_SPRINTF_3(lG_dynamic_width_prec_negt, "%*.*lG", 10, 5, -123.456, double)
TEST_SPRINTF_3(lG_dynamic_width_prec_small, "%*.*lG", 10, 5, -0.0000123456,
               double)
TEST_SPRINTF_3(lG_dynamic_width_prec_large, "%*.*lG", 10, 5, 123456789.0,
               double)
#pragma endregion

// =========================================================================
// Вещественные типы модификатор L (long long) %lf %Le %LE %Lg %LG
// =========================================================================
#pragma region
TEST_SPRINTF(Le_mins_post, "%-Le", 123.456L, long double)
TEST_SPRINTF(Le_plus_post, "%+Le", 123.456L, long double)
TEST_SPRINTF(Le_spac_post, "% Le", 123.456L, long double)
TEST_SPRINTF(Le_hash_post, "%#Le", 123.456L, long double)
TEST_SPRINTF(Le_fzer_post, "%0Le", 123.456L, long double)
TEST_SPRINTF(Le_mins_negt, "%-Le", -123.456L, long double)
TEST_SPRINTF(Le_plus_negt, "%+Le", -123.456L, long double)
TEST_SPRINTF(Le_spac_negt, "% Le", -123.456L, long double)
TEST_SPRINTF(Le_hash_negt, "%#Le", -123.456L, long double)
TEST_SPRINTF(Le_fzer_negt, "%0Le", -123.456L, long double)
TEST_SPRINTF(Le_mins_small, "%-Le", -0.0000123456L, long double)
TEST_SPRINTF(Le_plus_small, "%+Le", -0.0000123456L, long double)
TEST_SPRINTF(Le_spac_small, "% Le", -0.0000123456L, long double)
TEST_SPRINTF(Le_hash_small, "%#Le", -0.0000123456L, long double)
TEST_SPRINTF(Le_fzer_small, "%0Le", -0.0000123456L, long double)
TEST_SPRINTF(Le_mins_large, "%-Le", 123456789.0L, long double)
TEST_SPRINTF(Le_plus_large, "%+Le", 123456789.0L, long double)
TEST_SPRINTF(Le_spac_large, "% Le", 123456789.0L, long double)
TEST_SPRINTF(Le_hash_large, "%#Le", 123456789.0L, long double)
TEST_SPRINTF(Le_fzer_large, "%0Le", 123456789.0L, long double)

TEST_SPRINTF(Le_width_post, "%5Le", 123.456L, long double)
TEST_SPRINTF(Le_zrpc_post, "%.0Le", 123.456L, long double)
TEST_SPRINTF(Le_prec_post, "%.5Le", 123.456L, long double)
TEST_SPRINTF(Le_width_negt, "%5Le", -123.456L, long double)
TEST_SPRINTF(Le_zrpc_negt, "%.0Le", -123.456L, long double)
TEST_SPRINTF(Le_prec_negt, "%.5Le", -123.456L, long double)
TEST_SPRINTF(Le_width_small, "%5Le", -0.0000123456L, long double)
TEST_SPRINTF(Le_zrpc_small, "%.0Le", -0.0000123456L, long double)
TEST_SPRINTF(Le_prec_small, "%.5Le", -0.0000123456L, long double)
TEST_SPRINTF(Le_width_large, "%5Le", 123456789.0L, long double)
TEST_SPRINTF(Le_zrpc_large, "%.0Le", 123456789.0L, long double)
TEST_SPRINTF(Le_prec_large, "%.5Le", 123456789.0L, long double)

TEST_SPRINTF(Le_width_prec_post, "%10.5Le", 123.456L, long double)
TEST_SPRINTF(Le_width_prec_negt, "%10.5Le", -123.456L, long double)
TEST_SPRINTF(Le_width_prec_small, "%10.5Le", -0.0000123456L, long double)
TEST_SPRINTF(Le_width_prec_large, "%10.5Le", 123456789.0L, long double)

TEST_SPRINTF(Le_width_mins_post, "%-5Le", 123.456L, long double)
TEST_SPRINTF(Le_width_plus_post, "%+5Le", 123.456L, long double)
TEST_SPRINTF(Le_width_spac_post, "% 5Le", 123.456L, long double)
TEST_SPRINTF(Le_width_hash_post, "%#5Le", 123.456L, long double)
TEST_SPRINTF(Le_width_fzer_post, "%05Le", 123.456L, long double)
TEST_SPRINTF(Le_width_mins_negt, "%-5Le", -123.456L, long double)
TEST_SPRINTF(Le_width_plus_negt, "%+5Le", -123.456L, long double)
TEST_SPRINTF(Le_width_spac_negt, "% 5Le", -123.456L, long double)
TEST_SPRINTF(Le_width_hash_negt, "%#5Le", -123.456L, long double)
TEST_SPRINTF(Le_width_fzer_negt, "%05Le", -123.456L, long double)
TEST_SPRINTF(Le_width_mins_small, "%-5Le", -0.0000123456L, long double)
TEST_SPRINTF(Le_width_plus_small, "%+5Le", -0.0000123456L, long double)
TEST_SPRINTF(Le_width_spac_small, "% 5Le", -0.0000123456L, long double)
TEST_SPRINTF(Le_width_hash_small, "%#5Le", -0.0000123456L, long double)
TEST_SPRINTF(Le_width_fzer_small, "%05Le", -0.0000123456L, long double)
TEST_SPRINTF(Le_width_mins_large, "%-5Le", 123456789.0L, long double)
TEST_SPRINTF(Le_width_plus_large, "%+5Le", 123456789.0L, long double)
TEST_SPRINTF(Le_width_spac_large, "% 5Le", 123456789.0L, long double)
TEST_SPRINTF(Le_width_hash_large, "%#5Le", 123456789.0L, long double)
TEST_SPRINTF(Le_width_fzer_large, "%05Le", 123456789.0L, long double)

TEST_SPRINTF(Le_zrwth_plus_post, "%+0Le", 123.456L, long double)
TEST_SPRINTF(Le_zrwth_spac_post, "% 0Le", 123.456L, long double)
TEST_SPRINTF(Le_zrwth_hash_post, "%#0Le", 123.456L, long double)
TEST_SPRINTF(Le_zrwth_plus_negt, "%+0Le", -123.456L, long double)
TEST_SPRINTF(Le_zrwth_spac_negt, "% 0Le", -123.456L, long double)
TEST_SPRINTF(Le_zrwth_hash_negt, "%#0Le", -123.456L, long double)
TEST_SPRINTF(Le_zrwth_plus_small, "%+0Le", -0.0000123456L, long double)
TEST_SPRINTF(Le_zrwth_spac_small, "% 0Le", -0.0000123456L, long double)
TEST_SPRINTF(Le_zrwth_hash_small, "%#0Le", -0.0000123456L, long double)
TEST_SPRINTF(Le_zrwth_plus_large, "%+0Le", 123456789.0L, long double)
TEST_SPRINTF(Le_zrwth_spac_large, "% 0Le", 123456789.0L, long double)
TEST_SPRINTF(Le_zrwth_hash_large, "%#0Le", 123456789.0L, long double)

TEST_SPRINTF(Le_prec_mins_post, "%-.5Le", 123.456L, long double)
TEST_SPRINTF(Le_prec_plus_post, "%+.5Le", 123.456L, long double)
TEST_SPRINTF(Le_prec_spac_post, "% .5Le", 123.456L, long double)
TEST_SPRINTF(Le_prec_hash_post, "%#.5Le", 123.456L, long double)
TEST_SPRINTF(Le_prec_fzer_post, "%0.5Le", 123.456L, long double)
TEST_SPRINTF(Le_prec_mins_negt, "%-.5Le", -123.456L, long double)
TEST_SPRINTF(Le_prec_plus_negt, "%+.5Le", -123.456L, long double)
TEST_SPRINTF(Le_prec_spac_negt, "% .5Le", -123.456L, long double)
TEST_SPRINTF(Le_prec_hash_negt, "%#.5Le", -123.456L, long double)
TEST_SPRINTF(Le_prec_fzer_negt, "%0.5Le", -123.456L, long double)
TEST_SPRINTF(Le_prec_mins_small, "%-.5Le", -0.0000123456L, long double)
TEST_SPRINTF(Le_prec_plus_small, "%+.5Le", -0.0000123456L, long double)
TEST_SPRINTF(Le_prec_spac_small, "% .5Le", -0.0000123456L, long double)
TEST_SPRINTF(Le_prec_hash_small, "%#.5Le", -0.0000123456L, long double)
TEST_SPRINTF(Le_prec_fzer_small, "%0.5Le", -0.0000123456L, long double)
TEST_SPRINTF(Le_prec_mins_large, "%-.5Le", 123456789.0L, long double)
TEST_SPRINTF(Le_prec_plus_large, "%+.5Le", 123456789.0L, long double)
TEST_SPRINTF(Le_prec_spac_large, "% .5Le", 123456789.0L, long double)
TEST_SPRINTF(Le_prec_hash_large, "%#.5Le", 123456789.0L, long double)
TEST_SPRINTF(Le_prec_fzer_large, "%0.5Le", 123456789.0L, long double)

TEST_SPRINTF(Le_zrpc_mins_post, "%-.0Le", 123.456L, long double)
TEST_SPRINTF(Le_zrpc_plus_post, "%+.0Le", 123.456L, long double)
TEST_SPRINTF(Le_zrpc_spac_post, "% .0Le", 123.456L, long double)
TEST_SPRINTF(Le_zrpc_hash_post, "%#.0Le", 123.456L, long double)
TEST_SPRINTF(Le_zrpc_fzer_post, "%0.0Le", 123.456L, long double)
TEST_SPRINTF(Le_zrpc_mins_negt, "%-.0Le", -123.456L, long double)
TEST_SPRINTF(Le_zrpc_plus_negt, "%+.0Le", -123.456L, long double)
TEST_SPRINTF(Le_zrpc_spac_negt, "% .0Le", -123.456L, long double)
TEST_SPRINTF(Le_zrpc_hash_negt, "%#.0Le", -123.456L, long double)
TEST_SPRINTF(Le_zrpc_fzer_negt, "%0.0Le", -123.456L, long double)
TEST_SPRINTF(Le_zrpc_mins_small, "%-.0Le", -0.0000123456L, long double)
TEST_SPRINTF(Le_zrpc_plus_small, "%+.0Le", -0.0000123456L, long double)
TEST_SPRINTF(Le_zrpc_spac_small, "% .0Le", -0.0000123456L, long double)
TEST_SPRINTF(Le_zrpc_hash_small, "%#.0Le", -0.0000123456L, long double)
TEST_SPRINTF(Le_zrpc_fzer_small, "%0.0Le", -0.0000123456L, long double)
TEST_SPRINTF(Le_zrpc_mins_large, "%-.0Le", 123456789.0L, long double)
TEST_SPRINTF(Le_zrpc_plus_large, "%+.0Le", 123456789.0L, long double)
TEST_SPRINTF(Le_zrpc_spac_large, "% .0Le", 123456789.0L, long double)
TEST_SPRINTF(Le_zrpc_hash_large, "%#.0Le", 123456789.0L, long double)
TEST_SPRINTF(Le_zrpc_fzer_large, "%0.0Le", 123456789.0L, long double)

TEST_SPRINTF(Le_width_prec_mins_post, "%-10.5Le", 123.456L, long double)
TEST_SPRINTF(Le_width_prec_plus_post, "%+10.5Le", 123.456L, long double)
TEST_SPRINTF(Le_width_prec_spac_post, "% 10.5Le", 123.456L, long double)
TEST_SPRINTF(Le_width_prec_hash_post, "%#10.5Le", 123.456L, long double)
TEST_SPRINTF(Le_width_prec_fzer_post, "%010.5Le", 123.456L, long double)
TEST_SPRINTF(Le_width_prec_mins_negt, "%-10.5Le", -123.456L, long double)
TEST_SPRINTF(Le_width_prec_plus_negt, "%+10.5Le", -123.456L, long double)
TEST_SPRINTF(Le_width_prec_spac_negt, "% 10.5Le", -123.456L, long double)
TEST_SPRINTF(Le_width_prec_hash_negt, "%#10.5Le", -123.456L, long double)
TEST_SPRINTF(Le_width_prec_fzer_negt, "%010.5Le", -123.456L, long double)
TEST_SPRINTF(Le_width_prec_mins_small, "%-10.5Le", -0.0000123456L, long double)
TEST_SPRINTF(Le_width_prec_plus_small, "%+10.5Le", -0.0000123456L, long double)
TEST_SPRINTF(Le_width_prec_spac_small, "% 10.5Le", -0.0000123456L, long double)
TEST_SPRINTF(Le_width_prec_hash_small, "%#10.5Le", -0.0000123456L, long double)
TEST_SPRINTF(Le_width_prec_fzer_small, "%010.5Le", -0.0000123456L, long double)
TEST_SPRINTF(Le_width_prec_mins_large, "%-10.5Le", 123456789.0L, long double)
TEST_SPRINTF(Le_width_prec_plus_large, "%+10.5Le", 123456789.0L, long double)
TEST_SPRINTF(Le_width_prec_spac_large, "% 10.5Le", 123456789.0L, long double)
TEST_SPRINTF(Le_width_prec_hash_large, "%#10.5Le", 123456789.0L, long double)
TEST_SPRINTF(Le_width_prec_fzer_large, "%010.5Le", 123456789.0L, long double)

TEST_SPRINTF(Le_zrwth_zrpc_plus_post, "%+0.0Le", 123.456L, long double)
TEST_SPRINTF(Le_zrwth_zrpc_spac_post, "% 0.0Le", 123.456L, long double)
TEST_SPRINTF(Le_zrwth_zrpc_hash_post, "%#0.0Le", 123.456L, long double)
TEST_SPRINTF(Le_zrwth_zrpc_plus_negt, "%+0.0Le", -123.456L, long double)
TEST_SPRINTF(Le_zrwth_zrpc_spac_negt, "% 0.0Le", -123.456L, long double)
TEST_SPRINTF(Le_zrwth_zrpc_hash_negt, "%#0.0Le", -123.456L, long double)
TEST_SPRINTF(Le_zrwth_zrpc_plus_small, "%+0.0Le", -0.0000123456L, long double)
TEST_SPRINTF(Le_zrwth_zrpc_spac_small, "% 0.0Le", -0.0000123456L, long double)
TEST_SPRINTF(Le_zrwth_zrpc_hash_small, "%#0.0Le", -0.0000123456L, long double)
TEST_SPRINTF(Le_zrwth_zrpc_plus_large, "%+0.0Le", 123456789.0L, long double)
TEST_SPRINTF(Le_zrwth_zrpc_spac_large, "% 0.0Le", 123456789.0L, long double)
TEST_SPRINTF(Le_zrwth_zrpc_hash_large, "%#0.0Le", 123456789.0L, long double)

TEST_SPRINTF_2(Le_dynamic_width_post, "%*Le", 10, 123.456L, long double)
TEST_SPRINTF_2(Le_dynamic_width_negt, "%*Le", 10, -123.456L, long double)
TEST_SPRINTF_2(Le_dynamic_width_small, "%*Le", 10, -0.0000123456L, long double)
TEST_SPRINTF_2(Le_dynamic_width_large, "%*Le", 10, 123456789.0L, long double)

TEST_SPRINTF_2(Le_dynamic_prec_post, "%.*Le", 5, 123.456L, long double)
TEST_SPRINTF_2(Le_dynamic_prec_negt, "%.*Le", 5, -123.456L, long double)
TEST_SPRINTF_2(Le_dynamic_prec_small, "%.*Le", 5, -0.0000123456L, long double)
TEST_SPRINTF_2(Le_dynamic_prec_large, "%.*Le", 5, 123456789.0L, long double)

TEST_SPRINTF_3(Le_dynamic_width_prec_post, "%*.*Le", 10, 5, 123.456L,
               long double)
TEST_SPRINTF_3(Le_dynamic_width_prec_negt, "%*.*Le", 10, 5, -123.456L,
               long double)
TEST_SPRINTF_3(Le_dynamic_width_prec_small, "%*.*Le", 10, 5, -0.0000123456L,
               long double)
TEST_SPRINTF_3(Le_dynamic_width_prec_large, "%*.*Le", 10, 5, 123456789.0L,
               long double)

// =========================================================================

TEST_SPRINTF(LE_mins_post, "%-LE", 123.456L, long double)
TEST_SPRINTF(LE_plus_post, "%+LE", 123.456L, long double)
TEST_SPRINTF(LE_spac_post, "% LE", 123.456L, long double)
TEST_SPRINTF(LE_hash_post, "%#LE", 123.456L, long double)
TEST_SPRINTF(LE_fzer_post, "%0LE", 123.456L, long double)
TEST_SPRINTF(LE_mins_negt, "%-LE", -123.456L, long double)
TEST_SPRINTF(LE_plus_negt, "%+LE", -123.456L, long double)
TEST_SPRINTF(LE_spac_negt, "% LE", -123.456L, long double)
TEST_SPRINTF(LE_hash_negt, "%#LE", -123.456L, long double)
TEST_SPRINTF(LE_fzer_negt, "%0LE", -123.456L, long double)
TEST_SPRINTF(LE_mins_small, "%-LE", -0.0000123456L, long double)
TEST_SPRINTF(LE_plus_small, "%+LE", -0.0000123456L, long double)
TEST_SPRINTF(LE_spac_small, "% LE", -0.0000123456L, long double)
TEST_SPRINTF(LE_hash_small, "%#LE", -0.0000123456L, long double)
TEST_SPRINTF(LE_fzer_small, "%0LE", -0.0000123456L, long double)
TEST_SPRINTF(LE_mins_large, "%-LE", 123456789.0L, long double)
TEST_SPRINTF(LE_plus_large, "%+LE", 123456789.0L, long double)
TEST_SPRINTF(LE_spac_large, "% LE", 123456789.0L, long double)
TEST_SPRINTF(LE_hash_large, "%#LE", 123456789.0L, long double)
TEST_SPRINTF(LE_fzer_large, "%0LE", 123456789.0L, long double)

TEST_SPRINTF(LE_width_post, "%5LE", 123.456L, long double)
TEST_SPRINTF(LE_zrpc_post, "%.0LE", 123.456L, long double)
TEST_SPRINTF(LE_prec_post, "%.5LE", 123.456L, long double)
TEST_SPRINTF(LE_width_negt, "%5LE", -123.456L, long double)
TEST_SPRINTF(LE_zrpc_negt, "%.0LE", -123.456L, long double)
TEST_SPRINTF(LE_prec_negt, "%.5LE", -123.456L, long double)
TEST_SPRINTF(LE_width_small, "%5LE", -0.0000123456L, long double)
TEST_SPRINTF(LE_zrpc_small, "%.0LE", -0.0000123456L, long double)
TEST_SPRINTF(LE_prec_small, "%.5LE", -0.0000123456L, long double)
TEST_SPRINTF(LE_width_large, "%5LE", 123456789.0L, long double)
TEST_SPRINTF(LE_zrpc_large, "%.0LE", 123456789.0L, long double)
TEST_SPRINTF(LE_prec_large, "%.5LE", 123456789.0L, long double)

TEST_SPRINTF(LE_width_prec_post, "%10.5LE", 123.456L, long double)
TEST_SPRINTF(LE_width_prec_negt, "%10.5LE", -123.456L, long double)
TEST_SPRINTF(LE_width_prec_small, "%10.5LE", -0.0000123456L, long double)
TEST_SPRINTF(LE_width_prec_large, "%10.5LE", 123456789.0L, long double)

TEST_SPRINTF(LE_width_mins_post, "%-5LE", 123.456L, long double)
TEST_SPRINTF(LE_width_plus_post, "%+5LE", 123.456L, long double)
TEST_SPRINTF(LE_width_spac_post, "% 5LE", 123.456L, long double)
TEST_SPRINTF(LE_width_hash_post, "%#5LE", 123.456L, long double)
TEST_SPRINTF(LE_width_fzer_post, "%05LE", 123.456L, long double)
TEST_SPRINTF(LE_width_mins_negt, "%-5LE", -123.456L, long double)
TEST_SPRINTF(LE_width_plus_negt, "%+5LE", -123.456L, long double)
TEST_SPRINTF(LE_width_spac_negt, "% 5LE", -123.456L, long double)
TEST_SPRINTF(LE_width_hash_negt, "%#5LE", -123.456L, long double)
TEST_SPRINTF(LE_width_fzer_negt, "%05LE", -123.456L, long double)
TEST_SPRINTF(LE_width_mins_small, "%-5LE", -0.0000123456L, long double)
TEST_SPRINTF(LE_width_plus_small, "%+5LE", -0.0000123456L, long double)
TEST_SPRINTF(LE_width_spac_small, "% 5LE", -0.0000123456L, long double)
TEST_SPRINTF(LE_width_hash_small, "%#5LE", -0.0000123456L, long double)
TEST_SPRINTF(LE_width_fzer_small, "%05LE", -0.0000123456L, long double)
TEST_SPRINTF(LE_width_mins_large, "%-5LE", 123456789.0L, long double)
TEST_SPRINTF(LE_width_plus_large, "%+5LE", 123456789.0L, long double)
TEST_SPRINTF(LE_width_spac_large, "% 5LE", 123456789.0L, long double)
TEST_SPRINTF(LE_width_hash_large, "%#5LE", 123456789.0L, long double)
TEST_SPRINTF(LE_width_fzer_large, "%05LE", 123456789.0L, long double)

TEST_SPRINTF(LE_zrwth_plus_post, "%+0LE", 123.456L, long double)
TEST_SPRINTF(LE_zrwth_spac_post, "% 0LE", 123.456L, long double)
TEST_SPRINTF(LE_zrwth_hash_post, "%#0LE", 123.456L, long double)
TEST_SPRINTF(LE_zrwth_plus_negt, "%+0LE", -123.456L, long double)
TEST_SPRINTF(LE_zrwth_spac_negt, "% 0LE", -123.456L, long double)
TEST_SPRINTF(LE_zrwth_hash_negt, "%#0LE", -123.456L, long double)
TEST_SPRINTF(LE_zrwth_plus_small, "%+0LE", -0.0000123456L, long double)
TEST_SPRINTF(LE_zrwth_spac_small, "% 0LE", -0.0000123456L, long double)
TEST_SPRINTF(LE_zrwth_hash_small, "%#0LE", -0.0000123456L, long double)
TEST_SPRINTF(LE_zrwth_plus_large, "%+0LE", 123456789.0L, long double)
TEST_SPRINTF(LE_zrwth_spac_large, "% 0LE", 123456789.0L, long double)
TEST_SPRINTF(LE_zrwth_hash_large, "%#0LE", 123456789.0L, long double)

TEST_SPRINTF(LE_prec_mins_post, "%-.5LE", 123.456L, long double)
TEST_SPRINTF(LE_prec_plus_post, "%+.5LE", 123.456L, long double)
TEST_SPRINTF(LE_prec_spac_post, "% .5LE", 123.456L, long double)
TEST_SPRINTF(LE_prec_hash_post, "%#.5LE", 123.456L, long double)
TEST_SPRINTF(LE_prec_fzer_post, "%0.5LE", 123.456L, long double)
TEST_SPRINTF(LE_prec_mins_negt, "%-.5LE", -123.456L, long double)
TEST_SPRINTF(LE_prec_plus_negt, "%+.5LE", -123.456L, long double)
TEST_SPRINTF(LE_prec_spac_negt, "% .5LE", -123.456L, long double)
TEST_SPRINTF(LE_prec_hash_negt, "%#.5LE", -123.456L, long double)
TEST_SPRINTF(LE_prec_fzer_negt, "%0.5LE", -123.456L, long double)
TEST_SPRINTF(LE_prec_mins_small, "%-.5LE", -0.0000123456L, long double)
TEST_SPRINTF(LE_prec_plus_small, "%+.5LE", -0.0000123456L, long double)
TEST_SPRINTF(LE_prec_spac_small, "% .5LE", -0.0000123456L, long double)
TEST_SPRINTF(LE_prec_hash_small, "%#.5LE", -0.0000123456L, long double)
TEST_SPRINTF(LE_prec_fzer_small, "%0.5LE", -0.0000123456L, long double)
TEST_SPRINTF(LE_prec_mins_large, "%-.5LE", 123456789.0L, long double)
TEST_SPRINTF(LE_prec_plus_large, "%+.5LE", 123456789.0L, long double)
TEST_SPRINTF(LE_prec_spac_large, "% .5LE", 123456789.0L, long double)
TEST_SPRINTF(LE_prec_hash_large, "%#.5LE", 123456789.0L, long double)
TEST_SPRINTF(LE_prec_fzer_large, "%0.5LE", 123456789.0L, long double)

TEST_SPRINTF(LE_zrpc_mins_post, "%-.0LE", 123.456L, long double)
TEST_SPRINTF(LE_zrpc_plus_post, "%+.0LE", 123.456L, long double)
TEST_SPRINTF(LE_zrpc_spac_post, "% .0LE", 123.456L, long double)
TEST_SPRINTF(LE_zrpc_hash_post, "%#.0LE", 123.456L, long double)
TEST_SPRINTF(LE_zrpc_fzer_post, "%0.0LE", 123.456L, long double)
TEST_SPRINTF(LE_zrpc_mins_negt, "%-.0LE", -123.456L, long double)
TEST_SPRINTF(LE_zrpc_plus_negt, "%+.0LE", -123.456L, long double)
TEST_SPRINTF(LE_zrpc_spac_negt, "% .0LE", -123.456L, long double)
TEST_SPRINTF(LE_zrpc_hash_negt, "%#.0LE", -123.456L, long double)
TEST_SPRINTF(LE_zrpc_fzer_negt, "%0.0LE", -123.456L, long double)
TEST_SPRINTF(LE_zrpc_mins_small, "%-.0LE", -0.0000123456L, long double)
TEST_SPRINTF(LE_zrpc_plus_small, "%+.0LE", -0.0000123456L, long double)
TEST_SPRINTF(LE_zrpc_spac_small, "% .0LE", -0.0000123456L, long double)
TEST_SPRINTF(LE_zrpc_hash_small, "%#.0LE", -0.0000123456L, long double)
TEST_SPRINTF(LE_zrpc_fzer_small, "%0.0LE", -0.0000123456L, long double)
TEST_SPRINTF(LE_zrpc_mins_large, "%-.0LE", 123456789.0L, long double)
TEST_SPRINTF(LE_zrpc_plus_large, "%+.0LE", 123456789.0L, long double)
TEST_SPRINTF(LE_zrpc_spac_large, "% .0LE", 123456789.0L, long double)
TEST_SPRINTF(LE_zrpc_hash_large, "%#.0LE", 123456789.0L, long double)
TEST_SPRINTF(LE_zrpc_fzer_large, "%0.0LE", 123456789.0L, long double)

TEST_SPRINTF(LE_width_prec_mins_post, "%-10.5LE", 123.456L, long double)
TEST_SPRINTF(LE_width_prec_plus_post, "%+10.5LE", 123.456L, long double)
TEST_SPRINTF(LE_width_prec_spac_post, "% 10.5LE", 123.456L, long double)
TEST_SPRINTF(LE_width_prec_hash_post, "%#10.5LE", 123.456L, long double)
TEST_SPRINTF(LE_width_prec_fzer_post, "%010.5LE", 123.456L, long double)
TEST_SPRINTF(LE_width_prec_mins_negt, "%-10.5LE", -123.456L, long double)
TEST_SPRINTF(LE_width_prec_plus_negt, "%+10.5LE", -123.456L, long double)
TEST_SPRINTF(LE_width_prec_spac_negt, "% 10.5LE", -123.456L, long double)
TEST_SPRINTF(LE_width_prec_hash_negt, "%#10.5LE", -123.456L, long double)
TEST_SPRINTF(LE_width_prec_fzer_negt, "%010.5LE", -123.456L, long double)
TEST_SPRINTF(LE_width_prec_mins_small, "%-10.5LE", -0.0000123456L, long double)
TEST_SPRINTF(LE_width_prec_plus_small, "%+10.5LE", -0.0000123456L, long double)
TEST_SPRINTF(LE_width_prec_spac_small, "% 10.5LE", -0.0000123456L, long double)
TEST_SPRINTF(LE_width_prec_hash_small, "%#10.5LE", -0.0000123456L, long double)
TEST_SPRINTF(LE_width_prec_fzer_small, "%010.5LE", -0.0000123456L, long double)
TEST_SPRINTF(LE_width_prec_mins_large, "%-10.5LE", 123456789.0L, long double)
TEST_SPRINTF(LE_width_prec_plus_large, "%+10.5LE", 123456789.0L, long double)
TEST_SPRINTF(LE_width_prec_spac_large, "% 10.5LE", 123456789.0L, long double)
TEST_SPRINTF(LE_width_prec_hash_large, "%#10.5LE", 123456789.0L, long double)
TEST_SPRINTF(LE_width_prec_fzer_large, "%010.5LE", 123456789.0L, long double)

TEST_SPRINTF(LE_zrwth_zrpc_plus_post, "%+0.0LE", 123.456L, long double)
TEST_SPRINTF(LE_zrwth_zrpc_spac_post, "% 0.0LE", 123.456L, long double)
TEST_SPRINTF(LE_zrwth_zrpc_hash_post, "%#0.0LE", 123.456L, long double)
TEST_SPRINTF(LE_zrwth_zrpc_plus_negt, "%+0.0LE", -123.456L, long double)
TEST_SPRINTF(LE_zrwth_zrpc_spac_negt, "% 0.0LE", -123.456L, long double)
TEST_SPRINTF(LE_zrwth_zrpc_hash_negt, "%#0.0LE", -123.456L, long double)
TEST_SPRINTF(LE_zrwth_zrpc_plus_small, "%+0.0LE", -0.0000123456L, long double)
TEST_SPRINTF(LE_zrwth_zrpc_spac_small, "% 0.0LE", -0.0000123456L, long double)
TEST_SPRINTF(LE_zrwth_zrpc_hash_small, "%#0.0LE", -0.0000123456L, long double)
TEST_SPRINTF(LE_zrwth_zrpc_plus_large, "%+0.0LE", 123456789.0L, long double)
TEST_SPRINTF(LE_zrwth_zrpc_spac_large, "% 0.0LE", 123456789.0L, long double)
TEST_SPRINTF(LE_zrwth_zrpc_hash_large, "%#0.0LE", 123456789.0L, long double)

TEST_SPRINTF_2(LE_dynamic_width_post, "%*LE", 10, 123.456L, long double)
TEST_SPRINTF_2(LE_dynamic_width_negt, "%*LE", 10, -123.456L, long double)
TEST_SPRINTF_2(LE_dynamic_width_small, "%*LE", 10, -0.0000123456L, long double)
TEST_SPRINTF_2(LE_dynamic_width_large, "%*LE", 10, 123456789.0L, long double)

TEST_SPRINTF_2(LE_dynamic_prec_post, "%.*LE", 5, 123.456L, long double)
TEST_SPRINTF_2(LE_dynamic_prec_negt, "%.*LE", 5, -123.456L, long double)
TEST_SPRINTF_2(LE_dynamic_prec_small, "%.*LE", 5, -0.0000123456L, long double)
TEST_SPRINTF_2(LE_dynamic_prec_large, "%.*LE", 5, 123456789.0L, long double)

TEST_SPRINTF_3(LE_dynamic_width_prec_post, "%*.*LE", 10, 5, 123.456L,
               long double)
TEST_SPRINTF_3(LE_dynamic_width_prec_negt, "%*.*LE", 10, 5, -123.456L,
               long double)
TEST_SPRINTF_3(LE_dynamic_width_prec_small, "%*.*LE", 10, 5, -0.0000123456L,
               long double)
TEST_SPRINTF_3(LE_dynamic_width_prec_large, "%*.*LE", 10, 5, 123456789.0L,
               long double)

// =========================================================================

TEST_SPRINTF(Lf_mins_post, "%-Lf", 123.456L, long double)
TEST_SPRINTF(Lf_plus_post, "%+Lf", 123.456L, long double)
TEST_SPRINTF(Lf_spac_post, "% Lf", 123.456L, long double)
TEST_SPRINTF(Lf_hash_post, "%#Lf", 123.456L, long double)
TEST_SPRINTF(Lf_fzer_post, "%0Lf", 123.456L, long double)
TEST_SPRINTF(Lf_mins_negt, "%-Lf", -123.456L, long double)
TEST_SPRINTF(Lf_plus_negt, "%+Lf", -123.456L, long double)
TEST_SPRINTF(Lf_spac_negt, "% Lf", -123.456L, long double)
TEST_SPRINTF(Lf_hash_negt, "%#Lf", -123.456L, long double)
TEST_SPRINTF(Lf_fzer_negt, "%0Lf", -123.456L, long double)
TEST_SPRINTF(Lf_mins_small, "%-Lf", -0.0000123456L, long double)
TEST_SPRINTF(Lf_plus_small, "%+Lf", -0.0000123456L, long double)
TEST_SPRINTF(Lf_spac_small, "% Lf", -0.0000123456L, long double)
TEST_SPRINTF(Lf_hash_small, "%#Lf", -0.0000123456L, long double)
TEST_SPRINTF(Lf_fzer_small, "%0Lf", -0.0000123456L, long double)
TEST_SPRINTF(Lf_mins_large, "%-Lf", 123456789.0L, long double)
TEST_SPRINTF(Lf_plus_large, "%+Lf", 123456789.0L, long double)
TEST_SPRINTF(Lf_spac_large, "% Lf", 123456789.0L, long double)
TEST_SPRINTF(Lf_hash_large, "%#Lf", 123456789.0L, long double)
TEST_SPRINTF(Lf_fzer_large, "%0Lf", 123456789.0L, long double)

TEST_SPRINTF(Lf_width_post, "%5Lf", 123.456L, long double)
TEST_SPRINTF(Lf_zrpc_post, "%.0Lf", 123.456L, long double)
TEST_SPRINTF(Lf_prec_post, "%.5Lf", 123.456L, long double)
TEST_SPRINTF(Lf_width_negt, "%5Lf", -123.456L, long double)
TEST_SPRINTF(Lf_zrpc_negt, "%.0Lf", -123.456L, long double)
TEST_SPRINTF(Lf_prec_negt, "%.5Lf", -123.456L, long double)
TEST_SPRINTF(Lf_width_small, "%5Lf", -0.0000123456L, long double)
TEST_SPRINTF(Lf_zrpc_small, "%.0Lf", -0.0000123456L, long double)
TEST_SPRINTF(Lf_prec_small, "%.5Lf", -0.0000123456L, long double)
TEST_SPRINTF(Lf_width_large, "%5Lf", 123456789.0L, long double)
TEST_SPRINTF(Lf_zrpc_large, "%.0Lf", 123456789.0L, long double)
TEST_SPRINTF(Lf_prec_large, "%.5Lf", 123456789.0L, long double)

TEST_SPRINTF(Lf_width_prec_post, "%10.5Lf", 123.456L, long double)
TEST_SPRINTF(Lf_width_prec_negt, "%10.5Lf", -123.456L, long double)
TEST_SPRINTF(Lf_width_prec_small, "%10.5Lf", -0.0000123456L, long double)
TEST_SPRINTF(Lf_width_prec_large, "%10.5Lf", 123456789.0L, long double)

TEST_SPRINTF(Lf_width_mins_post, "%-5Lf", 123.456L, long double)
TEST_SPRINTF(Lf_width_plus_post, "%+5Lf", 123.456L, long double)
TEST_SPRINTF(Lf_width_spac_post, "% 5Lf", 123.456L, long double)
TEST_SPRINTF(Lf_width_hash_post, "%#5Lf", 123.456L, long double)
TEST_SPRINTF(Lf_width_fzer_post, "%05Lf", 123.456L, long double)
TEST_SPRINTF(Lf_width_mins_negt, "%-5Lf", -123.456L, long double)
TEST_SPRINTF(Lf_width_plus_negt, "%+5Lf", -123.456L, long double)
TEST_SPRINTF(Lf_width_spac_negt, "% 5Lf", -123.456L, long double)
TEST_SPRINTF(Lf_width_hash_negt, "%#5Lf", -123.456L, long double)
TEST_SPRINTF(Lf_width_fzer_negt, "%05Lf", -123.456L, long double)
TEST_SPRINTF(Lf_width_mins_small, "%-5Lf", -0.0000123456L, long double)
TEST_SPRINTF(Lf_width_plus_small, "%+5Lf", -0.0000123456L, long double)
TEST_SPRINTF(Lf_width_spac_small, "% 5Lf", -0.0000123456L, long double)
TEST_SPRINTF(Lf_width_hash_small, "%#5Lf", -0.0000123456L, long double)
TEST_SPRINTF(Lf_width_fzer_small, "%05Lf", -0.0000123456L, long double)
TEST_SPRINTF(Lf_width_mins_large, "%-5Lf", 123456789.0L, long double)
TEST_SPRINTF(Lf_width_plus_large, "%+5Lf", 123456789.0L, long double)
TEST_SPRINTF(Lf_width_spac_large, "% 5Lf", 123456789.0L, long double)
TEST_SPRINTF(Lf_width_hash_large, "%#5Lf", 123456789.0L, long double)
TEST_SPRINTF(Lf_width_fzer_large, "%05Lf", 123456789.0L, long double)

TEST_SPRINTF(Lf_zrwth_plus_post, "%+0Lf", 123.456L, long double)
TEST_SPRINTF(Lf_zrwth_spac_post, "% 0Lf", 123.456L, long double)
TEST_SPRINTF(Lf_zrwth_hash_post, "%#0Lf", 123.456L, long double)
TEST_SPRINTF(Lf_zrwth_plus_negt, "%+0Lf", -123.456L, long double)
TEST_SPRINTF(Lf_zrwth_spac_negt, "% 0Lf", -123.456L, long double)
TEST_SPRINTF(Lf_zrwth_hash_negt, "%#0Lf", -123.456L, long double)
TEST_SPRINTF(Lf_zrwth_plus_small, "%+0Lf", -0.0000123456L, long double)
TEST_SPRINTF(Lf_zrwth_spac_small, "% 0Lf", -0.0000123456L, long double)
TEST_SPRINTF(Lf_zrwth_hash_small, "%#0Lf", -0.0000123456L, long double)
TEST_SPRINTF(Lf_zrwth_plus_large, "%+0Lf", 123456789.0L, long double)
TEST_SPRINTF(Lf_zrwth_spac_large, "% 0Lf", 123456789.0L, long double)
TEST_SPRINTF(Lf_zrwth_hash_large, "%#0Lf", 123456789.0L, long double)

TEST_SPRINTF(Lf_prec_mins_post, "%-.5Lf", 123.456L, long double)
TEST_SPRINTF(Lf_prec_plus_post, "%+.5Lf", 123.456L, long double)
TEST_SPRINTF(Lf_prec_spac_post, "% .5Lf", 123.456L, long double)
TEST_SPRINTF(Lf_prec_hash_post, "%#.5Lf", 123.456L, long double)
TEST_SPRINTF(Lf_prec_fzer_post, "%0.5Lf", 123.456L, long double)
TEST_SPRINTF(Lf_prec_mins_negt, "%-.5Lf", -123.456L, long double)
TEST_SPRINTF(Lf_prec_plus_negt, "%+.5Lf", -123.456L, long double)
TEST_SPRINTF(Lf_prec_spac_negt, "% .5Lf", -123.456L, long double)
TEST_SPRINTF(Lf_prec_hash_negt, "%#.5Lf", -123.456L, long double)
TEST_SPRINTF(Lf_prec_fzer_negt, "%0.5Lf", -123.456L, long double)
TEST_SPRINTF(Lf_prec_mins_small, "%-.5Lf", -0.0000123456L, long double)
TEST_SPRINTF(Lf_prec_plus_small, "%+.5Lf", -0.0000123456L, long double)
TEST_SPRINTF(Lf_prec_spac_small, "% .5Lf", -0.0000123456L, long double)
TEST_SPRINTF(Lf_prec_hash_small, "%#.5Lf", -0.0000123456L, long double)
TEST_SPRINTF(Lf_prec_fzer_small, "%0.5Lf", -0.0000123456L, long double)
TEST_SPRINTF(Lf_prec_mins_large, "%-.5Lf", 123456789.0L, long double)
TEST_SPRINTF(Lf_prec_plus_large, "%+.5Lf", 123456789.0L, long double)
TEST_SPRINTF(Lf_prec_spac_large, "% .5Lf", 123456789.0L, long double)
TEST_SPRINTF(Lf_prec_hash_large, "%#.5Lf", 123456789.0L, long double)
TEST_SPRINTF(Lf_prec_fzer_large, "%0.5Lf", 123456789.0L, long double)

TEST_SPRINTF(Lf_zrpc_mins_post, "%-.0Lf", 123.456L, long double)
TEST_SPRINTF(Lf_zrpc_plus_post, "%+.0Lf", 123.456L, long double)
TEST_SPRINTF(Lf_zrpc_spac_post, "% .0Lf", 123.456L, long double)
TEST_SPRINTF(Lf_zrpc_hash_post, "%#.0Lf", 123.456L, long double)
TEST_SPRINTF(Lf_zrpc_fzer_post, "%0.0Lf", 123.456L, long double)
TEST_SPRINTF(Lf_zrpc_mins_negt, "%-.0Lf", -123.456L, long double)
TEST_SPRINTF(Lf_zrpc_plus_negt, "%+.0Lf", -123.456L, long double)
TEST_SPRINTF(Lf_zrpc_spac_negt, "% .0Lf", -123.456L, long double)
TEST_SPRINTF(Lf_zrpc_hash_negt, "%#.0Lf", -123.456L, long double)
TEST_SPRINTF(Lf_zrpc_fzer_negt, "%0.0Lf", -123.456L, long double)
TEST_SPRINTF(Lf_zrpc_mins_small, "%-.0Lf", -0.0000123456L, long double)
TEST_SPRINTF(Lf_zrpc_plus_small, "%+.0Lf", -0.0000123456L, long double)
TEST_SPRINTF(Lf_zrpc_spac_small, "% .0Lf", -0.0000123456L, long double)
TEST_SPRINTF(Lf_zrpc_hash_small, "%#.0Lf", -0.0000123456L, long double)
TEST_SPRINTF(Lf_zrpc_fzer_small, "%0.0Lf", -0.0000123456L, long double)
TEST_SPRINTF(Lf_zrpc_mins_large, "%-.0Lf", 123456789.0L, long double)
TEST_SPRINTF(Lf_zrpc_plus_large, "%+.0Lf", 123456789.0L, long double)
TEST_SPRINTF(Lf_zrpc_spac_large, "% .0Lf", 123456789.0L, long double)
TEST_SPRINTF(Lf_zrpc_hash_large, "%#.0Lf", 123456789.0L, long double)
TEST_SPRINTF(Lf_zrpc_fzer_large, "%0.0Lf", 123456789.0L, long double)

TEST_SPRINTF(Lf_width_prec_mins_post, "%-10.5Lf", 123.456L, long double)
TEST_SPRINTF(Lf_width_prec_plus_post, "%+10.5Lf", 123.456L, long double)
TEST_SPRINTF(Lf_width_prec_spac_post, "% 10.5Lf", 123.456L, long double)
TEST_SPRINTF(Lf_width_prec_hash_post, "%#10.5Lf", 123.456L, long double)
TEST_SPRINTF(Lf_width_prec_fzer_post, "%010.5Lf", 123.456L, long double)
TEST_SPRINTF(Lf_width_prec_mins_negt, "%-10.5Lf", -123.456L, long double)
TEST_SPRINTF(Lf_width_prec_plus_negt, "%+10.5Lf", -123.456L, long double)
TEST_SPRINTF(Lf_width_prec_spac_negt, "% 10.5Lf", -123.456L, long double)
TEST_SPRINTF(Lf_width_prec_hash_negt, "%#10.5Lf", -123.456L, long double)
TEST_SPRINTF(Lf_width_prec_fzer_negt, "%010.5Lf", -123.456L, long double)
TEST_SPRINTF(Lf_width_prec_mins_small, "%-10.5Lf", -0.0000123456L, long double)
TEST_SPRINTF(Lf_width_prec_plus_small, "%+10.5Lf", -0.0000123456L, long double)
TEST_SPRINTF(Lf_width_prec_spac_small, "% 10.5Lf", -0.0000123456L, long double)
TEST_SPRINTF(Lf_width_prec_hash_small, "%#10.5Lf", -0.0000123456L, long double)
TEST_SPRINTF(Lf_width_prec_fzer_small, "%010.5Lf", -0.0000123456L, long double)
TEST_SPRINTF(Lf_width_prec_mins_large, "%-10.5Lf", 123456789.0L, long double)
TEST_SPRINTF(Lf_width_prec_plus_large, "%+10.5Lf", 123456789.0L, long double)
TEST_SPRINTF(Lf_width_prec_spac_large, "% 10.5Lf", 123456789.0L, long double)
TEST_SPRINTF(Lf_width_prec_hash_large, "%#10.5Lf", 123456789.0L, long double)
TEST_SPRINTF(Lf_width_prec_fzer_large, "%010.5Lf", 123456789.0L, long double)

TEST_SPRINTF(Lf_zrwth_zrpc_plus_post, "%+0.0Lf", 123.456L, long double)
TEST_SPRINTF(Lf_zrwth_zrpc_spac_post, "% 0.0Lf", 123.456L, long double)
TEST_SPRINTF(Lf_zrwth_zrpc_hash_post, "%#0.0Lf", 123.456L, long double)
TEST_SPRINTF(Lf_zrwth_zrpc_plus_negt, "%+0.0Lf", -123.456L, long double)
TEST_SPRINTF(Lf_zrwth_zrpc_spac_negt, "% 0.0Lf", -123.456L, long double)
TEST_SPRINTF(Lf_zrwth_zrpc_hash_negt, "%#0.0Lf", -123.456L, long double)
TEST_SPRINTF(Lf_zrwth_zrpc_plus_small, "%+0.0Lf", -0.0000123456L, long double)
TEST_SPRINTF(Lf_zrwth_zrpc_spac_small, "% 0.0Lf", -0.0000123456L, long double)
TEST_SPRINTF(Lf_zrwth_zrpc_hash_small, "%#0.0Lf", -0.0000123456L, long double)
TEST_SPRINTF(Lf_zrwth_zrpc_plus_large, "%+0.0Lf", 123456789.0L, long double)
TEST_SPRINTF(Lf_zrwth_zrpc_spac_large, "% 0.0Lf", 123456789.0L, long double)
TEST_SPRINTF(Lf_zrwth_zrpc_hash_large, "%#0.0Lf", 123456789.0L, long double)

TEST_SPRINTF_2(Lf_dynamic_width_post, "%*Lf", 10, 123.456L, long double)
TEST_SPRINTF_2(Lf_dynamic_width_negt, "%*Lf", 10, -123.456L, long double)
TEST_SPRINTF_2(Lf_dynamic_width_small, "%*Lf", 10, -0.0000123456L, long double)
TEST_SPRINTF_2(Lf_dynamic_width_large, "%*Lf", 10, 123456789.0L, long double)

TEST_SPRINTF_2(Lf_dynamic_prec_post, "%.*Lf", 5, 123.456L, long double)
TEST_SPRINTF_2(Lf_dynamic_prec_negt, "%.*Lf", 5, -123.456L, long double)
TEST_SPRINTF_2(Lf_dynamic_prec_small, "%.*Lf", 5, -0.0000123456L, long double)
TEST_SPRINTF_2(Lf_dynamic_prec_large, "%.*Lf", 5, 123456789.0L, long double)

TEST_SPRINTF_3(Lf_dynamic_width_prec_post, "%*.*Lf", 10, 5, 123.456L,
               long double)
TEST_SPRINTF_3(Lf_dynamic_width_prec_negt, "%*.*Lf", 10, 5, -123.456L,
               long double)
TEST_SPRINTF_3(Lf_dynamic_width_prec_small, "%*.*Lf", 10, 5, -0.0000123456L,
               long double)
TEST_SPRINTF_3(Lf_dynamic_width_prec_large, "%*.*Lf", 10, 5, 123456789.0L,
               long double)

// =========================================================================

TEST_SPRINTF(Lg_mins_post, "%-Lg", 123.456L, long double)
TEST_SPRINTF(Lg_plus_post, "%+Lg", 123.456L, long double)
TEST_SPRINTF(Lg_spac_post, "% Lg", 123.456L, long double)
TEST_SPRINTF(Lg_hash_post, "%#Lg", 123.456L, long double)
TEST_SPRINTF(Lg_fzer_post, "%0Lg", 123.456L, long double)
TEST_SPRINTF(Lg_mins_negt, "%-Lg", -123.456L, long double)
TEST_SPRINTF(Lg_plus_negt, "%+Lg", -123.456L, long double)
TEST_SPRINTF(Lg_spac_negt, "% Lg", -123.456L, long double)
TEST_SPRINTF(Lg_hash_negt, "%#Lg", -123.456L, long double)
TEST_SPRINTF(Lg_fzer_negt, "%0Lg", -123.456L, long double)
TEST_SPRINTF(Lg_mins_small, "%-Lg", -0.0000123456L, long double)
TEST_SPRINTF(Lg_plus_small, "%+Lg", -0.0000123456L, long double)
TEST_SPRINTF(Lg_spac_small, "% Lg", -0.0000123456L, long double)
TEST_SPRINTF(Lg_hash_small, "%#Lg", -0.0000123456L, long double)
TEST_SPRINTF(Lg_fzer_small, "%0Lg", -0.0000123456L, long double)
TEST_SPRINTF(Lg_mins_large, "%-Lg", 123456789.0L, long double)
TEST_SPRINTF(Lg_plus_large, "%+Lg", 123456789.0L, long double)
TEST_SPRINTF(Lg_spac_large, "% Lg", 123456789.0L, long double)
TEST_SPRINTF(Lg_hash_large, "%#Lg", 123456789.0L, long double)
TEST_SPRINTF(Lg_fzer_large, "%0Lg", 123456789.0L, long double)

TEST_SPRINTF(Lg_width_post, "%5Lg", 123.456L, long double)
TEST_SPRINTF(Lg_zrpc_post, "%.0Lg", 123.456L, long double)
TEST_SPRINTF(Lg_prec_post, "%.5Lg", 123.456L, long double)
TEST_SPRINTF(Lg_width_negt, "%5Lg", -123.456L, long double)
TEST_SPRINTF(Lg_zrpc_negt, "%.0Lg", -123.456L, long double)
TEST_SPRINTF(Lg_prec_negt, "%.5Lg", -123.456L, long double)
TEST_SPRINTF(Lg_width_small, "%5Lg", -0.0000123456L, long double)
TEST_SPRINTF(Lg_zrpc_small, "%.0Lg", -0.0000123456L, long double)
TEST_SPRINTF(Lg_prec_small, "%.5Lg", -0.0000123456L, long double)
TEST_SPRINTF(Lg_width_large, "%5Lg", 123456789.0L, long double)
TEST_SPRINTF(Lg_zrpc_large, "%.0Lg", 123456789.0L, long double)
TEST_SPRINTF(Lg_prec_large, "%.5Lg", 123456789.0L, long double)

TEST_SPRINTF(Lg_width_prec_post, "%10.5Lg", 123.456L, long double)
TEST_SPRINTF(Lg_width_prec_negt, "%10.5Lg", -123.456L, long double)
TEST_SPRINTF(Lg_width_prec_small, "%10.5Lg", -0.0000123456L, long double)
TEST_SPRINTF(Lg_width_prec_large, "%10.5Lg", 123456789.0L, long double)

TEST_SPRINTF(Lg_width_mins_post, "%-5Lg", 123.456L, long double)
TEST_SPRINTF(Lg_width_plus_post, "%+5Lg", 123.456L, long double)
TEST_SPRINTF(Lg_width_spac_post, "% 5Lg", 123.456L, long double)
TEST_SPRINTF(Lg_width_hash_post, "%#5Lg", 123.456L, long double)
TEST_SPRINTF(Lg_width_fzer_post, "%05Lg", 123.456L, long double)
TEST_SPRINTF(Lg_width_mins_negt, "%-5Lg", -123.456L, long double)
TEST_SPRINTF(Lg_width_plus_negt, "%+5Lg", -123.456L, long double)
TEST_SPRINTF(Lg_width_spac_negt, "% 5Lg", -123.456L, long double)
TEST_SPRINTF(Lg_width_hash_negt, "%#5Lg", -123.456L, long double)
TEST_SPRINTF(Lg_width_fzer_negt, "%05Lg", -123.456L, long double)
TEST_SPRINTF(Lg_width_mins_small, "%-5Lg", -0.0000123456L, long double)
TEST_SPRINTF(Lg_width_plus_small, "%+5Lg", -0.0000123456L, long double)
TEST_SPRINTF(Lg_width_spac_small, "% 5Lg", -0.0000123456L, long double)
TEST_SPRINTF(Lg_width_hash_small, "%#5Lg", -0.0000123456L, long double)
TEST_SPRINTF(Lg_width_fzer_small, "%05Lg", -0.0000123456L, long double)
TEST_SPRINTF(Lg_width_mins_large, "%-5Lg", 123456789.0L, long double)
TEST_SPRINTF(Lg_width_plus_large, "%+5Lg", 123456789.0L, long double)
TEST_SPRINTF(Lg_width_spac_large, "% 5Lg", 123456789.0L, long double)
TEST_SPRINTF(Lg_width_hash_large, "%#5Lg", 123456789.0L, long double)
TEST_SPRINTF(Lg_width_fzer_large, "%05Lg", 123456789.0L, long double)

TEST_SPRINTF(Lg_zrwth_plus_post, "%+0Lg", 123.456L, long double)
TEST_SPRINTF(Lg_zrwth_spac_post, "% 0Lg", 123.456L, long double)
TEST_SPRINTF(Lg_zrwth_hash_post, "%#0Lg", 123.456L, long double)
TEST_SPRINTF(Lg_zrwth_plus_negt, "%+0Lg", -123.456L, long double)
TEST_SPRINTF(Lg_zrwth_spac_negt, "% 0Lg", -123.456L, long double)
TEST_SPRINTF(Lg_zrwth_hash_negt, "%#0Lg", -123.456L, long double)
TEST_SPRINTF(Lg_zrwth_plus_small, "%+0Lg", -0.0000123456L, long double)
TEST_SPRINTF(Lg_zrwth_spac_small, "% 0Lg", -0.0000123456L, long double)
TEST_SPRINTF(Lg_zrwth_hash_small, "%#0Lg", -0.0000123456L, long double)
TEST_SPRINTF(Lg_zrwth_plus_large, "%+0Lg", 123456789.0L, long double)
TEST_SPRINTF(Lg_zrwth_spac_large, "% 0Lg", 123456789.0L, long double)
TEST_SPRINTF(Lg_zrwth_hash_large, "%#0Lg", 123456789.0L, long double)

TEST_SPRINTF(Lg_prec_mins_post, "%-.5Lg", 123.456L, long double)
TEST_SPRINTF(Lg_prec_plus_post, "%+.5Lg", 123.456L, long double)
TEST_SPRINTF(Lg_prec_spac_post, "% .5Lg", 123.456L, long double)
TEST_SPRINTF(Lg_prec_hash_post, "%#.5Lg", 123.456L, long double)
TEST_SPRINTF(Lg_prec_fzer_post, "%0.5Lg", 123.456L, long double)
TEST_SPRINTF(Lg_prec_mins_negt, "%-.5Lg", -123.456L, long double)
TEST_SPRINTF(Lg_prec_plus_negt, "%+.5Lg", -123.456L, long double)
TEST_SPRINTF(Lg_prec_spac_negt, "% .5Lg", -123.456L, long double)
TEST_SPRINTF(Lg_prec_hash_negt, "%#.5Lg", -123.456L, long double)
TEST_SPRINTF(Lg_prec_fzer_negt, "%0.5Lg", -123.456L, long double)
TEST_SPRINTF(Lg_prec_mins_small, "%-.5Lg", -0.0000123456L, long double)
TEST_SPRINTF(Lg_prec_plus_small, "%+.5Lg", -0.0000123456L, long double)
TEST_SPRINTF(Lg_prec_spac_small, "% .5Lg", -0.0000123456L, long double)
TEST_SPRINTF(Lg_prec_hash_small, "%#.5Lg", -0.0000123456L, long double)
TEST_SPRINTF(Lg_prec_fzer_small, "%0.5Lg", -0.0000123456L, long double)
TEST_SPRINTF(Lg_prec_mins_large, "%-.5Lg", 123456789.0L, long double)
TEST_SPRINTF(Lg_prec_plus_large, "%+.5Lg", 123456789.0L, long double)
TEST_SPRINTF(Lg_prec_spac_large, "% .5Lg", 123456789.0L, long double)
TEST_SPRINTF(Lg_prec_hash_large, "%#.5Lg", 123456789.0L, long double)
TEST_SPRINTF(Lg_prec_fzer_large, "%0.5Lg", 123456789.0L, long double)

TEST_SPRINTF(Lg_zrpc_mins_post, "%-.0Lg", 123.456L, long double)
TEST_SPRINTF(Lg_zrpc_plus_post, "%+.0Lg", 123.456L, long double)
TEST_SPRINTF(Lg_zrpc_spac_post, "% .0Lg", 123.456L, long double)
TEST_SPRINTF(Lg_zrpc_hash_post, "%#.0Lg", 123.456L, long double)
TEST_SPRINTF(Lg_zrpc_fzer_post, "%0.0Lg", 123.456L, long double)
TEST_SPRINTF(Lg_zrpc_mins_negt, "%-.0Lg", -123.456L, long double)
TEST_SPRINTF(Lg_zrpc_plus_negt, "%+.0Lg", -123.456L, long double)
TEST_SPRINTF(Lg_zrpc_spac_negt, "% .0Lg", -123.456L, long double)
TEST_SPRINTF(Lg_zrpc_hash_negt, "%#.0Lg", -123.456L, long double)
TEST_SPRINTF(Lg_zrpc_fzer_negt, "%0.0Lg", -123.456L, long double)
TEST_SPRINTF(Lg_zrpc_mins_small, "%-.0Lg", -0.0000123456L, long double)
TEST_SPRINTF(Lg_zrpc_plus_small, "%+.0Lg", -0.0000123456L, long double)
TEST_SPRINTF(Lg_zrpc_spac_small, "% .0Lg", -0.0000123456L, long double)
TEST_SPRINTF(Lg_zrpc_hash_small, "%#.0Lg", -0.0000123456L, long double)
TEST_SPRINTF(Lg_zrpc_fzer_small, "%0.0Lg", -0.0000123456L, long double)
TEST_SPRINTF(Lg_zrpc_mins_large, "%-.0Lg", 123456789.0L, long double)
TEST_SPRINTF(Lg_zrpc_plus_large, "%+.0Lg", 123456789.0L, long double)
TEST_SPRINTF(Lg_zrpc_spac_large, "% .0Lg", 123456789.0L, long double)
TEST_SPRINTF(Lg_zrpc_hash_large, "%#.0Lg", 123456789.0L, long double)
TEST_SPRINTF(Lg_zrpc_fzer_large, "%0.0Lg", 123456789.0L, long double)

TEST_SPRINTF(Lg_width_prec_mins_post, "%-10.5Lg", 123.456L, long double)
TEST_SPRINTF(Lg_width_prec_plus_post, "%+10.5Lg", 123.456L, long double)
TEST_SPRINTF(Lg_width_prec_spac_post, "% 10.5Lg", 123.456L, long double)
TEST_SPRINTF(Lg_width_prec_hash_post, "%#10.5Lg", 123.456L, long double)
TEST_SPRINTF(Lg_width_prec_fzer_post, "%010.5Lg", 123.456L, long double)
TEST_SPRINTF(Lg_width_prec_mins_negt, "%-10.5Lg", -123.456L, long double)
TEST_SPRINTF(Lg_width_prec_plus_negt, "%+10.5Lg", -123.456L, long double)
TEST_SPRINTF(Lg_width_prec_spac_negt, "% 10.5Lg", -123.456L, long double)
TEST_SPRINTF(Lg_width_prec_hash_negt, "%#10.5Lg", -123.456L, long double)
TEST_SPRINTF(Lg_width_prec_fzer_negt, "%010.5Lg", -123.456L, long double)
TEST_SPRINTF(Lg_width_prec_mins_small, "%-10.5Lg", -0.0000123456L, long double)
TEST_SPRINTF(Lg_width_prec_plus_small, "%+10.5Lg", -0.0000123456L, long double)
TEST_SPRINTF(Lg_width_prec_spac_small, "% 10.5Lg", -0.0000123456L, long double)
TEST_SPRINTF(Lg_width_prec_hash_small, "%#10.5Lg", -0.0000123456L, long double)
TEST_SPRINTF(Lg_width_prec_fzer_small, "%010.5Lg", -0.0000123456L, long double)
TEST_SPRINTF(Lg_width_prec_mins_large, "%-10.5Lg", 123456789.0L, long double)
TEST_SPRINTF(Lg_width_prec_plus_large, "%+10.5Lg", 123456789.0L, long double)
TEST_SPRINTF(Lg_width_prec_spac_large, "% 10.5Lg", 123456789.0L, long double)
TEST_SPRINTF(Lg_width_prec_hash_large, "%#10.5Lg", 123456789.0L, long double)
TEST_SPRINTF(Lg_width_prec_fzer_large, "%010.5Lg", 123456789.0L, long double)

TEST_SPRINTF(Lg_zrwth_zrpc_plus_post, "%+0.0Lg", 123.456L, long double)
TEST_SPRINTF(Lg_zrwth_zrpc_spac_post, "% 0.0Lg", 123.456L, long double)
TEST_SPRINTF(Lg_zrwth_zrpc_hash_post, "%#0.0Lg", 123.456L, long double)
TEST_SPRINTF(Lg_zrwth_zrpc_plus_negt, "%+0.0Lg", -123.456L, long double)
TEST_SPRINTF(Lg_zrwth_zrpc_spac_negt, "% 0.0Lg", -123.456L, long double)
TEST_SPRINTF(Lg_zrwth_zrpc_hash_negt, "%#0.0Lg", -123.456L, long double)
TEST_SPRINTF(Lg_zrwth_zrpc_plus_small, "%+0.0Lg", -0.0000123456L, long double)
TEST_SPRINTF(Lg_zrwth_zrpc_spac_small, "% 0.0Lg", -0.0000123456L, long double)
TEST_SPRINTF(Lg_zrwth_zrpc_hash_small, "%#0.0Lg", -0.0000123456L, long double)
TEST_SPRINTF(Lg_zrwth_zrpc_plus_large, "%+0.0Lg", 123456789.0L, long double)
TEST_SPRINTF(Lg_zrwth_zrpc_spac_large, "% 0.0Lg", 123456789.0L, long double)
TEST_SPRINTF(Lg_zrwth_zrpc_hash_large, "%#0.0Lg", 123456789.0L, long double)

TEST_SPRINTF_2(Lg_dynamic_width_post, "%*Lg", 10, 123.456L, long double)
TEST_SPRINTF_2(Lg_dynamic_width_negt, "%*Lg", 10, -123.456L, long double)
TEST_SPRINTF_2(Lg_dynamic_width_small, "%*Lg", 10, -0.0000123456L, long double)
TEST_SPRINTF_2(Lg_dynamic_width_large, "%*Lg", 10, 123456789.0L, long double)

TEST_SPRINTF_2(Lg_dynamic_prec_post, "%.*Lg", 5, 123.456L, long double)
TEST_SPRINTF_2(Lg_dynamic_prec_negt, "%.*Lg", 5, -123.456L, long double)
TEST_SPRINTF_2(Lg_dynamic_prec_small, "%.*Lg", 5, -0.0000123456L, long double)
TEST_SPRINTF_2(Lg_dynamic_prec_large, "%.*Lg", 5, 123456789.0L, long double)

TEST_SPRINTF_3(Lg_dynamic_width_prec_post, "%*.*Lg", 10, 5, 123.456L,
               long double)
TEST_SPRINTF_3(Lg_dynamic_width_prec_negt, "%*.*Lg", 10, 5, -123.456L,
               long double)
TEST_SPRINTF_3(Lg_dynamic_width_prec_small, "%*.*Lg", 10, 5, -0.0000123456L,
               long double)
TEST_SPRINTF_3(Lg_dynamic_width_prec_large, "%*.*Lg", 10, 5, 123456789.0L,
               long double)

// =========================================================================

TEST_SPRINTF(LG_mins_post, "%-LG", 123.456L, long double)
TEST_SPRINTF(LG_plus_post, "%+LG", 123.456L, long double)
TEST_SPRINTF(LG_spac_post, "% LG", 123.456L, long double)
TEST_SPRINTF(LG_hash_post, "%#LG", 123.456L, long double)
TEST_SPRINTF(LG_fzer_post, "%0LG", 123.456L, long double)
TEST_SPRINTF(LG_mins_negt, "%-LG", -123.456L, long double)
TEST_SPRINTF(LG_plus_negt, "%+LG", -123.456L, long double)
TEST_SPRINTF(LG_spac_negt, "% LG", -123.456L, long double)
TEST_SPRINTF(LG_hash_negt, "%#LG", -123.456L, long double)
TEST_SPRINTF(LG_fzer_negt, "%0LG", -123.456L, long double)
TEST_SPRINTF(LG_mins_small, "%-LG", -0.0000123456L, long double)
TEST_SPRINTF(LG_plus_small, "%+LG", -0.0000123456L, long double)
TEST_SPRINTF(LG_spac_small, "% LG", -0.0000123456L, long double)
TEST_SPRINTF(LG_hash_small, "%#LG", -0.0000123456L, long double)
TEST_SPRINTF(LG_fzer_small, "%0LG", -0.0000123456L, long double)
TEST_SPRINTF(LG_mins_large, "%-LG", 123456789.0L, long double)
TEST_SPRINTF(LG_plus_large, "%+LG", 123456789.0L, long double)
TEST_SPRINTF(LG_spac_large, "% LG", 123456789.0L, long double)
TEST_SPRINTF(LG_hash_large, "%#LG", 123456789.0L, long double)
TEST_SPRINTF(LG_fzer_large, "%0LG", 123456789.0L, long double)

TEST_SPRINTF(LG_width_post, "%5LG", 123.456L, long double)
TEST_SPRINTF(LG_zrpc_post, "%.0LG", 123.456L, long double)
TEST_SPRINTF(LG_prec_post, "%.5LG", 123.456L, long double)
TEST_SPRINTF(LG_width_negt, "%5LG", -123.456L, long double)
TEST_SPRINTF(LG_zrpc_negt, "%.0LG", -123.456L, long double)
TEST_SPRINTF(LG_prec_negt, "%.5LG", -123.456L, long double)
TEST_SPRINTF(LG_width_small, "%5LG", -0.0000123456L, long double)
TEST_SPRINTF(LG_zrpc_small, "%.0LG", -0.0000123456L, long double)
TEST_SPRINTF(LG_prec_small, "%.5LG", -0.0000123456L, long double)
TEST_SPRINTF(LG_width_large, "%5LG", 123456789.0L, long double)
TEST_SPRINTF(LG_zrpc_large, "%.0LG", 123456789.0L, long double)
TEST_SPRINTF(LG_prec_large, "%.5LG", 123456789.0L, long double)

TEST_SPRINTF(LG_width_prec_post, "%10.5LG", 123.456L, long double)
TEST_SPRINTF(LG_width_prec_negt, "%10.5LG", -123.456L, long double)
TEST_SPRINTF(LG_width_prec_small, "%10.5LG", -0.0000123456L, long double)
TEST_SPRINTF(LG_width_prec_large, "%10.5LG", 123456789.0L, long double)

TEST_SPRINTF(LG_width_mins_post, "%-5LG", 123.456L, long double)
TEST_SPRINTF(LG_width_plus_post, "%+5LG", 123.456L, long double)
TEST_SPRINTF(LG_width_spac_post, "% 5LG", 123.456L, long double)
TEST_SPRINTF(LG_width_hash_post, "%#5LG", 123.456L, long double)
TEST_SPRINTF(LG_width_fzer_post, "%05LG", 123.456L, long double)
TEST_SPRINTF(LG_width_mins_negt, "%-5LG", -123.456L, long double)
TEST_SPRINTF(LG_width_plus_negt, "%+5LG", -123.456L, long double)
TEST_SPRINTF(LG_width_spac_negt, "% 5LG", -123.456L, long double)
TEST_SPRINTF(LG_width_hash_negt, "%#5LG", -123.456L, long double)
TEST_SPRINTF(LG_width_fzer_negt, "%05LG", -123.456L, long double)
TEST_SPRINTF(LG_width_mins_small, "%-5LG", -0.0000123456L, long double)
TEST_SPRINTF(LG_width_plus_small, "%+5LG", -0.0000123456L, long double)
TEST_SPRINTF(LG_width_spac_small, "% 5LG", -0.0000123456L, long double)
TEST_SPRINTF(LG_width_hash_small, "%#5LG", -0.0000123456L, long double)
TEST_SPRINTF(LG_width_fzer_small, "%05LG", -0.0000123456L, long double)
TEST_SPRINTF(LG_width_mins_large, "%-5LG", 123456789.0L, long double)
TEST_SPRINTF(LG_width_plus_large, "%+5LG", 123456789.0L, long double)
TEST_SPRINTF(LG_width_spac_large, "% 5LG", 123456789.0L, long double)
TEST_SPRINTF(LG_width_hash_large, "%#5LG", 123456789.0L, long double)
TEST_SPRINTF(LG_width_fzer_large, "%05LG", 123456789.0L, long double)

TEST_SPRINTF(LG_zrwth_plus_post, "%+0LG", 123.456L, long double)
TEST_SPRINTF(LG_zrwth_spac_post, "% 0LG", 123.456L, long double)
TEST_SPRINTF(LG_zrwth_hash_post, "%#0LG", 123.456L, long double)
TEST_SPRINTF(LG_zrwth_plus_negt, "%+0LG", -123.456L, long double)
TEST_SPRINTF(LG_zrwth_spac_negt, "% 0LG", -123.456L, long double)
TEST_SPRINTF(LG_zrwth_hash_negt, "%#0LG", -123.456L, long double)
TEST_SPRINTF(LG_zrwth_plus_small, "%+0LG", -0.0000123456L, long double)
TEST_SPRINTF(LG_zrwth_spac_small, "% 0LG", -0.0000123456L, long double)
TEST_SPRINTF(LG_zrwth_hash_small, "%#0LG", -0.0000123456L, long double)
TEST_SPRINTF(LG_zrwth_plus_large, "%+0LG", 123456789.0L, long double)
TEST_SPRINTF(LG_zrwth_spac_large, "% 0LG", 123456789.0L, long double)
TEST_SPRINTF(LG_zrwth_hash_large, "%#0LG", 123456789.0L, long double)

TEST_SPRINTF(LG_prec_mins_post, "%-.5LG", 123.456L, long double)
TEST_SPRINTF(LG_prec_plus_post, "%+.5LG", 123.456L, long double)
TEST_SPRINTF(LG_prec_spac_post, "% .5LG", 123.456L, long double)
TEST_SPRINTF(LG_prec_hash_post, "%#.5LG", 123.456L, long double)
TEST_SPRINTF(LG_prec_fzer_post, "%0.5LG", 123.456L, long double)
TEST_SPRINTF(LG_prec_mins_negt, "%-.5LG", -123.456L, long double)
TEST_SPRINTF(LG_prec_plus_negt, "%+.5LG", -123.456L, long double)
TEST_SPRINTF(LG_prec_spac_negt, "% .5LG", -123.456L, long double)
TEST_SPRINTF(LG_prec_hash_negt, "%#.5LG", -123.456L, long double)
TEST_SPRINTF(LG_prec_fzer_negt, "%0.5LG", -123.456L, long double)
TEST_SPRINTF(LG_prec_mins_small, "%-.5LG", -0.0000123456L, long double)
TEST_SPRINTF(LG_prec_plus_small, "%+.5LG", -0.0000123456L, long double)
TEST_SPRINTF(LG_prec_spac_small, "% .5LG", -0.0000123456L, long double)
TEST_SPRINTF(LG_prec_hash_small, "%#.5LG", -0.0000123456L, long double)
TEST_SPRINTF(LG_prec_fzer_small, "%0.5LG", -0.0000123456L, long double)
TEST_SPRINTF(LG_prec_mins_large, "%-.5LG", 123456789.0L, long double)
TEST_SPRINTF(LG_prec_plus_large, "%+.5LG", 123456789.0L, long double)
TEST_SPRINTF(LG_prec_spac_large, "% .5LG", 123456789.0L, long double)
TEST_SPRINTF(LG_prec_hash_large, "%#.5LG", 123456789.0L, long double)
TEST_SPRINTF(LG_prec_fzer_large, "%0.5LG", 123456789.0L, long double)

TEST_SPRINTF(LG_zrpc_mins_post, "%-.0LG", 123.456L, long double)
TEST_SPRINTF(LG_zrpc_plus_post, "%+.0LG", 123.456L, long double)
TEST_SPRINTF(LG_zrpc_spac_post, "% .0LG", 123.456L, long double)
TEST_SPRINTF(LG_zrpc_hash_post, "%#.0LG", 123.456L, long double)
TEST_SPRINTF(LG_zrpc_fzer_post, "%0.0LG", 123.456L, long double)
TEST_SPRINTF(LG_zrpc_mins_negt, "%-.0LG", -123.456L, long double)
TEST_SPRINTF(LG_zrpc_plus_negt, "%+.0LG", -123.456L, long double)
TEST_SPRINTF(LG_zrpc_spac_negt, "% .0LG", -123.456L, long double)
TEST_SPRINTF(LG_zrpc_hash_negt, "%#.0LG", -123.456L, long double)
TEST_SPRINTF(LG_zrpc_fzer_negt, "%0.0LG", -123.456L, long double)
TEST_SPRINTF(LG_zrpc_mins_small, "%-.0LG", -0.0000123456L, long double)
TEST_SPRINTF(LG_zrpc_plus_small, "%+.0LG", -0.0000123456L, long double)
TEST_SPRINTF(LG_zrpc_spac_small, "% .0LG", -0.0000123456L, long double)
TEST_SPRINTF(LG_zrpc_hash_small, "%#.0LG", -0.0000123456L, long double)
TEST_SPRINTF(LG_zrpc_fzer_small, "%0.0LG", -0.0000123456L, long double)
TEST_SPRINTF(LG_zrpc_mins_large, "%-.0LG", 123456789.0L, long double)
TEST_SPRINTF(LG_zrpc_plus_large, "%+.0LG", 123456789.0L, long double)
TEST_SPRINTF(LG_zrpc_spac_large, "% .0LG", 123456789.0L, long double)
TEST_SPRINTF(LG_zrpc_hash_large, "%#.0LG", 123456789.0L, long double)
TEST_SPRINTF(LG_zrpc_fzer_large, "%0.0LG", 123456789.0L, long double)

TEST_SPRINTF(LG_width_prec_mins_post, "%-10.5LG", 123.456L, long double)
TEST_SPRINTF(LG_width_prec_plus_post, "%+10.5LG", 123.456L, long double)
TEST_SPRINTF(LG_width_prec_spac_post, "% 10.5LG", 123.456L, long double)
TEST_SPRINTF(LG_width_prec_hash_post, "%#10.5LG", 123.456L, long double)
TEST_SPRINTF(LG_width_prec_fzer_post, "%010.5LG", 123.456L, long double)
TEST_SPRINTF(LG_width_prec_mins_negt, "%-10.5LG", -123.456L, long double)
TEST_SPRINTF(LG_width_prec_plus_negt, "%+10.5LG", -123.456L, long double)
TEST_SPRINTF(LG_width_prec_spac_negt, "% 10.5LG", -123.456L, long double)
TEST_SPRINTF(LG_width_prec_hash_negt, "%#10.5LG", -123.456L, long double)
TEST_SPRINTF(LG_width_prec_fzer_negt, "%010.5LG", -123.456L, long double)
TEST_SPRINTF(LG_width_prec_mins_small, "%-10.5LG", -0.0000123456L, long double)
TEST_SPRINTF(LG_width_prec_plus_small, "%+10.5LG", -0.0000123456L, long double)
TEST_SPRINTF(LG_width_prec_spac_small, "% 10.5LG", -0.0000123456L, long double)
TEST_SPRINTF(LG_width_prec_hash_small, "%#10.5LG", -0.0000123456L, long double)
TEST_SPRINTF(LG_width_prec_fzer_small, "%010.5LG", -0.0000123456L, long double)
TEST_SPRINTF(LG_width_prec_mins_large, "%-10.5LG", 123456789.0L, long double)
TEST_SPRINTF(LG_width_prec_plus_large, "%+10.5LG", 123456789.0L, long double)
TEST_SPRINTF(LG_width_prec_spac_large, "% 10.5LG", 123456789.0L, long double)
TEST_SPRINTF(LG_width_prec_hash_large, "%#10.5LG", 123456789.0L, long double)
TEST_SPRINTF(LG_width_prec_fzer_large, "%010.5LG", 123456789.0L, long double)

TEST_SPRINTF(LG_zrwth_zrpc_plus_post, "%+0.0LG", 123.456L, long double)
TEST_SPRINTF(LG_zrwth_zrpc_spac_post, "% 0.0LG", 123.456L, long double)
TEST_SPRINTF(LG_zrwth_zrpc_hash_post, "%#0.0LG", 123.456L, long double)
TEST_SPRINTF(LG_zrwth_zrpc_plus_negt, "%+0.0LG", -123.456L, long double)
TEST_SPRINTF(LG_zrwth_zrpc_spac_negt, "% 0.0LG", -123.456L, long double)
TEST_SPRINTF(LG_zrwth_zrpc_hash_negt, "%#0.0LG", -123.456L, long double)
TEST_SPRINTF(LG_zrwth_zrpc_plus_small, "%+0.0LG", -0.0000123456L, long double)
TEST_SPRINTF(LG_zrwth_zrpc_spac_small, "% 0.0LG", -0.0000123456L, long double)
TEST_SPRINTF(LG_zrwth_zrpc_hash_small, "%#0.0LG", -0.0000123456L, long double)
TEST_SPRINTF(LG_zrwth_zrpc_plus_large, "%+0.0LG", 123456789.0L, long double)
TEST_SPRINTF(LG_zrwth_zrpc_spac_large, "% 0.0LG", 123456789.0L, long double)
TEST_SPRINTF(LG_zrwth_zrpc_hash_large, "%#0.0LG", 123456789.0L, long double)

TEST_SPRINTF_2(LG_dynamic_width_post, "%*LG", 10, 123.456L, long double)
TEST_SPRINTF_2(LG_dynamic_width_negt, "%*LG", 10, -123.456L, long double)
TEST_SPRINTF_2(LG_dynamic_width_small, "%*LG", 10, -0.0000123456L, long double)
TEST_SPRINTF_2(LG_dynamic_width_large, "%*LG", 10, 123456789.0L, long double)

TEST_SPRINTF_2(LG_dynamic_prec_post, "%.*LG", 5, 123.456L, long double)
TEST_SPRINTF_2(LG_dynamic_prec_negt, "%.*LG", 5, -123.456L, long double)
TEST_SPRINTF_2(LG_dynamic_prec_small, "%.*LG", 5, -0.0000123456L, long double)
TEST_SPRINTF_2(LG_dynamic_prec_large, "%.*LG", 5, 123456789.0L, long double)

TEST_SPRINTF_3(LG_dynamic_width_prec_post, "%*.*LG", 10, 5, 123.456L,
               long double)
TEST_SPRINTF_3(LG_dynamic_width_prec_negt, "%*.*LG", 10, 5, -123.456L,
               long double)
TEST_SPRINTF_3(LG_dynamic_width_prec_small, "%*.*LG", 10, 5, -0.0000123456L,
               long double)
TEST_SPRINTF_3(LG_dynamic_width_prec_large, "%*.*LG", 10, 5, 123456789.0L,
               long double)
#pragma endregion

// =========================================================================
// Тесты для строковых спецификаторов NULL
// =========================================================================
#pragma region
TEST_SPRINTF(s_mins_null, "%-s", NULL, char *)
TEST_SPRINTF(s_width_null, "%5s", NULL, char *)
TEST_SPRINTF(s_zrpc_null, "%.0s", NULL, char *)
TEST_SPRINTF(s_prec_null, "%.5s", NULL, char *)
TEST_SPRINTF(s_width_prec_null, "%10.5s", NULL, char *)
TEST_SPRINTF(s_width_mins_null, "%-5s", NULL, char *)
TEST_SPRINTF(s_prec_mins_null, "%-.5s", NULL, char *)
TEST_SPRINTF(s_zrpc_mins_null, "%-.0s", NULL, char *)
TEST_SPRINTF(s_width_prec_mins_null, "%-10.5s", NULL, char *)
TEST_SPRINTF_2(s_dynamic_width_null, "%*s", 10, NULL, char *)
TEST_SPRINTF_2(s_dynamic_prec_null, "%.*s", 5, NULL, char *)
TEST_SPRINTF_3(s_dynamic_width_prec_null, "%*.*s", 10, 5, NULL, char *)

// =========================================================================

TEST_SPRINTF(s_mins_zero, "%-s", 0, char *)
TEST_SPRINTF(s_width_zero, "%5s", 0, char *)
TEST_SPRINTF(s_zrpc_zero, "%.0s", 0, char *)
TEST_SPRINTF(s_prec_zero, "%.5s", 0, char *)
TEST_SPRINTF(s_width_prec_zero, "%10.5s", 0, char *)
TEST_SPRINTF(s_width_mins_zero, "%-5s", 0, char *)
TEST_SPRINTF(s_prec_mins_zero, "%-.5s", 0, char *)
TEST_SPRINTF(s_zrpc_mins_zero, "%-.0s", 0, char *)
TEST_SPRINTF(s_width_prec_mins_zero, "%-10.5s", 0, char *)
TEST_SPRINTF_2(s_dynamic_width_zero, "%*s", 10, 0, char *)
TEST_SPRINTF_2(s_dynamic_prec_zero, "%.*s", 5, 0, char *)
TEST_SPRINTF_3(s_dynamic_width_prec_zero, "%*.*s", 10, 5, 0, char *)

// =========================================================================

TEST_SPRINTF(c_mins_zero, "%-c", 0, char)
TEST_SPRINTF(c_width_zero, "%5c", 0, char)
TEST_SPRINTF(c_width_mins_zero, "%-5c", 0, char)
TEST_SPRINTF_2(c_dynamic_width_zero, "%*c", 10, 0, char)
#pragma endregion

// =========================================================================
// Тесты для строковых спецификаторов %s %c
// =========================================================================
#pragma region
TEST_SPRINTF(s_mins_str, "%-s", "Hello", char *)
TEST_SPRINTF(s_width_str, "%5s", "Hello", char *)
TEST_SPRINTF(s_zrpc_str, "%.0s", "Hello", char *)
TEST_SPRINTF(s_prec_str, "%.5s", "Hello", char *)
TEST_SPRINTF(s_width_prec_str, "%10.5s", "Hello", char *)
TEST_SPRINTF(s_width_mins_str, "%-5s", "Hello", char *)
TEST_SPRINTF(s_prec_mins_str, "%-.5s", "Hello", char *)
TEST_SPRINTF(s_zrpc_mins_str, "%-.0s", "Hello", char *)
TEST_SPRINTF(s_width_prec_mins_str, "%-10.5s", "Hello", char *)
TEST_SPRINTF_2(s_dynamic_width_str, "%*s", 10, "Hello", char *)
TEST_SPRINTF_2(s_dynamic_prec_str, "%.*s", 5, "Hello", char *)
TEST_SPRINTF_3(s_dynamic_width_prec_str, "%*.*s", 10, 5, "Hello", char *)

// =========================================================================

TEST_SPRINTF(c_mins_char, "%-c", 'A', char)
TEST_SPRINTF(c_width_char, "%5c", 'A', char)
TEST_SPRINTF(c_width_mins_char, "%-5c", 'A', char)
TEST_SPRINTF_2(c_dynamic_width_char, "%*c", 10, 'A', char)
#pragma endregion

// =========================================================================
// Тесты для указателя %p
// =========================================================================
#pragma region
TEST_SPRINTF(p_mins_null, "%-p", NULL, void *)

TEST_SPRINTF(p_width_null, "%5p", NULL, void *)

TEST_SPRINTF(p_width_mins_null, "%-5p", NULL, void *)

TEST_SPRINTF_2(p_dynamic_width_null, "%*p", 10, NULL, void *)

// =========================================================================

TEST_SPRINTF(p_mins_ptr, "%-p", (void *)0x1234abcd, void *)

TEST_SPRINTF(p_width_ptr, "%5p", (void *)0x1234abcd, void *)

TEST_SPRINTF(p_width_mins_ptr, "%-5p", (void *)0x1234abcd, void *)

TEST_SPRINTF_2(p_dynamic_width_ptr, "%*p", 10, (void *)0x1234abcd, void *)

#pragma endregion

// ================================================================================================================================
//                                                      ДЛИННАЯ СТРОКА И СИМВОЛ
//                                                             (%ls %lc)
// ================================================================================================================================
// ================================================================================================================================

// ================================================================================================================================
//                                                         БЕЗ СПЕЦИФИКАТОРА
// ================================================================================================================================
// ================================================================================================================================

// =========================================================================
// Длинная строка %ls
// =========================================================================
#pragma region
TEST_SPRINTF(ls_basic, "%ls", L"Hello, world!", wchar_t *)
TEST_SPRINTF(ls_unicode, "%ls", L"Привет мир!", wchar_t *)
TEST_SPRINTF(ls_wide_chars, "%ls", L"Привет, 世界!", wchar_t *)

TEST_SPRINTF(ls_special, "%ls", L"Hello\tWorld\n", wchar_t *)
TEST_SPRINTF(ls_nonprint, "%ls", L"Line1\nLine2\tTab\x01", wchar_t *)

TEST_SPRINTF(ls_null, "%ls", NULL, wchar_t *)
TEST_SPRINTF(ls_empty, "%ls", L"", wchar_t *)

TEST_SPRINTF(ls_width, "%10ls", L"漢字", wchar_t *)
TEST_SPRINTF(ls_left_align, "%-10ls", L"test", wchar_t *)
TEST_SPRINTF(ls_precision, "%.2ls", L"абвгд", wchar_t *)
TEST_SPRINTF(ls_zero_precision, "%.0ls", L"anything", wchar_t *)
TEST_SPRINTF(ls_large_precision, "%.10ls", L"short", wchar_t *)
TEST_SPRINTF(ls_width_precision, "%15.2ls", L"こんにちは", wchar_t *)
TEST_SPRINTF(ls_complex_align, "%-8.3ls", L"align", wchar_t *)

TEST_SPRINTF(ls_mixed, "[%ls]", L"ABC\xE0\xF0 日本語", wchar_t *)

TEST_SPRINTF(ls_ascii_only, "[%ls]", L"ASCII", wchar_t *)
TEST_SPRINTF(ls_brackets, "[%ls]", L"", wchar_t *)

TEST_SPRINTF(ls_utf8_locale, "%ls", L"€ßå", wchar_t *)  // UTF-8 locale
TEST_SPRINTF(ls_utf16_locale, "%ls", L"𐍈𐍉", wchar_t *)  // UTF-16 locale

START_TEST(ls_surrogate_pair) {
  wchar_t ws[] = {0xD83D, 0xDE00, 0};  // 😀
  char buf1[32], buf2[32];
  int res1 = s21_sprintf(buf1, "%ls", ws);
  int res2 = sprintf(buf2, "%ls", ws);
  ck_assert_str_eq(buf1, buf2);
  ck_assert_int_eq(res1, res2);
}
END_TEST
#pragma endregion

// =========================================================================
// Длинный символ %lc
// =========================================================================
#pragma region
TEST_SPRINTF(lc_basic, "%lc", L'Я', wchar_t)
TEST_SPRINTF(lc_ascii, "[%lc]", L'A', wchar_t)
TEST_SPRINTF(lc_width, "%8lc", L'€', wchar_t)
TEST_SPRINTF(lc_width_left_align, "%-6lc", L'ß', wchar_t)
TEST_SPRINTF(lc_euro, "%lc", L'€', wchar_t)
TEST_SPRINTF(lc_cyrillic, "%lc", L'я', wchar_t)
TEST_SPRINTF(lc_hiragana, "%lc", L'あ', wchar_t)
TEST_SPRINTF(lc_gothic, "%lc", L'𐍈', wchar_t)

TEST_SPRINTF(lc_min, "%lc", WCHAR_MIN, wchar_t)
TEST_SPRINTF(lc_max, "%lc", WCHAR_MAX, wchar_t)

TEST_SPRINTF(lc_neg_128, "%lc", -128, wchar_t)
TEST_SPRINTF(lc_zero, "%lc", 0, wchar_t)
TEST_SPRINTF(lc_128, "%lc", 128, wchar_t)
TEST_SPRINTF(lc_256, "%lc", 256, wchar_t)
TEST_SPRINTF(lc_1024, "%lc", 1024, wchar_t)
TEST_SPRINTF(lc_0xFFFF, "%lc", 0xFFFF, wchar_t)
TEST_SPRINTF(lc_0x10000, "%lc", 0x10000, wchar_t)
TEST_SPRINTF(lc_0x10FFFF, "%lc", 0x10FFFF, wchar_t)

TEST_SPRINTF(lc_null_char, "[%lc]", L'\0', wchar_t)
TEST_SPRINTF(lc_nonprint, "%lc", L'\x01', wchar_t)
TEST_SPRINTF(lc_newline, "%lc", L'\n', wchar_t)
TEST_SPRINTF(lc_tab, "%lc", L'\t', wchar_t)

TEST_SPRINTF(lc_invalid_wide, "%lc", (wchar_t)-2,
             wchar_t)  // Недопустимый wide-char
TEST_SPRINTF(lc_surrogate, "%lc", 0xD800, wchar_t)  // Одиночный surrogate
TEST_SPRINTF(lc_bom, "%lc", 0xFEFF, wchar_t)        // BOM-символ
TEST_SPRINTF(lc_replacement, "%lc", 0xFFFD, wchar_t)  // Символ замены

TEST_SPRINTF(lc_long_string, "%1000lc", L'·', wchar_t)  // Длинный вывод
#pragma endregion

// ================================================================================================================================
//                                                         С СПЕЦИФИКАТОРОМ
// ================================================================================================================================
// ================================================================================================================================

// =========================================================================
// Длинная строка %ls
// =========================================================================
#pragma region

#pragma endregion

// =========================================================================
// Длинная строка NULL
// =========================================================================
#pragma region
TEST_SPRINTF(ls_mins_null, "%-ls", NULL, wchar_t *)

TEST_SPRINTF(ls_width_null, "%5ls", NULL, wchar_t *)
TEST_SPRINTF(ls_zrpc_null, "%.0ls", NULL, wchar_t *)
TEST_SPRINTF(ls_prec_null, "%.5ls", NULL, wchar_t *)
TEST_SPRINTF(ls_width_prec_null, "%10.5ls", NULL, wchar_t *)

TEST_SPRINTF(ls_width_mins_null, "%-5ls", NULL, wchar_t *)

TEST_SPRINTF(ls_prec_mins_null, "%-.5ls", NULL, wchar_t *)

TEST_SPRINTF(ls_zrpc_mins_null, "%-.0ls", NULL, wchar_t *)

TEST_SPRINTF(ls_width_prec_mins_null, "%-10.5ls", NULL, wchar_t *)

TEST_SPRINTF_2(ls_dynamic_width_null, "%*ls", 10, NULL, wchar_t *)
TEST_SPRINTF_2(ls_dynamic_prec_null, "%.*ls", 5, NULL, wchar_t *)
TEST_SPRINTF_3(ls_dynamic_width_prec_null, "%*.*ls", 10, 5, NULL, wchar_t *)

// =========================================================================

TEST_SPRINTF(ls_mins_zero, "%-ls", 0, wchar_t *)

TEST_SPRINTF(ls_width_zero, "%5ls", 0, wchar_t *)
TEST_SPRINTF(ls_zrpc_zero, "%.0ls", 0, wchar_t *)
TEST_SPRINTF(ls_prec_zero, "%.5ls", 0, wchar_t *)
TEST_SPRINTF(ls_width_prec_zero, "%10.5ls", 0, wchar_t *)

TEST_SPRINTF(ls_width_mins_zero, "%-5ls", 0, wchar_t *)

TEST_SPRINTF(ls_prec_mins_zero, "%-.5ls", 0, wchar_t *)

TEST_SPRINTF(ls_zrpc_mins_zero, "%-.0ls", 0, wchar_t *)

TEST_SPRINTF(ls_width_prec_mins_zero, "%-10.5ls", 0, wchar_t *)

TEST_SPRINTF_2(ls_dynamic_width_zero, "%*ls", 10, 0, wchar_t *)
TEST_SPRINTF_2(ls_dynamic_prec_zero, "%.*ls", 5, 0, wchar_t *)
TEST_SPRINTF_3(ls_dynamic_width_prec_zero, "%*.*ls", 10, 5, 0, wchar_t *)
#pragma endregion

// =========================================================================
// Длинный символ %lc
// =========================================================================
#pragma region
TEST_SPRINTF(lc_mins_wchar_t, "%-lc", 'A', wchar_t)

TEST_SPRINTF(lc_width_wchar_t, "%5lc", 'A', wchar_t)

TEST_SPRINTF(lc_width_mins_wchar_t, "%-5lc", 'A', wchar_t)

TEST_SPRINTF_2(lc_dynamic_width_wchar_t, "%*lc", 10, 'A', wchar_t)
#pragma endregion

// =========================================================================
// Длинный символ NULL
// =========================================================================
#pragma region

// =========================================================================

TEST_SPRINTF(lc_mins_zero, "%-lc", 0, wchar_t)

TEST_SPRINTF(lc_width_zero, "%5lc", 0, wchar_t)

TEST_SPRINTF(lc_width_mins_zero, "%-5lc", 0, wchar_t)

TEST_SPRINTF_2(lc_dynamic_width_zero, "%*lc", 10, 0, wchar_t)
#pragma endregion

// ================================================================================================================================
//                                                        ~~  TEST SUITE  ~~
// ================================================================================================================================
// ================================================================================================================================

// ================================================================
// Test suite sprintf_suite
// ================================================================
#pragma region

Suite *sprintf_suite(void) {
  Suite *suite = suite_create("test_sprintf");
  TCase *tc = tcase_create("Core");
#pragma region
  tcase_add_test(tc, d_zero);
  tcase_add_test(tc, i_zero);
  tcase_add_test(tc, hd_zero);
  tcase_add_test(tc, hi_zero);
  tcase_add_test(tc, hhd_zero);
  tcase_add_test(tc, hhi_zero);
  tcase_add_test(tc, ld_zero);
  tcase_add_test(tc, li_zero);
  tcase_add_test(tc, lld_zero);
  tcase_add_test(tc, lli_zero);
  tcase_add_test(tc, d_);
  tcase_add_test(tc, d_min);
  tcase_add_test(tc, d_max);
  tcase_add_test(tc, i_);
  tcase_add_test(tc, i_min);
  tcase_add_test(tc, i_max);
  tcase_add_test(tc, o_);
  tcase_add_test(tc, o_min);
  tcase_add_test(tc, o_max);
  tcase_add_test(tc, o_min_pl);
  tcase_add_test(tc, o_max_pl);
  tcase_add_test(tc, u_);
  tcase_add_test(tc, u_min);
  tcase_add_test(tc, u_max);
  tcase_add_test(tc, u_min_pl);
  tcase_add_test(tc, u_max_pl);
  tcase_add_test(tc, x_);
  tcase_add_test(tc, x_min);
  tcase_add_test(tc, x_max);
  tcase_add_test(tc, x_min_pl);
  tcase_add_test(tc, x_max_pl);
  tcase_add_test(tc, X_);
  tcase_add_test(tc, X_min);
  tcase_add_test(tc, X_max);
  tcase_add_test(tc, X_min_pl);
  tcase_add_test(tc, X_max_pl);
  tcase_add_test(tc, hd_);
  tcase_add_test(tc, hd_min);
  tcase_add_test(tc, hd_max);
  tcase_add_test(tc, hd_max_pl);
  tcase_add_test(tc, hi_);
  tcase_add_test(tc, hi_min);
  tcase_add_test(tc, hi_max);
  tcase_add_test(tc, hi_max_pl);
  tcase_add_test(tc, ho_);
  tcase_add_test(tc, ho_min);
  tcase_add_test(tc, ho_max);
  tcase_add_test(tc, ho_min_pl);
  tcase_add_test(tc, hu_);
  tcase_add_test(tc, hu_min);
  tcase_add_test(tc, hu_max);
  tcase_add_test(tc, hu_min_pl);
  tcase_add_test(tc, hx_);
  tcase_add_test(tc, hx_min);
  tcase_add_test(tc, hx_max);
  tcase_add_test(tc, hx_min_pl);
  tcase_add_test(tc, hX_);
  tcase_add_test(tc, hX_min);
  tcase_add_test(tc, hX_max);
  tcase_add_test(tc, hX_min_pl);
  tcase_add_test(tc, hhd_);
  tcase_add_test(tc, hhd_min);
  tcase_add_test(tc, hhd_max);
  tcase_add_test(tc, hhd_max_pl);
  tcase_add_test(tc, hhi_);
  tcase_add_test(tc, hhi_min);
  tcase_add_test(tc, hhi_max);
  tcase_add_test(tc, hhi_max_pl);
  tcase_add_test(tc, hho_);
  tcase_add_test(tc, hho_min);
  tcase_add_test(tc, hho_max);
  tcase_add_test(tc, hho_min_pl);
  tcase_add_test(tc, hhu_);
  tcase_add_test(tc, hhu_min);
  tcase_add_test(tc, hhu_max);
  tcase_add_test(tc, hhu_min_pl);
  tcase_add_test(tc, hhx_);
  tcase_add_test(tc, hhx_min);
  tcase_add_test(tc, hhx_max);
  tcase_add_test(tc, hhx_min_pl);
  tcase_add_test(tc, hhX_);
  tcase_add_test(tc, hhX_min);
  tcase_add_test(tc, hhX_max);
  tcase_add_test(tc, hhX_min_pl);
  tcase_add_test(tc, ld_);
  tcase_add_test(tc, ld_min);
  tcase_add_test(tc, ld_max);
  tcase_add_test(tc, li_);
  tcase_add_test(tc, li_min);
  tcase_add_test(tc, li_max);
  tcase_add_test(tc, lo_);
  tcase_add_test(tc, lo_min);
  tcase_add_test(tc, lo_max);
  tcase_add_test(tc, lo_min_pl);
  tcase_add_test(tc, lo_max_pl);
  tcase_add_test(tc, lu_);
  tcase_add_test(tc, lu_min);
  tcase_add_test(tc, lu_max);
  tcase_add_test(tc, lu_min_pl);
  tcase_add_test(tc, lu_max_pl);
  tcase_add_test(tc, lx_);
  tcase_add_test(tc, lx_min);
  tcase_add_test(tc, lx_max);
  tcase_add_test(tc, lx_min_pl);
  tcase_add_test(tc, lx_max_pl);
  tcase_add_test(tc, lX_);
  tcase_add_test(tc, lX_min);
  tcase_add_test(tc, lX_max);
  tcase_add_test(tc, lX_min_pl);
  tcase_add_test(tc, lX_max_pl);
  tcase_add_test(tc, lld_);
  tcase_add_test(tc, lld_min);
  tcase_add_test(tc, lld_max);
  tcase_add_test(tc, lli_);
  tcase_add_test(tc, lli_min);
  tcase_add_test(tc, lli_max);
  tcase_add_test(tc, llo_);
  tcase_add_test(tc, llo_min);
  tcase_add_test(tc, llo_max);
  tcase_add_test(tc, llo_min_pl);
  tcase_add_test(tc, llo_max_pl);
  tcase_add_test(tc, llu_);
  tcase_add_test(tc, llu_min);
  tcase_add_test(tc, llu_max);
  tcase_add_test(tc, llu_min_pl);
  tcase_add_test(tc, llu_max_pl);
  tcase_add_test(tc, llx_);
  tcase_add_test(tc, llx_min);
  tcase_add_test(tc, llx_max);
  tcase_add_test(tc, llx_min_pl);
  tcase_add_test(tc, llx_max_pl);
  tcase_add_test(tc, llX_);
  tcase_add_test(tc, llX_min);
  tcase_add_test(tc, llX_max);
  tcase_add_test(tc, llX_min_pl);
  tcase_add_test(tc, llX_max_pl);
  tcase_add_test(tc, e_nan);
  tcase_add_test(tc, e_inf);
  tcase_add_test(tc, e_ng_inf);
  tcase_add_test(tc, E_nan);
  tcase_add_test(tc, E_inf);
  tcase_add_test(tc, E_ng_inf);
  tcase_add_test(tc, f_nan);
  tcase_add_test(tc, f_inf);
  tcase_add_test(tc, f_ng_inf);
  tcase_add_test(tc, g_nan);
  tcase_add_test(tc, g_inf);
  tcase_add_test(tc, g_ng_inf);
  tcase_add_test(tc, G_nan);
  tcase_add_test(tc, G_inf);
  tcase_add_test(tc, G_ng_inf);
  tcase_add_test(tc, le_nan);
  tcase_add_test(tc, le_inf);
  tcase_add_test(tc, le_ng_inf);
  tcase_add_test(tc, lE_nan);
  tcase_add_test(tc, lE_inf);
  tcase_add_test(tc, lE_ng_inf);
  tcase_add_test(tc, lf_nan);
  tcase_add_test(tc, lf_inf);
  tcase_add_test(tc, lf_ng_inf);
  tcase_add_test(tc, lg_nan);
  tcase_add_test(tc, lg_inf);
  tcase_add_test(tc, lg_ng_inf);
  tcase_add_test(tc, lG_nan);
  tcase_add_test(tc, lG_inf);
  tcase_add_test(tc, lG_ng_inf);
  tcase_add_test(tc, Le_nan);
  tcase_add_test(tc, Le_inf);
  tcase_add_test(tc, Le_ng_inf);
  tcase_add_test(tc, LE_nan);
  tcase_add_test(tc, LE_inf);
  tcase_add_test(tc, LE_ng_inf);
  tcase_add_test(tc, Lf_nan);
  tcase_add_test(tc, Lf_inf);
  tcase_add_test(tc, Lf_ng_inf);
  tcase_add_test(tc, Lg_nan);
  tcase_add_test(tc, Lg_inf);
  tcase_add_test(tc, Lg_ng_inf);
  tcase_add_test(tc, LG_nan);
  tcase_add_test(tc, LG_inf);
  tcase_add_test(tc, LG_ng_inf);
  tcase_add_test(tc, e_null);
  tcase_add_test(tc, e_zero);
  tcase_add_test(tc, e_ng_z);
  tcase_add_test(tc, E_null);
  tcase_add_test(tc, E_zero);
  tcase_add_test(tc, E_ng_z);
  tcase_add_test(tc, f_null);
  tcase_add_test(tc, f_zero);
  tcase_add_test(tc, f_ng_z);
  tcase_add_test(tc, g_null);
  tcase_add_test(tc, g_zero);
  tcase_add_test(tc, g_ng_z);
  tcase_add_test(tc, G_null);
  tcase_add_test(tc, G_zero);
  tcase_add_test(tc, G_ng_z);
  tcase_add_test(tc, le_null);
  tcase_add_test(tc, le_zero);
  tcase_add_test(tc, le_ng_z);
  tcase_add_test(tc, lE_null);
  tcase_add_test(tc, lE_zero);
  tcase_add_test(tc, lE_ng_z);
  tcase_add_test(tc, lf_null);
  tcase_add_test(tc, lf_zero);
  tcase_add_test(tc, lf_ng_z);
  tcase_add_test(tc, lg_null);
  tcase_add_test(tc, lg_zero);
  tcase_add_test(tc, lg_ng_z);
  tcase_add_test(tc, lG_null);
  tcase_add_test(tc, lG_zero);
  tcase_add_test(tc, lG_ng_z);
  tcase_add_test(tc, Le_null);
  tcase_add_test(tc, Le_zero);
  tcase_add_test(tc, Le_ng_z);
  tcase_add_test(tc, LE_null);
  tcase_add_test(tc, LE_zero);
  tcase_add_test(tc, LE_ng_z);
  tcase_add_test(tc, Lf_null);
  tcase_add_test(tc, Lf_zero);
  tcase_add_test(tc, Lf_ng_z);
  tcase_add_test(tc, Lg_null);
  tcase_add_test(tc, Lg_zero);
  tcase_add_test(tc, Lg_ng_z);
  tcase_add_test(tc, LG_null);
  tcase_add_test(tc, LG_zero);
  tcase_add_test(tc, LG_ng_z);
  tcase_add_test(tc, e_post_small);
  tcase_add_test(tc, e_negt_small);
  tcase_add_test(tc, e_post_medium);
  tcase_add_test(tc, e_negt_medium);
  tcase_add_test(tc, e_post_int);
  tcase_add_test(tc, e_negt_int);
  tcase_add_test(tc, e_post_vsmall);
  tcase_add_test(tc, e_negt_vsmall);
  tcase_add_test(tc, e_post_large);
  tcase_add_test(tc, e_negt_large);
  tcase_add_test(tc, e_post_1e6);
  tcase_add_test(tc, e_post_1em6);
  tcase_add_test(tc, e_round_to_2);
  tcase_add_test(tc, e_round_to_10);
  tcase_add_test(tc, e_max_exp);
  tcase_add_test(tc, e_min_exp);
  tcase_add_test(tc, E_post_small);
  tcase_add_test(tc, E_negt_small);
  tcase_add_test(tc, E_post_medium);
  tcase_add_test(tc, E_negt_medium);
  tcase_add_test(tc, E_post_int);
  tcase_add_test(tc, E_negt_int);
  tcase_add_test(tc, E_post_vsmall);
  tcase_add_test(tc, E_negt_vsmall);
  tcase_add_test(tc, E_post_large);
  tcase_add_test(tc, E_negt_large);
  tcase_add_test(tc, E_post_1e6);
  tcase_add_test(tc, E_post_1em6);
  tcase_add_test(tc, E_round_to_2);
  tcase_add_test(tc, E_round_to_10);
  tcase_add_test(tc, E_max_exp);
  tcase_add_test(tc, E_min_exp);
  tcase_add_test(tc, f_post_small);
  tcase_add_test(tc, f_negt_small);
  tcase_add_test(tc, f_post_medium);
  tcase_add_test(tc, f_negt_medium);
  tcase_add_test(tc, f_post_int);
  tcase_add_test(tc, f_negt_int);
  tcase_add_test(tc, f_post_vsmall);
  tcase_add_test(tc, f_negt_vsmall);
  tcase_add_test(tc, f_post_large);
  tcase_add_test(tc, f_negt_large);
  tcase_add_test(tc, f_post_1e6);
  tcase_add_test(tc, f_post_1em6);
  tcase_add_test(tc, f_round_to_2);
  tcase_add_test(tc, f_round_to_10);
  tcase_add_test(tc, f_max_exp);
  tcase_add_test(tc, f_min_exp);
  tcase_add_test(tc, g_post_small);
  tcase_add_test(tc, g_negt_small);
  tcase_add_test(tc, g_post_medium);
  tcase_add_test(tc, g_negt_medium);
  tcase_add_test(tc, g_post_int);
  tcase_add_test(tc, g_negt_int);
  tcase_add_test(tc, g_post_vsmall);
  tcase_add_test(tc, g_negt_vsmall);
  tcase_add_test(tc, g_post_large);
  tcase_add_test(tc, g_negt_large);
  tcase_add_test(tc, g_post_1e6);
  tcase_add_test(tc, g_post_1em6);
  tcase_add_test(tc, g_round_to_2);
  tcase_add_test(tc, g_round_to_10);
  tcase_add_test(tc, g_max_exp);
  tcase_add_test(tc, g_min_exp);
  tcase_add_test(tc, G_post_small);
  tcase_add_test(tc, G_negt_small);
  tcase_add_test(tc, G_post_medium);
  tcase_add_test(tc, G_negt_medium);
  tcase_add_test(tc, G_post_int);
  tcase_add_test(tc, G_negt_int);
  tcase_add_test(tc, G_post_vsmall);
  tcase_add_test(tc, G_negt_vsmall);
  tcase_add_test(tc, G_post_large);
  tcase_add_test(tc, G_negt_large);
  tcase_add_test(tc, G_post_1e6);
  tcase_add_test(tc, G_post_1em6);
  tcase_add_test(tc, G_round_to_2);
  tcase_add_test(tc, G_round_to_10);
  tcase_add_test(tc, G_max_exp);
  tcase_add_test(tc, G_min_exp);
  tcase_add_test(tc, le_post_small);
  tcase_add_test(tc, le_negt_small);
  tcase_add_test(tc, le_post_medium);
  tcase_add_test(tc, le_negt_medium);
  tcase_add_test(tc, le_post_int);
  tcase_add_test(tc, le_negt_int);
  tcase_add_test(tc, le_post_vsmall);
  tcase_add_test(tc, le_negt_vsmall);
  tcase_add_test(tc, le_post_large);
  tcase_add_test(tc, le_negt_large);
  tcase_add_test(tc, le_post_1e6);
  tcase_add_test(tc, le_post_1em6);
  tcase_add_test(tc, le_round_to_2);
  tcase_add_test(tc, le_round_to_10);
  tcase_add_test(tc, le_max_exp);
  tcase_add_test(tc, le_min_exp);
  tcase_add_test(tc, lE_post_small);
  tcase_add_test(tc, lE_negt_small);
  tcase_add_test(tc, lE_post_medium);
  tcase_add_test(tc, lE_negt_medium);
  tcase_add_test(tc, lE_post_int);
  tcase_add_test(tc, lE_negt_int);
  tcase_add_test(tc, lE_post_vsmall);
  tcase_add_test(tc, lE_negt_vsmall);
  tcase_add_test(tc, lE_post_large);
  tcase_add_test(tc, lE_negt_large);
  tcase_add_test(tc, lE_post_1e6);
  tcase_add_test(tc, lE_post_1em6);
  tcase_add_test(tc, lE_round_to_2);
  tcase_add_test(tc, lE_round_to_10);
  tcase_add_test(tc, lE_max_exp);
  tcase_add_test(tc, lE_min_exp);
  tcase_add_test(tc, lf_post_small);
  tcase_add_test(tc, lf_negt_small);
  tcase_add_test(tc, lf_post_medium);
  tcase_add_test(tc, lf_negt_medium);
  tcase_add_test(tc, lf_post_int);
  tcase_add_test(tc, lf_negt_int);
  tcase_add_test(tc, lf_post_vsmall);
  tcase_add_test(tc, lf_negt_vsmall);
  tcase_add_test(tc, lf_post_large);
  tcase_add_test(tc, lf_negt_large);
  tcase_add_test(tc, lf_post_1e6);
  tcase_add_test(tc, lf_post_1em6);
  tcase_add_test(tc, lf_round_to_2);
  tcase_add_test(tc, lf_round_to_10);
  tcase_add_test(tc, lf_max_exp);
  tcase_add_test(tc, lf_min_exp);
  tcase_add_test(tc, lg_post_small);
  tcase_add_test(tc, lg_negt_small);
  tcase_add_test(tc, lg_post_medium);
  tcase_add_test(tc, lg_negt_medium);
  tcase_add_test(tc, lg_post_int);
  tcase_add_test(tc, lg_negt_int);
  tcase_add_test(tc, lg_post_vsmall);
  tcase_add_test(tc, lg_negt_vsmall);
  tcase_add_test(tc, lg_post_large);
  tcase_add_test(tc, lg_negt_large);
  tcase_add_test(tc, lg_post_1e6);
  tcase_add_test(tc, lg_post_1em6);
  tcase_add_test(tc, lg_round_to_2);
  tcase_add_test(tc, lg_round_to_10);
  tcase_add_test(tc, lg_max_exp);
  tcase_add_test(tc, lg_min_exp);
  tcase_add_test(tc, lG_post_small);
  tcase_add_test(tc, lG_negt_small);
  tcase_add_test(tc, lG_post_medium);
  tcase_add_test(tc, lG_negt_medium);
  tcase_add_test(tc, lG_post_int);
  tcase_add_test(tc, lG_negt_int);
  tcase_add_test(tc, lG_post_vsmall);
  tcase_add_test(tc, lG_negt_vsmall);
  tcase_add_test(tc, lG_post_large);
  tcase_add_test(tc, lG_negt_large);
  tcase_add_test(tc, lG_post_1e6);
  tcase_add_test(tc, lG_post_1em6);
  tcase_add_test(tc, lG_round_to_2);
  tcase_add_test(tc, lG_round_to_10);
  tcase_add_test(tc, lG_max_exp);
  tcase_add_test(tc, lG_min_exp);
  tcase_add_test(tc, Le_post_small);
  tcase_add_test(tc, Le_negt_small);
  tcase_add_test(tc, Le_post_medium);
  tcase_add_test(tc, Le_negt_medium);
  tcase_add_test(tc, Le_post_int);
  tcase_add_test(tc, Le_negt_int);
  tcase_add_test(tc, Le_post_vsmall);
  tcase_add_test(tc, Le_negt_vsmall);
  tcase_add_test(tc, Le_post_large);
  tcase_add_test(tc, Le_negt_large);
  tcase_add_test(tc, Le_post_1e6L);
  tcase_add_test(tc, Le_post_1em6L);
  tcase_add_test(tc, Le_round_to_2L);
  tcase_add_test(tc, Le_round_to_10L);
  tcase_add_test(tc, Le_max_exp);
  tcase_add_test(tc, Le_min_exp);
  tcase_add_test(tc, LE_post_small);
  tcase_add_test(tc, LE_negt_small);
  tcase_add_test(tc, LE_post_medium);
  tcase_add_test(tc, LE_negt_medium);
  tcase_add_test(tc, LE_post_int);
  tcase_add_test(tc, LE_negt_int);
  tcase_add_test(tc, LE_post_vsmall);
  tcase_add_test(tc, LE_negt_vsmall);
  tcase_add_test(tc, LE_post_large);
  tcase_add_test(tc, LE_negt_large);
  tcase_add_test(tc, LE_post_1e6L);
  tcase_add_test(tc, LE_post_1em6L);
  tcase_add_test(tc, LE_round_to_2L);
  tcase_add_test(tc, LE_round_to_10L);
  tcase_add_test(tc, LE_max_exp);
  tcase_add_test(tc, LE_min_exp);
  tcase_add_test(tc, Lf_post_small);
  tcase_add_test(tc, Lf_negt_small);
  tcase_add_test(tc, Lf_post_medium);
  tcase_add_test(tc, Lf_negt_medium);
  tcase_add_test(tc, Lf_post_int);
  tcase_add_test(tc, Lf_negt_int);
  tcase_add_test(tc, Lf_post_vsmall);
  tcase_add_test(tc, Lf_negt_vsmall);
  tcase_add_test(tc, Lf_post_large);
  tcase_add_test(tc, Lf_negt_large);
  tcase_add_test(tc, Lf_post_1e6L);
  tcase_add_test(tc, Lf_post_1em6L);
  tcase_add_test(tc, Lf_round_to_2L);
  tcase_add_test(tc, Lf_round_to_10L);
  tcase_add_test(tc, Lf_max_exp);
  tcase_add_test(tc, Lf_min_exp);
  tcase_add_test(tc, Lg_post_small);
  tcase_add_test(tc, Lg_negt_small);
  tcase_add_test(tc, Lg_post_medium);
  tcase_add_test(tc, Lg_negt_medium);
  tcase_add_test(tc, Lg_post_int);
  tcase_add_test(tc, Lg_negt_int);
  tcase_add_test(tc, Lg_post_vsmall);
  tcase_add_test(tc, Lg_negt_vsmall);
  tcase_add_test(tc, Lg_post_large);
  tcase_add_test(tc, Lg_negt_large);
  tcase_add_test(tc, Lg_post_1e6L);
  tcase_add_test(tc, Lg_post_1em6L);
  tcase_add_test(tc, Lg_round_to_2L);
  tcase_add_test(tc, Lg_round_to_10L);
  tcase_add_test(tc, Lg_max_exp);
  tcase_add_test(tc, Lg_min_exp);
  tcase_add_test(tc, LG_post_small);
  tcase_add_test(tc, LG_negt_small);
  tcase_add_test(tc, LG_post_medium);
  tcase_add_test(tc, LG_negt_medium);
  tcase_add_test(tc, LG_post_int);
  tcase_add_test(tc, LG_negt_int);
  tcase_add_test(tc, LG_post_vsmall);
  tcase_add_test(tc, LG_negt_vsmall);
  tcase_add_test(tc, LG_post_large);
  tcase_add_test(tc, LG_negt_large);
  tcase_add_test(tc, LG_post_1e6L);
  tcase_add_test(tc, LG_post_1em6L);
  tcase_add_test(tc, LG_round_to_2L);
  tcase_add_test(tc, LG_round_to_10L);
  tcase_add_test(tc, LG_max_exp);
  tcase_add_test(tc, LG_min_exp);
  tcase_add_test(tc, c_);
  tcase_add_test(tc, c_min);
  tcase_add_test(tc, c_max);
  tcase_add_test(tc, c_nonprint);
  tcase_add_test(tc, c_zero);
  tcase_add_test(tc, c_newline);
  tcase_add_test(tc, c_tab);
  tcase_add_test(tc, c_null_char);
  tcase_add_test(tc, c_expression);
  tcase_add_test(tc, c_middle_of_string);
  tcase_add_test(tc, s_);
  tcase_add_test(tc, s_null);
  tcase_add_test(tc, s_null_middle);
  tcase_add_test(tc, s_special);
  tcase_add_test(tc, s_special_chars);
  tcase_add_test(tc, s_unicode);
  tcase_add_test(tc, s_empty);
  tcase_add_test(tc, s_escaped);
  tcase_add_test(tc, s_utf8);
  tcase_add_test(tc, s_single_char);
  tcase_add_test(tc, s_russian_utf8);
  tcase_add_test(tc, s_chinese);
  tcase_add_test(tc, s_arabic);
  tcase_add_test(tc, s_max_length);
  tcase_add_test(tc, s_expression);
  tcase_add_test(tc, p);
  tcase_add_test(tc, p_int);
  tcase_add_test(tc, p_unsigned_int);
  tcase_add_test(tc, p_double);
  tcase_add_test(tc, p_min);
  tcase_add_test(tc, p_max64);
  tcase_add_test(tc, p_null);
  tcase_add_test(tc, p_string_pointer);
  tcase_add_test(tc, test_s21_sprintf_p_struct);
  tcase_add_test(tc, p_pointer_to_pointer);
  tcase_add_test(tc, test_s21_sprintf_p_func);
  tcase_add_test(tc, single_percent);
  tcase_add_test(tc, double_percent);
  tcase_add_test(tc, test_s21_sprintf_percent_combined);
  tcase_add_test(tc, percent_with_string);
  tcase_add_test(tc, n_);
  tcase_add_test(tc, hn_);
  tcase_add_test(tc, hhn_);
  tcase_add_test(tc, ln_);
  tcase_add_test(tc, lln_);
  tcase_add_test(tc, n_beginning);
  tcase_add_test(tc, n_middle);
  tcase_add_test(tc, n_multiple);
  tcase_add_test(tc, d_mins_zero);
  tcase_add_test(tc, d_plus_zero);
  tcase_add_test(tc, d_spac_zero);
  tcase_add_test(tc, d_fzer_zero);
  tcase_add_test(tc, d_width_zero);
  tcase_add_test(tc, d_zrpc_zero);
  tcase_add_test(tc, d_prec_zero);
  tcase_add_test(tc, d_width_prec_zero);
  tcase_add_test(tc, d_width_mins_zero);
  tcase_add_test(tc, d_width_plus_zero);
  tcase_add_test(tc, d_width_spac_zero);
  tcase_add_test(tc, d_width_fzer_zero);
  tcase_add_test(tc, d_zrwth_plus_zero);
  tcase_add_test(tc, d_zrwth_spac_zero);
  tcase_add_test(tc, d_prec_mins_zero);
  tcase_add_test(tc, d_prec_plus_zero);
  tcase_add_test(tc, d_prec_spac_zero);
  tcase_add_test(tc, d_zrpc_mins_zero);
  tcase_add_test(tc, d_zrpc_plus_zero);
  tcase_add_test(tc, d_zrpc_spac_zero);
  tcase_add_test(tc, d_width_prec_mins_zero);
  tcase_add_test(tc, d_width_prec_plus_zero);
  tcase_add_test(tc, d_width_prec_spac_zero);
  tcase_add_test(tc, d_dynamic_width_zero);
  tcase_add_test(tc, d_dynamic_prec_zero);
  tcase_add_test(tc, d_dynamic_width_prec_zero);
  tcase_add_test(tc, i_mins_zero);
  tcase_add_test(tc, i_plus_zero);
  tcase_add_test(tc, i_spac_zero);
  tcase_add_test(tc, i_fzer_zero);
  tcase_add_test(tc, i_width_zero);
  tcase_add_test(tc, i_zrpc_zero);
  tcase_add_test(tc, i_prec_zero);
  tcase_add_test(tc, i_width_prec_zero);
  tcase_add_test(tc, i_width_mins_zero);
  tcase_add_test(tc, i_width_plus_zero);
  tcase_add_test(tc, i_width_spac_zero);
  tcase_add_test(tc, i_width_fzer_zero);
  tcase_add_test(tc, i_zrwth_plus_zero);
  tcase_add_test(tc, i_zrwth_spac_zero);
  tcase_add_test(tc, i_prec_mins_zero);
  tcase_add_test(tc, i_prec_plus_zero);
  tcase_add_test(tc, i_prec_spac_zero);
  tcase_add_test(tc, i_zrpc_mins_zero);
  tcase_add_test(tc, i_zrpc_plus_zero);
  tcase_add_test(tc, i_zrpc_spac_zero);
  tcase_add_test(tc, i_width_prec_mins_zero);
  tcase_add_test(tc, i_width_prec_plus_zero);
  tcase_add_test(tc, i_width_prec_spac_zero);
  tcase_add_test(tc, i_dynamic_width_zero);
  tcase_add_test(tc, i_dynamic_prec_zero);
  tcase_add_test(tc, i_dynamic_width_prec_zero);
  tcase_add_test(tc, o_mins_zero);
  tcase_add_test(tc, o_hash_zero);
  tcase_add_test(tc, o_fzer_zero);
  tcase_add_test(tc, o_width_zero);
  tcase_add_test(tc, o_zrpc_zero);
  tcase_add_test(tc, o_prec_zero);
  tcase_add_test(tc, o_width_prec_zero);
  tcase_add_test(tc, o_width_mins_zero);
  tcase_add_test(tc, o_width_hash_zero);
  tcase_add_test(tc, o_width_fzer_zero);
  tcase_add_test(tc, o_zrwth_hash_zero);
  tcase_add_test(tc, o_prec_mins_zero);
  tcase_add_test(tc, o_prec_hash_zero);
  tcase_add_test(tc, o_zrpc_mins_zero);
  tcase_add_test(tc, o_zrpc_hash_zero);
  tcase_add_test(tc, o_width_prec_mins_zero);
  tcase_add_test(tc, o_width_prec_hash_zero);
  tcase_add_test(tc, o_dynamic_width_zero);
  tcase_add_test(tc, o_dynamic_prec_zero);
  tcase_add_test(tc, o_dynamic_width_prec_zero);
  tcase_add_test(tc, u_mins_zero);
  tcase_add_test(tc, u_fzer_zero);
  tcase_add_test(tc, u_width_zero);
  tcase_add_test(tc, u_zrpc_zero);
  tcase_add_test(tc, u_prec_zero);
  tcase_add_test(tc, u_width_prec_zero);
  tcase_add_test(tc, u_width_mins_zero);
  tcase_add_test(tc, u_width_fzer_zero);
  tcase_add_test(tc, u_prec_mins_zero);
  tcase_add_test(tc, u_zrpc_mins_zero);
  tcase_add_test(tc, u_width_prec_mins_zero);
  tcase_add_test(tc, u_dynamic_width_zero);
  tcase_add_test(tc, u_dynamic_prec_zero);
  tcase_add_test(tc, u_dynamic_width_prec_zero);
  tcase_add_test(tc, x_mins_zero);
  tcase_add_test(tc, x_hash_zero);
  tcase_add_test(tc, x_fzer_zero);
  tcase_add_test(tc, x_width_zero);
  tcase_add_test(tc, x_zrpc_zero);
  tcase_add_test(tc, x_prec_zero);
  tcase_add_test(tc, x_width_prec_zero);
  tcase_add_test(tc, x_width_mins_zero);
  tcase_add_test(tc, x_width_hash_zero);
  tcase_add_test(tc, x_width_fzer_zero);
  tcase_add_test(tc, x_zrwth_hash_zero);
  tcase_add_test(tc, x_prec_mins_zero);
  tcase_add_test(tc, x_prec_hash_zero);
  tcase_add_test(tc, x_zrpc_mins_zero);
  tcase_add_test(tc, x_zrpc_hash_zero);
  tcase_add_test(tc, x_width_prec_mins_zero);
  tcase_add_test(tc, x_width_prec_hash_zero);
  tcase_add_test(tc, x_dynamic_width_zero);
  tcase_add_test(tc, x_dynamic_prec_zero);
  tcase_add_test(tc, x_dynamic_width_prec_zero);
  tcase_add_test(tc, X_mins_zero);
  tcase_add_test(tc, X_hash_zero);
  tcase_add_test(tc, X_fzer_zero);
  tcase_add_test(tc, X_width_zero);
  tcase_add_test(tc, X_zrpc_zero);
  tcase_add_test(tc, X_prec_zero);
  tcase_add_test(tc, X_width_prec_zero);
  tcase_add_test(tc, X_width_mins_zero);
  tcase_add_test(tc, X_width_hash_zero);
  tcase_add_test(tc, X_width_fzer_zero);
  tcase_add_test(tc, X_zrwth_hash_zero);
  tcase_add_test(tc, X_prec_mins_zero);
  tcase_add_test(tc, X_prec_hash_zero);
  tcase_add_test(tc, X_zrpc_mins_zero);
  tcase_add_test(tc, X_zrpc_hash_zero);
  tcase_add_test(tc, X_width_prec_mins_zero);
  tcase_add_test(tc, X_width_prec_hash_zero);
  tcase_add_test(tc, X_dynamic_width_zero);
  tcase_add_test(tc, X_dynamic_prec_zero);
  tcase_add_test(tc, X_dynamic_width_prec_zero);
  tcase_add_test(tc, hd_mins_zero);
  tcase_add_test(tc, hd_plus_zero);
  tcase_add_test(tc, hd_spac_zero);
  tcase_add_test(tc, hd_fzer_zero);
  tcase_add_test(tc, hd_width_zero);
  tcase_add_test(tc, hd_zrpc_zero);
  tcase_add_test(tc, hd_prec_zero);
  tcase_add_test(tc, hd_width_prec_zero);
  tcase_add_test(tc, hd_width_mins_zero);
  tcase_add_test(tc, hd_width_plus_zero);
  tcase_add_test(tc, hd_width_spac_zero);
  tcase_add_test(tc, hd_width_fzer_zero);
  tcase_add_test(tc, hd_zrwth_plus_zero);
  tcase_add_test(tc, hd_zrwth_spac_zero);
  tcase_add_test(tc, hd_prec_mins_zero);
  tcase_add_test(tc, hd_prec_plus_zero);
  tcase_add_test(tc, hd_prec_spac_zero);
  tcase_add_test(tc, hd_zrpc_mins_zero);
  tcase_add_test(tc, hd_zrpc_plus_zero);
  tcase_add_test(tc, hd_zrpc_spac_zero);
  tcase_add_test(tc, hd_width_prec_mins_zero);
  tcase_add_test(tc, hd_width_prec_plus_zero);
  tcase_add_test(tc, hd_width_prec_spac_zero);
  tcase_add_test(tc, hd_dynamic_width_zero);
  tcase_add_test(tc, hd_dynamic_prec_zero);
  tcase_add_test(tc, hd_dynamic_width_prec_zero);
  tcase_add_test(tc, hi_mins_zero);
  tcase_add_test(tc, hi_plus_zero);
  tcase_add_test(tc, hi_spac_zero);
  tcase_add_test(tc, hi_fzer_zero);
  tcase_add_test(tc, hi_width_zero);
  tcase_add_test(tc, hi_zrpc_zero);
  tcase_add_test(tc, hi_prec_zero);
  tcase_add_test(tc, hi_width_prec_zero);
  tcase_add_test(tc, hi_width_mins_zero);
  tcase_add_test(tc, hi_width_plus_zero);
  tcase_add_test(tc, hi_width_spac_zero);
  tcase_add_test(tc, hi_width_fzer_zero);
  tcase_add_test(tc, hi_zrwth_plus_zero);
  tcase_add_test(tc, hi_zrwth_spac_zero);
  tcase_add_test(tc, hi_prec_mins_zero);
  tcase_add_test(tc, hi_prec_plus_zero);
  tcase_add_test(tc, hi_prec_spac_zero);
  tcase_add_test(tc, hi_zrpc_mins_zero);
  tcase_add_test(tc, hi_zrpc_plus_zero);
  tcase_add_test(tc, hi_zrpc_spac_zero);
  tcase_add_test(tc, hi_width_prec_mins_zero);
  tcase_add_test(tc, hi_width_prec_plus_zero);
  tcase_add_test(tc, hi_width_prec_spac_zero);
  tcase_add_test(tc, hi_dynamic_width_zero);
  tcase_add_test(tc, hi_dynamic_prec_zero);
  tcase_add_test(tc, hi_dynamic_width_prec_zero);
  tcase_add_test(tc, ho_mins_zero);
  tcase_add_test(tc, ho_hash_zero);
  tcase_add_test(tc, ho_fzer_zero);
  tcase_add_test(tc, ho_width_zero);
  tcase_add_test(tc, ho_zrpc_zero);
  tcase_add_test(tc, ho_prec_zero);
  tcase_add_test(tc, ho_width_prec_zero);
  tcase_add_test(tc, ho_width_mins_zero);
  tcase_add_test(tc, ho_width_hash_zero);
  tcase_add_test(tc, ho_width_fzer_zero);
  tcase_add_test(tc, ho_zrwth_hash_zero);
  tcase_add_test(tc, ho_prec_mins_zero);
  tcase_add_test(tc, ho_prec_hash_zero);
  tcase_add_test(tc, ho_zrpc_mins_zero);
  tcase_add_test(tc, ho_zrpc_hash_zero);
  tcase_add_test(tc, ho_width_prec_mins_zero);
  tcase_add_test(tc, ho_width_prec_hash_zero);
  tcase_add_test(tc, ho_dynamic_width_zero);
  tcase_add_test(tc, ho_dynamic_prec_zero);
  tcase_add_test(tc, ho_dynamic_width_prec_zero);
  tcase_add_test(tc, hu_mins_zero);
  tcase_add_test(tc, hu_fzer_zero);
  tcase_add_test(tc, hu_width_zero);
  tcase_add_test(tc, hu_zrpc_zero);
  tcase_add_test(tc, hu_prec_zero);
  tcase_add_test(tc, hu_width_prec_zero);
  tcase_add_test(tc, hu_width_mins_zero);
  tcase_add_test(tc, hu_width_fzer_zero);
  tcase_add_test(tc, hu_prec_mins_zero);
  tcase_add_test(tc, hu_zrpc_mins_zero);
  tcase_add_test(tc, hu_width_prec_mins_zero);
  tcase_add_test(tc, hu_dynamic_width_zero);
  tcase_add_test(tc, hu_dynamic_prec_zero);
  tcase_add_test(tc, hu_dynamic_width_prec_zero);
  tcase_add_test(tc, hx_mins_zero);
  tcase_add_test(tc, hx_hash_zero);
  tcase_add_test(tc, hx_fzer_zero);
  tcase_add_test(tc, hx_width_zero);
  tcase_add_test(tc, hx_zrpc_zero);
  tcase_add_test(tc, hx_prec_zero);
  tcase_add_test(tc, hx_width_prec_zero);
  tcase_add_test(tc, hx_width_mins_zero);
  tcase_add_test(tc, hx_width_hash_zero);
  tcase_add_test(tc, hx_width_fzer_zero);
  tcase_add_test(tc, hx_zrwth_hash_zero);
  tcase_add_test(tc, hx_prec_mins_zero);
  tcase_add_test(tc, hx_prec_hash_zero);
  tcase_add_test(tc, hx_zrpc_mins_zero);
  tcase_add_test(tc, hx_zrpc_hash_zero);
  tcase_add_test(tc, hx_width_prec_mins_zero);
  tcase_add_test(tc, hx_width_prec_hash_zero);
  tcase_add_test(tc, hx_dynamic_width_zero);
  tcase_add_test(tc, hx_dynamic_prec_zero);
  tcase_add_test(tc, hx_dynamic_width_prec_zero);
  tcase_add_test(tc, hX_mins_zero);
  tcase_add_test(tc, hX_hash_zero);
  tcase_add_test(tc, hX_fzer_zero);
  tcase_add_test(tc, hX_width_zero);
  tcase_add_test(tc, hX_zrpc_zero);
  tcase_add_test(tc, hX_prec_zero);
  tcase_add_test(tc, hX_width_prec_zero);
  tcase_add_test(tc, hX_width_mins_zero);
  tcase_add_test(tc, hX_width_hash_zero);
  tcase_add_test(tc, hX_width_fzer_zero);
  tcase_add_test(tc, hX_zrwth_hash_zero);
  tcase_add_test(tc, hX_prec_mins_zero);
  tcase_add_test(tc, hX_prec_hash_zero);
  tcase_add_test(tc, hX_zrpc_mins_zero);
  tcase_add_test(tc, hX_zrpc_hash_zero);
  tcase_add_test(tc, hX_width_prec_mins_zero);
  tcase_add_test(tc, hX_width_prec_hash_zero);
  tcase_add_test(tc, hX_dynamic_width_zero);
  tcase_add_test(tc, hX_dynamic_prec_zero);
  tcase_add_test(tc, hX_dynamic_width_prec_zero);
  tcase_add_test(tc, hhd_mins_zero);
  tcase_add_test(tc, hhd_plus_zero);
  tcase_add_test(tc, hhd_spac_zero);
  tcase_add_test(tc, hhd_fzer_zero);
  tcase_add_test(tc, hhd_width_zero);
  tcase_add_test(tc, hhd_zrpc_zero);
  tcase_add_test(tc, hhd_prec_zero);
  tcase_add_test(tc, hhd_width_prec_zero);
  tcase_add_test(tc, hhd_width_mins_zero);
  tcase_add_test(tc, hhd_width_plus_zero);
  tcase_add_test(tc, hhd_width_spac_zero);
  tcase_add_test(tc, hhd_width_fzer_zero);
  tcase_add_test(tc, hhd_zrwth_plus_zero);
  tcase_add_test(tc, hhd_zrwth_spac_zero);
  tcase_add_test(tc, hhd_prec_mins_zero);
  tcase_add_test(tc, hhd_prec_plus_zero);
  tcase_add_test(tc, hhd_prec_spac_zero);
  tcase_add_test(tc, hhd_zrpc_mins_zero);
  tcase_add_test(tc, hhd_zrpc_plus_zero);
  tcase_add_test(tc, hhd_zrpc_spac_zero);
  tcase_add_test(tc, hhd_width_prec_mins_zero);
  tcase_add_test(tc, hhd_width_prec_plus_zero);
  tcase_add_test(tc, hhd_width_prec_spac_zero);
  tcase_add_test(tc, hhd_dynamic_width_zero);
  tcase_add_test(tc, hhd_dynamic_prec_zero);
  tcase_add_test(tc, hhd_dynamic_width_prec_zero);
  tcase_add_test(tc, hhi_mins_zero);
  tcase_add_test(tc, hhi_plus_zero);
  tcase_add_test(tc, hhi_spac_zero);
  tcase_add_test(tc, hhi_fzer_zero);
  tcase_add_test(tc, hhi_width_zero);
  tcase_add_test(tc, hhi_zrpc_zero);
  tcase_add_test(tc, hhi_prec_zero);
  tcase_add_test(tc, hhi_width_prec_zero);
  tcase_add_test(tc, hhi_width_mins_zero);
  tcase_add_test(tc, hhi_width_plus_zero);
  tcase_add_test(tc, hhi_width_spac_zero);
  tcase_add_test(tc, hhi_width_fzer_zero);
  tcase_add_test(tc, hhi_zrwth_plus_zero);
  tcase_add_test(tc, hhi_zrwth_spac_zero);
  tcase_add_test(tc, hhi_prec_mins_zero);
  tcase_add_test(tc, hhi_prec_plus_zero);
  tcase_add_test(tc, hhi_prec_spac_zero);
  tcase_add_test(tc, hhi_zrpc_mins_zero);
  tcase_add_test(tc, hhi_zrpc_plus_zero);
  tcase_add_test(tc, hhi_zrpc_spac_zero);
  tcase_add_test(tc, hhi_width_prec_mins_zero);
  tcase_add_test(tc, hhi_width_prec_plus_zero);
  tcase_add_test(tc, hhi_width_prec_spac_zero);
  tcase_add_test(tc, hhi_dynamic_width_zero);
  tcase_add_test(tc, hhi_dynamic_prec_zero);
  tcase_add_test(tc, hhi_dynamic_width_prec_zero);
  tcase_add_test(tc, hho_mins_zero);
  tcase_add_test(tc, hho_hash_zero);
  tcase_add_test(tc, hho_fzer_zero);
  tcase_add_test(tc, hho_width_zero);
  tcase_add_test(tc, hho_zrpc_zero);
  tcase_add_test(tc, hho_prec_zero);
  tcase_add_test(tc, hho_width_prec_zero);
  tcase_add_test(tc, hho_width_mins_zero);
  tcase_add_test(tc, hho_width_hash_zero);
  tcase_add_test(tc, hho_width_fzer_zero);
  tcase_add_test(tc, hho_zrwth_hash_zero);
  tcase_add_test(tc, hho_prec_mins_zero);
  tcase_add_test(tc, hho_prec_hash_zero);
  tcase_add_test(tc, hho_zrpc_mins_zero);
  tcase_add_test(tc, hho_zrpc_hash_zero);
  tcase_add_test(tc, hho_width_prec_mins_zero);
  tcase_add_test(tc, hho_width_prec_hash_zero);
  tcase_add_test(tc, hho_dynamic_width_zero);
  tcase_add_test(tc, hho_dynamic_prec_zero);
  tcase_add_test(tc, hho_dynamic_width_prec_zero);
  tcase_add_test(tc, hhu_mins_zero);
  tcase_add_test(tc, hhu_fzer_zero);
  tcase_add_test(tc, hhu_width_zero);
  tcase_add_test(tc, hhu_zrpc_zero);
  tcase_add_test(tc, hhu_prec_zero);
  tcase_add_test(tc, hhu_width_prec_zero);
  tcase_add_test(tc, hhu_width_mins_zero);
  tcase_add_test(tc, hhu_width_fzer_zero);
  tcase_add_test(tc, hhu_prec_mins_zero);
  tcase_add_test(tc, hhu_zrpc_mins_zero);
  tcase_add_test(tc, hhu_width_prec_mins_zero);
  tcase_add_test(tc, hhu_dynamic_width_zero);
  tcase_add_test(tc, hhu_dynamic_prec_zero);
  tcase_add_test(tc, hhu_dynamic_width_prec_zero);
  tcase_add_test(tc, hhx_mins_zero);
  tcase_add_test(tc, hhx_hash_zero);
  tcase_add_test(tc, hhx_fzer_zero);
  tcase_add_test(tc, hhx_width_zero);
  tcase_add_test(tc, hhx_zrpc_zero);
  tcase_add_test(tc, hhx_prec_zero);
  tcase_add_test(tc, hhx_width_prec_zero);
  tcase_add_test(tc, hhx_width_mins_zero);
  tcase_add_test(tc, hhx_width_hash_zero);
  tcase_add_test(tc, hhx_width_fzer_zero);
  tcase_add_test(tc, hhx_zrwth_hash_zero);
  tcase_add_test(tc, hhx_prec_mins_zero);
  tcase_add_test(tc, hhx_prec_hash_zero);
  tcase_add_test(tc, hhx_zrpc_mins_zero);
  tcase_add_test(tc, hhx_zrpc_hash_zero);
  tcase_add_test(tc, hhx_width_prec_mins_zero);
  tcase_add_test(tc, hhx_width_prec_hash_zero);
  tcase_add_test(tc, hhx_dynamic_width_zero);
  tcase_add_test(tc, hhx_dynamic_prec_zero);
  tcase_add_test(tc, hhx_dynamic_width_prec_zero);
  tcase_add_test(tc, hhX_mins_zero);
  tcase_add_test(tc, hhX_hash_zero);
  tcase_add_test(tc, hhX_fzer_zero);
  tcase_add_test(tc, hhX_width_zero);
  tcase_add_test(tc, hhX_zrpc_zero);
  tcase_add_test(tc, hhX_prec_zero);
  tcase_add_test(tc, hhX_width_prec_zero);
  tcase_add_test(tc, hhX_width_mins_zero);
  tcase_add_test(tc, hhX_width_hash_zero);
  tcase_add_test(tc, hhX_width_fzer_zero);
  tcase_add_test(tc, hhX_zrwth_hash_zero);
  tcase_add_test(tc, hhX_prec_mins_zero);
  tcase_add_test(tc, hhX_prec_hash_zero);
  tcase_add_test(tc, hhX_zrpc_mins_zero);
  tcase_add_test(tc, hhX_zrpc_hash_zero);
  tcase_add_test(tc, hhX_width_prec_mins_zero);
  tcase_add_test(tc, hhX_width_prec_hash_zero);
  tcase_add_test(tc, hhX_dynamic_width_zero);
  tcase_add_test(tc, hhX_dynamic_prec_zero);
  tcase_add_test(tc, hhX_dynamic_width_prec_zero);
  tcase_add_test(tc, ld_mins_zero);
  tcase_add_test(tc, ld_plus_zero);
  tcase_add_test(tc, ld_spac_zero);
  tcase_add_test(tc, ld_fzer_zero);
  tcase_add_test(tc, ld_width_zero);
  tcase_add_test(tc, ld_zrpc_zero);
  tcase_add_test(tc, ld_prec_zero);
  tcase_add_test(tc, ld_width_prec_zero);
  tcase_add_test(tc, ld_width_mins_zero);
  tcase_add_test(tc, ld_width_plus_zero);
  tcase_add_test(tc, ld_width_spac_zero);
  tcase_add_test(tc, ld_width_fzer_zero);
  tcase_add_test(tc, ld_zrwth_plus_zero);
  tcase_add_test(tc, ld_zrwth_spac_zero);
  tcase_add_test(tc, ld_prec_mins_zero);
  tcase_add_test(tc, ld_prec_plus_zero);
  tcase_add_test(tc, ld_prec_spac_zero);
  tcase_add_test(tc, ld_zrpc_mins_zero);
  tcase_add_test(tc, ld_zrpc_plus_zero);
  tcase_add_test(tc, ld_zrpc_spac_zero);
  tcase_add_test(tc, ld_width_prec_mins_zero);
  tcase_add_test(tc, ld_width_prec_plus_zero);
  tcase_add_test(tc, ld_width_prec_spac_zero);
  tcase_add_test(tc, ld_dynamic_width_zero);
  tcase_add_test(tc, ld_dynamic_prec_zero);
  tcase_add_test(tc, ld_dynamic_width_prec_zero);
  tcase_add_test(tc, li_mins_zero);
  tcase_add_test(tc, li_plus_zero);
  tcase_add_test(tc, li_spac_zero);
  tcase_add_test(tc, li_fzer_zero);
  tcase_add_test(tc, li_width_zero);
  tcase_add_test(tc, li_zrpc_zero);
  tcase_add_test(tc, li_prec_zero);
  tcase_add_test(tc, li_width_prec_zero);
  tcase_add_test(tc, li_width_mins_zero);
  tcase_add_test(tc, li_width_plus_zero);
  tcase_add_test(tc, li_width_spac_zero);
  tcase_add_test(tc, li_width_fzer_zero);
  tcase_add_test(tc, li_zrwth_plus_zero);
  tcase_add_test(tc, li_zrwth_spac_zero);
  tcase_add_test(tc, li_prec_mins_zero);
  tcase_add_test(tc, li_prec_plus_zero);
  tcase_add_test(tc, li_prec_spac_zero);
  tcase_add_test(tc, li_zrpc_mins_zero);
  tcase_add_test(tc, li_zrpc_plus_zero);
  tcase_add_test(tc, li_zrpc_spac_zero);
  tcase_add_test(tc, li_width_prec_mins_zero);
  tcase_add_test(tc, li_width_prec_plus_zero);
  tcase_add_test(tc, li_width_prec_spac_zero);
  tcase_add_test(tc, li_dynamic_width_zero);
  tcase_add_test(tc, li_dynamic_prec_zero);
  tcase_add_test(tc, li_dynamic_width_prec_zero);
  tcase_add_test(tc, lo_mins_zero);
  tcase_add_test(tc, lo_hash_zero);
  tcase_add_test(tc, lo_fzer_zero);
  tcase_add_test(tc, lo_width_zero);
  tcase_add_test(tc, lo_zrpc_zero);
  tcase_add_test(tc, lo_prec_zero);
  tcase_add_test(tc, lo_width_prec_zero);
  tcase_add_test(tc, lo_width_mins_zero);
  tcase_add_test(tc, lo_width_hash_zero);
  tcase_add_test(tc, lo_width_fzer_zero);
  tcase_add_test(tc, lo_zrwth_hash_zero);
  tcase_add_test(tc, lo_prec_mins_zero);
  tcase_add_test(tc, lo_prec_hash_zero);
  tcase_add_test(tc, lo_zrpc_mins_zero);
  tcase_add_test(tc, lo_zrpc_hash_zero);
  tcase_add_test(tc, lo_width_prec_mins_zero);
  tcase_add_test(tc, lo_width_prec_hash_zero);
  tcase_add_test(tc, lo_dynamic_width_zero);
  tcase_add_test(tc, lo_dynamic_prec_zero);
  tcase_add_test(tc, lo_dynamic_width_prec_zero);
  tcase_add_test(tc, lu_mins_zero);
  tcase_add_test(tc, lu_fzer_zero);
  tcase_add_test(tc, lu_width_zero);
  tcase_add_test(tc, lu_zrpc_zero);
  tcase_add_test(tc, lu_prec_zero);
  tcase_add_test(tc, lu_width_prec_zero);
  tcase_add_test(tc, lu_width_mins_zero);
  tcase_add_test(tc, lu_width_fzer_zero);
  tcase_add_test(tc, lu_prec_mins_zero);
  tcase_add_test(tc, lu_zrpc_mins_zero);
  tcase_add_test(tc, lu_width_prec_mins_zero);
  tcase_add_test(tc, lu_dynamic_width_zero);
  tcase_add_test(tc, lu_dynamic_prec_zero);
  tcase_add_test(tc, lu_dynamic_width_prec_zero);
  tcase_add_test(tc, lx_mins_zero);
  tcase_add_test(tc, lx_hash_zero);
  tcase_add_test(tc, lx_fzer_zero);
  tcase_add_test(tc, lx_width_zero);
  tcase_add_test(tc, lx_zrpc_zero);
  tcase_add_test(tc, lx_prec_zero);
  tcase_add_test(tc, lx_width_prec_zero);
  tcase_add_test(tc, lx_width_mins_zero);
  tcase_add_test(tc, lx_width_hash_zero);
  tcase_add_test(tc, lx_width_fzer_zero);
  tcase_add_test(tc, lx_zrwth_hash_zero);
  tcase_add_test(tc, lx_prec_mins_zero);
  tcase_add_test(tc, lx_prec_hash_zero);
  tcase_add_test(tc, lx_zrpc_mins_zero);
  tcase_add_test(tc, lx_zrpc_hash_zero);
  tcase_add_test(tc, lx_width_prec_mins_zero);
  tcase_add_test(tc, lx_width_prec_hash_zero);
  tcase_add_test(tc, lx_dynamic_width_zero);
  tcase_add_test(tc, lx_dynamic_prec_zero);
  tcase_add_test(tc, lx_dynamic_width_prec_zero);
  tcase_add_test(tc, lX_mins_zero);
  tcase_add_test(tc, lX_hash_zero);
  tcase_add_test(tc, lX_fzer_zero);
  tcase_add_test(tc, lX_width_zero);
  tcase_add_test(tc, lX_zrpc_zero);
  tcase_add_test(tc, lX_prec_zero);
  tcase_add_test(tc, lX_width_prec_zero);
  tcase_add_test(tc, lX_width_mins_zero);
  tcase_add_test(tc, lX_width_hash_zero);
  tcase_add_test(tc, lX_width_fzer_zero);
  tcase_add_test(tc, lX_zrwth_hash_zero);
  tcase_add_test(tc, lX_prec_mins_zero);
  tcase_add_test(tc, lX_prec_hash_zero);
  tcase_add_test(tc, lX_zrpc_mins_zero);
  tcase_add_test(tc, lX_zrpc_hash_zero);
  tcase_add_test(tc, lX_width_prec_mins_zero);
  tcase_add_test(tc, lX_width_prec_hash_zero);
  tcase_add_test(tc, lX_dynamic_width_zero);
  tcase_add_test(tc, lX_dynamic_prec_zero);
  tcase_add_test(tc, lX_dynamic_width_prec_zero);
  tcase_add_test(tc, lld_mins_zero);
  tcase_add_test(tc, lld_plus_zero);
  tcase_add_test(tc, lld_spac_zero);
  tcase_add_test(tc, lld_fzer_zero);
  tcase_add_test(tc, lld_width_zero);
  tcase_add_test(tc, lld_zrpc_zero);
  tcase_add_test(tc, lld_prec_zero);
  tcase_add_test(tc, lld_width_prec_zero);
  tcase_add_test(tc, lld_width_mins_zero);
  tcase_add_test(tc, lld_width_plus_zero);
  tcase_add_test(tc, lld_width_spac_zero);
  tcase_add_test(tc, lld_width_fzer_zero);
  tcase_add_test(tc, lld_zrwth_plus_zero);
  tcase_add_test(tc, lld_zrwth_spac_zero);
  tcase_add_test(tc, lld_prec_mins_zero);
  tcase_add_test(tc, lld_prec_plus_zero);
  tcase_add_test(tc, lld_prec_spac_zero);
  tcase_add_test(tc, lld_zrpc_mins_zero);
  tcase_add_test(tc, lld_zrpc_plus_zero);
  tcase_add_test(tc, lld_zrpc_spac_zero);
  tcase_add_test(tc, lld_width_prec_mins_zero);
  tcase_add_test(tc, lld_width_prec_plus_zero);
  tcase_add_test(tc, lld_width_prec_spac_zero);
  tcase_add_test(tc, lld_dynamic_width_zero);
  tcase_add_test(tc, lld_dynamic_prec_zero);
  tcase_add_test(tc, lld_dynamic_width_prec_zero);
  tcase_add_test(tc, lli_mins_zero);
  tcase_add_test(tc, lli_plus_zero);
  tcase_add_test(tc, lli_spac_zero);
  tcase_add_test(tc, lli_fzer_zero);
  tcase_add_test(tc, lli_width_zero);
  tcase_add_test(tc, lli_zrpc_zero);
  tcase_add_test(tc, lli_prec_zero);
  tcase_add_test(tc, lli_width_prec_zero);
  tcase_add_test(tc, lli_width_mins_zero);
  tcase_add_test(tc, lli_width_plus_zero);
  tcase_add_test(tc, lli_width_spac_zero);
  tcase_add_test(tc, lli_width_fzer_zero);
  tcase_add_test(tc, lli_zrwth_plus_zero);
  tcase_add_test(tc, lli_zrwth_spac_zero);
  tcase_add_test(tc, lli_prec_mins_zero);
  tcase_add_test(tc, lli_prec_plus_zero);
  tcase_add_test(tc, lli_prec_spac_zero);
  tcase_add_test(tc, lli_zrpc_mins_zero);
  tcase_add_test(tc, lli_zrpc_plus_zero);
  tcase_add_test(tc, lli_zrpc_spac_zero);
  tcase_add_test(tc, lli_width_prec_mins_zero);
  tcase_add_test(tc, lli_width_prec_plus_zero);
  tcase_add_test(tc, lli_width_prec_spac_zero);
  tcase_add_test(tc, lli_dynamic_width_zero);
  tcase_add_test(tc, lli_dynamic_prec_zero);
  tcase_add_test(tc, lli_dynamic_width_prec_zero);
  tcase_add_test(tc, llo_mins_zero);
  tcase_add_test(tc, llo_hash_zero);
  tcase_add_test(tc, llo_fzer_zero);
  tcase_add_test(tc, llo_width_zero);
  tcase_add_test(tc, llo_zrpc_zero);
  tcase_add_test(tc, llo_prec_zero);
  tcase_add_test(tc, llo_width_prec_zero);
  tcase_add_test(tc, llo_width_mins_zero);
  tcase_add_test(tc, llo_width_hash_zero);
  tcase_add_test(tc, llo_width_fzer_zero);
  tcase_add_test(tc, llo_zrwth_hash_zero);
  tcase_add_test(tc, llo_prec_mins_zero);
  tcase_add_test(tc, llo_prec_hash_zero);
  tcase_add_test(tc, llo_zrpc_mins_zero);
  tcase_add_test(tc, llo_zrpc_hash_zero);
  tcase_add_test(tc, llo_width_prec_mins_zero);
  tcase_add_test(tc, llo_width_prec_hash_zero);
  tcase_add_test(tc, llo_dynamic_width_zero);
  tcase_add_test(tc, llo_dynamic_prec_zero);
  tcase_add_test(tc, llo_dynamic_width_prec_zero);
  tcase_add_test(tc, llu_mins_zero);
  tcase_add_test(tc, llu_fzer_zero);
  tcase_add_test(tc, llu_width_zero);
  tcase_add_test(tc, llu_zrpc_zero);
  tcase_add_test(tc, llu_prec_zero);
  tcase_add_test(tc, llu_width_prec_zero);
  tcase_add_test(tc, llu_width_mins_zero);
  tcase_add_test(tc, llu_width_fzer_zero);
  tcase_add_test(tc, llu_prec_mins_zero);
  tcase_add_test(tc, llu_zrpc_mins_zero);
  tcase_add_test(tc, llu_width_prec_mins_zero);
  tcase_add_test(tc, llu_dynamic_width_zero);
  tcase_add_test(tc, llu_dynamic_prec_zero);
  tcase_add_test(tc, llu_dynamic_width_prec_zero);
  tcase_add_test(tc, llx_mins_zero);
  tcase_add_test(tc, llx_hash_zero);
  tcase_add_test(tc, llx_fzer_zero);
  tcase_add_test(tc, llx_width_zero);
  tcase_add_test(tc, llx_zrpc_zero);
  tcase_add_test(tc, llx_prec_zero);
  tcase_add_test(tc, llx_width_prec_zero);
  tcase_add_test(tc, llx_width_mins_zero);
  tcase_add_test(tc, llx_width_hash_zero);
  tcase_add_test(tc, llx_width_fzer_zero);
  tcase_add_test(tc, llx_zrwth_hash_zero);
  tcase_add_test(tc, llx_prec_mins_zero);
  tcase_add_test(tc, llx_prec_hash_zero);
  tcase_add_test(tc, llx_zrpc_mins_zero);
  tcase_add_test(tc, llx_zrpc_hash_zero);
  tcase_add_test(tc, llx_width_prec_mins_zero);
  tcase_add_test(tc, llx_width_prec_hash_zero);
  tcase_add_test(tc, llx_dynamic_width_zero);
  tcase_add_test(tc, llx_dynamic_prec_zero);
  tcase_add_test(tc, llx_dynamic_width_prec_zero);
  tcase_add_test(tc, llX_mins_zero);
  tcase_add_test(tc, llX_hash_zero);
  tcase_add_test(tc, llX_fzer_zero);
  tcase_add_test(tc, llX_width_zero);
  tcase_add_test(tc, llX_zrpc_zero);
  tcase_add_test(tc, llX_prec_zero);
  tcase_add_test(tc, llX_width_prec_zero);
  tcase_add_test(tc, llX_width_mins_zero);
  tcase_add_test(tc, llX_width_hash_zero);
  tcase_add_test(tc, llX_width_fzer_zero);
  tcase_add_test(tc, llX_zrwth_hash_zero);
  tcase_add_test(tc, llX_prec_mins_zero);
  tcase_add_test(tc, llX_prec_hash_zero);
  tcase_add_test(tc, llX_zrpc_mins_zero);
  tcase_add_test(tc, llX_zrpc_hash_zero);
  tcase_add_test(tc, llX_width_prec_mins_zero);
  tcase_add_test(tc, llX_width_prec_hash_zero);
  tcase_add_test(tc, llX_dynamic_width_zero);
  tcase_add_test(tc, llX_dynamic_prec_zero);
  tcase_add_test(tc, llX_dynamic_width_prec_zero);
  tcase_add_test(tc, d_mins_post);
  tcase_add_test(tc, d_plus_post);
  tcase_add_test(tc, d_spac_post);
  tcase_add_test(tc, d_fzer_post);
  tcase_add_test(tc, d_mins_negt);
  tcase_add_test(tc, d_plus_negt);
  tcase_add_test(tc, d_spac_negt);
  tcase_add_test(tc, d_fzer_negt);
  tcase_add_test(tc, d_width_post);
  tcase_add_test(tc, d_zrpc_post);
  tcase_add_test(tc, d_prec_post);
  tcase_add_test(tc, d_width_prec_post);
  tcase_add_test(tc, d_width_negt);
  tcase_add_test(tc, d_zrpc_negt);
  tcase_add_test(tc, d_prec_negt);
  tcase_add_test(tc, d_width_prec_negt);
  tcase_add_test(tc, d_width_mins_post);
  tcase_add_test(tc, d_width_plus_post);
  tcase_add_test(tc, d_width_spac_post);
  tcase_add_test(tc, d_width_fzer_post);
  tcase_add_test(tc, d_width_mins_negt);
  tcase_add_test(tc, d_width_plus_negt);
  tcase_add_test(tc, d_width_spac_negt);
  tcase_add_test(tc, d_width_fzer_negt);
  tcase_add_test(tc, d_zrwth_plus_post);
  tcase_add_test(tc, d_zrwth_spac_post);
  tcase_add_test(tc, d_zrwth_plus_negt);
  tcase_add_test(tc, d_zrwth_spac_negt);
  tcase_add_test(tc, d_prec_mins_post);
  tcase_add_test(tc, d_prec_plus_post);
  tcase_add_test(tc, d_prec_spac_post);
  tcase_add_test(tc, d_prec_mins_negt);
  tcase_add_test(tc, d_prec_plus_negt);
  tcase_add_test(tc, d_prec_spac_negt);
  tcase_add_test(tc, d_zrpc_mins_post);
  tcase_add_test(tc, d_zrpc_plus_post);
  tcase_add_test(tc, d_zrpc_spac_post);
  tcase_add_test(tc, d_zrpc_mins_negt);
  tcase_add_test(tc, d_zrpc_plus_negt);
  tcase_add_test(tc, d_zrpc_spac_negt);
  tcase_add_test(tc, d_width_prec_mins_post);
  tcase_add_test(tc, d_width_prec_plus_post);
  tcase_add_test(tc, d_width_prec_spac_post);
  tcase_add_test(tc, d_width_prec_mins_negt);
  tcase_add_test(tc, d_width_prec_plus_negt);
  tcase_add_test(tc, d_width_prec_spac_negt);
  tcase_add_test(tc, d_dynamic_width_post);
  tcase_add_test(tc, d_dynamic_prec_post);
  tcase_add_test(tc, d_dynamic_width_prec_post);
  tcase_add_test(tc, d_dynamic_width_negt);
  tcase_add_test(tc, d_dynamic_prec_negt);
  tcase_add_test(tc, d_dynamic_width_prec_negt);
  tcase_add_test(tc, i_mins_post);
  tcase_add_test(tc, i_plus_post);
  tcase_add_test(tc, i_spac_post);
  tcase_add_test(tc, i_fzer_post);
  tcase_add_test(tc, i_mins_negt);
  tcase_add_test(tc, i_plus_negt);
  tcase_add_test(tc, i_spac_negt);
  tcase_add_test(tc, i_fzer_negt);
  tcase_add_test(tc, i_width_post);
  tcase_add_test(tc, i_zrpc_post);
  tcase_add_test(tc, i_prec_post);
  tcase_add_test(tc, i_width_prec_post);
  tcase_add_test(tc, i_width_negt);
  tcase_add_test(tc, i_zrpc_negt);
  tcase_add_test(tc, i_prec_negt);
  tcase_add_test(tc, i_width_prec_negt);
  tcase_add_test(tc, i_width_mins_post);
  tcase_add_test(tc, i_width_plus_post);
  tcase_add_test(tc, i_width_spac_post);
  tcase_add_test(tc, i_width_fzer_post);
  tcase_add_test(tc, i_width_mins_negt);
  tcase_add_test(tc, i_width_plus_negt);
  tcase_add_test(tc, i_width_spac_negt);
  tcase_add_test(tc, i_width_fzer_negt);
  tcase_add_test(tc, i_zrwth_plus_post);
  tcase_add_test(tc, i_zrwth_spac_post);
  tcase_add_test(tc, i_zrwth_plus_negt);
  tcase_add_test(tc, i_zrwth_spac_negt);
  tcase_add_test(tc, i_prec_mins_post);
  tcase_add_test(tc, i_prec_plus_post);
  tcase_add_test(tc, i_prec_spac_post);
  tcase_add_test(tc, i_prec_mins_negt);
  tcase_add_test(tc, i_prec_plus_negt);
  tcase_add_test(tc, i_prec_spac_negt);
  tcase_add_test(tc, i_zrpc_mins_post);
  tcase_add_test(tc, i_zrpc_plus_post);
  tcase_add_test(tc, i_zrpc_spac_post);
  tcase_add_test(tc, i_zrpc_mins_negt);
  tcase_add_test(tc, i_zrpc_plus_negt);
  tcase_add_test(tc, i_zrpc_spac_negt);
  tcase_add_test(tc, i_width_prec_mins_post);
  tcase_add_test(tc, i_width_prec_plus_post);
  tcase_add_test(tc, i_width_prec_spac_post);
  tcase_add_test(tc, i_width_prec_mins_negt);
  tcase_add_test(tc, i_width_prec_plus_negt);
  tcase_add_test(tc, i_width_prec_spac_negt);
  tcase_add_test(tc, i_dynamic_width_post);
  tcase_add_test(tc, i_dynamic_prec_post);
  tcase_add_test(tc, i_dynamic_width_prec_post);
  tcase_add_test(tc, i_dynamic_width_negt);
  tcase_add_test(tc, i_dynamic_prec_negt);
  tcase_add_test(tc, i_dynamic_width_prec_negt);
  tcase_add_test(tc, o_mins_post);
  tcase_add_test(tc, o_hash_post);
  tcase_add_test(tc, o_fzer_post);
  tcase_add_test(tc, o_mins_negt);
  tcase_add_test(tc, o_hash_negt);
  tcase_add_test(tc, o_fzer_negt);
  tcase_add_test(tc, o_width_post);
  tcase_add_test(tc, o_zrpc_post);
  tcase_add_test(tc, o_prec_post);
  tcase_add_test(tc, o_width_prec_post);
  tcase_add_test(tc, o_width_negt);
  tcase_add_test(tc, o_zrpc_negt);
  tcase_add_test(tc, o_prec_negt);
  tcase_add_test(tc, o_width_prec_negt);
  tcase_add_test(tc, o_width_mins_post);
  tcase_add_test(tc, o_width_hash_post);
  tcase_add_test(tc, o_width_fzer_post);
  tcase_add_test(tc, o_width_mins_negt);
  tcase_add_test(tc, o_width_hash_negt);
  tcase_add_test(tc, o_width_fzer_negt);
  tcase_add_test(tc, o_zrwth_hash_post);
  tcase_add_test(tc, o_zrwth_hash_negt);
  tcase_add_test(tc, o_prec_mins_post);
  tcase_add_test(tc, o_prec_hash_post);
  tcase_add_test(tc, o_prec_mins_negt);
  tcase_add_test(tc, o_prec_hash_negt);
  tcase_add_test(tc, o_zrpc_mins_post);
  tcase_add_test(tc, o_zrpc_hash_post);
  tcase_add_test(tc, o_zrpc_mins_negt);
  tcase_add_test(tc, o_zrpc_hash_negt);
  tcase_add_test(tc, o_width_prec_mins_post);
  tcase_add_test(tc, o_width_prec_hash_post);
  tcase_add_test(tc, o_width_prec_mins_negt);
  tcase_add_test(tc, o_width_prec_hash_negt);
  tcase_add_test(tc, o_dynamic_width_post);
  tcase_add_test(tc, o_dynamic_prec_post);
  tcase_add_test(tc, o_dynamic_width_prec_post);
  tcase_add_test(tc, o_dynamic_width_negt);
  tcase_add_test(tc, o_dynamic_prec_negt);
  tcase_add_test(tc, o_dynamic_width_prec_negt);
  tcase_add_test(tc, u_mins_post);
  tcase_add_test(tc, u_fzer_post);
  tcase_add_test(tc, u_mins_negt);
  tcase_add_test(tc, u_fzer_negt);
  tcase_add_test(tc, u_width_post);
  tcase_add_test(tc, u_zrpc_post);
  tcase_add_test(tc, u_prec_post);
  tcase_add_test(tc, u_width_prec_post);
  tcase_add_test(tc, u_width_negt);
  tcase_add_test(tc, u_zrpc_negt);
  tcase_add_test(tc, u_prec_negt);
  tcase_add_test(tc, u_width_prec_negt);
  tcase_add_test(tc, u_width_mins_post);
  tcase_add_test(tc, u_width_fzer_post);
  tcase_add_test(tc, u_width_mins_negt);
  tcase_add_test(tc, u_width_fzer_negt);
  tcase_add_test(tc, u_prec_mins_post);
  tcase_add_test(tc, u_prec_mins_negt);
  tcase_add_test(tc, u_zrpc_mins_post);
  tcase_add_test(tc, u_zrpc_mins_negt);
  tcase_add_test(tc, u_width_prec_mins_post);
  tcase_add_test(tc, u_width_prec_mins_negt);
  tcase_add_test(tc, u_dynamic_width_post);
  tcase_add_test(tc, u_dynamic_prec_post);
  tcase_add_test(tc, u_dynamic_width_prec_post);
  tcase_add_test(tc, u_dynamic_width_negt);
  tcase_add_test(tc, u_dynamic_prec_negt);
  tcase_add_test(tc, u_dynamic_width_prec_negt);
  tcase_add_test(tc, x_mins_post);
  tcase_add_test(tc, x_hash_post);
  tcase_add_test(tc, x_fzer_post);
  tcase_add_test(tc, x_mins_negt);
  tcase_add_test(tc, x_hash_negt);
  tcase_add_test(tc, x_fzer_negt);
  tcase_add_test(tc, x_width_post);
  tcase_add_test(tc, x_zrpc_post);
  tcase_add_test(tc, x_prec_post);
  tcase_add_test(tc, x_width_prec_post);
  tcase_add_test(tc, x_width_negt);
  tcase_add_test(tc, x_zrpc_negt);
  tcase_add_test(tc, x_prec_negt);
  tcase_add_test(tc, x_width_prec_negt);
  tcase_add_test(tc, x_width_mins_post);
  tcase_add_test(tc, x_width_hash_post);
  tcase_add_test(tc, x_width_fzer_post);
  tcase_add_test(tc, x_width_mins_negt);
  tcase_add_test(tc, x_width_hash_negt);
  tcase_add_test(tc, x_width_fzer_negt);
  tcase_add_test(tc, x_zrwth_hash_post);
  tcase_add_test(tc, x_zrwth_hash_negt);
  tcase_add_test(tc, x_prec_mins_post);
  tcase_add_test(tc, x_prec_hash_post);
  tcase_add_test(tc, x_prec_mins_negt);
  tcase_add_test(tc, x_prec_hash_negt);
  tcase_add_test(tc, x_zrpc_mins_post);
  tcase_add_test(tc, x_zrpc_hash_post);
  tcase_add_test(tc, x_zrpc_mins_negt);
  tcase_add_test(tc, x_zrpc_hash_negt);
  tcase_add_test(tc, x_width_prec_mins_post);
  tcase_add_test(tc, x_width_prec_hash_post);
  tcase_add_test(tc, x_width_prec_mins_negt);
  tcase_add_test(tc, x_width_prec_hash_negt);
  tcase_add_test(tc, x_dynamic_width_post);
  tcase_add_test(tc, x_dynamic_prec_post);
  tcase_add_test(tc, x_dynamic_width_prec_post);
  tcase_add_test(tc, x_dynamic_width_negt);
  tcase_add_test(tc, x_dynamic_prec_negt);
  tcase_add_test(tc, x_dynamic_width_prec_negt);
  tcase_add_test(tc, X_mins_post);
  tcase_add_test(tc, X_hash_post);
  tcase_add_test(tc, X_fzer_post);
  tcase_add_test(tc, X_mins_negt);
  tcase_add_test(tc, X_hash_negt);
  tcase_add_test(tc, X_fzer_negt);
  tcase_add_test(tc, X_width_post);
  tcase_add_test(tc, X_zrpc_post);
  tcase_add_test(tc, X_prec_post);
  tcase_add_test(tc, X_width_prec_post);
  tcase_add_test(tc, X_width_negt);
  tcase_add_test(tc, X_zrpc_negt);
  tcase_add_test(tc, X_prec_negt);
  tcase_add_test(tc, X_width_prec_negt);
  tcase_add_test(tc, X_width_mins_post);
  tcase_add_test(tc, X_width_hash_post);
  tcase_add_test(tc, X_width_fzer_post);
  tcase_add_test(tc, X_width_mins_negt);
  tcase_add_test(tc, X_width_hash_negt);
  tcase_add_test(tc, X_width_fzer_negt);
  tcase_add_test(tc, X_zrwth_hash_post);
  tcase_add_test(tc, X_zrwth_hash_negt);
  tcase_add_test(tc, X_prec_mins_post);
  tcase_add_test(tc, X_prec_hash_post);
  tcase_add_test(tc, X_prec_mins_negt);
  tcase_add_test(tc, X_prec_hash_negt);
  tcase_add_test(tc, X_zrpc_mins_post);
  tcase_add_test(tc, X_zrpc_hash_post);
  tcase_add_test(tc, X_zrpc_mins_negt);
  tcase_add_test(tc, X_zrpc_hash_negt);
  tcase_add_test(tc, X_width_prec_mins_post);
  tcase_add_test(tc, X_width_prec_hash_post);
  tcase_add_test(tc, X_width_prec_mins_negt);
  tcase_add_test(tc, X_width_prec_hash_negt);
  tcase_add_test(tc, X_dynamic_width_post);
  tcase_add_test(tc, X_dynamic_prec_post);
  tcase_add_test(tc, X_dynamic_width_prec_post);
  tcase_add_test(tc, X_dynamic_width_negt);
  tcase_add_test(tc, X_dynamic_prec_negt);
  tcase_add_test(tc, X_dynamic_width_prec_negt);
  tcase_add_test(tc, hd_mins_post);
  tcase_add_test(tc, hd_plus_post);
  tcase_add_test(tc, hd_spac_post);
  tcase_add_test(tc, hd_fzer_post);
  tcase_add_test(tc, hd_mins_negt);
  tcase_add_test(tc, hd_plus_negt);
  tcase_add_test(tc, hd_spac_negt);
  tcase_add_test(tc, hd_fzer_negt);
  tcase_add_test(tc, hd_width_post);
  tcase_add_test(tc, hd_zrpc_post);
  tcase_add_test(tc, hd_prec_post);
  tcase_add_test(tc, hd_width_prec_post);
  tcase_add_test(tc, hd_width_negt);
  tcase_add_test(tc, hd_zrpc_negt);
  tcase_add_test(tc, hd_prec_negt);
  tcase_add_test(tc, hd_width_prec_negt);
  tcase_add_test(tc, hd_width_mins_post);
  tcase_add_test(tc, hd_width_plus_post);
  tcase_add_test(tc, hd_width_spac_post);
  tcase_add_test(tc, hd_width_fzer_post);
  tcase_add_test(tc, hd_width_mins_negt);
  tcase_add_test(tc, hd_width_plus_negt);
  tcase_add_test(tc, hd_width_spac_negt);
  tcase_add_test(tc, hd_width_fzer_negt);
  tcase_add_test(tc, hd_zrwth_plus_post);
  tcase_add_test(tc, hd_zrwth_spac_post);
  tcase_add_test(tc, hd_zrwth_plus_negt);
  tcase_add_test(tc, hd_zrwth_spac_negt);
  tcase_add_test(tc, hd_prec_mins_post);
  tcase_add_test(tc, hd_prec_plus_post);
  tcase_add_test(tc, hd_prec_spac_post);
  tcase_add_test(tc, hd_prec_mins_negt);
  tcase_add_test(tc, hd_prec_plus_negt);
  tcase_add_test(tc, hd_prec_spac_negt);
  tcase_add_test(tc, hd_zrpc_mins_post);
  tcase_add_test(tc, hd_zrpc_plus_post);
  tcase_add_test(tc, hd_zrpc_spac_post);
  tcase_add_test(tc, hd_zrpc_mins_negt);
  tcase_add_test(tc, hd_zrpc_plus_negt);
  tcase_add_test(tc, hd_zrpc_spac_negt);
  tcase_add_test(tc, hd_width_prec_mins_post);
  tcase_add_test(tc, hd_width_prec_plus_post);
  tcase_add_test(tc, hd_width_prec_spac_post);
  tcase_add_test(tc, hd_width_prec_mins_negt);
  tcase_add_test(tc, hd_width_prec_plus_negt);
  tcase_add_test(tc, hd_width_prec_spac_negt);
  tcase_add_test(tc, hd_dynamic_width_post);
  tcase_add_test(tc, hd_dynamic_prec_post);
  tcase_add_test(tc, hd_dynamic_width_prec_post);
  tcase_add_test(tc, hd_dynamic_width_negt);
  tcase_add_test(tc, hd_dynamic_prec_negt);
  tcase_add_test(tc, hd_dynamic_width_prec_negt);
  tcase_add_test(tc, hi_mins_post);
  tcase_add_test(tc, hi_plus_post);
  tcase_add_test(tc, hi_spac_post);
  tcase_add_test(tc, hi_fzer_post);
  tcase_add_test(tc, hi_mins_negt);
  tcase_add_test(tc, hi_plus_negt);
  tcase_add_test(tc, hi_spac_negt);
  tcase_add_test(tc, hi_fzer_negt);
  tcase_add_test(tc, hi_width_post);
  tcase_add_test(tc, hi_zrpc_post);
  tcase_add_test(tc, hi_prec_post);
  tcase_add_test(tc, hi_width_prec_post);
  tcase_add_test(tc, hi_width_negt);
  tcase_add_test(tc, hi_zrpc_negt);
  tcase_add_test(tc, hi_prec_negt);
  tcase_add_test(tc, hi_width_prec_negt);
  tcase_add_test(tc, hi_width_mins_post);
  tcase_add_test(tc, hi_width_plus_post);
  tcase_add_test(tc, hi_width_spac_post);
  tcase_add_test(tc, hi_width_fzer_post);
  tcase_add_test(tc, hi_width_mins_negt);
  tcase_add_test(tc, hi_width_plus_negt);
  tcase_add_test(tc, hi_width_spac_negt);
  tcase_add_test(tc, hi_width_fzer_negt);
  tcase_add_test(tc, hi_zrwth_plus_post);
  tcase_add_test(tc, hi_zrwth_spac_post);
  tcase_add_test(tc, hi_zrwth_plus_negt);
  tcase_add_test(tc, hi_zrwth_spac_negt);
  tcase_add_test(tc, hi_prec_mins_post);
  tcase_add_test(tc, hi_prec_plus_post);
  tcase_add_test(tc, hi_prec_spac_post);
  tcase_add_test(tc, hi_prec_mins_negt);
  tcase_add_test(tc, hi_prec_plus_negt);
  tcase_add_test(tc, hi_prec_spac_negt);
  tcase_add_test(tc, hi_zrpc_mins_post);
  tcase_add_test(tc, hi_zrpc_plus_post);
  tcase_add_test(tc, hi_zrpc_spac_post);
  tcase_add_test(tc, hi_zrpc_mins_negt);
  tcase_add_test(tc, hi_zrpc_plus_negt);
  tcase_add_test(tc, hi_zrpc_spac_negt);
  tcase_add_test(tc, hi_width_prec_mins_post);
  tcase_add_test(tc, hi_width_prec_plus_post);
  tcase_add_test(tc, hi_width_prec_spac_post);
  tcase_add_test(tc, hi_width_prec_mins_negt);
  tcase_add_test(tc, hi_width_prec_plus_negt);
  tcase_add_test(tc, hi_width_prec_spac_negt);
  tcase_add_test(tc, hi_dynamic_width_post);
  tcase_add_test(tc, hi_dynamic_prec_post);
  tcase_add_test(tc, hi_dynamic_width_prec_post);
  tcase_add_test(tc, hi_dynamic_width_negt);
  tcase_add_test(tc, hi_dynamic_prec_negt);
  tcase_add_test(tc, hi_dynamic_width_prec_negt);
  tcase_add_test(tc, ho_mins_post);
  tcase_add_test(tc, ho_hash_post);
  tcase_add_test(tc, ho_fzer_post);
  tcase_add_test(tc, ho_mins_negt);
  tcase_add_test(tc, ho_hash_negt);
  tcase_add_test(tc, ho_fzer_negt);
  tcase_add_test(tc, ho_width_post);
  tcase_add_test(tc, ho_zrpc_post);
  tcase_add_test(tc, ho_prec_post);
  tcase_add_test(tc, ho_width_prec_post);
  tcase_add_test(tc, ho_width_negt);
  tcase_add_test(tc, ho_zrpc_negt);
  tcase_add_test(tc, ho_prec_negt);
  tcase_add_test(tc, ho_width_prec_negt);
  tcase_add_test(tc, ho_width_mins_post);
  tcase_add_test(tc, ho_width_hash_post);
  tcase_add_test(tc, ho_width_fzer_post);
  tcase_add_test(tc, ho_width_mins_negt);
  tcase_add_test(tc, ho_width_hash_negt);
  tcase_add_test(tc, ho_width_fzer_negt);
  tcase_add_test(tc, ho_zrwth_hash_post);
  tcase_add_test(tc, ho_zrwth_hash_negt);
  tcase_add_test(tc, ho_prec_mins_post);
  tcase_add_test(tc, ho_prec_hash_post);
  tcase_add_test(tc, ho_prec_mins_negt);
  tcase_add_test(tc, ho_prec_hash_negt);
  tcase_add_test(tc, ho_zrpc_mins_post);
  tcase_add_test(tc, ho_zrpc_hash_post);
  tcase_add_test(tc, ho_zrpc_mins_negt);
  tcase_add_test(tc, ho_zrpc_hash_negt);
  tcase_add_test(tc, ho_width_prec_mins_post);
  tcase_add_test(tc, ho_width_prec_hash_post);
  tcase_add_test(tc, ho_width_prec_mins_negt);
  tcase_add_test(tc, ho_width_prec_hash_negt);
  tcase_add_test(tc, ho_dynamic_width_post);
  tcase_add_test(tc, ho_dynamic_prec_post);
  tcase_add_test(tc, ho_dynamic_width_prec_post);
  tcase_add_test(tc, ho_dynamic_width_negt);
  tcase_add_test(tc, ho_dynamic_prec_negt);
  tcase_add_test(tc, ho_dynamic_width_prec_negt);
  tcase_add_test(tc, hu_mins_post);
  tcase_add_test(tc, hu_fzer_post);
  tcase_add_test(tc, hu_mins_negt);
  tcase_add_test(tc, hu_fzer_negt);
  tcase_add_test(tc, hu_width_post);
  tcase_add_test(tc, hu_zrpc_post);
  tcase_add_test(tc, hu_prec_post);
  tcase_add_test(tc, hu_width_prec_post);
  tcase_add_test(tc, hu_width_negt);
  tcase_add_test(tc, hu_zrpc_negt);
  tcase_add_test(tc, hu_prec_negt);
  tcase_add_test(tc, hu_width_prec_negt);
  tcase_add_test(tc, hu_width_mins_post);
  tcase_add_test(tc, hu_width_fzer_post);
  tcase_add_test(tc, hu_width_mins_negt);
  tcase_add_test(tc, hu_width_fzer_negt);
  tcase_add_test(tc, hu_prec_mins_post);
  tcase_add_test(tc, hu_prec_mins_negt);
  tcase_add_test(tc, hu_zrpc_mins_post);
  tcase_add_test(tc, hu_zrpc_mins_negt);
  tcase_add_test(tc, hu_width_prec_mins_post);
  tcase_add_test(tc, hu_width_prec_mins_negt);
  tcase_add_test(tc, hu_dynamic_width_post);
  tcase_add_test(tc, hu_dynamic_prec_post);
  tcase_add_test(tc, hu_dynamic_width_prec_post);
  tcase_add_test(tc, hu_dynamic_width_negt);
  tcase_add_test(tc, hu_dynamic_prec_negt);
  tcase_add_test(tc, hu_dynamic_width_prec_negt);
  tcase_add_test(tc, hx_mins_post);
  tcase_add_test(tc, hx_hash_post);
  tcase_add_test(tc, hx_fzer_post);
  tcase_add_test(tc, hx_mins_negt);
  tcase_add_test(tc, hx_hash_negt);
  tcase_add_test(tc, hx_fzer_negt);
  tcase_add_test(tc, hx_width_post);
  tcase_add_test(tc, hx_zrpc_post);
  tcase_add_test(tc, hx_prec_post);
  tcase_add_test(tc, hx_width_prec_post);
  tcase_add_test(tc, hx_width_negt);
  tcase_add_test(tc, hx_zrpc_negt);
  tcase_add_test(tc, hx_prec_negt);
  tcase_add_test(tc, hx_width_prec_negt);
  tcase_add_test(tc, hx_width_mins_post);
  tcase_add_test(tc, hx_width_hash_post);
  tcase_add_test(tc, hx_width_fzer_post);
  tcase_add_test(tc, hx_width_mins_negt);
  tcase_add_test(tc, hx_width_hash_negt);
  tcase_add_test(tc, hx_width_fzer_negt);
  tcase_add_test(tc, hx_zrwth_hash_post);
  tcase_add_test(tc, hx_zrwth_hash_negt);
  tcase_add_test(tc, hx_prec_mins_post);
  tcase_add_test(tc, hx_prec_hash_post);
  tcase_add_test(tc, hx_prec_mins_negt);
  tcase_add_test(tc, hx_prec_hash_negt);
  tcase_add_test(tc, hx_zrpc_mins_post);
  tcase_add_test(tc, hx_zrpc_hash_post);
  tcase_add_test(tc, hx_zrpc_mins_negt);
  tcase_add_test(tc, hx_zrpc_hash_negt);
  tcase_add_test(tc, hx_width_prec_mins_post);
  tcase_add_test(tc, hx_width_prec_hash_post);
  tcase_add_test(tc, hx_width_prec_mins_negt);
  tcase_add_test(tc, hx_width_prec_hash_negt);
  tcase_add_test(tc, hx_dynamic_width_post);
  tcase_add_test(tc, hx_dynamic_prec_post);
  tcase_add_test(tc, hx_dynamic_width_prec_post);
  tcase_add_test(tc, hx_dynamic_width_negt);
  tcase_add_test(tc, hx_dynamic_prec_negt);
  tcase_add_test(tc, hx_dynamic_width_prec_negt);
  tcase_add_test(tc, hX_mins_post);
  tcase_add_test(tc, hX_hash_post);
  tcase_add_test(tc, hX_fzer_post);
  tcase_add_test(tc, hX_mins_negt);
  tcase_add_test(tc, hX_hash_negt);
  tcase_add_test(tc, hX_fzer_negt);
  tcase_add_test(tc, hX_width_post);
  tcase_add_test(tc, hX_zrpc_post);
  tcase_add_test(tc, hX_prec_post);
  tcase_add_test(tc, hX_width_prec_post);
  tcase_add_test(tc, hX_width_negt);
  tcase_add_test(tc, hX_zrpc_negt);
  tcase_add_test(tc, hX_prec_negt);
  tcase_add_test(tc, hX_width_prec_negt);
  tcase_add_test(tc, hX_width_mins_post);
  tcase_add_test(tc, hX_width_hash_post);
  tcase_add_test(tc, hX_width_fzer_post);
  tcase_add_test(tc, hX_width_mins_negt);
  tcase_add_test(tc, hX_width_hash_negt);
  tcase_add_test(tc, hX_width_fzer_negt);
  tcase_add_test(tc, hX_zrwth_hash_post);
  tcase_add_test(tc, hX_zrwth_hash_negt);
  tcase_add_test(tc, hX_prec_mins_post);
  tcase_add_test(tc, hX_prec_hash_post);
  tcase_add_test(tc, hX_prec_mins_negt);
  tcase_add_test(tc, hX_prec_hash_negt);
  tcase_add_test(tc, hX_zrpc_mins_post);
  tcase_add_test(tc, hX_zrpc_hash_post);
  tcase_add_test(tc, hX_zrpc_mins_negt);
  tcase_add_test(tc, hX_zrpc_hash_negt);
  tcase_add_test(tc, hX_width_prec_mins_post);
  tcase_add_test(tc, hX_width_prec_hash_post);
  tcase_add_test(tc, hX_width_prec_mins_negt);
  tcase_add_test(tc, hX_width_prec_hash_negt);
  tcase_add_test(tc, hX_dynamic_width_post);
  tcase_add_test(tc, hX_dynamic_prec_post);
  tcase_add_test(tc, hX_dynamic_width_prec_post);
  tcase_add_test(tc, hX_dynamic_width_negt);
  tcase_add_test(tc, hX_dynamic_prec_negt);
  tcase_add_test(tc, hX_dynamic_width_prec_negt);
  tcase_add_test(tc, hhd_mins_post);
  tcase_add_test(tc, hhd_plus_post);
  tcase_add_test(tc, hhd_spac_post);
  tcase_add_test(tc, hhd_fzer_post);
  tcase_add_test(tc, hhd_mins_negt);
  tcase_add_test(tc, hhd_plus_negt);
  tcase_add_test(tc, hhd_spac_negt);
  tcase_add_test(tc, hhd_fzer_negt);
  tcase_add_test(tc, hhd_width_post);
  tcase_add_test(tc, hhd_zrpc_post);
  tcase_add_test(tc, hhd_prec_post);
  tcase_add_test(tc, hhd_width_prec_post);
  tcase_add_test(tc, hhd_width_negt);
  tcase_add_test(tc, hhd_zrpc_negt);
  tcase_add_test(tc, hhd_prec_negt);
  tcase_add_test(tc, hhd_width_prec_negt);
  tcase_add_test(tc, hhd_width_mins_post);
  tcase_add_test(tc, hhd_width_plus_post);
  tcase_add_test(tc, hhd_width_spac_post);
  tcase_add_test(tc, hhd_width_fzer_post);
  tcase_add_test(tc, hhd_width_mins_negt);
  tcase_add_test(tc, hhd_width_plus_negt);
  tcase_add_test(tc, hhd_width_spac_negt);
  tcase_add_test(tc, hhd_width_fzer_negt);
  tcase_add_test(tc, hhd_zrwth_plus_post);
  tcase_add_test(tc, hhd_zrwth_spac_post);
  tcase_add_test(tc, hhd_zrwth_plus_negt);
  tcase_add_test(tc, hhd_zrwth_spac_negt);
  tcase_add_test(tc, hhd_prec_mins_post);
  tcase_add_test(tc, hhd_prec_plus_post);
  tcase_add_test(tc, hhd_prec_spac_post);
  tcase_add_test(tc, hhd_prec_mins_negt);
  tcase_add_test(tc, hhd_prec_plus_negt);
  tcase_add_test(tc, hhd_prec_spac_negt);
  tcase_add_test(tc, hhd_zrpc_mins_post);
  tcase_add_test(tc, hhd_zrpc_plus_post);
  tcase_add_test(tc, hhd_zrpc_spac_post);
  tcase_add_test(tc, hhd_zrpc_mins_negt);
  tcase_add_test(tc, hhd_zrpc_plus_negt);
  tcase_add_test(tc, hhd_zrpc_spac_negt);
  tcase_add_test(tc, hhd_width_prec_mins_post);
  tcase_add_test(tc, hhd_width_prec_plus_post);
  tcase_add_test(tc, hhd_width_prec_spac_post);
  tcase_add_test(tc, hhd_width_prec_mins_negt);
  tcase_add_test(tc, hhd_width_prec_plus_negt);
  tcase_add_test(tc, hhd_width_prec_spac_negt);
  tcase_add_test(tc, hhd_dynamic_width_post);
  tcase_add_test(tc, hhd_dynamic_prec_post);
  tcase_add_test(tc, hhd_dynamic_width_prec_post);
  tcase_add_test(tc, hhd_dynamic_width_negt);
  tcase_add_test(tc, hhd_dynamic_prec_negt);
  tcase_add_test(tc, hhd_dynamic_width_prec_negt);
  tcase_add_test(tc, hhi_mins_post);
  tcase_add_test(tc, hhi_plus_post);
  tcase_add_test(tc, hhi_spac_post);
  tcase_add_test(tc, hhi_fzer_post);
  tcase_add_test(tc, hhi_mins_negt);
  tcase_add_test(tc, hhi_plus_negt);
  tcase_add_test(tc, hhi_spac_negt);
  tcase_add_test(tc, hhi_fzer_negt);
  tcase_add_test(tc, hhi_width_post);
  tcase_add_test(tc, hhi_zrpc_post);
  tcase_add_test(tc, hhi_prec_post);
  tcase_add_test(tc, hhi_width_prec_post);
  tcase_add_test(tc, hhi_width_negt);
  tcase_add_test(tc, hhi_zrpc_negt);
  tcase_add_test(tc, hhi_prec_negt);
  tcase_add_test(tc, hhi_width_prec_negt);
  tcase_add_test(tc, hhi_width_mins_post);
  tcase_add_test(tc, hhi_width_plus_post);
  tcase_add_test(tc, hhi_width_spac_post);
  tcase_add_test(tc, hhi_width_fzer_post);
  tcase_add_test(tc, hhi_width_mins_negt);
  tcase_add_test(tc, hhi_width_plus_negt);
  tcase_add_test(tc, hhi_width_spac_negt);
  tcase_add_test(tc, hhi_width_fzer_negt);
  tcase_add_test(tc, hhi_zrwth_plus_post);
  tcase_add_test(tc, hhi_zrwth_spac_post);
  tcase_add_test(tc, hhi_zrwth_plus_negt);
  tcase_add_test(tc, hhi_zrwth_spac_negt);
  tcase_add_test(tc, hhi_prec_mins_post);
  tcase_add_test(tc, hhi_prec_plus_post);
  tcase_add_test(tc, hhi_prec_spac_post);
  tcase_add_test(tc, hhi_prec_mins_negt);
  tcase_add_test(tc, hhi_prec_plus_negt);
  tcase_add_test(tc, hhi_prec_spac_negt);
  tcase_add_test(tc, hhi_zrpc_mins_post);
  tcase_add_test(tc, hhi_zrpc_plus_post);
  tcase_add_test(tc, hhi_zrpc_spac_post);
  tcase_add_test(tc, hhi_zrpc_mins_negt);
  tcase_add_test(tc, hhi_zrpc_plus_negt);
  tcase_add_test(tc, hhi_zrpc_spac_negt);
  tcase_add_test(tc, hhi_width_prec_mins_post);
  tcase_add_test(tc, hhi_width_prec_plus_post);
  tcase_add_test(tc, hhi_width_prec_spac_post);
  tcase_add_test(tc, hhi_width_prec_mins_negt);
  tcase_add_test(tc, hhi_width_prec_plus_negt);
  tcase_add_test(tc, hhi_width_prec_spac_negt);
  tcase_add_test(tc, hhi_dynamic_width_post);
  tcase_add_test(tc, hhi_dynamic_prec_post);
  tcase_add_test(tc, hhi_dynamic_width_prec_post);
  tcase_add_test(tc, hhi_dynamic_width_negt);
  tcase_add_test(tc, hhi_dynamic_prec_negt);
  tcase_add_test(tc, hhi_dynamic_width_prec_negt);
  tcase_add_test(tc, hho_mins_post);
  tcase_add_test(tc, hho_hash_post);
  tcase_add_test(tc, hho_fzer_post);
  tcase_add_test(tc, hho_mins_negt);
  tcase_add_test(tc, hho_hash_negt);
  tcase_add_test(tc, hho_fzer_negt);
  tcase_add_test(tc, hho_width_post);
  tcase_add_test(tc, hho_zrpc_post);
  tcase_add_test(tc, hho_prec_post);
  tcase_add_test(tc, hho_width_prec_post);
  tcase_add_test(tc, hho_width_negt);
  tcase_add_test(tc, hho_zrpc_negt);
  tcase_add_test(tc, hho_prec_negt);
  tcase_add_test(tc, hho_width_prec_negt);
  tcase_add_test(tc, hho_width_mins_post);
  tcase_add_test(tc, hho_width_hash_post);
  tcase_add_test(tc, hho_width_fzer_post);
  tcase_add_test(tc, hho_width_mins_negt);
  tcase_add_test(tc, hho_width_hash_negt);
  tcase_add_test(tc, hho_width_fzer_negt);
  tcase_add_test(tc, hho_zrwth_hash_post);
  tcase_add_test(tc, hho_zrwth_hash_negt);
  tcase_add_test(tc, hho_prec_mins_post);
  tcase_add_test(tc, hho_prec_hash_post);
  tcase_add_test(tc, hho_prec_mins_negt);
  tcase_add_test(tc, hho_prec_hash_negt);
  tcase_add_test(tc, hho_zrpc_mins_post);
  tcase_add_test(tc, hho_zrpc_hash_post);
  tcase_add_test(tc, hho_zrpc_mins_negt);
  tcase_add_test(tc, hho_zrpc_hash_negt);
  tcase_add_test(tc, hho_width_prec_mins_post);
  tcase_add_test(tc, hho_width_prec_hash_post);
  tcase_add_test(tc, hho_width_prec_mins_negt);
  tcase_add_test(tc, hho_width_prec_hash_negt);
  tcase_add_test(tc, hho_dynamic_width_post);
  tcase_add_test(tc, hho_dynamic_prec_post);
  tcase_add_test(tc, hho_dynamic_width_prec_post);
  tcase_add_test(tc, hho_dynamic_width_negt);
  tcase_add_test(tc, hho_dynamic_prec_negt);
  tcase_add_test(tc, hho_dynamic_width_prec_negt);
  tcase_add_test(tc, hhu_mins_post);
  tcase_add_test(tc, hhu_fzer_post);
  tcase_add_test(tc, hhu_mins_negt);
  tcase_add_test(tc, hhu_fzer_negt);
  tcase_add_test(tc, hhu_width_post);
  tcase_add_test(tc, hhu_zrpc_post);
  tcase_add_test(tc, hhu_prec_post);
  tcase_add_test(tc, hhu_width_prec_post);
  tcase_add_test(tc, hhu_width_negt);
  tcase_add_test(tc, hhu_zrpc_negt);
  tcase_add_test(tc, hhu_prec_negt);
  tcase_add_test(tc, hhu_width_prec_negt);
  tcase_add_test(tc, hhu_width_mins_post);
  tcase_add_test(tc, hhu_width_fzer_post);
  tcase_add_test(tc, hhu_width_mins_negt);
  tcase_add_test(tc, hhu_width_fzer_negt);
  tcase_add_test(tc, hhu_prec_mins_post);
  tcase_add_test(tc, hhu_prec_mins_negt);
  tcase_add_test(tc, hhu_zrpc_mins_post);
  tcase_add_test(tc, hhu_zrpc_mins_negt);
  tcase_add_test(tc, hhu_width_prec_mins_post);
  tcase_add_test(tc, hhu_width_prec_mins_negt);
  tcase_add_test(tc, hhu_dynamic_width_post);
  tcase_add_test(tc, hhu_dynamic_prec_post);
  tcase_add_test(tc, hhu_dynamic_width_prec_post);
  tcase_add_test(tc, hhu_dynamic_width_negt);
  tcase_add_test(tc, hhu_dynamic_prec_negt);
  tcase_add_test(tc, hhu_dynamic_width_prec_negt);
  tcase_add_test(tc, hhx_mins_post);
  tcase_add_test(tc, hhx_hash_post);
  tcase_add_test(tc, hhx_fzer_post);
  tcase_add_test(tc, hhx_mins_negt);
  tcase_add_test(tc, hhx_hash_negt);
  tcase_add_test(tc, hhx_fzer_negt);
  tcase_add_test(tc, hhx_width_post);
  tcase_add_test(tc, hhx_zrpc_post);
  tcase_add_test(tc, hhx_prec_post);
  tcase_add_test(tc, hhx_width_prec_post);
  tcase_add_test(tc, hhx_width_negt);
  tcase_add_test(tc, hhx_zrpc_negt);
  tcase_add_test(tc, hhx_prec_negt);
  tcase_add_test(tc, hhx_width_prec_negt);
  tcase_add_test(tc, hhx_width_mins_post);
  tcase_add_test(tc, hhx_width_hash_post);
  tcase_add_test(tc, hhx_width_fzer_post);
  tcase_add_test(tc, hhx_width_mins_negt);
  tcase_add_test(tc, hhx_width_hash_negt);
  tcase_add_test(tc, hhx_width_fzer_negt);
  tcase_add_test(tc, hhx_zrwth_hash_post);
  tcase_add_test(tc, hhx_zrwth_hash_negt);
  tcase_add_test(tc, hhx_prec_mins_post);
  tcase_add_test(tc, hhx_prec_hash_post);
  tcase_add_test(tc, hhx_prec_mins_negt);
  tcase_add_test(tc, hhx_prec_hash_negt);
  tcase_add_test(tc, hhx_zrpc_mins_post);
  tcase_add_test(tc, hhx_zrpc_hash_post);
  tcase_add_test(tc, hhx_zrpc_mins_negt);
  tcase_add_test(tc, hhx_zrpc_hash_negt);
  tcase_add_test(tc, hhx_width_prec_mins_post);
  tcase_add_test(tc, hhx_width_prec_hash_post);
  tcase_add_test(tc, hhx_width_prec_mins_negt);
  tcase_add_test(tc, hhx_width_prec_hash_negt);
  tcase_add_test(tc, hhx_dynamic_width_post);
  tcase_add_test(tc, hhx_dynamic_prec_post);
  tcase_add_test(tc, hhx_dynamic_width_prec_post);
  tcase_add_test(tc, hhx_dynamic_width_negt);
  tcase_add_test(tc, hhx_dynamic_prec_negt);
  tcase_add_test(tc, hhx_dynamic_width_prec_negt);
  tcase_add_test(tc, hhX_mins_post);
  tcase_add_test(tc, hhX_hash_post);
  tcase_add_test(tc, hhX_fzer_post);
  tcase_add_test(tc, hhX_mins_negt);
  tcase_add_test(tc, hhX_hash_negt);
  tcase_add_test(tc, hhX_fzer_negt);
  tcase_add_test(tc, hhX_width_post);
  tcase_add_test(tc, hhX_zrpc_post);
  tcase_add_test(tc, hhX_prec_post);
  tcase_add_test(tc, hhX_width_prec_post);
  tcase_add_test(tc, hhX_width_negt);
  tcase_add_test(tc, hhX_zrpc_negt);
  tcase_add_test(tc, hhX_prec_negt);
  tcase_add_test(tc, hhX_width_prec_negt);
  tcase_add_test(tc, hhX_width_mins_post);
  tcase_add_test(tc, hhX_width_hash_post);
  tcase_add_test(tc, hhX_width_fzer_post);
  tcase_add_test(tc, hhX_width_mins_negt);
  tcase_add_test(tc, hhX_width_hash_negt);
  tcase_add_test(tc, hhX_width_fzer_negt);
  tcase_add_test(tc, hhX_zrwth_hash_post);
  tcase_add_test(tc, hhX_zrwth_hash_negt);
  tcase_add_test(tc, hhX_prec_mins_post);
  tcase_add_test(tc, hhX_prec_hash_post);
  tcase_add_test(tc, hhX_prec_mins_negt);
  tcase_add_test(tc, hhX_prec_hash_negt);
  tcase_add_test(tc, hhX_zrpc_mins_post);
  tcase_add_test(tc, hhX_zrpc_hash_post);
  tcase_add_test(tc, hhX_zrpc_mins_negt);
  tcase_add_test(tc, hhX_zrpc_hash_negt);
  tcase_add_test(tc, hhX_width_prec_mins_post);
  tcase_add_test(tc, hhX_width_prec_hash_post);
  tcase_add_test(tc, hhX_width_prec_mins_negt);
  tcase_add_test(tc, hhX_width_prec_hash_negt);
  tcase_add_test(tc, hhX_dynamic_width_post);
  tcase_add_test(tc, hhX_dynamic_prec_post);
  tcase_add_test(tc, hhX_dynamic_width_prec_post);
  tcase_add_test(tc, hhX_dynamic_width_negt);
  tcase_add_test(tc, hhX_dynamic_prec_negt);
  tcase_add_test(tc, hhX_dynamic_width_prec_negt);
  tcase_add_test(tc, ld_mins_post);
  tcase_add_test(tc, ld_plus_post);
  tcase_add_test(tc, ld_spac_post);
  tcase_add_test(tc, ld_fzer_post);
  tcase_add_test(tc, ld_mins_negt);
  tcase_add_test(tc, ld_plus_negt);
  tcase_add_test(tc, ld_spac_negt);
  tcase_add_test(tc, ld_fzer_negt);
  tcase_add_test(tc, ld_width_post);
  tcase_add_test(tc, ld_zrpc_post);
  tcase_add_test(tc, ld_prec_post);
  tcase_add_test(tc, ld_width_prec_post);
  tcase_add_test(tc, ld_width_negt);
  tcase_add_test(tc, ld_zrpc_negt);
  tcase_add_test(tc, ld_prec_negt);
  tcase_add_test(tc, ld_width_prec_negt);
  tcase_add_test(tc, ld_width_mins_post);
  tcase_add_test(tc, ld_width_plus_post);
  tcase_add_test(tc, ld_width_spac_post);
  tcase_add_test(tc, ld_width_fzer_post);
  tcase_add_test(tc, ld_width_mins_negt);
  tcase_add_test(tc, ld_width_plus_negt);
  tcase_add_test(tc, ld_width_spac_negt);
  tcase_add_test(tc, ld_width_fzer_negt);
  tcase_add_test(tc, ld_zrwth_plus_post);
  tcase_add_test(tc, ld_zrwth_spac_post);
  tcase_add_test(tc, ld_zrwth_plus_negt);
  tcase_add_test(tc, ld_zrwth_spac_negt);
  tcase_add_test(tc, ld_prec_mins_post);
  tcase_add_test(tc, ld_prec_plus_post);
  tcase_add_test(tc, ld_prec_spac_post);
  tcase_add_test(tc, ld_prec_mins_negt);
  tcase_add_test(tc, ld_prec_plus_negt);
  tcase_add_test(tc, ld_prec_spac_negt);
  tcase_add_test(tc, ld_zrpc_mins_post);
  tcase_add_test(tc, ld_zrpc_plus_post);
  tcase_add_test(tc, ld_zrpc_spac_post);
  tcase_add_test(tc, ld_zrpc_mins_negt);
  tcase_add_test(tc, ld_zrpc_plus_negt);
  tcase_add_test(tc, ld_zrpc_spac_negt);
  tcase_add_test(tc, ld_width_prec_mins_post);
  tcase_add_test(tc, ld_width_prec_plus_post);
  tcase_add_test(tc, ld_width_prec_spac_post);
  tcase_add_test(tc, ld_width_prec_mins_negt);
  tcase_add_test(tc, ld_width_prec_plus_negt);
  tcase_add_test(tc, ld_width_prec_spac_negt);
  tcase_add_test(tc, ld_dynamic_width_post);
  tcase_add_test(tc, ld_dynamic_prec_post);
  tcase_add_test(tc, ld_dynamic_width_prec_post);
  tcase_add_test(tc, ld_dynamic_width_negt);
  tcase_add_test(tc, ld_dynamic_prec_negt);
  tcase_add_test(tc, ld_dynamic_width_prec_negt);
  tcase_add_test(tc, li_mins_post);
  tcase_add_test(tc, li_plus_post);
  tcase_add_test(tc, li_spac_post);
  tcase_add_test(tc, li_fzer_post);
  tcase_add_test(tc, li_mins_negt);
  tcase_add_test(tc, li_plus_negt);
  tcase_add_test(tc, li_spac_negt);
  tcase_add_test(tc, li_fzer_negt);
  tcase_add_test(tc, li_width_post);
  tcase_add_test(tc, li_zrpc_post);
  tcase_add_test(tc, li_prec_post);
  tcase_add_test(tc, li_width_prec_post);
  tcase_add_test(tc, li_width_negt);
  tcase_add_test(tc, li_zrpc_negt);
  tcase_add_test(tc, li_prec_negt);
  tcase_add_test(tc, li_width_prec_negt);
  tcase_add_test(tc, li_width_mins_post);
  tcase_add_test(tc, li_width_plus_post);
  tcase_add_test(tc, li_width_spac_post);
  tcase_add_test(tc, li_width_fzer_post);
  tcase_add_test(tc, li_width_mins_negt);
  tcase_add_test(tc, li_width_plus_negt);
  tcase_add_test(tc, li_width_spac_negt);
  tcase_add_test(tc, li_width_fzer_negt);
  tcase_add_test(tc, li_zrwth_plus_post);
  tcase_add_test(tc, li_zrwth_spac_post);
  tcase_add_test(tc, li_zrwth_plus_negt);
  tcase_add_test(tc, li_zrwth_spac_negt);
  tcase_add_test(tc, li_prec_mins_post);
  tcase_add_test(tc, li_prec_plus_post);
  tcase_add_test(tc, li_prec_spac_post);
  tcase_add_test(tc, li_prec_mins_negt);
  tcase_add_test(tc, li_prec_plus_negt);
  tcase_add_test(tc, li_prec_spac_negt);
  tcase_add_test(tc, li_zrpc_mins_post);
  tcase_add_test(tc, li_zrpc_plus_post);
  tcase_add_test(tc, li_zrpc_spac_post);
  tcase_add_test(tc, li_zrpc_mins_negt);
  tcase_add_test(tc, li_zrpc_plus_negt);
  tcase_add_test(tc, li_zrpc_spac_negt);
  tcase_add_test(tc, li_width_prec_mins_post);
  tcase_add_test(tc, li_width_prec_plus_post);
  tcase_add_test(tc, li_width_prec_spac_post);
  tcase_add_test(tc, li_width_prec_mins_negt);
  tcase_add_test(tc, li_width_prec_plus_negt);
  tcase_add_test(tc, li_width_prec_spac_negt);
  tcase_add_test(tc, li_dynamic_width_post);
  tcase_add_test(tc, li_dynamic_prec_post);
  tcase_add_test(tc, li_dynamic_width_prec_post);
  tcase_add_test(tc, li_dynamic_width_negt);
  tcase_add_test(tc, li_dynamic_prec_negt);
  tcase_add_test(tc, li_dynamic_width_prec_negt);
  tcase_add_test(tc, lo_mins_post);
  tcase_add_test(tc, lo_hash_post);
  tcase_add_test(tc, lo_fzer_post);
  tcase_add_test(tc, lo_mins_negt);
  tcase_add_test(tc, lo_hash_negt);
  tcase_add_test(tc, lo_fzer_negt);
  tcase_add_test(tc, lo_width_post);
  tcase_add_test(tc, lo_zrpc_post);
  tcase_add_test(tc, lo_prec_post);
  tcase_add_test(tc, lo_width_prec_post);
  tcase_add_test(tc, lo_width_negt);
  tcase_add_test(tc, lo_zrpc_negt);
  tcase_add_test(tc, lo_prec_negt);
  tcase_add_test(tc, lo_width_prec_negt);
  tcase_add_test(tc, lo_width_mins_post);
  tcase_add_test(tc, lo_width_hash_post);
  tcase_add_test(tc, lo_width_fzer_post);
  tcase_add_test(tc, lo_width_mins_negt);
  tcase_add_test(tc, lo_width_hash_negt);
  tcase_add_test(tc, lo_width_fzer_negt);
  tcase_add_test(tc, lo_zrwth_hash_post);
  tcase_add_test(tc, lo_zrwth_hash_negt);
  tcase_add_test(tc, lo_prec_mins_post);
  tcase_add_test(tc, lo_prec_hash_post);
  tcase_add_test(tc, lo_prec_mins_negt);
  tcase_add_test(tc, lo_prec_hash_negt);
  tcase_add_test(tc, lo_zrpc_mins_post);
  tcase_add_test(tc, lo_zrpc_hash_post);
  tcase_add_test(tc, lo_zrpc_mins_negt);
  tcase_add_test(tc, lo_zrpc_hash_negt);
  tcase_add_test(tc, lo_width_prec_mins_post);
  tcase_add_test(tc, lo_width_prec_hash_post);
  tcase_add_test(tc, lo_width_prec_mins_negt);
  tcase_add_test(tc, lo_width_prec_hash_negt);
  tcase_add_test(tc, lo_dynamic_width_post);
  tcase_add_test(tc, lo_dynamic_prec_post);
  tcase_add_test(tc, lo_dynamic_width_prec_post);
  tcase_add_test(tc, lo_dynamic_width_negt);
  tcase_add_test(tc, lo_dynamic_prec_negt);
  tcase_add_test(tc, lo_dynamic_width_prec_negt);
  tcase_add_test(tc, lu_mins_post);
  tcase_add_test(tc, lu_fzer_post);
  tcase_add_test(tc, lu_mins_negt);
  tcase_add_test(tc, lu_fzer_negt);
  tcase_add_test(tc, lu_width_post);
  tcase_add_test(tc, lu_zrpc_post);
  tcase_add_test(tc, lu_prec_post);
  tcase_add_test(tc, lu_width_prec_post);
  tcase_add_test(tc, lu_width_negt);
  tcase_add_test(tc, lu_zrpc_negt);
  tcase_add_test(tc, lu_prec_negt);
  tcase_add_test(tc, lu_width_prec_negt);
  tcase_add_test(tc, lu_width_mins_post);
  tcase_add_test(tc, lu_width_fzer_post);
  tcase_add_test(tc, lu_width_mins_negt);
  tcase_add_test(tc, lu_width_fzer_negt);
  tcase_add_test(tc, lu_prec_mins_post);
  tcase_add_test(tc, lu_prec_mins_negt);
  tcase_add_test(tc, lu_zrpc_mins_post);
  tcase_add_test(tc, lu_zrpc_mins_negt);
  tcase_add_test(tc, lu_width_prec_mins_post);
  tcase_add_test(tc, lu_width_prec_mins_negt);
  tcase_add_test(tc, lu_dynamic_width_post);
  tcase_add_test(tc, lu_dynamic_prec_post);
  tcase_add_test(tc, lu_dynamic_width_prec_post);
  tcase_add_test(tc, lu_dynamic_width_negt);
  tcase_add_test(tc, lu_dynamic_prec_negt);
  tcase_add_test(tc, lu_dynamic_width_prec_negt);
  tcase_add_test(tc, lx_mins_post);
  tcase_add_test(tc, lx_hash_post);
  tcase_add_test(tc, lx_fzer_post);
  tcase_add_test(tc, lx_mins_negt);
  tcase_add_test(tc, lx_hash_negt);
  tcase_add_test(tc, lx_fzer_negt);
  tcase_add_test(tc, lx_width_post);
  tcase_add_test(tc, lx_zrpc_post);
  tcase_add_test(tc, lx_prec_post);
  tcase_add_test(tc, lx_width_prec_post);
  tcase_add_test(tc, lx_width_negt);
  tcase_add_test(tc, lx_zrpc_negt);
  tcase_add_test(tc, lx_prec_negt);
  tcase_add_test(tc, lx_width_prec_negt);
  tcase_add_test(tc, lx_width_mins_post);
  tcase_add_test(tc, lx_width_hash_post);
  tcase_add_test(tc, lx_width_fzer_post);
  tcase_add_test(tc, lx_width_mins_negt);
  tcase_add_test(tc, lx_width_hash_negt);
  tcase_add_test(tc, lx_width_fzer_negt);
  tcase_add_test(tc, lx_zrwth_hash_post);
  tcase_add_test(tc, lx_zrwth_hash_negt);
  tcase_add_test(tc, lx_prec_mins_post);
  tcase_add_test(tc, lx_prec_hash_post);
  tcase_add_test(tc, lx_prec_mins_negt);
  tcase_add_test(tc, lx_prec_hash_negt);
  tcase_add_test(tc, lx_zrpc_mins_post);
  tcase_add_test(tc, lx_zrpc_hash_post);
  tcase_add_test(tc, lx_zrpc_mins_negt);
  tcase_add_test(tc, lx_zrpc_hash_negt);
  tcase_add_test(tc, lx_width_prec_mins_post);
  tcase_add_test(tc, lx_width_prec_hash_post);
  tcase_add_test(tc, lx_width_prec_mins_negt);
  tcase_add_test(tc, lx_width_prec_hash_negt);
  tcase_add_test(tc, lx_dynamic_width_post);
  tcase_add_test(tc, lx_dynamic_prec_post);
  tcase_add_test(tc, lx_dynamic_width_prec_post);
  tcase_add_test(tc, lx_dynamic_width_negt);
  tcase_add_test(tc, lx_dynamic_prec_negt);
  tcase_add_test(tc, lx_dynamic_width_prec_negt);
  tcase_add_test(tc, lX_mins_post);
  tcase_add_test(tc, lX_hash_post);
  tcase_add_test(tc, lX_fzer_post);
  tcase_add_test(tc, lX_mins_negt);
  tcase_add_test(tc, lX_hash_negt);
  tcase_add_test(tc, lX_fzer_negt);
  tcase_add_test(tc, lX_width_post);
  tcase_add_test(tc, lX_zrpc_post);
  tcase_add_test(tc, lX_prec_post);
  tcase_add_test(tc, lX_width_prec_post);
  tcase_add_test(tc, lX_width_negt);
  tcase_add_test(tc, lX_zrpc_negt);
  tcase_add_test(tc, lX_prec_negt);
  tcase_add_test(tc, lX_width_prec_negt);
  tcase_add_test(tc, lX_width_mins_post);
  tcase_add_test(tc, lX_width_hash_post);
  tcase_add_test(tc, lX_width_fzer_post);
  tcase_add_test(tc, lX_width_mins_negt);
  tcase_add_test(tc, lX_width_hash_negt);
  tcase_add_test(tc, lX_width_fzer_negt);
  tcase_add_test(tc, lX_zrwth_hash_post);
  tcase_add_test(tc, lX_zrwth_hash_negt);
  tcase_add_test(tc, lX_prec_mins_post);
  tcase_add_test(tc, lX_prec_hash_post);
  tcase_add_test(tc, lX_prec_mins_negt);
  tcase_add_test(tc, lX_prec_hash_negt);
  tcase_add_test(tc, lX_zrpc_mins_post);
  tcase_add_test(tc, lX_zrpc_hash_post);
  tcase_add_test(tc, lX_zrpc_mins_negt);
  tcase_add_test(tc, lX_zrpc_hash_negt);
  tcase_add_test(tc, lX_width_prec_mins_post);
  tcase_add_test(tc, lX_width_prec_hash_post);
  tcase_add_test(tc, lX_width_prec_mins_negt);
  tcase_add_test(tc, lX_width_prec_hash_negt);
  tcase_add_test(tc, lX_dynamic_width_post);
  tcase_add_test(tc, lX_dynamic_prec_post);
  tcase_add_test(tc, lX_dynamic_width_prec_post);
  tcase_add_test(tc, lX_dynamic_width_negt);
  tcase_add_test(tc, lX_dynamic_prec_negt);
  tcase_add_test(tc, lX_dynamic_width_prec_negt);
  tcase_add_test(tc, lld_mins_post);
  tcase_add_test(tc, lld_plus_post);
  tcase_add_test(tc, lld_spac_post);
  tcase_add_test(tc, lld_fzer_post);
  tcase_add_test(tc, lld_mins_negt);
  tcase_add_test(tc, lld_plus_negt);
  tcase_add_test(tc, lld_spac_negt);
  tcase_add_test(tc, lld_fzer_negt);
  tcase_add_test(tc, lld_width_post);
  tcase_add_test(tc, lld_zrpc_post);
  tcase_add_test(tc, lld_prec_post);
  tcase_add_test(tc, lld_width_prec_post);
  tcase_add_test(tc, lld_width_negt);
  tcase_add_test(tc, lld_zrpc_negt);
  tcase_add_test(tc, lld_prec_negt);
  tcase_add_test(tc, lld_width_prec_negt);
  tcase_add_test(tc, lld_width_mins_post);
  tcase_add_test(tc, lld_width_plus_post);
  tcase_add_test(tc, lld_width_spac_post);
  tcase_add_test(tc, lld_width_fzer_post);
  tcase_add_test(tc, lld_width_mins_negt);
  tcase_add_test(tc, lld_width_plus_negt);
  tcase_add_test(tc, lld_width_spac_negt);
  tcase_add_test(tc, lld_width_fzer_negt);
  tcase_add_test(tc, lld_zrwth_plus_post);
  tcase_add_test(tc, lld_zrwth_spac_post);
  tcase_add_test(tc, lld_zrwth_plus_negt);
  tcase_add_test(tc, lld_zrwth_spac_negt);
  tcase_add_test(tc, lld_prec_mins_post);
  tcase_add_test(tc, lld_prec_plus_post);
  tcase_add_test(tc, lld_prec_spac_post);
  tcase_add_test(tc, lld_prec_mins_negt);
  tcase_add_test(tc, lld_prec_plus_negt);
  tcase_add_test(tc, lld_prec_spac_negt);
  tcase_add_test(tc, lld_zrpc_mins_post);
  tcase_add_test(tc, lld_zrpc_plus_post);
  tcase_add_test(tc, lld_zrpc_spac_post);
  tcase_add_test(tc, lld_zrpc_mins_negt);
  tcase_add_test(tc, lld_zrpc_plus_negt);
  tcase_add_test(tc, lld_zrpc_spac_negt);
  tcase_add_test(tc, lld_width_prec_mins_post);
  tcase_add_test(tc, lld_width_prec_plus_post);
  tcase_add_test(tc, lld_width_prec_spac_post);
  tcase_add_test(tc, lld_width_prec_mins_negt);
  tcase_add_test(tc, lld_width_prec_plus_negt);
  tcase_add_test(tc, lld_width_prec_spac_negt);
  tcase_add_test(tc, lld_dynamic_width_post);
  tcase_add_test(tc, lld_dynamic_prec_post);
  tcase_add_test(tc, lld_dynamic_width_prec_post);
  tcase_add_test(tc, lld_dynamic_width_negt);
  tcase_add_test(tc, lld_dynamic_prec_negt);
  tcase_add_test(tc, lld_dynamic_width_prec_negt);
  tcase_add_test(tc, lli_mins_post);
  tcase_add_test(tc, lli_plus_post);
  tcase_add_test(tc, lli_spac_post);
  tcase_add_test(tc, lli_fzer_post);
  tcase_add_test(tc, lli_mins_negt);
  tcase_add_test(tc, lli_plus_negt);
  tcase_add_test(tc, lli_spac_negt);
  tcase_add_test(tc, lli_fzer_negt);
  tcase_add_test(tc, lli_width_post);
  tcase_add_test(tc, lli_zrpc_post);
  tcase_add_test(tc, lli_prec_post);
  tcase_add_test(tc, lli_width_prec_post);
  tcase_add_test(tc, lli_width_negt);
  tcase_add_test(tc, lli_zrpc_negt);
  tcase_add_test(tc, lli_prec_negt);
  tcase_add_test(tc, lli_width_prec_negt);
  tcase_add_test(tc, lli_width_mins_post);
  tcase_add_test(tc, lli_width_plus_post);
  tcase_add_test(tc, lli_width_spac_post);
  tcase_add_test(tc, lli_width_fzer_post);
  tcase_add_test(tc, lli_width_mins_negt);
  tcase_add_test(tc, lli_width_plus_negt);
  tcase_add_test(tc, lli_width_spac_negt);
  tcase_add_test(tc, lli_width_fzer_negt);
  tcase_add_test(tc, lli_zrwth_plus_post);
  tcase_add_test(tc, lli_zrwth_spac_post);
  tcase_add_test(tc, lli_zrwth_plus_negt);
  tcase_add_test(tc, lli_zrwth_spac_negt);
  tcase_add_test(tc, lli_prec_mins_post);
  tcase_add_test(tc, lli_prec_plus_post);
  tcase_add_test(tc, lli_prec_spac_post);
  tcase_add_test(tc, lli_prec_mins_negt);
  tcase_add_test(tc, lli_prec_plus_negt);
  tcase_add_test(tc, lli_prec_spac_negt);
  tcase_add_test(tc, lli_zrpc_mins_post);
  tcase_add_test(tc, lli_zrpc_plus_post);
  tcase_add_test(tc, lli_zrpc_spac_post);
  tcase_add_test(tc, lli_zrpc_mins_negt);
  tcase_add_test(tc, lli_zrpc_plus_negt);
  tcase_add_test(tc, lli_zrpc_spac_negt);
  tcase_add_test(tc, lli_width_prec_mins_post);
  tcase_add_test(tc, lli_width_prec_plus_post);
  tcase_add_test(tc, lli_width_prec_spac_post);
  tcase_add_test(tc, lli_width_prec_mins_negt);
  tcase_add_test(tc, lli_width_prec_plus_negt);
  tcase_add_test(tc, lli_width_prec_spac_negt);
  tcase_add_test(tc, lli_dynamic_width_post);
  tcase_add_test(tc, lli_dynamic_prec_post);
  tcase_add_test(tc, lli_dynamic_width_prec_post);
  tcase_add_test(tc, lli_dynamic_width_negt);
  tcase_add_test(tc, lli_dynamic_prec_negt);
  tcase_add_test(tc, lli_dynamic_width_prec_negt);
  tcase_add_test(tc, llo_mins_post);
  tcase_add_test(tc, llo_hash_post);
  tcase_add_test(tc, llo_fzer_post);
  tcase_add_test(tc, llo_mins_negt);
  tcase_add_test(tc, llo_hash_negt);
  tcase_add_test(tc, llo_fzer_negt);
  tcase_add_test(tc, llo_width_post);
  tcase_add_test(tc, llo_zrpc_post);
  tcase_add_test(tc, llo_prec_post);
  tcase_add_test(tc, llo_width_prec_post);
  tcase_add_test(tc, llo_width_negt);
  tcase_add_test(tc, llo_zrpc_negt);
  tcase_add_test(tc, llo_prec_negt);
  tcase_add_test(tc, llo_width_prec_negt);
  tcase_add_test(tc, llo_width_mins_post);
  tcase_add_test(tc, llo_width_hash_post);
  tcase_add_test(tc, llo_width_fzer_post);
  tcase_add_test(tc, llo_width_mins_negt);
  tcase_add_test(tc, llo_width_hash_negt);
  tcase_add_test(tc, llo_width_fzer_negt);
  tcase_add_test(tc, llo_zrwth_hash_post);
  tcase_add_test(tc, llo_zrwth_hash_negt);
  tcase_add_test(tc, llo_prec_mins_post);
  tcase_add_test(tc, llo_prec_hash_post);
  tcase_add_test(tc, llo_prec_mins_negt);
  tcase_add_test(tc, llo_prec_hash_negt);
  tcase_add_test(tc, llo_zrpc_mins_post);
  tcase_add_test(tc, llo_zrpc_hash_post);
  tcase_add_test(tc, llo_zrpc_mins_negt);
  tcase_add_test(tc, llo_zrpc_hash_negt);
  tcase_add_test(tc, llo_width_prec_mins_post);
  tcase_add_test(tc, llo_width_prec_hash_post);
  tcase_add_test(tc, llo_width_prec_mins_negt);
  tcase_add_test(tc, llo_width_prec_hash_negt);
  tcase_add_test(tc, llo_dynamic_width_post);
  tcase_add_test(tc, llo_dynamic_prec_post);
  tcase_add_test(tc, llo_dynamic_width_prec_post);
  tcase_add_test(tc, llo_dynamic_width_negt);
  tcase_add_test(tc, llo_dynamic_prec_negt);
  tcase_add_test(tc, llo_dynamic_width_prec_negt);
  tcase_add_test(tc, llu_mins_post);
  tcase_add_test(tc, llu_fzer_post);
  tcase_add_test(tc, llu_mins_negt);
  tcase_add_test(tc, llu_fzer_negt);
  tcase_add_test(tc, llu_width_post);
  tcase_add_test(tc, llu_zrpc_post);
  tcase_add_test(tc, llu_prec_post);
  tcase_add_test(tc, llu_width_prec_post);
  tcase_add_test(tc, llu_width_negt);
  tcase_add_test(tc, llu_zrpc_negt);
  tcase_add_test(tc, llu_prec_negt);
  tcase_add_test(tc, llu_width_prec_negt);
  tcase_add_test(tc, llu_width_mins_post);
  tcase_add_test(tc, llu_width_fzer_post);
  tcase_add_test(tc, llu_width_mins_negt);
  tcase_add_test(tc, llu_width_fzer_negt);
  tcase_add_test(tc, llu_prec_mins_post);
  tcase_add_test(tc, llu_prec_mins_negt);
  tcase_add_test(tc, llu_zrpc_mins_post);
  tcase_add_test(tc, llu_zrpc_mins_negt);
  tcase_add_test(tc, llu_width_prec_mins_post);
  tcase_add_test(tc, llu_width_prec_mins_negt);
  tcase_add_test(tc, llu_dynamic_width_post);
  tcase_add_test(tc, llu_dynamic_prec_post);
  tcase_add_test(tc, llu_dynamic_width_prec_post);
  tcase_add_test(tc, llu_dynamic_width_negt);
  tcase_add_test(tc, llu_dynamic_prec_negt);
  tcase_add_test(tc, llu_dynamic_width_prec_negt);
  tcase_add_test(tc, llx_mins_post);
  tcase_add_test(tc, llx_hash_post);
  tcase_add_test(tc, llx_fzer_post);
  tcase_add_test(tc, llx_mins_negt);
  tcase_add_test(tc, llx_hash_negt);
  tcase_add_test(tc, llx_fzer_negt);
  tcase_add_test(tc, llx_width_post);
  tcase_add_test(tc, llx_zrpc_post);
  tcase_add_test(tc, llx_prec_post);
  tcase_add_test(tc, llx_width_prec_post);
  tcase_add_test(tc, llx_width_negt);
  tcase_add_test(tc, llx_zrpc_negt);
  tcase_add_test(tc, llx_prec_negt);
  tcase_add_test(tc, llx_width_prec_negt);
  tcase_add_test(tc, llx_width_mins_post);
  tcase_add_test(tc, llx_width_hash_post);
  tcase_add_test(tc, llx_width_fzer_post);
  tcase_add_test(tc, llx_width_mins_negt);
  tcase_add_test(tc, llx_width_hash_negt);
  tcase_add_test(tc, llx_width_fzer_negt);
  tcase_add_test(tc, llx_zrwth_hash_post);
  tcase_add_test(tc, llx_zrwth_hash_negt);
  tcase_add_test(tc, llx_prec_mins_post);
  tcase_add_test(tc, llx_prec_hash_post);
  tcase_add_test(tc, llx_prec_mins_negt);
  tcase_add_test(tc, llx_prec_hash_negt);
  tcase_add_test(tc, llx_zrpc_mins_post);
  tcase_add_test(tc, llx_zrpc_hash_post);
  tcase_add_test(tc, llx_zrpc_mins_negt);
  tcase_add_test(tc, llx_zrpc_hash_negt);
  tcase_add_test(tc, llx_width_prec_mins_post);
  tcase_add_test(tc, llx_width_prec_hash_post);
  tcase_add_test(tc, llx_width_prec_mins_negt);
  tcase_add_test(tc, llx_width_prec_hash_negt);
  tcase_add_test(tc, llx_dynamic_width_post);
  tcase_add_test(tc, llx_dynamic_prec_post);
  tcase_add_test(tc, llx_dynamic_width_prec_post);
  tcase_add_test(tc, llx_dynamic_width_negt);
  tcase_add_test(tc, llx_dynamic_prec_negt);
  tcase_add_test(tc, llx_dynamic_width_prec_negt);
  tcase_add_test(tc, llX_mins_post);
  tcase_add_test(tc, llX_hash_post);
  tcase_add_test(tc, llX_fzer_post);
  tcase_add_test(tc, llX_mins_negt);
  tcase_add_test(tc, llX_hash_negt);
  tcase_add_test(tc, llX_fzer_negt);
  tcase_add_test(tc, llX_width_post);
  tcase_add_test(tc, llX_zrpc_post);
  tcase_add_test(tc, llX_prec_post);
  tcase_add_test(tc, llX_width_prec_post);
  tcase_add_test(tc, llX_width_negt);
  tcase_add_test(tc, llX_zrpc_negt);
  tcase_add_test(tc, llX_prec_negt);
  tcase_add_test(tc, llX_width_prec_negt);
  tcase_add_test(tc, llX_width_mins_post);
  tcase_add_test(tc, llX_width_hash_post);
  tcase_add_test(tc, llX_width_fzer_post);
  tcase_add_test(tc, llX_width_mins_negt);
  tcase_add_test(tc, llX_width_hash_negt);
  tcase_add_test(tc, llX_width_fzer_negt);
  tcase_add_test(tc, llX_zrwth_hash_post);
  tcase_add_test(tc, llX_zrwth_hash_negt);
  tcase_add_test(tc, llX_prec_mins_post);
  tcase_add_test(tc, llX_prec_hash_post);
  tcase_add_test(tc, llX_prec_mins_negt);
  tcase_add_test(tc, llX_prec_hash_negt);
  tcase_add_test(tc, llX_zrpc_mins_post);
  tcase_add_test(tc, llX_zrpc_hash_post);
  tcase_add_test(tc, llX_zrpc_mins_negt);
  tcase_add_test(tc, llX_zrpc_hash_negt);
  tcase_add_test(tc, llX_width_prec_mins_post);
  tcase_add_test(tc, llX_width_prec_hash_post);
  tcase_add_test(tc, llX_width_prec_mins_negt);
  tcase_add_test(tc, llX_width_prec_hash_negt);
  tcase_add_test(tc, llX_dynamic_width_post);
  tcase_add_test(tc, llX_dynamic_prec_post);
  tcase_add_test(tc, llX_dynamic_width_prec_post);
  tcase_add_test(tc, llX_dynamic_width_negt);
  tcase_add_test(tc, llX_dynamic_prec_negt);
  tcase_add_test(tc, llX_dynamic_width_prec_negt);
  tcase_add_test(tc, e_mins_nan);
  tcase_add_test(tc, e_plus_nan);
  tcase_add_test(tc, e_spac_nan);
  tcase_add_test(tc, e_hash_nan);
  tcase_add_test(tc, e_fzer_nan);
  tcase_add_test(tc, e_mins_inf);
  tcase_add_test(tc, e_plus_inf);
  tcase_add_test(tc, e_spac_inf);
  tcase_add_test(tc, e_hash_inf);
  tcase_add_test(tc, e_fzer_inf);
  tcase_add_test(tc, e_mins_ng_inf);
  tcase_add_test(tc, e_plus_ng_inf);
  tcase_add_test(tc, e_spac_ng_inf);
  tcase_add_test(tc, e_hash_ng_inf);
  tcase_add_test(tc, e_fzer_ng_inf);
  tcase_add_test(tc, e_width_nan);
  tcase_add_test(tc, e_zrpc_nan);
  tcase_add_test(tc, e_prec_nan);
  tcase_add_test(tc, e_width_inf);
  tcase_add_test(tc, e_zrpc_inf);
  tcase_add_test(tc, e_prec_inf);
  tcase_add_test(tc, e_width_ng_inf);
  tcase_add_test(tc, e_zrpc_ng_inf);
  tcase_add_test(tc, e_prec_ng_inf);
  tcase_add_test(tc, e_width_prec_nan);
  tcase_add_test(tc, e_width_prec_inf);
  tcase_add_test(tc, e_width_prec_ng_inf);
  tcase_add_test(tc, e_width_mins_nan);
  tcase_add_test(tc, e_width_plus_nan);
  tcase_add_test(tc, e_width_spac_nan);
  tcase_add_test(tc, e_width_hash_nan);
  tcase_add_test(tc, e_width_fzer_nan);
  tcase_add_test(tc, e_width_mins_inf);
  tcase_add_test(tc, e_width_plus_inf);
  tcase_add_test(tc, e_width_spac_inf);
  tcase_add_test(tc, e_width_hash_inf);
  tcase_add_test(tc, e_width_fzer_inf);
  tcase_add_test(tc, e_width_mins_ng_inf);
  tcase_add_test(tc, e_width_plus_ng_inf);
  tcase_add_test(tc, e_width_spac_ng_inf);
  tcase_add_test(tc, e_width_hash_ng_inf);
  tcase_add_test(tc, e_width_fzer_ng_inf);
  tcase_add_test(tc, e_zrwth_plus_nan);
  tcase_add_test(tc, e_zrwth_spac_nan);
  tcase_add_test(tc, e_zrwth_hash_nan);
  tcase_add_test(tc, e_zrwth_plus_inf);
  tcase_add_test(tc, e_zrwth_spac_inf);
  tcase_add_test(tc, e_zrwth_hash_inf);
  tcase_add_test(tc, e_zrwth_plus_ng_inf);
  tcase_add_test(tc, e_zrwth_spac_ng_inf);
  tcase_add_test(tc, e_zrwth_hash_ng_inf);
  tcase_add_test(tc, e_prec_mins_nan);
  tcase_add_test(tc, e_prec_plus_nan);
  tcase_add_test(tc, e_prec_spac_nan);
  tcase_add_test(tc, e_prec_hash_nan);
  tcase_add_test(tc, e_prec_fzer_nan);
  tcase_add_test(tc, e_prec_mins_inf);
  tcase_add_test(tc, e_prec_plus_inf);
  tcase_add_test(tc, e_prec_spac_inf);
  tcase_add_test(tc, e_prec_hash_inf);
  tcase_add_test(tc, e_prec_fzer_inf);
  tcase_add_test(tc, e_prec_mins_ng_inf);
  tcase_add_test(tc, e_prec_plus_ng_inf);
  tcase_add_test(tc, e_prec_spac_ng_inf);
  tcase_add_test(tc, e_prec_hash_ng_inf);
  tcase_add_test(tc, e_prec_fzer_ng_inf);
  tcase_add_test(tc, e_zrpc_mins_nan);
  tcase_add_test(tc, e_zrpc_plus_nan);
  tcase_add_test(tc, e_zrpc_spac_nan);
  tcase_add_test(tc, e_zrpc_hash_nan);
  tcase_add_test(tc, e_zrpc_fzer_nan);
  tcase_add_test(tc, e_zrpc_mins_inf);
  tcase_add_test(tc, e_zrpc_plus_inf);
  tcase_add_test(tc, e_zrpc_spac_inf);
  tcase_add_test(tc, e_zrpc_hash_inf);
  tcase_add_test(tc, e_zrpc_fzer_inf);
  tcase_add_test(tc, e_zrpc_mins_ng_inf);
  tcase_add_test(tc, e_zrpc_plus_ng_inf);
  tcase_add_test(tc, e_zrpc_spac_ng_inf);
  tcase_add_test(tc, e_zrpc_hash_ng_inf);
  tcase_add_test(tc, e_zrpc_fzer_ng_inf);
  tcase_add_test(tc, e_width_prec_mins_nan);
  tcase_add_test(tc, e_width_prec_plus_nan);
  tcase_add_test(tc, e_width_prec_spac_nan);
  tcase_add_test(tc, e_width_prec_hash_nan);
  tcase_add_test(tc, e_width_prec_fzer_nan);
  tcase_add_test(tc, e_width_prec_mins_inf);
  tcase_add_test(tc, e_width_prec_plus_inf);
  tcase_add_test(tc, e_width_prec_spac_inf);
  tcase_add_test(tc, e_width_prec_hash_inf);
  tcase_add_test(tc, e_width_prec_fzer_inf);
  tcase_add_test(tc, e_width_prec_mins_ng_inf);
  tcase_add_test(tc, e_width_prec_plus_ng_inf);
  tcase_add_test(tc, e_width_prec_spac_ng_inf);
  tcase_add_test(tc, e_width_prec_hash_ng_inf);
  tcase_add_test(tc, e_width_prec_fzer_ng_inf);
  tcase_add_test(tc, e_zrwth_zrpc_plus_nan);
  tcase_add_test(tc, e_zrwth_zrpc_spac_nan);
  tcase_add_test(tc, e_zrwth_zrpc_hash_nan);
  tcase_add_test(tc, e_zrwth_zrpc_plus_inf);
  tcase_add_test(tc, e_zrwth_zrpc_spac_inf);
  tcase_add_test(tc, e_zrwth_zrpc_hash_inf);
  tcase_add_test(tc, e_zrwth_zrpc_plus_ng_inf);
  tcase_add_test(tc, e_zrwth_zrpc_spac_ng_inf);
  tcase_add_test(tc, e_zrwth_zrpc_hash_ng_inf);
  tcase_add_test(tc, e_dynamic_prec_nan);
  tcase_add_test(tc, e_dynamic_prec_inf);
  tcase_add_test(tc, e_dynamic_prec_ng_inf);
  tcase_add_test(tc, e_dynamic_width_nan);
  tcase_add_test(tc, e_dynamic_width_inf);
  tcase_add_test(tc, e_dynamic_width_ng_inf);
  tcase_add_test(tc, e_dynamic_width_prec_nan);
  tcase_add_test(tc, e_dynamic_width_prec_inf);
  tcase_add_test(tc, e_dynamic_width_prec_ng_inf);
  tcase_add_test(tc, E_mins_nan);
  tcase_add_test(tc, E_plus_nan);
  tcase_add_test(tc, E_spac_nan);
  tcase_add_test(tc, E_hash_nan);
  tcase_add_test(tc, E_fzer_nan);
  tcase_add_test(tc, E_mins_inf);
  tcase_add_test(tc, E_plus_inf);
  tcase_add_test(tc, E_spac_inf);
  tcase_add_test(tc, E_hash_inf);
  tcase_add_test(tc, E_fzer_inf);
  tcase_add_test(tc, E_mins_ng_inf);
  tcase_add_test(tc, E_plus_ng_inf);
  tcase_add_test(tc, E_spac_ng_inf);
  tcase_add_test(tc, E_hash_ng_inf);
  tcase_add_test(tc, E_fzer_ng_inf);
  tcase_add_test(tc, E_width_nan);
  tcase_add_test(tc, E_zrpc_nan);
  tcase_add_test(tc, E_prec_nan);
  tcase_add_test(tc, E_width_inf);
  tcase_add_test(tc, E_zrpc_inf);
  tcase_add_test(tc, E_prec_inf);
  tcase_add_test(tc, E_width_ng_inf);
  tcase_add_test(tc, E_zrpc_ng_inf);
  tcase_add_test(tc, E_prec_ng_inf);
  tcase_add_test(tc, E_width_prec_nan);
  tcase_add_test(tc, E_width_prec_inf);
  tcase_add_test(tc, E_width_prec_ng_inf);
  tcase_add_test(tc, E_width_mins_nan);
  tcase_add_test(tc, E_width_plus_nan);
  tcase_add_test(tc, E_width_spac_nan);
  tcase_add_test(tc, E_width_hash_nan);
  tcase_add_test(tc, E_width_fzer_nan);
  tcase_add_test(tc, E_width_mins_inf);
  tcase_add_test(tc, E_width_plus_inf);
  tcase_add_test(tc, E_width_spac_inf);
  tcase_add_test(tc, E_width_hash_inf);
  tcase_add_test(tc, E_width_fzer_inf);
  tcase_add_test(tc, E_width_mins_ng_inf);
  tcase_add_test(tc, E_width_plus_ng_inf);
  tcase_add_test(tc, E_width_spac_ng_inf);
  tcase_add_test(tc, E_width_hash_ng_inf);
  tcase_add_test(tc, E_width_fzer_ng_inf);
  tcase_add_test(tc, E_zrwth_plus_nan);
  tcase_add_test(tc, E_zrwth_spac_nan);
  tcase_add_test(tc, E_zrwth_hash_nan);
  tcase_add_test(tc, E_zrwth_plus_inf);
  tcase_add_test(tc, E_zrwth_spac_inf);
  tcase_add_test(tc, E_zrwth_hash_inf);
  tcase_add_test(tc, E_zrwth_plus_ng_inf);
  tcase_add_test(tc, E_zrwth_spac_ng_inf);
  tcase_add_test(tc, E_zrwth_hash_ng_inf);
  tcase_add_test(tc, E_prec_mins_nan);
  tcase_add_test(tc, E_prec_plus_nan);
  tcase_add_test(tc, E_prec_spac_nan);
  tcase_add_test(tc, E_prec_hash_nan);
  tcase_add_test(tc, E_prec_fzer_nan);
  tcase_add_test(tc, E_prec_mins_inf);
  tcase_add_test(tc, E_prec_plus_inf);
  tcase_add_test(tc, E_prec_spac_inf);
  tcase_add_test(tc, E_prec_hash_inf);
  tcase_add_test(tc, E_prec_fzer_inf);
  tcase_add_test(tc, E_prec_mins_ng_inf);
  tcase_add_test(tc, E_prec_plus_ng_inf);
  tcase_add_test(tc, E_prec_spac_ng_inf);
  tcase_add_test(tc, E_prec_hash_ng_inf);
  tcase_add_test(tc, E_prec_fzer_ng_inf);
  tcase_add_test(tc, E_zrpc_mins_nan);
  tcase_add_test(tc, E_zrpc_plus_nan);
  tcase_add_test(tc, E_zrpc_spac_nan);
  tcase_add_test(tc, E_zrpc_hash_nan);
  tcase_add_test(tc, E_zrpc_fzer_nan);
  tcase_add_test(tc, E_zrpc_mins_inf);
  tcase_add_test(tc, E_zrpc_plus_inf);
  tcase_add_test(tc, E_zrpc_spac_inf);
  tcase_add_test(tc, E_zrpc_hash_inf);
  tcase_add_test(tc, E_zrpc_fzer_inf);
  tcase_add_test(tc, E_zrpc_mins_ng_inf);
  tcase_add_test(tc, E_zrpc_plus_ng_inf);
  tcase_add_test(tc, E_zrpc_spac_ng_inf);
  tcase_add_test(tc, E_zrpc_hash_ng_inf);
  tcase_add_test(tc, E_zrpc_fzer_ng_inf);
  tcase_add_test(tc, E_width_prec_mins_nan);
  tcase_add_test(tc, E_width_prec_plus_nan);
  tcase_add_test(tc, E_width_prec_spac_nan);
  tcase_add_test(tc, E_width_prec_hash_nan);
  tcase_add_test(tc, E_width_prec_fzer_nan);
  tcase_add_test(tc, E_width_prec_mins_inf);
  tcase_add_test(tc, E_width_prec_plus_inf);
  tcase_add_test(tc, E_width_prec_spac_inf);
  tcase_add_test(tc, E_width_prec_hash_inf);
  tcase_add_test(tc, E_width_prec_fzer_inf);
  tcase_add_test(tc, E_width_prec_mins_ng_inf);
  tcase_add_test(tc, E_width_prec_plus_ng_inf);
  tcase_add_test(tc, E_width_prec_spac_ng_inf);
  tcase_add_test(tc, E_width_prec_hash_ng_inf);
  tcase_add_test(tc, E_width_prec_fzer_ng_inf);
  tcase_add_test(tc, E_zrwth_zrpc_plus_nan);
  tcase_add_test(tc, E_zrwth_zrpc_spac_nan);
  tcase_add_test(tc, E_zrwth_zrpc_hash_nan);
  tcase_add_test(tc, E_zrwth_zrpc_plus_inf);
  tcase_add_test(tc, E_zrwth_zrpc_spac_inf);
  tcase_add_test(tc, E_zrwth_zrpc_hash_inf);
  tcase_add_test(tc, E_zrwth_zrpc_plus_ng_inf);
  tcase_add_test(tc, E_zrwth_zrpc_spac_ng_inf);
  tcase_add_test(tc, E_zrwth_zrpc_hash_ng_inf);
  tcase_add_test(tc, E_dynamic_prec_nan);
  tcase_add_test(tc, E_dynamic_prec_inf);
  tcase_add_test(tc, E_dynamic_prec_ng_inf);
  tcase_add_test(tc, E_dynamic_width_nan);
  tcase_add_test(tc, E_dynamic_width_inf);
  tcase_add_test(tc, E_dynamic_width_ng_inf);
  tcase_add_test(tc, E_dynamic_width_prec_nan);
  tcase_add_test(tc, E_dynamic_width_prec_inf);
  tcase_add_test(tc, E_dynamic_width_prec_ng_inf);
  tcase_add_test(tc, f_mins_nan);
  tcase_add_test(tc, f_plus_nan);
  tcase_add_test(tc, f_spac_nan);
  tcase_add_test(tc, f_hash_nan);
  tcase_add_test(tc, f_fzer_nan);
  tcase_add_test(tc, f_mins_inf);
  tcase_add_test(tc, f_plus_inf);
  tcase_add_test(tc, f_spac_inf);
  tcase_add_test(tc, f_hash_inf);
  tcase_add_test(tc, f_fzer_inf);
  tcase_add_test(tc, f_mins_ng_inf);
  tcase_add_test(tc, f_plus_ng_inf);
  tcase_add_test(tc, f_spac_ng_inf);
  tcase_add_test(tc, f_hash_ng_inf);
  tcase_add_test(tc, f_fzer_ng_inf);
  tcase_add_test(tc, f_width_nan);
  tcase_add_test(tc, f_zrpc_nan);
  tcase_add_test(tc, f_prec_nan);
  tcase_add_test(tc, f_width_inf);
  tcase_add_test(tc, f_zrpc_inf);
  tcase_add_test(tc, f_prec_inf);
  tcase_add_test(tc, f_width_ng_inf);
  tcase_add_test(tc, f_zrpc_ng_inf);
  tcase_add_test(tc, f_prec_ng_inf);
  tcase_add_test(tc, f_width_prec_nan);
  tcase_add_test(tc, f_width_prec_inf);
  tcase_add_test(tc, f_width_prec_ng_inf);
  tcase_add_test(tc, f_width_mins_nan);
  tcase_add_test(tc, f_width_plus_nan);
  tcase_add_test(tc, f_width_spac_nan);
  tcase_add_test(tc, f_width_hash_nan);
  tcase_add_test(tc, f_width_fzer_nan);
  tcase_add_test(tc, f_width_mins_inf);
  tcase_add_test(tc, f_width_plus_inf);
  tcase_add_test(tc, f_width_spac_inf);
  tcase_add_test(tc, f_width_hash_inf);
  tcase_add_test(tc, f_width_fzer_inf);
  tcase_add_test(tc, f_width_mins_ng_inf);
  tcase_add_test(tc, f_width_plus_ng_inf);
  tcase_add_test(tc, f_width_spac_ng_inf);
  tcase_add_test(tc, f_width_hash_ng_inf);
  tcase_add_test(tc, f_width_fzer_ng_inf);
  tcase_add_test(tc, f_zrwth_plus_nan);
  tcase_add_test(tc, f_zrwth_spac_nan);
  tcase_add_test(tc, f_zrwth_hash_nan);
  tcase_add_test(tc, f_zrwth_plus_inf);
  tcase_add_test(tc, f_zrwth_spac_inf);
  tcase_add_test(tc, f_zrwth_hash_inf);
  tcase_add_test(tc, f_zrwth_plus_ng_inf);
  tcase_add_test(tc, f_zrwth_spac_ng_inf);
  tcase_add_test(tc, f_zrwth_hash_ng_inf);
  tcase_add_test(tc, f_prec_mins_nan);
  tcase_add_test(tc, f_prec_plus_nan);
  tcase_add_test(tc, f_prec_spac_nan);
  tcase_add_test(tc, f_prec_hash_nan);
  tcase_add_test(tc, f_prec_fzer_nan);
  tcase_add_test(tc, f_prec_mins_inf);
  tcase_add_test(tc, f_prec_plus_inf);
  tcase_add_test(tc, f_prec_spac_inf);
  tcase_add_test(tc, f_prec_hash_inf);
  tcase_add_test(tc, f_prec_fzer_inf);
  tcase_add_test(tc, f_prec_mins_ng_inf);
  tcase_add_test(tc, f_prec_plus_ng_inf);
  tcase_add_test(tc, f_prec_spac_ng_inf);
  tcase_add_test(tc, f_prec_hash_ng_inf);
  tcase_add_test(tc, f_prec_fzer_ng_inf);
  tcase_add_test(tc, f_zrpc_mins_nan);
  tcase_add_test(tc, f_zrpc_plus_nan);
  tcase_add_test(tc, f_zrpc_spac_nan);
  tcase_add_test(tc, f_zrpc_hash_nan);
  tcase_add_test(tc, f_zrpc_fzer_nan);
  tcase_add_test(tc, f_zrpc_mins_inf);
  tcase_add_test(tc, f_zrpc_plus_inf);
  tcase_add_test(tc, f_zrpc_spac_inf);
  tcase_add_test(tc, f_zrpc_hash_inf);
  tcase_add_test(tc, f_zrpc_fzer_inf);
  tcase_add_test(tc, f_zrpc_mins_ng_inf);
  tcase_add_test(tc, f_zrpc_plus_ng_inf);
  tcase_add_test(tc, f_zrpc_spac_ng_inf);
  tcase_add_test(tc, f_zrpc_hash_ng_inf);
  tcase_add_test(tc, f_zrpc_fzer_ng_inf);
  tcase_add_test(tc, f_width_prec_mins_nan);
  tcase_add_test(tc, f_width_prec_plus_nan);
  tcase_add_test(tc, f_width_prec_spac_nan);
  tcase_add_test(tc, f_width_prec_hash_nan);
  tcase_add_test(tc, f_width_prec_fzer_nan);
  tcase_add_test(tc, f_width_prec_mins_inf);
  tcase_add_test(tc, f_width_prec_plus_inf);
  tcase_add_test(tc, f_width_prec_spac_inf);
  tcase_add_test(tc, f_width_prec_hash_inf);
  tcase_add_test(tc, f_width_prec_fzer_inf);
  tcase_add_test(tc, f_width_prec_mins_ng_inf);
  tcase_add_test(tc, f_width_prec_plus_ng_inf);
  tcase_add_test(tc, f_width_prec_spac_ng_inf);
  tcase_add_test(tc, f_width_prec_hash_ng_inf);
  tcase_add_test(tc, f_width_prec_fzer_ng_inf);
  tcase_add_test(tc, f_zrwth_zrpc_plus_nan);
  tcase_add_test(tc, f_zrwth_zrpc_spac_nan);
  tcase_add_test(tc, f_zrwth_zrpc_hash_nan);
  tcase_add_test(tc, f_zrwth_zrpc_plus_inf);
  tcase_add_test(tc, f_zrwth_zrpc_spac_inf);
  tcase_add_test(tc, f_zrwth_zrpc_hash_inf);
  tcase_add_test(tc, f_zrwth_zrpc_plus_ng_inf);
  tcase_add_test(tc, f_zrwth_zrpc_spac_ng_inf);
  tcase_add_test(tc, f_zrwth_zrpc_hash_ng_inf);
  tcase_add_test(tc, f_dynamic_prec_nan);
  tcase_add_test(tc, f_dynamic_prec_inf);
  tcase_add_test(tc, f_dynamic_prec_ng_inf);
  tcase_add_test(tc, f_dynamic_width_nan);
  tcase_add_test(tc, f_dynamic_width_inf);
  tcase_add_test(tc, f_dynamic_width_ng_inf);
  tcase_add_test(tc, f_dynamic_width_prec_nan);
  tcase_add_test(tc, f_dynamic_width_prec_inf);
  tcase_add_test(tc, f_dynamic_width_prec_ng_inf);
  tcase_add_test(tc, g_mins_nan);
  tcase_add_test(tc, g_plus_nan);
  tcase_add_test(tc, g_spac_nan);
  tcase_add_test(tc, g_hash_nan);
  tcase_add_test(tc, g_fzer_nan);
  tcase_add_test(tc, g_mins_inf);
  tcase_add_test(tc, g_plus_inf);
  tcase_add_test(tc, g_spac_inf);
  tcase_add_test(tc, g_hash_inf);
  tcase_add_test(tc, g_fzer_inf);
  tcase_add_test(tc, g_mins_ng_inf);
  tcase_add_test(tc, g_plus_ng_inf);
  tcase_add_test(tc, g_spac_ng_inf);
  tcase_add_test(tc, g_hash_ng_inf);
  tcase_add_test(tc, g_fzer_ng_inf);
  tcase_add_test(tc, g_width_nan);
  tcase_add_test(tc, g_zrpc_nan);
  tcase_add_test(tc, g_prec_nan);
  tcase_add_test(tc, g_width_inf);
  tcase_add_test(tc, g_zrpc_inf);
  tcase_add_test(tc, g_prec_inf);
  tcase_add_test(tc, g_width_ng_inf);
  tcase_add_test(tc, g_zrpc_ng_inf);
  tcase_add_test(tc, g_prec_ng_inf);
  tcase_add_test(tc, g_width_prec_nan);
  tcase_add_test(tc, g_width_prec_inf);
  tcase_add_test(tc, g_width_prec_ng_inf);
  tcase_add_test(tc, g_width_mins_nan);
  tcase_add_test(tc, g_width_plus_nan);
  tcase_add_test(tc, g_width_spac_nan);
  tcase_add_test(tc, g_width_hash_nan);
  tcase_add_test(tc, g_width_fzer_nan);
  tcase_add_test(tc, g_width_mins_inf);
  tcase_add_test(tc, g_width_plus_inf);
  tcase_add_test(tc, g_width_spac_inf);
  tcase_add_test(tc, g_width_hash_inf);
  tcase_add_test(tc, g_width_fzer_inf);
  tcase_add_test(tc, g_width_mins_ng_inf);
  tcase_add_test(tc, g_width_plus_ng_inf);
  tcase_add_test(tc, g_width_spac_ng_inf);
  tcase_add_test(tc, g_width_hash_ng_inf);
  tcase_add_test(tc, g_width_fzer_ng_inf);
  tcase_add_test(tc, g_zrwth_plus_nan);
  tcase_add_test(tc, g_zrwth_spac_nan);
  tcase_add_test(tc, g_zrwth_hash_nan);
  tcase_add_test(tc, g_zrwth_plus_inf);
  tcase_add_test(tc, g_zrwth_spac_inf);
  tcase_add_test(tc, g_zrwth_hash_inf);
  tcase_add_test(tc, g_zrwth_plus_ng_inf);
  tcase_add_test(tc, g_zrwth_spac_ng_inf);
  tcase_add_test(tc, g_zrwth_hash_ng_inf);
  tcase_add_test(tc, g_prec_mins_nan);
  tcase_add_test(tc, g_prec_plus_nan);
  tcase_add_test(tc, g_prec_spac_nan);
  tcase_add_test(tc, g_prec_hash_nan);
  tcase_add_test(tc, g_prec_fzer_nan);
  tcase_add_test(tc, g_prec_mins_inf);
  tcase_add_test(tc, g_prec_plus_inf);
  tcase_add_test(tc, g_prec_spac_inf);
  tcase_add_test(tc, g_prec_hash_inf);
  tcase_add_test(tc, g_prec_fzer_inf);
  tcase_add_test(tc, g_prec_mins_ng_inf);
  tcase_add_test(tc, g_prec_plus_ng_inf);
  tcase_add_test(tc, g_prec_spac_ng_inf);
  tcase_add_test(tc, g_prec_hash_ng_inf);
  tcase_add_test(tc, g_prec_fzer_ng_inf);
  tcase_add_test(tc, g_zrpc_mins_nan);
  tcase_add_test(tc, g_zrpc_plus_nan);
  tcase_add_test(tc, g_zrpc_spac_nan);
  tcase_add_test(tc, g_zrpc_hash_nan);
  tcase_add_test(tc, g_zrpc_fzer_nan);
  tcase_add_test(tc, g_zrpc_mins_inf);
  tcase_add_test(tc, g_zrpc_plus_inf);
  tcase_add_test(tc, g_zrpc_spac_inf);
  tcase_add_test(tc, g_zrpc_hash_inf);
  tcase_add_test(tc, g_zrpc_fzer_inf);
  tcase_add_test(tc, g_zrpc_mins_ng_inf);
  tcase_add_test(tc, g_zrpc_plus_ng_inf);
  tcase_add_test(tc, g_zrpc_spac_ng_inf);
  tcase_add_test(tc, g_zrpc_hash_ng_inf);
  tcase_add_test(tc, g_zrpc_fzer_ng_inf);
  tcase_add_test(tc, g_width_prec_mins_nan);
  tcase_add_test(tc, g_width_prec_plus_nan);
  tcase_add_test(tc, g_width_prec_spac_nan);
  tcase_add_test(tc, g_width_prec_hash_nan);
  tcase_add_test(tc, g_width_prec_fzer_nan);
  tcase_add_test(tc, g_width_prec_mins_inf);
  tcase_add_test(tc, g_width_prec_plus_inf);
  tcase_add_test(tc, g_width_prec_spac_inf);
  tcase_add_test(tc, g_width_prec_hash_inf);
  tcase_add_test(tc, g_width_prec_fzer_inf);
  tcase_add_test(tc, g_width_prec_mins_ng_inf);
  tcase_add_test(tc, g_width_prec_plus_ng_inf);
  tcase_add_test(tc, g_width_prec_spac_ng_inf);
  tcase_add_test(tc, g_width_prec_hash_ng_inf);
  tcase_add_test(tc, g_width_prec_fzer_ng_inf);
  tcase_add_test(tc, g_zrwth_zrpc_plus_nan);
  tcase_add_test(tc, g_zrwth_zrpc_spac_nan);
  tcase_add_test(tc, g_zrwth_zrpc_hash_nan);
  tcase_add_test(tc, g_zrwth_zrpc_plus_inf);
  tcase_add_test(tc, g_zrwth_zrpc_spac_inf);
  tcase_add_test(tc, g_zrwth_zrpc_hash_inf);
  tcase_add_test(tc, g_zrwth_zrpc_plus_ng_inf);
  tcase_add_test(tc, g_zrwth_zrpc_spac_ng_inf);
  tcase_add_test(tc, g_zrwth_zrpc_hash_ng_inf);
  tcase_add_test(tc, g_dynamic_prec_nan);
  tcase_add_test(tc, g_dynamic_prec_inf);
  tcase_add_test(tc, g_dynamic_prec_ng_inf);
  tcase_add_test(tc, g_dynamic_width_nan);
  tcase_add_test(tc, g_dynamic_width_inf);
  tcase_add_test(tc, g_dynamic_width_ng_inf);
  tcase_add_test(tc, g_dynamic_width_prec_nan);
  tcase_add_test(tc, g_dynamic_width_prec_inf);
  tcase_add_test(tc, g_dynamic_width_prec_ng_inf);
  tcase_add_test(tc, G_mins_nan);
  tcase_add_test(tc, G_plus_nan);
  tcase_add_test(tc, G_spac_nan);
  tcase_add_test(tc, G_hash_nan);
  tcase_add_test(tc, G_fzer_nan);
  tcase_add_test(tc, G_mins_inf);
  tcase_add_test(tc, G_plus_inf);
  tcase_add_test(tc, G_spac_inf);
  tcase_add_test(tc, G_hash_inf);
  tcase_add_test(tc, G_fzer_inf);
  tcase_add_test(tc, G_mins_ng_inf);
  tcase_add_test(tc, G_plus_ng_inf);
  tcase_add_test(tc, G_spac_ng_inf);
  tcase_add_test(tc, G_hash_ng_inf);
  tcase_add_test(tc, G_fzer_ng_inf);
  tcase_add_test(tc, G_width_nan);
  tcase_add_test(tc, G_zrpc_nan);
  tcase_add_test(tc, G_prec_nan);
  tcase_add_test(tc, G_width_inf);
  tcase_add_test(tc, G_zrpc_inf);
  tcase_add_test(tc, G_prec_inf);
  tcase_add_test(tc, G_width_ng_inf);
  tcase_add_test(tc, G_zrpc_ng_inf);
  tcase_add_test(tc, G_prec_ng_inf);
  tcase_add_test(tc, G_width_prec_nan);
  tcase_add_test(tc, G_width_prec_inf);
  tcase_add_test(tc, G_width_prec_ng_inf);
  tcase_add_test(tc, G_width_mins_nan);
  tcase_add_test(tc, G_width_plus_nan);
  tcase_add_test(tc, G_width_spac_nan);
  tcase_add_test(tc, G_width_hash_nan);
  tcase_add_test(tc, G_width_fzer_nan);
  tcase_add_test(tc, G_width_mins_inf);
  tcase_add_test(tc, G_width_plus_inf);
  tcase_add_test(tc, G_width_spac_inf);
  tcase_add_test(tc, G_width_hash_inf);
  tcase_add_test(tc, G_width_fzer_inf);
  tcase_add_test(tc, G_width_mins_ng_inf);
  tcase_add_test(tc, G_width_plus_ng_inf);
  tcase_add_test(tc, G_width_spac_ng_inf);
  tcase_add_test(tc, G_width_hash_ng_inf);
  tcase_add_test(tc, G_width_fzer_ng_inf);
  tcase_add_test(tc, G_zrwth_plus_nan);
  tcase_add_test(tc, G_zrwth_spac_nan);
  tcase_add_test(tc, G_zrwth_hash_nan);
  tcase_add_test(tc, G_zrwth_plus_inf);
  tcase_add_test(tc, G_zrwth_spac_inf);
  tcase_add_test(tc, G_zrwth_hash_inf);
  tcase_add_test(tc, G_zrwth_plus_ng_inf);
  tcase_add_test(tc, G_zrwth_spac_ng_inf);
  tcase_add_test(tc, G_zrwth_hash_ng_inf);
  tcase_add_test(tc, G_prec_mins_nan);
  tcase_add_test(tc, G_prec_plus_nan);
  tcase_add_test(tc, G_prec_spac_nan);
  tcase_add_test(tc, G_prec_hash_nan);
  tcase_add_test(tc, G_prec_fzer_nan);
  tcase_add_test(tc, G_prec_mins_inf);
  tcase_add_test(tc, G_prec_plus_inf);
  tcase_add_test(tc, G_prec_spac_inf);
  tcase_add_test(tc, G_prec_hash_inf);
  tcase_add_test(tc, G_prec_fzer_inf);
  tcase_add_test(tc, G_prec_mins_ng_inf);
  tcase_add_test(tc, G_prec_plus_ng_inf);
  tcase_add_test(tc, G_prec_spac_ng_inf);
  tcase_add_test(tc, G_prec_hash_ng_inf);
  tcase_add_test(tc, G_prec_fzer_ng_inf);
  tcase_add_test(tc, G_zrpc_mins_nan);
  tcase_add_test(tc, G_zrpc_plus_nan);
  tcase_add_test(tc, G_zrpc_spac_nan);
  tcase_add_test(tc, G_zrpc_hash_nan);
  tcase_add_test(tc, G_zrpc_fzer_nan);
  tcase_add_test(tc, G_zrpc_mins_inf);
  tcase_add_test(tc, G_zrpc_plus_inf);
  tcase_add_test(tc, G_zrpc_spac_inf);
  tcase_add_test(tc, G_zrpc_hash_inf);
  tcase_add_test(tc, G_zrpc_fzer_inf);
  tcase_add_test(tc, G_zrpc_mins_ng_inf);
  tcase_add_test(tc, G_zrpc_plus_ng_inf);
  tcase_add_test(tc, G_zrpc_spac_ng_inf);
  tcase_add_test(tc, G_zrpc_hash_ng_inf);
  tcase_add_test(tc, G_zrpc_fzer_ng_inf);
  tcase_add_test(tc, G_width_prec_mins_nan);
  tcase_add_test(tc, G_width_prec_plus_nan);
  tcase_add_test(tc, G_width_prec_spac_nan);
  tcase_add_test(tc, G_width_prec_hash_nan);
  tcase_add_test(tc, G_width_prec_fzer_nan);
  tcase_add_test(tc, G_width_prec_mins_inf);
  tcase_add_test(tc, G_width_prec_plus_inf);
  tcase_add_test(tc, G_width_prec_spac_inf);
  tcase_add_test(tc, G_width_prec_hash_inf);
  tcase_add_test(tc, G_width_prec_fzer_inf);
  tcase_add_test(tc, G_width_prec_mins_ng_inf);
  tcase_add_test(tc, G_width_prec_plus_ng_inf);
  tcase_add_test(tc, G_width_prec_spac_ng_inf);
  tcase_add_test(tc, G_width_prec_hash_ng_inf);
  tcase_add_test(tc, G_width_prec_fzer_ng_inf);
  tcase_add_test(tc, G_zrwth_zrpc_plus_nan);
  tcase_add_test(tc, G_zrwth_zrpc_spac_nan);
  tcase_add_test(tc, G_zrwth_zrpc_hash_nan);
  tcase_add_test(tc, G_zrwth_zrpc_plus_inf);
  tcase_add_test(tc, G_zrwth_zrpc_spac_inf);
  tcase_add_test(tc, G_zrwth_zrpc_hash_inf);
  tcase_add_test(tc, G_zrwth_zrpc_plus_ng_inf);
  tcase_add_test(tc, G_zrwth_zrpc_spac_ng_inf);
  tcase_add_test(tc, G_zrwth_zrpc_hash_ng_inf);
  tcase_add_test(tc, G_dynamic_prec_nan);
  tcase_add_test(tc, G_dynamic_prec_inf);
  tcase_add_test(tc, G_dynamic_prec_ng_inf);
  tcase_add_test(tc, G_dynamic_width_nan);
  tcase_add_test(tc, G_dynamic_width_inf);
  tcase_add_test(tc, G_dynamic_width_ng_inf);
  tcase_add_test(tc, G_dynamic_width_prec_nan);
  tcase_add_test(tc, G_dynamic_width_prec_inf);
  tcase_add_test(tc, G_dynamic_width_prec_ng_inf);
  tcase_add_test(tc, le_mins_nan);
  tcase_add_test(tc, le_plus_nan);
  tcase_add_test(tc, le_spac_nan);
  tcase_add_test(tc, le_hash_nan);
  tcase_add_test(tc, le_fzer_nan);
  tcase_add_test(tc, le_mins_inf);
  tcase_add_test(tc, le_plus_inf);
  tcase_add_test(tc, le_spac_inf);
  tcase_add_test(tc, le_hash_inf);
  tcase_add_test(tc, le_fzer_inf);
  tcase_add_test(tc, le_mins_ng_inf);
  tcase_add_test(tc, le_plus_ng_inf);
  tcase_add_test(tc, le_spac_ng_inf);
  tcase_add_test(tc, le_hash_ng_inf);
  tcase_add_test(tc, le_fzer_ng_inf);
  tcase_add_test(tc, le_width_nan);
  tcase_add_test(tc, le_zrpc_nan);
  tcase_add_test(tc, le_prec_nan);
  tcase_add_test(tc, le_width_inf);
  tcase_add_test(tc, le_zrpc_inf);
  tcase_add_test(tc, le_prec_inf);
  tcase_add_test(tc, le_width_ng_inf);
  tcase_add_test(tc, le_zrpc_ng_inf);
  tcase_add_test(tc, le_prec_ng_inf);
  tcase_add_test(tc, le_width_prec_nan);
  tcase_add_test(tc, le_width_prec_inf);
  tcase_add_test(tc, le_width_prec_ng_inf);
  tcase_add_test(tc, le_width_mins_nan);
  tcase_add_test(tc, le_width_plus_nan);
  tcase_add_test(tc, le_width_spac_nan);
  tcase_add_test(tc, le_width_hash_nan);
  tcase_add_test(tc, le_width_fzer_nan);
  tcase_add_test(tc, le_width_mins_inf);
  tcase_add_test(tc, le_width_plus_inf);
  tcase_add_test(tc, le_width_spac_inf);
  tcase_add_test(tc, le_width_hash_inf);
  tcase_add_test(tc, le_width_fzer_inf);
  tcase_add_test(tc, le_width_mins_ng_inf);
  tcase_add_test(tc, le_width_plus_ng_inf);
  tcase_add_test(tc, le_width_spac_ng_inf);
  tcase_add_test(tc, le_width_hash_ng_inf);
  tcase_add_test(tc, le_width_fzer_ng_inf);
  tcase_add_test(tc, le_zrwth_plus_nan);
  tcase_add_test(tc, le_zrwth_spac_nan);
  tcase_add_test(tc, le_zrwth_hash_nan);
  tcase_add_test(tc, le_zrwth_plus_inf);
  tcase_add_test(tc, le_zrwth_spac_inf);
  tcase_add_test(tc, le_zrwth_hash_inf);
  tcase_add_test(tc, le_zrwth_plus_ng_inf);
  tcase_add_test(tc, le_zrwth_spac_ng_inf);
  tcase_add_test(tc, le_zrwth_hash_ng_inf);
  tcase_add_test(tc, le_prec_mins_nan);
  tcase_add_test(tc, le_prec_plus_nan);
  tcase_add_test(tc, le_prec_spac_nan);
  tcase_add_test(tc, le_prec_hash_nan);
  tcase_add_test(tc, le_prec_fzer_nan);
  tcase_add_test(tc, le_prec_mins_inf);
  tcase_add_test(tc, le_prec_plus_inf);
  tcase_add_test(tc, le_prec_spac_inf);
  tcase_add_test(tc, le_prec_hash_inf);
  tcase_add_test(tc, le_prec_fzer_inf);
  tcase_add_test(tc, le_prec_mins_ng_inf);
  tcase_add_test(tc, le_prec_plus_ng_inf);
  tcase_add_test(tc, le_prec_spac_ng_inf);
  tcase_add_test(tc, le_prec_hash_ng_inf);
  tcase_add_test(tc, le_prec_fzer_ng_inf);
  tcase_add_test(tc, le_zrpc_mins_nan);
  tcase_add_test(tc, le_zrpc_plus_nan);
  tcase_add_test(tc, le_zrpc_spac_nan);
  tcase_add_test(tc, le_zrpc_hash_nan);
  tcase_add_test(tc, le_zrpc_fzer_nan);
  tcase_add_test(tc, le_zrpc_mins_inf);
  tcase_add_test(tc, le_zrpc_plus_inf);
  tcase_add_test(tc, le_zrpc_spac_inf);
  tcase_add_test(tc, le_zrpc_hash_inf);
  tcase_add_test(tc, le_zrpc_fzer_inf);
  tcase_add_test(tc, le_zrpc_mins_ng_inf);
  tcase_add_test(tc, le_zrpc_plus_ng_inf);
  tcase_add_test(tc, le_zrpc_spac_ng_inf);
  tcase_add_test(tc, le_zrpc_hash_ng_inf);
  tcase_add_test(tc, le_zrpc_fzer_ng_inf);
  tcase_add_test(tc, le_width_prec_mins_nan);
  tcase_add_test(tc, le_width_prec_plus_nan);
  tcase_add_test(tc, le_width_prec_spac_nan);
  tcase_add_test(tc, le_width_prec_hash_nan);
  tcase_add_test(tc, le_width_prec_fzer_nan);
  tcase_add_test(tc, le_width_prec_mins_inf);
  tcase_add_test(tc, le_width_prec_plus_inf);
  tcase_add_test(tc, le_width_prec_spac_inf);
  tcase_add_test(tc, le_width_prec_hash_inf);
  tcase_add_test(tc, le_width_prec_fzer_inf);
  tcase_add_test(tc, le_width_prec_mins_ng_inf);
  tcase_add_test(tc, le_width_prec_plus_ng_inf);
  tcase_add_test(tc, le_width_prec_spac_ng_inf);
  tcase_add_test(tc, le_width_prec_hash_ng_inf);
  tcase_add_test(tc, le_width_prec_fzer_ng_inf);
  tcase_add_test(tc, le_zrwth_zrpc_plus_nan);
  tcase_add_test(tc, le_zrwth_zrpc_spac_nan);
  tcase_add_test(tc, le_zrwth_zrpc_hash_nan);
  tcase_add_test(tc, le_zrwth_zrpc_plus_inf);
  tcase_add_test(tc, le_zrwth_zrpc_spac_inf);
  tcase_add_test(tc, le_zrwth_zrpc_hash_inf);
  tcase_add_test(tc, le_zrwth_zrpc_plus_ng_inf);
  tcase_add_test(tc, le_zrwth_zrpc_spac_ng_inf);
  tcase_add_test(tc, le_zrwth_zrpc_hash_ng_inf);
  tcase_add_test(tc, le_dynamic_prec_nan);
  tcase_add_test(tc, le_dynamic_prec_inf);
  tcase_add_test(tc, le_dynamic_prec_ng_inf);
  tcase_add_test(tc, le_dynamic_width_nan);
  tcase_add_test(tc, le_dynamic_width_inf);
  tcase_add_test(tc, le_dynamic_width_ng_inf);
  tcase_add_test(tc, le_dynamic_width_prec_nan);
  tcase_add_test(tc, le_dynamic_width_prec_inf);
  tcase_add_test(tc, le_dynamic_width_prec_ng_inf);
  tcase_add_test(tc, lE_mins_nan);
  tcase_add_test(tc, lE_plus_nan);
  tcase_add_test(tc, lE_spac_nan);
  tcase_add_test(tc, lE_hash_nan);
  tcase_add_test(tc, lE_fzer_nan);
  tcase_add_test(tc, lE_mins_inf);
  tcase_add_test(tc, lE_plus_inf);
  tcase_add_test(tc, lE_spac_inf);
  tcase_add_test(tc, lE_hash_inf);
  tcase_add_test(tc, lE_fzer_inf);
  tcase_add_test(tc, lE_mins_ng_inf);
  tcase_add_test(tc, lE_plus_ng_inf);
  tcase_add_test(tc, lE_spac_ng_inf);
  tcase_add_test(tc, lE_hash_ng_inf);
  tcase_add_test(tc, lE_fzer_ng_inf);
  tcase_add_test(tc, lE_width_nan);
  tcase_add_test(tc, lE_zrpc_nan);
  tcase_add_test(tc, lE_prec_nan);
  tcase_add_test(tc, lE_width_inf);
  tcase_add_test(tc, lE_zrpc_inf);
  tcase_add_test(tc, lE_prec_inf);
  tcase_add_test(tc, lE_width_ng_inf);
  tcase_add_test(tc, lE_zrpc_ng_inf);
  tcase_add_test(tc, lE_prec_ng_inf);
  tcase_add_test(tc, lE_width_prec_nan);
  tcase_add_test(tc, lE_width_prec_inf);
  tcase_add_test(tc, lE_width_prec_ng_inf);
  tcase_add_test(tc, lE_width_mins_nan);
  tcase_add_test(tc, lE_width_plus_nan);
  tcase_add_test(tc, lE_width_spac_nan);
  tcase_add_test(tc, lE_width_hash_nan);
  tcase_add_test(tc, lE_width_fzer_nan);
  tcase_add_test(tc, lE_width_mins_inf);
  tcase_add_test(tc, lE_width_plus_inf);
  tcase_add_test(tc, lE_width_spac_inf);
  tcase_add_test(tc, lE_width_hash_inf);
  tcase_add_test(tc, lE_width_fzer_inf);
  tcase_add_test(tc, lE_width_mins_ng_inf);
  tcase_add_test(tc, lE_width_plus_ng_inf);
  tcase_add_test(tc, lE_width_spac_ng_inf);
  tcase_add_test(tc, lE_width_hash_ng_inf);
  tcase_add_test(tc, lE_width_fzer_ng_inf);
  tcase_add_test(tc, lE_zrwth_plus_nan);
  tcase_add_test(tc, lE_zrwth_spac_nan);
  tcase_add_test(tc, lE_zrwth_hash_nan);
  tcase_add_test(tc, lE_zrwth_plus_inf);
  tcase_add_test(tc, lE_zrwth_spac_inf);
  tcase_add_test(tc, lE_zrwth_hash_inf);
  tcase_add_test(tc, lE_zrwth_plus_ng_inf);
  tcase_add_test(tc, lE_zrwth_spac_ng_inf);
  tcase_add_test(tc, lE_zrwth_hash_ng_inf);
  tcase_add_test(tc, lE_prec_mins_nan);
  tcase_add_test(tc, lE_prec_plus_nan);
  tcase_add_test(tc, lE_prec_spac_nan);
  tcase_add_test(tc, lE_prec_hash_nan);
  tcase_add_test(tc, lE_prec_fzer_nan);
  tcase_add_test(tc, lE_prec_mins_inf);
  tcase_add_test(tc, lE_prec_plus_inf);
  tcase_add_test(tc, lE_prec_spac_inf);
  tcase_add_test(tc, lE_prec_hash_inf);
  tcase_add_test(tc, lE_prec_fzer_inf);
  tcase_add_test(tc, lE_prec_mins_ng_inf);
  tcase_add_test(tc, lE_prec_plus_ng_inf);
  tcase_add_test(tc, lE_prec_spac_ng_inf);
  tcase_add_test(tc, lE_prec_hash_ng_inf);
  tcase_add_test(tc, lE_prec_fzer_ng_inf);
  tcase_add_test(tc, lE_zrpc_mins_nan);
  tcase_add_test(tc, lE_zrpc_plus_nan);
  tcase_add_test(tc, lE_zrpc_spac_nan);
  tcase_add_test(tc, lE_zrpc_hash_nan);
  tcase_add_test(tc, lE_zrpc_fzer_nan);
  tcase_add_test(tc, lE_zrpc_mins_inf);
  tcase_add_test(tc, lE_zrpc_plus_inf);
  tcase_add_test(tc, lE_zrpc_spac_inf);
  tcase_add_test(tc, lE_zrpc_hash_inf);
  tcase_add_test(tc, lE_zrpc_fzer_inf);
  tcase_add_test(tc, lE_zrpc_mins_ng_inf);
  tcase_add_test(tc, lE_zrpc_plus_ng_inf);
  tcase_add_test(tc, lE_zrpc_spac_ng_inf);
  tcase_add_test(tc, lE_zrpc_hash_ng_inf);
  tcase_add_test(tc, lE_zrpc_fzer_ng_inf);
  tcase_add_test(tc, lE_width_prec_mins_nan);
  tcase_add_test(tc, lE_width_prec_plus_nan);
  tcase_add_test(tc, lE_width_prec_spac_nan);
  tcase_add_test(tc, lE_width_prec_hash_nan);
  tcase_add_test(tc, lE_width_prec_fzer_nan);
  tcase_add_test(tc, lE_width_prec_mins_inf);
  tcase_add_test(tc, lE_width_prec_plus_inf);
  tcase_add_test(tc, lE_width_prec_spac_inf);
  tcase_add_test(tc, lE_width_prec_hash_inf);
  tcase_add_test(tc, lE_width_prec_fzer_inf);
  tcase_add_test(tc, lE_width_prec_mins_ng_inf);
  tcase_add_test(tc, lE_width_prec_plus_ng_inf);
  tcase_add_test(tc, lE_width_prec_spac_ng_inf);
  tcase_add_test(tc, lE_width_prec_hash_ng_inf);
  tcase_add_test(tc, lE_width_prec_fzer_ng_inf);
  tcase_add_test(tc, lE_zrwth_zrpc_plus_nan);
  tcase_add_test(tc, lE_zrwth_zrpc_spac_nan);
  tcase_add_test(tc, lE_zrwth_zrpc_hash_nan);
  tcase_add_test(tc, lE_zrwth_zrpc_plus_inf);
  tcase_add_test(tc, lE_zrwth_zrpc_spac_inf);
  tcase_add_test(tc, lE_zrwth_zrpc_hash_inf);
  tcase_add_test(tc, lE_zrwth_zrpc_plus_ng_inf);
  tcase_add_test(tc, lE_zrwth_zrpc_spac_ng_inf);
  tcase_add_test(tc, lE_zrwth_zrpc_hash_ng_inf);
  tcase_add_test(tc, lE_dynamic_prec_nan);
  tcase_add_test(tc, lE_dynamic_prec_inf);
  tcase_add_test(tc, lE_dynamic_prec_ng_inf);
  tcase_add_test(tc, lE_dynamic_width_nan);
  tcase_add_test(tc, lE_dynamic_width_inf);
  tcase_add_test(tc, lE_dynamic_width_ng_inf);
  tcase_add_test(tc, lE_dynamic_width_prec_nan);
  tcase_add_test(tc, lE_dynamic_width_prec_inf);
  tcase_add_test(tc, lE_dynamic_width_prec_ng_inf);
  tcase_add_test(tc, lf_mins_nan);
  tcase_add_test(tc, lf_plus_nan);
  tcase_add_test(tc, lf_spac_nan);
  tcase_add_test(tc, lf_hash_nan);
  tcase_add_test(tc, lf_fzer_nan);
  tcase_add_test(tc, lf_mins_inf);
  tcase_add_test(tc, lf_plus_inf);
  tcase_add_test(tc, lf_spac_inf);
  tcase_add_test(tc, lf_hash_inf);
  tcase_add_test(tc, lf_fzer_inf);
  tcase_add_test(tc, lf_mins_ng_inf);
  tcase_add_test(tc, lf_plus_ng_inf);
  tcase_add_test(tc, lf_spac_ng_inf);
  tcase_add_test(tc, lf_hash_ng_inf);
  tcase_add_test(tc, lf_fzer_ng_inf);
  tcase_add_test(tc, lf_width_nan);
  tcase_add_test(tc, lf_zrpc_nan);
  tcase_add_test(tc, lf_prec_nan);
  tcase_add_test(tc, lf_width_inf);
  tcase_add_test(tc, lf_zrpc_inf);
  tcase_add_test(tc, lf_prec_inf);
  tcase_add_test(tc, lf_width_ng_inf);
  tcase_add_test(tc, lf_zrpc_ng_inf);
  tcase_add_test(tc, lf_prec_ng_inf);
  tcase_add_test(tc, lf_width_prec_nan);
  tcase_add_test(tc, lf_width_prec_inf);
  tcase_add_test(tc, lf_width_prec_ng_inf);
  tcase_add_test(tc, lf_width_mins_nan);
  tcase_add_test(tc, lf_width_plus_nan);
  tcase_add_test(tc, lf_width_spac_nan);
  tcase_add_test(tc, lf_width_hash_nan);
  tcase_add_test(tc, lf_width_fzer_nan);
  tcase_add_test(tc, lf_width_mins_inf);
  tcase_add_test(tc, lf_width_plus_inf);
  tcase_add_test(tc, lf_width_spac_inf);
  tcase_add_test(tc, lf_width_hash_inf);
  tcase_add_test(tc, lf_width_fzer_inf);
  tcase_add_test(tc, lf_width_mins_ng_inf);
  tcase_add_test(tc, lf_width_plus_ng_inf);
  tcase_add_test(tc, lf_width_spac_ng_inf);
  tcase_add_test(tc, lf_width_hash_ng_inf);
  tcase_add_test(tc, lf_width_fzer_ng_inf);
  tcase_add_test(tc, lf_zrwth_plus_nan);
  tcase_add_test(tc, lf_zrwth_spac_nan);
  tcase_add_test(tc, lf_zrwth_hash_nan);
  tcase_add_test(tc, lf_zrwth_plus_inf);
  tcase_add_test(tc, lf_zrwth_spac_inf);
  tcase_add_test(tc, lf_zrwth_hash_inf);
  tcase_add_test(tc, lf_zrwth_plus_ng_inf);
  tcase_add_test(tc, lf_zrwth_spac_ng_inf);
  tcase_add_test(tc, lf_zrwth_hash_ng_inf);
  tcase_add_test(tc, lf_prec_mins_nan);
  tcase_add_test(tc, lf_prec_plus_nan);
  tcase_add_test(tc, lf_prec_spac_nan);
  tcase_add_test(tc, lf_prec_hash_nan);
  tcase_add_test(tc, lf_prec_fzer_nan);
  tcase_add_test(tc, lf_prec_mins_inf);
  tcase_add_test(tc, lf_prec_plus_inf);
  tcase_add_test(tc, lf_prec_spac_inf);
  tcase_add_test(tc, lf_prec_hash_inf);
  tcase_add_test(tc, lf_prec_fzer_inf);
  tcase_add_test(tc, lf_prec_mins_ng_inf);
  tcase_add_test(tc, lf_prec_plus_ng_inf);
  tcase_add_test(tc, lf_prec_spac_ng_inf);
  tcase_add_test(tc, lf_prec_hash_ng_inf);
  tcase_add_test(tc, lf_prec_fzer_ng_inf);
  tcase_add_test(tc, lf_zrpc_mins_nan);
  tcase_add_test(tc, lf_zrpc_plus_nan);
  tcase_add_test(tc, lf_zrpc_spac_nan);
  tcase_add_test(tc, lf_zrpc_hash_nan);
  tcase_add_test(tc, lf_zrpc_fzer_nan);
  tcase_add_test(tc, lf_zrpc_mins_inf);
  tcase_add_test(tc, lf_zrpc_plus_inf);
  tcase_add_test(tc, lf_zrpc_spac_inf);
  tcase_add_test(tc, lf_zrpc_hash_inf);
  tcase_add_test(tc, lf_zrpc_fzer_inf);
  tcase_add_test(tc, lf_zrpc_mins_ng_inf);
  tcase_add_test(tc, lf_zrpc_plus_ng_inf);
  tcase_add_test(tc, lf_zrpc_spac_ng_inf);
  tcase_add_test(tc, lf_zrpc_hash_ng_inf);
  tcase_add_test(tc, lf_zrpc_fzer_ng_inf);
  tcase_add_test(tc, lf_width_prec_mins_nan);
  tcase_add_test(tc, lf_width_prec_plus_nan);
  tcase_add_test(tc, lf_width_prec_spac_nan);
  tcase_add_test(tc, lf_width_prec_hash_nan);
  tcase_add_test(tc, lf_width_prec_fzer_nan);
  tcase_add_test(tc, lf_width_prec_mins_inf);
  tcase_add_test(tc, lf_width_prec_plus_inf);
  tcase_add_test(tc, lf_width_prec_spac_inf);
  tcase_add_test(tc, lf_width_prec_hash_inf);
  tcase_add_test(tc, lf_width_prec_fzer_inf);
  tcase_add_test(tc, lf_width_prec_mins_ng_inf);
  tcase_add_test(tc, lf_width_prec_plus_ng_inf);
  tcase_add_test(tc, lf_width_prec_spac_ng_inf);
  tcase_add_test(tc, lf_width_prec_hash_ng_inf);
  tcase_add_test(tc, lf_width_prec_fzer_ng_inf);
  tcase_add_test(tc, lf_zrwth_zrpc_plus_nan);
  tcase_add_test(tc, lf_zrwth_zrpc_spac_nan);
  tcase_add_test(tc, lf_zrwth_zrpc_hash_nan);
  tcase_add_test(tc, lf_zrwth_zrpc_plus_inf);
  tcase_add_test(tc, lf_zrwth_zrpc_spac_inf);
  tcase_add_test(tc, lf_zrwth_zrpc_hash_inf);
  tcase_add_test(tc, lf_zrwth_zrpc_plus_ng_inf);
  tcase_add_test(tc, lf_zrwth_zrpc_spac_ng_inf);
  tcase_add_test(tc, lf_zrwth_zrpc_hash_ng_inf);
  tcase_add_test(tc, lf_dynamic_prec_nan);
  tcase_add_test(tc, lf_dynamic_prec_inf);
  tcase_add_test(tc, lf_dynamic_prec_ng_inf);
  tcase_add_test(tc, lf_dynamic_width_nan);
  tcase_add_test(tc, lf_dynamic_width_inf);
  tcase_add_test(tc, lf_dynamic_width_ng_inf);
  tcase_add_test(tc, lf_dynamic_width_prec_nan);
  tcase_add_test(tc, lf_dynamic_width_prec_inf);
  tcase_add_test(tc, lf_dynamic_width_prec_ng_inf);
  tcase_add_test(tc, lg_mins_nan);
  tcase_add_test(tc, lg_plus_nan);
  tcase_add_test(tc, lg_spac_nan);
  tcase_add_test(tc, lg_hash_nan);
  tcase_add_test(tc, lg_fzer_nan);
  tcase_add_test(tc, lg_mins_inf);
  tcase_add_test(tc, lg_plus_inf);
  tcase_add_test(tc, lg_spac_inf);
  tcase_add_test(tc, lg_hash_inf);
  tcase_add_test(tc, lg_fzer_inf);
  tcase_add_test(tc, lg_mins_ng_inf);
  tcase_add_test(tc, lg_plus_ng_inf);
  tcase_add_test(tc, lg_spac_ng_inf);
  tcase_add_test(tc, lg_hash_ng_inf);
  tcase_add_test(tc, lg_fzer_ng_inf);
  tcase_add_test(tc, lg_width_nan);
  tcase_add_test(tc, lg_zrpc_nan);
  tcase_add_test(tc, lg_prec_nan);
  tcase_add_test(tc, lg_width_inf);
  tcase_add_test(tc, lg_zrpc_inf);
  tcase_add_test(tc, lg_prec_inf);
  tcase_add_test(tc, lg_width_ng_inf);
  tcase_add_test(tc, lg_zrpc_ng_inf);
  tcase_add_test(tc, lg_prec_ng_inf);
  tcase_add_test(tc, lg_width_prec_nan);
  tcase_add_test(tc, lg_width_prec_inf);
  tcase_add_test(tc, lg_width_prec_ng_inf);
  tcase_add_test(tc, lg_width_mins_nan);
  tcase_add_test(tc, lg_width_plus_nan);
  tcase_add_test(tc, lg_width_spac_nan);
  tcase_add_test(tc, lg_width_hash_nan);
  tcase_add_test(tc, lg_width_fzer_nan);
  tcase_add_test(tc, lg_width_mins_inf);
  tcase_add_test(tc, lg_width_plus_inf);
  tcase_add_test(tc, lg_width_spac_inf);
  tcase_add_test(tc, lg_width_hash_inf);
  tcase_add_test(tc, lg_width_fzer_inf);
  tcase_add_test(tc, lg_width_mins_ng_inf);
  tcase_add_test(tc, lg_width_plus_ng_inf);
  tcase_add_test(tc, lg_width_spac_ng_inf);
  tcase_add_test(tc, lg_width_hash_ng_inf);
  tcase_add_test(tc, lg_width_fzer_ng_inf);
  tcase_add_test(tc, lg_zrwth_plus_nan);
  tcase_add_test(tc, lg_zrwth_spac_nan);
  tcase_add_test(tc, lg_zrwth_hash_nan);
  tcase_add_test(tc, lg_zrwth_plus_inf);
  tcase_add_test(tc, lg_zrwth_spac_inf);
  tcase_add_test(tc, lg_zrwth_hash_inf);
  tcase_add_test(tc, lg_zrwth_plus_ng_inf);
  tcase_add_test(tc, lg_zrwth_spac_ng_inf);
  tcase_add_test(tc, lg_zrwth_hash_ng_inf);
  tcase_add_test(tc, lg_prec_mins_nan);
  tcase_add_test(tc, lg_prec_plus_nan);
  tcase_add_test(tc, lg_prec_spac_nan);
  tcase_add_test(tc, lg_prec_hash_nan);
  tcase_add_test(tc, lg_prec_fzer_nan);
  tcase_add_test(tc, lg_prec_mins_inf);
  tcase_add_test(tc, lg_prec_plus_inf);
  tcase_add_test(tc, lg_prec_spac_inf);
  tcase_add_test(tc, lg_prec_hash_inf);
  tcase_add_test(tc, lg_prec_fzer_inf);
  tcase_add_test(tc, lg_prec_mins_ng_inf);
  tcase_add_test(tc, lg_prec_plus_ng_inf);
  tcase_add_test(tc, lg_prec_spac_ng_inf);
  tcase_add_test(tc, lg_prec_hash_ng_inf);
  tcase_add_test(tc, lg_prec_fzer_ng_inf);
  tcase_add_test(tc, lg_zrpc_mins_nan);
  tcase_add_test(tc, lg_zrpc_plus_nan);
  tcase_add_test(tc, lg_zrpc_spac_nan);
  tcase_add_test(tc, lg_zrpc_hash_nan);
  tcase_add_test(tc, lg_zrpc_fzer_nan);
  tcase_add_test(tc, lg_zrpc_mins_inf);
  tcase_add_test(tc, lg_zrpc_plus_inf);
  tcase_add_test(tc, lg_zrpc_spac_inf);
  tcase_add_test(tc, lg_zrpc_hash_inf);
  tcase_add_test(tc, lg_zrpc_fzer_inf);
  tcase_add_test(tc, lg_zrpc_mins_ng_inf);
  tcase_add_test(tc, lg_zrpc_plus_ng_inf);
  tcase_add_test(tc, lg_zrpc_spac_ng_inf);
  tcase_add_test(tc, lg_zrpc_hash_ng_inf);
  tcase_add_test(tc, lg_zrpc_fzer_ng_inf);
  tcase_add_test(tc, lg_width_prec_mins_nan);
  tcase_add_test(tc, lg_width_prec_plus_nan);
  tcase_add_test(tc, lg_width_prec_spac_nan);
  tcase_add_test(tc, lg_width_prec_hash_nan);
  tcase_add_test(tc, lg_width_prec_fzer_nan);
  tcase_add_test(tc, lg_width_prec_mins_inf);
  tcase_add_test(tc, lg_width_prec_plus_inf);
  tcase_add_test(tc, lg_width_prec_spac_inf);
  tcase_add_test(tc, lg_width_prec_hash_inf);
  tcase_add_test(tc, lg_width_prec_fzer_inf);
  tcase_add_test(tc, lg_width_prec_mins_ng_inf);
  tcase_add_test(tc, lg_width_prec_plus_ng_inf);
  tcase_add_test(tc, lg_width_prec_spac_ng_inf);
  tcase_add_test(tc, lg_width_prec_hash_ng_inf);
  tcase_add_test(tc, lg_width_prec_fzer_ng_inf);
  tcase_add_test(tc, lg_zrwth_zrpc_plus_nan);
  tcase_add_test(tc, lg_zrwth_zrpc_spac_nan);
  tcase_add_test(tc, lg_zrwth_zrpc_hash_nan);
  tcase_add_test(tc, lg_zrwth_zrpc_plus_inf);
  tcase_add_test(tc, lg_zrwth_zrpc_spac_inf);
  tcase_add_test(tc, lg_zrwth_zrpc_hash_inf);
  tcase_add_test(tc, lg_zrwth_zrpc_plus_ng_inf);
  tcase_add_test(tc, lg_zrwth_zrpc_spac_ng_inf);
  tcase_add_test(tc, lg_zrwth_zrpc_hash_ng_inf);
  tcase_add_test(tc, lg_dynamic_prec_nan);
  tcase_add_test(tc, lg_dynamic_prec_inf);
  tcase_add_test(tc, lg_dynamic_prec_ng_inf);
  tcase_add_test(tc, lg_dynamic_width_nan);
  tcase_add_test(tc, lg_dynamic_width_inf);
  tcase_add_test(tc, lg_dynamic_width_ng_inf);
  tcase_add_test(tc, lg_dynamic_width_prec_nan);
  tcase_add_test(tc, lg_dynamic_width_prec_inf);
  tcase_add_test(tc, lg_dynamic_width_prec_ng_inf);
  tcase_add_test(tc, lG_mins_nan);
  tcase_add_test(tc, lG_plus_nan);
  tcase_add_test(tc, lG_spac_nan);
  tcase_add_test(tc, lG_hash_nan);
  tcase_add_test(tc, lG_fzer_nan);
  tcase_add_test(tc, lG_mins_inf);
  tcase_add_test(tc, lG_plus_inf);
  tcase_add_test(tc, lG_spac_inf);
  tcase_add_test(tc, lG_hash_inf);
  tcase_add_test(tc, lG_fzer_inf);
  tcase_add_test(tc, lG_mins_ng_inf);
  tcase_add_test(tc, lG_plus_ng_inf);
  tcase_add_test(tc, lG_spac_ng_inf);
  tcase_add_test(tc, lG_hash_ng_inf);
  tcase_add_test(tc, lG_fzer_ng_inf);
  tcase_add_test(tc, lG_width_nan);
  tcase_add_test(tc, lG_zrpc_nan);
  tcase_add_test(tc, lG_prec_nan);
  tcase_add_test(tc, lG_width_inf);
  tcase_add_test(tc, lG_zrpc_inf);
  tcase_add_test(tc, lG_prec_inf);
  tcase_add_test(tc, lG_width_ng_inf);
  tcase_add_test(tc, lG_zrpc_ng_inf);
  tcase_add_test(tc, lG_prec_ng_inf);
  tcase_add_test(tc, lG_width_prec_nan);
  tcase_add_test(tc, lG_width_prec_inf);
  tcase_add_test(tc, lG_width_prec_ng_inf);
  tcase_add_test(tc, lG_width_mins_nan);
  tcase_add_test(tc, lG_width_plus_nan);
  tcase_add_test(tc, lG_width_spac_nan);
  tcase_add_test(tc, lG_width_hash_nan);
  tcase_add_test(tc, lG_width_fzer_nan);
  tcase_add_test(tc, lG_width_mins_inf);
  tcase_add_test(tc, lG_width_plus_inf);
  tcase_add_test(tc, lG_width_spac_inf);
  tcase_add_test(tc, lG_width_hash_inf);
  tcase_add_test(tc, lG_width_fzer_inf);
  tcase_add_test(tc, lG_width_mins_ng_inf);
  tcase_add_test(tc, lG_width_plus_ng_inf);
  tcase_add_test(tc, lG_width_spac_ng_inf);
  tcase_add_test(tc, lG_width_hash_ng_inf);
  tcase_add_test(tc, lG_width_fzer_ng_inf);
  tcase_add_test(tc, lG_zrwth_plus_nan);
  tcase_add_test(tc, lG_zrwth_spac_nan);
  tcase_add_test(tc, lG_zrwth_hash_nan);
  tcase_add_test(tc, lG_zrwth_plus_inf);
  tcase_add_test(tc, lG_zrwth_spac_inf);
  tcase_add_test(tc, lG_zrwth_hash_inf);
  tcase_add_test(tc, lG_zrwth_plus_ng_inf);
  tcase_add_test(tc, lG_zrwth_spac_ng_inf);
  tcase_add_test(tc, lG_zrwth_hash_ng_inf);
  tcase_add_test(tc, lG_prec_mins_nan);
  tcase_add_test(tc, lG_prec_plus_nan);
  tcase_add_test(tc, lG_prec_spac_nan);
  tcase_add_test(tc, lG_prec_hash_nan);
  tcase_add_test(tc, lG_prec_fzer_nan);
  tcase_add_test(tc, lG_prec_mins_inf);
  tcase_add_test(tc, lG_prec_plus_inf);
  tcase_add_test(tc, lG_prec_spac_inf);
  tcase_add_test(tc, lG_prec_hash_inf);
  tcase_add_test(tc, lG_prec_fzer_inf);
  tcase_add_test(tc, lG_prec_mins_ng_inf);
  tcase_add_test(tc, lG_prec_plus_ng_inf);
  tcase_add_test(tc, lG_prec_spac_ng_inf);
  tcase_add_test(tc, lG_prec_hash_ng_inf);
  tcase_add_test(tc, lG_prec_fzer_ng_inf);
  tcase_add_test(tc, lG_zrpc_mins_nan);
  tcase_add_test(tc, lG_zrpc_plus_nan);
  tcase_add_test(tc, lG_zrpc_spac_nan);
  tcase_add_test(tc, lG_zrpc_hash_nan);
  tcase_add_test(tc, lG_zrpc_fzer_nan);
  tcase_add_test(tc, lG_zrpc_mins_inf);
  tcase_add_test(tc, lG_zrpc_plus_inf);
  tcase_add_test(tc, lG_zrpc_spac_inf);
  tcase_add_test(tc, lG_zrpc_hash_inf);
  tcase_add_test(tc, lG_zrpc_fzer_inf);
  tcase_add_test(tc, lG_zrpc_mins_ng_inf);
  tcase_add_test(tc, lG_zrpc_plus_ng_inf);
  tcase_add_test(tc, lG_zrpc_spac_ng_inf);
  tcase_add_test(tc, lG_zrpc_hash_ng_inf);
  tcase_add_test(tc, lG_zrpc_fzer_ng_inf);
  tcase_add_test(tc, lG_width_prec_mins_nan);
  tcase_add_test(tc, lG_width_prec_plus_nan);
  tcase_add_test(tc, lG_width_prec_spac_nan);
  tcase_add_test(tc, lG_width_prec_hash_nan);
  tcase_add_test(tc, lG_width_prec_fzer_nan);
  tcase_add_test(tc, lG_width_prec_mins_inf);
  tcase_add_test(tc, lG_width_prec_plus_inf);
  tcase_add_test(tc, lG_width_prec_spac_inf);
  tcase_add_test(tc, lG_width_prec_hash_inf);
  tcase_add_test(tc, lG_width_prec_fzer_inf);
  tcase_add_test(tc, lG_width_prec_mins_ng_inf);
  tcase_add_test(tc, lG_width_prec_plus_ng_inf);
  tcase_add_test(tc, lG_width_prec_spac_ng_inf);
  tcase_add_test(tc, lG_width_prec_hash_ng_inf);
  tcase_add_test(tc, lG_width_prec_fzer_ng_inf);
  tcase_add_test(tc, lG_zrwth_zrpc_plus_nan);
  tcase_add_test(tc, lG_zrwth_zrpc_spac_nan);
  tcase_add_test(tc, lG_zrwth_zrpc_hash_nan);
  tcase_add_test(tc, lG_zrwth_zrpc_plus_inf);
  tcase_add_test(tc, lG_zrwth_zrpc_spac_inf);
  tcase_add_test(tc, lG_zrwth_zrpc_hash_inf);
  tcase_add_test(tc, lG_zrwth_zrpc_plus_ng_inf);
  tcase_add_test(tc, lG_zrwth_zrpc_spac_ng_inf);
  tcase_add_test(tc, lG_zrwth_zrpc_hash_ng_inf);
  tcase_add_test(tc, lG_dynamic_prec_nan);
  tcase_add_test(tc, lG_dynamic_prec_inf);
  tcase_add_test(tc, lG_dynamic_prec_ng_inf);
  tcase_add_test(tc, lG_dynamic_width_nan);
  tcase_add_test(tc, lG_dynamic_width_inf);
  tcase_add_test(tc, lG_dynamic_width_ng_inf);
  tcase_add_test(tc, lG_dynamic_width_prec_nan);
  tcase_add_test(tc, lG_dynamic_width_prec_inf);
  tcase_add_test(tc, lG_dynamic_width_prec_ng_inf);
  tcase_add_test(tc, Le_mins_nan);
  tcase_add_test(tc, Le_plus_nan);
  tcase_add_test(tc, Le_spac_nan);
  tcase_add_test(tc, Le_hash_nan);
  tcase_add_test(tc, Le_fzer_nan);
  tcase_add_test(tc, Le_mins_inf);
  tcase_add_test(tc, Le_plus_inf);
  tcase_add_test(tc, Le_spac_inf);
  tcase_add_test(tc, Le_hash_inf);
  tcase_add_test(tc, Le_fzer_inf);
  tcase_add_test(tc, Le_mins_ng_inf);
  tcase_add_test(tc, Le_plus_ng_inf);
  tcase_add_test(tc, Le_spac_ng_inf);
  tcase_add_test(tc, Le_hash_ng_inf);
  tcase_add_test(tc, Le_fzer_ng_inf);
  tcase_add_test(tc, Le_width_nan);
  tcase_add_test(tc, Le_zrpc_nan);
  tcase_add_test(tc, Le_prec_nan);
  tcase_add_test(tc, Le_width_inf);
  tcase_add_test(tc, Le_zrpc_inf);
  tcase_add_test(tc, Le_prec_inf);
  tcase_add_test(tc, Le_width_ng_inf);
  tcase_add_test(tc, Le_zrpc_ng_inf);
  tcase_add_test(tc, Le_prec_ng_inf);
  tcase_add_test(tc, Le_width_prec_nan);
  tcase_add_test(tc, Le_width_prec_inf);
  tcase_add_test(tc, Le_width_prec_ng_inf);
  tcase_add_test(tc, Le_width_mins_nan);
  tcase_add_test(tc, Le_width_plus_nan);
  tcase_add_test(tc, Le_width_spac_nan);
  tcase_add_test(tc, Le_width_hash_nan);
  tcase_add_test(tc, Le_width_fzer_nan);
  tcase_add_test(tc, Le_width_mins_inf);
  tcase_add_test(tc, Le_width_plus_inf);
  tcase_add_test(tc, Le_width_spac_inf);
  tcase_add_test(tc, Le_width_hash_inf);
  tcase_add_test(tc, Le_width_fzer_inf);
  tcase_add_test(tc, Le_width_mins_ng_inf);
  tcase_add_test(tc, Le_width_plus_ng_inf);
  tcase_add_test(tc, Le_width_spac_ng_inf);
  tcase_add_test(tc, Le_width_hash_ng_inf);
  tcase_add_test(tc, Le_width_fzer_ng_inf);
  tcase_add_test(tc, Le_zrwth_plus_nan);
  tcase_add_test(tc, Le_zrwth_spac_nan);
  tcase_add_test(tc, Le_zrwth_hash_nan);
  tcase_add_test(tc, Le_zrwth_plus_inf);
  tcase_add_test(tc, Le_zrwth_spac_inf);
  tcase_add_test(tc, Le_zrwth_hash_inf);
  tcase_add_test(tc, Le_zrwth_plus_ng_inf);
  tcase_add_test(tc, Le_zrwth_spac_ng_inf);
  tcase_add_test(tc, Le_zrwth_hash_ng_inf);
  tcase_add_test(tc, Le_prec_mins_nan);
  tcase_add_test(tc, Le_prec_plus_nan);
  tcase_add_test(tc, Le_prec_spac_nan);
  tcase_add_test(tc, Le_prec_hash_nan);
  tcase_add_test(tc, Le_prec_fzer_nan);
  tcase_add_test(tc, Le_prec_mins_inf);
  tcase_add_test(tc, Le_prec_plus_inf);
  tcase_add_test(tc, Le_prec_spac_inf);
  tcase_add_test(tc, Le_prec_hash_inf);
  tcase_add_test(tc, Le_prec_fzer_inf);
  tcase_add_test(tc, Le_prec_mins_ng_inf);
  tcase_add_test(tc, Le_prec_plus_ng_inf);
  tcase_add_test(tc, Le_prec_spac_ng_inf);
  tcase_add_test(tc, Le_prec_hash_ng_inf);
  tcase_add_test(tc, Le_prec_fzer_ng_inf);
  tcase_add_test(tc, Le_zrpc_mins_nan);
  tcase_add_test(tc, Le_zrpc_plus_nan);
  tcase_add_test(tc, Le_zrpc_spac_nan);
  tcase_add_test(tc, Le_zrpc_hash_nan);
  tcase_add_test(tc, Le_zrpc_fzer_nan);
  tcase_add_test(tc, Le_zrpc_mins_inf);
  tcase_add_test(tc, Le_zrpc_plus_inf);
  tcase_add_test(tc, Le_zrpc_spac_inf);
  tcase_add_test(tc, Le_zrpc_hash_inf);
  tcase_add_test(tc, Le_zrpc_fzer_inf);
  tcase_add_test(tc, Le_zrpc_mins_ng_inf);
  tcase_add_test(tc, Le_zrpc_plus_ng_inf);
  tcase_add_test(tc, Le_zrpc_spac_ng_inf);
  tcase_add_test(tc, Le_zrpc_hash_ng_inf);
  tcase_add_test(tc, Le_zrpc_fzer_ng_inf);
  tcase_add_test(tc, Le_width_prec_mins_nan);
  tcase_add_test(tc, Le_width_prec_plus_nan);
  tcase_add_test(tc, Le_width_prec_spac_nan);
  tcase_add_test(tc, Le_width_prec_hash_nan);
  tcase_add_test(tc, Le_width_prec_fzer_nan);
  tcase_add_test(tc, Le_width_prec_mins_inf);
  tcase_add_test(tc, Le_width_prec_plus_inf);
  tcase_add_test(tc, Le_width_prec_spac_inf);
  tcase_add_test(tc, Le_width_prec_hash_inf);
  tcase_add_test(tc, Le_width_prec_fzer_inf);
  tcase_add_test(tc, Le_width_prec_mins_ng_inf);
  tcase_add_test(tc, Le_width_prec_plus_ng_inf);
  tcase_add_test(tc, Le_width_prec_spac_ng_inf);
  tcase_add_test(tc, Le_width_prec_hash_ng_inf);
  tcase_add_test(tc, Le_width_prec_fzer_ng_inf);
  tcase_add_test(tc, Le_zrwth_zrpc_plus_nan);
  tcase_add_test(tc, Le_zrwth_zrpc_spac_nan);
  tcase_add_test(tc, Le_zrwth_zrpc_hash_nan);
  tcase_add_test(tc, Le_zrwth_zrpc_plus_inf);
  tcase_add_test(tc, Le_zrwth_zrpc_spac_inf);
  tcase_add_test(tc, Le_zrwth_zrpc_hash_inf);
  tcase_add_test(tc, Le_zrwth_zrpc_plus_ng_inf);
  tcase_add_test(tc, Le_zrwth_zrpc_spac_ng_inf);
  tcase_add_test(tc, Le_zrwth_zrpc_hash_ng_inf);
  tcase_add_test(tc, Le_dynamic_prec_nan);
  tcase_add_test(tc, Le_dynamic_prec_inf);
  tcase_add_test(tc, Le_dynamic_prec_ng_inf);
  tcase_add_test(tc, Le_dynamic_width_nan);
  tcase_add_test(tc, Le_dynamic_width_inf);
  tcase_add_test(tc, Le_dynamic_width_ng_inf);
  tcase_add_test(tc, Le_dynamic_width_prec_nan);
  tcase_add_test(tc, Le_dynamic_width_prec_inf);
  tcase_add_test(tc, Le_dynamic_width_prec_ng_inf);
  tcase_add_test(tc, LE_mins_nan);
  tcase_add_test(tc, LE_plus_nan);
  tcase_add_test(tc, LE_spac_nan);
  tcase_add_test(tc, LE_hash_nan);
  tcase_add_test(tc, LE_fzer_nan);
  tcase_add_test(tc, LE_mins_inf);
  tcase_add_test(tc, LE_plus_inf);
  tcase_add_test(tc, LE_spac_inf);
  tcase_add_test(tc, LE_hash_inf);
  tcase_add_test(tc, LE_fzer_inf);
  tcase_add_test(tc, LE_mins_ng_inf);
  tcase_add_test(tc, LE_plus_ng_inf);
  tcase_add_test(tc, LE_spac_ng_inf);
  tcase_add_test(tc, LE_hash_ng_inf);
  tcase_add_test(tc, LE_fzer_ng_inf);
  tcase_add_test(tc, LE_width_nan);
  tcase_add_test(tc, LE_zrpc_nan);
  tcase_add_test(tc, LE_prec_nan);
  tcase_add_test(tc, LE_width_inf);
  tcase_add_test(tc, LE_zrpc_inf);
  tcase_add_test(tc, LE_prec_inf);
  tcase_add_test(tc, LE_width_ng_inf);
  tcase_add_test(tc, LE_zrpc_ng_inf);
  tcase_add_test(tc, LE_prec_ng_inf);
  tcase_add_test(tc, LE_width_prec_nan);
  tcase_add_test(tc, LE_width_prec_inf);
  tcase_add_test(tc, LE_width_prec_ng_inf);
  tcase_add_test(tc, LE_width_mins_nan);
  tcase_add_test(tc, LE_width_plus_nan);
  tcase_add_test(tc, LE_width_spac_nan);
  tcase_add_test(tc, LE_width_hash_nan);
  tcase_add_test(tc, LE_width_fzer_nan);
  tcase_add_test(tc, LE_width_mins_inf);
  tcase_add_test(tc, LE_width_plus_inf);
  tcase_add_test(tc, LE_width_spac_inf);
  tcase_add_test(tc, LE_width_hash_inf);
  tcase_add_test(tc, LE_width_fzer_inf);
  tcase_add_test(tc, LE_width_mins_ng_inf);
  tcase_add_test(tc, LE_width_plus_ng_inf);
  tcase_add_test(tc, LE_width_spac_ng_inf);
  tcase_add_test(tc, LE_width_hash_ng_inf);
  tcase_add_test(tc, LE_width_fzer_ng_inf);
  tcase_add_test(tc, LE_zrwth_plus_nan);
  tcase_add_test(tc, LE_zrwth_spac_nan);
  tcase_add_test(tc, LE_zrwth_hash_nan);
  tcase_add_test(tc, LE_zrwth_plus_inf);
  tcase_add_test(tc, LE_zrwth_spac_inf);
  tcase_add_test(tc, LE_zrwth_hash_inf);
  tcase_add_test(tc, LE_zrwth_plus_ng_inf);
  tcase_add_test(tc, LE_zrwth_spac_ng_inf);
  tcase_add_test(tc, LE_zrwth_hash_ng_inf);
  tcase_add_test(tc, LE_prec_mins_nan);
  tcase_add_test(tc, LE_prec_plus_nan);
  tcase_add_test(tc, LE_prec_spac_nan);
  tcase_add_test(tc, LE_prec_hash_nan);
  tcase_add_test(tc, LE_prec_fzer_nan);
  tcase_add_test(tc, LE_prec_mins_inf);
  tcase_add_test(tc, LE_prec_plus_inf);
  tcase_add_test(tc, LE_prec_spac_inf);
  tcase_add_test(tc, LE_prec_hash_inf);
  tcase_add_test(tc, LE_prec_fzer_inf);
  tcase_add_test(tc, LE_prec_mins_ng_inf);
  tcase_add_test(tc, LE_prec_plus_ng_inf);
  tcase_add_test(tc, LE_prec_spac_ng_inf);
  tcase_add_test(tc, LE_prec_hash_ng_inf);
  tcase_add_test(tc, LE_prec_fzer_ng_inf);
  tcase_add_test(tc, LE_zrpc_mins_nan);
  tcase_add_test(tc, LE_zrpc_plus_nan);
  tcase_add_test(tc, LE_zrpc_spac_nan);
  tcase_add_test(tc, LE_zrpc_hash_nan);
  tcase_add_test(tc, LE_zrpc_fzer_nan);
  tcase_add_test(tc, LE_zrpc_mins_inf);
  tcase_add_test(tc, LE_zrpc_plus_inf);
  tcase_add_test(tc, LE_zrpc_spac_inf);
  tcase_add_test(tc, LE_zrpc_hash_inf);
  tcase_add_test(tc, LE_zrpc_fzer_inf);
  tcase_add_test(tc, LE_zrpc_mins_ng_inf);
  tcase_add_test(tc, LE_zrpc_plus_ng_inf);
  tcase_add_test(tc, LE_zrpc_spac_ng_inf);
  tcase_add_test(tc, LE_zrpc_hash_ng_inf);
  tcase_add_test(tc, LE_zrpc_fzer_ng_inf);
  tcase_add_test(tc, LE_width_prec_mins_nan);
  tcase_add_test(tc, LE_width_prec_plus_nan);
  tcase_add_test(tc, LE_width_prec_spac_nan);
  tcase_add_test(tc, LE_width_prec_hash_nan);
  tcase_add_test(tc, LE_width_prec_fzer_nan);
  tcase_add_test(tc, LE_width_prec_mins_inf);
  tcase_add_test(tc, LE_width_prec_plus_inf);
  tcase_add_test(tc, LE_width_prec_spac_inf);
  tcase_add_test(tc, LE_width_prec_hash_inf);
  tcase_add_test(tc, LE_width_prec_fzer_inf);
  tcase_add_test(tc, LE_width_prec_mins_ng_inf);
  tcase_add_test(tc, LE_width_prec_plus_ng_inf);
  tcase_add_test(tc, LE_width_prec_spac_ng_inf);
  tcase_add_test(tc, LE_width_prec_hash_ng_inf);
  tcase_add_test(tc, LE_width_prec_fzer_ng_inf);
  tcase_add_test(tc, LE_zrwth_zrpc_plus_nan);
  tcase_add_test(tc, LE_zrwth_zrpc_spac_nan);
  tcase_add_test(tc, LE_zrwth_zrpc_hash_nan);
  tcase_add_test(tc, LE_zrwth_zrpc_plus_inf);
  tcase_add_test(tc, LE_zrwth_zrpc_spac_inf);
  tcase_add_test(tc, LE_zrwth_zrpc_hash_inf);
  tcase_add_test(tc, LE_zrwth_zrpc_plus_ng_inf);
  tcase_add_test(tc, LE_zrwth_zrpc_spac_ng_inf);
  tcase_add_test(tc, LE_zrwth_zrpc_hash_ng_inf);
  tcase_add_test(tc, LE_dynamic_prec_nan);
  tcase_add_test(tc, LE_dynamic_prec_inf);
  tcase_add_test(tc, LE_dynamic_prec_ng_inf);
  tcase_add_test(tc, LE_dynamic_width_nan);
  tcase_add_test(tc, LE_dynamic_width_inf);
  tcase_add_test(tc, LE_dynamic_width_ng_inf);
  tcase_add_test(tc, LE_dynamic_width_prec_nan);
  tcase_add_test(tc, LE_dynamic_width_prec_inf);
  tcase_add_test(tc, LE_dynamic_width_prec_ng_inf);
  tcase_add_test(tc, Lf_mins_nan);
  tcase_add_test(tc, Lf_plus_nan);
  tcase_add_test(tc, Lf_spac_nan);
  tcase_add_test(tc, Lf_hash_nan);
  tcase_add_test(tc, Lf_fzer_nan);
  tcase_add_test(tc, Lf_mins_inf);
  tcase_add_test(tc, Lf_plus_inf);
  tcase_add_test(tc, Lf_spac_inf);
  tcase_add_test(tc, Lf_hash_inf);
  tcase_add_test(tc, Lf_fzer_inf);
  tcase_add_test(tc, Lf_mins_ng_inf);
  tcase_add_test(tc, Lf_plus_ng_inf);
  tcase_add_test(tc, Lf_spac_ng_inf);
  tcase_add_test(tc, Lf_hash_ng_inf);
  tcase_add_test(tc, Lf_fzer_ng_inf);
  tcase_add_test(tc, Lf_width_nan);
  tcase_add_test(tc, Lf_zrpc_nan);
  tcase_add_test(tc, Lf_prec_nan);
  tcase_add_test(tc, Lf_width_inf);
  tcase_add_test(tc, Lf_zrpc_inf);
  tcase_add_test(tc, Lf_prec_inf);
  tcase_add_test(tc, Lf_width_ng_inf);
  tcase_add_test(tc, Lf_zrpc_ng_inf);
  tcase_add_test(tc, Lf_prec_ng_inf);
  tcase_add_test(tc, Lf_width_prec_nan);
  tcase_add_test(tc, Lf_width_prec_inf);
  tcase_add_test(tc, Lf_width_prec_ng_inf);
  tcase_add_test(tc, Lf_width_mins_nan);
  tcase_add_test(tc, Lf_width_plus_nan);
  tcase_add_test(tc, Lf_width_spac_nan);
  tcase_add_test(tc, Lf_width_hash_nan);
  tcase_add_test(tc, Lf_width_fzer_nan);
  tcase_add_test(tc, Lf_width_mins_inf);
  tcase_add_test(tc, Lf_width_plus_inf);
  tcase_add_test(tc, Lf_width_spac_inf);
  tcase_add_test(tc, Lf_width_hash_inf);
  tcase_add_test(tc, Lf_width_fzer_inf);
  tcase_add_test(tc, Lf_width_mins_ng_inf);
  tcase_add_test(tc, Lf_width_plus_ng_inf);
  tcase_add_test(tc, Lf_width_spac_ng_inf);
  tcase_add_test(tc, Lf_width_hash_ng_inf);
  tcase_add_test(tc, Lf_width_fzer_ng_inf);
  tcase_add_test(tc, Lf_zrwth_plus_nan);
  tcase_add_test(tc, Lf_zrwth_spac_nan);
  tcase_add_test(tc, Lf_zrwth_hash_nan);
  tcase_add_test(tc, Lf_zrwth_plus_inf);
  tcase_add_test(tc, Lf_zrwth_spac_inf);
  tcase_add_test(tc, Lf_zrwth_hash_inf);
  tcase_add_test(tc, Lf_zrwth_plus_ng_inf);
  tcase_add_test(tc, Lf_zrwth_spac_ng_inf);
  tcase_add_test(tc, Lf_zrwth_hash_ng_inf);
  tcase_add_test(tc, Lf_prec_mins_nan);
  tcase_add_test(tc, Lf_prec_plus_nan);
  tcase_add_test(tc, Lf_prec_spac_nan);
  tcase_add_test(tc, Lf_prec_hash_nan);
  tcase_add_test(tc, Lf_prec_fzer_nan);
  tcase_add_test(tc, Lf_prec_mins_inf);
  tcase_add_test(tc, Lf_prec_plus_inf);
  tcase_add_test(tc, Lf_prec_spac_inf);
  tcase_add_test(tc, Lf_prec_hash_inf);
  tcase_add_test(tc, Lf_prec_fzer_inf);
  tcase_add_test(tc, Lf_prec_mins_ng_inf);
  tcase_add_test(tc, Lf_prec_plus_ng_inf);
  tcase_add_test(tc, Lf_prec_spac_ng_inf);
  tcase_add_test(tc, Lf_prec_hash_ng_inf);
  tcase_add_test(tc, Lf_prec_fzer_ng_inf);
  tcase_add_test(tc, Lf_zrpc_mins_nan);
  tcase_add_test(tc, Lf_zrpc_plus_nan);
  tcase_add_test(tc, Lf_zrpc_spac_nan);
  tcase_add_test(tc, Lf_zrpc_hash_nan);
  tcase_add_test(tc, Lf_zrpc_fzer_nan);
  tcase_add_test(tc, Lf_zrpc_mins_inf);
  tcase_add_test(tc, Lf_zrpc_plus_inf);
  tcase_add_test(tc, Lf_zrpc_spac_inf);
  tcase_add_test(tc, Lf_zrpc_hash_inf);
  tcase_add_test(tc, Lf_zrpc_fzer_inf);
  tcase_add_test(tc, Lf_zrpc_mins_ng_inf);
  tcase_add_test(tc, Lf_zrpc_plus_ng_inf);
  tcase_add_test(tc, Lf_zrpc_spac_ng_inf);
  tcase_add_test(tc, Lf_zrpc_hash_ng_inf);
  tcase_add_test(tc, Lf_zrpc_fzer_ng_inf);
  tcase_add_test(tc, Lf_width_prec_mins_nan);
  tcase_add_test(tc, Lf_width_prec_plus_nan);
  tcase_add_test(tc, Lf_width_prec_spac_nan);
  tcase_add_test(tc, Lf_width_prec_hash_nan);
  tcase_add_test(tc, Lf_width_prec_fzer_nan);
  tcase_add_test(tc, Lf_width_prec_mins_inf);
  tcase_add_test(tc, Lf_width_prec_plus_inf);
  tcase_add_test(tc, Lf_width_prec_spac_inf);
  tcase_add_test(tc, Lf_width_prec_hash_inf);
  tcase_add_test(tc, Lf_width_prec_fzer_inf);
  tcase_add_test(tc, Lf_width_prec_mins_ng_inf);
  tcase_add_test(tc, Lf_width_prec_plus_ng_inf);
  tcase_add_test(tc, Lf_width_prec_spac_ng_inf);
  tcase_add_test(tc, Lf_width_prec_hash_ng_inf);
  tcase_add_test(tc, Lf_width_prec_fzer_ng_inf);
  tcase_add_test(tc, Lf_zrwth_zrpc_plus_nan);
  tcase_add_test(tc, Lf_zrwth_zrpc_spac_nan);
  tcase_add_test(tc, Lf_zrwth_zrpc_hash_nan);
  tcase_add_test(tc, Lf_zrwth_zrpc_plus_inf);
  tcase_add_test(tc, Lf_zrwth_zrpc_spac_inf);
  tcase_add_test(tc, Lf_zrwth_zrpc_hash_inf);
  tcase_add_test(tc, Lf_zrwth_zrpc_plus_ng_inf);
  tcase_add_test(tc, Lf_zrwth_zrpc_spac_ng_inf);
  tcase_add_test(tc, Lf_zrwth_zrpc_hash_ng_inf);
  tcase_add_test(tc, Lf_dynamic_prec_nan);
  tcase_add_test(tc, Lf_dynamic_prec_inf);
  tcase_add_test(tc, Lf_dynamic_prec_ng_inf);
  tcase_add_test(tc, Lf_dynamic_width_nan);
  tcase_add_test(tc, Lf_dynamic_width_inf);
  tcase_add_test(tc, Lf_dynamic_width_ng_inf);
  tcase_add_test(tc, Lf_dynamic_width_prec_nan);
  tcase_add_test(tc, Lf_dynamic_width_prec_inf);
  tcase_add_test(tc, Lf_dynamic_width_prec_ng_inf);
  tcase_add_test(tc, Lg_mins_nan);
  tcase_add_test(tc, Lg_plus_nan);
  tcase_add_test(tc, Lg_spac_nan);
  tcase_add_test(tc, Lg_hash_nan);
  tcase_add_test(tc, Lg_fzer_nan);
  tcase_add_test(tc, Lg_mins_inf);
  tcase_add_test(tc, Lg_plus_inf);
  tcase_add_test(tc, Lg_spac_inf);
  tcase_add_test(tc, Lg_hash_inf);
  tcase_add_test(tc, Lg_fzer_inf);
  tcase_add_test(tc, Lg_mins_ng_inf);
  tcase_add_test(tc, Lg_plus_ng_inf);
  tcase_add_test(tc, Lg_spac_ng_inf);
  tcase_add_test(tc, Lg_hash_ng_inf);
  tcase_add_test(tc, Lg_fzer_ng_inf);
  tcase_add_test(tc, Lg_width_nan);
  tcase_add_test(tc, Lg_zrpc_nan);
  tcase_add_test(tc, Lg_prec_nan);
  tcase_add_test(tc, Lg_width_inf);
  tcase_add_test(tc, Lg_zrpc_inf);
  tcase_add_test(tc, Lg_prec_inf);
  tcase_add_test(tc, Lg_width_ng_inf);
  tcase_add_test(tc, Lg_zrpc_ng_inf);
  tcase_add_test(tc, Lg_prec_ng_inf);
  tcase_add_test(tc, Lg_width_prec_nan);
  tcase_add_test(tc, Lg_width_prec_inf);
  tcase_add_test(tc, Lg_width_prec_ng_inf);
  tcase_add_test(tc, Lg_width_mins_nan);
  tcase_add_test(tc, Lg_width_plus_nan);
  tcase_add_test(tc, Lg_width_spac_nan);
  tcase_add_test(tc, Lg_width_hash_nan);
  tcase_add_test(tc, Lg_width_fzer_nan);
  tcase_add_test(tc, Lg_width_mins_inf);
  tcase_add_test(tc, Lg_width_plus_inf);
  tcase_add_test(tc, Lg_width_spac_inf);
  tcase_add_test(tc, Lg_width_hash_inf);
  tcase_add_test(tc, Lg_width_fzer_inf);
  tcase_add_test(tc, Lg_width_mins_ng_inf);
  tcase_add_test(tc, Lg_width_plus_ng_inf);
  tcase_add_test(tc, Lg_width_spac_ng_inf);
  tcase_add_test(tc, Lg_width_hash_ng_inf);
  tcase_add_test(tc, Lg_width_fzer_ng_inf);
  tcase_add_test(tc, Lg_zrwth_plus_nan);
  tcase_add_test(tc, Lg_zrwth_spac_nan);
  tcase_add_test(tc, Lg_zrwth_hash_nan);
  tcase_add_test(tc, Lg_zrwth_plus_inf);
  tcase_add_test(tc, Lg_zrwth_spac_inf);
  tcase_add_test(tc, Lg_zrwth_hash_inf);
  tcase_add_test(tc, Lg_zrwth_plus_ng_inf);
  tcase_add_test(tc, Lg_zrwth_spac_ng_inf);
  tcase_add_test(tc, Lg_zrwth_hash_ng_inf);
  tcase_add_test(tc, Lg_prec_mins_nan);
  tcase_add_test(tc, Lg_prec_plus_nan);
  tcase_add_test(tc, Lg_prec_spac_nan);
  tcase_add_test(tc, Lg_prec_hash_nan);
  tcase_add_test(tc, Lg_prec_fzer_nan);
  tcase_add_test(tc, Lg_prec_mins_inf);
  tcase_add_test(tc, Lg_prec_plus_inf);
  tcase_add_test(tc, Lg_prec_spac_inf);
  tcase_add_test(tc, Lg_prec_hash_inf);
  tcase_add_test(tc, Lg_prec_fzer_inf);
  tcase_add_test(tc, Lg_prec_mins_ng_inf);
  tcase_add_test(tc, Lg_prec_plus_ng_inf);
  tcase_add_test(tc, Lg_prec_spac_ng_inf);
  tcase_add_test(tc, Lg_prec_hash_ng_inf);
  tcase_add_test(tc, Lg_prec_fzer_ng_inf);
  tcase_add_test(tc, Lg_zrpc_mins_nan);
  tcase_add_test(tc, Lg_zrpc_plus_nan);
  tcase_add_test(tc, Lg_zrpc_spac_nan);
  tcase_add_test(tc, Lg_zrpc_hash_nan);
  tcase_add_test(tc, Lg_zrpc_fzer_nan);
  tcase_add_test(tc, Lg_zrpc_mins_inf);
  tcase_add_test(tc, Lg_zrpc_plus_inf);
  tcase_add_test(tc, Lg_zrpc_spac_inf);
  tcase_add_test(tc, Lg_zrpc_hash_inf);
  tcase_add_test(tc, Lg_zrpc_fzer_inf);
  tcase_add_test(tc, Lg_zrpc_mins_ng_inf);
  tcase_add_test(tc, Lg_zrpc_plus_ng_inf);
  tcase_add_test(tc, Lg_zrpc_spac_ng_inf);
  tcase_add_test(tc, Lg_zrpc_hash_ng_inf);
  tcase_add_test(tc, Lg_zrpc_fzer_ng_inf);
  tcase_add_test(tc, Lg_width_prec_mins_nan);
  tcase_add_test(tc, Lg_width_prec_plus_nan);
  tcase_add_test(tc, Lg_width_prec_spac_nan);
  tcase_add_test(tc, Lg_width_prec_hash_nan);
  tcase_add_test(tc, Lg_width_prec_fzer_nan);
  tcase_add_test(tc, Lg_width_prec_mins_inf);
  tcase_add_test(tc, Lg_width_prec_plus_inf);
  tcase_add_test(tc, Lg_width_prec_spac_inf);
  tcase_add_test(tc, Lg_width_prec_hash_inf);
  tcase_add_test(tc, Lg_width_prec_fzer_inf);
  tcase_add_test(tc, Lg_width_prec_mins_ng_inf);
  tcase_add_test(tc, Lg_width_prec_plus_ng_inf);
  tcase_add_test(tc, Lg_width_prec_spac_ng_inf);
  tcase_add_test(tc, Lg_width_prec_hash_ng_inf);
  tcase_add_test(tc, Lg_width_prec_fzer_ng_inf);
  tcase_add_test(tc, Lg_zrwth_zrpc_plus_nan);
  tcase_add_test(tc, Lg_zrwth_zrpc_spac_nan);
  tcase_add_test(tc, Lg_zrwth_zrpc_hash_nan);
  tcase_add_test(tc, Lg_zrwth_zrpc_plus_inf);
  tcase_add_test(tc, Lg_zrwth_zrpc_spac_inf);
  tcase_add_test(tc, Lg_zrwth_zrpc_hash_inf);
  tcase_add_test(tc, Lg_zrwth_zrpc_plus_ng_inf);
  tcase_add_test(tc, Lg_zrwth_zrpc_spac_ng_inf);
  tcase_add_test(tc, Lg_zrwth_zrpc_hash_ng_inf);
  tcase_add_test(tc, Lg_dynamic_prec_nan);
  tcase_add_test(tc, Lg_dynamic_prec_inf);
  tcase_add_test(tc, Lg_dynamic_prec_ng_inf);
  tcase_add_test(tc, Lg_dynamic_width_nan);
  tcase_add_test(tc, Lg_dynamic_width_inf);
  tcase_add_test(tc, Lg_dynamic_width_ng_inf);
  tcase_add_test(tc, Lg_dynamic_width_prec_nan);
  tcase_add_test(tc, Lg_dynamic_width_prec_inf);
  tcase_add_test(tc, Lg_dynamic_width_prec_ng_inf);
  tcase_add_test(tc, LG_mins_nan);
  tcase_add_test(tc, LG_plus_nan);
  tcase_add_test(tc, LG_spac_nan);
  tcase_add_test(tc, LG_hash_nan);
  tcase_add_test(tc, LG_fzer_nan);
  tcase_add_test(tc, LG_mins_inf);
  tcase_add_test(tc, LG_plus_inf);
  tcase_add_test(tc, LG_spac_inf);
  tcase_add_test(tc, LG_hash_inf);
  tcase_add_test(tc, LG_fzer_inf);
  tcase_add_test(tc, LG_mins_ng_inf);
  tcase_add_test(tc, LG_plus_ng_inf);
  tcase_add_test(tc, LG_spac_ng_inf);
  tcase_add_test(tc, LG_hash_ng_inf);
  tcase_add_test(tc, LG_fzer_ng_inf);
  tcase_add_test(tc, LG_width_nan);
  tcase_add_test(tc, LG_zrpc_nan);
  tcase_add_test(tc, LG_prec_nan);
  tcase_add_test(tc, LG_width_inf);
  tcase_add_test(tc, LG_zrpc_inf);
  tcase_add_test(tc, LG_prec_inf);
  tcase_add_test(tc, LG_width_ng_inf);
  tcase_add_test(tc, LG_zrpc_ng_inf);
  tcase_add_test(tc, LG_prec_ng_inf);
  tcase_add_test(tc, LG_width_prec_nan);
  tcase_add_test(tc, LG_width_prec_inf);
  tcase_add_test(tc, LG_width_prec_ng_inf);
  tcase_add_test(tc, LG_width_mins_nan);
  tcase_add_test(tc, LG_width_plus_nan);
  tcase_add_test(tc, LG_width_spac_nan);
  tcase_add_test(tc, LG_width_hash_nan);
  tcase_add_test(tc, LG_width_fzer_nan);
  tcase_add_test(tc, LG_width_mins_inf);
  tcase_add_test(tc, LG_width_plus_inf);
  tcase_add_test(tc, LG_width_spac_inf);
  tcase_add_test(tc, LG_width_hash_inf);
  tcase_add_test(tc, LG_width_fzer_inf);
  tcase_add_test(tc, LG_width_mins_ng_inf);
  tcase_add_test(tc, LG_width_plus_ng_inf);
  tcase_add_test(tc, LG_width_spac_ng_inf);
  tcase_add_test(tc, LG_width_hash_ng_inf);
  tcase_add_test(tc, LG_width_fzer_ng_inf);
  tcase_add_test(tc, LG_zrwth_plus_nan);
  tcase_add_test(tc, LG_zrwth_spac_nan);
  tcase_add_test(tc, LG_zrwth_hash_nan);
  tcase_add_test(tc, LG_zrwth_plus_inf);
  tcase_add_test(tc, LG_zrwth_spac_inf);
  tcase_add_test(tc, LG_zrwth_hash_inf);
  tcase_add_test(tc, LG_zrwth_plus_ng_inf);
  tcase_add_test(tc, LG_zrwth_spac_ng_inf);
  tcase_add_test(tc, LG_zrwth_hash_ng_inf);
  tcase_add_test(tc, LG_prec_mins_nan);
  tcase_add_test(tc, LG_prec_plus_nan);
  tcase_add_test(tc, LG_prec_spac_nan);
  tcase_add_test(tc, LG_prec_hash_nan);
  tcase_add_test(tc, LG_prec_fzer_nan);
  tcase_add_test(tc, LG_prec_mins_inf);
  tcase_add_test(tc, LG_prec_plus_inf);
  tcase_add_test(tc, LG_prec_spac_inf);
  tcase_add_test(tc, LG_prec_hash_inf);
  tcase_add_test(tc, LG_prec_fzer_inf);
  tcase_add_test(tc, LG_prec_mins_ng_inf);
  tcase_add_test(tc, LG_prec_plus_ng_inf);
  tcase_add_test(tc, LG_prec_spac_ng_inf);
  tcase_add_test(tc, LG_prec_hash_ng_inf);
  tcase_add_test(tc, LG_prec_fzer_ng_inf);
  tcase_add_test(tc, LG_zrpc_mins_nan);
  tcase_add_test(tc, LG_zrpc_plus_nan);
  tcase_add_test(tc, LG_zrpc_spac_nan);
  tcase_add_test(tc, LG_zrpc_hash_nan);
  tcase_add_test(tc, LG_zrpc_fzer_nan);
  tcase_add_test(tc, LG_zrpc_mins_inf);
  tcase_add_test(tc, LG_zrpc_plus_inf);
  tcase_add_test(tc, LG_zrpc_spac_inf);
  tcase_add_test(tc, LG_zrpc_hash_inf);
  tcase_add_test(tc, LG_zrpc_fzer_inf);
  tcase_add_test(tc, LG_zrpc_mins_ng_inf);
  tcase_add_test(tc, LG_zrpc_plus_ng_inf);
  tcase_add_test(tc, LG_zrpc_spac_ng_inf);
  tcase_add_test(tc, LG_zrpc_hash_ng_inf);
  tcase_add_test(tc, LG_zrpc_fzer_ng_inf);
  tcase_add_test(tc, LG_width_prec_mins_nan);
  tcase_add_test(tc, LG_width_prec_plus_nan);
  tcase_add_test(tc, LG_width_prec_spac_nan);
  tcase_add_test(tc, LG_width_prec_hash_nan);
  tcase_add_test(tc, LG_width_prec_fzer_nan);
  tcase_add_test(tc, LG_width_prec_mins_inf);
  tcase_add_test(tc, LG_width_prec_plus_inf);
  tcase_add_test(tc, LG_width_prec_spac_inf);
  tcase_add_test(tc, LG_width_prec_hash_inf);
  tcase_add_test(tc, LG_width_prec_fzer_inf);
  tcase_add_test(tc, LG_width_prec_mins_ng_inf);
  tcase_add_test(tc, LG_width_prec_plus_ng_inf);
  tcase_add_test(tc, LG_width_prec_spac_ng_inf);
  tcase_add_test(tc, LG_width_prec_hash_ng_inf);
  tcase_add_test(tc, LG_width_prec_fzer_ng_inf);
  tcase_add_test(tc, LG_zrwth_zrpc_plus_nan);
  tcase_add_test(tc, LG_zrwth_zrpc_spac_nan);
  tcase_add_test(tc, LG_zrwth_zrpc_hash_nan);
  tcase_add_test(tc, LG_zrwth_zrpc_plus_inf);
  tcase_add_test(tc, LG_zrwth_zrpc_spac_inf);
  tcase_add_test(tc, LG_zrwth_zrpc_hash_inf);
  tcase_add_test(tc, LG_zrwth_zrpc_plus_ng_inf);
  tcase_add_test(tc, LG_zrwth_zrpc_spac_ng_inf);
  tcase_add_test(tc, LG_zrwth_zrpc_hash_ng_inf);
  tcase_add_test(tc, LG_dynamic_prec_nan);
  tcase_add_test(tc, LG_dynamic_prec_inf);
  tcase_add_test(tc, LG_dynamic_prec_ng_inf);
  tcase_add_test(tc, LG_dynamic_width_nan);
  tcase_add_test(tc, LG_dynamic_width_inf);
  tcase_add_test(tc, LG_dynamic_width_ng_inf);
  tcase_add_test(tc, LG_dynamic_width_prec_nan);
  tcase_add_test(tc, LG_dynamic_width_prec_inf);
  tcase_add_test(tc, LG_dynamic_width_prec_ng_inf);
  tcase_add_test(tc, e_mins_zero);
  tcase_add_test(tc, e_plus_zero);
  tcase_add_test(tc, e_spac_zero);
  tcase_add_test(tc, e_hash_zero);
  tcase_add_test(tc, e_fzer_zero);
  tcase_add_test(tc, e_width_zero);
  tcase_add_test(tc, e_zrpc_zero);
  tcase_add_test(tc, e_prec_zero);
  tcase_add_test(tc, e_width_prec_zero);
  tcase_add_test(tc, e_width_mins_zero);
  tcase_add_test(tc, e_width_plus_zero);
  tcase_add_test(tc, e_width_spac_zero);
  tcase_add_test(tc, e_width_hash_zero);
  tcase_add_test(tc, e_width_fzer_zero);
  tcase_add_test(tc, e_zrwth_plus_zero);
  tcase_add_test(tc, e_zrwth_spac_zero);
  tcase_add_test(tc, e_zrwth_hash_zero);
  tcase_add_test(tc, e_prec_mins_zero);
  tcase_add_test(tc, e_prec_plus_zero);
  tcase_add_test(tc, e_prec_spac_zero);
  tcase_add_test(tc, e_prec_hash_zero);
  tcase_add_test(tc, e_prec_fzer_zero);
  tcase_add_test(tc, e_zrpc_mins_zero);
  tcase_add_test(tc, e_zrpc_plus_zero);
  tcase_add_test(tc, e_zrpc_spac_zero);
  tcase_add_test(tc, e_zrpc_hash_zero);
  tcase_add_test(tc, e_zrpc_fzer_zero);
  tcase_add_test(tc, e_width_prec_mins_zero);
  tcase_add_test(tc, e_width_prec_plus_zero);
  tcase_add_test(tc, e_width_prec_spac_zero);
  tcase_add_test(tc, e_width_prec_hash_zero);
  tcase_add_test(tc, e_width_prec_fzer_zero);
  tcase_add_test(tc, e_zrwth_zrpc_plus_zero);
  tcase_add_test(tc, e_zrwth_zrpc_spac_zero);
  tcase_add_test(tc, e_zrwth_zrpc_hash_zero);
  tcase_add_test(tc, e_dynamic_width_zero);
  tcase_add_test(tc, e_dynamic_prec_zero);
  tcase_add_test(tc, e_dynamic_width_prec_zero);
  tcase_add_test(tc, E_mins_zero);
  tcase_add_test(tc, E_plus_zero);
  tcase_add_test(tc, E_spac_zero);
  tcase_add_test(tc, E_hash_zero);
  tcase_add_test(tc, E_fzer_zero);
  tcase_add_test(tc, E_width_zero);
  tcase_add_test(tc, E_zrpc_zero);
  tcase_add_test(tc, E_prec_zero);
  tcase_add_test(tc, E_width_prec_zero);
  tcase_add_test(tc, E_width_mins_zero);
  tcase_add_test(tc, E_width_plus_zero);
  tcase_add_test(tc, E_width_spac_zero);
  tcase_add_test(tc, E_width_hash_zero);
  tcase_add_test(tc, E_width_fzer_zero);
  tcase_add_test(tc, E_zrwth_plus_zero);
  tcase_add_test(tc, E_zrwth_spac_zero);
  tcase_add_test(tc, E_zrwth_hash_zero);
  tcase_add_test(tc, E_prec_mins_zero);
  tcase_add_test(tc, E_prec_plus_zero);
  tcase_add_test(tc, E_prec_spac_zero);
  tcase_add_test(tc, E_prec_hash_zero);
  tcase_add_test(tc, E_prec_fzer_zero);
  tcase_add_test(tc, E_zrpc_mins_zero);
  tcase_add_test(tc, E_zrpc_plus_zero);
  tcase_add_test(tc, E_zrpc_spac_zero);
  tcase_add_test(tc, E_zrpc_hash_zero);
  tcase_add_test(tc, E_zrpc_fzer_zero);
  tcase_add_test(tc, E_width_prec_mins_zero);
  tcase_add_test(tc, E_width_prec_plus_zero);
  tcase_add_test(tc, E_width_prec_spac_zero);
  tcase_add_test(tc, E_width_prec_hash_zero);
  tcase_add_test(tc, E_width_prec_fzer_zero);
  tcase_add_test(tc, E_zrwth_zrpc_plus_zero);
  tcase_add_test(tc, E_zrwth_zrpc_spac_zero);
  tcase_add_test(tc, E_zrwth_zrpc_hash_zero);
  tcase_add_test(tc, E_dynamic_width_zero);
  tcase_add_test(tc, E_dynamic_prec_zero);
  tcase_add_test(tc, E_dynamic_width_prec_zero);
  tcase_add_test(tc, f_mins_zero);
  tcase_add_test(tc, f_plus_zero);
  tcase_add_test(tc, f_spac_zero);
  tcase_add_test(tc, f_hash_zero);
  tcase_add_test(tc, f_fzer_zero);
  tcase_add_test(tc, f_width_zero);
  tcase_add_test(tc, f_zrpc_zero);
  tcase_add_test(tc, f_prec_zero);
  tcase_add_test(tc, f_width_prec_zero);
  tcase_add_test(tc, f_width_mins_zero);
  tcase_add_test(tc, f_width_plus_zero);
  tcase_add_test(tc, f_width_spac_zero);
  tcase_add_test(tc, f_width_hash_zero);
  tcase_add_test(tc, f_width_fzer_zero);
  tcase_add_test(tc, f_zrwth_plus_zero);
  tcase_add_test(tc, f_zrwth_spac_zero);
  tcase_add_test(tc, f_zrwth_hash_zero);
  tcase_add_test(tc, f_prec_mins_zero);
  tcase_add_test(tc, f_prec_plus_zero);
  tcase_add_test(tc, f_prec_spac_zero);
  tcase_add_test(tc, f_prec_hash_zero);
  tcase_add_test(tc, f_prec_fzer_zero);
  tcase_add_test(tc, f_zrpc_mins_zero);
  tcase_add_test(tc, f_zrpc_plus_zero);
  tcase_add_test(tc, f_zrpc_spac_zero);
  tcase_add_test(tc, f_zrpc_hash_zero);
  tcase_add_test(tc, f_zrpc_fzer_zero);
  tcase_add_test(tc, f_width_prec_mins_zero);
  tcase_add_test(tc, f_width_prec_plus_zero);
  tcase_add_test(tc, f_width_prec_spac_zero);
  tcase_add_test(tc, f_width_prec_hash_zero);
  tcase_add_test(tc, f_width_prec_fzer_zero);
  tcase_add_test(tc, f_zrwth_zrpc_plus_zero);
  tcase_add_test(tc, f_zrwth_zrpc_spac_zero);
  tcase_add_test(tc, f_zrwth_zrpc_hash_zero);
  tcase_add_test(tc, f_dynamic_width_zero);
  tcase_add_test(tc, f_dynamic_prec_zero);
  tcase_add_test(tc, f_dynamic_width_prec_zero);
  tcase_add_test(tc, g_mins_zero);
  tcase_add_test(tc, g_plus_zero);
  tcase_add_test(tc, g_spac_zero);
  tcase_add_test(tc, g_hash_zero);
  tcase_add_test(tc, g_fzer_zero);
  tcase_add_test(tc, g_width_zero);
  tcase_add_test(tc, g_zrpc_zero);
  tcase_add_test(tc, g_prec_zero);
  tcase_add_test(tc, g_width_prec_zero);
  tcase_add_test(tc, g_width_mins_zero);
  tcase_add_test(tc, g_width_plus_zero);
  tcase_add_test(tc, g_width_spac_zero);
  tcase_add_test(tc, g_width_hash_zero);
  tcase_add_test(tc, g_width_fzer_zero);
  tcase_add_test(tc, g_zrwth_plus_zero);
  tcase_add_test(tc, g_zrwth_spac_zero);
  tcase_add_test(tc, g_zrwth_hash_zero);
  tcase_add_test(tc, g_prec_mins_zero);
  tcase_add_test(tc, g_prec_plus_zero);
  tcase_add_test(tc, g_prec_spac_zero);
  tcase_add_test(tc, g_prec_hash_zero);
  tcase_add_test(tc, g_prec_fzer_zero);
  tcase_add_test(tc, g_zrpc_mins_zero);
  tcase_add_test(tc, g_zrpc_plus_zero);
  tcase_add_test(tc, g_zrpc_spac_zero);
  tcase_add_test(tc, g_zrpc_hash_zero);
  tcase_add_test(tc, g_zrpc_fzer_zero);
  tcase_add_test(tc, g_width_prec_mins_zero);
  tcase_add_test(tc, g_width_prec_plus_zero);
  tcase_add_test(tc, g_width_prec_spac_zero);
  tcase_add_test(tc, g_width_prec_hash_zero);
  tcase_add_test(tc, g_width_prec_fzer_zero);
  tcase_add_test(tc, g_zrwth_zrpc_plus_zero);
  tcase_add_test(tc, g_zrwth_zrpc_spac_zero);
  tcase_add_test(tc, g_zrwth_zrpc_hash_zero);
  tcase_add_test(tc, g_dynamic_width_zero);
  tcase_add_test(tc, g_dynamic_prec_zero);
  tcase_add_test(tc, g_dynamic_width_prec_zero);
  tcase_add_test(tc, G_mins_zero);
  tcase_add_test(tc, G_plus_zero);
  tcase_add_test(tc, G_spac_zero);
  tcase_add_test(tc, G_hash_zero);
  tcase_add_test(tc, G_fzer_zero);
  tcase_add_test(tc, G_width_zero);
  tcase_add_test(tc, G_zrpc_zero);
  tcase_add_test(tc, G_prec_zero);
  tcase_add_test(tc, G_width_prec_zero);
  tcase_add_test(tc, G_width_mins_zero);
  tcase_add_test(tc, G_width_plus_zero);
  tcase_add_test(tc, G_width_spac_zero);
  tcase_add_test(tc, G_width_hash_zero);
  tcase_add_test(tc, G_width_fzer_zero);
  tcase_add_test(tc, G_zrwth_plus_zero);
  tcase_add_test(tc, G_zrwth_spac_zero);
  tcase_add_test(tc, G_zrwth_hash_zero);
  tcase_add_test(tc, G_prec_mins_zero);
  tcase_add_test(tc, G_prec_plus_zero);
  tcase_add_test(tc, G_prec_spac_zero);
  tcase_add_test(tc, G_prec_hash_zero);
  tcase_add_test(tc, G_prec_fzer_zero);
  tcase_add_test(tc, G_zrpc_mins_zero);
  tcase_add_test(tc, G_zrpc_plus_zero);
  tcase_add_test(tc, G_zrpc_spac_zero);
  tcase_add_test(tc, G_zrpc_hash_zero);
  tcase_add_test(tc, G_zrpc_fzer_zero);
  tcase_add_test(tc, G_width_prec_mins_zero);
  tcase_add_test(tc, G_width_prec_plus_zero);
  tcase_add_test(tc, G_width_prec_spac_zero);
  tcase_add_test(tc, G_width_prec_hash_zero);
  tcase_add_test(tc, G_width_prec_fzer_zero);
  tcase_add_test(tc, G_zrwth_zrpc_plus_zero);
  tcase_add_test(tc, G_zrwth_zrpc_spac_zero);
  tcase_add_test(tc, G_zrwth_zrpc_hash_zero);
  tcase_add_test(tc, G_dynamic_width_zero);
  tcase_add_test(tc, G_dynamic_prec_zero);
  tcase_add_test(tc, G_dynamic_width_prec_zero);
  tcase_add_test(tc, le_mins_zero);
  tcase_add_test(tc, le_plus_zero);
  tcase_add_test(tc, le_spac_zero);
  tcase_add_test(tc, le_hash_zero);
  tcase_add_test(tc, le_fzer_zero);
  tcase_add_test(tc, le_width_zero);
  tcase_add_test(tc, le_zrpc_zero);
  tcase_add_test(tc, le_prec_zero);
  tcase_add_test(tc, le_width_prec_zero);
  tcase_add_test(tc, le_width_mins_zero);
  tcase_add_test(tc, le_width_plus_zero);
  tcase_add_test(tc, le_width_spac_zero);
  tcase_add_test(tc, le_width_hash_zero);
  tcase_add_test(tc, le_width_fzer_zero);
  tcase_add_test(tc, le_zrwth_plus_zero);
  tcase_add_test(tc, le_zrwth_spac_zero);
  tcase_add_test(tc, le_zrwth_hash_zero);
  tcase_add_test(tc, le_prec_mins_zero);
  tcase_add_test(tc, le_prec_plus_zero);
  tcase_add_test(tc, le_prec_spac_zero);
  tcase_add_test(tc, le_prec_hash_zero);
  tcase_add_test(tc, le_prec_fzer_zero);
  tcase_add_test(tc, le_zrpc_mins_zero);
  tcase_add_test(tc, le_zrpc_plus_zero);
  tcase_add_test(tc, le_zrpc_spac_zero);
  tcase_add_test(tc, le_zrpc_hash_zero);
  tcase_add_test(tc, le_zrpc_fzer_zero);
  tcase_add_test(tc, le_width_prec_mins_zero);
  tcase_add_test(tc, le_width_prec_plus_zero);
  tcase_add_test(tc, le_width_prec_spac_zero);
  tcase_add_test(tc, le_width_prec_hash_zero);
  tcase_add_test(tc, le_width_prec_fzer_zero);
  tcase_add_test(tc, le_zrwth_zrpc_plus_zero);
  tcase_add_test(tc, le_zrwth_zrpc_spac_zero);
  tcase_add_test(tc, le_zrwth_zrpc_hash_zero);
  tcase_add_test(tc, le_dynamic_width_zero);
  tcase_add_test(tc, le_dynamic_prec_zero);
  tcase_add_test(tc, le_dynamic_width_prec_zero);
  tcase_add_test(tc, lE_mins_zero);
  tcase_add_test(tc, lE_plus_zero);
  tcase_add_test(tc, lE_spac_zero);
  tcase_add_test(tc, lE_hash_zero);
  tcase_add_test(tc, lE_fzer_zero);
  tcase_add_test(tc, lE_width_zero);
  tcase_add_test(tc, lE_zrpc_zero);
  tcase_add_test(tc, lE_prec_zero);
  tcase_add_test(tc, lE_width_prec_zero);
  tcase_add_test(tc, lE_width_mins_zero);
  tcase_add_test(tc, lE_width_plus_zero);
  tcase_add_test(tc, lE_width_spac_zero);
  tcase_add_test(tc, lE_width_hash_zero);
  tcase_add_test(tc, lE_width_fzer_zero);
  tcase_add_test(tc, lE_zrwth_plus_zero);
  tcase_add_test(tc, lE_zrwth_spac_zero);
  tcase_add_test(tc, lE_zrwth_hash_zero);
  tcase_add_test(tc, lE_prec_mins_zero);
  tcase_add_test(tc, lE_prec_plus_zero);
  tcase_add_test(tc, lE_prec_spac_zero);
  tcase_add_test(tc, lE_prec_hash_zero);
  tcase_add_test(tc, lE_prec_fzer_zero);
  tcase_add_test(tc, lE_zrpc_mins_zero);
  tcase_add_test(tc, lE_zrpc_plus_zero);
  tcase_add_test(tc, lE_zrpc_spac_zero);
  tcase_add_test(tc, lE_zrpc_hash_zero);
  tcase_add_test(tc, lE_zrpc_fzer_zero);
  tcase_add_test(tc, lE_width_prec_mins_zero);
  tcase_add_test(tc, lE_width_prec_plus_zero);
  tcase_add_test(tc, lE_width_prec_spac_zero);
  tcase_add_test(tc, lE_width_prec_hash_zero);
  tcase_add_test(tc, lE_width_prec_fzer_zero);
  tcase_add_test(tc, lE_zrwth_zrpc_plus_zero);
  tcase_add_test(tc, lE_zrwth_zrpc_spac_zero);
  tcase_add_test(tc, lE_zrwth_zrpc_hash_zero);
  tcase_add_test(tc, lE_dynamic_width_zero);
  tcase_add_test(tc, lE_dynamic_prec_zero);
  tcase_add_test(tc, lE_dynamic_width_prec_zero);
  tcase_add_test(tc, lf_mins_zero);
  tcase_add_test(tc, lf_plus_zero);
  tcase_add_test(tc, lf_spac_zero);
  tcase_add_test(tc, lf_hash_zero);
  tcase_add_test(tc, lf_fzer_zero);
  tcase_add_test(tc, lf_width_zero);
  tcase_add_test(tc, lf_zrpc_zero);
  tcase_add_test(tc, lf_prec_zero);
  tcase_add_test(tc, lf_width_prec_zero);
  tcase_add_test(tc, lf_width_mins_zero);
  tcase_add_test(tc, lf_width_plus_zero);
  tcase_add_test(tc, lf_width_spac_zero);
  tcase_add_test(tc, lf_width_hash_zero);
  tcase_add_test(tc, lf_width_fzer_zero);
  tcase_add_test(tc, lf_zrwth_plus_zero);
  tcase_add_test(tc, lf_zrwth_spac_zero);
  tcase_add_test(tc, lf_zrwth_hash_zero);
  tcase_add_test(tc, lf_prec_mins_zero);
  tcase_add_test(tc, lf_prec_plus_zero);
  tcase_add_test(tc, lf_prec_spac_zero);
  tcase_add_test(tc, lf_prec_hash_zero);
  tcase_add_test(tc, lf_prec_fzer_zero);
  tcase_add_test(tc, lf_zrpc_mins_zero);
  tcase_add_test(tc, lf_zrpc_plus_zero);
  tcase_add_test(tc, lf_zrpc_spac_zero);
  tcase_add_test(tc, lf_zrpc_hash_zero);
  tcase_add_test(tc, lf_zrpc_fzer_zero);
  tcase_add_test(tc, lf_width_prec_mins_zero);
  tcase_add_test(tc, lf_width_prec_plus_zero);
  tcase_add_test(tc, lf_width_prec_spac_zero);
  tcase_add_test(tc, lf_width_prec_hash_zero);
  tcase_add_test(tc, lf_width_prec_fzer_zero);
  tcase_add_test(tc, lf_zrwth_zrpc_plus_zero);
  tcase_add_test(tc, lf_zrwth_zrpc_spac_zero);
  tcase_add_test(tc, lf_zrwth_zrpc_hash_zero);
  tcase_add_test(tc, lf_dynamic_width_zero);
  tcase_add_test(tc, lf_dynamic_prec_zero);
  tcase_add_test(tc, lf_dynamic_width_prec_zero);
  tcase_add_test(tc, lg_mins_zero);
  tcase_add_test(tc, lg_plus_zero);
  tcase_add_test(tc, lg_spac_zero);
  tcase_add_test(tc, lg_hash_zero);
  tcase_add_test(tc, lg_fzer_zero);
  tcase_add_test(tc, lg_width_zero);
  tcase_add_test(tc, lg_zrpc_zero);
  tcase_add_test(tc, lg_prec_zero);
  tcase_add_test(tc, lg_width_prec_zero);
  tcase_add_test(tc, lg_width_mins_zero);
  tcase_add_test(tc, lg_width_plus_zero);
  tcase_add_test(tc, lg_width_spac_zero);
  tcase_add_test(tc, lg_width_hash_zero);
  tcase_add_test(tc, lg_width_fzer_zero);
  tcase_add_test(tc, lg_zrwth_plus_zero);
  tcase_add_test(tc, lg_zrwth_spac_zero);
  tcase_add_test(tc, lg_zrwth_hash_zero);
  tcase_add_test(tc, lg_prec_mins_zero);
  tcase_add_test(tc, lg_prec_plus_zero);
  tcase_add_test(tc, lg_prec_spac_zero);
  tcase_add_test(tc, lg_prec_hash_zero);
  tcase_add_test(tc, lg_prec_fzer_zero);
  tcase_add_test(tc, lg_zrpc_mins_zero);
  tcase_add_test(tc, lg_zrpc_plus_zero);
  tcase_add_test(tc, lg_zrpc_spac_zero);
  tcase_add_test(tc, lg_zrpc_hash_zero);
  tcase_add_test(tc, lg_zrpc_fzer_zero);
  tcase_add_test(tc, lg_width_prec_mins_zero);
  tcase_add_test(tc, lg_width_prec_plus_zero);
  tcase_add_test(tc, lg_width_prec_spac_zero);
  tcase_add_test(tc, lg_width_prec_hash_zero);
  tcase_add_test(tc, lg_width_prec_fzer_zero);
  tcase_add_test(tc, lg_zrwth_zrpc_plus_zero);
  tcase_add_test(tc, lg_zrwth_zrpc_spac_zero);
  tcase_add_test(tc, lg_zrwth_zrpc_hash_zero);
  tcase_add_test(tc, lg_dynamic_width_zero);
  tcase_add_test(tc, lg_dynamic_prec_zero);
  tcase_add_test(tc, lg_dynamic_width_prec_zero);
  tcase_add_test(tc, lG_mins_zero);
  tcase_add_test(tc, lG_plus_zero);
  tcase_add_test(tc, lG_spac_zero);
  tcase_add_test(tc, lG_hash_zero);
  tcase_add_test(tc, lG_fzer_zero);
  tcase_add_test(tc, lG_width_zero);
  tcase_add_test(tc, lG_zrpc_zero);
  tcase_add_test(tc, lG_prec_zero);
  tcase_add_test(tc, lG_width_prec_zero);
  tcase_add_test(tc, lG_width_mins_zero);
  tcase_add_test(tc, lG_width_plus_zero);
  tcase_add_test(tc, lG_width_spac_zero);
  tcase_add_test(tc, lG_width_hash_zero);
  tcase_add_test(tc, lG_width_fzer_zero);
  tcase_add_test(tc, lG_zrwth_plus_zero);
  tcase_add_test(tc, lG_zrwth_spac_zero);
  tcase_add_test(tc, lG_zrwth_hash_zero);
  tcase_add_test(tc, lG_prec_mins_zero);
  tcase_add_test(tc, lG_prec_plus_zero);
  tcase_add_test(tc, lG_prec_spac_zero);
  tcase_add_test(tc, lG_prec_hash_zero);
  tcase_add_test(tc, lG_prec_fzer_zero);
  tcase_add_test(tc, lG_zrpc_mins_zero);
  tcase_add_test(tc, lG_zrpc_plus_zero);
  tcase_add_test(tc, lG_zrpc_spac_zero);
  tcase_add_test(tc, lG_zrpc_hash_zero);
  tcase_add_test(tc, lG_zrpc_fzer_zero);
  tcase_add_test(tc, lG_width_prec_mins_zero);
  tcase_add_test(tc, lG_width_prec_plus_zero);
  tcase_add_test(tc, lG_width_prec_spac_zero);
  tcase_add_test(tc, lG_width_prec_hash_zero);
  tcase_add_test(tc, lG_width_prec_fzer_zero);
  tcase_add_test(tc, lG_zrwth_zrpc_plus_zero);
  tcase_add_test(tc, lG_zrwth_zrpc_spac_zero);
  tcase_add_test(tc, lG_zrwth_zrpc_hash_zero);
  tcase_add_test(tc, lG_dynamic_width_zero);
  tcase_add_test(tc, lG_dynamic_prec_zero);
  tcase_add_test(tc, lG_dynamic_width_prec_zero);
  tcase_add_test(tc, Le_mins_zero);
  tcase_add_test(tc, Le_plus_zero);
  tcase_add_test(tc, Le_spac_zero);
  tcase_add_test(tc, Le_hash_zero);
  tcase_add_test(tc, Le_fzer_zero);
  tcase_add_test(tc, Le_width_zero);
  tcase_add_test(tc, Le_zrpc_zero);
  tcase_add_test(tc, Le_prec_zero);
  tcase_add_test(tc, Le_width_prec_zero);
  tcase_add_test(tc, Le_width_mins_zero);
  tcase_add_test(tc, Le_width_plus_zero);
  tcase_add_test(tc, Le_width_spac_zero);
  tcase_add_test(tc, Le_width_hash_zero);
  tcase_add_test(tc, Le_width_fzer_zero);
  tcase_add_test(tc, Le_zrwth_plus_zero);
  tcase_add_test(tc, Le_zrwth_spac_zero);
  tcase_add_test(tc, Le_zrwth_hash_zero);
  tcase_add_test(tc, Le_prec_mins_zero);
  tcase_add_test(tc, Le_prec_plus_zero);
  tcase_add_test(tc, Le_prec_spac_zero);
  tcase_add_test(tc, Le_prec_hash_zero);
  tcase_add_test(tc, Le_prec_fzer_zero);
  tcase_add_test(tc, Le_zrpc_mins_zero);
  tcase_add_test(tc, Le_zrpc_plus_zero);
  tcase_add_test(tc, Le_zrpc_spac_zero);
  tcase_add_test(tc, Le_zrpc_hash_zero);
  tcase_add_test(tc, Le_zrpc_fzer_zero);
  tcase_add_test(tc, Le_width_prec_mins_zero);
  tcase_add_test(tc, Le_width_prec_plus_zero);
  tcase_add_test(tc, Le_width_prec_spac_zero);
  tcase_add_test(tc, Le_width_prec_hash_zero);
  tcase_add_test(tc, Le_width_prec_fzer_zero);
  tcase_add_test(tc, Le_zrwth_zrpc_plus_zero);
  tcase_add_test(tc, Le_zrwth_zrpc_spac_zero);
  tcase_add_test(tc, Le_zrwth_zrpc_hash_zero);
  tcase_add_test(tc, Le_dynamic_width_zero);
  tcase_add_test(tc, Le_dynamic_prec_zero);
  tcase_add_test(tc, Le_dynamic_width_prec_zero);
  tcase_add_test(tc, LE_mins_zero);
  tcase_add_test(tc, LE_plus_zero);
  tcase_add_test(tc, LE_spac_zero);
  tcase_add_test(tc, LE_hash_zero);
  tcase_add_test(tc, LE_fzer_zero);
  tcase_add_test(tc, LE_width_zero);
  tcase_add_test(tc, LE_zrpc_zero);
  tcase_add_test(tc, LE_prec_zero);
  tcase_add_test(tc, LE_width_prec_zero);
  tcase_add_test(tc, LE_width_mins_zero);
  tcase_add_test(tc, LE_width_plus_zero);
  tcase_add_test(tc, LE_width_spac_zero);
  tcase_add_test(tc, LE_width_hash_zero);
  tcase_add_test(tc, LE_width_fzer_zero);
  tcase_add_test(tc, LE_zrwth_plus_zero);
  tcase_add_test(tc, LE_zrwth_spac_zero);
  tcase_add_test(tc, LE_zrwth_hash_zero);
  tcase_add_test(tc, LE_prec_mins_zero);
  tcase_add_test(tc, LE_prec_plus_zero);
  tcase_add_test(tc, LE_prec_spac_zero);
  tcase_add_test(tc, LE_prec_hash_zero);
  tcase_add_test(tc, LE_prec_fzer_zero);
  tcase_add_test(tc, LE_zrpc_mins_zero);
  tcase_add_test(tc, LE_zrpc_plus_zero);
  tcase_add_test(tc, LE_zrpc_spac_zero);
  tcase_add_test(tc, LE_zrpc_hash_zero);
  tcase_add_test(tc, LE_zrpc_fzer_zero);
  tcase_add_test(tc, LE_width_prec_mins_zero);
  tcase_add_test(tc, LE_width_prec_plus_zero);
  tcase_add_test(tc, LE_width_prec_spac_zero);
  tcase_add_test(tc, LE_width_prec_hash_zero);
  tcase_add_test(tc, LE_width_prec_fzer_zero);
  tcase_add_test(tc, LE_zrwth_zrpc_plus_zero);
  tcase_add_test(tc, LE_zrwth_zrpc_spac_zero);
  tcase_add_test(tc, LE_zrwth_zrpc_hash_zero);
  tcase_add_test(tc, LE_dynamic_width_zero);
  tcase_add_test(tc, LE_dynamic_prec_zero);
  tcase_add_test(tc, LE_dynamic_width_prec_zero);
  tcase_add_test(tc, Lf_mins_zero);
  tcase_add_test(tc, Lf_plus_zero);
  tcase_add_test(tc, Lf_spac_zero);
  tcase_add_test(tc, Lf_hash_zero);
  tcase_add_test(tc, Lf_fzer_zero);
  tcase_add_test(tc, Lf_width_zero);
  tcase_add_test(tc, Lf_zrpc_zero);
  tcase_add_test(tc, Lf_prec_zero);
  tcase_add_test(tc, Lf_width_prec_zero);
  tcase_add_test(tc, Lf_width_mins_zero);
  tcase_add_test(tc, Lf_width_plus_zero);
  tcase_add_test(tc, Lf_width_spac_zero);
  tcase_add_test(tc, Lf_width_hash_zero);
  tcase_add_test(tc, Lf_width_fzer_zero);
  tcase_add_test(tc, Lf_zrwth_plus_zero);
  tcase_add_test(tc, Lf_zrwth_spac_zero);
  tcase_add_test(tc, Lf_zrwth_hash_zero);
  tcase_add_test(tc, Lf_prec_mins_zero);
  tcase_add_test(tc, Lf_prec_plus_zero);
  tcase_add_test(tc, Lf_prec_spac_zero);
  tcase_add_test(tc, Lf_prec_hash_zero);
  tcase_add_test(tc, Lf_prec_fzer_zero);
  tcase_add_test(tc, Lf_zrpc_mins_zero);
  tcase_add_test(tc, Lf_zrpc_plus_zero);
  tcase_add_test(tc, Lf_zrpc_spac_zero);
  tcase_add_test(tc, Lf_zrpc_hash_zero);
  tcase_add_test(tc, Lf_zrpc_fzer_zero);
  tcase_add_test(tc, Lf_width_prec_mins_zero);
  tcase_add_test(tc, Lf_width_prec_plus_zero);
  tcase_add_test(tc, Lf_width_prec_spac_zero);
  tcase_add_test(tc, Lf_width_prec_hash_zero);
  tcase_add_test(tc, Lf_width_prec_fzer_zero);
  tcase_add_test(tc, Lf_zrwth_zrpc_plus_zero);
  tcase_add_test(tc, Lf_zrwth_zrpc_spac_zero);
  tcase_add_test(tc, Lf_zrwth_zrpc_hash_zero);
  tcase_add_test(tc, Lf_dynamic_width_zero);
  tcase_add_test(tc, Lf_dynamic_prec_zero);
  tcase_add_test(tc, Lf_dynamic_width_prec_zero);
  tcase_add_test(tc, Lg_mins_zero);
  tcase_add_test(tc, Lg_plus_zero);
  tcase_add_test(tc, Lg_spac_zero);
  tcase_add_test(tc, Lg_hash_zero);
  tcase_add_test(tc, Lg_fzer_zero);
  tcase_add_test(tc, Lg_width_zero);
  tcase_add_test(tc, Lg_zrpc_zero);
  tcase_add_test(tc, Lg_prec_zero);
  tcase_add_test(tc, Lg_width_prec_zero);
  tcase_add_test(tc, Lg_width_mins_zero);
  tcase_add_test(tc, Lg_width_plus_zero);
  tcase_add_test(tc, Lg_width_spac_zero);
  tcase_add_test(tc, Lg_width_hash_zero);
  tcase_add_test(tc, Lg_width_fzer_zero);
  tcase_add_test(tc, Lg_zrwth_plus_zero);
  tcase_add_test(tc, Lg_zrwth_spac_zero);
  tcase_add_test(tc, Lg_zrwth_hash_zero);
  tcase_add_test(tc, Lg_prec_mins_zero);
  tcase_add_test(tc, Lg_prec_plus_zero);
  tcase_add_test(tc, Lg_prec_spac_zero);
  tcase_add_test(tc, Lg_prec_hash_zero);
  tcase_add_test(tc, Lg_prec_fzer_zero);
  tcase_add_test(tc, Lg_zrpc_mins_zero);
  tcase_add_test(tc, Lg_zrpc_plus_zero);
  tcase_add_test(tc, Lg_zrpc_spac_zero);
  tcase_add_test(tc, Lg_zrpc_hash_zero);
  tcase_add_test(tc, Lg_zrpc_fzer_zero);
  tcase_add_test(tc, Lg_width_prec_mins_zero);
  tcase_add_test(tc, Lg_width_prec_plus_zero);
  tcase_add_test(tc, Lg_width_prec_spac_zero);
  tcase_add_test(tc, Lg_width_prec_hash_zero);
  tcase_add_test(tc, Lg_width_prec_fzer_zero);
  tcase_add_test(tc, Lg_zrwth_zrpc_plus_zero);
  tcase_add_test(tc, Lg_zrwth_zrpc_spac_zero);
  tcase_add_test(tc, Lg_zrwth_zrpc_hash_zero);
  tcase_add_test(tc, Lg_dynamic_width_zero);
  tcase_add_test(tc, Lg_dynamic_prec_zero);
  tcase_add_test(tc, Lg_dynamic_width_prec_zero);
  tcase_add_test(tc, LG_mins_zero);
  tcase_add_test(tc, LG_plus_zero);
  tcase_add_test(tc, LG_spac_zero);
  tcase_add_test(tc, LG_hash_zero);
  tcase_add_test(tc, LG_fzer_zero);
  tcase_add_test(tc, LG_width_zero);
  tcase_add_test(tc, LG_zrpc_zero);
  tcase_add_test(tc, LG_prec_zero);
  tcase_add_test(tc, LG_width_prec_zero);
  tcase_add_test(tc, LG_width_mins_zero);
  tcase_add_test(tc, LG_width_plus_zero);
  tcase_add_test(tc, LG_width_spac_zero);
  tcase_add_test(tc, LG_width_hash_zero);
  tcase_add_test(tc, LG_width_fzer_zero);
  tcase_add_test(tc, LG_zrwth_plus_zero);
  tcase_add_test(tc, LG_zrwth_spac_zero);
  tcase_add_test(tc, LG_zrwth_hash_zero);
  tcase_add_test(tc, LG_prec_mins_zero);
  tcase_add_test(tc, LG_prec_plus_zero);
  tcase_add_test(tc, LG_prec_spac_zero);
  tcase_add_test(tc, LG_prec_hash_zero);
  tcase_add_test(tc, LG_prec_fzer_zero);
  tcase_add_test(tc, LG_zrpc_mins_zero);
  tcase_add_test(tc, LG_zrpc_plus_zero);
  tcase_add_test(tc, LG_zrpc_spac_zero);
  tcase_add_test(tc, LG_zrpc_hash_zero);
  tcase_add_test(tc, LG_zrpc_fzer_zero);
  tcase_add_test(tc, LG_width_prec_mins_zero);
  tcase_add_test(tc, LG_width_prec_plus_zero);
  tcase_add_test(tc, LG_width_prec_spac_zero);
  tcase_add_test(tc, LG_width_prec_hash_zero);
  tcase_add_test(tc, LG_width_prec_fzer_zero);
  tcase_add_test(tc, LG_zrwth_zrpc_plus_zero);
  tcase_add_test(tc, LG_zrwth_zrpc_spac_zero);
  tcase_add_test(tc, LG_zrwth_zrpc_hash_zero);
  tcase_add_test(tc, LG_dynamic_width_zero);
  tcase_add_test(tc, LG_dynamic_prec_zero);
  tcase_add_test(tc, LG_dynamic_width_prec_zero);
  tcase_add_test(tc, e_mins_post);
  tcase_add_test(tc, e_plus_post);
  tcase_add_test(tc, e_spac_post);
  tcase_add_test(tc, e_hash_post);
  tcase_add_test(tc, e_fzer_post);
  tcase_add_test(tc, e_mins_negt);
  tcase_add_test(tc, e_plus_negt);
  tcase_add_test(tc, e_spac_negt);
  tcase_add_test(tc, e_hash_negt);
  tcase_add_test(tc, e_fzer_negt);
  tcase_add_test(tc, e_mins_small);
  tcase_add_test(tc, e_plus_small);
  tcase_add_test(tc, e_spac_small);
  tcase_add_test(tc, e_hash_small);
  tcase_add_test(tc, e_fzer_small);
  tcase_add_test(tc, e_mins_large);
  tcase_add_test(tc, e_plus_large);
  tcase_add_test(tc, e_spac_large);
  tcase_add_test(tc, e_hash_large);
  tcase_add_test(tc, e_fzer_large);
  tcase_add_test(tc, e_width_post);
  tcase_add_test(tc, e_zrpc_post);
  tcase_add_test(tc, e_prec_post);
  tcase_add_test(tc, e_width_negt);
  tcase_add_test(tc, e_zrpc_negt);
  tcase_add_test(tc, e_prec_negt);
  tcase_add_test(tc, e_width_small);
  tcase_add_test(tc, e_zrpc_small);
  tcase_add_test(tc, e_prec_small);
  tcase_add_test(tc, e_width_large);
  tcase_add_test(tc, e_zrpc_large);
  tcase_add_test(tc, e_prec_large);
  tcase_add_test(tc, e_width_prec_post);
  tcase_add_test(tc, e_width_prec_negt);
  tcase_add_test(tc, e_width_prec_small);
  tcase_add_test(tc, e_width_prec_large);
  tcase_add_test(tc, e_width_mins_post);
  tcase_add_test(tc, e_width_plus_post);
  tcase_add_test(tc, e_width_spac_post);
  tcase_add_test(tc, e_width_hash_post);
  tcase_add_test(tc, e_width_fzer_post);
  tcase_add_test(tc, e_width_mins_negt);
  tcase_add_test(tc, e_width_plus_negt);
  tcase_add_test(tc, e_width_spac_negt);
  tcase_add_test(tc, e_width_hash_negt);
  tcase_add_test(tc, e_width_fzer_negt);
  tcase_add_test(tc, e_width_mins_small);
  tcase_add_test(tc, e_width_plus_small);
  tcase_add_test(tc, e_width_spac_small);
  tcase_add_test(tc, e_width_hash_small);
  tcase_add_test(tc, e_width_fzer_small);
  tcase_add_test(tc, e_width_mins_large);
  tcase_add_test(tc, e_width_plus_large);
  tcase_add_test(tc, e_width_spac_large);
  tcase_add_test(tc, e_width_hash_large);
  tcase_add_test(tc, e_width_fzer_large);
  tcase_add_test(tc, e_zrwth_plus_post);
  tcase_add_test(tc, e_zrwth_spac_post);
  tcase_add_test(tc, e_zrwth_hash_post);
  tcase_add_test(tc, e_zrwth_plus_negt);
  tcase_add_test(tc, e_zrwth_spac_negt);
  tcase_add_test(tc, e_zrwth_hash_negt);
  tcase_add_test(tc, e_zrwth_plus_small);
  tcase_add_test(tc, e_zrwth_spac_small);
  tcase_add_test(tc, e_zrwth_hash_small);
  tcase_add_test(tc, e_zrwth_plus_large);
  tcase_add_test(tc, e_zrwth_spac_large);
  tcase_add_test(tc, e_zrwth_hash_large);
  tcase_add_test(tc, e_prec_mins_post);
  tcase_add_test(tc, e_prec_plus_post);
  tcase_add_test(tc, e_prec_spac_post);
  tcase_add_test(tc, e_prec_hash_post);
  tcase_add_test(tc, e_prec_fzer_post);
  tcase_add_test(tc, e_prec_mins_negt);
  tcase_add_test(tc, e_prec_plus_negt);
  tcase_add_test(tc, e_prec_spac_negt);
  tcase_add_test(tc, e_prec_hash_negt);
  tcase_add_test(tc, e_prec_fzer_negt);
  tcase_add_test(tc, e_prec_mins_small);
  tcase_add_test(tc, e_prec_plus_small);
  tcase_add_test(tc, e_prec_spac_small);
  tcase_add_test(tc, e_prec_hash_small);
  tcase_add_test(tc, e_prec_fzer_small);
  tcase_add_test(tc, e_prec_mins_large);
  tcase_add_test(tc, e_prec_plus_large);
  tcase_add_test(tc, e_prec_spac_large);
  tcase_add_test(tc, e_prec_hash_large);
  tcase_add_test(tc, e_prec_fzer_large);
  tcase_add_test(tc, e_zrpc_mins_post);
  tcase_add_test(tc, e_zrpc_plus_post);
  tcase_add_test(tc, e_zrpc_spac_post);
  tcase_add_test(tc, e_zrpc_hash_post);
  tcase_add_test(tc, e_zrpc_fzer_post);
  tcase_add_test(tc, e_zrpc_mins_negt);
  tcase_add_test(tc, e_zrpc_plus_negt);
  tcase_add_test(tc, e_zrpc_spac_negt);
  tcase_add_test(tc, e_zrpc_hash_negt);
  tcase_add_test(tc, e_zrpc_fzer_negt);
  tcase_add_test(tc, e_zrpc_mins_small);
  tcase_add_test(tc, e_zrpc_plus_small);
  tcase_add_test(tc, e_zrpc_spac_small);
  tcase_add_test(tc, e_zrpc_hash_small);
  tcase_add_test(tc, e_zrpc_fzer_small);
  tcase_add_test(tc, e_zrpc_mins_large);
  tcase_add_test(tc, e_zrpc_plus_large);
  tcase_add_test(tc, e_zrpc_spac_large);
  tcase_add_test(tc, e_zrpc_hash_large);
  tcase_add_test(tc, e_zrpc_fzer_large);
  tcase_add_test(tc, e_width_prec_mins_post);
  tcase_add_test(tc, e_width_prec_plus_post);
  tcase_add_test(tc, e_width_prec_spac_post);
  tcase_add_test(tc, e_width_prec_hash_post);
  tcase_add_test(tc, e_width_prec_fzer_post);
  tcase_add_test(tc, e_width_prec_mins_negt);
  tcase_add_test(tc, e_width_prec_plus_negt);
  tcase_add_test(tc, e_width_prec_spac_negt);
  tcase_add_test(tc, e_width_prec_hash_negt);
  tcase_add_test(tc, e_width_prec_fzer_negt);
  tcase_add_test(tc, e_width_prec_mins_small);
  tcase_add_test(tc, e_width_prec_plus_small);
  tcase_add_test(tc, e_width_prec_spac_small);
  tcase_add_test(tc, e_width_prec_hash_small);
  tcase_add_test(tc, e_width_prec_fzer_small);
  tcase_add_test(tc, e_width_prec_mins_large);
  tcase_add_test(tc, e_width_prec_plus_large);
  tcase_add_test(tc, e_width_prec_spac_large);
  tcase_add_test(tc, e_width_prec_hash_large);
  tcase_add_test(tc, e_width_prec_fzer_large);
  tcase_add_test(tc, e_zrwth_zrpc_plus_post);
  tcase_add_test(tc, e_zrwth_zrpc_spac_post);
  tcase_add_test(tc, e_zrwth_zrpc_hash_post);
  tcase_add_test(tc, e_zrwth_zrpc_plus_negt);
  tcase_add_test(tc, e_zrwth_zrpc_spac_negt);
  tcase_add_test(tc, e_zrwth_zrpc_hash_negt);
  tcase_add_test(tc, e_zrwth_zrpc_plus_small);
  tcase_add_test(tc, e_zrwth_zrpc_spac_small);
  tcase_add_test(tc, e_zrwth_zrpc_hash_small);
  tcase_add_test(tc, e_zrwth_zrpc_plus_large);
  tcase_add_test(tc, e_zrwth_zrpc_spac_large);
  tcase_add_test(tc, e_zrwth_zrpc_hash_large);
  tcase_add_test(tc, e_dynamic_width_post);
  tcase_add_test(tc, e_dynamic_width_negt);
  tcase_add_test(tc, e_dynamic_width_small);
  tcase_add_test(tc, e_dynamic_width_large);
  tcase_add_test(tc, e_dynamic_prec_post);
  tcase_add_test(tc, e_dynamic_prec_negt);
  tcase_add_test(tc, e_dynamic_prec_small);
  tcase_add_test(tc, e_dynamic_prec_large);
  tcase_add_test(tc, e_dynamic_width_prec_post);
  tcase_add_test(tc, e_dynamic_width_prec_negt);
  tcase_add_test(tc, e_dynamic_width_prec_small);
  tcase_add_test(tc, e_dynamic_width_prec_large);
  tcase_add_test(tc, E_mins_post);
  tcase_add_test(tc, E_plus_post);
  tcase_add_test(tc, E_spac_post);
  tcase_add_test(tc, E_hash_post);
  tcase_add_test(tc, E_fzer_post);
  tcase_add_test(tc, E_mins_negt);
  tcase_add_test(tc, E_plus_negt);
  tcase_add_test(tc, E_spac_negt);
  tcase_add_test(tc, E_hash_negt);
  tcase_add_test(tc, E_fzer_negt);
  tcase_add_test(tc, E_mins_small);
  tcase_add_test(tc, E_plus_small);
  tcase_add_test(tc, E_spac_small);
  tcase_add_test(tc, E_hash_small);
  tcase_add_test(tc, E_fzer_small);
  tcase_add_test(tc, E_mins_large);
  tcase_add_test(tc, E_plus_large);
  tcase_add_test(tc, E_spac_large);
  tcase_add_test(tc, E_hash_large);
  tcase_add_test(tc, E_fzer_large);
  tcase_add_test(tc, E_width_post);
  tcase_add_test(tc, E_zrpc_post);
  tcase_add_test(tc, E_prec_post);
  tcase_add_test(tc, E_width_negt);
  tcase_add_test(tc, E_zrpc_negt);
  tcase_add_test(tc, E_prec_negt);
  tcase_add_test(tc, E_width_small);
  tcase_add_test(tc, E_zrpc_small);
  tcase_add_test(tc, E_prec_small);
  tcase_add_test(tc, E_width_large);
  tcase_add_test(tc, E_zrpc_large);
  tcase_add_test(tc, E_prec_large);
  tcase_add_test(tc, E_width_prec_post);
  tcase_add_test(tc, E_width_prec_negt);
  tcase_add_test(tc, E_width_prec_small);
  tcase_add_test(tc, E_width_prec_large);
  tcase_add_test(tc, E_width_mins_post);
  tcase_add_test(tc, E_width_plus_post);
  tcase_add_test(tc, E_width_spac_post);
  tcase_add_test(tc, E_width_hash_post);
  tcase_add_test(tc, E_width_fzer_post);
  tcase_add_test(tc, E_width_mins_negt);
  tcase_add_test(tc, E_width_plus_negt);
  tcase_add_test(tc, E_width_spac_negt);
  tcase_add_test(tc, E_width_hash_negt);
  tcase_add_test(tc, E_width_fzer_negt);
  tcase_add_test(tc, E_width_mins_small);
  tcase_add_test(tc, E_width_plus_small);
  tcase_add_test(tc, E_width_spac_small);
  tcase_add_test(tc, E_width_hash_small);
  tcase_add_test(tc, E_width_fzer_small);
  tcase_add_test(tc, E_width_mins_large);
  tcase_add_test(tc, E_width_plus_large);
  tcase_add_test(tc, E_width_spac_large);
  tcase_add_test(tc, E_width_hash_large);
  tcase_add_test(tc, E_width_fzer_large);
  tcase_add_test(tc, E_zrwth_plus_post);
  tcase_add_test(tc, E_zrwth_spac_post);
  tcase_add_test(tc, E_zrwth_hash_post);
  tcase_add_test(tc, E_zrwth_plus_negt);
  tcase_add_test(tc, E_zrwth_spac_negt);
  tcase_add_test(tc, E_zrwth_hash_negt);
  tcase_add_test(tc, E_zrwth_plus_small);
  tcase_add_test(tc, E_zrwth_spac_small);
  tcase_add_test(tc, E_zrwth_hash_small);
  tcase_add_test(tc, E_zrwth_plus_large);
  tcase_add_test(tc, E_zrwth_spac_large);
  tcase_add_test(tc, E_zrwth_hash_large);
  tcase_add_test(tc, E_prec_mins_post);
  tcase_add_test(tc, E_prec_plus_post);
  tcase_add_test(tc, E_prec_spac_post);
  tcase_add_test(tc, E_prec_hash_post);
  tcase_add_test(tc, E_prec_fzer_post);
  tcase_add_test(tc, E_prec_mins_negt);
  tcase_add_test(tc, E_prec_plus_negt);
  tcase_add_test(tc, E_prec_spac_negt);
  tcase_add_test(tc, E_prec_hash_negt);
  tcase_add_test(tc, E_prec_fzer_negt);
  tcase_add_test(tc, E_prec_mins_small);
  tcase_add_test(tc, E_prec_plus_small);
  tcase_add_test(tc, E_prec_spac_small);
  tcase_add_test(tc, E_prec_hash_small);
  tcase_add_test(tc, E_prec_fzer_small);
  tcase_add_test(tc, E_prec_mins_large);
  tcase_add_test(tc, E_prec_plus_large);
  tcase_add_test(tc, E_prec_spac_large);
  tcase_add_test(tc, E_prec_hash_large);
  tcase_add_test(tc, E_prec_fzer_large);
  tcase_add_test(tc, E_zrpc_mins_post);
  tcase_add_test(tc, E_zrpc_plus_post);
  tcase_add_test(tc, E_zrpc_spac_post);
  tcase_add_test(tc, E_zrpc_hash_post);
  tcase_add_test(tc, E_zrpc_fzer_post);
  tcase_add_test(tc, E_zrpc_mins_negt);
  tcase_add_test(tc, E_zrpc_plus_negt);
  tcase_add_test(tc, E_zrpc_spac_negt);
  tcase_add_test(tc, E_zrpc_hash_negt);
  tcase_add_test(tc, E_zrpc_fzer_negt);
  tcase_add_test(tc, E_zrpc_mins_small);
  tcase_add_test(tc, E_zrpc_plus_small);
  tcase_add_test(tc, E_zrpc_spac_small);
  tcase_add_test(tc, E_zrpc_hash_small);
  tcase_add_test(tc, E_zrpc_fzer_small);
  tcase_add_test(tc, E_zrpc_mins_large);
  tcase_add_test(tc, E_zrpc_plus_large);
  tcase_add_test(tc, E_zrpc_spac_large);
  tcase_add_test(tc, E_zrpc_hash_large);
  tcase_add_test(tc, E_zrpc_fzer_large);
  tcase_add_test(tc, E_width_prec_mins_post);
  tcase_add_test(tc, E_width_prec_plus_post);
  tcase_add_test(tc, E_width_prec_spac_post);
  tcase_add_test(tc, E_width_prec_hash_post);
  tcase_add_test(tc, E_width_prec_fzer_post);
  tcase_add_test(tc, E_width_prec_mins_negt);
  tcase_add_test(tc, E_width_prec_plus_negt);
  tcase_add_test(tc, E_width_prec_spac_negt);
  tcase_add_test(tc, E_width_prec_hash_negt);
  tcase_add_test(tc, E_width_prec_fzer_negt);
  tcase_add_test(tc, E_width_prec_mins_small);
  tcase_add_test(tc, E_width_prec_plus_small);
  tcase_add_test(tc, E_width_prec_spac_small);
  tcase_add_test(tc, E_width_prec_hash_small);
  tcase_add_test(tc, E_width_prec_fzer_small);
  tcase_add_test(tc, E_width_prec_mins_large);
  tcase_add_test(tc, E_width_prec_plus_large);
  tcase_add_test(tc, E_width_prec_spac_large);
  tcase_add_test(tc, E_width_prec_hash_large);
  tcase_add_test(tc, E_width_prec_fzer_large);
  tcase_add_test(tc, E_zrwth_zrpc_plus_post);
  tcase_add_test(tc, E_zrwth_zrpc_spac_post);
  tcase_add_test(tc, E_zrwth_zrpc_hash_post);
  tcase_add_test(tc, E_zrwth_zrpc_plus_negt);
  tcase_add_test(tc, E_zrwth_zrpc_spac_negt);
  tcase_add_test(tc, E_zrwth_zrpc_hash_negt);
  tcase_add_test(tc, E_zrwth_zrpc_plus_small);
  tcase_add_test(tc, E_zrwth_zrpc_spac_small);
  tcase_add_test(tc, E_zrwth_zrpc_hash_small);
  tcase_add_test(tc, E_zrwth_zrpc_plus_large);
  tcase_add_test(tc, E_zrwth_zrpc_spac_large);
  tcase_add_test(tc, E_zrwth_zrpc_hash_large);
  tcase_add_test(tc, E_dynamic_width_post);
  tcase_add_test(tc, E_dynamic_width_negt);
  tcase_add_test(tc, E_dynamic_width_small);
  tcase_add_test(tc, E_dynamic_width_large);
  tcase_add_test(tc, E_dynamic_prec_post);
  tcase_add_test(tc, E_dynamic_prec_negt);
  tcase_add_test(tc, E_dynamic_prec_small);
  tcase_add_test(tc, E_dynamic_prec_large);
  tcase_add_test(tc, E_dynamic_width_prec_post);
  tcase_add_test(tc, E_dynamic_width_prec_negt);
  tcase_add_test(tc, E_dynamic_width_prec_small);
  tcase_add_test(tc, E_dynamic_width_prec_large);
  tcase_add_test(tc, f_mins_post);
  tcase_add_test(tc, f_plus_post);
  tcase_add_test(tc, f_spac_post);
  tcase_add_test(tc, f_hash_post);
  tcase_add_test(tc, f_fzer_post);
  tcase_add_test(tc, f_mins_negt);
  tcase_add_test(tc, f_plus_negt);
  tcase_add_test(tc, f_spac_negt);
  tcase_add_test(tc, f_hash_negt);
  tcase_add_test(tc, f_fzer_negt);
  tcase_add_test(tc, f_mins_small);
  tcase_add_test(tc, f_plus_small);
  tcase_add_test(tc, f_spac_small);
  tcase_add_test(tc, f_hash_small);
  tcase_add_test(tc, f_fzer_small);
  tcase_add_test(tc, f_mins_large);
  tcase_add_test(tc, f_plus_large);
  tcase_add_test(tc, f_spac_large);
  tcase_add_test(tc, f_hash_large);
  tcase_add_test(tc, f_fzer_large);
  tcase_add_test(tc, f_width_post);
  tcase_add_test(tc, f_zrpc_post);
  tcase_add_test(tc, f_prec_post);
  tcase_add_test(tc, f_width_negt);
  tcase_add_test(tc, f_zrpc_negt);
  tcase_add_test(tc, f_prec_negt);
  tcase_add_test(tc, f_width_small);
  tcase_add_test(tc, f_zrpc_small);
  tcase_add_test(tc, f_prec_small);
  tcase_add_test(tc, f_width_large);
  tcase_add_test(tc, f_zrpc_large);
  tcase_add_test(tc, f_prec_large);
  tcase_add_test(tc, f_width_prec_post);
  tcase_add_test(tc, f_width_prec_negt);
  tcase_add_test(tc, f_width_prec_small);
  tcase_add_test(tc, f_width_prec_large);
  tcase_add_test(tc, f_width_mins_post);
  tcase_add_test(tc, f_width_plus_post);
  tcase_add_test(tc, f_width_spac_post);
  tcase_add_test(tc, f_width_hash_post);
  tcase_add_test(tc, f_width_fzer_post);
  tcase_add_test(tc, f_width_mins_negt);
  tcase_add_test(tc, f_width_plus_negt);
  tcase_add_test(tc, f_width_spac_negt);
  tcase_add_test(tc, f_width_hash_negt);
  tcase_add_test(tc, f_width_fzer_negt);
  tcase_add_test(tc, f_width_mins_small);
  tcase_add_test(tc, f_width_plus_small);
  tcase_add_test(tc, f_width_spac_small);
  tcase_add_test(tc, f_width_hash_small);
  tcase_add_test(tc, f_width_fzer_small);
  tcase_add_test(tc, f_width_mins_large);
  tcase_add_test(tc, f_width_plus_large);
  tcase_add_test(tc, f_width_spac_large);
  tcase_add_test(tc, f_width_hash_large);
  tcase_add_test(tc, f_width_fzer_large);
  tcase_add_test(tc, f_zrwth_plus_post);
  tcase_add_test(tc, f_zrwth_spac_post);
  tcase_add_test(tc, f_zrwth_hash_post);
  tcase_add_test(tc, f_zrwth_plus_negt);
  tcase_add_test(tc, f_zrwth_spac_negt);
  tcase_add_test(tc, f_zrwth_hash_negt);
  tcase_add_test(tc, f_zrwth_plus_small);
  tcase_add_test(tc, f_zrwth_spac_small);
  tcase_add_test(tc, f_zrwth_hash_small);
  tcase_add_test(tc, f_zrwth_plus_large);
  tcase_add_test(tc, f_zrwth_spac_large);
  tcase_add_test(tc, f_zrwth_hash_large);
  tcase_add_test(tc, f_prec_mins_post);
  tcase_add_test(tc, f_prec_plus_post);
  tcase_add_test(tc, f_prec_spac_post);
  tcase_add_test(tc, f_prec_hash_post);
  tcase_add_test(tc, f_prec_fzer_post);
  tcase_add_test(tc, f_prec_mins_negt);
  tcase_add_test(tc, f_prec_plus_negt);
  tcase_add_test(tc, f_prec_spac_negt);
  tcase_add_test(tc, f_prec_hash_negt);
  tcase_add_test(tc, f_prec_fzer_negt);
  tcase_add_test(tc, f_prec_mins_small);
  tcase_add_test(tc, f_prec_plus_small);
  tcase_add_test(tc, f_prec_spac_small);
  tcase_add_test(tc, f_prec_hash_small);
  tcase_add_test(tc, f_prec_fzer_small);
  tcase_add_test(tc, f_prec_mins_large);
  tcase_add_test(tc, f_prec_plus_large);
  tcase_add_test(tc, f_prec_spac_large);
  tcase_add_test(tc, f_prec_hash_large);
  tcase_add_test(tc, f_prec_fzer_large);
  tcase_add_test(tc, f_zrpc_mins_post);
  tcase_add_test(tc, f_zrpc_plus_post);
  tcase_add_test(tc, f_zrpc_spac_post);
  tcase_add_test(tc, f_zrpc_hash_post);
  tcase_add_test(tc, f_zrpc_fzer_post);
  tcase_add_test(tc, f_zrpc_mins_negt);
  tcase_add_test(tc, f_zrpc_plus_negt);
  tcase_add_test(tc, f_zrpc_spac_negt);
  tcase_add_test(tc, f_zrpc_hash_negt);
  tcase_add_test(tc, f_zrpc_fzer_negt);
  tcase_add_test(tc, f_zrpc_mins_small);
  tcase_add_test(tc, f_zrpc_plus_small);
  tcase_add_test(tc, f_zrpc_spac_small);
  tcase_add_test(tc, f_zrpc_hash_small);
  tcase_add_test(tc, f_zrpc_fzer_small);
  tcase_add_test(tc, f_zrpc_mins_large);
  tcase_add_test(tc, f_zrpc_plus_large);
  tcase_add_test(tc, f_zrpc_spac_large);
  tcase_add_test(tc, f_zrpc_hash_large);
  tcase_add_test(tc, f_zrpc_fzer_large);
  tcase_add_test(tc, f_width_prec_mins_post);
  tcase_add_test(tc, f_width_prec_plus_post);
  tcase_add_test(tc, f_width_prec_spac_post);
  tcase_add_test(tc, f_width_prec_hash_post);
  tcase_add_test(tc, f_width_prec_fzer_post);
  tcase_add_test(tc, f_width_prec_mins_negt);
  tcase_add_test(tc, f_width_prec_plus_negt);
  tcase_add_test(tc, f_width_prec_spac_negt);
  tcase_add_test(tc, f_width_prec_hash_negt);
  tcase_add_test(tc, f_width_prec_fzer_negt);
  tcase_add_test(tc, f_width_prec_mins_small);
  tcase_add_test(tc, f_width_prec_plus_small);
  tcase_add_test(tc, f_width_prec_spac_small);
  tcase_add_test(tc, f_width_prec_hash_small);
  tcase_add_test(tc, f_width_prec_fzer_small);
  tcase_add_test(tc, f_width_prec_mins_large);
  tcase_add_test(tc, f_width_prec_plus_large);
  tcase_add_test(tc, f_width_prec_spac_large);
  tcase_add_test(tc, f_width_prec_hash_large);
  tcase_add_test(tc, f_width_prec_fzer_large);
  tcase_add_test(tc, f_zrwth_zrpc_plus_post);
  tcase_add_test(tc, f_zrwth_zrpc_spac_post);
  tcase_add_test(tc, f_zrwth_zrpc_hash_post);
  tcase_add_test(tc, f_zrwth_zrpc_plus_negt);
  tcase_add_test(tc, f_zrwth_zrpc_spac_negt);
  tcase_add_test(tc, f_zrwth_zrpc_hash_negt);
  tcase_add_test(tc, f_zrwth_zrpc_plus_small);
  tcase_add_test(tc, f_zrwth_zrpc_spac_small);
  tcase_add_test(tc, f_zrwth_zrpc_hash_small);
  tcase_add_test(tc, f_zrwth_zrpc_plus_large);
  tcase_add_test(tc, f_zrwth_zrpc_spac_large);
  tcase_add_test(tc, f_zrwth_zrpc_hash_large);
  tcase_add_test(tc, f_dynamic_width_post);
  tcase_add_test(tc, f_dynamic_width_negt);
  tcase_add_test(tc, f_dynamic_width_small);
  tcase_add_test(tc, f_dynamic_width_large);
  tcase_add_test(tc, f_dynamic_prec_post);
  tcase_add_test(tc, f_dynamic_prec_negt);
  tcase_add_test(tc, f_dynamic_prec_small);
  tcase_add_test(tc, f_dynamic_prec_large);
  tcase_add_test(tc, f_dynamic_width_prec_post);
  tcase_add_test(tc, f_dynamic_width_prec_negt);
  tcase_add_test(tc, f_dynamic_width_prec_small);
  tcase_add_test(tc, f_dynamic_width_prec_large);
  tcase_add_test(tc, g_mins_post);
  tcase_add_test(tc, g_plus_post);
  tcase_add_test(tc, g_spac_post);
  tcase_add_test(tc, g_hash_post);
  tcase_add_test(tc, g_fzer_post);
  tcase_add_test(tc, g_mins_negt);
  tcase_add_test(tc, g_plus_negt);
  tcase_add_test(tc, g_spac_negt);
  tcase_add_test(tc, g_hash_negt);
  tcase_add_test(tc, g_fzer_negt);
  tcase_add_test(tc, g_mins_small);
  tcase_add_test(tc, g_plus_small);
  tcase_add_test(tc, g_spac_small);
  tcase_add_test(tc, g_hash_small);
  tcase_add_test(tc, g_fzer_small);
  tcase_add_test(tc, g_mins_large);
  tcase_add_test(tc, g_plus_large);
  tcase_add_test(tc, g_spac_large);
  tcase_add_test(tc, g_hash_large);
  tcase_add_test(tc, g_fzer_large);
  tcase_add_test(tc, g_width_post);
  tcase_add_test(tc, g_zrpc_post);
  tcase_add_test(tc, g_prec_post);
  tcase_add_test(tc, g_width_negt);
  tcase_add_test(tc, g_zrpc_negt);
  tcase_add_test(tc, g_prec_negt);
  tcase_add_test(tc, g_width_small);
  tcase_add_test(tc, g_zrpc_small);
  tcase_add_test(tc, g_prec_small);
  tcase_add_test(tc, g_width_large);
  tcase_add_test(tc, g_zrpc_large);
  tcase_add_test(tc, g_prec_large);
  tcase_add_test(tc, g_width_prec_post);
  tcase_add_test(tc, g_width_prec_negt);
  tcase_add_test(tc, g_width_prec_small);
  tcase_add_test(tc, g_width_prec_large);
  tcase_add_test(tc, g_width_mins_post);
  tcase_add_test(tc, g_width_plus_post);
  tcase_add_test(tc, g_width_spac_post);
  tcase_add_test(tc, g_width_hash_post);
  tcase_add_test(tc, g_width_fzer_post);
  tcase_add_test(tc, g_width_mins_negt);
  tcase_add_test(tc, g_width_plus_negt);
  tcase_add_test(tc, g_width_spac_negt);
  tcase_add_test(tc, g_width_hash_negt);
  tcase_add_test(tc, g_width_fzer_negt);
  tcase_add_test(tc, g_width_mins_small);
  tcase_add_test(tc, g_width_plus_small);
  tcase_add_test(tc, g_width_spac_small);
  tcase_add_test(tc, g_width_hash_small);
  tcase_add_test(tc, g_width_fzer_small);
  tcase_add_test(tc, g_width_mins_large);
  tcase_add_test(tc, g_width_plus_large);
  tcase_add_test(tc, g_width_spac_large);
  tcase_add_test(tc, g_width_hash_large);
  tcase_add_test(tc, g_width_fzer_large);
  tcase_add_test(tc, g_zrwth_plus_post);
  tcase_add_test(tc, g_zrwth_spac_post);
  tcase_add_test(tc, g_zrwth_hash_post);
  tcase_add_test(tc, g_zrwth_plus_negt);
  tcase_add_test(tc, g_zrwth_spac_negt);
  tcase_add_test(tc, g_zrwth_hash_negt);
  tcase_add_test(tc, g_zrwth_plus_small);
  tcase_add_test(tc, g_zrwth_spac_small);
  tcase_add_test(tc, g_zrwth_hash_small);
  tcase_add_test(tc, g_zrwth_plus_large);
  tcase_add_test(tc, g_zrwth_spac_large);
  tcase_add_test(tc, g_zrwth_hash_large);
  tcase_add_test(tc, g_prec_mins_post);
  tcase_add_test(tc, g_prec_plus_post);
  tcase_add_test(tc, g_prec_spac_post);
  tcase_add_test(tc, g_prec_hash_post);
  tcase_add_test(tc, g_prec_fzer_post);
  tcase_add_test(tc, g_prec_mins_negt);
  tcase_add_test(tc, g_prec_plus_negt);
  tcase_add_test(tc, g_prec_spac_negt);
  tcase_add_test(tc, g_prec_hash_negt);
  tcase_add_test(tc, g_prec_fzer_negt);
  tcase_add_test(tc, g_prec_mins_small);
  tcase_add_test(tc, g_prec_plus_small);
  tcase_add_test(tc, g_prec_spac_small);
  tcase_add_test(tc, g_prec_hash_small);
  tcase_add_test(tc, g_prec_fzer_small);
  tcase_add_test(tc, g_prec_mins_large);
  tcase_add_test(tc, g_prec_plus_large);
  tcase_add_test(tc, g_prec_spac_large);
  tcase_add_test(tc, g_prec_hash_large);
  tcase_add_test(tc, g_prec_fzer_large);
  tcase_add_test(tc, g_zrpc_mins_post);
  tcase_add_test(tc, g_zrpc_plus_post);
  tcase_add_test(tc, g_zrpc_spac_post);
  tcase_add_test(tc, g_zrpc_hash_post);
  tcase_add_test(tc, g_zrpc_fzer_post);
  tcase_add_test(tc, g_zrpc_mins_negt);
  tcase_add_test(tc, g_zrpc_plus_negt);
  tcase_add_test(tc, g_zrpc_spac_negt);
  tcase_add_test(tc, g_zrpc_hash_negt);
  tcase_add_test(tc, g_zrpc_fzer_negt);
  tcase_add_test(tc, g_zrpc_mins_small);
  tcase_add_test(tc, g_zrpc_plus_small);
  tcase_add_test(tc, g_zrpc_spac_small);
  tcase_add_test(tc, g_zrpc_hash_small);
  tcase_add_test(tc, g_zrpc_fzer_small);
  tcase_add_test(tc, g_zrpc_mins_large);
  tcase_add_test(tc, g_zrpc_plus_large);
  tcase_add_test(tc, g_zrpc_spac_large);
  tcase_add_test(tc, g_zrpc_hash_large);
  tcase_add_test(tc, g_zrpc_fzer_large);
  tcase_add_test(tc, g_width_prec_mins_post);
  tcase_add_test(tc, g_width_prec_plus_post);
  tcase_add_test(tc, g_width_prec_spac_post);
  tcase_add_test(tc, g_width_prec_hash_post);
  tcase_add_test(tc, g_width_prec_fzer_post);
  tcase_add_test(tc, g_width_prec_mins_negt);
  tcase_add_test(tc, g_width_prec_plus_negt);
  tcase_add_test(tc, g_width_prec_spac_negt);
  tcase_add_test(tc, g_width_prec_hash_negt);
  tcase_add_test(tc, g_width_prec_fzer_negt);
  tcase_add_test(tc, g_width_prec_mins_small);
  tcase_add_test(tc, g_width_prec_plus_small);
  tcase_add_test(tc, g_width_prec_spac_small);
  tcase_add_test(tc, g_width_prec_hash_small);
  tcase_add_test(tc, g_width_prec_fzer_small);
  tcase_add_test(tc, g_width_prec_mins_large);
  tcase_add_test(tc, g_width_prec_plus_large);
  tcase_add_test(tc, g_width_prec_spac_large);
  tcase_add_test(tc, g_width_prec_hash_large);
  tcase_add_test(tc, g_width_prec_fzer_large);
  tcase_add_test(tc, g_zrwth_zrpc_plus_post);
  tcase_add_test(tc, g_zrwth_zrpc_spac_post);
  tcase_add_test(tc, g_zrwth_zrpc_hash_post);
  tcase_add_test(tc, g_zrwth_zrpc_plus_negt);
  tcase_add_test(tc, g_zrwth_zrpc_spac_negt);
  tcase_add_test(tc, g_zrwth_zrpc_hash_negt);
  tcase_add_test(tc, g_zrwth_zrpc_plus_small);
  tcase_add_test(tc, g_zrwth_zrpc_spac_small);
  tcase_add_test(tc, g_zrwth_zrpc_hash_small);
  tcase_add_test(tc, g_zrwth_zrpc_plus_large);
  tcase_add_test(tc, g_zrwth_zrpc_spac_large);
  tcase_add_test(tc, g_zrwth_zrpc_hash_large);
  tcase_add_test(tc, g_dynamic_width_post);
  tcase_add_test(tc, g_dynamic_width_negt);
  tcase_add_test(tc, g_dynamic_width_small);
  tcase_add_test(tc, g_dynamic_width_large);
  tcase_add_test(tc, g_dynamic_prec_post);
  tcase_add_test(tc, g_dynamic_prec_negt);
  tcase_add_test(tc, g_dynamic_prec_small);
  tcase_add_test(tc, g_dynamic_prec_large);
  tcase_add_test(tc, g_dynamic_width_prec_post);
  tcase_add_test(tc, g_dynamic_width_prec_negt);
  tcase_add_test(tc, g_dynamic_width_prec_small);
  tcase_add_test(tc, g_dynamic_width_prec_large);
  tcase_add_test(tc, G_mins_post);
  tcase_add_test(tc, G_plus_post);
  tcase_add_test(tc, G_spac_post);
  tcase_add_test(tc, G_hash_post);
  tcase_add_test(tc, G_fzer_post);
  tcase_add_test(tc, G_mins_negt);
  tcase_add_test(tc, G_plus_negt);
  tcase_add_test(tc, G_spac_negt);
  tcase_add_test(tc, G_hash_negt);
  tcase_add_test(tc, G_fzer_negt);
  tcase_add_test(tc, G_mins_small);
  tcase_add_test(tc, G_plus_small);
  tcase_add_test(tc, G_spac_small);
  tcase_add_test(tc, G_hash_small);
  tcase_add_test(tc, G_fzer_small);
  tcase_add_test(tc, G_mins_large);
  tcase_add_test(tc, G_plus_large);
  tcase_add_test(tc, G_spac_large);
  tcase_add_test(tc, G_hash_large);
  tcase_add_test(tc, G_fzer_large);
  tcase_add_test(tc, G_width_post);
  tcase_add_test(tc, G_zrpc_post);
  tcase_add_test(tc, G_prec_post);
  tcase_add_test(tc, G_width_negt);
  tcase_add_test(tc, G_zrpc_negt);
  tcase_add_test(tc, G_prec_negt);
  tcase_add_test(tc, G_width_small);
  tcase_add_test(tc, G_zrpc_small);
  tcase_add_test(tc, G_prec_small);
  tcase_add_test(tc, G_width_large);
  tcase_add_test(tc, G_zrpc_large);
  tcase_add_test(tc, G_prec_large);
  tcase_add_test(tc, G_width_prec_post);
  tcase_add_test(tc, G_width_prec_negt);
  tcase_add_test(tc, G_width_prec_small);
  tcase_add_test(tc, G_width_prec_large);
  tcase_add_test(tc, G_width_mins_post);
  tcase_add_test(tc, G_width_plus_post);
  tcase_add_test(tc, G_width_spac_post);
  tcase_add_test(tc, G_width_hash_post);
  tcase_add_test(tc, G_width_fzer_post);
  tcase_add_test(tc, G_width_mins_negt);
  tcase_add_test(tc, G_width_plus_negt);
  tcase_add_test(tc, G_width_spac_negt);
  tcase_add_test(tc, G_width_hash_negt);
  tcase_add_test(tc, G_width_fzer_negt);
  tcase_add_test(tc, G_width_mins_small);
  tcase_add_test(tc, G_width_plus_small);
  tcase_add_test(tc, G_width_spac_small);
  tcase_add_test(tc, G_width_hash_small);
  tcase_add_test(tc, G_width_fzer_small);
  tcase_add_test(tc, G_width_mins_large);
  tcase_add_test(tc, G_width_plus_large);
  tcase_add_test(tc, G_width_spac_large);
  tcase_add_test(tc, G_width_hash_large);
  tcase_add_test(tc, G_width_fzer_large);
  tcase_add_test(tc, G_zrwth_plus_post);
  tcase_add_test(tc, G_zrwth_spac_post);
  tcase_add_test(tc, G_zrwth_hash_post);
  tcase_add_test(tc, G_zrwth_plus_negt);
  tcase_add_test(tc, G_zrwth_spac_negt);
  tcase_add_test(tc, G_zrwth_hash_negt);
  tcase_add_test(tc, G_zrwth_plus_small);
  tcase_add_test(tc, G_zrwth_spac_small);
  tcase_add_test(tc, G_zrwth_hash_small);
  tcase_add_test(tc, G_zrwth_plus_large);
  tcase_add_test(tc, G_zrwth_spac_large);
  tcase_add_test(tc, G_zrwth_hash_large);
  tcase_add_test(tc, G_prec_mins_post);
  tcase_add_test(tc, G_prec_plus_post);
  tcase_add_test(tc, G_prec_spac_post);
  tcase_add_test(tc, G_prec_hash_post);
  tcase_add_test(tc, G_prec_fzer_post);
  tcase_add_test(tc, G_prec_mins_negt);
  tcase_add_test(tc, G_prec_plus_negt);
  tcase_add_test(tc, G_prec_spac_negt);
  tcase_add_test(tc, G_prec_hash_negt);
  tcase_add_test(tc, G_prec_fzer_negt);
  tcase_add_test(tc, G_prec_mins_small);
  tcase_add_test(tc, G_prec_plus_small);
  tcase_add_test(tc, G_prec_spac_small);
  tcase_add_test(tc, G_prec_hash_small);
  tcase_add_test(tc, G_prec_fzer_small);
  tcase_add_test(tc, G_prec_mins_large);
  tcase_add_test(tc, G_prec_plus_large);
  tcase_add_test(tc, G_prec_spac_large);
  tcase_add_test(tc, G_prec_hash_large);
  tcase_add_test(tc, G_prec_fzer_large);
  tcase_add_test(tc, G_zrpc_mins_post);
  tcase_add_test(tc, G_zrpc_plus_post);
  tcase_add_test(tc, G_zrpc_spac_post);
  tcase_add_test(tc, G_zrpc_hash_post);
  tcase_add_test(tc, G_zrpc_fzer_post);
  tcase_add_test(tc, G_zrpc_mins_negt);
  tcase_add_test(tc, G_zrpc_plus_negt);
  tcase_add_test(tc, G_zrpc_spac_negt);
  tcase_add_test(tc, G_zrpc_hash_negt);
  tcase_add_test(tc, G_zrpc_fzer_negt);
  tcase_add_test(tc, G_zrpc_mins_small);
  tcase_add_test(tc, G_zrpc_plus_small);
  tcase_add_test(tc, G_zrpc_spac_small);
  tcase_add_test(tc, G_zrpc_hash_small);
  tcase_add_test(tc, G_zrpc_fzer_small);
  tcase_add_test(tc, G_zrpc_mins_large);
  tcase_add_test(tc, G_zrpc_plus_large);
  tcase_add_test(tc, G_zrpc_spac_large);
  tcase_add_test(tc, G_zrpc_hash_large);
  tcase_add_test(tc, G_zrpc_fzer_large);
  tcase_add_test(tc, G_width_prec_mins_post);
  tcase_add_test(tc, G_width_prec_plus_post);
  tcase_add_test(tc, G_width_prec_spac_post);
  tcase_add_test(tc, G_width_prec_hash_post);
  tcase_add_test(tc, G_width_prec_fzer_post);
  tcase_add_test(tc, G_width_prec_mins_negt);
  tcase_add_test(tc, G_width_prec_plus_negt);
  tcase_add_test(tc, G_width_prec_spac_negt);
  tcase_add_test(tc, G_width_prec_hash_negt);
  tcase_add_test(tc, G_width_prec_fzer_negt);
  tcase_add_test(tc, G_width_prec_mins_small);
  tcase_add_test(tc, G_width_prec_plus_small);
  tcase_add_test(tc, G_width_prec_spac_small);
  tcase_add_test(tc, G_width_prec_hash_small);
  tcase_add_test(tc, G_width_prec_fzer_small);
  tcase_add_test(tc, G_width_prec_mins_large);
  tcase_add_test(tc, G_width_prec_plus_large);
  tcase_add_test(tc, G_width_prec_spac_large);
  tcase_add_test(tc, G_width_prec_hash_large);
  tcase_add_test(tc, G_width_prec_fzer_large);
  tcase_add_test(tc, G_zrwth_zrpc_plus_post);
  tcase_add_test(tc, G_zrwth_zrpc_spac_post);
  tcase_add_test(tc, G_zrwth_zrpc_hash_post);
  tcase_add_test(tc, G_zrwth_zrpc_plus_negt);
  tcase_add_test(tc, G_zrwth_zrpc_spac_negt);
  tcase_add_test(tc, G_zrwth_zrpc_hash_negt);
  tcase_add_test(tc, G_zrwth_zrpc_plus_small);
  tcase_add_test(tc, G_zrwth_zrpc_spac_small);
  tcase_add_test(tc, G_zrwth_zrpc_hash_small);
  tcase_add_test(tc, G_zrwth_zrpc_plus_large);
  tcase_add_test(tc, G_zrwth_zrpc_spac_large);
  tcase_add_test(tc, G_zrwth_zrpc_hash_large);
  tcase_add_test(tc, G_dynamic_width_post);
  tcase_add_test(tc, G_dynamic_width_negt);
  tcase_add_test(tc, G_dynamic_width_small);
  tcase_add_test(tc, G_dynamic_width_large);
  tcase_add_test(tc, G_dynamic_prec_post);
  tcase_add_test(tc, G_dynamic_prec_negt);
  tcase_add_test(tc, G_dynamic_prec_small);
  tcase_add_test(tc, G_dynamic_prec_large);
  tcase_add_test(tc, G_dynamic_width_prec_post);
  tcase_add_test(tc, G_dynamic_width_prec_negt);
  tcase_add_test(tc, G_dynamic_width_prec_small);
  tcase_add_test(tc, G_dynamic_width_prec_large);
  tcase_add_test(tc, le_mins_post);
  tcase_add_test(tc, le_plus_post);
  tcase_add_test(tc, le_spac_post);
  tcase_add_test(tc, le_hash_post);
  tcase_add_test(tc, le_fzer_post);
  tcase_add_test(tc, le_mins_negt);
  tcase_add_test(tc, le_plus_negt);
  tcase_add_test(tc, le_spac_negt);
  tcase_add_test(tc, le_hash_negt);
  tcase_add_test(tc, le_fzer_negt);
  tcase_add_test(tc, le_mins_small);
  tcase_add_test(tc, le_plus_small);
  tcase_add_test(tc, le_spac_small);
  tcase_add_test(tc, le_hash_small);
  tcase_add_test(tc, le_fzer_small);
  tcase_add_test(tc, le_mins_large);
  tcase_add_test(tc, le_plus_large);
  tcase_add_test(tc, le_spac_large);
  tcase_add_test(tc, le_hash_large);
  tcase_add_test(tc, le_fzer_large);
  tcase_add_test(tc, le_width_post);
  tcase_add_test(tc, le_zrpc_post);
  tcase_add_test(tc, le_prec_post);
  tcase_add_test(tc, le_width_negt);
  tcase_add_test(tc, le_zrpc_negt);
  tcase_add_test(tc, le_prec_negt);
  tcase_add_test(tc, le_width_small);
  tcase_add_test(tc, le_zrpc_small);
  tcase_add_test(tc, le_prec_small);
  tcase_add_test(tc, le_width_large);
  tcase_add_test(tc, le_zrpc_large);
  tcase_add_test(tc, le_prec_large);
  tcase_add_test(tc, le_width_prec_post);
  tcase_add_test(tc, le_width_prec_negt);
  tcase_add_test(tc, le_width_prec_small);
  tcase_add_test(tc, le_width_prec_large);
  tcase_add_test(tc, le_width_mins_post);
  tcase_add_test(tc, le_width_plus_post);
  tcase_add_test(tc, le_width_spac_post);
  tcase_add_test(tc, le_width_hash_post);
  tcase_add_test(tc, le_width_fzer_post);
  tcase_add_test(tc, le_width_mins_negt);
  tcase_add_test(tc, le_width_plus_negt);
  tcase_add_test(tc, le_width_spac_negt);
  tcase_add_test(tc, le_width_hash_negt);
  tcase_add_test(tc, le_width_fzer_negt);
  tcase_add_test(tc, le_width_mins_small);
  tcase_add_test(tc, le_width_plus_small);
  tcase_add_test(tc, le_width_spac_small);
  tcase_add_test(tc, le_width_hash_small);
  tcase_add_test(tc, le_width_fzer_small);
  tcase_add_test(tc, le_width_mins_large);
  tcase_add_test(tc, le_width_plus_large);
  tcase_add_test(tc, le_width_spac_large);
  tcase_add_test(tc, le_width_hash_large);
  tcase_add_test(tc, le_width_fzer_large);
  tcase_add_test(tc, le_zrwth_plus_post);
  tcase_add_test(tc, le_zrwth_spac_post);
  tcase_add_test(tc, le_zrwth_hash_post);
  tcase_add_test(tc, le_zrwth_plus_negt);
  tcase_add_test(tc, le_zrwth_spac_negt);
  tcase_add_test(tc, le_zrwth_hash_negt);
  tcase_add_test(tc, le_zrwth_plus_small);
  tcase_add_test(tc, le_zrwth_spac_small);
  tcase_add_test(tc, le_zrwth_hash_small);
  tcase_add_test(tc, le_zrwth_plus_large);
  tcase_add_test(tc, le_zrwth_spac_large);
  tcase_add_test(tc, le_zrwth_hash_large);
  tcase_add_test(tc, le_prec_mins_post);
  tcase_add_test(tc, le_prec_plus_post);
  tcase_add_test(tc, le_prec_spac_post);
  tcase_add_test(tc, le_prec_hash_post);
  tcase_add_test(tc, le_prec_fzer_post);
  tcase_add_test(tc, le_prec_mins_negt);
  tcase_add_test(tc, le_prec_plus_negt);
  tcase_add_test(tc, le_prec_spac_negt);
  tcase_add_test(tc, le_prec_hash_negt);
  tcase_add_test(tc, le_prec_fzer_negt);
  tcase_add_test(tc, le_prec_mins_small);
  tcase_add_test(tc, le_prec_plus_small);
  tcase_add_test(tc, le_prec_spac_small);
  tcase_add_test(tc, le_prec_hash_small);
  tcase_add_test(tc, le_prec_fzer_small);
  tcase_add_test(tc, le_prec_mins_large);
  tcase_add_test(tc, le_prec_plus_large);
  tcase_add_test(tc, le_prec_spac_large);
  tcase_add_test(tc, le_prec_hash_large);
  tcase_add_test(tc, le_prec_fzer_large);
  tcase_add_test(tc, le_zrpc_mins_post);
  tcase_add_test(tc, le_zrpc_plus_post);
  tcase_add_test(tc, le_zrpc_spac_post);
  tcase_add_test(tc, le_zrpc_hash_post);
  tcase_add_test(tc, le_zrpc_fzer_post);
  tcase_add_test(tc, le_zrpc_mins_negt);
  tcase_add_test(tc, le_zrpc_plus_negt);
  tcase_add_test(tc, le_zrpc_spac_negt);
  tcase_add_test(tc, le_zrpc_hash_negt);
  tcase_add_test(tc, le_zrpc_fzer_negt);
  tcase_add_test(tc, le_zrpc_mins_small);
  tcase_add_test(tc, le_zrpc_plus_small);
  tcase_add_test(tc, le_zrpc_spac_small);
  tcase_add_test(tc, le_zrpc_hash_small);
  tcase_add_test(tc, le_zrpc_fzer_small);
  tcase_add_test(tc, le_zrpc_mins_large);
  tcase_add_test(tc, le_zrpc_plus_large);
  tcase_add_test(tc, le_zrpc_spac_large);
  tcase_add_test(tc, le_zrpc_hash_large);
  tcase_add_test(tc, le_zrpc_fzer_large);
  tcase_add_test(tc, le_width_prec_mins_post);
  tcase_add_test(tc, le_width_prec_plus_post);
  tcase_add_test(tc, le_width_prec_spac_post);
  tcase_add_test(tc, le_width_prec_hash_post);
  tcase_add_test(tc, le_width_prec_fzer_post);
  tcase_add_test(tc, le_width_prec_mins_negt);
  tcase_add_test(tc, le_width_prec_plus_negt);
  tcase_add_test(tc, le_width_prec_spac_negt);
  tcase_add_test(tc, le_width_prec_hash_negt);
  tcase_add_test(tc, le_width_prec_fzer_negt);
  tcase_add_test(tc, le_width_prec_mins_small);
  tcase_add_test(tc, le_width_prec_plus_small);
  tcase_add_test(tc, le_width_prec_spac_small);
  tcase_add_test(tc, le_width_prec_hash_small);
  tcase_add_test(tc, le_width_prec_fzer_small);
  tcase_add_test(tc, le_width_prec_mins_large);
  tcase_add_test(tc, le_width_prec_plus_large);
  tcase_add_test(tc, le_width_prec_spac_large);
  tcase_add_test(tc, le_width_prec_hash_large);
  tcase_add_test(tc, le_width_prec_fzer_large);
  tcase_add_test(tc, le_zrwth_zrpc_plus_post);
  tcase_add_test(tc, le_zrwth_zrpc_spac_post);
  tcase_add_test(tc, le_zrwth_zrpc_hash_post);
  tcase_add_test(tc, le_zrwth_zrpc_plus_negt);
  tcase_add_test(tc, le_zrwth_zrpc_spac_negt);
  tcase_add_test(tc, le_zrwth_zrpc_hash_negt);
  tcase_add_test(tc, le_zrwth_zrpc_plus_small);
  tcase_add_test(tc, le_zrwth_zrpc_spac_small);
  tcase_add_test(tc, le_zrwth_zrpc_hash_small);
  tcase_add_test(tc, le_zrwth_zrpc_plus_large);
  tcase_add_test(tc, le_zrwth_zrpc_spac_large);
  tcase_add_test(tc, le_zrwth_zrpc_hash_large);
  tcase_add_test(tc, le_dynamic_width_post);
  tcase_add_test(tc, le_dynamic_width_negt);
  tcase_add_test(tc, le_dynamic_width_small);
  tcase_add_test(tc, le_dynamic_width_large);
  tcase_add_test(tc, le_dynamic_prec_post);
  tcase_add_test(tc, le_dynamic_prec_negt);
  tcase_add_test(tc, le_dynamic_prec_small);
  tcase_add_test(tc, le_dynamic_prec_large);
  tcase_add_test(tc, le_dynamic_width_prec_post);
  tcase_add_test(tc, le_dynamic_width_prec_negt);
  tcase_add_test(tc, le_dynamic_width_prec_small);
  tcase_add_test(tc, le_dynamic_width_prec_large);
  tcase_add_test(tc, lE_mins_post);
  tcase_add_test(tc, lE_plus_post);
  tcase_add_test(tc, lE_spac_post);
  tcase_add_test(tc, lE_hash_post);
  tcase_add_test(tc, lE_fzer_post);
  tcase_add_test(tc, lE_mins_negt);
  tcase_add_test(tc, lE_plus_negt);
  tcase_add_test(tc, lE_spac_negt);
  tcase_add_test(tc, lE_hash_negt);
  tcase_add_test(tc, lE_fzer_negt);
  tcase_add_test(tc, lE_mins_small);
  tcase_add_test(tc, lE_plus_small);
  tcase_add_test(tc, lE_spac_small);
  tcase_add_test(tc, lE_hash_small);
  tcase_add_test(tc, lE_fzer_small);
  tcase_add_test(tc, lE_mins_large);
  tcase_add_test(tc, lE_plus_large);
  tcase_add_test(tc, lE_spac_large);
  tcase_add_test(tc, lE_hash_large);
  tcase_add_test(tc, lE_fzer_large);
  tcase_add_test(tc, lE_width_post);
  tcase_add_test(tc, lE_zrpc_post);
  tcase_add_test(tc, lE_prec_post);
  tcase_add_test(tc, lE_width_negt);
  tcase_add_test(tc, lE_zrpc_negt);
  tcase_add_test(tc, lE_prec_negt);
  tcase_add_test(tc, lE_width_small);
  tcase_add_test(tc, lE_zrpc_small);
  tcase_add_test(tc, lE_prec_small);
  tcase_add_test(tc, lE_width_large);
  tcase_add_test(tc, lE_zrpc_large);
  tcase_add_test(tc, lE_prec_large);
  tcase_add_test(tc, lE_width_prec_post);
  tcase_add_test(tc, lE_width_prec_negt);
  tcase_add_test(tc, lE_width_prec_small);
  tcase_add_test(tc, lE_width_prec_large);
  tcase_add_test(tc, lE_width_mins_post);
  tcase_add_test(tc, lE_width_plus_post);
  tcase_add_test(tc, lE_width_spac_post);
  tcase_add_test(tc, lE_width_hash_post);
  tcase_add_test(tc, lE_width_fzer_post);
  tcase_add_test(tc, lE_width_mins_negt);
  tcase_add_test(tc, lE_width_plus_negt);
  tcase_add_test(tc, lE_width_spac_negt);
  tcase_add_test(tc, lE_width_hash_negt);
  tcase_add_test(tc, lE_width_fzer_negt);
  tcase_add_test(tc, lE_width_mins_small);
  tcase_add_test(tc, lE_width_plus_small);
  tcase_add_test(tc, lE_width_spac_small);
  tcase_add_test(tc, lE_width_hash_small);
  tcase_add_test(tc, lE_width_fzer_small);
  tcase_add_test(tc, lE_width_mins_large);
  tcase_add_test(tc, lE_width_plus_large);
  tcase_add_test(tc, lE_width_spac_large);
  tcase_add_test(tc, lE_width_hash_large);
  tcase_add_test(tc, lE_width_fzer_large);
  tcase_add_test(tc, lE_zrwth_plus_post);
  tcase_add_test(tc, lE_zrwth_spac_post);
  tcase_add_test(tc, lE_zrwth_hash_post);
  tcase_add_test(tc, lE_zrwth_plus_negt);
  tcase_add_test(tc, lE_zrwth_spac_negt);
  tcase_add_test(tc, lE_zrwth_hash_negt);
  tcase_add_test(tc, lE_zrwth_plus_small);
  tcase_add_test(tc, lE_zrwth_spac_small);
  tcase_add_test(tc, lE_zrwth_hash_small);
  tcase_add_test(tc, lE_zrwth_plus_large);
  tcase_add_test(tc, lE_zrwth_spac_large);
  tcase_add_test(tc, lE_zrwth_hash_large);
  tcase_add_test(tc, lE_prec_mins_post);
  tcase_add_test(tc, lE_prec_plus_post);
  tcase_add_test(tc, lE_prec_spac_post);
  tcase_add_test(tc, lE_prec_hash_post);
  tcase_add_test(tc, lE_prec_fzer_post);
  tcase_add_test(tc, lE_prec_mins_negt);
  tcase_add_test(tc, lE_prec_plus_negt);
  tcase_add_test(tc, lE_prec_spac_negt);
  tcase_add_test(tc, lE_prec_hash_negt);
  tcase_add_test(tc, lE_prec_fzer_negt);
  tcase_add_test(tc, lE_prec_mins_small);
  tcase_add_test(tc, lE_prec_plus_small);
  tcase_add_test(tc, lE_prec_spac_small);
  tcase_add_test(tc, lE_prec_hash_small);
  tcase_add_test(tc, lE_prec_fzer_small);
  tcase_add_test(tc, lE_prec_mins_large);
  tcase_add_test(tc, lE_prec_plus_large);
  tcase_add_test(tc, lE_prec_spac_large);
  tcase_add_test(tc, lE_prec_hash_large);
  tcase_add_test(tc, lE_prec_fzer_large);
  tcase_add_test(tc, lE_zrpc_mins_post);
  tcase_add_test(tc, lE_zrpc_plus_post);
  tcase_add_test(tc, lE_zrpc_spac_post);
  tcase_add_test(tc, lE_zrpc_hash_post);
  tcase_add_test(tc, lE_zrpc_fzer_post);
  tcase_add_test(tc, lE_zrpc_mins_negt);
  tcase_add_test(tc, lE_zrpc_plus_negt);
  tcase_add_test(tc, lE_zrpc_spac_negt);
  tcase_add_test(tc, lE_zrpc_hash_negt);
  tcase_add_test(tc, lE_zrpc_fzer_negt);
  tcase_add_test(tc, lE_zrpc_mins_small);
  tcase_add_test(tc, lE_zrpc_plus_small);
  tcase_add_test(tc, lE_zrpc_spac_small);
  tcase_add_test(tc, lE_zrpc_hash_small);
  tcase_add_test(tc, lE_zrpc_fzer_small);
  tcase_add_test(tc, lE_zrpc_mins_large);
  tcase_add_test(tc, lE_zrpc_plus_large);
  tcase_add_test(tc, lE_zrpc_spac_large);
  tcase_add_test(tc, lE_zrpc_hash_large);
  tcase_add_test(tc, lE_zrpc_fzer_large);
  tcase_add_test(tc, lE_width_prec_mins_post);
  tcase_add_test(tc, lE_width_prec_plus_post);
  tcase_add_test(tc, lE_width_prec_spac_post);
  tcase_add_test(tc, lE_width_prec_hash_post);
  tcase_add_test(tc, lE_width_prec_fzer_post);
  tcase_add_test(tc, lE_width_prec_mins_negt);
  tcase_add_test(tc, lE_width_prec_plus_negt);
  tcase_add_test(tc, lE_width_prec_spac_negt);
  tcase_add_test(tc, lE_width_prec_hash_negt);
  tcase_add_test(tc, lE_width_prec_fzer_negt);
  tcase_add_test(tc, lE_width_prec_mins_small);
  tcase_add_test(tc, lE_width_prec_plus_small);
  tcase_add_test(tc, lE_width_prec_spac_small);
  tcase_add_test(tc, lE_width_prec_hash_small);
  tcase_add_test(tc, lE_width_prec_fzer_small);
  tcase_add_test(tc, lE_width_prec_mins_large);
  tcase_add_test(tc, lE_width_prec_plus_large);
  tcase_add_test(tc, lE_width_prec_spac_large);
  tcase_add_test(tc, lE_width_prec_hash_large);
  tcase_add_test(tc, lE_width_prec_fzer_large);
  tcase_add_test(tc, lE_zrwth_zrpc_plus_post);
  tcase_add_test(tc, lE_zrwth_zrpc_spac_post);
  tcase_add_test(tc, lE_zrwth_zrpc_hash_post);
  tcase_add_test(tc, lE_zrwth_zrpc_plus_negt);
  tcase_add_test(tc, lE_zrwth_zrpc_spac_negt);
  tcase_add_test(tc, lE_zrwth_zrpc_hash_negt);
  tcase_add_test(tc, lE_zrwth_zrpc_plus_small);
  tcase_add_test(tc, lE_zrwth_zrpc_spac_small);
  tcase_add_test(tc, lE_zrwth_zrpc_hash_small);
  tcase_add_test(tc, lE_zrwth_zrpc_plus_large);
  tcase_add_test(tc, lE_zrwth_zrpc_spac_large);
  tcase_add_test(tc, lE_zrwth_zrpc_hash_large);
  tcase_add_test(tc, lE_dynamic_width_post);
  tcase_add_test(tc, lE_dynamic_width_negt);
  tcase_add_test(tc, lE_dynamic_width_small);
  tcase_add_test(tc, lE_dynamic_width_large);
  tcase_add_test(tc, lE_dynamic_prec_post);
  tcase_add_test(tc, lE_dynamic_prec_negt);
  tcase_add_test(tc, lE_dynamic_prec_small);
  tcase_add_test(tc, lE_dynamic_prec_large);
  tcase_add_test(tc, lE_dynamic_width_prec_post);
  tcase_add_test(tc, lE_dynamic_width_prec_negt);
  tcase_add_test(tc, lE_dynamic_width_prec_small);
  tcase_add_test(tc, lE_dynamic_width_prec_large);
  tcase_add_test(tc, lf_mins_post);
  tcase_add_test(tc, lf_plus_post);
  tcase_add_test(tc, lf_spac_post);
  tcase_add_test(tc, lf_hash_post);
  tcase_add_test(tc, lf_fzer_post);
  tcase_add_test(tc, lf_mins_negt);
  tcase_add_test(tc, lf_plus_negt);
  tcase_add_test(tc, lf_spac_negt);
  tcase_add_test(tc, lf_hash_negt);
  tcase_add_test(tc, lf_fzer_negt);
  tcase_add_test(tc, lf_mins_small);
  tcase_add_test(tc, lf_plus_small);
  tcase_add_test(tc, lf_spac_small);
  tcase_add_test(tc, lf_hash_small);
  tcase_add_test(tc, lf_fzer_small);
  tcase_add_test(tc, lf_mins_large);
  tcase_add_test(tc, lf_plus_large);
  tcase_add_test(tc, lf_spac_large);
  tcase_add_test(tc, lf_hash_large);
  tcase_add_test(tc, lf_fzer_large);
  tcase_add_test(tc, lf_width_post);
  tcase_add_test(tc, lf_zrpc_post);
  tcase_add_test(tc, lf_prec_post);
  tcase_add_test(tc, lf_width_negt);
  tcase_add_test(tc, lf_zrpc_negt);
  tcase_add_test(tc, lf_prec_negt);
  tcase_add_test(tc, lf_width_small);
  tcase_add_test(tc, lf_zrpc_small);
  tcase_add_test(tc, lf_prec_small);
  tcase_add_test(tc, lf_width_large);
  tcase_add_test(tc, lf_zrpc_large);
  tcase_add_test(tc, lf_prec_large);
  tcase_add_test(tc, lf_width_prec_post);
  tcase_add_test(tc, lf_width_prec_negt);
  tcase_add_test(tc, lf_width_prec_small);
  tcase_add_test(tc, lf_width_prec_large);
  tcase_add_test(tc, lf_width_mins_post);
  tcase_add_test(tc, lf_width_plus_post);
  tcase_add_test(tc, lf_width_spac_post);
  tcase_add_test(tc, lf_width_hash_post);
  tcase_add_test(tc, lf_width_fzer_post);
  tcase_add_test(tc, lf_width_mins_negt);
  tcase_add_test(tc, lf_width_plus_negt);
  tcase_add_test(tc, lf_width_spac_negt);
  tcase_add_test(tc, lf_width_hash_negt);
  tcase_add_test(tc, lf_width_fzer_negt);
  tcase_add_test(tc, lf_width_mins_small);
  tcase_add_test(tc, lf_width_plus_small);
  tcase_add_test(tc, lf_width_spac_small);
  tcase_add_test(tc, lf_width_hash_small);
  tcase_add_test(tc, lf_width_fzer_small);
  tcase_add_test(tc, lf_width_mins_large);
  tcase_add_test(tc, lf_width_plus_large);
  tcase_add_test(tc, lf_width_spac_large);
  tcase_add_test(tc, lf_width_hash_large);
  tcase_add_test(tc, lf_width_fzer_large);
  tcase_add_test(tc, lf_zrwth_plus_post);
  tcase_add_test(tc, lf_zrwth_spac_post);
  tcase_add_test(tc, lf_zrwth_hash_post);
  tcase_add_test(tc, lf_zrwth_plus_negt);
  tcase_add_test(tc, lf_zrwth_spac_negt);
  tcase_add_test(tc, lf_zrwth_hash_negt);
  tcase_add_test(tc, lf_zrwth_plus_small);
  tcase_add_test(tc, lf_zrwth_spac_small);
  tcase_add_test(tc, lf_zrwth_hash_small);
  tcase_add_test(tc, lf_zrwth_plus_large);
  tcase_add_test(tc, lf_zrwth_spac_large);
  tcase_add_test(tc, lf_zrwth_hash_large);
  tcase_add_test(tc, lf_prec_mins_post);
  tcase_add_test(tc, lf_prec_plus_post);
  tcase_add_test(tc, lf_prec_spac_post);
  tcase_add_test(tc, lf_prec_hash_post);
  tcase_add_test(tc, lf_prec_fzer_post);
  tcase_add_test(tc, lf_prec_mins_negt);
  tcase_add_test(tc, lf_prec_plus_negt);
  tcase_add_test(tc, lf_prec_spac_negt);
  tcase_add_test(tc, lf_prec_hash_negt);
  tcase_add_test(tc, lf_prec_fzer_negt);
  tcase_add_test(tc, lf_prec_mins_small);
  tcase_add_test(tc, lf_prec_plus_small);
  tcase_add_test(tc, lf_prec_spac_small);
  tcase_add_test(tc, lf_prec_hash_small);
  tcase_add_test(tc, lf_prec_fzer_small);
  tcase_add_test(tc, lf_prec_mins_large);
  tcase_add_test(tc, lf_prec_plus_large);
  tcase_add_test(tc, lf_prec_spac_large);
  tcase_add_test(tc, lf_prec_hash_large);
  tcase_add_test(tc, lf_prec_fzer_large);
  tcase_add_test(tc, lf_zrpc_mins_post);
  tcase_add_test(tc, lf_zrpc_plus_post);
  tcase_add_test(tc, lf_zrpc_spac_post);
  tcase_add_test(tc, lf_zrpc_hash_post);
  tcase_add_test(tc, lf_zrpc_fzer_post);
  tcase_add_test(tc, lf_zrpc_mins_negt);
  tcase_add_test(tc, lf_zrpc_plus_negt);
  tcase_add_test(tc, lf_zrpc_spac_negt);
  tcase_add_test(tc, lf_zrpc_hash_negt);
  tcase_add_test(tc, lf_zrpc_fzer_negt);
  tcase_add_test(tc, lf_zrpc_mins_small);
  tcase_add_test(tc, lf_zrpc_plus_small);
  tcase_add_test(tc, lf_zrpc_spac_small);
  tcase_add_test(tc, lf_zrpc_hash_small);
  tcase_add_test(tc, lf_zrpc_fzer_small);
  tcase_add_test(tc, lf_zrpc_mins_large);
  tcase_add_test(tc, lf_zrpc_plus_large);
  tcase_add_test(tc, lf_zrpc_spac_large);
  tcase_add_test(tc, lf_zrpc_hash_large);
  tcase_add_test(tc, lf_zrpc_fzer_large);
  tcase_add_test(tc, lf_width_prec_mins_post);
  tcase_add_test(tc, lf_width_prec_plus_post);
  tcase_add_test(tc, lf_width_prec_spac_post);
  tcase_add_test(tc, lf_width_prec_hash_post);
  tcase_add_test(tc, lf_width_prec_fzer_post);
  tcase_add_test(tc, lf_width_prec_mins_negt);
  tcase_add_test(tc, lf_width_prec_plus_negt);
  tcase_add_test(tc, lf_width_prec_spac_negt);
  tcase_add_test(tc, lf_width_prec_hash_negt);
  tcase_add_test(tc, lf_width_prec_fzer_negt);
  tcase_add_test(tc, lf_width_prec_mins_small);
  tcase_add_test(tc, lf_width_prec_plus_small);
  tcase_add_test(tc, lf_width_prec_spac_small);
  tcase_add_test(tc, lf_width_prec_hash_small);
  tcase_add_test(tc, lf_width_prec_fzer_small);
  tcase_add_test(tc, lf_width_prec_mins_large);
  tcase_add_test(tc, lf_width_prec_plus_large);
  tcase_add_test(tc, lf_width_prec_spac_large);
  tcase_add_test(tc, lf_width_prec_hash_large);
  tcase_add_test(tc, lf_width_prec_fzer_large);
  tcase_add_test(tc, lf_zrwth_zrpc_plus_post);
  tcase_add_test(tc, lf_zrwth_zrpc_spac_post);
  tcase_add_test(tc, lf_zrwth_zrpc_hash_post);
  tcase_add_test(tc, lf_zrwth_zrpc_plus_negt);
  tcase_add_test(tc, lf_zrwth_zrpc_spac_negt);
  tcase_add_test(tc, lf_zrwth_zrpc_hash_negt);
  tcase_add_test(tc, lf_zrwth_zrpc_plus_small);
  tcase_add_test(tc, lf_zrwth_zrpc_spac_small);
  tcase_add_test(tc, lf_zrwth_zrpc_hash_small);
  tcase_add_test(tc, lf_zrwth_zrpc_plus_large);
  tcase_add_test(tc, lf_zrwth_zrpc_spac_large);
  tcase_add_test(tc, lf_zrwth_zrpc_hash_large);
  tcase_add_test(tc, lf_dynamic_width_post);
  tcase_add_test(tc, lf_dynamic_width_negt);
  tcase_add_test(tc, lf_dynamic_width_small);
  tcase_add_test(tc, lf_dynamic_width_large);
  tcase_add_test(tc, lf_dynamic_prec_post);
  tcase_add_test(tc, lf_dynamic_prec_negt);
  tcase_add_test(tc, lf_dynamic_prec_small);
  tcase_add_test(tc, lf_dynamic_prec_large);
  tcase_add_test(tc, lf_dynamic_width_prec_post);
  tcase_add_test(tc, lf_dynamic_width_prec_negt);
  tcase_add_test(tc, lf_dynamic_width_prec_small);
  tcase_add_test(tc, lf_dynamic_width_prec_large);
  tcase_add_test(tc, lg_mins_post);
  tcase_add_test(tc, lg_plus_post);
  tcase_add_test(tc, lg_spac_post);
  tcase_add_test(tc, lg_hash_post);
  tcase_add_test(tc, lg_fzer_post);
  tcase_add_test(tc, lg_mins_negt);
  tcase_add_test(tc, lg_plus_negt);
  tcase_add_test(tc, lg_spac_negt);
  tcase_add_test(tc, lg_hash_negt);
  tcase_add_test(tc, lg_fzer_negt);
  tcase_add_test(tc, lg_mins_small);
  tcase_add_test(tc, lg_plus_small);
  tcase_add_test(tc, lg_spac_small);
  tcase_add_test(tc, lg_hash_small);
  tcase_add_test(tc, lg_fzer_small);
  tcase_add_test(tc, lg_mins_large);
  tcase_add_test(tc, lg_plus_large);
  tcase_add_test(tc, lg_spac_large);
  tcase_add_test(tc, lg_hash_large);
  tcase_add_test(tc, lg_fzer_large);
  tcase_add_test(tc, lg_width_post);
  tcase_add_test(tc, lg_zrpc_post);
  tcase_add_test(tc, lg_prec_post);
  tcase_add_test(tc, lg_width_negt);
  tcase_add_test(tc, lg_zrpc_negt);
  tcase_add_test(tc, lg_prec_negt);
  tcase_add_test(tc, lg_width_small);
  tcase_add_test(tc, lg_zrpc_small);
  tcase_add_test(tc, lg_prec_small);
  tcase_add_test(tc, lg_width_large);
  tcase_add_test(tc, lg_zrpc_large);
  tcase_add_test(tc, lg_prec_large);
  tcase_add_test(tc, lg_width_prec_post);
  tcase_add_test(tc, lg_width_prec_negt);
  tcase_add_test(tc, lg_width_prec_small);
  tcase_add_test(tc, lg_width_prec_large);
  tcase_add_test(tc, lg_width_mins_post);
  tcase_add_test(tc, lg_width_plus_post);
  tcase_add_test(tc, lg_width_spac_post);
  tcase_add_test(tc, lg_width_hash_post);
  tcase_add_test(tc, lg_width_fzer_post);
  tcase_add_test(tc, lg_width_mins_negt);
  tcase_add_test(tc, lg_width_plus_negt);
  tcase_add_test(tc, lg_width_spac_negt);
  tcase_add_test(tc, lg_width_hash_negt);
  tcase_add_test(tc, lg_width_fzer_negt);
  tcase_add_test(tc, lg_width_mins_small);
  tcase_add_test(tc, lg_width_plus_small);
  tcase_add_test(tc, lg_width_spac_small);
  tcase_add_test(tc, lg_width_hash_small);
  tcase_add_test(tc, lg_width_fzer_small);
  tcase_add_test(tc, lg_width_mins_large);
  tcase_add_test(tc, lg_width_plus_large);
  tcase_add_test(tc, lg_width_spac_large);
  tcase_add_test(tc, lg_width_hash_large);
  tcase_add_test(tc, lg_width_fzer_large);
  tcase_add_test(tc, lg_zrwth_plus_post);
  tcase_add_test(tc, lg_zrwth_spac_post);
  tcase_add_test(tc, lg_zrwth_hash_post);
  tcase_add_test(tc, lg_zrwth_plus_negt);
  tcase_add_test(tc, lg_zrwth_spac_negt);
  tcase_add_test(tc, lg_zrwth_hash_negt);
  tcase_add_test(tc, lg_zrwth_plus_small);
  tcase_add_test(tc, lg_zrwth_spac_small);
  tcase_add_test(tc, lg_zrwth_hash_small);
  tcase_add_test(tc, lg_zrwth_plus_large);
  tcase_add_test(tc, lg_zrwth_spac_large);
  tcase_add_test(tc, lg_zrwth_hash_large);
  tcase_add_test(tc, lg_prec_mins_post);
  tcase_add_test(tc, lg_prec_plus_post);
  tcase_add_test(tc, lg_prec_spac_post);
  tcase_add_test(tc, lg_prec_hash_post);
  tcase_add_test(tc, lg_prec_fzer_post);
  tcase_add_test(tc, lg_prec_mins_negt);
  tcase_add_test(tc, lg_prec_plus_negt);
  tcase_add_test(tc, lg_prec_spac_negt);
  tcase_add_test(tc, lg_prec_hash_negt);
  tcase_add_test(tc, lg_prec_fzer_negt);
  tcase_add_test(tc, lg_prec_mins_small);
  tcase_add_test(tc, lg_prec_plus_small);
  tcase_add_test(tc, lg_prec_spac_small);
  tcase_add_test(tc, lg_prec_hash_small);
  tcase_add_test(tc, lg_prec_fzer_small);
  tcase_add_test(tc, lg_prec_mins_large);
  tcase_add_test(tc, lg_prec_plus_large);
  tcase_add_test(tc, lg_prec_spac_large);
  tcase_add_test(tc, lg_prec_hash_large);
  tcase_add_test(tc, lg_prec_fzer_large);
  tcase_add_test(tc, lg_zrpc_mins_post);
  tcase_add_test(tc, lg_zrpc_plus_post);
  tcase_add_test(tc, lg_zrpc_spac_post);
  tcase_add_test(tc, lg_zrpc_hash_post);
  tcase_add_test(tc, lg_zrpc_fzer_post);
  tcase_add_test(tc, lg_zrpc_mins_negt);
  tcase_add_test(tc, lg_zrpc_plus_negt);
  tcase_add_test(tc, lg_zrpc_spac_negt);
  tcase_add_test(tc, lg_zrpc_hash_negt);
  tcase_add_test(tc, lg_zrpc_fzer_negt);
  tcase_add_test(tc, lg_zrpc_mins_small);
  tcase_add_test(tc, lg_zrpc_plus_small);
  tcase_add_test(tc, lg_zrpc_spac_small);
  tcase_add_test(tc, lg_zrpc_hash_small);
  tcase_add_test(tc, lg_zrpc_fzer_small);
  tcase_add_test(tc, lg_zrpc_mins_large);
  tcase_add_test(tc, lg_zrpc_plus_large);
  tcase_add_test(tc, lg_zrpc_spac_large);
  tcase_add_test(tc, lg_zrpc_hash_large);
  tcase_add_test(tc, lg_zrpc_fzer_large);
  tcase_add_test(tc, lg_width_prec_mins_post);
  tcase_add_test(tc, lg_width_prec_plus_post);
  tcase_add_test(tc, lg_width_prec_spac_post);
  tcase_add_test(tc, lg_width_prec_hash_post);
  tcase_add_test(tc, lg_width_prec_fzer_post);
  tcase_add_test(tc, lg_width_prec_mins_negt);
  tcase_add_test(tc, lg_width_prec_plus_negt);
  tcase_add_test(tc, lg_width_prec_spac_negt);
  tcase_add_test(tc, lg_width_prec_hash_negt);
  tcase_add_test(tc, lg_width_prec_fzer_negt);
  tcase_add_test(tc, lg_width_prec_mins_small);
  tcase_add_test(tc, lg_width_prec_plus_small);
  tcase_add_test(tc, lg_width_prec_spac_small);
  tcase_add_test(tc, lg_width_prec_hash_small);
  tcase_add_test(tc, lg_width_prec_fzer_small);
  tcase_add_test(tc, lg_width_prec_mins_large);
  tcase_add_test(tc, lg_width_prec_plus_large);
  tcase_add_test(tc, lg_width_prec_spac_large);
  tcase_add_test(tc, lg_width_prec_hash_large);
  tcase_add_test(tc, lg_width_prec_fzer_large);
  tcase_add_test(tc, lg_zrwth_zrpc_plus_post);
  tcase_add_test(tc, lg_zrwth_zrpc_spac_post);
  tcase_add_test(tc, lg_zrwth_zrpc_hash_post);
  tcase_add_test(tc, lg_zrwth_zrpc_plus_negt);
  tcase_add_test(tc, lg_zrwth_zrpc_spac_negt);
  tcase_add_test(tc, lg_zrwth_zrpc_hash_negt);
  tcase_add_test(tc, lg_zrwth_zrpc_plus_small);
  tcase_add_test(tc, lg_zrwth_zrpc_spac_small);
  tcase_add_test(tc, lg_zrwth_zrpc_hash_small);
  tcase_add_test(tc, lg_zrwth_zrpc_plus_large);
  tcase_add_test(tc, lg_zrwth_zrpc_spac_large);
  tcase_add_test(tc, lg_zrwth_zrpc_hash_large);
  tcase_add_test(tc, lg_dynamic_width_post);
  tcase_add_test(tc, lg_dynamic_width_negt);
  tcase_add_test(tc, lg_dynamic_width_small);
  tcase_add_test(tc, lg_dynamic_width_large);
  tcase_add_test(tc, lg_dynamic_prec_post);
  tcase_add_test(tc, lg_dynamic_prec_negt);
  tcase_add_test(tc, lg_dynamic_prec_small);
  tcase_add_test(tc, lg_dynamic_prec_large);
  tcase_add_test(tc, lg_dynamic_width_prec_post);
  tcase_add_test(tc, lg_dynamic_width_prec_negt);
  tcase_add_test(tc, lg_dynamic_width_prec_small);
  tcase_add_test(tc, lg_dynamic_width_prec_large);
  tcase_add_test(tc, lG_mins_post);
  tcase_add_test(tc, lG_plus_post);
  tcase_add_test(tc, lG_spac_post);
  tcase_add_test(tc, lG_hash_post);
  tcase_add_test(tc, lG_fzer_post);
  tcase_add_test(tc, lG_mins_negt);
  tcase_add_test(tc, lG_plus_negt);
  tcase_add_test(tc, lG_spac_negt);
  tcase_add_test(tc, lG_hash_negt);
  tcase_add_test(tc, lG_fzer_negt);
  tcase_add_test(tc, lG_mins_small);
  tcase_add_test(tc, lG_plus_small);
  tcase_add_test(tc, lG_spac_small);
  tcase_add_test(tc, lG_hash_small);
  tcase_add_test(tc, lG_fzer_small);
  tcase_add_test(tc, lG_mins_large);
  tcase_add_test(tc, lG_plus_large);
  tcase_add_test(tc, lG_spac_large);
  tcase_add_test(tc, lG_hash_large);
  tcase_add_test(tc, lG_fzer_large);
  tcase_add_test(tc, lG_width_post);
  tcase_add_test(tc, lG_zrpc_post);
  tcase_add_test(tc, lG_prec_post);
  tcase_add_test(tc, lG_width_negt);
  tcase_add_test(tc, lG_zrpc_negt);
  tcase_add_test(tc, lG_prec_negt);
  tcase_add_test(tc, lG_width_small);
  tcase_add_test(tc, lG_zrpc_small);
  tcase_add_test(tc, lG_prec_small);
  tcase_add_test(tc, lG_width_large);
  tcase_add_test(tc, lG_zrpc_large);
  tcase_add_test(tc, lG_prec_large);
  tcase_add_test(tc, lG_width_prec_post);
  tcase_add_test(tc, lG_width_prec_negt);
  tcase_add_test(tc, lG_width_prec_small);
  tcase_add_test(tc, lG_width_prec_large);
  tcase_add_test(tc, lG_width_mins_post);
  tcase_add_test(tc, lG_width_plus_post);
  tcase_add_test(tc, lG_width_spac_post);
  tcase_add_test(tc, lG_width_hash_post);
  tcase_add_test(tc, lG_width_fzer_post);
  tcase_add_test(tc, lG_width_mins_negt);
  tcase_add_test(tc, lG_width_plus_negt);
  tcase_add_test(tc, lG_width_spac_negt);
  tcase_add_test(tc, lG_width_hash_negt);
  tcase_add_test(tc, lG_width_fzer_negt);
  tcase_add_test(tc, lG_width_mins_small);
  tcase_add_test(tc, lG_width_plus_small);
  tcase_add_test(tc, lG_width_spac_small);
  tcase_add_test(tc, lG_width_hash_small);
  tcase_add_test(tc, lG_width_fzer_small);
  tcase_add_test(tc, lG_width_mins_large);
  tcase_add_test(tc, lG_width_plus_large);
  tcase_add_test(tc, lG_width_spac_large);
  tcase_add_test(tc, lG_width_hash_large);
  tcase_add_test(tc, lG_width_fzer_large);
  tcase_add_test(tc, lG_zrwth_plus_post);
  tcase_add_test(tc, lG_zrwth_spac_post);
  tcase_add_test(tc, lG_zrwth_hash_post);
  tcase_add_test(tc, lG_zrwth_plus_negt);
  tcase_add_test(tc, lG_zrwth_spac_negt);
  tcase_add_test(tc, lG_zrwth_hash_negt);
  tcase_add_test(tc, lG_zrwth_plus_small);
  tcase_add_test(tc, lG_zrwth_spac_small);
  tcase_add_test(tc, lG_zrwth_hash_small);
  tcase_add_test(tc, lG_zrwth_plus_large);
  tcase_add_test(tc, lG_zrwth_spac_large);
  tcase_add_test(tc, lG_zrwth_hash_large);
  tcase_add_test(tc, lG_prec_mins_post);
  tcase_add_test(tc, lG_prec_plus_post);
  tcase_add_test(tc, lG_prec_spac_post);
  tcase_add_test(tc, lG_prec_hash_post);
  tcase_add_test(tc, lG_prec_fzer_post);
  tcase_add_test(tc, lG_prec_mins_negt);
  tcase_add_test(tc, lG_prec_plus_negt);
  tcase_add_test(tc, lG_prec_spac_negt);
  tcase_add_test(tc, lG_prec_hash_negt);
  tcase_add_test(tc, lG_prec_fzer_negt);
  tcase_add_test(tc, lG_prec_mins_small);
  tcase_add_test(tc, lG_prec_plus_small);
  tcase_add_test(tc, lG_prec_spac_small);
  tcase_add_test(tc, lG_prec_hash_small);
  tcase_add_test(tc, lG_prec_fzer_small);
  tcase_add_test(tc, lG_prec_mins_large);
  tcase_add_test(tc, lG_prec_plus_large);
  tcase_add_test(tc, lG_prec_spac_large);
  tcase_add_test(tc, lG_prec_hash_large);
  tcase_add_test(tc, lG_prec_fzer_large);
  tcase_add_test(tc, lG_zrpc_mins_post);
  tcase_add_test(tc, lG_zrpc_plus_post);
  tcase_add_test(tc, lG_zrpc_spac_post);
  tcase_add_test(tc, lG_zrpc_hash_post);
  tcase_add_test(tc, lG_zrpc_fzer_post);
  tcase_add_test(tc, lG_zrpc_mins_negt);
  tcase_add_test(tc, lG_zrpc_plus_negt);
  tcase_add_test(tc, lG_zrpc_spac_negt);
  tcase_add_test(tc, lG_zrpc_hash_negt);
  tcase_add_test(tc, lG_zrpc_fzer_negt);
  tcase_add_test(tc, lG_zrpc_mins_small);
  tcase_add_test(tc, lG_zrpc_plus_small);
  tcase_add_test(tc, lG_zrpc_spac_small);
  tcase_add_test(tc, lG_zrpc_hash_small);
  tcase_add_test(tc, lG_zrpc_fzer_small);
  tcase_add_test(tc, lG_zrpc_mins_large);
  tcase_add_test(tc, lG_zrpc_plus_large);
  tcase_add_test(tc, lG_zrpc_spac_large);
  tcase_add_test(tc, lG_zrpc_hash_large);
  tcase_add_test(tc, lG_zrpc_fzer_large);
  tcase_add_test(tc, lG_width_prec_mins_post);
  tcase_add_test(tc, lG_width_prec_plus_post);
  tcase_add_test(tc, lG_width_prec_spac_post);
  tcase_add_test(tc, lG_width_prec_hash_post);
  tcase_add_test(tc, lG_width_prec_fzer_post);
  tcase_add_test(tc, lG_width_prec_mins_negt);
  tcase_add_test(tc, lG_width_prec_plus_negt);
  tcase_add_test(tc, lG_width_prec_spac_negt);
  tcase_add_test(tc, lG_width_prec_hash_negt);
  tcase_add_test(tc, lG_width_prec_fzer_negt);
  tcase_add_test(tc, lG_width_prec_mins_small);
  tcase_add_test(tc, lG_width_prec_plus_small);
  tcase_add_test(tc, lG_width_prec_spac_small);
  tcase_add_test(tc, lG_width_prec_hash_small);
  tcase_add_test(tc, lG_width_prec_fzer_small);
  tcase_add_test(tc, lG_width_prec_mins_large);
  tcase_add_test(tc, lG_width_prec_plus_large);
  tcase_add_test(tc, lG_width_prec_spac_large);
  tcase_add_test(tc, lG_width_prec_hash_large);
  tcase_add_test(tc, lG_width_prec_fzer_large);
  tcase_add_test(tc, lG_zrwth_zrpc_plus_post);
  tcase_add_test(tc, lG_zrwth_zrpc_spac_post);
  tcase_add_test(tc, lG_zrwth_zrpc_hash_post);
  tcase_add_test(tc, lG_zrwth_zrpc_plus_negt);
  tcase_add_test(tc, lG_zrwth_zrpc_spac_negt);
  tcase_add_test(tc, lG_zrwth_zrpc_hash_negt);
  tcase_add_test(tc, lG_zrwth_zrpc_plus_small);
  tcase_add_test(tc, lG_zrwth_zrpc_spac_small);
  tcase_add_test(tc, lG_zrwth_zrpc_hash_small);
  tcase_add_test(tc, lG_zrwth_zrpc_plus_large);
  tcase_add_test(tc, lG_zrwth_zrpc_spac_large);
  tcase_add_test(tc, lG_zrwth_zrpc_hash_large);
  tcase_add_test(tc, lG_dynamic_width_post);
  tcase_add_test(tc, lG_dynamic_width_negt);
  tcase_add_test(tc, lG_dynamic_width_small);
  tcase_add_test(tc, lG_dynamic_width_large);
  tcase_add_test(tc, lG_dynamic_prec_post);
  tcase_add_test(tc, lG_dynamic_prec_negt);
  tcase_add_test(tc, lG_dynamic_prec_small);
  tcase_add_test(tc, lG_dynamic_prec_large);
  tcase_add_test(tc, lG_dynamic_width_prec_post);
  tcase_add_test(tc, lG_dynamic_width_prec_negt);
  tcase_add_test(tc, lG_dynamic_width_prec_small);
  tcase_add_test(tc, lG_dynamic_width_prec_large);
  tcase_add_test(tc, Le_mins_post);
  tcase_add_test(tc, Le_plus_post);
  tcase_add_test(tc, Le_spac_post);
  tcase_add_test(tc, Le_hash_post);
  tcase_add_test(tc, Le_fzer_post);
  tcase_add_test(tc, Le_mins_negt);
  tcase_add_test(tc, Le_plus_negt);
  tcase_add_test(tc, Le_spac_negt);
  tcase_add_test(tc, Le_hash_negt);
  tcase_add_test(tc, Le_fzer_negt);
  tcase_add_test(tc, Le_mins_small);
  tcase_add_test(tc, Le_plus_small);
  tcase_add_test(tc, Le_spac_small);
  tcase_add_test(tc, Le_hash_small);
  tcase_add_test(tc, Le_fzer_small);
  tcase_add_test(tc, Le_mins_large);
  tcase_add_test(tc, Le_plus_large);
  tcase_add_test(tc, Le_spac_large);
  tcase_add_test(tc, Le_hash_large);
  tcase_add_test(tc, Le_fzer_large);
  tcase_add_test(tc, Le_width_post);
  tcase_add_test(tc, Le_zrpc_post);
  tcase_add_test(tc, Le_prec_post);
  tcase_add_test(tc, Le_width_negt);
  tcase_add_test(tc, Le_zrpc_negt);
  tcase_add_test(tc, Le_prec_negt);
  tcase_add_test(tc, Le_width_small);
  tcase_add_test(tc, Le_zrpc_small);
  tcase_add_test(tc, Le_prec_small);
  tcase_add_test(tc, Le_width_large);
  tcase_add_test(tc, Le_zrpc_large);
  tcase_add_test(tc, Le_prec_large);
  tcase_add_test(tc, Le_width_prec_post);
  tcase_add_test(tc, Le_width_prec_negt);
  tcase_add_test(tc, Le_width_prec_small);
  tcase_add_test(tc, Le_width_prec_large);
  tcase_add_test(tc, Le_width_mins_post);
  tcase_add_test(tc, Le_width_plus_post);
  tcase_add_test(tc, Le_width_spac_post);
  tcase_add_test(tc, Le_width_hash_post);
  tcase_add_test(tc, Le_width_fzer_post);
  tcase_add_test(tc, Le_width_mins_negt);
  tcase_add_test(tc, Le_width_plus_negt);
  tcase_add_test(tc, Le_width_spac_negt);
  tcase_add_test(tc, Le_width_hash_negt);
  tcase_add_test(tc, Le_width_fzer_negt);
  tcase_add_test(tc, Le_width_mins_small);
  tcase_add_test(tc, Le_width_plus_small);
  tcase_add_test(tc, Le_width_spac_small);
  tcase_add_test(tc, Le_width_hash_small);
  tcase_add_test(tc, Le_width_fzer_small);
  tcase_add_test(tc, Le_width_mins_large);
  tcase_add_test(tc, Le_width_plus_large);
  tcase_add_test(tc, Le_width_spac_large);
  tcase_add_test(tc, Le_width_hash_large);
  tcase_add_test(tc, Le_width_fzer_large);
  tcase_add_test(tc, Le_zrwth_plus_post);
  tcase_add_test(tc, Le_zrwth_spac_post);
  tcase_add_test(tc, Le_zrwth_hash_post);
  tcase_add_test(tc, Le_zrwth_plus_negt);
  tcase_add_test(tc, Le_zrwth_spac_negt);
  tcase_add_test(tc, Le_zrwth_hash_negt);
  tcase_add_test(tc, Le_zrwth_plus_small);
  tcase_add_test(tc, Le_zrwth_spac_small);
  tcase_add_test(tc, Le_zrwth_hash_small);
  tcase_add_test(tc, Le_zrwth_plus_large);
  tcase_add_test(tc, Le_zrwth_spac_large);
  tcase_add_test(tc, Le_zrwth_hash_large);
  tcase_add_test(tc, Le_prec_mins_post);
  tcase_add_test(tc, Le_prec_plus_post);
  tcase_add_test(tc, Le_prec_spac_post);
  tcase_add_test(tc, Le_prec_hash_post);
  tcase_add_test(tc, Le_prec_fzer_post);
  tcase_add_test(tc, Le_prec_mins_negt);
  tcase_add_test(tc, Le_prec_plus_negt);
  tcase_add_test(tc, Le_prec_spac_negt);
  tcase_add_test(tc, Le_prec_hash_negt);
  tcase_add_test(tc, Le_prec_fzer_negt);
  tcase_add_test(tc, Le_prec_mins_small);
  tcase_add_test(tc, Le_prec_plus_small);
  tcase_add_test(tc, Le_prec_spac_small);
  tcase_add_test(tc, Le_prec_hash_small);
  tcase_add_test(tc, Le_prec_fzer_small);
  tcase_add_test(tc, Le_prec_mins_large);
  tcase_add_test(tc, Le_prec_plus_large);
  tcase_add_test(tc, Le_prec_spac_large);
  tcase_add_test(tc, Le_prec_hash_large);
  tcase_add_test(tc, Le_prec_fzer_large);
  tcase_add_test(tc, Le_zrpc_mins_post);
  tcase_add_test(tc, Le_zrpc_plus_post);
  tcase_add_test(tc, Le_zrpc_spac_post);
  tcase_add_test(tc, Le_zrpc_hash_post);
  tcase_add_test(tc, Le_zrpc_fzer_post);
  tcase_add_test(tc, Le_zrpc_mins_negt);
  tcase_add_test(tc, Le_zrpc_plus_negt);
  tcase_add_test(tc, Le_zrpc_spac_negt);
  tcase_add_test(tc, Le_zrpc_hash_negt);
  tcase_add_test(tc, Le_zrpc_fzer_negt);
  tcase_add_test(tc, Le_zrpc_mins_small);
  tcase_add_test(tc, Le_zrpc_plus_small);
  tcase_add_test(tc, Le_zrpc_spac_small);
  tcase_add_test(tc, Le_zrpc_hash_small);
  tcase_add_test(tc, Le_zrpc_fzer_small);
  tcase_add_test(tc, Le_zrpc_mins_large);
  tcase_add_test(tc, Le_zrpc_plus_large);
  tcase_add_test(tc, Le_zrpc_spac_large);
  tcase_add_test(tc, Le_zrpc_hash_large);
  tcase_add_test(tc, Le_zrpc_fzer_large);
  tcase_add_test(tc, Le_width_prec_mins_post);
  tcase_add_test(tc, Le_width_prec_plus_post);
  tcase_add_test(tc, Le_width_prec_spac_post);
  tcase_add_test(tc, Le_width_prec_hash_post);
  tcase_add_test(tc, Le_width_prec_fzer_post);
  tcase_add_test(tc, Le_width_prec_mins_negt);
  tcase_add_test(tc, Le_width_prec_plus_negt);
  tcase_add_test(tc, Le_width_prec_spac_negt);
  tcase_add_test(tc, Le_width_prec_hash_negt);
  tcase_add_test(tc, Le_width_prec_fzer_negt);
  tcase_add_test(tc, Le_width_prec_mins_small);
  tcase_add_test(tc, Le_width_prec_plus_small);
  tcase_add_test(tc, Le_width_prec_spac_small);
  tcase_add_test(tc, Le_width_prec_hash_small);
  tcase_add_test(tc, Le_width_prec_fzer_small);
  tcase_add_test(tc, Le_width_prec_mins_large);
  tcase_add_test(tc, Le_width_prec_plus_large);
  tcase_add_test(tc, Le_width_prec_spac_large);
  tcase_add_test(tc, Le_width_prec_hash_large);
  tcase_add_test(tc, Le_width_prec_fzer_large);
  tcase_add_test(tc, Le_zrwth_zrpc_plus_post);
  tcase_add_test(tc, Le_zrwth_zrpc_spac_post);
  tcase_add_test(tc, Le_zrwth_zrpc_hash_post);
  tcase_add_test(tc, Le_zrwth_zrpc_plus_negt);
  tcase_add_test(tc, Le_zrwth_zrpc_spac_negt);
  tcase_add_test(tc, Le_zrwth_zrpc_hash_negt);
  tcase_add_test(tc, Le_zrwth_zrpc_plus_small);
  tcase_add_test(tc, Le_zrwth_zrpc_spac_small);
  tcase_add_test(tc, Le_zrwth_zrpc_hash_small);
  tcase_add_test(tc, Le_zrwth_zrpc_plus_large);
  tcase_add_test(tc, Le_zrwth_zrpc_spac_large);
  tcase_add_test(tc, Le_zrwth_zrpc_hash_large);
  tcase_add_test(tc, Le_dynamic_width_post);
  tcase_add_test(tc, Le_dynamic_width_negt);
  tcase_add_test(tc, Le_dynamic_width_small);
  tcase_add_test(tc, Le_dynamic_width_large);
  tcase_add_test(tc, Le_dynamic_prec_post);
  tcase_add_test(tc, Le_dynamic_prec_negt);
  tcase_add_test(tc, Le_dynamic_prec_small);
  tcase_add_test(tc, Le_dynamic_prec_large);
  tcase_add_test(tc, Le_dynamic_width_prec_post);
  tcase_add_test(tc, Le_dynamic_width_prec_negt);
  tcase_add_test(tc, Le_dynamic_width_prec_small);
  tcase_add_test(tc, Le_dynamic_width_prec_large);
  tcase_add_test(tc, LE_mins_post);
  tcase_add_test(tc, LE_plus_post);
  tcase_add_test(tc, LE_spac_post);
  tcase_add_test(tc, LE_hash_post);
  tcase_add_test(tc, LE_fzer_post);
  tcase_add_test(tc, LE_mins_negt);
  tcase_add_test(tc, LE_plus_negt);
  tcase_add_test(tc, LE_spac_negt);
  tcase_add_test(tc, LE_hash_negt);
  tcase_add_test(tc, LE_fzer_negt);
  tcase_add_test(tc, LE_mins_small);
  tcase_add_test(tc, LE_plus_small);
  tcase_add_test(tc, LE_spac_small);
  tcase_add_test(tc, LE_hash_small);
  tcase_add_test(tc, LE_fzer_small);
  tcase_add_test(tc, LE_mins_large);
  tcase_add_test(tc, LE_plus_large);
  tcase_add_test(tc, LE_spac_large);
  tcase_add_test(tc, LE_hash_large);
  tcase_add_test(tc, LE_fzer_large);
  tcase_add_test(tc, LE_width_post);
  tcase_add_test(tc, LE_zrpc_post);
  tcase_add_test(tc, LE_prec_post);
  tcase_add_test(tc, LE_width_negt);
  tcase_add_test(tc, LE_zrpc_negt);
  tcase_add_test(tc, LE_prec_negt);
  tcase_add_test(tc, LE_width_small);
  tcase_add_test(tc, LE_zrpc_small);
  tcase_add_test(tc, LE_prec_small);
  tcase_add_test(tc, LE_width_large);
  tcase_add_test(tc, LE_zrpc_large);
  tcase_add_test(tc, LE_prec_large);
  tcase_add_test(tc, LE_width_prec_post);
  tcase_add_test(tc, LE_width_prec_negt);
  tcase_add_test(tc, LE_width_prec_small);
  tcase_add_test(tc, LE_width_prec_large);
  tcase_add_test(tc, LE_width_mins_post);
  tcase_add_test(tc, LE_width_plus_post);
  tcase_add_test(tc, LE_width_spac_post);
  tcase_add_test(tc, LE_width_hash_post);
  tcase_add_test(tc, LE_width_fzer_post);
  tcase_add_test(tc, LE_width_mins_negt);
  tcase_add_test(tc, LE_width_plus_negt);
  tcase_add_test(tc, LE_width_spac_negt);
  tcase_add_test(tc, LE_width_hash_negt);
  tcase_add_test(tc, LE_width_fzer_negt);
  tcase_add_test(tc, LE_width_mins_small);
  tcase_add_test(tc, LE_width_plus_small);
  tcase_add_test(tc, LE_width_spac_small);
  tcase_add_test(tc, LE_width_hash_small);
  tcase_add_test(tc, LE_width_fzer_small);
  tcase_add_test(tc, LE_width_mins_large);
  tcase_add_test(tc, LE_width_plus_large);
  tcase_add_test(tc, LE_width_spac_large);
  tcase_add_test(tc, LE_width_hash_large);
  tcase_add_test(tc, LE_width_fzer_large);
  tcase_add_test(tc, LE_zrwth_plus_post);
  tcase_add_test(tc, LE_zrwth_spac_post);
  tcase_add_test(tc, LE_zrwth_hash_post);
  tcase_add_test(tc, LE_zrwth_plus_negt);
  tcase_add_test(tc, LE_zrwth_spac_negt);
  tcase_add_test(tc, LE_zrwth_hash_negt);
  tcase_add_test(tc, LE_zrwth_plus_small);
  tcase_add_test(tc, LE_zrwth_spac_small);
  tcase_add_test(tc, LE_zrwth_hash_small);
  tcase_add_test(tc, LE_zrwth_plus_large);
  tcase_add_test(tc, LE_zrwth_spac_large);
  tcase_add_test(tc, LE_zrwth_hash_large);
  tcase_add_test(tc, LE_prec_mins_post);
  tcase_add_test(tc, LE_prec_plus_post);
  tcase_add_test(tc, LE_prec_spac_post);
  tcase_add_test(tc, LE_prec_hash_post);
  tcase_add_test(tc, LE_prec_fzer_post);
  tcase_add_test(tc, LE_prec_mins_negt);
  tcase_add_test(tc, LE_prec_plus_negt);
  tcase_add_test(tc, LE_prec_spac_negt);
  tcase_add_test(tc, LE_prec_hash_negt);
  tcase_add_test(tc, LE_prec_fzer_negt);
  tcase_add_test(tc, LE_prec_mins_small);
  tcase_add_test(tc, LE_prec_plus_small);
  tcase_add_test(tc, LE_prec_spac_small);
  tcase_add_test(tc, LE_prec_hash_small);
  tcase_add_test(tc, LE_prec_fzer_small);
  tcase_add_test(tc, LE_prec_mins_large);
  tcase_add_test(tc, LE_prec_plus_large);
  tcase_add_test(tc, LE_prec_spac_large);
  tcase_add_test(tc, LE_prec_hash_large);
  tcase_add_test(tc, LE_prec_fzer_large);
  tcase_add_test(tc, LE_zrpc_mins_post);
  tcase_add_test(tc, LE_zrpc_plus_post);
  tcase_add_test(tc, LE_zrpc_spac_post);
  tcase_add_test(tc, LE_zrpc_hash_post);
  tcase_add_test(tc, LE_zrpc_fzer_post);
  tcase_add_test(tc, LE_zrpc_mins_negt);
  tcase_add_test(tc, LE_zrpc_plus_negt);
  tcase_add_test(tc, LE_zrpc_spac_negt);
  tcase_add_test(tc, LE_zrpc_hash_negt);
  tcase_add_test(tc, LE_zrpc_fzer_negt);
  tcase_add_test(tc, LE_zrpc_mins_small);
  tcase_add_test(tc, LE_zrpc_plus_small);
  tcase_add_test(tc, LE_zrpc_spac_small);
  tcase_add_test(tc, LE_zrpc_hash_small);
  tcase_add_test(tc, LE_zrpc_fzer_small);
  tcase_add_test(tc, LE_zrpc_mins_large);
  tcase_add_test(tc, LE_zrpc_plus_large);
  tcase_add_test(tc, LE_zrpc_spac_large);
  tcase_add_test(tc, LE_zrpc_hash_large);
  tcase_add_test(tc, LE_zrpc_fzer_large);
  tcase_add_test(tc, LE_width_prec_mins_post);
  tcase_add_test(tc, LE_width_prec_plus_post);
  tcase_add_test(tc, LE_width_prec_spac_post);
  tcase_add_test(tc, LE_width_prec_hash_post);
  tcase_add_test(tc, LE_width_prec_fzer_post);
  tcase_add_test(tc, LE_width_prec_mins_negt);
  tcase_add_test(tc, LE_width_prec_plus_negt);
  tcase_add_test(tc, LE_width_prec_spac_negt);
  tcase_add_test(tc, LE_width_prec_hash_negt);
  tcase_add_test(tc, LE_width_prec_fzer_negt);
  tcase_add_test(tc, LE_width_prec_mins_small);
  tcase_add_test(tc, LE_width_prec_plus_small);
  tcase_add_test(tc, LE_width_prec_spac_small);
  tcase_add_test(tc, LE_width_prec_hash_small);
  tcase_add_test(tc, LE_width_prec_fzer_small);
  tcase_add_test(tc, LE_width_prec_mins_large);
  tcase_add_test(tc, LE_width_prec_plus_large);
  tcase_add_test(tc, LE_width_prec_spac_large);
  tcase_add_test(tc, LE_width_prec_hash_large);
  tcase_add_test(tc, LE_width_prec_fzer_large);
  tcase_add_test(tc, LE_zrwth_zrpc_plus_post);
  tcase_add_test(tc, LE_zrwth_zrpc_spac_post);
  tcase_add_test(tc, LE_zrwth_zrpc_hash_post);
  tcase_add_test(tc, LE_zrwth_zrpc_plus_negt);
  tcase_add_test(tc, LE_zrwth_zrpc_spac_negt);
  tcase_add_test(tc, LE_zrwth_zrpc_hash_negt);
  tcase_add_test(tc, LE_zrwth_zrpc_plus_small);
  tcase_add_test(tc, LE_zrwth_zrpc_spac_small);
  tcase_add_test(tc, LE_zrwth_zrpc_hash_small);
  tcase_add_test(tc, LE_zrwth_zrpc_plus_large);
  tcase_add_test(tc, LE_zrwth_zrpc_spac_large);
  tcase_add_test(tc, LE_zrwth_zrpc_hash_large);
  tcase_add_test(tc, LE_dynamic_width_post);
  tcase_add_test(tc, LE_dynamic_width_negt);
  tcase_add_test(tc, LE_dynamic_width_small);
  tcase_add_test(tc, LE_dynamic_width_large);
  tcase_add_test(tc, LE_dynamic_prec_post);
  tcase_add_test(tc, LE_dynamic_prec_negt);
  tcase_add_test(tc, LE_dynamic_prec_small);
  tcase_add_test(tc, LE_dynamic_prec_large);
  tcase_add_test(tc, LE_dynamic_width_prec_post);
  tcase_add_test(tc, LE_dynamic_width_prec_negt);
  tcase_add_test(tc, LE_dynamic_width_prec_small);
  tcase_add_test(tc, LE_dynamic_width_prec_large);
  tcase_add_test(tc, Lf_mins_post);
  tcase_add_test(tc, Lf_plus_post);
  tcase_add_test(tc, Lf_spac_post);
  tcase_add_test(tc, Lf_hash_post);
  tcase_add_test(tc, Lf_fzer_post);
  tcase_add_test(tc, Lf_mins_negt);
  tcase_add_test(tc, Lf_plus_negt);
  tcase_add_test(tc, Lf_spac_negt);
  tcase_add_test(tc, Lf_hash_negt);
  tcase_add_test(tc, Lf_fzer_negt);
  tcase_add_test(tc, Lf_mins_small);
  tcase_add_test(tc, Lf_plus_small);
  tcase_add_test(tc, Lf_spac_small);
  tcase_add_test(tc, Lf_hash_small);
  tcase_add_test(tc, Lf_fzer_small);
  tcase_add_test(tc, Lf_mins_large);
  tcase_add_test(tc, Lf_plus_large);
  tcase_add_test(tc, Lf_spac_large);
  tcase_add_test(tc, Lf_hash_large);
  tcase_add_test(tc, Lf_fzer_large);
  tcase_add_test(tc, Lf_width_post);
  tcase_add_test(tc, Lf_zrpc_post);
  tcase_add_test(tc, Lf_prec_post);
  tcase_add_test(tc, Lf_width_negt);
  tcase_add_test(tc, Lf_zrpc_negt);
  tcase_add_test(tc, Lf_prec_negt);
  tcase_add_test(tc, Lf_width_small);
  tcase_add_test(tc, Lf_zrpc_small);
  tcase_add_test(tc, Lf_prec_small);
  tcase_add_test(tc, Lf_width_large);
  tcase_add_test(tc, Lf_zrpc_large);
  tcase_add_test(tc, Lf_prec_large);
  tcase_add_test(tc, Lf_width_prec_post);
  tcase_add_test(tc, Lf_width_prec_negt);
  tcase_add_test(tc, Lf_width_prec_small);
  tcase_add_test(tc, Lf_width_prec_large);
  tcase_add_test(tc, Lf_width_mins_post);
  tcase_add_test(tc, Lf_width_plus_post);
  tcase_add_test(tc, Lf_width_spac_post);
  tcase_add_test(tc, Lf_width_hash_post);
  tcase_add_test(tc, Lf_width_fzer_post);
  tcase_add_test(tc, Lf_width_mins_negt);
  tcase_add_test(tc, Lf_width_plus_negt);
  tcase_add_test(tc, Lf_width_spac_negt);
  tcase_add_test(tc, Lf_width_hash_negt);
  tcase_add_test(tc, Lf_width_fzer_negt);
  tcase_add_test(tc, Lf_width_mins_small);
  tcase_add_test(tc, Lf_width_plus_small);
  tcase_add_test(tc, Lf_width_spac_small);
  tcase_add_test(tc, Lf_width_hash_small);
  tcase_add_test(tc, Lf_width_fzer_small);
  tcase_add_test(tc, Lf_width_mins_large);
  tcase_add_test(tc, Lf_width_plus_large);
  tcase_add_test(tc, Lf_width_spac_large);
  tcase_add_test(tc, Lf_width_hash_large);
  tcase_add_test(tc, Lf_width_fzer_large);
  tcase_add_test(tc, Lf_zrwth_plus_post);
  tcase_add_test(tc, Lf_zrwth_spac_post);
  tcase_add_test(tc, Lf_zrwth_hash_post);
  tcase_add_test(tc, Lf_zrwth_plus_negt);
  tcase_add_test(tc, Lf_zrwth_spac_negt);
  tcase_add_test(tc, Lf_zrwth_hash_negt);
  tcase_add_test(tc, Lf_zrwth_plus_small);
  tcase_add_test(tc, Lf_zrwth_spac_small);
  tcase_add_test(tc, Lf_zrwth_hash_small);
  tcase_add_test(tc, Lf_zrwth_plus_large);
  tcase_add_test(tc, Lf_zrwth_spac_large);
  tcase_add_test(tc, Lf_zrwth_hash_large);
  tcase_add_test(tc, Lf_prec_mins_post);
  tcase_add_test(tc, Lf_prec_plus_post);
  tcase_add_test(tc, Lf_prec_spac_post);
  tcase_add_test(tc, Lf_prec_hash_post);
  tcase_add_test(tc, Lf_prec_fzer_post);
  tcase_add_test(tc, Lf_prec_mins_negt);
  tcase_add_test(tc, Lf_prec_plus_negt);
  tcase_add_test(tc, Lf_prec_spac_negt);
  tcase_add_test(tc, Lf_prec_hash_negt);
  tcase_add_test(tc, Lf_prec_fzer_negt);
  tcase_add_test(tc, Lf_prec_mins_small);
  tcase_add_test(tc, Lf_prec_plus_small);
  tcase_add_test(tc, Lf_prec_spac_small);
  tcase_add_test(tc, Lf_prec_hash_small);
  tcase_add_test(tc, Lf_prec_fzer_small);
  tcase_add_test(tc, Lf_prec_mins_large);
  tcase_add_test(tc, Lf_prec_plus_large);
  tcase_add_test(tc, Lf_prec_spac_large);
  tcase_add_test(tc, Lf_prec_hash_large);
  tcase_add_test(tc, Lf_prec_fzer_large);
  tcase_add_test(tc, Lf_zrpc_mins_post);
  tcase_add_test(tc, Lf_zrpc_plus_post);
  tcase_add_test(tc, Lf_zrpc_spac_post);
  tcase_add_test(tc, Lf_zrpc_hash_post);
  tcase_add_test(tc, Lf_zrpc_fzer_post);
  tcase_add_test(tc, Lf_zrpc_mins_negt);
  tcase_add_test(tc, Lf_zrpc_plus_negt);
  tcase_add_test(tc, Lf_zrpc_spac_negt);
  tcase_add_test(tc, Lf_zrpc_hash_negt);
  tcase_add_test(tc, Lf_zrpc_fzer_negt);
  tcase_add_test(tc, Lf_zrpc_mins_small);
  tcase_add_test(tc, Lf_zrpc_plus_small);
  tcase_add_test(tc, Lf_zrpc_spac_small);
  tcase_add_test(tc, Lf_zrpc_hash_small);
  tcase_add_test(tc, Lf_zrpc_fzer_small);
  tcase_add_test(tc, Lf_zrpc_mins_large);
  tcase_add_test(tc, Lf_zrpc_plus_large);
  tcase_add_test(tc, Lf_zrpc_spac_large);
  tcase_add_test(tc, Lf_zrpc_hash_large);
  tcase_add_test(tc, Lf_zrpc_fzer_large);
  tcase_add_test(tc, Lf_width_prec_mins_post);
  tcase_add_test(tc, Lf_width_prec_plus_post);
  tcase_add_test(tc, Lf_width_prec_spac_post);
  tcase_add_test(tc, Lf_width_prec_hash_post);
  tcase_add_test(tc, Lf_width_prec_fzer_post);
  tcase_add_test(tc, Lf_width_prec_mins_negt);
  tcase_add_test(tc, Lf_width_prec_plus_negt);
  tcase_add_test(tc, Lf_width_prec_spac_negt);
  tcase_add_test(tc, Lf_width_prec_hash_negt);
  tcase_add_test(tc, Lf_width_prec_fzer_negt);
  tcase_add_test(tc, Lf_width_prec_mins_small);
  tcase_add_test(tc, Lf_width_prec_plus_small);
  tcase_add_test(tc, Lf_width_prec_spac_small);
  tcase_add_test(tc, Lf_width_prec_hash_small);
  tcase_add_test(tc, Lf_width_prec_fzer_small);
  tcase_add_test(tc, Lf_width_prec_mins_large);
  tcase_add_test(tc, Lf_width_prec_plus_large);
  tcase_add_test(tc, Lf_width_prec_spac_large);
  tcase_add_test(tc, Lf_width_prec_hash_large);
  tcase_add_test(tc, Lf_width_prec_fzer_large);
  tcase_add_test(tc, Lf_zrwth_zrpc_plus_post);
  tcase_add_test(tc, Lf_zrwth_zrpc_spac_post);
  tcase_add_test(tc, Lf_zrwth_zrpc_hash_post);
  tcase_add_test(tc, Lf_zrwth_zrpc_plus_negt);
  tcase_add_test(tc, Lf_zrwth_zrpc_spac_negt);
  tcase_add_test(tc, Lf_zrwth_zrpc_hash_negt);
  tcase_add_test(tc, Lf_zrwth_zrpc_plus_small);
  tcase_add_test(tc, Lf_zrwth_zrpc_spac_small);
  tcase_add_test(tc, Lf_zrwth_zrpc_hash_small);
  tcase_add_test(tc, Lf_zrwth_zrpc_plus_large);
  tcase_add_test(tc, Lf_zrwth_zrpc_spac_large);
  tcase_add_test(tc, Lf_zrwth_zrpc_hash_large);
  tcase_add_test(tc, Lf_dynamic_width_post);
  tcase_add_test(tc, Lf_dynamic_width_negt);
  tcase_add_test(tc, Lf_dynamic_width_small);
  tcase_add_test(tc, Lf_dynamic_width_large);
  tcase_add_test(tc, Lf_dynamic_prec_post);
  tcase_add_test(tc, Lf_dynamic_prec_negt);
  tcase_add_test(tc, Lf_dynamic_prec_small);
  tcase_add_test(tc, Lf_dynamic_prec_large);
  tcase_add_test(tc, Lf_dynamic_width_prec_post);
  tcase_add_test(tc, Lf_dynamic_width_prec_negt);
  tcase_add_test(tc, Lf_dynamic_width_prec_small);
  tcase_add_test(tc, Lf_dynamic_width_prec_large);
  tcase_add_test(tc, Lg_mins_post);
  tcase_add_test(tc, Lg_plus_post);
  tcase_add_test(tc, Lg_spac_post);
  tcase_add_test(tc, Lg_hash_post);
  tcase_add_test(tc, Lg_fzer_post);
  tcase_add_test(tc, Lg_mins_negt);
  tcase_add_test(tc, Lg_plus_negt);
  tcase_add_test(tc, Lg_spac_negt);
  tcase_add_test(tc, Lg_hash_negt);
  tcase_add_test(tc, Lg_fzer_negt);
  tcase_add_test(tc, Lg_mins_small);
  tcase_add_test(tc, Lg_plus_small);
  tcase_add_test(tc, Lg_spac_small);
  tcase_add_test(tc, Lg_hash_small);
  tcase_add_test(tc, Lg_fzer_small);
  tcase_add_test(tc, Lg_mins_large);
  tcase_add_test(tc, Lg_plus_large);
  tcase_add_test(tc, Lg_spac_large);
  tcase_add_test(tc, Lg_hash_large);
  tcase_add_test(tc, Lg_fzer_large);
  tcase_add_test(tc, Lg_width_post);
  tcase_add_test(tc, Lg_zrpc_post);
  tcase_add_test(tc, Lg_prec_post);
  tcase_add_test(tc, Lg_width_negt);
  tcase_add_test(tc, Lg_zrpc_negt);
  tcase_add_test(tc, Lg_prec_negt);
  tcase_add_test(tc, Lg_width_small);
  tcase_add_test(tc, Lg_zrpc_small);
  tcase_add_test(tc, Lg_prec_small);
  tcase_add_test(tc, Lg_width_large);
  tcase_add_test(tc, Lg_zrpc_large);
  tcase_add_test(tc, Lg_prec_large);
  tcase_add_test(tc, Lg_width_prec_post);
  tcase_add_test(tc, Lg_width_prec_negt);
  tcase_add_test(tc, Lg_width_prec_small);
  tcase_add_test(tc, Lg_width_prec_large);
  tcase_add_test(tc, Lg_width_mins_post);
  tcase_add_test(tc, Lg_width_plus_post);
  tcase_add_test(tc, Lg_width_spac_post);
  tcase_add_test(tc, Lg_width_hash_post);
  tcase_add_test(tc, Lg_width_fzer_post);
  tcase_add_test(tc, Lg_width_mins_negt);
  tcase_add_test(tc, Lg_width_plus_negt);
  tcase_add_test(tc, Lg_width_spac_negt);
  tcase_add_test(tc, Lg_width_hash_negt);
  tcase_add_test(tc, Lg_width_fzer_negt);
  tcase_add_test(tc, Lg_width_mins_small);
  tcase_add_test(tc, Lg_width_plus_small);
  tcase_add_test(tc, Lg_width_spac_small);
  tcase_add_test(tc, Lg_width_hash_small);
  tcase_add_test(tc, Lg_width_fzer_small);
  tcase_add_test(tc, Lg_width_mins_large);
  tcase_add_test(tc, Lg_width_plus_large);
  tcase_add_test(tc, Lg_width_spac_large);
  tcase_add_test(tc, Lg_width_hash_large);
  tcase_add_test(tc, Lg_width_fzer_large);
  tcase_add_test(tc, Lg_zrwth_plus_post);
  tcase_add_test(tc, Lg_zrwth_spac_post);
  tcase_add_test(tc, Lg_zrwth_hash_post);
  tcase_add_test(tc, Lg_zrwth_plus_negt);
  tcase_add_test(tc, Lg_zrwth_spac_negt);
  tcase_add_test(tc, Lg_zrwth_hash_negt);
  tcase_add_test(tc, Lg_zrwth_plus_small);
  tcase_add_test(tc, Lg_zrwth_spac_small);
  tcase_add_test(tc, Lg_zrwth_hash_small);
  tcase_add_test(tc, Lg_zrwth_plus_large);
  tcase_add_test(tc, Lg_zrwth_spac_large);
  tcase_add_test(tc, Lg_zrwth_hash_large);
  tcase_add_test(tc, Lg_prec_mins_post);
  tcase_add_test(tc, Lg_prec_plus_post);
  tcase_add_test(tc, Lg_prec_spac_post);
  tcase_add_test(tc, Lg_prec_hash_post);
  tcase_add_test(tc, Lg_prec_fzer_post);
  tcase_add_test(tc, Lg_prec_mins_negt);
  tcase_add_test(tc, Lg_prec_plus_negt);
  tcase_add_test(tc, Lg_prec_spac_negt);
  tcase_add_test(tc, Lg_prec_hash_negt);
  tcase_add_test(tc, Lg_prec_fzer_negt);
  tcase_add_test(tc, Lg_prec_mins_small);
  tcase_add_test(tc, Lg_prec_plus_small);
  tcase_add_test(tc, Lg_prec_spac_small);
  tcase_add_test(tc, Lg_prec_hash_small);
  tcase_add_test(tc, Lg_prec_fzer_small);
  tcase_add_test(tc, Lg_prec_mins_large);
  tcase_add_test(tc, Lg_prec_plus_large);
  tcase_add_test(tc, Lg_prec_spac_large);
  tcase_add_test(tc, Lg_prec_hash_large);
  tcase_add_test(tc, Lg_prec_fzer_large);
  tcase_add_test(tc, Lg_zrpc_mins_post);
  tcase_add_test(tc, Lg_zrpc_plus_post);
  tcase_add_test(tc, Lg_zrpc_spac_post);
  tcase_add_test(tc, Lg_zrpc_hash_post);
  tcase_add_test(tc, Lg_zrpc_fzer_post);
  tcase_add_test(tc, Lg_zrpc_mins_negt);
  tcase_add_test(tc, Lg_zrpc_plus_negt);
  tcase_add_test(tc, Lg_zrpc_spac_negt);
  tcase_add_test(tc, Lg_zrpc_hash_negt);
  tcase_add_test(tc, Lg_zrpc_fzer_negt);
  tcase_add_test(tc, Lg_zrpc_mins_small);
  tcase_add_test(tc, Lg_zrpc_plus_small);
  tcase_add_test(tc, Lg_zrpc_spac_small);
  tcase_add_test(tc, Lg_zrpc_hash_small);
  tcase_add_test(tc, Lg_zrpc_fzer_small);
  tcase_add_test(tc, Lg_zrpc_mins_large);
  tcase_add_test(tc, Lg_zrpc_plus_large);
  tcase_add_test(tc, Lg_zrpc_spac_large);
  tcase_add_test(tc, Lg_zrpc_hash_large);
  tcase_add_test(tc, Lg_zrpc_fzer_large);
  tcase_add_test(tc, Lg_width_prec_mins_post);
  tcase_add_test(tc, Lg_width_prec_plus_post);
  tcase_add_test(tc, Lg_width_prec_spac_post);
  tcase_add_test(tc, Lg_width_prec_hash_post);
  tcase_add_test(tc, Lg_width_prec_fzer_post);
  tcase_add_test(tc, Lg_width_prec_mins_negt);
  tcase_add_test(tc, Lg_width_prec_plus_negt);
  tcase_add_test(tc, Lg_width_prec_spac_negt);
  tcase_add_test(tc, Lg_width_prec_hash_negt);
  tcase_add_test(tc, Lg_width_prec_fzer_negt);
  tcase_add_test(tc, Lg_width_prec_mins_small);
  tcase_add_test(tc, Lg_width_prec_plus_small);
  tcase_add_test(tc, Lg_width_prec_spac_small);
  tcase_add_test(tc, Lg_width_prec_hash_small);
  tcase_add_test(tc, Lg_width_prec_fzer_small);
  tcase_add_test(tc, Lg_width_prec_mins_large);
  tcase_add_test(tc, Lg_width_prec_plus_large);
  tcase_add_test(tc, Lg_width_prec_spac_large);
  tcase_add_test(tc, Lg_width_prec_hash_large);
  tcase_add_test(tc, Lg_width_prec_fzer_large);
  tcase_add_test(tc, Lg_zrwth_zrpc_plus_post);
  tcase_add_test(tc, Lg_zrwth_zrpc_spac_post);
  tcase_add_test(tc, Lg_zrwth_zrpc_hash_post);
  tcase_add_test(tc, Lg_zrwth_zrpc_plus_negt);
  tcase_add_test(tc, Lg_zrwth_zrpc_spac_negt);
  tcase_add_test(tc, Lg_zrwth_zrpc_hash_negt);
  tcase_add_test(tc, Lg_zrwth_zrpc_plus_small);
  tcase_add_test(tc, Lg_zrwth_zrpc_spac_small);
  tcase_add_test(tc, Lg_zrwth_zrpc_hash_small);
  tcase_add_test(tc, Lg_zrwth_zrpc_plus_large);
  tcase_add_test(tc, Lg_zrwth_zrpc_spac_large);
  tcase_add_test(tc, Lg_zrwth_zrpc_hash_large);
  tcase_add_test(tc, Lg_dynamic_width_post);
  tcase_add_test(tc, Lg_dynamic_width_negt);
  tcase_add_test(tc, Lg_dynamic_width_small);
  tcase_add_test(tc, Lg_dynamic_width_large);
  tcase_add_test(tc, Lg_dynamic_prec_post);
  tcase_add_test(tc, Lg_dynamic_prec_negt);
  tcase_add_test(tc, Lg_dynamic_prec_small);
  tcase_add_test(tc, Lg_dynamic_prec_large);
  tcase_add_test(tc, Lg_dynamic_width_prec_post);
  tcase_add_test(tc, Lg_dynamic_width_prec_negt);
  tcase_add_test(tc, Lg_dynamic_width_prec_small);
  tcase_add_test(tc, Lg_dynamic_width_prec_large);
  tcase_add_test(tc, LG_mins_post);
  tcase_add_test(tc, LG_plus_post);
  tcase_add_test(tc, LG_spac_post);
  tcase_add_test(tc, LG_hash_post);
  tcase_add_test(tc, LG_fzer_post);
  tcase_add_test(tc, LG_mins_negt);
  tcase_add_test(tc, LG_plus_negt);
  tcase_add_test(tc, LG_spac_negt);
  tcase_add_test(tc, LG_hash_negt);
  tcase_add_test(tc, LG_fzer_negt);
  tcase_add_test(tc, LG_mins_small);
  tcase_add_test(tc, LG_plus_small);
  tcase_add_test(tc, LG_spac_small);
  tcase_add_test(tc, LG_hash_small);
  tcase_add_test(tc, LG_fzer_small);
  tcase_add_test(tc, LG_mins_large);
  tcase_add_test(tc, LG_plus_large);
  tcase_add_test(tc, LG_spac_large);
  tcase_add_test(tc, LG_hash_large);
  tcase_add_test(tc, LG_fzer_large);
  tcase_add_test(tc, LG_width_post);
  tcase_add_test(tc, LG_zrpc_post);
  tcase_add_test(tc, LG_prec_post);
  tcase_add_test(tc, LG_width_negt);
  tcase_add_test(tc, LG_zrpc_negt);
  tcase_add_test(tc, LG_prec_negt);
  tcase_add_test(tc, LG_width_small);
  tcase_add_test(tc, LG_zrpc_small);
  tcase_add_test(tc, LG_prec_small);
  tcase_add_test(tc, LG_width_large);
  tcase_add_test(tc, LG_zrpc_large);
  tcase_add_test(tc, LG_prec_large);
  tcase_add_test(tc, LG_width_prec_post);
  tcase_add_test(tc, LG_width_prec_negt);
  tcase_add_test(tc, LG_width_prec_small);
  tcase_add_test(tc, LG_width_prec_large);
  tcase_add_test(tc, LG_width_mins_post);
  tcase_add_test(tc, LG_width_plus_post);
  tcase_add_test(tc, LG_width_spac_post);
  tcase_add_test(tc, LG_width_hash_post);
  tcase_add_test(tc, LG_width_fzer_post);
  tcase_add_test(tc, LG_width_mins_negt);
  tcase_add_test(tc, LG_width_plus_negt);
  tcase_add_test(tc, LG_width_spac_negt);
  tcase_add_test(tc, LG_width_hash_negt);
  tcase_add_test(tc, LG_width_fzer_negt);
  tcase_add_test(tc, LG_width_mins_small);
  tcase_add_test(tc, LG_width_plus_small);
  tcase_add_test(tc, LG_width_spac_small);
  tcase_add_test(tc, LG_width_hash_small);
  tcase_add_test(tc, LG_width_fzer_small);
  tcase_add_test(tc, LG_width_mins_large);
  tcase_add_test(tc, LG_width_plus_large);
  tcase_add_test(tc, LG_width_spac_large);
  tcase_add_test(tc, LG_width_hash_large);
  tcase_add_test(tc, LG_width_fzer_large);
  tcase_add_test(tc, LG_zrwth_plus_post);
  tcase_add_test(tc, LG_zrwth_spac_post);
  tcase_add_test(tc, LG_zrwth_hash_post);
  tcase_add_test(tc, LG_zrwth_plus_negt);
  tcase_add_test(tc, LG_zrwth_spac_negt);
  tcase_add_test(tc, LG_zrwth_hash_negt);
  tcase_add_test(tc, LG_zrwth_plus_small);
  tcase_add_test(tc, LG_zrwth_spac_small);
  tcase_add_test(tc, LG_zrwth_hash_small);
  tcase_add_test(tc, LG_zrwth_plus_large);
  tcase_add_test(tc, LG_zrwth_spac_large);
  tcase_add_test(tc, LG_zrwth_hash_large);
  tcase_add_test(tc, LG_prec_mins_post);
  tcase_add_test(tc, LG_prec_plus_post);
  tcase_add_test(tc, LG_prec_spac_post);
  tcase_add_test(tc, LG_prec_hash_post);
  tcase_add_test(tc, LG_prec_fzer_post);
  tcase_add_test(tc, LG_prec_mins_negt);
  tcase_add_test(tc, LG_prec_plus_negt);
  tcase_add_test(tc, LG_prec_spac_negt);
  tcase_add_test(tc, LG_prec_hash_negt);
  tcase_add_test(tc, LG_prec_fzer_negt);
  tcase_add_test(tc, LG_prec_mins_small);
  tcase_add_test(tc, LG_prec_plus_small);
  tcase_add_test(tc, LG_prec_spac_small);
  tcase_add_test(tc, LG_prec_hash_small);
  tcase_add_test(tc, LG_prec_fzer_small);
  tcase_add_test(tc, LG_prec_mins_large);
  tcase_add_test(tc, LG_prec_plus_large);
  tcase_add_test(tc, LG_prec_spac_large);
  tcase_add_test(tc, LG_prec_hash_large);
  tcase_add_test(tc, LG_prec_fzer_large);
  tcase_add_test(tc, LG_zrpc_mins_post);
  tcase_add_test(tc, LG_zrpc_plus_post);
  tcase_add_test(tc, LG_zrpc_spac_post);
  tcase_add_test(tc, LG_zrpc_hash_post);
  tcase_add_test(tc, LG_zrpc_fzer_post);
  tcase_add_test(tc, LG_zrpc_mins_negt);
  tcase_add_test(tc, LG_zrpc_plus_negt);
  tcase_add_test(tc, LG_zrpc_spac_negt);
  tcase_add_test(tc, LG_zrpc_hash_negt);
  tcase_add_test(tc, LG_zrpc_fzer_negt);
  tcase_add_test(tc, LG_zrpc_mins_small);
  tcase_add_test(tc, LG_zrpc_plus_small);
  tcase_add_test(tc, LG_zrpc_spac_small);
  tcase_add_test(tc, LG_zrpc_hash_small);
  tcase_add_test(tc, LG_zrpc_fzer_small);
  tcase_add_test(tc, LG_zrpc_mins_large);
  tcase_add_test(tc, LG_zrpc_plus_large);
  tcase_add_test(tc, LG_zrpc_spac_large);
  tcase_add_test(tc, LG_zrpc_hash_large);
  tcase_add_test(tc, LG_zrpc_fzer_large);
  tcase_add_test(tc, LG_width_prec_mins_post);
  tcase_add_test(tc, LG_width_prec_plus_post);
  tcase_add_test(tc, LG_width_prec_spac_post);
  tcase_add_test(tc, LG_width_prec_hash_post);
  tcase_add_test(tc, LG_width_prec_fzer_post);
  tcase_add_test(tc, LG_width_prec_mins_negt);
  tcase_add_test(tc, LG_width_prec_plus_negt);
  tcase_add_test(tc, LG_width_prec_spac_negt);
  tcase_add_test(tc, LG_width_prec_hash_negt);
  tcase_add_test(tc, LG_width_prec_fzer_negt);
  tcase_add_test(tc, LG_width_prec_mins_small);
  tcase_add_test(tc, LG_width_prec_plus_small);
  tcase_add_test(tc, LG_width_prec_spac_small);
  tcase_add_test(tc, LG_width_prec_hash_small);
  tcase_add_test(tc, LG_width_prec_fzer_small);
  tcase_add_test(tc, LG_width_prec_mins_large);
  tcase_add_test(tc, LG_width_prec_plus_large);
  tcase_add_test(tc, LG_width_prec_spac_large);
  tcase_add_test(tc, LG_width_prec_hash_large);
  tcase_add_test(tc, LG_width_prec_fzer_large);
  tcase_add_test(tc, LG_zrwth_zrpc_plus_post);
  tcase_add_test(tc, LG_zrwth_zrpc_spac_post);
  tcase_add_test(tc, LG_zrwth_zrpc_hash_post);
  tcase_add_test(tc, LG_zrwth_zrpc_plus_negt);
  tcase_add_test(tc, LG_zrwth_zrpc_spac_negt);
  tcase_add_test(tc, LG_zrwth_zrpc_hash_negt);
  tcase_add_test(tc, LG_zrwth_zrpc_plus_small);
  tcase_add_test(tc, LG_zrwth_zrpc_spac_small);
  tcase_add_test(tc, LG_zrwth_zrpc_hash_small);
  tcase_add_test(tc, LG_zrwth_zrpc_plus_large);
  tcase_add_test(tc, LG_zrwth_zrpc_spac_large);
  tcase_add_test(tc, LG_zrwth_zrpc_hash_large);
  tcase_add_test(tc, LG_dynamic_width_post);
  tcase_add_test(tc, LG_dynamic_width_negt);
  tcase_add_test(tc, LG_dynamic_width_small);
  tcase_add_test(tc, LG_dynamic_width_large);
  tcase_add_test(tc, LG_dynamic_prec_post);
  tcase_add_test(tc, LG_dynamic_prec_negt);
  tcase_add_test(tc, LG_dynamic_prec_small);
  tcase_add_test(tc, LG_dynamic_prec_large);
  tcase_add_test(tc, LG_dynamic_width_prec_post);
  tcase_add_test(tc, LG_dynamic_width_prec_negt);
  tcase_add_test(tc, LG_dynamic_width_prec_small);
  tcase_add_test(tc, LG_dynamic_width_prec_large);
  tcase_add_test(tc, s_mins_null);
  tcase_add_test(tc, s_width_null);
  tcase_add_test(tc, s_zrpc_null);
  tcase_add_test(tc, s_prec_null);
  tcase_add_test(tc, s_width_prec_null);
  tcase_add_test(tc, s_width_mins_null);
  tcase_add_test(tc, s_prec_mins_null);
  tcase_add_test(tc, s_zrpc_mins_null);
  tcase_add_test(tc, s_width_prec_mins_null);
  tcase_add_test(tc, s_dynamic_width_null);
  tcase_add_test(tc, s_dynamic_prec_null);
  tcase_add_test(tc, s_dynamic_width_prec_null);
  tcase_add_test(tc, s_mins_zero);
  tcase_add_test(tc, s_width_zero);
  tcase_add_test(tc, s_zrpc_zero);
  tcase_add_test(tc, s_prec_zero);
  tcase_add_test(tc, s_width_prec_zero);
  tcase_add_test(tc, s_width_mins_zero);
  tcase_add_test(tc, s_prec_mins_zero);
  tcase_add_test(tc, s_zrpc_mins_zero);
  tcase_add_test(tc, s_width_prec_mins_zero);
  tcase_add_test(tc, s_dynamic_width_zero);
  tcase_add_test(tc, s_dynamic_prec_zero);
  tcase_add_test(tc, s_dynamic_width_prec_zero);
  tcase_add_test(tc, c_mins_zero);
  tcase_add_test(tc, c_width_zero);
  tcase_add_test(tc, c_width_mins_zero);
  tcase_add_test(tc, c_dynamic_width_zero);
  tcase_add_test(tc, s_mins_str);
  tcase_add_test(tc, s_width_str);
  tcase_add_test(tc, s_zrpc_str);
  tcase_add_test(tc, s_prec_str);
  tcase_add_test(tc, s_width_prec_str);
  tcase_add_test(tc, s_width_mins_str);
  tcase_add_test(tc, s_prec_mins_str);
  tcase_add_test(tc, s_zrpc_mins_str);
  tcase_add_test(tc, s_width_prec_mins_str);
  tcase_add_test(tc, s_dynamic_width_str);
  tcase_add_test(tc, s_dynamic_prec_str);
  tcase_add_test(tc, s_dynamic_width_prec_str);
  tcase_add_test(tc, c_mins_char);
  tcase_add_test(tc, c_width_char);
  tcase_add_test(tc, c_width_mins_char);
  tcase_add_test(tc, c_dynamic_width_char);
  tcase_add_test(tc, p_mins_null);
  tcase_add_test(tc, p_width_null);
  tcase_add_test(tc, p_width_mins_null);
  tcase_add_test(tc, p_dynamic_width_null);
  tcase_add_test(tc, p_mins_ptr);
  tcase_add_test(tc, p_width_ptr);
  tcase_add_test(tc, p_width_mins_ptr);
  tcase_add_test(tc, p_dynamic_width_ptr);
#pragma endregion
  suite_add_tcase(suite, tc);
  return suite;
}

#pragma endregion

// ================================================================
// Test suite sprintf_suite_lc_and_ls
// ================================================================
#pragma region

static void setup_wide(void) {
  if (!setlocale(LC_ALL, "en_US.UTF-8")) {
    setlocale(LC_ALL, "C.UTF-8");
  }
}

Suite *sprintf_suite_lc_and_ls(void) {
  Suite *suite = suite_create("test_sprintf_lc_and_ls");
  TCase *tc = tcase_create("Core");
  tcase_add_checked_fixture(tc, setup_wide, NULL);
#pragma region
  tcase_add_test(tc, ls_basic);
  tcase_add_test(tc, ls_unicode);
  tcase_add_test(tc, ls_wide_chars);
  tcase_add_test(tc, ls_special);
  tcase_add_test(tc, ls_nonprint);
  tcase_add_test(tc, ls_null);
  tcase_add_test(tc, ls_empty);
  tcase_add_test(tc, ls_width);
  tcase_add_test(tc, ls_left_align);
  tcase_add_test(tc, ls_precision);
  tcase_add_test(tc, ls_zero_precision);
  tcase_add_test(tc, ls_large_precision);
  tcase_add_test(tc, ls_width_precision);
  tcase_add_test(tc, ls_complex_align);
  tcase_add_test(tc, ls_mixed);
  tcase_add_test(tc, ls_ascii_only);
  tcase_add_test(tc, ls_brackets);
  tcase_add_test(tc, ls_utf8_locale);
  tcase_add_test(tc, ls_utf16_locale);
  tcase_add_test(tc, ls_surrogate_pair);
  tcase_add_test(tc, lc_basic);
  tcase_add_test(tc, lc_ascii);
  tcase_add_test(tc, lc_width);
  tcase_add_test(tc, lc_width_left_align);
  tcase_add_test(tc, lc_euro);
  tcase_add_test(tc, lc_cyrillic);
  tcase_add_test(tc, lc_hiragana);
  tcase_add_test(tc, lc_gothic);
  tcase_add_test(tc, lc_min);
  tcase_add_test(tc, lc_max);
  tcase_add_test(tc, lc_neg_128);
  tcase_add_test(tc, lc_zero);
  tcase_add_test(tc, lc_128);
  tcase_add_test(tc, lc_256);
  tcase_add_test(tc, lc_1024);
  tcase_add_test(tc, lc_0xFFFF);
  tcase_add_test(tc, lc_0x10000);
  tcase_add_test(tc, lc_0x10FFFF);
  tcase_add_test(tc, lc_null_char);
  tcase_add_test(tc, lc_nonprint);
  tcase_add_test(tc, lc_newline);
  tcase_add_test(tc, lc_tab);
  tcase_add_test(tc, lc_invalid_wide);
  tcase_add_test(tc, lc_surrogate);
  tcase_add_test(tc, lc_bom);
  tcase_add_test(tc, lc_replacement);
  tcase_add_test(tc, lc_long_string);
  tcase_add_test(tc, ls_mins_null);
  tcase_add_test(tc, ls_width_null);
  tcase_add_test(tc, ls_zrpc_null);
  tcase_add_test(tc, ls_prec_null);
  tcase_add_test(tc, ls_width_prec_null);
  tcase_add_test(tc, ls_width_mins_null);
  tcase_add_test(tc, ls_prec_mins_null);
  tcase_add_test(tc, ls_zrpc_mins_null);
  tcase_add_test(tc, ls_width_prec_mins_null);
  tcase_add_test(tc, ls_dynamic_width_null);
  tcase_add_test(tc, ls_dynamic_prec_null);
  tcase_add_test(tc, ls_dynamic_width_prec_null);
  tcase_add_test(tc, ls_mins_zero);
  tcase_add_test(tc, ls_width_zero);
  tcase_add_test(tc, ls_zrpc_zero);
  tcase_add_test(tc, ls_prec_zero);
  tcase_add_test(tc, ls_width_prec_zero);
  tcase_add_test(tc, ls_width_mins_zero);
  tcase_add_test(tc, ls_prec_mins_zero);
  tcase_add_test(tc, ls_zrpc_mins_zero);
  tcase_add_test(tc, ls_width_prec_mins_zero);
  tcase_add_test(tc, ls_dynamic_width_zero);
  tcase_add_test(tc, ls_dynamic_prec_zero);
  tcase_add_test(tc, ls_dynamic_width_prec_zero);
  tcase_add_test(tc, lc_mins_wchar_t);
  tcase_add_test(tc, lc_width_wchar_t);
  tcase_add_test(tc, lc_width_mins_wchar_t);
  tcase_add_test(tc, lc_dynamic_width_wchar_t);
  tcase_add_test(tc, lc_mins_zero);
  tcase_add_test(tc, lc_width_zero);
  tcase_add_test(tc, lc_width_mins_zero);
  tcase_add_test(tc, lc_dynamic_width_zero);
#pragma endregion
  suite_add_tcase(suite, tc);
  return suite;
}
#pragma endregion

// ================================================================================================================================
//                                                           ~~  MAIN  ~~
// ================================================================================================================================
// ================================================================================================================================

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