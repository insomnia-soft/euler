/*
    projecteuler.net

    Goldbach's other conjecture
    Problem 46

    It was proposed by Christian Goldbach that every odd composite number can be written as the sum of a prime and twice a square.

    9 = 7 + 2×1^2
    15 = 7 + 2×2^2
    21 = 3 + 2×3^2
    25 = 7 + 2×3^2
    27 = 19 + 2×2^2
    33 = 31 + 2×1^2

    It turns out that the conjecture was false.

    What is the smallest odd composite that cannot be written as the sum of a prime and twice a square?
*/

#include <stdio.h>

int is_prime(long long n) {
    long long i;

    for (i = 2; i < (n / 2); i++) {
        if (n % i == 0) {
            return 0;
        }
    }

    return 1;
}

int is_natural(long double n) {
    if (n - (long long) n) {
        return 0;
    }

    return 1;
}

int main(int argc, char *argv[]) {
    long long i = 5, j, k;
    long double tmp;
    int win;

    while (1) {
        if (!is_prime(i)) {
            win = 1;

            for (j = 2; j < (i - 1); j++) {
                if (is_prime(j)) {
                    if (is_natural(sqrt((i - j) / 2))) {
                        win = 0;
                        break;
                    }
                }
            }

            if (win == 1) {
                printf("%lld\n", i);
                system("pause");
            }
        }

        i += 2;
    }

    system("PAUSE");
    return 0;
}
