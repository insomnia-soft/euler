/*

Anagramic squares
Problem 98

By replacing each of the letters in the word CARE with 1, 2, 9, and 6
respectively, we form a square number: 1296 = 362. What is remarkable is that,
by using the same digital substitutions, the anagram, RACE, also forms a square
number: 9216 = 962. We shall call CARE (and RACE) a square anagram word pair and
specify further that leading zeroes are not permitted, neither may a different
letter have the same digital value as another letter.

Using words.txt (right click and 'Save Link/Target As...'), a 16K text file
containing nearly two-thousand common English words, find all the square anagram
word pairs (a palindromic word is NOT considered to be an anagram of itself).

What is the largest square number formed by any member of such a pair?

NOTE: All anagrams formed must be contained in the given text file.


Solution:

18769

- 40 ms

*/


#include <stdio.h>
#include <math.h>
#include <limits.h>

#define WORDS 2000
#define COLS 100

char word[WORDS][COLS] = {0};
int wordCount = 0;
char wordLength[WORDS] = {0};

int anagram[50][2];
int anagramCount = 0;

long max = 0;

int len(char a[]) {
    int i = 0;
    for (i = 0; a[i] != 0; i++);
    return i;
}

void rotate(char a[]) {
    char tmp;
    int i, strLen;
    strLen = len(a);
    for (i = 0; i < strLen / 2; i++) {
        tmp = a[i];
        a[i] = a[strLen - i - 1];
        a[strLen - i - 1] = tmp;
    }
}

void intToStr(long a, char s[]) {
    long i = 0;
    while (a > 0) {
        s[i] = a % 10 + 48;
        a /= 10;
        i++;
    }
    s[i] = 0;
}

int readFile() {
    int s = 1;
    int c = 0;
    int i;

    char tmp[COLS] = {0};
    int tmpLen = 0;

    FILE *fp;

    fp = fopen("p098_words.txt", "r");

    if (!fp) {
        printf("Can't open p098_words.txt!\n");
        return 0;
    }

    while (1) {
        c = fgetc(fp);
        if (feof(fp)) {
            break;
        }
        if (s == 1) {
            if (c == '"') {
                s = 0;
                tmpLen = 0;
            }
        }
        else if (s == 0) {
            if (c == '"') {
                s = 1;
                for (i = 0; i < tmpLen; i++) {
                    word[wordCount][i] = tmp[i];
                }
                wordLength[wordCount] = tmpLen;
                wordCount++;
                continue;
            }
            tmp[tmpLen++] = c;
        }
    }
}

int isAnagram(char a[], char b[]) {
    int i;
    int abc1[26] = {0};
    int abc2[26] = {0};

    for (i = 0; a[i] != 0; i++) {
        abc1[a[i] - 65]++;
        abc2[b[i] - 65]++;
    }

    for (i = 0; i < 26; i++) {
        if (abc1[i] != abc2[i]) {
            return 0;
        }
    }

    return 1;
}

void findAnagrams() {
    for (int i = 0; i < wordCount - 1; i++) {
        for (int j = i + 1; j < wordCount; j++) {
            if (wordLength[i] == wordLength[j] && isAnagram(word[i], word[j])) {
                anagram[anagramCount][0] = i;
                anagram[anagramCount][1] = j;
                anagramCount++;
            }
        }
    }
}

int getLetterValues(char a[], int wl, int n, char alpha[10][2]) {
    int i, j;

    char number[100] = {0};

    intToStr(n, number);

    rotate(number);

    for (i = 0; i < wl; i++) {
        for (j = 0; j < i; j++) {
            if (alpha[j][1] == number[i]) {
                return 0;
            }
            if (alpha[j][0] == a[i] && number[i] != alpha[j][1]) {
                return 0;
            }
        }

        alpha[i][0] = a[i];
        alpha[i][1] = number[i];
    }

    return 1;
}

void testNumber(char b[], char wl, char alpha[10][2], long sq) {
    int i, j;
    long n = 0;
    float nSqrt;
    for (i = 0; i < wl; i++) {
        for (j = 0; alpha[j][0] != 0; j++) {
            if (alpha[j][0] == b[i]) {
                if (i == 0 && alpha[j][1] == 48) {
                    return;
                }
                n *= 10;
                n += alpha[j][1] - 48;
            }
        }
    }

    nSqrt = sqrt(n);
    if (nSqrt - (int) nSqrt == 0) {
        if (sq > max) {
            max = sq;
        }

        if (n > max) {
            max = n;
        }
    }
}

void testAnagram(int n) {
    long i, j, lower, upper;
    long sq;
    // max letters = 10
    // alphabet[10][0] = 65-97
    // alphabet[10][1] = 0-9
    char alpha[10][2] = {0};

//    printf("%s %s [%d]\n", word[anagram[n][0]], word[anagram[n][1]], wordLength[anagram[n][0]]);

    switch (wordLength[anagram[n][0]]) {
        case 1:
            lower = 1;
            upper = 3;
            break;
        case 2:
            lower = 4;
            upper = 9;
            break;
        case 3:
            lower = 10;
            upper = 31;
            break;
        case 4:
            lower = 32;
            upper = 99;
            break;
        case 5:
            lower = 100;
            upper = 316;
            break;
        case 6:
            lower = 317;
            upper = 999;
            break;
        case 7:
            lower = 1000;
            upper = 3162;
            break;
        case 8:
            lower = 3163;
            upper = 9999;
            break;
        case 9:
            lower = 10000;
            upper = 31622;
            break;
        case 10:
            lower = 31623;
            upper = 99999;
            break;
        case 11:
            lower = 100000;
            upper = 316227;
            break;
        case 12:
            lower = 316228;
            upper = 999999;
            break;
        case 13:
            lower = 1000000;
            upper = 3162277;
            break;
        case 14:
            lower = 3162278;
            upper = 9999999;
            break;
    }

    for (i = lower; i <= upper; i++) {
        for (j = 0; j < 10; j++) {
            alpha[j][0] = 0;
            alpha[j][1] = 0;
        }

        sq = i * i;

        if (getLetterValues(word[anagram[n][0]], wordLength[anagram[n][0]], sq, alpha)) {
            testNumber(word[anagram[n][1]], wordLength[anagram[n][0]], alpha, sq);
        }
    }
}

int main() {
    int i;
    if(!readFile()) {
        return 0;
    }

    findAnagrams();

    for (i = 0; i < anagramCount; i++) {
        testAnagram(i);
    }

    printf("%ld\n", max);

    return 0;
}
