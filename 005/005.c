/*
    projecteuler.net

    Smallest multiple
    Problem 5

    2520 is the smallest number that can be divided by each of the numbers from 1 to 10 without any remainder.

    What is the smallest positive number that is evenly divisible by all of the numbers from 1 to 20?
*/

#include <stdio.h>
#include <stdlib.h>
#define MAX 20

int main(int argc, char *argv[]) {
    int i = MAX;
    int j;

    while (1) {
        for (j = 1; j <= MAX; j++) {
            if (i % j) {
                break;
            }

            if (j == MAX) {
                printf("%d\n", i);
                system("PAUSE");
                return 0;
            }
        }

        i += 20;
    }

    system("PAUSE");
    return 0;
}
