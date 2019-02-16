/******************************************************************************
 * Student Name    :
 * RMIT Student ID :
 * COURSE CODE     :
 *
 * Startup code provided by Paul Miller for use in "Programming in C",
 * study period 4, 2018.
 *****************************************************************************/

#include "repl.h"
/**
 *
 * commands to be implemented for our repl:
 * - read(r): read a file into memory. Lines when read in must be wrapped at or
 *   before 80 characters.
 *
 * - write(w): write the lines in memory to a file - a file must have been
 *   previously loaded.
 *
 * - print(p): print out the lines of a file. Optionally a range of lines can
 *   be provided, either a single line number or a range where the first
 *   number must be lower than the second however both numbers must be within
 *   the range of the lines in the file loaded.
 *
 * - insert(i): specified by i followed by an integer within the range of 1
 *   to the number of lines in the file plus 1.
 *
 * - delete (d): specified by the letter d followed by a single number or 2
 *   numbers separated by a minus sign where the first number must be less
 *   than or equal to the second number.
 *
 * - search (s): specified by the letter s followed by a work or a phrase. The
 *   program will iterate over all the lines of the file and print out each
 *   line that contains the matching phrase. All leading spaces between the
 *   command and the first letter shall be ignored.
 *
 *   After printing out 25 matches, the user will be asked if they wish to
 *   continue and if they do, the next 25 lines that match will be printed.
 *
 *   The prompt which must be used to indicate that the program is ready for
 *   input is the > character. Any errors should have clear output so the user
 *   knows what they need to do to correct it.
 *
 *   All commands may have 0 or more spaces between the command and the
 *   argument. For
 **/

static void read_rest_of_line(void) {
        int ch;
        while (ch = getc(stdin), ch != '\n' && ch != EOF)
                ;
        clearerr(stdin);
}

void repl(const struct command commands[], char filename[]) {
        struct line_list* thelist;
        /* tell the compiler that the local definition of read_rest_of_line()
         * won't be used */
        (void)read_rest_of_line;
        /* create the list */
        thelist = linelist_make();
        /* load the file into the list */
        load_file(filename, thelist);
        /* print the list */
        linelist_print(thelist, stdout);
        /* save the file back to disk */
        save_file(filename, thelist);
        /* free the list */
        linelist_free(thelist);
}

/**
 * acts as a proxy to printf. All output sent here will go to normal output via
 * "stdout"
 **/
int normal_print(const char format[], ...) {
        va_list va_args;
        int output_chars;
        /* initialise the variable args */
        va_start(va_args, format);
        /* pass them to printf */
        output_chars = vprintf(format, va_args);
        /* finish with processing the variable args */
        va_end(va_args);
        /* return the number of chars written out */
        return output_chars;
}

/**
 * acts as a proxy to printf, except the output gets sent to stderr, the
 * error file pointer. . All output sent here will go to normal output via
 * "stdout"
 **/
int error_print(const char format[], ...) {
        va_list va_args;
        int output_chars;
        /* initialise the variable args */
        va_start(va_args, format);
        /* output preamble to an error message: */
        output_chars = fprintf(stderr, "Error: ");
        /* print the error message */
        output_chars += vfprintf(stderr, format, va_args);
        output_chars += fprintf(stderr, "\n");
        return output_chars;
}
