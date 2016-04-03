#pragma once

#include "char_info.h"

typedef struct {
    int line_height;

    int base;

    int scale_w, scale_h;

    int num_chars;
    s3d_fnt_char_info *chars;
} s3d_fnt_info;
