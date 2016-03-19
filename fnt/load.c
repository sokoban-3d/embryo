#include <linux/limits.h>

#include "load.h"

#include "load_info.h"

#include "../str/arrjoin.h"

#include "../gl/load_dds.h"

void s3d_fnt_load(s3d_fnt *fnt, const char *path) {
    s3d_fnt_load_info(&fnt->info, path);

    {
        static char path_buf[PATH_MAX];

        s3d_strarrjoin(path_buf, { path, "/tex" });

        s3d_gl_load_dds(&fnt->tex_id, path_buf);
    }
}
