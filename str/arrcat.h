#pragma once

#include <bsd/string.h>

#define s3d_strarrcat(dst, src) strlcat(dst, src, sizeof(dst))
