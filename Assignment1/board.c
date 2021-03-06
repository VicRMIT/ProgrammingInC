/******************************************************************************
 * Student Name    : Victor Ageev
 * RMIT Student ID : S3732094
 * COURSE CODE     : COSC2138
 *
 * Startup code provided by Paul Miller for use in "Programming in C",
 * study period 4, 2018.
 *****************************************************************************/
#include "board.h"

/**
 * initialises the board to a known safe (empty) state
 **/
void board_init(gameboard aboard) {
    int i;
    int j;
    /* 
     * Iterates through height and width setting
     * all to C_BLANK
     */
    for (i = 0; i < BOARDHEIGHT; i++) {
        for (j = 0; j < BOARDWIDTH; j++) {
            aboard[i][j] = C_BLANK;
        }
    } 
}

/* you may wish to add further functions for the managing of the gameboard here
 */
BOOLEAN check_draw_condition(gameboard aboard) {
    int i;
    int j;
    /* 
     * Iterates through height and width
     * with draw condition false if any blanks
     * remain.
     */
    for (i = 0; i < BOARDHEIGHT; i++) {
        for (j = 0; j < BOARDWIDTH; j++) {
            if (aboard[i][j]==C_BLANK)
                return FALSE;
        }
    } 
    return TRUE;
}
