/*
    projecteuler.net

    Pandigital products
    Problem 32

    We shall say that an n-digit number is pandigital if it makes use of all the digits 1 to n exactly once; for example, the 5-digit number, 15234, is 1 through 5 pandigital.

    The product 7254 is unusual, as the identity, 39 × 186 = 7254, containing multiplicand, multiplier, and product is 1 through 9 pandigital.

    Find the sum of all products whose multiplicand/multiplier/product identity can be written as a 1 through 9 pandigital.
    HINT: Some products can be obtained in more than one way so be sure to only include it once in your sum.
*/

#include <stdio.h>
#include <stdlib.h>

void reset(int *n) {
    int i = 0;

    while (i < 11) {
        *(n + i) = 0;
        i++;
    }
}

int main(int argc, char *argv[]) {
    int i, j, k, n, next, sum, x;
    int array[11] = {0};
    int numbers[100] = {0};
    int numbers_count = 0;

    i = 1;
    sum = 0;

    while (1) {
        for (j = 2; j < i; j++) {
            if (i % j == 0) {
                reset(array);

                k = i / j;
                next = 1;

                n = i;

                while (n > 0) {
                    if (array[n % 10] == 1 || n % 10 == 0) {
                        next = 0;
                        break;
                    } else {
                        array[n % 10] = 1;
                    }

                    n /= 10;
                }

                if (next == 1) {
                    n = j;
                    while (n > 0) {
                        if (array[n % 10] == 1 || n % 10 == 0) {
                            next = 0;
                            break;
                        } else {
                            array[n % 10] = 1;
                        }

                        n /= 10;
                    }
                }

                if (next == 1) {
                    n = k;
                    while (n > 0) {
                        if (array[n % 10] == 1 || n % 10 == 0) {
                            next = 0;
                            break;
                        } else {
                            array[n % 10] = 1;
                        }

                        n /= 10;
                    }
                }

                if (next == 1) {
                    for (n = 1; n <= 9; n++) {
                        if (array[n] == 0) {
                            next = 0;
                            break;
                        }
                    }
                }

                if (next == 1) {
                    next = 1;

                    for (x = 0; x < numbers_count; x++) {
                        if (i == numbers[x]) {
                            next = 0;
                            break;
                        }
                    }

                    if (next == 1) {
                        numbers[numbers_count] = i;
                        numbers_count++;
                        sum += i;
                        printf("%d * %d = %d [%d]\n", j, k, i, sum);
                    }
                }
            }
        }

        i++;
    }

    system("PAUSE");
    return 0;
}
