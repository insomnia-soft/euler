/*

Path sum: four ways
Problem 83

NOTE: This problem is a significantly more challenging version of Problem 81.

In the 5 by 5 matrix below, the minimal path sum from the top left to the bottom
right, by moving left, right, up, and down, is indicated in bold red and is
equal to 2297.

*131*  673  *234* *103*  *18*
*201*  *96* *342*  965  *150*
 630   803   746  *422* *111*
 537   699   497  *121*  956
 805   732   524   *37* *331


Find the minimal path sum, in matrix.txt (right click and "Save Link/Target
As..."), a 31K text file containing a 80 by 80 matrix, from the top left to the
bottom right by moving left, right, up, and down.


Solution:

425185

- https://en.wikipedia.org/wiki/Dijkstra%27s_algorithm
- 120ms

*/


#include <stdio.h>
#include <limits.h>

#define SIZE 80

// 0 - input array
// 1 - sum
// 2 - visited
int arr[SIZE][SIZE][3] = {0};

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

    fp = fopen("p083_matrix.txt", "r");

    if (fp == NULL) {
        printf("Can't open file p083_matrix.txt!\n");
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
    arr[row][col][2] = 0;
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
        arr[minRow][minCol][2] = 1;
    }
    unvisitedCount--;

    return min_i;
}

void findNeighbours(int row, int col, int neighbour[3][2], int *count) {
    *count = 0;

    if (row > 0 && arr[row - 1][col][2] == 0) {
        neighbour[*count][0] = row - 1;
        neighbour[*count][1] = col;
        *count += 1;
    }

    if (col > 0 && arr[row][col - 1][2] == 0) {
        neighbour[*count][0] = row;
        neighbour[*count][1] = col - 1;
        *count += 1;
    }

    if (col < SIZE - 1 && arr[row][col + 1][2] == 0) {
        neighbour[*count][0] = row;
        neighbour[*count][1] = col + 1;
        *count += 1;
    }

    if (row < SIZE - 1 && arr[row + 1][col][2] == 0) {
        neighbour[*count][0] = row + 1;
        neighbour[*count][1] = col;
        *count += 1;
    }
}

int main() {
    int row;
    int col;

    int neighbour[4][2];
    int neighbourCount = 0;

    int nRow, nCol;

    int i;
    int sum;

    if (!readFile()) {
        return 0;
    }

    unvisitedCount = 0;

    for (row = 0; row < SIZE; row++) {
        for (col = 0; col < SIZE; col++) {
            addUnvisited(row, col);
            arr[row][col][1] = INT_MAX;
        }
    }

    arr[0][0][1] = arr[0][0][0];

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

    printf("%d\n", arr[SIZE - 1][SIZE - 1][1]);

    return 0;
}
