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
    FILE * input; 
    char charline[LINELEN + EXTRACHARS];
    struct line newLine;
    char * file_name;
    file_name  = strdup(fname);
    line_init(&newLine); 
 /*   newLine = safemalloc(sizeof(struct line));*/
        
    if((input = fopen(file_name, "r")) == NULL)
    {
        error_print("Failed to open file");
        return FALSE;
    }

    thelist->file_name = file_name;

    while(fgets(charline, BUFSIZ, input) != NULL)
    {
        if(charline[strlen(charline)-1]!='\n')
        {
            fprintf(stderr, "Implement fold");
            return FALSE;
        }
        charline[strlen(charline)]=0;
       
        if(!addnode(thelist, charline, &newLine))
        {
            fprintf(stderr, "Error adding lines");
            return FALSE;
        }
    }
    fclose(input);
    return TRUE;
}

/**
 * saves the file represented by the line_list to the filename specified
 **/
BOOLEAN save_file(const char fname[], const struct line_list* thelist) {
    FILE * output;
    struct line_node * current = thelist->head;
    
    output=gwopen(fname);

    while(current!=NULL)

    {
        struct line_node * next;
        next = current;
        current = current->next;
        if(fprintf(output, "%s\n", next->data->data) < 0)
        {
            error_print("Failed to save file");
            return FALSE;
        } 
    }
    fclose(output);
    return TRUE;

}

FILE* gwopen(const char * fname)
{
    FILE * fp;
    if((fp=fopen(fname,"w"))==NULL)
    {
        error_print("Failed to prepare file for saving");
        exit(EXIT_FAILURE);
    }
    return fp;
}
  
