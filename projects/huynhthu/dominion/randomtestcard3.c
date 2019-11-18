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

int passed = 0, failed = 0, handCountFailed = 0, coinsFailed = 0, actionsFailed = 0;
int xtraCoins = 2;
int xtraCards = 2;
int xtraActions = 2;
int tributeRevealedCards[2] = {-1, -1};

void testPlayTribute(int thisPlayer, int nextPlayer, struct gameState *testG, struct gameState *G)
{
    int handCountExpected = G->handCount[thisPlayer];
    int coinsExpected = G->coins;
    int actionsExpected = G->numActions;
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

    // remove duplicated card
    if (tributeRevealedCards[0] == tributeRevealedCards[1])
    {
        tributeRevealedCards[1] = -1;
    }

    // check revealed cards
    for (int i = 0; i < 2; i++)
    {
        if (tributeRevealedCards[i] > -1)
        {
            // reveal treasure card
            if ((tributeRevealedCards[i] == copper || tributeRevealedCards[i] == silver || tributeRevealedCards[i] == gold))
            {
                coinsExpected += xtraCoins;
            }

            // reveal victory card
            else if ((tributeRevealedCards[i] == estate || tributeRevealedCards[i] == duchy || tributeRevealedCards[i] == province || tributeRevealedCards[i] == gardens || tributeRevealedCards[i] == great_hall))
            {
                handCountExpected += xtraCards;
            }

            // reveal action card
            else
            {
                actionsExpected += xtraActions;
            }
        }
    }

    if (testG->coins != coinsExpected)
    {
        coinsFailed++;
        thisTestResult = 0;
        printf("testG->coins = %d\n", testG->coins);
        printf("coinsExpected = %d\n", coinsExpected);
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

    int iterations = 10000;
    for (int i = 0; i < iterations; i++)
    {
        // copy the game state to a test case
        memcpy(&testG, &G, sizeof(struct gameState));
        // generate random number of discardCount and deckCount of next player
        testG.discardCount[nextPlayer] = rand() % 10;
        testG.deckCount[nextPlayer] = rand() % 10;

        testPlayTribute(thisPlayer, nextPlayer, &testG, &G);
    }
    printf("# total Tests: %d\n", passed + failed);
    printf("# Passed Tests: %d\n", passed);
    printf("# Failed Tests: %d\n", failed);
    printf("# handCountFailed: %i\n", handCountFailed);
    printf("# coinsFailed: %i\n", coinsFailed);
    printf("# numOfActionsFailed: %i\n", actionsFailed);
    printf("\n >>>>> SUCCESS: Testing complete %s <<<<<\n\n", TESTFUNC);

    return 0;
}