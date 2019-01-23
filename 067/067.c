/*
    projecteuler.net

    Maximum path sum II
    Problem 67

    By starting at the top of the triangle below and moving to adjacent numbers on the row below, the maximum total from top to bottom is 23.

    3
    7 4
    2 4 6
    8 5 9 3

    That is, 3 + 7 + 4 + 9 = 23.

    Find the maximum total from top to bottom in triangle.txt (right click and 'Save Link/Target As...'), a 15K text file containing a triangle with one-hundred rows.

    NOTE: This is a much more difficult version of Problem 18. It is not possible to try every route to solve this problem, as there are 299 altogether! If you could check one trillion (1012) routes every second it would take over twenty billion years to check them all. There is an efficient algorithm to solve it. ;o)
*/

#include <stdio.h>
#define MAX_ROWS 100
#define LINE 10000

int strlen(char *a) {
    int i = 0;
    for (i = 0; *(a + i) != 0; i++);
    return i;
}

int max(int a, int b) {
    if (a > b) {
        return a;
    }
    return b;
}

int main(int argc, char *argv[]) {
    FILE *fp;
    char row[LINE];
    int i, j;
    int rows = 0;
    int curr_row = 0;
    int curr_col = 0;
    int triangle[MAX_ROWS][MAX_ROWS] = {0};
    
    fp = fopen("p067_triangle.txt", "r");
    
    if (fp == NULL) {
        printf("can't open file 'p067_triangle.txt'\n");
        system("PAUSE");
        return 0;
    }
    
    while (fgets(row, LINE, fp) != NULL) {
        rows++;
        for (i = 0; i < strlen(row); i++) {
            if (row[i] >= 48 && row[i] <= 57) {
                triangle[curr_row][curr_col] = triangle[curr_row][curr_col] * 10 + row[i] - 48;
            } else {
                curr_col++;
            }
        }
        curr_col = 0;
        curr_row++;
    }
    
    for (i = 1; i < rows; i++) {
        for (j = 0; j <= i; j++) {
            if (j == 0) {
                triangle[i][j] += triangle[i - 1][j];
            }
            else if (j < i) {
                triangle[i][j] += max(triangle[i - 1][j - 1], triangle[i - 1][j]);
            }
            else {
                triangle[i][j] += triangle[i - 1][j - 1];
            }
        }
    }

    j = 0;
    for (i = 0; i < rows; i++) {
        if (triangle[rows - 1][i] > j) {
            j = triangle[rows - 1][i];
        }
    }
    
    printf("max = %d\n", j);

    system("PAUSE");
    return 0;
}
