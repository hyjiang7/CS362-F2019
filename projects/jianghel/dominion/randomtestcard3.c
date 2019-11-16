/*

tribute:
left player reveals top 2 cards from deck 
action card +2 actions #3
treasury +2 coins #2
victory +2 cards  #1
*/
#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

#define MAX_TRIES 10000


int cardType(int card)
{
    if(card > 0 && card < 27 )
    {
        if(card < 4 || card == gardens || card == great_hall)
        {
            return 1;
        }
        else if (card > 3 && card < 7)
        {
            return 2;
        }
        else{
            return 3;
        }
    }

    return -1;
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
    printf("\n\nBegin Testing tribute:\n");

    for (i = 1; i <= MAX_TRIES; i++)
    {
        numPlayers = rand() % (MAX_PLAYERS - 1) + 2;
        initializeGame(numPlayers, k, seed, &g);
        currentPlayer = g.whoseTurn;

        g.hand[currentPlayer][g.handCount[currentPlayer]] = tribute;
        handPos = g.handCount[currentPlayer];
        g.handCount[currentPlayer]++;

        int nextPlayer = currentPlayer == 0 ? numPlayers - 1 : currentPlayer - 1;

        //randomize the cards the player's deck and discard piles and count
        g.deckCount[nextPlayer] = rand() % 5;
        for(int k = 0; k < g.deckCount[nextPlayer]; k++)
        {
            g.deck[nextPlayer][k] = rand() % 27;
        }

        g.discardCount[nextPlayer] = rand() % 5;
        for(int k = 0; k < g.discardCount[nextPlayer]; k++)
        {
            g.discard[nextPlayer][k] = rand() % 27;
        }

        memcpy(&testG, &g, sizeof(struct gameState));
        tributeAction(handPos, currentPlayer, &g);

        int card1, card2 = 0;
        //only 1 card to reveal 
        if ((testG.discardCount[nextPlayer] + testG.deckCount[nextPlayer]) < 2)
        {
            //player has 1 card in deck, reveal that card and discard
            if (testG.deckCount[nextPlayer] > 0)
            {
                card1 = cardType(testG.deck[nextPlayer][0]);
            }
            //player has 1 card in discard pile, reveal and discard card
            else if (testG.discardCount[nextPlayer] > 0)
            {
                    card1 = cardType(testG.discard[nextPlayer][0]);
            }
            //no cards to reveal ... all conditions remain the same
            else
            {
                    card1 = -1;
            }    
                
        }
        else {
            if(testG.deckCount[nextPlayer] == 1)
            {
                card1 = testG.deck[nextPlayer][0];
                card2 = testG.discard[nextPlayer][0];
            }
            else
            {
                card1 = testG.deck[nextPlayer][0];
                card2 = testG.deck[nextPlayer][1];
            }
        }

        if(card1 == card2)
        {
           if (card1 == 1)
            {
                //plus 2 cards
                if(testG.handCount[currentPlayer] + 1 == g.handCount[currentPlayer])
                {
                    passed++;
                }
                else 
                {
                    printf("Cards expected: %d vs actual: %d\n", testG.handCount[currentPlayer] + 1, g.handCount[currentPlayer]);
                    failed++;
                }
            }
            else if (card1 == 2)
            {
                //+2 coins
                if (testG.numActions + 2 == g.numActions)
                {
                    passed++;
                }
                else
                {
                    printf("Coins expected: %d vs actual: %d\n", testG.coins + 2, g.coins);
                    failed++;
                }
            }
            else if(card1 == 3)
            {
                //+2 actions
                if (testG.numActions + 2 == g.numActions)
                {
                    passed++;
                }
                else
                {
                    printf("Actions expected: %d vs actual: %d\n", testG.numActions + 2, g.numActions);
                    failed++;
                }
            }
            else
            {
                //no change
                if (testG.numActions == g.numActions)
                {
                    passed++;
                }
                else
                {
                    printf("Actions expected: %d vs actual: %d\n", testG.numActions, g.numActions);
                    failed++;
                }

                if (testG.coins == g.coins)
                {
                    passed++;
                }
                else
                {
                    printf("Coins expected: %d vs actual: %d\n", testG.coins , g.coins);
                    failed++;
                }
            }
        }
        else
        {
            if(card1 == 1 && card2 == 2)
            {
                if(testG.handCount[currentPlayer] + 1 == g.handCount[currentPlayer])
                {
                    passed++;
                }
                else 
                {
                    printf("Cards expected: %d vs actual: %d\n", testG.handCount[currentPlayer] + 1, g.handCount[currentPlayer]);
                    failed++;
                }
                if (testG.numActions + 2 == g.numActions)
                {
                    passed++;
                }
                else
                {
                    printf("Coins expected: %d vs actual: %d\n", testG.coins + 2, g.coins);
                    failed++;
                }
            }
            else if(card1 == 1 && card2 == 3)
            {
                if(testG.handCount[currentPlayer] + 1 == g.handCount[currentPlayer])
                {
                    passed++;
                }
                else 
                {
                    printf("Cards expected: %d vs actual: %d\n", testG.handCount[currentPlayer] + 1, g.handCount[currentPlayer]);
                    failed++;
                }
                if (testG.numActions + 2 == g.numActions)
                {
                    passed++;
                }
                else
                {
                    printf("Actions expected: %d vs actual: %d\n", testG.numActions + 2, g.numActions);
                    failed++;
                }
            }
            else if(card1 == 2 && card2 == 3)
            {
                if (testG.numActions + 2 == g.numActions)
                {
                    passed++;
                }
                else
                {
                    printf("Coins expected: %d vs actual: %d\n", testG.coins + 2, g.coins);
                    failed++;
                }
                if (testG.numActions + 2 == g.numActions)
                {
                    passed++;
                }
                else
                {
                    printf("Actions expected: %d vs actual: %d\n", testG.numActions + 2, g.numActions);
                    failed++;
                }
            }
            
        }
        
    }
        printf("Tribute Test Summary: Passed: %d vs Failed: %d\n", passed, failed);

    return 0;

}