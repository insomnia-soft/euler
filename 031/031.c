#include <stdio.h>

int total = 0;


void sto(int sum)
{
	int i, res;
	
	for (i = 0; i <= 2; i++)
	{
		res = sum + i * 100;
		
		if (res == 200 && i > 0)
			total++;
		else if (res > 200)
			break;
	}
}

void pedeset(int sum)
{
	int i, res;
	
	for (i = 0; i <= 4; i++)
	{
		res = sum + i * 50;
		
		if (res < 200)
			sto(res);
		else if (res == 200 && i > 0)
			total++;
		else if (res > 200)
			break;
	}
}

void dvadeset(int sum)
{
	int i, res;
	
	for (i = 0; i <= 10; i++)
	{
		res = sum + i * 20;
		
		if (res < 200)
			pedeset(res);
		else if (res == 200 && i > 0)
			total++;
		else if (res > 200)
			break;
	}
}

void deset(int sum)
{
	int i, res;
	
	for (i = 0; i <= 20; i++)
	{
		res = sum + i * 10;
		
		if (res < 200)
			dvadeset(res);
		else if (res == 200 && i > 0)
			total++;
		else if (res > 200)
			break;
	}
}

void pet(int sum)
{
	int i, res;
	
	for (i = 0; i <= 40; i++)
	{
		res = sum + i * 5;
		
		if (res < 200)
			deset(res);
		else if (res == 200 && i > 0)
			total++;
		else if (res > 200)
			break;
	}
}

void dva(int sum)
{
	int i, res;
	
	for (i = 0; i <= 100; i++)
	{
		res = sum + i * 2;
		
		if (res < 200)
			pet(res);
		else if (res == 200 && i > 0)
			total++;
		else if (res > 200)
			break;
	}
}

int main(int argc, char *argv[])
{
	int i;
	
	for (i = 0; i <= 200; i++)
	{
		dva(i);
		
		if (i == 200)
			total++;
	}
	
	printf("total: %d\n", total + 1); //+1 je za 2 funte

	system("PAUSE");
	return 0;
}
