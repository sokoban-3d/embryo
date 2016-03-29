#ifndef S3D_ARRAY_H
#define S3D_ARRAY_H

#include<stdlib.h>

#define s3d_callocptr(ptr, n) (ptr) = calloc(n, sizeof(*(ptr)))
#define s3d_array_len(arr) (sizeof(arr) / sizeof((arr)[0]))

#endif
