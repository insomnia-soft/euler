/*

Prime power triples
Problem 87

The smallest number expressible as the sum of a prime square, prime cube, and
prime fourth power is 28. In fact, there are exactly four numbers below fifty
that can be expressed in such a way:

28 = 2^2 + 2^3 + 2^4
33 = 3^2 + 2^3 + 2^4
49 = 5^2 + 2^3 + 2^4
47 = 2^2 + 3^3 + 2^4

How many numbers below fifty million can be expressed as the sum of a prime
square, prime cube, and prime fourth power?


Solution:

1097343

- 150 ms
- x^2 + 2^3 + 2^4 = 50.000.000
- biggest prime is below 7071

*/


#include <stdio.h>

#define MAX 7100
#define LIMIT 50000000

int primes[MAX] = {0};
int primesCount;

char count[LIMIT + 1] = {0};

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
    for (int i = 2; i < MAX; i++) {
        if (isPrime(i)) {
            primes[primesCount++] = i;
        }
    }
}

void find() {
    int i = 0;
    int j = 0;
    int k = 0;
    int sum = 0;

    while (1) {
        j = 0;
        while (1) {
            k = 0;
            while (1) {
                sum = primes[i] * primes[i];
                sum += primes[j] * primes[j] * primes[j];
                sum += primes[k] * primes[k] * primes[k] * primes[k];
                if (sum >= LIMIT) {
                    break;
                }
                count[sum] = 1;
                k++;
            }
            j++;
            if (primes[i] * primes[i] + primes[j] * primes[j] * primes[j] >= LIMIT) {
                break;
            }
        }
        i++;
        if (primes[i] * primes[i] + 16 >= LIMIT) {
            break;
        }
    }
}

int getCount() {
    int i, total = 0;
    for (i = 0; i < LIMIT; i++) {
        if (count[i] == 1) {
            total++;
        }
    }
    return total;
}

int main() {
    generatePrimes();
    find();
    printf("%d\n", getCount());
}
