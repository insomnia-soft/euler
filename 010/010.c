/*
    projecteuler.net

    Summation of primes
    Problem 10

    The sum of the primes below 10 is 2 + 3 + 5 + 7 = 17.

    Find the sum of all the primes below two million.
*/

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    int i;
    int n = 2;
    int div = 0;

    int primes[200000] = {0};
    int primes_count = 0;

    long long sum = 0;

    while (1) {
        div = 0;

        for (i = 1; i < primes_count; i++) {
            if (n % primes[i] == 0) {
                div = 1;
                break;
            }
        }

        if (div == 0) {
            primes_count++;
            primes[primes_count] = n;
            sum += n;
        }

        if (n % 10000 == 0) {
            printf("%d\n", n);
        }

        if (n >= 2000000) {
            break;
        }

        n++;
    }

    printf("sum of all the primes below two million = %lld\n", sum);

    system("PAUSE");
    return 0;
}
