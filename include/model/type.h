#ifndef S3D_MODEL_TYPE_H
#define S3D_MODEL_TYPE_H

#include "model/idxtab.h"

typedef struct {
    unsigned va_id;

    unsigned tex_id;

    s3d_model_idxtab idxtab;
} s3d_model;

#endif
