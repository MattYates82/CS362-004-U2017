#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <time.h>
#include <stdlib.h>

#define DEBUG 0
#define TESTS 10000

int checkAdventurer(int p, struct gameState *post, double testNumber) {
  
  struct gameState test;
  memcpy(&test, &post, sizeof(struct gameState));

  int player = whoseTurn(post);
  int r = Adventurer(p, 0, 0, 0, post);
  int pass = 0;
  int firstCard = post->hand[player][post->handCount[player]-1];
  int secondCard = post->hand[player][post->handCount[player]-2];

  if (post->handCount[player] != test.handCount[player] + 2){

	printf("FAILED TEST %g: Player %d failed to draw 2 cards.\n", testNumber, player);
	pass = 1;

  }  

  if ( (firstCard != copper && firstCard != silver && firstCard != gold) ||
	(secondCard!= copper && firstCard != silver && firstCard != gold) ){

	printf("FAILED TEST %g: Player %d did not draw 2 treasure cards.\n", testNumber, p);
	pass = 1;
  }

  if (pass == 0){

	printf("Passed Test %g!\n", testNumber);

  }

  return pass;
  
}

int main () {

  int i, n, r, p, deckCount, discardCount, handCount;

  int k[10] = {adventurer, council_room, feast, gardens, mine,
	       remodel, smithy, village, baron, great_hall};

  struct gameState G;

  printf ("...................Random Testing: Adventurer Card.....................\n\n");

  double failedTests = 0.0;
  double total = 0.0;
  for (n = 0; n < TESTS; n++) {

	srand(time(NULL));

	int numPlayers = rand() % (4-1) + 2; //2-4 Players
	
	initializeGame(numPlayers, k, rand, &G);
	
	int j;
	for (j = 0; j < numPlayers; j++){
		G.whoseTurn = j; 
		failedTests += checkAdventurer(j, &G, total);
		total++;
	}  
}

  double passRate;
  passRate = 100 - (failedTests / total) * 100;
  printf ("ALL TESTS COMPLETED SUCCESSFULLY.\n");
  printf ("Failed %g of %g tests. Test Pass Rate: %.2f\n", failedTests, total, passRate);

  return 0;
}
