#include <string.h>
#include <glm/gtx/transform.hpp>
#include "perspective.h"

cppfn void s3d_perspective(
    s3d_mat4 out, float fov, float ratio, float near, float far
) {
    glm::mat4 *_out = (glm::mat4 *)(out);

    *_out = glm::perspective(fov, ratio, near, far);
}
