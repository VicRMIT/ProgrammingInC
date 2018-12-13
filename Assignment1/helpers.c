/******************************************************************************
 * Student Name    : Victor Ageev
 * RMIT Student ID : S3732094
 * COURSE CODE     : COSC2138
 *
 * Startup code provided by Paul Miller for use in "Programming in C",
 * study period 4, 2018.
 *****************************************************************************/
#include "helpers.h"
#include "scores.h"

/*
 * Conversion of const void to score data structures was developed with
 * reference to a stackoverflow answer, see [2] in readme.txt 
 */

int compare_score_asc(const void *a, const void *b) {
    /* 
     * Comparison function is positive if the first score
     * is smaller than the following score, meaning a goes
     * before b
     */
    struct score *scoreA = (struct score *) a;
    struct score *scoreB = (struct score *) b; 
    return (scoreA->score-scoreB->score);
}
int compare_score_desc(const void *a, const void *b) {
    /*
     * Comparison function is negative if the first score
     * is smaller than the following score, meaning b goes
     * before a.
     */
    struct score *scoreA = (struct score *) a;
    struct score *scoreB = (struct score *) b; 
    return (scoreB->score-scoreA->score);
}

/*
 * Function for removing new line characters. While loop returns the address
 * of each newline character until there aren't any left, and sets it to the
 * character '\000'
 */
void remove_newlines(char s[]) {
    char *newlinePointer;
    while ((newlinePointer = (strrchr(s, '\n'))) != NULL) {
        *newlinePointer = '\000';        
    }
}
