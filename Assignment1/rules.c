/******************************************************************************
 * Student Name    : Victor Ageev
 * RMIT Student ID : S3732094
 * COURSE CODE     : COSC2138
 *
 * Startup code provided by Paul Miller for use in "Programming in C",
 * study period 4, 2018.
 *****************************************************************************/
#include "rules.h"
#include "game.h"

/**
 * validates that the move passed in would be legal if applied
 **/
BOOLEAN is_valid_move(const struct coordinate *coord, gameboard board) {
    if (board[coord->y-1][coord->x-1] == C_BLANK)
        return TRUE; 
    else {
        error_print("That is not a valid move! Please enter a different move in x,y format: ");
        return FALSE;
    }
}

/**
 * applies the move to the board
 **/
void apply_move(const struct coordinate *coord, struct player *curplayer) {
    curplayer->curr_game->board[coord->y-1][coord->x-1] = curplayer->token;
}

/**
 * iterates over all locations on the board and counts up how many tokens
 * occur in a row. The score for the player shall be the maximum number of
 * their tokens in a row vertically, horizontally or diagonally from any
 * position on the board.
 **/
void calculate_score(struct player *curplayer) {
}

/**
 * tests for a winner by searching the board for any sequence that is greater
 * than or equal to the current player's token being wincount times in a row.
 **/
BOOLEAN is_winner(struct player *curplayer) {
    if(curplayer->score == curplayer->curr_game->wincount)
       return TRUE;
    else
        return FALSE;
}
