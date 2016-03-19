#include <libgen.h>

#include <string.h>

#include <GLFW/glfw3.h>

#include "gl/init.h"
#include "gl/should_close.h"
#include "gl/wnd.h"
#include "gl/swap.h"

#include "err/assert_gl_ok.h"

#include "pad/callback.h"
#include "pad/pad.h"
#include "pad/reset.h"
#include "pad/update.h"

#include "time/fsleep.h"

int main(int argc, char **argv) {
    int w = 800, h = 600;

    s3d_gl_init(w, h, basename(__FILE__));

    glfwSetKeyCallback(s3d_gl_wnd, s3d_pad_callback);

    int log_held = (argc >= 2 && strcmp(argv[1], "--held") == 0);

    while(!s3d_gl_should_close()) {
        assert_gl_ok();

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glfwPollEvents();

        #define log_btn(btn) \
            if(s3d_pad_btn_st(btn, hit)) { \
                puts(#btn " hit!"); \
            } \
            else \
            if(log_held && s3d_pad_btn_st(btn, active)) { \
                puts(#btn " held!"); \
            } \
            else \
            if(s3d_pad_btn_st(btn, release)) { \
                puts(#btn " release!"); \
            }

        log_btn(A);
        log_btn(X);

        log_btn(L);
        log_btn(R);

        log_btn(DL);
        log_btn(DU);
        log_btn(DR);
        log_btn(DD);

        #undef log_btn

        if(s3d_pad_btn_st(X, hit)) {
            s3d_pad_reset();
        }

        s3d_gl_swap();

        s3d_pad_update();

        s3d_fsleep(0.001);
    }

    return 0;
}
