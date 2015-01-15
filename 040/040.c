/*
    projecteuler.net

    An irrational decimal fraction is created by concatenating the positive integers:

    0.123456789101112131415161718192021...
                 ^
                ^^^

    It can be seen that the 12^(th) digit of the fractional part is 1.

    If d_(n) represents the n^(th) digit of the fractional part, find the value of the following expression.

    d_(1) × d_(10) × d_(100) × d_(1000) × d_(10000) × d_(100000) × d_(1000000)


       1    5     10    15    20    25    30
    0. 1234 56789 10111 21314 15161 71819 2021...
*/

#include <stdio.h>

int rotate(int n, char *arr) {
    int i = 0;
    int tmp = n;
    int len = 0;

    do {
        tmp /= 10;
        len++;
    } while (tmp > 0);

    do {
        *(arr + len - i - 1) = n % 10 + 48;
        n /= 10;
        i++;
    } while (n > 0);

    return len;
}

int main(int argc, char *argv[]) {
    long i = 1;
    long index = 1;
    long index_count = 1;
    char arr[10] = {0};
    int prod = 1;
    int len;
    int j;

    while (1) {
        len = rotate(i, arr);

        for (j = 0; j < len; j++) {
            if (index == index_count) {
                prod *= arr[j] - 48;
                index *= 10;
            }
            index_count++;
        }

        i++;

        if (index == 1000000) {
            break;
        }
    }

    printf("%d\n", prod);

    system("PAUSE");
    return 0;
}
