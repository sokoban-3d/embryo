#include "gl/swap.h"

#include<GL/GLee.h>
#include<GLFW/glfw3.h>

#include "gl/window.h"

void s3d_gl_swap() {
    glfwSwapBuffers(s3d_gl_window);
}

