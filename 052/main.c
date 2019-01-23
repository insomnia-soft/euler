/*

It can be seen that the number, 125874, and its double, 251748, contain exactly the same digits,
but in a different order.

Find the smallest positive integer, x, such that 2x, 3x, 4x, 5x, and 6x, contain the same digits.


Solution:

142857

*/

#include <stdio.h>
#include <stdlib.h>

void reset(int *a) {
    int i;
    for (i = 0; i < 10; i++) {
        a[i] = 0;
    }
}

void explode(int n, int *a) {
    int tmp;
    while (n > 0) {
        tmp = n % 10;
        a[tmp]++;
        n /= 10;
    }
}

int compare(int *a, int *b) {
    int i;
    for (i = 0; i < 10; i++) {
        if (a[i] != b[i]) {
            return 0;
        }
    }
    return 1;
}

int isPermutation(int *a, int n) {
    int nd[10] = {0};
    explode(n, nd);
    if (compare(a, nd)) {
        return 1;
    }
    return 0;
}

int main() {
    int i = 1;
    int j;
    int n;
    int loop = 1;
    int ret;
    int total = 0;
    int max = 6;
    
    int digits[10];
    
    do {
        i++;
        total = 1;
        reset(digits);
        explode(i, digits);
        for (j = 2; j <= max; j++) {
            ret = isPermutation(digits, j * i);
            if (ret == 0) {
                break;
            } else {
                total++;
            }
        }
        
        if (total == max) {
            printf("%d\n", i);
            break;
        }
        
    } while (loop);

    return (EXIT_SUCCESS);
}
