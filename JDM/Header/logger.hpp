#pragma once
#ifndef JDM_LOGGER
#define JDM_LOGGER
#include "defines.hpp"

JNAMESPACE JDM {
    JINLINE JVOID Logger() { std::cout << std::endl; }
    JTEMPLATE <JCLASS X, JCLASS... Args>
    JINLINE JVOID Logger(JCONST X &x, JCONST Args... args) {
        std::cout << x;
        Logger(args...);
    }
};

#endif