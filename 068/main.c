/*

Magic 5-gon ring
Problem 68

Consider the following "magic" 3-gon ring, filled with the numbers 1 to 6, and
each line adding to nine.

Working clockwise, and starting from the group of three with the numerically
lowest external node (4,3,2 in this example), each solution can be described
uniquely. For example, the above solution can be described by the set: 4,3,2;
6,2,1; 5,1,3.

It is possible to complete the ring with four different totals: 9, 10, 11, and
12. There are eight solutions in total.

Total	Solution Set
9       4,2,3; 5,3,1; 6,1,2
9       4,3,2; 6,2,1; 5,1,3
10      2,3,5; 4,5,1; 6,1,3
10      2,5,3; 6,3,1; 4,1,5
11      1,4,6; 3,6,2; 5,2,4
11      1,6,4; 5,4,2; 3,2,6
12      1,5,6; 2,6,4; 3,4,5
12      1,6,5; 3,5,4; 2,4,6

By concatenating each group it is possible to form 9-digit strings; the maximum
string for a 3-gon ring is 432621513.

Using the numbers 1 to 10, and depending on arrangements, it is possible to form
16- and 17-digit strings. What is the maximum 16-digit string for a "magic"
5-gon ring?


Solution:

6531031914842725

*/


#include <stdio.h>
#include <limits.h>

#define MAX 10
#define STR_LENGTH 20
#define TARGET_DIGITS 16

char list[100][STR_LENGTH] = {0};
int listCount = 0;

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

void printList() {
    int i, j;
    for (i = 0; i < listCount; i++) {
        for (j = 0; list[i][j] != 0; j++) {
            printf("%c", list[i][j]);
        }
        printf("\n");
    }
}

void printSolution(int n) {
    int i;
    rotate(list[n]);
    printf("Solution: ");
    for (i = 0; list[n][i] != 0; i++) {
        printf("%c", list[n][i]);
    }
}

void printGroups(char a[], int group[MAX / 2][3], int groupCount, int targetSum) {
    int i;
    int min = INT_MAX;
    int min_i;

    for (i = 0; i < MAX; i++) {
        printf("%d ", (int) a[i]);
    }

    for (i = 0; i < groupCount; i++) {
        if (group[i][2] < min) {
            min = group[i][2];
            min_i = i;
        }
    }

    printf(" [sum: %3d] ", targetSum);

    for (i = min_i; i < groupCount; i++) {
//        printf("%d, %d, %d; ", group[i][2], group[i][1], group[i][0]);
        printf("%d%d%d", group[i][2], group[i][1], group[i][0]);
    }
    for (i = 0; i < min_i; i++) {
//        printf("%d, %d, %d; ", group[i][2], group[i][1], group[i][0]);
        printf("%d%d%d", group[i][2], group[i][1], group[i][0]);
    }

    printf("\n");
}

// compare strings as numbers
// a > b returns 1
// a == b returns 0
// a < b returns -1
int strCompare(int a, int b) {
    int i;
    int lenA = len(list[a]);
    int lenB = len(list[b]);

    if (lenA > lenB) {
        return 1;
    }
    else if (lenA < lenB) {
        return -1;
    }

    for (i = lenA - 1; i >= 0; i--) {
        if (list[a][i] > list[b][i]) {
            return 1;
        }
        else if (list[a][i] < list[b][i]) {
            return -1;
        }
    }

    return 0;
}

void swapStrings(int a, int b) {
    int i;
    char tmp;
    for (i = 0; i < STR_LENGTH; i++) {
        tmp = list[a][i];
        list[a][i] = list[b][i];
        list[b][i] = tmp;
    }
}

void bubbleSort() {
    int i;
    int n = listCount;
    int swapped;
    do {
        swapped = 0;
        for (i = 1; i < n; i++) {
            if (strCompare(i - 1, i) == 1) {
                swapStrings(i - 1, i);
                swapped = 1;
            }
        }
        n--;
    } while (swapped == 1);
}

int findTarget() {
    int i, target = -1;
    for (i = 0; i < listCount; i++) {
        if (len(list[i]) == TARGET_DIGITS) {
            target = i;
        }
    }
    return target;
}

void addToList(int group[MAX / 2][3]) {
    int i, j;
    int start;
    int listIndex = 0;
    int min = INT_MAX;

    for (i = 0; i < MAX / 2; i++) {
        if (group[i][2] < min) {
            start = i;
            min = group[i][2];
        }
    }

    // for each group
    for (i = start; i < MAX / 2; i++) {
        // each number
        for (j = 2; j >= 0; j--) {
            if (group[i][j] == 10) {
                list[listCount][listIndex] = 49;
                listIndex++;
                list[listCount][listIndex] = 48;
                listIndex++;
            } else {
                list[listCount][listIndex] = group[i][j] + 48;
                listIndex++;
            }
        }
    }

    for (i = 0; i < start; i++) {
        for (j = 2; j >= 0; j--) {
            if (group[i][j] == 10) {
                list[listCount][listIndex] = 49;
                listIndex++;
                list[listCount][listIndex] = 48;
                listIndex++;
            } else {
                list[listCount][listIndex] = group[i][j] + 48;
                listIndex++;
            }
        }
    }

    rotate(list[listCount]);
    listCount++;
}

void testPermutation(char a[]) {
    int i, j;
    int targetSum;
    int sum;
    int group[MAX / 2][3] = {0};

    int x, y, z;

    // test first group
    targetSum = a[0] + a[1] + a[2];

    group[0][0] = a[0];
    group[0][1] = a[1];
    group[0][2] = a[2];

    // test 2nd, 3rd ... MAX - 1
    for (i = 1; i < MAX / 2 - 1; i++) {
        x = a[2 * i + 1];
        if (i == 1) {
            y = a[0];
        } else {
            y = a[2 * i - 1];
        }
        z = a[2 * i + 2];

        sum = x + y + z;

        group[i][0] = x;
        group[i][1] = y;
        group[i][2] = z;

        if (sum != targetSum) {
            return;
        }
    }

    // test last (MAX)
    x = a[1];
    y = a[MAX - 3];
    z = a[MAX - 1];

    sum = x + y + z;

    group[i][0] = x;
    group[i][1] = y;
    group[i][2] = z;

    if (sum != targetSum) {
        return;
    }

//    printGroups(a, group, MAX / 2, targetSum);

    addToList(group);
}

void swap(char *x, char *y) {
    char temp;
    temp = *x;
    *x = *y;
    *y = temp;
}

void permutePos(char a[]) {
    testPermutation(a);
    swap(a, a + 2);
    testPermutation(a);
    swap(a, a + 2);
}

/* Function to print permutations of string
   This function takes three parameters:
   1. String
   2. Starting index of the string
   3. Ending index of the string. */
void permute(char *a, int l, int r) {
    int i;
    if (l == r) {
        permutePos(a);
    } else {
        for (i = l; i <= r; i++) {
            swap((a + l), (a + i));
            permute(a, l + 1, r);
            swap((a + l), (a + i)); //backtrack
        }
    }
}

int main() {
    int i;
    char permStr[MAX + 1] = {0};

    for (i = 0; i < MAX; i++) {
        permStr[i] = i + 1;
    }

    permute(permStr, 1, MAX - 1);
    bubbleSort();

    //printList();
    printSolution(findTarget());

    return 0;
}