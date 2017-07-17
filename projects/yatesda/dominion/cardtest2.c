#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"

#define DEBUG 0
#define NOISY_TEST 1

#ifndef CARD
#define CARD "adventurer"
#endif
int checkAdventurer(int p, struct gameState *initial) {

  	struct gameState testGame;
  	memcpy (&testGame, initial, sizeof(struct gameState));
	
	int newCards = 3, discards = 1, handPosition = 0;
	 
  	int choice1 = 0, choice2 = 0, choice3 = 0;
  	printf ("Initial State: p %d HC %d DeC %d DiC %d G: %d S: %d C: %d\n",
                p,(initial->handCount[p]), (initial->deckCount[p]), initial->discardCount[p],
                initial->supplyCount[gold], initial->supplyCount[silver], initial->supplyCount[copper]);

	Adventurer(handPosition, choice1, choice2, choice3, &testGame);

  	printf ("Final State: p %d HC %d DeC %d DiC %d G: %d S: %d C: %d\n",
  		p, testGame.handCount[p], testGame.deckCount[p], testGame.discardCount[p], 
		testGame.supplyCount[gold], testGame.supplyCount[silver], testGame.supplyCount[copper]);

	int nextPlayer = p + 1;

	int tributeRevealedCards[2] = {-1, -1};
	int temphand[MAX_HAND];// moved above the if statement
	int drawntreasure=0;
	int cardDrawn;
	int z = 0;// this is the counter for the temp hand
	if (nextPlayer > (initial->numPlayers - 1)){
		nextPlayer = 0;
	}

	while(drawntreasure<2){
		if (initial->deckCount[p] < 1){ //Assignment 2 Bug: Changed < to > 
		//if the deck is empty we need to shuffle discard and add to deck
			shuffle(p, initial);
		}
		drawCard(p, initial);
		cardDrawn = initial->hand[p][initial->handCount[p]-1];//top card of hand is most recently drawn card.
		if (cardDrawn == copper || cardDrawn == silver || cardDrawn == gold)
		  	drawntreasure++;
		else{
			temphand[z]=cardDrawn;
			initial->handCount[p]--; //this should just remove the top card (the most recently drawn one).	
			z++;
		}
  	}
  	while(z-1>=0){
		initial->discard[p][initial->discardCount[p]++]=temphand[z-1]; // discard all cards in play that have been drawn
		z=z-1;
	}

	printf ("Expected State: p %d HC %d DeC %d Dic %d G: %d S: %d C: %d\n",
	        p,initial->handCount[p], initial->deckCount[p], initial->discardCount[p], 
		initial->supplyCount[gold], initial->supplyCount[silver], initial->supplyCount[copper]);

	if(testGame.handCount[p] == (initial->handCount[p])){
		printf("%s HandCount Test: Passed!\n", CARD);
	}

        else{ printf("%s HandCount Test: Failed!\n", CARD);}

	if(testGame.deckCount[p] == (initial->deckCount[p])){
		printf("%s DeckCount Test: Passed!\n", CARD);
	}

        else{ printf("%s DeckCount Test: Failed!\n", CARD);}

	if(testGame.supplyCount[copper] == initial->supplyCount[copper]){
        	printf("%s Copper Supply Test: Passed!\n", CARD);
	}

	else{ printf("%s Copper Supply Test: Failed!\n", CARD);}

        if(testGame.supplyCount[silver] == initial->supplyCount[silver]){
		printf("%s Silver Supply Test: Passed!\n", CARD);
	}
        
        else{ printf("%s Silver Supply Test: Failed!\n", CARD);}

	if(testGame.supplyCount[gold] == initial->supplyCount[gold]){
		printf("%s Gold Supply Test: Passed!\n", CARD);
	}

        else{ printf("%s Gold Supply Test: Failed!\n", CARD);}

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
	checkAdventurer(player, &game);

	return 0;
	

}
