#include "assert.h"
#include "dominion.h"
#include <stdio.h>
#include "rngs.h"
#include <stdlib.h>

int testShuffle()
{
    //
    // Tests that shuffle works properly
    //

    // Status of test
    // set to 0 if the test didn't crash,
    // set to -1 if the test fails to finish,
    int status = -1;

    // Create play variable
    int p = 0;

    // Create gamestate
    struct gameState G;

    // Manually setup G to be sufficient for testing
    G.deckCount[p] = 3;
    G.deck[p][0] = copper;
    G.deck[p][1] = silver;
    G.deck[p][2] = gold;

    // shuffle the cards
    // Return status if shuffle failed internally (short-circut test)
    status = shuffle(p, &G);
    if (status < 0)
        return status;

    // Create a deck initialized at 0
    int cardsSet[MAX_DECK] = {0};
    int i;
    // For each of the cards we had, set cardSet's index of that card to 1
    for (i=0 ; i<3 ; i++)
    {
        cardsSet[G.deck[p][i]] = 1;
    }

    // If all of those cards are set to 1 (non-zero really)
    // set status to 1
    assert (cardsSet[copper] && cardsSet[silver] && cardsSet[gold]);
    status = 0;

    printf ("testShuffle passes.\n");

    return status;
}


int main()
{
    return testShuffle();
}
