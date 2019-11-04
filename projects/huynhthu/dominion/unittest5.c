/*
 * unittest5.c
 *
 
 */

/*
 * Include the following lines in your makefile:
 *
 * unittest5: unittest5.c dominion.o rngs.o
 *      gcc -o unittest5 -g  unittest5.c dominion.o rngs.o $(CFLAGS)
 */

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

#define TESTFUNC "playMine()"

int main()
{
    
    int choice1 = 0, choice2 = 0, handpos = 0;
    int result = 0;

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
    printf("TEST 1: choice1 = 0; Choose invalid card to trash\n");

    // copy the game state to a test case
    memcpy(&testG, &G, sizeof(struct gameState));

    // set the choice
    choice1 = 0;

    // set the card of choice to be invalid
    testG.hand[thisPlayer][0] = estate;
    
    // call the test function
    result = playMine(thisPlayer, choice1, choice2, &testG, handpos);

    printf("Result = %d\n", result);
    printf("Expected = %d\n", -1);
    testResult(result, -1);

    // ----------- TEST 2: --------------
    printf("TEST 2: choice2 = 0; Choose invalid card to gain\n");

    // copy the game state to a test case
    memcpy(&testG, &G, sizeof(struct gameState));

    // set the choice
    choice1 = 0;
    choice2 = 0;

    // set the card
    testG.hand[thisPlayer][0] = copper;
    
    // call the test function
    result = playMine(thisPlayer, choice1, choice2, &testG, handpos);

    printf("Result = %d\n", result);
    printf("Expected = %d\n", -1);
    testResult(result, -1);

    // ----------- TEST 3: --------------
    printf("TEST 3: choice1 = 1 (copper); choice2 = gold; Choose invalid card to gain\n");

    // copy the game state to a test case
    memcpy(&testG, &G, sizeof(struct gameState));

    // set the choice
    choice1 = 1;
    choice2 = gold;

    // set handpos
    handpos = 1;
    
    // set the cards for choice to be invalid
    testG.hand[thisPlayer][1] = copper;
    
    // call the test function
    result = playMine(thisPlayer, choice1, choice2, &testG, handpos);

    printf("Result = %d\n", result);
    printf("Expected = %d\n", -1);
    testResult(result, -1);

    // ----------- TEST 4: --------------
    printf("TEST 4: choice1 = 1 (copper); choice2 = copper; \n");

    // copy the game state to a test case
    memcpy(&testG, &G, sizeof(struct gameState));

    // set the choice
    choice1 = 1;
    choice2 = copper;

    // set handpos
    handpos = 1;

    // set the card of choice to be invalid
    testG.hand[thisPlayer][0] = curse;
    testG.hand[thisPlayer][1] = copper;
    testG.hand[thisPlayer][2] = duchy;
    testG.hand[thisPlayer][3] = ambassador;
    testG.hand[thisPlayer][4] = feast;
    
    // call the test function
    result = playMine(thisPlayer, choice1, choice2, &testG, handpos);

    printf("1. Card to be trashed = %d\n", testG.hand[thisPlayer][choice1]);
    printf("Expected = %d\n", -1);
    testResult(testG.hand[thisPlayer][choice1], -1);

    printf("2. Played count = %d\n", testG.playedCardCount);
    printf("Expected = %d\n", G.playedCardCount + 1);
    testResult(testG.playedCardCount, G.playedCardCount + 1);

    printf("\n >>>>> SUCCESS: Testing complete %s <<<<<\n\n", TESTFUNC);

    return 0;
}
