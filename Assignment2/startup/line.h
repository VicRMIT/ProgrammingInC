/******************************************************************************
 * Student Name    : Victor Ageev
 * RMIT Student ID : s3732094
 * COURSE CODE     : CPT220
 *
 * Startup code provided by Paul Miller for use in "Programming in C",
 * study period 4, 2018.
 *****************************************************************************/
#include <assert.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "shared.h"
#ifndef LINE_H
#define LINE_H
struct line {
        char* data;
        long len;
        long lineno;
};

struct line_node {
        struct line* data;
        struct line_node* next;
};

struct line_list {
        struct line_node* head;
        char* file_name;
        long num_lines;
};

/**
 * function prototypes for allocating, manipulating and freeing the line_list
 * and its components go here.
 **/
void line_init(struct line* line);
void line_list_init(struct line_list * line_list);
BOOLEAN addnode(struct line_list * line_list, char[], struct line * data);
void list_print(struct line_list*);
void list_free(struct line_list * line_list);

#endif
