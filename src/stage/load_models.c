#include "stage/load_models.h"

#include<linux/limits.h>

#include "model/load.h"
#include "model/type.h"
#include "stage/type.h"
#include "string/arrjoin.h"

void s3d_stg_load_models(const char *path) {
    static char path_buf[PATH_MAX];

    {
        s3d_strarrjoin(path_buf, { path, "/model/stg" });

        s3d_model *m = &s3d_stg.model;

        s3d_model_load(m, path_buf);
    }

    {
        s3d_strarrjoin(path_buf, { path, "/model/player" });

        s3d_model *m = &s3d_stg.player_model;

        s3d_model_load(m, path_buf);
    }

    {
        s3d_strarrjoin(path_buf, { path, "/model/wall" });

        s3d_model *m = &s3d_stg.wall_model;

        s3d_model_load(m, path_buf);
    }

    {
        s3d_strarrjoin(path_buf, { path, "/model/block" });

        s3d_model *m = &s3d_stg.block_model;

        s3d_model_load(m, path_buf);
    }

    {
        s3d_strarrjoin(path_buf, { path, "/model/slot" });

        s3d_model *m = &s3d_stg.slot_model;

        s3d_model_load(m, path_buf);
    }
}
