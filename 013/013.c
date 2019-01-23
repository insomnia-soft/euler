/*
    projecteuler.net
    
    Large sum
    Problem 13

    Work out the first ten digits of the sum of the following one-hundred 50-digit numbers.
*/

#include <stdio.h>
#define LEN 500

void reset(char *a) {
	int i = 0;
	while (*(a + i)) 	{
		*(a + i) = 0;
		i++;
	}	
}

void rotate(char *a) {
	int i, len;
	char tmp;
	
	len = str_len(a) - 1;

	for (i = 0; i <= (int) len / 2; i++) {
	    tmp = *(a + len - i);
	    *(a + len - i) = *(a + i);
	    *(a + i) = tmp;
	}
}

int str_len(char *a) {
	int i, res = 0;
	for (i = 0; *(a + i); i++, res++);
	return res;
}

void add(char *a, char *b, char *rez) {
	int i = 0;
	int tmp;
	int next = 0;
	int len = 0;
	
	len = strlen(a);
	
	while (*(a + i) || *(b + i) || next) {
		tmp = 0;
		
		if (*(a + i))		tmp += *(a + i) - 48;
		if (*(b + i))		tmp += *(b + i) - 48;
		if (next)			tmp += next;

		*(rez + i) = tmp % 10 + 48;
		next = (int) tmp / 10;
		i++;
	}
}

void copy(char *a, char *b) {
	int i = 0;
	reset(b);
	while (*(a + i)) {
		*(b + i) = *(a + i);
		i++;
	}
}

int main(int argc, char *argv[]) {
	FILE *fp;
	char row[100] = {0};
	int curr_line = 0;
	char num[100] = {0};
	char sum[500] = {0};
	char tmp[500] = {0};
	int i;

	int zbroj = 0;
	
	fp = fopen("numbers.txt", "r");
		
	if (fp != NULL) {
		while (fgets(row, 100, fp) != NULL) {
			reset(num);
			reset(tmp);
			
			for (i = 0; i < 50; i++) {
				num[49 - i] = row[i];
			}
			
			add(num, sum, tmp);
			copy(tmp, sum);
			curr_line++;
		}
	}
	else {
		printf("File missing!\n");
    }
	
	rotate(sum);

	printf("%s\n", sum);
	
	system("PAUSE");	
	return 0;
}
