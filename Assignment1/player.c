/******************************************************************************
 * Student Name    : Victor Ageev
 * RMIT Student ID : S3732094
 * COURSE CODE     : COSC2138
 *
 * Startup code provided by Paul Miller for use in "Programming in C",
 * study period 4, 2018.
 *****************************************************************************/
#include "player.h"
#include "game.h"

/**
 * initialise the player by prompting and reading the player's name from
 * the keyboard. Set the rest of the elements of the player struct to sensible
 * values. and capture the game pointer in the player's game pointer so we
 * don't have to repeatedly pass it around later.
 **/
enum input_result player_init(struct player* curplayer, int playernum,
                              struct game* curgame) {
    enum input_result result;
    curplayer->score = 0;
    curplayer->curr_game = curgame;
    /* 
     * Loop that keeps trying to get a valid entry for player name until
     * successful or player quits.
     */
    while ((result=get_name(curplayer->name))!=IR_SUCCESS) {
        if (result == IR_RTM)
            return IR_RTM;        
    }
    return IR_SUCCESS;
}

/**
 * Prints out the current board and whose turn it is.  It then
 * handles input (and validation of input) for a turn. It then checks if the
 * the move requested is valid and if it is it applies it. For most of these
 * actions, a function should be called in another module.
 **/
enum input_result player_turn(struct player* curplayer) {
    char getTurn[SIZECOORDSTRING]={0}; 
    struct coordinate turnCoordinate;
    enum input_result result;

    print_game_status(curplayer->name, curplayer->score, curplayer->token);
    
    do { 
        while ((result=get_player_turn(getTurn)) != IR_SUCCESS) {
            if (result == IR_RTM)
                return IR_RTM;        
        }
        turnCoordinate.x = getTurn[XPOSITION]-'0';
        turnCoordinate.y = getTurn[YPOSITION]-'0';
    } while (is_valid_move(&turnCoordinate, curplayer->curr_game->board) != TRUE);

    apply_move(&turnCoordinate, curplayer);
    calculate_score(curplayer);

    return IR_SUCCESS;  
}
