#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
	int i, j, k;
	
	
	for (i = 1; i <= 1000; i++)
	    for (j = 1; j < 1000; j++)
	    {
			k = sqrt(i * i + j * j);
			
			if (k * k - i * i == j * j)
			    if (i + j + k == 1000)
			        printf("%d + %d + %d = %d\t\t%d * %d * %d = %d\n", i, j, k, i + j + k, i, j, k, i * j *k);
		}
	
	system("PAUSE");
	return 0;
}
