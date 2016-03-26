#include <assert.h>

#include "push_block.h"

#include "stg.h"

#include "query_at.h"
#include "obj_type.h"

#include "../err/abort_because.h"

int s3d_stg_push_block(s3d_stg_block *b, int x, int y) {
    assert(b);

    if(!x && !y) {
        abort_because("Invalid push: (%d, %d).", x, y);
    }

    int dx = b->tpos[0] + x;
    int dy = b->tpos[1] + y;

    {
        int d_obj_type;

        void *d_obj;
        s3d_stg_slot *d_slot;

        s3d_stg_query_at(dx, dy, &d_obj_type, &d_obj, &d_slot);

        if(
            d_obj_type == s3d_stg_obj_type_outer_wall
            || (d_obj && d_obj_type != s3d_stg_obj_type_slot)
        ) {
            return 0;
        }

        if(d_slot) {
            ++s3d_stg.num_slotted_blocks;

            s3d_stg.slotted = 1;
        }
    }

    {
        s3d_stg_slot *o_slot;

        s3d_stg_query_at(b->tpos[0], b->tpos[1], 0, 0, &o_slot);

        if(o_slot) {
            --s3d_stg.num_slotted_blocks;
        }
    }

    b->tpos[0] = dx;
    b->tpos[1] = dy;

    s3d_stg.pushed = 1;

    return 1;
}
