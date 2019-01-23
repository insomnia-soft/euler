/*

Large non-Mersenne prime
Problem 97

The first known prime found to exceed one million digits was discovered in 1999,
and is a Mersenne prime of the form 26972593−1; it contains exactly 2,098,960
digits. Subsequently other Mersenne primes, of the form 2p−1, have been found
which contain more digits.

However, in 2004 there was found a massive non-Mersenne prime which contains
2,357,207 digits: 28433 × 2^7830457 + 1.

Find the last ten digits of this prime number.


Solution:

8739992577

- 1 s

*/


#include <stdio.h>

#define P 7830457
#define COLS_SHORT 15
#define COLS 10000

void print(char n[]) {
    for (int i = 0; n[i] != 0; i++) {
        printf("%c", n[i]);
    }
    printf("\n");
}

int len(char a[]) {
    int i = 0;
    for (i = 0; a[i] != 0; i++);
    return i;
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

void reset(char a[]) {
    int i;
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

void mul2(char n[]) {
    int i, prod, carry = 0;

    for (i = 0; i < COLS_SHORT; i++) {
        if (n[i] == 0) {
            if (carry) {
                prod = carry;
            } else {
                break;
            }
        } else {
            prod = (n[i] - 48) * 2 + carry;
        }
        n[i] = prod % 10 + 48;
        carry = prod / 10;
    }
}

int main() {
    int i;
    char n[COLS_SHORT] = {0};
    char a[COLS] = {0};
    char b[COLS] = {0};
    char c[COLS] = {0};
    char prod[COLS] = {0};
    char one[COLS] = {0};

    n[0] = 2 + 48;
    one[0] = 1 + 48;

    for (i = 1; i < P; i++) {
        mul2(n);
    }

    for (i = 0; i < COLS_SHORT; i++) {
        a[i] = n[i];
    }

    intToStr(28433, b);
    multiply(a, b, prod);
    add(prod, one, c);

    for (i = 9; i >= 0; i--) {
        printf("%c", c[i]);
    }
    printf("\n");

    return 0;
}
