/*

Special subset sums: optimum
Problem 103

Let S(A) represent the sum of elements in set A of size n. We shall call it a
special sum set if for any two non-empty disjoint subsets, B and C, the
following properties are true:

    S(B) ≠ S(C); that is, sums of subsets cannot be equal.
    If B contains more elements than C then S(B) > S(C).

If S(A) is minimised for a given n, we shall call it an optimum special sum set.
The first five optimum special sum sets are given below.

n = 1: {1}
n = 2: {1, 2}
n = 3: {2, 3, 4}
n = 4: {3, 5, 6, 7}
n = 5: {6, 9, 11, 12, 13}

It seems that for a given optimum set, A = {a1, a2, ... , an}, the next optimum
set is of the form B = {b, a1+b, a2+b, ... ,an+b}, where b is the "middle"
element on the previous row.

By applying this "rule" we would expect the optimum set for n = 6 to be
A = {11, 17, 20, 22, 23, 24}, with S(A) = 117. However, this is not the optimum
set, as we have merely applied an algorithm to provide a near optimum set. The
optimum set for n = 6 is A = {11, 18, 19, 20, 22, 25}, with S(A) = 115 and
corresponding set string: 111819202225.

Given that A is an optimum special sum set for n = 7, find its set string.

NOTE: This problem is related to Problem 105 and Problem 106.


Solution:

20313839404245

- 1 s

*/

// n = 1: {1}
// n = 2: {1, 2}
// n = 3: {2, 3, 4}
// n = 4: {3, 5, 6, 7}
// n = 5: {6, 9, 11, 12, 13}
// n = 6: {11, 18, 19, 20, 22, 25}
// n = 7: {20, 31, 38, 39, 40, 42, 45}

#include <stdio.h>

#define LOW 19
#define HIGH 51
#define DIGITS 7

int bestSum;
int bestComb[DIGITS];

int testGreaterSums(int arr[], int a, int b) {
    int i, sa = 0, sb = 0;
    for (i = 0; i < a; i++) {
        sa += arr[i];
    }
    for (i = 1; i <= b; i++) {
        sb += arr[DIGITS - i];
    }
    if (sa < sb) {
        return 0;
    }
    return 1;
}

int pickDigit(int arr[], int used[], int takenA, int maxA, int takenB, int maxB) {
    int i, j, startA, startB, digitUsed, sumA = 0, sumB = 0;
    if (takenA < maxA) {
        if (takenA == 0) {
            startA = 0;
        } else {
            startA = used[takenA - 1] + 1;
        }
        for (i = startA; i < DIGITS; i++) {
            used[takenA] = i;
            if (!pickDigit(arr, used, takenA + 1, maxA, takenB, maxB)) {
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
        for (i = startB; i < DIGITS; i++) {
            digitUsed = 0;
            for (j = 0; j < takenA + takenB; j++) {
                if (used[j] == i) {
                    digitUsed = 1;
                    break;
                }
            }
            if (digitUsed == 0) {
                used[takenA + takenB] = i;
                if (!pickDigit(arr, used, takenA, maxA, takenB + 1, maxB)) {
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

int testEqualSums(int arr[], int a, int b) {
    int used[DIGITS];
    return pickDigit(arr, used, 0, a, 0, b);
}

/**
 * kreira kombinaciju s pravim brojevima prema generiranim indexima
 * od: 20 21 22 23 24 25 26
 * do: 44 45 46 47 48 49 50
 * poziva funkciju za sumiranje
 */
int testCombination(int comb[]) {
    int i;
    int arr[DIGITS];
    int sum = 0;

    // upisi znamenke umjesto indeksa
    for (i = 0; i < DIGITS; i++) {
        arr[i] = comb[i] + LOW;
    }

    // provjeriti drugi uvjet (brze eliminira losu kombinaciju)
    // If B contains more elements than C then S(B) > S(C).
    // 2>1 - zbrojiti prva dva clana i ako su manji od zadnjeg
    // 3>2 - zbrojiti prva tri i ako su manji od zbroja zadnja dva
    // 4>3 - zbrojiti cetiri tri i ako su manji od zbroja zadnja tri
    // ako je uvjet ispunjen, kombinacija je ok
    for (i = 2; i <= DIGITS / 2 + 1; i++) {
        if (!testGreaterSums(arr, i, i - 1)) {
            return 0;
        }
    }

    // provjeriti prvi uvjet
    // S(B) ≠ S(C); that is, sums of subsets cannot be equal.
    // 2+1 - moguce (20+21 = 41)
    // 2+2 - moguce (20+24 = 21+23)
    // 2+3 - moguce (20+21+22 = 31+32)
    // 2+4 - moguce (20+21+22+23 = 42+44)
    // 2+5 - nemoguce (20+21+22+23+24 > 49+50)
    // 3+3 - moguce (20+21+28 = 22+23+24)
    // 3+4 - moguce (20+21+22+23 = 27+29+30)
    if (!testEqualSums(arr, 2, 1)) {
        return 0;
    }
    if (!testEqualSums(arr, 2, 2)) {
        return 0;
    }
    if (!testEqualSums(arr, 3, 2)) {
        return 0;
    }
    if (!testEqualSums(arr, 3, 3)) {
        return 0;
    }
    if (!testEqualSums(arr, 4, 2)) {
        return 0;
    }
    if (!testEqualSums(arr, 4, 3)) {
        return 0;
    }

    // sumirati znamenke
    for (i = 0; i < DIGITS; i++) {
        sum += arr[i];
    }

    // ako je suma manja, pronadjeno je nova povoljna kombinacija
    if (sum < bestSum) {
        for (i = 0; i < DIGITS; i++) {
            bestComb[i] = arr[i];
        }
        bestSum = sum;
    }

    return 1;
}

/**
 * generira kombinaciju 7 brojeva
 * od:  0  1  2  3  4  5  6
 * do: 23 24 25 26 27 28 29
 * svaku kombinaciju testira
 */
void comb(int arr[], int n, int k) {
    int i, t;

    for (i = 0; i < k; i++) {
        arr[i] = i;
    }

    while (arr[k - 1] < n) {
        testCombination(arr);

        t = k - 1;
        while (t != 0 && arr[t] == n - k + t) {
            t--;
        }

        arr[t]++;

        for (i = t + 1; i < k; i++) {
            arr[i] = arr[i - 1] + 1;
        }
    }
}

int main() {
    int i;
    int arr[LOW + HIGH];

    for (i = 0; i < DIGITS; i++) {
        bestSum += HIGH - i;
    }

    comb(arr, HIGH - LOW + 1, DIGITS);

    for (i = 0; i < DIGITS; i++) {
        printf("%d", bestComb[i]);
    }

    return 0;
}