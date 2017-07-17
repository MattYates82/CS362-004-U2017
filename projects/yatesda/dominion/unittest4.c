#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"

#define DEBUG 1
#define NOISY_TEST 1

#ifndef FUNCTION
#define FUNCTION "supplyCount"
#endif
int checkSupplyCount(int p, struct gameState *initial) {

  	struct gameState testGame;
  	memcpy (&testGame, initial, sizeof(struct gameState));
	
	int newCards = 3, discards = 1, handPosition = 0;
	 
  	int choice1 = 0, choice2 = 1, choice3 = 2;
  	printf ("Initial State: p %d HC %d DeC %d DiC %d G: %d S: %d C: %d Coins: %d\n",
                p,(initial->handCount[p]), (initial->deckCount[p]), initial->discardCount[p],
                initial->supplyCount[gold], initial->supplyCount[silver], initial->supplyCount[copper], initial->coins);

  	int i = supplyCount(gold, initial);
	if(i != (initial->supplyCount[0])){
		printf("%s Test: Passed!\n", FUNCTION);
	}

        else{ printf("%s Test: Failed!\n", FUNCTION);}

	return 0;

}

int main(){


	int player = 0;
	int players = 2;
	
	int k[10] = {adventurer, council_room, feast, gardens, mine,
			remodel, smithy, village, baron, great_hall};

	struct gameState game;
	int seed = 1000;
	initializeGame(players, k, seed, &game);
	player = whoseTurn(&game);
	printf("------------------Testing Function: %s------------------------\n", FUNCTION);
	checkSupplyCount(player, &game);

	return 0;
	

}
