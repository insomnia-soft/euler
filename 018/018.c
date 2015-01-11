#include <stdio.h>
#include <time.h>
#include <windows.h>

#define MAX 70

int a[MAX + 1][MAX + 1] = {0};
int max_sum = 0;
int loops;
int b;

void rect(int x, int y, int sum)
{
	int i;
	
	if (x < loops)
	{
		sum += a[x][y];
		rect(x + 1, y, sum);
		rect(x + 1, y + 1, sum);
	}
	else
	{
	    sum += a[x][y];
	    if (sum > max_sum)
	    	max_sum = sum;
	}
}

int main(int argc, char *argv[])
{
	int i, j;
	int k = 0;
	int tick_s, tick_e;
	
	int in[] = {75, 95, 64, 17, 47, 82, 18, 35, 87, 10, 20, 4, 82, 47, 65, 19, 1, 23, 75, 3, 34, 88, 2, 77, 73, 7, 63, 67, 99, 65, 4, 28, 6, 16, 70, 92, 41, 41, 26, 56, 83, 40, 80, 70, 33, 41, 48, 72, 33, 47, 32, 37, 16, 94, 29, 53, 71, 44, 65, 25, 43, 91, 52, 97, 51, 14, 70, 11, 33, 28, 77, 73, 17, 78, 39, 68, 17, 57, 91, 71, 52, 38, 17, 14, 91, 43, 58, 50, 27, 29, 48, 63, 66, 4, 68, 89, 53, 67, 30, 73, 16, 69, 87, 40, 31, 4, 62, 98, 27, 23, 9, 70, 98, 73, 93, 38, 53, 60, 4, 23};
	
	for (i = 1; i <= MAX; i++)
		for (j = 1; j <= i; j++)
			a[i][j] = in[k++];

	printf("http://projecteuler.net/index.php?section=problems&id=18\n");
	printf("Solving it with brute force method...\n\n");
	
	loops = 15;
	tick_s = GetTickCount();
	rect(1, 1, 0);
	tick_e = GetTickCount();
	
	printf("Done! Max sum = %d (lasted %d ms)\n\n", max_sum, tick_e - tick_s);
	
	printf("http://projecteuler.net/index.php?section=problems&id=67 unsolvable with this method :)\n\n");
	
	for (i = 1; i <= MAX; i++)
		for (j = 1; j <= MAX; j++)
			a[i][j] = rand() % 100;
	
	for (loops = 2; loops < MAX; loops++)
	{
		max_sum = 0;
		
		printf("Benchmarking for %2d rows... ", loops);
		
		tick_s = GetTickCount();
		rect(1, 1, 0);
		tick_e = GetTickCount();
	
		printf("Done! wasted %8d ms\n", tick_e - tick_s);
	}

	system("PAUSE");	
	return 0;
}
