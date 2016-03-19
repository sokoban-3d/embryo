#pragma once

#include "../txt/txt.h"

typedef struct {
    s3d_txt *txt;

    float speed;

    float start;

    int done;
} s3d_anim_txt_alpha_state;
