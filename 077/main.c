/*

Prime summations
Problem 77

It is possible to write ten as the sum of primes in exactly five different ways:

7 + 3
5 + 5
5 + 3 + 2
3 + 3 + 2 + 2
2 + 2 + 2 + 2 + 2

What is the first value which can be written as the sum of primes in over five
thousand different ways?


Solution:

71

- 20ms

*/

#include <stdio.h>

#define MAX 5000
#define MAX_PRIMES 100

int count = 0;

int primes[MAX_PRIMES];
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
    for (i = 2; primesCount < MAX_PRIMES; i++) {
        if (isPrime(i)) {
            primes[primesCount++] = i;
        }
    }
}

void step(int max, int sum, int maxChar) {
    int i;
    int tmpSum;
    int prime;

    for (i = 1; i <= maxChar; i++) {
        prime = primes[i - 1];
        tmpSum = sum + prime;
        if (tmpSum == max) {
            count++;
        }
        else if (tmpSum < max) {
            step(max, tmpSum, i);
        }
    }
}

int main() {
    int i;
    int value;

    generatePrimes();

    for (value = 10; value <= MAX; value++) {
        count = 0;
        for (i = 1; i < value; i++) {
            step(value, primes[i - 1], i);
        }
        if (count > MAX) {
            printf("%d\n", value);
            break;
        }
    }

    return 0;
}
