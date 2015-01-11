#include <stdio.h>
#define MAX 1001

int main(int argc, char *argv[])
{
	int x, y, n;
	int smjer = 2;
	long sum = 1;
	char polje[MAX][MAX] = {0};
	
	polje[MAX / 2][MAX / 2] = 1;
	polje[MAX / 2][MAX / 2 + 1] = 1;
	
	n = 3;
	
	x = MAX / 2 + 1;
	y = MAX / 2 + 1;

	while (n <= MAX * MAX)
	{
		polje[x][y] = 1;
		
		if (x == y)
			sum += n;
		else if ((MAX - x - 1) == y)
			sum += n;
		
		if (smjer == 1)
		{
			if (polje[x + 1][y] == 0)
			{
				smjer = 2;
				x++;
			}
			else
				y++;
		}
		else if (smjer == 2)
		{
			if (polje[x][y - 1] == 0)
			{
				smjer = 3;
				y--;
			}
			else
				x++;
		}
		else if (smjer == 3)
		{
			if (polje[x - 1][y] == 0)
			{
				smjer = 4;
				x--;
			}
			else
				y--;
		}
		else if (smjer == 4)
		{
			if (polje[x][y + 1] == 0)
			{
				smjer = 1;
				y++;
			}
			else
				x--;
		}
		
		n++;
	}
	
	printf("Suma: %d\n", sum);

	system("PAUSE");
	return 0;
}
