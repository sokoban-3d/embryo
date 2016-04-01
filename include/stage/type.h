#ifndef S3D_STAGE_TYPE_H
#define S3D_STAGE_TYPE_H

struct {
    struct {
        s3d_ivec2 sz;

        s3d_fvec3 origin;

        float tsz;
    } board;

    s3d_fvec3 pos;
    s3d_fvec3 rot;
    s3d_fvec3 scale;

    s3d_fmat4 mat;

    s3d_model model;

    s3d_stg_player player;

    s3d_model player_model;

    int num_walls;
    s3d_stg_wall *walls;

    s3d_model wall_model;

    int num_blocks;
    s3d_stg_block *blocks;

    s3d_model block_model;

    int num_slots;
    s3d_stg_slot *slots;

    s3d_model slot_model;

    int num_slotted_blocks;

    int pushed;
    int slotted;
} s3d_stg;

#endif
