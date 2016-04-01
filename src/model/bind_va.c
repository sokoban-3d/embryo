#include "model/bind_va.h"

void s3d_model_bind_va(s3d_model *m) {
    glBindVertexArray(m->va_id);
}
