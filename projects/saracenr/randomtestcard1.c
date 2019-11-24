/*
Baron random testing 
+1 buy
discard estate for +4 coinds
Gain estate if no discard 
*/

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

#define MAX_TRIES 10000

//return # of cards passed in 
int hasCard(int card, int cp, struct gameState *g)
{
    int i;
    int count = 0; 
    for(i = 0; i < g->handCount[cp]; i++)
    {
        if(g->hand[cp][i] == estate)
        {
            count++;
        }
    }
    return count;
}

int main()
{
    int i;
    int totalTests = 15;
    int failed = 0;
    int passed = 0;
    //set card array
    int k[10] = { ambassador, minion, tribute, gardens, mine, remodel, smithy, village, baron, great_hall };

    //declare game state
    struct gameState g, testG;

 
    int seed = 1000;
    int numPlayers, handPos, currentPlayer, choice1, choice2, choice3 = 0;
    printf("\n\nBegin Testing baron:\n");

  

    for(i = 1; i <= MAX_TRIES; i++){
        numPlayers = rand() % (MAX_PLAYERS - 1) + 2;
        initializeGame(numPlayers, k, seed, &g);
        currentPlayer = g.whoseTurn;

        choice1 = rand() % 2;


        //add baron card to last card in hand;

        g.hand[currentPlayer][g.handCount[currentPlayer]] = baron;
        handPos = g.handCount[currentPlayer];
        g.handCount[currentPlayer]++;

        memcpy(&testG, &g, sizeof(struct gameState));
        baronCard(choice1,currentPlayer, &g, handPos);

        if(testG.numBuys + 1 == g.numBuys)
        {
            // printf("Buys expected: %d vs Buys actual: %d\n", testG.numBuys + 1, g.numBuys);
            passed++;
        }
        else{
            printf("Buys expected: %d vs Buys actual: %d\n", testG.numBuys + 1, g.numBuys);
            failed++;
        }

        if(choice1 == 0 && hasCard(estate, currentPlayer, &g))
        {
            if(testG.coins + 4 == g.coins)
            {
                // printf("Coins expected: %d vs Coins actual: %d\n", testG.coins + 4, g.coins);
                passed++;
            }
            else{
                printf("Coins expected: %d vs Coins actual: %d\n", testG.coins + 4, g.coins);
                failed++;
            }
            if(testG.handCount[currentPlayer] + 1 == g.handCount[currentPlayer])
            {
                passed;
            }
            else
            {
                printf("handcount expected: %d vs actual: %d\n", testG.handCount[currentPlayer] + 1, g.handCount[currentPlayer]);
                failed++;
            }
            
        }
        else{
            if(testG.coins == g.coins)
            {
                // printf("Coins expected: %d vs Coins actual: %d\n", testG.coins , g.coins);
                passed++;
            }
            else{
                printf("Coins expected: %d vs Coins actual: %d\n", testG.coins , g.coins);
                failed++;
            }
            if(hasCard(estate, currentPlayer, &testG) + 1 == hasCard(estate, currentPlayer, &g))
            {
                passed;
            }
            else
            {
                printf("estate expected: %d vs estate actual: %d\n", hasCard(estate, currentPlayer, &testG) , hasCard(estate, currentPlayer, &g));
                failed++;
            }

            if(testG.supplyCount[estate] - 1 == g.supplyCount[estate])
            {
                passed;
            }
            else
            {
                printf("supply estate expected: %d vs actual: %d\n", testG.supplyCount[estate] - 1 , g.supplyCount[estate]);
                failed++;
            }
            
            
        }

    }

    

    return 0;
}