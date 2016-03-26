#pragma once

#include "../math/intvec2.h"
#include "../math/vec3.h"
#include "../math/mat4.h"

typedef struct {
    s3d_intvec2 tpos;

    s3d_vec3 pos;
    s3d_vec3 rot;
    s3d_vec3 scale;

    s3d_mat4 mat;
} s3d_stg_block;
