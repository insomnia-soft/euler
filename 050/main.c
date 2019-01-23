/*

Consecutive prime sum
Problem 50

The prime 41, can be written as the sum of six consecutive primes:
41 = 2 + 3 + 5 + 7 + 11 + 13

This is the longest sum of consecutive primes that adds to a prime below
one-hundred.

The longest sum of consecutive primes below one-thousand that adds to a prime,
contains 21 terms, and is equal to 953.

Which prime, below one-million, can be written as the sum of the most
consecutive primes?


Solution:

997651

*/

#include <stdio.h>
#include <stdlib.h>

#define MAX 1000000

int primes[MAX] = {0};
int totalPrimes;

int isPrime(int n) {
    for (int i = 0; i < totalPrimes - 1; i++) {
        if (n % primes[i] == 0) {
            return 0;
        }
    }
    return 1;
}

int getCount(int prime) {
    int i, j;
    int sum;
    int count = 0;
    int maxCount = 1;

    for (i = 0; i < totalPrimes; i++) {
        sum = 0;
        j = i;
        count = 0;

        do {
            sum += primes[j];
            count++;
            j++;
            if (sum == prime) {
                if (maxCount < count) {
                    maxCount = count;
                    break;
                }
            }
        } while (sum < prime);
    }
    return maxCount;
}

int findMaxCount() {
    int i;
    int prime;
    int count;
    int maxCount = 0;

    for (i = totalPrimes - 1; i > 0; i--) {
        count = getCount(primes[i]);
        if (count > maxCount) {
            maxCount = count;
            prime = primes[i];
        }
    }
    return prime;
}

int main() {
    int i = 4;
    int max;

    primes[0] = 2;
    primes[1] = 3;
    totalPrimes = 2;

    do {
        if (isPrime(i)) {
            primes[totalPrimes++] = i;
        }
        i++;
    } while (i < MAX);

    max = findMaxCount();
    printf("%d\n", max);

    return (EXIT_SUCCESS);
}
