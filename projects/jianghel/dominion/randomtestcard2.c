/*

minion: 
+1 action
choice 1: +2 coins
choice 2:
+4 cards for players with 5 cards in hand

*/
#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

#define MAX_TRIES 10000

//returns 1 if same
//returns 0 if not same
int compareHands(int player, struct gameState *test, struct gameState *g)
{
    int i;

    for (i = 0; i < g->handCount[player]; i++)
    {
        if (test->hand[player][i] != g->hand[player][i])
        {
            return 0;
        }
    }

    return 1;
}

int main()
{
    int i;
    int totalTests = 15;
    int failed = 0;
    int passed = 0;
    //set card array
    int k[10] = {ambassador, minion, tribute, gardens, mine, remodel, smithy, village, baron, great_hall};

    //declare game state
    struct gameState g, testG;

    int seed = 1000;
    int numPlayers, handPos, currentPlayer, choice1, choice2, choice3 = 0;
    printf("\n\nBegin Testing minion:\n");

    for (i = 1; i <= MAX_TRIES; i++)
    {
        numPlayers = rand() % (MAX_PLAYERS - 1) + 2;
        initializeGame(numPlayers, k, seed, &g);
        currentPlayer = g.whoseTurn;

        choice1 = rand() % 2;
        if (choice1 == 0)
        {
            choice2 = 1;
        }
        else
        {
            choice2 = 0;
        }

        //add baron card to last card in hand;

        g.hand[currentPlayer][g.handCount[currentPlayer]] = baron;
        handPos = g.handCount[currentPlayer];
        g.handCount[currentPlayer]++;

        memcpy(&testG, &g, sizeof(struct gameState));
        minionAction(handPos, currentPlayer, choice1, choice2, &g);

        if (testG.numActions + 1 == g.numActions)
        {
            passed++;
        }
        else
        {
            printf("Actions expected: %d vs actual: %d\n", testG.numActions + 1, g.numActions);
            failed++;
        }

        if (choice1)
        {
            if (testG.coins + 2 == g.coins)
            {
                passed++;
            }
            else
            {
                printf("Coins expected: %d vs Coins actual: %d\n", testG.coins + 2, g.coins);
                failed++;
            }
        }
        else
        {
            if (testG.coins == g.coins)
            {
                // printf("Coins expected: %d vs Coins actual: %d\n", testG.coins + 4, g.coins);
                passed++;
            }
            else
            {
                printf("Coins expected: %d vs Coins actual: %d\n", testG.coins, g.coins);
                failed++;
            }
            //find players with 5 cards in testG
            //test to see if these cards match ...if so, then fail
            //find players with 4 cards in testG
            //if cards match...fail

            //current player is different
            int j;

            for (j = 0; j < numPlayers; j++)
            {
                if (testG.handCount[i] > 5)
                {
                    if (compareHands(j, &testG, &g))
                    {
                        failed++;
                    }
                    else
                    {
                        passed++;
                    }
                }
                else
                {
                    if(j != currentPlayer)
                    {
                        if (compareHands(j, &testG, &g))
                        {
                            passed++;
                        }
                        else
                        {
                            failed++;
                        }
                    }
                    
                }

                
            }
        }
    }

    printf("Baron Test Summary: Passed: %d vs Failed: %d\n", passed, failed);
    return 0;
}