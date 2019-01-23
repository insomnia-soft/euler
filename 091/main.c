/*

Right triangles with integer coordinates
Problem 91

The points P (x1, y1) and Q (x2, y2) are plotted at integer co-ordinates and are
joined to the origin, O(0,0), to form ΔOPQ.

see p091_1.gif

There are exactly fourteen triangles containing a right angle that can be formed
when each co-ordinate lies between 0 and 2 inclusive; that is,
0 <= x1, y1, x2, y2 <= 2.

see p091_2.gif

Given that 0 <= x1, y1, x2, y2 <= 50, how many right triangles can be formed?


Solution:

14234

- 90 ms

*/


#include <stdio.h>

#define MAX 50

int count = 0;

void rightTriangle(int x2, int y2, int x3, int y3) {
    int x1 = 0;
    int y1 = 0;

    int a2, b2, c2, tmp;

    a2 = (x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2);
    b2 = (x1 - x3) * (x1 - x3) + (y1 - y3) * (y1 - y3);
    c2 = (x2 - x3) * (x2 - x3) + (y2 - y3) * (y2 - y3);

    if (a2 > b2 && a2 > c2) {
        tmp = c2;
        c2 = a2;
        a2 = tmp;
    }
    else if (b2 > a2 && b2 > c2) {
        tmp = c2;
        c2 = b2;
        b2 = tmp;
    }

    if (a2 + b2 != c2) {
        return;
    }

//    printf("(0 0) (%d %d) (%d %d) = %d %d %d\n", x2, y2, x3, y3, a2, b2, c2);

    count++;
}

int main() {
    int p2, p3;
    int x2, y2, x3, y3;
    int m = MAX + 1;

    for (p2 = 1; p2 < m * m - 1; p2++) {
        x2 = p2 % m;
        y2 = p2 / m;

        for (p3 = p2 + 1; p3 < m * m; p3++) {
            x3 = p3 % m;
            y3 = p3 / m;

            rightTriangle(x2, y2, x3, y3);
        }

    }

    printf("%d\n", count);

    return 0;
}