#include "myassert.h"
#include "dominion.h"
#include "dominion_helpers.h"
#include <stdio.h>
#include "rngs.h"
#include <stdlib.h>

int testVillageCard () {
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

    myAssert (status == 0);

    int choices[3] = {0};
    int pos;
    buyCard(village, &G);
    buyCard(village, &G);
    int loops = 0, cardFound = 0;
    while(cardFound == 0 && loops < 5) {
        for (pos=0, loops++; pos<numHandCards(&G); pos++)
            if (handCard(pos, &G) == village)
                cardFound = 1;
        endTurn(&G);
    }
    status = cardEffect(village,
                        choices[0], choices[1], choices[2],
                        &G, pos, NULL);

    myAssert (status == 0);


    printf ("testVillageCard passes.\n");

    status = 0;
    return status;
}

int main() {
    return testVillageCard();    
}
