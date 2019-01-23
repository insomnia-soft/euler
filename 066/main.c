/*

Diophantine equation
Problem 66

Consider quadratic Diophantine equations of the form:

x^2 – Dy^2 = 1

For example, when D=13, the minimal solution in x is 6492 – 13×1802 = 1.

It can be assumed that there are no solutions in positive integers when D is
square.

By finding minimal solutions in x for D = {2, 3, 5, 6, 7}, we obtain the
following:

3^2 – 2×2^2 = 1
2^2 – 3×1^2 = 1
9^2 – 5×4^2 = 1
5^2 – 6×2^2 = 1
8^2 – 7×3^2 = 1

Hence, by considering minimal solutions in x for D <= 7, the largest x is
obtained when D=5.

Find the value of D <= 1000 in minimal solutions of x for which the largest
value of x is obtained.


Solution:

661

*/


#include <stdio.h>

#define MAX 10000
#define COLS 1000

void reset(char a[]) {
    int i;
    for (i = 0; i < COLS; i++) {
        a[i] = 0;
    }
}

void resetIntArray(int a[]) {
    int i;
    for (i = 0; i < MAX; i++) {
        a[i] = 0;
    }
}

int len(char a[]) {
    int i = 0;
    for (i = 0; a[i] != 0; i++);
    return i;
}

int lenIntArray(int a[]) {
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

int strToInt(char a[]) {
    int i = 0;
    int n = 0;
    int mul = 1;

    while (a[i] > 0) {
        n += (a[i] - 48) * mul;
        mul *= 10;
        i++;
    }
    return n;
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

int approximateSquareRoot(int n) {
    int digit;
    for (digit = 2; digit * digit < n; digit++);
    return digit - 1;
}

int step(int sqroot, int strPart[], int a, int numerator, int stepIndex) {
    int i;

    // step 1
    int b = a * -1;

    // step 2
    int c = sqroot + a * b;

    // step 3
    int repeat;
    do {
        repeat = 0;
        for (i = 2; i <= numerator; i++) {
            if (numerator % i == 0 && c % i == 0) {
                numerator /= i;
                c /= i;
                repeat = 1;
                break;
            }
        }
    } while (repeat);

    if (numerator != 1) {
        printf("ERROR, this shouldn't happen\n");
    }

    // step 4
    int d = (strPart[0] + b) / c;
    int e = c * d;
    a = b - e;
    strPart[stepIndex + 1] = d;

    if (c > 1) {
        step(sqroot, strPart, a, c, stepIndex + 1);
    } else {
        return 0;
    }
}

int fractionCount(int strPart[], int n) {
    int approx = approximateSquareRoot(n);
    int ret;
    strPart[0] = approx;
    ret = step(n, strPart, approx * -1, 1, 0);
    return ret;
}

int skip(int n) {
    int i;
    for (i = 2; i * i <= n; i++) {
        if (i * i == n) {
            return 1;
        }
    }
    return 0;
}

int calcContinueFraction(int contFract[], char num[], char denum[]) {
    int i;
    int strLen;
    int index;
    char a[COLS] = {0};
    char b[COLS] = {0};
    char c[COLS] = {0};
    char d[COLS] = {0};
    char tmp[COLS] = {0};

    strLen = lenIntArray(contFract);
    index = 1;
    if (strLen == 2) {
        index = 0;
    }

    a[0] = 1 + 48;
    intToStr(contFract[strLen - 1 - index], b);
    for (i = strLen - 2 - index; i >= 0; i--) {
        reset(d);
        intToStr(contFract[i], d);

        reset(tmp);
        multiply(b, d, tmp);

        reset(c);
        add(tmp, a, c);

        reset(a);
        copy(b, a);

        reset(b);
        copy(c, b);
    }

    copy(b, num);
    copy(a, denum);
}

/*
 * If
 *      x^2 - D*y^2 = -1
 * Then
 *      x = x^2 + D*y^2
 *      y = 2*x*y
 */
void checkIfMinus1(int d, char num[], char denum[]) {
    char a[COLS];
    char b[COLS];
    char c[COLS];
    char tmp[COLS];
    char tmp2[COLS];
    reset(a);
    multiply(num, num, a);
    reset(c);
    intToStr(d, c);
    reset(tmp);
    multiply(denum, denum, tmp);
    reset(tmp2);
    multiply(tmp, c, tmp2);
    if (strCompare(a, tmp2) == -1) {
        reset(b);
        add(a, tmp2, b);
        reset(tmp);
        reset(tmp);
        intToStr(2, tmp);
        reset(c);
        multiply(num, denum, c);
        reset(denum);
        multiply(tmp, c, denum);
        reset(num);
        copy(b, num);
    }
}

int main() {
    int d;
    int contFract[MAX] = {0};

    // fraction
    char num[COLS] = {0};
    char denum[COLS] = {0};

    char max_num[COLS] = {0};
    int max_d = 0;

    for (d = 2; d <= 1000; d++) {
        if (skip(d)) {
            continue;
        }
        resetIntArray(contFract);
        fractionCount(contFract, d);
        calcContinueFraction(contFract, num, denum);
        checkIfMinus1(d, num, denum);

        if (strCompare(num, max_num) == 1) {
            reset(max_num);
            copy(num, max_num);
            max_d = d;
        }
    }

    rotate(max_num);
    printf("D = %d\n", max_d);

    return 0;
}


///* This is brute-force solution which does not work because 1. too much time
//   is required and 2. unsigned long long is not big enough for solution */
//#include <stdio.h>
//
//#define MAX 100000
//#define D_MAX 1000
//
//int main() {
//    unsigned long long i, j;
//    unsigned long long x;
//    unsigned long long y;
//    unsigned long long count = 0;
//    int iMax = 0;
//    int jMax;
//    int dMax;
//    int square = 2;
//    int d;
//    int found;
//
//    for (d = 2; d <= D_MAX; d++) {
//        if (d == square * square) {
//            square++;
//            continue;
//        }
//
//        found = 0;
//        i = 1;
//        j = 1;
//        count = 0;
//        do {
//            x = i * i;
//            y = j * j;
//            if (x - d * y == 1) {
//                if (i > iMax) {
//                    iMax = i;
//                    jMax = j;
//                    dMax = d;
//                }
//                printf("%llu^2 - %d * %llu^2 = 1   [[[ %d^2 - %d * %d^2 = 1 ]]]", i, d, j, iMax, dMax, jMax);
//                found = 1;
//                break;
//            }
//
//            j++;
//            if (j >= i) {
//                i++;
//                j = 1;
//            }
//
//            count++;
//            if (count % 10000000000 == 0) {
//                printf("count [%d] = %llu\n", d, count);
//                break;
//            }
//        } while (!found);
//
//        printf("\n");
//    }
//
//    printf("\n--\n%d^2 - %d * %d^2 = 1\n", iMax, dMax, jMax);
//
//    return 0;
//}


