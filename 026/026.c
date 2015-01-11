#include <stdio.h>
#define MAX 50000

void reset(char *a)
{
	int i = 0;
	
	while (*(a + i) != 0)
	{
		*(a + i) = 0;
		i++;
	}
}

void reset_int(int *a)
{
	int i = 0;
	
	while (*(a + i) != 0)
	{
		*(a + i) = 0;
		i++;
	}
}

int field_len(int *a)
{
	int i = 0;
	
	while (*(a + i))
		i++;
		
	return i;
}

int find_match(int *a, int *x, int *y)
{
	int i, j, len;
	
	len = field_len(a);
	
	for (i = 0; i < len; i++)
	{
		for (j = i + 1; j < len; j++)
		{
			if (*(a + i) == *(a + j))
			{
				*x = i;
				*y = j;
				return 1;
			}
		}
	}
	
	return 0;
}

int main(int argc, char *argv[])
{
	int i, j, n, a, b, max, max_i;
	
	int ost[MAX] = {0};
	char res[MAX] = {0};
	int counter;
	
	max = 0;
	
	for (i = 1; i <= 1000; i++)
	{
		n = 1;
		counter = 0;
		
		do
		{
			if ((float) n / i > 0)
				n *= 10;
			
			res[counter] = n / i + 48;
			n %= i;
			ost[counter] = n;
			counter++;
			
			if (n > 0 && find_match(ost, &a, &b) == 1)
			{
				if ((b - a) > max)
				{
					max = b - a;
					max_i = i;
				}

				break;
			}
			
			if (counter >= MAX)
				break;
			
		} while (n != 0);
		
		reset(res);
		reset_int(ost);
	}
	
	printf("%d: %d\n", max_i, max);
	
	system("PAUSE");
	return 0;
}
