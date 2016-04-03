#include <GLFW/glfw3.h>
#include "should_close.h"
#include "wnd.h"

int s3d_gl_should_close() {
    return glfwWindowShouldClose(s3d_gl_wnd);
}
