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

// Для целочисленных типов
#define TEST_SSCANF_INT(test_name, format, input_str, type, expected_value) \
  START_TEST(test_name) {                                                   \
    type val_sp = 0, val_s21 = 0;                                           \
    int res_sp = sscanf(input_str, format, &val_sp);                        \
    int res_s21 = s21_sscanf(input_str, format, &val_s21);                  \
    ck_assert_int_eq(res_sp, res_s21);                                      \
    ck_assert(val_sp == val_s21);                                           \
    ck_assert(val_sp == (type)(expected_value));                            \
  }                                                                         \
  END_TEST

// Для строк
#define TEST_SSCANF_STRING(test_name, format, input_str, expected_str) \
  START_TEST(test_name) {                                              \
    char str_sp[256] = {0};                                            \
    char str_s21[256] = {0};                                           \
    int res_sp = sscanf(input_str, format, str_sp);                    \
    int res_s21 = s21_sscanf(input_str, format, str_s21);              \
    ck_assert_int_eq(res_sp, res_s21);                                 \
    ck_assert_str_eq(str_sp, str_s21);                                 \
    ck_assert_str_eq(str_sp, expected_str);                            \
  }                                                                    \
  END_TEST

// Для символов
#define TEST_SSCANF_CHAR(test_name, format, input_str, expected_char) \
  START_TEST(test_name) {                                             \
    char c_sp = 0, c_s21 = 0;                                         \
    int res_sp = sscanf(input_str, format, &c_sp);                    \
    int res_s21 = s21_sscanf(input_str, format, &c_s21);              \
    ck_assert_int_eq(res_sp, res_s21);                                \
    ck_assert(c_sp == c_s21);                                         \
    ck_assert(c_sp == expected_char);                                 \
  }                                                                   \
  END_TEST

// Для вещественных чисел
#define TEST_SSCANF_FLOAT(test_name, format, input_str, expected_value) \
  START_TEST(test_name) {                                               \
    float val_sp = 0, val_s21 = 0;                                      \
    int res_sp = sscanf(input_str, format, &val_sp);                    \
    int res_s21 = s21_sscanf(input_str, format, &val_s21);              \
    ck_assert_int_eq(res_sp, res_s21);                                  \
    ck_assert_float_eq_tol(val_sp, val_s21, 1e-6);                      \
    ck_assert_float_eq_tol(val_sp, expected_value, 1e-6);               \
  }                                                                     \
  END_TEST

#define TEST_SSCANF_DOUBLE(test_name, format, input_str, expected_value) \
  START_TEST(test_name) {                                                \
    double val_sp = 0, val_s21 = 0;                                      \
    int res_sp = sscanf(input_str, format, &val_sp);                     \
    int res_s21 = s21_sscanf(input_str, format, &val_s21);               \
    ck_assert_int_eq(res_sp, res_s21);                                   \
    ck_assert_double_eq_tol(val_sp, val_s21, 1e-6);                      \
    ck_assert_double_eq_tol(val_sp, expected_value, 1e-6);               \
  }                                                                      \
  END_TEST

// Для указателей
#define TEST_SSCANF_POINTER(test_name, format, input_str, expected_ptr) \
  START_TEST(test_name) {                                               \
    void *ptr_sp = NULL;                                                \
    void *ptr_s21 = NULL;                                               \
    int res_sp = sscanf(input_str, format, &ptr_sp);                    \
    int res_s21 = s21_sscanf(input_str, format, &ptr_s21);              \
    ck_assert_int_eq(res_sp, res_s21);                                  \
    ck_assert_ptr_eq(ptr_sp, ptr_s21);                                  \
    ck_assert_ptr_eq(ptr_sp, expected_ptr);                             \
  }                                                                     \
  END_TEST

// ================================================================
// Целочисленные типы без модификаторов
// ================================================================

// %d - int (обычное значение)
TEST_SSCANF_INT(test_s21_sscanf_d, "%d", "123", int, 123)
// INT_MIN
TEST_SSCANF_INT(test_s21_sscanf_d_min, "%d", "-2147483648", int, INT_MIN)
// INT_MAX
TEST_SSCANF_INT(test_s21_sscanf_d_max, "%d", "2147483647", int, INT_MAX)

// %i - int (шестнадцатеричное)
TEST_SSCANF_INT(test_s21_sscanf_i_hex, "%i", "0x7B", int, 123)
// Восьмеричное
TEST_SSCANF_INT(test_s21_sscanf_i_oct, "%i", "0173", int, 123)

// %o - unsigned int
TEST_SSCANF_INT(test_s21_sscanf_o, "%o", "173", unsigned int, 0123)
// UINT_MAX в восьмеричной системе
TEST_SSCANF_INT(test_s21_sscanf_o_max, "%o", "37777777777", unsigned int,
                UINT_MAX)

// %u - unsigned int
TEST_SSCANF_INT(test_s21_sscanf_u, "%u", "123", unsigned int, 123)
// UINT_MAX
TEST_SSCANF_INT(test_s21_sscanf_u_max, "%u", "4294967295", unsigned int,
                UINT_MAX)

// %x - unsigned int (нижний регистр)
TEST_SSCANF_INT(test_s21_sscanf_x, "%x", "7b", unsigned int, 0x7B)
// UINT_MAX в шестнадцатеричной
TEST_SSCANF_INT(test_s21_sscanf_x_max, "%x", "ffffffff", unsigned int, UINT_MAX)

// %X - unsigned int (верхний регистр)
TEST_SSCANF_INT(test_s21_sscanf_X, "%X", "7B", unsigned int, 0x7B)

// ================================================================
// Модификатор h (short)
// ================================================================

// %hd - short
TEST_SSCANF_INT(test_s21_sscanf_hd, "%hd", "123", short, 123)
// SHRT_MIN
TEST_SSCANF_INT(test_s21_sscanf_hd_min, "%hd", "-32768", short, SHRT_MIN)

// %hu - unsigned short
TEST_SSCANF_INT(test_s21_sscanf_hu, "%hu", "123", unsigned short, 123)
// USHRT_MAX
TEST_SSCANF_INT(test_s21_sscanf_hu_max, "%hu", "65535", unsigned short,
                USHRT_MAX)

// ================================================================
// Модификатор hh (char)
// ================================================================

// %hhd - signed char
TEST_SSCANF_INT(test_s21_sscanf_hhd, "%hhd", "123", signed char, 123)
// SCHAR_MIN
TEST_SSCANF_INT(test_s21_sscanf_hhd_min, "%hhd", "-128", signed char, SCHAR_MIN)

// %hhu - unsigned char
TEST_SSCANF_INT(test_s21_sscanf_hhu, "%hhu", "123", unsigned char, 123)
// UCHAR_MAX
TEST_SSCANF_INT(test_s21_sscanf_hhu_max, "%hhu", "255", unsigned char,
                UCHAR_MAX)

// ================================================================
// Модификатор l (long)
// ================================================================

// %ld - long
TEST_SSCANF_INT(test_s21_sscanf_ld, "%ld", "1234567890", long, 1234567890L)
// LONG_MIN
TEST_SSCANF_INT(test_s21_sscanf_ld_min, "%ld", "-9223372036854775808", long,
                LONG_MIN)

// %lu - unsigned long
TEST_SSCANF_INT(test_s21_sscanf_lu, "%lu", "1234567890", unsigned long,
                1234567890UL)
// ULONG_MAX
TEST_SSCANF_INT(test_s21_sscanf_lu_max, "%lu", "18446744073709551615",
                unsigned long, ULONG_MAX)

// ================================================================
// Модификатор ll (long long)
// ================================================================

// %lld - long long
TEST_SSCANF_INT(test_s21_sscanf_lld, "%lld", "123456789012345", long long,
                123456789012345LL)
// LLONG_MIN
TEST_SSCANF_INT(test_s21_sscanf_lld_min, "%lld", "-9223372036854775808",
                long long, LLONG_MIN)

// %llu - unsigned long long
TEST_SSCANF_INT(test_s21_sscanf_llu, "%llu", "123456789012345",
                unsigned long long, 123456789012345ULL)
// ULLONG_MAX
TEST_SSCANF_INT(test_s21_sscanf_llu_max, "%llu", "18446744073709551615",
                unsigned long long, ULLONG_MAX)

// ================================================================
// Строковые типы
// ================================================================

// %c - char
TEST_SSCANF_CHAR(test_s21_sscanf_c, "%c", "A", 'A')
TEST_SSCANF_CHAR(test_s21_sscanf_c_newline, "%c", "\n", '\n')

// %s - string
TEST_SSCANF_STRING(test_s21_sscanf_s, "%s", "Hello", "Hello")
TEST_SSCANF_STRING(test_s21_sscanf_s_unicode, "%s", "Привет", "Привет")

// ================================================================
// Вещественные типы
// ================================================================

// %f - float
TEST_SSCANF_FLOAT(test_s21_sscanf_f, "%f", "123.456", 123.456f)
TEST_SSCANF_FLOAT(test_s21_sscanf_f_zero, "%f", "0.0", 0.0f)

// %lf - double
TEST_SSCANF_DOUBLE(test_s21_sscanf_lf, "%lf", "123.456", 123.456)
TEST_SSCANF_DOUBLE(test_s21_sscanf_lf_exp, "%lf", "1.23456e2", 123.456)

// Специальные значения
START_TEST(test_s21_sscanf_inf) {
  float f1, f2;
  double d1, d2;
  const char *input = "inf";

  int res1 = sscanf(input, "%f", &f1);
  int res2 = s21_sscanf(input, "%f", &f2);
  ck_assert_int_eq(res1, res2);
  ck_assert(isinf(f1) && isinf(f2));

  res1 = sscanf(input, "%lf", &d1);
  res2 = s21_sscanf(input, "%lf", &d2);
  ck_assert_int_eq(res1, res2);
  ck_assert(isinf(d1) && isinf(d2));
}
END_TEST

// ================================================================
// Особые типы
// ================================================================

// %p - pointer
START_TEST(test_s21_sscanf_p) {
  void *ptr = NULL;
  char input_str[50];
  sprintf(input_str, "%p", &ptr);

  void *p1 = NULL, *p2 = NULL;
  int res1 = sscanf(input_str, "%p", &p1);
  int res2 = s21_sscanf(input_str, "%p", &p2);

  ck_assert_int_eq(res1, res2);
  ck_assert_ptr_eq(p1, p2);
  ck_assert_ptr_eq(p1, &ptr);
}
END_TEST

// %n - количество символов
START_TEST(test_s21_sscanf_n) {
  const char *input = "12345";
  int n1 = 0, n2 = 0;
  int a1 = 0, a2 = 0;

  int res1 = sscanf(input, "%d%n", &a1, &n1);
  int res2 = s21_sscanf(input, "%d%n", &a2, &n2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(n1, n2);
  ck_assert_int_eq(n1, 5);  // 5 символов в "12345"
}
END_TEST

// %% - знак процента
START_TEST(test_s21_sscanf_percent) {
  int a1 = 0, a2 = 0;
  const char *input = "50%";

  int res1 = sscanf(input, "%d%%", &a1);
  int res2 = s21_sscanf(input, "%d%%", &a2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(a1, 50);
  ck_assert_int_eq(a2, 50);
}
END_TEST

// %d - int (обычное значение)
// ================================================================
// Test suite
// ================================================================

Suite *sscanf_suite(void) {
  Suite *s = suite_create("test_sscanf");
  TCase *tc = tcase_create("Core");

  tcase_add_test(tc, test_s21_sscanf_d);
  tcase_add_test(tc, test_s21_sscanf_d_min);
  tcase_add_test(tc, test_s21_sscanf_d_max);
  tcase_add_test(tc, test_s21_sscanf_i_hex);
  tcase_add_test(tc, test_s21_sscanf_i_oct);
  tcase_add_test(tc, test_s21_sscanf_o);
  tcase_add_test(tc, test_s21_sscanf_o_max);
  tcase_add_test(tc, test_s21_sscanf_u);
  tcase_add_test(tc, test_s21_sscanf_u_max);
  tcase_add_test(tc, test_s21_sscanf_x);
  tcase_add_test(tc, test_s21_sscanf_x_max);
  tcase_add_test(tc, test_s21_sscanf_X);
  tcase_add_test(tc, test_s21_sscanf_hd);
  tcase_add_test(tc, test_s21_sscanf_hd_min);
  tcase_add_test(tc, test_s21_sscanf_hu);
  tcase_add_test(tc, test_s21_sscanf_hu_max);
  tcase_add_test(tc, test_s21_sscanf_hhd);
  tcase_add_test(tc, test_s21_sscanf_hhd_min);
  tcase_add_test(tc, test_s21_sscanf_hhu);
  tcase_add_test(tc, test_s21_sscanf_hhu_max);
  tcase_add_test(tc, test_s21_sscanf_ld);
  tcase_add_test(tc, test_s21_sscanf_ld_min);
  tcase_add_test(tc, test_s21_sscanf_lu);
  tcase_add_test(tc, test_s21_sscanf_lu_max);
  tcase_add_test(tc, test_s21_sscanf_lld);
  tcase_add_test(tc, test_s21_sscanf_lld_min);
  tcase_add_test(tc, test_s21_sscanf_llu);
  tcase_add_test(tc, test_s21_sscanf_llu_max);
  tcase_add_test(tc, test_s21_sscanf_c);
  tcase_add_test(tc, test_s21_sscanf_c_newline);
  tcase_add_test(tc, test_s21_sscanf_s);
  tcase_add_test(tc, test_s21_sscanf_s_unicode);
  tcase_add_test(tc, test_s21_sscanf_f);
  tcase_add_test(tc, test_s21_sscanf_f_zero);
  tcase_add_test(tc, test_s21_sscanf_lf);
  tcase_add_test(tc, test_s21_sscanf_lf_exp);
  tcase_add_test(tc, test_s21_sscanf_inf);
  tcase_add_test(tc, test_s21_sscanf_p);
  tcase_add_test(tc, test_s21_sscanf_n);
  tcase_add_test(tc, test_s21_sscanf_percent);
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