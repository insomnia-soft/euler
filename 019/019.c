/*
    projecteuler.net
    
    Counting Sundays
    Problem 19

    You are given the following information, but you may prefer to do some research for yourself.

        1 Jan 1900 was a Monday.
        Thirty days has September,
        April, June and November.
        All the rest have thirty-one,
        Saving February alone,
        Which has twenty-eight, rain or shine.
        And on leap years, twenty-nine.
        A leap year occurs on any year evenly divisible by 4, but not on a century unless it is divisible by 400.

    How many Sundays fell on the first of the month during the twentieth century (1 Jan 1901 to 31 Dec 2000)?
*/

#include <stdio.h>
#include <stdlib.h>

int get_days_in_month(int y, int m) {
    int ret;

    switch (m) {
        case 1:
        case 3:
        case 5:
        case 7:
        case 8:
        case 10:
        case 12:
            ret = 31;
            break;

        case 4:
        case 6:
        case 9:
        case 11:
            ret = 30;
            break;

        case 2:
            if ((y % 4 == 0 && !(y % 100 == 0)) || y % 400 == 0) {
                ret = 29;
            } else {
                ret = 28;
            }
            break;
    }

    return ret;
}

int main(int argc, char *argv[]) {
    int year, month, day, weekday, days_in_month, result;

    weekday = 1; // 1 = monday, 2 = tuesday, ..., 7 = wednesday
    result = 0;

    for (month = 1; month <= 12; month++) {
        days_in_month = get_days_in_month(1900, month);

        for (day = 1; day <= days_in_month; day++) {
            weekday++;

            if (weekday > 7) {
                weekday = 1;
            }
        }
    }

    for (year = 1901; year <= 2000; year++) {
        for (month = 1; month <= 12; month++) {
            days_in_month = get_days_in_month(year, month);

            for (day = 1; day <= days_in_month; day++) {
                if (weekday == 7 && day == 1) {
                    result++;
                }

                weekday++;

                if (weekday > 7) {
                    weekday = 1;
                }
            }
        }
    }

    printf("%d\n", result);

    system("PAUSE");	
    return 0;
}
