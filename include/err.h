#ifndef S3D_ERR_H
#define S3D_ERR_H

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

#define assert_bool(expr) ({                              \
    typeof(expr) val = (expr);                            \
                                                          \
    if (!val) {                                           \
        abort_because(                                    \
            "assert_bool(" #expr ") failed (val == %d).", \
            val                                           \
        );                                                \
    }                                                     \
                                                          \
    val;                                                  \
})

#define assert_ptr(expr) ({                              \
    typeof(expr) val = (expr);                           \
                                                         \
    if (!val) {                                          \
        abort_because(                                   \
            "assert_ptr(" #expr ") failed (val == %d).", \
            val                                          \
        );                                               \
    }                                                    \
                                                         \
    val;                                                 \
})

#endif
