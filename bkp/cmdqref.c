#include <stdio.h>

#include "cmdq/enqueue.h"
#include "cmdq/update.h"

typedef struct {
    int c;
} st_1, st_2;

int fn_1(void *st_) {
    st_1 *st = st_;

    if(++st->c == 5) {
        printf("fn_1: %d\n", st->c);

        return 0;
    }

    return 1;
}

int fn_2(void *st_) {
    st_2 *st = st_;

    if(++st->c == 20) {
        printf("fn_2: %d\n", st->c);

        return 0;
    }

    return 1;
}

int main() {
    s3d_cmdq_enqueue(fn_1, sizeof(st_1));

    s3d_cmdq_enqueue(fn_2, sizeof(st_2));

    while(s3d_cmdq_update()) {
    }
    
    return 0;
}
