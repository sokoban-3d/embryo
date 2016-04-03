#include "matrix/identity.h"

#include "matrix/type.h"
#include "matrix/copy.h"

void s3d_identity(s3d_fmat4 mat) {
    static const s3d_fmat4 id = {
        1, 0, 0, 0,
        0, 1, 0, 0,
        0, 0, 1, 0,
        0, 0, 0, 1
    };

    s3d_mat_copy(mat, id);
}

