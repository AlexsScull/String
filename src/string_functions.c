#include "s21_string.h"

char *s21_strncat(char *dest, const char *src, s21_size_t n) {
  if (dest == S21_NULL || src == S21_NULL) {
    return S21_NULL;
  }

  s21_size_t i = s21_strlen(dest);
  s21_size_t len_src = s21_strlen(src);

  if (len_src < n) {
    n = len_src;
  }

  for (s21_size_t j = 0; j < n; ++i, ++j) {
    dest[i] = src[j];
  }
  dest[i] = '\0';

  return dest;
}

char *s21_strchr(const char *str, int c) {
  char *ptr = S21_NULL;
  int flag = 0;
  int i = 0;
  int len = 0;

  if (str == S21_NULL) {
    return S21_NULL;
  }

  char uc = (char)c;

  while (flag == 0 && str[i] != '\0') {
    if (str[i] == uc) {
      ptr = (char *)&str[i];
      flag = 1;
    }
    ++i;
    ++len;
  }

  if (flag == 0) {
    ptr = S21_NULL;
  }
  if (uc == '\0') {
    ptr = (char *)&str[len];
  }
  return ptr;
}

int s21_strncmp(const char *str1, const char *str2, s21_size_t n) {
  int result = 0;

  if (str1 != S21_NULL && str2 != S21_NULL) {
    for (s21_size_t i = 0; i < n && result == 0; ++i) {
      if (str1[i] != str2[i]) {
        result = (unsigned char)str1[i] - (unsigned char)str2[i];
      }
      // Если достигнут конец
      else if (str1[i] == '\0') {
        break;
      }
    }
  }
  return result;
}

char *s21_strncpy(char *dest, const char *src, s21_size_t n) {
  if (dest == S21_NULL || src == S21_NULL) {
    return S21_NULL;
  }

  s21_size_t len_src = s21_strlen(src);

  for (s21_size_t i = 0; i < n; ++i) {
    if (i < len_src) {
      dest[i] = src[i];
    } else {
      dest[i] = 0;
    }
  }

  return dest;
}

s21_size_t s21_strcspn(const char *str1, const char *str2) {
  s21_size_t result = 0;
  if (str1 == S21_NULL || str2 == S21_NULL) {
    return result;
  }

  int i = 0;
  int j = 0;
  int flag = 0;
  while (str1[i] != '\0' && flag == 0) {
    while (str2[j] != '\0' && flag == 0) {
      if (str1[i] == str2[j]) {
        flag = 1;
      }
      ++j;
    }
    if (flag == 0) {
      ++result;
    }
    ++i;
    j = 0;
  }
  if (flag == 0) {
    result = s21_strlen(str1);
  }

  return result;
}
s21_size_t s21_strlen(const char *str) {
  s21_size_t len = 0;
  if (str == S21_NULL) {
    return len;
  }

  while (str[len] != '\0') {
    ++len;
  }
  return len;
}
char *s21_strpbrk(const char *str1, const char *str2) {
  if (str1 == S21_NULL || str2 == S21_NULL) {
    return S21_NULL;
  }

  int i = 0;
  int j = 0;
  char *ptr = S21_NULL;
  int flag = 0;
  while (str1[i] != '\0' && flag == 0) {
    while (str2[j] != '\0' && flag == 0) {
      if (str1[i] == str2[j]) {
        ptr = (char *)&str1[i];
        flag = 1;
      }
      ++j;
    }
    ++i;
    j = 0;
  }

  if (flag == 0) {
    ptr = S21_NULL;
  }

  return ptr;
}

char *s21_strrchr(const char *str, int c) {
  if (str == S21_NULL) {
    return S21_NULL;
  }
  char *ptr = S21_NULL;
  int flag = 0;
  int i = 0;
  int len = 0;
  char uc = (char)c;

  while (str[i] != '\0') {
    if (str[i] == uc) {
      ptr = (char *)&str[i];
      flag = 1;
    }
    ++i;
    ++len;
  }

  if (flag == 0) {
    ptr = S21_NULL;
  }
  if (uc == '\0') {
    ptr = (char *)&str[len];
  }
  return ptr;
}

char *s21_strstr(const char *haystack, const char *needle) {
  if (haystack == S21_NULL || needle == S21_NULL) {
    return S21_NULL;
  }

  char *ptr = S21_NULL;
  if (*needle == '\0') {
    ptr = (char *)&haystack[0];
    return ptr;
  }
  int i = 0;
  int j = 0;
  int flag = 0;

  while (haystack[i] != '\0' && flag == 0 && ptr == S21_NULL) {
    if (haystack[i] == needle[j]) {
      int i2 = i;
      int j2 = j;
      int flag2 = 0;

      while (needle[j2] != '\0' && flag2 == 0) {
        if (haystack[i2] != needle[j2]) {
          flag2 = 1;
        } else {
          ++i2;
          ++j2;
        }
      }

      if (flag2 == 0 && needle[j2] == '\0') {
        ptr = (char *)&haystack[i];
        flag = 1;
      }
    }
    i++;
  }

  return ptr;
}

char *s21_strtok(char *str, const char *delim) {
  static char *last_pos = S21_NULL;
  char *token_start = S21_NULL;
  char *token_end = S21_NULL;

  if (str != S21_NULL) {
    last_pos = str;
  }

  if (last_pos == S21_NULL || *last_pos == '\0') {
    token_start = S21_NULL;
  } else {
    token_start = last_pos;
    while (*token_start != '\0' &&
           s21_strchr(delim, *token_start) != S21_NULL) {
      token_start++;
    }

    if (*token_start == '\0') {
      token_start = S21_NULL;
      last_pos = S21_NULL;
    } else {
      token_end = token_start;
      while (*token_end != '\0' && s21_strchr(delim, *token_end) == S21_NULL) {
        ++token_end;
      }

      if (*token_end != '\0') {
        *token_end = '\0';
        last_pos = token_end + 1;
      } else {
        last_pos = S21_NULL;
      }
    }
  }

  return token_start;
}