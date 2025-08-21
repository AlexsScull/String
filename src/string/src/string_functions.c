#include "../include/s21_string.h"
// #include <wchar.h>

char *s21_strncat(char *dest, const char *src, s21_size_t n) {
  /*Задача:
  Добавить не более n символов из src в конец dest. (Т.е. добавить n символов
  или или до символа конца строки ('\0'))

  Обратить внимание:

  Результирующая строка всегда завершается нуль-терминатором (\0).

  Если src короче n, копируется только strlen(src) символов.

  Возвращает указатель на dest.*/

  if (dest == NULL || src == NULL) {
    return NULL;
  }

  s21_size_t i = s21_strlen(dest);
  s21_size_t len_src = s21_strlen(src);

  if (len_src < n) {
    n = len_src;
  }

  for (int j = 0; j < n; i++, j++) {
    dest[i] = src[j];
  }

  return dest;
}
char *s21_strchr(const char *str, int c) {
  /*Задача:
  Найти первое вхождение символа c в строке str.
  Обратить внимание:

  c интерпретируется как unsigned char.

  Возвращает указатель на найденный символ или NULL.

  Если c = '\0', возвращает указатель на конец строки.*/

  char *ptr;
  int flag = 0;
  int i = 0;
  int len = 0;

  if (str == NULL) {
    return NULL;
  }

  char uc = (char)c;

  while (flag == 0 && str[i] != '\0') {
    if (str[i] == uc) {
      ptr = (char *)&str[i];
      flag = 1;
    }
    i++;
    len++;
  }

  if (flag == 0) {
    ptr = NULL;
  }
  if (uc == '\0') {
    ptr = (char *)&str[len];
  }
  return ptr;

  /* Unicode!! */
}

int s21_strncmp(const char *str1, const char *str2, s21_size_t n) {
  /*Задача:
  Сравнить первые n символов строк str1 и str2.
  Обратить внимание:

  Сравнение прекращается при обнаружении различий или достижении n.

  Возвращает:

  0, если строки равны,

  < 0, если str1 < str2,

  > 0, если str1 > str2.

  Если n = 0, возвращает 0.*/

  int result = 0;
  int i = 0;
  if (str1 != NULL && str2 != NULL) {
    while (n > 0 && result == 0 && str1[i] != '\0' && str2[i] != '\0') {
      result = (unsigned char)str1[i] - (unsigned char)str2[i];
      n--;
      i++;
    }
  } else {
    result = 0;
  }
  return result;
  /*ТУТ ЧТО-ТО СТРАННОЕ ПОСМОТРЕТЬ ЕЩЁ РАЗ*/
}
char *s21_strncpy(char *dest, const char *src, s21_size_t n) {
  /*Задача:
  Скопировать не более n символов из src в dest.
  Обратить внимание:

  Если src короче n, оставшиеся символы заполняются нулями.

  Возвращает указатель на dest.*/

  if (dest == NULL || src == NULL) {
    return NULL;
  }

  s21_size_t len_src = s21_strlen(src);

  for (int i = 0; i < n; i++) {
    if (i <= len_src) {
      dest[i] = src[i];
    } else {
      dest[i] = 0;
    }
  }

  return dest;
}
s21_size_t s21_strcspn(const char *str1, const char *str2) {
  /*Задача:
  Найти длину начального сегмента str1, не содержащего символов из str2.
  Обратить внимание:

  Возвращает количество символов до первого вхождения любого символа из str2.

  Если совпадений нет, возвращает strlen(str1).*/

  s21_size_t result = 0;
  if (str1 == NULL || str2 == NULL) {
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
      j++;
    }
    if (flag == 0) {
      result++;
    }
    i++;
    j = 0;
  }

  if (flag == 0) {
    result = s21_strlen(str1);
  }

  return result;
}
s21_size_t s21_strlen(const char *str) {
  /*Задача:
  Вычислить длину строки str (без учета \0).
  Обратить внимание:
  Если строка не завершена нулевым символом, то её поведение не определено.
  Если str = NULL, поведение не определено.*/

  s21_size_t len = 0;
  if (str == NULL) {
    return len;
  }

  while (str[len] != '\0') {
    len++;
  }
  return len;
}
char *s21_strpbrk(const char *str1, const char *str2) {
  /*Задача:
  Найти первое вхождение любого символа из str2 в str1.
  Обратить внимание:

  Возвращает указатель на найденный символ или NULL.*/

  if (str1 == NULL || str2 == NULL) {
    return NULL;
  }

  int i = 0;
  int j = 0;
  char *ptr;
  int flag = 0;
  while (str1[i] != '\0' && flag == 0) {
    while (str2[j] != '\0' && flag == 0) {
      if (str1[i] == str2[j]) {
        ptr = (char *)&str1[i];
        flag = 1;
      }
      j++;
    }
    i++;
    j = 0;
  }

  if (flag == 0) {
    ptr = NULL;
  }

  return ptr;
}
char *s21_strrchr(const char *str, int c) {
  /*Задача:
  Найти последнее вхождение символа c в str.
  Обратить внимание:

  Если c = '\0', возвращает указатель на конец строки.
  Если совпадений нет, возвращает NULL*/

  char *ptr;
  int flag = 0;
  int i = 0;
  int len = 0;
  char uc = (char)c;
  if (str == NULL) {
    return NULL;
  }

  while (str[i] != '\0') {
    if (str[i] == uc) {
      ptr = (char *)&str[i];
      flag = 1;
    }
    i++;
    len++;
  }

  if (flag == 0) {
    ptr = NULL;
  }
  if (uc == '\0') {
    ptr = (char *)&str[len];
  }
  return ptr;
}
char *s21_strstr(const char *haystack, const char *needle) {
  /*Задача:
  Найти первое вхождение подстроки needle в haystack.
  Обратить внимание:

  Если needle = "", возвращает haystack.

  Чувствителен к регистру.*/

  if (haystack == NULL) {
    return NULL;
  }

  char *ptr = NULL;
  if (*needle == '\0' | needle == NULL) {
    ptr = (char *)&haystack[0];
  } else {
    int i = 0;
    int j = 0;
    int flag = 0;
    int flag2 = 0;
    while (haystack[i] != '\0' && flag == 0) {
      if (haystack[i] == needle[j]) {
        ptr = (char *)&haystack[i];
        flag = 1;
      }
      if (flag == 1) {
        while (needle[j] != '\0') {
          if (haystack[i] != needle[j]) {
            flag2 = 1;
          }
          j++;
          i++;
        }
        if (flag2 == 1) {
          flag = 0;
          j = 0;
          ptr = NULL;
        }
      }
      i++;
    }
  }

  return ptr;

  /* ВЛОЖЕННОСТЬ ЕПТ ТВОЮ МАТЬ*/
}
char *s21_strtok(char *str, const char *delim) {
  /*Задача:
  Разбить строку str на токены по разделителям из delim.
  Обратить внимание:

  При первом вызове str указывает на строку, при последующих — NULL.

  Сохраняет состояние между вызовами (статическая переменная). (хвост)

  Модифицирует исходную строку (заменяет разделители на \0).*/

  static char *last_pos = NULL;  // объявляем все штучки что нужны
  char *token_start = NULL;
  char *token_end = NULL;

  if (str != NULL) {  // первый вызов
    token_start = str;
    token_end = s21_strpbrk(token_start, delim);
    // while(token_start == token_end){
    //  token_start++;
    //  token_end = strpbrk(token_start, delim);
    // }
    // if (i != 0){
    //   token_end = token_end + i;
    // }
    if (token_end != NULL) {
      last_pos = token_end + 1;
      *token_end = '\0';
    } else {  // пока думаем что здесь делать
      last_pos = NULL;
    }
  }

  if (last_pos != NULL && *last_pos != '\0' && str == NULL) {
    token_start = last_pos;
    token_end = s21_strpbrk(token_start, delim);
    while (token_start == token_end) {
      token_start++;
      token_end = s21_strpbrk(token_start, delim);
    }
    if (token_end != NULL) {
      last_pos = token_end + 1;
      *token_end = '\0';
    } else {  // пока думаем что здесь делать
      token_start = last_pos;
      last_pos = NULL;
    }
  }

  return token_start;
}
