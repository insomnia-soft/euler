#include <stdio.h>

int main(int argc, char *argv[])
{
	int polje[10001] = {0};
	int i, j, sum, sum2, sum3 = 0;
	
	for (i = 2; i <= 10000; i++)
	{
		sum = 0;
		sum2 = 0;
		
		for (j = 1; j < i; j++)
		{
			if (i % j == 0)
				sum += j;
		}
		
		for (j = 1; j < sum; j++)
		{
			if (sum % j == 0)
				sum2 += j;
		}
				
		if (i == sum2 && i != sum)
		{
			printf("[%2d] %d = %d\n", i, sum, sum2);
			sum3 += i;
		}
			
	}
	printf("%d\n", sum3);
	system("PAUSE");
	return 0;
}
