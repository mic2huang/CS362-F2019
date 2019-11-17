/*
 * randomtestcard1.c
 *
 
 */

/*
 * Include the following lines in your makefile:
 *
 * randomtestcard1: randomtestcard1.c dominion.o rngs.o
 *      gcc -o randomtestcard1 -g  randomtestcard1.c dominion.o rngs.o $(CFLAGS)
 */

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>
#include <time.h>

#define TESTFUNC "playBaron()"

int passed = 0;
int discarded = 1;
int xtraCoins = 4;
int xtraBuys = 1;

int estateInHand = 0;
int estateSupplyBefore;

void testPlayBaron(int thisPlayer, int choice1, gameState *testG)
{
    // call the test function
    playBaron(thisPlayer, choice1, testG);

    // check choice
    if (choice1 == 1)
    {
        // check card in hand
        if (estateInHand > 0)
        {
            if ((testG.handCount[thisPlayer], G.handCount[thisPlayer] - discarded) && (testG.coins, G.coins + xtraCoins) && (testG.numBuys, G.numBuys + xtraBuys))
            {
                passed++;
            }
        }
        else
        {

            if ((testG.supplyCount[estate], estateSupplyBefore - 1) && (testG.numBuys, G.numBuys + xtraBuys))
            {
                passed++;
            }
        }
    }
    else // choice1 = 0
    {

        if ((testG.supplyCount[estate], 0) && (testG.numBuys, G.numBuys + xtraBuys))
        {
            passed++;
        }
    }
}

int main()
{
    struct gameState G, testG;
    int choice1 = 0;
    int seed = 1000;
    int numPlayers = 2;
    int thisPlayer = 0;
    int i;

    int k[10] = {baron, ambassador, estate, embargo, village, minion, mine, cutpurse,
                 sea_hag, tribute};
    // initialize a game state and player cards
    initializeGame(numPlayers, k, seed, &G);

    srand(time(NULL));

    printf("----------------- Testing function: %s ----------------\n", TESTFUNC);

    // copy the game state to a test case
    memcpy(&testG, &G, sizeof(struct gameState));

    // generate random choice
    choice1 = rand() % 2;

    // generate random number of supply Estate
    testG.supplyCount[estate] = rand() % 8 + 1;
    estateSupplyBefore = testG.supplyCount[estate];

    // generate random number of estate card in hand
    estateInHand = rand() % 5;

    if (estateInHand > 0)
    {
        testG.hand[thisPlayer][estateInHand] = estate;
    }
    else
    {
        // remove estate card in current player's hand
        testG.hand[thisPlayer][0] = ambassador;
        testG.hand[thisPlayer][1] = copper;
        testG.hand[thisPlayer][2] = duchy;
        testG.hand[thisPlayer][3] = ambassador;
        testG.hand[thisPlayer][4] = feast;
    }

    int iterations = 10000;
    for (i = 0; i < iterations; i++)
    {
        testPlayBaron(thisPlayer, choice1, &testG);
    }
    printf("# Passed Tests: %i\n", passed);
    printf("# Failed Tests: %i\n", iterations - passed);
    printf("\n >>>>> SUCCESS: Testing complete %s <<<<<\n\n", TESTFUNC);

    return 0;
}