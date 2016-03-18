#pragma once

#include <bsd/string.h>

#define s3d_strarrcpy(dst, src) strlcpy(dst, src, sizeof(dst))
