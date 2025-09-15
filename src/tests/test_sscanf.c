#include <check.h>
#include <float.h>
#include <limits.h>
#include <locale.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wchar.h>

#include "../s21_string.h"

// =========================================================================
// МАКРОСЫ
// =========================================================================
#pragma region

// Макрос для тестирования целых чисел
#define TEST_SSCANF_INT(test_name, format, input, type) \
  START_TEST(test_name) {                               \
    type var1_std = 5, var1_s21 = 5;                    \
    int res_std = sscanf(input, format, &var1_std);     \
    int res_s21 = s21_sscanf(input, format, &var1_s21); \
    ck_assert_int_eq(var1_std, var1_s21);               \
    ck_assert_int_eq(res_std, res_s21);                 \
  }                                                     \
  END_TEST

// Макрос для тестирования беззнаковых целых чисел
#define TEST_SSCANF_UINT(test_name, format, input, type) \
  START_TEST(test_name) {                                \
    type var1_std = 5, var1_s21 = 5;                     \
    int res_std = sscanf(input, format, &var1_std);      \
    int res_s21 = s21_sscanf(input, format, &var1_s21);  \
    ck_assert_int_eq(var1_std, var1_s21);                \
    ck_assert_int_eq(res_std, res_s21);                  \
  }                                                      \
  END_TEST

#include <math.h>

// Универсальный макрос для тестирования вещественных чисел
#define TEST_SSCANF_FLOAT(test_name, format, input, type)                      \
  START_TEST(test_name) {                                                      \
    type var1_std = 0, var1_s21 = 0;                                           \
    int res_std = sscanf(input, format, &var1_std);                            \
    int res_s21 = s21_sscanf(input, format, &var1_s21);                        \
                                                                               \
    /* Проверка специальных значений */             \
    if (isnan(var1_std)) {                                                     \
      ck_assert(isnan(var1_s21));                                              \
    } else if (isinf(var1_std)) {                                              \
      ck_assert(isinf(var1_s21));                                              \
      ck_assert(signbit(var1_std) == signbit(var1_s21));                       \
    } else {                                                                   \
      /* Для обычных чисел используем допуск */ \
      ck_assert_float_eq_tol(var1_std, var1_s21, 1e-6);                        \
    }                                                                          \
                                                                               \
    ck_assert_int_eq(res_std, res_s21);                                        \
  }                                                                            \
  END_TEST

// Макрос для тестирования строк
#define TEST_SSCANF_STR(test_name, format, input)      \
  START_TEST(test_name) {                              \
    char str1_std[100] = {0}, str1_s21[100] = {0};     \
    int res_std = sscanf(input, format, str1_std);     \
    int res_s21 = s21_sscanf(input, format, str1_s21); \
    ck_assert_str_eq(str1_std, str1_s21);              \
    ck_assert_int_eq(res_std, res_s21);                \
  }                                                    \
  END_TEST

// Макрос для тестирования символов
#define TEST_SSCANF_CHAR(test_name, format, input)       \
  START_TEST(test_name) {                                \
    char char1_std = 0, char1_s21 = 0;                   \
    int res_std = sscanf(input, format, &char1_std);     \
    int res_s21 = s21_sscanf(input, format, &char1_s21); \
    ck_assert_int_eq(char1_std, char1_s21);              \
    ck_assert_int_eq(res_std, res_s21);                  \
  }                                                      \
  END_TEST

// Макрос для тестирования %n
#define TEST_SSCANF_N(test_name, input, format)       \
  START_TEST(test_name) {                             \
    int n1_std = 0, n1_s21 = 0;                       \
    int res_std = sscanf(input, format, &n1_std);     \
    int res_s21 = s21_sscanf(input, format, &n1_s21); \
    ck_assert_int_eq(n1_std, n1_s21);                 \
    ck_assert_int_eq(res_std, res_s21);               \
  }                                                   \
  END_TEST

// Макрос для тестирования %%
#define TEST_SSCANF_PERCENT(test_name, input, format) \
  START_TEST(test_name) {                             \
    int res_std = sscanf(input, format);              \
    int res_s21 = s21_sscanf(input, format);          \
    ck_assert_int_eq(res_std, res_s21);               \
  }                                                   \
  END_TEST

// Макрос для тестирования указателей
#define TEST_SSCANF_PTR(test_name, format, input)   \
  START_TEST(test_name) {                           \
    void *ptr1 = NULL, *ptr2 = NULL;                \
    int res_std = sscanf(input, format, &ptr1);     \
    int res_s21 = s21_sscanf(input, format, &ptr2); \
    ck_assert_ptr_eq(ptr1, ptr2);                   \
    ck_assert_int_eq(res_std, res_s21);             \
  }                                                 \
  END_TEST

// Макрос для тестирования целых чисел с шириной
#define TEST_SSCANF_INT_WIDTH(test_name, format, input, type) \
  START_TEST(test_name) {                                     \
    type var1_std = 0, var1_s21 = 0;                          \
    int res_std = sscanf(input, format, &var1_std);           \
    int res_s21 = s21_sscanf(input, format, &var1_s21);       \
    ck_assert_int_eq(var1_std, var1_s21);                     \
    ck_assert_int_eq(res_std, res_s21);                       \
  }                                                           \
  END_TEST

// Макрос для тестирования строк с шириной
#define TEST_SSCANF_STR_WIDTH(test_name, format, input) \
  START_TEST(test_name) {                               \
    char str1_std[100] = {0}, str1_s21[100] = {0};      \
    int res_std = sscanf(input, format, str1_std);      \
    int res_s21 = s21_sscanf(input, format, str1_s21);  \
    ck_assert_str_eq(str1_std, str1_s21);               \
    ck_assert_int_eq(res_std, res_s21);                 \
  }                                                     \
  END_TEST

// Макрос для тестирования символов с шириной
#define TEST_SSCANF_CHAR_WIDTH(test_name, format, input) \
  START_TEST(test_name) {                                \
    char char1_std = 0, char1_s21 = 0;                   \
    int res_std = sscanf(input, format, &char1_std);     \
    int res_s21 = s21_sscanf(input, format, &char1_s21); \
    ck_assert_int_eq(char1_std, char1_s21);              \
    ck_assert_int_eq(res_std, res_s21);                  \
  }                                                      \
  END_TEST

// Тесты для граничных значений
TEST_SSCANF_INT(test_int_min, "%d", "-2147483648", int)
TEST_SSCANF_INT(test_int_max, "%d", "2147483647", int)
TEST_SSCANF_UINT(test_uint_max, "%u", "4294967295", unsigned int)
TEST_SSCANF_INT(test_long_min, "%ld", "-9223372036854775808", long)
TEST_SSCANF_INT(test_long_max, "%ld", "9223372036854775807", long)
TEST_SSCANF_UINT(test_ulong_max, "%lu", "18446744073709551615", unsigned long)
TEST_SSCANF_INT(test_llong_min, "%lld", "-9223372036854775808", long long)
TEST_SSCANF_INT(test_llong_max, "%lld", "9223372036854775807", long long)
TEST_SSCANF_UINT(test_ullong_max, "%llu", "18446744073709551615",
                 unsigned long long)

// Тесты для %d
TEST_SSCANF_INT(d_zero, "%d", "0", int)
TEST_SSCANF_INT(d_pos, "%d", "123", int)
TEST_SSCANF_INT(d_neg, "%d", "-123", int)
TEST_SSCANF_INT(d_octal, "%d", "0123", int)
TEST_SSCANF_INT(d_hex, "%d", "0x123", int)
TEST_SSCANF_INT(d_hex_, "%d", "ffffffffff", int)
TEST_SSCANF_INT(d_some, "%d", "0a", int)

// Тесты для %i:
TEST_SSCANF_INT(i_zero, "%i", "0", int)
TEST_SSCANF_INT(i_pos, "%i", "123", int)
TEST_SSCANF_INT(i_neg, "%i", "-123", int)
TEST_SSCANF_INT(i_octal, "%i", "0123", int)
TEST_SSCANF_INT(i_hex, "%i", "0x123", int)
TEST_SSCANF_INT(i_hex_, "%i", "ffffffffff", int)

// Тесты для %o:
TEST_SSCANF_UINT(o_zero, "%o", "0", unsigned int)
TEST_SSCANF_UINT(o_pos, "%o", "123", unsigned int)
TEST_SSCANF_UINT(o_octal, "%o", "0123", unsigned int)
TEST_SSCANF_UINT(o_hex, "%o", "0x123", unsigned int)
TEST_SSCANF_UINT(o_hex_, "%o", "ffffffffff", unsigned int)

// Тесты для %x:
TEST_SSCANF_UINT(x_zero, "%x", "0", unsigned int)
TEST_SSCANF_UINT(x_pos, "%x", "123", unsigned int)
TEST_SSCANF_UINT(x_octal, "%x", "0123", unsigned int)
TEST_SSCANF_UINT(x_hex, "%x", "0x123", unsigned int)
TEST_SSCANF_UINT(x_hex_, "%x", "ffffffffff", unsigned int)

// Тесты для %X:
TEST_SSCANF_UINT(X_zero, "%X", "0", unsigned int)
TEST_SSCANF_UINT(X_pos, "%X", "123", unsigned int)
TEST_SSCANF_UINT(X_octal, "%X", "0123", unsigned int)
TEST_SSCANF_UINT(X_hex, "%X", "0x123", unsigned int)
TEST_SSCANF_UINT(X_hex_, "%X", "ffffffffff", unsigned int)

// Тесты для %u:
TEST_SSCANF_UINT(u_zero, "%u", "0", unsigned int)
TEST_SSCANF_UINT(u_pos, "%u", "123", unsigned int)
TEST_SSCANF_UINT(u_octal, "%u", "0123", unsigned int)
TEST_SSCANF_UINT(u_hex, "%u", "0x123", unsigned int)
TEST_SSCANF_UINT(u_hex_, "%u", "ffffffffff", unsigned int)

// Тесты для %d с разными длинами
TEST_SSCANF_INT(test_sscanf_hd, "%hd", "12345", short)
TEST_SSCANF_INT(test_sscanf_ld, "%ld", "123456789", long)
TEST_SSCANF_INT(test_sscanf_lld, "%lld", "123456789012", long long)

TEST_SSCANF_INT(test_sscanf_hd_, "%hd", "1a3", short)
TEST_SSCANF_INT(test_sscanf_ld_, "%ld", "1a3b5c7", long)
TEST_SSCANF_INT(test_sscanf_lld_, "%lld", "1a3b5c7d9", long long)

// Тесты для %i с разными длинами:
TEST_SSCANF_INT(test_sscanf_hi, "%hi", "12345", short)
TEST_SSCANF_INT(test_sscanf_li, "%li", "123456789", long)
TEST_SSCANF_INT(test_sscanf_lli, "%lli", "123456789012", long long)

TEST_SSCANF_INT(test_sscanf_hi_, "%hi", "1a3", short)
TEST_SSCANF_INT(test_sscanf_li_, "%li", "1a3b5c7", long)
TEST_SSCANF_INT(test_sscanf_lli_, "%lli", "1a3b5c7d9", long long)

// Тесты для %o с разными длинами:
TEST_SSCANF_UINT(test_sscanf_ho, "%ho", "12345", unsigned short)
TEST_SSCANF_UINT(test_sscanf_lo, "%lo", "123456789", unsigned long)
TEST_SSCANF_UINT(test_sscanf_llo, "%llo", "123456789012", unsigned long long)

TEST_SSCANF_UINT(test_sscanf_ho_, "%ho", "1a3", unsigned short)
TEST_SSCANF_UINT(test_sscanf_lo_, "%lo", "1a3b5c7", unsigned long)
TEST_SSCANF_UINT(test_sscanf_llo_, "%llo", "1a3b5c7d9", unsigned long long)

// Тесты для %x с разными длинами:
TEST_SSCANF_UINT(test_sscanf_hx, "%hx", "12345", unsigned short)
TEST_SSCANF_UINT(test_sscanf_lx, "%lx", "123456789", unsigned long)
TEST_SSCANF_UINT(test_sscanf_llx, "%llx", "123456789012", unsigned long long)

TEST_SSCANF_UINT(test_sscanf_hx_, "%hx", "1a3", unsigned short)
TEST_SSCANF_UINT(test_sscanf_lx_, "%lx", "1a3b5c7", unsigned long)
TEST_SSCANF_UINT(test_sscanf_llx_, "%llx", "1a3b5c7d9", unsigned long long)

// Тесты для %X с разными длинами:
TEST_SSCANF_UINT(test_sscanf_hX, "%hX", "12345", unsigned short)
TEST_SSCANF_UINT(test_sscanf_lX, "%lX", "123456789", unsigned long)
TEST_SSCANF_UINT(test_sscanf_llX, "%llX", "123456789012", unsigned long long)

TEST_SSCANF_UINT(test_sscanf_hX_, "%hX", "1a3", unsigned short)
TEST_SSCANF_UINT(test_sscanf_lX_, "%lX", "1a3b5c7", unsigned long)
TEST_SSCANF_UINT(test_sscanf_llX_, "%llX", "1a3b5c7d9", unsigned long long)

// Тесты для %u с разными длинами:
TEST_SSCANF_UINT(test_sscanf_hu, "%hu", "12345", unsigned short)
TEST_SSCANF_UINT(test_sscanf_lu, "%lu", "123456789", unsigned long)
TEST_SSCANF_UINT(test_sscanf_llu, "%llu", "123456789012", unsigned long long)

TEST_SSCANF_UINT(test_sscanf_hu_, "%hu", "1a3", unsigned short)
TEST_SSCANF_UINT(test_sscanf_lu_, "%lu", "1a3b5c7", unsigned long)
TEST_SSCANF_UINT(test_sscanf_llu_, "%llu", "1a3b5c7d9", unsigned long long)

// Тесты для %f
TEST_SSCANF_FLOAT(f_max, "%f", "3.402823e+38", float)
TEST_SSCANF_FLOAT(f_min, "%f", "1.175494e-38", float)
TEST_SSCANF_FLOAT(lf_min, "%lf", "2.2250738585072014e-308", double)
TEST_SSCANF_FLOAT(f_inf, "%f", "inf", float)
TEST_SSCANF_FLOAT(f_minus_inf, "%f", "-inf", float)
TEST_SSCANF_FLOAT(f_nan, "%f", "nan", float)

// Тесты для %e:
TEST_SSCANF_FLOAT(e_max, "%e", "3.402823e+38", float)
TEST_SSCANF_FLOAT(e_min, "%e", "1.175494e-38", float)
TEST_SSCANF_FLOAT(le_min, "%le", "2.2250738585072014e-308", double)
TEST_SSCANF_FLOAT(e_inf, "%e", "inf", float)
TEST_SSCANF_FLOAT(e_minus_inf, "%e", "-inf", float)
TEST_SSCANF_FLOAT(e_nan, "%e", "nan", float)

// Тесты для %E:
TEST_SSCANF_FLOAT(E_max, "%E", "3.402823e+38", float)
TEST_SSCANF_FLOAT(E_min, "%E", "1.175494e-38", float)
TEST_SSCANF_FLOAT(lE_min, "%lE", "2.2250738585072014e-308", double)
TEST_SSCANF_FLOAT(E_inf, "%E", "inf", float)
TEST_SSCANF_FLOAT(E_minus_inf, "%E", "-inf", float)
TEST_SSCANF_FLOAT(E_nan, "%E", "nan", float)

// Тесты для %g:
TEST_SSCANF_FLOAT(g_max, "%g", "3.402823e+38", float)
TEST_SSCANF_FLOAT(g_min, "%g", "1.175494e-38", float)
TEST_SSCANF_FLOAT(lg_min, "%lg", "2.2250738585072014e-308", double)
TEST_SSCANF_FLOAT(g_inf, "%g", "inf", float)
TEST_SSCANF_FLOAT(g_minus_inf, "%g", "-inf", float)
TEST_SSCANF_FLOAT(g_nan, "%g", "nan", float)

// Тесты для %G:
TEST_SSCANF_FLOAT(G_max, "%G", "3.402823e+38", float)
TEST_SSCANF_FLOAT(G_min, "%G", "1.175494e-38", float)
TEST_SSCANF_FLOAT(lG_min, "%lG", "2.2250738585072014e-308", double)
TEST_SSCANF_FLOAT(G_inf, "%G", "inf", float)
TEST_SSCANF_FLOAT(G_minus_inf, "%G", "-inf", float)
TEST_SSCANF_FLOAT(G_nan, "%G", "nan", float)

// Тесты для %f с разными длинами
TEST_SSCANF_FLOAT(test_sscanf_f, "%f", "1.23e4", float)
TEST_SSCANF_FLOAT(test_sscanf_lf, "%lf", "123.456", double)
TEST_SSCANF_FLOAT(test_sscanf_Lf, "%Lf", "123.456789", long double)

// Тесты для %e с разными длинами:
TEST_SSCANF_FLOAT(test_sscanf_e, "%e", "1.23e4", float)
TEST_SSCANF_FLOAT(test_sscanf_le, "%le", "123.456", double)
TEST_SSCANF_FLOAT(test_sscanf_Le, "%Le", "123.456789", long double)

// Тесты для %E с разными длинами:
TEST_SSCANF_FLOAT(test_sscanf_E, "%E", "1.23e4", float)
TEST_SSCANF_FLOAT(test_sscanf_lE, "%lE", "123.456", double)
TEST_SSCANF_FLOAT(test_sscanf_LE, "%LE", "123.456789", long double)

// Тесты для %g с разными длинами:
TEST_SSCANF_FLOAT(test_sscanf_g, "%g", "1.23e4", float)
TEST_SSCANF_FLOAT(test_sscanf_lg, "%lg", "123.456", double)
TEST_SSCANF_FLOAT(test_sscanf_Lg, "%Lg", "123.456789", long double)

// Тесты для %G с разными длинами:
TEST_SSCANF_FLOAT(test_sscanf_G, "%G", "1.23e4", float)
TEST_SSCANF_FLOAT(test_sscanf_lG, "%lG", "123.456", double)
TEST_SSCANF_FLOAT(test_sscanf_LG, "%LG", "123.456789", long double)

// Тесты с шириной
TEST_SSCANF_INT_WIDTH(test_sscanf_d_width, "%5d", "1234567", int)
TEST_SSCANF_STR_WIDTH(test_sscanf_s_width, "%5s", "hello world")
TEST_SSCANF_INT_WIDTH(test_sscanf_d_width_, "12345%5d", "1234567", int)
TEST_SSCANF_STR_WIDTH(test_sscanf_s_width_, "hello%5s", "hello world")

START_TEST(test_sscanf_c_width) {
  char char1_std[4] = {0};  // Буфер для 3 символов + нулевой терминатор
  char char1_s21[4] = {0};
  int res_std = sscanf("abcd", "%3c", char1_std);
  int res_s21 = s21_sscanf("abcd", "%3c", char1_s21);
  ck_assert_str_eq(char1_std, char1_s21);
  ck_assert_int_eq(res_std, res_s21);
}
END_TEST

START_TEST(test_sscanf_c_width_) {
  char char1_std[4] = {0};
  char char1_s21[4] = {0};
  int res_std = sscanf("abcd", "ab%3c", char1_std);
  int res_s21 = s21_sscanf("abcd", "ab%3c", char1_s21);
  ck_assert_str_eq(char1_std, char1_s21);
  ck_assert_int_eq(res_std, res_s21);
}
END_TEST

// Неполные совпадения и прекращение чтения
START_TEST(partial_match1) {
  int a_std = 0, a_s21 = 0;
  char b_std[100] = {0}, b_s21[100] = {0};
  int c_std = 0, c_s21 = 0;
  const char *input = "123 abc 456";

  int res_std = sscanf(input, "%d %s %d", &a_std, b_std, &c_std);
  int res_s21 = s21_sscanf(input, "%d %s %d", &a_s21, b_s21, &c_s21);

  ck_assert_int_eq(res_std, res_s21);
  if (res_std >= 1) ck_assert_int_eq(a_std, a_s21);
  if (res_std >= 2) ck_assert_str_eq(b_std, b_s21);
  if (res_std >= 3) ck_assert_int_eq(c_std, c_s21);
}
END_TEST

START_TEST(partial_match2) {
  float a_std = 0, a_s21 = 0;
  char b_std[100] = {0}, b_s21[100] = {0};
  int c_std = 0, c_s21 = 0;
  const char *input = "123.45 abc";

  int res_std = sscanf(input, "%f %s %d", &a_std, b_std, &c_std);
  int res_s21 = s21_sscanf(input, "%f %s %d", &a_s21, b_s21, &c_s21);

  ck_assert_int_eq(res_std, res_s21);
  if (res_std >= 1) ck_assert_float_eq(a_std, a_s21);
  if (res_std >= 2) ck_assert_str_eq(b_std, b_s21);
  if (res_std >= 3) ck_assert_int_eq(c_std, c_s21);
}
END_TEST

START_TEST(partial_match3) {
  char a_std[100] = {0}, a_s21[100] = {0};
  int b_std = 0, b_s21 = 0;
  float c_std = 0, c_s21 = 0;
  const char *input = "hello 123";

  int res_std = sscanf(input, "%s %d %f", a_std, &b_std, &c_std);
  int res_s21 = s21_sscanf(input, "%s %d %f", a_s21, &b_s21, &c_s21);

  ck_assert_int_eq(res_std, res_s21);
  if (res_std >= 1) ck_assert_str_eq(a_std, a_s21);
  if (res_std >= 2) ck_assert_int_eq(b_std, b_s21);
  if (res_std >= 3) ck_assert_float_eq(c_std, c_s21);
}
END_TEST

TEST_SSCANF_INT(empty_string, "%d", "", int)
TEST_SSCANF_INT(whitespace_only, "%d", "   ", int)
TEST_SSCANF_INT(whitespace_before, "%d", "   123", int)
TEST_SSCANF_INT(whitespace_after, "%d", "123   ", int)

TEST_SSCANF_INT(no_integer, "%d", "abc", int)
TEST_SSCANF_FLOAT(no_float, "%f", "abc", float)
TEST_SSCANF_STR(no_string, "%s", "")

// Тесты на пробельные символы
START_TEST(test_sscanf_whitespace) {
  int a_std = 0, b_std = 0;
  int a_s21 = 0, b_s21 = 0;
  const char *input = "   123  456  ";
  int res_std = sscanf(input, "%d %d", &a_std, &b_std);
  int res_s21 = s21_sscanf(input, "%d %d", &a_s21, &b_s21);
  ck_assert_int_eq(a_std, a_s21);
  ck_assert_int_eq(b_std, b_s21);
  ck_assert_int_eq(res_std, res_s21);
}
END_TEST

START_TEST(test_sscanf_whitespace_format) {
  int a_std = 0, b_std = 0;
  int a_s21 = 0, b_s21 = 0;
  const char *input = "123\n\t456";
  int res_std = sscanf(input, "%d %d", &a_std, &b_std);
  int res_s21 = s21_sscanf(input, "%d %d", &a_s21, &b_s21);
  ck_assert_int_eq(a_std, a_s21);
  ck_assert_int_eq(b_std, b_s21);
  ck_assert_int_eq(res_std, res_s21);
}
END_TEST

// Тесты для %s
TEST_SSCANF_STR(test_sscanf_s, "%s", "hello world")
START_TEST(test_sscanf_percent_s_basic) {
  char input[] = "Hello World";
  char std_str1[20] = {0};
  char std_str2[20] = {0};
  char s21_str1[20] = {0};
  char s21_str2[20] = {0};

  int std_ret = sscanf(input, "%s %s", std_str1, std_str2);
  int s21_ret = s21_sscanf(input, "%s %s", s21_str1, s21_str2);

  ck_assert_int_eq(std_ret, s21_ret);
  ck_assert_str_eq(std_str1, s21_str1);
  ck_assert_str_eq(std_str2, s21_str2);
}
END_TEST

START_TEST(test_sscanf_percent_s_with_length) {
  char input[] = "Hello World";
  char std_str1[20] = {0};
  char std_str2[20] = {0};
  char s21_str1[20] = {0};
  char s21_str2[20] = {0};

  int std_ret = sscanf(input, "%5s %3s", std_str1, std_str2);
  int s21_ret = s21_sscanf(input, "%5s %3s", s21_str1, s21_str2);

  ck_assert_int_eq(std_ret, s21_ret);
  ck_assert_str_eq(std_str1, s21_str1);
  ck_assert_str_eq(std_str2, s21_str2);
}
END_TEST

START_TEST(test_sscanf_percent_s_with_asterisk) {
  char input[] = "Hello World";
  char std_str[20] = {0};
  char s21_str[20] = {0};

  int std_ret = sscanf(input, "%*s %s", std_str);
  int s21_ret = s21_sscanf(input, "%*s %s", s21_str);

  ck_assert_int_eq(std_ret, s21_ret);
  ck_assert_str_eq(std_str, s21_str);
}
END_TEST

START_TEST(test_sscanf_percent_s_multiple_spaces) {
  char input[] = "Hello    World";
  char std_str1[20] = {0};
  char std_str2[20] = {0};
  char s21_str1[20] = {0};
  char s21_str2[20] = {0};

  int std_ret = sscanf(input, "%s %s", std_str1, std_str2);
  int s21_ret = s21_sscanf(input, "%s %s", s21_str1, s21_str2);

  ck_assert_int_eq(std_ret, s21_ret);
  ck_assert_str_eq(std_str1, s21_str1);
  ck_assert_str_eq(std_str2, s21_str2);
}
END_TEST

START_TEST(test_sscanf_percent_s_empty_string) {
  char input[] = "";
  char std_str[20] = {0};
  char s21_str[20] = {0};

  int std_ret = sscanf(input, "%s", std_str);
  int s21_ret = s21_sscanf(input, "%s", s21_str);

  ck_assert_int_eq(std_ret, s21_ret);
  ck_assert_str_eq(std_str, s21_str);
}
END_TEST

START_TEST(test_sscanf_percent_s_only_spaces) {
  char input[] = "   ";
  char std_str[20] = {0};
  char s21_str[20] = {0};

  int std_ret = sscanf(input, "%s", std_str);
  int s21_ret = s21_sscanf(input, "%s", s21_str);

  ck_assert_int_eq(std_ret, s21_ret);
  ck_assert_str_eq(std_str, s21_str);
}
END_TEST

START_TEST(test_sscanf_percent_s_mixed_format) {
  char input[] = "Hello 123 World";
  char std_str1[20] = {0};
  char std_str2[20] = {0};
  int std_num = 0;
  char s21_str1[20] = {0};
  char s21_str2[20] = {0};
  int s21_num = 0;

  int std_ret = sscanf(input, "%s %d %s", std_str1, &std_num, std_str2);
  int s21_ret = s21_sscanf(input, "%s %d %s", s21_str1, &s21_num, s21_str2);

  ck_assert_int_eq(std_ret, s21_ret);
  ck_assert_str_eq(std_str1, s21_str1);
  ck_assert_int_eq(std_num, s21_num);
  ck_assert_str_eq(std_str2, s21_str2);
}
END_TEST

// Тесты для %c
TEST_SSCANF_CHAR(test_sscanf_c, "%c", "a")

START_TEST(test_sscanf_percent_c) {
  char input[] = "12345";
  char std_name[10] = {0};
  char s21_name[10] = {0};
  char std_job[10] = {0};
  char s21_job[10] = {0};

  int std_ret = sscanf(input, "%2c %*c %c", std_name, std_job);
  int s21_ret = s21_sscanf(input, "%2c %*c %c", s21_name, s21_job);

  ck_assert_int_eq(std_ret, s21_ret);
  ck_assert_mem_eq(std_name, s21_name, 10);
  ck_assert_mem_eq(std_job, s21_job, 10);
}
END_TEST

START_TEST(test_sscanf_percent_c_long) {
  char input[] = "12345";
  char std_name[10] = {0};
  char s21_name[10] = {0};
  char std_job[10] = {0};
  char s21_job[10] = {0};

  int std_ret = sscanf(input, "%7c %c", std_name, std_job);
  int s21_ret = s21_sscanf(input, "%7c %c", s21_name, s21_job);

  ck_assert_int_eq(std_ret, s21_ret);
  ck_assert_mem_eq(std_name, s21_name, 10);
  ck_assert_mem_eq(std_job, s21_job, 10);
}
END_TEST

START_TEST(test_sscanf_percent_c_short) {
  char input[] = "12345";
  char std_name[10] = {0};
  char s21_name[10] = {0};
  char std_job[10] = {0};
  char s21_job[10] = {0};

  int std_ret = sscanf(input, "%2c %c", std_name, std_job);
  int s21_ret = s21_sscanf(input, "%2c %c", s21_name, s21_job);

  ck_assert_int_eq(std_ret, s21_ret);
  ck_assert_mem_eq(std_name, s21_name, 10);
  ck_assert_mem_eq(std_job, s21_job, 10);
}
END_TEST

START_TEST(test_sscanf_percent_c_with_spaces) {
  char input[] = "1 2345";
  char std_name[10] = {0};
  char s21_name[10] = {0};
  char std_job[10] = {0};
  char s21_job[10] = {0};

  int std_ret = sscanf(input, "%5c %c", std_name, std_job);
  int s21_ret = s21_sscanf(input, "%5c %c", s21_name, s21_job);

  ck_assert_int_eq(std_ret, s21_ret);
  ck_assert_mem_eq(std_name, s21_name, 10);
  ck_assert_mem_eq(std_job, s21_job, 10);
}
END_TEST

START_TEST(test_sscanf_percent_c_multiple_spaces) {
  char input[] = "1     2345";
  char std_name[10] = {0};
  char s21_name[10] = {0};
  char std_job[10] = {0};
  char s21_job[10] = {0};

  int std_ret = sscanf(input, "%5c %c", std_name, std_job);
  int s21_ret = s21_sscanf(input, "%5c %c", s21_name, s21_job);

  ck_assert_int_eq(std_ret, s21_ret);
  ck_assert_mem_eq(std_name, s21_name, 10);
  ck_assert_mem_eq(std_job, s21_job, 10);
}
END_TEST

START_TEST(test_sscanf_percent_c_single_char) {
  char input[] = "1";
  char std_name[10] = {0};
  char s21_name[10] = {0};
  char std_job[10] = {0};
  char s21_job[10] = {0};

  int std_ret = sscanf(input, "%c %c", std_name, std_job);
  int s21_ret = s21_sscanf(input, "%c %c", s21_name, s21_job);

  ck_assert_int_eq(std_ret, s21_ret);
  ck_assert_mem_eq(std_name, s21_name, 10);
  ck_assert_mem_eq(std_job, s21_job, 10);
}
END_TEST

START_TEST(test_sscanf_percent_c_space_only) {
  char input[] = " ";
  char std_name[10] = {0};
  char s21_name[10] = {0};
  char std_job[10] = {0};
  char s21_job[10] = {0};

  int std_ret = sscanf(input, "%c %c", std_name, std_job);
  int s21_ret = s21_sscanf(input, "%c %c", s21_name, s21_job);

  ck_assert_int_eq(std_ret, s21_ret);
  ck_assert_mem_eq(std_name, s21_name, 10);
  ck_assert_mem_eq(std_job, s21_job, 10);
}
END_TEST

START_TEST(test_sscanf_percent_c_empty_string) {
  char input[] = "";
  char std_name[10] = {0};
  char s21_name[10] = {0};
  char std_job[10] = {0};
  char s21_job[10] = {0};

  int std_ret = sscanf(input, "%5c %c", std_name, std_job);
  int s21_ret = s21_sscanf(input, "%5c %c", s21_name, s21_job);

  ck_assert_int_eq(std_ret, s21_ret);
  ck_assert_mem_eq(std_name, s21_name, 10);
  ck_assert_mem_eq(std_job, s21_job, 10);
}
END_TEST

// Тесты для %n
TEST_SSCANF_N(test_sscanf_n, "hello", "hello%n")

// Тесты для %%
TEST_SSCANF_PERCENT(test_sscanf_percent, "%", "%%")

// Тесты для %p
TEST_SSCANF_PTR(test_sscanf_p, "%p", "0x1234")

// Тесты на спецификатор %n
START_TEST(test_sscanf_n_multiple) {
  int n1_std = 0, n2_std = 0;
  int n1_s21 = 0, n2_s21 = 0;
  int a_std = 0, a_s21 = 0;
  const char *input = "123 abc";

  int res_std = sscanf(input, "%d%n abc%n", &a_std, &n1_std, &n2_std);
  int res_s21 = s21_sscanf(input, "%d%n abc%n", &a_s21, &n1_s21, &n2_s21);

  ck_assert_int_eq(res_std, res_s21);
  ck_assert_int_eq(a_std, a_s21);
  ck_assert_int_eq(n1_std, n1_s21);
  ck_assert_int_eq(n2_std, n2_s21);
}
END_TEST

// Тесты с разными локалями
START_TEST(test_sscanf_locale_decimal) {
  setlocale(LC_NUMERIC, "de_DE.UTF-8");
  float f_std = 0, f_s21 = 0;
  const char *input = "123,456";

  int res_std = sscanf(input, "%f", &f_std);
  int res_s21 = s21_sscanf(input, "%f", &f_s21);

  setlocale(LC_NUMERIC, "C");
  ck_assert_int_eq(res_std, res_s21);
  // Note: поведение может отличаться в зависимости от реализации
}
END_TEST

// Тесты на переполнение буфера
START_TEST(test_sscanf_buffer_overflow) {
  char buf_std[5] = {0};
  char buf_s21[5] = {0};
  const char *input = "abcdefghij";

  int res_std = sscanf(input, "%4s", buf_std);
  int res_s21 = s21_sscanf(input, "%4s", buf_s21);

  ck_assert_int_eq(res_std, res_s21);
  ck_assert_str_eq(buf_std, buf_s21);
}
END_TEST

// Тесты на производительность и большие данные
START_TEST(test_sscanf_large_number) {
  long long ll_std = 0, ll_s21 = 0;
  const char *input = "12345678901234567890";

  int res_std = sscanf(input, "%lld", &ll_std);
  int res_s21 = s21_sscanf(input, "%lld", &ll_s21);

  ck_assert_int_eq(res_std, res_s21);
  ck_assert_int_eq(ll_std, ll_s21);
}
END_TEST

START_TEST(test_sscanf_long_string) {
  char buf_std[100] = {0};
  char buf_s21[100] = {0};
  char long_input[1000];

  // Создаем очень длинную строку
  memset(long_input, 'a', sizeof(long_input) - 1);
  long_input[sizeof(long_input) - 1] = '\0';

  int res_std = sscanf(long_input, "%99s", buf_std);
  int res_s21 = s21_sscanf(long_input, "%99s", buf_s21);

  ck_assert_int_eq(res_std, res_s21);
  ck_assert_str_eq(buf_std, buf_s21);
}
END_TEST

// Тесты с бинарными данными
START_TEST(test_sscanf_binary_data) {
  char data[] = {0x48, 0x65, 0x6C, 0x6C, 0x6F, 0x00,
                 0x57, 0x6F, 0x72, 0x6C, 0x64};
  char buf1_std[20] = {0}, buf2_std[20] = {0};
  char buf1_s21[20] = {0}, buf2_s21[20] = {0};

  int res_std = sscanf(data, "%5s %5s", buf1_std, buf2_std);
  int res_s21 = s21_sscanf(data, "%5s %5s", buf1_s21, buf2_s21);

  ck_assert_int_eq(res_std, res_s21);
  ck_assert_str_eq(buf1_std, buf1_s21);
  if (res_std > 1) ck_assert_str_eq(buf2_std, buf2_s21);
}
END_TEST

// Проверка обработки ошибок
START_TEST(test_sscanf_overflow) {
  short s_std = 0, s_s21 = 0;
  const char *input = "1000000";  // Слишком большое для short

  int res_std = sscanf(input, "%hd", &s_std);
  int res_s21 = s21_sscanf(input, "%hd", &s_s21);

  ck_assert_int_eq(res_std, res_s21);
  // Поведение при переполнении может различаться
}
END_TEST

// Дополнительные тесты для %p
START_TEST(test_sscanf_p_null) {
  void *p_std = NULL, *p_s21 = NULL;
  const char *input = "(nil)";

  int res_std = sscanf(input, "%p", &p_std);
  int res_s21 = s21_sscanf(input, "%p", &p_s21);

  ck_assert_int_eq(res_std, res_s21);
  ck_assert_ptr_eq(p_std, p_s21);
}
END_TEST

START_TEST(test_sscanf_p_large) {
  void *p_std = NULL, *p_s21 = NULL;
  const char *input = "0xFFFFFFFFFFFFFFFF";

  int res_std = sscanf(input, "%p", &p_std);
  int res_s21 = s21_sscanf(input, "%p", &p_s21);

  ck_assert_int_eq(res_std, res_s21);
  ck_assert_ptr_eq(p_std, p_s21);
}
END_TEST

// Тесты для %n с разными позициями
START_TEST(test_sscanf_n_beginning) {
  int n_std = 0, n_s21 = 0;
  int a_std = 0, a_s21 = 0;
  const char *input = "123";

  int res_std = sscanf(input, "%n%d", &n_std, &a_std);
  int res_s21 = s21_sscanf(input, "%n%d", &n_s21, &a_s21);

  ck_assert_int_eq(res_std, res_s21);
  ck_assert_int_eq(a_std, a_s21);
  ck_assert_int_eq(n_std, n_s21);
}
END_TEST

START_TEST(test_sscanf_n_middle) {
  int n1_std = 0, n2_std = 0;
  int n1_s21 = 0, n2_s21 = 0;
  int a_std = 0, b_std = 0;
  int a_s21 = 0, b_s21 = 0;
  const char *input = "123 456";

  int res_std = sscanf(input, "%d%n %d%n", &a_std, &n1_std, &b_std, &n2_std);
  int res_s21 =
      s21_sscanf(input, "%d%n %d%n", &a_s21, &n1_s21, &b_s21, &n2_s21);

  ck_assert_int_eq(res_std, res_s21);
  ck_assert_int_eq(a_std, a_s21);
  ck_assert_int_eq(b_std, b_s21);
  ck_assert_int_eq(n1_std, n1_s21);
  ck_assert_int_eq(n2_std, n2_s21);
}
END_TEST

// Тесты для %%
START_TEST(test_sscanf_double_percent) {
  const char *input = "%%";
  int res_std = sscanf(input, "%%%%");
  int res_s21 = s21_sscanf(input, "%%%%");
  ck_assert_int_eq(res_std, res_s21);
}
END_TEST

START_TEST(test_sscanf_percent_with_text) {
  const char *input = "50% discount";
  int percent_std = 0, percent_s21 = 0;
  char text_std[20] = {0}, text_s21[20] = {0};

  int res_std = sscanf(input, "%d%% %s", &percent_std, text_std);
  int res_s21 = s21_sscanf(input, "%d%% %s", &percent_s21, text_s21);

  ck_assert_int_eq(res_std, res_s21);
  ck_assert_int_eq(percent_std, percent_s21);
  ck_assert_str_eq(text_std, text_s21);
}
END_TEST

// Тесты с очень длинными строками формата
START_TEST(test_long_format_string) {
  int a1_std = 0, a2_std = 0, a3_std = 0, a4_std = 0;
  int a1_s21 = 0, a2_s21 = 0, a3_s21 = 0, a4_s21 = 0;
  const char *input = "1 2 3 4";
  const char *format = "%d %d %d %d";

  int res_std = sscanf(input, format, &a1_std, &a2_std, &a3_std, &a4_std);
  int res_s21 = s21_sscanf(input, format, &a1_s21, &a2_s21, &a3_s21, &a4_s21);

  ck_assert_int_eq(res_std, res_s21);
  ck_assert_int_eq(a1_std, a1_s21);
  ck_assert_int_eq(a2_std, a2_s21);
  ck_assert_int_eq(a3_std, a3_s21);
  ck_assert_int_eq(a4_std, a4_s21);
}
END_TEST

// =========================================================================
// СЮИТЫ
// =========================================================================
#pragma region

Suite *sscanf_suite(void) {
  Suite *s = suite_create("s21_sscanf");

  // Граничные значения
  TCase *tc_bounds = tcase_create("Bounds");
  tcase_add_test(tc_bounds, test_int_min);
  tcase_add_test(tc_bounds, test_int_max);
  tcase_add_test(tc_bounds, test_uint_max);
  tcase_add_test(tc_bounds, test_long_min);
  tcase_add_test(tc_bounds, test_long_max);
  tcase_add_test(tc_bounds, test_ulong_max);
  tcase_add_test(tc_bounds, test_llong_min);
  tcase_add_test(tc_bounds, test_llong_max);
  tcase_add_test(tc_bounds, test_ullong_max);
  suite_add_tcase(s, tc_bounds);

  // %d
  TCase *tc_d = tcase_create("%d");
  tcase_add_test(tc_d, d_zero);
  tcase_add_test(tc_d, d_pos);
  tcase_add_test(tc_d, d_neg);
  tcase_add_test(tc_d, d_octal);
  tcase_add_test(tc_d, d_hex);
  tcase_add_test(tc_d, d_hex_);
  tcase_add_test(tc_d, d_some);
  suite_add_tcase(s, tc_d);

  // %i
  TCase *tc_i = tcase_create("%i");
  tcase_add_test(tc_i, i_zero);
  tcase_add_test(tc_i, i_pos);
  tcase_add_test(tc_i, i_neg);
  tcase_add_test(tc_i, i_octal);
  tcase_add_test(tc_i, i_hex);
  tcase_add_test(tc_i, i_hex_);
  suite_add_tcase(s, tc_i);

  // %o
  TCase *tc_o = tcase_create("%o");
  tcase_add_test(tc_o, o_zero);
  tcase_add_test(tc_o, o_pos);
  tcase_add_test(tc_o, o_octal);
  tcase_add_test(tc_o, o_hex);
  tcase_add_test(tc_o, o_hex_);
  suite_add_tcase(s, tc_o);

  // %x
  TCase *tc_x = tcase_create("%x");
  tcase_add_test(tc_x, x_zero);
  tcase_add_test(tc_x, x_pos);
  tcase_add_test(tc_x, x_octal);
  tcase_add_test(tc_x, x_hex);
  tcase_add_test(tc_x, x_hex_);
  suite_add_tcase(s, tc_x);

  // %X
  TCase *tc_X = tcase_create("%X");
  tcase_add_test(tc_X, X_zero);
  tcase_add_test(tc_X, X_pos);
  tcase_add_test(tc_X, X_octal);
  tcase_add_test(tc_X, X_hex);
  tcase_add_test(tc_X, X_hex_);
  suite_add_tcase(s, tc_X);

  // %u
  TCase *tc_u = tcase_create("%u");
  tcase_add_test(tc_u, u_zero);
  tcase_add_test(tc_u, u_pos);
  tcase_add_test(tc_u, u_octal);
  tcase_add_test(tc_u, u_hex);
  tcase_add_test(tc_u, u_hex_);
  suite_add_tcase(s, tc_u);

  // %d с разными длинами
  TCase *tc_d_length = tcase_create("%d_length");
  tcase_add_test(tc_d_length, test_sscanf_hd);
  tcase_add_test(tc_d_length, test_sscanf_ld);
  tcase_add_test(tc_d_length, test_sscanf_lld);
  tcase_add_test(tc_d_length, test_sscanf_hd_);
  tcase_add_test(tc_d_length, test_sscanf_ld_);
  tcase_add_test(tc_d_length, test_sscanf_lld_);
  suite_add_tcase(s, tc_d_length);

  // %i с разными длинами
  TCase *tc_i_length = tcase_create("%i_length");
  tcase_add_test(tc_i_length, test_sscanf_hi);
  tcase_add_test(tc_i_length, test_sscanf_li);
  tcase_add_test(tc_i_length, test_sscanf_lli);
  tcase_add_test(tc_i_length, test_sscanf_hi_);
  tcase_add_test(tc_i_length, test_sscanf_li_);
  tcase_add_test(tc_i_length, test_sscanf_lli_);
  suite_add_tcase(s, tc_i_length);

  // %o с разными длинами
  TCase *tc_o_length = tcase_create("%o_length");
  tcase_add_test(tc_o_length, test_sscanf_ho);
  tcase_add_test(tc_o_length, test_sscanf_lo);
  tcase_add_test(tc_o_length, test_sscanf_llo);
  tcase_add_test(tc_o_length, test_sscanf_ho_);
  tcase_add_test(tc_o_length, test_sscanf_lo_);
  tcase_add_test(tc_o_length, test_sscanf_llo_);
  suite_add_tcase(s, tc_o_length);

  // %x с разными длинами
  TCase *tc_x_length = tcase_create("%x_length");
  tcase_add_test(tc_x_length, test_sscanf_hx);
  tcase_add_test(tc_x_length, test_sscanf_lx);
  tcase_add_test(tc_x_length, test_sscanf_llx);
  tcase_add_test(tc_x_length, test_sscanf_hx_);
  tcase_add_test(tc_x_length, test_sscanf_lx_);
  tcase_add_test(tc_x_length, test_sscanf_llx_);
  suite_add_tcase(s, tc_x_length);

  // %X с разными длинами
  TCase *tc_X_length = tcase_create("%X_length");
  tcase_add_test(tc_X_length, test_sscanf_hX);
  tcase_add_test(tc_X_length, test_sscanf_lX);
  tcase_add_test(tc_X_length, test_sscanf_llX);
  tcase_add_test(tc_X_length, test_sscanf_hX_);
  tcase_add_test(tc_X_length, test_sscanf_lX_);
  tcase_add_test(tc_X_length, test_sscanf_llX_);
  suite_add_tcase(s, tc_X_length);

  // %u с разными длинами
  TCase *tc_u_length = tcase_create("%u_length");
  tcase_add_test(tc_u_length, test_sscanf_hu);
  tcase_add_test(tc_u_length, test_sscanf_lu);
  tcase_add_test(tc_u_length, test_sscanf_llu);
  tcase_add_test(tc_u_length, test_sscanf_hu_);
  tcase_add_test(tc_u_length, test_sscanf_lu_);
  tcase_add_test(tc_u_length, test_sscanf_llu_);
  suite_add_tcase(s, tc_u_length);

  // %f
  TCase *tc_f = tcase_create("%f");
  tcase_add_test(tc_f, f_max);
  tcase_add_test(tc_f, f_min);
  tcase_add_test(tc_f, lf_min);
  tcase_add_test(tc_f, f_inf);
  tcase_add_test(tc_f, f_minus_inf);
  tcase_add_test(tc_f, f_nan);
  suite_add_tcase(s, tc_f);

  // %e
  TCase *tc_e = tcase_create("%e");
  tcase_add_test(tc_e, e_max);
  tcase_add_test(tc_e, e_min);
  tcase_add_test(tc_e, le_min);
  tcase_add_test(tc_e, e_inf);
  tcase_add_test(tc_e, e_minus_inf);
  tcase_add_test(tc_e, e_nan);
  suite_add_tcase(s, tc_e);

  // %E
  TCase *tc_E = tcase_create("%E");
  tcase_add_test(tc_E, E_max);
  tcase_add_test(tc_E, E_min);
  tcase_add_test(tc_E, lE_min);
  tcase_add_test(tc_E, E_inf);
  tcase_add_test(tc_E, E_minus_inf);
  tcase_add_test(tc_E, E_nan);
  suite_add_tcase(s, tc_E);

  // %g
  TCase *tc_g = tcase_create("%g");
  tcase_add_test(tc_g, g_max);
  tcase_add_test(tc_g, g_min);
  tcase_add_test(tc_g, lg_min);
  tcase_add_test(tc_g, g_inf);
  tcase_add_test(tc_g, g_minus_inf);
  tcase_add_test(tc_g, g_nan);
  suite_add_tcase(s, tc_g);

  // %G
  TCase *tc_G = tcase_create("%G");
  tcase_add_test(tc_G, G_max);
  tcase_add_test(tc_G, G_min);
  tcase_add_test(tc_G, lG_min);
  tcase_add_test(tc_G, G_inf);
  tcase_add_test(tc_G, G_minus_inf);
  tcase_add_test(tc_G, G_nan);
  suite_add_tcase(s, tc_G);

  // %f с разными длинами
  TCase *tc_f_length = tcase_create("%f_length");
  tcase_add_test(tc_f_length, test_sscanf_f);
  tcase_add_test(tc_f_length, test_sscanf_lf);
  tcase_add_test(tc_f_length, test_sscanf_Lf);
  suite_add_tcase(s, tc_f_length);

  // %e с разными длинами
  TCase *tc_e_length = tcase_create("%e_length");
  tcase_add_test(tc_e_length, test_sscanf_e);
  tcase_add_test(tc_e_length, test_sscanf_le);
  tcase_add_test(tc_e_length, test_sscanf_Le);
  suite_add_tcase(s, tc_e_length);

  // %E с разными длинами
  TCase *tc_E_length = tcase_create("%E_length");
  tcase_add_test(tc_E_length, test_sscanf_E);
  tcase_add_test(tc_E_length, test_sscanf_lE);
  tcase_add_test(tc_E_length, test_sscanf_LE);
  suite_add_tcase(s, tc_E_length);

  // %g с разными длинами
  TCase *tc_g_length = tcase_create("%g_length");
  tcase_add_test(tc_g_length, test_sscanf_g);
  tcase_add_test(tc_g_length, test_sscanf_lg);
  tcase_add_test(tc_g_length, test_sscanf_Lg);
  suite_add_tcase(s, tc_g_length);

  // %G с разными длинами
  TCase *tc_G_length = tcase_create("%G_length");
  tcase_add_test(tc_G_length, test_sscanf_G);
  tcase_add_test(tc_G_length, test_sscanf_lG);
  tcase_add_test(tc_G_length, test_sscanf_LG);
  suite_add_tcase(s, tc_G_length);

  // Ширина
  TCase *tc_width = tcase_create("Width");
  tcase_add_test(tc_width, test_sscanf_d_width);
  tcase_add_test(tc_width, test_sscanf_s_width);
  tcase_add_test(tc_width, test_sscanf_c_width);
  tcase_add_test(tc_width, test_sscanf_d_width_);
  tcase_add_test(tc_width, test_sscanf_s_width_);
  tcase_add_test(tc_width, test_sscanf_c_width_);
  suite_add_tcase(s, tc_width);

  // Неполные совпадения
  TCase *tc_partial = tcase_create("Partial");
  tcase_add_test(tc_partial, partial_match1);
  tcase_add_test(tc_partial, partial_match2);
  tcase_add_test(tc_partial, partial_match3);
  tcase_add_test(tc_partial, empty_string);
  tcase_add_test(tc_partial, whitespace_only);
  tcase_add_test(tc_partial, whitespace_before);
  tcase_add_test(tc_partial, whitespace_after);
  tcase_add_test(tc_partial, no_integer);
  tcase_add_test(tc_partial, no_float);
  tcase_add_test(tc_partial, no_string);
  suite_add_tcase(s, tc_partial);

  // Пробельные символы
  TCase *tc_whitespace = tcase_create("Whitespace");
  tcase_add_test(tc_whitespace, test_sscanf_whitespace);
  tcase_add_test(tc_whitespace, test_sscanf_whitespace_format);
  suite_add_tcase(s, tc_whitespace);

  // %s
  TCase *tc_s = tcase_create("%s");
  tcase_add_test(tc_s, test_sscanf_s);
  tcase_add_test(tc_s, test_sscanf_percent_s_basic);
  tcase_add_test(tc_s, test_sscanf_percent_s_with_length);
  tcase_add_test(tc_s, test_sscanf_percent_s_with_asterisk);
  tcase_add_test(tc_s, test_sscanf_percent_s_multiple_spaces);
  tcase_add_test(tc_s, test_sscanf_percent_s_empty_string);
  tcase_add_test(tc_s, test_sscanf_percent_s_only_spaces);
  tcase_add_test(tc_s, test_sscanf_percent_s_mixed_format);
  suite_add_tcase(s, tc_s);

  // %c
  TCase *tc_c = tcase_create("%c");
  tcase_add_test(tc_c, test_sscanf_c);
  tcase_add_test(tc_c, test_sscanf_percent_c);
  tcase_add_test(tc_c, test_sscanf_percent_c_long);
  tcase_add_test(tc_c, test_sscanf_percent_c_short);
  tcase_add_test(tc_c, test_sscanf_percent_c_with_spaces);
  tcase_add_test(tc_c, test_sscanf_percent_c_multiple_spaces);
  tcase_add_test(tc_c, test_sscanf_percent_c_single_char);
  tcase_add_test(tc_c, test_sscanf_percent_c_space_only);
  tcase_add_test(tc_c, test_sscanf_percent_c_empty_string);
  suite_add_tcase(s, tc_c);

  // %n
  TCase *tc_n = tcase_create("%n");
  tcase_add_test(tc_n, test_sscanf_n);
  tcase_add_test(tc_n, test_sscanf_n_multiple);
  tcase_add_test(tc_n, test_sscanf_n_beginning);
  tcase_add_test(tc_n, test_sscanf_n_middle);
  suite_add_tcase(s, tc_n);

  // %%
  TCase *tc_percent = tcase_create("%%");
  tcase_add_test(tc_percent, test_sscanf_percent);
  tcase_add_test(tc_percent, test_sscanf_double_percent);
  tcase_add_test(tc_percent, test_sscanf_percent_with_text);
  suite_add_tcase(s, tc_percent);

  // %p
  TCase *tc_p = tcase_create("%p");
  tcase_add_test(tc_p, test_sscanf_p);
  tcase_add_test(tc_p, test_sscanf_p_null);
  tcase_add_test(tc_p, test_sscanf_p_large);
  suite_add_tcase(s, tc_p);

  // Локали
  TCase *tc_locale = tcase_create("Locale");
  tcase_add_test(tc_locale, test_sscanf_locale_decimal);
  suite_add_tcase(s, tc_locale);

  // Переполнение буфера
  TCase *tc_buffer = tcase_create("Buffer");
  tcase_add_test(tc_buffer, test_sscanf_buffer_overflow);
  suite_add_tcase(s, tc_buffer);

  // Большие данные
  TCase *tc_large = tcase_create("Large");
  tcase_add_test(tc_large, test_sscanf_large_number);
  tcase_add_test(tc_large, test_sscanf_long_string);
  suite_add_tcase(s, tc_large);

  // Бинарные данные
  TCase *tc_binary = tcase_create("Binary");
  tcase_add_test(tc_binary, test_sscanf_binary_data);
  suite_add_tcase(s, tc_binary);

  // Обработка ошибок
  TCase *tc_error = tcase_create("Error");
  tcase_add_test(tc_error, test_sscanf_overflow);
  suite_add_tcase(s, tc_error);

  // Длинные строки формата
  TCase *tc_long_format = tcase_create("LongFormat");
  tcase_add_test(tc_long_format, test_long_format_string);
  suite_add_tcase(s, tc_long_format);

  return s;
}

#pragma endregion

int main(void) {
  int number_failed;
  Suite *s;
  SRunner *sr;

  s = sscanf_suite();
  sr = srunner_create(s);

  srunner_run_all(sr, CK_NORMAL);
  number_failed = srunner_ntests_failed(sr);
  srunner_free(sr);

  return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}