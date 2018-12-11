/******************************************************************************
 * Student Name    : Victor Ageev
 * RMIT Student ID : S3732094
 * COURSE CODE     : COSC2138
 *
 * Startup code provided by Paul Miller for use in "Programming in C",
 * study period 4, 2018.
 *****************************************************************************/
#include "game.h"

/**
 * initialise the game to a safe state. Think a little bit about the nature of
 * the data. then, call board_init() to initialise the board to be empty,
 *
 **/
BOOLEAN init_game(struct game* thegame) { 
    
    /* FALSE is being returned here because there's no implementation yet.
     * In your implementation you need to initialise all elements of the game
     * struct including the players (get their name as assign tokens randomly). 
     * You should also decide who is going first (use random) and assign the 
     * pointers to current and other appropriately.
     */
    enum input_result result;
    int i;

    board_init(thegame->board);

    normal_print("Please enter a number between 3 and 8 for the minimum number in a "
            "row required for a win: ");

    while ((result = get_win_count(&thegame->wincount))!=IR_SUCCESS) {
        if (result==IR_RTM)
            return FALSE;
    }

    for (i=0; i<NUMPLAYERS; i++) {
        normal_print("Please enter a name for player %d: ", i+1);
        while ((result = player_init(&thegame->players[i], i+1, 
                        thegame))!=IR_SUCCESS) {
            if (result == IR_RTM)
                return FALSE;
        }
    }
    
    thegame->players[0].token = C_NOUGHT ;   
    thegame->players[1].token = C_CROSS ;   
    thegame->current = &thegame->players[0];
    thegame->other = &thegame->players[1];

    return TRUE; 
}

/**
 * defines the progress of the game in a broad sense. You should call
 * init_game() to initialise the game's data structures including the game
 * and the board. Next, perform the game loop until either the board is full
 * or a player has won the game. Finally when the game ends, you should print
 * out the details about how the game has been completed.
 **/
struct player* play_game(struct player players[]) {
        /* this declaration also allocates memory for what is contained in the
         * game struct */
        struct game thegame;

        /* we need to attach the players array to the game struct as the players
         * need to be allocated outside of play_game() so we can return the
         * player to main()
         */
        
        thegame.players = players;
        /* initialise the game */

        if (init_game(&thegame)!=FALSE) {
            print_board(thegame.board);
            print_game_status(thegame.current->name, thegame.current->score, 
                thegame.current->token);
        }

        /* the game loop - continue until there is a winner or all spots have
         * been filled up
         */
                /* if the attempt to move failed , reprompt for the move */
                /* if the game has been won or the board is full, the game is
                 * over */

        /* when the game is over, we will reprint out the board and detail
         * who the winner is, if there was a winner. If the board is full the
         * game is drawn and if the game was quit early such as by pressing
         * enter or ctrl-d on a new line, we will also print out that
         * information
         */

        /* replace this return statement with appropriate logic for determining 
         * the winner and return that 
         */
        return NULL;
}

/**
 * swap the player pointers passed in so that first points to the address second
 * used to and vice-versa. It is common in c when you want to swap where a
 * ponter points to pass in its address.
 **/
void swap_players(struct player** first, struct player** second) {
    struct player* firstPlayer;
    firstPlayer = * first;
    *first = *second;
    *second = firstPlayer;
}
