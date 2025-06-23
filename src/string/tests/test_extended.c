#include <check.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/s21_string.h"

////////////////////////////////////////////
//                                        //
//              s21_to_upper              //
//                                        //
////////////////////////////////////////////

/* Основные тесты для преобразования в верхний регистр */
START_TEST(test_to_upper_regular_string) {  // Обычная строка
  const char *str = "Hello, World!";
  char *result = s21_to_upper(str);
  ck_assert_str_eq(result, "HELLO, WORLD!");
  free(result);
}

START_TEST(test_to_upper_mixed_case) {  // Смешанный регистр
  const char *str = "HeLlo, WoRld!";
  char *result = s21_to_upper(str);
  ck_assert_str_eq(result, "HELLO, WORLD!");
  free(result);
}

START_TEST(test_to_upper_cyrillic) {  // Кириллические символы
  const char *str = "Привет, МИР!";
  char *result = s21_to_upper(str);
  ck_assert_str_eq(result, "ПРИВЕТ, МИР!");
  free(result);
}

START_TEST(test_to_upper_empty_string) {  // Пустая строка
  const char *str = "";
  char *result = s21_to_upper(str);
  ck_assert_str_eq(result, "");
  free(result);
}

START_TEST(test_to_upper_no_letters) {  // Строка без букв
  const char *str = "12345!@#$";
  char *result = s21_to_upper(str);
  ck_assert_str_eq(result, "12345!@#$");
  free(result);
}

/* Граничные случаи */
START_TEST(test_to_upper_null_input) {  // NULL вход
  char *result = s21_to_upper(NULL);
  ck_assert_ptr_eq(result, NULL);
}

START_TEST(test_to_upper_with_null_char) {  // Строка с нуль-символом
  const char *str = "\n\tabc\0\n";
  char *result = s21_to_upper(str);
  ck_assert_str_eq(result, "\n\tABC");
  free(result);
}

////////////////////////////////////////////
//                                        //
//              s21_to_lower              //
//                                        //
////////////////////////////////////////////

/* Основные тесты для преобразования в нижний регистр */
START_TEST(test_to_lower_regular_string) {  // Обычная строка
  const char *str = "Hello, World!";
  char *result = s21_to_lower(str);
  ck_assert_str_eq(result, "hello, world!");
  free(result);
}

START_TEST(test_to_lower_mixed_case) {  // Смешанный регистр
  const char *str = "HeLlo, WoRld!";
  char *result = s21_to_lower(str);
  ck_assert_str_eq(result, "hello, world!");
  free(result);
}

START_TEST(test_to_lower_cyrillic) {  // Кириллические символы
  const char *str = "Привет, МИР!";
  char *result = s21_to_lower(str);
  ck_assert_str_eq(result, "привет, мир!");
  free(result);
}

START_TEST(test_to_lower_empty_string) {  // Пустая строка
  const char *str = "";
  char *result = s21_to_lower(str);
  ck_assert_str_eq(result, "");
  free(result);
}

START_TEST(test_to_lower_no_letters) {  // Строка без букв
  const char *str = "12345!@#$";
  char *result = s21_to_lower(str);
  ck_assert_str_eq(result, "12345!@#$");
  free(result);
}

/* Граничные случаи */
START_TEST(test_to_lower_null_input) {  // NULL вход
  char *result = s21_to_lower(NULL);
  ck_assert_ptr_eq(result, NULL);
}

START_TEST(test_to_lower_with_null_char) {  // Строка с нуль-символом
  const char *str = "\n\tABC\0\n";
  char *result = s21_to_lower(str);
  ck_assert_str_eq(result, "\n\tabc");
  free(result);
}

////////////////////////////////////////////
//                                        //
//              s21_insert                //
//                                        //
////////////////////////////////////////////

/* Основные тесты для вставки строки */
START_TEST(test_insert_at_end) {  // Вставка в конец
  const char *src = "Hello";
  const char *str = ", World!";
  char *result = s21_insert(src, str, 5);
  ck_assert_str_eq(result, "Hello, World!");
  free(result);
}

START_TEST(test_insert_at_start) {  // Вставка в начало
  const char *src = "world";
  const char *str = "Hello ";
  char *result = s21_insert(src, str, 0);
  ck_assert_str_eq(result, "Hello world");
  free(result);
}

START_TEST(test_insert_in_middle) {  // Вставка в середину
  const char *src = "Helo";
  const char *str = "l";
  char *result = s21_insert(src, str, 2);
  ck_assert_str_eq(result, "Hello");
  free(result);
}

START_TEST(test_insert_to_empty) {  // Вставка в пустую строку
  const char *src = "";
  const char *str = "Hello";
  char *result = s21_insert(src, str, 0);
  ck_assert_str_eq(result, "Hello");
  free(result);
}

START_TEST(test_insert_empty_string) {  // Вставка пустой строки
  const char *src = "Hello";
  const char *str = "";
  char *result = s21_insert(src, str, 2);
  ck_assert_str_eq(result, "Hello");
  free(result);
}

/* Граничные случаи */
START_TEST(test_insert_null_source) {  // NULL исходная строка
  const char *str = "test";
  char *result = s21_insert(NULL, str, 0);
  ck_assert_ptr_eq(result, NULL);
}

START_TEST(test_insert_null_insert) {  // NULL строка для вставки
  const char *src = "test";
  char *result = s21_insert(src, NULL, 0);
  ck_assert_ptr_eq(result, NULL);
}

START_TEST(test_insert_invalid_position) {  // Неверная позиция
  const char *src = "Hello";
  const char *str = ", World!";
  char *result = s21_insert(src, str, 10);
  ck_assert_ptr_eq(result, NULL);
}

////////////////////////////////////////////
//                                        //
//               s21_trim                 //
//                                        //
////////////////////////////////////////////

/* Основные тесты для обрезки строк */
START_TEST(test_trim_spaces) {  // Обрезка пробелов
  const char *src = "  Hello, World!  ";
  const char *trim_chars = " ";
  char *result = s21_trim(src, trim_chars);
  ck_assert_str_eq(result, "Hello, World!");
  free(result);
}

START_TEST(test_trim_multiple_chars) {  // Обрезка нескольких символов
  const char *src = " \t\nHello, World! \t\n";
  const char *trim_chars = " \t\n";
  char *result = s21_trim(src, trim_chars);
  ck_assert_str_eq(result, "Hello, World!");
  free(result);
}

START_TEST(test_trim_no_trim_needed) {  // Когда обрезать не нужно
  const char *src = "Hello, World!";
  const char *trim_chars = " ";
  char *result = s21_trim(src, trim_chars);
  ck_assert_str_eq(result, "Hello, World!");
  free(result);
}

START_TEST(test_trim_empty_source) {  // Пустая исходная строка
  const char *src = "";
  const char *trim_chars = " ";
  char *result = s21_trim(src, trim_chars);
  ck_assert_str_eq(result, "");
  free(result);
}

START_TEST(test_trim_empty_chars) {  // Пустые символы для обрезки
  const char *src = "  Hello, World!  ";
  const char *trim_chars = "";
  char *result = s21_trim(src, trim_chars);
  ck_assert_str_eq(result, "  Hello, World!  ");
  free(result);
}

START_TEST(test_trim_all_chars) {  // Все символы подлежат обрезке
  const char *src = "abcHello, World!cba";
  const char *trim_chars = "abc";
  char *result = s21_trim(src, trim_chars);
  ck_assert_str_eq(result, "Hello, World!");
  free(result);
}

START_TEST(test_trim_completely) {  // Полная обрезка всей строки
  char *result = s21_trim("abcabcabc", "abc");
  ck_assert_str_eq(result, "");
  free(result);
}

/* Граничные случаи */
START_TEST(test_trim_null_source) {  // NULL исходная строка
  const char *trim_chars = " ";
  char *result = s21_trim(NULL, trim_chars);
  ck_assert_ptr_eq(result, NULL);
}

START_TEST(test_trim_null_chars) {  // NULL символы для обрезки
  const char *src = "Hello, World!";
  char *result = s21_trim(src, NULL);
  ck_assert_str_eq(result, "Hello, World!");
  free(result);
}

////////////////////////////////////////////
//                                        //
//               Test Suite               //
//                                        //
////////////////////////////////////////////

Suite *extended_suite(void) {
  Suite *s = suite_create("s21_string");
  TCase *tc = tcase_create("Core");

  // s21_to_upper
  tcase_add_test(tc, test_to_upper_regular_string);
  tcase_add_test(tc, test_to_upper_mixed_case);
  tcase_add_test(tc, test_to_upper_cyrillic);
  tcase_add_test(tc, test_to_upper_empty_string);
  tcase_add_test(tc, test_to_upper_no_letters);
  tcase_add_test(tc, test_to_upper_null_input);
  tcase_add_test(tc, test_to_upper_with_null_char);

  // s21_to_lower
  tcase_add_test(tc, test_to_lower_regular_string);
  tcase_add_test(tc, test_to_lower_mixed_case);
  tcase_add_test(tc, test_to_lower_cyrillic);
  tcase_add_test(tc, test_to_lower_empty_string);
  tcase_add_test(tc, test_to_lower_no_letters);
  tcase_add_test(tc, test_to_lower_null_input);
  tcase_add_test(tc, test_to_lower_with_null_char);

  // s21_insert
  tcase_add_test(tc, test_insert_at_end);
  tcase_add_test(tc, test_insert_at_start);
  tcase_add_test(tc, test_insert_in_middle);
  tcase_add_test(tc, test_insert_to_empty);
  tcase_add_test(tc, test_insert_empty_string);
  tcase_add_test(tc, test_insert_null_source);
  tcase_add_test(tc, test_insert_null_insert);
  tcase_add_test(tc, test_insert_invalid_position);

  // s21_trim
  tcase_add_test(tc, test_trim_spaces);
  tcase_add_test(tc, test_trim_multiple_chars);
  tcase_add_test(tc, test_trim_no_trim_needed);
  tcase_add_test(tc, test_trim_empty_source);
  tcase_add_test(tc, test_trim_empty_chars);
  tcase_add_test(tc, test_trim_all_chars);
  tcase_add_test(tc, test_trim_completely);
  tcase_add_test(tc, test_trim_null_source);
  tcase_add_test(tc, test_trim_null_chars);

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
  Suite *s = extended_suite();
  SRunner *runner = srunner_create(s);

  // Устанавливаем режим вывода в зависимости от аргументов
  if (argc > 1 && strcmp(argv[1], "+") == 0) {
    srunner_run_all(runner, CK_VERBOSE);  // Подробный вывод
  } else {
    srunner_run_all(runner, CK_NORMAL);  // Только ошибки
  }

  failed = srunner_ntests_failed(runner);
  srunner_free(runner);

  return (failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
