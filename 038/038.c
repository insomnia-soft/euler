#include <stdio.h>
#define MAX_NUM 100
#define MAX 150

void reset(int *a, int max)
{
	int i = 0;
	while (i < max)
		*(a + i++) = 0;
}

int main(int argc, char *argv[])
{
	int i, j, n, pos, res, tmp_pos, x, win;
	int polje[MAX] = {1};
	int num[MAX_NUM] = {0};

	for (i = 2; i < 10000; i++)
	{
		n = 1;
		pos = 0;
		win = 1;
		reset(polje, MAX);
		reset(num, MAX_NUM);
		
		do
		{
			res = i * n;
			tmp_pos = pos;
			while (res > 0)
			{
				x = res % 10 + 48;

				if (num[x - 48] == 1)
				{
					win = 0;
					break;
				}

				if (res >= 10000)
				    polje[tmp_pos + 4] = x;
				else if (res >= 1000 && res < 10000)
					polje[tmp_pos + 3] = x;
				else if (res >= 100 && res < 1000)
					polje[tmp_pos + 2] = x;
				else if (res >= 10 && res < 100)
					polje[tmp_pos + 1] = x;
				else
					polje[tmp_pos] = x;

				num[x - 48] = 1;
				res /= 10;
				pos++;
			}

			if (win == 0)
				break;

			n++;

		} while (pos < 9);

		if (win == 1 && pos == 9)
		{
			for (j = 1; j <= 9; j++)
				if (num[j] == 0)
					win = 0;

			if (win == 1)
			{
				printf("%d: ", i);
				for (j = 0; j <= 8; j++)
					printf("%d", polje[j] - 48);
				printf("\n");
			}
		}
	}

	system("PAUSE");
	return 0;
}
