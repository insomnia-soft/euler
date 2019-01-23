/*

Path sum: three ways
Problem 82

NOTE: This problem is a more challenging version of Problem 81.

The minimal path sum in the 5 by 5 matrix below, by starting in any cell in the
left column and finishing in any cell in the right column, and only moving up,
down, and right, is indicated in red and bold; the sum is equal to 994.

 131   673  *234* *103*  *18*
*201*  *96* *342*  965   150
 630   803   746   422   111
 537   699   497   121   956
 805   732   524    37   331

Find the minimal path sum, in matrix.txt (right click and "Save Link/Target
As..."), a 31K text file containing a 80 by 80 matrix, from the left column to
the right column.


Solution:

260324

- https://en.wikipedia.org/wiki/Dijkstra%27s_algorithm
- 8 sec

*/


#include <stdio.h>
#include <limits.h>

#define SIZE 80

// 0 - input array
// 1 - sum
int arr[SIZE][SIZE][2] = {0};

// 0 - row
// 1 - col
int unvisited[SIZE * SIZE][2] = {0};
int unvisitedCount = 0;

int readFile() {
    FILE *fp;

    int i;
    int row = 0;
    int col = 0;
    int n = 0;
    char text[500];

    fp = fopen("p082_matrix.txt", "r");

    if (fp == NULL) {
        printf("Can't open file p082_matrix.txt!\n");
        return 0;
    }

    while (fgets(text, 500, fp) != NULL) {
        col = 0;

        for (i = 0; text[i] != 0; i++) {
            if (text[i] >= 48 && text[i] <= 57) {
                n *= 10;
                n += text[i] - 48;
            } else {
                arr[row][col][0] = n;
                n = 0;
                col++;
            }
        }

        row++;
    }

    fclose(fp);

    return 1;
}

void addUnvisited(int row, int col) {
    unvisited[unvisitedCount][0] = row;
    unvisited[unvisitedCount][1] = col;
    unvisitedCount++;
}

int findMin(int *row, int *col) {
    int i, min_i, min = INT_MAX;
    int tmpRow = -1;
    int tmpCol = -1;
    int minRow, minCol;

    for (i = 0; i < unvisitedCount; i++) {
        tmpRow = unvisited[i][0];
        tmpCol = unvisited[i][1];
        if (arr[tmpRow][tmpCol][1] < min) {
            min = arr[tmpRow][tmpCol][1];
            min_i = i;
            minRow = tmpRow;
            minCol = tmpCol;
        }
    }

    *row = minRow;
    *col = minCol;

    if (min_i != unvisitedCount - 1) {
        unvisited[min_i][0] = unvisited[unvisitedCount - 1][0];
        unvisited[min_i][1] = unvisited[unvisitedCount - 1][1];
    }
    unvisitedCount--;

    return min_i;
}

void findNeighbours(int row, int col, int neighbour[3][2], int *count) {
    *count = 0;

    if (row > 0) {
        neighbour[*count][0] = row - 1;
        neighbour[*count][1] = col;
        *count += 1;
    }

    if (col < SIZE - 1) {
        neighbour[*count][0] = row;
        neighbour[*count][1] = col + 1;
        *count += 1;
    }

    if (row < SIZE - 1) {
        neighbour[*count][0] = row + 1;
        neighbour[*count][1] = col;
        *count += 1;
    }
}

int main() {
    int row;
    int col;
    int x;

    int neighbour[3][2];
    int neighbourCount = 0;

    int nRow, nCol;

    int i;
    int sum;
    int min = INT_MAX;


    if (!readFile()) {
        return 0;
    }

    for (x = 0; x < SIZE; x++) {
        unvisitedCount = 0;

        for (row = 0; row < SIZE; row++) {
            for (col = 0; col < SIZE; col++) {
                addUnvisited(row, col);
                arr[row][col][1] = INT_MAX;
            }
        }

        arr[x][0][1] = arr[x][0][0];

        while (unvisitedCount > 0) {
            findMin(&row, &col);
            findNeighbours(row, col, neighbour, &neighbourCount);

            for (i = 0; i < neighbourCount; i++) {
                nRow = neighbour[i][0];
                nCol = neighbour[i][1];
                sum = arr[row][col][1] + arr[nRow][nCol][0];
                if (sum < arr[nRow][nCol][1]) {
                    arr[nRow][nCol][1] = sum;
                }
            }
        }

        for (i = 0; i < SIZE; i++) {
            if (arr[i][SIZE - 1][1] < min) {
                min = arr[i][SIZE - 1][1];
            }
        }
    }

    printf("%d\n", min);

    return 0;
}
