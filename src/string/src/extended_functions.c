#include "../include/s21_string.h"

//! Надо память освободить и разобраться с s21_size_t !

void *s21_to_upper(const char *str) {
  /*Задача:
  Преобразовать строку в верхний регистр.
  Обратить внимание:

  Возвращает новую строку (выделяет память).

  Если str = NULL, возвращает NULL.*/

  if (str == S21_NULL) {
    return S21_NULL;
  }
  char *res = S21_NULL;  // объявляем результат поиска как NULL
  s21_size_t len = strlen(str);

  res = (char *)malloc(strlen(str) + 1);

  if (res == S21_NULL) {
    return S21_NULL;
  }

  for (int i = 0; i < len; i++) {
    if (str[i] >= 'a' && str[i] <= 'z') {
      res[i] = str[i] - 32;
    } else {
      res[i] = str[i];
    }
  }

  res[len] = '\0';

  return res;
}

void *s21_to_lower(const char *str) {
  /*Задача:
  Преобразовать строку в нижний регистр.
  Обратить внимание:

  Возвращает новую строку (выделяет память).

  Если str = NULL, возвращает NULL.*/

    if (str == S21_NULL) {
        return S21_NULL;
    }

    char *res = S21_NULL;
    size_t len = strlen(str);

    res = (char *)malloc(strlen(str) + 1);

    if (res == S21_NULL) {
        return S21_NULL;
    }

    for (int i = 0; i < len; i++) {
        if (str[i] >= 'A' && str[i] <= 'Z') {
            res[i] = str[i] + 32;
        } else {
            res[i] = str[i];
        }
    }


    res[len] = '\0';

    return res;

}

void *s21_insert(const char *src, const char *str, s21_size_t start_index) {
  /*Задача:
  Вставить строку str в src на позицию start_index.
  Обратить внимание:

  Если start_index > strlen(src), вернуть NULL.

  Возвращает новую строку (выделяет память).*/

    if(src == S21_NULL || str == S21_NULL || start_index > strlen(src)){
        return S21_NULL;
    }

    int size = strlen(str) + strlen(src) + 1;
    char *insert = malloc(size);

    
    if (insert != S21_NULL) {
        int i = 0;

        for (; i < start_index; i++) {
            insert[i] = src[i];
        }

        for (int j = 0; j < strlen(str); j++) {
            insert[i] = str[j];
            i++;
        }

        for (; i < size - 1; i++) {
            insert[i] = src[start_index];
            start_index++;
        }

        insert[i] = '\0';

        return insert;
    } else {
        return S21_NULL;
    }
}

void *s21_trim(const char *src, const char *trim_chars) {
  /*Задача:
  Удалить начальные и конечные символы из trim_chars из строки src.
  Обратить внимание:

  Если trim_chars = NULL, удалять пробельные символы, *нужно вернуть NULL*
  

  Возвращает новую строку (выделяет память).*/

    //s21_size_t len_trim_chars = strlen(trim_chars);

    if(src == S21_NULL){     // NULL исходная строка нужно до выделения памяти
        return S21_NULL;
    }

    s21_size_t start = 0;
    s21_size_t end = strlen(src) - 1;

    char *result = malloc(1);

    if(result == S21_NULL || src == S21_NULL){     // NULL исходная строка или не выделилась память
        return S21_NULL;
    }

    if(src[0] == '\0'){             // Пустая исходная строка
        result[0] = src[0];
        return result;
    }

    if(trim_chars == S21_NULL){     // NULL trim chars или пустые символы для обрезки
        result = malloc(strlen(src) * sizeof(char));
        strcpy(result, src);
        return result;
    }                               

    //char *new_chars = malloc(len_trim_chars);

    // if (len_trim_chars == 0) {
    //     new_chars[0] = ' ';
    // } else {
    //     for (int i = 0; i < len_trim_chars; i++) {
    //         new_chars[i] = trim_chars[i];
    //     }
    //     // хз надо тут символ \0 или нет!
    // }

   
    int start_flag = 1;
    // <= для обработки случая с разницей в 1 последнюю букву
    while (start_flag && start <= end) {
        if (strchr(trim_chars, (int)src[start])) {
            start++;
        } else {
            start_flag = 0;
        }
    }

    int end_flag = 1;
    while (end_flag && end > start) {
        if (strchr(trim_chars, (int)src[end])) {
            end--;
        } else {
            end_flag = 0;
        }
    }

    // if (start_flag && end_flag) {       //Полная обрезка всей строки должна вернуть result
    //     return S21_NULL;
    // }

    s21_size_t result_len = (end - start) + 1;
    result = malloc(result_len * sizeof(char));
    memcpy(result, src + start, result_len);

    result[result_len] = '\0';
    return result;
    
}
