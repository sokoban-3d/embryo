#pragma once

#include <alloca.h>

#define s3d_allocaptr(ptr, n) (ptr) = alloca(sizeof(*(ptr)) * (n))
