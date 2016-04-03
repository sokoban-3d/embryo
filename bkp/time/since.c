#include "since.h"

#include "now.h"

float s3d_since(float when) {
    return s3d_now() - when;
}
