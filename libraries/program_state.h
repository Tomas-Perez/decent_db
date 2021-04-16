#ifndef PROGRAM_STATE_H
#define PROGRAM_STATE_H

#include "libraries/list.h"
#include "credentials.h"

typedef struct user_state {
    int user_id_gen;
    int current_user_id;
} user_state;

typedef struct program_state {
    list *items;
    list *saved_credentials;
    credentials *current_user;
    user_state u_state;
} program_state;

#endif