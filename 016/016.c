#include <stdio.h>
#include <stdlib.h>

#define MAX 1000

char broj[MAX] = {0};

void mnozi(char *a)
{
	int n = 0;
	int i = 0;
	int dalje = 0;
	
	while (*(a + i) != 0)
	{
		n = *(a + i) - 48;
		n = n * 2 + dalje;

		if (n >= 10)
		{
		    *(a + i) = n + 38;
		    dalje = 1;
		}
		else
		{
		    *(a + i) = n + 48;
		    dalje = 0;
		}

		i++;
	}
	
	if (dalje)
	    *(a + i) = 49;
}

void ispis(char *a)
{
	int i = 0;
	int len = 0;
	
	for (len = 0; *(a + len) != 0; len++);

	for (i = len; i >= 0; i--)
		printf("%c", *(a + i));

	printf("\n");
}

void zbroji_decimale(char *a)
{
	int zbroj = 0;
	int i;
	
	for (i = 0; *(a + i) != 0; zbroj += (*(a + i) - 48), i++);
	
	printf("Ukupan zbroj znamenki je: %d\n", zbroj);
}



int main(int argc, char *argv[])
{
	int i = 1;
	
	broj[0] = 49;
	
	while (i <= 1000)
	{
		mnozi(broj);
		printf("2 ^ %d = ", i);
		ispis(broj);
		i++;
	}

	zbroji_decimale(broj);

	system("PAUSE");
	return 0;
}
