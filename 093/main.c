/*

Arithmetic expressions
Problem 93

By using each of the digits from the set, {1, 2, 3, 4}, exactly once, and making
use of the four arithmetic operations (+, −, *, /) and brackets/parentheses, it
is possible to form different positive integer targets.

For example,

8 = (4 * (1 + 3)) / 2
14 = 4 * (3 + 1 / 2)
19 = 4 * (2 + 3) − 1
36 = 3 * 4 * (2 + 1)

Note that concatenations of the digits, like 12 + 34, are not allowed.

Using the set, {1, 2, 3, 4}, it is possible to obtain thirty-one different
target numbers of which 36 is the maximum, and each of the numbers 1 to 28 can
be obtained before encountering the first non-expressible number.

Find the set of four distinct digits, a < b < c < d, for which the longest set
of consecutive positive integers, 1 to n, can be obtained, giving your answer as
a string: abcd.


Solution:

1258

- 10 sec

*/


// case1:   x_x_x_x
// case2:   (x_x)_x_x
// case3:   x_(x_x)_x
// case4:   x_x_(x_x)
// case5:   (x_x)_(x_x)
// case6:   (x_x_x)_x
// case7:   x_(x_x_x)
// case8:   ((x_x)_x)_x
// case9:   (x_(x_x))_x
// case10:  x_((x_x)_x)
// case11:  x_(x_(x_x))


#include <stdio.h>

#define MAX 500

int list[MAX] = {0};
int listCount = 0;

int isPositiveInt(float f) {
    int d = (int) f;
    if (f - d != 0) {
        return 0;
    }
    return 1;
}

void addToList(float f) {
    if (!isPositiveInt(f) || f <= 0) {
        return;
    }
    for (int i = 0; i < listCount; i++) {
        if (list[i] == f) {
            return;
        }
    }
    list[listCount++] = (int) f;
}

float operation(float a, float b, int op) {
    switch (op) {
        case 1: return a + b;
        case 2: return a - b;
        case 3: return a * b;
        case 4: return a / b;
    }
}

// case1:   x_x_x_x
float case1(float n[], int op[]) {
    float a, b;
    // a * b _ c _ d
    if (op[0] >= 3) {
        a = operation(n[0], n[1], op[0]);

        // a * b * c _ d
        if (op[1] >= 3) {
            a = operation(a, n[2], op[1]);
            a = operation(a, n[3], op[2]);
        }
        // a * b + c * d
        else if (op[2] >= 3) {
            b = operation(n[2], n[3], op[2]);
            a = operation(a, b, op[1]);
        }
        else {
            a = operation(a, n[2], op[1]);
            a = operation(a, n[3], op[2]);
        }
    }
    // a + b * c _ d
    else if (op[1] >= 3) {
        a = operation(n[1], n[2], op[1]);

        // a + b * c * d
        if (op[2] >= 3) {
            a = operation(a, n[3], op[2]);
            a = operation(n[0], a, op[0]);
        // a + b * c + d
        } else {
            a = operation(n[0], a, op[0]);
            a = operation(a, n[3], op[2]);
        }
    }
    // a + b + c * d
    else if (op[2] >= 3) {
        b = operation(n[2], n[3], op[2]);
        a = operation(n[0], n[1], op[0]);
        a = operation(a, b, op[1]);
    }
    // a + b + c + d
    else {
        a = operation(n[0], n[1], op[0]);
        a = operation(a, n[2], op[1]);
        a = operation(a, n[3], op[2]);
    }
    return a;
}

// case2:   (x_x)_x_x
float case2(float n[], int op[]) {
    float a, b = operation(n[0], n[1], op[0]);
    if (op[2] >= 3 && op[1] < 3) {
        a = operation(n[2], n[3], op[2]);
        a = operation(b, a, op[1]);
    }
    else {
        b = operation(b, n[2], op[1]);
        a = operation(b, n[3], op[2]);
    }
    return a;
}

// case3:   x_(x_x)_x
float case3(float n[], int op[]) {
    float a = operation(n[1], n[2], op[1]);
    if (op[2] >= 3 && op[0] < 3) {
        a = operation(a, n[3], op[2]);
        a = operation(n[0], a, op[0]);
    } else {
        a = operation(n[0], a, op[0]);
        a = operation(a, n[3], op[2]);
    }
    return a;
}

// case4:   x_x_(x_x)
float case4(float n[], int op[]) {
    float a, b = operation(n[2], n[3], op[2]);
    if (op[1] >= 3 && op[0] < 3) {
        a = operation(n[1], b, op[1]);
        a = operation(n[0], a, op[0]);
    } else {
        a = operation(n[0], n[1], op[0]);
        a = operation(a, b, op[1]);
    }
    return a;
}

// case5:   (x_x)_(x_x)
float case5(float n[], int op[]) {
    float a = operation(n[0], n[1], op[0]);
    float b = operation(n[2], n[3], op[2]);
    a = operation(a, b, op[1]);
    return a;
}

// case6:   (x_x_x)_x
float case6(float n[], int op[]) {
    float a;
    if (op[1] >= 3 && op[0] < 3) {
        a = operation(n[1], n[2], op[1]);
        a = operation(n[0], a, op[0]);
        a = operation(a, n[3], op[2]);
    } else {
        a = operation(n[0], n[1], op[0]);
        a = operation(a, n[2], op[1]);
        a = operation(a, n[3], op[2]);
    }
}

// case7:   x_(x_x_x)
float case7(float n[], int op[]) {
    float a;
    if (op[2] >= 3 && op[1] < 3) {
        a = operation(n[2], n[3], op[2]);
        a = operation(n[1], a, op[1]);
        a = operation(n[0], a, op[0]);
    } else {
        a = operation(n[1], n[2], op[1]);
        a = operation(a, n[3], op[2]);
        a = operation(n[0], a, op[0]);
    }
}

// case8:   ((x_x)_x)_x
float case8(float n[], int op[]) {
    float a = operation(n[0], n[1], op[0]);
    a = operation(a, n[2], op[1]);
    a = operation(a, n[3], op[2]);
    return a;
}

// case9:   (x_(x_x))_x
float case9(float n[], int op[]) {
    float a = operation(n[1], n[2], op[1]);
    a = operation(n[0], a, op[0]);
    a = operation(a, n[3], op[2]);
    return a;
}

// case10:  x_((x_x)_x)
float case10(float n[], int op[]) {
    float a = operation(n[1], n[2], op[1]);
    a = operation(a, n[3], op[2]);
    a = operation(n[0], a, op[0]);
    return a;
}

// case11:  x_(x_(x_x))
float case11(float n[], int op[]) {
    float a = operation(n[2], n[3], op[2]);
    a = operation(n[1], a, op[1]);
    a = operation(n[0], a, op[0]);
    return a;
}

void test(int n[], int op[]) {
    int i;
    float num[4];

    for (i = 0; i < 4; i++) {
        num[i] = n[i];
    }

    // brackets combinations
    addToList(case1(num, op));
    addToList(case2(num, op));
    addToList(case3(num, op));
    addToList(case4(num, op));
    addToList(case5(num, op));
    addToList(case6(num, op));
    addToList(case7(num, op));
    addToList(case8(num, op));
    addToList(case9(num, op));
    addToList(case10(num, op));
    addToList(case11(num, op));
}

int inc(int n[], int min, int max, int len) {
    int i = 0, repeat;

    do {
        if (i >= len) {
            return 0;
        }

        repeat = 0;

        if (n[i] + 1 > max) {
            n[i] = min;
            repeat = 1;
        } else {
            n[i] += 1;
        }

        i++;
    } while (repeat);

    return 1;
}

void opCombination(int number[]) {
    int op[3] = {1, 1, 1};

    do {
        test(number, op);
    } while (inc(op, 1, 4, 3));
}

void swap(int *x, int *y) {
    int temp;
    temp = *x;
    *x = *y;
    *y = temp;
}

void numPermutation(int *a, int l, int r) {
    int i;
    if (l == r) {
        opCombination(a);
    } else {
        for (i = l; i <= r; i++) {
            swap((a+l), (a+i));
            numPermutation(a, l+1, r);
            swap((a+l), (a+i));
        }
    }
}

int countExpressible() {
    int i, found, n = 1;
    do {
        found = 0;
        for (i = 0; i < listCount; i++) {
            if (list[i] == n) {
                found = 1;
                n++;
                break;
            }
        }
    } while (found);
    return n;
}

int main() {
    int number[] = {1, 1, 1, 1};
    int n = sizeof(number) / sizeof(number[0]);
    int expr;
    int maxExpr = 0;
    int maxExprN[4];
    int i;

    do {
        listCount = 0;
        numPermutation(number, 0, n - 1);
        expr = countExpressible();
        if (maxExpr < expr) {
            maxExpr = expr;
            for (i = 0; i < 4; i++) {
                maxExprN[i] = number[3 - i];
            }
        }
    } while (inc(number, 1, 9, 4));

    for (i = 0; i < 4; i++) {
        printf("%d", maxExprN[i]);
    }
    printf("\n");

    return 0;
}

