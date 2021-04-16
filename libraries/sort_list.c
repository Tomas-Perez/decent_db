#include <stdlib.h>
#include <stdio.h>
#include "list.h"

void merge(list *left, list *right, int (*comp)(void *, void*)) {
    node *curr_l = left->head;
    node *curr_r = right->head;
    node *head = NULL;
    if (comp(curr_l->data, curr_r->data) <= 0) {
        head = curr_l;
        curr_l = curr_l->next;
    } else {
        head = curr_r;
        curr_r = curr_r->next;
    }
    node *curr = head;
    while (curr_l && curr_r) {
        if (comp(curr_l->data, curr_r->data) <= 0) {
            curr->next = curr_l;
            curr = curr->next;
            curr_l = curr_l->next;
        } else {
            curr->next = curr_r;
            curr = curr->next;
            curr_r = curr_r->next;
        }
    }
    while (curr_r) {
        curr->next = curr_r;
        curr = curr->next;
        curr_r = curr_r->next;
    }
    while (curr_l) {
        curr->next = curr_l;
        curr = curr->next;
        curr_l = curr_l->next;
    }
    left->head = head;
    left->tail = curr;
    left->length += right->length;
    free(right);
}

int split(list *l, list **half) {
    if (length(l) < 2) return 1;
    node *prev = l->head;
    node *curr = l->head->next;
    node *ahead = l->head->next->next;
    while(ahead && ahead->next) {
        prev = curr;
        curr = curr->next;
        ahead = ahead->next->next;
    }
    prev->next = NULL;
    unsigned int length = l->length;
    l->length = length / 2;
    list *half_res = empty();
    half_res->head = curr;
    half_res->tail = l->tail;
    half_res->length = length % 2 == 0 ? (length / 2) : (length / 2 + 1); 
    l->tail = prev;
    *half = half_res;
    return 0;
}

void sort(list *l, int (*comp)(void *, void*)) {
    list *r;
    if (split(l, &r)) return;
    sort(l, comp);
    sort(r, comp);
    merge(l, r, comp);
}
