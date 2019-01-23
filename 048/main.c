/*

Self powers
Problem 48

The series, 1^1 + 2^2 + 3^3 + ... + 10^10 = 10405071317.

Find the last ten digits of the series, 1^1 + 2^2 + 3^3 + ... + 1000^1000.


Solution:

9110846700

*/

#include <stdio.h>
#include <stdlib.h>

// string length of 1000^1000 = 3001 + null char
#define MAX 3002

char sum[MAX] = {0};

void print(char *a) {
	for (int i = 0; a[i] != 0; i++) {
		printf("%c", a[i]);
	}
	printf("\n");
}

int len(char *a) {
    int i = 0;
    for (i = 0; a[i] != 0; i++);
    return i;
}

void copy(char *a, char *b) {
    int i = 0;
    while (a[i] != 0) {
        b[i] = a[i];
        i++;
    }
    b[i] = 0;
}

void rotate(char *a) {
    char tmp;
    int i, strLen;
    strLen = len(a);
    for (i = 0; i < strLen / 2; i++) {
        tmp = a[i];
        a[i] = a[strLen - i - 1];
        a[strLen - i - 1] = tmp;
    }
}

void reset(char *a) {
    int i = 0;
    for (i = 0; i < MAX; i++) {
        a[i] = 0;
    }
}

void intToStr(int a, char *s) {
    int i = 0;
    while (a > 0) {
        s[i] = a % 10 + 48;
        a /= 10;
        i++;
    }
    s[i] = 0;
}

int strToInt(char *s) {
    int i = 0;
    int pos = 1;
    int res = 0;
    while (s[i] != 0) {
        res += (s[i] - 48) * pos;
        pos *= 10;
        i++;
    }
    return res;
}

void add(char *a, char *b, char *c) {
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

void multiplySingle(char *a, char b, char *c, int start) {
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

void multiply(char *a, char *b, char *c) {
    int i = 0;
    char tmp[MAX];
    char tmp2[MAX] = {0};
    char sum[MAX] = {0};

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

void strPow(int a, int b, char *c) {
    int i;
    char mul[MAX] = {0};
    char tmp[MAX] = {0};
    char num[MAX] = {0};

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
    int i, strLen;
    char tmp[MAX];
    char tmp2[MAX];

    int from = 1;
    int to = 1000;

    for (i = from; i <= to; i++) {
        reset(tmp);
        reset(tmp2);
        strPow(i, i, tmp);
        add(sum, tmp, tmp2);
        copy(tmp2, sum);
    }

    rotate(sum);
    strLen = len(sum);
    for (i = strLen - 10; i < strLen; i++) {
        printf("%c", sum[i]);
    }

    return (EXIT_SUCCESS);
}
