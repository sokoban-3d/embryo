#include <GL/GLee.h>
#include <GLFW/glfw3.h>

#include "load_buf.h"

#include "../fs/read_file.h"

#include "../err/assert_gl_ok.h"

unsigned s3d_gl_load_buf(int type, const char *path, int hint) {
    unsigned buf_id;

    glGenBuffers(1, &buf_id);

    int len;
    char *data = s3d_read_file(path, 0, &len);

    glBindBuffer(type, buf_id);
    glBufferData(type, len, data, hint);

    assert_gl_ok();

    free(data);

    return buf_id;
}
