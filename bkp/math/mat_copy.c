#include <string.h>
#include "mat_copy.h"

void s3d_mat_copy(s3d_mat4 dest, const s3d_mat4 src) {
    memcpy(dest, src, sizeof(s3d_mat4));
}
