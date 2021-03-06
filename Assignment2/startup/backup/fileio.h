/******************************************************************************
 * Student Name    : Victor Ageev
 * RMIT Student ID : s3732094
 * COURSE CODE     : CPT220
 *
 * Startup code provided by Paul Miller for use in "Programming in C",
 * study period 4, 2018.
 *****************************************************************************/

#include "shared.h"
#include "line.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>

#ifndef FILEIO_H
#define FILEIO_H

BOOLEAN load_file(const char[], struct line_list*);
BOOLEAN save_file(const char[], const struct line_list*);

#endif
