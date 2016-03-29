#ifndef S3D_STRING_H
#define S3D_STRING_H

#include<string.h>
#include<bsd/string.h>

#include "array.h"

#define s3d_strempty(s) ((s)[0] == 0)
#define s3d_strarrcpy(dst, src) strlcpy(dst, src, sizeof(dst))
#define s3d_strarrcat(dst, src) strlcat(dst, src, sizeof(dst))

#define s3d_strarrjoin(dst, ...) ({ \
    const char *strs_[] = __VA_ARGS__; \
    \
    s3d_strarrcpy(dst, strs_[0]); \
    \
    for(int i = 1; i < s3d_array_len(strs_); ++i) { \
        s3d_strarrcat(dst, strs_[i]); \
    } \
    \
    dst; \
})

#define s3d_streachline(lines, line, i, ...) { \
    int i = 0; \
    \
    char *strtokctx; \
    \
    for( \
        char *line = strtok_r(lines, "\n", &strtokctx); \
        line; \
        line = strtok_r(0, "\n", &strtokctx) \
    ) { \
        ++i; \
        \
        s3d_strrtrim(line, "\r"); \
        \
        { __VA_ARGS__ } \
    } \
}

int s3d_strcharin(char c, const char *chars);

int s3d_strstartswith(const char *s, const char *prefix);
int s3d_strendswith(const char *s, const char *suffix);

char *s3d_strskip(char ** const s, const char *chars);

int s3d_strconsume(char ** const s, const char *token);

char *s3d_strrtrim(char *s, const char *suffix);

#endif

