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

int passed = 0, failed = 0, handCountFailed = 0, coinsFailed = 0, numBuysFailed = 0, supplyCountFailed = 0;
int discarded = 1;
int xtraCoins = 4;
int xtraBuys = 1;

int estateInHand = 0;
int estateSupplyBefore;

void testPlayBaron(int thisPlayer, int choice1, struct gameState *testG, struct gameState *G)
{
    // call the test function
    playBaron(testG, choice1);
    int thisTestResult = 1;
    // check choice
    if (choice1 == 1)
    {
        // check card in hand
        if (estateInHand > 0)
        {
            if (testG->handCount[thisPlayer] != G->handCount[thisPlayer] - discarded)
            {
                handCountFailed++;
                thisTestResult = 0;
            }

            if (testG->coins != G->coins + xtraCoins)
            {
                coinsFailed++;
                thisTestResult = 0;
            }

            if (testG->numBuys != G->numBuys + xtraBuys)
            {
                numBuysFailed++;
                thisTestResult = 0;
            }

            if (thisTestResult)
            {
                passed++;
            }
            else
            {
                failed++;
            }
        }
        else
        {
            if (testG->supplyCount[estate] != estateSupplyBefore - 1)
            {
                supplyCountFailed++;
                thisTestResult = 0;
            }

            if (testG->numBuys != G->numBuys + xtraBuys)
            {
                numBuysFailed++;
                thisTestResult = 0;
            }

            if (thisTestResult)
            {
                passed++;
            }
            else
            {
                failed++;
            }
        }
    }
    else // choice1 = 0
    {
        if (testG->supplyCount[estate] != estateSupplyBefore - 1)
        {
            supplyCountFailed++;
            thisTestResult = 0;
        }

        if (testG->numBuys != G->numBuys + xtraBuys)
        {
            numBuysFailed++;
            thisTestResult = 0;
        }

        if (thisTestResult)
        {
            passed++;
        }
        else
        {
            failed++;
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

    int iterations = 10000;
    for (i = 0; i < iterations; i++)
    {
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
        testPlayBaron(thisPlayer, choice1, &testG, &G);
    }
    printf("# total Tests: %d\n", passed + failed);
    printf("# Passed Tests: %d\n", passed);
    printf("# Failed Tests: %d\n", failed);
    printf("# handCountFailed: %d\n", handCountFailed);
    printf("# coinsFailed: %d\n", coinsFailed);
    printf("# numBuysFailed: %d\n", numBuysFailed);
    printf("# supplyCountFailed: %d\n", supplyCountFailed);
    printf("\n >>>>> SUCCESS: Testing complete %s <<<<<\n\n", TESTFUNC);

    return 0;
}