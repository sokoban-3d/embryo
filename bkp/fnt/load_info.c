#include <errno.h>

#include <string.h>
#include <stdlib.h>

#include <linux/limits.h>

#include "load_info.h"

#include "../str/arrjoin.h"
#include "../str/eachline.h"
#include "../str/consume.h"
#include "../str/empty.h"
#include "../str/skip.h"

#include "../fs/read_file.h"

#include "../err/abort_because.h"

#include "../mem/mallocptr.h"

void s3d_fnt_load_info(s3d_fnt_info *info, const char *path) {
    {
        info->line_height = -1;
        info->chars = 0;
    }

    int ichar = -1;

    static char path_buf[PATH_MAX];

    s3d_strarrjoin(path_buf, { path, "/info" });

    char *lines = s3d_read_file(path_buf, 1, 0);

    s3d_streachline(lines, line, line_no, {
        char *lptr = line;

        #define abort_parse(message, more...) \
            abort_because( \
                "%s:%d: " message ": %s", \
                path_buf, line_no, ##more, line \
            )

        #define parse_tag(name) s3d_strconsume(&lptr, name " ")

        #define parse_attr_tok(name) { \
            s3d_strskip(&lptr, " "); \
            \
            if(!s3d_strconsume(&lptr, name "=")) { \
                abort_parse("Expected '" name "=' token"); \
            } \
        }

        #define parse_tok(tok) \
            s3d_strskip(&lptr, " "); \
            \
            if(!s3d_strconsume(&lptr, tok)) { \
                abort_parse("Expected '" tok "' token"); \
            }

        #define parse_long(dst, name) { \
            errno = 0; \
            \
            dst = strtol(lptr, &lptr, 10); \
            \
            if(errno) { \
                abort_parse("Bad " name " value"); \
            } \
        }

        #define parse_eol() \
            if(!s3d_strempty(lptr)) { \
                abort_parse("Trailing characters"); \
            }

        if(parse_tag("common")) {
            parse_attr_tok("lineHeight");
            parse_long(info->line_height, "line height");

            parse_attr_tok("base");
            parse_long(info->base, "base");

            parse_attr_tok("scaleW");
            parse_long(info->scale_w, "scale width");

            parse_attr_tok("scaleH");
            parse_long(info->scale_h, "scale height");

            parse_tok("pages=1");
            parse_tok("packed=0");
            parse_tok("alphaChnl=1");
            parse_tok("redChnl=4");
            parse_tok("greenChnl=4");
            parse_tok("blueChnl=4");

            parse_eol();
        }
        else
        if(parse_tag("chars")) {
            parse_attr_tok("count");
            parse_long(info->num_chars, "char count");

            parse_eol();

            if(info->num_chars > 0) {
                s3d_mallocptr(info->chars, info->num_chars);
            }

            ichar = 0;
        }
        else
        if(parse_tag("char")) {
            if(ichar == -1) {
                abort_parse("char tag before chars tag");
            }

            if(ichar >= info->num_chars) {
                abort_parse(
                    "Too many char tags (more than %d)", info->num_chars
                );
            }

            s3d_fnt_char_info *cptr = &info->chars[ichar];

            parse_attr_tok("id");
            parse_long(cptr->id, "ID");

            parse_attr_tok("x");
            parse_long(cptr->x, "X");

            parse_attr_tok("y");
            parse_long(cptr->y, "Y");

            parse_attr_tok("width");
            parse_long(cptr->w, "width");

            parse_attr_tok("height");
            parse_long(cptr->h, "height");

            parse_attr_tok("xoffset");
            parse_long(cptr->xoff, "X offset");

            parse_attr_tok("yoffset");
            parse_long(cptr->yoff, "Y offset");

            parse_attr_tok("xadvance");
            parse_long(cptr->xadv, "X advance");

            parse_tok("page=0");
            parse_tok("chnl=15");

            parse_eol();

            ++ichar;
        }
        else {
            abort_parse("Invalid tag");
        }
    })

    #undef parse_tag
    #undef parse_attr_tok
    #undef parse_tok
    #undef parse_long
    #undef parse_eol

    #undef abort_parse

    if(info->line_height == -1) {
        abort_because("%s: Missing common tag.", path_buf);
    }

    free(lines);
}
