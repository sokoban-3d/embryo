#include "stage/query_at.h"

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
