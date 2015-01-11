#include <stdio.h>

int main(int argc, char *argv[])
{
	int i, j, k, p, pmax, max, res;
	float f;
	
	pmax = 0;
	max = 0;
	res = 0;
	
	for (p = 1; p <= 1000; p++)
	{
		pmax = 0;
		for (i = 1; i < 1000; i++)
		    for (j = 1; j < 1000; j++)
		    {
				f = sqrt(i * i + j * j);
				k = f;
				
				if (k == f)
					if (i + j + k == p)
					{
					    //printf("[%d] %d %d %d\n", p, i, j, k);
					    pmax++;
					    
					    if (pmax > max)
					    {
							res = p;
							max = pmax;
						}
					}
			}
			
		printf("i = %d\n", p);
	}
	
	printf("%d\n", res);

	system("PAUSE");	
	return 0;
}
