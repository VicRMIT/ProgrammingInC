/******************************************************************************
 * Student Name    : Victor Ageev
 * RMIT Student ID : S3732094
 * COURSE CODE     : COSC2138
 *
 * Startup code provided by Paul Miller for use in "Programming in C",
 * study period 4, 2018.
 *****************************************************************************/
#include "io.h"
#include "player.h"

#define menuOptionSize 1
#define crossColor 3
#define noughtColor 0
#define resetColor 6
#define breakChar 1
/**
 * The colour codes for printing out coloured output. You just print out the
 * code to change the current colour being printed outThe colour codes for
 * printing out coloured output. You just print out the
 * code to change the current colour being printed out.
 **/
const char* color_strings[NUM_COLORS] = {
    /* red */ "\x1b[31m",    /* green */ "\x1b[32m",
    /* yellow */ "\x1b[33m",
    /* blue */ "\x1b[34m",   /* magenta */ "\x1b[35m",
    /* cyan */ "\x1b[36m",   /* reset */ "\x1b[0m",
};

/**
 * clear the input buffer so we don't skip prompts. Please note that you don't
 * need to call this function unless you have actually detected that too
 * much input has been received. Please note that as this function is declared
 * static, it must be called in this module and not outside of it.
 **/
static void read_rest_of_line(void) {
        int ch;
        while (ch = getc(stdin), ch != '\n' && ch != EOF)
                ;
        clearerr(stdin);
}

/**
 * get symbol passed as an argument and print the appropriate characters
 * to the string.
 **/
void print_symbol(enum cell symbol) {
    switch(symbol) {
        case C_NOUGHT:
            normal_print(" %sO%s |", color_strings[noughtColor], color_strings[resetColor]);
            break;
        case C_CROSS:
            normal_print(" %sX%s |", color_strings[crossColor], color_strings[resetColor]);
            break;
        case C_BLANK:
            normal_print("   |");
            break;
        case C_INVALID:
            normal_print("   |");
            break;
    }
}

/** 
 * prints the name of the current player and the current player's score
 **/
void print_game_status(char s[], int score, enum cell token) { 
    int colorNum;
    if (token==C_CROSS)
        colorNum=crossColor;
    else
        colorNum=noughtColor;
    
    normal_print("It is %s%s%s's turn to make a move, and their score is %d. Please enter "
            "a coordinate to place your piece in comma separated format with the column "
            "first and the row second: ",color_strings[colorNum],s,color_strings[resetColor],score);
} 

/**
 * prints out the current state of the board. Hard coded boundary characters, otherwise
 * reads the symbol at the board location and calls print_symbol.
 **/
void print_board(gameboard board) {
    int i;
    int j;
    normal_print("Current board state\n");
    normal_print("===================\n");
    for (i=-1; i<BOARDHEIGHT; i++) {
        normal_print("|");
        for (j=-1; j<BOARDWIDTH; j++) {
            if (i == -1 && j == -1)   
                normal_print("   |");
            else if (i == -1)
                normal_print(" %d |",j+1);
            else if (j == -1)
                normal_print(" %d |",i+1);
            else {
                print_symbol(board[i][j]);
            }
        }
        normal_print("\n");
        normal_print("-------------------------------------");
        normal_print("\n");
    }
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

enum input_result get_player_turn(char coordString[]) {
        
    char input[SIZECOORDSTRING] = {0};
    while (fgets(input, sizeof(input)+1,stdin) != NULL) {
        if(input[0] == '\n') {
            return IR_RTM; 
        }
        else if(input[sizeof(input)-1] != '\n' && input[sizeof(input)-1] != 0 ) {
            error_print("That entry was too long, please enter "
                    "comma delimited coordinates x,y: ");
            read_rest_of_line();
            return IR_FAILURE;
        }
        else if(isdigit(input[0])==FALSE || isdigit(input[2])==FALSE || input[1]!=',') {
            error_print("That entry is not a coordinate, please enter "
                    "comma delimited coordinates x,y: ");
            return IR_FAILURE;
        } else if (input[0]-'0' < 1 || input[0]-'0' > BOARDHEIGHT  
                || input[2]-'0' < 1 || input[2]-'0' > BOARDWIDTH){
            error_print("That entry is not a valid coordinate, please enter "
                    "comma delimited coordinates x,y: ");
            return IR_FAILURE; 
        } else {
            strcpy(coordString, input);
            return IR_SUCCESS;
        }
    }
    normal_print("\n");
    return IR_RTM;

}

/**
 * fgets conditional that checks for newline or ctrl-d, entries that are too long
 * and a successful entry. Returns the appropriate value.
 **/
enum input_result get_name(char curName[]) {
    char name[NAMELEN+1] = {0};
    if (fgets(name, sizeof(name)+1,stdin) != NULL) {
        if(name[0] == '\n') {
            return IR_RTM; 
        }
        else if(name[sizeof(name)-1] != '\n' && name[sizeof(name)-1] != 0 ) {
            error_print("That name is too long, please enter "
                    "another: ");
            read_rest_of_line();
            return IR_FAILURE;
        }
        else {
            strcpy(curName, name);
            return IR_SUCCESS;
        }
    }
    normal_print("\n");
    return IR_RTM;
}

/**
 * fgets conditional that checks for newline or crl-d, entries that are too long, entries
 * that are out of range, and a successful entry. Returns the appropriate value.
 **/
enum input_result get_win_count(int *winCount) {
    int selection;
    char menuChoice[menuOptionSize + breakChar]; 

    if (fgets(menuChoice, sizeof(menuChoice)+1, stdin) != NULL) {
        if (menuChoice[0] == '\n') {
            return IR_RTM;
        }
        else if (menuChoice[1] != '\n') {
            error_print("That entry is too long, please enter a number between 3 "
                    "and 8: ");
            read_rest_of_line();
            return IR_FAILURE;
        }
        else if (isdigit(menuChoice[0])) {
            selection = menuChoice[0] - '0';
            if (selection > 2 && selection < 9) {
                *winCount = selection;
                return IR_SUCCESS;
            } else {
                error_print("That entry is invalid, please enter a number between 3 "
                        "and 8: ");
                return IR_FAILURE;
            }
        } else {
                error_print("That entry is invalid, please enter a number between 3 "
                        "and 8: ");
                return IR_FAILURE;
        }
    }
    normal_print("\n");
    return IR_RTM;
}

/**
 * fgets conditional loop that checks for newline or crl-d, entries that are too long, entries
 * that are out of range, and a successful entry. Returns the appropriate menu selection.
 **/
int menuSelection(void) {
    int selection;
    char menuChoice[menuOptionSize + breakChar]; 
    normal_print("Welcome to TicTacN\n"); 
    normal_print("------------------\n"); 
    normal_print("1. Play the Game\n"); 
    normal_print("2. Display high scores\n"); 
    normal_print("3. Exit the program \n"); 
    normal_print("Please enter the number of the item you wish to select: "); 

    while (fgets(menuChoice, sizeof(menuChoice)+1, stdin) != NULL) {
        if (menuChoice[0] == '\n') {
            error_print("You did not make a selection, please select [1], [2], or [3]: ");
            selection = INVALID_SELECTION;
        }
        else if (menuChoice[1] != '\n') {
            error_print("Your selection is not valid, please select [1], [2], or [3]: ");
            read_rest_of_line();
            selection = INVALID_SELECTION;
        }
        else if (isdigit(menuChoice[0])) {
            selection = menuChoice[0] - '0';
            if (selection > 0 && selection < 4) {
                switch (selection) {
                    case 1:
                        return PLAY_GAME;
                    case 2:
                        return DISPLAY_SCORE;
                    case 3:
                        return EXIT_PROG;
                }
            } else {
                selection = INVALID_SELECTION;
                error_print("Your selection is not valid, please select [1], [2], or [3]: ");
            }
        } else {
            selection = INVALID_SELECTION;
            error_print("Your selection is not valid, please select [1], [2], or [3]: ");
        }
    }
    return EXIT_PROG;
}
