#include "stage/init.h"

void s3d_stg_init() {
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
        s3d_vec3_assign(s3d_stg.scale, 1, 1, 1);

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
