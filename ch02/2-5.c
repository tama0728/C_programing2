#include<stdio.h>
#include<limits.h>

int main(){
    printf("  signed char  MIN : %d, MAX : %d\n", SCHAR_MIN, SCHAR_MAX);
    printf("unsigned char  MIN : %d, MAX : %d\n", 0, UCHAR_MAX);
    printf("  signed short MIN : %d, MAX : %d\n", SHRT_MIN, SHRT_MAX);
    printf("unsigned short MIN : %d, MAX : %d\n", 0, USHRT_MAX);
    printf("  signed int   MIN : %d, MAX : %d\n", INT_MIN, INT_MAX);
    printf("unsigned int   MIN : %d, MAX : %u\n", 0, UINT_MAX);         //unsigned int는 %u로 출력
    printf("  signed long  MIN : %ld, MAX : %ld\n", LONG_MIN, LONG_MAX);
    printf("unsigned long  MIN : %d, MAX : %lu\n", 0, ULONG_MAX);       //unsinged long은 %lu로 출력

    return 0;
}
