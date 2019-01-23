/*
    projecteuler.net

    Pandigital prime
    Problem 41

    We shall say that an n-digit number is pandigital if it makes use of all the digits 1 to n exactly once. For example, 2143 is a 4-digit pandigital and is also prime.

    What is the largest n-digit pandigital prime that exists?
*/

#include <stdio.h>

int array[9];
long long max;

void swap(int x, int y) {
    int tmp = *(array + x);
    *(array + x) = *(array + y);
    *(array + y) = tmp;
}

int is_prime(long long n) {
    long long i;

    for (i = 2; i <= (n / 2); i++) {
        if (n % i == 0) {
            return 0;
        }
    }
    return 1;
}

void test(len) {
    int i;
    long long n = 0;
    for (i = 0; i < len; i++) {
        n = n * 10 + array[i];
    }
    if (is_prime(n) && n > max) {
        max = n;
    }
}

void permute(int len, int n) {
    int c;

    if (n == 0) {
        test(len);
        return;
    }
    for (c = 0; c < n; c++) {
        permute(len, n - 1);
        swap(n % 2 ? 0 : c, n - 1);
    }
}

int main(int argc, char *argv[]) {
    long long i;
    int j;
    max = 0;

    for (i = 9; i > 0; i--) {
        for (j = 0; j < 9; j++) {
            array[j] = j + 1;
        }
        printf("searching %d digit numbers...\n", i);
        permute(i, i);
        if (max) {
            break;
        }
    }

    printf("max = %d\n", max);

    system("PAUSE");
    return 0;
}
