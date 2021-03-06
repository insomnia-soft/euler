/*
    projecteuler.net

    Pentagon numbers
    Problem 44

    Pentagonal numbers are generated by the formula, Pn=n(3n−1)/2. The first ten pentagonal numbers are:

    1, 5, 12, 22, 35, 51, 70, 92, 117, 145, ...

    It can be seen that P4 + P7 = 22 + 70 = 92 = P8. However, their difference, 70 − 22 = 48, is not pentagonal.

    Find the pair of pentagonal numbers, Pj and Pk, for which their sum and difference are pentagonal and D = |Pk - Pj| is minimised; what is the value of D?
*/

#include <stdio.h>
#define MAX 1000000000LL

int is_pentagonal(unsigned long long a) {
    double res = (sqrt(24.0 * a + 1.0) + 1.0) / 6.0;

    if (res - (int) res != 0) {
        return 0;
    }

    return 1;
}

int main(int argc, char *argv[]) {
    unsigned long long i;
    unsigned long long j;
    unsigned long long a;
    unsigned long long b;
    unsigned long long x = MAX;

    for (i = 1; i < (MAX - 1); i++) {
        a = i * (i * 3 - 1) / 2;

        for (j = i + 1; j < MAX; j++) {
            b = j * (j * 3 - 1) / 2;

            if (x > (b - a)) {
                if (is_pentagonal(a + b) && is_pentagonal(abs(a - b))) {
                    x = abs(b - a);
                    printf("i=%lld   j=%lld  |%lld - %lld| = %lld\n", i, j, a, b, x);
                }
            } else {
                break;
            }
        }
    }

    system("PAUSE");
    return 0;
}
