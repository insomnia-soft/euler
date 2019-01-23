/*
    projecteuler.net

    Largest prime factor
    Problem 3

    The prime factors of 13195 are 5, 7, 13 and 29.

    What is the largest prime factor of the number 600851475143 ?
*/

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    int i;
    int n = 2;
    int div = 0;

    long long number = 0x8BE589EAC7LL;

    while (1) {
        div = 0;

        for (i = 2; i < n; i++) {
            if (n % i == 0) {
                div = 1;
                break;
            }
        }

        if (div == 0) {
            printf("%lld mod %d = %d\n", number, n, number % n);

            if (number % n == 0) {
                number /= n;

                if (n > number) {
                    break;
                }
            }
        }

        n++;
    }

    printf("%lld mod %d = %d\n", number, n, number % n);

    system("PAUSE");
    return 0;
}
