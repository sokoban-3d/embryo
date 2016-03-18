#include <assert.h>
#include <string.h>

#include "rtrim.h"

#include "endswith.h"

char *s3d_strrtrim(char *s, const char *suffix) {
    int s_len = strlen(s);
    int suff_len = strlen(suffix);

    while(s3d_strendswith(s, suffix)) {
        assert(s_len >= 0);

        s[s_len - suff_len] = 0;

        s_len -= suff_len;
    }

    return s;
}
