#include "math.hpp"

#include<glm/gtx/transform.hpp>

#include "cppfn.h"
#include "mat.h"
#include "maths.h"
#include "vec.h"

cppfn void s3d_translate(s3d_fmat4 mat, const s3d_fvec3 val) {
    glm::mat4 *_mat = (glm::mat4 *)(mat);
    const glm::vec3 *_val = (const glm::vec3 *)(val);

    *_mat *= glm::translate(*_val);
}

cppfn void s3d_scale(s3d_fmat4 mat, const s3d_fvec3 val) {
    glm::mat4 *_mat = (glm::mat4 *)(mat);
    const glm::vec3 *_val = (const glm::vec3 *)(val);

    *_mat = glm::scale(*_mat, *_val);
}

cppfn void s3d_axis_rot(s3d_fmat4 out, float angle, const s3d_fvec3 axis) {
    glm::mat4 *_out = (glm::mat4 *)(out);
    const glm::vec3 *_axis = (const glm::vec3 *)(axis);

    *_out = glm::rotate(*_out, angle, *_axis);
}
   
cppfn void s3d_euler_rot(s3d_fmat4 mat, s3d_fvec3 rot) {
    for(int i = 0; i < 3; ++i) {
        s3d_axis_rot(mat, rot[i], s3d_axis[i]);
    }
}

