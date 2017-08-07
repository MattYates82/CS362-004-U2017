/**************************************************
******Random Tests: Great Hall Card   *************
******David M Yates		      *************
******Summer 2017		      *************
******CS 362 - 400		      *************
******Assignment 5		      *************
**************************************************/

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <time.h>
#include <stdlib.h>

#define DEBUG 0
#define TESTS 2000

int checkGreatHall(struct gameState *initial, int handPos) {

        struct gameState testGame;
        memcpy (&testGame, initial, sizeof(struct gameState));
        int p = whoseTurn(&testGame);

        alteredGreatHall(&testGame, handPos);

        int currentPlayer = whoseTurn(initial);
        int nextPlayer = currentPlayer + 1;
	int failed = 0;

        if (nextPlayer > (initial->numPlayers - 1)){
                nextPlayer = 0;
        }

	drawCard(currentPlayer, initial);
        initial->numActions ++;
        //discard card from hand
        discardCard(handPos, currentPlayer, initial, 0);

        printf ("Expected State: p %d HC %d DeC %d Dic %d Actions %d\n",
                p,initial->handCount[p], initial->deckCount[p], initial->discardCount[p],initial->numActions);

        if(testGame.handCount[p] == (initial->handCount[p])){
                printf("HandCount Test: Passed!\n");
        }

	else{ printf("HandCount Test: Failed!\n"); failed = 1;}

        if(testGame.deckCount[p] == (initial->deckCount[p])){
                printf("DeckCount Test: Passed!\n");
        }

	else{ printf("DeckCount Test: Failed!\n"); failed = 1;}

        if(testGame.discardCount[p] == (initial->discardCount[p])){

                printf("DiscardCount Test: Passed!\n");
        }

        else{ printf("DiscardCount Test: Failed!\n"); failed = 1;}

        if(testGame.numActions == initial->numActions){
                printf("Actions Test: Passed!\n");
        }

        else{ printf("Actions Test: Failed!\n"); failed = 1;}

	return failed;

}

int main () {

  int i, n, r, p, deckCount, discardCount, handCount;

  int k[10] = {adventurer, council_room, feast, gardens, mine,
	       remodel, smithy, village, baron, great_hall};

  printf ("...................Random Testing: Great Hall Card.....................\n\n");

  double failedTests = 0;
  double total = 0;
  for (n = 0; n < TESTS; n++) {

	srand(time(NULL));
	struct gameState G;
	int numPlayers = rand() % (MAX_PLAYERS - 1) + 2; //2-4 Players
        
	initializeGame(numPlayers, k, rand(), &G);
	
	for (p = 0; p < numPlayers; p++){
		G.whoseTurn = p;
		int choice1 = rand() % (G.handCount[p] + 1);
		int choice2 = rand() % (G.handCount[p] + 1); 
		int choice3 = rand() % (G.handCount[p] + 1);
        	int handPos = rand() % (G.handCount[p] + 1);
		failedTests += checkGreatHall(&G, handPos);
		total++;
  	}
  }

  double passRate;
  passRate = 100 - failedTests / total * 100;
  printf ("ALL TESTS COMPLETED SUCCESSFULLY.\n");
  printf ("Failed %g of %g tests. Test Pass Rate: %.2f\n", failedTests, total, passRate);

  return 0;
}
