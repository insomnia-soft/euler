/*

Spiral primes
Problem 58

Starting with 1 and spiralling anticlockwise in the following way, a square
spiral with side length 7 is formed.

37 36 35 34 33 32 31
38 17 16 15 14 13 30
39 18  5  4  3 12 29
40 19  6  1  2 11 28
41 20  7  8  9 10 27
42 21 22 23 24 25 26
43 44 45 46 47 48 49

It is interesting to note that the odd squares lie along the bottom right
diagonal, but what is more interesting is that 8 out of the 13 numbers lying
along both diagonals are prime; that is, a ratio of 8/13 ~ 62%.

If one complete new layer is wrapped around the spiral above, a square spiral
with side length 9 will be formed. If this process is continued, what is the
side length of the square spiral for which the ratio of primes along both
diagonals first falls below 10%?


Solution:

26241

*/


#include <stdlib.h>
#include <stdio.h>

int isPrime(long n) {
    long i;
    for (i = 2; i < n / 2; i++) {
        if (n % i == 0) {
            return 0;
        }
    }
    return 1;
}

int main() {
    long i = 0;
    long j;
    long n = 1;
    long corner[4];
    long step = 2;
    int primes = 0;
    float ratio = 1;

    while (ratio >= 0.1) {
        corner[0] = n + step;
        corner[1] = n + step * 2;
        corner[2] = n + step * 3;
        corner[3] = n + step * 4;

        step += 2;
        n = corner[3];

        for (j = 0; j < 3; j++) {
            if (isPrime(corner[j])) {
                primes++;
            }
        }

        ratio = (float) primes / ((i + 1) * 4 + 1);
        printf("Layer %ld (max number = %ld): %d / %ld = %f\n", i + 1, corner[3], primes, (i + 1) * 4 + 1, ratio);
        i++;
    }
    printf("%ld\n", corner[1] - corner[0] + 1);

    return (EXIT_SUCCESS);
}
