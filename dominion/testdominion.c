#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>

#define NUM_GAMES 20
#define RAND_SEED 4

struct cards cardsCounter(struct gameState * g);
char * cardStr(int card);
int cardPos(int c, struct gameState * g);

struct cards {
    int copper;
    int silver;
    int gold;
    int adventurer;
    int gardens;
    int embargo;
    int village;
    int minion;
    int mine;
    int cutpurse;
    int sea_hag;
    int tribute;
    int smithy;
};

int main()
{
    int i1, i2, i3, seed, randomNumber, moves;
    struct gameState * gState;

    seed = RAND_SEED;
    srand(seed);
    printf("Random seed is %i \n", seed);

    for (i1=0 ; i1<NUM_GAMES ; i1++)
    {
        printf("Initializing game #%i \n", i1);

        randomNumber = rand();
        printf("Random number is %i \n", randomNumber);

        int numPlayers = randomNumber % 2 + 2;
        printf("Number of players is %i \n", numPlayers);

        // Allocate memory and create cards array.
        gState = malloc(sizeof(struct gameState));
        int kingdomCards[10] = {adventurer, gardens, embargo, village, minion,
                                mine, cutpurse, sea_hag, tribute, smithy};

        // Call the initailize game function,
        // Tests assume that this works.
        initializeGame(numPlayers, kingdomCards, randomNumber, gState);

        ////
        // Buying Preferences:
        //   Players 0 and 2:
        //     5+: Dutchy
        //     3+: Silver
        //     0+: Copper
        //   Players 1 and 3:
        //     5+: Mine
        //     3+: Village
        //     0+: Copper
        ////
        int * pref;
        int prefEven[3] = {duchy, village, copper};
        int prefOdd[3] = {mine, silver, copper};

        moves = 0;
        // While the game is still going
        while (!isGameOver(gState))
        {
            moves += 1;
            // Count up the current player's cards
            struct cards cCount = cardsCounter(gState);

            // If players 0 or 2 are playing
            if (whoseTurn(gState) % 2 == 0)
                pref = prefEven;
            // If players 1 or 3 are playing
            else
                pref = prefOdd;

            // Action Phase
            i2 = 0;

            // talley up the money
            int money = cCount.silver + cCount.gold + cCount.copper;
            // For every card in the player's hand
            while( numHandCards(gState) > i2 )
            {
                for( i3=0 ; i3<3 ; i3++ )
                {
                    // If the player has that card in their preference list 
                    if( handCard(i2, gState) == pref[i3] )
                    {
                        // Play the card
                        // If that card is a mine
                        if( pref[i3] == mine )
                        {
                            int count1, count2;
                            // And the player has any copper
                            if( cardPos(copper, gState) > 0 )
                            {
                                // Use the mine to trade the copper for a silver
                                // Count the number of silvers and coppers before the use of mine
                                count1 = fullDeckCount(whoseTurn(gState), copper, gState);
                                count2 = fullDeckCount(whoseTurn(gState), silver, gState);
                                playCard(i2, cardPos(copper, gState), silver, -1, gState);
                                printf("Player %i played a %s from position %i \n", whoseTurn(gState),
                                                                                    cardStr(pref[i3]),
                                                                                    i2);
                                // Assert that the new count is -1 for the copper and +1 for the silver
                                assert(fullDeckCount(whoseTurn(gState), copper, gState) == count1-1);
                                assert(fullDeckCount(whoseTurn(gState), silver, gState) == count2+1);
                            }
                            else if( cardPos(silver, gState) > 0 )
                            {
                                count1 = fullDeckCount(whoseTurn(gState), silver, gState);
                                count2 = fullDeckCount(whoseTurn(gState), gold, gState);
                                playCard(i2, cardPos(silver, gState), gold, -1, gState);
                                printf("Player %i played a %s from position %i \n", whoseTurn(gState),
                                                                                    cardStr(pref[i3]),
                                                                                    i2);
                                assert(fullDeckCount(whoseTurn(gState), silver, gState) == count1-1);
                                assert(fullDeckCount(whoseTurn(gState), gold, gState)   == count2+1);
                            }
                        }
                        else
                        {
                            // Otherwise just play the card you've got.
                            // This has a byproduct of 'playing' money and victory cards
                            // While this isn't strictly the way you play the game, it is
                            // a side effect that helps in reproducing the game later.
                            playCard(i2, -1, -1, -1, gState);
                            printf("Player %i played a %s from position %i \n", whoseTurn(gState),
                                                                                cardStr(pref[i3]),
                                                                                i2);
                        }
                        break;
                    }
                }
                i2 += 1;
            }

            // Buy Phase
            while( money > 0 )
            {
                // If the player has 5+ money, buy a dutchy or mine
                if( money >= 5 )
                {
                    printf("Player %i bought a %s \n", whoseTurn(gState), cardStr(pref[2]));
                    buyCard(pref[2], gState);
                    money -= 5;
                }

                // If the player has 3+ money buy a silver or village
                if( money >= 3 )
                {
                    printf("Player %i bought a %s \n", whoseTurn(gState), cardStr(pref[1]));
                    buyCard(pref[1], gState);
                    money -= 3;
                }

                // If the player has no money, buy a copper
                if( money >= 0 )
                {
                    printf("Player %i bought a %s \n", whoseTurn(gState), cardStr(pref[0]));
                    buyCard(pref[0], gState);
                    money = 0;
                }
            }

            printf("Scores:\n");
            for( i2=0 ; i2<numPlayers ; i2++ )
            {
                printf("Player %i, score %i \n", i2, scoreFor(i2, gState));
            }

            // Clean-up Phase
            endTurn(gState);
            printf("%i has ended their turn \n", whoseTurn(gState));
        }

        printf("Final Scores:\n");
        for( i2=0 ; i2<numPlayers ; i2++ )
        {
            printf("Player %i, score %i \n", i2, scoreFor(i2, gState));
        }
        printf("%i moves played \n", moves);

        // Clean up any loose memory.
        free(gState);
        printf("############################################################\n");
        printf("################ Thank you for not playing #################\n");
        printf("############################################################\n");
    }
    return 0;
}

// Collects data on the current player's hand
struct cards cardsCounter(struct gameState * g)
{
    struct cards c;
    int i;

    c.copper = c.silver = c.gold = c.adventurer = c.gardens = c.embargo =
    c.village = c.minion = c.mine = c.cutpurse = c.sea_hag = c.tribute =
    c.smithy = 0;    

    for (i = 0; i < numHandCards(g); i++) {
        if (handCard(i, g) == copper)
            c.copper += 1;
        else if (handCard(i, g) == silver)
            c.silver += 1;
        else if (handCard(i, g) == gold)
            c.gold += 1;
        else if (handCard(i, g) == adventurer)
            c.adventurer += 1;
        else if (handCard(i, g) == gardens)
            c.gardens += 1;
        else if (handCard(i, g) == embargo)
            c.embargo += 1;
        else if (handCard(i, g) == village)
            c.village += 1;
        else if (handCard(i, g) == minion)
            c.minion += 1;
        else if (handCard(i, g) == mine)
            c.mine += 1;
        else if (handCard(i, g) == cutpurse)
            c.cutpurse += 1;
        else if (handCard(i, g) == sea_hag)
            c.sea_hag += 1;
        else if (handCard(i, g) == tribute)
            c.tribute += 1;
        else if (handCard(i, g) == smithy)
            c.smithy += 1;
    }

    return c;
}

// returns the string representation of a card
char * cardStr(int card)
{
    char * strs[27] = {"curse", "estate", "duchy", "province", "copper", "silver",
    "gold", "adventurer", "council_room", "feast", "gardens", "mine",
    "remodel", "smithy", "village", "baron", "great_hall", "minion", "steward",
    "tribute", "ambassador", "cutpurse", "embargo", "outpost", "salvager",
    "sea_hag", "treasure_map"};

    return strs[card];
}

// returns the position of a card in the playe's hand
int cardPos(int c, struct gameState * g)
{
    int i;
    for( i=0 ; i<numHandCards(g) ; i++ )
    {
        if( handCard(i, g) == c )
        {
            return i;
            break;
        }
    }
    return 0;
}
