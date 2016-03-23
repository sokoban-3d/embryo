#include "recompute_slotted_blocks.h"

#include "stg.h"

#include "query_at.h"

void s3d_stg_recompute_slotted_blocks() {
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
