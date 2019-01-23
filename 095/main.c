/*

Amicable chains
Problem 95

The proper divisors of a number are all the divisors excluding the number
itself. For example, the proper divisors of 28 are 1, 2, 4, 7, and 14. As the
sum of these divisors is equal to 28, we call it a perfect number.

Interestingly the sum of the proper divisors of 220 is 284 and the sum of the
proper divisors of 284 is 220, forming a chain of two numbers. For this reason,
220 and 284 are called an amicable pair.

Perhaps less well known are longer chains. For example, starting with 12496, we
form a chain of five numbers:

12496 -> 14288 -> 15472 -> 14536 -> 14264 (-> 12496 -> ...)

Since this chain returns to its starting point, it is called an amicable chain.

Find the smallest member of the longest amicable chain with no element exceeding
one million.


Solution:

14316

- 22 sec

*/



#include <stdio.h>
#include <math.h>

#define MAX   2000000
#define MAX_N 1000000

long divSum[MAX] = {0};
long chain[MAX] = {0};
long chainCount = 0;

int inChain(long n) {
    long i;
    for (i = 0; i < chainCount - 1; i++) {
        if (chain[i] == n) {
            return i;
        }
    }
    return -1;
}

long divisorsSum(long n) {
    long i, sq = sqrt(n), sum = 0, ni;
    for (i = 2; i <= sq; i++) {
        if (n % i == 0) {
            sum += i;
            ni = n / i;
            if (ni != i) {
                sum += ni;
            }
        }
    }
    return sum + 1;
}

long checkChain(long *min) {
    long i;

    if (chain[chainCount - 1] >= MAX_N) {
        return 0;
    }

    *min = chain[chainCount - 1];
    for (i = chainCount - 2; i >= 0; i--) {
        if (chain[i] >= MAX_N) {
            return 0;
        }
        if (chain[i] == chain[chainCount - 1]) {
            return chainCount - i - 1;
        } else {
            if (chain[i] < *min) {
                *min = chain[i];
            }
        }
    }

    return 0;
}

int main() {
    long i = 1;
    long n;
    long max = 0;
    long max_i;
    long min;
    long minA;
    long tmp;

    for (i = 1; i < MAX; i++) {
        divSum[i] = divisorsSum(i);
    }

    for (i = 1; i < MAX; i++) {
        chainCount = 0;
        n = i;
        chain[chainCount++] = n;
        while (1) {
            if (n > MAX) {
                break;
                chainCount = 0;
            }
            n = divSum[n];
            if (inChain(n) == -1) {
                chain[chainCount++] = n;
            } else {
                chain[chainCount++] = n;
                tmp = checkChain(&min);
                if (tmp > max) {
                    max = tmp;
                    max_i = i;
                    minA = min;
                }
                break;
            }
        }
    }

    printf("n = %ld\nchain length = %ld\nminimum = %ld\n", max_i, max, minA);

    return 0;
}
