/******************************************************************************
 * Student Name    : Victor Ageev
 * RMIT Student ID : s3732094
 * COURSE CODE     : CPT220
 *
 * Startup code provided by Paul Miller for use in "Programming in C",
 * study period 4, 2018.
 *****************************************************************************/
#include "helpers.h"
#include "repl.h"
#include "line.h"
/**
 * loads the file specified from disk into a line_list.
 **/
BOOLEAN load_file(const char fname[], struct line_list* thelist) {
    char charline[BUFSIZ + EXTRACHARS];
    char* tok;
    FILE* input = fopen(fname, "r"); 
        
    if(!input)
    {
        error_print("Failed to open file\n");
        return FALSE;
    }

    while(fgets(charline, BUFSIZ + EXTRACHARS, input))
    {
        if(charline[strlen(charline)-1]!='\n')
        {
            if(!feof(input)) {
                error_print("%s\n", strerror(errno));
                return FALSE;
            }
        } else {
            charline[strlen(charline) - 1] = 0;
        }
        fold(charline, LINELEN);
        if (strlen(charline)==0) {
            if(!linelist_append(thelist, "")) {
                return FALSE;
            }
        } else {
            tok = strtok(charline,"\n");
            while(tok) {
                if(!linelist_append(thelist, tok)) {
                    return FALSE;
                }
                tok = strtok(NULL, "\n");
            }
        }
    }
    fclose(input);
    if(thelist->file_name) {
        free(thelist->file_name);
    }
    thelist->file_name = strdup(fname);
    return TRUE;
}

/**
 * saves the file represented by the line_list to the filename specified
 **/
BOOLEAN save_file(const char fname[], const struct line_list* thelist) {
    FILE * output;
    output = fopen(fname, "w"); 
    if(!output) {
        error_print("%s\n", strerror(errno));
        return FALSE;
    }
    if(!linelist_print(thelist, output)) {
        fclose(output);
        return FALSE;
    }
    fclose(output);
    return TRUE;

}

