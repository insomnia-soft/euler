/*

Powerful digit sum
Problem 56

A googol (10^100) is a massive number: one followed by one-hundred zeros;
100^100 is almost unimaginably large: one followed by two-hundred zeros.
Despite their size, the sum of the digits in each number is only 1.

Considering natural numbers of the form, a^b, where a, b < 100, what is the
maximum digital sum?


Solution:

972

*/


#include <stdlib.h>
#include <stdio.h>

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

void intToStr(int a, char s[]) {
    int i = 0;
    while (a > 0) {
        s[i] = a % 10 + 48;
        a /= 10;
        i++;
    }
    s[i] = 0;
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

void strPow(int a, int b, char c[]) {
    int i;
    char mul[MAX] = {0};
    char tmp[MAX] = {0};
    char num[MAX] = {0};

    intToStr(a, tmp);
    intToStr(a, num);

    for (i = 1; i < b; i++) {
        multiply(tmp, num, mul);
        copy(mul, tmp);
        reset(mul);
    }
    copy(tmp, c);
}

int digitSum(char a[]) {
    int i;
    int sum = 0;
    for (i = 0; a[i] != 0; i++) {
        sum += a[i] - 48;
    }
    return sum;
}

int main() {
    int a, b;
    int sum;
    int max = 0;

    char n[MAX] = {0};

    for (a = 2; a < 100; a++) {
        for (b = 2; b < 100; b++) {
            reset(n);
            strPow(a, b, n);
            sum = digitSum(n);
            if (sum > max) {
                max = sum;
            }
        }
    }

    printf("%d\n", max);

    return (EXIT_SUCCESS);
}