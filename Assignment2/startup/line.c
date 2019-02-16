/******************************************************************************
 * Student Name    : Victor Ageev
 * RMIT Student ID : s3732094
 * COURSE CODE     : CPT220
 *
 * Startup code provided by Paul Miller for use in "Programming in C",
 * study period 4, 2018.
 *****************************************************************************/
#include "repl.h"
#include "line.h"
#include "helpers.h"
/**
 * Functions for allocation, manipulation and freeing of the line_list go here
 **/

struct line* line_init(const char text[], long lineno) {
    struct line* theline;
    theline = (struct line*)malloc(sizeof(struct line));
    if(!theline){
        perror("malloc failed");
        return NULL;
    }
    theline->data = strdup(text);
    if(!theline->data) {
        line_free(theline);
        return NULL;
    }

    theline->len = strlen(theline->data);
    theline->lineno = lineno;
    return theline;
}

struct line_node* line_node_init(struct line* theline) {
    struct line_node* newNode;
    newNode = (struct line_node*)malloc(sizeof(struct line_node));
    if(!newNode) {
        perror("malloc failed");
        return NULL;
    }
    newNode->data=theline;
    if(!newNode->data) {
        return NULL;
    }
    newNode->next = NULL;
    return newNode;
}

struct line_list* line_list_init(void) {

    struct line_list* newList;
    newList= (struct line_list*)malloc(sizeof(struct line_list));
    if(!newList) {
        perror("malloc failed");
        return NULL;
    }
    newList->head = NULL;
    newList->file_name = NULL;
    newList->num_lines = 0;
    return newList;
}


BOOLEAN list_insert(struct line_list* lines,const char currentLine[], long index)
{
    long count;
    struct line_node * current, *prev, *new;
    struct line* newLine;

    prev = NULL;

    if (index > lines->num_lines + 1 || index <=0) {
        error_print("%ld is outside the list range.\n", index);
        return FALSE;
    }
    
    newLine = line_init(currentLine, index);
    if (!newLine) {
        return FALSE;
    }

    new = line_node_init(newLine);
    if (!new) {
        line_free(newLine);
        return FALSE;
    }

    for (count=1, current = lines->head; count<index; ++count) {
        prev = current;
        current = current->next;
    }

    if(!prev) {
        new->next = lines->head;
        lines->head = new->next;
    } else {
        prev->next=new;
        if (index<lines->num_lines) {
            new->next = current;
        }
    }

    for (; current; current=current->next) {
        ++current->data->lineno;
    }

    ++lines->num_lines;
    return TRUE;
}

BOOLEAN list_append(struct line_list* theList, const char theLine[]) {
    return list_insert(theList, theLine, theList->num_lines+1);
}

BOOLEAN linelist_print(const struct line_list* theList, FILE* out)
{
    struct line_node * current = theList->head;
    while(current!=NULL)
    {   
        if (!line_print(current->data, out)) {
            return FALSE;
        }
        current = current->next;
    }
    return TRUE;
}

BOOLEAN line_print(const struct line* theLine, FILE* out) {
    if (out ==stdout || out ==stderr) {
        if (fprintf(out, "%ld: %s\n", theLine->lineno, theLine->data) < 0) {
            error_print("%s\n", strerror(ferror(out)));
            return FALSE;
        }
    } else {
        if (fprintf(out, "%s\n", theLine->data) < 0) {
            error_print("%s\n", strerror(ferror(out)));
        }
    }
    return TRUE;
}

void list_free(struct line_list * aList)
{
    struct line_node* current, *nextnode;
    current = aList->head;

    while(current) {
        nextnode = current->next;
        node_free(current);
        current = nextnode;;
    }
    free(aList->file_name);
    free(aList);
}

void node_free(struct line_node* node)
{
    line_free(node->data);
    free(node);
}

void line_free(struct line* aLine) {
    free(aLine->data);
    free(aLine);
}
