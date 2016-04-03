#pragma once

#include "arrcpy.h"
#include "arrcat.h"
#include "../mem/array_len.h"

#define s3d_strarrjoin(dst, ...) ({ \
    const char *strs_[] = __VA_ARGS__; \
    \
    s3d_strarrcpy(dst, strs_[0]); \
    \
    for(int i = 1; i < s3d_array_len(strs_); ++i) { \
        s3d_strarrcat(dst, strs_[i]); \
    } \
    \
    dst; \
})
