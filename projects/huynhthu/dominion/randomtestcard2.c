/*
 * randomtestcard2.c
 *
 
 */

/*
 * Include the following lines in your makefile:
 *
 * randomtestcard2: randomtestcard2.c dominion.o rngs.o
 *      gcc -o randomtestcard2 -g  randomtestcard2.c dominion.o rngs.o $(CFLAGS)
 */

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>
#include <time.h>

#define TESTFUNC "playMinion()"

int passed = 0, handCountFailed = 0, coinsFailed = 0, numActionsFailed = 0, otherHandCountFailed = 0;
int discarded = 1;
int xtraCoins = 2;
int xtraActions = 1;

void testPlayMinion(int thisPlayer, int choice1, int choice2, struct gameState *testG, struct gameState *G, int handpos)
{
    // call the test function
    playMinion(thisPlayer, choice1, choice2, testG, handpos);

    int thisTestResult = 1;
    // check choice
    if (choice1 == 1 && choice2 == 0)
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

        if (testG->numActions != G->numActions + xtraActions)
        {
            numActionsFailed++;
            thisTestResult = 0;
        }

        if (thisTestResult)
        {
            passed++;
        }
    }
    else if (choice1 == 0 && choice2 == 1 && testG->handCount[thisPlayer + 1] >= 5)
    {
        if (testG->coins != G->coins + xtraCoins)
        {
            coinsFailed++;
            thisTestResult = 0;
        }

        if (testG->numActions != G->numActions + xtraActions)
        {
            numActionsFailed++;
            thisTestResult = 0;
        }

        if (testG->handCount[thisPlayer + 1] != 4)
        {
            otherHandCountFailed++;
            thisTestResult = 0;
        }

        if (thisTestResult)
        {
            passed++;
        }
    }
}

int main()
{

    int choice1 = 0, choice2 = 0, handpos = 0;
    int seed = 1000;
    int numPlayers = 2;
    int thisPlayer = 0;
    struct gameState G, testG;
    int i;
    int k[10] = {baron, ambassador, adventurer, embargo, village, minion, mine, cutpurse,
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
        choice2 = rand() % 2;

        // generate other player's handCount
        testG.handCount[thisPlayer + 1] = rand() % 10;

        testPlayMinion(thisPlayer, choice1, choice2, &testG, &G, handpos);
    }
    printf("# Passed Tests: %i\n", passed);
    printf("# Failed Tests: %i\n", iterations - passed);
    printf("# handCountFailed: %i\n", handCountFailed);
    printf("# coinsFailed: %i\n", coinsFailed);
    printf("# numActionsFailed: %i\n", numActionsFailed);
    printf("# otherHandCountFailed: %i\n", otherHandCountFailed);
    printf("\n >>>>> SUCCESS: Testing complete %s <<<<<\n\n", TESTFUNC);

    return 0;
}