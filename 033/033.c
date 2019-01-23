/*
    projecteuler.net

    Digit cancelling fractions
    Problem 33

    The fraction 49/98 is a curious fraction, as an inexperienced mathematician in attempting to simplify it may incorrectly believe that 49/98 = 4/8, which is correct, is obtained by cancelling the 9s.

    We shall consider fractions like, 30/50 = 3/5, to be trivial examples.

    There are exactly four non-trivial examples of this type of fraction, less than one in value, and containing two digits in the numerator and denominator.

    If the product of these four fractions is given in its lowest common terms, find the value of the denominator.
*/

#include <stdio.h>

int main(int argc, char *argv[]) {
    int i, j, a, b, prod1, prod2;
    float res1, res2;

    prod1 = 1;
    prod2 = 1;

    for (i = 10; i < 100; i++) {
        for (j = 10; j < 100; j++) {
            a = (int) (i / 10);
            b = (int) (j / 10);

            res1 = (float) a / b;
            res2 = (float) i / j;

            if (res1 != res2) {
                res1 = (float) i / j;

                a = (int) (i / 10);
                b = j % 10;

                res2 = (float) a / b;

                if (res1 == res2 && res1 < 1) {
                    a = i % 10;
                    b = (int) (j / 10);

                    if (a == b) {
                        prod1 *= i;
                        prod2 *= j;
                        printf("%d / %d\n", i, j);
                    }
                }
            }
        }
    }

    printf("%d / %d\n", prod1, prod2);

    a = 1;

    while (a == 1) {
        a = 0;

        for (i = 2; i < prod2; i++) {
            if (prod1 % i == 0 && prod2 % i == 0) {
                prod1 /= i;
                prod2 /= i;
                a = 1;
                break;
            }
        }
    }

    printf("%d / %d\n", prod1, prod2);
    printf("solution: %d\n", prod2);

    system("PAUSE");
    return 0;
}
