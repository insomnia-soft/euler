#include <stdio.h>

int main(int argc, char *argv[])
{
	int i, j, a, b, prod1, prod2;
	float res1, res2;
	
	prod1 = 1;
	prod2 = 1;
	
	for (i = 10; i < 100; i++)
	{
		for (j = 10; j < 100; j++)
		{
			a = (int) (i / 10);
			b = (int) (j / 10);
			
			res1 = (float) a / b;
			res2 = (float) i / j;
			
			if (res1 != res2)
			{
				res1 = (float) i / j;
				
				a = (int) (i / 10);
				b = j % 10;
				
				res2 = (float) a / b;
				
				if (res1 == res2 && res1 < 1)
				{
					a = i % 10;
					b = (int) (j / 10);
				
					if (a == b)
					{
						prod1 *= i;
						prod2 *= j;
						printf("%d %d\n", i, j);
					}
				}
			}			
		}
	}
	
	printf("%d / %d\n", prod1, prod2);
	
	a = 1;
	
	while (a == 1)
	{
		a = 0;
		
		for (i = 2; i < prod2; i++)
		{
			if (prod1 % i == 0 && prod2 % i == 0)
			{
				prod1 /= i;
				prod2 /= i;
				a = 1;
				break;
			}
		}
	}
	
	printf("%d / %d\n", prod1, prod2);


	system("PAUSE");
	return 0;
}
