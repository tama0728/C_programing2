#include <stdio.h>

static char daytab[2][13] = {
        {0, 31, 28, 31, 30, 31, 30,31, 31, 30, 31, 30, 31},
        {0, 31, 29, 31, 30, 31, 30,31, 31, 30, 31, 30, 31}
};

// day_of_year: set day of year from month & day
int day_of_year(int year, int month, int day) {
    int i, leap;

    leap = year%4 == 0 && year%100 != 0 || year%400 == 0;
    for (i = 1; i < month; ++i)
        day += daytab[leap][i];
    return day;
}

// month_day: set month, day from day of year
void month_day(int year, int yearday, int *pmonth, int *pday) {
    int i, leap;

    leap = year%4 == 0 && year%100 != 0 || year%400 == 0;
    for (i = 1; yearday > daytab[leap][i]; ++i)
        yearday -= daytab[leap][i];
    *pmonth = i;
    *pday = yearday;
}

int main(void) {
    printf("2022/05/05 : %d\n", day_of_year(2022, 5, 5));
    printf("2014/05/05 : %d\n", day_of_year(2014, 5, 5));

    int month = 0, day = 0; //월 일을 저장할 변수 생성

    month_day(2022, 200, &month, &day);
    printf("2022년 200번째 날 : %d월 %d일\n", month, day);
    month_day(2000, 300, &month, &day);
    printf("2000년 300번째 날 : %d월 %d일\n", month, day);
    return 0;
}
