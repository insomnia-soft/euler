/*
    Double-base palindromes
    Problem 36

    The decimal number, 585 = 1001001001 (binary), is palindromic in both bases.

    Find the sum of all numbers, less than one million, which are palindromic in base 10 and base 2.

    (Please note that the palindromic number, in either base, may not include leading zeros.)
*/

#include <stdio.h>
#define MAX 30

void reset(char *a) {
    int i = 0;

    while (*(a + i)) {
        *(a + i) = 0;
        i++;
    }
}

int isto(char *a) {
    int i, len;

    len = 0;

    while (*(a + len))
    len++;

    for (i = 0; i < (int) (len / 2); i++)
        if (*(a + i) != *(a + len - i - 1))
            return 0;

    return 1;
}

int main(int argc, char *argv[]) {
    int i, n, x, ret, sum;
    char bin[MAX] = {0};
    sum = 0;

    for (i = 1; i <= 1000000; i++) {
        reset(bin);

        x = 0;
        n = i;
        while (n > 0) {
            bin[x] = n % 10 + 48;
            x++;
            n /= 10;
        }

        ret = isto(bin);

        if (ret) {
            reset(bin);
            x = 0;
            n = i;
            while (n > 0) {
                bin[x] = n % 2 + 48;
                x++;
                n /= 2;
            }

            ret = isto(bin);

            if (ret) {
                sum += i;
                printf("%d [%d]\n", i, sum);
            }
        }
    }

    system("PAUSE");
    return 0;
}
