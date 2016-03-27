#include "init.h"
#include "update.h"

#include "stg.h"
#include "query_at.h"

#include "../math/identity.h"
#include "../math/scale.h"
#include "../math/euler_rot.h"
#include "../math/translate.h"
#include "../math/vec3_assign.h"

#define pos_from_tpos(p, i, j) \
    s3d_stg.board.origin[i] + ( \
        p->tpos[j] * s3d_stg.board.tsz \
    )

#define pos_update(p) \
    p->pos[0] = pos_from_tpos(p, 0, 0); \
    p->pos[1] = s3d_stg.board.origin[1]; \
    p->pos[2] = pos_from_tpos(p, 2, 1);

#define mat_update(p) \
    s3d_identity(p->mat); \
    s3d_scale(p->mat, p->scale); \
    s3d_euler_rot(p->mat, p->rot); \
    s3d_translate(p->mat, p->pos);

void s3d_stg_init() {
    s3d_identity(s3d_stg.mat);

    {
        s3d_stg.num_slotted_blocks = 0;

        for(int i = 0; i < s3d_stg.num_blocks; ++i) {
            s3d_stg_block *b = &s3d_stg.blocks[i];

            s3d_stg_slot *s;

            s3d_stg_query_at(b->tpos[0], b->tpos[1], 0, 0, &s);

            if(s) {
                ++s3d_stg.num_slotted_blocks;
            }
        }
    }

    {
        s3d_vec3_assign(s3d_stg.player.scale, 1, 1, 1);

        for(int i = 0; i < s3d_stg.num_blocks; ++i) {
            s3d_stg_block *b = &s3d_stg.blocks[i];

            s3d_vec3_assign(b->scale, 1, 1, 1);
        }
    }

    for(int i = 0; i < s3d_stg.num_walls; ++i) {
        s3d_stg_wall *w = &s3d_stg.walls[i];

        s3d_vec3_assign(w->scale, 1, 1, 1);

        pos_update(w);
        mat_update(w);
    }

    for(int i = 0; i < s3d_stg.num_slots; ++i) {
        s3d_stg_slot *s = &s3d_stg.slots[i];

        s3d_vec3_assign(s->scale, 1, 1, 1);

        pos_update(s);
        mat_update(s);
    }

    s3d_stg_update();
}

void s3d_stg_update() {
    {
        s3d_stg_player *p = &s3d_stg.player;

        pos_update(p);
        mat_update(p);
    }

    for(int i = 0; i < s3d_stg.num_blocks; ++i) {
        s3d_stg_block *b = &s3d_stg.blocks[i];

        pos_update(b);
        mat_update(b);
    }
}

#undef pos_from_tpos
#undef pos_update
#undef mat_update
