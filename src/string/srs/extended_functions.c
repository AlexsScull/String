#include "../include/s21_string.h"

void *s21_to_upper(const char *str) {
  /*Задача:
  Преобразовать строку в верхний регистр.
  Обратить внимание:

  Возвращает новую строку (выделяет память).

  Если str = NULL, возвращает NULL.*/
}
void *s21_to_lower(const char *str) {
  /*Задача:
  Преобразовать строку в нижний регистр.
  Обратить внимание:

  Возвращает новую строку (выделяет память).

  Если str = NULL, возвращает NULL.*/
}
void *s21_insert(const char *src, const char *str, s21_size_t start_index) {
  /*Задача:
  Вставить строку str в src на позицию start_index.
  Обратить внимание:

  Если start_index > strlen(src), вернуть NULL.

  Возвращает новую строку (выделяет память).*/
}
void *s21_trim(const char *src, const char *trim_chars) {
  /*Задача:
  Удалить начальные и конечные символы из trim_chars из строки src.
  Обратить внимание:

  Если trim_chars = NULL, удалять пробельные символы.

  Возвращает новую строку (выделяет память).*/
}