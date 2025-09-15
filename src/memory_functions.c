#include "s21_string.h"

void *s21_memchr(const void *str, int c, s21_size_t n) {
  if (str == S21_NULL) {
    return S21_NULL;
  }

  const unsigned char *ptr_element = (const unsigned char *)str;
  unsigned char target = (unsigned char)c;

  void *result = S21_NULL;
  int flag = 0;

  for (s21_size_t i = 0; i < n && flag == 0; ++i) {
    if (ptr_element[i] == target) {
      result = (void *)(ptr_element + i);
      flag = 1;
    }
  }
  return result;
}

int s21_memcmp(const void *str1, const void *str2, s21_size_t n) {
  int res = 0;

  if (str1 == S21_NULL || str2 == S21_NULL) {
    return 0;
  }

  const unsigned char *ptr_str_1 = (const unsigned char *)str1;
  const unsigned char *ptr_str_2 = (const unsigned char *)str2;

  for (s21_size_t i = 0; i < n && res == 0; ++i) {
    if (ptr_str_1[i] - ptr_str_2[i] > 0) {
      res = 1;
    } else if (ptr_str_1[i] - ptr_str_2[i] < 0) {
      res = -1;
    }
  }

  return res;
}

void *s21_memcpy(void *dest, const void *src, s21_size_t n) {
  if (dest == S21_NULL || src == S21_NULL) {
    return S21_NULL;
  }

  unsigned char *ptr_dest = (unsigned char *)dest;
  const unsigned char *ptr_src = (const unsigned char *)src;

  for (s21_size_t i = 0; i < n; ++i) {
    ptr_dest[i] = ptr_src[i];
  }

  return dest;
}

void *s21_memset(void *str, int c, s21_size_t n) {
  if (str == S21_NULL) {
    return S21_NULL;
  }
  unsigned char *ptr_str = (unsigned char *)str;
  unsigned char value = (unsigned char)c;

  for (s21_size_t i = 0; i < n; ++i) {
    ptr_str[i] = value;
  }

  return str;
}