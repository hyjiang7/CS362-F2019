/*
Test function: baron
You may discard an Estate for +4, if you don't gain an Estate
compile: make unittest1
1. hand has estate card, and chooses to discard +4 ; supply count unchanged, discard count++; 
2. handpos discarded
3. hand doesn't have estate card, gain estate card to hand, supplycount -1 only
4. numbuy ++
5. player doesn't choose to discard even though they have discard card
*/
#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

void clearHandAndDiscard(struct gameState *g, int cp){
    int i;
    for( i = 0; i < g->handCount[cp]; i++){
            discardCard(0, cp, g, 0);
    }
    g->handCount[cp] = 0;

    for( i = 0; i < g->discardCount[cp]; i++)
    {
        g->discardCount[i] = -1;
    }
    g->discardCount[cp] = 0;

}

int main()
{
    int i;
    int totalTests = 15;
    int failed = 0;
    //set card array
    int k[10] = { ambassador, minion, tribute, gardens, mine, remodel, smithy, village, baron, great_hall };

    //declare game state
    struct gameState g, testG;

    // declare the arrays
    int coppers[MAX_HAND]; int silvers[MAX_HAND]; int golds[MAX_HAND];

    int seed = 1000;
    int numPlayers = 2;
    int handPos = 0;
    int currentPlayer;
    int choice1, choice2, choice3 = 0;
    printf("\n\nBegin Testing baron:\n");

    initializeGame(numPlayers, k, seed, &g);

    printf("-------Test 1: baron card is discarded ----------------------------------------------\n");
    currentPlayer = g.whoseTurn;
    
    clearHandAndDiscard(&g, currentPlayer);

    g.hand[currentPlayer][0] = baron;
    g.handCount[currentPlayer]++;
    g.hand[currentPlayer][1] = estate;
    g.handCount[currentPlayer]++;
    choice1 = 1;
    
    memcpy(&testG, &g, sizeof(struct gameState));
    baronCard(choice1,currentPlayer, &g, handPos);
    if(g.hand[currentPlayer][0] == baron || g.hand[currentPlayer][1] == baron)
    {
        printf("Test1: failed; baron card still in hand\n");
        failed++;
    }
    else{
        printf("Test1: passed; baron card no longer in hand\n");
    }
    
    //discard count should increase by 2, 1 for discarding estate and 1 for baron card discard
    if(g.discardCount[currentPlayer] - 2 != testG.discardCount[currentPlayer])
    {
        printf("Test1: failed; baron card not in discard pile; count = %d\n", g.discardCount[currentPlayer]);
        failed++;
    }
    else {
        printf("Test1: passed; discard pile changed\n");
    }

    printf("-------Test 2: player chooses to discard estate in hand ----------------------------------------------\n");
    currentPlayer = g.whoseTurn;
    
    clearHandAndDiscard(&g, currentPlayer);

    g.hand[currentPlayer][0] = baron;
    g.handCount[currentPlayer]++;
    g.hand[currentPlayer][1] = estate;
    g.handCount[currentPlayer]++;
    g.hand[currentPlayer][2] = gold;
    g.handCount[currentPlayer]++;
    printf("handcount: %d\n", g.handCount[currentPlayer]);
    choice1 = 1;

    memcpy(&testG, &g, sizeof(struct gameState));
    baronCard(choice1,currentPlayer, &g, handPos);

    int estateFound = 0;
    //discard pile should contain estate
    for( i = 0; i < g.discardCount[currentPlayer]; i++)
    {
        if(g.discard[currentPlayer][i] == estate)
        {
            printf("Test2: passed; discard pile changed\n");
            estateFound = 1;
        }
    }
    if(!estateFound)
    {
        printf("Test2: failed; no estate in discard pile\n");
        failed++;
    }

    if(g.numBuys == testG.numBuys + 1)
    {
        printf("Test2: passed; +1 numbuys\n");
    }
    else
    {
        printf("Test2: failed; did not gain 1 numbuys; numBuys = %d\n", g.numBuys);
        failed++;
    }

    if (g.coins == testG.coins + 4)
    {
        printf("Test2: passed; +4 coins\n");
    }
    else
    {
        printf("Test2: failed; did not gain 4 coins; coins = %d vs %d\n", g.coins, testG.coins);
        failed++;
    }

    if(g.hand[currentPlayer][0] == estate || g.hand[currentPlayer][1] == estate)
    {
        printf("Test2: failed; estate card still in hand \n");
        failed++;
    }
    else
    {
        printf("Test2: passed; estate card no longer in hand\n");
    }

    printf("-------Test 3: player chooses to discard estate card with no estate card in hand ----------------------------\n");
    currentPlayer = g.whoseTurn;
    g.supplyCount[estate] = 5; //make sure plenty of estate cards left 
    clearHandAndDiscard(&g, currentPlayer);


    g.hand[currentPlayer][0] = baron;
    g.handCount[currentPlayer]++;
    choice1 = 1;

    memcpy(&testG, &g, sizeof(struct gameState));
    baronCard(choice1,currentPlayer, &g, handPos);
    

    if (g.coins != testG.coins)
    {
        printf("Test3: failed; coins changed \n");
        failed++;
    }
    else
    {
        printf("Test3: passed; did not gain coins\n");
    }

    //estate card in hand from supply 
    //supply count should be -1 
    if(g.hand[currentPlayer][0] == estate || g.hand[currentPlayer][1] == estate)
    {
        printf("Test3: passed; estate card gained from supply");
    }
    else{
        printf("Test3: failed; estate card not gained \n");
        failed++;
    }

    if(g.supplyCount[estate] == 4)
    {
        printf("Test3: passed; estate card taken from supply");
    }
    else{
        printf("Test3: failed; estate supply count incorrect; count is %d\n", g.supplyCount[estate]);
        failed++;
    }

    printf("-------Test 4: player chooses gain estate card even with estate card in hand----------------------------\n");
    currentPlayer = g.whoseTurn;
    
    clearHandAndDiscard(&g, currentPlayer);


    memcpy(&testG, &g, sizeof(struct gameState));
    g.hand[currentPlayer][0] = baron;
    g.handCount[currentPlayer]++;
    g.hand[currentPlayer][1] = estate;
    g.handCount[currentPlayer]++;
    choice1 = 0;
    g.supplyCount[estate] = 5;

    baronCard(choice1,currentPlayer, &g, handPos);
    if (g.coins != testG.coins)
    {
        printf("Test4: failed; coins changed \n");
        failed++;
    }
    else
    {
        printf("Test4: passed; did not gain coins\n");
    }

    //should have 2 estate cards in hand
    int numEstate = 0;
    for( i = 0; i < g.handCount[currentPlayer]; i++){
            if(g.hand[currentPlayer][i] == estate)
            {
                numEstate++;
            }
    }

    if(numEstate == 2)
    {
        printf("Test4: passed; 2 estates in hand\n");
    }
    else
    {
        printf("Test4: failed; incorrect estate card nunmber: %d \n", numEstate);
        failed++;
    }

    if(g.supplyCount[estate] == 4)
    {
        printf("Test4: passed; estate card taken from supply");
    }
    else{
        printf("Test4: failed; estate supply count incorrect; count is %d\n", g.supplyCount[estate]);
        failed++;
    }

    printf("-------Test 5: player chooses gain estate card because no estate card in hand----------------------------\n");
    currentPlayer = g.whoseTurn;
    
    clearHandAndDiscard(&g, currentPlayer);


    memcpy(&testG, &g, sizeof(struct gameState));
    g.hand[currentPlayer][0] = baron;
    g.handCount[currentPlayer]++;
    choice1 = 0;
    g.supplyCount[estate] = 1;

    baronCard(choice1,currentPlayer, &g, handPos);
    if (g.coins != testG.coins)
    {
        printf("Test5: failed; coins changed \n");
        failed++;
    }
    else
    {
        printf("Test5: passed; did not gain coins\n");
    }

    //should have 1 estate cards in hand
    numEstate = 0;
    for( i = 0; i < g.handCount[currentPlayer]; i++){
            if(g.hand[currentPlayer][i] == estate)
            {
                numEstate++;
            }
    }

    if(numEstate == 1)
    {
        printf("Test5: passed; 1 estates in hand\n");
    }
    else
    {
        printf("Test5: failed; incorrect estate card nunmber: %d \n", numEstate);
        failed++;
    }

    if(g.supplyCount[estate] == 0)
    {
        printf("Test5: passed; 1 estate card taken from supply");
    }
    else{
        printf("Test5: failed; estate supply count incorrect; count is %d\n", g.supplyCount[estate]);
        failed++;
    }



    
    printf("Tests completed! Failed %d tests out of %d\n", failed, totalTests);

    return 0;
}