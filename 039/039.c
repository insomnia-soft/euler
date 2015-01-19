/*
    projecteuler.net

    Integer right triangles
    Problem 39

    If p is the perimeter of a right angle triangle with integral length sides, {a,b,c}, there are exactly three solutions for p = 120.

    {20,48,52}, {24,45,51}, {30,40,50}

    For which value of p ? 1000, is the number of solutions maximised?
*/

#include <stdio.h>

int main(int argc, char *argv[]) {
    int i, j, k, p, pmax, max, res;
    float f;

    pmax = 0;
    max = 0;
    res = 0;

    for (p = 1; p <= 1000; p++) {
        pmax = 0;
        for (i = 1; i < 1000; i++) {
            for (j = 1; j < 1000; j++) {
                f = sqrt(i * i + j * j);
                k = f;

                if (k == f) {
                    if (i + j + k == p) {
                        pmax++;
                        if (pmax > max) {
                            res = p;
                            max = pmax;
                        }
                    }
                }
            }
        }

        printf("i = %d\n", p);
    }

    printf("%d\n", res);

    system("PAUSE");
    return 0;
}
