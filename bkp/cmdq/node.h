#pragma once

#include "fn.h"

struct s3d_cmdq_node;

typedef struct s3d_cmdq_node s3d_cmdq_node;

struct s3d_cmdq_node {
    s3d_cmdq_fn fn;

    s3d_cmdq_node *next;
};
