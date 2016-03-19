#include <GLFW/glfw3.h>

#include "callback.h"

#include "pad.h"

void s3d_pad_callback(
    GLFWwindow *wnd, int key, int scan, int action, int mods
) {
    if(action == GLFW_REPEAT) {
        return;
    }

    int active = (action == GLFW_PRESS);

    // TODO: Make keys bindings configurable.
    // TODO: Implement actual gamepad support.

    switch(key) {
        #define key_case(key, btn) \
            case GLFW_KEY_##key: \
                if(active) { \
                    s3d_pad_btn(btn) = ( \
                        s3d_pad_btn_hit | s3d_pad_btn_active \
                    ); \
                } \
                else \
                if(s3d_pad_btn_st(btn, active)) { \
                    s3d_pad_btn(btn) = s3d_pad_btn_release; \
                } \
                break

        key_case(Z, A);
        key_case(X, X);

        key_case(A, L);
        key_case(S, R);

        key_case(LEFT, DL);
        key_case(UP, DU);
        key_case(RIGHT, DR);
        key_case(DOWN, DD);

        #undef key_case
    }
}
