#include <stdio.h>
#include <stdlib.h>

int is_prime(int n)
{
	int i;
	
	for (i = 2; i < n; i++)
		if (n % i == 0)
			return 0;

	return 1;
}


int main(int argc, char *argv[])
{
	int n, a, b, prim, max, max_a, max_b;
	long res;
	
	max = 0;

	for (a = -999; a <= 999; a++)
	{
		for (b = -999; b <= 999; b++)
		{
			n = 0;
			
			do
			{
				res = n * n + a * n + b;
				
				if (res > 0)
					prim = is_prime(res);
				else
					break;

				n++;
			}
            while (prim == 1);
            
            n--;
            
            if (n > max)
			{
            	max_a = a;
            	max_b = b;
				max = n;
			}
		}
	}
	
	printf("%d * %d = %d\n", max_a, max_b, max_a * max_b);
	system("PAUSE");	
	return 0;
}
