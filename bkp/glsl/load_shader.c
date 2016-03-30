#include <GL/GLee.h>
#include <GLFW/glfw3.h>
#include "load_shader.h"
#include "../fs/read_file.h"
#include "../err/abort_because.h"

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
