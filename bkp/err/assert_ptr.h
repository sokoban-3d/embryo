#pragma once

#include "abort_because.h"

#define assert_ptr(expr) ({ \
    typeof(expr) val = (expr); \
    \
    if(!val) { \
        abort_because( \
            "assert_ptr(" #expr ") failed (val == %d).", \
            val \
        ); \
    } \
    \
    val; \
})
