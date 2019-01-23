/*

Largest exponential
Problem 99

Comparing two numbers written in index form like 2^11 and 3^7 is not difficult,
as any calculator would confirm that 2^11 = 2048 < 3^7 = 2187.

However, confirming that 632382^518061 > 519432^525806 would be much more
difficult, as both numbers contain over three million digits.

Using base_exp.txt (right click and 'Save Link/Target As...'), a 22K text file
containing one thousand lines with a base/exponent pair on each line, determine
which line number has the greatest numerical value.

NOTE: The first two lines in the file represent the numbers in the example given
above.


Solution:

709

- 0 ms
- convert all to 2^power using logarithms
- compare powers

2^x = 10^1
log(2^x) = log(10^1)
x * log(2) = 1 * log(10)
x = 1 * (log(10)/log(2))

*/


#include <stdio.h>

#define NUMBERS 1000

int n[NUMBERS][2] = {0};
double p[NUMBERS] = {0};
double max = 0;
int max_index;

void test(int index) {
    double a;
    a = n[index][1] * (log10(n[index][0]) / log10(2));

    if (a > max) {
        max = a;
        max_index = index;
    }
}

int readFile() {
    FILE *fp;
    char file[] = "p099_base_exp.txt";
    char row[100];
    int i, r = 0, tmp;

    fp = fopen(file, "r");

    if (!fp) {
        printf("Can't open file %s!\n", file);
        return 0;
    }

    while (fgets(row, 100, fp)) {
        tmp = 0;
        i = 0;
        while (1) {
            if (row[i] == 10 || row[i] == 0) {
                n[r][1] = tmp;
                break;
            }
            else if (row[i] == ',') {
                n[r][0] = tmp;
                tmp = 0;
            }
            else {
                tmp *= 10;
                tmp += row[i] - 48;
            }
            i++;
        }

        r++;
    }

    return 1;
}

int main() {
    int i;

    if (!readFile()) {
        return 0;
    }

    for (i = 0; i < NUMBERS; i++) {
        test(i);
    }

    printf("%d\n", max_index + 1);

    return 0;
}




















//#include <stdio.h>
//
//#define NUMBERS 1000
//#define COLS 10000000
//
//int n[NUMBERS][2] = {0};
//
//char a[COLS] = {0};
//char b[COLS] = {0};
//char c[COLS] = {0};
//
//// multiply
//char x1[COLS] = {0};
//char x2[COLS] = {0};
//char x3[COLS] = {0};
//
//// strPow
//char x4[COLS] = {0};
//char x5[COLS] = {0};
//char x6[COLS] = {0};
//
//
//void reset(char a[]) {
//    int i;
//    for (i = 0; i < COLS; i++) {
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
//
//    reset(x2);
//    reset(x3);
//
//    while (b[i] != 0) {
//        reset(x1);
//        multiplySingle(a, b[i], x1, i);
//        add(x1, x2, x3);
//        copy(x3, x2);
//        reset(x3);
//        i++;
//    }
//    copy(x2, c);
//}
//
//void strPow(int a, int b, char *c) {
//    int i;
//    reset(x4);
//    reset(x5);
//    reset(x6);
//
//    intToStr(a, x5);
//    intToStr(a, x6);
//
//    for (i = 1; i < b; i++) {
//        multiply(x5, x6, x4);
//        copy(x4, x5);
//        reset(x4);
//    }
//    copy(x5, c);
//}
//
//void test(int x, int y) {
//    reset(a);
//    strPow(x, y, a);
//    printf("%s\n", a);
//}
//
//int readFile() {
//    FILE *fp;
//    char file[] = "p099_base_exp.txt";
//    char row[100];
//    int i, r = 0, tmp;
//
//    fp = fopen(file, "r");
//
//    if (!fp) {
//        printf("Can't open file %s!\n", file);
//        return 0;
//    }
//
//    while (fgets(row, 100, fp)) {
//        tmp = 0;
//        i = 0;
//        while (1) {
//            if (row[i] == 10 || row[i] == 0) {
//                n[r][1] = tmp;
//                break;
//            }
//            else if (row[i] == ',') {
//                n[r][0] = tmp;
//                tmp = 0;
//            }
//            else {
//                tmp *= 10;
//                tmp += row[i] - 48;
//            }
//            i++;
//        }
//
//        r++;
//    }
//
//    return 1;
//}
//
//int main() {
//    int i;
//
//    if (!readFile()) {
//        return 0;
//    }
//
////    test(n[0][0], n[0][1]);
////    for (i = 0; i < NUMBERS; i++) {
////        test(n[i][0], n[i][1]);
////    }
//
//    printf("%f\n", (3 * log10(3)) / log10(2));
//
//    return 0;
//}