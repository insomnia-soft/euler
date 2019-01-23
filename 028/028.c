/*
    projecteuler.net

    Number spiral diagonals
    Problem 28

    Starting with the number 1 and moving to the right in a clockwise direction a 5 by 5 spiral is formed as follows:

    21 22 23 24 25
    20  7  8  9 10
    19  6  1  2 11
    18  5  4  3 12
    17 16 15 14 13

    It can be verified that the sum of the numbers on the diagonals is 101.

    What is the sum of the numbers on the diagonals in a 1001 by 1001 spiral formed in the same way?
*/

#include <stdio.h>
#define MAX 1001

int main(int argc, char *argv[]) {
    int x, y, n;
    int dir = 2;
    long sum = 1;
    char array[MAX][MAX] = {0};

    array[MAX / 2][MAX / 2] = 1;
    array[MAX / 2][MAX / 2 + 1] = 1;

    n = 3;

    x = MAX / 2 + 1;
    y = MAX / 2 + 1;

    while (n <= MAX * MAX) {
        array[x][y] = 1;

        if (x == y) {
            sum += n;
        }
        else if ((MAX - x - 1) == y) {
            sum += n;
        }

        if (dir == 1) {
            if (array[x + 1][y] == 0) {
                dir = 2;
                x++;
            } else {
                y++;
            }
        }
        else if (dir == 2) {
            if (array[x][y - 1] == 0) {
                dir = 3;
                y--;
            } else {
                x++;
            }
        }
        else if (dir == 3) {
            if (array[x - 1][y] == 0) {
                dir = 4;
                x--;
            } else {
                y--;
            }
        }
        else if (dir == 4) {
            if (array[x][y + 1] == 0) {
                dir = 1;
                y++;
            }
            else {
                x--;
            }
        }

        n++;
    }

    printf("Suma: %d\n", sum);

    system("PAUSE");
    return 0;
}
