/*
Ambassador

Reveal a card from your hand

Return up to 2 copies of it from your hand to the supply

Then each other player gains a copy of it 

1. choice 1 = some card; choice 2 = 2 copies 
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

int goldCount(struct gameState *g, int cp)
{
    int i, count = 0;
    for(i = 0; i < g->handCount[cp]; i++)
    {
        if(g->hand[cp][i] == gold)
            count++;
    }
    return count;
}

int main(){
    int i;
    int totalTests = 9;
    int failed = 0;
    //set card array
    int k[10] = { ambassador, minion, tribute, gardens, mine, remodel, smithy, village, baron, great_hall };

    //declare game state
    struct gameState g, testG;

    // declare the arrays
    int coppers[MAX_HAND]; int silvers[MAX_HAND]; int golds[MAX_HAND];

    int seed = 1000;
    int numPlayers = 3;
    int handPos = 0;
    int currentPlayer;
    int choice1, choice2, choice3 = 0;
    printf("\n\nBegin Testing ambassador:\n");

    initializeGame(numPlayers, k, seed, &g);

    printf("-------Test 1: ambassador choice 1 is valid card and choice 2 is 2 copies --------------------------\n");

    currentPlayer = g.whoseTurn;
    clearHand(&g, currentPlayer);
    g.hand[currentPlayer][0] = ambassador;
    g.hand[currentPlayer][1] = gold;
    g.hand[currentPlayer][2] = gold;
    g.hand[currentPlayer][3] = gold;
    g.handCount[currentPlayer] += 4;

    choice1 = 1;
    choice2 = 2;

    memcpy(&testG, &g, sizeof(struct gameState));
    int r = ambassadorAction(handPos, currentPlayer, choice1, choice2, &g);
    if ( r != -1)
    {
         printf("Test 1: passed; r != -1\n");
    }
    else{
        printf("Test 1: failed; function returned prematurely\n");
        failed++;
    }
    // should only have 1 gold left in hand 
    
    if(goldCount(&g, currentPlayer) > 1)
    {
        printf("Test 1: failed; gold count : %d vs expected: 1\n", goldCount(&g, currentPlayer));
        failed++;
    }
    else
    {
        printf("Test 1: passed; correct gold count\n");
    }
    
    printf("-------Test 2: ambassador choice 1 is valid card but insufficent copies of choice 2 -----------------\n");
    currentPlayer = g.whoseTurn;
    clearHand(&g, currentPlayer);
    g.hand[currentPlayer][0] = ambassador;
    g.hand[currentPlayer][1] = gold;
    g.handCount[currentPlayer] += 2;

    choice1 = 1;
    choice2 = 4;

    memcpy(&testG, &g, sizeof(struct gameState));
    r = ambassadorAction(handPos, currentPlayer, choice1, choice2, &g);
    if ( r == -1)
    {
         printf("Test 2: passed; r == -1\n");
    }
    else{
        printf("Test 2: failed; function didn't returned prematurely\n");
        failed++;
    }

    printf("-------Test 3: choice1 = ambassador   ----------------------\n");
    currentPlayer = g.whoseTurn;
    clearHand(&g, currentPlayer);
    g.hand[currentPlayer][0] = ambassador;
    g.handCount[currentPlayer] ++;

    choice1 = 0;
    choice2 = 1;

    memcpy(&testG, &g, sizeof(struct gameState));
    r = ambassadorAction(handPos, currentPlayer, choice1, choice2, &g);
    if ( r == -1)
    {
         printf("Test 3: passed; r == -1\n");
    }
    else{
        printf("Test 3: failed; r != -1\n");
        failed++;
    }

    printf("-------Test 4: choice1 = not in hand   ----------------------\n");
      currentPlayer = g.whoseTurn;
    clearHand(&g, currentPlayer);
    g.hand[currentPlayer][0] = ambassador;
    g.hand[currentPlayer][1] = gold;
    g.handCount[currentPlayer] += 2;

    choice1 = 4;
    choice2 = 1;

    memcpy(&testG, &g, sizeof(struct gameState));
    r = ambassadorAction(handPos, currentPlayer, choice1, choice2, &g);
    if ( r == -1)
    {
         printf("Test 4: passed; r == -1\n");
    }
    else{
        printf("Test 4: failed; r != -1\n");
        failed++;
    }

    printf("-------Test 5: ambassador choice 1 is valid card and choice2 =1  ----------------------\n");
    //check for supply
    //check for other players
    //check for current players 
    currentPlayer = 1;
    clearHand(&g, currentPlayer);
    g.hand[currentPlayer][0] = ambassador;
    g.hand[currentPlayer][1] = gold;
    g.hand[currentPlayer][2] = gold;
    g.handCount[currentPlayer] += 3;
    choice1 = 1;
    choice2 = 1;

    int nextPlayer = currentPlayer == 0 ? numPlayers - 1 : currentPlayer - 1;
    clearHand(&g, nextPlayer);
    g.hand[nextPlayer][0] = silver;
    g.handCount[nextPlayer] ++;

    int otherPlayer = nextPlayer == 0 ? numPlayers - 1 : nextPlayer - 1;
    clearHand(&g, otherPlayer);
    g.hand[otherPlayer][0] = silver;
    g.handCount[otherPlayer] ++;

    memcpy(&testG, &g, sizeof(struct gameState));
    r = ambassadorAction(handPos, currentPlayer, choice1, choice2, &g);
    //current player should have 1 copy of gold left 

    if(r != -1){
        printf("Test 5: able to test as r != -1\n");
    }
    else{
        printf("Test 5 failed: function ended prematurely\n");
        failed++;
    }

    if(goldCount(&g, currentPlayer) > 1)
    {
        printf("Test 5: failed; currentplayer gold : %d vs expected: 1\n", goldCount(&g, currentPlayer));
        failed++;
    }
    else
    {
        printf("Test 5: passed; correct gold count\n");
    }

    if(goldCount(&g, nextPlayer) != 1)
    {
        printf("Test 5: failed; next player gold : %d vs expected: 1\n", goldCount(&g, nextPlayer));
        failed++;
    }
    else
    {
        printf("Test 5: passed; correct gold count: %d\n", goldCount(&g, nextPlayer));
    }

    if(goldCount(&g, otherPlayer) != 1)
    {
        printf("Test 5: failed; other player gold : %d vs expected: 1\n", goldCount(&g, otherPlayer));
        failed++;
    }
    else
    {
        printf("Test 5: passed; correct gold count: %d\n", goldCount(&g, otherPlayer));
    }

    //suply should be one less than before
    if(g.supplyCount[gold] + 1 != testG.supplyCount[gold])
    {
        printf("Test 5: failed; supply gold count: %d vs expected: %d\n", g.supplyCount[gold] + 1, testG.supplyCount[gold]);
        failed++;
    }
    else{
        printf("Test 5: passed; correct gold count: %d\n", g.supplyCount[gold]);
    }

    printf("Tests completed! Failed %d tests out of %d\n", failed, totalTests);
    return 0;
}