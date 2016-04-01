#ifndef S3D_STRING_EACHLINE_H
#define S3D_STRING_EACHLINE_H

#define s3d_streachline(lines, line, i, ...) {          \
    int i = 0;                                          \
                                                        \
    char *strtokctx;                                    \
                                                        \
    for(                                                \
        char *line = strtok_r(lines, "\n", &strtokctx); \
        line;                                           \
        line = strtok_r(0, "\n", &strtokctx)            \
    ) {                                                 \
        ++i;                                            \
                                                        \
        s3d_strrtrim(line, "\r");                       \
                                                        \
        { __VA_ARGS__ }                                 \
    }                                                   \
}

#endif
