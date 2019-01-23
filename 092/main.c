/*

Square digit chains
Problem 92

A number chain is created by continuously adding the square of the digits in a
number to form a new number until it has been seen before.

For example,

44 -> 32 -> 13 -> 10 -> 1 -> 1
85 -> 89 -> 145 -> 42 -> 20 -> 4 -> 16 -> 37 -> 58 -> 89

Therefore any chain that arrives at 1 or 89 will become stuck in an endless
loop. What is most amazing is that EVERY starting number will eventually arrive
at 1 or 89.

How many starting numbers below ten million will arrive at 89?


Solution:

8581146

- 600 ms

*/


#include <stdio.h>

#define MAX 10000000

char end[MAX] = {0};

int add(int n) {
    int sum = 0;
    int a;

    while (n > 0) {
        a = n % 10;
        sum += a * a;
        n /= 10;
    }

    return sum;
}

int main() {
    int i, sum, count = 0;

    for (i = 1; i < MAX; i++) {
        sum = i;
        while (1) {
            if (end[sum]) {
                end[i] = end[sum];
                if (end[sum] == 89) {
                    count++;
                }
                break;
            }

            sum = add(sum);

            if (sum == 1 || sum == 89) {
                end[i] = sum;
                if (sum == 89) {
                    count++;
                }
                break;
            }
        }
    }

    printf("%d\n", count);

    return 0;
}