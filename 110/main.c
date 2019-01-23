/*

Diophantine reciprocals II
Problem 110

In the following equation x, y, and n are positive integers.

1   1   1
- + - = -
x   y   n

It can be verified that when n = 1260 there are 113 distinct solutions and this
is the least value of n for which the total number of distinct solutions exceeds
one hundred.

What is the least value of n for which the number of distinct solutions exceeds
four million?

NOTE: This problem is a much more difficult version of Problem 108 and as it is
well beyond the limitations of a brute force approach it requires a clever
implementation.


Solution:

9350130049860600

- 290 ms

*/

#include <stdio.h>

#define MAX 4000000
#define P 50
#define COLS 100000

int primes[P] = {0};
int primesCount = 0;
int powers[P];
int best[P] = {0};
int bestLen = 0;
char bestSumStr[COLS] = {0};

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
    for (i = 0; a[i] != 0; i++) {
        a[i] = 0;
    }
}

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

void intToStr(int a, char s[]) {
    int i = 0;
    while (a > 0) {
        s[i] = a % 10 + 48;
        a /= 10;
        i++;
    }
    s[i] = 0;
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
    char tmp[COLS];
    char tmp2[COLS] = {0};
    char sum[COLS] = {0};

    while (b[i] != 0) {
        reset(tmp);
        multiplySingle(a, b[i], tmp, i);
        add(tmp, tmp2, sum);
        copy(sum, tmp2);
        reset(sum);
        i++;
    }
    copy(tmp2, c);
}

void strPow(int a, int b, char *c) {
    int i;
    char mul[COLS] = {0};
    char tmp[COLS] = {0};
    char num[COLS] = {0};

    intToStr(a, tmp);
    intToStr(a, num);

    for (i = 1; i < b; i++) {
        multiply(tmp, num, mul);
        copy(mul, tmp);
        reset(mul);
    }
    copy(tmp, c);
}

// compare strings as numbers
// a > b returns 1
// a == b returns 0
// a < b returns -1
int strCompare(char a[], char b[]) {
    int i;
    int lenA = len(a);
    int lenB = len(b);

    if (lenA > lenB) {
        return 1;
    }
    else if (lenA < lenB) {
        return -1;
    }

    for (i = lenA - 1; i >= 0; i--) {
        if (a[i] > b[i]) {
            return 1;
        }
        else if (a[i] < b[i]) {
            return -1;
        }
    }

    return 0;
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

void generatePrimes() {
    int i;
    for (i = 2; primesCount < P + 1; i++) {
        if (isPrime(i)) {
            primes[primesCount] = i;
            primesCount++;
        }
    }
}

int isSmaller(int len) {
    int i;
    char n[COLS] = {0};
    char tmp[COLS] = {0};
    char tmp2[COLS] = {0};
    n[0] = 49;

    for (i = 0; i < len; i++) {
        reset(tmp);
        reset(tmp2);
        strPow(primes[i], powers[i], tmp);
        multiply(n, tmp, tmp2);
        reset(n);
        copy(tmp2, n);
    }

    if (strCompare(n, bestSumStr) == -1) {
        reset(bestSumStr);
        copy(n, bestSumStr);
        return 1;
    }
    return 0;
}

long calc(int len) {
    int i;
    long s = 1;
    for (i = 0; i < len; i++) {
        s *= 2 * powers[i] + 1;
    }
    s = (s + 1) / 2;
    if (s >= MAX) {
        if (isSmaller(len)) {
            bestLen = 0;
            for (i = 0; i < P; i++) {
                if (i < len) {
                    best[i] = powers[i];
                    bestLen++;
                } else {
                    best[i] = 0;
                }
            }
        }
    }
    return s;
}

void test(int len, int start, int val) {
    int i;
    for (i = 0; i < start; i++) {
        powers[i] = val;
    }
    if (calc(len) > MAX) {
        return;
    }
    if (start > 1) {
        test(len, start - 1, val);
    }
    while (1) {
        val++;
        for (i = 0; i < start; i++) {
            powers[i] = val;
        }
        if (calc(len) < MAX) {
            if (start > 1) {
                test(len, start - 1, val);
            }
        } else {
            return;
        }
    }
}

int main() {
    int i;
    int len = 15;

    generatePrimes();

    for (i = 0; i < P; i++) {
        powers[i] = 1;
    }

    for (i = 0; i < COLS - 1; i++) {
        bestSumStr[i] = 9 + 48;
    }

    while (len > 8) {
        test(len, len, 1);
        len--;
        for (i = 0; i < P; i++) {
            powers[i] = 1;
        }
    }

    print(bestSumStr);

    return 0;
}

