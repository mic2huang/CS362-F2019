/*
 * randomtestcard1.c
 *
 
 */

/*
 * Include the following lines in your makefile:
 *
 * randomtestcard1: randomtestcard1.c dominion.o rngs.o
 *      gcc -o randomtestcard1 -g  randomtestcard1.c dominion.o rngs.o $(CFLAGS)
 */

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>
#include <time.h>

#define TESTFUNC "playBaron()"

int main()
{
    int discarded = 1;
    int xtraCoins = 0;
    int xtraBuys = 0;

    int choice1 = 0;
    int seed = 1000;
    int numPlayers = 2;
    int thisPlayer = 0;
    struct gameState G, testG;
    int k[10] = {baron, ambassador, estate, embargo, village, minion, mine, cutpurse,
                 sea_hag, tribute};

    // initialize a game state and player cards
    initializeGame(numPlayers, k, seed, &G);

    // copy the game state to a test case
    memcpy(&testG, &G, sizeof(struct gameState));

    // set extra buys and extra coins
    xtraBuys = 1;
    xtraCoins = 4;

    srand(time(NULL));

    printf("----------------- Testing function: %s ----------------\n", TESTFUNC);
    int cont = 1;
    int state1 = 0, state2 = 0, state3 = 0;
    int testNum = 1;
    int i;
    int estateInHand = 0;
    int estateNum;
    while (cont)
    {
        // copy the game state to a test case
        memcpy(&testG, &G, sizeof(struct gameState));

        // generate random choice
        choice1 = rand() % 2;

        // generate random number of supply Estate
        testG.supplyCount[estate] = rand() % 2;

        // generate random number of estate card in hand
        estateNum = rand() % 2;

        if (estateNum > 0)
        {
            testG.hand[thisPlayer][estateNum] = estate;
        }

        // call the test function
        playBaron(thisPlayer, choice1, &testG);

        // check choice
        if (choice1 == 1)
        {
            // check card in hand
            for (i = 0; i < 5; i++)
            {
                if (testG.hand[thisPlayer][0] == estate && state1 != 1)
                {
                    // reach state: choice = 1; Discard an Estate
                    state1 = 1;
                    printf("TEST %d:\n", testNum);
                    printf("Choice = 1; NumOfBuys += 1; Coins += 4; Discard an Estate\n")
                        printf("1. Hand count = %d\n", testG.handCount[thisPlayer]);
                    printf("Expected = %d\n", G.handCount[thisPlayer] - discarded);
                    testResult(testG.handCount[thisPlayer], G.handCount[thisPlayer] - discarded);

                    printf("2. Coins = %d\n", testG.coins);
                    printf("Expected = %d\n", G.coins + xtraCoins);
                    testResult(testG.coins, G.coins + xtraCoins);

                    printf("3. Num of buys = %d\n", testG.numBuys);
                    printf("Expected = %d\n", G.numBuys + xtraBuys);
                    testResult(testG.numBuys, G.numBuys + xtraBuys);
                    estateInHand = 1;
                    break;
                }
            }
            if (estateInHand == 0 && state2 != 1)
            {
                // reach state: choice = 1; No Estate card in hand, gain an Estate anyway
                state2 = 1;
                printf("TEST %d:\n", testNum);
                printf("Choice = 1; NumOfBuys += 1; No Estate card in hand, gain an Estate anyway\n");
                printf("1. Supply Estate = %d\n", testG.supplyCount[estate]);
                printf("Expected = %d\n", G.supplyCount[estate] - discarded);
                testResult(testG.supplyCount[estate], G.supplyCount[estate] - discarded);

                printf("2. Num of buys = %d\n", testG.numBuys);
                printf("Expected = %d\n", G.numBuys + xtraBuys);
                testResult(testG.numBuys, G.numBuys + xtraBuys);
            }
        }
        else // choice1 = 0
        {
            if (testG.supplyCount[estate] == 1 && state3 != 1)
            {
                // reach state: choice = 0; Gain an Estate, no Estate in Supply after player gaining Estate card, gameover
                state3 = 1;
                printf("TEST %d:\n", testNum);
                printf("Choice = 0; NumOfBuys += 1; Gain an Estate, no Estate in Supply after player gaining Estate card, gameover\n");
                printf("1. Supply Estate = %d\n", testG.supplyCount[estate]);
                printf("Expected = %d\n", 0);
                testResult(testG.supplyCount[estate], 0);

                printf("2. Num of buys = %d\n", testG.numBuys);
                printf("Expected = %d\n", G.numBuys + xtraBuys);
                testResult(testG.numBuys, G.numBuys + xtraBuys);

                printf("3. isGameOver = %d\n", isGameOver(&testG));
                testResult(isGameOver(&testG), 1);
            }
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