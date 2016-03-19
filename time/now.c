#include <errno.h>

#include <time.h>

#include "now.h"

#include "../err/assert_int.h"

float s3d_now() {
    errno = 0;

    struct timespec t;
    clock_gettime(CLOCK_MONOTONIC, &t);

    assert_int(errno, !val);

    return t.tv_sec + ((float)(t.tv_nsec) / 1e9);
}
