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
    /*
     * First check is that the coordinates are within the board range.
     */
    if (coord->y < 1 || coord->y > BOARDHEIGHT || coord->x < 1 
            || coord->x > BOARDWIDTH){
        error_print("That entry is not a valid coordinate, please enter "
                    "comma delimited coordinates x,y: ");
        return FALSE; 
    }
    /*
     * Second check is that the valid board location is blank.
     */
    else if (board[coord->y-1][coord->x-1] == C_BLANK)
        return TRUE; 
    /*
     * If the board location is not blank, the move is invalid.
     */
    else {
        error_print("That is not a valid move! Please enter a different move in x,y format: ");
        return FALSE;
    }
}

/**
 * applies the move to the board
 **/
void apply_move(const struct coordinate *coord, struct player *curplayer) {
    /*
     * Put the player's token in the relevant position on the board.
     */
    curplayer->curr_game->board[coord->y-1][coord->x-1] = curplayer->token;
}

/**
 * iterates over all locations on the board and counts up how many tokens
 * occur in a row. The score for the player shall be the maximum number of
 * their tokens in a row vertically, horizontally or diagonally from any
 * position on the board.
 **/
void calculate_score(struct player *curplayer) {
    int i;
    int j;
    int maxScore;
    int checkResult;
    maxScore = 0;
    /* 
     * Iterates through every location of the board checking whether the
     * current player's token exists.
     */
    for (i = 0; i < BOARDHEIGHT; i++) {
        for (j = 0; j < BOARDWIDTH; j++) {
            if (curplayer->curr_game->board[i][j]==curplayer->token) {
                /* 
                 * Each player token position is a starting point for counting
                 * consecutive tokens. Because of the traversal direction 
                 * (top-left to bottom-right), only four directions need to be
                 * checked. The check_consecutive function is called for all
                 * the relevant directions. If the consecutive count is greater
                 * than the current maximum, that becomes the score.
                 */
                if((checkResult =check_consecutive(i, j, curplayer, EAST))>maxScore)
                    maxScore = checkResult;
                if((checkResult =check_consecutive(i, j, curplayer, SOUTH_EAST))>maxScore)
                    maxScore = checkResult;
                if((checkResult =check_consecutive(i, j, curplayer, SOUTH))>maxScore)
                    maxScore = checkResult;
                if((checkResult =check_consecutive(i, j, curplayer, SOUTH_WEST))>maxScore)
                    maxScore = checkResult;
            }
        }
    }
    curplayer->score = maxScore;
}


int check_consecutive(int i_start, int j_start, struct player *curplayer, enum direction dir) {
    int horizontalIterator;
    int verticalIterator;
    int score;
    int i;
    int j;
    int iterations;
    /* 
     * Iteration starts from the location of the player's token
     */
    i = i_start;
    j = j_start;
    score = 1;
    /*
     * Iterators determine the direction of the loop below, and are set based on the 
     * desired traversal direction.
     */
    switch (dir) {
        case EAST:
            horizontalIterator = 1;
            verticalIterator = 0;
            break;
        case SOUTH_EAST:
            horizontalIterator = 1;
            verticalIterator = 1;
            break;
        case SOUTH:
            horizontalIterator = 0;
            verticalIterator = 1;
            break;
        case SOUTH_WEST:
            horizontalIterator = -1;
            verticalIterator = 1;
            break;
    } 
    /*
     * For loop moves in the appropriate direction along the board, adding 1
     * to the calculated score for each consecutive player token. A blank
     * space terminates the loop.
     */
    for (iterations = 0; iterations < BOARDWIDTH-1; iterations++) {
        i = i + verticalIterator;
        j = j + horizontalIterator;
        if (i > -1 && i < BOARDHEIGHT && j > -1 && j < BOARDWIDTH) {

            if (curplayer->curr_game->board[i][j]==curplayer->token) {
                score++;
            } else {
                i=BOARDHEIGHT;
                j=BOARDWIDTH;
            }
        }
    }

    return score;
}
/**
 * tests for a winner by searching the board for any sequence that is greater
 * than or equal to the current player's token being wincount times in a row.
 **/
BOOLEAN is_winner(struct player *curplayer) {
    /*
     * If the current player's score is equal to or greater than
     * the required wincount, they win the game.
     */
    if(curplayer->score >= curplayer->curr_game->wincount)
       return TRUE;
    else
        return FALSE;
}
