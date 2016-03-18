#include <glm/glm.hpp>
#include "mat_mul.h"

cppfn void s3d_mat_mul(s3d_mat4 a, const s3d_mat4 b) {
    glm::mat4 *_a = (glm::mat4 *)(a);
    const glm::mat4 *_b = (const glm::mat4 *)(b);

    *_a = (*_a) * (*_b);
}
