/*

Path sum: two ways
Problem 81

In the 5 by 5 matrix below, the minimal path sum from the top left to the bottom
right, by only moving to the right and down, is indicated in bold red and is
equal to 2427.

*131*  673   234   103    18
*201*  *96* *342*  965   150
 630   803  *746* *422*  111
 537   699   497  *121*  956
 805   732   524   *37* *331*

Find the minimal path sum, in matrix.txt (right click and "Save Link/Target
As..."), a 31K text file containing a 80 by 80 matrix, from the top left to the
bottom right by only moving right and down.


Solution:

427337

- 0ms
- split array to two triangles by diagonal NE-SW
- calculate sum for each field in diagonal in left triangle
- calculate sum for

*/


#include <stdio.h>
#include <limits.h>

#define SIZE 80

int arr[SIZE][SIZE] = {0};
long min = LONG_MAX;


int readFile() {
    FILE *fp;

    int i;
    int row = 0;
    int col = 0;
    int n = 0;
    char text[500];

    fp = fopen("p081_matrix.txt", "r");

    if (fp == NULL) {
        printf("Can't open file p081_matrix.txt!\n");
        return 0;
    }

    while (fgets(text, 500, fp) != NULL) {
        col = 0;

        for (i = 0; text[i] != 0; i++) {
            if (text[i] >= 48 && text[i] <= 57) {
                n *= 10;
                n += text[i] - 48;
            } else {
                arr[row][col] = n;
                n = 0;
                col++;
            }
        }

        row++;
    }

    fclose(fp);

    return 1;
}

void leftTree() {
    int row, col;
    int x, y;
    unsigned int a, b;

    int leftTreeArr[SIZE][SIZE] = {0};

    x = SIZE - 1;
    y = 0;

    while (x >= 0) {
        for (row = 0; row <= y; row++) {
            for (col = 0; col <= x; col++) {
                leftTreeArr[row][col] = arr[row][col];
            }
        }

        for (row = y; row >= 0; row--) {
            for (col = x; col >= 0; col--) {
                a = INT_MIN;
                b = INT_MIN;
                if (col < x) {
                    a = leftTreeArr[row][col + 1];
                }
                if (row < y) {
                    b = leftTreeArr[row + 1][col];
                }
                if (col == x && row == y) {
                    continue;
                }
                if (a < b) {
                    leftTreeArr[row][col] += leftTreeArr[row][col + 1];
                } else {
                    leftTreeArr[row][col] += leftTreeArr[row + 1][col];
                }
            }
        }

        arr[y][x] = leftTreeArr[0][0];

        x--;
        y++;
    }
}

void rightTree() {
    int row, col;

    for (row = 1; row < SIZE; row++) {
        for (col = SIZE - row; col < SIZE; col++) {
            if (arr[row][col - 1] < arr[row - 1][col]) {
                arr[row][col] += arr[row][col - 1];
            } else {
                arr[row][col] += arr[row - 1][col];
            }
        }
    }

    printf("%d\n", arr[SIZE - 1][SIZE - 1]);
}

int main() {
    if (!readFile()) {
        return 0;
    }

    leftTree();
    rightTree();

    return 0;
}