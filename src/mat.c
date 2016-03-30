#include "mat.h"

#include<string.h>

#include "vec.h"

void s3d_identity(s3d_fmat4 mat) {
    static const s3d_fmat4 id = {
        1, 0, 0, 0,
        0, 1, 0, 0,
        0, 0, 1, 0,
        0, 0, 0, 1
    };

    s3d_mat_copy(mat, id);
}
 
void s3d_mat_copy(s3d_fmat4 dest, const s3d_fmat4 src) {
    memcpy(dest, src, sizeof(s3d_fmat4));
}
