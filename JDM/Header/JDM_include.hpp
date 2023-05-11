#pragma once
#ifndef RJDM_INCLUDE
#define RJDM_INCLUDE

#include "defines.hpp"

JNAMESPACE JDM {
    SDL_Renderer *renderer;
    JDOUBLE TimeFrame = 0;
    JDOUBLE FramePerSeconds = 0;
    JDOUBLE ElapseTime = 0;
    JDOUBLE WinWidth = 500;
    JDOUBLE WinHeight = 500;

    JBOOL alreadyTouched = JFALSE;

    JNAMESPACE Mouse {
        JBOOL LeftMouseDown = JFALSE;
        JBOOL RightMouseDown = JFALSE;
        JINT MouseX = 0;
        JINT MouseY = 0;
        JINT GlobalMouseX = 0;
        JINT GlobalMouseY = 0;
    };
    JINT WindowX = 0;
    JINT WindowY = 0;

    JNAMESPACE Cache {
        JMAP<JCSTR, JPAIR<JINT, JINT>> textureSourceRect;
    };
};

#endif