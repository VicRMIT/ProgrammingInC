/******************************************************************************
 * Student Name    : Victor Ageev
 * RMIT Student ID : S3732094
 * COURSE CODE     : COSC2138
 *
 * Startup code provided by Paul Miller for use in "Programming in C",
 * study period 4, 2018.
 *****************************************************************************/
#include "scores.h"
#include "helpers.h"
/**
 * static scoreboard that you will populate with data on each game winner. It
 * is static which means it's only accessible from inside this module
 **/

void scoreboard_init(struct score scores[]) {
    int i;
    for (i=0; i<sizeof(*scores); i++) {
        scores[i].score = 0;
    }
}

/**
 * adds a score to the scoreboard in sorted order by score so that higher
 * scores are at the top
 **/
BOOLEAN scoreboard_add(struct score scores[], const struct player* winner) {
    int i;
    qsort(scores, NUM_SCORES, sizeof(struct score), compare_score_asc);

    for (i=0; i<NUM_SCORES; i++) {
        if (winner->score > scores[i].score) {
            strcpy(scores[i].player, winner->name);
            scores[i].score = winner->score;
            i = NUM_SCORES;
        }
    }
    qsort(scores, NUM_SCORES, sizeof(struct score), compare_score_desc);
    return TRUE;
}

/**
 * prints out the scoreboard according to the format specified in the
 * assignment specification
 **/
void scoreboard_print(struct score scores[]) {
    int scoresPrinted;
    int i;
    scoresPrinted = 0;
    print_scoreboard_title();
    for (i=0; i<NUM_SCORES; i++) {
        if (scores[i].score != 0) {
            if (scoresPrinterd == 0)
                print_scoreboard_header();
            print_scoreboard(scores[i].player, scores[i].score);
            scoresPrinted++;
        }
    }
    if (scoresPrinted == 0)
        print_no_score();
}
