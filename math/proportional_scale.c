#include "proportional_scale.h"
#include "scale.h"

void s3d_proportional_scale(s3d_mat4 mat, float val) {
    s3d_vec3 val_vec = { val, val, val };

    s3d_scale(mat, val_vec);
}
