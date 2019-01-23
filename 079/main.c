/*

Passcode derivation
Problem 79

A common security method used for online banking is to ask the user for three
random characters from a passcode. For example, if the passcode was 531278, they
may ask for the 2nd, 3rd, and 5th characters; the expected reply would be: 317.

The text file, keylog.txt, contains fifty successful login attempts.

Given that the three characters are always asked for in order, analyse the file
so as to determine the shortest possible secret passcode of unknown length.


Solution:

73162890

- 13 sec
- brute force

*/


#include <stdio.h>

#define TESTS 50
#define COLS 1000

int len(char a[]) {
    int i = 0;
    for (i = 0; a[i] != 0; i++);
    return i;
}

void rotate(char a[]) {
    char tmp;
    int i, strLen;
    strLen = len(a);
    for (i = 0; i < strLen / 2; i++) {
        tmp = a[i];
        a[i] = a[strLen - i - 1];
        a[strLen - i - 1] = tmp;
    }
}

void add(char *a, char *b) {
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

int main() {
    char tests[TESTS][3] = {
        {3, 1, 9}, {6, 8, 0}, {1, 8, 0}, {6, 9, 0}, {1, 2, 9}, {6, 2, 0},
        {7, 6, 2}, {6, 8, 9}, {7, 6, 2}, {3, 1, 8}, {3, 6, 8}, {7, 1, 0},
        {7, 2, 0}, {7, 1, 0}, {6, 2, 9}, {1, 6, 8}, {1, 6, 0}, {6, 8, 9},
        {7, 1, 6}, {7, 3, 1}, {7, 3, 6}, {7, 2, 9}, {3, 1, 6}, {7, 2, 9},
        {7, 2, 9}, {7, 1, 0}, {7, 6, 9}, {2, 9, 0}, {7, 1, 9}, {6, 8, 0},
        {3, 1, 8}, {3, 8, 9}, {1, 6, 2}, {2, 8, 9}, {1, 6, 2}, {7, 1, 8},
        {7, 2, 9}, {3, 1, 9}, {7, 9, 0}, {6, 8, 0}, {8, 9, 0}, {3, 6, 2},
        {3, 1, 9}, {7, 6, 0}, {3, 1, 6}, {7, 2, 9}, {3, 8, 0}, {3, 1, 9},
        {7, 2, 8}, {7, 1, 6},
    };

    char n[COLS] = {0};
    char one[COLS] = {0};

    int i, j;
    int nLen;
    int next;

    int start;
    int index;
    int found;

    n[0] = 48;
    one[0] = 1 + 48;

    for (i = 0; i < TESTS; i++) {
        for (j = 0; j < 3; j++) {
            tests[i][j] += 48;
        }
    }

    while (1) {
        add(one, n);
        nLen = len(n);
        next = 0;

        for (i = 0; i < TESTS; i++) {
            start = -1;
            next = 0;
            for (index = 2; index >= 0; index--) {
                found = 0;
                for (j = start + 1; j < nLen; j++) {
                    if (tests[i][index] == n[j]) {
                        found = 1;
                        start = j;
                        break;
                    }
                }
                if (found == 0) {
                    next = 1;
                    break;
                }
            }
            if (next == 1) {
                break;
            }
        }

        if (next) {
            continue;
        }

        rotate(n);
        printf("%s\n", n);
        break;
    }

    return 0;
}
