#include "file.h"

#include<stdio.h>

#include "err.h"

char *s3d_read_file(const char *path, int text, int *size) {
    FILE *f = assert_ptr(fopen(path, "rb"));

    fseek(f, 0, SEEK_END);

    int _size = ftell(f);

    if(text) {
        ++_size;
    }

    if(size) {
        *size = _size;
    }

    fseek(f, 0, SEEK_SET);

    char *buf = assert_ptr(malloc(_size));
    fread(buf, 1, _size, f);

    if(text) {
        buf[_size - 1] = 0;
    }

    fclose(f);

    return buf;
}
