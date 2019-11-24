/*
Test function: mine
compile: make unittest1
*/

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>


int main(){
    int i;
    int totalTests = 11;
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
    int choice1, choice2, choice3 = 0;
    printf("Begin Testing mine:\n");

    initializeGame(numPlayers, k, seed, &g);

    printf("Test 1: choice 1 isn't a treasure card ----------------------------------------------\n");
    int currentPlayer = g.whoseTurn;
    
    for(i =0; i < g.handCount[currentPlayer]; i++){
            discardCard(0, currentPlayer, &g, 0);
    }
    g.handCount[currentPlayer] = 0;

    g.hand[currentPlayer][0] = mine;
    g.handCount[currentPlayer]++;
    g.hand[currentPlayer][1] = adventurer;
    g.handCount[currentPlayer]++;
    choice1 = 1;

    int r= mineCard(choice1, choice2, currentPlayer, &g, handPos);
    if(r == -1)
    {
        printf("Test 1 passed; returned -1\n");
        
    }
    else 
    {
        printf("Test 1 failed; returned 0\n");
        failed++;
    }


    printf("Test 2: choice 2 costs more than 3 of choice 1 ----------------------------------------------\n");

    currentPlayer = g.whoseTurn;
    for( i = 0; i < g.handCount[currentPlayer]; i++){
            discardCard(0, currentPlayer, &g, 0);
    }
    g.handCount[currentPlayer] = 0;
    
    g.hand[currentPlayer][0] = mine;
    g.handCount[currentPlayer]++;
    g.hand[currentPlayer][1] = copper;
    g.handCount[currentPlayer]++;
    choice1 = 1;
    choice2 = gold;

    r = mineCard(choice1, choice2, currentPlayer, &g, handPos);
    if(r == -1)
    {
        printf("Test 2 passed; returned -1\n");
        
    }
    else 
    {
        printf("Test 2 failed; returned 0\n");
        failed++;
    }

    if(g.hand[currentPlayer][0] == gold || g.hand[currentPlayer][1] == gold || g.hand[currentPlayer][2] == gold)
    {
        printf("Test 2 failed; gold gained 0\n");
        failed++;
    }
    else
    {
        printf("Test 2 passed; card not gained\n");
    }
    

    printf("Test 3: valid choice 2 and choice1----------------------------------------------\n");
    currentPlayer = g.whoseTurn;
    for( i = 0; i < g.handCount[currentPlayer]; i++){
            discardCard(0, currentPlayer, &g, 0);
    }
    g.handCount[currentPlayer] = 0;
    
    memcpy(&testG, &g, sizeof(struct gameState));

    g.hand[currentPlayer][0] = mine;
    g.handCount[currentPlayer]++;
    g.hand[currentPlayer][1] = copper;
    g.handCount[currentPlayer]++;
    choice1 = 1;
    choice2 = silver;

    r = mineCard(choice1, choice2, currentPlayer, &g, handPos);
    if(r == -1)
    {
        printf("Test 3 failed; exited before gaining card\n");
        failed++;
    }
    else{
        printf("Test 3 passed; did not return before gaining card\n");
    }

    if (g.hand[currentPlayer][0] != silver && g.hand[currentPlayer][1] != silver && g.hand[currentPlayer][2] != silver)
    {
        printf("Test 3 failed; didnt gain card into hand\n");
        failed++;
    }
    else{
        printf("Test 3 passed; gained card onto hand\n");
    }

    if(testG.supplyCount[silver] == g.supplyCount[silver])
    {
        printf("Test 3 failed; didn't subtract card from supply\n");
        failed++;
    }
    else{
        printf("Test 3 passed; subtracted choice2 from supply\n");
    }


    printf("Test 4: choice 1 is actually trashed----------------------------------------------\n");
    currentPlayer = g.whoseTurn;
    for( i = 0; i < g.handCount[currentPlayer]; i++){
            discardCard(0, currentPlayer, &g, 0);
    }
    g.handCount[currentPlayer] = 0;
    g.supplyCount[copper]--;
    memcpy(&testG, &g, sizeof(struct gameState));

    g.hand[currentPlayer][0] = mine;
    g.handCount[currentPlayer]++;
    g.hand[currentPlayer][1] = copper;
    g.handCount[currentPlayer]++;
    choice1 = 1;
    choice2 = silver;

    mineCard(choice1, choice2, currentPlayer, &g, handPos);
    if(g.discardCount + 1 != testG.discardCount)
    {
        printf("Test 4 failed; discardCount changed\n");
        failed++;
    }
    else{
        printf("Test 4 passed; discardCount fine\n");
    }


    if(g.supplyCount[copper] != testG.supplyCount[copper])
    {
        printf("Test 4 failed; supplyCount changed\n");
        failed++;
    }
    else{
        printf("Test 4 passed; supplyCount fine\n");
    }


    if(g.hand[currentPlayer][0] == copper || g.hand[currentPlayer][1] == copper || g.hand[currentPlayer][2] == copper)
    {
        printf("Test 4 failed; choice 1 is in hand\n");
        failed++;
    }
    else{
        printf("Test 4 passed; choice1 not in hand\n");
    }

    printf("Test 5: choice 2 is not treasure card----------------------------------------------\n");
    currentPlayer = g.whoseTurn;
    for( i = 0; i < g.handCount[currentPlayer]; i++){
            discardCard(0, currentPlayer, &g, 0);
    }
    g.handCount[currentPlayer] = 0;

    g.hand[currentPlayer][0] = mine;
    g.handCount[currentPlayer]++;
    g.hand[currentPlayer][1] = silver;
    g.handCount[currentPlayer]++;
    choice1 = 1;
    choice2 = adventurer;
    r = mineCard(choice1, choice2, currentPlayer, &g, handPos);
    if(r == -1)
    {
        printf("Test 5 passed; returned -1\n");
        
    }
    else 
    {
        printf("Test 5 failed; returned 0\n");
        failed++;
    }

    if(g.hand[currentPlayer][0] == adventurer || g.hand[currentPlayer][1] == adventurer || g.hand[currentPlayer][2] == adventurer)
    {
        printf("Test 5 failed; card gained to hand\n");
        failed++;
    }
    else
    {
         printf("Test 5 passed; card not gained 0\n");
    }
    

    
    printf("Tests completed! Failed %d tests out of %d\n", failed, totalTests);
    return 0;
}

/*
1. Player doesn't have treasure card...do not gain any extra cards 
2. Player trashes Cooper, gain Silver or Copper to hand. Supply count of gained card decreases. 
3. Player trashes Silver to gain a Gold or Silver or Copper to hand. Supply count of gained card decreases. 
4. Picked card is actually trashed. nothing gained in supply, discard or other piles
5. Mine card is actually discarded int discard pile
*/