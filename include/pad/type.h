#ifndef S3D_PAD_TYPE_H
#define S3D_PAD_TYPE_H

#include "pad/buttons.h"
 
#define s3d_pad_btn(btn) (s3d_pad.btns[s3d_pad_btn_##btn])
#define s3d_pad_num_btns (s3d_pad_btn_DD + 1)

struct {
    int btns[s3d_pad_num_btns];
} s3d_pad;

#endif
