#include "assert.h"
#include "dominion.h"
#include "dominion_helpers.h"
#include <stdio.h>
#include "rngs.h"
#include <stdlib.h>

int testMineCard() {
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

    int pos;
    buyCard(mine, &G);
    buyCard(mine, &G);
    int loops = 0, cardFound = 0;
    while(cardFound == 0 && loops < 5) { 
        for (pos=0, loops++; pos<numHandCards(&G); pos++)
            if (handCard(pos, &G) == smithy)
                cardFound = 1;
        endTurn(&G);
    }
    int i, choices[3] = {0, 1, 2};
    for (i=0 ; i<3 ; i++)
        if (choices[i] == pos)
            choices[i] += 3;
    status = cardEffect(mine,
                        choices[0], choices[1], choices[2],
                        &G, pos, NULL);

    assert (status == 0);


    printf ("testMineCard passes.\n");

    status = 0;
    return status;
}

int main() {
    return testMineCard();    
}
