/*

Cube digit pairs
Problem 90

Each of the six faces on a cube has a different digit (0 to 9) written on it;
the same is done to a second cube. By placing the two cubes side-by-side in
different positions we can form a variety of 2-digit numbers.

For example, the square number 64 could be formed:

see p090.gif

In fact, by carefully choosing the digits on both cubes it is possible to
display all of the square numbers below one-hundred: 01, 04, 09, 16, 25, 36, 49,
64, and 81.

For example, one way this can be achieved is by placing {0, 5, 6, 7, 8, 9} on
one cube and {1, 2, 3, 4, 8, 9} on the other cube.

However, for this problem we shall allow the 6 or 9 to be turned upside-down so
that an arrangement like {0, 5, 6, 7, 8, 9} and {1, 2, 3, 4, 6, 7} allows for
all nine square numbers to be displayed; otherwise it would be impossible to
obtain 09.

In determining a distinct arrangement we are interested in the digits on each
cube, not the order.

{1, 2, 3, 4, 5, 6} is equivalent to {3, 6, 4, 1, 2, 5}
{1, 2, 3, 4, 5, 6} is distinct from {1, 2, 3, 4, 5, 9}

But because we are allowing 6 and 9 to be reversed, the two distinct sets in the
last example both represent the extended set {1, 2, 3, 4, 5, 6, 9} for the
purpose of forming 2-digit numbers.

How many distinct arrangements of the two cubes allow for all of the square
numbers to be displayed?


Solution:

1217

- 50 ms

*/


#include <stdio.h>

// 10! / (6! * (10 - 6)!) = 210
#define COMBINATIONS 210

char cube1[COMBINATIONS][6];

char cubes[10000][2][6] = {0};
int cubesCount = 0;

int add(char c1[], char c2[]) {
    int c, i, equal;

    for (c = 0; c < cubesCount; c++) {
        equal = 1;
        for (i = 0; i < 6; i++) {
            if (c1[i] != cubes[c][0][i]) {
                equal = 0;
                break;
            }
        }

        if (equal) {
            for (i = 0; i < 6; i++) {
                if (c2[i] != cubes[c][1][i]) {
                    equal = 0;
                    break;
                }
            }
            if (equal) {
                return 0;
            }
        }
    }

    for (c = 0; c < cubesCount; c++) {
        equal = 1;
        for (i = 0; i < 6; i++) {
            if (c1[i] != cubes[c][1][i]) {
                equal = 0;
                break;
            }
        }

        if (equal) {
            for (i = 0; i < 6; i++) {
                if (c2[i] != cubes[c][0][i]) {
                    equal = 0;
                    break;
                }
            }
            if (equal) {
                return 0;
            }
        }
    }

    for (i = 0; i < 6; i++) {
        cubes[cubesCount][0][i] = c1[i];
        cubes[cubesCount][1][i] = c2[i];
    }
    cubesCount++;
}

int cubeHasNumber(char c[], char n) {
    for (int i = 0; i < 6; i++) {
        if (n == 6 || n == 9) {
            if (c[i] == 6 || c[i] == 9) {
                return 1;
            }
        } else {
            if (c[i] == n) {
                return 1;
            }
        }
    }
    return 0;
}

int test(char c1[], char c2[]) {
    int i, f1, f2;

    char t[9][2] = {
        {0, 1},
        {0, 4},
        {0, 9},
        {1, 6},
        {2, 5},
        {3, 6},
        {4, 9},
        {6, 4},
        {8, 1},
    };

    for (i = 0; i < 9; i++) {
        f1 = cubeHasNumber(c1, t[i][0]) && cubeHasNumber(c2, t[i][1]);
        f2 = cubeHasNumber(c1, t[i][1]) && cubeHasNumber(c2, t[i][0]);

        if (f1 == 0 && f2 == 0) {
            return 0;
        }
    }

    return 1;
}

int comb(char arr[], int n, int k, int first, int c1index) {
    int i, t;
    int count = 0;

    for (i = 0; i < k; i++) {
        arr[i] = i;
    }

    while (arr[k - 1] < n) {
        if (first) {
            for (i = 0; i < 6; i++) {
                cube1[count][i] = arr[i];
            }
            count++;
        } else {
            if (test(cube1[c1index], arr) && add(cube1[c1index], arr)) {
                count++;
            }
        }

        t = k - 1;
        while (t != 0 && arr[t] == n - k + t) {
            t--;
        }

        arr[t]++;

        for (i = t + 1; i < k; i++) {
            arr[i] = arr[i - 1] + 1;
        }
    }

    return count;
}

int main() {
    char numbers[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    int numCount = sizeof(numbers) / sizeof(numbers[0]);
    int total = 0;
    int i;

    comb(numbers, numCount, 6, 1, 0);

    for (i = 0; i < COMBINATIONS; i++) {
        total += comb(numbers, numCount, 6, 0, i);
    }

    printf("%d\n", total);

    return 0;
}
