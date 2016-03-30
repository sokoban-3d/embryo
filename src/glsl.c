#include "glsl.h"

#include<GL/GLee.h>
#include<GLFW/glfw3.h>

#include "err.h"
#include "sys.h"

unsigned s3d_glsl_load_program(const char *vs_path, const char *fs_path) {
    unsigned vs_id = s3d_glsl_load_shader(GL_VERTEX_SHADER, vs_path);
    unsigned fs_id = s3d_glsl_load_shader(GL_FRAGMENT_SHADER, fs_path);

    unsigned p_id = glCreateProgram();

    glAttachShader(p_id, vs_id);
    glAttachShader(p_id, fs_id);

    glLinkProgram(p_id);

    {
        int log_len;

        glGetProgramiv(p_id, GL_INFO_LOG_LENGTH, &log_len);

        if(log_len > 1) {
            char *log = alloca(log_len + 1);

            glGetProgramInfoLog(fs_id, log_len, 0, log);

            abort_because("In %s + %s linked program: %s", vs_path, fs_path, log);
        }
    }

    glDetachShader(p_id, vs_id);
    glDetachShader(p_id, fs_id);

    glDeleteShader(vs_id);
    glDeleteShader(fs_id);

    return p_id;
}

unsigned s3d_glsl_load_shader(int type, const char *path) {
    unsigned shader_id = glCreateShader(type);

    {
        char *shader_text = s3d_read_file(path, 1, 0);

        glShaderSource(shader_id, 1, (const char **)(&shader_text), 0);
        free(shader_text);
    }

    glCompileShader(shader_id);

    {
        int log_len;

        glGetShaderiv(shader_id, GL_INFO_LOG_LENGTH, &log_len);

        if(log_len > 1) {
            char *log = alloca(log_len + 1);

            glGetShaderInfoLog(shader_id, log_len, 0, log);

            abort_because("In %s: %s", path, log);
        }
    }

    return shader_id;
}

