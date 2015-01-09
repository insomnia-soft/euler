/*
	projecteuler.net
	
	Largest palindrome product
	Problem 4

	A palindromic number reads the same both ways. The largest palindrome made from the product of two 2-digit numbers is 9009 = 91 × 99.

	Find the largest palindrome made from the product of two 3-digit numbers.
*/

#include <stdio.h>
#include <stdlib.h>

int palindrom(int n) {
	char norm[10] = {0};
	char back[10] = {0};
	int i = 0;
	int m = n;
	int ost;

	do {
		norm[i] = n % 10 + 48;
		n /= 10;
		i++;
	} while (n > 0);
	
	i--;
	
	do {
		back[i] = m % 10 + 48;
		m /= 10;
		i--;
	} while (m > 0);
	
	return strcmp(norm, back);
}

int main(int argc, char *argv[]) {
	int i, j, k;
	int max = 0;
	int max1, max2;
	
	for (i = 100; i < 1000; i++) {
	    for (j = 100; j < 1000; j++) {
			if (!palindrom(i * j)) {
			    if (max < (i * j))
			    {
			        max = i * j;
			        max1 = i;
			        max2 = j;
				}
			}
		}
	}

	printf("%d * %d = %d\n", max1, max2, max);

	system("PAUSE");
	return 0;
}
