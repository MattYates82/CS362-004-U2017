#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"

#define DEBUG 0
#define NOISY_TEST 1

#ifndef FUNCTION
#define FUNCTION "kingdomCards"
#endif
int checkKingdomCards() {

	int i = 1;
	int j = 0;
	int* kingdom;
	kingdom = kingdomCards(i, i, i, i, i, i, i, i, i, i);

	for(j=0; j < 10; j++){

		if(kingdom[j] == i){
			printf("%s Test %d: Passed!\n", FUNCTION, j+1);
		}

	        else{ printf("%s Test %d: Failed!\n", FUNCTION, j+1);}

	}

	return 0;

}

int main(){


	printf("------------------Testing Function: %s------------------------\n", FUNCTION);
	checkKingdomCards();

	return 0;
	

}
