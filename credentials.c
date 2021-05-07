#include <string.h>

#include "libraries/malloc_utils.h"

#include "credentials.h"

credentials *create_credentials(int user_id, const char *username, const char *password) {
    credentials *cred = malloc_or_die(sizeof(credentials));
    cred->user_id = user_id;
    strncpy(cred->username, username, sizeof(cred->username));
    strncpy(cred->password, password, sizeof(cred->password));
    return cred;
}

void destroy_credentials(credentials *c) {
    free(c);
    free(c->username);
    free(c->password);
}