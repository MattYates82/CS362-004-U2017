#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"

#define DEBUG 0
#define NOISY_TEST 1

#ifndef CARD
#define CARD "feast"
#endif
int checkMine(int p, struct gameState *initial) {

  	struct gameState testGame;
  	memcpy (&testGame, initial, sizeof(struct gameState));
	 
  	int choice1 = 0, choice2 = 1, choice3 = 3;
  	printf ("Initial State: p %d HC %d DeC %d DiC %d G: %d S: %d C: %d\n",
                p,(initial->handCount[p]), (initial->deckCount[p]), initial->discardCount[p],
                initial->supplyCount[gold], initial->supplyCount[silver], initial->supplyCount[copper]);

	Mine(p, choice1, choice2, choice3, &testGame);

  	printf ("Final State: p %d HC %d DeC %d DiC %d G: %d S: %d C: %d\n",
  		p, testGame.handCount[p], testGame.deckCount[p], testGame.discardCount[p], 
		testGame.supplyCount[gold], testGame.supplyCount[silver], testGame.supplyCount[copper]);

	int i;
  	int j;
  	int k;
  	int x;
  	int index;
  	int currentPlayer = whoseTurn(initial);
  	int nextPlayer = currentPlayer + 1;

  	int tributeRevealedCards[2] = {-1, -1};
  	int temphand[MAX_HAND];// moved above the if statement
 	int drawntreasure=0;
  	int cardDrawn;
  	int z = 0;// this is the counter for the temp hand
  	if (nextPlayer > (initial->numPlayers - 1)){
  	nextPlayer = 0;
  	}

  	//gain card with cost up to 5
  	//Backup hand
  	for (i = 0; i <= initial->handCount[currentPlayer]; i++){
		temphand[i] = initial->hand[currentPlayer][i];//Backup card
		initial->hand[currentPlayer][i] = -1;//Set to nothing
	  }
  	//Backup hand

  	//Update Coins for Buy
  	updateCoins(currentPlayer, initial, 5);
  	x = 1;//Condition to loop on
  	while( x == 1) {//Buy one card
  
		  if (supplyCount(choice1, initial) <= 0){
	  if (DEBUG)
		printf("None of that card left, sorry!\n");

	  if (DEBUG){
		printf("Cards Left: %d\n", supplyCount(choice1, initial));
	  }
	}
	else if (initial->coins < getCost(choice1)){
	  printf("That card is too expensive!\n");

	  if (DEBUG){
		printf("Coins: %d < %d\n", initial->coins, getCost(choice1));
	  }
	}
	else{

	  if (DEBUG){
		printf("Deck Count: %d\n", initial->handCount[currentPlayer] + initial->deckCount[currentPlayer] + initial->discardCount[currentPlayer]);
	  }

	  gainCard(choice1, initial, 0, currentPlayer);//Gain the card
	  x = 0;//No more buying cards

	  if (DEBUG){
		printf("Deck Count: %d\n", initial->handCount[currentPlayer] + initial->deckCount[currentPlayer] + initial->discardCount[currentPlayer]);
	  }

	}
  	}
	//Reset Hand
	for (i = 0; i <= initial->handCount[currentPlayer]; i++){
		initial->hand[currentPlayer][i] = temphand[i];
		temphand[i] = -1;
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


        if(testGame.discardCount[p] == initial->discardCount[p]){
                printf("%s Discard Count Test: Passed!\n", CARD);
        }

        else{ printf("%s Discard Count Test: Failed!\n", CARD);}

        if(testGame.coins == initial->coins){
                printf("%s Coin Test: Passed!\n", CARD);
        }

        else{ printf("%s Coin Test: Failed!\n", CARD);}

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
	checkMine(player, &game);

	return 0;
	

}
