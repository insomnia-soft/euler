/*

Almost equilateral triangles
Problem 94

It is easily proved that no equilateral triangle exists with integral length
sides and integral area. However, the almost equilateral triangle 5-5-6 has an
area of 12 square units.

We shall define an almost equilateral triangle to be a triangle for which two
sides are equal and the third differs by no more than one unit.

Find the sum of the perimeters of all almost equilateral triangles with integral
side lengths and area and whose perimeters do not exceed one billion
(1,000,000,000).


Solution:

518408346

- 29 sec

*/


#include <stdio.h>

#define PERIMETER 1000000000

int perimeterSum = 0;

long primTrip[8000][3] = {0};
int primTripCount = 0;

long longAbs(long n) {
    if (n < 0) {
        return n * -1;
    }
    return n;
}

void sort(long *a, long *b, long *c) {
    long tmp;

    // sort by size
    if (*a > *b) {
        tmp = *a;
        *a = *b;
        *b = tmp;
    }
    if (*a > *c) {
        tmp = *a;
        *a = *c;
        *c = tmp;
    }
    if (*b > *c) {
        tmp = *b;
        *b = *c;
        *c = tmp;
    }
}

int test(long a, long c) {
    long tmp;

    tmp = c - 2 * a;
    if (longAbs(tmp) == 1) {
//        printf("%ld %ld %ld\n", a * 2, a * 2, c);
        perimeterSum += 2 * a + 2 * c;
    }

    return 1;
}

int tooBig(long a, long c) {
    if (2 * a + 2 * c > PERIMETER) {
        return 1;
    }
    return 0;
}

int main() {
    int i, col, row = 0, index;
    long sum;
    long a, b, c;
    long tmp[3];
    long child[3][3];
    int matrix[3][3][3] = {
        {{1, -2, 2},
         {2, -1, 2},
         {2, -2, 3}},
        {{1, 2, 2},
         {2, 1, 2},
         {2, 2, 3}},
        {{-1, 2, 2},
         {-2, 1, 2},
         {-2, 2, 3}},
    };

    primTrip[0][0] = 3;
    primTrip[0][1] = 4;
    primTrip[0][2] = 5;
    primTripCount = 1;

    // first primitive pythagorean triple
    i = 1;
    do {
        test(3 * i, 5 * i);
        i++;
    } while (!tooBig(3 * i, 5 * i));

    // loop while there are primitive triples in array
    do {
        // pop triple from array
        for (i = 0; i < 3; i++) {
            tmp[i] = primTrip[primTripCount - 1][i];
            primTrip[primTripCount - 1][row] = 0;
        }
        primTripCount--;

        // calculate matrix
        for (i = 0; i < 3; i++) {
            for (row = 0; row < 3; row++) {
                sum = 0;
                for (col = 0; col < 3; col++) {
                    sum += matrix[i][row][col] * tmp[col];
                }
                child[i][row] = sum;
            }
        }

        // for each new child (parent has 3 children)
        for (index = 0; index < 3; index++) {
            a = child[index][0];
            b = child[index][1];
            c = child[index][2];

            sort(&a, &b, &c);

            if (tooBig(a, c)) {
                continue;
            }

            // add it to array
            for (row = 0; row < 3; row++) {
                primTrip[primTripCount][row] = child[index][row];
            }
            primTripCount++;

            i = 1;
            do {
                test(a * i, c * i);
                i++;
            } while (!tooBig(a * i, c * i));
        }
    } while (primTripCount);

    printf("%d\n", perimeterSum);

    return 0;
}



//// version 2 - bigint version with square root, very slow
//#include <stdio.h>
//
////#define PERIMETER 1000000000
//#define PERIMETER 100000
//#define COLS 100
//
//unsigned long long sum = 0;
//
//char max[COLS] = {0};
//char zero[COLS] = {0};
//char perimeterSum[COLS] = {0};
//
//int len(char a[]) {
//    int i = 0;
//    for (i = 0; a[i] != 0; i++);
//    return i;
//}
//
//void rotate(char a[]) {
//    char tmp;
//    int i, strLen;
//    strLen = len(a);
//    for (i = 0; i < strLen / 2; i++) {
//        tmp = a[i];
//        a[i] = a[strLen - i - 1];
//        a[strLen - i - 1] = tmp;
//    }
//}
//
//void reset(char a[]) {
//    int i;
//    for (i = 0; a[i] != 0; i++) {
//        a[i] = 0;
//    }
//}
//
//void intToStr(int a, char s[]) {
//    int i = 0;
//    while (a > 0) {
//        s[i] = a % 10 + 48;
//        a /= 10;
//        i++;
//    }
//    s[i] = 0;
//}
//
//void copy(char a[], char b[]) {
//    int i = 0;
//    while (a[i] != 0) {
//        b[i] = a[i];
//        i++;
//    }
//    b[i] = 0;
//}
//
//void add(char a[], char b[], char c[]) {
//	int i = 0;
//	char tmp;
//	char carry = 0;
//	char cont_a = 1;
//	char cont_b = 1;
//
//	do {
//        tmp = 0;
//		if (cont_a && a[i] != 0) {
//			tmp = a[i] - 48;
//		} else {
//            cont_a = 0;
//        }
//
//		if (cont_b && b[i] != 0) {
//			tmp += b[i] - 48;
//		} else {
//            cont_b = 0;
//        }
//
//        tmp += carry;
//
//        if (cont_a || cont_b || carry) {
//            c[i] = tmp % 10 + 48;
//            carry = tmp / 10;
//        }
//        i++;
//	} while (cont_a || cont_b);
//    c[i] = 0;
//}
//
//void sub(char a[], char b[], char c[]) {
//	int i = 0;
//	char tmp;
//	char carry = 0;
//	char cont_a = 1;
//	char cont_b = 1;
//
//	do {
//        tmp = carry;
//
//		if (cont_a && a[i] != 0) {
//			tmp += a[i] - 48;
//		} else {
//            cont_a = 0;
//        }
//
//		if (cont_b && b[i] != 0) {
//			tmp -= b[i] - 48;
//		} else {
//            cont_b = 0;
//        }
//
//        if (cont_a || cont_b || carry) {
//            if (tmp < 0) {
//                tmp += 10;
//                carry = -1;
//            }
//            else {
//                carry = 0;
//            }
//            c[i] = tmp + 48;
//        }
//        i++;
//	} while (cont_a || cont_b);
//    for (; i > 0; i--) {
//        if (c[i] == 0) {
//            continue;
//        }
//        else if (c[i] == 48) {
//            c[i] = 0;
//        }
//        else {
//            break;
//        }
//    }
//}
//
//void add2arg(char *a, char *b) {
//	int i = 0;
//    int remainder = 0;
//    int continue_a;
//    int continue_b;
//    char sum;
//
//    do {
//        continue_a = 0;
//        continue_b = 0;
//        sum = 0;
//        if (a[i]) {
//            sum += a[i] - 48;
//            continue_a = 1;
//        }
//        if (b[i]) {
//            sum += b[i] - 48;
//            continue_b = 1;
//        }
//
//        if (continue_a || continue_b || remainder) {
//            sum += remainder;
//            b[i] = sum % 10 + 48;
//            remainder = sum / 10;
//        }
//        i++;
//    } while (continue_a || continue_b);
//}
//
//void sub2arg(char a[], char b[]) {
//	int i = 0;
//	char tmp;
//	char carry = 0;
//	char cont_a = 1;
//	char cont_b = 1;
//
//	do {
//        tmp = carry;
//
//		if (cont_a && a[i] != 0) {
//			tmp += a[i] - 48;
//		} else {
//            cont_a = 0;
//        }
//
//		if (cont_b && b[i] != 0) {
//			tmp -= b[i] - 48;
//		} else {
//            cont_b = 0;
//        }
//
//        if (cont_a || cont_b || carry) {
//            if (tmp < 0) {
//                tmp += 10;
//                carry = -1;
//            }
//            else {
//                carry = 0;
//            }
//            a[i] = tmp + 48;
//        }
//        i++;
//	} while (cont_a || cont_b);
//    i--;
//    for (; i > 0; i--) {
//        if (a[i] == 48 || a[i] == 0) {
//            a[i] = 0;
//        } else {
//            break;
//        }
//    }
//}
//
//void shortMultiplySingle(char a[], char b, char c[]) {
//    int i;
//    int carry = 0;
//    int sum = 1;
//    int cont = 0;
//
//    i = 0;
//    b -= 48;
//    do {
//        cont = 1;
//        if (a[i] != 0) {
//            sum = (a[i] - 48) * b;
//        } else {
//            cont = 0;
//            sum = 0;
//        }
//        sum += carry;
//        if (carry || cont) {
//            c[i] = sum % 10 + 48;
//        }
//        carry = sum / 10;
//        i++;
//    } while (carry || cont);
//}
//
//void multiplySingle(char a[], char b, char c[], int start) {
//    int i;
//    int carry = 0;
//    int sum = 1;
//    int cont = 0;
//
//    for (i = 0; i < start; i++) {
//        c[i] = 48;
//    }
//
//    i = 0;
//    b -= 48;
//    do {
//        cont = 1;
//        if (a[i] != 0) {
//            sum = (a[i] - 48) * b;
//        } else {
//            cont = 0;
//            sum = 0;
//        }
//        sum += carry;
//        if (carry || cont) {
//            c[i + start] = sum % 10 + 48;
//        }
//        carry = sum / 10;
//        i++;
//    } while (carry || cont);
//}
//
//void multiply(char a[], char b[], char c[]) {
//    int i = 0;
//    char tmp[COLS];
//    char tmp2[COLS] = {0};
//    char sum[COLS] = {0};
//    int lenC;
//
//    while (b[i] != 0) {
//        reset(tmp);
//        multiplySingle(a, b[i], tmp, i);
//        add(tmp, tmp2, sum);
//        copy(sum, tmp2);
//        reset(sum);
//        i++;
//    }
//    copy(tmp2, c);
//    lenC = len(c);
//    if (len == 0) {
//        c[0] = 48;
//    }
//    for (i = lenC - 1; i > 0 && c[i] == 48; i--) {
//        c[i] = 0;
//    }
//}
//
//// compare strings as numbers
//// a > b returns 1
//// a == b returns 0
//// a < b returns -1
//int strCompare(char a[], char b[]) {
//    int i;
//    int lenA = len(a);
//    int lenB = len(b);
//
//    if (lenA > lenB) {
//        return 1;
//    }
//    else if (lenA < lenB) {
//        return -1;
//    }
//
//    for (i = lenA - 1; i >= 0; i--) {
//        if (a[i] > b[i]) {
//            return 1;
//        }
//        else if (a[i] < b[i]) {
//            return -1;
//        }
//    }
//
//    return 0;
//}
//
//void multiply10(char a[]) {
//    int i, strLen = len(a);
//    // if zero, return
//    if (strLen == 1 && a[0] == 48) {
//        return;
//    }
//    for (i = strLen; i > 0; i--) {
//        a[i] = a[i - 1];
//    }
//    a[0] = 48;
//}
//
//// returns 1 if integer, 0 if float
//int divide2(char n[]) {
//    int i, k, tmp = 0, lenN = len(n);
//    for (i = lenN - 1; i >= 0; i--) {
//        tmp += n[i] - 48;
//
//        k = tmp / 2;
//        n[i] = k + 48;
//        if (k > 0) {
//            tmp %= 2;
//            tmp *= 10;
//        } else {
//            tmp *= 10;
//        }
//    }
//
//    if (n[lenN - 1] == 48) {
//        n[lenN - 1] = 0;
//    }
//
//    if (tmp) {
//        return 0;
//    }
//
//    return 1;
//}
//
//int approx(char n[]) {
//    int i = 1;
//    char tmp[COLS] = {0};
//    while (1) {
//        reset(tmp);
//        intToStr(i * i, tmp);
//        if (strCompare(tmp, n) > 0) {
//            return i - 1;
//        }
//        i++;
//    }
//}
//
//int approxRoot(char r[], char n[], char remainder[]) {
//    int i;
//    char iStr[COLS] = {0};
//    char a[COLS] = {0};
//    char prod[COLS] = {0};
//    multiply10(r);
//    for (i = 0; i <= 10; i++) {
//        reset(iStr);
//        reset(prod);
//        reset(a);
//        intToStr(i, iStr);
//        add(r, iStr, a);
//        multiply(iStr, a, prod);
//        if (strCompare(prod, n) > 0) {
//            if (i == 0) {
//                return 0;
//            }
//            return i - 1;
//        }
//        reset(remainder);
//        sub(n, prod, remainder);
//    }
//
//    return i;
//}
//
//int isZero(char n[]) {
//    int nLen = len(n);
//    if (nLen == 1 && n[0] == 48) {
//        return 1;
//    }
//    return 0;
//}
//
//void addDigit(char a, char b[]) {
//    int i;
//    int lenB = len(b);
//
//    if (lenB > 1 || b[0] != 48) {
//        for (i = lenB; i > 0; i--) {
//            b[i] = b[i - 1];
//        }
//    }
//
//    b[0] = a;
//}
//
//// returns 1 if integer, 0 if float
//int strSqrt(char n[], char result[]) {
//    int strLen = len(n);
//    int newDigit;
//    char a[COLS] = {0};
//    char remainder[COLS] = {0};
//    char tmp[COLS] = {0};
//
//    a[0] = 48;
//    reset(result);
//    result[0] = 48;
//
//    while (1) {
//        if (strLen == 0) {
//            break;
//        }
//
//        addDigit(n[strLen-- - 1], a);
//        if (strLen % 2) {
//            addDigit(n[strLen-- - 1], a);
//        }
//
//        if (isZero(result)) {
//            newDigit = approx(a);
//            result[0] = newDigit + 48;
//            reset(tmp);
//            intToStr(newDigit * newDigit, tmp);
//            sub2arg(a, tmp);
//        } else {
//            reset(tmp);
//            shortMultiplySingle(result, 2 + 48, tmp);
//            reset(remainder);
//            newDigit = approxRoot(tmp, a, remainder);
//            addDigit(newDigit + 48, result);
//            reset(a);
//            copy(remainder, a);
//        }
//    }
//
//    if (strCompare(a, zero) == 1) {
//        return 0;
//    }
//
//    return 1;
//}
//
////    tmp = (double) a * a - (b / 2.0) * (b / 2.0);
////    vb = sqrt(tmp);
////    p = (b * vb) / 2.0;
////
////    pInt = (int) p;
////    if (p - pInt == 0) {
////        printf("%ld %ld %ld = %f\n", a, a, b, p);
////        sum += 2 * a + b;
////    }
//int test(int a, int b) {
//    char aa[COLS] = {0};
//    char bb[COLS] = {0};
//
//    char c[COLS] = {0};
//    char d[COLS] = {0};
//    char tmp[COLS] = {0};
//    char bHalf[COLS] = {0};
//    char bHalfSquare[COLS] = {0};
//    char area[COLS] = {0};
//
//    char vb[COLS] = {0};
//
//    intToStr(a, aa);
//    intToStr(b, bb);
//    intToStr(b / 2, bHalf);
//
//    shortMultiplySingle(bb, '2', c);
//    add(aa, c, d);
//
//    if (strCompare(d, max) == 1) {
//        return 0;
//    }
//
//    multiply(aa, aa, tmp);
//    multiply(bHalf, bHalf, bHalfSquare);
//    sub2arg(tmp, bHalfSquare);
//
//    if (!strSqrt(tmp, vb)) {
//        // not an integer
//        return 1;
//    }
//
//    multiply(bb, vb, area);
//    if (divide2(area) == 1) {
//        add2arg(aa, perimeterSum);
//        add2arg(aa, perimeterSum);
//        add2arg(bb, perimeterSum);
//        return 1;
//    }
//
//    return 1;
//}
//
//int main() {
//    int i, p = PERIMETER;
//
//    zero[0] = 48;
//
//    i = 0;
//    while (p > 0) {
//        max[i++] = p % 10 + 48;
//        p /= 10;
//    }
//
//    i = 1;
//    while (1) {
//        i += 2;
//
//        if (i - 1 % 100000 == 0) {
//            printf("%d\n", i);
//        }
//
//        test(i, i - 1);
//        if (test(i, i + 1) == 0) {
//            break;
//        }
//    }
//
//    rotate(perimeterSum);
//    printf("%s\n", perimeterSum);
//
//    return 0;
//}