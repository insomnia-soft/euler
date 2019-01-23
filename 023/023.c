/*
    projecteuler.net

    Non-abundant sums
    Problem 23

    A perfect number is a number for which the sum of its proper divisors is exactly equal to the number. For example, the sum of the proper divisors of 28 would be 1 + 2 + 4 + 7 + 14 = 28, which means that 28 is a perfect number.

    A number n is called deficient if the sum of its proper divisors is less than n and it is called abundant if this sum exceeds n.

    As 12 is the smallest abundant number, 1 + 2 + 3 + 4 + 6 = 16, the smallest number that can be written as the sum of two abundant numbers is 24. By mathematical analysis, it can be shown that all integers greater than 28123 can be written as the sum of two abundant numbers. However, this upper limit cannot be reduced any further by analysis even though it is known that the greatest number that cannot be expressed as the sum of two abundant numbers is less than this limit.

    Find the sum of all the positive integers which cannot be written as the sum of two abundant numbers.
*/

#include <stdio.h>

int main(int argc, char *argv[]) {
    int i, j, k, diff, exist, sum;
    long total_sum;
    int x, y;

    int abu[50000] = {0};
    int count_abu = 0;

    for (i = 1; i <= 10000000; i++) {
        sum = 0;
        exist = 0;

        for (j = 1; j < i; j++) {
            if (i % j == 0)
            sum += j;
        }

        if (sum > i) {
            abu[count_abu] = i;
            count_abu++;
        }

        for (j = 0; j < (count_abu - 1); j++) {
            diff = i - abu[j];

            exist = 0;

            for (k = 0; k < count_abu; k++) {
                if (abu[k] == diff) {
                    x = abu[j];
                    y = abu[k];
                    exist = 1;
                    break;
                }
            }

            if (exist == 1) {
                break;
            }
        }

        if (exist == 0) {
            total_sum += i;
            printf("[%d] total sum = %d\n", i, total_sum);
        }
    }

    system("PAUSE");
    return 0;
}
