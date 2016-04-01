#include "stage/play.h"

#include "error/abort_because.h"
#include "stage/obj_type.h"
#include "stage/push_block.h"
#include "stage/query_at.h"
#include "stage/type.h"

int s3d_stg_play(int x, int y) {
    if(
        (x && y) ||
        (!x && !y) ||
        (x < -1 || x > 1) ||
        (y < -1 || y > 1)
    ) {
        abort_because("Invalid move: (%d, %d).", x, y);
    }

    s3d_stg.pushed = 0;
    s3d_stg.slotted = 0;

    s3d_stg_player *p = &s3d_stg.player;

    int dx = p->tpos[0] + x;
    int dy = p->tpos[1] + y;

    {
        int d_obj_type;
        void *d_obj;

        s3d_stg_query_at(dx, dy, &d_obj_type, &d_obj, 0);

        switch(d_obj_type) {
            case s3d_stg_obj_type_outer_wall:
            case s3d_stg_obj_type_wall:
                return 0;

            case s3d_stg_obj_type_block:
                if(!s3d_stg_push_block(d_obj, x, y)) { return 0; }

                break;
        }
    }

    p->tpos[0] = dx;
    p->tpos[1] = dy;

    return 1;
}
