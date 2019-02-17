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

struct line_args* line_args(const char args[]) {
    int count;
    struct line_args* activeLines;
    char* tok;
    char temp[INPUTSIZE];
    strcpy(temp, args);
    tok = strtok(temp,"-");
    activeLines = (struct line_args*)malloc(sizeof(struct line_args));
    activeLines->start_line = 0;
    activeLines->finish_line = 0;
    count = 0;
    while(tok) {
        if(count<2) {
            if (count==0)
                activeLines->start_line=strtol(tok,NULL,10);
            else
                activeLines->finish_line=strtol(tok,NULL,10);
        }
        count++;
        tok = strtok(NULL,"-");
    }
    return activeLines;
}

struct line* line_make(const char text[], long lineno) {
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

struct line_node* linenode_make(struct line* theline) {
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

struct line_list* linelist_make(void) {

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


BOOLEAN linelist_insert(struct line_list* thelist,const char text[], long index)
{
    long count;
    struct line_node * curr, *prev=NULL, *newnode;
    struct line* newline;


    if (index > thelist->num_lines + 1 || index <=0) {
        error_print("%ld is outside the list range.\n", index);
        return FALSE;
    }
    
    newline = line_make(text, index);
    if (!newline) {
        return FALSE;
    }

    newnode = linenode_make(newline);
    if (!newnode) {
        line_free(newline);
        return FALSE;
    }

    for (count=1, curr = thelist->head; count<index; ++count) {
        prev = curr;
        curr = curr->next;
    }

    if(!prev) {
        newnode->next = thelist->head;
        thelist->head = newnode;
    } else {
        prev->next=newnode;
        if (index<thelist->num_lines) {
            newnode->next = curr;
        }
    }

    for (; curr; curr=curr->next) {
        ++curr->data->lineno;
    }

    ++thelist->num_lines;
    return TRUE;
}

BOOLEAN linelist_append(struct line_list* theList, const char theLine[]) {
    return linelist_insert(theList, theLine, theList->num_lines+1);
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
            return FALSE;
        }
    }
    return TRUE;
}

void linelist_free(struct line_list * aList)
{
    struct line_node* current, *nextnode;
    current = aList->head;

    while(current) {
        nextnode = current->next;
        linenode_free(current);
        current = nextnode;;
    }
    free(aList->file_name);
    free(aList);
}

void linenode_free(struct line_node* node)
{
    line_free(node->data);
    free(node);
}

void line_free(struct line* aLine) {
    free(aLine->data);
    free(aLine);
}
