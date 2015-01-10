/*
	projecteuler.net

	1: Add all the natural numbers below one thousand that are multiples of 3 or 5.
*/

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    int res = 0, i;

    for (i = 1; i < 1000; i++) {
        if (i % 3 == 0 || i % 5 == 0) {
            res += i;
        }
    }

    printf("%d\n", res);

    system("PAUSE");
    return 0;
}
