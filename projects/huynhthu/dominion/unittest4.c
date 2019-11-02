/*
 * unittest4.c
 *
 
 */

/*
 * Include the following lines in your makefile:
 *
 * unittest4: unittest4.c dominion.o rngs.o
 *      gcc -o unittest4 -g  unittest4.c dominion.o rngs.o $(CFLAGS)
 */

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

#define TESTFUNC "playTribute()"

int main()
{
    int xtraCoins = 2;
    int xtraCards = 2;
    int xtraActions = 2;
    int discardCountBefore = 0, deckCountBefore = 0;

    int seed = 1000;
    int numPlayers = 2;
    int thisPlayer = 0;
    int nextPlayer = thisPlayer + 1;
    struct gameState G, testG;
    int k[10] = {baron, ambassador, adventurer, embargo, village, minion, mine, cutpurse,
                 sea_hag, tribute};

    // initialize a game state and player cards
    initializeGame(numPlayers, k, seed, &G);

    printf("----------------- Testing function: %s ----------------\n", TESTFUNC);

    // ----------- TEST 1: --------------
    printf("TEST 1: Next player's discardCount = 0, deckCount = 1; Reveal a Treasure card, coins += 2\n");

    // copy the game state to a test case
    memcpy(&testG, &G, sizeof(struct gameState));

    // set number of discardCound and deckCount of next player
    testG.discardCount[nextPlayer] = 0;
    testG.deckCount[nextPlayer] = 1;
    deckCountBefore = testG.deckCount[nextPlayer]
    testG.deck[nextPlayer][testG.deckCount[nextPlayer] -1] = copper;

    // call the test function
    playTribute(thisPlayer, nextPlayer, &testG);

    printf("1. Next player's deckCount = %d\n", testG.deckCount[nextPlayer]);
    printf("Expected = %d\n", deckCountBefore - 1);
    testResult(testG.deckCount[nextPlayer], deckCountBefore - 1);

    printf("2. This player's coin = %d\n", testG.coins);
    printf("Expected = %d\n", G.coins + xtraCoins);
    testResult(testG.coins, G.coins + xtraCoins);

    // ----------- TEST 2: --------------
    printf("TEST 2: Next player's discardCount = 1, deckCount = 0; Reveal a Victory card, draw 2 cards\n");

    // copy the game state to a test case
    memcpy(&testG, &G, sizeof(struct gameState));

    // set number of discardCound and deckCount of next player
    testG.discardCount[nextPlayer] = 1;
    discardCountBefore = testG.discardCount[nextPlayer];
    testG.deckCount[nextPlayer] = 0;
    testG.deck[nextPlayer][testG.discardCount[nextPlayer] -1] = estate;

    // call the test function
    playTribute(thisPlayer, nextPlayer, &testG);

    printf("1. Next player's dicardCount = %d\n", testG.discardCount[nextPlayer]);
    printf("Expected = %d\n", discardCountBefore - 1);
    testResult(testG.discardCount[nextPlayer], discardCountBefore - 1);

    printf("2. This player's handCount = %d\n", testG.handCount[thisPlayer]);
    printf("Expected = %d\n", G.handCount[thisPlayer] + xtraCards);
    testResult(testG.handCount[thisPlayer], G.handCount[thisPlayer] + xtraCards);

    // ----------- TEST 3: --------------
    printf("TEST 3: Next player's discardCount = 2, deckCount = 0; Reveal 2 Actions card, drop 1, actions +=2\n");

    // copy the game state to a test case
    memcpy(&testG, &G, sizeof(struct gameState));

    // set number of discardCound and deckCount of next player
    testG.discardCount[nextPlayer] = 2;
    discardCountBefore = testG.discardCount[nextPlayer];
    testG.deckCount[nextPlayer] = 0;
    testG.discard[nextPlayer][0] = baron;
    testG.discard[nextPlayer][1] = baron;

    // call the test function
    playTribute(thisPlayer, nextPlayer, &testG);

    printf("1. Next player's discardCount = %d\n", testG.discardCount[nextPlayer]);
    printf("Expected = %d\n", discardCountBefore - 2);
    testResult(testG.discardCount[nextPlayer], discardCountBefore - 2);

    printf("2. This player's num of actions = %d\n", testG.numActions);
    printf("Expected = %d\n", G.numActions + xtraActions);
    testResult(testG.numActions, G.numActions + xtraActions);

    printf("\n >>>>> SUCCESS: Testing complete %s <<<<<\n\n", TESTFUNC);

    return 0;
}
