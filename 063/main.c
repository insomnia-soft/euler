/*

Powerful digit counts
Problem 63

The 5-digit number, 16807=7^5, is also a fifth power. Similarly, the 9-digit
number, 134217728=8^9, is a ninth power.

How many n-digit positive integers exist which are also an nth power?


Solution:

49

*/


#include <stdio.h>

#define COLS 1000

int len(char a[]) {
    int i = 0;
    for (i = 0; a[i] != 0; i++);
    return i;
}

void reset(char a[]) {
    int i = 0;
    for (i = 0; i < COLS; i++) {
        a[i] = 0;
    }
}

void copy(char a[], char b[]) {
    int i = 0;
    while (a[i] != 0) {
        b[i] = a[i];
        i++;
    }
    b[i] = 0;
}

void intToStr(int a, char s[]) {
    int i = 0;
    while (a > 0) {
        s[i] = a % 10 + 48;
        a /= 10;
        i++;
    }
    s[i] = 0;
}

void add(char a[], char b[], char c[]) {
	int i = 0;
	char tmp;
	char carry = 0;
	char cont_a = 1;
	char cont_b = 1;

	do {
        tmp = 0;
		if (cont_a && a[i] != 0) {
			tmp = a[i] - 48;
		} else {
            cont_a = 0;
        }

		if (cont_b && b[i] != 0) {
			tmp += b[i] - 48;
		} else {
            cont_b = 0;
        }

        tmp += carry;

        if (cont_a || cont_b || carry) {
            c[i] = tmp % 10 + 48;
            carry = tmp / 10;
        }
        i++;
	} while (cont_a || cont_b);
    c[i] = 0;
}

void multiplySingle(char a[], char b, char c[], int start) {
    int i;
    int carry = 0;
    int sum = 1;
    int cont = 0;

    for (i = 0; i < start; i++) {
        c[i] = 48;
    }

    i = 0;
    b -= 48;
    do {
        cont = 1;
        if (a[i] != 0) {
            sum = (a[i] - 48) * b;
        } else {
            cont = 0;
            sum = 0;
        }
        sum += carry;
        if (carry || cont) {
            c[i + start] = sum % 10 + 48;
        }
        carry = sum / 10;
        i++;
    } while (carry || cont);
}

void multiply(char a[], char b[], char c[]) {
    int i = 0;
    char tmp[COLS];
    char tmp2[COLS] = {0};
    char sum[COLS] = {0};

    while (b[i] != 0) {
        reset(tmp);
        multiplySingle(a, b[i], tmp, i);
        add(tmp, tmp2, sum);
        copy(sum, tmp2);
        reset(sum);
        i++;
    }
    copy(tmp2, c);
}

void strPow(int a, int b, char c[]) {
    int i;
    char mul[COLS] = {0};
    char tmp[COLS] = {0};
    char num[COLS] = {0};

    intToStr(a, tmp);
    intToStr(a, num);

    for (i = 1; i < b; i++) {
        multiply(tmp, num, mul);
        copy(mul, tmp);
        reset(mul);
    }
    copy(tmp, c);
}

int main() {
    char result[COLS] = {0};
    int from = 1;
    int to = 200;
    int total = 0;
    int i, j;
    int resLength;

    for (i = from; i <= to; i++) {
        for (j = from; j <= to; j++) {
            reset(result);
            strPow(i, j, result);
            resLength = len(result);
            if (resLength > j) {
                break;
            }
            else if (resLength == j) {
                total++;
                printf("%d ^ %d = %s\n", i, j, result);
            }
        }
    }

    printf("TOTAL: %d\n", total);

    return 0;
}
