/******************************************************************************
 * Student Name    : Victor Ageev
 * RMIT Student ID : s3732094
 * COURSE CODE     : CPT220
 *
 * Startup code provided by Paul Miller for use in "Programming in C",
 * study period 4, 2018.
 *****************************************************************************/

#include "line.h"
#include "helpers.h"
#include "safemalloc.h"
/**
 * Functions for allocation, manipulation and freeing of the line_list go here
 **/

void line_list_init(struct line_list * line_list) {

    assert(line_list);
    line_list->head = NULL;
    line_list->num_lines = 0;
    memset(line_list,0,sizeof(struct line_list));

}


BOOLEAN addNode(struct line_list* lines, char currentLine[], struct line * data)
{
    struct line_node * current, *prev;
    struct line_node *new;

    prev = NULL;

    assert(lines);
    assert(data);

    new = safemalloc(sizeof(struct line_node));

    new->data = data;
    new->data->lineno=lines->num_lines;
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

void list_print(struct line_list* lines)
{

}
