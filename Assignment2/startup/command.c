/******************************************************************************
 * Student Name    : Victor Ageev
 * RMIT Student ID : s3732094
 * COURSE CODE     : CPT220
 *
 * Startup code provided by Paul Miller for use in "Programming in C",
 * study period 4, 2018.
 *****************************************************************************/

#include "command.h"
#include "helpers.h"
#include "repl.h"
#include <math.h>
/**
 * copy into the commands array the structures to represeent each function to be
 * called by the system. The command_index enum defines the order of the command
 * structures in this array. Please note that your solution is meant to scale
 * and make it easy to update and maintain. An approach of a simple hardcoding
 * of the elements will get 0 marks. eg: you should use a loop or a mem*
 * function to do this initialisation.
 **/
void commands_init(struct command commands[])
{
    BOOLEAN (*func[NUM_COMMANDS])(const char[], struct line_list*) = {
        command_new, command_read, command_write, command_print, command_insert,
        command_delete, command_search, command_replace, command_help,
        command_quit
    };

    const enum command_type types[] = {CT_NEW, CT_READ, CT_WRITE, CT_PRINT,
       CT_INSERT, CT_DELETE, CT_SEARCH, CT_REPLACE, CT_HELP, CT_QUIT}; 
    
    int iter;
    for(iter=0; iter<NUM_COMMANDS;iter++) {
        commands[iter].type = types[iter];
        commands[iter].func = func[iter];
    }
}

static void remove_newlines(char input[]) {
   input[strcspn(input,"\n")] = 0; 
}
/**
 * implements the "new file" command. You should just set the line list to be
 * an empty list
 **/
BOOLEAN command_new(const char remainder[], struct line_list* thelist)
{
    if (thelist) {
        linelist_free(thelist);
    }
    thelist = linelist_make();
    if(thelist) {
        normal_print("New document started.");
        return TRUE;
    }
    normal_print("Could not create new doc.");
    return FALSE;
}
/**
 * handles a request to load a file into the linked list. The actual work of
 * loading the file should be done in fileio module.
 **/
BOOLEAN command_read(const char remainder[], struct line_list* thelist)
{   
    while (isspace(*remainder))
    {
        ++remainder;
    }
    if(load_file(remainder, thelist)) {
        normal_print("File loaded.");
        return TRUE;
    } else {
        error_print("Failed to load file");
        return FALSE;
    }
}

/**
 * handles the saving of a file to disk. If no file is specified, the filename
 * that the file was specified under when loaded (if any) will be used.
 **/
BOOLEAN command_write(const char remainder[], struct line_list* thelist)
{
    while (isspace(*remainder))
    {
        ++remainder;
    }
    if(save_file(remainder, thelist)) {
        return TRUE;
    }
    return FALSE;
}

/**
 * handles the printing of lines from the "file" loaded into memory. We need to
 * handle 3 cases: when no range of lines is asked for, print out the whole
 * file. When a single number is provided after the 'p', print just the line
 * requested. When a range is requested, eg: p3-7 print out those lines. In all
 * cases, each line must be printed out as linenumber: text, eg:
 *
 * 3: this is the third line of the file
 *
 **/
BOOLEAN command_print(const char remainder[], struct line_list* thelist)
{
    struct line_node *current = thelist->head;
    struct line_args* lines;
    while (isspace(*remainder))
    {
        ++remainder;
    }
    lines = line_args(remainder);
    while(current!=NULL)
    {
        if((current->data->lineno >= lines->start_line) && 
                (current->data->lineno <= lines->finish_line)) {
            if (!line_print(current->data, stdout)) {
                free(lines);
                return FALSE;
            }
        } else if (current->data->lineno == lines->start_line) {
            if (!line_print(current->data, stdout)) {
                free(lines);
                return FALSE;
            }
        } else if ((lines->start_line==0) && (lines->finish_line==0)) {
            if (!line_print(current->data, stdout)) {
                free(lines);
                return FALSE;
            }
        }
        current=current->next;
    }
    free(lines);
    return TRUE;
}

/**
 * inserts one or more lines into linked list, starting at the new line number
 * specified by the user. The new line number specified by the user must be
 * greater than or equal to 1 (the first line) and less than or equal to the
 * count of lines in the file plus one (when the user chooses to append to the
 * end of the file).
 **/
BOOLEAN command_insert(const char remainder[], struct line_list* thelist)
{
    char input[INPUTSIZE];
    int rangeLength;
    int initialInsert;
    struct line_args* lines;
    int iter = 0;
    while (isspace(*remainder))
    {
        ++remainder;
    }
    lines = line_args(remainder);
    rangeLength = floor(log10(abs(lines->start_line)))+1;
    for(; iter<rangeLength;iter++) {
        ++remainder;
    }    
   
    initialInsert = lines->start_line;
    normal_print("%d: ", initialInsert);
    while(fgets(input,sizeof(lines)+1,stdin) != NULL) {
        if(input[0]=='\n') {
            /*if (initialInsert!=0) {
               if(!linelist_insert(thelist, input, initialInsert))
                  return FALSE;
            }*/
            return TRUE;
        } else {
            remove_newlines(input);
            if (initialInsert!=0) {
               if(!linelist_insert(thelist, input, initialInsert))
                  return FALSE;
            }
            normal_print("%d: ", ++initialInsert);
        }
    }
    normal_print("\n");
    return FALSE;
}

/**
 * delete the lines at the line numbers specified in the remainder string.
 **/
BOOLEAN command_delete(const char remainder[], struct line_list* thelist)
{
    long removed_items;
    struct line_node *current = thelist->head;
    struct line_node *pre_delete = NULL, *next, *delete;
    struct line_args* lines;
    while (isspace(*remainder))
    {
        ++remainder;
    }
    lines = line_args(remainder);
    
    removed_items = lines->finish_line - lines->start_line;
    if(removed_items < 0)
        if (lines->finish_line != 0)
            return FALSE;
        else
            removed_items = 1;
    else if ((removed_items == 0) && lines->start_line!=0)
        removed_items = 1;
    else if (removed_items>0)
        removed_items++;
    
    while(current!=NULL)
    {  
        next = current->next; 
        if(current->data->lineno == lines->start_line-1){
            pre_delete=current;
        }
        else if(((current->data->lineno >= lines->start_line) && 
                    (lines->start_line != 0) &&
                (current->data->lineno <= lines->finish_line)) ||
                ((current->data->lineno == lines->start_line) && 
                (lines->finish_line == 0))) {
            delete = current;
            linenode_free(delete);
        }
        else {
            if(((current->data->lineno == lines->finish_line+1) &&
                   (lines->finish_line != 0)) ||
                   ((current->data->lineno == lines->start_line+1) &&
                   (lines->finish_line == 0))) {
                pre_delete->next = current;
                if (lines->start_line == 1) 
                    thelist->head = current;
            }
            if((current->data->lineno>lines->start_line) &&
                    (current->data->lineno>lines->finish_line)) {
                current->data->lineno = current->data->lineno - removed_items;
            }
        }
        current = next;
    }
    free(lines);
    thelist->num_lines = thelist->num_lines - removed_items;
    return TRUE;
}

/**
 * handles a request for a search across the list for a string specified. The
 * output here should be as spcified in the assignment specification and help
 * documentation provided in the sample executable.
 **/
BOOLEAN command_search(const char remainder[], struct line_list* thelist)
{
    struct line_node *current = thelist->head;
    while (isspace(*remainder))
    {
        ++remainder;
    }
    while(current!=NULL)
    {
        if(strstr(current->data->data,remainder)!=NULL) {
            if (!line_print(current->data, stdout)) {
                return FALSE;
            }
        }
        current=current->next;
    }
    return TRUE;
}

/**
 * performs the find and replace algorithm, including the processing of
 * user input from the repl. Check that there are two '/' characters in the
 * string separated by other chars. Duplicate the string to perform tokenization
 * on it. Iterate over the list replacing each instance of the search string
 * with the replacement. Print out each replacement made. Please note that
 * you should do much / most of this work in functions you create yourself.
 **/
BOOLEAN command_replace(const char remainder[], struct line_list* thelist)
{
        return FALSE;
}

/**
 * handles the quitting of the program and freeing any allocated memory
 **/
BOOLEAN command_quit(const char remainder[], struct line_list* thelist)
{
    linelist_free(thelist);
    return TRUE;
}

/**
 * handles providing help to the user. I've provided the sourcecode for this
 * function as I don't want you to be spending time copying and pasting text as
 * there's little learning involved.
 **/
BOOLEAN command_help(const char remainder[], struct line_list* thelist)
{
        (void)thelist;
        if (empty_string(remainder))
        {
                char help_string[] =
                    "You have the following options: \n\n"
                    "n - make a new file, discarding any currently loaded "
                    "text.\n"
                    "r - read a file into memory.\n"
                    "w - write a file out to disk.\n"
                    "p - print out lines from the file loaded into memory.\n"
                    "i - insert lines into the file loaded into memory.\n"
                    "d - delete lines from the file loaded into memory.\n"
                    "s - search the file loaded into memory.\n"
                    "h - display this help information.\n"
                    "q - quit the program.\n\n"
                    "If you want more information on one of these options, "
                    "simply enter 'h' followed by the option.\n";
                fold(help_string, LINELEN);
                normal_print("%s\n", help_string);
        }
        else
        {
                char* output = NULL;
                while (isspace(*remainder))
                {
                        ++remainder;
                }
                /* if the remainder at this point is more than one char (a
                 * command, then it's an invalid help request */
                if (strlen(remainder) > 2)
                {
                        error_print(
                            "trailing invalid chars in request for help.\n");
                        return FALSE;
                }
                /* handle each kind of possible help request */
                switch (tolower(*remainder))
                {
                        /* create a new file in memory */
                        case CT_NEW:
                        {
                                output = strdup(
                                    "n - no trailing argument. Creates a new "
                                    "empty file in memory. After doing this "
                                    "you can insert text on the first line. "
                                    "\n\n");
                        }
                        break;
                        /* read a file in from disk */
                        case CT_READ:
                        {
                                output = strdup(
                                    "r <path>, where path is the path to the "
                                    "file. Please note that no assumption is "
                                    "made about the path or the filename or "
                                    "file extension. Reads the file specified "
                                    "into memory and folds the file so that "
                                    "the maximul line length is 80 "
                                    "characters.");
                        }
                        break;
                        /* save the data in memory to a file on disk where the
                         * filename may be specified, if it is specified or
                         * should be taken from the file name that either it was
                         * loaded from or previously saved to */
                        case CT_WRITE:
                        {
                                output = strdup(
                                    "w <path> where path is the path to the "
                                    "file. Please note that no assumption is "
                                    "made about the path or the filename or "
                                    "file extension. Writes the file in memory "
                                    "to disk. If the lines in memory represent "
                                    "a file previously loaded into memory then "
                                    "the file name does not need to be "
                                    "provided.");
                        }
                        break;
                        /* print out a range of lines or the whole file if it is
                         * not specified */
                        case CT_PRINT:
                        {
                                output = strdup(
                                    "Prints out 1 or more lines of text. "
                                    "Can be invoked as: p on its own which "
                                    "will print out the whole file. "
                                    "Alternatively you can invoke this as pNUM "
                                    "where NUM is a valid line number and when "
                                    "invoked in this way, that line will be "
                                    "printed as NUM: text. For example: \n\n"
                                    "3: this is the text from line 3\n\n"
                                    "This can also be invoked as PNUM-NUM "
                                    "where NUM in both cases is a valid line "
                                    "number in the text file. Each line will "
                                    "be printed out in the same format as "
                                    "specified for printing out a single "
                                    "line.\n\n");
                        }
                        break;
                        case CT_INSERT:
                        {
                                output = strdup(
                                    "Inserts one or more lines into the file. "
                                    "You specify the line where you want the "
                                    "insert to start. For example: \n\n"
                                    "i3\n"
                                    "inserting at line 3: \n"
                                    "3: new text for line 3.\n"
                                    "4: new text for line 4.\n\n"
                                    "You can terminate the insertion of lines "
                                    "by pressing ctrl-d or [enter] on a new "
                                    "line. Please note that all new lines "
                                    "inserted will be folded at the 80 "
                                    "character mark, so if the line you enter "
                                    "is longer than 80 characters, it will "
                                    "become multiple lines in the list.\n\n");
                        }
                        break;
                        case CT_DELETE:
                        {
                                output = strdup(
                                    "Deletes one or more lines from the file "
                                    "loaded into memory. Obviously if there "
                                    "are no lines currently in the line list, "
                                    "nothing can be deleted.\n\n"
                                    "You enter d followed by either a single "
                                    "number such as 5 or a range of numbers "
                                    "such as 3-5. Please note that the numbers "
                                    "entered must be within the range of the "
                                    "list and the first number in the range "
                                    "must lower than or equal to the second "
                                    "number.\n\n");
                        }
                        break;
                        case CT_SEARCH:
                        {
                                output = strdup(
                                    "searches for the text search in each line "
                                    "of the file. Any leading spaces before the"
                                    " first non-space character are ignored "
                                    "however any paces after the beginning of "
                                    "the first word are considered part of the "
                                    "search because your search word might be "
                                    "multiword.\n\n");
                        }
                        break;
                        case CT_HELP:
                        {
                                output = strdup(
                                    "displays help for each option that can be "
                                    "invoked. Type h followed by the letter "
                                    "for the option you want to get help on. "
                                    "Eg: hp would give you help on the print "
                                    "command.\n\n");
                        }
                        break;
                        case CT_QUIT:
                        {
                                output = strdup(
                                    "Quits the program. Simply type the q "
                                    "character or press [enter] or ctrl-d at "
                                    "the prompt");
                        }
                        break;
                }
                if (output)
                {
                        fold(output, LINELEN);
                        normal_print(output);
                        free(output);
                }
        }
        return TRUE;
}
