#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "sort_list.h"
#include "../list_extras.h"

int *create_n(int n) {
    int *res = malloc(sizeof(int));
    *res = n;
    return res;
}

void print_numbers(list *l) {
    if (!l->length) {
        printf("Empty list\n");
        return;
    }

    node *curr = l->head;
    while(curr) {
        printf("%d, ", *(int*) curr->data);
        curr = curr->next;
    }
    printf("\n");
}

void test_1() {
    int expected_1[] = {1, 2};
    int expected_2[] = {3, 4};

    list *l = empty();
    add_last(l, create_n(1));
    add_last(l, create_n(2));
    add_last(l, create_n(3));
    add_last(l, create_n(4));
    print_numbers(l);
    list *half;
    split(l, &half);

    assert(length(l) == 2);
    assert(length(half) == 2);

    print_numbers(l);
    print_numbers(half);

    for (int i = 0; i < length(l); i++) {
        assert(expected_1[i] == *(int *) get_element(l, i));
    }
    for (int i = 0; i < length(half); i++) {
        assert(expected_2[i] == *(int *) get_element(half, i));
    }

    printf("Results OK\n");
    destroy_list(l, &free);
    destroy_list(half, &free);
}

void test_2() {
    list *l = empty();
    list *half = NULL;
    print_numbers(l);
    split(l, &half);

    assert(length(l) == 0);
    assert(!half);

    print_numbers(l);

    printf("Results OK\n");
    destroy_list(l, &free);
}

void test_3() {
    int expected_1[] = {1, 2};
    int expected_2[] = {3, 4, 5};

    list *l = empty();
    add_last(l, create_n(1));
    add_last(l, create_n(2));
    add_last(l, create_n(3));
    add_last(l, create_n(4));
    add_last(l, create_n(5));
    print_numbers(l);
    list *half;
    split(l, &half);

    assert(length(l) == 2);
    assert(length(half) == 3);

    print_numbers(l);
    print_numbers(half);

    for (int i = 0; i < length(l); i++) {
        assert(expected_1[i] == *(int *) get_element(l, i));
    }
    for (int i = 0; i < length(half); i++) {
        assert(expected_2[i] == *(int *) get_element(half, i));
    }

    printf("Results OK\n");
    destroy_list(l, &free);
    destroy_list(half, &free);
}

void test_4() {
    int expected_1[] = {1};
    int expected_2[] = {2, 3};
    list *l = empty();
    add_last(l, create_n(1));
    add_last(l, create_n(2));
    add_last(l, create_n(3));
    print_numbers(l);
    list *half;
    split(l, &half);

    assert(length(l) == 1);
    assert(length(half) == 2);

    print_numbers(l);
    print_numbers(half);

    for (int i = 0; i < length(l); i++) {
        assert(expected_1[i] == *(int *) get_element(l, i));
    }
    for (int i = 0; i < length(half); i++) {
        assert(expected_2[i] == *(int *) get_element(half, i));
    }

    printf("Results OK\n");
    destroy_list(l, &free);
    destroy_list(half, &free);
}

int ascending(void *a, void *b) {
    return *(int *) a - *(int *) b;
}

int descending(void *a, void *b) {
    return *(int *) b - *(int *) a;
}

void test_5() {
    int expected[] = {3, 27, 38, 43};

    list *left = empty();
    add_last(left, create_n(27));
    add_last(left, create_n(38));
    list *right = empty();
    add_last(right, create_n(3));
    add_last(right, create_n(43));
    print_numbers(left);
    print_numbers(right);
    merge(left, right, &ascending);
    list *sorted = left;
    print_numbers(sorted);

    assert(length(sorted) == 4);

    for (int i = 0; i < length(sorted); i++) {
        assert(expected[i] == *(int *) get_element(sorted, i));
    }

    printf("Results OK\n");
    destroy_list(sorted, &free);
}

void test_6() {
    int expected[] = {3, 27, 43};

    list *left = empty();
    add_last(left, create_n(27));
    list *right = empty();
    add_last(right, create_n(3));
    add_last(right, create_n(43));
    print_numbers(left);
    print_numbers(right);
    merge(left, right, &ascending);
    list *sorted = left;
    print_numbers(sorted);

    assert(length(sorted) == 3);

    for (int i = 0; i < length(sorted); i++) {
        assert(expected[i] == *(int *) get_element(sorted, i));
    }

    printf("Results OK\n");
    destroy_list(sorted, &free);
}

void test_7() {
    int expected[] = {27, 38, 43};

    list *left = empty();
    add_last(left, create_n(27));
    add_last(left, create_n(38));
    list *right = empty();
    add_last(right, create_n(43));
    print_numbers(left);
    print_numbers(right);
    merge(left, right, &ascending);
    list *sorted = left;
    print_numbers(sorted);

    assert(length(sorted) == 3);

    for (int i = 0; i < length(sorted); i++) {
        assert(expected[i] == *(int *) get_element(sorted, i));
    }

    printf("Results OK\n");
    destroy_list(sorted, &free);
}

void test_8() {
    int expected[] = {3, 27};

    list *left = empty();
    add_last(left, create_n(27));
    list *right = empty();
    add_last(right, create_n(3));
    print_numbers(left);
    print_numbers(right);
    merge(left, right, &ascending);
    list *sorted = left;
    print_numbers(sorted);

    assert(length(sorted) == 2);

    for (int i = 0; i < length(sorted); i++) {
        assert(expected[i] == *(int *) get_element(sorted, i));
    }

    printf("Results OK\n");
    destroy_list(sorted, &free);
}

void test_9() {
    int expected[] = {3, 9};
    list *unsorted = empty();
    add_last(unsorted, create_n(9));
    add_last(unsorted, create_n(3));
    print_numbers(unsorted);
    sort(unsorted, &ascending);
    list *sorted = unsorted;
    print_numbers(sorted);

    assert(length(sorted) == 2);

    for (int i = 0; i < length(sorted); i++) {
        assert(expected[i] == *(int *) get_element(sorted, i));
    }

    printf("Results OK\n");
    destroy_list(sorted, &free);
}

void test_10() {
    int expected[] = {3, 4, 9};
    list *unsorted = empty();
    add_last(unsorted, create_n(9));
    add_last(unsorted, create_n(4));
    add_last(unsorted, create_n(3));
    print_numbers(unsorted);
    sort(unsorted, &ascending);
    list *sorted = unsorted;
    print_numbers(sorted);

    assert(length(sorted) == 3);

    for (int i = 0; i < length(sorted); i++) {
        assert(expected[i] == *(int *) get_element(sorted, i));
    }

    printf("Results OK\n");
    destroy_list(sorted, &free);
}

void test_11() {
    int expected[] = {3, 9, 10, 27, 38, 43, 82};
    list *unsorted = empty();
    add_last(unsorted, create_n(38));
    add_last(unsorted, create_n(27));
    add_last(unsorted, create_n(43));
    add_last(unsorted, create_n(3));
    add_last(unsorted, create_n(9));
    add_last(unsorted, create_n(82));
    add_last(unsorted, create_n(10));
    print_numbers(unsorted);
    sort(unsorted, &ascending);
    list *sorted = unsorted;
    print_numbers(sorted);

    printf("Length: %d\n", length(sorted));
    assert(length(sorted) == 7);

    for (int i = 0; i < length(sorted); i++) {
        assert(expected[i] == *(int *) get_element(sorted, i));
    }

    printf("Results OK\n");

    destroy_list(sorted, &free);
}

void test_12() {
    int expected[] = {82, 43, 38, 27, 10, 9, 3};
    list *unsorted = empty();
    add_last(unsorted, create_n(38));
    add_last(unsorted, create_n(27));
    add_last(unsorted, create_n(43));
    add_last(unsorted, create_n(3));
    add_last(unsorted, create_n(9));
    add_last(unsorted, create_n(82));
    add_last(unsorted, create_n(10));
    print_numbers(unsorted);
    sort(unsorted, &descending);
    list *sorted = unsorted;
    print_numbers(sorted);

    printf("Length: %d\n", length(sorted));
    assert(length(sorted) == 7);

    for (int i = 0; i < length(sorted); i++) {
        assert(expected[i] == *(int *) get_element(sorted, i));
    }

    printf("Results OK\n");

    destroy_list(sorted, &free);
}


void test_13() {
    list *unsorted = empty();
    print_numbers(unsorted);
    sort(unsorted, &descending);
    list *sorted = unsorted;
    print_numbers(sorted);

    printf("Length: %d\n", length(sorted));
    assert(length(sorted) == 0);

    printf("Results OK\n");

    destroy_list(sorted, &free);
}


int main(int argc, char const *argv[])
{
    test_1();
    printf("------------------\n");
    test_2();
    printf("------------------\n");
    test_3();
    printf("------------------\n");
    test_4();
    printf("------------------\n");
    test_5();
    printf("------------------\n");
    test_6();
    printf("------------------\n");
    test_7();
    printf("------------------\n");
    test_8();
    printf("------------------\n");
    test_9();
    printf("------------------\n");
    test_10();
    printf("------------------\n");
    test_11();
    printf("------------------\n");
    test_12();
    printf("------------------\n");
    test_13();

    return 0;
}
