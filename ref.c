#include <assert.h>
#include <libgen.h>
#include <GL/GLee.h>
#include <GLFW/glfw3.h>
#include "gl/init.h"
#include "gl/load_dds.h"
#include "gl/should_close.h"
#include "gl/wnd.h"
#include "gl/swap.h"
#include "glsl/load_program.h"
#include "math/identity.h"
#include "math/proportional_scale.h"
#include "math/translate.h"
#include "math/perspective.h"
#include "math/normalize.h"
#include "math/radians.h"
#include "math/mat_copy.h"
#include "math/mat_mul.h"
#include "math/axis_rot.h"
#include "time/fsleep.h"

int main() {
    int w = 800, h = 600;

    s3d_gl_init(w, h, basename(__FILE__));

    float xyz[] = {
        -1, -1, -1,
        -1, -1, 1,
        -1, 1, 1,
        1, 1, -1,
        -1, -1, -1,
        -1, 1, -1,
        1, -1, 1,
        -1, -1, -1,
        1, -1, -1,
        1, 1, -1,
        1, -1, -1,
        -1, -1, -1,
        -1, -1, -1,
        -1, 1, 1,
        -1, 1, -1,
        1, -1, 1,
        -1, -1, 1,
        -1, -1, -1,
        -1, 1, 1,
        -1, -1, 1,
        1, -1, 1,
        1, 1, 1,
        1, -1, -1,
        1, 1, -1,
        1, -1, -1,
        1, 1, 1,
        1, -1, 1,
        1, 1, 1,
        1, 1, -1,
        -1, 1, -1,
        1, 1, 1,
        -1, 1, -1,
        -1, 1, 1,
        1, 1, 1,
        -1, 1, 1,
        1, -1, 1
    };

    float uv[] = {
        0.000059, 1.0 - 0.000004,
        0.000103, 1.0 - 0.336048,
        0.335973, 1.0 - 0.335903,
        1.000023, 1.0 - 0.000013,
        0.667979, 1.0 - 0.335851,
        0.999958, 1.0 - 0.336064,
        0.667979, 1.0 - 0.335851,
        0.336024, 1.0 - 0.671877,
        0.667969, 1.0 - 0.671889,
        1.000023, 1.0 - 0.000013,
        0.668104, 1.0 - 0.000013,
        0.667979, 1.0 - 0.335851,
        0.000059, 1.0 - 0.000004,
        0.335973, 1.0 - 0.335903,
        0.336098, 1.0 - 0.000071,
        0.667979, 1.0 - 0.335851,
        0.335973, 1.0 - 0.335903,
        0.336024, 1.0 - 0.671877,
        1.000004, 1.0 - 0.671847,
        0.999958, 1.0 - 0.336064,
        0.667979, 1.0 - 0.335851,
        0.668104, 1.0 - 0.000013,
        0.335973, 1.0 - 0.335903,
        0.667979, 1.0 - 0.335851,
        0.335973, 1.0 - 0.335903,
        0.668104, 1.0 - 0.000013,
        0.336098, 1.0 - 0.000071,
        0.000103, 1.0 - 0.336048,
        0.000004, 1.0 - 0.671870,
        0.336024, 1.0 - 0.671877,
        0.000103, 1.0 - 0.336048,
        0.336024, 1.0 - 0.671877,
        0.335973, 1.0 - 0.335903,
        0.667969, 1.0 - 0.671889,
        1.000004, 1.0 - 0.671847,
        0.667979, 1.0 - 0.335851
    };

    {
        unsigned va_id;

        glGenVertexArrays(1, &va_id);
        glBindVertexArray(va_id);

        unsigned xyz_vb_id;

        glGenBuffers(1, &xyz_vb_id);
        glBindBuffer(GL_ARRAY_BUFFER, xyz_vb_id);
        glBufferData(GL_ARRAY_BUFFER, sizeof(xyz), xyz, GL_STATIC_DRAW);

        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, 0, 0, 0);

        unsigned uv_vb_id;

        glGenBuffers(1, &uv_vb_id);
        glBindBuffer(GL_ARRAY_BUFFER, uv_vb_id);
        glBufferData(GL_ARRAY_BUFFER, sizeof(uv), uv, GL_STATIC_DRAW);

        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 2, GL_FLOAT, 0, 0, 0);

        s3d_gl_load_dds(0, "data/tex/grid_256.dds");
    }

    unsigned p_id = s3d_glsl_load_program(
        "glsl/xyz_uv.xyz.glsl", "glsl/uv_tex.frag.glsl"
    );

    glUseProgram(p_id);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    unsigned mvp_id = glGetUniformLocation(p_id, "mvp");

    s3d_mat4 model_mat;
    s3d_identity(model_mat);

    s3d_mat4 view_mat;
    s3d_vec3 view_translation = { 0, 0, -5 };
    s3d_translate(view_mat, view_translation);

    s3d_vec3 y_axis = { 0, 1, 0 };
    s3d_normalize(y_axis);

    s3d_mat4 mvp;

    while(!s3d_gl_should_close()) {
        assert(!glGetError());

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glfwGetWindowSize(s3d_gl_wnd, &w, &h);

        s3d_perspective(mvp, s3d_radians(45), (float)(w) / h, 0.1, 100);
        s3d_mat_mul(mvp, view_mat);
        s3d_mat_mul(mvp, model_mat);

        s3d_axis_rot(model_mat, s3d_radians(1), y_axis);

        glUniformMatrix4fv(mvp_id, 1, 0, (float *)(mvp));

        glDrawArrays(GL_TRIANGLES, 0, sizeof(xyz) / 3);

        s3d_gl_swap();

        glfwPollEvents();

        s3d_fsleep(0.001);
    }

    return 0;
}
