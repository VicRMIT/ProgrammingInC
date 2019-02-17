/******************************************************************************
 * Student Name    : Victor Ageev
 * RMIT Student ID : s3732094
 * COURSE CODE     : CPT220
 *
 * Startup code provided by Paul Miller for use in "Programming in C",
 * study period 4, 2018.
 *****************************************************************************/
#include "helpers.h"
#include "shared.h"
#include <assert.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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

struct line_args {
    long start_line;
    long finish_line;
};

struct replace_pair {
    const char* search;
    const char* replace;
};

struct linelist_pair {
    struct line_list* found;
    struct line_list* replace;
};

/**
 * function prototypes for allocating, manipulating and freeing the line_list
 * and its components go here.
 **/
struct line_args* line_args(const char[]);
struct line* line_make(const char[], long);
struct line_list* linelist_make(void);
struct line_node* linenode_make(struct line*);
BOOLEAN linelist_insert(struct line_list*, const char[], long);
BOOLEAN linelist_append(struct line_list*, const char[]);
BOOLEAN line_print(const struct line*, FILE*);
BOOLEAN linelist_print(const struct line_list*, FILE*);
void linelist_free(struct line_list*);
void linenode_free(struct line_node*);
void line_free(struct line*);

#endif
