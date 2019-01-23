/*

Counting fractions
Problem 72

Consider the fraction, n/d, where n and d are positive integers. If n<d and
HCF(n,d)=1, it is called a reduced proper fraction.

If we list the set of reduced proper fractions for d <= 8 in ascending order of
size, we get:

1/8, 1/7, 1/6, 1/5, 1/4, 2/7, 1/3, 3/8, 2/5, 3/7, 1/2, 4/7, 3/5, 5/8, 2/3, 5/7,
3/4, 4/5, 5/6, 6/7, 7/8

It can be seen that there are 21 elements in this set.

How many elements would be contained in the set of reduced proper fractions for
d <= 1,000,000?


Solution:

303963552391

- ~1h 45min
- https://en.wikipedia.org/wiki/Stern%E2%80%93Brocot_tree
- http://mathworld.wolfram.com/Stern-BrocotTree.html
- http://www.maths.surrey.ac.uk/hosted-sites/R.Knott/Fractions/fareySB.html

*/


#include <stdio.h>
#include <time.h>

#define LIMIT 1000000
#define MAX 1100000

int num[MAX] = {0};
int denum[MAX] = {0};
unsigned long long fractCount = 0;

int main() {
    unsigned long long count = 0;
    int a, b;

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

        num[fractCount] = num[fractCount - 1];
        denum[fractCount] = denum[fractCount - 1];
        num[fractCount - 1] = a;
        denum[fractCount - 1] = b;
        fractCount++;
        count++;
    } while (fractCount > 1);
    toc = clock();

    printf("%llu\n", count);
    printf("Time: %f\n", (double) (toc - tic) / CLOCKS_PER_SEC);

    return 0;
}

// version with recursion - doesn't work because too much recursion
//
//#include <stdio.h>
//
//#define LIMIT 10000
//
//unsigned long long step(int num_a, int denum_a, int num_b, int denum_b, int row) {
//    unsigned long long count = 0;
//    int a, b;
//
//    a = num_a + num_b;
//    b = denum_a + denum_b;
//
////    printf("%d\n", row);
//
//    if (b > LIMIT) {
//        return 0;
//    }
//
//    count++;
//
//    count += step(num_a, denum_a, a, b, row + 1);
//    count += step(a, b, num_a, denum_a, row + 1);
//
//    return count;
//}
//
//int main() {
//    unsigned long long count = 0;
//
////    count = step(0, 1, 1, 1, 1);
//
//    printf("%llu\n", count);
//
//    return 0;
//}