#ifndef S21_STRING_H_
#define S21_STRING_H_

#include <stdarg.h>  // Для работы с переменным количеством аргументов
#include <stddef.h>  // Для типа size_t и NULL

typedef unsigned long s21_size_t;

// Макрос NULL - нулевой указатель
#ifndef NULL
#define NULL ((void *)0)
#endif

// ==================== ОСНОВНЫЕ ФУНКЦИИ string.h ====================

/**
 * @brief Ищет первое вхождение символа c в первых n байтах строки str.
 * @param str Указатель на строку для поиска.
 * @param c Символ для поиска (передается как int, но интерпретируется как
 * unsigned char).
 * @param n Количество байтов для анализа.
 * @return Указатель на найденный символ или NULL, если символ не найден.
 */
void *s21_memchr(const void *str, int c, size_t n);

/**
 * @brief Сравнивает первые n байтов двух строк.
 * @param str1 Первая строка для сравнения.
 * @param str2 Вторая строка для сравнения.
 * @param n Количество байтов для сравнения.
 * @return 0 если равны, отрицательное если str1 < str2, положительное если str1
 * > str2.
 */
int s21_memcmp(const void *str1, const void *str2, size_t n);

/**
 * @brief Копирует n байтов из src в dest.
 * @param dest Указатель на место назначения.
 * @param src Указатель на источник.
 * @param n Количество байтов для копирования.
 * @return Указатель на dest.
 */
void *s21_memcpy(void *dest, const void *src, size_t n);

/**
 * @brief Заполняет первые n байтов строки str символом c.
 * @param str Указатель на строку для заполнения.
 * @param c Символ для заполнения (передается как int, но интерпретируется как
 * unsigned char).
 * @param n Количество байтов для заполнения.
 * @return Указатель на str.
 */
void *s21_memset(void *str, int c, size_t n);

/**
 * @brief Добавляет не более n символов из src в конец dest.
 * @param dest Указатель на строку назначения.
 * @param src Указатель на строку источника.
 * @param n Максимальное количество символов для добавления.
 * @return Указатель на dest.
 */
char *s21_strncat(char *dest, const char *src, size_t n);

/**
 * @brief Ищет первое вхождение символа c в строке str.
 * @param str Указатель на строку для поиска.
 * @param c Символ для поиска (передается как int, но интерпретируется как
 * unsigned char).
 * @return Указатель на найденный символ или NULL, если символ не найден.
 */
char *s21_strchr(const char *str, int c);

/**
 * @brief Сравнивает не более n символов двух строк.
 * @param str1 Первая строка для сравнения.
 * @param str2 Вторая строка для сравнения.
 * @param n Максимальное количество символов для сравнения.
 * @return 0 если равны, отрицательное если str1 < str2, положительное если str1
 * > str2.
 */
int s21_strncmp(const char *str1, const char *str2, size_t n);

/**
 * @brief Копирует не более n символов из src в dest.
 * @param dest Указатель на место назначения.
 * @param src Указатель на источник.
 * @param n Максимальное количество символов для копирования.
 * @return Указатель на dest.
 */
char *s21_strncpy(char *dest, const char *src, size_t n);

/**
 * @brief Вычисляет длину начального сегмента str1, не содержащего символов из
 * str2.
 * @param str1 Указатель на строку для анализа.
 * @param str2 Указатель на строку с символами для исключения.
 * @return Длина начального сегмента без символов из str2.
 */
size_t s21_strcspn(const char *str1, const char *str2);

/**
 * @brief Возвращает строковое описание ошибки по номеру errnum.
 * @param errnum Номер ошибки.
 * @return Указатель на строку с описанием ошибки.
 */
char *s21_strerror(int errnum);

/**
 * @brief Вычисляет длину строки str без учета нуль-терминатора.
 * @param str Указатель на строку.
 * @return Длина строки.
 */
size_t s21_strlen(const char *str);

/**
 * @brief Ищет первое вхождение любого символа из str2 в str1.
 * @param str1 Указатель на строку для поиска.
 * @param str2 Указатель на строку с символами для поиска.
 * @return Указатель на найденный символ или NULL, если символ не найден.
 */
char *s21_strpbrk(const char *str1, const char *str2);

/**
 * @brief Ищет последнее вхождение символа c в строке str.
 * @param str Указатель на строку для поиска.
 * @param c Символ для поиска (передается как int, но интерпретируется как
 * unsigned char).
 * @return Указатель на найденный символ или NULL, если символ не найден.
 */
char *s21_strrchr(const char *str, int c);

/**
 * @brief Ищет первое вхождение подстроки needle в строке haystack.
 * @param haystack Указатель на строку для поиска.
 * @param needle Указатель на подстроку для поиска.
 * @return Указатель на начало найденной подстроки или NULL, если подстрока не
 * найдена.
 */
char *s21_strstr(const char *haystack, const char *needle);

/**
 * @brief Разбивает строку str на токены, разделенные символами из delim.
 * @param str Строка для разбиения (NULL для продолжения разбиения предыдущей
 * строки).
 * @param delim Строка с символами-разделителями.
 * @return Указатель на следующий токен или NULL, если токены закончились.
 */
char *s21_strtok(char *str, const char *delim);

// ==================== ФУНКЦИИ SPRINTF И SSCANF ====================

/**
 * @brief Записывает форматированный вывод в строку str.
 * @param str Указатель на строку назначения.
 * @param format Строка формата.
 * @param ... Аргументы для форматирования.
 * @return Количество записанных символов (без учета нуль-терминатора).
 */
int s21_sprintf(char *str, const char *format, ...);

/**
 * @brief Считывает форматированный ввод из строки str.
 * @param str Указатель на строку для чтения.
 * @param format Строка формата.
 * @param ... Указатели для сохранения считанных данных.
 * @return Количество успешно считанных и присвоенных аргументов.
 */
int s21_sscanf(const char *str, const char *format, ...);

// ==================== СПЕЦИАЛЬНЫЕ ФУНКЦИИ ====================

/**
 * @brief Преобразует строку в верхний регистр.
 * @param str Указатель на строку для преобразования.
 * @return Указатель на новую строку в верхнем регистре или NULL при ошибке.
 */
void *s21_to_upper(const char *str);

/**
 * @brief Преобразует строку в нижний регистр.
 * @param str Указатель на строку для преобразования.
 * @return Указатель на новую строку в нижнем регистре или NULL при ошибке.
 */
void *s21_to_lower(const char *str);

/**
 * @brief Вставляет строку str в строку src на позицию start_index.
 * @param src Указатель на исходную строку.
 * @param str Указатель на строку для вставки.
 * @param start_index Позиция для вставки.
 * @return Указатель на новую строку с вставкой или NULL при ошибке.
 */
void *s21_insert(const char *src, const char *str, size_t start_index);

/**
 * @brief Удаляет начальные и конечные символы из trim_chars из строки src.
 * @param src Указатель на исходную строку.
 * @param trim_chars Указатель на строку с символами для удаления.
 * @return Указатель на новую обрезанную строку или NULL при ошибке.
 */
void *s21_trim(const char *src, const char *trim_chars);

// ==================== МАКРОСЫ ОШИБОК ====================
#if defined __APPLE__ || defined __MACH__
#define MAX_ERRNO 107
#define MIN_ERRNO 0
static const char *error_messages[] = {
    "Undefined error: 0", "Operation not permitted",
    "No such file or directory",
    // ... остальные сообщения об ошибках для macOS
};
#elif __linux__
#define MAX_ERRNO 134
#define MIN_ERRNO 0
static const char *error_messages[] = {
    "Success", "Operation not permitted", "No such file or directory",
    // ... остальные сообщения об ошибках для Linux
};
#else
#define MAX_ERRMSG 0
#define MAX_ERRSTR "Unknown error"
#endif

#endif  // S21_STRING_H_