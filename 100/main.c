/*

Arranged probability
Problem 100

If a box contains twenty-one coloured discs, composed of fifteen blue discs and
six red discs, and two discs were taken at random, it can be seen that the
probability of taking two blue discs, P(BB) = (15/21)×(14/20) = 1/2.

The next such arrangement, for which there is exactly 50% chance of taking two
blue discs at random, is a box containing eighty-five blue discs and thirty-five
red discs.

By finding the first arrangement to contain over 10^12 = 1,000,000,000,000 discs
in total, determine the number of blue discs that the box would contain.


Solution:

756872327473

- 10 ms


How this works?
First I wrote a simple brute force solution that would be stuck in a long loop
and it doesn't work correctly with higher numbers:

#include <stdio.h>

int check(double blue, double total) {
    double a = blue * (blue - 1);
    double b = total * (total - 1);
    double r = a / b;
    if (r < 0.5) {
        return -1;
    }
    else if (r > 0.5) {
        return 1;
    }
    else {
        return 0;
    }
}

int main() {
    double blue = 15;
    double total = 20;
    int ret;
    while (1) {
        ret = check(blue, total);
        if (ret == -1) {
            blue++;
            total++;
        }
        else if (ret == 1) {
            total++;
        }
        else {
            printf("%.0f + %.0f = %0.f\n", blue, total - blue, total);
            total++;
        }
    }
    return 0;
}


But it did give me some correct result:
15 + 6 = 21
85 + 35 = 120
493 + 204 = 697
2871 + 1189 = 4060
16731 + 6930 = 23661
97513 + 40391 = 137904
568345 + 235416 = 803761
3312555 + 1372105 = 4684660
19306983 + 7997214 = 27304197
112529341 + 46611179 = 159140520

I noticed blue/total discs ratio is near 0.7 and it gets more precision with
higher number of discs:
15 / 21 = 				0,714285714
85 / 120 = 				0,708333333
493 / 697 = 			0,707317073
2871 / 4060 = 			0,707142857
16731 / 23661 = 		0,707112971
97513 / 137904 = 		0,707107843
568345 / 803761 =   	0,707106963
3312555 / 4684660 =     0,707106812
19306983 / 27304197 =   0,707106787
112529341 / 159140520 = 0,707106782

I also noticed next correct total number of discs (for 0.5 chance) is near 5.82
and it gets more precision with higher number of discs:
120 / 21 = 				5,714285714 (1st digit correct: 5)
697 / 120 = 			5,808333333 (1st digit correct: 5)
4060 / 697 = 			5,824964132 (1st digit correct: 5)
23661 / 4060 = 			5,827832512 (2nd digit correct: 5.8)
137904 / 23661 = 		5,828325092 (3rd digit correct: 5.82)
803761 / 137904 = 		5,828409618 (3th digit correct: 5.82)
4684660 / 803761 = 		5,828424121 (4th digit correct: 5.828)
27304197 / 4684660 = 	5,828426609 (5th digit correct: 5.8284)
159140520 / 27304197 = 	5,828427036 (6th digit correct: 5.82842)
Formula is: digits in total disc number - 3 = correct digits
For example:
159140520 (9 digits) / 27304197 = 5,828427036
9 - 3 = 6 -> *5,82842*7036
This is enough for greatly reducing time required for searching the correct
number of discs.

It is possible to calculate with a calculator (excel :p) number of blue discs if
you know total number of discs. For example, total 1.000.000.000.000 discs:

1.000.000.000.000 discs * 0.7 = ~700.000.000.000 blue discs

blue discs          total discs         ratio (b/t)*((b-1)/(t-1))
700,000,000,000     1,000,000,000,000	0.48999999999979
710,000,000,000     1,000,000,000,000	0.504099999999794 <- too high
705,000,000,000     1,000,000,000,000	0.497024999999792 <- try next decimal
706,000,000,000     1,000,000,000,000	0.498435999999792
707,000,000,000     1,000,000,000,000	0.499848999999793
708,000,000,000     1,000,000,000,000	0.501263999999793
707,100,000,000     1,000,000,000,000	0.499990409999793
707,200,000,000     1,000,000,000,000	0.500131839999793
707,110,000,000     1,000,000,000,000	0.500004552099793
707,105,000,000     1,000,000,000,000	0.499997481024793
707,106,000,000     1,000,000,000,000	0.499998895235793
707,107,000,000     1,000,000,000,000	0.500000309448793
707,106,500,000     1,000,000,000,000	0.499999602342043
707,106,600,000     1,000,000,000,000	0.499999743763353
707,106,700,000     1,000,000,000,000	0.499999885184683
707,106,800,000     1,000,000,000,000	0.500000026606033
707,106,750,000     1,000,000,000,000	0.499999955895355
707,106,760,000     1,000,000,000,000	0.49999997003749
707,106,770,000     1,000,000,000,000	0.499999984179626
707,106,780,000     1,000,000,000,000	0.499999998321761
707,106,790,000     1,000,000,000,000	0.500000012463897
707,106,781,000     1,000,000,000,000	0.499999999735975
707,106,782,000     1,000,000,000,000	0.500000001150188
707,106,781,100     1,000,000,000,000	0.499999999877396
707,106,781,200     1,000,000,000,000	0.500000000018818
707,106,781,150     1,000,000,000,000	0.499999999948107
707,106,781,160     1,000,000,000,000	0.499999999962249
707,106,781,170     1,000,000,000,000	0.499999999976391
707,106,781,180     1,000,000,000,000	0.499999999990533
707,106,781,190     1,000,000,000,000	0.500000000004675
707,106,781,185     1,000,000,000,000	0.499999999997604
707,106,781,186     1,000,000,000,000	0.499999999999019
707,106,781,187     1,000,000,000,000	0.500000000000433


Steps in loop:
1. estimate next closest number of discs (previous total * 5.8...)
2. estimate number of blue discs
3. search for next correct solution (0.5 chance)
4. update precision for ratio (used in step 1)

*/

#include <stdio.h>

#define COLS 100

struct decNumStruct {
    // integer part
    char n[COLS];
    // decimal part
    char f[COLS];
};

void print(char a[]) {
	for (int i = 0; a[i] != 0; i++) {
		printf("%c", a[i]);
	}
	printf("\n");
}

void reset(char a[]) {
    int i;
    for (i = 0; i < COLS; i++) {
        a[i] = 0;
    }
}

int len(char a[]) {
    int i = 0;
    for (i = 0; a[i] != 0; i++);
    return i;
}

void copy(char a[], char b[]) {
    int i = 0;
    while (a[i] != 0) {
        b[i] = a[i];
        i++;
    }
    b[i] = 0;
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

void intToStr(int a, char s[]) {
    int i = 0;
    while (a > 0) {
        s[i] = a % 10 + 48;
        a /= 10;
        i++;
    }
    s[i] = 0;
}

//void numberToStr(char n[], char s[]) {
//    int i = 0;
//    while (n[i] != 0) {
//        s[i] = n[i];
//        i++;
//    }
//    s[i] = 0;
//    rotate(s);
//}

void add(char a[], char b[], char c[]) {
	int i = 0;
	char tmp;
	char carry = 0;
	char cont_a = 1;
	char cont_b = 1;

	do {
        tmp = 0;
		if (cont_a && a[i] != 0) {
			tmp = a[i] - 48;
		} else {
            cont_a = 0;
        }

		if (cont_b && b[i] != 0) {
			tmp += b[i] - 48;
		} else {
            cont_b = 0;
        }

        tmp += carry;

        if (cont_a || cont_b || carry) {
            c[i] = tmp % 10 + 48;
            carry = tmp / 10;
        }
        i++;
	} while (cont_a || cont_b);
    c[i] = 0;
}

void sub(char a[], char b[], char c[]) {
	int i = 0;
	char tmp;
	char carry = 0;
	char cont_a = 1;
	char cont_b = 1;

	do {
        tmp = carry;

		if (cont_a && a[i] != 0) {
			tmp += a[i] - 48;
		} else {
            cont_a = 0;
        }

		if (cont_b && b[i] != 0) {
			tmp -= b[i] - 48;
		} else {
            cont_b = 0;
        }

        if (cont_a || cont_b || carry) {
            if (tmp < 0) {
                tmp += 10;
                carry = -1;
            }
            else {
                carry = 0;
            }
            c[i] = tmp + 48;
        }
        i++;
	} while (cont_a || cont_b);
    for (; i >= 0; i--) {
        if (c[i] == 48) {
            c[i] = 0;
        }
        else if (c[i] == 0) {
            continue;
        }
        else {
            break;
        }
    }
}

void multiplySingle(char a[], char b, char c[], int start) {
    int i;
    int carry = 0;
    int sum = 1;
    int cont = 0;

    for (i = 0; i < start; i++) {
        c[i] = 48;
    }

    i = 0;
    b -= 48;
    do {
        cont = 1;
        if (a[i] != 0) {
            sum = (a[i] - 48) * b;
        } else {
            cont = 0;
            sum = 0;
        }
        sum += carry;
        if (carry || cont) {
            c[i + start] = sum % 10 + 48;
        }
        carry = sum / 10;
        i++;
    } while (carry || cont);
}

void multiply(char a[], char b[], char c[]) {
    int i = 0;
    char tmp[COLS];
    char tmp2[COLS] = {0};
    char sum[COLS] = {0};

    while (b[i] != 0) {
        reset(tmp);
        multiplySingle(a, b[i], tmp, i);
        add(tmp, tmp2, sum);
        copy(sum, tmp2);
        reset(sum);
        i++;
    }
    copy(tmp2, c);
}

// compare strings as numbers
// a > b returns 1
// a == b returns 0
// a < b returns -1
int strCompare(char a[], char b[]) {
    int i;
    int lenA = len(a);
    int lenB = len(b);

    if (lenA > lenB) {
        return 1;
    }
    else if (lenA < lenB) {
        return -1;
    }

    for (i = lenA - 1; i >= 0; i--) {
        if (a[i] > b[i]) {
            return 1;
        }
        else if (a[i] < b[i]) {
            return -1;
        }
    }

    return 0;
}

void add2arg(char *a, char *b) {
	int i = 0;
    int remainder = 0;
    int continue_a;
    int continue_b;
    char sum;

    do {
        continue_a = 0;
        continue_b = 0;
        sum = 0;
        if (a[i]) {
            sum += a[i] - 48;
            continue_a = 1;
        }
        if (b[i]) {
            sum += b[i] - 48;
            continue_b = 1;
        }

        if (continue_a || continue_b || remainder) {
            sum += remainder;
            b[i] = sum % 10 + 48;
            remainder = sum / 10;
        }
        i++;
    } while (continue_a || continue_b);
}

void printFloat(struct decNumStruct n) {
    int i, nLen = len(n.n);
    for (i = nLen - 1; i >= 0; i--) {
        printf("%c", n.n[i]);
    }
    printf(".");
    for (i = 0; n.f[i] != 0; i++) {
        printf("%c", n.f[i]);
    }
    printf("\n");
}

//void numberToFloatStr(char a[], struct decNumStruct *s) {
//    int i, j, dot = -1;
//    // find dot
//    for (i = 0; a[i] != 0; i++) {
//        if (a[i] == '.') {
//            dot = i;
//            break;
//        }
//    }
//
//    // dot found
//    if (dot > -1) {
//        // integer part
//        j = 0;
//        for (i = dot - 1; i >= 0; i--) {
//            s->n[j] = a[i];
//            j++;
//        }
//        s->n[j] = 0;
//        // float part
//        j = 0;
//        for (i = dot + 1; a[i] != 0; i++) {
//            s->f[j] = a[i];
//            j++;
//        }
//        s->f[j] = 0;
//    }
//}

void addFloat(struct decNumStruct a, struct decNumStruct b, struct decNumStruct *c) {
    int i;
    int sum;
    int carry = 0;

    int anLen = len(a.n);
    int afLen = len(a.f);

    int bnLen = len(b.n);
    int bfLen = len(b.f);

    for (i = (afLen > bfLen ? afLen : bfLen) - 1; i >= 0; i--) {
        sum = carry;
        if (i < afLen) {
            sum += a.f[i] - 48;
        }
        if (i < bfLen) {
            sum += b.f[i] - 48;
        }
        c -> f[i] = sum % 10 + 48;
        carry = sum / 10;
    }

    for (i = 0; i < (anLen > bnLen ? anLen : bnLen); i++) {
        sum = carry;
        if (i < anLen) {
            sum += a.n[i] - 48;
        }
        if (i < bnLen) {
            sum += b.n[i] - 48;
        }
        c -> n[i] = sum % 10 + 48;
        carry = sum / 10;
    }

    if (carry > 0) {
        c -> n[i] = carry + 48;
    }
}

void multiplyFloatSingle(struct decNumStruct a, int n, struct decNumStruct *res, int position) {
    int i;
    int m;
    int tmp;
    int carry = 0;

    int nLen = len(a.n);
    int fLen = len(a.f);

    int pos;

    res -> n[0] = 48;
    res -> f[0] = 48;

    for (i = 0; i < fLen * -1 + position; i++) {
        res -> n[i] = 48;
    }

    for (i = fLen * -1; i < nLen; i++) {
        if (i < 0) {
            m = a.f[i * -1 - 1];
        } else {
            m = a.n[i];
        }

        if (i < nLen) {
            tmp = (m - 48) * n + carry;
        }

        if (i + position < 0) {
            pos = (i + position) * -1 - 1;
            res -> f[pos] = tmp % 10 + 48;
        } else {
            pos = i + position;
            res -> n[pos] = tmp % 10 + 48;
        }

        carry = tmp / 10;
    }

    if (carry > 0) {
        if (i + position < 0) {
            pos = (i + position) * -1 - 1;
            res -> f[pos] = carry + 48;
        } else {
            pos = i + position;
            res -> n[pos] = carry + 48;
        }
    }

    if (i + position < 0) {
        for (i = pos - 1; i >= 0; i--) {
            res -> f[i] = 48;
        }
    }
}

void multiplyFloat(struct decNumStruct a, struct decNumStruct b, struct decNumStruct *c) {
    int i;
    struct decNumStruct tmp1 = {0, 0};
    struct decNumStruct tmp2 = {0, 0};

    for (i = 0; b.n[i] != 0; i++) {
        reset(tmp1.n);
        reset(tmp1.f);
        multiplyFloatSingle(a, b.n[i] - 48, &tmp1, i);

        reset(tmp2.n);
        reset(tmp2.f);
        addFloat(tmp1, *c, &tmp2);

        reset(c -> n);
        reset(c -> f);

        copy(tmp2.n, c -> n);
        copy(tmp2.f, c -> f);
    }

    for (i = 0; b.f[i] != 0; i++) {
        reset(tmp1.n);
        reset(tmp1.f);
        multiplyFloatSingle(a, b.f[i] - 48, &tmp1, i * -1 - 1);

        reset(tmp2.n);
        reset(tmp2.f);
        addFloat(tmp1, *c, &tmp2);

        reset(c -> n);
        reset(c -> f);

        copy(tmp2.n, c -> n);
        copy(tmp2.f, c -> f);
    }
}

/*
 * returns:
 * -1 - smaller than 0.5
 *  0 - equal to 0.5
 *  1 - greater than 0.5
 */
int calculateChance(char blue[], char total[]) {
    char blueMinusOne[COLS] = {0};
    char totalMinuOne[COLS] = {0};
    char a[COLS] = {0};
    char b[COLS] = {0};
    char c[COLS] = {0};
    char one[COLS] = {0};
    char two[COLS] = {0};

    intToStr(1, one);
    intToStr(2, two);

    sub(blue, one, blueMinusOne);
    sub(total, one, totalMinuOne);
    multiply(blue, blueMinusOne, a);
    multiply(total, totalMinuOne, b);
    multiply(a, two, c);
    return strCompare(c, b);
}

void getEstimatedBlueDiscs(char total[], char estimated[]) {
    struct decNumStruct t = {0, 0};
    struct decNumStruct r = {0, 0};
    struct decNumStruct e = {0, 0};
    r.f[0] = 7 + 48;
    copy(total, t.n);
    multiplyFloat(t, r, &e);
    copy(e.n, estimated);
}

void getMinimumBlueDiscs(char blue[], char total[]) {
    int i;
    int l;
    char inc[COLS];
    char tmp[COLS];
    char ok[COLS] = {0};
    int ret;
    getEstimatedBlueDiscs(total, blue);
    l = len(blue) - 1;

    while (l > 0) {
        reset(inc);
        for (i = 0; i < l - 1; i++) {
            inc[i] = 48;
        }
        inc[l - 1] = 1 + 48;

        do {
            reset(ok);
            copy(blue, ok);
            reset(tmp);
            add(blue, inc, tmp);
            reset(blue);
            copy(tmp, blue);
            ret = calculateChance(blue, total);
        } while (ret == -1);
        reset(blue);
        copy(ok, blue);

        l--;
    }
}

void getEstimatedDiscs(char total[], struct decNumStruct ratio, char estimated[]) {
    struct decNumStruct t = {0, 0};
    struct decNumStruct e = {0, 0};
    copy(total, t.n);
    multiplyFloat(t, ratio, &e);
    copy(e.n, estimated);
}

void findNextMatch(char blue[], char total[]) {
    int ret;
    char one[COLS] = {0};
    intToStr(1, one);
    while (1) {
        ret = calculateChance(blue, total);
        if (ret == -1) {
            add2arg(one, blue);
            add2arg(one, total);
        }
        else if (ret == 1) {
            add2arg(one, total);
        }
        else {
            break;
        }
    }
}

int findClosestPrecision(struct decNumStruct ratio, int precision, char prev1[], char prev2[]) {
    int i = 0;
    int ok = 0;
    int ret;
    struct decNumStruct p1 = {0, 0};
    struct decNumStruct p2 = {0, 0};
    struct decNumStruct r = {0, 0};

    copy(prev1, p1.n);
    copy(prev2, p2.n);
    ratio.f[precision] = 48;

    while (1) {
        ratio.f[precision]++;
        reset(r.n);
        reset(r.f);
        multiplyFloat(p1, ratio, &r);
        ret = strCompare(r.n, prev2);
        if (ret == -1) {
            ok = ratio.f[precision];
        } else {
            ratio.f[precision] = ok;
            break;
        }
    }
    return ok;
}

int main() {
    int precision;
    char blue[COLS] = {0};
    char total[COLS];
    char lastTotalDiscs[COLS] = {0};

    intToStr(120, lastTotalDiscs);

    struct decNumStruct ratio = {0, 0};

    ratio.n[0] = 5 + 48;

    while (1) {
        reset(total);
        getEstimatedDiscs(lastTotalDiscs, ratio, total);
        copy(total, blue);
        getMinimumBlueDiscs(blue, total);
        findNextMatch(blue, total);

        rotate(blue);
        rotate(total);
        printf("%s > %s (length %d)\n", blue, total, len(total));
        if (len(total) == 13) {
            break;
        }
        rotate(blue);
        rotate(total);

        precision = len(total) - 3;
        ratio.f[precision] = findClosestPrecision(ratio, precision, lastTotalDiscs, total);
        reset(lastTotalDiscs);
        copy(total, lastTotalDiscs);
    }

    return 0;
}
