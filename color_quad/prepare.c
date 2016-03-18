#include <GL/GLee.h>

#include "prepare.h"

#include "../glsl/load_program.h"

#include "../err/assert_gl_ok.h"

void s3d_color_quad_prepare() {
    static unsigned va_id = 0;
    static unsigned vb_id;

    static unsigned p_id;

    if(va_id) {
        glBindVertexArray(va_id);

        glBindBuffer(GL_ARRAY_BUFFER, vb_id);

        glUseProgram(p_id);
    }
    else {
        glGenVertexArrays(1, &va_id);
        glBindVertexArray(va_id);

        glGenBuffers(1, &vb_id);
        glBindBuffer(GL_ARRAY_BUFFER, vb_id);
        glBufferData(GL_ARRAY_BUFFER, 6 * 4 * 4, 0, GL_DYNAMIC_DRAW);

        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 2, GL_FLOAT, 0, 2 * 4, 0);

        glEnableVertexAttribArray(1);

        glVertexAttribPointer(
            1, 4, GL_FLOAT, 0, 4 * 4, (void *)(2 * 4 * 4)
        );

        p_id = s3d_glsl_load_program(
            "glsl/xy_rgba.xyz.glsl", "glsl/rgba.frag.glsl"
        );
    }

    assert_gl_ok();
}
