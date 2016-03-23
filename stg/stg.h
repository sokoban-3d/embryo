#pragma once

#include "../math/vec3.h"
#include "../math/intvec2.h"

#include "../model/model.h"

#include "player.h"
#include "wall.h"
#include "block.h"
#include "slot.h"

struct {
    struct {
        s3d_intvec2 sz;

        s3d_vec3 origin;

        float tsz;
    } board;

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
