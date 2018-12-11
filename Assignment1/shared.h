/******************************************************************************
 * Student Name    : Victor Ageev
 * RMIT Student ID : S3732094
 * COURSE CODE     : COSC2138
 *
 * Startup code provided by Paul Miller for use in "Programming in C",
 * study period 4, 2018.
 *****************************************************************************/
/**
 * This file contains the shared definitions required for the game.
 **/

/**
 * include guard to ensure that in each C source file "source translation unit"
 * that this module is only included once
 **/

#ifndef SHARED_H
#define SHARED_H

/**
 * The BOOLEAN datatype used in this application
 **/

typedef enum { /* FALSE comes first as we start counting at 0 */
               FALSE,
               TRUE
} BOOLEAN;

#endif /* end of include guard */
