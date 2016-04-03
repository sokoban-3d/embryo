#pragma once

#include "txt.h"

#include "../fnt/fnt.h"

#include "../math/vec3.h"

void s3d_txt_init(
    s3d_txt *txt, s3d_fnt *fnt, s3d_vec3 rgb,
    const char *encoding, const char *msg
);
