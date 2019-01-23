/*

Special subset sums: testing
Problem 105

Let S(A) represent the sum of elements in set A of size n. We shall call it a
special sum set if for any two non-empty disjoint subsets, B and C, the
following properties are true:

    1. S(B) ≠ S(C); that is, sums of subsets cannot be equal.
    2. If B contains more elements than C then S(B) > S(C).

For example, {81, 88, 75, 42, 87, 84, 86, 65} is not a special sum set because
65 + 87 + 88 = 75 + 81 + 84, whereas {157, 150, 164, 119, 79, 159, 161, 139,
158} satisfies both rules for all possible subset pair combinations and
S(A) = 1286.

Using sets.txt (right click and "Save Link/Target As..."), a 4K text file with
one-hundred sets containing seven to twelve elements (the two examples given
above are the first two sets in the file), identify all the special sum sets,
A1, A2, ..., Ak, and find the value of S(A1) + S(A2) + ... + S(Ak).

NOTE: This problem is related to Problem 103 and Problem 106.


Solution:

73702

- 200 ms

*/

#include <stdio.h>

#define COUNT 100
#define DIGITS 12

int numbers[COUNT][DIGITS] = {0};
int numbersLen[COUNT] = {0};

int pickDigit(int arr[], int used[], int takenA, int maxA, int takenB, int maxB, int len) {
    int i, j, startA, startB, digitUsed, sumA = 0, sumB = 0;
    if (takenA < maxA) {
        if (takenA == 0) {
            startA = 0;
        } else {
            startA = used[takenA - 1] + 1;
        }
        for (i = startA; i < len; i++) {
            used[takenA] = i;
            if (!pickDigit(arr, used, takenA + 1, maxA, takenB, maxB, len)) {
                return 0;
            }
        }
    }
    else if (takenB < maxB) {
        if (takenB == 0) {
            startB = 0;
        } else {
            startB = used[takenA + takenB - 1] + 1;
        }
        for (i = startB; i < len; i++) {
            digitUsed = 0;
            for (j = 0; j < takenA + takenB; j++) {
                if (used[j] == i) {
                    digitUsed = 1;
                    break;
                }
            }
            if (digitUsed == 0) {
                used[takenA + takenB] = i;
                if (!pickDigit(arr, used, takenA, maxA, takenB + 1, maxB, len)) {
                    return 0;
                }
            }
        }
    }
    else {
        for (i = 0; i < takenA; i++) {
            sumA += arr[used[i]];
        }
        for (i = takenA; i < takenA + takenB; i++) {
            sumB += arr[used[i]];
        }
        if (sumA == sumB) {
            return 0;
        }
    }
    return 1;
}

int testEqualSums(int arr[], int a, int b, int len) {
    int used[DIGITS];
    return pickDigit(arr, used, 0, a, 0, b, len);
}

int testGreaterSums(int arr[], int a, int b, int len) {
    int i, sa = 0, sb = 0;
    for (i = 0; i < a; i++) {
        sa += arr[i];
    }
    for (i = 1; i <= b; i++) {
        sb += arr[len - i];
    }
    if (sa < sb) {
        return 0;
    }
    return 1;
}

int isSpecialSet(int arr[], int len) {
    int i;
    int sum = 0;
    int a, b;

    // If B contains more elements than C then S(B) > S(C).
    for (i = 2; i <= len / 2 + 1; i++) {
        if (!testGreaterSums(arr, i, i - 1, len)) {
            return 0;
        }
    }

    // S(B) ≠ S(C); that is, sums of subsets cannot be equal.
    for (i = 3; i <= DIGITS; i++) {
        b = i / 2;
        a = i - b;
        if (!testEqualSums(arr, a, b, len)) {
            return 0;
        }
        if (i % 2 == 0) {
            a++;
            b--;
            if (!testEqualSums(arr, a, b, len)) {
                return 0;
            }
        }
    }

    // sum digits
    for (i = 0; i < len; i++) {
        sum += arr[i];
    }

    return sum;
}

int loadNumbers() {
    int n;
    int row;
    int col;
    char c;
    FILE *fp;
    fp = fopen("p105_sets.txt", "r");

    if (!fp) {
        printf("Can't open file p105_sets.txt!");
        return 0;
    }

    n = 0;
    row = 0;
    col = 0;
    while ((c = fgetc(fp)) != EOF) {
        if (c >= 48 && c <= 57) {
            numbers[row][col] = numbers[row][col] * 10 + c - 48;
        } else if (c == ',') {
            col++;
        } else if (c == '\n') {
            numbersLen[row] = col + 1;
            col = 0;
            row++;
        }
    }
    numbersLen[row] = col + 1;
    fclose(fp);

    return 1;
}

void sortArray(int n[], int len) {
    int i, j, tmp;
    for (i = 0; i < len - 1; i++) {
        for (j = 0; j < len - i - 1; j++) {
            if (n[j] > n[j + 1]) {
                tmp = n[j + 1];
                n[j + 1] = n[j];
                n[j] = tmp;
            }
        }
    }
}

int main() {
    int i, sum = 0;

    if (!loadNumbers()) {
        return 0;
    }

    for (i = 0; i < 100; i++) {
        sortArray(numbers[i], numbersLen[i]);
        sum += isSpecialSet(numbers[i], numbersLen[i]);
    }

    printf("%d\n", sum);

    return 0;
}