/*
    projecteuler.net

    Lattice paths
    Problem 15

    Starting in the top left corner of a 2×2 grid, and only being able to move to the right and down, there are exactly 6 routes to the bottom right corner.

    How many such routes are there through a 20×20 grid?
*/

#include <stdio.h>
#include <stdlib.h>
#define SIZE 20

long long paths = 0;

void find(int x, int y) {
    if (x == SIZE && y == SIZE) {
        paths++;
    } else {
        if (x < SIZE) {
            find(x + 1, y);
        }

        if (y < SIZE) {
            find(x, y + 1);
        }
    }
}

int main(int argc, char *argv[]) {
    printf("Please wait. Come back tomorrow.\n");
    find(0, 0);
    printf("Paths found: %lld\n", paths);

    system("PAUSE");
    return 0;
}
