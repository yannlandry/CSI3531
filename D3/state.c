#include "state.h"

#include <stdlib.h>
#include <string.h>

struct state* newState() {
    struct state* s = (struct state*)malloc(sizeof(struct state));
    memset(s, 0, sizeof(struct state));
    return s;
}
