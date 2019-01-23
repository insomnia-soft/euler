/*
    projecteuler.net
    
    Digit fifth powers
    Problem 30

    Surprisingly there are only three numbers that can be written as the sum of fourth powers of their digits:

        1634 = 1^4 + 6^4 + 3^4 + 4^4
        8208 = 8^4 + 2^4 + 0^4 + 8^4
        9474 = 9^4 + 4^4 + 7^4 + 4^4

    As 1 = 1^4 is not a sum it is not included.

    The sum of these numbers is 1634 + 8208 + 9474 = 19316.

    Find the sum of all the numbers that can be written as the sum of fifth powers of their digits.
*/

#include <stdio.h>
#include <math.h>

int main(int argc, char *argv[]) {
    int i, sum, tmp, res = 0;

    for (i = 2; i < 10000000; i++) {	
        sum = 0;
        tmp = i;

        while (tmp) {
            sum = sum + pow(tmp % 10, 5);
            tmp /= 10;
        }

        if (i == sum) {
            printf("%d\n", i);
            res += sum;
        }
    }

    printf("Total sum: %d\n", res);

    system("PAUSE");
    return 0;
}
