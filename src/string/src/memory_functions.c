#include "../include/s21_string.h"

void *s21_memchr(const void *str, int c, s21_size_t n) {
  /* Задача:
  Найти первое вхождение символа c в первых n байтах памяти, начиная с адреса
  str. Обратить внимание:

  Символ c интерпретируется как unsigned char.

  Поиск ведется в бинарных данных (не только строках).

  Если n = 0, функция должна вернуть NULL.

  Возвращает указатель на найденный байт или NULL, если символ не найден*/

  const unsigned char *ptr_element = (const unsigned char *)str;
    unsigned char target = (unsigned char)c;

    for(size_t i = 0; i < n; i++){
        if(ptr_element[i] ==  target){
            return (void *)(ptr_element + i);

        }
    }
    return NULL;
}

int s21_memcmp(const void *str1, const void *str2, s21_size_t n) {
  /* Задача:
Сравнить первые n байтов памяти str1 и str2.
Обратить внимание:

Сравнение побайтовое, без учета типа данных.

Возвращает:

0, если все байты совпадают,

< 0, если первый несовпадающий байт в str1 меньше,

> 0, если первый несовпадающий байт в str1 больше.

Если n = 0, возвращает 0.*/
	const unsigned char *ptr_str_1 = (const unsigned char *)str1;
	const unsigned char *ptr_str_2 = (const unsigned char *)str2;

	for(size_t i = 0; i < n; i++){
		int res = ptr_str_1[i] - ptr_str_2[i];
		if(res != 0){
			return res;
		}
	}

	return 0;

}


void *s21_memcpy(void *dest, const void *src, s21_size_t n) {
  /* Задача:
Скопировать n байтов из src в dest.
Обратить внимание:

Области памяти не должны пересекаться (поведение при перекрытии не определено).

Возвращает указатель на dest.

Если n = 0, копирования не происходит, но dest возвращается.*/

  unsigned char *str1 = (unsigned char*)dest;
    const unsigned char *str2 = (const unsigned char*)src;

    if(n != 0){
        for(int i = 0; i < n; i++){
            str1[i] = str2[i];
        }
    }
    
    return dest;

}
void *s21_memset(void *str, int c, s21_size_t n) {
  /* Задача:
Заполнить первые n байтов памяти str значением c.
Обратить внимание:

c приводится к unsigned char.

Возвращает указатель на str.

Если n = 0, заполнения не происходит.*/

  unsigned char *str_1 = (unsigned char*)str;
    unsigned char value = (unsigned char)c;

    for(int i = 0; i < n; i++){
        str_1[i] = value; 
    }

    return str;
}