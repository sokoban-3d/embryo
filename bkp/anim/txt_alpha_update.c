#include "txt_alpha_update.h"

#include "../time/since.h"
#include "../time/now.h"

#include "../math/clamp.h"

void s3d_anim_txt_alpha_update(s3d_anim_txt_alpha_state *st) {
    s3d_txt *txt = st->txt;

    int num_chars = txt->num_xyz / 6;
    int num_cols = num_chars * 2;

    s3d_txt_vertex *buf = txt->buf;

    float elapsed = s3d_since(st->start) * st->speed;

    if(elapsed > num_cols) {
        st->done = 1;

        return;
    }

    for(int i = 0, col = 0; i < num_chars; ++i) {
        s3d_txt_vertex *v = &buf[i * 6];

        #define va(off) (v[off].rgba[3])

        #define lcol va(0) = va(2) = va(3)
        #define rcol va(1) = va(4) = va(5)

        lcol = s3d_clamp(elapsed - col++, 0, 1);
        rcol = s3d_clamp(elapsed - col++, 0, 1);
    }
}
