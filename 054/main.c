/*

Poker hands
Problem 54

In the card game poker, a hand consists of five cards and are ranked, from
lowest to highest, in the following way:

    High Card: Highest value card.
    One Pair: Two cards of the same value.
    Two Pairs: Two different pairs.
    Three of a Kind: Three cards of the same value.
    Straight: All cards are consecutive values.
    Flush: All cards of the same suit.
    Full House: Three of a kind and a pair.
    Four of a Kind: Four cards of the same value.
    Straight Flush: All cards are consecutive values of same suit.
    Royal Flush: Ten, Jack, Queen, King, Ace, in same suit.

The cards are valued in the order:
2, 3, 4, 5, 6, 7, 8, 9, 10, Jack, Queen, King, Ace.

If two players have the same ranked hands then the rank made up of the highest
value wins; for example, a pair of eights beats a pair of fives (see example 1
below). But if two ranks tie, for example, both players have a pair of queens,
then highest cards in each hand are compared (see example 4 below); if the
highest cards tie then the next highest cards are compared, and so on.

Consider the following five hands dealt to two players:

 Hand   Player 1            Player 2                Winner

 1      5H 5C 6S 7S KD      2C 3S 8S 8D TD          Player 2
        Pair of Fives       Pair of Eights

 2      5D 8C 9S JS AC      2C 5C 7D 8S QH          Player 1
        Highest card Ace    Highest card Queen

 3      2D 9C AS AH AC      3D 6D 7D TD QD          Player 2
        Three Aces          Flush with Diamonds

 4      4D 6S 9H QH QC      3D 6D 7H QD QS          Player 1
        Pair of Queens      Pair of Queens
        Highest card Nine   Highest card Seven

 5      2H 2D 4C 4D 4S      3C 3D 3S 9S 9D          Player 1
        Full House          Full House
        With Three Fours    with Three Threes

The file, poker.txt, contains one-thousand random hands dealt to two players.
Each line of the file contains ten cards (separated by a single space): the
first five are Player 1's cards and the last five are Player 2's cards. You can
assume that all hands are valid (no invalid characters or repeated cards), each
player's hand is in no specific order, and in each hand there is a clear winner.

How many hands does Player 1 win?


Solution:

376

*/

#include <stdlib.h>
#include <stdio.h>

#define GAMES 1000
#define PLAYERS 2
#define HAND 5
#define CARD 2

// 14 Ace
// 13 King
// 12 Queen
// 11 Jack
// 10 Ten
//  9 9
//  . .
//  2 2
#define TOTAL_CARD_NUMBERS 15
#define TOTAL_CARD_COLORS 5

char poker[GAMES][PLAYERS][HAND][CARD] = {0};
int games = 0;

int decodeCard(char card) {
    switch (card) {
        case 'T':
            return 10;
        case 'J':
            return 11;
        case 'Q':
            return 12;
        case 'K':
            return 13;
        case 'A':
            return 14;
        default:
            return card - 48;
    }
    return 0;
}

int decodeColor(char card) {
    switch (card) {
        case 'H':
            return 1;
        case 'D':
            return 2;
        case 'C':
            return 3;
        case 'S':
            return 4;
    }
}

// Royal Flush: Ten, Jack, Queen, King, Ace, in same suit.
int isRoyalFlush(int game, int player) {
    int i, c;
    int cards[TOTAL_CARD_NUMBERS] = {0};
    int colors[TOTAL_CARD_COLORS] = {0};
    int found;
    for (i = 0; i < HAND; i++) {
        c = poker[game][player][i][0];
        cards[c] = 1;
        c = poker[game][player][i][1];
        colors[c]++;
    }

    found = 0;
    for (i = 0; i < 4; i++) {
        if (colors[i] == 5) {
            found = 1;
            break;
        }
    }

    if (found == 0) {
        return 0;
    }

    for (i = 10; i <= 14; i++) {
        if (cards[i] == 0) {
            return 0;
        }
    }

    return 1;
}

// Straight Flush: All cards are consecutive values of same suit.
int isStraightFlush(int game, int player) {
    int i, j, c, found;
    int cards[TOTAL_CARD_NUMBERS] = {0};
    int colors[TOTAL_CARD_COLORS] = {0};
    for (i = 0; i < HAND; i++) {
        c = poker[game][player][i][0];
        cards[c] = 1;
        c = poker[game][player][i][1];
        colors[c]++;
    }

    found = 0;
    for (i = 0; i < 4; i++) {
        if (colors[i] == 5) {
            found = 1;
            break;
        }
    }

    if (found == 0) {
        return 0;
    }

    for (i = 2; i <= 9; i++) {
        found = 0;
        for (j = 0; j < 5; j++) {
            found += cards[i + j];
        }
        if (found == 5) {
            return 1;
        }
    }

    return 0;
}

// Four of a Kind: Four cards of the same value.
int isFourOfAKind(int game, int player) {
    int i, c;
    int cards[TOTAL_CARD_NUMBERS] = {0};
    for (i = 0; i < HAND; i++) {
        c = poker[game][player][i][0];
        cards[c]++;
    }
    for (i = 2; i <= 14; i++) {
        if (cards[i] == 4) {
            return 1;
        }
    }

    return 0;
}

// Full House: Three of a kind and a pair.
int isFullHouse(int game, int player) {
    int i, c;
    int three = 0;
    int two = 0;
    int cards[TOTAL_CARD_NUMBERS] = {0};
    for (i = 0; i < HAND; i++) {
        c = poker[game][player][i][0];
        cards[c]++;
    }
    for (i = 2; i <= 14; i++) {
        if (cards[i] == 3) {
            three = 1;
        }
        if (cards[i] == 2) {
            two = 1;
        }
    }

    if (three && two) {
        return 1;
    }

    return 0;
}

// Flush: All cards of the same suit.
int isFlush(int game, int player) {
    int i, c;
    int colors[TOTAL_CARD_COLORS] = {0};
    for (i = 0; i < HAND; i++) {
        c = poker[game][player][i][1];
        colors[c]++;
    }
    for (i = 0; i < 4; i++) {
        if (colors[i] == 5) {
            return 1;
        }
    }

    return 0;
}

// Straight: All cards are consecutive values.
int isStraight(int game, int player) {
    int i, j, c, found;
    int cards[TOTAL_CARD_NUMBERS] = {0};
    for (i = 0; i < HAND; i++) {
        c = poker[game][player][i][0];
        cards[c] = 1;
    }

    for (i = 2; i <= 9; i++) {
        found = 0;
        for (j = 0; j < 5; j++) {
            found += cards[i + j];
        }
        if (found == 5) {
            return 1;
        }
    }

    return 0;
}

// Three of a Kind: Three cards of the same value.
int isThreeOfAKind(int game, int player) {
    int i, c;
    int cards[TOTAL_CARD_NUMBERS] = {0};
    for (i = 0; i < HAND; i++) {
        c = poker[game][player][i][0];
        cards[c]++;
    }
    for (i = 2; i <= 14; i++) {
        if (cards[i] == 3) {
            return 1;
        }
    }

    return 0;
}

// Two Pairs: Two different pairs.
int isTwoPairs(int game, int player) {
    int i, c;
    int pair1 = 0;
    int pair2 = 0;
    int cards[TOTAL_CARD_NUMBERS] = {0};
    for (i = 0; i < HAND; i++) {
        c = poker[game][player][i][0];
        cards[c]++;
    }
    for (i = 2; i <= 14; i++) {
        if (pair1 == 0) {
            if (cards[i] == 2) {
                pair1 = 1;
            }
        } else {
            if (cards[i] == 2) {
                pair2 = 1;
            }
        }
    }

    if (pair1 && pair2) {
        return 1;
    }

    return 0;
}

// One Pair: Two cards of the same value.
int isOnePair(int game, int player) {
    int i, c;
    int cards[TOTAL_CARD_NUMBERS] = {0};
    for (i = 0; i < HAND; i++) {
        c = poker[game][player][i][0];
        cards[c]++;
    }
    for (i = 2; i <= 14; i++) {
        if (cards[i] == 2) {
            return 1;
        }
    }

    return 0;
}

int BetterPair(int game) {
    int i, c;
    int cards1[TOTAL_CARD_NUMBERS] = {0};
    int cards2[TOTAL_CARD_NUMBERS] = {0};
    int max1pair = 0;
    int max2pair = 0;

    int max1 = 0;
    int max2 = 0;

    for (i = 0; i < HAND; i++) {
        c = poker[game][0][i][0];
        cards1[c]++;
        c = poker[game][1][i][0];
        cards2[c]++;
    }
    for (i = 2; i <= 14; i++) {
        if (cards1[i] == 2) {
            max1pair = i;
        } else {
            if (cards1[i] == 1 && i > max1) {
                max1 = i;
            }
        }
    }
    for (i = 2; i <= 14; i++) {
        if (cards2[i] == 2) {
            max2pair = i;
        } else {
            if (cards2[i] == 1 && i > max2) {
                max2 = i;
            }
        }
    }

    if (max1pair > max2pair) {
        return 1;
    }
    else if (max1pair < max2pair) {
        return 2;
    }
    else {
        if (max1 > max2) {
            return 1;
        }
        else if (max1 < max2) {
            return 2;
        }
    }

    return 0;
}

// High Card: Highest value card.
int HighCard(int game) {
    int i, p1 = 0, p2 = 0, card;
    for (i = 0; i < HAND; i++) {
        card = poker[game][0][i][0];
        if (card > p1) {
            p1 = card;
        }
        card = poker[game][1][i][0];
        if (card > p2) {
            p2 = card;
        }
    }

    if (p1 > p2) {
        return 1;
    }
    else if (p2 > p1) {
        return 2;
    }

    return 0;
}

int loadFile() {
    FILE *fp;
    char line[30];
    int player, hand;
    int pos;
    int game = 0;

    fp = fopen("p054_poker.txt", "r");

    if (!fp) {
        return 0;
    }

    while(fgets(line, 100, fp)) {
        pos = 0;
        for (player = 0; player < PLAYERS; player++) {
            for (hand = 0; hand < HAND; hand++) {
                poker[game][player][hand][0] = decodeCard(line[pos]);
                poker[game][player][hand][1] = decodeColor(line[pos + 1]);
                pos += 3;
            }
        }
        game++;
    }

    games = game;

    fclose(fp);
    return 1;
}

int main() {
    int game;
    int p1 = 0;
    int p2 = 0;

    int p1wins = 0;
    int p2wins = 0;
    int ret;

    if (loadFile() == 0) {
        printf("Can't open file p054_poker.txt!");
        return (EXIT_SUCCESS);
    }

    for (game = 0; game < games; game++) {

        /* Royal Flush: Ten, Jack, Queen, King, Ace, in same suit. ************/
        p1 = isRoyalFlush(game, 0);
        p2 = isRoyalFlush(game, 1);
        if (p1 > p2) {
            p1wins++;
            continue;
        }
        else if (p2 > p1) {
            p2wins++;
            continue;
        }
        /**********************************************************************/

        /* Straight Flush: All cards are consecutive values of same suit. *****/
        p1 = isStraightFlush(game, 0);
        p2 = isStraightFlush(game, 1);
        if (p1 > p2) {
            p1wins++;
            continue;
        }
        else if (p2 > p1) {
            p2wins++;
            continue;
        }
        /**********************************************************************/

        /* Four of a Kind: Four cards of the same value. **********************/
        p1 = isFourOfAKind(game, 0);
        p2 = isFourOfAKind(game, 1);
        if (p1 > p2) {
            p1wins++;
            continue;
        }
        else if (p2 > p1) {
            p2wins++;
            continue;
        }
        /**********************************************************************/

        /* Full House: Three of a kind and a pair. ****************************/
        p1 = isFullHouse(game, 0);
        p2 = isFullHouse(game, 1);
        if (p1 > p2) {
            p1wins++;
            continue;
        }
        else if (p2 > p1) {
            p2wins++;
            continue;
        }
        /**********************************************************************/

        /* Flush: All cards of the same suit. *********************************/
        p1 = isFlush(game, 0);
        p2 = isFlush(game, 1);
        if (p1 > p2) {
            p1wins++;
            continue;
        }
        else if (p2 > p1) {
            p2wins++;
            continue;
        }
        /**********************************************************************/

        /* Straight: All cards are consecutive values. ************************/
        p1 = isStraight(game, 0);
        p2 = isStraight(game, 1);
        if (p1 > p2) {
            p1wins++;
            continue;
        }
        else if (p2 > p1) {
            p2wins++;
            continue;
        }
        /**********************************************************************/

        /* Three of a Kind: Three cards of the same value. ********************/
        p1 = isThreeOfAKind(game, 0);
        p2 = isThreeOfAKind(game, 1);
        if (p1 > p2) {
            p1wins++;
            continue;
        }
        else if (p2 > p1) {
            p2wins++;
            continue;
        }
        /**********************************************************************/

        /* Two Pairs: Two different pairs. ************************************/
        p1 = isTwoPairs(game, 0);
        p2 = isTwoPairs(game, 1);
        if (p1 > p2) {
            p1wins++;
            continue;
        }
        else if (p2 > p1) {
            p2wins++;
            continue;
        }
        /**********************************************************************/

        /* One Pair: Two cards of the same value. *****************************/
        p1 = isOnePair(game, 0);
        p2 = isOnePair(game, 1);
        if (p1 > p2) {
            p1wins++;
            continue;
        }
        else if (p2 > p1) {
            p2wins++;
            continue;
        }
        else if (p1 == 1 && p2 == 1) {
            ret = BetterPair(game);
            if (ret == 1) {
                p1wins++;
                continue;
            }
            else if (ret == 2) {
                p2wins++;
                continue;
            }
        }
        /**********************************************************************/

        /* Highest card *******************************************************/
        ret = HighCard(game);
        if (ret == 1) {
            p1wins++;
            continue;
        }
        else if (ret == 2) {
            p2wins++;
            continue;
        }
        /**********************************************************************/
    }

    printf("Player 1: %d\n", p1wins);
    printf("Player 2: %d\n", p2wins);

    return (EXIT_SUCCESS);
}
