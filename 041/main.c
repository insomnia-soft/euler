#include <stdio.h>
#define MAX 7
#define MIN 1

void sest(int a, int b, int c, int d, int e, int f)
{
	int fail;
	int i;
	long long broj;
	long long cx;
	for (i = MAX; i >= MIN; i--)
		if (i != a && i != b && i != c && i != d && i != e && i != f)
		{
			broj = a * 10 + b;
			broj = broj * 10 + c;
			broj = broj * 10 + d;
			broj = broj * 10 + e;
			broj = broj * 10 + f;
			broj = broj * 10 + i;

			fail = 1;
			for (cx = 2; cx < broj / 2; cx++)
			{
				if (broj % cx == 0)
				{
					fail = 0;
					break;
				}
			}
			if (fail == 1)
			{
				printf("solution: %d\n", broj);
				system("pause");
			}
		}
}

void pet(int a, int b, int c, int d, int e)
{
	int i;
	for (i = MAX; i >= MIN; i--)
		if (i != a && i != b && i != c && i != d && i != e)
			sest(a, b, c, d, e, i);
}

void cetiri(int a, int b, int c, int d)
{
	int i;
	for (i = MAX; i >= MIN; i--)
		if (i != a && i != b && i != c && i != d)
			pet(a, b, c, d, i);
}

void tri(int a, int b, int c)
{
	int i;
	for (i = MAX; i >= MIN; i--)
		if (i != a && i != b && i != c)
			cetiri(a, b, c, i);
}

void dva(int a, int b)
{
	int i;
	for (i = MAX; i >= MIN; i--)
		if (i != a && i != b)
			tri(a, b, i);
}

void jedan(int a)
{
	int i;
	for (i = MAX; i >= MIN; i--)
		if (i != a)
			dva(a, i);
}

int main(int argc, char *argv[])
{
	int i;
	
	for (i = MAX; i >= MIN; i--)
	{
		jedan(i);
	}
	
	
	system("PAUSE");
	return 0;
}


/*

#include <stdio.h>

void devet(int a, int b, int c, int d, int e, int f, int g, int h, int i)
{
	int fail;
	int x;
	long long broj;
	long long cx;
	for (x = 9; x >= 0; x--)
		if (x != a && x != b && x != c && x != d && x != e && x != f && x != g && x != h && x != i)
		{
			broj = a * 10 + b;
			broj = broj * 10 + c;
			broj = broj * 10 + d;
			broj = broj * 10 + e;
			broj = broj * 10 + f;
			broj = broj * 10 + g;
			broj = broj * 10 + h;
			broj = broj * 10 + i;
			broj = broj * 10 + x;
			
			fail = 1;
			for (cx = 2; cx < broj / 2; cx++)
			{
				printf("%lld mod %d\n", broj, cx);
				if (broj % cx == 0)
				{
					fail = 0;
					break;
				}
			}
			if (fail == 1)
			{
				printf("%lld\n", broj);
				system("pause");
			}
			system("pause");
		}
}

void osam(int a, int b, int c, int d, int e, int f, int g, int h)
{
	int i;
	for (i = 9; i >= 0; i--)
		if (i != a && i != b && i != c && i != d && i != e && i != f && i != g && i != h)
			devet(a, b, c, d, e, f, g, h, i);
}

void sedam(int a, int b, int c, int d, int e, int f, int g)
{
	int i;
	for (i = 9; i >= 0; i--)
		if (i != a && i != b && i != c && i != d && i != e && i != f && i != g)
			osam(a, b, c, d, e, f, g, i);
}

void sest(int a, int b, int c, int d, int e, int f)
{
	int i;
	for (i = 9; i >= 0; i--)
		if (i != a && i != b && i != c && i != d && i != e && i != f)
			sedam(a, b, c, d, e, f, i);
}

void pet(int a, int b, int c, int d, int e)
{
	int i;
	for (i = 9; i >= 0; i--)
		if (i != a && i != b && i != c && i != d && i != e)
			sest(a, b, c, d, e, i);
}

void cetiri(int a, int b, int c, int d)
{
	int i;
	for (i = 9; i >= 0; i--)
		if (i != a && i != b && i != c && i != d)
			pet(a, b, c, d, i);
}

void tri(int a, int b, int c)
{
	int i;
	for (i = 9; i >= 0; i--)
		if (i != a && i != b && i != c)
			cetiri(a, b, c, i);
}

void dva(int a, int b)
{
	int i;
	for (i = 9; i >= 0; i--)
		if (i != a && i != b)
			tri(a, b, i);
}

void jedan(int a)
{
	int i;
	for (i = 9; i >= 0; i--)
		if (i != a)
			dva(a, i);
}

int main(int argc, char *argv[])
{
	int i;
	
	for (i = 9; i >= 0; i--)
	{
		jedan(i);
	}
	
	
	system("PAUSE");
	return 0;
}


*/
