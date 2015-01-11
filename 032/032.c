#include <stdio.h>
#include <stdlib.h>

void reset(int *n)
{
	int i = 0;
	
	while (i < 11)
	{
		*(n + i) = 0;
		i++;
	}
}

int main(int argc, char *argv[])
{
	int i, j, k, n, dalje, sum, x;
	int polje[11] = {0};
	int numbers[100] = {0};
	int numbers_count = 0;
	
	i = 1;
	sum = 0;
	
	while (1)
	{
		for (j = 2; j < i; j++)
		{
			if (i % j == 0)
			{
				reset(polje);

				k = i / j;
				dalje = 1;

				n = i;
				while (n > 0)
				{
					if (polje[n % 10] == 1 || n % 10 == 0)
					{
						dalje = 0;
						break;
					}
					else
						polje[n % 10] = 1;

					n /= 10;
				}
				
				if (dalje == 1)
				{
					n = j;
					while (n > 0)
					{
						if (polje[n % 10] == 1 || n % 10 == 0)
						{
						    dalje = 0;
						    break;
						}
						else
						    polje[n % 10] = 1;

						n /= 10;
					}
				}
				
				if (dalje == 1)
				{
					n = k;
					while (n > 0)
					{
						if (polje[n % 10] == 1 || n % 10 == 0)
						{
					    	dalje = 0;
					    	break;
						}
						else
					    	polje[n % 10] = 1;

						n /= 10;
					}
				}
				
				if (dalje == 1)
				{
					for (n = 1; n <= 9; n++)
					{
						if (polje[n] == 0)
						{
							dalje = 0;
							break;
						}
					}
				}
				
				if (dalje == 1)
				{
					dalje = 1;
					
					for (x = 0; x < numbers_count; x++)
						if (i == numbers[x])
						{
							dalje = 0;
							break;
						}
						
					if (dalje == 1)
					{
                        numbers[numbers_count] = i;
						numbers_count++;
						sum += i;
				    	printf("%d * %d = %d [%d]\n", j, k, i, sum);
					}
				    
				    //system("pause");
				}
			}
		}

		i++;
	}

	system("PAUSE");	
	return 0;
}
