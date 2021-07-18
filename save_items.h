#ifndef SAVE_ITEMS_H
#define SAVE_ITEMS_H

#include <stdio.h>

#include "libraries/items.h"

int fwrite_item(item *i, FILE *file);
int fread_item(item **i, FILE *file);

#endif