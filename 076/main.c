/*

Counting summations
Problem 76

It is possible to write five as a sum in exactly six different ways:

4 + 1
3 + 2
3 + 1 + 1
2 + 2 + 1
2 + 1 + 1 + 1
1 + 1 + 1 + 1 + 1

How many different ways can one hundred be written as a sum of at least two
positive integers?


Solution:

190569291

- 0ms

*/

#include <stdio.h>

#define MAX 101

unsigned long long arr[MAX][MAX] = {0};

int main() {
    int col, row;
    int n = 100;

    arr[0][0] = 1;
    for (row = 1; row < MAX; row++) {
        arr[row][0] = 1;
    }
    for (row = 1; row < MAX; row++) {
        for (col = 1; col < MAX; col++) {
            if (row > col) {
                arr[row][col] = arr[row - 1][col];
            } else {
                arr[row][col] = arr[row - 1][col] + arr[row][col - row];
            }
        }
    }

    printf("%llu\n", arr[100][100]);

    return 0;
}

/*
 * v1 - 9 sec

#include <stdio.h>

#define MAX 100

int count = 0;

int reset(char n[]) {
    int i;
    for (i = 0; i < MAX; i++) {
        n[i] = 1;
    }
}

void step(int sum, int maxChar) {
    int i;
    int tmpSum;

    for (i = 1; i <= maxChar; i++) {
        tmpSum = sum + i;
        if (tmpSum == MAX) {
            count++;
        }
        else if (tmpSum < MAX) {
            step(tmpSum, i);
        }
    }
}

int main() {
    int i;

    for (i = 1; i < MAX; i++) {
        step(i, i);
    }

    printf("%d\n", count);
    return 0;
}
*/
