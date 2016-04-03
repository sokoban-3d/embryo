#include <GLFW/glfw3.h>

#include "draw.h"

void s3d_txt_draw(s3d_txt *txt) {
    glDrawArrays(GL_TRIANGLES, 0, txt->num_xyz);
}
