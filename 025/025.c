#include <stdio.h>
#define MAX 1500
void reset(char *a)
{
	int i = 0;
	while (*(a + i))
	{
		*(a + i) = 0;
		i++;
	}	
}

void kopiraj(char *a, char *b)
{
	int i = 0;
	reset(b);
	while (*(a + i))
	{
		*(b + i) = *(a + i);
		i++;
	}
}

void zbroji(char *a, char *b, char *rez)
{
	int i = 0;
	int tmp;
	int dalje = 0;
	
	while (*(a + i) || *(b + i) || dalje)
	{
		tmp = 0;
		
		if (*(a + i))		tmp += *(a + i) - 48;
		if (*(b + i))		tmp += *(b + i) - 48;
		if (dalje)			tmp += dalje;

		*(rez + i) = tmp % 10 + 48;
		dalje = (int) tmp / 10;
		i++;
	}
}

int string_len(char *a)
{
	int i;
	int res = 0;
	for (i = 0; *(a + i) != 0; i++, res++);
	return res;
}

void ispis(char *a)
{
	int i = 0;
	
	while (*(a + i))
	{
		printf("%c", *(a + i));
		i++;
	}
}

int main(int argc, char *argv[])
{
	int i;
	
	char a[MAX] = {0};
	char b[MAX] = {0};
	char c[MAX] = {0};
	
	int counter = 2;
	
	a[0] = 49;
	b[0] = 49;
	
	while (1)
	{
		zbroji(a, b, c);
		kopiraj(b, a);
		kopiraj(c, b);
		counter++;
		
		/*printf("%d: ", counter);
		ispis(b);
		printf(" [%d]\n", string_len(b));*/
		
		if (string_len(b) == 1000)
		{
			printf("%d\n", counter);
			break;
		}
		
		//if (counter % 100 == 0)
		//	system("pause");
	}
	
	printf("%d\n", counter);

	system("PAUSE");
	return 0;
}
