#include "math/axis_rot.hpp" 

#include<glm/gtx/transform.hpp>

#include "cppfn.h"
#include "matrix/type.h"
#include "vector/type.h"

cppfn void s3d_axis_rot(s3d_fmat4 out, float angle, const s3d_fvec3 axis) {
    glm::mat4 *_out = (glm::mat4 *)(out);
    const glm::vec3 *_axis = (const glm::vec3 *)(axis);

    *_out = glm::rotate(*_out, angle, *_axis);
}

