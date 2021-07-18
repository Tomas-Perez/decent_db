#include <stdio.h>
#include <string.h>
#include <assert.h>

#include "libraries/malloc_utils.h"
#include "list_extras.h"

#include "save_list.h"

int save_list(const char *filename, size_t elem_size, list *l) {
    FILE *f = fopen(filename, "w");
    if(!f) return 1;
    node *curr = l->head;
    while (curr) {
        size_t elems_written = fwrite(curr->data, elem_size, 1, f);
        if (elems_written != 1) return 1;
        curr = curr->next;
    }
    fclose(f);
    return 0;
}

int load_list(const char *filename, size_t elem_size, list *l) {
    FILE *f = fopen(filename, "r");
    if (!f) return 1;
    char buf[elem_size];
    size_t elems_read = fread(&buf, elem_size, 1, f);
    while (elems_read == 1) { // Bytes written instead of elements written
        void *data = malloc_or_die(elem_size);
        memcpy(data, &buf, elem_size);
        add_last(l, data); // Adding buf directly, without malloc and memcpy.
        elems_read = fread(&buf, elem_size, 1, f);
    }
    fclose(f);
    return 0;
}