#include "gl.h"
#include "vec.h"

s3d_ivec2 wnd_sz;

int main(int argc, char **argv) {
    s3d_vec2_assign(wnd_sz, 1280, 720);
    s3d_gl_init(wnd_sz[0], wnd_sz[1], "Sokoban 3D Prototype 1");
    return 0;
}
