#include <GLFW/glfw3.h>

#include "draw.h"

void s3d_color_quad_draw() {
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
}
