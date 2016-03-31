#ifndef S3D_STG_H
#define S3D_STG_H

#include "model.h"
#include "vec.h"
#include "matrix/type.h"
 
enum {
    s3d_stg_obj_type_none,
    s3d_stg_obj_type_player,
    s3d_stg_obj_type_outer_wall,
    s3d_stg_obj_type_wall,
    s3d_stg_obj_type_block,
    s3d_stg_obj_type_slot
};

typedef struct {
    s3d_ivec2 tpos;

    s3d_fvec3 pos;
    s3d_fvec3 rot;
    s3d_fvec3 scale;

    s3d_fmat4 mat;
} s3d_stg_slot;

typedef struct {
    s3d_ivec2 tpos;

    s3d_fvec3 pos;
    s3d_fvec3 rot;
    s3d_fvec3 scale;

    s3d_fmat4 mat;
} s3d_stg_wall;

typedef struct {
    s3d_ivec2 tpos;

    s3d_fvec3 pos;
    s3d_fvec3 rot;
    s3d_fvec3 scale;

    s3d_fmat4 mat;
} s3d_stg_block;

typedef struct {
    s3d_ivec2 tpos;

    s3d_fvec3 pos;
    s3d_fvec3 rot;
    s3d_fvec3 scale;

    s3d_fmat4 mat;
} s3d_stg_player;

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

void s3d_stg_load_spec(const char *path);
void s3d_stg_load_models(const char *path);
void s3d_stg_init();
void s3d_stg_update();
int s3d_stg_play(int x, int y);
int s3d_stg_push_block(s3d_stg_block *b, int x, int y);

#endif

