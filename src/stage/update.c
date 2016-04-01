#include "stage/update.h"

#include "math/radians.h"
#include "stage/def_macros.h"
 
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

#include "stage/undef_macros.h"
