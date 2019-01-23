/*

Cuboid route
Problem 86

A spider, S, sits in one corner of a cuboid room, measuring 6 by 5 by 3, and a
fly, F, sits in the opposite corner. By travelling on the surfaces of the room
the shortest "straight line" distance from S to F is 10 and the path is shown on
the diagram.

see p086.gif

However, there are up to three "shortest" path candidates for any given cuboid
and the shortest route doesn't always have integer length.

It can be shown that there are exactly 2060 distinct cuboids, ignoring
rotations, with integer dimensions, up to a maximum size of M by M by M, for
which the shortest route has integer length when M = 100. This is the least
value of M for which the number of solutions first exceeds two thousand; the
number of solutions when M = 99 is 1975.

Find the least value of M such that the number of solutions first exceeds one
million.


Solution:

1818

- 11 sec

*/


#include <stdio.h>

#define MAX 100000000

int sqr[MAX] = {0};

int initSqr() {
    for (int i = 1; i * i < MAX; i++) {
        sqr[i * i] = 1;
    }
}

int calc() {
    int x, y, z;
    int r, r1, r2, r3;
    int count = 0;

    for (x = 1; count <= 1000000; x++) {
        for (y = 1; y < x; y++) {
            for (z = y; z <= x; z++) {
                r1 = (x + z) * (x + z) + y * y;
                r2 = (y + z) * (y + z) + x * x;
                r3 = (x + y) * (x + y) + z * z;

                if (r1 < r2) {
                    if (r1 < r3) {
                        r = r1;
                    } else {
                        r = r3;
                    }
                } else {
                    if (r2 < r3) {
                        r = r2;
                    } else {
                        r = r3;
                    }
                }

                if (sqr[r] == 1) {
                    count++;
                    continue;
                }
            }
        }
    }

    return x - 1;
}

int main() {
    initSqr();
    printf("%d\n", calc());
    return 0;
}
