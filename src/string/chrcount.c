#include "string/chrcount.h"

int s3d_strchrcount(const char *s, int c) {
    int i = 0;
    const char *ptr = s;

    do {
        if(*ptr == c) {
            ++i;
        }
    } while(*(++ptr) != 0);

    return i;
}
