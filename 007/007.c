/*
	projecteuler.net

	10001st prime
	Problem 7

	By listing the first six prime numbers: 2, 3, 5, 7, 11, and 13, we can see that the 6th prime is 13.

	What is the 10001st prime number?
*/

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
	int i;
	int n = 2;
	int prime = 0;
	
	int count = 0;
	
	while (1) {
		prime = 0;
		
		for (i = 2; i < n; i++) {
			if (n % i == 0) {
				prime = 1;
				break;
			}
		}
		
		if (prime == 0) {
			count++;
			
			if (count == 10001) {
				break;
			}
		}

		n++;
	}
	
	printf("10001th prime nuber = %d\n", n);
	
	system("PAUSE");
	return 0;
}
