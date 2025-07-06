#include "../include/s21_string.h"


char *s21_strncat(char *dest, const char *src, s21_size_t n) {
  /*Задача:
  Добавить не более n символов из src в конец dest. (Т.е. добавить n символов
  или или до символа конца строки ('\0'))

  Обратить внимание:

  Результирующая строка всегда завершается нуль-терминатором (\0).

  Если src короче n, копируется только strlen(src) символов.

  Возвращает указатель на dest.*/
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
  unsigned char uc = (unsigned char)c;
  if (str != NULL){
  while (flag == 0 && str[i] != '\0'){
    if (str[i] == uc){
    ptr = &str[i];
    flag = 1;
    }
    i++;
    len++;
  }
}
  if (flag == 0){
    ptr = NULL;
  }
  if (uc == '\0'){
    ptr = &str[len];
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
  if (str1 != NULL && str2 != NULL){
  while (n > 0 && result == 0 && str1[i] != '\0' && str2[i] != '\0'){
      result = (unsigned char)str1[i] - (unsigned char)str2[i];
      n--;
      i++;
  }
}
else {
  result = NULL;
}
  return result;
}
char *s21_strncpy(char *dest, const char *src, s21_size_t n) {
  /*Задача:
  Скопировать не более n символов из src в dest.
  Обратить внимание:

  Если src короче n, оставшиеся символы заполняются нулями.

  Возвращает указатель на dest.*/

}
s21_size_t s21_strcspn(const char *str1, const char *str2) {
  /*Задача:
  Найти длину начального сегмента str1, не содержащего символов из str2.
  Обратить внимание:

  Возвращает количество символов до первого вхождения любого символа из str2.

  Если совпадений нет, возвращает strlen(str1).*/
}
s21_size_t s21_strlen(const char *str) {
  /*Задача:
  Вычислить длину строки str (без учета \0).
  Обратить внимание:
  Если строка не завершена нулевым символом, то её поведение не определено.
  Если str = NULL, поведение не определено.*/
  
  if (str == NULL){
    return NULL;
  }
  size_t len = 0;
  while (str[len] != '\0'){
    len++;
  }
  return len;
}
char *s21_strpbrk(const char *str1, const char *str2) {
  /*Задача:
  Найти первое вхождение любого символа из str2 в str1.
  Обратить внимание:

  Возвращает указатель на найденный символ или NULL.*/

  if (str1 == NULL || str2 == NULL){
    return NULL;
  }

  int i = 0;
  int j = 0;
  char *ptr;
  int flag = 0;
  while (str1[i] != '\0' && flag == 0){
    while (str2[j] != '\0' && flag == 0){
      if (str1[i] == str2[j]){
        ptr = &str1[i];
        flag = 1;
      }
      j++;
    }
    i++;
    j = 0;
  }

  if (flag == 0){
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
  unsigned char uc = (unsigned char)c;
  if (str == NULL){
    return NULL;
  }

  while (str[i] != '\0'){
    if (str[i] == uc){
    ptr = &str[i];
    flag = 1;
    }
    i++;
    len++;
  }

  if (flag == 0){
    ptr = NULL;
  }
  if (uc == '\0'){
    ptr = &str[len];
  }
  return ptr;
}
char *s21_strstr(const char *haystack, const char *needle) {
  /*Задача:
  Найти первое вхождение подстроки needle в haystack.
  Обратить внимание:

  Если needle = "", возвращает haystack.

  Чувствителен к регистру.*/
}
char *s21_strtok(char *str, const char *delim) {
  /*Задача:
  Разбить строку str на токены по разделителям из delim.
  Обратить внимание:

  При первом вызове str указывает на строку, при последующих — NULL.

  Сохраняет состояние между вызовами (статическая переменная).

  Модифицирует исходную строку (заменяет разделители на \0).*/
}