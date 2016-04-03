#include <string.h>

#include <GL/GLee.h>
#include <GLFW/glfw3.h>

#include "set.h"

#include "../err/assert_gl_ok.h"

void s3d_color_quad_set(s3d_vec2 xy[4], s3d_vec4 rgba[4]) {
    // 4 vertices, 2 floats per vertex, 4 bytes per float.
    #define xy_len (4 * 2 * 4)

    // 4 vertices, 4 floats per vertex, 4 bytes per float.
    #define rgba_len (4 * 4 * 4)

    static char buf[xy_len + rgba_len];

    memcpy(buf, xy, xy_len);
    memcpy(buf + xy_len, rgba, rgba_len);

    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(buf), buf);

    assert_gl_ok();
}
