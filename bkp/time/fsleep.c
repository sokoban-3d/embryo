#include <unistd.h>
#include "fsleep.h"

void s3d_fsleep(float seconds) {
    usleep(seconds * 1e6);
}
