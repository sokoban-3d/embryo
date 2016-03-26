#include <string.h>

#include <stdlib.h>
#include <stdio.h>

#include "mem/allocaptr.h"
#include "mem/array_len.h"

#include "stg/stg.h"
#include "stg/query_at.h"
#include "stg/obj_type.h"
#include "stg/load_spec.h"
#include "stg/recompute_slotted_blocks.h"
#include "stg/play.h"

#include "io/print.h"

void print_state() {
    printf("Pushed: %s.\n", s3d_stg.pushed? "yes" : "no");
    printf("Slotted: %s.\n", s3d_stg.slotted? "yes" : "no");

    printf(
        "Slotted blocks: %d of %d.\n\n",
        s3d_stg.num_slotted_blocks,
        s3d_stg.num_slots
    );

    int w = s3d_stg.board.sz[0];
    int h = s3d_stg.board.sz[1];

    for(int i = 0; i < w + 4; ++i) {
        s3d_print("W");
    }

    s3d_print("\n");

    for(int y = 0; y < h; ++y) {
        s3d_print("W ");

        for(int x = 0; x < w; ++x) {
            int obj_type;

            s3d_stg_query_at(x, y, &obj_type, 0, 0);

            switch(obj_type) {
                #define obj_case(type, s) \
                    case s3d_stg_obj_type_##type: \
                        s3d_print(s); \
                        break

                obj_case(player, "P");
                obj_case(wall, "W");
                obj_case(block, "B");
                obj_case(slot, "S");

                #undef obj_case

                default:
                    s3d_print("·");
                    break;
            }
        }

        s3d_print(" W\n");
    }

    for(int i = 0; i < w + 4; ++i) {
        s3d_print("W");
    }

    s3d_print("\n\n");
}

int main(int argc, char **argv) {
    s3d_stg_load_spec(
        (argc >= 2)? argv[1] : "data/stg/proto_1"
    );

    s3d_stg_recompute_slotted_blocks();

    while(1) {
        system("clear");

        print_state();

        if(s3d_stg.num_slotted_blocks == s3d_stg.num_slots) {
            puts("You win!"); break;
        }

        int c = fgetc(stdin);

        if(c == EOF) {
            break;
        }

        switch(c) {
            case 'w':
                s3d_stg_play(0, -1);
                break;

            case 'a':
                s3d_stg_play(-1, 0);
                break;

            case 's':
                s3d_stg_play(0, 1);
                break;

            case 'd':
                s3d_stg_play(1, 0);
                break;

            case 'q':
                goto end;
        }
    }

    end:
    return 0;
}
