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

#define TESTFUNC "playMinion()"

int main()
{
    int discarded = 1;
    int xtraCoins = 2;
    int xtraActions = 1;

    int choice1 = 0, choice2 = 0, handpos = 0;
    int seed = 1000;
    int numPlayers = 2;
    int thisPlayer = 0;
    struct gameState G, testG;
    int k[10] = {baron, ambassador, adventurer, embargo, village, minion, mine, cutpurse,
                 sea_hag, tribute};

    // initialize a game state and player cards
    initializeGame(numPlayers, k, seed, &G);

    srand(time(NULL));

    printf("----------------- Testing function: %s ----------------\n", TESTFUNC);
    int cont = 1;
    int state1 = 0, state2 = 0;
    int testNum = 1;

    while (cont)
    {
        // copy the game state to a test case
        memcpy(&testG, &G, sizeof(struct gameState));
        // generate random choice
        choice1 = rand() % 2;
        choice2 = rand() % 2;

        // generate other player's handCount
        testG.handCount[thisPlayer + 1] = rand() % 10;

        // check choices
        if (choice1 == 1 && choice2 == 0 && state1 != 1)
        {
            // reach state: choice1 = 1; choice2 = 0; numActions += 1; Coins +=2
            state1 = 1;
            // call the test function
            playMinion(thisPlayer, choice1, choice2, &testG, handpos);

            printf("TEST %d:\n", testNum);
            printf("STATE 1: choice1 = 1; choice2 = 0; numActions += 1; Coins +=2\n");
            printf("1. Hand count = %d\n", testG.handCount[thisPlayer]);
            printf("Expected = %d\n", G.handCount[thisPlayer] - discarded);
            testResult(testG.handCount[thisPlayer], G.handCount[thisPlayer] - discarded);

            printf("2. Coins = %d\n", testG.coins);
            printf("Expected = %d\n", G.coins + xtraCoins);
            testResult(testG.coins, G.coins + xtraCoins);

            printf("3. Num of actions = %d\n", testG.numActions);
            printf("Expected = %d\n", G.numActions + xtraActions);
            testResult(testG.numActions, G.numActions + xtraActions);
        }
        else if (choice1 == 0 && choice2 == 1 && testG.handCount[thisPlayer + 1] >= 5 && state2 != 1)
        {
            // reach state: choice1 = 0; choice2 = 1; numActions += 1; Discard hand, redraw 4, other players has 5 cards, discard, redraw
            state2 = 1;
            // call the test function
            playMinion(thisPlayer, choice1, choice2, &testG, handpos);

            printf("TEST %d:\n", testNum);
            printf("STATE 2: choice1 = 0; choice2 = 1; numActions += 1; Discard hand, redraw 4, other players has 5 cards, discard, redraw\n");
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
        }
        testNum++;
        // check branch coverage
        if (state1 == 1 && state2 == 1 && state3 == 1)
        {
            // test DONE
            cont = 0;
            printf("\n >>>>> SUCCESS: Testing complete %s <<<<<\n\n", TESTFUNC);
        }
    }

    return 0;
}