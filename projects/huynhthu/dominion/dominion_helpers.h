#ifndef _DOMINION_HELPERS_H
#define _DOMINION_HELPERS_H

#include "dominion.h"

int drawCard(int player, struct gameState *state);
int updateCoins(int player, struct gameState *state, int bonus);
int discardCard(int handPos, int currentPlayer, struct gameState *state,
                int trashFlag);
int gainCard(int supplyPos, struct gameState *state, int toFlag, int player);
int getCost(int cardNumber);
int cardEffect(int card, int choice1, int choice2, int choice3,
               struct gameState *state, int handPos, int *bonus);

void drawNCards(int currentPlayer, int num, struct gameState *state);
/* Draw n cards for current player */

int playBaron(int currentPlayer, int choice, struct gameState *state);
/* Play Baron card */

int playMinion(int currentPlayer, int choice1, int choice2, struct gameState *state, int handPos);
/* Play Minion card */

int playAmbassador(int currentPlayer, int choice1, int choice2, struct gameState *state, int handPos);
/* Play Ambassador card */

int playTribute(int currentPlayer, int nextPlayer, struct gameState *state);
/* Play Tribute card */

int playMine(int currentPlayer, int choice1, int choice2, struct gameState *state, int handPos);
/* Play Mine card */

void testResult(int a, int b);
/* Print test result */

#endif
