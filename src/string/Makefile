CC=gcc
CFLAGS=-std=c11 -Wall -Werror -Wextra


all: s21_string test_s21_string clean_peace

s21_cat: s21_cat.c  
	$(CC) s21_cat.c -o s21_cat

test_s21_string: test_s21_string.c
	$(CC) $(CFLAGS) test_s21_string.c -o test_s21_string -D_GNU_SOURCE

# s21_cat: s21_cat.c  
# 	$(CC) s21_cat.c -o s21_cat -fsanitize=address

# test_s21_string: test_s21_string.c
# 	$(CC) $(CFLAGS) test_s21_string.c -o test_s21_string -D_GNU_SOURCE -fsanitize=address

rebuild: clean all

clean_peace:
	rm -rf *.o

clean:
	rm -rf *.o s21_string test_s21_string


