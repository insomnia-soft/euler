/*
    projecteuler.net

    Digit factorials
    Problem 34

    145 is a curious number, as 1! + 4! + 5! = 1 + 24 + 120 = 145.

    Find the sum of all numbers which are equal to the sum of the factorial of their digits.

    Note: as 1! = 1 and 2! = 2 are not sums they are not included.
*/

#include <stdio.h>

int factorial(int n) {
    if (n <= 1) {
        return 1;
    }
    return n * factorial(n - 1);
}

int main(int argc, char *argv[]) {
    int i = 3;
    int n;
    int total_sum = 0;
    int tmp, sum;

    while (1) {
        tmp = i;
        sum = 0;

        while (tmp > 0) {
            sum += factorial(tmp % 10);
            tmp = tmp / 10;

            if (sum == i && tmp == 0) {
                total_sum += i;
                printf("%d [%d]\n", i, total_sum);
            }
            else if (sum > i) {
                break;
            }
        }

        i++;
    }

    system("PAUSE");
    return 0;
}
