/*

Bouncy numbers
Problem 112

Working from left-to-right if no digit is exceeded by the digit to its left it
is called an increasing number; for example, 134468.

Similarly if no digit is exceeded by the digit to its right it is called a
decreasing number; for example, 66420.

We shall call a positive integer that is neither increasing nor decreasing a
"bouncy" number; for example, 155349.

Clearly there cannot be any bouncy numbers below one-hundred, but just over half
of the numbers below one-thousand (525) are bouncy. In fact, the least number
for which the proportion of bouncy numbers first reaches 50% is 538.

Surprisingly, bouncy numbers become more and more common and by the time we
reach 21780 the proportion of bouncy numbers is equal to 90%.

Find the least number for which the proportion of bouncy numbers is exactly 99%.


Solution:

1587000

- 30 ms

*/

#include <stdio.h>

int isBouncy(int n) {
    int digit, prev = -1;
    int up = 0, down = 0;

    while (n > 0) {
        digit = n % 10;
        n /= 10;
        if (prev != -1) {
            if (prev == digit) {
                continue;
            }
            else if (prev < digit) {
                prev = digit;
                up = 1;
            }
            else {
                prev = digit;
                down = 1;
            }
            if (up == 1 && down == 1) {
                return 1;
            }
        } else {
            prev = digit;
        }
    }

    return 0;
}

int main() {
    long i = 1, bouncy = 0;
    while (1) {
        if (isBouncy(i)) {
            bouncy++;
        }
        if ((double) bouncy / i == 0.99) {
            break;
        }
        i++;
    }
    printf("%ld\n", i);

    return 0;
}

