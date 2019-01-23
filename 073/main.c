/*

Counting fractions in a range
Problem 73

Consider the fraction, n/d, where n and d are positive integers. If n<d and
HCF(n,d)=1, it is called a reduced proper fraction.

If we list the set of reduced proper fractions for d ≤ 8 in ascending order of
size, we get:

1/8, 1/7, 1/6, 1/5, 1/4, 2/7, 1/3, 3/8, 2/5, 3/7, 1/2, 4/7, 3/5, 5/8, 2/3, 5/7,
3/4, 4/5, 5/6, 6/7, 7/8

It can be seen that there are 3 fractions between 1/3 and 1/2.

How many fractions lie between 1/3 and 1/2 in the sorted set of reduced proper
fractions for d <= 12,000?


Solution:

7295372

- ~1 sec

*/


#include <stdio.h>
#include <time.h>

#define LIMIT 12000
#define MAX 1100000

int num[MAX] = {0};
int denum[MAX] = {0};
unsigned long long fractCount = 0;

int main() {
    unsigned long long count = 0;
    int a, b;
    double ratio;
    double ratio_13 = 1 / 3.0;
    double ratio_12 = 1 / 2.0;

    num[0] = 0;
    denum[0] = 1;
    num[1] = 1;
    denum[1] = 1;
    fractCount = 2;

    clock_t tic;
    clock_t toc;

    tic = clock();
    do {
        a = num[fractCount - 1] + num[fractCount - 2];
        b = denum[fractCount - 1] + denum[fractCount - 2];

        if (b > LIMIT) {
            num[fractCount - 1] = 0;
            denum[fractCount - 1] = 0;

            fractCount--;
            continue;
        }

//        printf("%llu %llu [%d/%d]\n", count, fractCount, a, b);

        ratio = (double) a / b;

        if (ratio > ratio_13 && ratio < ratio_12) {
            count++;
        }
        num[fractCount] = num[fractCount - 1];
        denum[fractCount] = denum[fractCount - 1];
        num[fractCount - 1] = a;
        denum[fractCount - 1] = b;
        fractCount++;
    } while (fractCount > 1);
    toc = clock();

    printf("%llu\n", count);
    printf("Time: %f\n", (double) (toc - tic) / CLOCKS_PER_SEC);

    return 0;
}
