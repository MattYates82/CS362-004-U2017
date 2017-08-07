#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"

#define DEBUG 0
#define NOISY_TEST 1

#ifndef CARD
#define CARD "village"
#endif
int checkVillage(struct gameState *initial, int handPos) {

  	struct gameState testGame;
  	memcpy (&testGame, initial, sizeof(struct gameState));
	int p = whoseTurn(&testGame);
 
  	printf ("Initial State: p %d HC %d DeC %d DiC %d Actions %d\n",
                p,(initial->handCount[p]), (initial->deckCount[p]), initial->discardCount[p], initial->numActions);

	alteredVillage(&testGame, handPos);

  	printf ("Final State: p %d HC %d DeC %d DiC %d Actions %d\n",
  		p, testGame.handCount[p], testGame.deckCount[p], testGame.discardCount[p], testGame.numActions);
  	
  	int currentPlayer = whoseTurn(initial);
	int nextPlayer = currentPlayer + 1;

  	if (nextPlayer > (initial->numPlayers - 1)){
    		nextPlayer = 0;
	}

	drawCard(currentPlayer, initial);
	initial->numActions += 2;
  	//discard card from hand
  	discardCard(handPos, currentPlayer, initial, 0);

  	printf ("Expected State: p %d HC %d DeC %d Dic %d Actions %d\n",
                p,initial->handCount[p], initial->deckCount[p], initial->discardCount[p],initial->numActions);

	if(testGame.handCount[p] == (initial->handCount[p])){
		printf("%s HandCount Test: Passed!\n", CARD);
	}

        else{ printf("%s HandCount Test: Failed!\n", CARD);}

	if(testGame.deckCount[p] == (initial->deckCount[p])){
		printf("%s DeckCount Test: Passed!\n", CARD);
	}

        else{ printf("%s DeckCount Test: Failed!\n", CARD);}

        if(testGame.discardCount[p] == (initial->discardCount[p])){
                printf("%s DiscardCount Test: Passed!\n", CARD);
        }

        else{ printf("%s DiscardCount Test: Failed!\n", CARD);}

	if(testGame.numActions == initial->numActions){
        	printf("%s Actions Supply Test: Passed!\n", CARD);
	}

	else{ printf("%s Actions Test: Failed!\n", CARD);}

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
	checkVillage(&game, 3);

	return 0;
	

}
