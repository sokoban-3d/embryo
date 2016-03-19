#include <string.h>

#include "startswith.h"

int s3d_strstartswith(const char *s, const char *prefix) {
    return (strncmp(s, prefix, strlen(prefix)) == 0);
}
