#include "pad.h"

#include<GLFW/glfw3.h>

void s3d_pad_callback(GLFWwindow *wnd, int key, int scan, int action, int mods) {
    if(action == GLFW_REPEAT) {
        return;
    }

    int active = (action == GLFW_PRESS);

    // TODO: Make keys bindings configurable.
    // TODO: Implement actual gamepad support.

    switch(key) {
        #define key_case(key, btn)                           \
            case GLFW_KEY_##key:                             \
                if (active) {                                \
                    s3d_pad_btn(btn) = (                     \
                        s3d_pad_btn_hit | s3d_pad_btn_active \
                    );                                       \
                                                             \
                } else if (s3d_pad_btn_st(btn, active)) {    \
                    s3d_pad_btn(btn) = s3d_pad_btn_release;  \
                }                                            \
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

void s3d_pad_update() {
    #define update_btn(btn) \
        if(s3d_pad_btn_st(btn, hit)) { \
            s3d_pad_btn(btn) ^= s3d_pad_btn_hit; \
        } \
        \
        if(s3d_pad_btn_st(btn, release)) { \
            s3d_pad_btn(btn) ^= s3d_pad_btn_release; \
        }

    update_btn(A);
    update_btn(X);

    update_btn(L);
    update_btn(R);

    update_btn(DL);
    update_btn(DU);
    update_btn(DR);
    update_btn(DD);

    #undef update_btn
}

