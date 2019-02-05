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
#include "safemalloc.h"
/**
 * Functions for allocation, manipulation and freeing of the line_list go here
 **/

void line_init(struct line * line) {
    assert(line);
    line->data = NULL;
    line->lineno = 0;
    line->len = 0;
    memset(line,0,sizeof(struct line));
}

void line_list_init(struct line_list * line_list) {

    assert(line_list);
    line_list->head = NULL;
    line_list->num_lines = 0;
    memset(line_list,0,sizeof(struct line_list));

}


BOOLEAN addnode(struct line_list* lines, char currentLine[], struct line * data)
{
    struct line_node * current, *prev;
    struct line_node *new;

    prev = NULL;

    assert(lines);
    assert(data);
    
    data->data = currentLine;

    new = safemalloc(sizeof(struct line_node));

    new->data = data;
    new->data->lineno=lines->num_lines+1;
    new->next = NULL;

    if(lines->head == NULL)
    {
        lines->head = new;
        ++lines->num_lines;
        return TRUE;
    }
    
    current = lines->head;

    while(current != NULL)
    {
        prev=current;
        current=current->next;
    }

    if(!current) {
        prev->next = new;
        new->next = current;
    }

    ++lines->num_lines;
    return TRUE;
}

void list_print(struct line_list* line_list)
{
    struct line_node * current = line_list->head;
    while(current!=NULL)

    {
        struct line_node * next;
        next = current;
        current = current->next;
        normal_print("%li",next->data->lineno);
        normal_print(": ");
        normal_print("%s",next->data->data);
    }
}

void list_free(struct line_list * line_list)
{
    struct line_node * current = line_list->head;
    while(current!=NULL)

    {
        struct line_node * next;
        next = current;
        current = current->next;
        free(next->data);
        free(next);
    }
}
