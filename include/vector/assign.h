#ifndef S3D_VECTOR_ASSIGN_H
#define S3D_VECTOR_ASSIGN_H

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

#endif
