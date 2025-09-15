#include "s21_string.h"

void *s21_to_upper(const char *str) {
  if (str == S21_NULL) {
    return S21_NULL;
  }

  s21_size_t len = s21_strlen(str);
  if (len == 0) {
    char *res = (char *)malloc(1);
    if (res != S21_NULL) {
      res[0] = '\0';
    }
    return res;
  }

  char *res = (char *)malloc(len + 1);
  if (res == S21_NULL) {
    return S21_NULL;
  }

  for (s21_size_t i = 0; i < len; ++i) {
    if (str[i] >= 'a' && str[i] <= 'z') {
      res[i] = str[i] - ('a' - 'A');
    } else {
      res[i] = str[i];
    }
  }

  res[len] = '\0';

  return (void *)res;
}

void *s21_to_lower(const char *str) {
  if (str == S21_NULL) {
    return S21_NULL;
  }

  s21_size_t len = s21_strlen(str);
  if (len == 0) {
    char *res = (char *)malloc(1);
    if (res != S21_NULL) {
      res[0] = '\0';
    }
    return res;
  }

  char *res = (char *)malloc(len + 1);
  if (res == S21_NULL) {
    return S21_NULL;
  }

  for (s21_size_t i = 0; i < len; ++i) {
    if (str[i] >= 'A' && str[i] <= 'Z') {
      res[i] = str[i] + ('a' - 'A');
    } else {
      res[i] = str[i];
    }
  }

  res[len] = '\0';

  return (void *)res;
}

void *s21_insert(const char *src, const char *str, s21_size_t start_index) {
  s21_size_t src_len = s21_strlen(src);
  s21_size_t str_len = s21_strlen(str);
  if (src == S21_NULL || str == S21_NULL || start_index > src_len) {
    return S21_NULL;
  }

  s21_size_t total_size = str_len + src_len + 1;
  char *result = malloc(total_size);
  if (result == S21_NULL) {
    return S21_NULL;
  }

  s21_size_t i = 0;
  for (; i < start_index; ++i) {
    result[i] = src[i];
  }

  for (s21_size_t j = 0; j < str_len; ++j) {
    result[i] = str[j];
    ++i;
  }

  for (; i < total_size - 1; ++i) {
    result[i] = src[start_index];
    start_index++;
  }
  result[i] = '\0';

  return (void *)result;
}

void *s21_trim(const char *src, const char *trim_chars) {
  if (src == S21_NULL) {
    return S21_NULL;
  }
  if (src[0] == '\0') {
    char *result = malloc(1);
    if (result) {
      result[0] = '\0';
    }
    return result;
  }
  s21_size_t src_len = s21_strlen(src);

  const char *trim_set = (trim_chars == S21_NULL) ? "" : trim_chars;
  s21_size_t start = 0;
  s21_size_t end = src_len - 1;

  while (start <= end && s21_strchr(trim_set, src[start])) {
    start++;
  }

  while (end >= start && s21_strchr(trim_set, src[end])) {
    end--;
  }

  s21_size_t result_len = (end >= start) ? (end - start + 1) : 0;
  char *result = malloc(result_len + 1);

  if (result) {
    if (result_len > 0) {
      s21_memcpy(result, src + start, result_len);
    }
    result[result_len] = '\0';
  }

  return (void *)result;
}
