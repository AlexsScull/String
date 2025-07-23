#include <check.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/s21_string.h"

////////////////////////////////////////////
//                                        //
//               s21_memchr               //
//                                        //
////////////////////////////////////////////

/* Основные случаи работы */
START_TEST(test_memchr_basic) {  // Поиск существующего символа
  ck_assert_ptr_eq(s21_memchr("abcde", 'c', strlen("abcde")),
                   memchr("abcde", 'c', strlen("abcde")));
}

START_TEST(test_memchr_no_char) {  // Поиск отсутствующего символа
  ck_assert_ptr_eq(s21_memchr("abcde", 'f', strlen("abcde")),
                   memchr("abcde", 'f', strlen("abcde")));
}

START_TEST(test_memchr_first_char) {  // Поиск первого символа
  ck_assert_ptr_eq(s21_memchr("abcde", 'a', strlen("abcde")),
                   memchr("abcde", 'a', strlen("abcde")));
}

START_TEST(test_memchr_last_char) {  // Поиск последнего символа
  ck_assert_ptr_eq(s21_memchr("abcde", 'e', strlen("abcde")),
                   memchr("abcde", 'e', strlen("abcde")));
}

START_TEST(test_memchr_recurring_char) {  // Поиск повторяющегося символа
  ck_assert_ptr_eq(s21_memchr("aabcadea", 'a', strlen("aabcadea")),
                   memchr("aabcadea", 'a', strlen("aabcadea")));
}

START_TEST(test_memchr_all_ascii_chars) {  // Поиск всех символов по очереди
  char str[128];

  for (int i = 1; i < 128; i++) {
    str[i - 1] = (char)i;
  }
  str[127] = '\0';

  for (int i = 1; i < 128; i++) {
    char ch = (char)i;
    ck_assert_ptr_eq(s21_memchr(str, ch, strlen(str)),
                     memchr(str, ch, strlen(str)));
  }
}

/* Работа с нуль-терминатором */
START_TEST(test_memchr_null) {  // Поиск нуль-символа
  ck_assert_ptr_eq(s21_memchr("abcde", '\0', strlen("abcde") + 1),
                   memchr("abcde", '\0', strlen("abcde") + 1));
}

START_TEST(test_memchr_null_in_middle) {  // Явный нуль-символ в строке
  ck_assert_ptr_eq(s21_memchr("abc\0de", '\0', 6), memchr("abc\0de", '\0', 6));
}

START_TEST(test_memchr_after_null) {  // Поиск после нуль-терминатора
  ck_assert_ptr_eq(s21_memchr("abc\0de", 'd', 7), memchr("abc\0de", 'd', 7));
}

/* Граничные случаи */
START_TEST(test_memchr_null_ptr) {  // NULL строка
  ck_assert_ptr_eq(s21_memchr(NULL, 'a', 4), NULL);
}

START_TEST(test_memchr_zero_length) {  // Нулевая длина
  ck_assert_ptr_eq(s21_memchr("abcde", 'a', 0), memchr("abcde", 'a', 0));
}

START_TEST(test_memchr_partial_search) {  // Поиск в части строки
  ck_assert_ptr_eq(s21_memchr("abcde", 'e', 1), memchr("abcde", 'e', 1));
}

/* Специальные значения символов */
START_TEST(test_memchr_large_char) {  // Символ > 255
  ck_assert_ptr_eq(s21_memchr("abcde", 1024, strlen("abcde")),
                   memchr("abcde", 1024, strlen("abcde")));
}

START_TEST(test_memchr_negative_char) {  // Отрицательный символ
  int s = 'c' * -1;
  ck_assert_ptr_eq(s21_memchr("abcde", s, strlen("abcde")),
                   memchr("abcde", s, strlen("abcde")));
}

START_TEST(test_memchr_unicode) {  // Unicode символы
  const char str[] = "aбвгд";
  ck_assert_ptr_eq(s21_memchr(str, 0xd0, sizeof(str)),  // Байт кириллицы
                   memchr(str, 0xd0, sizeof(str)));
}

START_TEST(test_memchr_max_size) {  // Максимальный размер
  const char str[] = "test";
  void *res = s21_memchr(str, 't', SIZE_MAX);
  ck_assert(res != NULL);  // Проверяем, что не упало
}

START_TEST(test_memchr_large_buffer) {  // длинная строка
  char large_str[1024];
  memset(large_str, 'a', sizeof(large_str));
  large_str[1023] = 'b';
  ck_assert_ptr_eq(s21_memchr(large_str, 'b', sizeof(large_str)),
                   memchr(large_str, 'b', sizeof(large_str)));
}

START_TEST(test_memchr_overlap) {  // Перекрытие буферов
  char buf[] = "abcdef";
  ck_assert_ptr_eq(s21_memchr(buf + 1, 'a', 5), memchr(buf + 1, 'a', 5));
}

/* Бинарные данные */
START_TEST(test_memchr_binary_data) {  // Поиск в бинарных данных
  unsigned char data[] = {0x01, 0x02, 0x03, 0xFF, 0x05};
  ck_assert_ptr_eq(s21_memchr(data, 0xFF, sizeof(data)),
                   memchr(data, 0xFF, sizeof(data)));
}

START_TEST(test_memchr_binary_data_normal) {  // Поиск в бинарных данных
  unsigned char data[] = {0x01, 0x02, 0x03, 0x04, 0x05};
  ck_assert_ptr_eq(s21_memchr(data, 0x04, sizeof(data)),
                   memchr(data, 0x04, sizeof(data)));
}

START_TEST(test_memchr_high_ascii) {  // Символы верхнего ASCII (0x80-0xFF)
  const char data[] = {0x61, 0x80, 0x63, 0x00};
  ck_assert_ptr_eq(s21_memchr(data, 0x80, sizeof(data)),
                   memchr(data, 0x80, sizeof(data)));
}

////////////////////////////////////////////
//                                        //
//               s21_memcmp               //
//                                        //
////////////////////////////////////////////

/* Основные случаи работы */
START_TEST(test_memcmp_equal) {  // Строки полностью равны
  ck_assert_int_eq(s21_memcmp("abcde", "abcde", strlen("abcde")),
                   memcmp("abcde", "abcde", strlen("abcde")));
}

START_TEST(test_memcmp_less) {  // s1 < s2 (разница в середине)
  ck_assert_int_eq(s21_memcmp("abcde", "abczz", strlen("abcde")),
                   memcmp("abcde", "abczz", strlen("abcde")));
}

START_TEST(test_memcmp_greater) {  // s1 > s2 (разница в середине)
  ck_assert_int_eq(s21_memcmp("abczz", "abcde", strlen("abczz")),
                   memcmp("abczz", "abcde", strlen("abczz")));
}

START_TEST(test_memcmp_diff_prefix) {  // Различие в первых n байтах
  ck_assert_int_eq(s21_memcmp("xbcde", "ybcde", strlen("xbcde")),
                   memcmp("xbcde", "ybcde", strlen("xbcde")));
}
START_TEST(test_memcmp_case_sensitive) {  // Сравнение строк с разным регистром
  ck_assert_int_eq(s21_memcmp("ABC", "abc", strlen("ABC")),
                   memcmp("ABC", "abc", strlen("ABC")));
}

START_TEST(test_memcmp_equal_prefix) {  // Строки различаются, но сравниваются
                                        // только первые `n` байт
  ck_assert_int_eq(s21_memcmp("abcde", "abcxx", strlen("abc")),
                   memcmp("abcde", "abcxx", strlen("abc")));
}

/* Работа с нуль-терминатором */
/* Граничные случаи */

START_TEST(test_memcmp_null_in_str) {
  ck_assert_int_eq(s21_memcmp("ab\0de", "ab\0zz", 5),
                   memcmp("ab\0de", "ab\0zz", 5));
}

START_TEST(test_memcmp_zero_length_n) {  // n = 0
  ck_assert_int_eq(s21_memcmp("abcde", "xxxxx", 0),
                   memcmp("abcde", "xxxxx", 0));
}
START_TEST(
    test_memcmp_zero_length) {  // Передача `NULL` (UB, но проверяем на краш)
  ck_assert_int_eq(s21_memcmp(NULL, "xxxxx", strlen("xxxxx")), 0);
}
START_TEST(test_memcmp_null_ptr) {  // NULL указатели (UB)
  ck_assert_int_eq(s21_memcmp(NULL, NULL, 0), 0);
}

/* Специальные значения */

START_TEST(test_memcmp_large_char) {  // Сравнение символов вне `unsigned char`
                                      // (например, `c = 256`)
  ck_assert_int_eq(s21_memcmp("abc", "ab\xFF", strlen("abc")),
                   memcmp("abc", "ab\xFF", strlen("abc")));
  // 0xFF — максимальный `unsigned char`
}

START_TEST(test_memcmp_negative_chars) {  // Отрицательные значения
  const char s1[] = {-1, -2, -3};
  const char s2[] = {-1, -2, -4};
  ck_assert_int_eq(s21_memcmp(s1, s2, strlen(s1)), memcmp(s1, s2, strlen(s1)));
}

/* Бинарные данные */
START_TEST(test_memcmp_binary_data) {
  unsigned char d1[] = {0x01, 0x02, 0x03};
  unsigned char d2[] = {0x01, 0x02, 0x04};
  ck_assert_int_eq(s21_memcmp(d1, d2, strlen(d1)), memcmp(d1, d2, strlen(d1)));
}

START_TEST(test_memcmp_unicode) {  // Unicode сравнение
  ck_assert_int_eq(s21_memcmp("aбв", "aбг", strlen("aбв")),
                   memcmp("aбв", "aбг", strlen("aбв")));
}

/* Максимальный размер (проверка на переполнение) */
START_TEST(test_memcmp_max_size) {
  ck_assert_int_eq(s21_memcmp("abc", "abc", SIZE_MAX),
                   memcmp("abc", "abc", SIZE_MAX));
}

/* Перекрытие буферов */
START_TEST(test_memcmp_overlap) {
  char buf[] = "abcdef";
  ck_assert_int_eq(s21_memcmp(buf, buf + 1, 3), memcmp(buf, buf + 1, 3));
}

////////////////////////////////////////////
//                                        //
//               s21_memcpy               //
//                                        //
////////////////////////////////////////////

/* Основные случаи работы */

START_TEST(test_memcpy_basic) {  // Копирование строки
  char src[] = "Hello, world!";
  char dest_s21[20];
  char dest_std[20];

  ck_assert_ptr_eq(s21_memcpy(dest_s21, src, strlen(src) + 1),
                   memcpy(dest_std, src, strlen(src) + 1));
  ck_assert_str_eq(dest_s21, dest_std);
}

START_TEST(test_memcpy_partial) {  // Частичное копирование
  char src[] = "Hello, World!";
  char dest_s21[10] = {0};
  char dest_std[10] = {0};
  s21_memcpy(dest_s21, src, 5);
  memcpy(dest_std, src, 5);
  ck_assert_mem_eq(dest_s21, dest_std, 5);
}

START_TEST(
    test_memcpy_binary_data) {  // Копирование бинарных данных (не строки)
  unsigned char src[] = {0x01, 0x02, 0x03, 0xFF};
  unsigned char dest_s21[4];
  unsigned char dest_std[4];

  ck_assert_ptr_eq(s21_memcpy(dest_s21, src, sizeof(src)),
                   memcpy(dest_std, src, sizeof(src)));
  ck_assert_mem_eq(dest_s21, dest_std, sizeof(src));
}

START_TEST(
    test_memcpy_overwrite_middle) {  // Копирование в середину другой строки
  char str[20] = "abcdefghij";
  ck_assert_ptr_eq(s21_memcpy(str + 3, "123", 3), memcpy(str + 3, "123", 3));
  ck_assert_str_eq(str, "abc123ghij");
}

/* Работа с нуль-терминатором
И
Граничные случаи */

START_TEST(test_memcpy_zero_length) {  // n = 0
  char src[] = "abc";
  char dest_s21[10] = "abc";
  char dest_std[10] = "abc";

  ck_assert_ptr_eq(s21_memcpy(dest_s21, src, 0), memcpy(dest_std, src, 0));
  ck_assert_str_eq(dest_s21, dest_std);
}

START_TEST(
    test_memcpy_null_src) {  // Передача `NULL` (UB, но проверяем на краш)
  char dest[10];
  ck_assert_ptr_eq(s21_memcpy(dest, NULL, 5), NULL);
}

START_TEST(
    test_memcpy_null_dest) {  // Передача `NULL` (UB, но проверяем на краш)
  char src[] = "abc";
  ck_assert_ptr_eq(s21_memcpy(NULL, src, 3), NULL);
}

START_TEST(test_memcpy_null_ptr) {  // NULL указатели (UB)
  ck_assert_ptr_eq(s21_memcpy(NULL, NULL, 0), memcpy(NULL, NULL, 0));
}

START_TEST(test_memcpy_null_terminator) {  // Копирование нуль-терминатора
  char src[] = "Hello\0World";
  char dest_s21[12];
  char dest_std[12];
  ck_assert_ptr_eq(s21_memcpy(dest_s21, src, sizeof(src)),
                   memcpy(dest_std, src, sizeof(src)));
  ck_assert_mem_eq(dest_s21, dest_std, sizeof(src));
}

/* Специальные значения */

// Копирование в буфер меньшего размера (потенциальное переполнение)
START_TEST(test_memcpy_small_buffer) {
  char src[] = "This is a long string";
  char dest[5] = {0};  // Буфер меньше, чем `src`
  char expected[5] = {0};

  ck_assert_ptr_eq(s21_memcpy(dest, src, sizeof(dest)),
                   memcpy(expected, src, sizeof(dest)));
  ck_assert_mem_eq(dest, expected, sizeof(dest));
}

START_TEST(test_memcpy_overlap) {  // Копирование в перекрывающиеся буферы (UB,
                                   // но проверяем)
  char buf[] = "abcdef";
  ck_assert_ptr_eq(s21_memcpy(buf + 1, buf, 3), memcpy(buf + 1, buf, 3));
  ck_assert_str_eq(buf, "aabcdf");
}

START_TEST(test_memcpy_large_data) {  // Копирование большого объема данных
  char src[1024];
  char dest_s21[1024];
  char dest_std[1024];

  memset(src, 'A', sizeof(src));
  ck_assert_ptr_eq(s21_memcpy(dest_s21, src, sizeof(src)),
                   memcpy(dest_std, src, sizeof(src)));
  ck_assert_mem_eq(dest_s21, dest_std, sizeof(src));
}

START_TEST(test_memcpy_large_n) {  // Большой размер
  char src[1024];
  char dest_s21[1024];
  char dest_std[1024];
  memset(src, 'A', sizeof(src));
  ck_assert_ptr_eq(s21_memcpy(dest_s21, src, sizeof(src)),
                   memcpy(dest_std, src, sizeof(src)));
  ck_assert_mem_eq(dest_s21, dest_std, sizeof(src));
}

START_TEST(test_memcpy_large_char) {  // Копирование символов вне `unsigned
                                      // char` (например, `c = 256`)
  unsigned char src[] = {0x01, 0x02, 0xFF, 0x00};
  unsigned char dest_s21[4];
  unsigned char dest_std[4];
  ck_assert_ptr_eq(s21_memcpy(dest_s21, src, sizeof(src)),
                   memcpy(dest_std, src, sizeof(src)));
  ck_assert_mem_eq(dest_s21, dest_std, sizeof(src));
}

////////////////////////////////////////////
//                                        //
//               s21_memset               //
//                                        //
////////////////////////////////////////////

/* Основные случаи работы */

// Заполнение нулями
START_TEST(test_memset_zero) {
  char str_s21[10] = "abcdef";
  char str_std[10] = "abcdef";

  ck_assert_ptr_eq(s21_memset(str_s21, 0, 3), memset(str_std, 0, 3));
  ck_assert_mem_eq(str_s21, str_std, 10);
}

// Заполнение конкретным символом (например, 'A')
START_TEST(test_memset_fill_char) {
  char str_s21[10] = {0};
  char str_std[10] = {0};

  ck_assert_ptr_eq(s21_memset(str_s21, 'A', 5), memset(str_std, 'A', 5));
  ck_assert_str_eq(str_s21, str_std);
}

// Частичное заполнение строки
START_TEST(test_memset_partial_fill) {
  char str_s21[10] = "abcdef";
  char str_std[10] = "abcdef";

  ck_assert_ptr_eq(s21_memset(str_s21 + 2, 'X', 3),
                   memset(str_std + 2, 'X', 3));
  ck_assert_str_eq(str_s21, str_std);
}

/* Работа с нуль-терминатором
И
Граничные случаи */

// `n = 0` → Ничего не заполняется
START_TEST(test_memset_zero_length) {
  char str_s21[10] = "abc";
  char str_std[10] = "abc";

  ck_assert_ptr_eq(s21_memset(str_s21, 'X', 0), memset(str_std, 'X', 0));
  ck_assert_str_eq(str_s21, str_std);
}

// Передача `NULL` (UB, но проверяем на краш)
START_TEST(test_memset_null_ptr) {
  ck_assert_ptr_eq(s21_memset(NULL, 'A', 5), NULL);
}

// Заполнение нуль-терминатором ('\0')
START_TEST(test_memset_null_byte) {
  char str_s21[10] = "abcdef";
  char str_std[10] = "abcdef";

  ck_assert_ptr_eq(s21_memset(str_s21, '\0', 3), memset(str_std, '\0', 3));
  ck_assert_str_eq(str_s21, str_std);
}

START_TEST(test_memset_null_ptr_all) {  // NULL указатель (UB)
  ck_assert_ptr_eq(s21_memset(NULL, 0, 0), memset(NULL, 0, 0));
}

/* Специальные значения */

// Заполнение символами вне `unsigned char` (например, `c = 1024`)
START_TEST(test_memset_large_char) {
  char str_s21[10] = {0};
  char str_std[10] = {0};

  ck_assert_ptr_eq(s21_memset(str_s21, 1024, 5), memset(str_std, 1024, 5));
  ck_assert_mem_eq(str_s21, str_std, 5);
}

START_TEST(test_memset_large_char2) {  // Символы вне unsigned char
  unsigned char data_s21[4] = {0x01, 0x02, 0x03, 0x04};
  unsigned char data_std[4] = {0x01, 0x02, 0x03, 0x04};
  ck_assert_ptr_eq(s21_memset(data_s21, 0xFF, sizeof(data_s21)),
                   memset(data_std, 0xFF, sizeof(data_std)));
  ck_assert_mem_eq(data_s21, data_std, sizeof(data_s21));
}

// Заполнение отрицательными значениями (интерпретируется как `unsigned char`)
START_TEST(test_memset_negative_char) {
  char str_s21[10] = {0};
  char str_std[10] = {0};

  ck_assert_ptr_eq(s21_memset(str_s21, -10, 5), memset(str_std, -10, 5));
  ck_assert_mem_eq(str_s21, str_std, 5);
}

// Заполнение бинарных данных (не `char`-строка)
START_TEST(test_memset_binary_data) {
  unsigned char data_s21[5] = {0x01, 0x02, 0x03, 0x04, 0x05};
  unsigned char data_std[5] = {0x01, 0x02, 0x03, 0x04, 0x05};

  ck_assert_ptr_eq(s21_memset(data_s21, 0xFF, 3), memset(data_std, 0xFF, 3));
  ck_assert_mem_eq(data_s21, data_std, 5);
}

////////////////////////////////////////////
//                                        //
//               Test Suite               //
//                                        //
////////////////////////////////////////////

Suite *memory_suite(void) {
  Suite *s = suite_create("test_memory");
  TCase *tc = tcase_create("Core");

  //// s21_memchr ////

  // Основные случаи работы
  tcase_add_test(tc, test_memchr_basic);
  tcase_add_test(tc, test_memchr_no_char);
  tcase_add_test(tc, test_memchr_first_char);
  tcase_add_test(tc, test_memchr_last_char);
  tcase_add_test(tc, test_memchr_recurring_char);
  tcase_add_test(tc, test_memchr_all_ascii_chars);

  // Работа с нуль-терминатором
  tcase_add_test(tc, test_memchr_null);
  tcase_add_test(tc, test_memchr_null_in_middle);
  tcase_add_test(tc, test_memchr_after_null);

  // Граничные случаи
  tcase_add_test(tc, test_memchr_null_ptr);
  tcase_add_test(tc, test_memchr_zero_length);
  tcase_add_test(tc, test_memchr_partial_search);

  // Специальные значения символов
  tcase_add_test(tc, test_memchr_large_char);
  tcase_add_test(tc, test_memchr_negative_char);
  tcase_add_test(tc, test_memchr_unicode);
  tcase_add_test(tc, test_memchr_max_size);
  tcase_add_test(tc, test_memchr_large_buffer);
  tcase_add_test(tc, test_memchr_overlap);

  // Бинарные данные
  tcase_add_test(tc, test_memchr_binary_data);
  tcase_add_test(tc, test_memchr_binary_data_normal);
  tcase_add_test(tc, test_memchr_high_ascii);

  //// s21_memchr ////

  // Основные случаи работы
  tcase_add_test(tc, test_memcmp_equal);
  tcase_add_test(tc, test_memcmp_less);
  tcase_add_test(tc, test_memcmp_greater);
  tcase_add_test(tc, test_memcmp_diff_prefix);
  tcase_add_test(tc, test_memcmp_case_sensitive);
  tcase_add_test(tc, test_memcmp_equal_prefix);
  // Работа с нуль-терминатором И Граничные случаи
  tcase_add_test(tc, test_memcmp_null_in_str);
  tcase_add_test(tc, test_memcmp_zero_length_n);
  tcase_add_test(tc, test_memcmp_zero_length);
  tcase_add_test(tc, test_memcmp_null_ptr);
  // Специальные значения символов
  tcase_add_test(tc, test_memcmp_large_char);
  tcase_add_test(tc, test_memcmp_negative_chars);
  // Бинарные данные
  tcase_add_test(tc, test_memcmp_binary_data);
  tcase_add_test(tc, test_memcmp_unicode);
  tcase_add_test(tc, test_memcmp_max_size);
  tcase_add_test(tc, test_memcmp_overlap);

  //// s21_memcpy ////

  // Основные случаи работы
  tcase_add_test(tc, test_memcpy_basic);
  tcase_add_test(tc, test_memcpy_partial);
  tcase_add_test(tc, test_memcpy_binary_data);
  tcase_add_test(tc, test_memcpy_overwrite_middle);
  // Работа с нуль-терминатором И Граничные случаи
  tcase_add_test(tc, test_memcpy_zero_length);
  tcase_add_test(tc, test_memcpy_null_src);
  tcase_add_test(tc, test_memcpy_null_dest);
  tcase_add_test(tc, test_memcpy_null_ptr);
  tcase_add_test(tc, test_memcpy_null_terminator);
  // Специальные значения символов
  tcase_add_test(tc, test_memcpy_small_buffer);
  tcase_add_test(tc, test_memcpy_overlap);
  tcase_add_test(tc, test_memcpy_large_data);
  tcase_add_test(tc, test_memcpy_large_n);
  tcase_add_test(tc, test_memcpy_large_char);

  //// s21_memset ////

  // Основные случаи работы
  tcase_add_test(tc, test_memset_zero);
  tcase_add_test(tc, test_memset_fill_char);
  tcase_add_test(tc, test_memset_partial_fill);

  // Работа с нуль-терминатором И Граничные случаи

  tcase_add_test(tc, test_memset_zero_length);
  tcase_add_test(tc, test_memset_null_ptr);
  tcase_add_test(tc, test_memset_null_byte);
  tcase_add_test(tc, test_memset_null_ptr_all);
  // Специальные значения символов
  tcase_add_test(tc, test_memset_large_char);
  tcase_add_test(tc, test_memcpy_small_buffer);
  tcase_add_test(tc, test_memset_large_char2);
  tcase_add_test(tc, test_memset_negative_char);
  tcase_add_test(tc, test_memset_binary_data);

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
  Suite *s = memory_suite();
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
