#include <stdio.h>
#include <math.h>

int main(int argc, char *argv[])
{
	int i, sum, tmp, res = 0;
	
	for (i = 2; i < 10000000; i++)
	{	
		sum = 0;
		tmp = i;
		
		while (tmp)
		{
			sum = sum + pow(tmp % 10, 5);
			tmp /= 10;
		}
		
		if (i == sum)
		{
			printf("%d\n", i);
			res += sum;
		}
	}
	
	printf("Total sum: %d\n", res);

	system("PAUSE");
	return 0;
}
