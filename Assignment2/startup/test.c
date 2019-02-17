/******************************************************************************
 * Student Name    : Victor Ageev
 * RMIT Student ID : s3732094
 * COURSE CODE     : CPT220
 *
 * Startup code provided by Paul Miller for use in "Programming in C",
 * study period 4, 2018.
 *****************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


struct line_args {
    long start_line;
    long finish_line;
};

int main(int argc, char* argv[]) {
    int count;
    struct line_args* activeLines;
    char* tok;
    char testText[10] = "3-5 ";
    tok = strtok(testText,"-");
    activeLines = (struct line_args*)malloc(sizeof(struct line_args));
    count = 0;
    while(tok) {
        if(count<2) {
            printf("%s",tok);
            if (count==0)
                activeLines->start_line=strtol(tok,NULL,10);
            else
                activeLines->finish_line=strtol(tok,NULL,10);
        }
        count++;
        tok = strtok(NULL,"-");
    }
    free(activeLines);
    return EXIT_SUCCESS;
}
