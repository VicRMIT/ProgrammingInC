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

/**
 * function prototypes for allocating, manipulating and freeing the line_list
 * and its components go here.
 **/
struct line* line_init(const char[], long);
struct line_list* line_list_init(void);
struct line_node* line_node_init(struct line*);
BOOLEAN list_insert(struct line_list*, const char[], long);
BOOLEAN list_append(struct line_list*, const char[]);
BOOLEAN line_print(const struct line*, FILE*);
BOOLEAN linelist_print(const struct line_list*, FILE*);
void list_free(struct line_list*);
void node_free(struct line_node*);
void line_free(struct line*);

#endif
