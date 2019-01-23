/*

Square root digital expansion
Problem 80

It is well known that if the square root of a natural number is not an integer,
then it is irrational. The decimal expansion of such square roots is infinite
without any repeating pattern at all.

The square root of two is 1.41421356237309504880..., and the digital sum of the
first one hundred decimal digits is 475.

For the first one hundred natural numbers, find the total of the digital sums of
the first one hundred decimal digits for all the irrational square roots.


Solution:

40886

- 5 sec
- http://www.squarerootcalculator.co/square-root-without-calculator.html

*/


#include <stdio.h>

#define COLS 200

void reset(char a[]) {
    int i;
    for (i = 0; i < COLS; i++) {
        a[i] = 0;
    }
}

int len(char a[]) {
    int i = 0;
    for (i = 0; a[i] != 0; i++);
    return i;
}

void copy(char a[], char b[]) {
    int i = 0;
    while (a[i] != 0) {
        b[i] = a[i];
        i++;
    }
    b[i] = 0;
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

void intToStr(int a, char s[]) {
    int i = 0;
    while (a > 0) {
        s[i] = a % 10 + 48;
        a /= 10;
        i++;
    }
    s[i] = 0;
}

int intLength(int n) {
    int i = 0;
    while (n > 0) {
        n /= 10;
        i++;
    }
    return i;
}

// compare strings as numbers
// a > b returns 1
// a == b returns 0
// a < b returns -1
int strCompare(char a[], char b[]) {
    int i;
    int lenA = len(a);
    int lenB = len(b);

    if (lenA > lenB) {
        return 1;
    }
    else if (lenA < lenB) {
        return -1;
    }

    for (i = lenA - 1; i >= 0; i--) {
        if (a[i] > b[i]) {
            return 1;
        }
        else if (a[i] < b[i]) {
            return -1;
        }
    }

    return 0;
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

void add2arg(char *a, char *b) {
	int i = 0;
    int remainder = 0;
    int continue_a;
    int continue_b;
    char sum;

    do {
        continue_a = 0;
        continue_b = 0;
        sum = 0;
        if (a[i]) {
            sum += a[i] - 48;
            continue_a = 1;
        }
        if (b[i]) {
            sum += b[i] - 48;
            continue_b = 1;
        }

        if (continue_a || continue_b || remainder) {
            sum += remainder;
            b[i] = sum % 10 + 48;
            remainder = sum / 10;
        }
        i++;
    } while (continue_a || continue_b);
}

void sub2arg(char a[], char b[]) {
	int i = 0;
	char tmp;
	char carry = 0;
	char cont_a = 1;
	char cont_b = 1;

	do {
        tmp = carry;

		if (cont_a && a[i] != 0) {
			tmp += a[i] - 48;
		} else {
            cont_a = 0;
        }

		if (cont_b && b[i] != 0) {
			tmp -= b[i] - 48;
		} else {
            cont_b = 0;
        }

        if (cont_a || cont_b || carry) {
            if (tmp < 0) {
                tmp += 10;
                carry = -1;
            }
            else {
                carry = 0;
            }
            a[i] = tmp + 48;
        }
        i++;
	} while (cont_a || cont_b);
    i--;
    for (; i > 0; i--) {
        if (a[i] == 48 || a[i] == 0) {
            a[i] = 0;
        } else {
            break;
        }
    }
}

void multiply10(char a[]) {
    int i, strLen = len(a);
    // if zero, return
    if (strLen == 1 && a[0] == 48) {
        return;
    }
    for (i = strLen; i > 0; i--) {
        a[i] = a[i - 1];
    }
    a[0] = 48;
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
    if (len(c) == 0) {
        c[0] = 48;
    }
}

int approxRoot(char r[], char n[]) {
    int i;
    char iStr[COLS] = {0};
    char a[COLS] = {0};
    char sum[COLS] = {0};
    multiply10(r);

    for (i = 0; i <= 10; i++) {
        reset(iStr);
        reset(sum);
        reset(a);
        intToStr(i, iStr);
        add(r, iStr, a);
        multiply(iStr, a, sum);
        if (strCompare(sum, n) > -1) {
            if (i == 0) {
                return 0;
            }
            return i - 1;
        }
    }

    return i;
}

void addDigit(int n, char a[]) {
    int strLen = len(a);
    if (strLen == 1 && a[0] == 48) {
        a[0] = n + 48;
    } else {
        a[strLen] = n + 48;
    }
}

int squareRoot(int n) {
    char nStr[COLS] = {0};
    char a[COLS] = {0};
    char b[COLS] = {0};
    char c[COLS] = {0};
    char remainder[COLS] = {0};
    char result[COLS * 2] = {0};
    char two[COLS] = {0};
    char ten[COLS] = {0};
    int dotIndex = 0;
    int nIndex = intLength(n);
    int newDigit;
    int i;
    int decCount = 0;
    int decSum = 0;

    a[0] = 48;
    two[0] = 2 + 48;
    ten[0] = 48;
    ten[1] = 1 + 48;
    result[0] = 48;
    remainder[0] = 48;

    intToStr(n, nStr);

    for (int x = 0; x < 100; x++) {
        if (nIndex == 0) {
            multiply10(remainder);
            multiply10(remainder);
            remainder[0] = 48;
            remainder[1] = 48;
            decCount++;
        } else {
            if (nIndex % 2 == 0) {
                multiply10(remainder);
                multiply10(remainder);
                remainder[0] = nStr[nIndex - 2];
                remainder[1] = nStr[nIndex - 1];
                nIndex -= 2;
            } else {
                // samo ako početni broj ima neparan broj znamenki
                remainder[0] = nStr[nIndex - 1];
                nIndex -= 1;
            }
            dotIndex = len(result);
        }

        reset(a);
        reset(b);
        copy(result, b);
        rotate(b);
        a[0] = 48;
        multiply(two, b, a);
        newDigit = approxRoot(a, remainder);
        addDigit(newDigit, result);
        reset(b);
        if (x > 0) {
            if (newDigit > 0) {
                intToStr(newDigit, b);
                add2arg(b, a);
                reset(c);
                multiply(a, b, c);
                sub2arg(remainder, c);
            }
        } else {
            intToStr(newDigit * newDigit, b);
            sub2arg(remainder, b);
        }
    }

    printf("%d = ", n);
    for (i = 0; result[i] != 0; i++) {
        if (i == dotIndex) {
            printf(",");
        }
        printf("%c", result[i]);
        decSum += result[i] - 48;
    }
    printf("\n");

    return decSum;
}

int main() {
    int i, j = 2;
    int sum = 0;

    for (i = 2; i < 100; i++) {
        if (i == j * j) {
            j++;
            continue;
        }
        sum += squareRoot(i);
    }

    printf("sum = %d\n", sum);

    return 0;
}
