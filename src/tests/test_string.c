#include <check.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wchar.h>

#include "../s21_string.h"

////////////////////////////////////////////
//                                        //
//              s21_strncat               //
//                                        //
////////////////////////////////////////////

START_TEST(test_strncat_basic) {
  char dest[20] = "Hello";
  const char *src = ", world!";
  char expected[20] = "Hello";
  strncat(expected, src, 5);
  s21_strncat(dest, src, 5);
  ck_assert_str_eq(dest, expected);  // проверка базового добавления
}
END_TEST

START_TEST(test_strncat_full_copy) {
  char dest[20] = "Hello";
  const char *src = ", world!";
  char expected[20] = "Hello";
  strncat(expected, src, strlen(src));
  s21_strncat(dest, src, strlen(src));
  ck_assert_str_eq(dest, expected);  // проверка полного копирования
}
END_TEST

START_TEST(test_strncat_empty_dest) {
  char dest[20] = "";
  const char *src = "Hello, world!";
  char expected[20] = "";
  strncat(expected, src, 13);
  s21_strncat(dest, src, 13);
  ck_assert_str_eq(dest, expected);  // пустая строка dest
}
END_TEST

START_TEST(test_strncat_empty_src) {
  char dest[20] = "Hello, world!";
  const char *src = "";
  char expected[20] = "Hello, world!";
  strncat(expected, src, 10);
  s21_strncat(dest, src, 10);
  ck_assert_str_eq(dest, expected);  // пустая строка src
}
END_TEST

START_TEST(test_strncat_zero_length) {
  char dest[20] = "Hello";
  const char *src = ", world!";
  char expected[20] = "Hello";
  strncat(expected, src, 0);
  s21_strncat(dest, src, 0);
  ck_assert_str_eq(dest, expected);  // нулевая n
}
END_TEST

START_TEST(test_strncat_null_src) {
  char dest[20] = "Hello";
  ck_assert_ptr_eq(s21_strncat(dest, NULL, 5), NULL);  // NULL src
}
END_TEST

START_TEST(test_strncat_null_dest) {
  const char *src = "world";
  ck_assert_ptr_eq(s21_strncat(NULL, src, 5), NULL);  // NULL dest
}
END_TEST

START_TEST(test_strncat_small_buffer) {
  char dest[10] = "Hello";
  const char *src = ", world!";
  char expected[10] = "Hello";
  strncat(expected, src, 3);
  s21_strncat(dest, src, 3);
  ck_assert_str_eq(dest, expected);  // буфер меньше добавляемой строки
}
END_TEST

START_TEST(test_strncat_large_string) {
  char src[1024];
  char dest[2048] = "Start: ";
  char expected[2048] = "Start: ";

  memset(src, 'A', sizeof(src) - 1);
  src[sizeof(src) - 1] = '\0';

  strncat(expected, src, strlen(src));
  s21_strncat(dest, src, strlen(src));
  ck_assert_str_eq(dest, expected);  // длинная строка
}
END_TEST

START_TEST(test_strncat_unicode) {
  char dest[50] = "Привет";
  const char *src = ", мир!";
  char expected[50] = "Привет";
  strncat(expected, src, strlen(src));
  s21_strncat(dest, src, strlen(src));
  ck_assert_str_eq(dest, expected);  // Unicode
}
END_TEST

////////////////////////////////////////////
//                                        //
//               s21_strchr               //
//                                        //
////////////////////////////////////////////

START_TEST(test_strchr_basic) {
  const char *str = "Hello, world!";
  ck_assert_ptr_eq(s21_strchr(str, 'o'), strchr(str, 'o'));  // поиск символа
}
END_TEST

START_TEST(test_strchr_not_found) {
  const char *str = "Hello, world!";
  ck_assert_ptr_eq(s21_strchr(str, 'z'), strchr(str, 'z'));  // символа нет
}
END_TEST

START_TEST(test_strchr_null_char) {
  const char *str = "Hello\0world";
  ck_assert_ptr_eq(s21_strchr(str, '\0'), strchr(str, '\0'));  // поиск '\0'
}
END_TEST

START_TEST(test_strchr_null_char_end) {
  const char *str = "Hello, world";
  ck_assert_ptr_eq(s21_strchr(str, '\0'),
                   strchr(str, '\0'));  // поиск '\0' в конце
}
END_TEST

START_TEST(test_strchr_null_ptr) {
  ck_assert_ptr_eq(s21_strchr(NULL, 'a'), NULL);  // NULL строка
}
END_TEST

START_TEST(test_strchr_empty_str) {
  const char *str = "";
  ck_assert_ptr_eq(s21_strchr(str, 'o'), strchr(str, 'o'));  // пустая строка
}
END_TEST

START_TEST(test_strchr_large_char) {
  const char *str = "Hello";
  ck_assert_ptr_eq(s21_strchr(str, 1024), strchr(str, 1024));  // символ > 255
}
END_TEST

START_TEST(test_strchr_negative_char) {
  const char *str = "Hello";
  int c = 'e' * -1;
  ck_assert_ptr_eq(s21_strchr(str, c), strchr(str, c));  // отрицательный символ
}
END_TEST

START_TEST(test_strchr_unicode) {
  const char *str = "Привет";
  wchar_t wc = L'и';
  int c = (int)wc;
  ck_assert_ptr_eq(s21_strchr(str, c), strchr(str, c));  // Unicode
}
END_TEST

START_TEST(test_strchr_long_string) {
  char long_str[1024];
  memset(long_str, 'A', sizeof(long_str) - 1);
  long_str[sizeof(long_str) - 1] = 'B';

  ck_assert_ptr_eq(s21_strchr(long_str, 'B'),
                   strchr(long_str, 'B'));  // поиск в длинной строке
}
END_TEST

////////////////////////////////////////////
//                                        //
//              s21_strncmp               //
//                                        //
////////////////////////////////////////////

START_TEST(test_strncmp_equal) {
  const char *str1 = "Hello";
  const char *str2 = "Hello";
  ck_assert_int_eq(s21_strncmp(str1, str2, 5),
                   strncmp(str1, str2, 5));  // строки равны
}
END_TEST

START_TEST(test_strncmp_equal_2) {
  const char *str1 = "Hello";
  const char *str2 = "Hello";
  ck_assert_int_eq(s21_strncmp(str1, str2, 10),
                   strncmp(str1, str2, 10));  // строки равны, но короче n
}
END_TEST

START_TEST(test_strncmp_partially_equal) {
  const char *str1 = "Hello";
  const char *str2 = "Hello, world!";
  ck_assert_int_eq(
      s21_strncmp(str1, str2, 5),
      strncmp(str1, str2,
              5));  // строки равны на n символов, дальше различаются
}
END_TEST

START_TEST(test_strncmp_less) {
  const char *str1 = "Hello";
  const char *str2 = "Hellz";
  ck_assert_int_eq(s21_strncmp(str1, str2, 5),
                   strncmp(str1, str2, 5));  // s1 < s2
}
END_TEST

START_TEST(test_strncmp_less_2) {
  const char *str1 = "Hello";
  const char *str2 = "Hello, world!";
  ck_assert_int_eq(s21_strncmp(str1, str2, 10),
                   strncmp(str1, str2, 10));  // s1 < s2
}
END_TEST

START_TEST(test_strncmp_less_3) {
  const char *str1 = "cat";
  const char *str2 = "dog";
  ck_assert_int_eq(s21_strncmp(str1, str2, 3),
                   strncmp(str1, str2, 3));  // s1 < s2
}
END_TEST

START_TEST(test_strncmp_greater) {
  const char *str1 = "Hellz";
  const char *str2 = "Hello";
  ck_assert_int_eq(s21_strncmp(str1, str2, 5),
                   strncmp(str1, str2, 5));  // s1 > s2
}
END_TEST

START_TEST(test_strncmp_greater_2) {
  const char *str1 = "computer";
  const char *str2 = "compute";
  ck_assert_int_eq(s21_strncmp(str1, str2, 8),
                   strncmp(str1, str2, 8));  // сравнение с '\0'
}
END_TEST

START_TEST(test_strncmp_greater_3) {
  const char *str1 = "Hello, world!";
  const char *str2 = "Hel";
  ck_assert_int_eq(s21_strncmp(str1, str2, 10),
                   strncmp(str1, str2, 10));  // вторая строка короче n
}
END_TEST

START_TEST(test_strncmp_partial) {
  const char *str1 = "Hello";
  const char *str2 = "Hellz";
  ck_assert_int_eq(s21_strncmp(str1, str2, 4),
                   strncmp(str1, str2, 4));  // частичное сравнение
}
END_TEST

START_TEST(test_strncmp_zero_length) {
  const char *str1 = "Hello";
  const char *str2 = "World";
  ck_assert_int_eq(s21_strncmp(str1, str2, 0),
                   strncmp(str1, str2, 0));  // нулевая длина
}
END_TEST

START_TEST(test_strncmp_empty_str1) {
  const char *str1 = "";
  const char *str2 = "World";
  ck_assert_int_eq(s21_strncmp(str1, str2, 3),
                   strncmp(str1, str2, 3));  // пустая первая строка
}
END_TEST

START_TEST(test_strncmp_empty_str2) {
  const char *str1 = "Hello";
  const char *str2 = "";
  ck_assert_int_eq(s21_strncmp(str1, str2, 3),
                   strncmp(str1, str2, 3));  // пустая вторая строка
}
END_TEST

START_TEST(test_strncmp_null_ptr) {
  ck_assert_int_eq(s21_strncmp(NULL, "Hello", 5),
                   0);  // NULL str
}
END_TEST

START_TEST(test_strncmp_unicode) {
  const char *str1 = "Привет";
  const char *str2 = "Привет";
  ck_assert_int_eq(s21_strncmp(str1, str2, 6),
                   strncmp(str1, str2, 6));  // Unicode
}
END_TEST

START_TEST(test_strncmp_large_string) {
  char str1[1024], str2[1024];
  memset(str1, 'A', sizeof(str1));
  memset(str2, 'A', sizeof(str2));
  str1[1023] = 'B';

  ck_assert_int_eq(s21_strncmp(str1, str2, sizeof(str1)),
                   strncmp(str1, str2, sizeof(str1)));  // очень длинные строки
}
END_TEST

////////////////////////////////////////////
//                                        //
//              s21_strncpy               //
//                                        //
////////////////////////////////////////////

START_TEST(test_strncpy_basic) {
  char dest[20] = {0};
  const char *src = "Hello";
  char expected[20] = {0};
  strncpy(expected, src, 5);
  s21_strncpy(dest, src, 5);
  ck_assert_str_eq(dest, expected);  // базовое копирование
}
END_TEST

START_TEST(test_strncpy_basic_2) {
  char dest[20] = {0};
  const char *src = "Hello";
  char expected[20] = {0};
  strncpy(expected, src, 10);
  s21_strncpy(dest, src, 10);
  ck_assert_str_eq(dest, expected);  // n больше чем src
}
END_TEST

START_TEST(test_strncpy_partial) {
  char dest[20] = {0};
  const char *src = "Hello, world!";
  char expected[20] = {0};
  strncpy(expected, src, 5);
  s21_strncpy(dest, src, 5);
  ck_assert_str_eq(dest, expected);  // частичное копирование
}
END_TEST

START_TEST(test_strncpy_zero_length) {
  char dest[20] = "Original";
  const char *src = "Hello";
  char expected[20] = "Original";

  size_t zero_length = 0;
  strncpy(expected, src, zero_length);
  s21_strncpy(dest, src, zero_length);
  ck_assert_str_eq(dest, expected);  // нулевая длина
}
END_TEST

START_TEST(test_strncpy_empty_srs) {
  char dest[20] = "Original";
  const char *src = "";
  char expected[20] = "Original";
  strncpy(expected, src, 10);
  s21_strncpy(dest, src, 10);
  ck_assert_str_eq(dest, expected);  // пустой src
}
END_TEST

START_TEST(test_strncpy_null_src) {
  char dest[20] = {0};
  ck_assert_ptr_eq(s21_strncpy(dest, NULL, 5), NULL);  // NULL source
}
END_TEST

START_TEST(test_strncpy_null_dest) {
  const char *src = "Hello";
  ck_assert_ptr_eq(s21_strncpy(NULL, src, 5), NULL);  // NULL destination
}
END_TEST

START_TEST(test_strncpy_small_buffer) {
  char dest[5] = {0};
  const char *src = "Hello, world!";
  char expected[5] = {0};
  strncpy(expected, src, sizeof(dest));
  s21_strncpy(dest, src, sizeof(dest));
  ck_assert_mem_eq(dest, expected, sizeof(dest));  // буфер меньше источника
}
END_TEST

START_TEST(test_strncpy_unicode) {
  char dest[20] = {0};
  const char *src = "Привет";
  char expected[20] = {0};
  strncpy(expected, src, 6);
  s21_strncpy(dest, src, 6);
  ck_assert_mem_eq(dest, expected, 6);  // Unicode символы
}
END_TEST

START_TEST(test_strncpy_large_string) {
  char src[1024];
  char dest[1024];
  char expected[1024];

  memset(src, 'A', sizeof(src) - 1);
  src[sizeof(src) - 1] = '\0';

  strncpy(expected, src, sizeof(src));
  s21_strncpy(dest, src, sizeof(src));
  ck_assert_mem_eq(dest, expected, sizeof(src));  // длинная строка
}
END_TEST

////////////////////////////////////////////
//                                        //
//              s21_strcspn               //
//                                        //
////////////////////////////////////////////

START_TEST(test_strcspn_basic) {
  const char *str1 = "Hello, world!";
  const char *str2 = " ,!";
  ck_assert_int_eq(s21_strcspn(str1, str2),
                   strcspn(str1, str2));  // базовый случай
}
END_TEST

START_TEST(test_strcspn_register) {
  const char *str1 = "Hello, wOrld!";
  const char *str2 = "O";
  ck_assert_int_eq(s21_strcspn(str1, str2), strcspn(str1, str2));  // регистр
}
END_TEST

START_TEST(test_strcspn_no_match) {
  const char *str1 = "Hello";
  const char *str2 = "xyz";
  ck_assert_int_eq(s21_strcspn(str1, str2),
                   strcspn(str1, str2));  // нет совпадений
}
END_TEST

START_TEST(test_strcspn_first_char) {
  const char *str1 = "Hello";
  const char *str2 = "Hl";
  ck_assert_int_eq(s21_strcspn(str1, str2),
                   strcspn(str1, str2));  // первый символ
}
END_TEST

START_TEST(test_strcspn_null_ptr) {
  ck_assert_int_eq(s21_strcspn(NULL, "abc"),
                   0);  // NULL указатель
}
END_TEST

START_TEST(test_strcspn_empty_str2) {
  const char *str1 = "Hello";
  const char *str2 = "";
  ck_assert_int_eq(s21_strcspn(str1, str2),
                   strcspn(str1, str2));  // пустая str2
}
END_TEST
START_TEST(test_strcspn_empty_str1) {
  const char *str1 = "";
  const char *str2 = " ,!";
  ck_assert_int_eq(s21_strcspn(str1, str2),
                   strcspn(str1, str2));  // пустая str1
}
END_TEST

START_TEST(test_strcspn_unicode) {
  const char *str1 = "Привет мир";
  const char *str2 = "мир";
  ck_assert_int_eq(s21_strcspn(str1, str2),
                   strcspn(str1, str2));  // Unicode символы
}
END_TEST

START_TEST(test_strcspn_long_string) {
  char str1[1024];
  const char *str2 = "X";

  memset(str1, 'A', sizeof(str1) - 1);
  str1[sizeof(str1) - 1] = 'X';
  str1[sizeof(str1) - 1] = '\0';

  ck_assert_int_eq(s21_strcspn(str1, str2),
                   strcspn(str1, str2));  // длинная строка
}
END_TEST

////////////////////////////////////////////
//                                        //
//              s21_strlen                //
//                                        //
////////////////////////////////////////////

START_TEST(test_strlen_basic) {
  const char *str = "Hello";
  ck_assert_int_eq(s21_strlen(str), strlen(str));  // базовая строка
}
END_TEST

START_TEST(test_strlen_numbers) {
  const char *str = "Hello 12345";
  ck_assert_int_eq(s21_strlen(str), strlen(str));  // базовая строка
}
END_TEST

START_TEST(test_strlen_one_char) {
  const char *str = "H";
  ck_assert_int_eq(s21_strlen(str), strlen(str));  // базовая строка
}
END_TEST

START_TEST(test_strlen_empty) {
  const char *str = "";
  ck_assert_int_eq(s21_strlen(str), strlen(str));  // пустая строка
}
END_TEST

START_TEST(test_strlen_null_ptr) {
  ck_assert_int_eq(s21_strlen(NULL), 0);  // NULL указатель
}
END_TEST

START_TEST(test_strlen_unicode) {
  const char *str = "Привет";
  ck_assert_int_eq(s21_strlen(str), strlen(str));  // Unicode символы
}
END_TEST

START_TEST(test_strlen_long_string) {
  char long_str[1024];
  memset(long_str, 'A', sizeof(long_str) - 1);
  long_str[sizeof(long_str) - 1] = '\0';

  ck_assert_int_eq(s21_strlen(long_str),
                   strlen(long_str));  // длинная строка
}
END_TEST

////////////////////////////////////////////
//                                        //
//              s21_strpbrk               //
//                                        //
////////////////////////////////////////////

START_TEST(test_strpbrk_basic) {
  const char *str1 = "Hello, world!";
  const char *str2 = " ,!";
  ck_assert_ptr_eq(s21_strpbrk(str1, str2),
                   strpbrk(str1, str2));  // базовый случай
}
END_TEST

START_TEST(test_strpbrk_first_char) {
  const char *str1 = "Hello, world!";
  const char *str2 = "H";
  ck_assert_ptr_eq(s21_strpbrk(str1, str2),
                   strpbrk(str1, str2));  // совпадение - первый символ
}
END_TEST

START_TEST(test_strpbrk_last_char) {
  const char *str1 = "Hello, world!";
  const char *str2 = "!";
  ck_assert_ptr_eq(s21_strpbrk(str1, str2),
                   strpbrk(str1, str2));  // совпадение - последний символ
}
END_TEST

START_TEST(test_strpbrk_not_found) {
  const char *str1 = "Hello";
  const char *str2 = "xyz";
  ck_assert_ptr_eq(s21_strpbrk(str1, str2),
                   strpbrk(str1, str2));  // нет совпадений
}
END_TEST

START_TEST(test_strpbrk_null_ptr) {
  ck_assert_ptr_eq(s21_strpbrk(NULL, "abc"),
                   NULL);  // NULL str1
}
END_TEST

START_TEST(test_strpbrk_symbol) {
  const char *str1 = "&^*$#";
  const char *str2 = "#";
  ck_assert_ptr_eq(s21_strpbrk(str1, str2),
                   strpbrk(str1, str2));  // базовый случай
}
END_TEST

START_TEST(test_strpbrk_unicode) {
  const char *str1 = "Привет мир";
  const char *str2 = " ";
  ck_assert_ptr_eq(s21_strpbrk(str1, str2),
                   strpbrk(str1, str2));  // Unicode символы
}
END_TEST

START_TEST(test_strpbrk_long_string) {
  char str1[1024];
  const char *str2 = "X";

  memset(str1, 'A', sizeof(str1) - 1);
  str1[sizeof(str1) - 2] = 'X';
  str1[sizeof(str1) - 1] = '\0';

  ck_assert_ptr_eq(s21_strpbrk(str1, str2),
                   strpbrk(str1, str2));  // длинная строка
}
END_TEST

////////////////////////////////////////////
//                                        //
//              s21_strrchr               //
//                                        //
////////////////////////////////////////////

START_TEST(test_strrchr_basic) {
  const char *str = "Hello, world!";
  ck_assert_ptr_eq(s21_strrchr(str, 'o'), strrchr(str, 'o'));  // базовый поиск
}
END_TEST

START_TEST(test_strrchr_not_found) {
  const char *str = "Hello";
  ck_assert_ptr_eq(s21_strrchr(str, 'z'),
                   strrchr(str, 'z'));  // символ не найден
}
END_TEST

START_TEST(test_strrchr_null_char) {
  const char *str = "Hello\0world";
  ck_assert_ptr_eq(s21_strrchr(str, '\0'), strrchr(str, '\0'));  // Поиск '\0'
}
END_TEST

START_TEST(test_strrchr_null_ptr) {
  ck_assert_ptr_eq(s21_strrchr(NULL, 'a'), NULL);  // NULL указатель
}
END_TEST

START_TEST(test_strrchr_empty_str) {
  const char *str = "";
  ck_assert_ptr_eq(s21_strrchr(str, 'y'), strrchr(str, 'y'));  // пустая str
}
END_TEST

START_TEST(test_strrchr_unicode) {
  const char *str = "Прииивет";
  wchar_t wc = L'и';
  int c = (int)wc;
  ck_assert_ptr_eq(s21_strrchr(str, c), strrchr(str, c));  // Unicode символ
}
END_TEST

START_TEST(test_strrchr_long_string) {
  char str[1024];
  memset(str, 'A', sizeof(str));
  str[sizeof(str) - 2] = 'B';
  str[sizeof(str) - 1] = '\0';

  ck_assert_ptr_eq(s21_strrchr(str, 'B'), strrchr(str, 'B'));  // длинная строка
}
END_TEST

////////////////////////////////////////////
//                                        //
//              s21_strstr                //
//                                        //
////////////////////////////////////////////

START_TEST(test_strstr_basic) {
  const char *haystack = "Hello, world!";
  const char *needle = "world";
  ck_assert_ptr_eq(s21_strstr(haystack, needle),
                   strstr(haystack, needle));  // базовый поиск
}
END_TEST

START_TEST(test_strstr_basic_2) {
  const char *haystack = "Hello, world!";
  const char *needle = "Hello, world!";
  ck_assert_ptr_eq(s21_strstr(haystack, needle),
                   strstr(haystack, needle));  // полностью одинаковые строки
}
END_TEST

START_TEST(test_strstr_basic_3) {
  const char *haystack = "peace, peaceful";
  const char *needle = "peaceful";
  ck_assert_ptr_eq(s21_strstr(haystack, needle),
                   strstr(haystack, needle));  // подстрока начинается схоже
}
END_TEST

START_TEST(test_strstr_basic_register) {
  const char *haystack = "Hello, world!";
  const char *needle = "World";
  ck_assert_ptr_eq(s21_strstr(haystack, needle),
                   strstr(haystack, needle));  // чувствительность к регистру
}
END_TEST

START_TEST(test_strstr_not_found) {
  const char *haystack = "Hello";
  const char *needle = "world";
  ck_assert_ptr_eq(s21_strstr(haystack, needle),
                   strstr(haystack, needle));  // подстрока не найдена
}
END_TEST

START_TEST(test_strstr_empty_needle) {
  const char *haystack = "Hello";
  const char *needle = "";
  ck_assert_ptr_eq(s21_strstr(haystack, needle),
                   strstr(haystack, needle));  // пустая подстрока
}
END_TEST

START_TEST(test_strstr_NULL_needle) {
  const char *haystack = "Hello";
  const char *needle = NULL;
  ck_assert_ptr_eq(s21_strstr(haystack, needle),
                   NULL);  // NULL подстрока
}
END_TEST

START_TEST(test_strstr_null_ptr) {
  ck_assert_ptr_eq(s21_strstr(NULL, "abc"),
                   NULL);  // NULL haystack
}
END_TEST

START_TEST(test_strstr_unicode) {
  const char *haystack = "Привет мираж";
  const char *needle = "мир";
  ck_assert_ptr_eq(s21_strstr(haystack, needle),
                   strstr(haystack, needle));  // Unicode символы
}
END_TEST

START_TEST(test_strstr_long_string) {
  char haystack[1024];
  const char *needle = "XYZ";

  memset(haystack, 'A', sizeof(haystack) - 4);
  strcpy(haystack + sizeof(haystack) - 4, "XYZ");

  ck_assert_ptr_eq(s21_strstr(haystack, needle),
                   strstr(haystack, needle));  // длинная строка
}
END_TEST

////////////////////////////////////////////
//                                        //
//              s21_strtok                //
//                                        //
////////////////////////////////////////////

START_TEST(test_strtok_basic) {
  char str[] = "Hello, world!";
  char str2[] = "Hello, world!";
  const char *delim = " ,!";
  char *token = s21_strtok(str, delim);
  char *expected = strtok(str2, delim);
  while (token != NULL && expected != NULL) {
    ck_assert_str_eq(token, expected);
    token = s21_strtok(NULL, delim);
    expected = strtok(NULL, delim);
  }
  ck_assert_ptr_eq(token, expected);  // базовая работа
}
END_TEST

START_TEST(test_strtok_basic_2) {
  char str[] = "Hello,       world!";
  char str2[] = "Hello,       world!";
  const char *delim = " ,!";
  char *token = s21_strtok(str, delim);
  char *expected = strtok(str2, delim);
  while (token != NULL && expected != NULL) {
    ck_assert_str_eq(token, expected);
    token = s21_strtok(NULL, delim);
    expected = strtok(NULL, delim);
  }
  ck_assert_ptr_eq(token,
                   expected);  // базовая работа, много разделителей подряд
}
END_TEST

START_TEST(test_strtok_basic_3) {
  char str[] = "Hello, world! It's my project!!!";
  char str2[] = "Hello, world! It's my project!!!";
  const char *delim = " ,!";
  char *token = s21_strtok(str, delim);
  char *expected = strtok(str2, delim);
  while (token != NULL && expected != NULL) {
    ck_assert_str_eq(token, expected);
    token = s21_strtok(NULL, delim);
    expected = strtok(NULL, delim);
  }
  ck_assert_ptr_eq(token,
                   expected);  // базовая работа, несколько разделителей в конце
}
END_TEST

START_TEST(test_strtok_basic_4) {
  char str[] = "!!!!Hello, world!";
  char str2[] = "!!!!Hello, world!";
  const char *delim = " ,!";
  char *token = s21_strtok(str, delim);
  char *expected = strtok(str2, delim);
  while (token != NULL && expected != NULL) {
    ck_assert_str_eq(token, expected);
    token = s21_strtok(NULL, delim);
    expected = strtok(NULL, delim);
  }
  ck_assert_ptr_eq(
      token,
      expected);  // базовая работа, несколько разделителей в начале
}
END_TEST

START_TEST(test_strtok_no_delim) {
  char str[] = "Hello, world!";
  char str2[] = "Hello, world!";
  const char *delim = "?8";
  char *token = s21_strtok(str, delim);
  char *expected = strtok(str2, delim);
  while (token != NULL && expected != NULL) {
    ck_assert_str_eq(token, expected);
    token = s21_strtok(NULL, delim);
    expected = strtok(NULL, delim);
  }
  ck_assert_ptr_eq(token, expected);  // нет разделителей
}
END_TEST

START_TEST(test_strtok_basic_register) {
  char str[] = "Hello, world!";
  char str2[] = "Hello, world!";
  const char *delim = "h";
  char *token = s21_strtok(str, delim);
  char *expected = strtok(str2, delim);
  while (token != NULL && expected != NULL) {
    ck_assert_str_eq(token, expected);
    token = s21_strtok(NULL, delim);
    expected = strtok(NULL, delim);
  }
  ck_assert_ptr_eq(token, expected);  // регистр
}
END_TEST

START_TEST(test_strtok_basic_whitespace) {
  char str[] = "Hello, world! This is a cat.";
  char str2[] = "Hello, world! This is a cat.";
  const char *delim = " ";
  char *token = s21_strtok(str, delim);
  char *expected = strtok(str2, delim);
  while (token != NULL && expected != NULL) {
    ck_assert_str_eq(token, expected);
    token = s21_strtok(NULL, delim);
    expected = strtok(NULL, delim);
  }
  ck_assert_ptr_eq(token, expected);  // базовая работа, просто пробел
}
END_TEST

START_TEST(test_strtok_null_str) {
  const char *delim = " ,!";
  char *token = s21_strtok(NULL, delim);
  ck_assert_ptr_eq(token, NULL);  // изначально NULL str
}
END_TEST

START_TEST(test_strtok_empty_delim) {
  char str[] = "Hello";
  const char *delim = "";
  char *token = s21_strtok(str, delim);
  char *expected = strtok(str, delim);
  ck_assert_ptr_eq(token, expected);  // пустые разделители
}
END_TEST

START_TEST(test_strtok_null_ptr) {
  ck_assert_ptr_eq(s21_strtok(NULL, NULL),
                   NULL);  // NULL параметры
}
END_TEST

START_TEST(test_strtok_unicode) {
  char str[] = "Привет,мир!";
  char str2[] = "Привет,мир!";
  const char *delim = ",!";
  char *token = s21_strtok(str, delim);
  char *expected = strtok(str2, delim);

  ck_assert_str_eq(token, expected);  // Unicode символы

  token = s21_strtok(NULL, delim);
  expected = strtok(NULL, delim);
  ck_assert_str_eq(token, expected);
}
END_TEST

START_TEST(test_strtok_long_string) {
  char str[1024];
  const char *delim = "|";

  memset(str, 'A', sizeof(str) - 2);
  str[sizeof(str) - 2] = '|';
  str[sizeof(str) - 1] = '\0';

  char *token = s21_strtok(str, delim);
  char *expected = strtok(str, delim);

  ck_assert_str_eq(token, expected);  // длинная строка
}
END_TEST

////////////////////////////////////////////
//                                        //
//               Test Suite               //
//                                        //
////////////////////////////////////////////

Suite *sscanf_suite(void) {
  Suite *s = suite_create("s21_string");
  TCase *tc = tcase_create("Core");

  // s21_strncat
  tcase_add_test(tc, test_strncat_basic);
  tcase_add_test(tc, test_strncat_full_copy);
  tcase_add_test(tc, test_strncat_empty_dest);
  tcase_add_test(tc, test_strncat_empty_src);
  tcase_add_test(tc, test_strncat_zero_length);
  tcase_add_test(tc, test_strncat_null_src);
  tcase_add_test(tc, test_strncat_null_dest);
  tcase_add_test(tc, test_strncat_small_buffer);
  tcase_add_test(tc, test_strncat_large_string);
  tcase_add_test(tc, test_strncat_unicode);

  // s21_strchr
  tcase_add_test(tc, test_strchr_basic);
  tcase_add_test(tc, test_strchr_not_found);
  tcase_add_test(tc, test_strchr_null_char);
  tcase_add_test(tc, test_strchr_null_char_end);
  tcase_add_test(tc, test_strchr_null_ptr);
  tcase_add_test(tc, test_strchr_empty_str);
  tcase_add_test(tc, test_strchr_large_char);
  tcase_add_test(tc, test_strchr_negative_char);
  tcase_add_test(tc, test_strchr_unicode);
  tcase_add_test(tc, test_strchr_long_string);

  // s21_strncmp
  tcase_add_test(tc, test_strncmp_equal);
  tcase_add_test(tc, test_strncmp_equal_2);
  tcase_add_test(tc, test_strncmp_partially_equal);
  tcase_add_test(tc, test_strncmp_less);
  tcase_add_test(tc, test_strncmp_less_2);
  tcase_add_test(tc, test_strncmp_less_3);
  tcase_add_test(tc, test_strncmp_greater);
  tcase_add_test(tc, test_strncmp_greater_2);
  tcase_add_test(tc, test_strncmp_greater_3);
  tcase_add_test(tc, test_strncmp_partial);
  tcase_add_test(tc, test_strncmp_zero_length);
  tcase_add_test(tc, test_strncmp_empty_str1);
  tcase_add_test(tc, test_strncmp_empty_str2);
  tcase_add_test(tc, test_strncmp_null_ptr);
  tcase_add_test(tc, test_strncmp_unicode);
  tcase_add_test(tc, test_strncmp_large_string);

  // s21_strncpy
  tcase_add_test(tc, test_strncpy_basic);
  tcase_add_test(tc, test_strncpy_basic_2);
  tcase_add_test(tc, test_strncpy_partial);
  tcase_add_test(tc, test_strncpy_zero_length);
  tcase_add_test(tc, test_strncpy_empty_srs);
  tcase_add_test(tc, test_strncpy_null_src);
  tcase_add_test(tc, test_strncpy_null_dest);
  tcase_add_test(tc, test_strncpy_small_buffer);
  tcase_add_test(tc, test_strncpy_unicode);
  tcase_add_test(tc, test_strncpy_large_string);

  // s21_strcspn
  tcase_add_test(tc, test_strcspn_basic);
  tcase_add_test(tc, test_strcspn_register);
  tcase_add_test(tc, test_strcspn_no_match);
  tcase_add_test(tc, test_strcspn_first_char);
  tcase_add_test(tc, test_strcspn_null_ptr);
  tcase_add_test(tc, test_strcspn_empty_str2);
  tcase_add_test(tc, test_strcspn_empty_str1);
  tcase_add_test(tc, test_strcspn_unicode);
  tcase_add_test(tc, test_strcspn_long_string);

  // s21_strlen
  tcase_add_test(tc, test_strlen_basic);
  tcase_add_test(tc, test_strlen_numbers);
  tcase_add_test(tc, test_strlen_one_char);
  tcase_add_test(tc, test_strlen_empty);
  tcase_add_test(tc, test_strlen_null_ptr);
  tcase_add_test(tc, test_strlen_unicode);
  tcase_add_test(tc, test_strlen_long_string);

  // s21_strpbrk
  tcase_add_test(tc, test_strpbrk_basic);
  tcase_add_test(tc, test_strpbrk_first_char);
  tcase_add_test(tc, test_strpbrk_last_char);
  tcase_add_test(tc, test_strpbrk_not_found);
  tcase_add_test(tc, test_strpbrk_null_ptr);
  tcase_add_test(tc, test_strpbrk_symbol);
  tcase_add_test(tc, test_strpbrk_unicode);
  tcase_add_test(tc, test_strpbrk_long_string);

  // s21_strrchr
  tcase_add_test(tc, test_strrchr_basic);
  tcase_add_test(tc, test_strrchr_not_found);
  tcase_add_test(tc, test_strrchr_null_char);
  tcase_add_test(tc, test_strrchr_null_ptr);
  tcase_add_test(tc, test_strrchr_empty_str);
  tcase_add_test(tc, test_strrchr_unicode);
  tcase_add_test(tc, test_strrchr_long_string);

  // s21_strstr
  tcase_add_test(tc, test_strstr_basic);
  tcase_add_test(tc, test_strstr_basic_2);
  tcase_add_test(tc, test_strstr_basic_3);
  tcase_add_test(tc, test_strstr_basic_register);
  tcase_add_test(tc, test_strstr_not_found);
  tcase_add_test(tc, test_strstr_empty_needle);
  tcase_add_test(tc, test_strstr_NULL_needle);
  tcase_add_test(tc, test_strstr_null_ptr);
  tcase_add_test(tc, test_strstr_unicode);
  tcase_add_test(tc, test_strstr_long_string);

  // s21_strtok
  tcase_add_test(tc, test_strtok_basic);
  tcase_add_test(tc, test_strtok_basic_2);
  tcase_add_test(tc, test_strtok_basic_3);
  tcase_add_test(tc, test_strtok_basic_4);
  tcase_add_test(tc, test_strtok_no_delim);
  tcase_add_test(tc, test_strtok_basic_register);
  tcase_add_test(tc, test_strtok_basic_whitespace);
  tcase_add_test(tc, test_strtok_null_str);
  tcase_add_test(tc, test_strtok_empty_delim);
  tcase_add_test(tc, test_strtok_null_ptr);
  tcase_add_test(tc, test_strtok_unicode);
  tcase_add_test(tc, test_strtok_long_string);

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