#include "assert.h"
#include "dominion.h"
#include <stdio.h>
#include "rngs.h"
#include <stdlib.h>

int testFullDeckCount()
{
    //
    // Tests that fullDeckCount works properly
    
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

    status = fullDeckCount(0, copper, &G);

    assert (status >= 0);

    int i, j, count = 0;
    for (i=0 ; i<G.deckCount[0] ; i++)
    {
        if (G.deck[0][i] == copper) count++;
    }
    for (i=0 ; i<G.handCount[0] ; i++)
    {
        if (G.hand[0][i] == copper) count++;
    }
    for (i=0 ; i<G.discardCount[0] ; i++)
    {
        if (G.discard[0][i] == copper) count++;
    }

    assert (status == count);

    printf ("testfullDeckCount passes.\n");

    status = 0;
    return status;
}

int main ()
{
    return testFullDeckCount();
}
