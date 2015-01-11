#include <stdio.h>

int main(int argc, char *argv[])
{
	int i, j, k, razlika, exist, sum;
	long total_sum;
	int x, y;
	
	int abu[50000] = {0};
	int count_abu = 0;
	
	for (i = 1; i <= 10000000; i++)
	{
		sum = 0;
		exist = 0;
		
		for (j = 1; j < i; j++)
		{
			if (i % j == 0)
				sum += j;
		}
		
		if (sum > i)
		{
			abu[count_abu] = i;
			count_abu++;
		}
		
		for (j = 0; j < (count_abu - 1); j++)
		{
			razlika = i - abu[j];
			
			exist = 0;
			
			for (k = 0; k < count_abu; k++)
			{
				if (abu[k] == razlika)
				{
					x = abu[j];
					y = abu[k];
					exist = 1;
					break;
				}
			}
			
			if (exist == 1)
			{
				break;
			}
		}
		
		if (exist == 0)
		{
			total_sum += i;
			printf("[%d] total sum = %d\n", i, total_sum);
		}
	}
	
	system("PAUSE");
	return 0;
}
