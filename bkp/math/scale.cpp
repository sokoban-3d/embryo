#include <glm/gtx/transform.hpp>
#include "scale.h"

cppfn void s3d_scale(s3d_mat4 mat, const s3d_vec3 val) {
    glm::mat4 *_mat = (glm::mat4 *)(mat);
    const glm::vec3 *_val = (const glm::vec3 *)(val);

    *_mat = glm::scale(*_mat, *_val);
}
