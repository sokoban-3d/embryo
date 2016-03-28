#include <GL/GLee.h>
#include <GLFW/glfw3.h>

#include "math/intvec2.h"
#include "math/vec3.h"
#include "math/vec4.h"
#include "math/mat4.h"
#include "math/perspective.h"
#include "math/radians.h"
#include "math/ratio.h"
#include "math/identity.h"
#include "math/translate.h"
#include "math/euler_rot.h"
#include "math/vec2_assign.h"
#include "math/vec3_assign.h"
#include "math/mat_copy.h"
#include "math/mat_mul.h"

#include "gl/init.h"
#include "gl/wnd.h"
#include "gl/should_close.h"
#include "gl/swap.h"

#include "pad/callback.h"
#include "pad/update.h"
#include "pad/pad.h"

#include "glsl/load_program.h"

#include "stg/load_spec.h"
#include "stg/load_models.h"
#include "stg/init.h"
#include "stg/play.h"
#include "stg/update.h"

#include "stg/stg.h"

#include "err/assert_gl_ok.h"

#include "model/bind_va.h"
#include "model/bind_tex.h"
#include "model/draw.h"

#include "time/fsleep.h"

s3d_intvec2 wnd_sz;

struct {
    float fov;
    s3d_vec3 rot;
    s3d_vec3 pos;

    s3d_mat4 mat;
} cam;

void cam_mat_update() {
    s3d_perspective(cam.mat, cam.fov, s3d_ratio(wnd_sz), 0.1, 100);

    s3d_translate(cam.mat, cam.pos);
    s3d_euler_rot(cam.mat, cam.rot);
}

struct {
    unsigned id;

    struct {
        unsigned mvp_id;
    } uni;
} main_prog;

int main(int argc, char **argv) {
    s3d_vec2_assign(wnd_sz, 1280, 720);

    s3d_gl_init(wnd_sz[0], wnd_sz[1], "Sokoban 3D Prototype 1");

    glfwSetKeyCallback(s3d_gl_wnd, s3d_pad_callback);

    {
        cam.fov = s3d_radians(45);

        s3d_vec3_assign(cam.rot, s3d_radians(45), s3d_radians(-35), 0);
        s3d_vec3_assign(cam.pos, 0, 2, -25);
    }

    {
        main_prog.id = s3d_glsl_load_program(
            "glsl/xyz_uv.xyz.glsl", "glsl/uv_tex.frag.glsl"
        );

        main_prog.uni.mvp_id = glGetUniformLocation(
            main_prog.id, "mvp"
        );
    }

    {
        const char *stg_path = (
            (argc >= 2)? argv[1] : "data/stg/proto_2"
        );

        s3d_stg_load_spec(stg_path);

        s3d_stg_load_models(stg_path);

        s3d_stg_init();
    }

    while(!s3d_gl_should_close()) {
        assert_gl_ok();

        if(s3d_stg.num_slotted_blocks == s3d_stg.num_blocks) {
            break;
        }

        if(s3d_pad_btn_st(DL, hit)) {
            s3d_stg_play(-1, 0);
        }
        else
        if(s3d_pad_btn_st(DU, hit)) {
            s3d_stg_play(0, -1);
        }
        else
        if(s3d_pad_btn_st(DR, hit)) {
            s3d_stg_play(1, 0);
        }
        else
        if(s3d_pad_btn_st(DD, hit)) {
            s3d_stg_play(0, 1);
        }

        s3d_stg_update();

        s3d_pad_update();

        glfwGetWindowSize(s3d_gl_wnd, &wnd_sz[0], &wnd_sz[1]);

        cam_mat_update();

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        {
            glDepthMask(1);
            glEnable(GL_DEPTH_TEST);

            glUseProgram(main_prog.id);

            static s3d_mat4 mvp;

            #define upload_mvp() \
                glUniformMatrix4fv( \
                    main_prog.uni.mvp_id, 1, 0, (float *)(mvp) \
                )

            {
                {
                    s3d_mat_copy(mvp, cam.mat);
                    s3d_mat_mul(mvp, s3d_stg.mat);

                    upload_mvp();
                }

                {
                    s3d_model_bind_va(&s3d_stg.model);

                    s3d_model_bind_tex(&s3d_stg.model);

                    s3d_model_draw(&s3d_stg.model, 0);
                }
            }

            {
                {
                    s3d_mat_copy(mvp, cam.mat);
                    s3d_mat_mul(mvp, s3d_stg.player.mat);

                    upload_mvp();
                }

                {
                    s3d_model_bind_va(&s3d_stg.player_model);

                    s3d_model_bind_tex(&s3d_stg.player_model);

                    s3d_model_draw(&s3d_stg.player_model, 0);
                }
            }

            for(int i = 0; i < s3d_stg.num_walls; ++i) {
                s3d_stg_wall *w = &s3d_stg.walls[i];

                {
                    s3d_mat_copy(mvp, cam.mat);
                    s3d_mat_mul(mvp, w->mat);

                    upload_mvp();
                }

                {
                    s3d_model_bind_va(&s3d_stg.wall_model);

                    s3d_model_bind_tex(&s3d_stg.wall_model);

                    s3d_model_draw(&s3d_stg.wall_model, 0);
                }
            }

            for(int i = 0; i < s3d_stg.num_blocks; ++i) {
                s3d_stg_block *b = &s3d_stg.blocks[i];

                {
                    s3d_mat_copy(mvp, cam.mat);
                    s3d_mat_mul(mvp, b->mat);

                    upload_mvp();
                }

                {
                    s3d_model_bind_va(&s3d_stg.block_model);

                    s3d_model_bind_tex(&s3d_stg.block_model);

                    s3d_model_draw(&s3d_stg.block_model, 0);
                }
            }

            for(int i = 0; i < s3d_stg.num_slots; ++i) {
                s3d_stg_slot *s = &s3d_stg.slots[i];

                {
                    s3d_mat_copy(mvp, cam.mat);
                    s3d_mat_mul(mvp, s->mat);

                    upload_mvp();
                }

                {
                    s3d_model_bind_va(&s3d_stg.slot_model);

                    s3d_model_bind_tex(&s3d_stg.slot_model);

                    s3d_model_draw(&s3d_stg.slot_model, 0);
                }
            }

            #undef upload_mvp
        }

        s3d_gl_swap();

        glfwPollEvents();

        s3d_fsleep(0.001);
    }

    return 0;
}
