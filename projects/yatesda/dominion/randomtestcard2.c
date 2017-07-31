/**************************************************
******Random Tests: Council Room  Card*************
******David M Yates		      *************
******Summer 2017		      *************
******CS 362 - 400		      *************
******Assignment 4		      *************
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

int checkCouncilRoom(int p, struct gameState *post, double testNumber, int choice1, int choice2, int choice3, int handPos) {
  
  struct gameState test;
  memcpy(&test, &post, sizeof(struct gameState));

  int r = CouncilRoom(p, choice1, choice2, choice3, post);

  int pass = 0;
  //int firstCard = post->hand[p][post->handCount[p]-1];
  //int secondCard = post->hand[p][post->handCount[p]-2];

  if (post->handCount[p] != test.handCount[p] + 4 - 1 ){

	printf("FAILED TEST %g: Player %d failed to draw 4 cards.\n", testNumber, p);
	pass = 1;

  }

  if (post->numBuys != (test.numBuys + 1)){

        printf("FAILED TEST %g: Game State didn't increment an additional Buy.\n", testNumber, p);
        pass = 1;

  }
  int i = 0;	  
  for (i = 0; i < post->numPlayers; i++){
  	
	if ( (i != p ) && (post->handCount[i] != (test.handCount[i] + 1) )){

		printf("FAILED TEST %g: Player %d failed to draw 1 card.\n", testNumber, i);
		pass = 1;
	}
  }
  if (pass == 0){

	printf("Passed Test %g!\n", testNumber);
	return 0;
  }

  return 1;
  
}

int main () {

  int i, n, r, p, deckCount, discardCount, handCount;

  int k[10] = {adventurer, council_room, feast, gardens, mine,
	       remodel, smithy, village, baron, great_hall};

  printf ("...................Random Testing: Council Room Card.....................\n\n");

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
		failedTests += checkCouncilRoom(p, &G, total, choice1, choice2, choice3, handPos);
		total++;
  	}
  }

  double passRate;
  passRate = 100 - failedTests / total * 100;
  printf ("ALL TESTS COMPLETED SUCCESSFULLY.\n");
  printf ("Failed %g of %g tests. Test Pass Rate: %.2f\n", failedTests, total, passRate);

  return 0;
}
