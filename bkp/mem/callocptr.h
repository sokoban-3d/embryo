#pragma once

#include <stdlib.h>

#define s3d_callocptr(ptr, n) (ptr) = calloc(n, sizeof(*(ptr)))
