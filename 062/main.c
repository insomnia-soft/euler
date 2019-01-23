/*

Cubic permutations
Problem 62

The cube, 41063625 (345^3), can be permuted to produce two other cubes:
56623104 (384^3) and 66430125 (405^3). In fact, 41063625 is the smallest cube
which has exactly three permutations of its digits which are also cube.

Find the smallest cube for which exactly five permutations of its digits are
cube.


Solution:

127035954683
(5027 7061 7202 8288 8384)

*/

#include <stdio.h>
#define MAX 10000

void reset(int arr[]) {
    int i;
    for (i = 0; i < 10; i++) {
        arr[i] = 0;
    }
}

void countDigits(int arr[], unsigned long long n) {
    unsigned long long tmp;
    while (n > 0) {
        tmp = n % 10;
        arr[(int) tmp]++;
        n /= 10;
    }
}

int compareDigits(int a[], int b[]) {
    int i;
    for (i = 0; i < 10; i++) {
        if (a[i] != b[i]) {
            return 0;
        }
    }
    return 1;
}

int main() {
    unsigned long long i, j, k, l, m;
    unsigned long long ii, jj, kk, ll, mm;
    int di[10];
    int dj[10];
    int dk[10];
    int dl[10];
    int dm[10];

    for (i = 1; i < MAX - 4; i++) {
        reset(di);
        ii = i * i * i;
        countDigits(di, ii);

        for (j = i + 1; j < MAX - 3; j++) {
            reset(dj);
            jj = j * j * j;
            countDigits(dj, jj);

            if (!compareDigits(di, dj)) {
                continue;
            }

            for (k = j + 1; k < MAX - 2; k++) {
                reset(dk);
                kk = k * k * k;
                countDigits(dk, kk);

                if (!compareDigits(di, dk)) {
                    continue;
                }

                for (l = k + 1; l < MAX - 1; l++) {
                    reset(dl);
                    ll = l * l * l;
                    countDigits(dl, ll);

                    if (!compareDigits(di, dl)) {
                        continue;
                    }

                    for (m = l + 1; m < MAX; m++) {
                        reset(dm);
                        mm = m * m * m;
                        countDigits(dm, mm);

                        if (!compareDigits(di, dm)) {
                            continue;
                        }

                        printf("%llu %llu %llu %llu %llu\n", i, j, k, l, m);
                        return 0;
                    }
                }
            }
        }
    }

    return 0;
}
