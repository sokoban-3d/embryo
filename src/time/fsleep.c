#include "time/fsleep.h"

#include<unistd.h>

void s3d_fsleep(float seconds) {
    usleep(seconds * 1e6);
}

