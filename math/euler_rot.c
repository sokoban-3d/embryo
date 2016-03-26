#include "euler_rot.h"

#include "axis_rot.h"
#include "axis.h"

void s3d_euler_rot(s3d_mat4 mat, s3d_vec3 rot) {
    for(int i = 0; i < 3; ++i) {
        s3d_axis_rot(mat, rot[i], s3d_axis[i]);
    }
}
