/*
    projecteuler.net

    Quadratic primes
    Problem 27

    Euler discovered the remarkable quadratic formula:

    n² + n + 41

    It turns out that the formula will produce 40 primes for the consecutive values n = 0 to 39. However, when n = 40, 402 + 40 + 41 = 40(40 + 1) + 41 is divisible by 41, and certainly when n = 41, 41² + 41 + 41 is clearly divisible by 41.

    The incredible formula  n² − 79n + 1601 was discovered, which produces 80 primes for the consecutive values n = 0 to 79. The product of the coefficients, −79 and 1601, is −126479.

    Considering quadratics of the form:

        n² + an + b, where |a| < 1000 and |b| < 1000

        where |n| is the modulus/absolute value of n
        e.g. |11| = 11 and |−4| = 4

    Find the product of the coefficients, a and b, for the quadratic expression that produces the maximum number of primes for consecutive values of n, starting with n = 0.
*/

#include <stdio.h>
#include <stdlib.h>

int is_prime(int n) {
    int i;

    for (i = 2; i < n; i++) {
        if (n % i == 0) {
            return 0;
        }
    }

    return 1;
}


int main(int argc, char *argv[]) {
    int n, a, b, prim, max, max_a, max_b;
    long res;

    max = 0;

    for (a = -999; a <= 999; a++) {
        for (b = -999; b <= 999; b++) {
            n = 0;

            do {
                res = n * n + a * n + b;

                if (res > 0) {
                    prim = is_prime(res);
                } else {
                    break;
                }

                n++;
            } while (prim == 1);

            n--;

            if (n > max) {
                max_a = a;
                max_b = b;
                max = n;
            }
        }
    }

    printf("%d * %d = %d\n", max_a, max_b, max_a * max_b);
    system("PAUSE");
    return 0;
}
