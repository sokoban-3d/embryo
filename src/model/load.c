#include "model/load.h"

void s3d_model_load(s3d_model *m, const char *path) {
    m->va_id = s3d_model_load_bufs(path);
    m->tex_id = s3d_model_load_tex(path);

    s3d_model_load_idxtab(&m->idxtab, path);
}
 
