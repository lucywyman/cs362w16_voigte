#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <assert.h>

#define NUM_TESTS 500
#define GAME_LIMIT 6

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
        retVal,
        count,
        failures,
        success;

    //struct gameState state;
    struct gameState * gState;

    printf("Running Random Card Test for Adventure\n");

    // Runs NUM_TESTS.
    for( i1=0, failures=0, success=0; i1<NUM_TESTS ; i1++ )
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

        // Gather initial data to compare against later
        // Check for treasure cards
        count = 0;
        for( i2=0 ; i2<gState->handCount[player]; i2++ )
        {
            if((gState->hand[player][i2] == copper) ||
               (gState->hand[player][i2] == silver) ||
               (gState->hand[player][i2] == gold))
                count++;
        }

        //Run adventure card
        cardEffect(adventurer, 1, 1, 1, gState, 0, 0); 

        // Test that the card did a thing
        for( i2=0 ; i2<gState->handCount[player]; i2++ )
        {
            if((gState->hand[player][i2] == copper) ||
               (gState->hand[player][i2] == silver) ||
               (gState->hand[player][i2] == gold))
                count--;
        }
        if( count < 0 )
        {
            success++;
        } else {
            failures++;
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

    printf("We're not sure where the failures came from. We're gonna get a guy"
           " in here to fumigate later this week.\n");
}
