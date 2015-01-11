#include <stdio.h>
#include <math.h>
#define MAX 2000000

int main(int argc, char *argv[])
{
	int i, j, n, prim, ok, tmp, d, sum, total;
	char primes[MAX] = {0};
	
	i = 1;
	sum = 0;
	total = 0;
	
	while (1)
	{
		i++;
		
		prim = 1;
		n = i;
		
		for (j = 2; j < n; j++)
		{
			if (n % j == 0)
			{
				prim = 0;
				break;
			}
		}
		
		if (prim)
		{
			primes[i] = 1;
				
			if (i > 10)
			{
				ok = 1;
				n = i;
				d = 0;
				
				while ((int) (n / 10) > 0)
				{
					if (primes[(int) (n / 10)] != 1)
					{
						ok = 0;
						break;
					}
					d++;
					n /= 10;
				}
				
				if (ok == 1)
				{
					j = 0;
					ok = 1;

					while (d > 0)
					{
						tmp = (float) pow(10, d);
						n = i % tmp;
						d--;
						if (primes[n] != 1)
						{
							ok = 0;
							break;
						}
					}
				
					if (ok == 1)
					{
						sum += i;
						total++;
						printf("[%d]: %d [%d]\n", total, i, sum);
					}
				}
			}
		}
	}

	system("PAUSE");
	return 0;
}
