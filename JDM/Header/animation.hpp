#pragma once
#ifndef JDM_ANIMATION
#define JDM_ANIMATION

#include "defines.hpp"

JNAMESPACE JDM {

    JCLASS AnimationBase {
    JPUBLIC:
        JVIRTUAL ~AnimationBase() {}
        JVIRTUAL JCVOID SetDuration(JCDOUBLE duration)  = 0;
        JVIRTUAL JCVOID SetAutoRemove(JCBOOL autoRemove)  = 0;
        JVIRTUAL JCBOOL GetAutoRemove() = 0;
        JVIRTUAL JCVOID start() = 0;
        JVIRTUAL JCBOOL update() = 0;
        JVIRTUAL JCVOID stop() = 0;
        JVIRTUAL JCVOID cont() = 0;
        JVIRTUAL JCVOID cancel() = 0;
    };

    JTEMPLATE<JCLASS T>
    JCLASS Animation : JPUBLIC AnimationBase {
    JPROTECTED:
        JBOOL started = JFALSE;
        JBOOL stopped = JFALSE;
        JBOOL autoremove = JFALSE;
        JDOUBLE Duration = 1;
        T Target = 0;
        T *targetAnimating;
        JDOUBLE distance = 0;
        JDOUBLE adder = 0;
        funcCallback function = []() {};

        JINLINE JCVOID setVariables() {
            JTHIS->distance = JTHIS->Target - *JTHIS->targetAnimating;
            JTHIS->adder = distance * (1.0 / (JTHIS->Duration * 80));
        }

    JPUBLIC:
        Animation(T *ref, JCONST T target, JCDOUBLE duration = 1, JCBOOL autoRemove = JTRUE, funcCallback func = [](){}) 
            : Duration(duration), targetAnimating(ref), Target(target), autoremove(autoRemove), function(func) { JTHIS->setVariables(); }
        JINLINE JCVOID SetReference(T *ref) {
            JIF (!JTHIS->started) {
                JTHIS->targetAnimating = ref;
                JTHIS->setVariables();
            }
        }
        JINLINE JCVOID SetDuration(JCDOUBLE duration) {
            JIF (!JTHIS->started) {
                JTHIS->Duration = duration;
                JTHIS->setVariables();
            }
        }

        JINLINE JCVOID SetAutoRemove(JCBOOL autoRemove) { JIF (!JTHIS->started) JTHIS->autoremove = autoRemove; }
        JINLINE JCBOOL GetAutoRemove() { JRETURN JTHIS->autoremove; }
        
        JINLINE JCVOID SetTarget(T target) {
            JIF (!JTHIS->started) {
                JTHIS->Target = target;
                JTHIS->setVariables();
            }
        }
        JINLINE JCVOID start() {
            JIF(!JTHIS->started) {
                JTHIS->setVariables();
                JTHIS->started = JTRUE;
            }
        }
        JINLINE JCBOOL update() {
            JIF (JTHIS->started && !JTHIS->stopped) {
                JIF ((JTHIS->Target <= *JTHIS->targetAnimating && JTHIS->adder >= 0)
                  || (JTHIS->Target >= *JTHIS->targetAnimating && JTHIS->adder <= 0)) {
                    *JTHIS->targetAnimating = JTHIS->Target;
                    JTHIS->started = JFALSE;
                    JRETURN JTRUE;
                } JELSE {
                    *JTHIS->targetAnimating = JSTATICC<T>(*JTHIS->targetAnimating + JTHIS->adder);
                    JTHIS->function();
                }
            }
            JRETURN JFALSE;
        }
        JINLINE JCVOID stop() { JIF(JTHIS->started) JTHIS->stopped = JTRUE; }
        JINLINE JCVOID cont() { JIF(JTHIS->started) JTHIS->stopped = JFALSE; }
        JINLINE JCVOID cancel() { JTHIS->started = JFALSE; }
    };
};

#endif
