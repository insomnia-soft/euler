/*
    projecteuler.net

    Factorial digit sum
    Problem 20

    n! means n × (n - 1) × ... × 3 × 2 × 1

    For example, 10! = 10 × 9 × ... × 3 × 2 × 1 = 3628800,
    and the sum of the digits in the number 10! is 3 + 6 + 2 + 8 + 8 + 0 + 0 = 27.

    Find the sum of the digits in the number 100!
*/

#include <stdio.h>
#define MAX 100000

void reset(char *a) {
    int i = 0;
    while (*(a + i)) {
        *(a + i) = 0;
        i++;
    }
}

void copy(char *a, char *b) {
    int i = 0;
    reset(b);
    while (*(a + i)) {
        *(b + i) = *(a + i);
        i++;
    }
}

void sum(char *a, char *b, char *rez) {
    int i = 0;
    int tmp;
    int next = 0;

    while (*(a + i) || *(b + i) || next) {
        tmp = 0;

        if (*(a + i))       tmp += *(a + i) - 48;
        if (*(b + i))       tmp += *(b + i) - 48;
        if (next)           tmp += next;

        *(rez + i) = tmp % 10 + 48;
        next = (int) tmp / 10;
        i++;
    }
}

void multiply(char *a, char *b, char *rez) {
    int i, j, k, tmp, len_next;
    int len_a = str_len(a);
    int len_b = str_len(b);
    int next = 0;
    int c = 0;
    char tmp_res[MAX] = {0};
    char res[MAX] = {0};

    for (i = 0; i < len_a; i++) {
        c = 0;

        for (k = 0; k < i; k++) {
            *(tmp_res + k) = 48;
        }

        for (j = 0; j < len_b; j++) {
            tmp = (*(a + i) - 48) * (*(b + j) - 48);
            *(tmp_res + c + i) = (tmp + next) % 10 + 48;
            next = (tmp + next) / 10;

            c++;
        }

        len_next = num_len(next);

        while (next != 0) {
            *(tmp_res + c + i) = next % 10 + 48;
            c++;
            next /= 10;
        }

        sum(tmp_res, rez, res);
        copy(res, rez);
        reset(tmp_res);
        reset(res);
    }
}

/*void rotate(char *a) {
    int i, len;
    char tmp;

    len = str_len(a) - 1;

    for (i = 0; i <= (int) len / 2; i++) {
        tmp = *(a + len - i);
        *(a + len - i) = *(a + i);
        *(a + i) = tmp;
    }
}*/

int str_len(char *a) {
    int i;
    int res = 0;
    for (i = 0; *(a + i) != 0; i++, res++);
    return res;
}

int num_len(int a) {
    int i = 0;

    while (a > 0) {
        a /= 10;
        i++;
    }

    return i;
}

/*void print(char *a) {
    int i = 0;

    while (*(a + i)) {
        printf("%c", *(a + i));
        i++;
    }
}*/

int main(int argc, char *argv[]) {
    char a[MAX] = {0};
    char b[MAX] = {0};
    char c[MAX] = {0};
    int i = 0;
    int j;
    int k;

    b[0] = 49;

    for (i = 1; i <= 100; i++) {
        k = 0;
        j = i;

        while (j) {
            a[k] = j % 10 + 48;
            j /= 10;
            k++;
        }

        multiply(a, b, c);
        copy(c, b);
        reset(c);
    }

    k = 0;
    i = 0;
    while (*(b + i)) {
        k = k + *(b + i) - 48;
        i++;
    }

    printf("sum: %d\n", k);

    system("PAUSE");
    return 0;
}
