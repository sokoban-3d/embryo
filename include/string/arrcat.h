#ifndef S3D_STRING_ARRCAT_H
#define S3D_STRING_ARRCAT_H

#include<bsd/string.h>

#define s3d_strarrcat(dst, src) strlcat(dst, src, sizeof(dst))

#endif
