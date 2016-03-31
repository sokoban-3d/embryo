#include "math/euler_rot.h"

#include "math/axis_rot.hpp"
#include "matrix/type.h"
#include "vector/axis.h"
#include "vector/type.h"

void s3d_euler_rot(s3d_fmat4 mat, s3d_fvec3 rot) {
    for(int i = 0; i < 3; ++i) {
        s3d_axis_rot(mat, rot[i], s3d_axis[i]);
    }
}

