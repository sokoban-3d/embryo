#include "txt_alpha_init.h"

#include "../time/now.h"

void s3d_anim_txt_alpha_init(s3d_anim_txt_alpha_state *st) {
    st->start = s3d_now();

    st->done = 0;
}
