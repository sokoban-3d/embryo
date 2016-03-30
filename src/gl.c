#include "gl.h"

#include<GL/GLee.h>
#include<GLFW/glfw3.h>

#include "err.h"
#include "str.h"
#include "sys.h"

GLFWwindow *s3d_gl_wnd = 0;

void glfw_on_error(int err, const char *desc) {
    abort_because("GLFW error: %s", desc);
}

void glfw_on_resize(GLFWwindow *wnd, int width, int height) {
    glViewport(0, 0, width, height);
} 

void s3d_gl_init(int width, int height, const char *wndCaption) {
    glfwSetErrorCallback(glfw_on_error);

    assert_bool(glfwInit());

    s3d_gl_wnd = assert_ptr(
        glfwCreateWindow(width, height, wndCaption, 0, 0)
    );

    glfwMakeContextCurrent(s3d_gl_wnd);
    glfwSwapInterval(1);

    glfwSetWindowSizeCallback(s3d_gl_wnd, glfw_on_resize);
}

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

void s3d_gl_load_dds(unsigned *tex_id, const char *path) {
    int file_len;
    char *file_data = s3d_read_file(path, 0, &file_len);

    if(strncmp(file_data, "DDS ", 4)) {
        abort_because("%s is not a DDS file.", path);
    }

    static const int header_len = 128;

    if(file_len < header_len) {
        abort_because("%s is corrupt.", path);
    }

    unsigned h = *(unsigned *)(&file_data[12]);
    unsigned w = *(unsigned *)(&file_data[16]);
    unsigned linear_len = *(unsigned *)(&file_data[20]);
    unsigned num_mipmaps = *(unsigned *)(&file_data[28]);
    char *fmt = &file_data[84];

    unsigned gl_fmt;
    unsigned block_len;

    if(strncmp(fmt, "DXT1", 4) == 0) {
        gl_fmt = GL_COMPRESSED_RGBA_S3TC_DXT1_EXT;
        block_len = 8;
    }
    else
    if(strncmp(fmt, "DXT3", 4) == 0) {
        gl_fmt = GL_COMPRESSED_RGBA_S3TC_DXT3_EXT;
        block_len = 16;
    }
    else
    if(strncmp(fmt, "DXT5", 4) == 0) {
        gl_fmt = GL_COMPRESSED_RGBA_S3TC_DXT5_EXT;
        block_len = 16;
    }
    else {
        abort_because("%s: Unknown format: %s", path, fmt);
    }

    unsigned tex_id_;

    glGenTextures(1, &tex_id_);
    glBindTexture(GL_TEXTURE_2D, tex_id_);

    unsigned offset = header_len;

    for(int i = 0; i < num_mipmaps && (w || h); ++i) {
        unsigned len = ((w + 3) / 4) * ((h + 3) / 4) * block_len;

        if(offset + len > file_len) {
            abort_because("%s is corrupt.", path);
        }

        glCompressedTexImage2D(
            GL_TEXTURE_2D, i, gl_fmt, w, h, 0, len, file_data + offset
        );

        offset += len;

        w /= 2;
        h /= 2;
    }

    free(file_data);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

    if(tex_id) {
        *tex_id = tex_id_;
    }
}

int s3d_gl_should_close() {
    return glfwWindowShouldClose(s3d_gl_wnd);
}

void s3d_gl_swap() {
    glfwSwapBuffers(s3d_gl_wnd);
}

