#include <glm/glm.hpp>
#include "normalize.h"

cppfn void s3d_normalize(s3d_vec3 vec) {
    glm::vec3 *_vec = (glm::vec3 *)(vec);

    *_vec = glm::normalize(*_vec);
}
