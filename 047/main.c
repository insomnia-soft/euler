/*

Distinct primes factors
Problem 47

The first two consecutive numbers to have two distinct prime factors are:

14 = 2 × 7
15 = 3 × 5

The first three consecutive numbers to have three distinct prime factors are:

644 = 2^2 × 7 × 23
645 = 3 × 5 × 43
646 = 2 × 17 × 19.

Find the first four consecutive integers to have four distinct prime factors each. What is the first of these numbers?


Solution:

134043

*/

#include <stdio.h>
#include <stdlib.h>

#define MAX 1000000
#define TARGET 4

int primes[MAX] = {0};
int totalPrimes = 0;

int distinct[3][4] = {0};

int isPrime(int n) {
    for (int i = 0; i < totalPrimes - 1; i++) {
        if (n % primes[i] == 0) {
            return 0;
        }
    }
    return 1;
}

int inArray(int *distinct, int count, int prime) {
    for (int i = 0; i < count; i++) {
        if (distinct[i] == prime) {
            return 1;
        }
    }
    return 0;
}

int distinctFactors(int n) {
    int distinct[TARGET + 1] = {0};
    int count = 0;
    int i;

    while (n != 1) {
        for (i = 0; i < totalPrimes; i++) {
            if (n % primes[i] == 0) {
                if (inArray(distinct, count, primes[i]) == 0) {
                    distinct[count] = primes[i];
                    count++;
                    if (count > TARGET) {
                        return 0;
                    }
                }

                n /= primes[i];
                break;
            }
        }
    }

    if (count == TARGET) {
        return 1;
    }

    return 0;
}

int main() {
    int i, j;

    primes[0] = 2;
    primes[1] = 3;
    totalPrimes = 2;

    int distinct = 0;

    for (i = 4; i < MAX; i++) {
        if (isPrime(i)) {
            primes[totalPrimes++] = i;
            distinct = 0;
        } else {
            if (distinctFactors(i) == 1) {
                distinct++;

                if (distinct == TARGET) {
                    break;
                }
            } else {
                distinct = 0;
            }
        }
    }

    for (j = TARGET - 1; j >= 0; j--) {
        printf("%d\n", i - j);
    }

    return (EXIT_SUCCESS);
}

