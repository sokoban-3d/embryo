#include "stg.h"

#include<assert.h>
#include<errno.h>
#include<linux/limits.h>
#include<stdlib.h>
#include<string.h>

#include "err.h"
#include "maths.h"
#include "math.hpp"
#include "model.h"
#include "str.h"
#include "sys.h"

#include "matrix/identity.h"

#define pos_from_tpos(p, i, j) \
    s3d_stg.board.origin[i] + ( \
        (p)->tpos[j] * s3d_stg.board.tsz \
    )

#define pos_update(p) \
    (p)->pos[0] = pos_from_tpos((p), 0, 0); \
    (p)->pos[1] = s3d_stg.board.origin[1]; \
    (p)->pos[2] = pos_from_tpos((p), 2, 1);

#define mat_update(p) \
    s3d_identity((p)->mat); \
    s3d_translate((p)->mat, (p)->pos); \
    s3d_euler_rot((p)->mat, (p)->rot); \
    s3d_scale((p)->mat, (p)->scale);

void s3d_stg_query_at(
    int x, int y, int *obj_type, void **obj, s3d_stg_slot **slot
) {
    if(obj_type) {
        *obj_type = s3d_stg_obj_type_none;
    }

    if(obj) {
        *obj = 0;
    }

    if(slot) {
        *slot = 0;
    }

    if(
        x < 0 || x >= s3d_stg.board.sz[0]
        || y < 0 || y >= s3d_stg.board.sz[1]
    ) {
        if(obj_type) {
            *obj_type = s3d_stg_obj_type_outer_wall;
        }

        return;
    }

    int found = 0;

    #define obj_matches_query(obj_) ({ \
        typeof(obj_) obj = obj_; \
        \
        (obj->tpos[0] == x && obj->tpos[1] == y); \
    })

    #define obj_found(type, ptr_) ({ \
        typeof(ptr_) ptr = ptr_; \
        \
        found = 1; \
        \
        if(obj_type) { \
            *obj_type = s3d_stg_obj_type_##type; \
        } \
        \
        if(obj) { \
            *obj = ptr; \
        } \
    })

    if(!found) {
        s3d_stg_player *p = &s3d_stg.player;

        if(obj_matches_query(p)) {
            obj_found(player, p);
        }
    }

    if(!found) {
        for(int i = 0; i < s3d_stg.num_walls; ++i) {
            s3d_stg_wall *w = &s3d_stg.walls[i];

            if(obj_matches_query(w)) {
                obj_found(wall, w);

                break;
            }
        }
    }

    if(!found) {
        for(int i = 0; i < s3d_stg.num_blocks; ++i) {
            s3d_stg_block *b = &s3d_stg.blocks[i];

            if(obj_matches_query(b)) {
                obj_found(block, b);

                break;
            }
        }
    }

    if(!found || slot) {
        for(int i = 0; i < s3d_stg.num_slots; ++i) {
            s3d_stg_slot *s = &s3d_stg.slots[i];

            if(obj_matches_query(s)) {
                if(!found) {
                    obj_found(slot, s);
                }

                if(slot) {
                    *slot = s;
                }

                break;
            }
        }
    }

    #undef obj_matches_query
    #undef obj_found
}

void s3d_stg_init() {
    {
        s3d_stg.num_slotted_blocks = 0;

        for(int i = 0; i < s3d_stg.num_blocks; ++i) {
            s3d_stg_block *b = &s3d_stg.blocks[i];

            s3d_stg_slot *s;

            s3d_stg_query_at(b->tpos[0], b->tpos[1], 0, 0, &s);

            if(s) {
                ++s3d_stg.num_slotted_blocks;
            }
        }
    }

    {
        s3d_vec3_assign(s3d_stg.scale, 1, 1, 1);

        s3d_vec3_assign(s3d_stg.player.scale, 1, 1, 1);

        for(int i = 0; i < s3d_stg.num_blocks; ++i) {
            s3d_stg_block *b = &s3d_stg.blocks[i];

            s3d_vec3_assign(b->scale, 1, 1, 1);
        }
    }

    for(int i = 0; i < s3d_stg.num_walls; ++i) {
        s3d_stg_wall *w = &s3d_stg.walls[i];

        s3d_vec3_assign(w->scale, 1, 1, 1);

        pos_update(w);
        mat_update(w);
    }

    for(int i = 0; i < s3d_stg.num_slots; ++i) {
        s3d_stg_slot *s = &s3d_stg.slots[i];

        s3d_vec3_assign(s->scale, 1, 1, 1);

        pos_update(s);
        mat_update(s);
    }

    s3d_stg_update();
}

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

void s3d_stg_load_models(const char *path) {
    static char path_buf[PATH_MAX];

    {
        s3d_strarrjoin(path_buf, { path, "/model/stg" });

        s3d_model *m = &s3d_stg.model;

        s3d_model_load(m, path_buf);
    }

    {
        s3d_strarrjoin(path_buf, { path, "/model/player" });

        s3d_model *m = &s3d_stg.player_model;

        s3d_model_load(m, path_buf);
    }

    {
        s3d_strarrjoin(path_buf, { path, "/model/wall" });

        s3d_model *m = &s3d_stg.wall_model;

        s3d_model_load(m, path_buf);
    }

    {
        s3d_strarrjoin(path_buf, { path, "/model/block" });

        s3d_model *m = &s3d_stg.block_model;

        s3d_model_load(m, path_buf);
    }

    {
        s3d_strarrjoin(path_buf, { path, "/model/slot" });

        s3d_model *m = &s3d_stg.slot_model;

        s3d_model_load(m, path_buf);
    }
}
 
void s3d_stg_update() {
    mat_update(&s3d_stg);

    {
        s3d_stg_player *p = &s3d_stg.player;

        p->rot[1] += s3d_radians(2);

        pos_update(p);
        mat_update(p);
    }

    for(int i = 0; i < s3d_stg.num_blocks; ++i) {
        s3d_stg_block *b = &s3d_stg.blocks[i];

        pos_update(b);
        mat_update(b);
    }
}

int s3d_stg_play(int x, int y) {
    if(
        (x && y) ||
        (!x && !y) ||
        (x < -1 || x > 1) ||
        (y < -1 || y > 1)
    ) {
        abort_because("Invalid move: (%d, %d).", x, y);
    }

    s3d_stg.pushed = 0;
    s3d_stg.slotted = 0;

    s3d_stg_player *p = &s3d_stg.player;

    int dx = p->tpos[0] + x;
    int dy = p->tpos[1] + y;

    {
        int d_obj_type;
        void *d_obj;

        s3d_stg_query_at(dx, dy, &d_obj_type, &d_obj, 0);

        switch(d_obj_type) {
            case s3d_stg_obj_type_outer_wall:
            case s3d_stg_obj_type_wall:
                return 0;

            case s3d_stg_obj_type_block:
                if(!s3d_stg_push_block(d_obj, x, y)) { return 0; }

                break;
        }
    }

    p->tpos[0] = dx;
    p->tpos[1] = dy;

    return 1;
}

int s3d_stg_push_block(s3d_stg_block *b, int x, int y) {
    assert(b);

    if(!x && !y) {
        abort_because("Invalid push: (%d, %d).", x, y);
    }

    int dx = b->tpos[0] + x;
    int dy = b->tpos[1] + y;

    {
        int d_obj_type;

        void *d_obj;
        s3d_stg_slot *d_slot;

        s3d_stg_query_at(dx, dy, &d_obj_type, &d_obj, &d_slot);

        if(
            d_obj_type == s3d_stg_obj_type_outer_wall
            || (d_obj && d_obj_type != s3d_stg_obj_type_slot)
        ) {
            return 0;
        }

        if(d_slot) {
            ++s3d_stg.num_slotted_blocks;

            s3d_stg.slotted = 1;
        }
    }

    {
        s3d_stg_slot *o_slot;

        s3d_stg_query_at(b->tpos[0], b->tpos[1], 0, 0, &o_slot);

        if(o_slot) {
            --s3d_stg.num_slotted_blocks;
        }
    }

    b->tpos[0] = dx;
    b->tpos[1] = dy;

    s3d_stg.pushed = 1;

    return 1;
}

#undef pos_from_tpos
#undef pos_update
#undef mat_update

