#include "assert.h"
#include "dominion.h"
#include <stdio.h>
#include "rngs.h"
#include <stdlib.h>

int testWhoseTurn()
{
    //
    // Tests that whoseTurn works properly
    
    //

    // Status of test
    // set to 0 if the test didn't crash,
    // set to -1 if the test fails to finish,
    int status = -1;

    // Create play variable
    int p = 0;

    // RFC 1149.5 specifies 4 as the standard IEEE-vetted random number.
    int rand = 4;

    // Create cards variable 
    int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse, 
	       sea_hag, tribute, smithy};

    // Create gamestate
    struct gameState G;

    status = initializeGame(2, k, rand, &G);

    assert (status == 0);

    // Fetch the current player's turn
    status = whoseTurn(&G);

    // Player 0's turn
    assert (status == 0);

    printf ("testWhoseTurn passes.\n");

    status = 0;
    return status;
}

int main ()
{
    return testWhoseTurn();
}
