/******************************************************************************
 * Student Name    : Victor Ageev
 * RMIT Student ID : S3732094
 * COURSE CODE     : COSC2138
 *
 * Startup code provided by Paul Miller for use in "Programming in C",
 * study period 4, 2018.
 *****************************************************************************/
#include "main.h"
#include "io.h"

int main(void) {
        /**
         * allocation of players they are available after the end of the game.
         * Please note we are required to do this as items on the system
         * stack are removed once we leave the block in which they were
         * allocted.
         **/
        struct player players[NUMPLAYERS];
        /* pointer to the winner - at the end of the game if this is not NULL,
         * this is the winner of the game just played
         */
        
        struct player *winner;
        
        /* scoreboard for the program - add winners to this scoreboard */
        struct score scores[NUM_SCORES];
        /* menuSelection char to process user selections on menu */
        int menuSelected;
        /* initialise the scores */
        scoreboard_init(scores);
        /* repeatedly display the menu until the decision is made to quit.
         * Allow the options to play the game, display high scores or
         * quit
         */
        do {

            menuSelected = menuSelection();
            if (menuSelected == PLAY_GAME) {
                if ((winner = play_game(players))!=NULL) {
                    scoreboard_add(scores, winner);
                }
            } else if (menuSelected == DISPLAY_SCORE) {
                scoreboard_print(scores);
                /* getchar();*/                
            }
            
        } while (menuSelected !=EXIT_PROG); 

        return EXIT_SUCCESS;
}

