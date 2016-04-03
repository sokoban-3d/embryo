#pragma once

#ifndef offsetof
    #define offsetof(type,member) ((std::size_t) &(((type*)0)->member))
#endif
