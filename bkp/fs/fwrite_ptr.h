#pragma once

#include <stdio.h>

#define s3d_fwrite_ptr(ptr, n, f) fwrite(ptr, sizeof(*(ptr)), n, f)
