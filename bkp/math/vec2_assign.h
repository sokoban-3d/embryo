#pragma once

#define s3d_vec2_assign(vec, x, y) ({ \
    typeof(vec[0]) *vec_ = vec; \
    \
    vec_[0] = x; \
    vec_[1] = y; \
})
