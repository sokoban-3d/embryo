#include <GL/GLee.h>

#include "upload.h"

void s3d_txt_upload(s3d_txt *txt, int usage) {
    glBufferData(
        GL_ARRAY_BUFFER,
        txt->num_xyz * sizeof(s3d_txt_vertex),
        txt->buf,
        usage
    );
}
