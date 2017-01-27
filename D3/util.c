#include "util.h"

#include <stdlib.h>
#include <time.h>

char* gen_time(char* buffer) {
    time_t timer;
    time(&timer);

    struct tm* tm_info = localtime(&timer);

    strftime(buffer, 10, "%H:%M:%S", tm_info);
    buffer[10] = 0;

    return buffer;
}
