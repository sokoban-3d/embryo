#include "gl/load_dds.h" 

#include<GL/GLee.h>

#include "err.h"
#include "sys.h"

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

