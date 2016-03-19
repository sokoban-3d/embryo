#include "clamp.h"

float s3d_clamp(float val, float min, float max) {
    return (
        val < min? min :
        val > max? max :
        val
    );
}
