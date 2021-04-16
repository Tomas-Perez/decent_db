#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>

#include "libraries/list.h"
#include "libraries/items.h"
#include "libraries/program_state.h"

#include "list_extras.h"
#include "credentials.h"
#include "save_list.h"
#include "save_items.h"
#include "menu.h"

char *credentials_filename = "data/credentials.bin";
char *state_filename = "data/state.bin";
char *items_filename = "data/items.bin";

int load_items(const char *filename, list *items) {
    FILE *f = fopen(filename, "w+");
    unsigned int amt_items;
    fread(&amt_items, sizeof(amt_items), 1, f);
    for (int i = 0; i < amt_items; i++) {
        item *i;
        size_t elem_read = fread_item(&i, f);
        if (!elem_read) return 1;
        add_last(items, i);
    }
    return 0;
}

int save_items(const char *filename, list *items) {
    FILE *f = fopen(filename, "w");
    unsigned int amt_items = length(items);
    fwrite(&amt_items, sizeof(amt_items), 1, f);
    node *curr = items->head;
    size_t elems_written;
    while (!curr) {
        int elem_written = fwrite_item((item *) curr->data, f);
        if (!elem_written) return 1;
        elems_written += elem_written;
        curr = curr->next;
    }
    return 0;
}

void init_user_state(user_state *u_state) {
    u_state->user_id_gen = 0;
    u_state->current_user_id = -1;
}

credentials *find_by_id(int id, list *creds) {
    node *curr = creds->head;
    while(curr) {
        credentials *cred = curr->data;
        if (id == cred->user_id) {
            return cred;
        }
        curr = curr->next;
    }
    return NULL;
}

int load_user_state(const char *filename, program_state *state) {
    int fd = open(filename, O_WRONLY);
    user_state buf;
    ssize_t bytes_read = read(fd, &buf, sizeof(state->u_state));
    if (bytes_read != sizeof(state->u_state)) return 1;
    state->u_state = buf;
    credentials *user = find_by_id(state->u_state.current_user_id, state->saved_credentials); 
    if (!user) {
        state->u_state.current_user_id = -1;
    } else {
        state->current_user = user;
    }
    return 0;
}

int save_user_state(const char *filename, program_state *state) {
    int fd = open(filename, O_WRONLY);
    ssize_t bytes_written = write(fd, &state->u_state, sizeof(state->u_state));
    if (bytes_written != 1) return 1;
    return 0;
}

int main(int argc, char const *argv[])
{
    program_state state;
    state.current_user = NULL;
    state.items = empty();
    state.saved_credentials = empty();

    if (load_items(items_filename, state.items)) {
        printf("No items saved, initializing...\n");
        add_last(state.items, create_food("Chicken breast", 4, 165, 31, 0, 3.6));
        add_last(state.items, create_food("Strawberries", 2, 32, 0.7, 7.7, 0.3));
        add_last(state.items, create_appliance("Fridge", 4000, 900));
        add_last(state.items, create_appliance("Washing machine", 2500, 600));
        add_last(state.items, create_electronic_device("iPhone X", 1200));
        add_last(state.items, create_electronic_device("iPhone XR", 1500));
        add_last(state.items, create_kitchen_equipment("Chef's knife", 90, METAL));
        add_last(state.items, create_kitchen_equipment("Cutting board", 30, WOOD));
        add_last(state.items, create_kitchen_equipment("Spatula", 10, PLASTIC));
    }

    if(load_list(credentials_filename, sizeof(credentials), state.saved_credentials)) {
        printf("No credentials saved, initializing...\n");
        credentials *user_1 = create_credentials(state.u_state.user_id_gen++, "username", "password");
        credentials *user_2 = create_credentials(state.u_state.user_id_gen++, "johnny", "wasn't there");
        add_last(state.saved_credentials, user_1);
        add_last(state.saved_credentials, user_2);
    }

    if (load_user_state(state_filename, &state)) {
        printf("No state saved, initializing...\n");
        init_user_state(&state.u_state);
    }

    start_menu(&state);

    if (save_items(items_filename, state.items)) {
        perror("save_items");
    }
    if(save_list(credentials_filename, sizeof(credentials), state.saved_credentials)) {
        perror("save_list");
    }
    if (save_user_state(state_filename, &state)) {
        perror("save_state");
    }
    return 0;
}