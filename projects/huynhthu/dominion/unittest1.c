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

    printf("1. Hand count should = %d\n", G.handCount[thisPlayer] - discarded);
    if (testG.handCount[thisPlayer] == G.handCount[thisPlayer] - discarded)
    {
        printf("Pass.\n");
    }
    else
    {
        printf("Fail.\n\n");
    }

    printf("2. Discarded count should = %d = %d\n", G.discardCount[thisPlayer] + discarded);
    if (testG.discardCount[thisPlayer] == G.discardCount[thisPlayer] + discarded)
    {
        printf("Pass.\n");
    }
    else
    {
        printf("Fail.\n\n");
    }

    printf("3. Coins should = %d = %d\n", G.coins + xtraCoins);
    if (testG.coins == G.coins + xtraCoins)
    {
        printf("Pass.\n");
    }
    else
    {
        printf("Fail.\n\n");
    }

    printf("4. Num of buys should = %d = %d\n", G.numBuys + xtraBuys);
    if (testG.numBuys == G.numBuys + xtraBuys)
    {
        printf("Pass.\n");
    }
    else
    {
        printf("Fail.\n\n");
    }

    // ----------- TEST 2: --------------
    printf("TEST 2: choice = 1; NumOfBuys += 1; No Estate card in hand, gain an Estate anyway, Coins += 4\n");

    // copy the game state to a test case
    memcpy(&testG, &G, sizeof(struct gameState));

    // remove estate card in current player's hand
    G.hand[thisPlayer][0] = steward;
    G.hand[thisPlayer][1] = copper;
    G.hand[thisPlayer][2] = duchy;
    G.hand[thisPlayer][3] = ambassador;
    G.hand[thisPlayer][4] = feast;

    // set choice
    choice1 = 1;

    // call the test function
    playBaron(thisPlayer, choice1, &testG);

    // set extra buys and extra coins
    xtraBuys = 1;
    xtraCoins = 4;

    printf("1. Supply Estate = %d = %d\n", G.supplyCount[estate] - discarded);
    if (testG.supplyCount[estate] == G.supplyCount[estate] - discarded)
    {
        printf("Pass.\n");
    }
    else
    {
        printf("Fail.\n\n");
    }

    printf("2. Discarded count should = %d = %d\n", G.discardCount[thisPlayer] + discarded);
    if (testG.discardCount[thisPlayer] == G.discardCount[thisPlayer] + discarded)
    {
        printf("Pass.\n");
    }
    else
    {
        printf("Fail.\n\n");
    }

    printf("3. Coins should = %d = %d\n", G.coins + xtraCoins);
    if (testG.coins == G.coins + xtraCoins)
    {
        printf("Pass.\n");
    }
    else
    {
        printf("Fail.\n\n");
    }

    printf("4. Num of buys should = %d = %d\n", G.numBuys + xtraBuys);
    if (testG.numBuys == G.numBuys + xtraBuys)
    {
        printf("Pass.\n");
    }
    else
    {
        printf("Fail.\n\n");
    }

    // ----------- TEST 3: --------------

    printf("TEST 3: choice = 0; NumOfBuys += 1; No Estate in Supply after player gaining Estate card, gameover, Coins += 4\n");

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

    printf("1. Supply Estate = %d = %d\n", G.supplyCount[estate] - discarded);
    if (testG.supplyCount[estate] == G.supplyCount[estate] - discarded)
    {
        printf("Pass.\n");
    }
    else
    {
        printf("Fail.\n\n");
    }

    printf("2. Discarded count should = %d = %d\n", G.discardCount[thisPlayer] + discarded);
    if (testG.discardCount[thisPlayer] == G.discardCount[thisPlayer] + discarded)
    {
        printf("Pass.\n");
    }
    else
    {
        printf("Fail.\n\n");
    }

    printf("3. Coins should = %d = %d\n", G.coins + xtraCoins);
    if (testG.coins == G.coins + xtraCoins)
    {
        printf("Pass.\n");
    }
    else
    {
        printf("Fail.\n\n");
    }

    printf("4. Num of buys should = %d = %d\n", G.numBuys + xtraBuys);
    if (testG.numBuys == G.numBuys + xtraBuys)
    {
        printf("Pass.\n");
    }
    else
    {
        printf("Fail.\n\n");
    }

    printf("4. isGameOver should = 1\n");
    if (isGameOver(&testG) == 1)
    {
        printf("Pass.\n");
    }
    else
    {
        printf("Fail.\n\n");
    }

    printf("\n >>>>> SUCCESS: Testing complete %s <<<<<\n\n", TESTFUNC);

    return 0;
}
