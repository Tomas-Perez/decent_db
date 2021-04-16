#ifndef SORT_LIST_H
#define SORT_LIST_H

#include "list.h"

// Sorts the given list "l" in-place according to the given "comp" function.
void sort(list *l, int (*comp)(void *, void*));

// Splits the given list "l" in half, the other half of the list is stored in "half"
int split(list *l, list **half);

// Merges two sorted lists "left" and "right" into the "left" list keeping order according to the "comp" function.
// The "right" list is destroyed afterwards. 
void merge(list *left, list *right, int (*comp)(void *, void*));

#endif