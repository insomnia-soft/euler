/*

Powerful digit sum
Problem 56

A googol (10^100) is a massive number: one followed by one-hundred zeros;
100^100 is almost unimaginably large: one followed by two-hundred zeros.
Despite their size, the sum of the digits in each number is only 1.

Considering natural numbers of the form, a^b, where a, b < 100, what is the
maximum digital sum?


Solution:

?

*/


#include <stdlib.h>
#include <stdio.h>

#define MAX 10000
#define TARGET 10000

void print(char a[]) {
	for (int i = 0; a[i] != 0; i++) {
		printf("%c", a[i]);
	}
	printf("\n");
}

int len(char a[]) {
    int i = 0;
    for (i = 0; a[i] != 0; i++);
    return i;
}

void reset(char a[]) {
    int i = 0;
    for (i = 0; i < MAX; i++) {
        a[i] = 0;
    }
}

void rotateTo(char a[], char b[]) {
    int i, strLen;
    strLen = len(a);
    reset(b);
    for (i = 0; i < strLen; i++) {
        b[strLen - 1 - i] = a[i];
    }
    for (i = strLen - 1; i >= 0; i--) {
        if (b[i] == 48) {
            b[i] = 0;
        } else {
            break;
        }
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

int isPalindrome(char a[]) {
    int i;
    int strLen = len(a);

    for (i = 0; i < strLen / 2; i++) {
        if (a[i] != a[strLen - 1 - i]) {
            return 0;
        }
    }

    return 1;
}

int main() {
    int i;
    char a[MAX] = {0};
    char b[MAX] = {0};
    int iteration;
    int palindrome;
    int total = 0;

    for (i = 1; i < MAX; i++) {
        iteration = 1;
        palindrome = 0;
        reset(a);
        intToStr(i, a);

        do {
            reset(b);
            rotateTo(a, b);
            add(a, b);
            reset(a);
            copy(b, a);
            if (isPalindrome(a)) {
                palindrome = 1;
                break;
            }
            iteration++;
        } while (iteration < 50);

        if (!palindrome) {
            printf("Lychrel number: %d\n", i);
            total++;
        }
    }

    printf("Total Lychrel's numbers below %d = %d\n", MAX, total);

    return (EXIT_SUCCESS);
}
