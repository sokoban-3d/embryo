#include "pad/update.h"

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

