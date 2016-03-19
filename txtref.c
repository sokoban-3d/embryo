#include <libgen.h>

#include <GL/GLee.h>
#include <GLFW/glfw3.h>

#include "gl/init.h"
#include "gl/should_close.h"
#include "gl/wnd.h"
#include "gl/swap.h"
#include "gl/u8_rgb.h"

#include "err/assert_gl_ok.h"
#include "err/assert_int.h"

#include "color_quad/prepare.h"
#include "color_quad/set.h"
#include "color_quad/draw.h"

#include "geom/full_screen_quad.h"

#include "glsl/load_program.h"

#include "fnt/load.h"

#include "txt/init.h"
#include "txt/bind.h"
#include "txt/upload.h"
#include "txt/draw.h"

#include "time/fsleep.h"

int main(int argc, char **argv) {
    int w = 800, h = 600;

    s3d_gl_init(w, h, basename(__FILE__));

    assert_int(argc, val <= 4);

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

    s3d_txt txt;

    {
        s3d_fnt fnt;

        s3d_fnt_load(&fnt, (argc >= 2)? argv[1] : "data/fnt/jp");

        s3d_vec3 color = { 0.8, 1, 0.8 };

        s3d_txt_init(
            &txt, &fnt, color, 0, (argc >= 3)? argv[2] : "京都は綺麗"
        );

        s3d_txt_upload(&txt, GL_STATIC_DRAW);
    }

    unsigned p_id = s3d_glsl_load_program(
        "glsl/fnt.xyz.glsl", "glsl/fnt.frag.glsl"
    );

    unsigned vw_uni_id = glGetUniformLocation(p_id, "vw");
    unsigned xy_uni_id = glGetUniformLocation(p_id, "xy");

    while(!s3d_gl_should_close()) {
        assert_gl_ok();

        int w, h;

        glfwGetWindowSize(s3d_gl_wnd, &w, &h);

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        {
            s3d_color_quad_prepare();

            s3d_color_quad_draw();
        }

        {
            glUseProgram(p_id);

            {
                s3d_vec2 vw = { w, h };

                glUniform2fv(vw_uni_id, 1, vw);
            }

            {
                s3d_vec2 xy = { 0.008, 0.009 };

                glUniform2fv(xy_uni_id, 1, xy);
            }

            {
                glEnable(GL_BLEND);
                glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

                s3d_txt_bind(&txt);

                s3d_txt_draw(&txt);
            }
        }

        s3d_gl_swap();

        glfwPollEvents();

        s3d_fsleep(0.001);
    }

    return 0;
}
