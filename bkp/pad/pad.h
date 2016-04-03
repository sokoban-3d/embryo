#pragma once

#define s3d_pad_btn_A 0
#define s3d_pad_btn_X 1

#define s3d_pad_btn_L 2
#define s3d_pad_btn_R 3

#define s3d_pad_btn_DL 4
#define s3d_pad_btn_DU 5
#define s3d_pad_btn_DR 6
#define s3d_pad_btn_DD 7

#define s3d_pad_num_btns (s3d_pad_btn_DD + 1)

struct {
    int btns[s3d_pad_num_btns];
} s3d_pad;

#define s3d_pad_btn(btn) (s3d_pad.btns[s3d_pad_btn_##btn])

#define s3d_pad_btn_active 1
#define s3d_pad_btn_hit 2
#define s3d_pad_btn_release 4

#define s3d_pad_btn_st(btn, state) \
    (s3d_pad_btn(btn) & s3d_pad_btn_##state)
