#pragma once

#include <stdlib.h>
#include <stdio.h>

#define abort_because(message, more...) ({ \
    fprintf( \
        stderr, \
        __FILE__ ":%d: %s: " message "\n", \
        __LINE__, __func__, \
        ##more \
    ); \
    \
    abort(); \
})
