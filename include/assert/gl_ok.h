#ifndef S3D_ASSERT_GL_OK_H 
#define S3D_ASSERT_GL_OK_H 

#include<GL/GLee.h>

#include "error/abort_because.h"

#define assert_gl_ok() ({ \
    int err = glGetError(); \
    \
    if(err) { \
        abort_because("OpenGL error: %d.", err); \
    } \
})

#endif
