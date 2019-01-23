/*

Singular integer right triangles
Problem 75

It turns out that 12 cm is the smallest length of wire that can be bent to form
an integer sided right angle triangle in exactly one way, but there are many
more examples.

12 cm: (3,4,5)
24 cm: (6,8,10)
30 cm: (5,12,13)
36 cm: (9,12,15)
40 cm: (8,15,17)
48 cm: (12,16,20)

In contrast, some lengths of wire, like 20 cm, cannot be bent to form an integer
sided right angle triangle, and other lengths allow more than one solution to be
found; for example, using 120 cm it is possible to form exactly three different
integer sided right angle triangles.

120 cm: (30,40,50), (20,48,52), (24,45,51)

Given that L is the length of the wire, for how many values of L <= 1,500,000
can exactly one integer sided right angle triangle be formed?


Solution:

161667

- 60ms
- https://en.wikipedia.org/wiki/Tree_of_primitive_Pythagorean_triples
- https://everything2.com/user/abiessu/writeups/Pythagorean+Triple

*/


#include <stdio.h>

#define MAX 1500000

int main() {
    int i, col, row = 0, index, sum;
    int tmp[3];
    int child[3][3];
    int primTrip[1000][3] = {0};
    int primTripCount = 0;
    int repeats[MAX + 1] = {0};
    int matrix[3][3][3] = {
        {{1, -2, 2},
         {2, -1, 2},
         {2, -2, 3}},
        {{1, 2, 2},
         {2, 1, 2},
         {2, 2, 3}},
        {{-1, 2, 2},
         {-2, 1, 2},
         {-2, 2, 3}},
    };

    primTrip[0][0] = 3;
    primTrip[0][1] = 4;
    primTrip[0][2] = 5;
    primTripCount = 1;

    // first primitive pythagorean triple
    repeats[3 + 4 + 5]++;
    sum = 0;
    // add non-primitive triples
    for (i = 2; sum <= MAX; i++) {
        sum = 3 * i + 4 * i + 5 * i;
        if (sum <= MAX) {
            repeats[sum]++;
        }
    }

    // loop while there are primitive triples in array
    do {
        // pop triple from array
        for (i = 0; i < 3; i++) {
            tmp[i] = primTrip[primTripCount - 1][i];
            primTrip[primTripCount - 1][row] = 0;
        }
        primTripCount--;

        // calculate matrix
        for (i = 0; i < 3; i++) {
            for (row = 0; row < 3; row++) {
                sum = 0;
                for (col = 0; col < 3; col++) {
                    sum += matrix[i][row][col] * tmp[col];
                }
                child[i][row] = sum;
            }
        }

        // for each new child (parent has 3 children)
        for (index = 0; index < 3; index++) {

            // a + b + c
            sum = 0;
            for (row = 0; row < 3; row++) {
                sum += child[index][row];
            }

            if (sum <= MAX) {
                // found a new triple
                repeats[sum]++;

                // add it to array
                for (row = 0; row < 3; row++) {
                    primTrip[primTripCount][row] = child[index][row];
                }
                primTripCount++;

                // add non-primitive triples
                for (i = 2; sum <= MAX; i++) {
                    sum = 0;
                    for (row = 0; row < 3; row++) {
                        sum += child[index][row] * i;
                    }
                    if (sum <= MAX) {
                        repeats[sum]++;
                    }
                }
            }
        }
    } while (primTripCount);

    // count single triples
    sum = 0;
    for (i = 0; i < MAX + 1; i++) {
        if (repeats[i] == 1) {
            sum++;
        }
    }
    printf("%d\n", sum);

    return 0;
}
