#include <GL/GLee.h>

#include "bind.h"

void s3d_txt_bind(s3d_txt *txt) {
    glBindVertexArray(txt->va_id);

    glBindBuffer(GL_ARRAY_BUFFER, txt->vb_id);
}
