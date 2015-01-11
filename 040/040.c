/*

An irrational decimal fraction is created by concatenating the positive integers:

0.123456789101112131415161718192021...

It can be seen that the 12^(th) digit of the fractional part is 1.

If d_(n) represents the n^(th) digit of the fractional part, find the value of the following expression.

d_(1) × d_(10) × d_(100) × d_(1000) × d_(10000) × d_(100000) × d_(1000000)

*/

#include <stdio.h>

void reset(char *a)
{
	int i = 0;
	while (*(a + i) != 0)
	{
		*(a + i) = 0;
		i++;
	}
}

int split(int n, char *a)
{
	int i;
	int len = 0;
	int tmp = n;
	
	while (tmp > 0)
	{
		tmp /= 10;
		len++;
	}
	
	tmp = n;
	for (i = len - 1; i >= 0; i--)
	{
		*(a + i) = tmp % 10 + 48;
		tmp /= 10;
	}
		
	return len;
}

int main(int argc, char *argv[])
{
	int i, j, len, redni, res;
	char n[100] = {0};
	
	i = 11;
	redni = 11;
	res = 1;
	
	while (i <= 1000000)
	{
		reset(n);
		//doznati duljinu
		len = split(i, n);
		
		j = 0;
		while (n[j] > 0)
		{
			redni++;
			
			
			if (redni == 100)
			{
				res *= (n[j] - 48);
				printf("100: %d\n", res);
			}
			else if (redni == 1000)
			{
				res *= (n[j] - 48);
				printf("1000: %d\n", res);
			}
			else if (redni == 10000)
			{
				res *= (n[j] - 48);
				printf("10000: %d\n", res);
			}
			else if (redni == 100000)
			{
				res *= (n[j] - 48);
				printf("100000: %d\n", res);
			}
			else if (redni == 1000000)
			{
				res *= (n[j] - 48);
				printf("1000000: %d\n", res);
			}
			
			// printf("%d: %c\n", redni, n[j]);
			
			/*
			   1    5     10    15    20    25    30
			0. 1234 56789 10111 21314 15161 71819 2021...
			*/
			
			j++;
		}
		
		i++;
	}
	
	printf("%d\n", res);

	system("PAUSE");
	return 0;
}
