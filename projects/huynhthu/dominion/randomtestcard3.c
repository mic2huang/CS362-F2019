/*
 * randomtestcard3.c
 *
 
 */

/*
 * Include the following lines in your makefile:
 *
 * randomtestcard3: randomtestcard3.c dominion.o rngs.o
 *      gcc -o randomtestcard3 -g  randomtestcard3.c dominion.o rngs.o $(CFLAGS)
 */

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>
#include <time.h>

#define TESTFUNC "playTribute()"

int passed = 0, failed = 0, handCountFailed = 0, discardCountFailed = 0, deckCountFailed = 0, coinsFailed = 0, actionsFailed = 0;
int xtraCoins = 2;
int xtraCards = 2;
int xtraActions = 2;
int discardCountBefore = 0, deckCountBefore = 0;
int tributeRevealedCards[2] = {-1, -1};

void testPlayTribute(int thisPlayer, int nextPlayer, struct gameState *testG, struct gameState *G)
{
    printf("BEGIN\n");
    int handCountExpected = G->handCount[thisPlayer];
    printf("handCountExpected = %d\n", handCountExpected);
    int discardCardCountExpected = discardCountBefore;
    printf("discardCardCountExpected = %d\n", discardCardCountExpected);
    int deckCountExpected = deckCountBefore;
    printf("deckCountExpected = %d\n", deckCountExpected);
    int coinsExpected = G->coins;
    printf("coinsExpected = %d\n", coinsExpected);
    int actionsExpected = G->numActions;
    printf("actionsExpected = %d\n\n", actionsExpected);

    int thisTestResult = 1;
    // check deckCount and discardCount to get revealed cards
    if ((testG->discardCount[nextPlayer] + testG->deckCount[nextPlayer]) <= 1)
    {
        if (testG->deckCount[nextPlayer] > 0)
        {
            tributeRevealedCards[0] = testG->deck[nextPlayer][testG->deckCount[nextPlayer] - 1];
        }
        else if (testG->discardCount[nextPlayer] > 0)
        {
            tributeRevealedCards[0] = testG->discard[nextPlayer][testG->discardCount[nextPlayer] - 1];
        }
    }
    else
    {
        if (testG->deckCount[nextPlayer] == 0)
        {
            for (int i = 0; i < 2; i++)
            {
                tributeRevealedCards[i] = testG->discard[nextPlayer][i];
            }
        }
        else
        {
            for (int i = 0; i < 2; i++)
            {
                tributeRevealedCards[i] = testG->deck[nextPlayer][testG->deckCount[nextPlayer] - (i + 1)];
            }
        }
    }

    // call the test function
    playTribute(thisPlayer, nextPlayer, testG);

    // check revealed cards
    for (int i = 0; i < 2; i++)
    {
        if (tributeRevealedCards[i] > -1)
        {
            // reveal treasure card
            if ((tributeRevealedCards[i] == copper || tributeRevealedCards[i] == silver || tributeRevealedCards[i] == gold))
            {
                deckCountExpected--;
                coinsExpected += xtraCoins;
                printf("TREASURE\n");
            }

            // reveal victory card
            else if ((tributeRevealedCards[i] == estate || tributeRevealedCards[i] == duchy || tributeRevealedCards[i] == province || tributeRevealedCards[i] == gardens || tributeRevealedCards[i] == great_hall))
            {
                discardCardCountExpected--;
                handCountExpected += xtraCards;
                printf("VIC\n");
            }

            // reveal action card
            else
            {
                discardCardCountExpected--;
                actionsExpected += xtraActions;
                printf("ACTION\n");
            }
        }
    }

    // test result
    if (testG->deckCount[nextPlayer] != deckCountExpected)
    {
        deckCountFailed++;
        thisTestResult = 0;
        printf("testG->deckCount[nextPlayer] = %d\n", testG->deckCount[nextPlayer]);
        printf("deckCountExpected = %d\n", deckCountExpected);
    }

    if (testG->coins != coinsExpected)
    {
        coinsFailed++;
        thisTestResult = 0;
        printf("testG->coins = %d\n", testG->coins);
        printf("coinsExpected = %d\n", coinsExpected);
    }

    if (testG->discardCount[nextPlayer] != discardCardCountExpected)
    {
        discardCountFailed++;
        thisTestResult = 0;
        printf("testG->discardCount[nextPlayer] = %d\n", testG->discardCount[nextPlayer]);
        printf("discardCardCountExpected = %d\n", discardCardCountExpected);
    }

    if (testG->handCount[thisPlayer] != handCountExpected)
    {
        handCountFailed++;
        thisTestResult = 0;
        printf("testG->handCount[thisPlayer] = %d\n", testG->handCount[thisPlayer]);
        printf("handCountExpected = %d\n", handCountExpected);
    }

    if (testG->numActions != actionsExpected)
    {
        actionsFailed++;
        thisTestResult = 0;
        printf("testG->numActions = %d\n", testG->numActions);
        printf("actionsExpected = %d\n\n", actionsExpected);
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

int main()
{

    int seed = 1000;
    int numPlayers = 2;
    int thisPlayer = 0;
    int nextPlayer = thisPlayer + 1;
    struct gameState G, testG;
    int k[10] = {baron, ambassador, adventurer, embargo, village, minion, mine, cutpurse,
                 sea_hag, tribute};

    // initialize a game state and player cards
    initializeGame(numPlayers, k, seed, &G);

    srand(time(NULL));

    printf("----------------- Testing function: %s ----------------\n", TESTFUNC);

    int iterations = 1;
    for (int i = 0; i < iterations; i++)
    {
        // copy the game state to a test case
        memcpy(&testG, &G, sizeof(struct gameState));
        // generate random number of discardCount and deckCount of next player
        testG.discardCount[nextPlayer] = rand() % 10;
        discardCountBefore = testG.discardCount[nextPlayer];
        testG.deckCount[nextPlayer] = rand() % 10;
        deckCountBefore = testG.deckCount[nextPlayer];

        testPlayTribute(thisPlayer, nextPlayer, &testG, &G);
    }
    printf("# total Tests: %d\n", passed + failed);
    printf("# Passed Tests: %d\n", passed);
    printf("# Failed Tests: %d\n", failed);
    printf("# handCountFailed: %i\n", handCountFailed);
    printf("# discardCountFailed: %i\n", discardCountFailed);
    printf("# deckCountFailed: %i\n", deckCountFailed);
    printf("# coinsFailed: %i\n", coinsFailed);
    printf("# numOfActionsFailed: %i\n", actionsFailed);
    printf("\n >>>>> SUCCESS: Testing complete %s <<<<<\n\n", TESTFUNC);

    return 0;
}