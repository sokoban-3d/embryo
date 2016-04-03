#include "matrix/copy.h"

#include<string.h>

#include "matrix/type.h"

void s3d_mat_copy(s3d_fmat4 dest, const s3d_fmat4 src) {
    memcpy(dest, src, sizeof(s3d_fmat4));
}
