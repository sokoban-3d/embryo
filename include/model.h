#ifndef S3D_MODEL_H
#define S3D_MODEL_H

typedef struct {
    void *idx_ptr;
    int num_idx;
} s3d_model_idxtab_row;

typedef struct {
    int num_rows;

    s3d_model_idxtab_row *rows;
} s3d_model_idxtab;

typedef struct {
    unsigned va_id;

    unsigned tex_id;

    s3d_model_idxtab idxtab;
} s3d_model;

int s3d_model_load_tex(const char *path);
void s3d_model_load_idxtab(s3d_model_idxtab *tab, const char *path);
void s3d_model_load(s3d_model *m, const char *path);

void s3d_model_bind_va(s3d_model *m);
void s3d_model_bind_tex(s3d_model *m);

void s3d_model_draw(s3d_model *m, int row);

#endif

