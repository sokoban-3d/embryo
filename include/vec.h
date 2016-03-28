#ifndef S3D_VEC_H
#define S3D_VEC_H

#define s3d_vec2_assign(vec, x, y) ({ \
    typeof(vec[0]) *vec_ = vec;       \
                                      \
    vec_[0] = x;                      \
    vec_[1] = y;                      \
})

typedef int s3d_ivec2[2];
typedef int s3d_ivec3[3];
typedef int s3d_ivec4[4];

typedef float s3d_fvec2[2];
typedef float s3d_fvec3[3];
typedef float s3d_fvec4[4];

#endif
