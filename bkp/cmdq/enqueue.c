#include <strings.h>

#include <stdlib.h>

#include "enqueue.h"

#include "head.h"
#include "tail.h"

void s3d_cmdq_enqueue(s3d_cmdq_fn fn, int st_len) {
    s3d_cmdq_node *n;

    {
        n = malloc(sizeof(s3d_cmdq_node) + st_len);

        n->fn = fn;

        n->next = 0;

        bzero(&n[1], st_len);
    }

    if(!s3d_cmdq_head) {
        s3d_cmdq_head = n;
    }

    if(s3d_cmdq_tail) {
        s3d_cmdq_tail->next = n;
    }

    s3d_cmdq_tail = n;
}
