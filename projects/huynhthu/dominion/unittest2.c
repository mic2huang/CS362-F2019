/*
 * unittest2.c
 *
 
 */

/*
 * Include the following lines in your makefile:
 *
 * unittest2: unittest2.c dominion.o rngs.o
 *      gcc -o unittest2 -g  unittest2.c dominion.o rngs.o $(CFLAGS)
 */

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

#define TESTFUNC "playMinion()"

int main()
{
    int discarded = 1;
    int xtraCoins = 0;
    int xtraActions = 0;

    int choice1 = 0, choice2 = 0, handpos = 0;
    int seed = 1000;
    int numPlayers = 2;
    int thisPlayer = 0;
    struct gameState G, testG;
    int k[10] = {baron, ambassador, adventurer, embargo, village, minion, mine, cutpurse,
                 sea_hag, tribute};

    // initialize a game state and player cards
    initializeGame(numPlayers, k, seed, &G);

    printf("----------------- Testing function: %s ----------------\n", TESTFUNC);

    // ----------- TEST 1: --------------
    printf("TEST 1: choice1 = 1; choice2 = 0; numActions += 1; Coins +=2\n");

    // copy the game state to a test case
    memcpy(&testG, &G, sizeof(struct gameState));

    // set choice
    choice1 = 1;

    // set extra actions and extra coins
    xtraCoins = 2;
    xtraActions = 1;

    // call the test function
    playMinion(thisPlayer, choice1, choice2, &testG, handpos);

    printf("1. Hand count = %d\n", testG.handCount[thisPlayer]);
    printf("Expected = %d\n", G.handCount[thisPlayer] - discarded);
    testResult(testG.handCount[thisPlayer], G.handCount[thisPlayer] - discarded);

    printf("2. Coins = %d\n", testG.coins);
    printf("Expected = %d\n", G.coins + xtraCoins);
    testResult(testG.coins, G.coins + xtraCoins);

    printf("3. Num of actions = %d\n", testG.numActions);
    printf("Expected = %d\n", G.numActions + xtraActions);
    testResult(testG.numActions, G.numActions + xtraActions);

    // ----------- TEST 2: --------------
    printf("TEST 2: choice1 = 0; choice2 = 1; numActions += 1; Discard hand, redraw 4, other players has 5 cards, discard, redraw\n");

    // copy the game state to a test case
    memcpy(&testG, &G, sizeof(struct gameState));

    // set choice
    choice1 = 0;
    choice2 = 1;

    // set handCount of other player = 5
    testG.handCount[thisPlayer + 1] = 5;

    // call the test function
    playMinion(thisPlayer, choice1, choice2, &testG, handpos);

    // set extra buys and extra coins
    xtraActions = 1;
    xtraCoins = 4;

    printf("1. Hand count = %d\n", testG.handCount[thisPlayer]);
    printf("Expected = %d\n", 4);
    testResult(testG.handCount[thisPlayer], 4);

    printf("2. Coins = %d\n", testG.coins);
    printf("Expected = %d\n", G.coins + xtraCoins);
    testResult(testG.coins, G.coins + xtraCoins);

    printf("3. Num of actions = %d\n", testG.numActions);
    printf("Expected = %d\n", G.numActions + xtraActions);
    testResult(testG.numActions, G.numActions + xtraActions);

    printf("4. Other player hand count = %d\n", testG.handCount[thisPlayer + 1]);
    printf("Expected = %d\n", 4);
    testResult(testG.handCount[thisPlayer + 1], 4);

    printf("\n >>>>> SUCCESS: Testing complete %s <<<<<\n\n", TESTFUNC);

    return 0;
}
