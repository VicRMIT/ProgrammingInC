/******************************************************************************
 * Student Name    : Victor Ageev
 * RMIT Student ID : s3732094
 * COURSE CODE     : CPT220
 *
 * Startup code provided by Paul Miller for use in "Programming in C",
 * study period 4, 2018.
 *****************************************************************************/

#include "command.h"
#include "line.h"
#include <stdarg.h>
#include <stdio.h>
#include <string.h>
enum input_result { IR_FAILURE, IR_SUCCESS, IR_RTM };
#ifndef REPL_H
#define REPL_H
#define INPUTSIZE 500
void repl(const struct command[], char[]);
int normal_print(const char[], ...);
int error_print(const char[], ...);
#endif
