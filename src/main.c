#include<GL/GLee.h>
#include<GLFW/glfw3.h>

#include "gl.h"
#include "glsl.h"
#include "mat.h"
#include "maths.h"
#include "pad.h"
#include "stg.h"
#include "vec.h"

s3d_ivec2 wnd_sz;

struct {
    float fov;
    s3d_fvec3 rot;
    s3d_ivec3 pos;
    s3d_fmat4 mat;
} cam;

struct {
    unsigned id;

    struct {
        unsigned mvp_id;
    } uni;
} main_prog;

int main(int argc, char **argv) {
    s3d_vec2_assign(wnd_sz, 1280, 720);

    s3d_gl_init(wnd_sz[0], wnd_sz[1], "Sokoban 3D Prototype");

    glfwSetKeyCallback(s3d_gl_wnd, s3d_pad_callback);

    {
        cam.fov = s3d_radians(45);

        s3d_vec3_assign(cam.rot,
            s3d_radians(45), s3d_radians(-35), 0
        );

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

    return 0;
}
