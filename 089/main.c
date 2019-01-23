/*

Roman numerals
Problem 89

For a number written in Roman numerals to be considered valid there are basic
rules which must be followed. Even though the rules allow some numbers to be
expressed in more than one way there is always a "best" way of writing a
particular number.

For example, it would appear that there are at least six ways of writing the
number sixteen:

IIIIIIIIIIIIIIII
VIIIIIIIIIII
VVIIIIII
XIIIIII
VVVI
XVI

However, according to the rules only XIIIIII and XVI are valid, and the last
example is considered to be the most efficient, as it uses the least number of
numerals.

The 11K text file, roman.txt (right click and 'Save Link/Target As...'),
contains one thousand numbers written in valid, but not necessarily minimal,
Roman numerals; see About... Roman Numerals for the definitive rules for this
problem.

Find the number of characters saved by writing each of these in their minimal
form.

Note: You can assume that all the Roman numerals in the file contain no more
than four consecutive identical units.


Solution:

743

- 0 ms

*/


#include <stdio.h>

#define ROWS 1000
#define COLS 100

void reset(char a[], int len) {
    for (int i = 0; i < len; i++) {
        a[i] = 0;
    }
}

int len(char a[]) {
    int i = 0;
    for (i = 0; a[i] != 0; i++);
    return i;
}

int readFile(char row[ROWS][2][COLS]) {
    FILE *fp;

    int i;
    int loop;
    int r = 0;
    char tmp[COLS] = {0};

    fp = fopen("p089_roman.txt", "r");

    if (fp == NULL) {
        printf("Can't open file p089_roman.txt!\n");
        return 0;
    }

    while (fgets(tmp, 50, fp) != NULL) {
        i = 0;
        loop = 1;
        while (loop) {
            switch (tmp[i]) {
                case 'I':
                case 'V':
                case 'X':
                case 'L':
                case 'C':
                case 'D':
                case 'M':
                    row[r][0][i] = tmp[i];
                    break;

                default:
                    loop = 0;
            }
            i++;
        }
        reset(tmp, COLS);
        r++;
    }

    fclose(fp);

    return 1;
}

int romanToInt(char r[]) {
    int sum = 0;
    int i = 0;

    while (r[i] != 0) {
        switch (r[i]) {
            case 'I':
                if (r[i + 1] != 0) {
                    switch (r[i + 1]) {
                        case 'V':
                            sum += 4;
                            i++;
                            break;

                        case 'X':
                            sum += 9;
                            i++;
                            break;

                        default:
                            sum += 1;
                    }
                } else {
                    sum += 1;
                }
                break;

            case 'V':
                sum += 5;
                break;

            case 'X':
                if (r[i + 1] != 0) {
                    switch (r[i + 1]) {
                        case 'L':
                            sum += 40;
                            i++;
                            break;

                        case 'C':
                            sum += 90;
                            i++;
                            break;

                        default:
                            sum += 10;
                    }
                } else {
                    sum += 10;
                }
                break;

            case 'L':
                sum += 50;
                break;

            case 'C':
                if (r[i + 1] != 0) {
                    switch (r[i + 1]) {
                        case 'D':
                            sum += 400;
                            i++;
                            break;

                        case 'M':
                            sum += 900;
                            i++;
                            break;

                        default:
                            sum += 100;
                    }
                } else {
                    sum += 100;
                }
                break;

            case 'D':
                sum += 500;
                break;

            case 'M':
                sum += 1000;
                break;
        }

        i++;
    }

    return sum;
}

void strCat(char r[], char repeat, char roman) {
    int i, j;
    for (i = 0; r[i] != 0; i++);
    for (j = 0; j < repeat; i++, j++) {
        r[i] = roman;
    }
}

void intToRoman(int n, char r[]) {
    // int i, tmp, len = 0;
    int a, b, c, d;

    d = n % 10;
    n /= 10;
    c = n % 10;
    n /= 10;
    b = n % 10;
    n /= 10;
    a = n % 10;

    if (a > 0) {
        strCat(r, a, 'M');
    }

    if (b > 0 && b <= 3) {
        strCat(r, b, 'C');
    }
    else if (b == 4) {
        strCat(r, 1, 'C');
        strCat(r, 1, 'D');
    }
    else if (b >= 5 && b <= 8) {
        strCat(r, 1, 'D');
        strCat(r, b - 5, 'C');
    }
    else if (b == 9) {
        strCat(r, 1, 'C');
        strCat(r, 1, 'M');
    }

    if (c > 0 && c <= 3) {
        strCat(r, c, 'X');
    }
    else if (c == 4) {
        strCat(r, 1, 'X');
        strCat(r, 1, 'L');
    }
    else if (c >= 5 && c <= 8) {
        strCat(r, 1, 'L');
        strCat(r, c - 5, 'X');
    }
    else if (c == 9) {
        strCat(r, 1, 'X');
        strCat(r, 1, 'C');
    }

    if (d > 0 && d <= 3) {
        strCat(r, d, 'I');
    }
    else if (d == 4) {
        strCat(r, 1, 'I');
        strCat(r, 1, 'V');
    }
    else if (d >= 5 && d <= 8) {
        strCat(r, 1, 'V');
        strCat(r, d - 5, 'I');
    }
    else if (d == 9) {
        strCat(r, 1, 'I');
        strCat(r, 1, 'X');
    }
}

int main() {
    int i;
    int n;
    int sum = 0;
    char row[ROWS][2][COLS] = {0};

    if (!readFile(row)) {
        return 0;
    }

    for (i = 0; i < ROWS; i++) {
        n = romanToInt(row[i][0]);
        intToRoman(n, row[i][1]);
        sum += len(row[i][0]) - len(row[i][1]);
    }

    printf("%d\n", sum);

    return 0;
}
