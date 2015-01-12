/*
    projecteuler.net
    
    1000-digit Fibonacci number
    Problem 25

    The Fibonacci sequence is defined by the recurrence relation:

        Fn = Fn-1 + Fn-2, where F1 = 1 and F2 = 1.

    Hence the first 12 terms will be:

        F1 = 1
        F2 = 1
        F3 = 2
        F4 = 3
        F5 = 5
        F6 = 8
        F7 = 13
        F8 = 21
        F9 = 34
        F10 = 55
        F11 = 89
        F12 = 144

    The 12th term, F12, is the first term to contain three digits.

    What is the first term in the Fibonacci sequence to contain 1000 digits?
*/

#include <stdio.h>
#define MAX 1500

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

void sum(char *a, char *b, char *res) {
    int i = 0;
    int tmp;
    int next = 0;

    while (*(a + i) || *(b + i) || next) {
        tmp = 0;

        if (*(a + i))       tmp += *(a + i) - 48;
        if (*(b + i))       tmp += *(b + i) - 48;
        if (next)           tmp += next;

        *(res + i) = tmp % 10 + 48;
        next = (int) tmp / 10;
        i++;
    }
}

int string_len(char *a) {
    int i;
    int res = 0;
    for (i = 0; *(a + i) != 0; i++, res++);
    return res;
}

int main(int argc, char *argv[]) {
    int i;

    char a[MAX] = {0};
    char b[MAX] = {0};
    char c[MAX] = {0};

    int counter = 2;

    a[0] = 49;
    b[0] = 49;

    while (1) {
        sum(a, b, c);
        copy(b, a);
        copy(c, b);
        counter++;

        if (string_len(b) == 1000) {
            break;
        }
    }

    printf("%d\n", counter);

    system("PAUSE");
    return 0;
}
