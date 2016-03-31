#include "gl/should_close.h" 

#include<GL/GLee.h>
#include<GLFW/glfw3.h>

#include "gl/window.h"

int s3d_gl_should_close() {
    return glfwWindowShouldClose(s3d_gl_window);
}

