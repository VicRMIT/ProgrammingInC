/******************************************************************************
 * Student Name    : Victor Ageev
 * RMIT Student ID : s3732094
 * COURSE CODE     : CPT220
 *
 * Startup code provided by Paul Miller for use in "Programming in C",
 * study period 4, 2018.
 *****************************************************************************/
#include "fileio.h"
#include "repl.h"
#include "helpers.h"
/**
 * loads the file specified from disk into a line_list.
 **/
BOOLEAN load_file(const char fname[], struct line_list* thelist) {
    FILE * input; 
    long line_count;
    char charline[LINELEN + EXTRASPACES];
    char fnameCopy; 
    line_count = 0;
    if((input = fopen(fname, "r")) == NULL)
    {
        error_print("Failed to open file");
        return FALSE;
    }
    fnameCopy = *strdup(fname);
    thelist->file_name = &fnameCopy;

    while(fgets(charline, LINELEN+EXTRASPACES, input) == NULL)
    {
        if(charline[strlen(charline)-1]!='\n')
        {
            fprintf(stderr, "Implement fold");
            return FALSE;
        }
        charline[strlen(charline)]=0;
        
       addNode(&thelist, charline, line_count++);
    }
    thelist->num_lines = line_count;
    return TRUE;
}

/**
 * saves the file represented by the line_list to the filename specified
 **/
BOOLEAN save_file(const char fname[], const struct line_list* thelist) {
        return FALSE;
}
