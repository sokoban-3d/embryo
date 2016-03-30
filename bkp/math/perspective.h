#pragma once

#include "../other/cppfn.h"
#include "mat4.h"

cppfn void s3d_perspective(
    s3d_mat4 out, float fov, float ratio, float near, float far
);
