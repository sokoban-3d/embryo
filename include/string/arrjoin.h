#ifndef S3D_STRING_ARRJOIN_H
#define S3D_STRING_ARRJOIN_H

#include "array/len.h"
#include "string/arrcat.h"
#include "string/arrcpy.h"

#define s3d_strarrjoin(dst, ...) ({                 \
    const char *strs_[] = __VA_ARGS__;              \
                                                    \
    s3d_strarrcpy(dst, strs_[0]);                   \
                                                    \
    for(int i = 1; i < s3d_array_len(strs_); ++i) { \
        s3d_strarrcat(dst, strs_[i]);               \
    }                                               \
                                                    \
    dst;                                            \
})

#endif
