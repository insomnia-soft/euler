/*

Square root convergents
Problem 57

It is possible to show that the square root of two can be expressed as an
infinite continued fraction.

√ 2 = 1 + 1/(2 + 1/(2 + 1/(2 + ... ))) = 1.414213...

By expanding this for the first four iterations, we get:

1 + 1/2 = 3/2 = 1.5
1 + 1/(2 + 1/2) = 7/5 = 1.4
1 + 1/(2 + 1/(2 + 1/2)) = 17/12 = 1.41666...
1 + 1/(2 + 1/(2 + 1/(2 + 1/2))) = 41/29 = 1.41379...

The next three expansions are 99/70, 239/169, and 577/408, but the eighth
expansion, 1393/985, is the first example where the number of digits in the
numerator exceeds the number of digits in the denominator.

In the first one-thousand expansions, how many fractions contain a numerator
with more digits than denominator?


Solution:

153

*/


#include <stdlib.h>
#include <stdio.h>

#define ITERATIONS 1000
#define MAX 500

int len(char a[]) {
    int i = 0;
    for (i = 0; a[i] != 0; i++);
    return i;
}

void reset(char a[]) {
    int i = 0;
    for (i = 0; i < MAX; i++) {
        a[i] = 0;
    }
}

void copy(char a[], char b[]) {
    int i = 0;
    while (a[i] != 0) {
        b[i] = a[i];
        i++;
    }
    b[i] = 0;
}

void add(char a[], char b[]) {
	int i = 0;
    int remainder = 0;
    int continue_a;
    int continue_b;
    char sum;

    do {
        continue_a = 0;
        continue_b = 0;
        sum = 0;
        if (a[i]) {
            sum += a[i] - 48;
            continue_a = 1;
        }
        if (b[i]) {
            sum += b[i] - 48;
            continue_b = 1;
        }

        if (continue_a || continue_b || remainder) {
            sum += remainder;
            b[i] = sum % 10 + 48;
            remainder = sum / 10;
        }
        i++;
    } while (continue_a || continue_b);
}

void multiplySingle(char a[], char b, char c[], int start) {
    int i;
    int carry = 0;
    int sum = 1;
    int cont = 0;

    for (i = 0; i < start; i++) {
        c[i] = 48;
    }

    i = 0;
    b -= 48;
    do {
        cont = 1;
        if (a[i] != 0) {
            sum = (a[i] - 48) * b;
        } else {
            cont = 0;
            sum = 0;
        }
        sum += carry;
        if (carry || cont) {
            c[i + start] = sum % 10 + 48;
        }
        carry = sum / 10;
        i++;
    } while (carry || cont);
}

void multiply(char a[], char b[], char c[]) {
    int i = 0;
    char tmp[MAX];
    char sum[MAX] = {0};

    while (b[i] != 0) {
        reset(tmp);
        multiplySingle(a, b[i], tmp, i);
        add(tmp, sum);
        i++;
    }
    copy(sum, c);
}

void swap(char a[], char b[]) {
    int i = 0;
    char tmp;
    while (a[i] != 0 || b[i] != 0) {
        tmp = a[i];
        a[i] = b[i];
        b[i] = tmp;
        i++;
    }
}

void iterate(char a[], char b[], int n) {
    int i;
    char c[MAX] = {0};
    char tmp[MAX];

    a[0] = 1 + 48;
    b[0] = 2 + 48;

    for (i = 1; i <= n; i++) {
        reset(c);
        if (i == n) {
            c[0] = 1 + 48;
        } else {
            c[0] = 2 + 48;
        }

        reset(tmp);
        multiply(c, b, tmp);
        reset(c);
        copy(tmp, c);

        add(c, a);

        if (i < n) {
            swap(a, b);
        }
    }
}

int main() {
    int i;
    int total = 0;
    char a[MAX];
    char b[MAX];

    for (i = 1; i <= ITERATIONS; i++) {
        reset(a);
        reset(b);
        iterate(a, b, i);
        if (len(a) > len(b)) {
            total++;
        }
    }

    printf("%d\n", total);

    return (EXIT_SUCCESS);
}