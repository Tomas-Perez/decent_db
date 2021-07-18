#ifndef LIST_EXTRAS_H
#define LIST_EXTRAS_H

#include "libraries/list.h"

void destroy_list(list *l, void (*dealloc)(void *));

#endif