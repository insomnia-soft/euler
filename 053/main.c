/*

Combinatoric selections
Problem 53

There are exactly ten ways of selecting three from five, 12345:

123, 124, 125, 134, 135, 145, 234, 235, 245, and 345

In combinatorics, we use the notation, 5C3 = 10.

In general, nCr = n! / (r!(n−r)!),where r <= n, n! = n×(n−1)×...×3×2×1,
and 0! = 1.

It is not until n = 23, that a value exceeds one-million: 23C10 = 1144066.

How many, not necessarily distinct, values of  nCr, for 1 <= n <= 100, are
greater than one-million?


Solution:

4075

*/

#include <stdlib.h>
#include <stdio.h>

#define BUFFER 100

int combinationCount(int n, int r) {
    int i, j;

    int a[BUFFER] = {0};
    int b[BUFFER] = {0};

    int lenA = 0;
    int lenB = 0;

    int posA;
    int posB;

    int divisor;
    int product = 1;

    // skraceno prema formuli
    // preskace se r! u nazivniku
    // zbog toga je brojnik generiran od broja r+1 do n

    // brojnik
    for (i = r + 1; i <= n; i++) {
        a[lenA++] = i;
    }

    // nazivnik
    for (i = 2; i <= (n - r); i++) {
        b[lenB++] = i;
    }

    // makni jednake brojeve
    if (n / 2 >= r) {
        j = 0;
        for (i = 0; i < lenB; i++) {
            if (a[j] == b[i]) {
                a[j] = 1;
                b[i] = 1;
                j++;
            }
        }
    }

    // skratiti razlomak, u brojniku ostaje 1
    for (divisor = 2; divisor <= n; divisor++) {
        posA = -1;
        posB = -1;
        // find A
        for (i = 0; i < lenA; i++) {
            if (a[i] % divisor == 0) {
                posA = i;
                break;
            }
        }
        for (i = 0; i < lenB; i++) {
            if (b[i] % divisor == 0) {
                posB = i;
                break;
            }
        }

        if (posA != -1 && posB != -1) {
            a[posA] /= divisor;
            b[posB] /= divisor;
            // repeat sequence
            divisor--;
        }
    }

    // ispis broja
    for (i = 0; i < lenA; i++) {
        product *= a[i];
        if (product > 1000000) {
            return 1;
        }
    }

    return 0;
}

int main() {
    int n = 10;
    int r = 4;
    int total = 0;

    for (n = 2; n <= 100; n++) {
        for (r = 2; r < n; r++) {
            total += combinationCount(n, r);
        }
    }

    printf("%d\n", total);

    return (EXIT_SUCCESS);
}
