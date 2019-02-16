/******************************************************************************
 * Student Name    :
 * RMIT Student ID :
 * COURSE CODE     :
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
        char line[BUFSIZ + EXTRACHARS];
        char* tok;
        /* open the file specified for reading and validate that it succeeded */
        FILE* reader = fopen(fname, "r");
        if (!reader) {
                error_print("%s\n", strerror(errno));
                return FALSE;
        }
        /* read each line and add it to the line list */
        while (fgets(line, BUFSIZ + EXTRACHARS, reader)) {
                /* check for buffer overflow */
                if (line[strlen(line) - 1] != '\n') {
                        /* if we are at the end of the file there may not be a
                         * newline character
                         */
                        if (!feof(reader)) {
                                error_print("%s\n", strerror(errno));
                                return FALSE;
                        }
                } else {
                        /* we know we got the full text to remove the newline */
                        line[strlen(line) - 1] = 0;
                }
                /* fold all lines to 80 chars */
                fold(line, LINELEN);
                if (strlen(line) == 0) {
                        if (!linelist_append(thelist, "")) {
                                return FALSE;
                        }
                } else {
                        /* split at the newline */
                        tok = strtok(line, "\n");
                        /* add each line to the line list */
                        while (tok) {
                                if (!linelist_append(thelist, tok)) {
                                        return FALSE;
                                }
                                tok = strtok(NULL, "\n");
                        }
                }
        }
        fclose(reader);
        if (thelist->file_name) {
                free(thelist->file_name);
        }
        thelist->file_name = strdup(fname);
        return TRUE;
}

BOOLEAN save_file(const char fname[], const struct line_list* thelist) {
        FILE* writer;
        writer = fopen(fname, "w");
        if (!writer) {
                error_print("%s\n", strerror(errno));
                return FALSE;
        }
        if (!linelist_print(thelist, writer)) {
                fclose(writer);
                return FALSE;
        }
        fclose(writer);
        return TRUE;
}
