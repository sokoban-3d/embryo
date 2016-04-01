#include "stage/update.h"

#define pos_from_tpos(p, i, j) \
    s3d_stg.board.origin[i] + ( \
        (p)->tpos[j] * s3d_stg.board.tsz \
    )

#define pos_update(p) \
    (p)->pos[0] = pos_from_tpos((p), 0, 0); \
    (p)->pos[1] = s3d_stg.board.origin[1]; \
    (p)->pos[2] = pos_from_tpos((p), 2, 1);

#define mat_update(p) \
    s3d_identity((p)->mat); \
    s3d_translate((p)->mat, (p)->pos); \
    s3d_euler_rot((p)->mat, (p)->rot); \
    s3d_scale((p)->mat, (p)->scale);
 
void s3d_stg_update() {
    mat_update(&s3d_stg);

    {
        s3d_stg_player *p = &s3d_stg.player;

        p->rot[1] += s3d_radians(2);

        pos_update(p);
        mat_update(p);
    }

    for(int i = 0; i < s3d_stg.num_blocks; ++i) {
        s3d_stg_block *b = &s3d_stg.blocks[i];

        pos_update(b);
        mat_update(b);
    }
}

#undef pos_update
#undef mat_update
#undef pos_from_tpos
