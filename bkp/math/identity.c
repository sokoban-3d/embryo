#include "mat_copy.h"
#include "identity.h"

void s3d_identity(s3d_mat4 mat) {
    static const s3d_mat4 id = {
        1, 0, 0, 0,
        0, 1, 0, 0,
        0, 0, 1, 0,
        0, 0, 0, 1
    };

    s3d_mat_copy(mat, id);
}
