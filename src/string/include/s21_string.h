#ifndef S21_STRING_H_
#define S21_STRING_H_

#include <stdarg.h>  // Для работы с переменным количеством аргументов
#include <stddef.h>  // Для типа size_t и NULL
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef unsigned long s21_size_t;

// Макрос NULL - нулевой указатель
#define S21_NULL ((void *)0)

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
    "Success",
    "Operation not permitted",
    "No such file or directory",
    "No such process",
    "Interrupted system call",
    "Input/output error",
    "No such device or address",
    "Argument list too long",
    "Exec format error",
    "Bad file descriptor",
    "No child processes",
    "Resource temporarily unavailable",
    "Cannot allocate memory",
    "Permission denied",
    "Bad address",
    "Block device required",
    "Device or resource busy",
    "File exists",
    "Invalid cross-device link",
    "No such device",
    "Not a directory",
    "Is a directory",
    "Invalid argument",
    "Too many open files in system",
    "Too many open files",
    "Inappropriate ioctl for device",
    "Text file busy",
    "File too large",
    "No space left on device",
    "Illegal seek",
    "Read-only file system",
    "Too many links",
    "Broken pipe",
    "Numerical argument out of domain",
    "Numerical result out of range",
    "Resource deadlock avoided",
    "File name too long",
    "No locks available",
    "Function not implemented",
    "Directory not empty",
    "Too many levels of symbolic links",
    "Unknown error 41",
    "No message of desired type",
    "Identifier removed",
    "Channel number out of range",
    "Level 2 not synchronized",
    "Level 3 halted",
    "Level 3 reset",
    "Link number out of range",
    "Protocol driver not attached",
    "No CSI structure available",
    "Level 2 halted",
    "Invalid exchange",
    "Invalid request descriptor",
    "Exchange full",
    "No anode",
    "Invalid request code",
    "Invalid slot",
    "Unknown error 58",
    "Bad font file format",
    "Device not a stream",
    "No data available",
    "Timer expired",
    "Out of streams resources",
    "Machine is not on the network",
    "Package not installed",
    "Object is remote",
    "Link has been severed",
    "Advertise error",
    "Srmount error",
    "Communication error on send",
    "Protocol error",
    "Multihop attempted",
    "RFS specific error",
    "Bad message",
    "Value too large for defined data type",
    "Name not unique on network",
    "File descriptor in bad state",
    "Remote address changed",
    "Can not access a needed shared library",
    "Accessing a corrupted shared library",
    ".lib section in a.out corrupted",
    "Attempting to link in too many shared libraries",
    "Cannot exec a shared library directly",
    "Invalid or incomplete multibyte or wide character",
    "Interrupted system call should be restarted",
    "Streams pipe error",
    "Too many users",
    "Socket operation on non-socket",
    "Destination address required",
    "Message too long",
    "Protocol wrong type for socket",
    "Protocol not available",
    "Protocol not supported",
    "Socket type not supported",
    "Operation not supported",
    "Protocol family not supported",
    "Address family not supported by protocol",
    "Address already in use",
    "Cannot assign requested address",
    "Network is down",
    "Network is unreachable",
    "Network dropped connection on reset",
    "Software caused connection abort",
    "Connection reset by peer",
    "No buffer space available",
    "Transport endpoint is already connected",
    "Transport endpoint is not connected",
    "Cannot send after transport endpoint shutdown",
    "Too many references: cannot splice",
    "Connection timed out",
    "Connection refused",
    "Host is down",
    "No route to host",
    "Operation already in progress",
    "Operation now in progress",
    "Stale file handle",
    "Structure needs cleaning",
    "Not a XENIX named type file",
    "No XENIX semaphores available",
    "Is a named type file",
    "Remote I/O error",
    "Disk quota exceeded",
    "No medium found",
    "Wrong medium type",
    "Operation canceled",
    "Required key not available",
    "Key has expired",
    "Key has been revoked",
    "Key was rejected by service",
    "Owner died",
    "State not recoverable",
    "Operation not possible due to RF-kill",
    "Memory page has hardware error"
    // ... остальные сообщения об ошибках для Linux
};
#else
#define MAX_ERRMSG 0
#define MAX_ERRSTR "Unknown error"
#endif

#endif  // S21_STRING_H_