/******************************************************************************
 * Student Name    :
 * RMIT Student ID :
 * COURSE CODE     :
 *
 * Startup code provided by Paul Miller for use in "Programming in C",
 * study period 4, 2018.
 *****************************************************************************/

#ifndef SHARED_H
#define SHARED_H
typedef enum {
        FALSE,
        TRUE
} BOOLEAN;
#define LINELEN 80
#define EXTRACHARS 2

struct result {
        BOOLEAN success;
        char error_string[LINELEN + 1];
};
#endif
