#include "load.h"

#include "load_bufs.h"
#include "load_idxtab.h"

void s3d_model_load(s3d_model *m, const char *path) {
    m->va_id = s3d_model_load_bufs(path);

    s3d_model_load_idxtab(&m->idxtab, path);
}
