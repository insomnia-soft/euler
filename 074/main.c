/*

Digit factorial chains
Problem 74

The number 145 is well known for the property that the sum of the factorial of
its digits is equal to 145:

1! + 4! + 5! = 1 + 24 + 120 = 145

Perhaps less well known is 169, in that it produces the longest chain of numbers
that link back to 169; it turns out that there are only three such loops that
exist:

169 → 363601 → 1454 → 169
871 → 45361 → 871
872 → 45362 → 872

It is not difficult to prove that EVERY starting number will eventually get
stuck in a loop. For example,

69 → 363600 → 1454 → 169 → 363601 (→ 1454)
78 → 45360 → 871 → 45361 (→ 871)
540 → 145 (→ 145)

Starting with 69 produces a chain of five non-repeating terms, but the longest
non-repeating chain with a starting number below one million is sixty terms.

How many chains, with a starting number below one million, contain exactly sixty
non-repeating terms?


Solution:

402

- 3sec

*/


#include <stdio.h>

#define MAX 1000000

int main() {
    int i, j;
    int fact[10];
    int repeats[100];
    int repeatsCount;
    int repeatIndex;
    int found;
    int sum, tmp;
    int count = 0;

    // init factorials
    fact[0] = 1;
    for (i = 1; i < 10; i++) {
        fact[i] = fact[i - 1] * i;
    }

    repeatIndex = 0;

    for (i = 1; i < MAX; i++) {
        repeats[0] = i;
        repeatsCount = 1;

        tmp = i;

        do {
            sum = 0;
            do {
                sum += fact[tmp % 10];
                tmp /= 10;
            } while (tmp > 0);

            tmp = sum;
            repeats[repeatsCount++] = sum;

            found = 0;
            for (j = 0; j < repeatsCount - 1; j++) {
                if (repeats[j] == sum) {
                    found = 1;
                }
            }

            if (found == 1 && repeatsCount - 1 == 60) {
                count++;
            }
        } while (!found);
    }

    printf("%d\n", count);

    return 0;
}