/*
projecteuler.net

Power digit sum
Problem 16

2^15 = 32768 and the sum of its digits is 3 + 2 + 7 + 6 + 8 = 26.

What is the sum of the digits of the number 21000?
*/

#include <stdio.h>
#include <stdlib.h>
#define MAX 1000

void multiply(char *a) {
    int n = 0;
    int i = 0;
    int next = 0;

    while (*(a + i) != 0) {
        n = *(a + i) - 48;
        n = n * 2 + next;

        if (n >= 10) {
            *(a + i) = n + 38;
            next = 1;
        } else {
            *(a + i) = n + 48;
            next = 0;
        }
        
        i++;
    }

    if (next) {
        *(a + i) = 49;
    }
}

void print(char *a) {
    int i = 0;
    int len = 0;

    for (len = 0; *(a + len) != 0; len++);

    for (i = len; i >= 0; i--) {
        printf("%c", *(a + i));
    }

    printf("\n");
}

void sum_digits(char *a) {
    int zbroj = 0;
    int i;

    for (i = 0; *(a + i) != 0; zbroj += (*(a + i) - 48), i++);

    printf("Ukupan zbroj znamenki je: %d\n", zbroj);
}

int main(int argc, char *argv[]) {
    int i = 1;
    char num[MAX] = {0};

    num[0] = 49;

    while (i <= 1000) {
        multiply(num);
        i++;
    }

    sum_digits(num);

    system("PAUSE");
    return 0;
}
