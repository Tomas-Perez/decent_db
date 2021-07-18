#ifndef SORT_LIST_H
#define SORT_LIST_H

#include "list.h"

void sort(list *l, int (*comp)(void *, void*));

int split(list *l, list **half);

void merge(list *left, list *right, int (*comp)(void *, void*));

#endif