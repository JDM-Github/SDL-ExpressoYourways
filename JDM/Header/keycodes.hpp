#pragma once
#ifndef JDM_KEYCODES
#define JDM_KEYCODES
#include "defines.hpp"

JNAMESPACE JDM {
    JNAMESPACE KeyCode {
        JBOOL A = JFALSE;
        JBOOL B = JFALSE;
        JBOOL C = JFALSE;
        JBOOL D = JFALSE;
        JBOOL E = JFALSE;
        JBOOL F = JFALSE;
        JBOOL G = JFALSE;
        JBOOL H = JFALSE;
        JBOOL I = JFALSE;
        JBOOL J = JFALSE;
        JBOOL K = JFALSE;
        JBOOL L = JFALSE;
        JBOOL M = JFALSE;
        JBOOL N = JFALSE;
        JBOOL O = JFALSE;
        JBOOL P = JFALSE;
        JBOOL Q = JFALSE;
        JBOOL R = JFALSE;
        JBOOL S = JFALSE;
        JBOOL T = JFALSE;
        JBOOL U = JFALSE;
        JBOOL V = JFALSE;
        JBOOL W = JFALSE;
        JBOOL X = JFALSE;
        JBOOL Y = JFALSE;
        JBOOL Z = JFALSE;

        JBOOL LEFT_SHIFT = JFALSE;
        JBOOL RIGHT_SHIFT = JFALSE;
        JBOOL LEFT_CONTROL = JFALSE;
        JBOOL RIGHT_CONTROL = JFALSE;
        JBOOL CAPSLOCK = JFALSE;
        JBOOL ENTER = JFALSE;
        JBOOL TAB = JFALSE;
        JBOOL BACKSPACE = JFALSE;
        JBOOL SPACE = JFALSE;
        JBOOL KPLUS = JFALSE;
        JBOOL KMINUS = JFALSE;

        JBOOL N0 = JFALSE;
        JBOOL N1 = JFALSE;
        JBOOL N2 = JFALSE;
        JBOOL N3 = JFALSE;
        JBOOL N4 = JFALSE;
        JBOOL N5 = JFALSE;
        JBOOL N6 = JFALSE;
        JBOOL N7 = JFALSE;
        JBOOL N8 = JFALSE;
        JBOOL N9 = JFALSE;

        JBOOL UP = JFALSE;
        JBOOL DOWN = JFALSE;
        JBOOL LEFT = JFALSE;
        JBOOL RIGHT = JFALSE;
        JBOOL PERIOD = JFALSE;
        JBOOL COMMA = JFALSE;
        JBOOL QUESTION = JFALSE;
        JBOOL QOUTE = JFALSE;

        JSTR KeyCodeToString(JBOOL *Key) {
            JIF (&JDM::KeyCode::A == Key) JRETURN "A";
            JIF (&JDM::KeyCode::B == Key) JRETURN "B";
            JIF (&JDM::KeyCode::C == Key) JRETURN "C";
            JIF (&JDM::KeyCode::D == Key) JRETURN "D";
            JIF (&JDM::KeyCode::E == Key) JRETURN "E";
            JIF (&JDM::KeyCode::F == Key) JRETURN "F";
            JIF (&JDM::KeyCode::G == Key) JRETURN "G";
            JIF (&JDM::KeyCode::H == Key) JRETURN "H";
            JIF (&JDM::KeyCode::I == Key) JRETURN "I";
            JIF (&JDM::KeyCode::J == Key) JRETURN "J";
            JIF (&JDM::KeyCode::K == Key) JRETURN "K";
            JIF (&JDM::KeyCode::L == Key) JRETURN "L";
            JIF (&JDM::KeyCode::M == Key) JRETURN "M";
            JIF (&JDM::KeyCode::N == Key) JRETURN "N";
            JIF (&JDM::KeyCode::O == Key) JRETURN "O";
            JIF (&JDM::KeyCode::P == Key) JRETURN "P";
            JIF (&JDM::KeyCode::Q == Key) JRETURN "Q";
            JIF (&JDM::KeyCode::R == Key) JRETURN "R";
            JIF (&JDM::KeyCode::S == Key) JRETURN "S";
            JIF (&JDM::KeyCode::T == Key) JRETURN "T";
            JIF (&JDM::KeyCode::U == Key) JRETURN "U";
            JIF (&JDM::KeyCode::V == Key) JRETURN "V";
            JIF (&JDM::KeyCode::W == Key) JRETURN "W";
            JIF (&JDM::KeyCode::X == Key) JRETURN "X";
            JIF (&JDM::KeyCode::Y == Key) JRETURN "Y";
            JIF (&JDM::KeyCode::Z == Key) JRETURN "Z";
            JIF (&JDM::KeyCode::LEFT_SHIFT == Key) JRETURN "LSHIFT";
            JIF (&JDM::KeyCode::RIGHT_SHIFT == Key) JRETURN "RSHIFT";
            JIF (&JDM::KeyCode::LEFT_CONTROL == Key) JRETURN "LCTRL"; 
            JIF (&JDM::KeyCode::RIGHT_CONTROL == Key) JRETURN "RCTRL"; 
            JIF (&JDM::KeyCode::CAPSLOCK == Key) JRETURN "CAPSLOCK"; 
            JIF (&JDM::KeyCode::ENTER == Key) JRETURN "ENTER"; 
            JIF (&JDM::KeyCode::TAB == Key) JRETURN "TAB"; 
            JIF (&JDM::KeyCode::BACKSPACE == Key) JRETURN "BACKSPACE";
            JIF (&JDM::KeyCode::SPACE == Key) JRETURN "SPACE"; 
            JIF (&JDM::KeyCode::KPLUS == Key) JRETURN "PLUS"; 
            JIF (&JDM::KeyCode::KMINUS == Key) JRETURN "MINUS";
            JIF (&JDM::KeyCode::N0 == Key) JRETURN "0";
            JIF (&JDM::KeyCode::N1 == Key) JRETURN "1";
            JIF (&JDM::KeyCode::N2 == Key) JRETURN "2";
            JIF (&JDM::KeyCode::N3 == Key) JRETURN "3";
            JIF (&JDM::KeyCode::N4 == Key) JRETURN "4";
            JIF (&JDM::KeyCode::N5 == Key) JRETURN "5";
            JIF (&JDM::KeyCode::N6 == Key) JRETURN "6";
            JIF (&JDM::KeyCode::N7 == Key) JRETURN "7";
            JIF (&JDM::KeyCode::N8 == Key) JRETURN "8";
            JIF (&JDM::KeyCode::N9 == Key) JRETURN "9";
            JIF (&JDM::KeyCode::UP == Key) JRETURN "UP";
            JIF (&JDM::KeyCode::DOWN == Key) JRETURN "DOWN";
            JIF (&JDM::KeyCode::LEFT == Key) JRETURN "LEFT";
            JIF (&JDM::KeyCode::RIGHT == Key) JRETURN "RIGHT";
            JIF (&JDM::KeyCode::PERIOD == Key) JRETURN ".";
            JIF (&JDM::KeyCode::COMMA == Key) JRETURN ",";
            JIF (&JDM::KeyCode::QUESTION == Key) JRETURN "?";
            JIF (&JDM::KeyCode::QOUTE == Key) JRETURN "'";
            JRETURN "";
        }
    };

    
};

#endif