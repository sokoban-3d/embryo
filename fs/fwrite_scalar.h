#pragma once

#include <stdio.h>

#define s3d_fwrite_scalar(val, f) ({ \
    typeof(val) _val = val; \
    \
    fwrite(&_val, sizeof(_val), 1, f); \
})
