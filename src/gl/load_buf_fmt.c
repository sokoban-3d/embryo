#include "gl/load_buf_fmt.h"

#include<GL/GLee.h>
#include<string.h>

#include "error/abort_because.h"
#include "file/read_file.h"
#include "string/rtrim.h"

void s3d_gl_load_buf_fmt(const char *path) {
    char *lines = s3d_read_file(path, 1, 0);

    s3d_strrtrim(lines, "\n");
    s3d_strrtrim(lines, "\r");

    int stride;
    void *uv_offset;

    if(strcmp(lines, "xyz") == 0) {
        stride = 0;
        uv_offset = (void *)(-1);
    }
    else
    if(strcmp(lines, "xyz uv") == 0) {
        stride = 5 * 4;
        uv_offset = (void *)(3 * 4);
    }
    else {
        abort_because("%s: Unrecognized buffer format.");
    }

    free(lines);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, 0, stride, 0);

    if(uv_offset != (void *)(-1)) {
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 2, GL_FLOAT, 0, stride, uv_offset);
    }
}

