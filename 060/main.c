/*

Prime pair sets
Problem 60

The primes 3, 7, 109, and 673, are quite remarkable. By taking any two primes
and concatenating them in any order the result will always be prime. For
example, taking 7 and 109, both 7109 and 1097 are prime. The sum of these four
primes, 792, represents the lowest sum for a set of four primes with this
property.

Find the lowest sum for a set of five primes for which any two primes
concatenate to produce another prime.


Solution:

26033

*/


#include <stdio.h>

#define BIGGEST_PRIME 10000

int primes[BIGGEST_PRIME][2] = {0};
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
    int i = 3;
    int multiplyer = 10;
    while (i <= BIGGEST_PRIME) {
        if (isPrime(i)) {
            if (i > multiplyer) {
                multiplyer *= 10;
            }
            primes[primesCount][0] = i;
            primes[primesCount][1] = multiplyer;
            primesCount++;
        }
        i++;
    }
}

int testTwo(int i, int j) {
    if (!isPrime(primes[i][0] * primes[j][1] + primes[j][0])) { return 0; }
    if (!isPrime(primes[j][0] * primes[i][1] + primes[i][0])) { return 0; }
    return 1;
}

int testThree(int i, int j, int k) {
    if (!isPrime(primes[i][0] * primes[k][1] + primes[k][0])) { return 0; }
    if (!isPrime(primes[k][0] * primes[i][1] + primes[i][0])) { return 0; }
    if (!isPrime(primes[j][0] * primes[k][1] + primes[k][0])) { return 0; }
    if (!isPrime(primes[k][0] * primes[j][1] + primes[j][0])) { return 0; }
    return 1;
}

int testFour(int i, int j, int k, int l) {
    if (!isPrime(primes[i][0] * primes[l][1] + primes[l][0])) { return 0; }
    if (!isPrime(primes[l][0] * primes[i][1] + primes[i][0])) { return 0; }
    if (!isPrime(primes[j][0] * primes[l][1] + primes[l][0])) { return 0; }
    if (!isPrime(primes[l][0] * primes[j][1] + primes[j][0])) { return 0; }
    if (!isPrime(primes[k][0] * primes[l][1] + primes[l][0])) { return 0; }
    if (!isPrime(primes[l][0] * primes[k][1] + primes[k][0])) { return 0; }
    return 1;
}

int testFive(int i, int j, int k, int l, int m) {
    if (!isPrime(primes[i][0] * primes[m][1] + primes[m][0])) { return 0; }
    if (!isPrime(primes[m][0] * primes[i][1] + primes[i][0])) { return 0; }
    if (!isPrime(primes[j][0] * primes[m][1] + primes[m][0])) { return 0; }
    if (!isPrime(primes[m][0] * primes[j][1] + primes[j][0])) { return 0; }
    if (!isPrime(primes[k][0] * primes[m][1] + primes[m][0])) { return 0; }
    if (!isPrime(primes[m][0] * primes[k][1] + primes[k][0])) { return 0; }
    if (!isPrime(primes[l][0] * primes[m][1] + primes[m][0])) { return 0; }
    if (!isPrime(primes[m][0] * primes[l][1] + primes[l][0])) { return 0; }
    return 1;
}

void findPrimes() {
    int i, j, k, l, m;
    int sum;
    for (i = 0; i < primesCount - 4; i++) {
        for (j = i + 1; j < primesCount - 3; j++) {
            if (!testTwo(i, j)) {
                continue;
            }
            for (k = j + 1; k < primesCount - 2; k++) {
                if (!testThree(i, j, k)) {
                    continue;
                }
                for (l = k + 1; l < primesCount - 1; l++) {
                    if (!testFour(i, j, k, l)) {
                        continue;
                    }
                    for (m = l + 1; m < primesCount; m++) {
                        if (!testFive(i, j, k, l, m)) {
                            continue;
                        }

                        sum = primes[i][0] + primes[j][0] + primes[k][0] + primes[l][0] + primes[m][0];
                        printf("%d + %d + %d + %d + %d = %d\n", primes[i][0], primes[j][0], primes[k][0], primes[l][0], primes[m][0], sum);
                        return;
                    }
                }
            }
        }
    }
}

int main() {
    generatePrimes();
    findPrimes();
    return 0;
}

