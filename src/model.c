#include "model.h"

#include<assert.h>
#include<errno.h>
#include<linux/limits.h>
#include<string.h>
#include<unistd.h>

#include "err.h"
#include "file.h"
#include "gl.h"
#include "str.h"

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

int s3d_model_load_tex(const char *path) {
    static char path_buf[PATH_MAX];

    s3d_strarrjoin(path_buf, { path, "/tex" });

    if(access(path_buf, F_OK) != 0) {
        return 0;
    }

    int id;

    s3d_gl_load_dds(&id, path_buf);

    return id;
}

void s3d_model_load_idxtab(s3d_model_idxtab *tab, const char *path) {
    char *lines;

    {
        static char path_buf[PATH_MAX];

        s3d_strarrjoin(path_buf, { path, "/idxtab" });

        lines = s3d_read_file(path_buf, 1, 0);
    }

    int num_rows = s3d_strchrcount(lines, '\n');

    s3d_model_idxtab_row *rows = (
        malloc((num_rows + 1) * sizeof(tab->rows[0]))
    );

    s3d_model_idxtab_row *row_ptr = rows;

    for(
        char *tokptr, *line = strtok_r(lines, "\n", &tokptr);
        line;
        line = strtok_r(0, "\n", &tokptr)
    ) {
        s3d_strrtrim(line, "\r");

        char *tok = assert_ptr(strtok(line, " "));

        errno = 0;

        char *endptr = 0;

        row_ptr->idx_ptr = (void *)(strtol(tok, &endptr, 10) * 4);

        assert(!errno && s3d_strempty(endptr));

        tok = assert_ptr(strtok(0, " "));

        endptr = 0;

        row_ptr->num_idx = strtol(tok, &endptr, 10);

        assert(!errno && s3d_strempty(endptr));

        ++row_ptr;
    }

    tab->num_rows = num_rows;
    tab->rows = rows;
}

void s3d_model_load(s3d_model *m, const char *path) {
    m->va_id = s3d_model_load_bufs(path);
    m->tex_id = s3d_model_load_tex(path);

    s3d_model_load_idxtab(&m->idxtab, path);
}

