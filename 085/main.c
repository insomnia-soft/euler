/*

Counting rectangles
Problem 85

By counting carefully it can be seen that a rectangular grid measuring 3 by 2
contains eighteen rectangles:

see p085.gif

Although there exists no rectangular grid that contains exactly two million
rectangles, find the area of the grid with the nearest solution.


Solution:

2772

- 80 ms

*/


#include <stdio.h>
#include <limits.h>

int main() {
    int gridW;
    int gridH;
    int rectW;
    int rectH;
    int count;
    int diff;

    int closestW;
    int closestH;
    int closestCount;
    int closestDiff = INT_MAX;

    for (gridW = 10; gridW <= 100; gridW++) {
        for (gridH = 10; gridH <= 100; gridH++) {
            count = 0;
            for (rectW = 1; rectW <= gridW; rectW++) {
                for (rectH = 1; rectH <= gridH; rectH++) {
                    count += (gridW - rectW + 1) * (gridH - rectH + 1);
                }
            }

            diff = 2000000 - count;
            if (diff < 0) {
                diff *= -1;
            }

            if (diff < closestDiff) {
                closestDiff = diff;
                closestW = gridW;
                closestH = gridH;
                closestCount = count;
            }
        }
    }

//    printf("%d * %d = %d [%d]\n", closestW, closestH, closestW * closestH, closestCount);
    printf("%d\n", closestW * closestH);

    return 0;
}
