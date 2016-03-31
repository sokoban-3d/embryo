#ifndef S3D_ASSERT_PTR_H
#define S3D_ASSERT_PTR_H

#include "error/abort_because.h"

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
