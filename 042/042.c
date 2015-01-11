#include <stdio.h>
#include <stdlib.h>

void reset(char *a)
{
	int i = 0;
	while(*(a + i))
	{
		*(a + i) = 0;
		i++;
	}
}

int suma(char *a)
{
	int i = 0;
	int sum = 0;
	
	while (*(a + i))
	{
		sum += *(a + i) - 64;
		i++;
	}
	return sum;
}

int main(int argc, char *argv[])
{
	char rijec[100] = {0};
	char input;
	int i;
	int tmp;
	int counter = 0;
	int pocetak, kraj, redni;
	int num[100] = {0};
	
	redni = 0;
	
	for (i = 1; i <= 100; i++)
	    num[i - 1] = 0.5 * i * (i + 1);
	
	
	FILE *fp;
	
	fp = fopen("words.txt", "r");
	
	if (fp == NULL)
	{
		printf("file error!\n");
		system("pause");
		return 0;
	}
	
	pocetak = 0;
	kraj = 0;
	
	while (!feof(fp))
	{

		input = fgetc(fp);
		//printf("%c", input);
		
		if (input >= 65 && input <= 90 && pocetak == 1)
		{
			rijec[redni] = input;
			redni++;
		}
		else if (input == 34)
		{
			if (pocetak == 0)
				pocetak = 1;
			else
			{
				if (kraj == 0)
				{
					tmp = suma(rijec);

					for (i = 0; i < 100; i++)
					    if (tmp == num[i])
					    {
							counter++;
							break;
						}

					pocetak = 0;
					kraj = 0;
					redni = 0;
					reset(rijec);
				}
			}
		}
	}
	
	fclose(fp);
	
	printf("%d\n", counter);

	system("PAUSE");	
	return 0;
}
