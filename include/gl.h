#ifndef S3D_GL_H
#define S3D_GL_H
 
#include<GL/GLee.h>
#include<GLFW/glfw3.h>

extern struct GLFWwindow *s3d_gl_wnd;

void s3d_gl_init(const int width, const int height, const char *wndCaption);
unsigned s3d_gl_load_buf(int type, const char *path, int hint);
void s3d_gl_load_buf_fmt(const char *path);
void s3d_gl_load_dds(unsigned *tex_id, const char *path);
int s3d_gl_should_close();
void s3d_gl_swap();

#endif
