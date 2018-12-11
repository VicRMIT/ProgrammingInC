/******************************************************************************
 * Student Name    : Victor Ageev
 * RMIT Student ID : S3732094
 * COURSE CODE     : COSC2138
 *
 * Startup code provided by Paul Miller for use in "Programming in C",
 * study period 4, 2018.
 *****************************************************************************/
#include "helpers.h"

void remove_newlines(char s[]) {
    char *newlinePointer;
    while ((newlinePointer = (strrchr(s, '\n'))) != NULL) {
        *newlinePointer = '\000';        
    }
}
