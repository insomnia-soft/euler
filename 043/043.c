/*
    projecteuler.net

    Sub-string divisibility
    Problem 43

    The number, 1406357289, is a 0 to 9 pandigital number because it is made up of each of the digits 0 to 9 in some order, but it also has a rather interesting sub-string divisibility property.

    Let d1 be the 1st digit, d2 be the 2nd digit, and so on. In this way, we note the following:

        d2d3d4=406 is divisible by 2
        d3d4d5=063 is divisible by 3
        d4d5d6=635 is divisible by 5
        d5d6d7=357 is divisible by 7
        d6d7d8=572 is divisible by 11
        d7d8d9=728 is divisible by 13
        d8d9d10=289 is divisible by 17

    Find the sum of all 0 to 9 pandigital numbers with this property.
*/

#include <stdio.h>
#define MAX 10

int prime[MAX];
int array[MAX];
long long int sum;

void swap(int x, int y) {
    int tmp = *(array + x);
    *(array + x) = *(array + y);
    *(array + y) = tmp;
}

void add() {
    int i;
    long long int n = 0;

    for (i = 0; i < MAX; i++) {
        n = n * 10 + array[i];
    }
    printf("%lld\n", n);
    sum += n;
}

int is_prime(int n) {
    int i;

    for (i = 2; i <= (n / 2); i++) {
        if (n % i == 0) {
            return 0;
        }
    }
    return 1;
}

void set_prime_numbers() {
    int c = 0;
    int i = 2;

    do {
        if (is_prime(i)) {
            prime[c] = i;
            c++;
        }
        i++;
    } while (c < MAX);
}

void test() {
    int i, j, n, add_sum = 0;

    for (i = 1; i < (MAX - 2); i++) {
        n = 0;
        for (j = 0; j < 3; j++) {
            n = n * 10 + array[i + j];
        }
        if (n % prime[i - 1] != 0) {
            return;
        }
    }
    add();
}

void permute(int n) {
    int c;

    if (n == 0) {
        test();
        return;
    }
    for (c = 0; c < n; c++) {
        permute(n - 1);
        swap(n % 2 ? 0 : c, n - 1);
    }
}

int main(int argc, char *argv[]) {
    int i;

    sum = 0;
    set_prime_numbers();
    for (i = 0; i < MAX; i++) {
        array[i] = MAX - i - 1;
    }

    permute(MAX);
    printf("sum = %lld\n", sum);
    system("PAUSE");
    return 0;
}
