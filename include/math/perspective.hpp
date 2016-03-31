#ifndef S3D_MATH_PERSPECTIVE_H 
#define S3D_MATH_PERSPECTIVE_H 

#include "cppfn.h"
#include "matrix/type.h"

cppfn void s3d_perspective(s3d_fmat4 out, float fov, float ratio, float near, float far);

#endif
