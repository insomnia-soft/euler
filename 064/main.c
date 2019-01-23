/*

Odd period square roots
Problem 64




Solution:

1322

*/


#include <stdio.h>

#define MAX 10000

int intPart = 0;

void reset(int a[]) {
    int i;
    for (i = 0; a[i] != 0; i++) {
        a[i] = 0;
    }
}

int len(int a[]) {
    int i = 0;
    for (i = 0; a[i] != 0; i++);
    return i;
}

int approximateSquareRoot(int n) {
    int digit;
    for (digit = 2; digit * digit < n; digit++);
    return digit - 1;
}

int step(int sqroot, int strPart[], int a, int numerator, int stepIndex) {
    int i;

    // step 1
    int b = a * -1;

    // step 2
    int c = sqroot + a * b;

    // step 3
    int repeat;
    do {
        repeat = 0;
        for (i = 2; i <= numerator; i++) {
            if (numerator % i == 0 && c % i == 0) {
                numerator /= i;
                c /= i;
                repeat = 1;
                break;
            }
        }
    } while (repeat);

    if (numerator != 1) {
        printf("ERROR, this shouldn't happen\n");
    }

    // step 4
    int d = (intPart + b) / c;
    int e = c * d;
    a = b - e;
    strPart[stepIndex] = d;

    if (c > 1) {
        step(sqroot, strPart, a, c, stepIndex + 1);
    } else {
        return 0;
    }
}

int fractionCount(int strPart[], int n) {
    int approx = approximateSquareRoot(n);
    int ret;
    intPart = approx;
    ret = step(n, strPart, intPart * -1, 1, 0);
    return ret;
}

int skip(int n) {
    int i;
    for (i = 2; i * i <= n; i++) {
        if (i * i == n) {
            return 1;
        }
    }
    return 0;
}

int main() {
    int i;
    int strPart[MAX] = {0};
    int strLen;
    int count = 0;

    for (i = 2; i <= 10000; i++) {
        if (skip(i)) {
            continue;
        }
        reset(strPart);
        fractionCount(strPart, i);
        strLen = len(strPart);
        if (strLen % 2 == 1) {
            count++;
        }
    }

    printf("Total with odd period: %d\n", count);

    return 0;
}
