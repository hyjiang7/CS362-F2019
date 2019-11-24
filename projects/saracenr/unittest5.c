/*
1. Revealed cards are same
2. Revealed cards are not same 
3. Player doesn't have 2 cards in hand
4. Player does have 2 cards in hand 
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

void clearDeck(struct gameState *g, int cp)
{
    int i;
    for (i = 0; i < g->deckCount[cp]; i++)
    {
        discardCard(0, cp, g, 0);
    }
    g->deckCount[cp] = 0;
}

void clearDiscard(struct gameState *g, int cp)
{
    int i;
    for (i = 0; i < g->discardCount[cp]; i++)
    {
        discardCard(0, cp, g, 0);
    }
    g->discardCount[cp] = 0;
}

int main(){
    int i;
    int totalTests = 17;
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
    printf("\n\nBegin Testing tribute:\n");

    initializeGame(numPlayers, k, seed, &g);

    printf("-------Test 1: tribute Left player has 2 cards in deck of same type--------------------------\n");
    //player should get +2 gold and nothing else changes 
    currentPlayer = g.whoseTurn;

    clearHand(&g, currentPlayer);
    g.hand[currentPlayer][0] = tribute;
    g.handCount[currentPlayer]++;

    int nextPlayer = currentPlayer == 0 ? numPlayers - 1 : currentPlayer - 1;
    clearDeck(&g, nextPlayer);
    g.deck[nextPlayer][0] = silver;
    g.deck[nextPlayer][1] = gold;
    g.deckCount[nextPlayer] += 2;

    memcpy(&testG, &g, sizeof(struct gameState));
    int r = tributeCard(choice1, currentPlayer, nextPlayer, &g, handPos);

    if(g.coins -2 == testG.coins)
    {
        printf("Test 1: passed; coins: %d vs expected: %d\n", g.coins, testG.coins + 2);
    }
    else{
        printf("Test 1: failed; coins: %d vs expected: %d\n", g.coins, testG.coins + 2);
        failed++;
    }

    if(g.handCount[currentPlayer] + 1 == testG.handCount[currentPlayer])
    {
        printf("Test 1: passed; handCount: %d vs expected: %d\n", g.handCount[currentPlayer], testG.handCount[currentPlayer] - 1);
    }
    else{
        printf("Test 1: failed; handCount: %d vs expected: %d\n", g.handCount[currentPlayer], testG.handCount[currentPlayer] - 1);
        failed++;
    }

    if(g.numActions == testG.numActions)
    {
        printf("Test 1: passed; actions: %d vs expected: %d\n", g.numActions, testG.numActions);
    }
    else{
        printf("Test 1: failed; actions: %d vs expected: %d\n", g.numActions, testG.numActions);
        failed++;
    }

    if(g.deckCount[nextPlayer] == 0)
    {
        printf("Test 1: passed; deckCount: %d vs expected: 0\n", g.deckCount[nextPlayer]);
    }
    else{
        printf("Test 1: failed; deckCount: %d vs expected: 0\n", g.deckCount[nextPlayer]);
        failed++;
    }

    printf("-------Test 2: tribute Left player has 1 card in deck and 1 card in discard with different types--------\n");
    //player should get +2 gold and nothing else changes 
    currentPlayer = g.whoseTurn;

    clearHand(&g, currentPlayer);
    g.hand[currentPlayer][0] = tribute;
    g.handCount[currentPlayer]++;

    nextPlayer = currentPlayer == 0 ? numPlayers - 1 : currentPlayer - 1;
    clearDeck(&g, nextPlayer);
    g.deck[nextPlayer][0] = silver;
    g.deckCount[nextPlayer] ++;

    clearDiscard(&g, nextPlayer);
    g.discard[nextPlayer][0] = estate;
    g.discardCount[nextPlayer]++;

    memcpy(&testG, &g, sizeof(struct gameState));
    r = tributeCard(choice1, currentPlayer, nextPlayer, &g, handPos);

    if(g.coins -2 == testG.coins)
    {
        printf("Test 2: passed; coins: %d vs expected: %d\n", g.coins, testG.coins + 2);
    }
    else{
        printf("Test 2: failed; coins: %d vs expected: %d\n", g.coins, testG.coins + 2);
        failed++;
    }

     if(g.handCount[currentPlayer] - 1 == testG.handCount[currentPlayer])
    {
        printf("Test 2: passed; handCount: %d vs expected: %d\n", g.handCount[currentPlayer], testG.handCount[currentPlayer] + 1);
    }
    else{
        printf("Test 2: failed; handCount: %d vs expected: %d\n", g.handCount[currentPlayer], testG.handCount[currentPlayer] + 1);
        failed++;
    }

    if(g.numActions == testG.numActions)
    {
        printf("Test 2: passed; actions: %d vs expected: %d\n", g.numActions, testG.numActions);
    }
    else{
        printf("Test 2: failed; actions: %d vs expected: %d\n", g.numActions, testG.numActions);
        failed++;
    }

    if(g.deckCount[nextPlayer] == 0)
    {
        printf("Test 2: passed; deckCount: %d vs expected: 0\n", g.deckCount[nextPlayer]);
    }
    else{
        printf("Test 2: failed; deckCount: %d vs expected: 0\n", g.deckCount[nextPlayer]);
        failed++;
    }

    if(g.discardCount[nextPlayer] == 0)
    {
        printf("Test 2: passed; discardCount: %d vs expected: 0\n", g.discardCount[nextPlayer]);
    }
    else{
        printf("Test 2: failed; discardCount: %d vs expected: 0\n", g.discardCount[nextPlayer]);
        failed++;
    }

    printf("-------Test 3: tribute Left player has 1 card in deck only------------\n");
    //player should get +2 gold and nothing else changes 
    currentPlayer = g.whoseTurn;

    clearHand(&g, currentPlayer);
    g.hand[currentPlayer][0] = tribute;
    g.handCount[currentPlayer]++;

    nextPlayer = currentPlayer == 0 ? numPlayers - 1 : currentPlayer - 1;
    clearDeck(&g, nextPlayer);
    g.deck[nextPlayer][0] = gardens;
    g.deckCount[nextPlayer] ++;

    clearDiscard(&g, nextPlayer);

    memcpy(&testG, &g, sizeof(struct gameState));
    r = tributeCard(choice1, currentPlayer, nextPlayer, &g, handPos);

    if(g.coins  == testG.coins)
    {
        printf("Test 3: passed; coins: %d vs expected: %d\n", g.coins, testG.coins );
    }
    else{
        printf("Test 3: failed; coins: %d vs expected: %d\n", g.coins, testG.coins );
        failed++;
    }

     if(g.handCount[currentPlayer]  == testG.handCount[currentPlayer])
    {
        printf("Test 3: passed; handCount: %d vs expected: %d\n", g.handCount[currentPlayer], testG.handCount[currentPlayer]);
    }
    else{
        printf("Test 3: failed; handCount: %d vs expected: %d\n", g.handCount[currentPlayer], testG.handCount[currentPlayer]);
        failed++;
    }

    if(g.numActions == testG.numActions)
    {
        printf("Test 3: passed; actions: %d vs expected: %d\n", g.numActions, testG.numActions);
    }
    else{
        printf("Test 3: failed; actions: %d vs expected: %d\n", g.numActions, testG.numActions);
        failed++;
    }

    if(g.deckCount[nextPlayer] == 0)
    {
        printf("Test 3: passed; deckCount: %d vs expected: 0\n", g.deckCount[nextPlayer]);
    }
    else{
        printf("Test 3: failed; deckCount: %d vs expected: 0\n", g.deckCount[nextPlayer]);
        failed++;
    }

    printf("-------Test 4: player has no cards to reveal--------\n");
    //player should get +2 gold and nothing else changes 
    currentPlayer = g.whoseTurn;

    clearHand(&g, currentPlayer);
    g.hand[currentPlayer][0] = tribute;
    g.handCount[currentPlayer]++;

    nextPlayer = currentPlayer == 0 ? numPlayers - 1 : currentPlayer - 1;
    clearDeck(&g, nextPlayer);

    clearDiscard(&g, nextPlayer);

    memcpy(&testG, &g, sizeof(struct gameState));
    r = tributeCard(choice1, currentPlayer, nextPlayer, &g, handPos);

    if(g.coins  == testG.coins)
    {
        printf("Test 4: passed; coins: %d vs expected: %d\n", g.coins, testG.coins );
    }
    else{
        printf("Test 4: failed; coins: %d vs expected: %d\n", g.coins, testG.coins );
        failed++;
    }

     if(g.handCount[currentPlayer] + 1 == testG.handCount[currentPlayer])
    {
        printf("Test 4: passed; handCount: %d vs expected: %d\n", g.handCount[currentPlayer], testG.handCount[currentPlayer] - 1);
    }
    else{
        printf("Test 4: failed; handCount: %d vs expected: %d\n", g.handCount[currentPlayer], testG.handCount[currentPlayer] - 1);
        failed++;
    }

    if(g.numActions == testG.numActions)
    {
        printf("Test 4: passed; actions: %d vs expected: %d\n", g.numActions, testG.numActions);
    }
    else{
        printf("Test 4: failed; actions: %d vs expected: %d\n", g.numActions, testG.numActions);
        failed++;
    }

    if(g.deckCount[nextPlayer] == 0)
    {
        printf("Test 4: passed; deckCount: %d vs expected: 0\n", g.deckCount[nextPlayer]);
    }
    else{
        printf("Test 4: failed; deckCount: %d vs expected: 0\n", g.deckCount[nextPlayer]);
        failed++;
    }

     printf("Tests completed! Failed %d tests out of %d\n\n\n", failed, totalTests);
    return 0;
}