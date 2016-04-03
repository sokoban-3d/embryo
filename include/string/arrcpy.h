#ifndef S3D_STRING_ARRCPY_H
#define S3D_STRING_ARRCPY_H

#include<bsd/string.h>

#define s3d_strarrcpy(dst, src) strlcpy(dst, src, sizeof(dst))

#endif
