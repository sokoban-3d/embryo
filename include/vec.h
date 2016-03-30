#ifndef S3D_VEC_H
#define S3D_VEC_H

#define s3d_vec2_assign(vec, x, y) ({ \
    typeof(vec[0]) *vec_ = vec;       \
                                      \
    vec_[0] = x;                      \
    vec_[1] = y;                      \
})

#define s3d_vec3_assign(vec, x, y, z) ({ \
    typeof(vec[0]) *vec_ = vec;          \
                                         \
    vec_[0] = x;                         \
    vec_[1] = y;                         \
    vec_[2] = z;                         \
})

#define s3d_axis_x (s3d_axis[0])
#define s3d_axis_y (s3d_axis[1])
#define s3d_axis_z (s3d_axis[2])

typedef int s3d_ivec2[2];
typedef int s3d_ivec3[3];
typedef int s3d_ivec4[4];

typedef float s3d_fvec2[2];
typedef float s3d_fvec3[3];
typedef float s3d_fvec4[4];

extern s3d_fvec3 s3d_axis[3];

#endif
