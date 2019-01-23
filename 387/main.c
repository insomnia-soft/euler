/*

Harshad Numbers
Problem 387

A Harshad or Niven number is a number that is divisible by the sum of its
digits.
201 is a Harshad number because it is divisible by 3 (the sum of its digits.)
When we truncate the last digit from 201, we get 20, which is a Harshad number.
When we truncate the last digit from 20, we get 2, which is also a Harshad
number.
Let's call a Harshad number that, while recursively truncating the last digit,
always results in a Harshad number a right truncatable Harshad number.

Also:
201/3=67 which is prime.
Let's call a Harshad number that, when divided by the sum of its digits, results
in a prime a strong Harshad number.

Now take the number 2011 which is prime.
When we truncate the last digit from it we get 201, a strong Harshad number that
is also right truncatable.
Let's call such primes strong, right truncatable Harshad primes.

You are given that the sum of the strong, right truncatable Harshad primes less
than 10000 is 90619.

Find the sum of the strong, right truncatable Harshad primes less than 10^14.


Solution:

696067597313468

- 26 s


Below are 3 digits (first column) and 4 digits (second column) harshad numbers.
I noticed 4 digits harshad numbers start with 3 digits harshad numbers.

100	1000
	1002
	1008
102	1020
	1026
108	1080
	1088
120	1200
	1204
	1206
126	1260
180	1800
200	2000
	2001
	2004
	2007
201	2010
	2016
204	2040
	2043
207	2070
209	2090
210	2100
	2106
216	2160
240	2400
	2401
	2403
	2408
243	2430
247	2470
	2478
270	2700
	2704
300	3000
	3006
306	3060
308	3080
360	3600
364	3640
400	4000
	4002
	4005
	4008
402	4020
	4023
405	4050
407	4070
408	4080
	4086
420	4200
	4203
423	4230
450	4500
480	4800
	4802
	4806
	4807
	4809
481	4810
486	4860
500	5000
	5004
504	5040
	5044
506	5060
	5066
540	5400
600	6000
	6003
603	6030
605	6050
630	6300
700	7000
	7002
702	7020
704	7040
720	7200
	7208
800	8000
	8001
	8004
801	8010
803	8030
804	8040
	8046
810	8100
840	8400
	8406
846	8460
	8463
900	9000
902	9020
	9022
1000    10000


 */

#include <stdio.h>

#define MAX 100000000000000

int isPrime(unsigned long long n) {
    unsigned long long i = 5;
    unsigned long long w = 2;

    if (n == 2) {
        return 1;
    }
    else if (n == 3) {
        return 1;
    }
    else if (n % 2 == 0) {
        return 0;
    }
    else if (n % 3 == 0) {
        return 0;
    }

    while (i * i <= n) {
        if (n % i == 0) {
            return 0;
        }
        i += w;
        w = 6 - w;
    }

    return 1;
}

int isStrongRightHarshad(unsigned long long n, int step) {
    long m = n;
    long sum = 0;
    while (m > 0) {
        sum += m % 10;
        m /= 10;
    }
    if (n % sum == 0) {
        if (step == 0 && !isPrime(n / sum)) {
            return 0;
        }
        if (n >= 10) {
            return isStrongRightHarshad(n / 10, step + 1);
        } else {
            return 1;
        }
    }
    return 0;
}

int isRightHarshad(unsigned long long n) {
    long m = n;
    long sum = 0;
    while (m > 0) {
        sum += m % 10;
        m /= 10;
    }
    if (n % sum == 0) {
        if (n >= 10) {
            return isRightHarshad(n / 10);
        } else {
            return 1;
        }
    }
    return 0;
}

int main() {
    int i;
    unsigned long long n;
    unsigned long long m;
    unsigned long long sum = 0;
    unsigned long long harshed[100] = {0};
    int harshedCount = 0;

    for (i = 100; i < 1000; i++) {
        if (isRightHarshad(i)) {
            harshed[harshedCount] = i;
            harshedCount++;
        }
        if (isPrime(i)) {
            if (isStrongRightHarshad(i / 10, 0)) {
                sum += i;
            }
        }
    }

    while (harshedCount > 0) {
        n = harshed[harshedCount - 1] * 10;
        harshedCount--;

        for (i = 0; i <= 9; i++) {
            m = n;
            m += i;

            if (m >= MAX) {
                continue;
            }

            if (isRightHarshad(m)) {
                harshed[harshedCount] = m;
                harshedCount++;
            }
            if (isPrime(m)) {
                if (isStrongRightHarshad(m / 10, 0)) {
                    sum += m;
                }
            }
        }
    }

    printf("%llu\n", sum);

    return 0;
}
