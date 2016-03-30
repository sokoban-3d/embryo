#include<./string.h>

#include<assert.h>
#include<string.h>

int s3d_strcharin(char c, const char *chars) {
    while(*chars != 0) {
        if(*chars == c) {
            return 1;
        }

        ++chars;
    }

    return 0;
}

int s3d_strchrcount(const char *s, int c) {
    int i = 0;
    const char *ptr = s;

    do {
        if(*ptr == c) {
            ++i;
        }
    } while(*(++ptr) != 0);

    return i;
}

int s3d_strstartswith(const char *s, const char *prefix) {
    return (strncmp(s, prefix, strlen(prefix)) == 0);
}

int s3d_strendswith(const char *s, const char *suffix) {
    int s_len = strlen(s);
    int suff_len = strlen(suffix);

    if(suff_len > s_len) {
        return 0;
    }

    const char *tail = s + s_len - suff_len;

    return (strcmp(tail, suffix) == 0);
}

char *s3d_strskip(char ** const s, const char *chars) {
    while(**s != 0 && s3d_strcharin(**s, chars)) {
        ++*s;
    }

    return *s;
}

int s3d_strconsume(char ** const s, const char *token) {
    if(!s3d_strstartswith(*s, token)) {
        return 0;
    }

    *s += strlen(token);

    return 1;
}

char *s3d_strrtrim(char *s, const char *suffix) {
    int s_len = strlen(s);
    int suff_len = strlen(suffix);

    while(s3d_strendswith(s, suffix)) {
        assert(s_len >= 0);

        s[s_len - suff_len] = 0;

        s_len -= suff_len;
    }

    return s;
}
