#pragma once

#include "../math/intvec2.h"

#include "player.h"
#include "wall.h"
#include "block.h"
#include "slot.h"

struct {
    s3d_intvec2 sz;

    s3d_stg_player player;

    int num_walls;
    s3d_stg_wall *walls;

    int num_blocks;
    s3d_stg_block *blocks;

    int num_slots;
    s3d_stg_slot *slots;

    int num_slotted_blocks;

    int pushed;
    int slotted;
} s3d_stg;
