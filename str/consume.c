#include <string.h>

#include "consume.h"

#include "startswith.h"

int s3d_strconsume(char ** const s, const char *token) {
    if(!s3d_strstartswith(*s, token)) {
        return 0;
    }

    *s += strlen(token);

    return 1;
}
