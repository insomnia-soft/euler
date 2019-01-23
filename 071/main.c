/*

Ordered fractions
Problem 71

Consider the fraction, n/d, where n and d are positive integers. If n<d and
HCF(n,d)=1, it is called a reduced proper fraction.

If we list the set of reduced proper fractions for d ≤ 8 in ascending order of
size, we get:

1/8, 1/7, 1/6, 1/5, 1/4, 2/7, 1/3, 3/8, 2/5, 3/7, 1/2, 4/7, 3/5, 5/8, 2/3, 5/7,
3/4, 4/5, 5/6, 6/7, 7/8

It can be seen that 2/5 is the fraction immediately to the left of 3/7.

By listing the set of reduced proper fractions for d <= 1,000,000 in ascending
order of size, find the numerator of the fraction immediately to the left of
3/7.


Solution:

428570

- ~1h 5min

*/


#include <stdio.h>
#include <time.h>

#define MAX 1000000

#define TARGET_NUM 3
#define TARGET_DENUM 7

int primes[MAX] = {0};
int primesCount = 0;

int isPrime(int n) {
    int i = 5;
    int w = 2;

    if (n == 2) {
        return 1;
    }
    else if (n == 3) {
        return 1;
    }
    else if (n % 2 == 0) {
        return 0;
    }
    else if (n % 3 == 0) {
        return 0;
    }

    while (i * i <= n) {
        if (n % i == 0) {
            return 0;
        }
        i += w;
        w = 6 - w;
    }

    return 1;
}

void generatePrimes() {
    int i;
    for (i = 2; i < MAX; i++) {
        if (isPrime(i)) {
            primes[primesCount++] = i;
        }
    }
}

void reduceFraction(int *num, int *denum) {
    int i;
    int repeat;
    do {
        repeat = 0;
        for (i = 0; primes[i] < *denum / 2 + 1; i++) {
            if (*num % primes[i] == 0 && *denum % primes[i] == 0) {
                *num /= primes[i];
                *denum /= primes[i];
                repeat = 1;
                break;
            }
        }
    } while (repeat);
}

int main() {
    int i, j;
    int num, denum;
    int fract[2] = {0};
    double divided;
    double smallerThanThis = (double) TARGET_NUM / TARGET_DENUM;
    double biggerThanThis = 0;
    clock_t tic;
    clock_t toc;

    generatePrimes();

    for (i = 1; i < MAX; i++) {
        tic = clock();
        for (j = i + 1; j <= MAX; j++) {
            num = i;
            denum = j;
            divided = (double) num / denum;
            if (divided < smallerThanThis && divided > biggerThanThis) {
                reduceFraction(&num, &denum);
                fract[0] = num;
                fract[1] = denum;
                biggerThanThis = divided;
            }
        }
        toc = clock();
        if (i % 1000 == 0) {
            printf("%d [%f]\n", i, (double) (toc - tic) / CLOCKS_PER_SEC);
        }
    }

    printf("%d / %d\n", fract[0], fract[1]);

    return 0;
}
