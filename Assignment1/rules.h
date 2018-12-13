/******************************************************************************
 * Student Name    : Victor Ageev
 * RMIT Student ID : S3732094
 * COURSE CODE     : COSC2138
 *
 * Startup code provided by Paul Miller for use in "Programming in C",
 * study period 4, 2018.
 *****************************************************************************/
#include "board.h"
#include "shared.h"
#include <math.h>
#include <stdarg.h>
#ifndef RULES_H
#define RULES_H

/*
 * The following enum is used to set iterators for traversing the board
 * when checking for the longest consecutive token position on the board.
 */
enum direction {
        EAST,
        SOUTH_EAST,
        SOUTH,
        SOUTH_WEST
};

struct game;
struct player;

struct coordinate {
        int x, y;
};

BOOLEAN is_valid_move(const struct coordinate *, gameboard);

int check_consecutive(int i, int j, struct player *, enum direction);

void apply_move(const struct coordinate *, struct player *);

BOOLEAN is_winner(struct player *);

void calculate_score(struct player *);
#endif
