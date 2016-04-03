#include "string/endswith.h"

#include<string.h>

int s3d_strendswith(const char *s, const char *suffix) {
    int s_len = strlen(s);
    int suff_len = strlen(suffix);

    if(suff_len > s_len) {
        return 0;
    }

    const char *tail = s + s_len - suff_len;

    return (strcmp(tail, suffix) == 0);
}
