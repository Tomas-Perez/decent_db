#include <stdlib.h>
#include "list_extras.h"

void destroy_list(list *l, void (*dealloc)(void *)) {
    void *removed;
    while(l->length) {
        remove_last(l, &removed);
        if (dealloc) dealloc(removed);
    }
    free(l);
}