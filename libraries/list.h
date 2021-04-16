#ifndef LIST_H
#define LIST_H

typedef struct node {
    void *data;
    struct node *next;
} node;

typedef struct list {
    node *head;
    node *tail;
    unsigned int length;
} list;

// Create empty list
list *empty();

// Add an element to the end of the list.
void add_last(list *l, void *data);

// Add an element to the start of the list.
void add_first(list *l, void *data);

// Add an element to the list at the given position.
// If the position is larger than the length of the list, the element is added at the end of the list.
void add_element(list *l, unsigned int pos, void *data);

// Remove the first element of the list.
// The address pointed to by data will be filled with the contents of the removed node.
void remove_first(list *l, void **data);

// Remove the last element of the list.
// The address pointed to by data will be filled with the contents of the removed node.
void remove_last(list *l, void **data);

// Remove an element at the given position in the list.
// The address pointed to by data will be filled with the contents of the removed node.
// If the position is larger than the length of the list, the last element is removed.
// If no element could be removed, data is set to NULL.
void remove_element(list *l, unsigned int pos, void **data);

// Get the data element at the given position of the list.
void *get_element(list *l, unsigned int pos);

// Get the length of the list.
unsigned int length(list *l);

#endif