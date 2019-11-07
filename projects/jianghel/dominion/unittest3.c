/*
Test function: minion
+1 Action
Choice 1: +2 gold
Choice 2: +4 cards and all players with 5 cards in hands discards their hand and draw 4 cards

1. +1 action for all cases 
2. 
*/
#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

void clearHand(struct gameState *g, int cp)
{
    int i;
    for (i = 0; i < g->handCount[cp]; i++)
    {
        discardCard(0, cp, g, 0);
    }
    g->handCount[cp] = 0;
}

void clearDiscard(struct gameState *g, int cp)
{

    int i;
    for (i = 0; i < g->discardCount[cp]; i++)
    {
        g->discardCount[i] = -1;
    }
    g->discardCount[cp] = 0;
}

//returns true if card in hand
int checkHand(struct gameState *g, int cp, int card)
{
    int i;
    for (i = 0; i < g->handCount[cp]; i++)
    {
        if (g->hand[cp][i] == card)
        {
            return 1;
        }
    }

    return 0;
}

int main()
{
    int i;
    int totalTests = 10;
    int failed = 0;
    //set card array
    int k[10] = { ambassador, minion, tribute, gardens, mine, remodel, smithy, village, baron, great_hall };

    //declare game state
    struct gameState g, testG;

    // declare the arrays
    int coppers[MAX_HAND];
    int silvers[MAX_HAND];
    int golds[MAX_HAND];

    int seed = 1000;
    int numPlayers = 3;
    int handPos = 0;
    int currentPlayer;
    int choice1, choice2, choice3 = 0;
    printf("\n\nBegin Testing minion:\n");

    initializeGame(numPlayers, k, seed, &g);

    printf("-------Test 1: minion choice 1  ----------------------------------------------\n");

    currentPlayer = g.whoseTurn;
    clearHand(&g, currentPlayer);
    g.hand[currentPlayer][0] = minion;
    g.handCount[currentPlayer]++;
    choice1 = 1;
    memcpy(&testG, &g, sizeof(struct gameState));
    minionAction(handPos, currentPlayer, choice1, choice2, &g);

    if (g.coins - 2 == testG.coins)
    {
        printf("Test 1: passed; correct amount of coins gained\n");
    }
    else
    {
        printf("Test 1: failed; incorrect gold; coins: %d vs testG coins: %d\n", g.coins, testG.coins);
        failed++;
    }

    if (g.numActions - 1 == testG.numActions)
    {
        printf("Test 1: passed; correct amount of actions gained");
    }
    else
    {
        printf("Test 1: failed; incorrect actions; actions: %d vs testG actions: %d\n", g.numActions, testG.numActions);
        failed++;
    }

    if (g.hand[currentPlayer][0] != minion)
    {
        printf("Test 1: passed; minion no longer in hand\n");
    }
    else
    {
        printf("Test 1: failed; minion card still on hand\n");
        failed++;
    }

    printf("-------Test 2: minion choice 2; 1 player with 5 cards, 1 player with 6 cards  -------------------------\n");
    //both players should have hand discarded
    //current player + 4 cards , + 1 action
    currentPlayer = g.whoseTurn;
    clearHand(&g, currentPlayer);
    int badCard = 30;
    g.hand[currentPlayer][0] = badCard;
    g.hand[currentPlayer][1] = badCard;
    g.hand[currentPlayer][2] = badCard;
    g.handCount[currentPlayer] += 3;

    int nextPlayer = currentPlayer == 0 ? numPlayers - 1 : currentPlayer - 1; //5 cards
    clearHand(&g, nextPlayer);
    g.hand[nextPlayer][0] = badCard; //have them gain impossible hands
    g.hand[nextPlayer][1] = badCard;
    g.hand[nextPlayer][2] = badCard;
    g.hand[nextPlayer][3] = badCard;
    g.hand[nextPlayer][4] = badCard;
    g.handCount[nextPlayer] += 5;

    int otherPlayer = nextPlayer == 0 ? numPlayers - 1 : nextPlayer - 1; //4 cards
    clearHand(&g, otherPlayer);
    g.hand[otherPlayer][0] = badCard;
    g.hand[otherPlayer][1] = badCard;
    g.hand[otherPlayer][2] = badCard;
    g.hand[otherPlayer][3] = badCard;
    g.hand[otherPlayer][4] = badCard;
    g.hand[otherPlayer][5] = badCard;
    g.handCount[otherPlayer] += 6;

    choice1 = 0;
    choice2 = 1;
    // printf("current, next, other %d, %d, %d\n", currentPlayer, nextPlayer, otherPlayer);
    memcpy(&testG, &g, sizeof(struct gameState));
    minionAction(handPos, currentPlayer, choice1, choice2, &g);

    if (g.numActions - 1 == testG.numActions)
    {
        printf("Test 2: passed; correct amount of actions gained\n");
    }
    else
    {
        printf("Test 2: failed; incorrect actions; actions: %d\n", g.numActions);
        failed++;
    }

    if (g.handCount[currentPlayer] == 4)
    {
        printf("Test 2: passed; correct amount of cards gained for current player\n");
    }
    else
    {
        printf("Test 2: failed; incorrect cards for current player; cards: %d\n", g.handCount[currentPlayer]);
        failed++;
    }

    if (g.handCount[nextPlayer] == 4)
    {
        printf("Test 2: passed; correct amount of cards gained for next player\n");
    }
    else
    {
        printf("Test 2: failed; incorrect cards for next player; cards: %d\n", g.handCount[nextPlayer]);
        failed++;
    }

    if (g.handCount[otherPlayer] == 4)
    {
        printf("Test 2: passed; correct amount of cards gained for other player\n");
    }
    else
    {
        printf("Test 2: failed; incorrect cards for other player; cards: %d\n", g.handCount[otherPlayer]);
        failed++;
    }

    if (checkHand(&g, currentPlayer, badCard))
    {
        printf("Test 2: failed; Bad card still left in current player's hand\n");
        failed++;
    }
    else
    {
        printf("Test 2: passed; no bad card left in current player's hand\n");
    }

    if (checkHand(&g, nextPlayer, badCard))
    {
        printf("Test 2: failed; Bad card still left in player 1 with 5 cards' hand\n");
        failed++;
    }
    else
    {
        printf("Test 2: passed; no bad card left in hand\n");
    }

    if (checkHand(&g, otherPlayer, badCard))
    {
        printf("Test 2: failed; Bad card still left in player 2 with 6 cards' hand\n");
        failed++;
    }
    else
    {
        printf("Test 2: passed; no bad card left in hand\n");
    }

    printf("Tests completed! Failed %d tests out of %d\n", failed, totalTests);

    return 0;
}