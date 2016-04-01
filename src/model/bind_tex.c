#include "model/bind_tex.h"
 
#include<GL/GLee.h>

#include "model/type.h"

void s3d_model_bind_tex(s3d_model *m) {
    glBindTexture(GL_TEXTURE_2D, m->tex_id);
}
