/*

Coin partitions
Problem 78

Let p(n) represent the number of different ways in which n coins can be
separated into piles. For example, five coins can be separated into piles in
exactly seven different ways, so p(5)=7.

OOOOO
OOOO O
OOO OO
OOO O O
OO OO O
OO O O O
O O O O O

Find the least value of n for which p(n) is divisible by one million.


Solution:

55374

- 41 sec
- https://en.wikipedia.org/wiki/Pentagonal_number_theorem

*/


#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#define MAX 100000
#define LEN 1000

char p[MAX][LEN] = {0};
int pent[MAX] = {0};
int pentCount = 0;
int pentK = 1;

int len(char a[]) {
    int i;
    for (i = 0; a[i] != 0; i++);
    return i;
}

void reset(char a[]) {
    for (int i = 0; i < LEN; i++) {
        a[i] = 0;
    }
}

void print(char a[]) {
	for (int i = 0; a[i] != 0; i++) {
		printf("%c", a[i]);
	}
	printf("\n");
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

void add(char *a, char *b) {
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

void sub(char a[], char b[], char c[]) {
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
            c[i] = tmp + 48;
        }
        i++;
	} while (cont_a || cont_b);
    for (; i >= 0; i--) {
        if (c[i] == 48 || c[i] == 0) {
            c[i] = 0;
        } else {
            break;
        }
    }
}

void nextPent() {
    pent[pentCount++] = (pentK * (3 * pentK - 1)) / 2;
    if (pentK > 0) {
        pentK *= -1;
    } else {
        pentK = pentK * -1 + 1;
    }
}

int check(char a[]) {
    int i;
    for (i = 0; i < 6; i++) {
        if (a[i] != 48) {
            return 0;
        }
    }
    return 1;
}

int main() {
    int n;
    int i;
    int minusIndex = 1;

    p[0][0] = 1 + 48;
    p[1][0] = 1 + 48;

    pent[pentCount++] = 1;

    for (n = 2; n < MAX; n++) {
        i = 1;
        minusIndex = 1;
        while (1) {
            if (i > pentCount - 1) {
                nextPent();
            }
            if (n - pent[i] < 0) {
                break;
            }
            switch (minusIndex) {
                case 1:
                case 2:
                    add(p[n - pent[i]], p[n]);
                    break;

                case 3:
                case 4:
                    sub(p[n], p[n - pent[i]], p[n]);
                    break;
            }

            minusIndex++;
            if (minusIndex > 4) {
                minusIndex = 1;
            }

            i++;
        }

        if (check(p[n])) {
            break;
        }
    }

    rotate(p[n]);
    printf("p(%d) = %s\n", n, p[n]);

    return 0;
}





// dosta brzo ali pojede sav RAM i swap
// https://www.youtube.com/watch?v=ZaVM057DuzE
//
//#include <stdio.h>
//#define COLS 125
//#define MAX 12000
//
//int m = 0;
//char arr[MAX][MAX][COLS] = {0};
//
//int len(char a[]) {
//    int i = 0;
//    for (i = 0; a[i] != 0; i++);
//    return i;
//}
//
////void rotate(char a[]) {
////    char tmp;
////    int i, strLen;
////    strLen = len(a);
////    for (i = 0; i < strLen / 2; i++) {
////        tmp = a[i];
////        a[i] = a[strLen - i - 1];
////        a[strLen - i - 1] = tmp;
////    }
////}
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
//int check(char a[]) {
//    int i;
//    for (i = 0; i < 6; i++) {
//        if (a[i] != 48) {
//            return 0;
//        } else {
//            if (m < i) {
//                m = i;
//            }
//        }
//    }
//    return 1;
//}
//
//int main() {
//    int col, row;
//
//    arr[0][0][0] = 1 + 48;
//    for (row = 1; row < MAX; row++) {
//        arr[row][0][0] = 1 + 48;
//    }
//    for (row = 1; row < MAX; row++) {
//        for (col = 1; col < MAX; col++) {
//            if (row > col) {
//                copy(arr[row - 1][col], arr[row][col]);
//            } else {
//                add(arr[row - 1][col], arr[row][col - row], arr[row][col]);
//
//                if (col == row) {
//                    if (check(arr[row][col])) {
//                        printf("p(%d) = %s\n", row, arr[row][col]);
//                        row = MAX;
//                        col = MAX;
//                    }
//                }
//            }
//        }
//    }
//
//    printf("%s\n", arr[5][5]);
//
//    for (row = 0; row < MAX; row++) {
//        printf("p(%d) = %s (%d)\n", row + 1, arr[row][row], len(arr[row][row]));
//    }
//
//    printf("%d\n", m);
//
//    return 0;
//}





// dobro radi, ali treba big int
//
//#include <stdio.h>
//
//#define MAX 500
//
//char arr[MAX][MAX][50] = {0};
//
//int main() {
//    int col, row;
//
//    arr[0][0] = 1;
//    for (row = 1; row < MAX; row++) {
//        arr[row][0] = 1;
//    }
//    for (row = 1; row < MAX; row++) {
//        for (col = 1; col < MAX; col++) {
//            if (row > col) {
//                arr[row][col] = arr[row - 1][col];
//            } else {
//                arr[row][col] = arr[row - 1][col] + arr[row][col - row];
//            }
//        }
//    }
//
////    printf("%llu\n", arr[MAX - 1][MAX - 1]);
//    for (row = 0; row < MAX; row++) {
//        printf("p(%d) = %llu\n", row + 1, arr[row][row]);
//    }
//
//    return 0;
//}





// još sporije
//
//#include <stdio.h>
//
//int step(int col, int row) {
//    if (row > col) {
//        return step(col, row - 1);
//    } else {
//        if (row == 0) {
//            if (col == 0) {
//                return 1;
//            } else {
//                return 0;
//            }
//        }
//        return step(col, row - 1) + step(col - row, row);
//    }
//}
//
//int main() {
//    int n;
//    int p;
//
//    n = 100;
//
//    p = step(n, n);
//
//    printf("%d\n", p);
//
//    return 0;
//}





// sporo
//
//#include <stdio.h>
//
//int count = 0;
//
//void step(int max, int sum, int maxChar) {
//    int i;
//    int tmpSum;
//
//    for (i = 1; i <= maxChar; i++) {
//        tmpSum = sum + i;
//        if (tmpSum == max) {
//            count++;
//        }
//        else if (tmpSum < max) {
//            step(max, tmpSum, i);
//        }
//    }
//}
//
//int main() {
//    int i;
//    int value = 1;
//
//    do {
//        value++;
//        count = 1;
//        for (i = 1; i <= value; i++) {
//            step(value, i, i);
//        }
//        printf("[%d] %d\n", value, count);
//    } while (count % 1000000 != 0);
//
//    printf("%d\n", value);
//
//    return 0;
//}
