#pragma once

#include <inttypes.h>
#include "fnt.h"

void s3d_fnt_find_char_info(
    s3d_fnt *fnt, s3d_fnt_char_info **char_info, uint32_t code
);
