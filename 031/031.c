/*
    projecteuler.net

    Coin sums
    Problem 31

    In England the currency is made up of pound, ?, and pence, p, and there are eight coins in general circulation:

        1p, 2p, 5p, 10p, 20p, 50p, ?1 (100p) and ?2 (200p).

    It is possible to make ?2 in the following way:

        1×?1 + 1×50p + 2×20p + 1×5p + 1×2p + 3×1p

    How many different ways can ?2 be made using any number of coins?
*/

#include <stdio.h>
#define MAX 200
#define COINS 7

int total = 0;
int step[COINS] = {1, 2, 5, 10, 20, 50, 100};

void coin(int sum, int index) {
    int i, res;

    for (i = 0; i <= (MAX / step[index]); i++) {
        res = sum + i * step[index];

        if (res < 200 && index < (COINS - 1)) {
            coin(res, index + 1);
        }
        else if (res == 200 && i > 0) {
            total++;
        }
        else if (res > 200) {
            break;
        }
    }
}

int main(int argc, char *argv[]) {
    int i;

    coin(0, 0);

    printf("total: %d\n", total + 1);

    system("PAUSE");
    return 0;
}
