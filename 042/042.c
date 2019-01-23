/*
    projecteuler.net

    Coded triangle numbers
    Problem 42

    The nth term of the sequence of triangle numbers is given by, tn = (1/2)n(n+1); so the first ten triangle numbers are:

    1, 3, 6, 10, 15, 21, 28, 36, 45, 55, ...

    By converting each letter in a word to a number corresponding to its alphabetical position and adding these values we form a word value. For example, the word value for SKY is 19 + 11 + 25 = 55 = t10. If the word value is a triangle number then we shall call the word a triangle word.

    Using words.txt (right click and 'Save Link/Target As...'), a 16K text file containing nearly two-thousand common English words, how many are triangle words?
*/

#include <stdio.h>
#include <stdlib.h>

void reset(char *a) {
    int i = 0;
    while(*(a + i)) {
        *(a + i) = 0;
        i++;
    }
}

int sum(char *a) {
    int i = 0;
    int s = 0;

    while (*(a + i)) {
        s += *(a + i) - 64;
        i++;
    }
    return s;
}

int main(int argc, char *argv[]) {
    char word[100] = {0};
    char input;
    int i;
    int tmp;
    int counter = 0;
    int start, end, index;
    int num[100] = {0};

    index = 0;

    for (i = 1; i <= 100; i++) {
        num[i - 1] = 0.5 * i * (i + 1);
    }

    FILE *fp;

    fp = fopen("words.txt", "r");

    if (fp == NULL) {
        printf("file error!\n");
        system("pause");
        return 0;
    }

    start = 0;
    end = 0;

    while (!feof(fp)) {
        input = fgetc(fp);

        if (input >= 65 && input <= 90 && start == 1) {
            word[index] = input;
            index++;
        }
        else if (input == 34) {
            if (start == 0)
                start = 1;
            else {
                if (end == 0) {
                    tmp = sum(word);

                    for (i = 0; i < 100; i++)
                    if (tmp == num[i]) {
                        counter++;
                        break;
                    }

                    start = 0;
                    end = 0;
                    index = 0;
                    reset(word);
                }
            }
        }
    }

    fclose(fp);

    printf("%d\n", counter);

    system("PAUSE");
    return 0;
}
