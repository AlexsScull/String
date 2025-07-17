#include <string.h>

#include "include/s21_string.h"


int main() {
    printf("s21_sprintf(str, \"12345\")\n");
    char str[200] = {0};    
    int res = s21_sprintf(str, "12345%d",12345);
    
    printf("res = %d\nstr = %s\n", res, str);
}