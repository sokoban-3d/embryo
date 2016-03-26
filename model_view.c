#include <assert.h>
#include <errno.h>

#include <math.h>

#include <stdio.h>
#include <stdlib.h>

#include <GL/GLee.h>
#include <GLFW/glfw3.h>

#include "err/assert_gl_ok.h"

#include "gl/init.h"
#include "gl/should_close.h"
#include "gl/wnd.h"
#include "gl/u8_rgb.h"
#include "gl/swap.h"

#include "glsl/load_program.h"

#include "model/load.h"
#include "model/bind_va.h"
#include "model/bind_tex.h"

#include "str/empty.h"

#include "math/identity.h"
#include "math/proportional_scale.h"
#include "math/translate.h"
#include "math/perspective.h"
#include "math/normalize.h"
#include "math/radians.h"
#include "math/mat_copy.h"
#include "math/mat_mul.h"
#include "math/axis_rot.h"

#include "geom/full_screen_quad.h"

#include "color_quad/prepare.h"
#include "color_quad/set.h"
#include "color_quad/draw.h"

#include "time/fsleep.h"

int w = 1024, h = 600;

s3d_model model;

int mode = 'A';
int i_idxtab_row = 0;

s3d_mat4 model_mat;
s3d_mat4 view_mat;
s3d_mat4 mvp;

s3d_vec3 view_translation = { 0, -2, -10 };

void print_idxtab_row_index() {
    printf("Current row: %d.\n", i_idxtab_row + 1);
}

void print_mode() {
    switch(mode) {
        case 'A':
            puts("Mode: Render all indices.");
            break;

        case 'S':
            puts("Mode: Render one index row at a time.");
            print_idxtab_row_index();
            break;
    }
}

void change_mode(int c) {
    mode = c;
    print_mode();
}

void jump_rows(int jmp) {
    int num_rows = model.idxtab.num_rows;

    if(num_rows == 1) {
        return;
    }

    if(mode != 'S') {
        change_mode('S');

        return;
    }

    i_idxtab_row += jmp;

    if(i_idxtab_row < 0) {
        i_idxtab_row = num_rows - 1;
    }
    else
    if(i_idxtab_row >= num_rows) {
        i_idxtab_row = 0;
    }

    print_idxtab_row_index();
}

void key_pressed(int key, int scan, int mod) {
    switch(key) {
        case GLFW_KEY_Z: view_translation[2] += 1; break;
        case GLFW_KEY_X: view_translation[2] -= 1; break;

        case GLFW_KEY_A: view_translation[1] += 0.2; break;
        case GLFW_KEY_S: view_translation[1] -= 0.2; break;
    }
}

void key_repeated(int key, int scan, int mod) {}

void key_released(int key, int scan, int mod) {
    switch(key) {
        case GLFW_KEY_Q: glfwSetWindowShouldClose(s3d_gl_wnd, 1); break;

        case GLFW_KEY_N: jump_rows(1); break;
        case GLFW_KEY_P: jump_rows(-1); break;

        case GLFW_KEY_M:
            if(model.idxtab.num_rows == 1) { break; }

            switch(mode) {
                case 'A': change_mode('S'); break;
                case 'S': change_mode('A'); break;
            }
            break;
    }
}

void key_callback(GLFWwindow *wnd, int key, int scan, int action, int mod) {
    switch(action) {
        case GLFW_PRESS:
            key_pressed(key, scan, mod);
            break;

        case GLFW_REPEAT:
            key_repeated(key, scan, mod);
            break;

        case GLFW_RELEASE:
            key_released(key, scan, mod);
            break;
    }
}

int main(int argc, char **argv) {
    assert(argc == 2 || argc == 3);

    char *path = argv[1];

    s3d_gl_init(w, h, "Sokoban 3D Model Viewer");

    glfwSetKeyCallback(s3d_gl_wnd, key_callback);

    s3d_model_load(&model, path);

    assert(model.idxtab.num_rows > 0);

    if(argc == 3) {
        errno = 0;

        char *endptr = 0;

        i_idxtab_row = strtol(argv[2], &endptr, 10) - 1;

        assert(!errno && s3d_strempty(endptr));

        if(i_idxtab_row < 0 || i_idxtab_row >= model.idxtab.num_rows) {
            fprintf(
                stderr, "Index row %d doesn't exist in %s.\n",
                i_idxtab_row + 1, path
            );

            i_idxtab_row = 0;
        }

        mode = 'S';
    }

    printf("Index table row count: %d.\n", model.idxtab.num_rows);

    print_mode();

    unsigned p_id = s3d_glsl_load_program(
        "glsl/xyz_uv.xyz.glsl", "glsl/uv_tex.frag.glsl"
    );

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    unsigned mvp_id = glGetUniformLocation(p_id, "mvp");

    s3d_identity(model_mat);

    s3d_vec3 y_axis = { 0, 1, 0 };
    s3d_normalize(y_axis);

    s3d_model_idxtab_row *idxrow;

    {
        s3d_color_quad_prepare();

        static s3d_vec4 bg_gradient[4] = {
            s3d_gl_u8_rgb(0x0f, 0x38, 0x7f), 1,
            s3d_gl_u8_rgb(0x0f, 0x30, 0x70), 1,
            s3d_gl_u8_rgb(0x40, 0xc0, 0xdf), 1,
            s3d_gl_u8_rgb(0x40, 0xc0, 0xdf), 1
        };

        s3d_color_quad_set(s3d_geom_full_screen_quad, bg_gradient);
    }

    while(!s3d_gl_should_close()) {
        assert_gl_ok();

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glDepthMask(0);

        s3d_color_quad_prepare();

        s3d_color_quad_draw();

        glDepthMask(1);

        glUseProgram(p_id);

        s3d_model_bind_va(&model);

        s3d_model_bind_tex(&model);

        glfwGetWindowSize(s3d_gl_wnd, &w, &h);

        s3d_perspective(mvp, s3d_radians(45), (float)(w) / h, 0.1, 100);

        s3d_identity(view_mat);
        s3d_translate(view_mat, view_translation);

        s3d_mat_mul(mvp, view_mat);
        s3d_mat_mul(mvp, model_mat);

        s3d_axis_rot(model_mat, s3d_radians(1), y_axis);

        glUniformMatrix4fv(mvp_id, 1, 0, (float *)(mvp));

        switch(mode) {
            case 'A':
                for(int i = 0; i < model.idxtab.num_rows; ++i) {
                    idxrow = &model.idxtab.rows[i];

                    glDrawElements(
                        GL_TRIANGLES, idxrow->num_idx, GL_UNSIGNED_INT, idxrow->idx_ptr
                    );
                }
                break;
                
            case 'S':
                idxrow = &model.idxtab.rows[i_idxtab_row];

                glDrawElements(
                    GL_TRIANGLES, idxrow->num_idx, GL_UNSIGNED_INT, idxrow->idx_ptr
                );
                break;
        }

        s3d_gl_swap();

        glfwPollEvents();

        s3d_fsleep(0.001);
    }

    return 0;
}
