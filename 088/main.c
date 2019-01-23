/*

Product-sum numbers
Problem 88

A natural number, N, that can be written as the sum and product of a given set
of at least two natural numbers, {a1, a2, ... , ak} is called a product-sum
number: N = a1 + a2 + ... + ak = a1 × a2 × ... × ak.

For example, 6 = 1 + 2 + 3 = 1 × 2 × 3.

For a given set of size, k, we shall call the smallest N with this property a
minimal product-sum number. The minimal product-sum numbers for sets of size,
k = 2, 3, 4, 5, and 6 are as follows.

k=2: 4 = 2 × 2 = 2 + 2
k=3: 6 = 1 × 2 × 3 = 1 + 2 + 3
k=4: 8 = 1 × 1 × 2 × 4 = 1 + 1 + 2 + 4
k=5: 8 = 1 × 1 × 2 × 2 × 2 = 1 + 1 + 2 + 2 + 2
k=6: 12 = 1 × 1 × 1 × 1 × 2 × 6 = 1 + 1 + 1 + 1 + 2 + 6

Hence for 2<=k<=6, the sum of all the minimal product-sum numbers is 4+6+8+12 =
30; note that 8 is only counted once in the sum.

In fact, as the complete set of minimal product-sum numbers for 2<=k<=12 is {4,
6, 8, 12, 15, 16}, the sum is 61.

What is the sum of all the minimal product-sum numbers for 2<=k<=12000?


Solution:

7587457

- 57 sec

*/


#include <stdio.h>
#include <limits.h>
#include <stdlib.h>

#define MAX 12000
#define LIMIT 12200

int k[MAX + 1];
int s[LIMIT] = {0};

int getLimit(int len) {
    int i, tmp;

    tmp = LIMIT;
    for (i = 1; i < len; i++) {
        tmp /= 2;
    }

    return tmp + 1;
}

int getProd(int n[], int len) {
    int i, prod = 1;
    for (i = 0; i < len; i++) {
        prod *= n[i];
    }
    return prod;
}

int inc(int n[], int len, int max, int maxProd) {
    int i = 0, j, repeat = 1;
    int prod;

    while (repeat) {
        if (i > len) {
            return 0;
        }

        n[i]++;

        if (n[i] > max) {
            repeat = 1;
        } else {
            repeat = 0;
            for (j = 0; j < i; j++) {
                n[j] = n[i];
            }
        }

        prod = getProd(n, len);
        if (prod > maxProd) {
            repeat = 1;
        }

        i++;
    }

    return prod;
}

int testComb(int n[], int nLen) {
    int i;
    int sum = 0, prod = 1;
    int len;
    int tmpSum;

    for (i = 0; i < nLen; i++) {
        sum += n[i];
        prod *= n[i];
    }

    len = i;

    while (len <= MAX) {
        tmpSum = sum + len - nLen;
        if (tmpSum == prod && prod < k[len]) {
            k[len] = prod;
        }
        if (tmpSum > prod) {
            break;
        }
        len++;
    }
}

void set(int n[], int len) {
    for (int i = 0; i < 20; i++) {
        if (i < len) {
            n[i] = 2;
        } else {
            n[i] = 0;
        }
    }
}

int main() {
    int i;
    int n[20] = {0};
    int nLen;
    int max;
    int sum = 0;

    n[0] = 2;
    n[1] = 2;
    n[2] = 2;

    for (i = 0; i <= MAX; i++) {
        k[i] = INT_MAX;
    }

    for (nLen = 2; nLen <= 13; nLen++) {
        set(n, nLen);
        max = getLimit(nLen);
        do {
            testComb(n, nLen);
        } while (inc(n, nLen, max, LIMIT));
    }

    max = 0;
    for (i = 2; i <= MAX; i++) {
        s[k[i]] = 1;
        if (k[i] > max) {
            max = k[i];
        }
    }

    for (i = 2; i <= max; i++) {
        if (s[i] == 1) {
            sum += i;
        }
    }

    printf("%d\n", sum);

    return 0;
}
