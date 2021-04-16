#ifndef MALLOC_UTILS_H
#define MALLOC_UTILS_H

#include <stdlib.h>

// Helper function to handle malloc out of memory errors
void *malloc_or_die(size_t size);

// Helper function to handle calloc out of memory errors
void *calloc_or_die(size_t nmemb, size_t size);

// Helper function to handle realloc out of memory errors
void *realloc_or_die(void *ptr, size_t size);

#endif