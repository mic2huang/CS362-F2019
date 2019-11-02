/*
 * unittest3.c
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

#define TESTFUNC "playAmbassador()"

int main()
{
    int choice1 = 0, choice2 = 0, handpos = 0, result = 0;
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
    printf("TEST 1: choice2 = 3; Invalid choices\n");

    // copy the game state to a test case
    memcpy(&testG, &G, sizeof(struct gameState));

    // set choice
    choice2 = 3;

    // call the test function
    result = playAmbassador(thisPlayer, choice1, choice2, &testG, handpos);

    printf("Result = %d\n", result);
    printf("Expected = %d\n", -1);
    testResult(result, -1);

    // ----------- TEST 2: --------------
    printf("TEST 2: choice1 = handpos; Invalid choice\n");

    // copy the game state to a test case
    memcpy(&testG, &G, sizeof(struct gameState));

    // set choice
    choice1 = handpos;

    // call the test function
    result = playAmbassador(thisPlayer, choice1, choice2, &testG, handpos);

    printf("Result = %d\n", result);
    printf("Expected = %d\n", -1);
    testResult(result, -1);

    // ----------- TEST 3: --------------
    printf("TEST 3: choice1 = 1; choice2 = 1; No other copy of card in hand; Invalid choice \n");

    // copy the game state to a test case
    memcpy(&testG, &G, sizeof(struct gameState));

    // set choice
    choice1 = 1;
    choice2 = 1;

    // set cards in current player's hand
    testG.hand[thisPlayer][0] = steward;
    testG.hand[thisPlayer][1] = copper;
    testG.hand[thisPlayer][2] = duchy;
    testG.hand[thisPlayer][3] = ambassador;
    testG.hand[thisPlayer][4] = feast;

    // call the test function
    result = playAmbassador(thisPlayer, choice1, choice2, &testG, handpos);

    printf("Result = %d\n", result);
    printf("Expected = %d\n", -1);
    testResult(result, -1);

    // ----------- TEST 4: --------------
    printf("TEST 4: choice1 = 1; choice2 = 1; Take 1 card from hand and put it on top of their Supply pile \n");

    // copy the game state to a test case
    memcpy(&testG, &G, sizeof(struct gameState));

    // set choice
    choice1 = 1;
    choice2 = 1;

    // set cards in current player's hand
    testG.hand[thisPlayer][0] = ambassador;
    testG.hand[thisPlayer][1] = minion;
    testG.hand[thisPlayer][2] = minion;
    testG.hand[thisPlayer][3] = ambassador;
    testG.hand[thisPlayer][4] = feast;
   
    // call the test function
    playAmbassador(thisPlayer, choice1, choice2, &testG, handpos);
    
    printf("1. Supply count = %d\n", testG.supplyCount[testG.hand[thisPlayer][choice1]]);
    printf("Expected = %d\n", G.supplyCount[testG.hand[thisPlayer][choice1]] + choice2);
    testResult(testG.supplyCount[testG.hand[thisPlayer][choice1]], G.supplyCount[testG.hand[thisPlayer][choice1]]  + choice2);

    printf("2. Other player discard count = %d\n", testG.discardCount[thisPlayer + 1]);
    printf("Expected = %d\n", G.discardCount[thisPlayer + 1] + 1);
    testResult(testG.discardCount[thisPlayer + 1], G.discardCount[thisPlayer + 1] + 1);

    printf("3. Played card count = %d\n", testG.playedCardCount);
    printf("Expected = %d\n", G.playedCardCount + 1);
    testResult(testG.playedCardCount, G.playedCardCount + 1);

    printf("\n >>>>> SUCCESS: Testing complete %s <<<<<\n\n", TESTFUNC);

    return 0;
}
