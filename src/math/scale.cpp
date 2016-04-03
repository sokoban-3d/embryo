#include "math/scale.hpp"

#include<glm/gtx/transform.hpp>

#include "cppfn.h"
#include "matrix/type.h"
#include "vector/type.h"

cppfn void s3d_scale(s3d_fmat4 mat, const s3d_fvec3 val) {
    glm::mat4 *_mat = (glm::mat4 *)(mat);
    const glm::vec3 *_val = (const glm::vec3 *)(val);

    *_mat = glm::scale(*_mat, *_val);
}

