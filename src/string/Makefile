CC=gcc
CFLAGS= 
# CFLAGS=-std=c11 -Wall -Werror -Wextra

all: s21_string.a test

s21_string.a: memory_functions.o string_functions.o sprintf_functions.o sscanf_functions.o extended_functions.o error_functions.o
	ar rcs s21_string.a src/*.o

memory_functions.o: src/memory_functions.c include/s21_string.h
	$(CC) $(CFLAGS) -c src/memory_functions.c -o src/memory_functions.o

string_functions.o: src/string_functions.c include/s21_string.h
	$(CC) $(CFLAGS) -c src/string_functions.c -o src/string_functions.o

sprintf_functions.o: src/sprintf_functions.c include/s21_string.h
	$(CC) $(CFLAGS) -c src/sprintf_functions.c -o src/sprintf_functions.o

sscanf_functions.o: src/sscanf_functions.c include/s21_string.h
	$(CC) $(CFLAGS) -c src/sscanf_functions.c -o src/sscanf_functions.o

extended_functions.o: src/extended_functions.c include/s21_string.h
	$(CC) $(CFLAGS) -c src/extended_functions.c -o src/extended_functions.o

error_functions.o: src/error_functions.c include/s21_string.h
	$(CC) $(CFLAGS) -c src/error_functions.c -o src/error_functions.o

test: test_memory test_string test_sprintf test_sscanf test_extended test_error

test_memory: tests/test_memory.c s21_string.a
	$(CC) $(CFLAGS) tests/test_memory.c s21_string.a -o test_memory -lcheck

test_string: tests/test_string.c s21_string.a
	$(CC) $(CFLAGS) tests/test_string.c s21_string.a -o test_string -lcheck

test_sprintf: tests/test_sprintf.c s21_string.a
	$(CC) $(CFLAGS) tests/test_sprintf.c s21_string.a -o test_sprintf -lcheck

test_sscanf: tests/test_sscanf.c s21_string.a
	$(CC) $(CFLAGS) tests/test_sscanf.c s21_string.a -o test_sscanf -lcheck

test_extended: tests/test_extended.c s21_string.a
	$(CC) $(CFLAGS) tests/test_extended.c s21_string.a -o test_extended -lcheck

test_error: tests/test_error.c s21_string.a
	$(CC) $(CFLAGS) tests/test_error.c s21_string.a -o test_error -lcheck

rebuild: clean_all all

clean:
	rm -f src/*.o

clean_all:
	rm -f src/*.o s21_string.a test_memory test_string test_sprintf test_sscanf test_extended test_error