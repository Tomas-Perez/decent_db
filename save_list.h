#ifndef SAVE_LIST_H
#define SAVE_LIST_H

#include <stdlib.h>

#include "libraries/list.h"

int save_list(const char *filename, size_t elem_size, list *l);
int load_list(const char *filename, size_t elem_size, list *l);

#endif