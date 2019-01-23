/*

Totient maximum
Problem 69

Euler's Totient function, φ(n) [sometimes called the phi function], is used to
determine the number of numbers less than n which are relatively prime to n.
For example, as 1, 2, 4, 5, 7, and 8, are all less than nine and relatively
prime to nine, φ(9)=6.

n   Relatively Prime 	φ(n) 	n/φ(n)
2   1                   1       2
3   1,2                 2       1.5
4   1,3                 2       2
5   1,2,3,4             4       1.25
6   1,5                 2       3
7   1,2,3,4,5,6         6       1.1666...
8   1,3,5,7             4       2
9   1,2,4,5,7,8         6       1.5
10  1,3,7,9             4       2.5

It can be seen that n=6 produces a maximum n/φ(n) for n <= 10.

Find the value of n <= 1,000,000 for which n/φ(n) is a maximum.


Solution:

510510

- ~10 sec
- generiraju se primarni brojevi do 1.000.000 (iako nisu svi potrebni)
- ako broj nije primaran, rastavlja ga se na faktore
- phi se računa putem algoritma:
https://en.wikipedia.org/wiki/Euler%27s_totient_function#Euler's_product_formula

*/


#include <stdio.h>

#define MAX 1000000
#define DIVISORS 10

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

int main() {
    int div[DIVISORS];
    int phi;
    int i;
    int max_i;
    double tmp;
    double max = 0;

    generatePrimes();

    for (i = 2; i <= MAX; i++) {
        if (isPrime(i)) {
            primes[primesCount++] = i;
        } else {
            reset(div);
            findDivisors(i, div);
            phi = getPhi(i, div);
            tmp = (double) i / phi;
            if (tmp > max) {
                max = tmp;
                max_i = i;
            }
        }
    }

    printf("max(n/phi(n)) = %f\n", max);
    printf("n = %d\n", max_i);

    return 0;
}
