#include <stdlib.h>

#include "update.h"

#include "head.h"

int s3d_cmdq_update() {
    if(!s3d_cmdq_head) {
        return 0;
    }

    s3d_cmdq_node *head = s3d_cmdq_head;

    if(!head->fn(&head[1])) {
        s3d_cmdq_head = head->next;

        free(head);

        return !!s3d_cmdq_head;
    }

    return 1;
}
