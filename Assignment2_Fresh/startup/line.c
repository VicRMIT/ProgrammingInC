/******************************************************************************
 * Student Name    :
 * RMIT Student ID :
 * COURSE CODE     :
 *
 * Startup code provided by Paul Miller for use in "Programming in C",
 * study period 4, 2018.
 *****************************************************************************/

#include "line.h"
#include "helpers.h"
#include "repl.h"

/**
 * allocates memory for a line and copies the text into that line
 **/
struct line* line_make(const char text[], long lineno) {
        struct line* theline;
        /* allocate space for the line struct */
        theline = (struct line*)malloc(sizeof(struct line));
        if (!theline) {
                perror("malloc failed");
                return NULL;
        }
        /* copy the text */
        theline->data = strdup(text);
        if (!theline->data) {
                line_free(theline);
                return NULL;
        }
        /* set the length of the line */
        theline->len = strlen(theline->data);
        theline->lineno = lineno;
        return theline;
}

/**
 * creates a new line node with the struct line provided to the data element
 * of the new node.
 **/
struct line_node* linenode_make(struct line* aline) {
        /* allocate space for the line node */
        struct line_node* new =
            (struct line_node*)malloc(sizeof(struct line_node));
        if (!new) {
                perror("malloc failed");
                return NULL;
        }
        /* duplicate the line passed in */
        new->data = aline;
        if (!new->data) {
                return NULL;
        }
        new->next = NULL;
        return new;
}

/**
 * create a new empty line list
 **/
struct line_list* linelist_make(void) {
        /* allocate space for the list structure */
        struct line_list* alist =
            (struct line_list*)malloc(sizeof(struct line_list));
        if (!alist) {
                perror("malloc failed");
                return NULL;
        }
        /* set all elements to sensible default values (usually some kind of 0 )
         */
        alist->head = NULL;
        alist->file_name = NULL;
        alist->num_lines = 0;
        return alist;
}

/**
 * frees the line struct and the text it contains. If you want the text in
 * the line to survive the free, duplicate the text to some other memory
 * first.
 **/
void line_free(struct line* theline) {
        free(theline->data);
        free(theline);
}

/**
 * free linenode's memory including containing structs
 **/
void linenode_free(struct line_node* node) {
        line_free(node->data);
        free(node);
}

/**
 * frees the line list and all lines in it
 **/
void linelist_free(struct line_list* thelist) {
        struct line_node* curnode, *nextnode;
        /* grab the head of the list */
        curnode = thelist->head;
        while (curnode) {
                /* grab the next node as any reference to freed data is illegal
                 */
                nextnode = curnode->next;
                /* free the data and then the node */
                linenode_free(curnode);
                curnode = nextnode;
        }
        free(thelist->file_name);
        free(thelist);
}

/**
 * adds a line to the end of the line list
 **/
BOOLEAN linelist_append(struct line_list* thelist, const char text[]) {
        /* just insert at the end of the list */
        return linelist_insert(thelist, text, thelist->num_lines + 1);
}

/**
 * searches for the insertion point and inserts the a new line with the
 * text specified.
 **/
BOOLEAN linelist_insert(struct line_list* thelist, const char text[],
                        long index) {
        long count;
        struct line_node* curr, *prev = NULL, *newnode;
        struct line* newline;
        /* test that the line is within the range of this list */
        if (index > thelist->num_lines + 1 || index <= 0) {
                error_print("%ld is outside the range of the line list.\n",
                            index);
                return FALSE;
        }
        /* allocate the new line */
        newline = line_make(text, index);
        if (!newline) {
                return FALSE;
        }
        /* allocate the new line node */
        newnode = linenode_make(newline);
        if (!newnode) {
                line_free(newline);
                return FALSE;
        }
        /* find the insertion point*/
        for (count = 1, curr = thelist->head; count < index; ++count) {
                prev = curr;
                curr = curr->next;
        }
        /* insert into the list */
        /* insert at the start of the list */
        if (!prev) {
                newnode->next = thelist->head;
                thelist->head = newnode;
        } else {
                /* insert elsewhere in the list */
                prev->next = newnode;
                /* if we are not at the end of the list, append the rest of
                 * the list
                 */
                if (index < thelist->num_lines) {
                        newnode->next = curr;
                }
        }
        /* update the line number for all lines after this one */
        for (; curr; curr = curr->next) {
                ++curr->data->lineno;
        }
        ++thelist->num_lines;
        return TRUE;
}

/**
 * prints out a single line to the file specified
 **/
BOOLEAN line_print(const struct line* aline, FILE* out) {
        if (out == stdout || out == stderr) {
                if (fprintf(out, "%ld: %s\n", aline->lineno, aline->data) < 0) {
                        error_print("%s\n", strerror(ferror(out)));
                        return FALSE;
                }
        } else {
                if (fprintf(out, "%s\n", aline->data) < 0) {
                        error_print("%s\n", strerror(ferror(out)));
                        return FALSE;
                }
        }
        return TRUE;
}

/**
 * iterates over each line in the line list and prints out each line to
 *the
 * file specified
 **/
BOOLEAN linelist_print(const struct line_list* thelist, FILE* out) {
        struct line_node* current;
        for (current = thelist->head; current; current = current->next) {
                if (!line_print(current->data, out)) {
                        return FALSE;
                }
        }
        return TRUE;
}
