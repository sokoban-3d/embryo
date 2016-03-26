#include <linux/limits.h>

#include <unistd.h>

#include "load_tex.h"

#include "../str/arrjoin.h"

#include "../gl/load_dds.h"

int s3d_model_load_tex(const char *path) {
    static char path_buf[PATH_MAX];

    s3d_strarrjoin(path_buf, { path, "/tex" });

    if(access(path_buf, F_OK) != 0) {
        return 0;
    }

    int id;

    s3d_gl_load_dds(&id, path_buf);

    return id;
}
