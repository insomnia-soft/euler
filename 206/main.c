/*

Concealed Square
Problem 206

Find the unique positive integer whose square has the form 1_2_3_4_5_6_7_8_9_0,
where each "_" is a single digit.


Solution:

1389019170

- 11 sec (starting from 1929394959697989900)

*/

#include <stdio.h>

#define COLS 100

void print(char a[]) {
    int len = 0, i;
    while (a[len] != 0) {
        len++;
    }
    for (i = len - 1; i >= 0; i--) {
        printf("%c", a[i]);
    }
    printf("\n");
}

void reset(char a[]) {
    int i;
    for (i = 0; a[i] != 0; i++) {
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
    if (a == 0) {
        s[0] = 48;
        s[1] = 0;
        return;
    }
    while (a > 0) {
        s[i] = a % 10 + 48;
        a /= 10;
        i++;
    }
    s[i] = 0;
}

void numberToStr(char n[], char s[]) {
    int i = 0;
    while (n[i] != 0) {
        s[i] = n[i];
        i++;
    }
    s[i] = 0;
    rotate(s);
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

char approxSquare(char remainder[], char sub[]) {
    int i;
    char ok = 0;
    char n[COLS] = {0};
    char sum[] = {0};
    for (i = 0; i < 10; i++) {
        sub[0] = i + 48;
        reset(n);
        reset(sum);
        intToStr(i, n);
        multiply(n, sub, sum);
        if (strCompare(sum, remainder) < 1) {
            ok = i;
        } else {
            break;
        }
    }
    return ok + 48;
}

int isPerfectSquare(char n[], char result[]) {
    int nLen = len(n);
    int nIndex = nLen;
    char newDigit;

    char sub[COLS] = {0};
    char remainder[COLS] = {0};
    char tmp1[COLS] = {0};
    char tmp2[COLS] = {0};

    reset(result);

    while (nIndex > 0) {
        if (nIndex % 2 == 0) {
            multiply10(remainder);
            multiply10(remainder);
            remainder[0] = n[nIndex - 2];
            remainder[1] = n[nIndex - 1];
            nIndex -= 2;
        } else {
            multiply10(remainder);
            remainder[0] = n[nIndex - 1];
            nIndex -= 1;
        }
        multiply10(sub);
        multiply10(result);
        newDigit = approxSquare(remainder, sub);
        result[0] = newDigit;
        sub[0] = newDigit;
        reset(tmp2);
        tmp2[0] = newDigit;
        reset(tmp1);
        multiply(tmp2, sub, tmp1);
        sub2arg(remainder, tmp1);
        reset(tmp1);
        add(sub, tmp2, tmp1);
        reset(sub);
        copy(tmp1, sub);
    }

    if (len(remainder) == 1 && remainder[0] == 48) {
        return 1;
    }

    return 0;
}

int main() {
    long i, n = 99999999, m;
    char mask[COLS] = {0};
    char result[COLS] = {0};

    numberToStr("1020304050607080900", mask);

    while (1) {
        m = n;
        for (i = 3; m > 0; i += 2) {
            mask[i] = m % 10 + 48;
            m /= 10;
        }
        if (isPerfectSquare(mask, result)) {
            break;
        }
        n--;
    }

    printf("number:   ");
    print(mask);
    printf("solution: ");
    print(result);

    return 0;
}
