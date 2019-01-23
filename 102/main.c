/*

Triangle containment
Problem 102

Three distinct points are plotted at random on a Cartesian plane, for which
-1000 ≤ x, y ≤ 1000, such that a triangle is formed.

Consider the following two triangles:

A(-340,495), B(-153,-910), C(835,-947)

X(-175,41), Y(-421,-714), Z(574,-645)

It can be verified that triangle ABC contains the origin, whereas triangle XYZ
does not.

Using triangles.txt (right click and 'Save Link/Target As...'), a 27K text file
containing the co-ordinates of one thousand "random" triangles, find the number
of triangles for which the interior contains the origin.

NOTE: The first two examples in the file represent the triangles in the example
given above.


Solution:

228

- 0 ms

*/

#include <stdio.h>

void sort(int p1[], int p2[]) {
    int tmp;
    if (p1[0] > p2[0]) {
        tmp = p1[0];
        p1[0] = p2[0];
        p2[0] = tmp;
        tmp = p1[1];
        p1[1] = p2[1];
        p2[1] = tmp;
    }
}

int testLine(int p1[], int p2[]) {
    if (p1[1] < 0 && p2[1] > 0) {
        return 1;
    }
    else if (p1[1] > 0 && p2[1] < 0) {
        return 1;
    }
    return 0;
}

double getA(int p1[], int p2[]) {
    int x1 = p1[0];
    int y1 = p1[1];
    int x2 = p2[0];
    int y2 = p2[1];
    return (float) ((float) y2 - (float) y1) / ((float) x2 - (float) x1);
}

double getB(int p1[], int p2[]) {
    int x1 = p1[0];
    int y1 = p1[1];
    int x2 = p2[0];
    int y2 = p2[1];
    return (float) y1 - (float) ((float) x1 * (float) y2 - (float) x1 * (float) y1) / (float) ((float) x2 - (float) x1);
}

int testTriangle(int t[3][2]) {
    int points[2][2];
    int test[3][2][2];
    int testIndex = 0;
    double a1;
    double b1;
    double a2;
    double b2;
    double x1;
    double x2;
    double tmp;

    if (t[0][1] == 0 || t[1][1] == 0 || t[2][1] == 0) {
        if (t[0][1] == 0) {
            points[0][0] = t[1][0];
            points[0][1] = t[1][1];
            points[1][0] = t[2][0];
            points[1][1] = t[2][1];
            x1 = t[0][0];
        }
        else if (t[1][1] == 0) {
            points[0][0] = t[0][0];
            points[0][1] = t[0][1];
            points[1][0] = t[2][0];
            points[1][1] = t[2][1];
            x1 = t[1][0];
        }
        else {
            points[0][0] = t[0][0];
            points[0][1] = t[0][1];
            points[1][0] = t[1][0];
            points[1][1] = t[1][1];
            x1 = t[2][0];
        }

        a2 = getA(points[0], points[1]);
        b2 = getB(points[0], points[1]);
        x2 = -1 * b2 / a2;

        if (x1 > x2) {
            tmp = x2;
            x2 = x1;
            x1 = tmp;
        }

        if (x1 < 0 && x2 > 0) {
            return 1;
        }
    } else {
        if (testLine(t[0], t[1])) {
            test[testIndex][0][0] = t[0][0];
            test[testIndex][0][1] = t[0][1];
            test[testIndex][1][0] = t[1][0];
            test[testIndex][1][1] = t[1][1];
            testIndex++;
        }
        if (testLine(t[0], t[2])) {
            test[testIndex][0][0] = t[0][0];
            test[testIndex][0][1] = t[0][1];
            test[testIndex][1][0] = t[2][0];
            test[testIndex][1][1] = t[2][1];
            testIndex++;
        }
        if (testLine(t[1], t[2])) {
            test[testIndex][0][0] = t[1][0];
            test[testIndex][0][1] = t[1][1];
            test[testIndex][1][0] = t[2][0];
            test[testIndex][1][1] = t[2][1];
            testIndex++;
        }

        if (testIndex == 2) {
            a1 = getA(test[0][0], test[0][1]);
            b1 = getB(test[0][0], test[0][1]);
            x1 = -1 * b1 / a1;

            a2 = getA(test[1][0], test[1][1]);
            b2 = getB(test[1][0], test[1][1]);
            x2 = -1 * b2 / a2;

            if (x1 > x2) {
                tmp = x2;
                x2 = x1;
                x1 = tmp;
            }

            if (x1 < 0 && x2 > 0) {
                return 1;
            }
        }
    }

    return 0;
}

int main() {
    int i;
    int j;
    int t[3][2];
    int total = 0;
    int lines = 0;
    int l[6];
    int dec;
    FILE *fp;
    char *line = NULL;
    size_t len = 0;
    ssize_t read;

    fp = fopen("p102_triangles.txt", "r");

    if (fp == NULL) {
        printf("Can't open file!\n");
        return 0;
    }

    while ((read = getline(&line, &len, fp)) != -1) {
        for (i = 0; i < 6; i++) {
            l[i] = 0;
        }

        i = 5;
        j = read - 2;
        dec = 1;

        if (j <= 0) {
            break;
        }

        while (i >= 0) {
            if ((line[j] >= 48 && line[j] <= 57) || line[j] == '-') {
                if ((line[j] >= 48 && line[j] <= 57)) {
                    l[i] += dec * (line[j] - 48);
                    dec *= 10;
                } else {
                    l[i] *= -1;
                }
            } else {
                dec = 1;
                i--;
            }
            j--;
        }

        t[0][0] = l[0];
        t[0][1] = l[1];
        t[1][0] = l[2];
        t[1][1] = l[3];
        t[2][0] = l[4];
        t[2][1] = l[5];

        if (testTriangle(t) == 1) {
            total++;
        }

        lines++;
    }

    printf("%d (%d)\n", total, lines);
    fclose(fp);

    return 0;
}