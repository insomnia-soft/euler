/*

Monopoly odds
Problem 84

In the game, Monopoly, the standard board is set up in the following way:

GO  A1 CC1  A2  T1  R1  B1 CH1  B2 B3  JAIL
H2                                      C1
T2                                      U1
H1                                      C2
CH3                                     C3
R4                                      R2
G3                                      D1
CC3                                     CC2
G2                                      D2
G1                                      D3
G2J F3  U2  F2  F1  R3  E3  E2 CH2 E1  FP

A player starts on the GO square and adds the scores on two 6-sided dice to
determine the number of squares they advance in a clockwise direction. Without
any further rules we would expect to visit each square with equal probability:
2.5%. However, landing on G2J (Go To Jail), CC (community chest), and CH
(chance) changes this distribution.

In addition to G2J, and one card from each of CC and CH, that orders the player
to go directly to jail, if a player rolls three consecutive doubles, they do not
advance the result of their 3rd roll. Instead they proceed directly to jail.

At the beginning of the game, the CC and CH cards are shuffled. When a player
lands on CC or CH they take a card from the top of the respective pile and,
after following the instructions, it is returned to the bottom of the pile.
There are sixteen cards in each pile, but for the purpose of this problem we are
only concerned with cards that order a movement; any instruction not concerned
with movement will be ignored and the player will remain on the CC/CH square.

Community Chest (2/16 cards):
    1.Advance to GO
    Go to JAIL
Chance (10/16 cards):
    Advance to GO
    Go to JAIL
    Go to C1
    Go to E3
    Go to H2
    Go to R1
    Go to next R (railway company)
    Go to next R
    Go to next U (utility company)
    Go back 3 squares.

The heart of this problem concerns the likelihood of visiting a particular
square. That is, the probability of finishing at that square after a roll. For
this reason it should be clear that, with the exception of G2J for which the
probability of finishing on it is zero, the CH squares will have the lowest
probabilities, as 5/8 request a movement to another square, and it is the final
square that the player finishes at on each roll that we are interested in. We
shall make no distinction between "Just Visiting" and being sent to JAIL, and we
shall also ignore the rule about requiring a double to "get out of jail",
assuming that they pay to get out on their next turn.

By starting at GO and numbering the squares sequentially from 00 to 39 we can
concatenate these two-digit numbers to produce strings that correspond with sets
of squares.

Statistically it can be shown that the three most popular squares, in order, are
JAIL (6.24%) = Square 10, E3 (3.18%) = Square 24, and GO (3.09%) = Square 00. So
these three most popular squares can be listed with the six-digit modal string:
102400.

If, instead of using two 6-sided dice, two 4-sided dice are used, find the
six-digit modal string.


Solution:

101524

- 50ms

*/

// 0 - normal card
// 1 - Advance to GO
// 2 - Go to JAIL
// 3 - Go to C1
// 4 - Go to E3
// 5 - Go to H2
// 6 - Go to R1
// 7 - Go to next R (railway company)
// 8 - Go to next U (utility company)
// 9 - Go back 3 squares

//      0   1   2   3   4   5   6   7   8  9
//     GO  A1 CC1  A2  T1  R1  B1 CH1  B2 B3   JAIL  10
// 39  H2                                      C1    11
// 38  T2                                      U1    12
// 37  H1                                      C2    13
// 36  CH3                                     C3    14
// 35  R4                                      R2    15
// 34  G3                                      D1    16
// 33  CC3                                     CC2   17
// 32  G2                                      D2    18
// 31  G1                                      D3    19
// 30  G2J F3  U2  F2  F1  R3  E3  E2 CH2 E1   FP
//         29  28  27  26  25  24  23  22 21   20


#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define DICE 4

//#define MAX 1000000000
#define MAX 1000000

int visited[40] = {0};

int position = 0;
int repeats = 0;

int CC[16] = {0};
int ccIndex = 16;

int CH[16] = {0};
int chIndex = 16;

void findMax3() {
    int top1 = 0;
    int top2 = 0;
    int top3 = 0;

    int top1i = 0;
    int top2i = 0;
    int top3i = 0;

    int i;
    for (i = 0; i < 40; i++) {
        if (visited[i] > top1) {
            top1 = visited[i];
            top1i = i;
        }
    }
    for (i = 0; i < 40; i++) {
        if (visited[i] > top2 && visited[i] < top1) {
            top2 = visited[i];
            top2i = i;
        }
    }
    for (i = 0; i < 40; i++) {
        if (visited[i] > top3 && visited[i] < top2) {
            top3 = visited[i];
            top3i = i;
        }
    }

    printf("%01d %01d %01d\n", top1i, top2i, top3i);
}

void shuffle(int deck[16]) {
    int j, i, r, tmp;

    for (j = 0; j < 100; j++) {
        for (i = 0; i < 16; i++) {
            do {
                r = rand() % 16;
            } while (r == i);
            tmp = deck[r];
            deck[r] = deck[i];
            deck[i] = tmp;
        }
    }
}

int rollCC(int pos) {
    ccIndex++;
    if (ccIndex >= 16) {
        ccIndex = 0;
    }
    switch (CC[ccIndex]) {
        // 1 - Advance to GO
        case 1:
            return 0;

        // 2 - Go to JAIL
        case 2:
            return 10;

        default:
            return pos;
    }
}

int rollCH(int pos) {
    int tmp;

    chIndex++;
    if (chIndex >= 16) {
        chIndex = 0;
    }
    switch (CH[chIndex]) {
        // 1 - Advance to GO
        case 1:
            return 0;

        // 2 - Go to JAIL
        case 2:
            return 10;

        // 3 - Go to C1
        case 3:
            return 11;

        // 4 - Go to E3
        case 4:
            return 24;

        // 5 - Go to H2
        case 5:
            return 39;

        // 6 - Go to R1
        case 6:
            return 5;

        // 7 - Go to next R (railway company)
        case 7:
            if (pos == 7) {
                return 15;
            }
            else if (pos == 22) {
                return 25;
            }
            else if (pos == 36) {
                return 5;
            }

        // 8 - Go to next U (utility company)
        case 8:
            if (pos == 7) {
                return 12;
            }
            else if (pos == 22) {
                return 28;
            }
            else if (pos == 36) {
                return 12;
            }

        // 9 - Go back 3 squares
        case 9:
            tmp = pos - 3;
            if (tmp == 33) {
                return rollCC(tmp);
            }
            return tmp;

        default:
            return pos;
    }
}

void roll() {
    int dice1, dice2;

    dice1 = rand() % DICE + 1;
    dice2 = rand() % DICE + 1;

    if (dice1 == dice2) {
        repeats++;
        // same dice 3 times in a row
        if (repeats == 3) {
            // Go to JAIL
            position = 10;
            visited[position]++;
            return;
        }
    } else {
        repeats = 0;
    }

    position += dice1 + dice2;
    if (position >= 40) {
        position -= 40;
    }

    switch (position) {
        // Go to JAIL
        case 30:
            position = 10;
            break;

        // CC
        case 2:
        case 17:
        case 33:
            position = rollCC(position);
            break;

        // CH
        case 7:
        case 22:
        case 36:
            position = rollCH(position);
            break;
    }

    visited[position]++;
}

int main() {
    int i;

    srand(time(NULL));

    CC[0] = 1; // 1 - Advance to GO
    CC[1] = 2; // 2 - Go to JAIL

    CH[0] = 1; // 1 - Advance to GO
    CH[1] = 2; // 2 - Go to JAIL
    CH[2] = 3; // 3 - Go to C1
    CH[3] = 4; // 4 - Go to E3
    CH[4] = 5; // 5 - Go to H2
    CH[5] = 6; // 6 - Go to R1
    CH[6] = 7; // 7 - Go to next R (railway company)
    CH[7] = 7; // 7 - Go to next R (railway company)
    CH[8] = 8; // 8 - Go to next U (utility company)
    CH[9] = 9; // 9 - Go back 3 squares

    shuffle(CC);
    shuffle(CH);

    for (i = 0; i < MAX; i++) {
        roll();
    }

//    for (i = 0; i < 40; i++) {
//        printf("[%2d] %6d %5.2f\n", i, visited[i], (double) visited[i] / (MAX / 100));
//    }
//    printf("\n");

    findMax3();

    return 0;
}
