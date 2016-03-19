#pragma once

#include "vertex.h"

typedef struct {
    unsigned va_id;
    unsigned vb_id;

    int num_xyz;

    s3d_txt_vertex *buf;
} s3d_txt;
