#include "reset.h"

#include "../mem/bzero_array.h"

#include "pad.h"

void s3d_pad_reset() {
    s3d_bzero_array(s3d_pad.btns);
}
