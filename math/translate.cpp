#include <glm/gtx/transform.hpp>
#include "translate.h"

cppfn void s3d_translate(s3d_mat4 mat, const s3d_vec3 val) {
    glm::mat4 *_mat = (glm::mat4 *)(mat);
    const glm::vec3 *_val = (const glm::vec3 *)(val);

    *_mat *= glm::translate(*_val);
}
