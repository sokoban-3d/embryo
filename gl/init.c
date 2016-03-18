#include <GLFW/glfw3.h>
#include "../err/abort_because.h"
#include "../err/assert_bool.h"
#include "../err/assert_ptr.h"
#include "init.h"
#include "wnd.h"

void glfw_on_error(int err, const char *desc) {
    abort_because("GLFW error: %s", desc);
}

void glfw_on_resize(GLFWwindow *wnd, int w, int h) {
    glViewport(0, 0, w, h);
}

void s3d_gl_init(int w, int h, const char *wndCaption) {
    glfwSetErrorCallback(glfw_on_error);

    assert_bool(glfwInit());

    s3d_gl_wnd = assert_ptr(glfwCreateWindow(w, h, wndCaption, 0, 0));

    glfwMakeContextCurrent(s3d_gl_wnd);
    glfwSwapInterval(1);

    glfwSetWindowSizeCallback(s3d_gl_wnd, glfw_on_resize);
}
