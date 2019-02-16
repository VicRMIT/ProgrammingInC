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
