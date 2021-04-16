#include <stddef.h>
#include <stdlib.h>

#include "list.h"
#include "malloc_utils.h"

list *empty() {
    list *result = (list *) malloc_or_die(sizeof(list));
    result->head = NULL;
    result->tail = NULL;
    result->length = 0;
    return result;
}

// Create list node
static node *create_node(void *data) {
    node *result = (node *) malloc_or_die(sizeof(node));

    result->data = data;
    result->next = NULL;
	
	return result;
}

static void add_to_empty_list(list *l, void *data) {
    node *new_node = create_node(data);
    l->head = new_node;
    l->tail = new_node;
    l->length++;
}

void add_last(list *l, void *data) {
    if (!l->length) 
        return add_to_empty_list(l, data);

    node *new_node = create_node(data);
    l->tail->next = new_node;
    l->tail = new_node;
    l->length++;
}

void add_first(list *l, void *data) {
    if (!l->length) 
        return add_to_empty_list(l, data);

    node *new_node = create_node(data);
    new_node->next = l->head;
    l->head = new_node;
    l->length++;
}

void add_element(list *l, unsigned int pos, void *data) { 
    // Empty list
    if (!l->length) 
        return add_to_empty_list(l, data);

    // Add element at the start.
    if (pos == 0)
        return add_first(l, data);

    // Add element at the end.
    if (pos >= l->length)
        return add_last(l, data);

    // Position in the middle of the list. Traverse the list to find where to store the node.
    node *prev = l->head;
    for (int i = 0; i < pos-1; i++)
        prev = prev->next;

    node *next = prev->next;
    node *new_node = create_node(data);
    new_node->next = next;
    prev->next = new_node;

    l->length++;
}

void remove_first(list *l, void **data) {
    if (!l->length) {
        *data = NULL;
        return;
    }

    node *to_remove = l->head;
    *data = to_remove->data;
    l->head = to_remove->next;
    l->length--;
    free(to_remove);
}

void remove_last(list *l, void **data) {
    if (!l->length) {
        *data = NULL;
        return;
    }

    if (l->length == 1) {
        *data = l->head->data;
        free(l->head);
        l->head = NULL;
        l->tail = NULL;
        l->length = 0;
        return;
    }

    node *prev = l->head;
    node *curr = l->head->next;
    while (curr->next) {
        prev = curr;
        curr = curr->next;
    }

    prev->next = NULL;
    l->tail = prev;
    l->length--;
    *data = curr->data;
    free(curr);
}

void remove_element(list *l, unsigned int pos, void **data) {
    if (!l->length) {
        *data = NULL;
        return;
    }

    if (pos == 0)
        return remove_first(l, data);

    if (pos >= l->length - 1)
        return remove_last(l, data);

    node *prev = l->head;
    for (int i = 0; i < pos-1; i++)
        prev = prev->next;

    node *to_remove = prev->next;
    node *next = to_remove->next;

    prev->next = next;
    *data = to_remove->data;
    free(to_remove);
    l->length--;
}

void *get_element(list *l, unsigned int pos) {
    node *curr_node = l->head;
    int curr_pos = 0;
    while (curr_node && curr_pos < pos) {
        curr_node = curr_node->next;
        curr_pos++;
    }
    if (curr_pos == pos) return curr_node->data;
    else return NULL;
}

unsigned int length(list *l) {
    return l->length;
}

