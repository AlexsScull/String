#include <check.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wchar.h>

#include "../include/s21_string.h"

////////////////////////////////////////////
//                                        //
//              s21_strncat               //
//                                        //
////////////////////////////////////////////

// Основные случаи работы
START_TEST(test_strncat_basic) {
  char dest[20] = "Hello";
  const char *src = ", world!";
  char expected[20] = "Hello";
  strncat(expected, src, 5);
  s21_strncat(dest, src, 5);
  ck_assert_str_eq(dest, expected);  // Проверка базового добавления
}

START_TEST(test_strncat_full_copy) {
  char dest[20] = "Hello";
  const char *src = ", world!";
  char expected[20] = "Hello";
  strncat(expected, src, strlen(src));
  s21_strncat(dest, src, strlen(src));
  ck_assert_str_eq(dest, expected);  // Проверка полного копирования
}

START_TEST(test_strncat_empty_dest) {
  char dest[20] = "";
  const char *src = "Hello, world!";
  char expected[20] = "";
  strncat(expected, src, 13);
  s21_strncat(dest, src, 13);
  ck_assert_str_eq(dest, expected);  // Пустая строка dest
}

START_TEST(test_strncat_empty_src) {
  char dest[20] = "Hello, world!";
  const char *src = "";
  char expected[20] = "Hello, world!";
  strncat(expected, src, 10);
  s21_strncat(dest, src, 10);
  ck_assert_str_eq(dest, expected);  // Пустая строка src
}

START_TEST(test_strncat_zero_length) {
  char dest[20] = "Hello";
  const char *src = ", world!";
  char expected[20] = "Hello";
  strncat(expected, src, 0);
  s21_strncat(dest, src, 0);
  ck_assert_str_eq(dest, expected);  // Проверка нулевой длины
}

START_TEST(test_strncat_null_src) {
  char dest[20] = "Hello";
  ck_assert_ptr_eq(s21_strncat(dest, NULL, 5), NULL);  // NULL source
}

START_TEST(test_strncat_null_dest) {
  const char *src = "world";
  ck_assert_ptr_eq(s21_strncat(NULL, src, 5), NULL);  // NULL destination
}

START_TEST(test_strncat_small_buffer) {
  char dest[10] = "Hello";
  const char *src = ", world!";
  char expected[10] = "Hello";
  strncat(expected, src, 3);  // Ожидаем усечение
  s21_strncat(dest, src, 3);
  ck_assert_str_eq(dest, expected);  // Буфер меньше добавляемой строки
}

START_TEST(test_strncat_large_string) {
  char src[1024];
  char dest[2048] = "Start: ";
  char expected[2048] = "Start: ";

  memset(src, 'A', sizeof(src) - 1);
  src[sizeof(src) - 1] = '\0';

  strncat(expected, src, sizeof(src));
  s21_strncat(dest, src, sizeof(src));
  ck_assert_str_eq(dest, expected);  // Очень длинная строка
}

START_TEST(test_strncat_unicode) {
  char dest[50] = "Привет";
  const char *src = ", мир!";
  char expected[50] = "Привет";
  strncat(expected, src, strlen(src));
  s21_strncat(dest, src, strlen(src));
  ck_assert_str_eq(dest, expected);  // Unicode символы
}

////////////////////////////////////////////
//                                        //
//               s21_strchr               //
//                                        //
////////////////////////////////////////////

// Основные случаи работы
START_TEST(test_strchr_basic) {
  const char *str = "Hello, world!";
  ck_assert_ptr_eq(s21_strchr(str, 'o'), strchr(str, 'o'));  // Поиск символа
}

START_TEST(test_strchr_not_found) {
  const char *str = "Hello, world!";
  ck_assert_ptr_eq(s21_strchr(str, 'z'), strchr(str, 'z'));  // Символ не найден
}

START_TEST(test_strchr_null_char) {
  const char *str = "Hello\0world";
  ck_assert_ptr_eq(s21_strchr(str, '\0'),
                   strchr(str, '\0'));  // Поиск нуль-терминатора
}

START_TEST(test_strchr_null_char_end) {
  const char *str = "Hello, world";
  ck_assert_ptr_eq(s21_strchr(str, '\0'),
                   strchr(str, '\0'));  // Поиск нуль-терминатора в конце
}

START_TEST(test_strchr_null_ptr) {
  ck_assert_ptr_eq(s21_strchr(NULL, 'a'), NULL);  // NULL строка
}

START_TEST(test_strchr_empty_str) {
  const char *str = "";
  ck_assert_ptr_eq(s21_strchr(str, 'o'), strchr(str, 'o'));  // Пустая строка
}

START_TEST(test_strchr_large_char) {
  const char *str = "Hello";
  ck_assert_ptr_eq(s21_strchr(str, 1024), strchr(str, 1024));  // Символ > 255
}

START_TEST(test_strchr_negative_char) {
  const char *str = "Hello";
  int c = 'e' * -1;
  ck_assert_ptr_eq(s21_strchr(str, c), strchr(str, c));  // Отрицательный символ
}

START_TEST(test_strchr_unicode) {
  const char *str = "Привет";
  wchar_t wc = L'и';
  int c = (int)wc; 
  ck_assert_ptr_eq(s21_strchr(str, c), strchr(str, c));  // Unicode символ
}

START_TEST(test_strchr_long_string) {
  char long_str[1024];
  memset(long_str, 'A', sizeof(long_str) - 1);
  long_str[sizeof(long_str) - 1] = 'B';

  ck_assert_ptr_eq(s21_strchr(long_str, 'B'),
                   strchr(long_str, 'B'));  // Поиск в длинной строке
}

////////////////////////////////////////////
//                                        //
//              s21_strncmp               //
//                                        //
////////////////////////////////////////////

// Основные случаи работы
START_TEST(test_strncmp_equal) {
  const char *s1 = "Hello";
  const char *s2 = "Hello";
  ck_assert_int_eq(s21_strncmp(s1, s2, 5), strncmp(s1, s2, 5));  // Строки равны
}

START_TEST(test_strncmp_equal_2) {
  const char *s1 = "Hello";
  const char *s2 = "Hello";
  ck_assert_int_eq(s21_strncmp(s1, s2, 10), strncmp(s1, s2, 10));  // Строки равны, но короче n
}

START_TEST(test_strncmp_partially_equal) {
  const char *s1 = "Hello";
  const char *s2 = "Hello, world!";
  ck_assert_int_eq(s21_strncmp(s1, s2, 5), strncmp(s1, s2, 5));  // Строки равны на n символов, дальше различаются
}

START_TEST(test_strncmp_less) {
  const char *s1 = "Hello";
  const char *s2 = "Hellz";
  ck_assert_int_eq(s21_strncmp(s1, s2, 5), strncmp(s1, s2, 5));  // s1 < s2
}

START_TEST(test_strncmp_less_2) {
  const char *s1 = "Hello";
  const char *s2 = "Hello, world!";
  ck_assert_int_eq(s21_strncmp(s1, s2, 10), strncmp(s1, s2, 10));  // s1 < s2
}

START_TEST(test_strncmp_less_3) {
  const char *s1 = "cat";
  const char *s2 = "dog";
  ck_assert_int_eq(s21_strncmp(s1, s2, 3), strncmp(s1, s2, 3));  // s1 < s2
}

START_TEST(test_strncmp_greater) {
  const char *s1 = "Hellz";
  const char *s2 = "Hello";
  ck_assert_int_eq(s21_strncmp(s1, s2, 5), strncmp(s1, s2, 5));  // s1 > s2
}

START_TEST(test_strncmp_greater_2) {
  const char *s1 = "computer";
  const char *s2 = "compute";
  ck_assert_int_eq(s21_strncmp(s1, s2, 8), strncmp(s1, s2, 8));  // сравнение с '\0'
}

START_TEST(test_strncmp_greater_3) {
  const char *s1 = "Hello, world!";
  const char *s2 = "Hel";
  ck_assert_int_eq(s21_strncmp(s1, s2, 10), strncmp(s1, s2, 10));  // вторая строка короче n
}

START_TEST(test_strncmp_partial) {
  const char *s1 = "Hello";
  const char *s2 = "Hellz";
  ck_assert_int_eq(s21_strncmp(s1, s2, 4),
                   strncmp(s1, s2, 4));  // Частичное сравнение
}

START_TEST(test_strncmp_zero_length) {
  const char *s1 = "Hello";
  const char *s2 = "World";
  ck_assert_int_eq(s21_strncmp(s1, s2, 0),
                   strncmp(s1, s2, 0));  // Нулевая длина
}

START_TEST(test_strncmp_empty_str1) {
  const char *s1 = "";
  const char *s2 = "World";
  ck_assert_int_eq(s21_strncmp(s1, s2, 3),
                   strncmp(s1, s2, 3));  // Пустая первая строка
}

START_TEST(test_strncmp_empty_str2) {
  const char *s1 = "Hello";
  const char *s2 = "";
  ck_assert_int_eq(s21_strncmp(s1, s2, 3),
                   strncmp(s1, s2, 3));  // Пустая вторая строка
}

START_TEST(test_strncmp_null_ptr) {
  ck_assert_int_eq(s21_strncmp(NULL, "Hello", 5),
                   0);  // NULL указатель (ИЗМЕНЕНО)
}

START_TEST(test_strncmp_unicode) {
  const char *s1 = "Привет";
  const char *s2 = "Привет";
  ck_assert_int_eq(s21_strncmp(s1, s2, 6),
                   strncmp(s1, s2, 6));  // Unicode сравнение
}

START_TEST(test_strncmp_large_string) {
  char s1[1024], s2[1024];
  memset(s1, 'A', sizeof(s1));
  memset(s2, 'A', sizeof(s2));
  s1[1023] = 'B';

  ck_assert_int_eq(s21_strncmp(s1, s2, sizeof(s1)),
                   strncmp(s1, s2, sizeof(s1)));  // Очень длинные строки
}

////////////////////////////////////////////
//                                        //
//              s21_strncpy               //
//                                        //
////////////////////////////////////////////

// Основные случаи работы
START_TEST(test_strncpy_basic) {
  char dest[20];
  const char *src = "Hello";
  char expected[20];
  strncpy(expected, src, 5);
  s21_strncpy(dest, src, 5);
  ck_assert_str_eq(dest, expected);  // Базовое копирование
}

START_TEST(test_strncpy_basic_2) {
  char dest[20];
  const char *src = "Hello";
  char expected[20];
  strncpy(expected, src, 10);
  s21_strncpy(dest, src, 10);
  ck_assert_str_eq(dest, expected);  // n больше чем src
}

START_TEST(test_strncpy_partial) {
  char dest[20];
  const char *src = "Hello, world!";
  char expected[20];
  strncpy(expected, src, 5);
  s21_strncpy(dest, src, 5);
  ck_assert_str_eq(dest, expected);  // Частичное копирование
}

START_TEST(test_strncpy_zero_length) {
  char dest[20] = "Original";
  const char *src = "Hello";
  char expected[20] = "Original";
  strncpy(expected, src, 0);
  s21_strncpy(dest, src, 0);
  ck_assert_str_eq(dest, expected);  // Нулевая длина
}

START_TEST(test_strncpy_empty_srs) {
  char dest[20] = "Original";
  const char *src = "";
  char expected[20] = "Original";
  strncpy(expected, src, 10);
  s21_strncpy(dest, src, 10);
  ck_assert_str_eq(dest, expected);  // Пустой src
}

START_TEST(test_strncpy_null_src) {
  char dest[20];
  ck_assert_ptr_eq(s21_strncpy(dest, NULL, 5), NULL);  // NULL source
}

START_TEST(test_strncpy_null_dest) {
  const char *src = "Hello";
  ck_assert_ptr_eq(s21_strncpy(NULL, src, 5), NULL);  // NULL destination
}

START_TEST(test_strncpy_small_buffer) {
  char dest[5];
  const char *src = "Hello, world!";
  char expected[5];
  strncpy(expected, src, sizeof(dest));
  s21_strncpy(dest, src, sizeof(dest));
  ck_assert_mem_eq(dest, expected, sizeof(dest));  // Буфер меньше источника
}

START_TEST(test_strncpy_unicode) {
  char dest[20];
  const char *src = "Привет";
  char expected[20];
  strncpy(expected, src, 6);
  s21_strncpy(dest, src, 6);
  ck_assert_mem_eq(dest, expected, 6);  // Unicode символы
}

START_TEST(test_strncpy_large_string) {
  char src[1024];
  char dest[1024];
  char expected[1024];

  memset(src, 'A', sizeof(src) - 1);
  src[sizeof(src) - 1] = '\0';

  strncpy(expected, src, sizeof(src));
  s21_strncpy(dest, src, sizeof(src));
  ck_assert_mem_eq(dest, expected, sizeof(src));  // Очень длинная строка
}

////////////////////////////////////////////
//                                        //
//              s21_strcspn               //
//                                        //
////////////////////////////////////////////

// Основные случаи работы
START_TEST(test_strcspn_basic) {
  const char *str1 = "Hello, world!";
  const char *str2 = " ,!";
  ck_assert_int_eq(s21_strcspn(str1, str2),
                   strcspn(str1, str2));  // Базовый случай
}

START_TEST(test_strcspn_register) {
  const char *str1 = "Hello, wOrld!";
  const char *str2 = "O";
  ck_assert_int_eq(s21_strcspn(str1, str2),
                   strcspn(str1, str2));  // Регистр
}

START_TEST(test_strcspn_no_match) {
  const char *str1 = "Hello";
  const char *str2 = "xyz";
  ck_assert_int_eq(s21_strcspn(str1, str2),
                   strcspn(str1, str2));  // Нет совпадений
}

START_TEST(test_strcspn_first_char) {
  const char *str1 = "Hello";
  const char *str2 = "Hl";
  ck_assert_int_eq(s21_strcspn(str1, str2),
                   strcspn(str1, str2));  // Первый символ
}

START_TEST(test_strcspn_null_ptr) {
  ck_assert_int_eq(s21_strcspn(NULL, "abc"),
                   0);  // NULL указатель
}

START_TEST(test_strcspn_empty_str2) {
  const char *str1 = "Hello";
  const char *str2 = "";
  ck_assert_int_eq(s21_strcspn(str1, str2),
                   strcspn(str1, str2));  // Пустая строка str2
}
START_TEST(test_strcspn_empty_str1) {
  const char *str1 = "";
  const char *str2 = " ,!";
  ck_assert_int_eq(s21_strcspn(str1, str2),
                   strcspn(str1, str2));  // Пустая строка str1
}

START_TEST(test_strcspn_unicode) {
  const char *str1 = "Привет мир";
  const char *str2 = "мир";
  ck_assert_int_eq(s21_strcspn(str1, str2),
                   strcspn(str1, str2));  // Unicode символы
}

START_TEST(test_strcspn_long_string) {
  char str1[1024];
  const char *str2 = "X";

  memset(str1, 'A', sizeof(str1) - 1);
  str1[sizeof(str1) - 1] = 'X';

  ck_assert_int_eq(s21_strcspn(str1, str2),
                   strcspn(str1, str2));  // Очень длинная строка
}

////////////////////////////////////////////
//                                        //
//              s21_strlen                //
//                                        //
////////////////////////////////////////////

// Основные случаи работы
START_TEST(test_strlen_basic) {
  const char *str = "Hello";
  ck_assert_int_eq(s21_strlen(str), strlen(str));  // Базовая строка
}

START_TEST(test_strlen_numbers) {
  const char *str = "Hello 12345";
  ck_assert_int_eq(s21_strlen(str), strlen(str));  // Базовая строка
}

START_TEST(test_strlen_one_char) {
  const char *str = "H";
  ck_assert_int_eq(s21_strlen(str), strlen(str));  // Базовая строка
}

START_TEST(test_strlen_empty) {
  const char *str = "";
  ck_assert_int_eq(s21_strlen(str), strlen(str));  // Пустая строка
}

START_TEST(test_strlen_null_ptr) {
  ck_assert_int_eq(s21_strlen(NULL), 0);  // NULL указатель
}

START_TEST(test_strlen_unicode) {
  const char *str = "Привет";
  ck_assert_int_eq(s21_strlen(str), strlen(str));  // Unicode символы
}

START_TEST(test_strlen_long_string) {
  char long_str[1024];
  memset(long_str, 'A', sizeof(long_str) - 1);
  long_str[sizeof(long_str) - 1] = '\0';

  ck_assert_int_eq(s21_strlen(long_str),
                   strlen(long_str));  // Очень длинная строка
}

////////////////////////////////////////////
//                                        //
//              s21_strpbrk               //
//                                        //
////////////////////////////////////////////

// Основные случаи работы
START_TEST(test_strpbrk_basic) {
  const char *str = "Hello, world!";
  const char *accept = " ,!";
  ck_assert_ptr_eq(s21_strpbrk(str, accept),
                   strpbrk(str, accept));  // Базовый случай
}

START_TEST(test_strpbrk_first_char) {
  const char *str = "Hello, world!";
  const char *accept = "H";
  ck_assert_ptr_eq(s21_strpbrk(str, accept),
                   strpbrk(str, accept));  // Совпадение - первый символ
}

START_TEST(test_strpbrk_last_char) {
  const char *str = "Hello, world!";
  const char *accept = "!";
  ck_assert_ptr_eq(s21_strpbrk(str, accept),
                   strpbrk(str, accept));  // Совпадение - последний символ
}

START_TEST(test_strpbrk_not_found) {
  const char *str = "Hello";
  const char *accept = "xyz";
  ck_assert_ptr_eq(s21_strpbrk(str, accept),
                   strpbrk(str, accept));  // Нет совпадений
}

START_TEST(test_strpbrk_null_ptr) {
  ck_assert_ptr_eq(s21_strpbrk(NULL, "abc"),
                   NULL);  // NULL указатель (ИЗМЕНЕНО)
}

START_TEST(test_strpbrk_symbol) {
  const char *str = "&^*$#";
  const char *accept = "#";
  ck_assert_ptr_eq(s21_strpbrk(str, accept),
                   strpbrk(str, accept));  // Базовый случай
}

START_TEST(test_strpbrk_unicode) {
  const char *str = "Привет мир";
  const char *accept = " ";
  ck_assert_ptr_eq(s21_strpbrk(str, accept),
                   strpbrk(str, accept));  // Unicode символы
}

START_TEST(test_strpbrk_long_string) {
  char long_str[1024];
  const char *accept = "X";

  memset(long_str, 'A', sizeof(long_str) - 1);
  long_str[sizeof(long_str) - 1] = 'X';

  ck_assert_ptr_eq(s21_strpbrk(long_str, accept),
                   strpbrk(long_str, accept));  // Очень длинная строка
}

////////////////////////////////////////////
//                                        //
//              s21_strrchr               //
//                                        //
////////////////////////////////////////////

// Основные случаи работы
START_TEST(test_strrchr_basic) {
  const char *str = "Hello, world!";
  ck_assert_ptr_eq(s21_strrchr(str, 'o'), strrchr(str, 'o'));  // Базовый поиск
}

START_TEST(test_strrchr_not_found) {
  const char *str = "Hello";
  ck_assert_ptr_eq(s21_strrchr(str, 'z'),
                   strrchr(str, 'z'));  // Символ не найден
}

START_TEST(test_strrchr_null_char) {
  const char *str = "Hello\0world";
  ck_assert_ptr_eq(s21_strrchr(str, '\0'),
                   strrchr(str, '\0'));  // Поиск нуль-терминатора
}

START_TEST(test_strrchr_null_ptr) {
  ck_assert_ptr_eq(s21_strrchr(NULL, 'a'), NULL);  // NULL указатель
}

START_TEST(test_strrchr_empty_str) {
  const char *str = "";
  ck_assert_ptr_eq(s21_strrchr(str, 'y'),
                   strrchr(str, 'y'));  // Пустая str
}

START_TEST(test_strrchr_unicode) {
  const char *str = "Прииивет";
  wchar_t wc = L'и';
  int c = (int)wc; 
  ck_assert_ptr_eq(s21_strrchr(str, c), strrchr(str, c));  // Unicode символ
}

START_TEST(test_strrchr_long_string) {
  char long_str[1024];
  memset(long_str, 'A', sizeof(long_str));
  long_str[sizeof(long_str) - 1] = 'B';

  ck_assert_ptr_eq(s21_strrchr(long_str, 'B'),
                   strrchr(long_str, 'B'));  // Очень длинная строка
}

////////////////////////////////////////////
//                                        //
//              s21_strstr                //
//                                        //
////////////////////////////////////////////

// Основные случаи работы
START_TEST(test_strstr_basic) {
  const char *haystack = "Hello, world!";
  const char *needle = "world";
  ck_assert_ptr_eq(s21_strstr(haystack, needle),
                   strstr(haystack, needle));  // Базовый поиск
}

START_TEST(test_strstr_basic_2) {
  const char *haystack = "Hello, world!";
  const char *needle = "Hello, world!";
  ck_assert_ptr_eq(s21_strstr(haystack, needle),
                   strstr(haystack, needle));  // Полностью одинаковые строки
}

START_TEST(test_strstr_basic_register) {
  const char *haystack = "Hello, world!";
  const char *needle = "World";
  ck_assert_ptr_eq(s21_strstr(haystack, needle),
                   strstr(haystack, needle));  // Чувствительность к регистру
}

START_TEST(test_strstr_not_found) {
  const char *haystack = "Hello";
  const char *needle = "world";
  ck_assert_ptr_eq(s21_strstr(haystack, needle),
                   strstr(haystack, needle));  // Подстрока не найдена
}

START_TEST(test_strstr_empty_needle) {
  const char *haystack = "Hello";
  const char *needle = "";
  ck_assert_ptr_eq(s21_strstr(haystack, needle),
                   strstr(haystack, needle));  // Пустая подстрока
}

START_TEST(test_strstr_null_ptr) {
  ck_assert_ptr_eq(s21_strstr(NULL, "abc"),
                   NULL);  // NULL указатель (ИЗМЕНЕНО)
}

START_TEST(test_strstr_unicode) {
  const char *haystack = "Привет мир";
  const char *needle = "мир";
  ck_assert_ptr_eq(s21_strstr(haystack, needle),
                   strstr(haystack, needle));  // Unicode символы
}

START_TEST(test_strstr_long_string) {
  char haystack[1024];
  const char *needle = "XYZ";

  memset(haystack, 'A', sizeof(haystack) - 4);
  strcpy(haystack + sizeof(haystack) - 4, "XYZ");

  ck_assert_ptr_eq(s21_strstr(haystack, needle),
                   strstr(haystack, needle));  // Очень длинная строка
}

////////////////////////////////////////////
//                                        //
//              s21_strtok                //
//                                        //
////////////////////////////////////////////

// Основные случаи работы
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
  ck_assert_ptr_eq(token, expected);  // Базовая работа
}

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
  ck_assert_ptr_eq(token, expected);  // Базовая работа, просто пробел
}

START_TEST(test_strtok_null_str) {
  const char *delim = " ,!";
  char *token = s21_strtok(NULL, delim);
  ck_assert_ptr_eq(token, NULL);
}

START_TEST(test_strtok_empty_delim) {
  char str[] = "Hello";
  const char *delim = "";
  char *token = s21_strtok(str, delim);
  char *expected = strtok(str, delim);
  ck_assert_ptr_eq(token, expected);  // Пустые разделители
}

START_TEST(test_strtok_null_ptr) {
  ck_assert_ptr_eq(s21_strtok(NULL, NULL),
                   NULL);  // NULL параметры (ИЗМЕНЕНО)
}

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

START_TEST(test_strtok_long_string) {
  char str[1024];
  const char *delim = "|";

  memset(str, 'A', sizeof(str) - 2);
  str[sizeof(str) - 2] = '|';
  str[sizeof(str) - 1] = '\0';

  char *token = s21_strtok(str, delim);
  char *expected = strtok(str, delim);

  ck_assert_str_eq(token, expected);  // Очень длинная строка
}

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
  tcase_add_test(tc, test_strstr_basic_register);
  tcase_add_test(tc, test_strstr_not_found);
  tcase_add_test(tc, test_strstr_empty_needle);
  tcase_add_test(tc, test_strstr_null_ptr);
  tcase_add_test(tc, test_strstr_unicode);
  tcase_add_test(tc, test_strstr_long_string);

  // s21_strtok
  tcase_add_test(tc, test_strtok_basic);
  tcase_add_test(tc, test_strtok_basic_whitespace);
  tcase_add_test(tc, test_strtok_null_str);
  tcase_add_test(tc, test_strtok_empty_delim);
  tcase_add_test(tc, test_strtok_null_ptr);
  tcase_add_test(tc, test_strtok_unicode);
  tcase_add_test(tc, test_strtok_long_string);

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