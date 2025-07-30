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

#include <math.h>

  // Для целочисленных типов и символов
void CompareDefault(const void *val_sp, const void *val_s21, void *dummy) {
    (void)dummy; // Подавление предупреждений о неиспользуемом параметре
    ck_assert(*(const long long *)val_sp == *(const long long *)val_s21);
}

// Для float
void CompareFloat(const void *val_sp, const void *val_s21, void *dummy) {
    (void)dummy;
    if (isnan(*(const float *)val_sp)) {
        ck_assert(isnan(*(const float *)val_s21));
    } else if (isinf(*(const float *)val_sp)) {
        ck_assert(isinf(*(const float *)val_s21));
        ck_assert(signbit(*(const float *)val_sp) == signbit(*(const float *)val_s21));
    } else {
        ck_assert_float_eq(*(const float *)val_sp, *(const float *)val_s21);
    }
}

// Для double
void CompareDouble(const void *val_sp, const void *val_s21, void *dummy) {
    (void)dummy;
    if (isnan(*(const double *)val_sp)) {
        ck_assert(isnan(*(const double *)val_s21));
    } else if (isinf(*(const double *)val_sp)) {
        ck_assert(isinf(*(const double *)val_s21));
        ck_assert(signbit(*(const double *)val_sp) == signbit(*(const double *)val_s21));
    } else {
        ck_assert_double_eq(*(const double *)val_sp, *(const double *)val_s21);
    }
}

// Для long double
void CompareLongDouble(const void *val_sp, const void *val_s21, void *dummy) {
    (void)dummy;
    if (isnan(*(const long double *)val_sp)) {
        ck_assert(isnan(*(const long double *)val_s21));
    } else if (isinf(*(const long double *)val_sp)) {
        ck_assert(isinf(*(const long double *)val_s21));
        ck_assert(signbit(*(const long double *)val_sp) == signbit(*(const long double *)val_s21));
    } else {
        ck_assert_ldouble_eq(*(const long double *)val_sp, *(const long double *)val_s21);
    }
}


#define TEST_SPRINTF(test_name, format_str, value, type) \
    START_TEST(test_name) { \
        char str[200] = {0}; \
        type val = (value); \
        sprintf(str, format_str, val); \
        type val_sp = 0; \
        type val_s21 = 0; \
        int res_sp = sscanf(str, format_str, &val_sp); \
        int res_s21 = s21_sscanf(str, format_str, &val_s21); \
        COMPARE_VALUES(&val_sp, &val_s21, type); \
        ck_assert_int_eq(res_sp, res_s21); \
    } \
    END_TEST


    #define TEST_SSCANF_S(test_name, input_str, format_str) \
    START_TEST(test_name) { \
        char str1[200] = {0}; \
        char str2[200] = {0}; \
        int res1 = sscanf(input_str, format_str, str1); \
        int res2 = s21_sscanf(input_str, format_str, str2); \
        ck_assert_str_eq(str1, str2); \
        ck_assert_int_eq(res1, res2); \
    } \
    END_TEST

    #define COMPARE_VALUES(val_sp, val_s21, type) \
    _Generic((type){0}, \
        float: CompareFloat, \
        double: CompareDouble, \
        long double: CompareLongDouble, \
        default: CompareDefault \
    )(val_sp, val_s21, (type){0})


// ================================================================
// Целочисленные типы без модификаторов
// ================================================================

// %d - int
TEST_SPRINTF(test_s21_sprintf_d, "%d", 123, int)
TEST_SPRINTF(test_s21_sprintf_d_min, "%d", INT_MIN, int)
TEST_SPRINTF(test_s21_sprintf_d_max, "%d", INT_MAX, int)

// %i - int
TEST_SPRINTF(test_s21_sprintf_i, "%i", 123, int)
TEST_SPRINTF(test_s21_sprintf_i_min, "%i", INT_MIN, int)
TEST_SPRINTF(test_s21_sprintf_i_max, "%i", INT_MAX, int)

// %o - unsigned int
TEST_SPRINTF(test_s21_sprintf_o, "%o", 123, unsigned int)
TEST_SPRINTF(test_s21_sprintf_o_min, "%o", 0, unsigned int)
TEST_SPRINTF(test_s21_sprintf_o_max, "%o", UINT_MAX, unsigned int)

// %u - unsigned int
TEST_SPRINTF(test_s21_sprintf_u, "%u", 123, unsigned int)
TEST_SPRINTF(test_s21_sprintf_u_min, "%u", 0, unsigned int)
TEST_SPRINTF(test_s21_sprintf_u_max, "%u", UINT_MAX, unsigned int)

// %x - unsigned int
TEST_SPRINTF(test_s21_sprintf_x, "%x", 123, unsigned int)
TEST_SPRINTF(test_s21_sprintf_x_min, "%x", 0, unsigned int)
TEST_SPRINTF(test_s21_sprintf_x_max, "%x", UINT_MAX, unsigned int)

// %X - unsigned int
TEST_SPRINTF(test_s21_sprintf_X, "%X", 123, unsigned int)
TEST_SPRINTF(test_s21_sprintf_X_min, "%X", 0, unsigned int)
TEST_SPRINTF(test_s21_sprintf_X_max, "%X", UINT_MAX, unsigned int)

// ================================================================
// Модификатор h (short)
// ================================================================

// %hd - short
TEST_SPRINTF(test_s21_sprintf_hd, " %hd", 123, short)
TEST_SPRINTF(test_s21_sprintf_hd_min, "%hd", SHRT_MIN, short)
TEST_SPRINTF(test_s21_sprintf_hd_max, "%hd", SHRT_MAX, short)

// %hi - short
TEST_SPRINTF(test_s21_sprintf_hi, "%hi", 123, short)
TEST_SPRINTF(test_s21_sprintf_hi_min, "%hi", SHRT_MIN, short)
TEST_SPRINTF(test_s21_sprintf_hi_max, "%hi", SHRT_MAX, short)

// %ho - unsigned short
TEST_SPRINTF(test_s21_sprintf_ho, "%ho", 123, unsigned short)
TEST_SPRINTF(test_s21_sprintf_ho_min, "%ho", 0, unsigned short)
TEST_SPRINTF(test_s21_sprintf_ho_max, "%ho", USHRT_MAX,
             unsigned short)

// %hu - unsigned short
TEST_SPRINTF(test_s21_sprintf_hu, "%hu", 123, unsigned short)
TEST_SPRINTF(test_s21_sprintf_hu_min, "%hu", 0, unsigned short)
TEST_SPRINTF(test_s21_sprintf_hu_max, "%hu", USHRT_MAX,
             unsigned short)

// %hx - unsigned short
TEST_SPRINTF(test_s21_sprintf_hx, "%hx", 123, unsigned short)
TEST_SPRINTF(test_s21_sprintf_hx_min, "%hx", 0, unsigned short)
TEST_SPRINTF(test_s21_sprintf_hx_max, "%hx", USHRT_MAX,
             unsigned short)

// %hX - unsigned short
TEST_SPRINTF(test_s21_sprintf_hX, "%hX", 123, unsigned short)
TEST_SPRINTF(test_s21_sprintf_hX_min, "%hX", 0, unsigned short)
TEST_SPRINTF(test_s21_sprintf_hX_max, "%hX", USHRT_MAX,
             unsigned short)

// ================================================================
// Модификатор hh (char)
// ================================================================

// %hhd - signed char
TEST_SPRINTF(test_s21_sprintf_hhd, "%hhd", 123, signed char)
TEST_SPRINTF(test_s21_sprintf_hhd_min, "%hhd", SCHAR_MIN,
             signed char)
TEST_SPRINTF(test_s21_sprintf_hhd_max, "%hhd", SCHAR_MAX,
             signed char)

// %hhi - signed char
TEST_SPRINTF(test_s21_sprintf_hhi, "%hhi", 123, signed char)
TEST_SPRINTF(test_s21_sprintf_hhi_min, "%hhi", SCHAR_MIN,
             signed char)
TEST_SPRINTF(test_s21_sprintf_hhi_max, "%hhi", SCHAR_MAX,
             signed char)

// %hho - unsigned char
TEST_SPRINTF(test_s21_sprintf_hho, "%hho", 123, unsigned char)
TEST_SPRINTF(test_s21_sprintf_hho_min, "%hho", 0, unsigned char)
TEST_SPRINTF(test_s21_sprintf_hho_max, "%hho", UCHAR_MAX,
             unsigned char)

// %hhu - unsigned char
TEST_SPRINTF(test_s21_sprintf_hhu, "%hhu", 123, unsigned char)
TEST_SPRINTF(test_s21_sprintf_hhu_min, "%hhu", 0, unsigned char)
TEST_SPRINTF(test_s21_sprintf_hhu_max, "%hhu", UCHAR_MAX,
             unsigned char)

// %hhx - unsigned char
TEST_SPRINTF(test_s21_sprintf_hhx, "%hhx", 123, unsigned char)
TEST_SPRINTF(test_s21_sprintf_hhx_min, "%hhx", 0, unsigned char)
TEST_SPRINTF(test_s21_sprintf_hhx_max, "%hhx", UCHAR_MAX,
             unsigned char)

// %hhX - unsigned char
TEST_SPRINTF(test_s21_sprintf_hhX, "%hhX", 123, unsigned char)
TEST_SPRINTF(test_s21_sprintf_hhX_min, "%hhX", 0, unsigned char)
TEST_SPRINTF(test_s21_sprintf_hhX_max, "%hhX", UCHAR_MAX,
             unsigned char)

// ================================================================
// Модификатор l (long)
// ================================================================

// %ld - long
TEST_SPRINTF(test_s21_sprintf_ld, "%ld", 123, long)
TEST_SPRINTF(test_s21_sprintf_ld_min, "%ld", LONG_MIN, long)
TEST_SPRINTF(test_s21_sprintf_ld_max, "%ld", LONG_MAX, long)

// %li - long
TEST_SPRINTF(test_s21_sprintf_li, "%li", 123, long)
TEST_SPRINTF(test_s21_sprintf_li_min, "%li", LONG_MIN, long)
TEST_SPRINTF(test_s21_sprintf_li_max, "%li", LONG_MAX, long)

// %lo - unsigned long
TEST_SPRINTF(test_s21_sprintf_lo, "%lo", 123, unsigned long)
TEST_SPRINTF(test_s21_sprintf_lo_min, "%lo", 0, unsigned long)
TEST_SPRINTF(test_s21_sprintf_lo_max, "%lo", ULONG_MAX,
             unsigned long)

// %lu - unsigned long
TEST_SPRINTF(test_s21_sprintf_lu, "%lu", 123, unsigned long)
TEST_SPRINTF(test_s21_sprintf_lu_min, "%lu", 0, unsigned long)
TEST_SPRINTF(test_s21_sprintf_lu_max, "%lu", ULONG_MAX,
             unsigned long)

// %lx - unsigned long
TEST_SPRINTF(test_s21_sprintf_lx, "%lx", 123, unsigned long)
TEST_SPRINTF(test_s21_sprintf_lx_min, "%lx", 0, unsigned long)
TEST_SPRINTF(test_s21_sprintf_lx_max, "%lx", ULONG_MAX,
             unsigned long)

// %lX - unsigned long
TEST_SPRINTF(test_s21_sprintf_lX, "%lX", 123, unsigned long)
TEST_SPRINTF(test_s21_sprintf_lX_min, "%lX", 0, unsigned long)
TEST_SPRINTF(test_s21_sprintf_lX_max, "%lX", USHRT_MAX,
             unsigned long)

// ================================================================
// Модификатор ll (long long)
// ================================================================

// %lld - long long
TEST_SPRINTF(test_s21_sprintf_lld, "%lld", 123, long long)
TEST_SPRINTF(test_s21_sprintf_lld_min, "%lld", LLONG_MIN, long long)
TEST_SPRINTF(test_s21_sprintf_lld_max, "%lld", LLONG_MAX, long long)

// %lli - long long
TEST_SPRINTF(test_s21_sprintf_lli, "%lli", 123, long long)
TEST_SPRINTF(test_s21_sprintf_lli_min, "%lli", LLONG_MIN, long long)
TEST_SPRINTF(test_s21_sprintf_lli_max, "%lli", LLONG_MAX, long long)

// %llo - unsigned long long
TEST_SPRINTF(test_s21_sprintf_llo, "%llo", 123,
             unsigned long long)
TEST_SPRINTF(test_s21_sprintf_llo_min, "%llo", 0,
             unsigned long long)
TEST_SPRINTF(test_s21_sprintf_llo_max, "%llo", ULLONG_MAX,
             unsigned long long)

// %llu - unsigned long long
TEST_SPRINTF(test_s21_sprintf_llu, "%llu", 123,
             unsigned long long)
TEST_SPRINTF(test_s21_sprintf_llu_min, "%llu", 0,
             unsigned long long)
TEST_SPRINTF(test_s21_sprintf_llu_max, "%llu", ULLONG_MAX,
             unsigned long long)

// %llx - unsigned long long
TEST_SPRINTF(test_s21_sprintf_llx, "%llx", 123,
             unsigned long long)
TEST_SPRINTF(test_s21_sprintf_llx_min, "%llx", 0,
             unsigned long long)
TEST_SPRINTF(test_s21_sprintf_llx_max, "%llx", ULLONG_MAX,
             unsigned long long)

// %llX - unsigned long long
TEST_SPRINTF(test_s21_sprintf_llX, "%llX", 123,
             unsigned long long)
TEST_SPRINTF(test_s21_sprintf_llX_min, "%llX", 0,
             unsigned long long)
TEST_SPRINTF(test_s21_sprintf_llX_max, "%llX", ULLONG_MAX,
             unsigned long long)

// ================================================================
// Строковые типы
// ================================================================

// %c - char
TEST_SPRINTF(test_s21_sprintf_c, "%c", 'A', char)
TEST_SPRINTF(test_s21_sprintf_c_min, "%c", -128, char)
TEST_SPRINTF(test_s21_sprintf_c_max, "%c", 127, char)
TEST_SPRINTF(test_s21_sprintf_c_nonprint, "%c", '\x01', char)
TEST_SPRINTF(test_s21_sprintf_c_zero, "%c", 0, char)
TEST_SPRINTF(test_s21_sprintf_c_newline, "%c", '\n', char)
TEST_SPRINTF(test_s21_sprintf_c_tab, "%c", '\t', char)
TEST_SPRINTF(test_s21_sprintf_c_null_char, "%c", '\0', char)

// %s - string
TEST_SSCANF_S(test_s21_sprintf_s, "%s", "Hello, world!")
TEST_SSCANF_S(test_s21_sprintf_s_special, "%s", "Hello\tWorld\n")
TEST_SSCANF_S(test_s21_sprintf_s_special_chars, "%s","Line1\nLine2\tTab\x01")
TEST_SSCANF_S(test_s21_sprintf_s_unicode, "%s", "Привет мир!")
TEST_SSCANF_S(test_s21_sprintf_s_null, "%s", NULL)
TEST_SSCANF_S(test_s21_sprintf_s_empty, "%s", "")

// ================================================================
// Вещественные типы
// ================================================================

// // %e %E %f %g %G
// TEST_SPRINTF(test_s21_sprintf_e_zero, "%e", 0.0, double)
// TEST_SPRINTF(test_s21_sprintf_e_minus_zero, "%e", -0.0, double)
// TEST_SPRINTF(test_s21_sprintf_E_zero, "%E", 0.0, double)
// TEST_SPRINTF(test_s21_sprintf_E_minus_zero, "%E", -0.0, double)
// TEST_SPRINTF(test_s21_sprintf_f_zero, "%f", 0.0, double)
// TEST_SPRINTF(test_s21_sprintf_f_minus_zero, "%f", -0.0, double)
// TEST_SPRINTF(test_s21_sprintf_g_zero, "%g", 0.0, double)
// TEST_SPRINTF(test_s21_sprintf_g_minus_zero, "%g", -0.0, double)
// TEST_SPRINTF(test_s21_sprintf_G_zero, "%G", 0.0, double)
// TEST_SPRINTF(test_s21_sprintf_G_minus_zero, "%G", -0.0, double)
// // %le %lE %lf %lg %lG
// TEST_SPRINTF(test_s21_sprintf_le_zero, "%le", 0.0, double)
// TEST_SPRINTF(test_s21_sprintf_le_minus_zero, "%le", -0.0, double)
// TEST_SPRINTF(test_s21_sprintf_lE_zero, "%lE", 0.0, double)
// TEST_SPRINTF(test_s21_sprintf_lE_minus_zero, "%lE", -0.0, double)
// TEST_SPRINTF(test_s21_sprintf_lf_zero, "%lf", 0.0, double)
// TEST_SPRINTF(test_s21_sprintf_lf_minus_zero, "%lf", -0.0, double)
// TEST_SPRINTF(test_s21_sprintf_lg_zero, "%lg", 0.0, double)
// TEST_SPRINTF(test_s21_sprintf_lg_minus_zero, "%lg", -0.0, double)
// TEST_SPRINTF(test_s21_sprintf_lG_zero, "%lG", 0.0, double)
// TEST_SPRINTF(test_s21_sprintf_lG_minus_zero, "%lG", -0.0, double)
// // %Le %LE %Lf %Lg %LG
// TEST_SPRINTF(test_s21_sprintf_Le_zero, "%Le", 0.0L, long double)
// TEST_SPRINTF(test_s21_sprintf_Le_minus_zero, "%Le", -0.0L, long double)
// TEST_SPRINTF(test_s21_sprintf_LE_zero, "%LE", 0.0L, long double)
// TEST_SPRINTF(test_s21_sprintf_LE_minus_zero, "%LE", -0.0L, long double)
// TEST_SPRINTF(test_s21_sprintf_Lf_zero, "%Lf", 0.0L, long double)
// TEST_SPRINTF(test_s21_sprintf_Lf_minus_zero, "%Lf", -0.0L, long double)
// TEST_SPRINTF(test_s21_sprintf_Lg_zero, "%Lg", 0.0L, long double)
// TEST_SPRINTF(test_s21_sprintf_Lg_minus_zero, "%Lg", -0.0L, long double)
// TEST_SPRINTF(test_s21_sprintf_LG_zero, "%LG", 0.0L, long double)
// TEST_SPRINTF(test_s21_sprintf_LG_minus_zero, "%LG", -0.0L, long double)

// // %e %E %f %g %G
// TEST_SPRINTF(test_s21_sprintf_e, "%e", 123.456, double)
// TEST_SPRINTF(test_s21_sprintf_e_neg, "%e", -123.456, double)
// TEST_SPRINTF(test_s21_sprintf_e_big, "%e", 1e308, double)
// TEST_SPRINTF(test_s21_sprintf_e_small, "%e", 1e-308, double)
// TEST_SPRINTF(test_s21_sprintf_E, "%E", 123.456, double)
// TEST_SPRINTF(test_s21_sprintf_E_neg, "%E", -123.456, double)
// TEST_SPRINTF(test_s21_sprintf_E_big, "%E", 1e308, double)
// TEST_SPRINTF(test_s21_sprintf_E_small, "%E", 1e-308, double)
// TEST_SPRINTF(test_s21_sprintf_f, "%f", 123.456, double)
// TEST_SPRINTF(test_s21_sprintf_f2, "%f", 123.9999996, double)
// TEST_SPRINTF(test_s21_sprintf_f_neg, "%f", -123.456, double)
// TEST_SPRINTF(test_s21_sprintf_f_small, "%f", 1e-308, double)
// TEST_SPRINTF(test_s21_sprintf_g, "%g", 123.456, double)
// TEST_SPRINTF(test_s21_sprintf_g2, "%g", 123.9999996, double)
// TEST_SPRINTF(test_s21_sprintf_g3, "%g", 1.89, double)
// TEST_SPRINTF(test_s21_sprintf_g_neg, "%g", -123.456, double)
// TEST_SPRINTF(test_s21_sprintf_g_big, "%g", 1e308, double)
// TEST_SPRINTF(test_s21_sprintf_g_small, "%g", 1e-308, double)
// TEST_SPRINTF(test_s21_sprintf_G, "%G", 123.456, double)
// TEST_SPRINTF(test_s21_sprintf_G2, "%G", 123.9999996, double)
// TEST_SPRINTF(test_s21_sprintf_G3, "%G", 1.89, double)
// TEST_SPRINTF(test_s21_sprintf_G_neg, "%G", -123.456, double)
// TEST_SPRINTF(test_s21_sprintf_G_big, "%G", 1e308, double)
// TEST_SPRINTF(test_s21_sprintf_G_small, "%G", 1e-308, double)
// // %le %lE %lf %lg %lG
// TEST_SPRINTF(test_s21_sprintf_le, "%le", 123.456, double)
// TEST_SPRINTF(test_s21_sprintf_le_neg, "%le", -123.456, double)
// TEST_SPRINTF(test_s21_sprintf_le_big, "%le", 1e308, double)
// TEST_SPRINTF(test_s21_sprintf_le_small, "%le", 1e-308, double)
// TEST_SPRINTF(test_s21_sprintf_lE, "%lE", 123.456, double)
// TEST_SPRINTF(test_s21_sprintf_lE_neg, "%lE", -123.456, double)
// TEST_SPRINTF(test_s21_sprintf_lE_big, "%lE", 1e308, double)
// TEST_SPRINTF(test_s21_sprintf_lE_small, "%lE", 1e-308, double)
// TEST_SPRINTF(test_s21_sprintf_lf, "%lf", 123.456, double)
// TEST_SPRINTF(test_s21_sprintf_lf2, "%lf", 123.9999996, double)
// TEST_SPRINTF(test_s21_sprintf_lf_neg, "%lf", -123.456, double)
// TEST_SPRINTF(test_s21_sprintf_lf_small, "%lf", 1e-308, double)
// TEST_SPRINTF(test_s21_sprintf_lg, "%lg", 123.456, double)
// TEST_SPRINTF(test_s21_sprintf_lg2, "%lg", 123.9999996, double)
// TEST_SPRINTF(test_s21_sprintf_lg3, "%lg", 1.89, double)
// TEST_SPRINTF(test_s21_sprintf_lg_neg, "%lg", -123.456, double)
// TEST_SPRINTF(test_s21_sprintf_lg_big, "%lg", 1e308, double)
// TEST_SPRINTF(test_s21_sprintf_lg_small, "%lg", 1e-308, double)
// TEST_SPRINTF(test_s21_sprintf_lG, "%lG", 123.456, double)
// TEST_SPRINTF(test_s21_sprintf_lG2, "%lG", 123.9999996, double)
// TEST_SPRINTF(test_s21_sprintf_lG3, "%lG", 1.89, double)
// TEST_SPRINTF(test_s21_sprintf_lG_neg, "%lG", -123.456, double)
// TEST_SPRINTF(test_s21_sprintf_lG_big, "%lG", 1e308, double)
// TEST_SPRINTF(test_s21_sprintf_lG_small, "%lG", 1e-308, double)
// // %Le %LE %Lf %Lg %LG
// TEST_SPRINTF(test_s21_sprintf_Le, "%Le", 123.456L, long double)
// TEST_SPRINTF(test_s21_sprintf_Le_neg, "%Le", -123.456L, long double)
// TEST_SPRINTF(test_s21_sprintf_Le_big, "%Le", 1e308L, long double)
// TEST_SPRINTF(test_s21_sprintf_Le_small, "%Le", 1e-308L, long double)
// TEST_SPRINTF(test_s21_sprintf_LE, "%LE", 123.456L, long double)
// TEST_SPRINTF(test_s21_sprintf_LE_neg, "%LE", -123.456L, long double)
// TEST_SPRINTF(test_s21_sprintf_LE_big, "%LE", 1e308L, long double)
// TEST_SPRINTF(test_s21_sprintf_LE_small, "%LE", 1e-308L, long double)
// TEST_SPRINTF(test_s21_sprintf_Lf, "%Lf", 123.456L, long double)
// TEST_SPRINTF(test_s21_sprintf_Lf2, "%Lf", 123.9999996L, long double)
// TEST_SPRINTF(test_s21_sprintf_Lf_neg, "%Lf", -123.456L, long double)
// TEST_SPRINTF(test_s21_sprintf_Lf_small, "%Lf", 1e-308L, long double)
// TEST_SPRINTF(test_s21_sprintf_Lg, "%Lg", 123.456L, long double)
// TEST_SPRINTF(test_s21_sprintf_Lg2, "%Lg", 123.9999996L, long double)
// TEST_SPRINTF(test_s21_sprintf_Lg3, "%Lg", 1.89L, long double)
// TEST_SPRINTF(test_s21_sprintf_Lg_neg, "%Lg", -123.456L, long double)
// TEST_SPRINTF(test_s21_sprintf_Lg_big, "%Lg", 1e308L, long double)
// TEST_SPRINTF(test_s21_sprintf_Lg_small, "%Lg", 1e-308L, long double)
// TEST_SPRINTF(test_s21_sprintf_LG, "%LG", 123.456L, long double)
// TEST_SPRINTF(test_s21_sprintf_LG2, "%LG", 123.9999996L, long double)
// TEST_SPRINTF(test_s21_sprintf_LG3, "%LG", 1.89L, long double)
// TEST_SPRINTF(test_s21_sprintf_LG_neg, "%LG", -123.456L, long double)
// TEST_SPRINTF(test_s21_sprintf_LG_big, "%LG", 1e308L, long double)
// TEST_SPRINTF(test_s21_sprintf_LG_small, "%LG", 1e-308L, long double)

// // %g - double
// TEST_SPRINTF(test_s21_sprintf_g_switch_to_e, "%g", 0.0000123456, double)
// TEST_SPRINTF(test_s21_sprintf_g_switch_to_f, "%g", 123.456, double)
// TEST_SPRINTF(test_s21_sprintf_g_switch, "%g", 123456789.0, double)
// TEST_SPRINTF(test_s21_sprintf_G_switch_to_e, "%G", 0.0000123456, double)
// TEST_SPRINTF(test_s21_sprintf_G_switch_to_f, "%G", 123.456, double)
// TEST_SPRINTF(test_s21_sprintf_G_switch, "%G", 123456789.0, double)

// // ================================================================
// // Вещественные типы: NaN и INFINITY
// // ================================================================

// // %e %E %f %g %G
// TEST_SPRINTF(test_s21_sprintf_e_nan, "%e", NAN, double)
// TEST_SPRINTF(test_s21_sprintf_e_inf, "%e", INFINITY, double)
// TEST_SPRINTF(test_s21_sprintf_e_neg_inf, "%e", -INFINITY, double)
// TEST_SPRINTF(test_s21_sprintf_E_nan, "%E", NAN, double)
// TEST_SPRINTF(test_s21_sprintf_E_inf, "%E", INFINITY, double)
// TEST_SPRINTF(test_s21_sprintf_E_neg_inf, "%E", -INFINITY, double)
// TEST_SPRINTF(test_s21_sprintf_f_nan, "%f", NAN, double)
// TEST_SPRINTF(test_s21_sprintf_f_inf, "%f", INFINITY, double)
// TEST_SPRINTF(test_s21_sprintf_f_neg_inf, "%f", -INFINITY, double)
// TEST_SPRINTF(test_s21_sprintf_g_nan, "%g", NAN, double)
// TEST_SPRINTF(test_s21_sprintf_g_inf, "%g", INFINITY, double)
// TEST_SPRINTF(test_s21_sprintf_g_neg_inf, "%g", -INFINITY, double)
// TEST_SPRINTF(test_s21_sprintf_G_nan, "%G", NAN, double)
// TEST_SPRINTF(test_s21_sprintf_G_inf, "%G", INFINITY, double)
// TEST_SPRINTF(test_s21_sprintf_G_neg_inf, "%G", -INFINITY, double)
// // %le %lE %lf %lg %lG
// TEST_SPRINTF(test_s21_sprintf_le_nan, "%le", NAN, double)
// TEST_SPRINTF(test_s21_sprintf_le_inf, "%le", INFINITY, double)
// TEST_SPRINTF(test_s21_sprintf_le_neg_inf, "%le", -INFINITY, double)
// TEST_SPRINTF(test_s21_sprintf_lE_nan, "%lE", NAN, double)
// TEST_SPRINTF(test_s21_sprintf_lE_inf, "%lE", INFINITY, double)
// TEST_SPRINTF(test_s21_sprintf_lE_neg_inf, "%lE", -INFINITY, double)
// TEST_SPRINTF(test_s21_sprintf_lf_nan, "%lf", NAN, double)
// TEST_SPRINTF(test_s21_sprintf_lf_inf, "%lf", INFINITY, double)
// TEST_SPRINTF(test_s21_sprintf_lf_neg_inf, "%lf", -INFINITY, double)
// TEST_SPRINTF(test_s21_sprintf_lg_nan, "%lg", NAN, double)
// TEST_SPRINTF(test_s21_sprintf_lg_inf, "%lg", INFINITY, double)
// TEST_SPRINTF(test_s21_sprintf_lg_neg_inf, "%lg", -INFINITY, double)
// TEST_SPRINTF(test_s21_sprintf_lG_nan, "%lG", NAN, double)
// TEST_SPRINTF(test_s21_sprintf_lG_inf, "%lG", INFINITY, double)
// TEST_SPRINTF(test_s21_sprintf_lG_neg_inf, "%lG", -INFINITY, double)
// // %Le %LE %Lf %Lg %LG
// TEST_SPRINTF(test_s21_sprintf_Le_nan, "%Le", (long double)NAN,
//              long double)
// TEST_SPRINTF(test_s21_sprintf_Le_inf, "%Le", (long double)INFINITY,
//              long double)
// TEST_SPRINTF(test_s21_sprintf_Le_neg_inf, "%Le",
//              (long double)(-INFINITY), long double)
// TEST_SPRINTF(test_s21_sprintf_LE_nan, "%LE", (long double)NAN,
//              long double)
// TEST_SPRINTF(test_s21_sprintf_LE_inf, "%LE", (long double)INFINITY,
//              long double)
// TEST_SPRINTF(test_s21_sprintf_LE_neg_inf, "%LE",
//              (long double)(-INFINITY), long double)
// TEST_SPRINTF(test_s21_sprintf_Lf_nan, "%Lf", (long double)NAN,
//              long double)
// TEST_SPRINTF(test_s21_sprintf_Lf_inf, "%Lf", (long double)INFINITY,
//              long double)
// TEST_SPRINTF(test_s21_sprintf_Lf_neg_inf, "%Lf",
//              (long double)(-INFINITY), long double)
// TEST_SPRINTF(test_s21_sprintf_Lg_nan, "%Lg", (long double)NAN,
//              long double)
// TEST_SPRINTF(test_s21_sprintf_Lg_inf, "%Lg", (long double)INFINITY,
//              long double)
// TEST_SPRINTF(test_s21_sprintf_Lg_neg_inf, "%Lg",
//              (long double)(-INFINITY), long double)
// TEST_SPRINTF(test_s21_sprintf_LG_nan, "%LG", (long double)NAN,
//              long double)
// TEST_SPRINTF(test_s21_sprintf_LG_inf, "%LG", (long double)INFINITY,
//              long double)
// TEST_SPRINTF(test_s21_sprintf_LG_neg_inf, "%LG",
//              (long double)(-INFINITY), long double)

// ================================================================
// Test suite
// ================================================================

Suite *sscanf_suite(void) {
  Suite *s = suite_create("test_sscanf");
  TCase *tc = tcase_create("Core");

      tcase_add_test(tc, test_s21_sprintf_d);
    tcase_add_test(tc, test_s21_sprintf_d_min);
    tcase_add_test(tc, test_s21_sprintf_d_max);
    tcase_add_test(tc, test_s21_sprintf_i);
    tcase_add_test(tc, test_s21_sprintf_i_min);
    tcase_add_test(tc, test_s21_sprintf_i_max);
    tcase_add_test(tc, test_s21_sprintf_o);
    tcase_add_test(tc, test_s21_sprintf_o_min);
    tcase_add_test(tc, test_s21_sprintf_o_max);
    tcase_add_test(tc, test_s21_sprintf_u);
    tcase_add_test(tc, test_s21_sprintf_u_min);
    tcase_add_test(tc, test_s21_sprintf_u_max);
    tcase_add_test(tc, test_s21_sprintf_x);
    tcase_add_test(tc, test_s21_sprintf_x_min);
    tcase_add_test(tc, test_s21_sprintf_x_max);
    tcase_add_test(tc, test_s21_sprintf_X);
    tcase_add_test(tc, test_s21_sprintf_X_min);
    tcase_add_test(tc, test_s21_sprintf_X_max);
    tcase_add_test(tc, test_s21_sprintf_hd);
    tcase_add_test(tc, test_s21_sprintf_hd_min);
    tcase_add_test(tc, test_s21_sprintf_hd_max);
    tcase_add_test(tc, test_s21_sprintf_hi);
    tcase_add_test(tc, test_s21_sprintf_hi_min);
    tcase_add_test(tc, test_s21_sprintf_hi_max);
    tcase_add_test(tc, test_s21_sprintf_ho);
    tcase_add_test(tc, test_s21_sprintf_ho_min);
    tcase_add_test(tc, test_s21_sprintf_ho_max);
    tcase_add_test(tc, test_s21_sprintf_hu);
    tcase_add_test(tc, test_s21_sprintf_hu_min);
    tcase_add_test(tc, test_s21_sprintf_hu_max);
    tcase_add_test(tc, test_s21_sprintf_hx);
    tcase_add_test(tc, test_s21_sprintf_hx_min);
    tcase_add_test(tc, test_s21_sprintf_hx_max);
    tcase_add_test(tc, test_s21_sprintf_hX);
    tcase_add_test(tc, test_s21_sprintf_hX_min);
    tcase_add_test(tc, test_s21_sprintf_hX_max);
    tcase_add_test(tc, test_s21_sprintf_hhd);
    tcase_add_test(tc, test_s21_sprintf_hhd_min);
    tcase_add_test(tc, test_s21_sprintf_hhd_max);
    tcase_add_test(tc, test_s21_sprintf_hhi);
    tcase_add_test(tc, test_s21_sprintf_hhi_min);
    tcase_add_test(tc, test_s21_sprintf_hhi_max);
    tcase_add_test(tc, test_s21_sprintf_hho);
    tcase_add_test(tc, test_s21_sprintf_hho_min);
    tcase_add_test(tc, test_s21_sprintf_hho_max);
    tcase_add_test(tc, test_s21_sprintf_hhu);
    tcase_add_test(tc, test_s21_sprintf_hhu_min);
    tcase_add_test(tc, test_s21_sprintf_hhu_max);
    tcase_add_test(tc, test_s21_sprintf_hhx);
    tcase_add_test(tc, test_s21_sprintf_hhx_min);
    tcase_add_test(tc, test_s21_sprintf_hhx_max);
    tcase_add_test(tc, test_s21_sprintf_hhX);
    tcase_add_test(tc, test_s21_sprintf_hhX_min);
    tcase_add_test(tc, test_s21_sprintf_hhX_max);
    tcase_add_test(tc, test_s21_sprintf_ld);
    tcase_add_test(tc, test_s21_sprintf_ld_min);
    tcase_add_test(tc, test_s21_sprintf_ld_max);
    tcase_add_test(tc, test_s21_sprintf_li);
    tcase_add_test(tc, test_s21_sprintf_li_min);
    tcase_add_test(tc, test_s21_sprintf_li_max);
    tcase_add_test(tc, test_s21_sprintf_lo);
    tcase_add_test(tc, test_s21_sprintf_lo_min);
    tcase_add_test(tc, test_s21_sprintf_lo_max);
    tcase_add_test(tc, test_s21_sprintf_lu);
    tcase_add_test(tc, test_s21_sprintf_lu_min);
    tcase_add_test(tc, test_s21_sprintf_lu_max);
    tcase_add_test(tc, test_s21_sprintf_lx);
    tcase_add_test(tc, test_s21_sprintf_lx_min);
    tcase_add_test(tc, test_s21_sprintf_lx_max);
    tcase_add_test(tc, test_s21_sprintf_lX);
    tcase_add_test(tc, test_s21_sprintf_lX_min);
    tcase_add_test(tc, test_s21_sprintf_lX_max);
    tcase_add_test(tc, test_s21_sprintf_lld);
    tcase_add_test(tc, test_s21_sprintf_lld_min);
    tcase_add_test(tc, test_s21_sprintf_lld_max);
    tcase_add_test(tc, test_s21_sprintf_lli);
    tcase_add_test(tc, test_s21_sprintf_lli_min);
    tcase_add_test(tc, test_s21_sprintf_lli_max);
    tcase_add_test(tc, test_s21_sprintf_llo);
    tcase_add_test(tc, test_s21_sprintf_llo_min);
    tcase_add_test(tc, test_s21_sprintf_llo_max);
    tcase_add_test(tc, test_s21_sprintf_llu);
    tcase_add_test(tc, test_s21_sprintf_llu_min);
    tcase_add_test(tc, test_s21_sprintf_llu_max);
    tcase_add_test(tc, test_s21_sprintf_llx);
    tcase_add_test(tc, test_s21_sprintf_llx_min);
    tcase_add_test(tc, test_s21_sprintf_llx_max);
    tcase_add_test(tc, test_s21_sprintf_llX);
    tcase_add_test(tc, test_s21_sprintf_llX_min);
    tcase_add_test(tc, test_s21_sprintf_llX_max);
    tcase_add_test(tc, test_s21_sprintf_c);
    tcase_add_test(tc, test_s21_sprintf_c_min);
    tcase_add_test(tc, test_s21_sprintf_c_max);
    tcase_add_test(tc, test_s21_sprintf_c_nonprint);
    tcase_add_test(tc, test_s21_sprintf_c_zero);
    tcase_add_test(tc, test_s21_sprintf_c_newline);
    tcase_add_test(tc, test_s21_sprintf_c_tab);
    tcase_add_test(tc, test_s21_sprintf_c_null_char);
    // tcase_add_test(tc, test_s21_sprintf_e_zero);
    // tcase_add_test(tc, test_s21_sprintf_e_minus_zero);
    // tcase_add_test(tc, test_s21_sprintf_E_zero);
    // tcase_add_test(tc, test_s21_sprintf_E_minus_zero);
    // tcase_add_test(tc, test_s21_sprintf_f_zero);
    // tcase_add_test(tc, test_s21_sprintf_f_minus_zero);
    // tcase_add_test(tc, test_s21_sprintf_g_zero);
    // tcase_add_test(tc, test_s21_sprintf_g_minus_zero);
    // tcase_add_test(tc, test_s21_sprintf_G_zero);
    // tcase_add_test(tc, test_s21_sprintf_G_minus_zero);
    // tcase_add_test(tc, test_s21_sprintf_le_zero);
    // tcase_add_test(tc, test_s21_sprintf_le_minus_zero);
    // tcase_add_test(tc, test_s21_sprintf_lE_zero);
    // tcase_add_test(tc, test_s21_sprintf_lE_minus_zero);
    // tcase_add_test(tc, test_s21_sprintf_lf_zero);
    // tcase_add_test(tc, test_s21_sprintf_lf_minus_zero);
    // tcase_add_test(tc, test_s21_sprintf_lg_zero);
    // tcase_add_test(tc, test_s21_sprintf_lg_minus_zero);
    // tcase_add_test(tc, test_s21_sprintf_lG_zero);
    // tcase_add_test(tc, test_s21_sprintf_lG_minus_zero);
    // tcase_add_test(tc, test_s21_sprintf_Le_zero);
    // tcase_add_test(tc, test_s21_sprintf_Le_minus_zero);
    // tcase_add_test(tc, test_s21_sprintf_LE_zero);
    // tcase_add_test(tc, test_s21_sprintf_LE_minus_zero);
    // tcase_add_test(tc, test_s21_sprintf_Lf_zero);
    // tcase_add_test(tc, test_s21_sprintf_Lf_minus_zero);
    // tcase_add_test(tc, test_s21_sprintf_Lg_zero);
    // tcase_add_test(tc, test_s21_sprintf_Lg_minus_zero);
    // tcase_add_test(tc, test_s21_sprintf_LG_zero);
    // tcase_add_test(tc, test_s21_sprintf_LG_minus_zero);
    // tcase_add_test(tc, test_s21_sprintf_e);
    // tcase_add_test(tc, test_s21_sprintf_e_neg);
    // tcase_add_test(tc, test_s21_sprintf_e_big);
    // tcase_add_test(tc, test_s21_sprintf_e_small);
    // tcase_add_test(tc, test_s21_sprintf_E);
    // tcase_add_test(tc, test_s21_sprintf_E_neg);
    // tcase_add_test(tc, test_s21_sprintf_E_big);
    // tcase_add_test(tc, test_s21_sprintf_E_small);
    // tcase_add_test(tc, test_s21_sprintf_f);
    // tcase_add_test(tc, test_s21_sprintf_f2);
    // tcase_add_test(tc, test_s21_sprintf_f_neg);
    // tcase_add_test(tc, test_s21_sprintf_f_small);
    // tcase_add_test(tc, test_s21_sprintf_g);
    // tcase_add_test(tc, test_s21_sprintf_g2);
    // tcase_add_test(tc, test_s21_sprintf_g3);
    // tcase_add_test(tc, test_s21_sprintf_g_neg);
    // tcase_add_test(tc, test_s21_sprintf_g_big);
    // tcase_add_test(tc, test_s21_sprintf_g_small);
    // tcase_add_test(tc, test_s21_sprintf_G);
    // tcase_add_test(tc, test_s21_sprintf_G2);
    // tcase_add_test(tc, test_s21_sprintf_G3);
    // tcase_add_test(tc, test_s21_sprintf_G_neg);
    // tcase_add_test(tc, test_s21_sprintf_G_big);
    // tcase_add_test(tc, test_s21_sprintf_G_small);
    // tcase_add_test(tc, test_s21_sprintf_le);
    // tcase_add_test(tc, test_s21_sprintf_le_neg);
    // tcase_add_test(tc, test_s21_sprintf_le_big);
    // tcase_add_test(tc, test_s21_sprintf_le_small);
    // tcase_add_test(tc, test_s21_sprintf_lE);
    // tcase_add_test(tc, test_s21_sprintf_lE_neg);
    // tcase_add_test(tc, test_s21_sprintf_lE_big);
    // tcase_add_test(tc, test_s21_sprintf_lE_small);
    // tcase_add_test(tc, test_s21_sprintf_lf);
    // tcase_add_test(tc, test_s21_sprintf_lf2);
    // tcase_add_test(tc, test_s21_sprintf_lf_neg);
    // tcase_add_test(tc, test_s21_sprintf_lf_small);
    // tcase_add_test(tc, test_s21_sprintf_lg);
    // tcase_add_test(tc, test_s21_sprintf_lg2);
    // tcase_add_test(tc, test_s21_sprintf_lg3);
    // tcase_add_test(tc, test_s21_sprintf_lg_neg);
    // tcase_add_test(tc, test_s21_sprintf_lg_big);
    // tcase_add_test(tc, test_s21_sprintf_lg_small);
    // tcase_add_test(tc, test_s21_sprintf_lG);
    // tcase_add_test(tc, test_s21_sprintf_lG2);
    // tcase_add_test(tc, test_s21_sprintf_lG3);
    // tcase_add_test(tc, test_s21_sprintf_lG_neg);
    // tcase_add_test(tc, test_s21_sprintf_lG_big);
    // tcase_add_test(tc, test_s21_sprintf_lG_small);
    // tcase_add_test(tc, test_s21_sprintf_Le);
    // tcase_add_test(tc, test_s21_sprintf_Le_neg);
    // tcase_add_test(tc, test_s21_sprintf_Le_big);
    // tcase_add_test(tc, test_s21_sprintf_Le_small);
    // tcase_add_test(tc, test_s21_sprintf_LE);
    // tcase_add_test(tc, test_s21_sprintf_LE_neg);
    // tcase_add_test(tc, test_s21_sprintf_LE_big);
    // tcase_add_test(tc, test_s21_sprintf_LE_small);
    // tcase_add_test(tc, test_s21_sprintf_Lf);
    // tcase_add_test(tc, test_s21_sprintf_Lf2);
    // tcase_add_test(tc, test_s21_sprintf_Lf_neg);
    // tcase_add_test(tc, test_s21_sprintf_Lf_small);
    // tcase_add_test(tc, test_s21_sprintf_Lg);
    // tcase_add_test(tc, test_s21_sprintf_Lg2);
    // tcase_add_test(tc, test_s21_sprintf_Lg3);
    // tcase_add_test(tc, test_s21_sprintf_Lg_neg);
    // tcase_add_test(tc, test_s21_sprintf_Lg_big);
    // tcase_add_test(tc, test_s21_sprintf_Lg_small);
    // tcase_add_test(tc, test_s21_sprintf_LG);
    // tcase_add_test(tc, test_s21_sprintf_LG2);
    // tcase_add_test(tc, test_s21_sprintf_LG3);
    // tcase_add_test(tc, test_s21_sprintf_LG_neg);
    // tcase_add_test(tc, test_s21_sprintf_LG_big);
    // tcase_add_test(tc, test_s21_sprintf_LG_small);
    // tcase_add_test(tc, test_s21_sprintf_g_switch_to_e);
    // tcase_add_test(tc, test_s21_sprintf_g_switch_to_f);
    // tcase_add_test(tc, test_s21_sprintf_g_switch);
    // tcase_add_test(tc, test_s21_sprintf_G_switch_to_e);
    // tcase_add_test(tc, test_s21_sprintf_G_switch_to_f);
    // tcase_add_test(tc, test_s21_sprintf_G_switch);
    // tcase_add_test(tc, test_s21_sprintf_e_nan);
    // tcase_add_test(tc, test_s21_sprintf_e_inf);
    // tcase_add_test(tc, test_s21_sprintf_e_neg_inf);
    // tcase_add_test(tc, test_s21_sprintf_E_nan);
    // tcase_add_test(tc, test_s21_sprintf_E_inf);
    // tcase_add_test(tc, test_s21_sprintf_E_neg_inf);
    // tcase_add_test(tc, test_s21_sprintf_f_nan);
    // tcase_add_test(tc, test_s21_sprintf_f_inf);
    // tcase_add_test(tc, test_s21_sprintf_f_neg_inf);
    // tcase_add_test(tc, test_s21_sprintf_g_nan);
    // tcase_add_test(tc, test_s21_sprintf_g_inf);
    // tcase_add_test(tc, test_s21_sprintf_g_neg_inf);
    // tcase_add_test(tc, test_s21_sprintf_G_nan);
    // tcase_add_test(tc, test_s21_sprintf_G_inf);
    // tcase_add_test(tc, test_s21_sprintf_G_neg_inf);
    // tcase_add_test(tc, test_s21_sprintf_le_nan);
    // tcase_add_test(tc, test_s21_sprintf_le_inf);
    // tcase_add_test(tc, test_s21_sprintf_le_neg_inf);
    // tcase_add_test(tc, test_s21_sprintf_lE_nan);
    // tcase_add_test(tc, test_s21_sprintf_lE_inf);
    // tcase_add_test(tc, test_s21_sprintf_lE_neg_inf);
    // tcase_add_test(tc, test_s21_sprintf_lf_nan);
    // tcase_add_test(tc, test_s21_sprintf_lf_inf);
    // tcase_add_test(tc, test_s21_sprintf_lf_neg_inf);
    // tcase_add_test(tc, test_s21_sprintf_lg_nan);
    // tcase_add_test(tc, test_s21_sprintf_lg_inf);
    // tcase_add_test(tc, test_s21_sprintf_lg_neg_inf);
    // tcase_add_test(tc, test_s21_sprintf_lG_nan);
    // tcase_add_test(tc, test_s21_sprintf_lG_inf);
    // tcase_add_test(tc, test_s21_sprintf_lG_neg_inf);
    // tcase_add_test(tc, test_s21_sprintf_Le_nan);
    // tcase_add_test(tc, test_s21_sprintf_Le_inf);
    // tcase_add_test(tc, test_s21_sprintf_Le_neg_inf);
    // tcase_add_test(tc, test_s21_sprintf_LE_nan);
    // tcase_add_test(tc, test_s21_sprintf_LE_inf);
    // tcase_add_test(tc, test_s21_sprintf_LE_neg_inf);
    // tcase_add_test(tc, test_s21_sprintf_Lf_nan);
    // tcase_add_test(tc, test_s21_sprintf_Lf_inf);
    // tcase_add_test(tc, test_s21_sprintf_Lf_neg_inf);
    // tcase_add_test(tc, test_s21_sprintf_Lg_nan);
    // tcase_add_test(tc, test_s21_sprintf_Lg_inf);
    // tcase_add_test(tc, test_s21_sprintf_Lg_neg_inf);
    // tcase_add_test(tc, test_s21_sprintf_LG_nan);
    // tcase_add_test(tc, test_s21_sprintf_LG_inf);
    // tcase_add_test(tc, test_s21_sprintf_LG_neg_inf);
  suite_add_tcase(s, tc);
  return s;
}

int main(int argc, char **argv) {
  int failed = 0;
  Suite *s = sscanf_suite();
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