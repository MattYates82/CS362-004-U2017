#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"

#define DEBUG 0
#define NOISY_TEST 1

#ifndef CARD
#define CARD "smithy"
#endif
int checkSmithy(int p, struct gameState *initial) {

  	struct gameState testGame;
  	memcpy (&testGame, initial, sizeof(struct gameState));

	int newCards = 3, discards = 1, handPosition = 0;
	 
  	int choice1 = 0, choice2 = 0, choice3 = 0;
  	printf ("Initial State: p %d HC %d DeC %d DiC %d\n",
        p, initial->handCount[p], initial->deckCount[p], initial->discardCount[p]);

	Smithy(handPosition, choice1, choice2, choice3, &testGame);

  	printf ("Final State: p %d HC %d DeC %d DiC %d\n",
  		p, testGame.handCount[p], testGame.deckCount[p], testGame.discardCount[p]);

	printf ("Expected State: p %d HC %d DeC %d Dic %d\n", 
		p,(initial->handCount[p]+newCards-discards), (initial->deckCount[p] - newCards), initial->discardCount[p]);

	if(testGame.handCount[p] == (initial->handCount[p] + newCards - discards)){printf("%s HandCount Test: Passed\n", CARD);}

	else{printf("%s HandCount Test: Failed\n", CARD);}

	if(testGame.deckCount[p] == (initial->deckCount[p] - newCards)){printf("%s DeckCount Test: Failed\n", CARD);}

	else{printf("%s DeckCount Test: Failed\n", CARD);}

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
	printf("------------------Testing Card: %s------------------------\n", CARD);
	checkSmithy(player, &game);

	return 0;
	

}
