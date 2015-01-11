#include <stdio.h>
#include <stdlib.h>

#define SIZE 20

long long paths = 0;

void find(int x, int y)
{
	if (x == 0)
		printf("RED Y: %d\n", y);
		
	if (x == SIZE && y == SIZE)
	{
		paths++;
		
		if (paths % 10000000 == 0)
			printf("%3lld\n", paths);
	}
	else
	{
		if (x < SIZE)
			find(x + 1, y);
		
		if (y < SIZE)
			find(x, y + 1);
	}
}

int main(int argc, char *argv[])
{
	find(0, 0);
	
	printf("Paths found: %lld\n", paths);
	
	system("PAUSE");
	return 0;
}
