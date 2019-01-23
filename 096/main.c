/*

Su Doku
Problem 96

Su Doku (Japanese meaning number place) is the name given to a popular puzzle
concept. Its origin is unclear, but credit must be attributed to Leonhard Euler
who invented a similar, and much more difficult, puzzle idea called Latin
Squares. The objective of Su Doku puzzles, however, is to replace the blanks (or
zeros) in a 9 by 9 grid in such that each row, column, and 3 by 3 box contains
each of the digits 1 to 9. Below is an example of a typical starting puzzle grid
and its solution grid.

0 0 3   0 2 0   6 0 0       4 8 3   9 2 1   6 5 7
9 0 0   3 0 5   0 0 1       9 6 7   3 4 5   8 2 1
0 0 1   8 0 6   4 0 0       2 5 1   8 7 6   4 9 3

0 0 8   1 0 2   9 0 0       5 4 8   1 3 2   9 7 6
7 0 0   0 0 0   0 0 8       7 2 9   5 6 4   1 3 8
0 0 6   7 0 8   2 0 0       1 3 6   7 9 8   2 4 5

0 0 2   6 0 9   5 0 0       3 7 2   6 8 9   5 1 4
8 0 0   2 0 3   0 0 9       8 1 4   2 5 3   7 6 9
0 0 5   0 1 0   3 0 0       6 9 5   4 1 7   3 8 2

A well constructed Su Doku puzzle has a unique solution and can be solved by
logic, although it may be necessary to employ "guess and test" methods in order
to eliminate options (there is much contested opinion over this). The complexity
of the search determines the difficulty of the puzzle; the example above is
considered easy because it can be solved by straight forward direct deduction.

The 6K text file, sudoku.txt (right click and 'Save Link/Target As...'),
contains fifty different Su Doku puzzles ranging in difficulty, but all with
unique solutions (the first puzzle in the file is the example above).

By solving all fifty puzzles find the sum of the 3-digit numbers found in the
top left corner of each solution grid; for example, 483 is the 3-digit number
found in the top left corner of the solution grid above.


Solution:

24702

- 50 ms

*/



#include <stdio.h>

#define GRIDS 50

int grid[GRIDS][9][9] = {0};

void loadFile() {
    int gridIndex = -1, rowIndex = 0, tmp, i;
    char row[100];
    FILE *fp;

    fp = fopen("p096_sudoku.txt", "r");

    while (fgets(row, 100, fp)) {
        tmp = rowIndex % 10;

        if (tmp == 0) {
            gridIndex++;
        } else {
            for (i = 0; i < 10; i++) {
                grid[gridIndex][tmp - 1][i] = row[i] - 48;
            }
        }

        rowIndex++;
    }
}

void printGrid(int g[9][9]) {
    int i, j;

    for (i = 0; i < 9; i++) {
        for (j = 0; j < 9; j++) {
            if (g[i][j] == 0) {
                printf(". ");
            } else {
                printf("%d ", g[i][j]);
            }
        }
        printf("\n");
    }
    printf("\n");
}

// return 0 if not found, 1 if found
int inArr(int n, int arr[], int arrLen) {
    for (int i = 0; i < arrLen; i++) {
        if (arr[i] == n) {
            return 1;
        }
    }
    return 0;
}

int inRow(int g[9][9], int n, int row) {
    int i;
    for (i = 0; i < 9; i++) {
        if (g[row][i] == n) {
            return 1;
        }
    }
    return 0;
}

int inCol(int g[9][9], int n, int col) {
    int i;
    for (i = 0; i < 9; i++) {
        if (g[i][col] == n) {
            return 1;
        }
    }
    return 0;
}

int isSolved(int g[9][9]) {
    int r, c, solved = 1;
    for (r = 0; r < 9; r++) {
        for (c = 0; c < 9; c++) {
            if (g[r][c] == 0) {
                solved = 0;
                break;
            }
        }
    }
    if (solved) {
        return 1;
    }
    return 0;
}

int step(int g[9][9], int *changedRow, int *changedCol) {
    int i;
    int blockCol, blockRow;
    int row, col;
    int r, c;
    int possible[9][9][9];
    int possibleCount[9][9] = {0};

    int inBlock[9];
    int inBlockCount = 0;

    int count;
    int tmpRow, tmpCol;

    *changedRow = -1;
    *changedCol = -1;

    for (blockRow = 0; blockRow < 3; blockRow++) {
        for (blockCol = 0; blockCol < 3; blockCol++) {

            // pohraniti već upisane brojeve
            inBlockCount = 0;
            for (row = 0; row < 3; row++) {
                for (col = 0; col < 3; col++) {
                    r = blockRow * 3 + row;
                    c = blockCol * 3 + col;
                    if (g[r][c] > 0) {
                        inBlock[inBlockCount++] = g[r][c];
                    }
                }
            }

            // provjeriti za svako prazno polje u ostalim blockovima
            for (row = 0; row < 3; row++) {
                for (col = 0; col < 3; col++) {
                    r = blockRow * 3 + row;
                    c = blockCol * 3 + col;
                    if (g[r][c] == 0) {
                        for (i = 1; i <= 9; i++) {
                            if (!inArr(i, inBlock, inBlockCount) && !inRow(g, i, r) && !inCol(g, i, c)) {
                                possible[r][c][possibleCount[r][c]++] = i;
                            }
                        }
                        if (possibleCount[r][c] == 1) {
                            g[r][c] = possible[r][c][0];
                            *changedRow = r;
                            *changedCol = c;
                            return 1;
                        }
                    }
                }
            }

            // provjeri ponavlja li se neki broj samo jednom (u 3x3 polju)
            for (i = 1; i <= 9; i++) {
                count = 0;
                for (row = 0; row < 3; row++) {
                    for (col = 0; col < 3; col++) {
                        r = blockRow * 3 + row;
                        c = blockCol * 3 + col;
                        if (inArr(i, possible[r][c], possibleCount[r][c])) {
                            count++;
                            tmpRow = r;
                            tmpCol = c;
                        }
                    }
                }
                if (count == 1) {
                    g[tmpRow][tmpCol] = i;
                    *changedRow = tmpRow;
                    *changedCol = tmpCol;
                    return 1;
                }
            }
        }
    }

    return 0;
}

int findFirstEmpty(int g[9][9], int *r, int *c) {
    for (*r = 0; *r < 9; *r += 1) {
        for (*c = 0; *c < 9; *c += 1) {
            if (g[*r][*c] == 0) {
                return 1;
            }
        }
    }
    return 0;
}

int findPossibleSolution(int g[9][9], int r, int c, int possible[9], int *possibleCount) {
    int blockRow = r / 3;
    int blockCol = c / 3;
    int used[10] = {0};
    int x, y;

    for (y = 0; y < 3; y++) {
        for (x = 0; x < 3; x++) {
            used[g[blockRow * 3 + y][blockCol * 3 + x]] = 1;
        }
    }

    for (x = 0; x < 9; x++) {
        used[g[r][x]] = 1;
    }

    for (y = 0; y < 9; y++) {
        used[g[y][c]] = 1;
    }

    *possibleCount = 0;
    for (x = 1; x <= 9; x++) {
        if (used[x] == 0) {
            possible[*possibleCount] = x;
            *possibleCount += 1;
        }
    }

    return *possibleCount;
}

int recursion(int g[9][9]) {
    int possible[10] = {0};
    int possibleCount;
    int revert[100][2];
    int revertCount = 0;
    int r, c, i, j;
    int changedRow, changedCol;

    if (!findFirstEmpty(g, &r, &c)) {
        return 1;
    }

    findPossibleSolution(g, r, c, possible, &possibleCount);

    for (i = 0; i < possibleCount; i++) {
        g[r][c] = possible[i];

        revert[revertCount][0] = r;
        revert[revertCount][1] = c;
        revertCount++;

        while (1) {
            if (step(g, &changedRow, &changedCol)) {
                revert[revertCount][0] = changedRow;
                revert[revertCount][1] = changedCol;
                revertCount++;
            } else {
                break;
            }
        }

        if (isSolved(g)) {
            return 1;
        }

        if (recursion(g) == 1) {
            return 1;
        }

        for (j = 0; j < revertCount; j++) {
            g[revert[j][0]][revert[j][1]] = 0;
        }
        revertCount = 0;
    }

    return 0;
}

int main() {
    int i, r, c;
    int sum = 0;

    loadFile();

    for (i = 0; i < GRIDS; i++) {
        while (1) {
            if (!step(grid[i], &r, &c)) {
                break;
            }
        }

        recursion(grid[i]);

        printGrid(grid[i]);

        sum += grid[i][0][0] * 100 + grid[i][0][1] * 10 + grid[i][0][2];
    }

    printf("%d\n", sum);

    return 0;
}
