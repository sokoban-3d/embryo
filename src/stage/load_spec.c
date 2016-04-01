#include "stage/load_spec.h"

void s3d_stg_load_spec(const char *path) {
    static char path_buf[PATH_MAX];

    s3d_strarrjoin(path_buf, { path, "/spec" });

    char *lines = s3d_read_file(path_buf, 1, 0);

    int iwall = -1;
    int iblock = -1;
    int islot = -1;

    s3d_streachline(lines, line, line_no, {
        if(s3d_strempty(line) || line[0] == '#') {
            continue;
        }

        char *lptr = line;

        #define bad_spec(msg, more...) \
            abort_because( \
                "%s:%d: " msg ": %s", \
                path_buf, line_no, ##more, line \
            )

        #define parse_tag_tok(name) s3d_strconsume(&lptr, name " ")

        #define parse_attr_tok(name) \
            s3d_strskip(&lptr, " "); \
            \
            if(!s3d_strconsume(&lptr, name "=")) { \
                bad_spec("Expected '" name "=' token"); \
            }

        #define parse_long_tok(dst, name) \
            errno = 0; \
            \
            dst = strtol(lptr, &lptr, 10); \
            \
            if(errno) { \
                bad_spec("Bad " name " value"); \
            }

        #define parse_float_tok(dst, name) \
            errno = 0; \
            \
            dst = strtof(lptr, &lptr); \
            \
            if(errno) { \
                bad_spec("Bad " name " value"); \
            }

        if(parse_tag_tok("board")) {
            parse_attr_tok("w");
            parse_long_tok(s3d_stg.board.sz[0], "width");

            parse_attr_tok("h");
            parse_long_tok(s3d_stg.board.sz[1], "height");

            parse_attr_tok("ox");
            parse_float_tok(s3d_stg.board.origin[0], "origin X");

            parse_attr_tok("oy");
            parse_float_tok(s3d_stg.board.origin[1], "origin Y");

            parse_attr_tok("oz");
            parse_float_tok(s3d_stg.board.origin[2], "origin Z");

            parse_attr_tok("sz");
            parse_float_tok(s3d_stg.board.tsz, "tile size");
        }
        else
        if(parse_tag_tok("player")) {
            s3d_stg_player *p = &s3d_stg.player;

            parse_attr_tok("x");
            parse_long_tok(p->tpos[0], "X");

            parse_attr_tok("y");
            parse_long_tok(p->tpos[1], "Y");
        }
        else
        if(parse_tag_tok("walls")) {
            parse_attr_tok("count");
            parse_long_tok(s3d_stg.num_walls, "count");

            if(s3d_stg.num_walls > 0) {
                s3d_callocptr(s3d_stg.walls, s3d_stg.num_walls);
            }

            iwall = 0;
        }
        else
        if(parse_tag_tok("wall")) {
            if(iwall == -1) {
                bad_spec("wall tag before walls tag");
            }

            if(iwall >= s3d_stg.num_walls) {
                bad_spec("Too many wall tags");
            }

            s3d_stg_wall *w = &s3d_stg.walls[iwall++];

            parse_attr_tok("x");
            parse_long_tok(w->tpos[0], "X");

            parse_attr_tok("y");
            parse_long_tok(w->tpos[1], "Y");
        }
        else
        if(parse_tag_tok("blocks")) {
            parse_attr_tok("count");
            parse_long_tok(s3d_stg.num_blocks, "count");

            if(s3d_stg.num_blocks > 0) {
                s3d_callocptr(s3d_stg.blocks, s3d_stg.num_blocks);
            }

            iblock = 0;
        }
        else
        if(parse_tag_tok("block")) {
            if(iblock == -1) {
                bad_spec("block tag before blocks tag");
            }

            if(iblock >= s3d_stg.num_blocks) {
                bad_spec("Too many block tags");
            }

            s3d_stg_block *b = &s3d_stg.blocks[iblock++];

            parse_attr_tok("x");
            parse_long_tok(b->tpos[0], "X");

            parse_attr_tok("y");
            parse_long_tok(b->tpos[1], "Y");
        }
        else
        if(parse_tag_tok("slots")) {
            parse_attr_tok("count");
            parse_long_tok(s3d_stg.num_slots, "count");

            if(s3d_stg.num_slots > 0) {
                s3d_callocptr(s3d_stg.slots, s3d_stg.num_slots);
            }

            islot = 0;
        }
        else
        if(parse_tag_tok("slot")) {
            if(islot == -1) {
                bad_spec("slot tag before slots tag");
            }

            if(islot >= s3d_stg.num_blocks) {
                bad_spec("Too many slot tags");
            }

            s3d_stg_slot *s = &s3d_stg.slots[islot++];

            parse_attr_tok("x");
            parse_long_tok(s->tpos[0], "X");

            parse_attr_tok("y");
            parse_long_tok(s->tpos[1], "Y");
        }
        else {
            bad_spec("Invalid tag");
        }

        s3d_strskip(&lptr, " ");

        if(!s3d_strempty(lptr)) {
            bad_spec("Trailing characters");
        }
    })

    #undef parse_tag_tok
    #undef parse_attr_tok
    #undef parse_long_tok

    #undef bad_spec

    #define bad_spec(msg, more...) \
        abort_because("%s: " msg, path_buf, ##more);

    {
        if(iwall != s3d_stg.num_walls) {
            bad_spec("Too few wall tags");
        }

        if(iblock != s3d_stg.num_blocks) {
            bad_spec("Too few block tags");
        }

        if(islot != s3d_stg.num_slots) {
            bad_spec("Too few slot tags");
        }
    }

    #undef bad_spec

    free(lines);
}
