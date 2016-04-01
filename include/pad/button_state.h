#ifndef S3D_PAD_BUTTON_STATE_H
#define S3D_PAD_BUTTON_STATE_H

#define s3d_pad_btn_active 1
#define s3d_pad_btn_hit 2
#define s3d_pad_btn_release 4

#define s3d_pad_btn_st(btn, state) \
    (s3d_pad_btn(btn) & s3d_pad_btn_##state)

#endif
