/*

Prime generating integers
Problem 357

Consider the divisors of 30: 1,2,3,5,6,10,15,30.
It can be seen that for every divisor d of 30, d+30/d is prime.

Find the sum of all positive integers n not exceeding 100 000 000 such that for
every divisor d of n, d+n/d is prime.


Solution:

1739023853137

- few hours

 */

#include <stdio.h>

#define COLS 1000
#define MAX 100000000

void print(char a[]) {
    int len = 0, i;
    while (a[len] != 0) {
        len++;
    }
    for (i = len - 1; i >= 0; i--) {
        printf("%c", a[i]);
    }
    printf("\n");
}

void reset(char a[]) {
    int i;
    for (i = 0; i < COLS; i++) {
        a[i] = 0;
    }
}

void add2arg(char *a, char *b) {
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

void intToStr(int a, char s[]) {
    int i = 0;
    if (a == 0) {
        s[0] = 48;
        s[1] = 0;
        return;
    }
    while (a > 0) {
        s[i] = a % 10 + 48;
        a /= 10;
        i++;
    }
    s[i] = 0;
}

int isPrime(int n) {
    int i = 5;
    int w = 2;

    if (n == 2) {
        return 1;
    }
    else if (n == 3) {
        return 1;
    }
    else if (n % 2 == 0) {
        return 0;
    }
    else if (n % 3 == 0) {
        return 0;
    }

    while (i * i <= n) {
        if (n % i == 0) {
            return 0;
        }
        i += w;
        w = 6 - w;
    }

    return 1;
}

int test(long n) {
    int i, last = n / 2;
    for (i = 1; i <= last; i++) {
        if (n % i == 0) {
            if (!isPrime(i + n / i)) {
                return 0;
            }
        }
    }
    if (!isPrime(n + n / n)) {
        return 0;
    }
    return 1;
}

int main() {
    long i;
    char n[COLS] = {0};
    char sum[COLS] = {0};

    for (i = MAX; i > 0; i--) {
        if (test(i)) {
            printf("%ld  ", i);
            intToStr(i, n);
            add2arg(n, sum);
            print(sum);
        }
    }

    print(sum);

    return 0;
}

