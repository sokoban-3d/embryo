#ifndef S3D_MODEL_IDXTAB_H
#define S3D_MODEL_IDXTAB_H

#include "model/idxtab_row.h"

typedef struct {
    int num_rows;

    s3d_model_idxtab_row *rows;
} s3d_model_idxtab;

#endif
