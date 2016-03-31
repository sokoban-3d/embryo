#ifndef S3D_ERROR_ABORT_BECAUSE_H 
#define S3D_ERROR_ABORT_BECAUSE_H 

#include<stdio.h>
#include<stdlib.h>

#define abort_because(message, more...) ({ \
    fprintf(                               \
        stderr,                            \
        __FILE__ ":%d: %s: " message "\n", \
        __LINE__, __func__,                \
        ##more                             \
    );                                     \
                                           \
    abort();                               \
})

#endif
