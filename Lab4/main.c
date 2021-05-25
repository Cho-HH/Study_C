#include <stdio.h>
#include <string.h>
#include "my_string.h"
 
/*
	my_string.c에 직접 구현하신 index_of()와,
	C 라이브러리(<string.h>)의 strstr()의 비교를 통해,
	구현한 index_of()가 제대로 동작하는지 검토합니다.
*/
static void compare(const char* str, const char* find) {
    int my;
    int libstrstr;
 
    my = index_of(str, find);
    libstrstr = strstr(str, find) - str;
    if (libstrstr < 0) {
        libstrstr = -1;
    }
    printf("Find... \"%s\" in \"%s\"\n", find, str);
    if (my != libstrstr) {
        printf("Wrong!!! - Your Function: %d, but Library: %d\n", my, libstrstr);
    } else {
        printf("OK - Your Function: %d, and Library: %d\n", my, libstrstr);
    }
}
 
int main(void)
{
    char str[] = "ddadday";
 
    compare(str, "dad");
    compare(str, "day");
 
    return 0;
}
