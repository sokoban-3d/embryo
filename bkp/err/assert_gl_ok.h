#pragma once

#include <GLFW/glfw3.h>

#include "abort_because.h"

#define assert_gl_ok() ({ \
    int err = glGetError(); \
    \
    if(err) { \
        abort_because("OpenGL error: %d.", err); \
    } \
})
