#include "math/perspective.hpp"
 
#include<glm/gtx/transform.hpp>

#include "cppfn.h"
#include "matrix/type.h"

cppfn void s3d_perspective(
    s3d_fmat4 out, float fov, float ratio, float near, float far
) {
    glm::mat4 *_out = (glm::mat4 *)(out);

    *_out = glm::perspective(fov, ratio, near, far);
}

