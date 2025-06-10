#include <check.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "../include/s21_string.h"

START_TEST(test_sscanf_d) {
  int a1, a2;
  const char *input = "42";

  int res1 = sscanf(input, "%d", &a1);
  int res2 = s21_sscanf(input, "%d", &a2);

  ck_assert_int_eq(res1,
                   res2);  // Ожидаем одинаковое кол-во успешных присваиваний
  ck_assert_int_eq(a1, a2);  // Ожидаем одинаковые значения
}
END_TEST

START_TEST(test_sscanf_s) {
  char str1[20], str2[20];
  const char *input = "Hello World";

  int res1 = sscanf(input, "%s", str1);
  int res2 = s21_sscanf(input, "%s", str2);

  ck_assert_int_eq(res1, res2);
  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(test_sscanf_c) {
  char c1, c2;
  const char *input = "X";

  int res1 = sscanf(input, "%c", &c1);
  int res2 = s21_sscanf(input, "%c", &c2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(c1, c2);
}
END_TEST

START_TEST(test_sscanf_width_d) {
  int a1, a2;
  const char *input = "12345";

  int res1 = sscanf(input, "%3d", &a1);
  int res2 = s21_sscanf(input, "%3d", &a2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(a1, a2);  // Ожидаем 123, а не 12345
}
END_TEST

START_TEST(test_sscanf_width_s) {
  char str1[10], str2[10];
  const char *input = "ABCDEFGH";

  int res1 = sscanf(input, "%5s", str1);
  int res2 = s21_sscanf(input, "%5s", str2);

  ck_assert_int_eq(res1, res2);
  ck_assert_str_eq(str1, str2);  // Ожидаем "ABCDE"
}
END_TEST

START_TEST(test_sscanf_suppress) {
  int a1, a2;
  const char *input = "10 20";

  int res1 = sscanf(input, "%*d %d", &a1);
  int res2 = s21_sscanf(input, "%*d %d", &a2);

  ck_assert_int_eq(res1, res2);  // Ожидаем 1 (только одно присваивание)
  ck_assert_int_eq(a1, a2);  // Ожидаем 20
}
END_TEST

START_TEST(test_sscanf_f) {
  float f1, f2;
  const char *input = "3.1415";

  int res1 = sscanf(input, "%f", &f1);
  int res2 = s21_sscanf(input, "%f", &f2);

  ck_assert_int_eq(res1, res2);
  ck_assert_float_eq_tol(f1, f2, 1e-6);
}
END_TEST

START_TEST(test_sscanf_hd) {
  short a1, a2;
  const char *input = "32767";

  int res1 = sscanf(input, "%hd", &a1);
  int res2 = s21_sscanf(input, "%hd", &a2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(a1, a2);
}
END_TEST

START_TEST(test_sscanf_ld) {
  long a1, a2;
  const char *input = "2147483647";

  int res1 = sscanf(input, "%ld", &a1);
  int res2 = s21_sscanf(input, "%ld", &a2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(a1, a2);
}
END_TEST

START_TEST(test_sscanf_n) {
  int n1, n2, a1, a2;
  const char *input = "12345";

  int res1 = sscanf(input, "%d%n", &a1, &n1);
  int res2 = s21_sscanf(input, "%d%n", &a2, &n2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(n1, n2);  // Ожидаем 5 (длина "12345")
}
END_TEST

START_TEST(test_sscanf_set) {
  char str1[10], str2[10];
  const char *input = "123abc456";

  int res1 = sscanf(input, "%[0-9]", str1);
  int res2 = s21_sscanf(input, "%[0-9]", str2);

  ck_assert_int_eq(res1, res2);
  ck_assert_str_eq(str1, str2);  // Ожидаем "123"
}
END_TEST

START_TEST(test_sscanf_invalid) {
  int a1, a2;
  const char *input = "abc";

  int res1 = sscanf(input, "%d", &a1);
  int res2 = s21_sscanf(input, "%d", &a2);

  ck_assert_int_eq(res1, res2);  // Ожидаем 0 (ничего не считано)
}
END_TEST

// Здесь все тесты (как выше)

Suite *sscanf_suite(void) {
  Suite *s = suite_create("s21_sscanf");
  TCase *tc = tcase_create("Core");

  tcase_add_test(tc, test_sscanf_d);
  tcase_add_test(tc, test_sscanf_s);
  tcase_add_test(tc, test_sscanf_c);
  tcase_add_test(tc, test_sscanf_width_d);
  tcase_add_test(tc, test_sscanf_width_s);
  tcase_add_test(tc, test_sscanf_suppress);
  tcase_add_test(tc, test_sscanf_f);
  tcase_add_test(tc, test_sscanf_hd);
  tcase_add_test(tc, test_sscanf_ld);
  tcase_add_test(tc, test_sscanf_n);
  tcase_add_test(tc, test_sscanf_set);
  tcase_add_test(tc, test_sscanf_invalid);

  suite_add_tcase(s, tc);
  return s;
}

/**
 * Точка входа в программу
 * @param argc Количество аргументов командной строки
 * @param argv Массив аргументов командной строки
 *
 * Использование:
 *   ./test      - обычный режим (вывод только ошибок)
 *   ./test +    - подробный режим (вывод всех тестов)
 */
int main(int argc, char **argv) {
  int failed = 0;
  Suite *s = sscanf_suite();
  SRunner *runner = srunner_create(s);
  bool output_mode = (argc > 1 && strcmp(argv[1], "+") == 0);

  srunner_run_all(runner, CK_NORMAL);
  failed = srunner_ntests_failed(runner);
  srunner_free(runner);

  return (failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}