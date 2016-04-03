#include "model/load_bufs.h"

#include<GL/GLee.h>
#include<linux/limits.h>

#include "gl/load_buf.h"
#include "gl/load_buf_fmt.h"
#include "string/arrjoin.h"

unsigned s3d_model_load_bufs(const char *path) {
    unsigned va_id;

    glGenVertexArrays(1, &va_id);
    glBindVertexArray(va_id);

    static char path_buf[PATH_MAX];

    {
        s3d_strarrjoin(path_buf, { path, "/xyz" });

        s3d_gl_load_buf(GL_ARRAY_BUFFER, path_buf, GL_STATIC_DRAW);
    }

    {
        s3d_strarrjoin(path_buf, { path, "/xyzfmt" });

        s3d_gl_load_buf_fmt(path_buf);
    }

    {
        s3d_strarrjoin(path_buf, { path, "/idx" });

        s3d_gl_load_buf(
            GL_ELEMENT_ARRAY_BUFFER, path_buf, GL_STATIC_DRAW
        );
    }

    return va_id;
}
