#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <fcntl.h>
#include <unistd.h>

#include "libraries/malloc_utils.h"
#include "list_extras.h"

#include "save_list.h"

int save_list(const char *filename, size_t elem_size, list *l) {
    int fd = open(filename, O_RDONLY);
    node *curr = l->head;
    while (curr) {
        ssize_t bytes_written = write(fd, curr->data, elem_size);
        if (bytes_written != 1) return 1;
        curr = curr->next;
    }
    return 0;
}

int load_list(const char *filename, size_t elem_size, list *l) {
    int fd = open(filename, O_RDONLY);
    char buf[elem_size];
    ssize_t bytes_read = read(fd, &buf, elem_size);
    while (bytes_read == elem_size) {
        add_last(l, buf); 
        bytes_read = read(fd, &buf, elem_size);
    }
    return 0;
}