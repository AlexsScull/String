#include <ctype.h>
#include <limits.h>
#include <locale.h>
#include <math.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <wchar.h>

#include "include/s21_string.h"

#define TEST(format_str, value, type) {\
    printf("format_str %s\n", format_str); \
    char str1[200] = {0};                                \
    char str2[200] = {0};                                \
    type val = (value);                                  \
    int res1 = sprintf(str1, format_str, val);           \
    int res2 = s21_sprintf(str2, format_str, val);       \
    printf("sprintf res = %d\nstr = \"%s\"\n", res1, str1);               \
    printf("s21_sprintf res = %d\nstr = \"%s\"\n", res2, str2);               \
    if (res1 == res2 && strcmp(str1, str2) == 0) \
    printf("OK\n\n");               \
    else \
    printf("!OK\n\n");               \
} \


#define TEST2(format_str, val_for, value, type){ \
    printf("format_str %s\n", format_str); \
    char str1[200] = {0};                                \
    char str2[200] = {0};                                \
    type val = (value);                                  \
    int res1 = sprintf(str1, format_str, (int)val_for, val);        \
    int res2 = s21_sprintf(str2, format_str, (int)val_for, val);    \
    if (res1 == res2 && strcmp(str1, str2) == 0) \
    printf("OK\n\n");               \
    else \
    printf("!OK\n\n");               \
  }                                                                 \


#define TEST3(format_str, val_for1, val_for2, value, type){ \
    printf("format_str %s\n", format_str); \
    char str1[200] = {0};                                \
    char str2[200] = {0};                                \
    type val = (value);                                  \
    int res1 = sprintf(str1, format_str, (int)val_for1, (int)val_for2, val);   \
    int res2 = s21_sprintf(str2, format_str, (int)val_for1, (int)val_for2, val);      \
    if (res1 == res2 && strcmp(str1, str2) == 0) \
    printf("OK\n\n");               \
    else \
    printf("!OK\n\n");               \
  }                                                                            \




int main() {

  TEST("%10s", 0, char *)
  TEST( "%.8s", 0, char *)
  TEST( "%10.8s", 0, char *)

TEST("%+10i", 123,int)
TEST("% 10i", 123,int)

TEST("%+10u", 123,int)
TEST("% 10u", 123,int)



TEST( "%+u", 123, int)
TEST( "%-05u", 123, int)
TEST( "%-5u", 123, int)
TEST( "%05u", 123, int)
TEST( "%10u", 123, int)
TEST( "%.5u", 123, int)
TEST( "%.-5u", 123, int)
TEST( "%10.5u", 123, int)
TEST( "%-10.5u", 123, int)
TEST( "%-05u", 123, int)
TEST2( "%*u", 10, 123, int)
TEST2( "%.*u", 5, 123, int)
TEST3( "%*.*u", 10, 5, 123, int)
TEST( "%u", -123, int)
TEST( "%+u", -123, int)
TEST( "% u", -123, int)
TEST( "%.0u", 123, int)
TEST( "%.0u", 0, int)
TEST( "%0u", 0, int)

  if (!setlocale(LC_ALL, "en_US.UTF-8")) {
    setlocale(LC_ALL, "C.UTF-8");
  }


TEST( "%-20ls", "Hello", wchar_t*)
// TEST( "%20ls", "Hello", wchar_t *)
TEST( "%.5ls", "Hello, world!", wchar_t *)
TEST( "%20.5ls", "Hello, world!",
             wchar_t *)
TEST2( "%*ls", 20, "Hello", wchar_t *)
TEST2( "%.*ls", 5, "Hello, world!",
               wchar_t *)
TEST3( "%*.*ls", 20, 5, "Hello, world!",
               wchar_t *)
TEST( "%.5ls", NULL, wchar_t *)

// Тесты для %lc
TEST( "%-5lc", 'A', wchar_t)
TEST( "%5lc", 'A', wchar_t)
TEST2( "%*lc", 5, 'A', wchar_t)
}