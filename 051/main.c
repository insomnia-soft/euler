/*

Prime digit replacements
Problem 51

By replacing the 1st digit of the 2-digit number *3, it turns out that six of
the nine possible values: 13, 23, 43, 53, 73, and 83, are all prime.

By replacing the 3rd and 4th digits of 56**3 with the same digit, this 5-digit
number is the first example having seven primes among the ten generated numbers,
yielding the family: 56003, 56113, 56333, 56443, 56663, 56773, and 56993.
Consequently 56003, being the first member of this family, is the smallest prime
with this property.

Find the smallest prime which, by replacing part of the number (not necessarily
adjacent digits) with the same digit, is part of an eight prime value family.


Solution:

121313
.2.3.3 (mask)

*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX 10
#define TARGET 8

int countMax = 0;

void rotate(char *a, int strLen) {
    char tmp;
    int i;
    for (i = 0; i < strLen / 2; i++) {
        tmp = a[i];
        a[i] = a[strLen - i - 1];
        a[strLen - i - 1] = tmp;
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

int isPrime(int n) {
    int i;
    for (i = 2; i < n / 2; i++) {
        if (n % i == 0) {
            return 0;
        }
    }
    return 1;
}

void printArray(int *arr, int sz) {
    int i;
    printf("%d: ", sz);
    for (i = 0; i < sz; i++) {
        printf("%d", arr[i]);
    }
    printf("\n");
}

void generateNumber(int *arrayMask, int maskLen, int digitCount) {
    int i, j;
    int mask[MAX] = {0};
    char str[MAX + 1] = {0};
    int minNumber = 1;
    int maxNumber = 1;
    int tmp;
    int digit;
    int d;
    int count;
    int lastPrime = 0;
    int generatedNumber;

    for (i = 0; i < maskLen; i++) {
        mask[arrayMask[i] - 1] = 1;
    }

    minNumber = 1 * pow(10, digitCount - maskLen - 1);
    maxNumber = minNumber * 10;

    for (i = minNumber; i < maxNumber; i++) {
        count = 0;
        digit = 0;
        for (digit = 9; digit >= 0; digit--) {
            tmp = i;
            for (d = 0; d < digitCount; d++) {
                if (mask[d] == 1) {
                    str[d] = digit + 48;
                } else {
                    str[d] = tmp % 10 + 48;
                    tmp /= 10;
                }
            }
            if (str[digitCount - 1] == 48) {
                continue;
            }
            generatedNumber = strToInt(str);
            if (isPrime(generatedNumber)) {
                count++;
                lastPrime = generatedNumber;
            }
        }
        if (count > countMax) {
            countMax = count;
            if (countMax == TARGET) {
                printf("%d\n", lastPrime);
                exit(EXIT_SUCCESS);
            }
        }
    }
}

void generateMask(int n, int r, int *arr, int size, int digitCount) {
    int i;
    for (i = n; i >= r; i--) {
        arr[r - 1] = i;
        if (r > 1) {
            generateMask(i - 1, r - 1, arr, size, digitCount);
        } else {
            generateNumber(arr, size, digitCount);
        }
    }
}

int main() {
    int i, j, arr[MAX] = {0};

    for (i = 2; i < 8; i++) {
        for (j = 1; j < i; j++) {
            generateMask(i, j, arr, j, i);
        }
    }

    return (EXIT_SUCCESS);
}
