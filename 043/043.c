#include <stdio.h>

#define MAX 9
#define MIN 0

long long sum = 0;

void devet(int a, int b, int c, int d, int e, int f, int g, int h, int i)
{
	int fail;
	int x;
	long long broj;
	for (x = 9; x >= 0; x--)
		if (x != a && x != b && x != c && x != d && x != e && x != f && x != g && x != h && x != i)
		{
			fail = 1;
			
			if ((b * 100 + c * 10 + d) % 2 != 0)				fail = 0;
			if (fail == 1 && (c * 100 + d * 10 + e) % 3 != 0)	fail = 0;
			if (fail == 1 && (d * 100 + e * 10 + f) % 5 != 0)	fail = 0;
			if (fail == 1 && (e * 100 + f * 10 + g) % 7 != 0)	fail = 0;
			if (fail == 1 && (f * 100 + g * 10 + h) % 11 != 0)	fail = 0;
			if (fail == 1 && (g * 100 + h * 10 + i) % 13 != 0)	fail = 0;
			if (fail == 1 && (h * 100 + i * 10 + x) % 17 != 0)	fail = 0;
			
			if (fail == 1)
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
				printf("%lld\n", broj);
				sum += broj;
			}
		}
}

void osam(int a, int b, int c, int d, int e, int f, int g, int h)
{
	int x;
	for (x = 9; x >= 0; x--)
		if (x != a && x != b && x != c && x != d && x != e && x != f && x != g && x != h)
			devet(a, b, c, d, e, f, g, h, x); // 987654321
}

void sedam(int a, int b, int c, int d, int e, int f, int g)
{
	int x;
	for (x = 9; x >= 0; x--)
		if (x != a && x != b && x != c && x != d && x != e && x != f && x != g)
			osam(a, b, c, d, e, f, g, x); // 98765432
}

void sest(int a, int b, int c, int d, int e, int f)
{
	int x;
	for (x = 9; x >= 0; x--)
		if (x != a && x != b && x != c && x != d && x != e && x != f)
			sedam(a, b, c, d, e, f, x); // 9876543
}

void pet(int a, int b, int c, int d, int e)
{
	int x;
	for (x = 9; x >= 0; x--)
		if (x != a && x != b && x != c && x != d && x != e)
			sest(a, b, c, d, e, x); // 987654
}

void cetiri(int a, int b, int c, int d)
{
	int x;
	for (x = 9; x >= 0; x--)
		if (x != a && x != b && x != c && x != d)
			pet(a, b, c, d, x); // 98765
}

void tri(int a, int b, int c)
{
	int x;
	for (x = 9; x >= 0; x--)
		if (x != a && x != b && x != c)
			cetiri(a, b, c, x); // 9876
}

void dva(int a, int b)
{
	int x;
	for (x = 9; x >= 0; x--)
		if (x != a && x != b)
			tri(a, b, x); // 987
}

void jedan(int a)
{
	int x;
	for (x = 9; x >= 0; x--)
		if (x != a)
			dva(a, x); // 98
}

int main(int argc, char *argv[])
{
	int x;
	
	for (x = MAX; x >= MIN; x--)
	{
		jedan(x); // 9
	}
	
	printf("sum: %lld\n", sum);
	
	system("PAUSE");
	return 0;
}
