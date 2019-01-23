/*
    projecteuler.net

    Reciprocal cycles
    Problem 26

    A unit fraction contains 1 in the numerator. The decimal representation of the unit fractions with denominators 2 to 10 are given:

     1/2 = 0.5
     1/3 = 0.(3)
     1/4 = 0.25
     1/5 = 0.2
     1/6 = 0.1(6)
     1/7 = 0.(142857)
     1/8 = 0.125
     1/9 = 0.(1)
    1/10 = 0.1

    Where 0.1(6) means 0.166666..., and has a 1-digit recurring cycle. It can be seen that 1/7 has a 6-digit recurring cycle.

    Find the value of d < 1000 for which 1/d contains the longest recurring cycle in its decimal fraction part.
*/

#include <stdio.h>
#define MAX 50000

void reset(char *a) {
    int i = 0;

    while (*(a + i) != 0) {
        *(a + i) = 0;
        i++;
    }
}

void reset_int(int *a) {
    int i = 0;

    while (*(a + i) != 0) {
        *(a + i) = 0;
        i++;
    }
}

int field_len(int *a) {
    int i = 0;

    while (*(a + i)) {
        i++;
    }

    return i;
}

int find_match(int *a, int *x, int *y) {
    int i, j, len;

    len = field_len(a);

    for (i = 0; i < len; i++) {
        for (j = i + 1; j < len; j++) {
            if (*(a + i) == *(a + j)) {
                *x = i;
                *y = j;
                return 1;
            }
        }
    }

    return 0;
}

int main(int argc, char *argv[]) {
    int i, j, n, a, b, max, max_i;

    int ost[MAX] = {0};
    char res[MAX] = {0};
    int counter;

    max = 0;

    for (i = 1; i <= 1000; i++) {
        n = 1;
        counter = 0;

        do {
            if ((float) n / i > 0) {
                n *= 10;
            }

            res[counter] = n / i + 48;
            n %= i;
            ost[counter] = n;
            counter++;

            if (n > 0 && find_match(ost, &a, &b) == 1) {
                if ((b - a) > max) {
                    max = b - a;
                    max_i = i;
                }
                break;
            }

            if (counter >= MAX) {
                break;
            }
        } while (n != 0);

        reset(res);
        reset_int(ost);
    }

    printf("%d: %d\n", max_i, max);

    system("PAUSE");
    return 0;
}
