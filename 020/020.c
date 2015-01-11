#include <stdio.h>
#define MAX 100000

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

void mnozi(char *a, char *b, char *rez)
{
	int i, j, k;
	int len_a = str_len(a);
	int len_b = str_len(b);
	int len_dalje;
	int dalje = 0;
	int tmp;
	char tmp_rez[MAX] = {0};
	char rez1[MAX] = {0};
	int znamenka = 0;
	
	for (i = 0; i < len_a; i++)
	{	
		znamenka = 0;
		
		for (k = 0; k < i; k++)
			*(tmp_rez + k) = 48;
		
		for (j = 0; j < len_b; j++)
		{
            tmp = (*(a + i) - 48) * (*(b + j) - 48);
			*(tmp_rez + znamenka + i) = (tmp + dalje) % 10 + 48;
			dalje = (tmp + dalje) / 10;
			
			znamenka++;
		}
		
		len_dalje = num_len(dalje);
		
		while (dalje != 0)
		{
			*(tmp_rez + znamenka + i) = dalje % 10 + 48;
			znamenka++;
			dalje /= 10;
		}
		
		zbroji(tmp_rez, rez, rez1);
		kopiraj(rez1, rez);
		reset(tmp_rez);
		reset(rez1);
	}
}

void okreni(char *a)
{
	int i, len;
	char tmp;
	
	len = str_len(a) - 1;

	for (i = 0; i <= (int) len / 2; i++)
	{
	    tmp = *(a + len - i);
	    *(a + len - i) = *(a + i);
	    *(a + i) = tmp;
	}
}

int str_len(char *a)
{
	int i;
	int res = 0;
	for (i = 0; *(a + i) != 0; i++, res++);
	return res;
}

int num_len(int a)
{
	int i = 0;
	
	while (a > 0)
	{
		a /= 10;
		i++;
	}
	
	return i;
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
	char a[MAX] = {0};
	char b[MAX] = {0};
	char c[MAX] = {0};
	int i = 0;
	int j;
	int k;

	b[0] = 49;
	
	for (i = 1; i <= 100; i++)
	{
		k = 0;
		j = i;
		while (j)
		{
			a[k] = j % 10 + 48;
			j /= 10;
			k++;
		}
	
		mnozi(a, b, c);
		kopiraj(c, b);
		reset(c);
	}
	
	k = 0;
	i = 0;
	while (*(b + i))
	{
		k = k + *(b + i) - 48;
		i++;
	}
	
	printf("sum: %d\n", k);

	system("PAUSE");
	return 0;
}
