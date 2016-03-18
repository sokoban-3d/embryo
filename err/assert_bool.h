#pragma once

#include "abort_because.h"

#define assert_bool(expr) ({ \
    typeof(expr) val = (expr); \
    \
    if(!val) { \
        abort_because( \
            "assert_bool(" #expr ") failed (val == %d).", \
            val \
        ); \
    } \
    \
    val; \
})
