#include "string/charin.h"

int s3d_strcharin(char c, const char *chars) {
    while(*chars != 0) {
        if(*chars == c) {
            return 1;
        }

        ++chars;
    }

    return 0;
}
