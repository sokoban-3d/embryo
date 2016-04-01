#ifndef S3D_STAGE_WALL_H
#define S3D_STAGE_WALL_H

typedef struct {
    s3d_ivec2 tpos;

    s3d_fvec3 pos;
    s3d_fvec3 rot;
    s3d_fvec3 scale;

    s3d_fmat4 mat;
} s3d_stg_wall;

#endif
