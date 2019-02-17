/******************************************************************************
 * Student Name    : Victor Ageev
 * RMIT Student ID : s3732094
 * COURSE CODE     : CPT220
 *
 * Startup code provided by Paul Miller for use in "Programming in C",
 * study period 4, 2018.
 *****************************************************************************/
#include "main.h"

int main(int argc, char* argv[]) {
        
    struct command commands[NUM_COMMANDS];

    commands_init(commands);

    if(argc > NUMARGS)
    {
        error_print("Error: incorrect number of arguments passed in.\n");
        print_usage();
        return EXIT_FAILURE;
    }
    
    
        
    if (argv[INPUT] == NULL)
    {
        repl(commands,NULL);
    } else {
        repl(commands, argv[INPUT]);
    }

    /* the array of commands that can be used in this program */
        /* initialise the commands */
        /* implement behaviour based on the number of arguments passed in */
        /* if there are invalid arguments, display appropriate
         * error messages and exit */
    return EXIT_SUCCESS;
}

/**
 * common function name used for explaining how to use the program
 **/
void print_usage(void) {
    printf("You should run this program by passing at most 1"
            " argument:\n\n\t./picedit [optional] inputfile\n\n"
            "Where inputfile is an optional original file. If no "
            "input file is provided, picedit will start a new "
            "document.\n");
}
