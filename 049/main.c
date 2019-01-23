/*

Prime permutations
Problem 49

The arithmetic sequence, 1487, 4817, 8147, in which each of the terms increases
by 3330, is unusual in two ways: (i) each of the three terms are prime, and,
(ii) each of the 4-digit numbers are permutations of one another.

There are no arithmetic sequences made up of three 1-, 2-, or 3-digit primes,
exhibiting this property, but there is one other 4-digit increasing sequence.

What 12-digit number do you form by concatenating the three terms in this
sequence?


Solution:

2969 6299 9629

*/

#include <stdio.h>
#include <stdlib.h>

#define MAX 10000

int primes[MAX] = {0};
int totalPrimes;

int primes4[MAX] = {0};
int total4primes = 0;

int perm[MAX][3] = {0};
int permCount = 0;

int isPrime(int n) {
    for (int i = 0; i < totalPrimes - 1; i++) {
        if (n % primes[i] == 0) {
            return 0;
        }
    }
    return 1;
}

void reset(int *n) {
    for (int i = 0; i < 10; i++) {
        n[i] = 0;
    }
}

void findPermutations() {
    int i, j, k, l, m, diff;
    int digits[3][10];
    int num[3];

    for (i = 0; i < total4primes - 2; i++) {
        for (j = i + 1; j < total4primes - 1; j++) {
            for (k = j + 1; k < total4primes; k++) {
                num[0] = primes4[i];
                num[1] = primes4[j];
                num[2] = primes4[k];

                reset(digits[0]);
                reset(digits[1]);
                reset(digits[2]);

                // for each prime
                for (l = 0; l < 3; l++) {
                    // find digits
                    for (m = 0; m < 4; m++) {
                        digits[l][num[l] % 10]++;
                        num[l] /= 10;
                    }
                }

                // check if permutation
                diff = 0;
                for (l = 0; l < 10; l++) {
                    if (digits[0][l] != digits[1][l] || digits[0][l] != digits[2][l]) {
                        diff = 1;
                        break;
                    }
                }

                // save to array
                if (diff == 0) {
                    perm[permCount][0] = primes4[i];
                    perm[permCount][1] = primes4[j];
                    perm[permCount][2] = primes4[k];
                    permCount++;
                }
            }
        }
    }
}

void findUnusual() {
    int i, diff;
    for (i = 0; i < permCount; i++) {
        diff = perm[i][2] - perm[i][1];
        if (perm[i][1] - perm[i][0] == diff) {
            printf("%d %d %d\n", perm[i][0], perm[i][1], perm[i][2]);
        }
    }
}

int main() {
    int i;

    primes[0] = 2;
    primes[1] = 3;
    totalPrimes = 2;

    for (i = 4; i < MAX; i++) {
        if (isPrime(i)) {
            primes[totalPrimes++] = i;
            if (i >= 1000) {
                primes4[total4primes++] = i;
            }
        }
    }

    findPermutations();
    findUnusual();

    return (EXIT_SUCCESS);
}

