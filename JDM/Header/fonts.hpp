#pragma once
#ifndef JDM_FONTS
#define JDM_FONTS
#include "defines.hpp"

JNAMESPACE JDM { JNAMESPACE Font {
    JENUM Valign { TOP, VCENTER, BOTTOM };
    JENUM Halign { LEFT, HCENTER, RIGHT };
    JSTRUCT Font {
        JSTR Normal, Italic, Bold, ItalicBold;
        Font() {}
    };

    JSTRUCT Consolas : JPUBLIC Font{
        Consolas() {
            JTHIS->Normal = "Assets/Font/consolas/consolas_regular.ttf";
            JTHIS->Italic = "Assets/Font/consolas/consolas_italic.ttf";
            JTHIS->Bold = "Assets/Font/consolas/consolas_bold.ttf";
            JTHIS->ItalicBold = "Assets/Font/consolas/consolas_italic_bold.ttf";
        }
    };
}};

#endif
