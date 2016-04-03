#include <assert.h>
#include <errno.h>

#include <inttypes.h>
#include <string.h>
#include <stdlib.h>
#include <alloca.h>

#include <iconv.h>

#include <GL/GLee.h>

#include "init.h"

#include "bind.h"

#include "vertex.h"

#include "../mem/offsetof.h"

#include "../fnt/find_char_info.h"

void s3d_txt_init(
    s3d_txt *txt, s3d_fnt *fnt, s3d_vec3 rgb,
    const char *encoding, const char *msg
) {
    {
        glGenVertexArrays(1, &txt->va_id);
        glGenBuffers(1, &txt->vb_id);

        s3d_txt_bind(txt);
    }

    {
        int txt_vertex_len = sizeof(s3d_txt_vertex);

        {
            glEnableVertexAttribArray(0);

            void *xy_off = (void *)(offsetof(s3d_txt_vertex, xy));

            glVertexAttribPointer(
                0, 2, GL_FLOAT, 0, txt_vertex_len, xy_off
            );
        }

        {
            glEnableVertexAttribArray(1);

            void *uv_off = (void *)(offsetof(s3d_txt_vertex, uv));

            glVertexAttribPointer(
                1, 2, GL_FLOAT, 0, txt_vertex_len, uv_off
            );
        }

        {
            glEnableVertexAttribArray(2);

            void *rgba_off = (void *)(
                offsetof(s3d_txt_vertex, rgba)
            );

            glVertexAttribPointer(
                2, 4, GL_FLOAT, 0, txt_vertex_len, rgba_off
            );
        }

        {
            size_t msglen = strlen(msg);

            // TODO: Allocate buf after real
            // character count is known.
            int buflen = msglen * txt_vertex_len * 6;
            s3d_txt_vertex *buf = txt->buf = malloc(buflen);

            {
                uint32_t *msgcodes;

                {
                    errno = 0;

                    if(!encoding) {
                        encoding = "UTF-8";
                    }

                    iconv_t cd = iconv_open("UCS-4LE", encoding);

                    assert(!errno);

                    size_t msgcodes_buflen = (
                        (msglen + 1) * sizeof(*msgcodes)
                    );

                    msgcodes = alloca(msgcodes_buflen);

                    char *inptr = (char *)(msg);
                    char *outptr = (char *)(msgcodes);

                    iconv(
                        cd, &inptr, &msglen,
                        &outptr, &msgcodes_buflen
                    );

                    assert(!errno);

                    iconv_close(cd);

                    assert(msgcodes_buflen > 0);

                    *outptr = 0;
                }

                {
                    s3d_fnt_info *fnt_info = &fnt->info;

                    int i = 0;

                    int pen_x = 0;
                    int pen_y = 0;

                    for(
                        uint32_t *msgcodeptr = msgcodes;
                        *msgcodeptr;
                        ++msgcodeptr
                    ) {
                        // TODO: Why would iconv output
                        // something like this?
                        if(*msgcodeptr > 0x10ffff) {
                            continue;
                        }

                        if(*msgcodeptr == '\n') {
                            pen_x = 0;
                            pen_y += fnt_info->line_height;

                            continue;
                        }

                        s3d_txt_vertex *tlv = &buf[i * 6];

                        s3d_fnt_char_info *char_info;

                        s3d_fnt_find_char_info(
                            fnt, &char_info, *msgcodeptr
                        );

                        int scale_w = fnt_info->scale_w;
                        int scale_h = fnt_info->scale_h;

                        {

                            tlv[0].xy[0] = pen_x + char_info->xoff;

                            tlv[0].xy[1] = (
                                -(pen_y + char_info->yoff)
                            );

                            tlv[0].uv[0] = (
                                (float)(char_info->x) / scale_w
                            );

                            tlv[0].uv[1] = (
                                (float)(char_info->y) / scale_h
                            );
                        }

                        {
                            tlv[1].xy[0] = (
                                tlv[0].xy[0] + char_info->w
                            );

                            tlv[1].xy[1] = tlv[0].xy[1];

                            tlv[1].uv[0] = (
                                tlv[0].uv[0] +
                                ((float)(char_info->w) / scale_w)
                            );

                            tlv[1].uv[1] = tlv[0].uv[1];
                        }

                        {
                            tlv[2].xy[0] = tlv[0].xy[0];

                            tlv[2].xy[1] = (
                                tlv[0].xy[1] - char_info->h
                            );

                            tlv[2].uv[0] = tlv[0].uv[0];

                            tlv[2].uv[1] = (
                                tlv[0].uv[1] +
                                ((float)(char_info->h) / scale_h)
                            );
                        }

                        memcpy(&tlv[3], &tlv[2], sizeof(tlv[3]));

                        memcpy(&tlv[4], &tlv[1], sizeof(tlv[4]));

                        {
                            tlv[5].xy[0] = (
                                tlv[0].xy[0] + char_info->w
                            );

                            tlv[5].xy[1] = (
                                tlv[0].xy[1] - char_info->h
                            );

                            tlv[5].uv[0] = (
                                tlv[0].uv[0] +
                                ((float)(char_info->w) / scale_w)
                            );

                            tlv[5].uv[1] = (
                                tlv[0].uv[1] +
                                ((float)(char_info->h) / scale_h)
                            );
                        }

                        for(int j = 0; j < 6; ++j) {
                            s3d_txt_vertex *v = &tlv[j];

                            memcpy(v->rgba, rgb, 3 * 4);

                            v->rgba[3] = 1;
                        }

                        pen_x += char_info->xadv;

                        ++i;
                    }

                    txt->num_xyz = i * 6;
                }
            }
        }
    }

    glBindTexture(GL_TEXTURE_2D, fnt->tex_id);
}
