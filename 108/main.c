/*

Diophantine reciprocals I
Problem 108

In the following equation x, y, and n are positive integers.

1   1   1
- + - = -
x   y   n

For n = 4 there are exactly three distinct solutions:

1    1   1
- + -- = -
5   20   4

1    1   1
- + -- = -
6   12   4

1   1   1
- + - = -
8   8   4

What is the least value of n for which the number of distinct solutions exceeds
one-thousand?

NOTE: This problem is an easier version of Problem 110; it is strongly advised
that you solve this one first.


Solution:

180180

- 3 min 42 sec

*/

#include <stdio.h>

int max = 0;

long calc(long n) {
    long x;
    double y;
    long yi;
    long sum = 0;

    for (x = n + 1; x <= n * 2; x++) {
        y = ((double) n * x) / ((double) x - n);
        yi = (long) y;
        if (y - yi == 0) {
            sum++;
        }
    }

    return sum;
}

int main() {
    long i = 1;
    long sum;

    while (1) {
        sum = calc(i);
        if (sum > 1000) {
            printf("%ld\n", i);
            break;
        }
        i++;
    }

    return 0;
}

