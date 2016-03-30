#pragma once

typedef struct {
    void *idx_ptr;
    int num_idx;
} s3d_model_idxtab_row;

typedef struct {
    int num_rows;

    s3d_model_idxtab_row *rows;
} s3d_model_idxtab;
