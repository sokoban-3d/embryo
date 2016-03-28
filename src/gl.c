#include "gl.h"

#include<GL/GLee.h>
#include<GLFW/glfw3.h>

#include "err.h"

GLFWwindow *s3d_gl_wnd = 0;

void glfw_on_error(int err, const char *desc) {
    abort_because("GLFW error: %s", desc);
}

void glfw_on_resize(GLFWwindow *wnd, int width, int height) {
    glViewport(0, 0, width, height);
} 

void s3d_gl_init(int width, int height, const char *wndCaption) {
    glfwSetErrorCallback(glfw_on_error);

    assert_bool(glfwInit());

    s3d_gl_wnd = assert_ptr(
        glfwCreateWindow(width, height, wndCaption, 0, 0)
    );

    glfwMakeContextCurrent(s3d_gl_wnd);
    glfwSwapInterval(1);

    glfwSetWindowSizeCallback(s3d_gl_wnd, glfw_on_resize);
}
