#include <stdio.h>
#define MAX 100000

int pot(int a)
{
	int i;
	long ret = 1;
	
	for (i = 1; i <= a; i++)
	    ret *= 10;
	
	if (a == 0)
	    return 1;
	else
	    return ret;
}

int rotate_check(int n)
{
	int i;
	int len = 0;
	int last;
	int tmp;
	
	i = n;
	
	while (i > 0)
	{
		i /= 10;
		len++;
	}
	
	for (i = 1; i < len; i++)
	{
		last = n % 10;
		tmp = n / 10;
		n = last * pot(len - 1) + tmp;
		
		if (!is_prime(n))
			return 0;
	}
	
	return 1;
}

int is_prime(int n)
{
	int i;
	
	for (i = 2; i < (n / 2); i++)
	    if (n % i == 0)
	        return 0;
	        
	return 1;
}

int main(int argc, char *argv[])
{
	int i, total = 0;
	
	for (i = 11; i <= 1000000; i = i + 2)
		if (is_prime(i))
		    if (rotate_check(i))
		    {
				printf("%d\n", i);
		        total++;
			}

	printf("TOTAL: %d\n", total + 4); // +4 jer ne provjerava brojeve od 1 do 10, a primarni su 2, 3, 5, 7

	system("PAUSE");	
	return 0;
}
