#ifndef S3D_ALLOC_CALLOCPTR_H
#define S3D_ALLOC_CALLOCPTR_H

#define s3d_callocptr(ptr, n) (ptr) = calloc(n, sizeof(*(ptr)))

#endif
