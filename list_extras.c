#include <stdlib.h>
#include "list_extras.h"

void destroy_list(list *l) {
    free(l);
}