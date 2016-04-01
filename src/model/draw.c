#include "model/draw.h"

void s3d_model_draw(s3d_model *m, int row) {
    s3d_model_idxtab_row *idxrow = &m->idxtab.rows[row];

    glDrawElements(
        GL_TRIANGLES,
        idxrow->num_idx,
        GL_UNSIGNED_INT,
        idxrow->idx_ptr
    );
}

