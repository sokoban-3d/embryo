#pragma once

#include "abort_because.h"

#define assert_int(expr, assertion) ({ \
    typeof(expr) val = (expr); \
    \
    if(!(assertion)) { \
        abort_because( \
            "assert_int(" #expr ", " #assertion ") " \
            "failed (val == %d).", val \
        ); \
    } \
    \
    val; \
})
