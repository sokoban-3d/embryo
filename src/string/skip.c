#include "string/skip.h"

#include "string/charin.h"

char *s3d_strskip(char ** const s, const char *chars) {
    while(**s != 0 && s3d_strcharin(**s, chars)) {
        ++*s;
    }

    return *s;
}
