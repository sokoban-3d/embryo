#include "find_char_info.h"
#include "../err/abort_because.h"

void s3d_fnt_find_char_info(
    s3d_fnt *fnt, s3d_fnt_char_info **char_info, uint32_t code
) {
    int num_chars;
    s3d_fnt_char_info *chars;

    {
        s3d_fnt_info *info = &fnt->info;

        num_chars = info->num_chars;
        chars = info->chars;
    }

    for(int i = 0; i < num_chars; ++i) {
        s3d_fnt_char_info *i_char_info = &chars[i];

        if(i_char_info->id == code) {
            *char_info = i_char_info;

            return;
        }
    }

    abort_because("Font doesn't contain character with code %d.", code);
}
