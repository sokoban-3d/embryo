#ifndef S3D_MAT_H
#define S3D_MAT_H

#include "vec.h"

typedef float s3d_fmat4[4][4];

void s3d_identity(s3d_fmat4 mat);
void s3d_mat_copy(s3d_fmat4 dest, const s3d_fmat4 src);

#endif
