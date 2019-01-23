/*

Convergents of e
Problem 65


Solution:

272

*/


#include <stdio.h>

#define COLS 100

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

void rotate(char a[]) {
    char tmp;
    int i, strLen;
    strLen = len(a);
    for (i = 0; i < strLen / 2; i++) {
        tmp = a[i];
        a[i] = a[strLen - i - 1];
        a[strLen - i - 1] = tmp;
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

int sumChars(char a[]) {
    int i;
    int sum = 0;
    for (i = 0; a[i] != 0; i++) {
        sum += a[i] - 48;
    }
    return sum;
}
int fract(char num[], char denum[], int eFract[], int index) {
    char a[COLS] = {0};
    char b[COLS] = {0};
    char c[COLS] = {0};

    intToStr(eFract[index], a);
    multiply(a, denum, b);
    add(b, num, c);

    if (index > 0) {
        fract(denum, c, eFract, index - 1);
    } else {
        rotate(denum);
        rotate(c);
        if (index % 2 == 0) {
            printf("%s / %s\n", c, denum);
            printf("%d\n", sumChars(c));
//        } else {
//            printf("%s / %s\n", denum, c);
        }
    }

}

int main() {
    char num[COLS] = {0};
    char denum[COLS] = {0};

    int eFract[150] = {0};
    int eIndex = 2;
    int n = 2;
    int i;

    int target = 100;

    eFract[0] = 2;
    for (i = 1; i < 150; i++) {
        if (i == n) {
            eFract[i] = eIndex;
            n += 3;
            eIndex += 2;
        } else {
            eFract[i] = 1;
        }
    }

    num[0] = 1 + 48;
    intToStr(eFract[target - 1], denum);
    fract(num, denum, eFract, target - 2);

    return 0;
}
