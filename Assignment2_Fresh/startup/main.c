/******************************************************************************
 * Student Name    :
 * RMIT Student ID :
 * COURSE CODE     :
 *
 * Startup code provided by Paul Miller for use in "Programming in C",
 * study period 4, 2018.
 *****************************************************************************/

#include "main.h"

int main(int argc, char* argv[]) {
        /* the array of commands that can be used in this program */
        struct command commands[NUM_COMMANDS];
        /* initialise the commands */
        commands_init(commands);
        /* implement behaviour based on the number of arguments passed in */
        switch (argc) {
                case NOARGS:
                        repl(commands, NULL);
                        break;
                case FILEARGS:
                        repl(commands, argv[FILEARG]);
                        break;
                default:
                        /* if there are invalid arguments, display appropriate
                         * error messages and exit */
                        error_print("invalid arguments provided. \n");
                        print_usage();
                        return EXIT_FAILURE;
        }
        return EXIT_SUCCESS;
}

/**
 * common function name used for explaining how to use the program
 **/
void print_usage(void) {
        normal_print(
            "You may invoke this program with either no arguments which means "
            "that no file will be loaded or 1 argument which means that the "
            "file specified will be loaded. No other amount of arguments is "
            "accepted.\n");
}
