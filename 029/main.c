/*

Distinct powers
Problem 29

Consider all integer combinations of ab for 2 <= a <= 5 and 2 <= b <= 5:

    2^2=4, 2^3=8, 2^4=16, 2^5=32
    3^2=9, 3^3=27, 3^4=81, 3^5=243
    4^2=16, 4^3=64, 4^4=256, 4^5=1024
    5^2=25, 5^3=125, 5^4=625, 5^5=3125

If they are then placed in numerical order, with any repeats removed, we get the following sequence of 15 distinct terms:

4, 8, 9, 16, 25, 27, 32, 64, 81, 125, 243, 256, 625, 1024, 3125

How many distinct terms are in the sequence generated by ab for 2 <= a <= 100 and 2 <= b <= 100?


Solution:

9183

*/

#include <stdio.h>
#include <stdlib.h>

#define TEMP_MAX_LENGTH 510

#define ROWS 850000
#define COLS 205

char list[ROWS][COLS] = {0};
long listCount = 0;

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
    while (a[i] != 0) {
        a[i++] = 0;
    }
}

void copy(char *a, char *b) {
    int i = 0;
    while (a[i] != 0) {
        b[i] = a[i];
        i++;
    }
    b[i] = 0;
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
    char tmp[TEMP_MAX_LENGTH];
    char tmp2[TEMP_MAX_LENGTH] = {0};
    char sum[TEMP_MAX_LENGTH] = {0};

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
    char mul[TEMP_MAX_LENGTH] = {0};
    char tmp[TEMP_MAX_LENGTH] = {0};
    char num[TEMP_MAX_LENGTH] = {0};

    intToStr(a, tmp);
    intToStr(a, num);

    for (i = 1; i < b; i++) {
        multiply(tmp, num, mul);
        copy(mul, tmp);
        reset(mul);
    }
    copy(tmp, c);
}

int searchList(char *a) {
    int row, col;
    int searchStrLen;
    int strLen;
    int equal;

    searchStrLen = len(a);

    for (row = 0; row < listCount - 1; row++) {
        strLen = len(list[row]);
        if (searchStrLen == strLen) {
            equal = 1;
            for (col = 0; col < strLen; col++) {
                if (a[col] != list[row][col]) {
                    equal = 0;
                    break;
                }
            }
            if (equal == 1) {
                return 1;
            }
        }
    }
    return 0;
}

int addToList(char *a) {
    if (searchList(a) == 0) {
        copy(a, list[listCount]);
        listCount++;
        return 1;
    }
    return 0;
}

int main() {
    char result[COLS] = {0};

    int from = 2;
    int to = 100;
    int total = 0;
    int i, j;

    for (i = from; i <= to; i++) {
        for (j = from; j <= to; j++) {
            reset(result);
            strPow(i, j, result);
            rotate(result);
            total += addToList(result);
        }
    }

    printf("TOTAL: %d\n", total);
    return (EXIT_SUCCESS);
}