#include <stdio.h>
#include <stdlib.h>

int main() {
  /*Требования к выводу тестов:

  Формат сообщений:

  Каждая проверка должна выводить результат в формате:

  text
  [PASS|FAIL]: <описание проверки>

  Пример:

  text
  PASS: memchr test 1 - basic functionality
  FAIL: memcmp test 3 - compare with null pointer

  Коды возврата:

  Тест должен возвращать:

  0 (успех) - если все проверки в тесте пройдены

  1 (ошибка) - если хотя бы одна проверка не пройдена*/

  printf("PASS: memchr test 1 - basic functionality\n");
  printf("FAIL: memcmp test 3 - compare with null pointer\n");

  return 1;
}