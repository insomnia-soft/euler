/*

Pandigital Fibonacci ends
Problem 104

The Fibonacci sequence is defined by the recurrence relation:

    Fn = Fn−1 + Fn−2, where F1 = 1 and F2 = 1.

It turns out that F541, which contains 113 digits, is the first Fibonacci number
for which the last nine digits are 1-9 pandigital (contain all the digits 1 to
9, but not necessarily in order). And F2749, which contains 575 digits, is the
first Fibonacci number for which the first nine digits are 1-9 pandigital.

Given that Fk is the first Fibonacci number for which the first nine digits AND
the last nine digits are 1-9 pandigital, find k.


Solution:

329468

- 2 min 23 sec

*/

#include <stdio.h>
#define COLS 70000
#define PAND 9

int len(char a[]) {
    int i = 0;
    for (i = 0; a[i] != 0; i++);
    return i;
}

void copy(char a[], char b[]) {
    int i = 0;
    while (a[i] != 0) {
        b[i] = a[i];
        i++;
    }
    b[i] = 0;
}

void add(char a[], char b[], char c[]) {
    int i = 0;
    char tmp;
    char carry = 0;
    char cont_a = 1;
    char cont_b = 1;

    do {
        tmp = 0;
        if (cont_a && a[i] != 0) {
            tmp = a[i] - 48;
        } else {
            cont_a = 0;
        }

        if (cont_b && b[i] != 0) {
            tmp += b[i] - 48;
        } else {
            cont_b = 0;
        }

        tmp += carry;

        if (cont_a || cont_b || carry) {
            c[i] = tmp % 10 + 48;
            carry = tmp / 10;
        }
        i++;
    } while (cont_a || cont_b);
    c[i] = 0;
}

int test(char a[], int start) {
    int i;
    char t[10] = {0};
    for (i = start; i < start + PAND; i++) {
        t[a[i] - 48]++;
    }
    for (i = 1; i < PAND + 1; i++) {
        if (t[i] != 1) {
            return 0;
        }
    }

    return 1;
}

int main() {
    char a[COLS] = {0};
    char b[COLS] = {0};
    char c[COLS] = {0};
    long n = 2;

    a[0] = 1 + 48;
    b[0] = 1 + 48;

    while (len(b) < PAND + 1) {
        add(a, b, c);
        copy(b, a);
        copy(c, b);
        n++;
    }

    while (1) {
        if (test(b, 0)) {
            if (test(b, len(b) - PAND)) {
                printf("%ld\n", n);
                break;
            }
        }
        add(a, b, c);
        copy(b, a);
        copy(c, b);
        n++;
    }

    return 0;
}