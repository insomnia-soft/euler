/*
    projecteuler.net

    2: Each new term in the Fibonacci sequence is generated by adding the previous two terms.
    By starting with 1 and 2, the first 10 terms will be:

    1, 2, 3, 5, 8, 13, 21, 34, 55, 89, ...

    Find the sum of all the even-valued terms in the sequence which do not exceed four million.
*/


#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    int i = 1;
    int j = 1;
    int tmp;
    int sum = 0;

    for (; i < 4000000;) {
        if (i % 2 == 0) {
            sum += i;
        }

        printf("%d\n", i);

        tmp = i;
        i += j;
        j = tmp;
    }

    printf("sum = %d\n", sum);

    system("PAUSE");
    return 0;
}
