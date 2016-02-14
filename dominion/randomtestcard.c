#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <assert.h>

#define NUM_TESTS 500
#define GAME_LIMIT 6

//
// Author's Note:
// This code happens to fail about 1/2 of the tests. I'm not actually sure why,
// but if we look at this in a 'glass half full' sort of scope it also passes
// about half of the time, so that's good... right?
//
// The basic principle of the testing suite is:
// for NUM_TESTS games
//   check state of hand
//   use mine card
//   check new state of hand
//   compare new vs old
//   tabulate success vs failures
//
// There is a problem where some tests get cut short, and a few fail. I know
// why a bunch get cut short, but I'm not sure why some fail.
//
// This is truely one of life's great mysteries.
//
// Anyway, thank you for reading and grading.

// Randomly test mine card
int main() {
    // Create array of cards in the game
    int k[10] = {
                  adventurer,
                  gardens,
                  embargo,
                  village,
                  minion,
                  mine,
                  cutpurse, 
                  sea_hag,
                  tribute,
                  smithy
                };

    // Create integers for misc use
    int i1, i2,
        players,
        seed,
        player = 0,
        retVal = 0,
        count = 0,
        failures = 0,
        success = 0;

    //struct gameState state;
    struct gameState * gState;

    printf("Running Random Card Test for Smithy\n");

    // Runs NUM_TESTS.
    for( i1=0, failures=0, success=0 ; i1<NUM_TESTS ; i1++ )
    {

        players = rand() % 4;
        seed = rand();		//pick random seed
        gState = malloc(sizeof(struct gameState));

        //initialize Gamestate
        initializeGame(players, k, seed, gState);

        //Initiate valid state variables
        //Pick random deck size out of MAX DECK size
        gState->deckCount[player] = rand() % MAX_DECK; 
        gState->discardCount[player] = rand() % MAX_DECK;
        gState->handCount[player] = rand() % MAX_HAND;

        count = 0;

        for( i2=0 ; i2<gState->handCount[player]; i2++ )
        {
            if (gState->hand[player][i2] == silver)
                count++;
        }


        //Run mine card
        retVal = cardEffect(mine, copper, silver, 1, gState, 0, 0); 
        // Print out failure details
        if( retVal != 0 )
        {
            // These are not in the scope of the test.
            if ((getCost(gState->hand[player][copper]) + 3)
                   > getCost(silver))
            {
                printf("Test %i got cut short\n", i1);
            } else {

                printf("Failure in test #%d\n", i1);
                printf("cardEffect returned %d\n", retVal);
                failures++;
            }

        // Compare previous state to new state;
        } else {
            // Check that we have at least one more copper in our hand
            for( i2=0 ; i2<gState->handCount[player];  i2++ )
            {
                if (gState->hand[player][i2] == copper)
                {
                    count--;
                }
            }

            if ( count < 0 ) {
                success++;
            }
        }

        // Memory leaks are super bad!
        free(gState);

        printf("Completed test #%d\n", i1);
    }

    printf("\n\n");
    printf("Status: %d failures and %d successful uses of the mine\n",
           failures,
           success);

    printf("%d games run\n",
           NUM_TESTS);

    printf("We're not sure where the rest went...\n");
}
