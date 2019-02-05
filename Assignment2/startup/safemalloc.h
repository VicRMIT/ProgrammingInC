/******************************************************************************
 * Student Name    : Victor Ageev
 * RMIT Student ID : s3732094
 * COURSE CODE     : CPT220
 *
 * Startup code provided by Paul Miller for use in "Programming in C",
 * study period 4, 2018. Lecture examples.
 *****************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

void * safe_malloc(size_t, unsigned long );
void * safe_calloc(size_t, size_t, unsigned long);
void safe_ptr_malloc(void**, size_t, unsigned long);
void * safe_realloc(void*, size_t, unsigned long);

#define safemalloc(size) safe_malloc(size, __LINE__)
#define safecalloc(nmem, size) safe_calloc(nmem, size, __LINE__)
#define safeptrmalloc(memory, size) safe_ptr_malloca(memory,size, __LINE__)
#define saferalloc(memory, size) safe_realloc(memory,size,__LINE__)
