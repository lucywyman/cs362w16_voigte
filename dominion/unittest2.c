#include "myassert.h"
#include "dominion.h"
#include <stdio.h>
#include "rngs.h"
#include <stdlib.h>

int testSupplyCount()
{
    //
    // Tests that supplyCount works properly
    //

    // Status of test
    // set to 0 if the test successfully finishes,
    // set to -1 if the test fails to finish,
    int status = -1;

    // Create gamestate
    struct gameState G;

    // Manually setup G to be sufficient for testing
    // This is a form of white-box testing. I know the function only checks
    // gameState's supplyCount variable
    // A more intelligent test should be created if we want to verify, by
    // checking the hand/deck of all players, how many cards are in play.
    G.supplyCount[copper] = 2;

    status = supplyCount(copper, &G);
    // The function returned an error (-1)

    myAssert (status == 2);
    status = 0;

    printf ("testSupplyCount passes.\n");

    return status;
}


int main()
{
    return testSupplyCount();
}
