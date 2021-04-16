#include <stdio.h>
#include <stdlib.h>
#include "malloc_utils.h"

void *malloc_or_die(size_t size) {
    void *ptr = malloc(size);
    if (!ptr) {
        fprintf(stderr, "Ran out of memory!\n");
        abort();
    }
    return ptr;
}

void *calloc_or_die(size_t nmemb, size_t size) {
    void *ptr = calloc(nmemb, size);
    if (!ptr) {
        fprintf(stderr, "Ran out of memory!\n");
        abort();
    }
    return ptr;
}

void *realloc_or_die(void *ptr, size_t size) {
    void *new_ptr = realloc(ptr, size);
    if (!new_ptr) {
        fprintf(stderr, "Ran out of memory!\n");
        abort();
    }
    return new_ptr;
}