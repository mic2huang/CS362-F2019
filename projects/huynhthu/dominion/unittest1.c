/*
 * unittest1.c
 *
 
 */

/*
 * Include the following lines in your makefile:
 *
 * unittest1: unittest1.c dominion.o rngs.o
 *      gcc -o cardtest1 -g  unittest1.c dominion.o rngs.o $(CFLAGS)
 */

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

#define TESTFUNC "playBaron()"

int main()
{
    int newCards = 0;
    int discarded = 1;
    int xtraCoins = 0;
    int xtraBuys = 0;
    int shuffledCards = 0;

    int i, j, m;
    int handpos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
    int remove1, remove2;
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
    printf("TEST 1: choice = 1; NumOfBuys += 1; Discard an Estate, Coins += 4\n");

    // copy the game state to a test case
    memcpy(&testG, &G, sizeof(struct gameState));

    // set estate card in current player's hand
    testG.hand[thisPlayer][2] = estate;

    // set choice
    choice1 = 1;

    // call the test function
    playBaron(thisPlayer, choice1, &testG);

    // set extra buys and extra coins
    xtraBuys = 1;
    xtraCoins = 4;

    printf("1. Hand count = %d\n", testG.handCount[thisPlayer]);
    printf("Expected = %d\n", G.handCount[thisPlayer] - discarded);
    testResult(testG.handCount[thisPlayer], G.handCount[thisPlayer] - discarded);

    printf("2. Discarded count = %d\n", testG.discardCount[thisPlayer]);
    printf("Expected = %d\n", G.discardCount[thisPlayer] + discarded);
    testResult(testG.discardCount[thisPlayer], G.discardCount[thisPlayer] + discarded);

    printf("3. Coins = %d\n", testG.coins);
    printf("Expected = %d\n", G.coins + xtraCoins);
    testResult(testG.coins, G.coins + xtraCoins);

    printf("4. Num of buys = %d\n", testG.numBuys);
    printf("Expected = %d\n", G.numBuys + xtraBuys);
    testResult(testG.numBuys, G.numBuys + xtraBuys);

    // ----------- TEST 2: --------------
    printf("TEST 2: choice = 1; NumOfBuys += 1; No Estate card in hand, gain an Estate anyway\n");

    // copy the game state to a test case
    memcpy(&testG, &G, sizeof(struct gameState));

    // remove estate card in current player's hand
    testG.hand[thisPlayer][0] = steward;
    testG.hand[thisPlayer][1] = copper;
    testG.hand[thisPlayer][2] = duchy;
    testG.hand[thisPlayer][3] = ambassador;
    testG.hand[thisPlayer][4] = feast;

    // set choice
    choice1 = 1;

    // call the test function
    playBaron(thisPlayer, choice1, &testG);

    // set extra buys and extra coins
    xtraBuys = 1;
    xtraCoins = 4;

    printf("1. Supply Estate = %d\n", testG.supplyCount[estate]);
    printf("Expected = %d\n", G.supplyCount[estate] - discarded);
    testResult(testG.supplyCount[estate], G.supplyCount[estate] - discarded);

    printf("2. Discarded count = %d\n", testG.discardCount[thisPlayer]);
    printf("Expected = %d\n", G.discardCount[thisPlayer] + discarded);
    testResult(testG.discardCount[thisPlayer], G.discardCount[thisPlayer] + discarded);

    printf("3. Num of buys = %d\n", testG.numBuys);
    printf("Expected = %d\n", G.numBuys + xtraBuys);
    testResult(testG.numBuys, G.numBuys + xtraBuys);

    // ----------- TEST 3: --------------

    printf("TEST 3: choice = 0; NumOfBuys += 1; Gain an Estate, no Estate in Supply after player gaining Estate card, gameover\n");

    // copy the game state to a test case
    memcpy(&testG, &G, sizeof(struct gameState));

    // set choice
    choice1 = 0;

    // set number of supply Estate
    testG.supplyCount[estate] = 1;

    playBaron(thisPlayer, choice1, &testG);

    // set extra buys and extra coins
    xtraBuys = 1;
    xtraCoins = 4;

    printf("1. Supply Estate = %d\n", testG.supplyCount[estate]);
    printf("Expected = %d\n", 0);
    testResult(testG.supplyCount[estate], 0);

    printf("2. Discarded count = %d\n", testG.discardCount[thisPlayer]);
    printf("Expected = %d\n", G.discardCount[thisPlayer] + discarded);
    testResult(testG.discardCount[thisPlayer], G.discardCount[thisPlayer] + discarded);

    printf("3. Num of buys = %d\n", testG.numBuys);
    printf("Expected = %d\n", G.numBuys + xtraBuys);
    testResult(testG.numBuys, G.numBuys + xtraBuys);

    printf("4. isGameOver = %d\n", isGameOver(&testG));
    testResult(isGameOver(&testG), 1);

    printf("\n >>>>> SUCCESS: Testing complete %s <<<<<\n\n", TESTFUNC);

    return 0;
}
