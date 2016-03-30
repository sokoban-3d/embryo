#include <string.h>
#include <glm/gtc/matrix_transform.hpp>
#include "axis_rot.h"

cppfn void s3d_axis_rot(s3d_mat4 out, float angle, const s3d_vec3 axis) {
    glm::mat4 *_out = (glm::mat4 *)(out);
    const glm::vec3 *_axis = (const glm::vec3 *)(axis);

    *_out = glm::rotate(*_out, angle, *_axis);
}
