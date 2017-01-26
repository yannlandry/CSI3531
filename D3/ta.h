#ifndef TA_H
#define TA_H

#include "state.h"

struct ta {
    int sleeping;
}

struct ta* newTA();

void* taThread(void* arg);

#endif
