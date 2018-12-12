/******************************************************************************
 * Student Name    : Victor Ageev
 * RMIT Student ID : S3732094
 * COURSE CODE     : COSC2138
 *
 * Startup code provided by Paul Miller for use in "Programming in C",
 * study period 4, 2018.
 *****************************************************************************/
#include "board.h"
#include <ctype.h>
#include <limits.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef IO_H
#define IO_H

/**
 * constant that defines the extra chars at the end of a string after a
 * successul call to fgets, namely the newline character followed by the null
 * terminator
 **/

#define EXTRACHARS 2

/**
 * constant defining a single line of input
 **/
#define LINELEN 80

/**
 * decimal is base 10 - this constant is required for use with strtol.
 **/
#define DECIMAL 10

/**
 * enumeration to identify colours available to be used on the system. These
 * colours were gotten from a stack overflow article:
 *
 * https://stackoverflow.com/questions/3219393/stdlib-and-colored-output-in-c
 *
 * Please note that I apply a convention of spelling where I use US spelling in
 * my code but australian spelling in comments.
 **/

enum color {
        COL_RED,
        COL_GREEN,
        COL_YELLOW,
        COL_BLUE,
        COL_MAGENTA,
        COL_CYAN,
        COL_RESET
};

/**
 * the count of colours in the above enumeration.
 **/

#define NUM_COLORS 7

/**
 * global array of strings used to change colours in output. This is extern as
 * the memory must be allocated in exactly one place and therefore can't be
 * done in a header file that may be included in multiple other files.
 **/

extern const char* color_strings[];

/**
 * enumeration that defines the possible values that can be returned from input/
 * output requests. Failure means that the result was undesirable, and thus
 * should be reprompted, success means we have a result we can pass onto the
 * next xtage and rtm means return to menu - so end the game.
 **/
enum input_result { IR_FAILURE, IR_SUCCESS, IR_RTM };

enum menu_choice {PLAY_GAME, DISPLAY_SCORE, EXIT_PROG, INVALID_SELECTION = EOF};
/**
 * functions implemented in this module. Please see io.c for further details
 **/

int normal_print(const char format[], ...);

int error_print(const char format[], ...);

int menuSelection();

void print_board(gameboard);

void print_game_status(char s[], int, enum cell);

enum input_result get_player_turn(char s[]);

enum input_result get_win_count(int *s);

enum input_result get_name(char s[]);

#endif
