#pragma once

#include <stdlib.h>

#define s3d_mallocptr(ptr, n) (ptr) = malloc(sizeof(*(ptr)) * (n))
