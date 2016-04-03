// No guard.

#include "math/euler_rot.h"
#include "math/scale.hpp"
#include "math/translate.hpp"
#include "matrix/identity.h"
#include "stage/type.h"

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

