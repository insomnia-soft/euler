/*

Totient permutation
Problem 70

Euler's Totient function, φ(n) [sometimes called the phi function], is used to
determine the number of positive numbers less than or equal to n which are
relatively prime to n. For example, as 1, 2, 4, 5, 7, and 8, are all less than
nine and relatively prime to nine, φ(9)=6.
The number 1 is considered to be relatively prime to every positive number, so
φ(1)=1.

Interestingly, φ(87109)=79180, and it can be seen that 87109 is a permutation of
79180.

Find the value of n, 1 < n < 107, for which φ(n) is a permutation of n and the
ratio n/φ(n) produces a minimum.


Solution:

8319823

- ~12 min
- generiraju se primarni brojevi do 10.000.000 (iako nisu svi potrebni)
- ako broj nije primaran, rastavlja ga se na faktore
- phi se računa putem algoritma:
https://en.wikipedia.org/wiki/Euler%27s_totient_function#Euler's_product_formula

*/


#include <stdio.h>

#define MAX 10000000
#define DIVISORS 20

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

void reset(int a[]) {
    int i;
    for (i = 0; i < DIVISORS; i++) {
        a[i] = 0;
    }
}

void addToDivisors(int divisor, int div[]) {
    int i = 0;
    for (; div[i] != 0; i++) {
        if (div[i] == divisor) {
            return;
        }
    }
    div[i] = divisor;
}

int getPhi(int n, int div[]) {
    int num = 1;
    int denum = 1;
    unsigned long long sumNum = n;
    unsigned long long sumDenum = 1;
    int i;

    for (i = 0; div[i] != 0; i++) {
        num = div[i] - 1;
        denum = div[i];
        sumNum *= num;
        sumDenum *= denum;
    }

    return sumNum / sumDenum;
}

void findDivisors(int n, int div[]) {
    int i;
    int repeat;

    do {
        repeat = 0;
        for (i = 0; n > 1; i++) {
            if (n % primes[i] == 0) {
                addToDivisors(primes[i], div);
                n /= primes[i];
                repeat = 1;
                break;
            }
        }
    } while (repeat);
}

int isPermutation(int n, int phi) {
    int i;
    int a[10] = {0};
    int b[10] = {0};
    while (n > 0) {
        a[n % 10]++;
        n /= 10;
    }
    while (phi > 0) {
        b[phi % 10]++;
        phi /= 10;
    }
    for (i = 0; i < 10; i++) {
        if (a[i] != b[i]) {
            return 0;
        }
    }
    return 1;
}

int main() {
    int div[DIVISORS];
    int phi;
    int i;
    int min_i;
    double tmp;
    double min = 100;

    generatePrimes();

    for (i = 2; i < MAX; i++) {
        if (i % 100000 == 0) {
            printf("%d\n", i);
        }
        if (isPrime(i)) {
            primes[primesCount++] = i;
        } else {
            reset(div);
            findDivisors(i, div);
            phi = getPhi(i, div);
            if (isPermutation(i, phi)) {
                tmp = (double) i / phi;
                if (tmp < min) {
                    min = tmp;
                    min_i = i;
                }
            }
        }
    }

    printf("min(n/phi(n)) = %f\n", min);
    printf("n = %d\n", min_i);

    return 0;
}
