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
    if (coord->y < 1 || coord->y > BOARDHEIGHT || coord->x < 1 
            || coord->x > BOARDWIDTH){
        error_print("That entry is not a valid coordinate, please enter "
                    "comma delimited coordinates x,y: ");
        return FALSE; 
    }
    else if (board[coord->y-1][coord->x-1] == C_BLANK)
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
    int i;
    int j;
    int maxScore;
    int checkResult;
    maxScore = 0;
    /* 
     * Iterates through height and width settings
     * all to C_BLANK
     */
    for (i = 0; i < BOARDHEIGHT; i++) {
        for (j = 0; j < BOARDWIDTH; j++) {
            if (curplayer->curr_game->board[i][j]==curplayer->token) {
                /* four directions this needs to be done in */
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

    i = i_start;
    j = j_start;
    score = 1;
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
    if(curplayer->score == curplayer->curr_game->wincount)
       return TRUE;
    else
        return FALSE;
}
