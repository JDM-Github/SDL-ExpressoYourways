#pragma once
#ifndef JDM_WINDOW
#define JDM_WINDOW

#include "JDM_include.hpp"
#include "animation.hpp"
#include "components.hpp"
#include "keycodes.hpp"
#include "logger.hpp"

JNAMESPACE JDM {
    JLIST<JSP<JDM::AnimationBase>> allAnimations;
    JLIST<JSP<JDM::Comp::Components>> allComponents;
    JDM::Comp::FocusedTextComponent *focusedTextComponent = JNULLPTR;

    JCLASS Window {
    JPRIVATE:
        ColorRGB winColor;
        JBOOL started = JFALSE;
        JBOOL isKeyDown = JFALSE;
        JBOOL isCursorChangeable = JFALSE;
        JSTR Title;

        SDL_bool running;
        SDL_Window *window;
        SDL_Event event;

        SDL_Surface *iconSurface;
        SDL_Texture *cursorTexture;
        SDL_Rect cursorRect;

        JUINT32 firstTime = 0;
        JUINT32 prevTime = 0;
        JUINT32 secondTime = 0;

    JPUBLIC:
        Window(JCSTR &title = "JDM - Window",
               JCINT x = SDL_WINDOWPOS_UNDEFINED,
               JCINT y = SDL_WINDOWPOS_UNDEFINED,
               JCINT width = 500,
               JCINT height = 500,
               JCONST ColorRGB& color = {0, 0, 0})
                : Title(title), winColor(color) {

            JDM::Logger(" > Windows Opening: JDM - SDL2 (", title , ")");
            JDM::Logger(" > [ INFO ]: Trying to init EVERYTHING...");

            JINT imgFlags = IMG_INIT_PNG | IMG_INIT_JPG;
            JIF (SDL_Init(SDL_INIT_EVERYTHING) != 0 || TTF_Init() != 0
                || !(IMG_Init(imgFlags) & imgFlags)) JEXIT(1);

            JDM::Logger(" > [ INFO ]: SDL Init Successfully");
            JTHIS->window = SDL_CreateWindow(title.c_str(), x, y, width, height, SDL_WINDOW_ALLOW_HIGHDPI);

            JDM::Logger(" > [ INFO ]: Creating window...");
            JIF (JTHIS->window == JNULLPTR) JEXIT(1);
            
            JDM::renderer = SDL_CreateRenderer(JTHIS->window, -1, SDL_RENDERER_ACCELERATED);
            JDM::Logger(" > [ INFO ]: Creating renderer...");
            JIF (JDM::renderer == JNULLPTR) JEXIT(1);

            SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "best");

            JDM::WinWidth = width;
            JDM::WinHeight = height;
            JTHIS->setIcon(DefaultImage);
            JDM::Logger(" > Windows Opened: JDM - SDL2 (", title , ")");
        }
        ~Window() {
            SDL_DestroyWindow(JTHIS->window);
            SDL_DestroyRenderer(JDM::renderer);
            SDL_FreeSurface(JTHIS->iconSurface);
            SDL_Quit();
            JDM::Logger("Windows Closed: JDM - SDL2 (", JTHIS->Title , ")");
        }
        JINLINE JCVOID run() {
            JDM::Logger("JDM - SDL2 (", JTHIS->Title , ") is running...");
            SRand(std::time(JNULL));
            JTHIS->running = SDL_TRUE;
            JTHIS->firstTime = SDL_GetTicks();

            JWHILE (JTHIS->running) {
                JTHIS->secondTime = SDL_GetTicks();
                if ((JTHIS->secondTime - JTHIS->firstTime) > (1000 / 80)) {
                    JUINT32 FrameTime = JTHIS->secondTime - JTHIS->prevTime;
                    JTHIS->prevTime = JTHIS->secondTime;
                    JDM::TimeFrame = FrameTime / 1000.0;
                    JDM::FramePerSeconds = 1000.0 / FrameTime;
                    JDM::ElapseTime += JDM::TimeFrame;

                    JTHIS->pollEvent();
                    JTHIS->animationUpdate();
                    JTHIS->winUpdate();
                    JTHIS->update();
                    JTHIS->winRender();
                    JTHIS->firstTime = SDL_GetTicks();
                }
            }
        }
        JVIRTUAL JVOID update() {};
        JVIRTUAL JVOID mouseDown() {}
        JVIRTUAL JVOID mouseUp() {}
        JVIRTUAL JVOID mouseMotion() {}
        JVIRTUAL JVOID keyDown(JCBOOL *Key) {}
        JVIRTUAL JVOID keyHold(JCBOOL *Key) {}
        JVIRTUAL JVOID keyUp(JCBOOL *Key) {}
        JVIRTUAL JVOID initAllObjects() {}

        JINLINE JCVOID setTitle(JCSTR &title) { SDL_SetWindowTitle(JTHIS->window, title.c_str()); }
        JINLINE JCVOID setIcon(JCSTR &path) {
            JIF (isFileExist(path)) {
                JTHIS->iconSurface = IMG_Load(path.c_str());
                SDL_SetWindowIcon(JTHIS->window, JTHIS->iconSurface);
            } JELSE {
                JTHIS->iconSurface = IMG_Load(CircleImage.c_str());
                SDL_SetWindowIcon(JTHIS->window, JTHIS->iconSurface);
            }
        }
        JINLINE JCVOID setCursor(JCSTR &path) {
            JTHIS->isCursorChangeable = JTRUE;
            JIF (isFileExist(path)) {
                JTHIS->cursorTexture = IMG_LoadTexture(JDM::renderer, path.c_str());
                SDL_SetTextureScaleMode(JTHIS->cursorTexture, SDL_ScaleModeLinear);
                SDL_SetTextureBlendMode(JTHIS->cursorTexture, SDL_BLENDMODE_BLEND);
                SDL_ShowCursor(SDL_DISABLE);
            } JELSE {
                JTHIS->isCursorChangeable = JFALSE;
                SDL_ShowCursor(SDL_ENABLE);
            }
        }
        JINLINE JCVOID addComponents(JCONST JSP<JDM::Comp::Components> &comp) { JDM::allComponents.push_back(comp); }
        JINLINE JCVOID removeComponents(JCONST JSP<JDM::Comp::Components> &comp) { JDM::allComponents.remove(comp); }

        JTEMPLATE<JCLASS T>
        JINLINE JSTATIC JCVOID addAnimation(JCONST JSP<JDM::Animation<T>> &anim) { JDM::allAnimations.push_back(anim); }
        JTEMPLATE<JCLASS T>
        JINLINE JSTATIC JCVOID addStartAnimation(JCONST JSP<JDM::Animation<T>> &anim) {
            anim->start();
            JDM::allAnimations.push_back(anim);
        }
        JTEMPLATE<JCLASS T>
        JINLINE JCVOID JSTATIC removeAnimation(JCONST JSP<JDM::Animation<T>> &anim) {
            anim->cancel();
            JDM::allAnimations.remove(anim);
        }
        JINLINE JCVOID setFocusedTextComponent(JDM::Comp::FocusedTextComponent *focusedText) { JDM::focusedTextComponent = focusedText; }

    JPRIVATE:
        JINLINE JCVOID animationUpdate() {
            JFOR(JAUTO anim = JDM::allAnimations.begin(); anim != JDM::allAnimations.end();) {
                JIF ((*anim)->update() && (*anim)->GetAutoRemove())
                    anim = JDM::allAnimations.erase(anim);
                anim++;
            }
        }
        JINLINE JCVOID winUpdate() {
            JFOR (JAUTO &comp : JDM::allComponents) comp->updateComp();
        }
        JINLINE JCVOID winRender() {
            SDL_SetRenderDrawColor(JDM::renderer, JTHIS->winColor.r, JTHIS->winColor.g, JTHIS->winColor.b, 255);
            SDL_RenderClear(JDM::renderer);
            JFOR (JAUTO &comp : JDM::allComponents) 
                JIF (!comp->getRendering()) comp->renderComp();

            JIF (JTHIS->isCursorChangeable) {
                JTHIS->cursorRect = {JDM::Mouse::GlobalMouseX - JDM::WindowX, JDM::Mouse::GlobalMouseY - JDM::WindowY, 20, 20};
                SDL_RenderCopy(JDM::renderer, JTHIS->cursorTexture, JNULLPTR, &JTHIS->cursorRect);
            }
            SDL_RenderPresent(JDM::renderer);
        }
        JINLINE JCVOID pollEvent() {
            SDL_GetGlobalMouseState(&JDM::Mouse::GlobalMouseX, &JDM::Mouse::GlobalMouseY);
            SDL_GetWindowPosition(JTHIS->window, &JDM::WindowX, &JDM::WindowY);
            JWHILE (SDL_PollEvent(&JTHIS->event)) {

                JSWITCH (JTHIS->event.type) {
                    JCASE SDL_QUIT: JTHIS->running = SDL_FALSE; JBREAK;
                    JCASE SDL_KEYDOWN:
                        JIF (JTHIS->isKeyDown) JTHIS->keyHold(JTHIS->keyBoardDown(JTHIS->event.key));
                        JELSE JTHIS->keyDown(JTHIS->keyBoardDown(JTHIS->event.key));
                        JBREAK;
                    JCASE SDL_KEYUP: JTHIS->keyUp(JTHIS->keyBoardUp(JTHIS->event.key)); JBREAK;

                    JCASE SDL_MOUSEBUTTONDOWN:
                        JDM::alreadyTouched = JFALSE;
                        JIF (JDM::focusedTextComponent != JNULLPTR) JDM::focusedTextComponent->isFocused = JFALSE;
                        JDM::focusedTextComponent = JNULLPTR;
                        JTHIS->mouseWinDown(JTHIS->event.button);
                        JFOR (JAUTO &comp : JDM::allComponents) {
                            JIF (comp->mouseDownComp(JTHIS->event.button) && comp->getName() == "FocusedTextComponent") {
                                JDM::focusedTextComponent = JDYNAMICC<JDM::Comp::FocusedTextComponent*>(&(*comp));
                                JDM::focusedTextComponent->isFocused = JTRUE;
                            }
                        }
                        JBREAK;
                    JCASE SDL_MOUSEMOTION:
                        JTHIS->mouseWinMotion(JTHIS->event.motion);
                        JFOR (JAUTO &comp : JDM::allComponents) comp->mouseMotionComp(JTHIS->event.motion);
                        JBREAK;

                    JCASE SDL_MOUSEBUTTONUP:
                        JTHIS->mouseWinUp(JTHIS->event.button);
                        JFOR (JAUTO &comp : JDM::allComponents) comp->mouseUpComp(JTHIS->event.button);
                        JBREAK;

                    JDEFAULT: JBREAK;
                }
            }
        }
        JINLINE JCVOID mouseWinDown(SDL_MouseButtonEvent &mouse) {
            JIF (mouse.button == SDL_BUTTON_LEFT)
                JDM::Mouse::LeftMouseDown = JTRUE;
            JELSE JDM::Mouse::RightMouseDown = JTRUE;
            JTHIS->mouseDown();
        }
        JINLINE JCVOID mouseWinUp(SDL_MouseButtonEvent &mouse) {
            JIF (mouse.button == SDL_BUTTON_RIGHT)
                JDM::Mouse::RightMouseDown = JFALSE;
            JELSE JDM::Mouse::LeftMouseDown = JFALSE;
            JTHIS->mouseUp();
        }
        JINLINE JCVOID mouseWinMotion(SDL_MouseMotionEvent &mouse) {
            SDL_GetMouseState(&JDM::Mouse::MouseX, &JDM::Mouse::MouseY);
            JTHIS->mouseMotion();
        }
        JINLINE JCBOOL *keyBoardDown(SDL_KeyboardEvent &key) {
            JTHIS->isKeyDown = JTRUE;
            JSWITCH (key.keysym.sym) {
                JCASE SDLK_a: JDM::KeyCode::A = JTRUE;
                    JTHIS->enterKey("a", "A");
                    JRETURN &JDM::KeyCode::A;
                JCASE SDLK_b: JDM::KeyCode::B = JTRUE;
                    JTHIS->enterKey("b", "B");
                    JRETURN &JDM::KeyCode::B;
                JCASE SDLK_c: JDM::KeyCode::C = JTRUE;
                    JTHIS->enterKey("c", "C");
                    JRETURN &JDM::KeyCode::C;
                JCASE SDLK_d: JDM::KeyCode::D = JTRUE;
                    JTHIS->enterKey("d", "D");
                    JRETURN &JDM::KeyCode::D;
                JCASE SDLK_e: JDM::KeyCode::E = JTRUE;
                    JTHIS->enterKey("e", "E");
                    JRETURN &JDM::KeyCode::E;
                JCASE SDLK_f: JDM::KeyCode::F = JTRUE;
                    JTHIS->enterKey("f", "F");
                    JRETURN &JDM::KeyCode::F;
                JCASE SDLK_g: JDM::KeyCode::G = JTRUE;
                    JTHIS->enterKey("g", "G");
                    JRETURN &JDM::KeyCode::G;
                JCASE SDLK_h: JDM::KeyCode::H = JTRUE;
                    JTHIS->enterKey("h", "H");
                    JRETURN &JDM::KeyCode::H;
                JCASE SDLK_i: JDM::KeyCode::I = JTRUE;
                    JTHIS->enterKey("i", "I");
                    JRETURN &JDM::KeyCode::I;
                JCASE SDLK_j: JDM::KeyCode::J = JTRUE;
                    JTHIS->enterKey("j", "J");
                    JRETURN &JDM::KeyCode::J;
                JCASE SDLK_k: JDM::KeyCode::K = JTRUE;
                    JTHIS->enterKey("k", "K");
                    JRETURN &JDM::KeyCode::K;
                JCASE SDLK_l: JDM::KeyCode::L = JTRUE;
                    JTHIS->enterKey("l", "L");
                    JRETURN &JDM::KeyCode::L;
                JCASE SDLK_m: JDM::KeyCode::M = JTRUE;
                    JTHIS->enterKey("m", "M");
                    JRETURN &JDM::KeyCode::M;
                JCASE SDLK_n: JDM::KeyCode::N = JTRUE;
                    JTHIS->enterKey("n", "N");
                    JRETURN &JDM::KeyCode::N;
                JCASE SDLK_o: JDM::KeyCode::O = JTRUE;
                    JTHIS->enterKey("o", "O");
                    JRETURN &JDM::KeyCode::O;
                JCASE SDLK_p: JDM::KeyCode::P = JTRUE;
                    JTHIS->enterKey("p", "P");
                    JRETURN &JDM::KeyCode::P;
                JCASE SDLK_q: JDM::KeyCode::Q = JTRUE;
                    JTHIS->enterKey("q", "Q");
                    JRETURN &JDM::KeyCode::Q;
                JCASE SDLK_r: JDM::KeyCode::R = JTRUE;
                    JTHIS->enterKey("r", "R");
                    JRETURN &JDM::KeyCode::R;
                JCASE SDLK_s: JDM::KeyCode::S = JTRUE;
                    JTHIS->enterKey("s", "S");
                    JRETURN &JDM::KeyCode::S;
                JCASE SDLK_t: JDM::KeyCode::T = JTRUE;
                    JTHIS->enterKey("t", "T");
                    JRETURN &JDM::KeyCode::T;
                JCASE SDLK_u: JDM::KeyCode::U = JTRUE;
                    JTHIS->enterKey("u", "U");
                    JRETURN &JDM::KeyCode::U;
                JCASE SDLK_v: JDM::KeyCode::V = JTRUE;
                    JTHIS->enterKey("v", "V");
                    JRETURN &JDM::KeyCode::V;
                JCASE SDLK_w: JDM::KeyCode::W = JTRUE;
                    JTHIS->enterKey("w", "W");
                    JRETURN &JDM::KeyCode::W;
                JCASE SDLK_x: JDM::KeyCode::X = JTRUE;
                    JTHIS->enterKey("x", "X");
                    JRETURN &JDM::KeyCode::X;
                JCASE SDLK_y: JDM::KeyCode::Y = JTRUE;
                    JTHIS->enterKey("y", "Y");
                    JRETURN &JDM::KeyCode::Y;
                JCASE SDLK_z: JDM::KeyCode::Z = JTRUE;
                    JTHIS->enterKey("z", "Z");
                    JRETURN &JDM::KeyCode::Z;

                JCASE SDLK_LSHIFT: JDM::KeyCode::LEFT_SHIFT = JTRUE; JRETURN &JDM::KeyCode::LEFT_SHIFT;
                JCASE SDLK_RSHIFT: JDM::KeyCode::RIGHT_SHIFT = JTRUE; JRETURN &JDM::KeyCode::RIGHT_SHIFT;
                JCASE SDLK_LCTRL: JDM::KeyCode::LEFT_CONTROL = JTRUE; JRETURN &JDM::KeyCode::LEFT_CONTROL;
                JCASE SDLK_RCTRL: JDM::KeyCode::RIGHT_CONTROL = JTRUE; JRETURN &JDM::KeyCode::RIGHT_CONTROL;
                JCASE SDLK_CAPSLOCK: JDM::KeyCode::CAPSLOCK = JTRUE; JRETURN &JDM::KeyCode::CAPSLOCK;
                JCASE SDLK_RETURN: JDM::KeyCode::ENTER = JTRUE;
                    JIF (JDM::focusedTextComponent != JNULLPTR) JDM::focusedTextComponent->isFocused = JFALSE;
                    JDM::focusedTextComponent = JNULLPTR;
                    JRETURN &JDM::KeyCode::ENTER;
                JCASE SDLK_TAB: JDM::KeyCode::TAB = JTRUE;
                    JTHIS->enterKey("    ", "    ");
                    JRETURN &JDM::KeyCode::TAB;
                JCASE SDLK_BACKSPACE: JDM::KeyCode::BACKSPACE = JTRUE;
                    JTHIS->deletekey();
                    JRETURN &JDM::KeyCode::BACKSPACE;

                JCASE SDLK_SPACE: JDM::KeyCode::SPACE = JTRUE;
                    JTHIS->enterKey(" ", " ");
                    JRETURN &JDM::KeyCode::SPACE;
                JCASE SDLK_EQUALS: JDM::KeyCode::KPLUS = JTRUE;
                    JTHIS->enterKey("=", "+");
                    JRETURN &JDM::KeyCode::KPLUS;
                JCASE SDLK_MINUS: JDM::KeyCode::KMINUS = JTRUE;
                    JTHIS->enterKey("-", "_");
                    JRETURN &JDM::KeyCode::KMINUS;

                JCASE SDLK_0: JDM::KeyCode::N0 = JTRUE;
                    JTHIS->enterKey("0", ")");
                    JRETURN &JDM::KeyCode::N0;
                JCASE SDLK_1: JDM::KeyCode::N1 = JTRUE;
                    JTHIS->enterKey("1", "!");
                    JRETURN &JDM::KeyCode::N1;
                JCASE SDLK_2: JDM::KeyCode::N2 = JTRUE;
                    JTHIS->enterKey("2", "@");
                    JRETURN &JDM::KeyCode::N2;
                JCASE SDLK_3: JDM::KeyCode::N3 = JTRUE;
                    JTHIS->enterKey("3", "#");
                    JRETURN &JDM::KeyCode::N3;
                JCASE SDLK_4: JDM::KeyCode::N4 = JTRUE;
                    JTHIS->enterKey("4", "$");
                    JRETURN &JDM::KeyCode::N4;
                JCASE SDLK_5: JDM::KeyCode::N5 = JTRUE;
                    JTHIS->enterKey("5", "%");
                    JRETURN &JDM::KeyCode::N5;
                JCASE SDLK_6: JDM::KeyCode::N6 = JTRUE;
                    JTHIS->enterKey("6", "^");
                    JRETURN &JDM::KeyCode::N6;
                JCASE SDLK_7: JDM::KeyCode::N7 = JTRUE;
                    JTHIS->enterKey("7", "&");
                    JRETURN &JDM::KeyCode::N7;
                JCASE SDLK_8: JDM::KeyCode::N8 = JTRUE;
                    JTHIS->enterKey("8", "*");
                    JRETURN &JDM::KeyCode::N8;
                JCASE SDLK_9: JDM::KeyCode::N9 = JTRUE;
                    JTHIS->enterKey("9", "(");
                    JRETURN &JDM::KeyCode::N9;

                JCASE SDLK_UP: JDM::KeyCode::UP = JTRUE; JRETURN &JDM::KeyCode::UP;
                JCASE SDLK_DOWN: JDM::KeyCode::DOWN = JTRUE; JRETURN &JDM::KeyCode::DOWN;
                JCASE SDLK_LEFT: JDM::KeyCode::LEFT = JTRUE;
                    JIF (JDM::focusedTextComponent != JNULLPTR) {
                        JDM::focusedTextComponent->index--;
                        JIF(JDM::focusedTextComponent->index < -1) JDM::focusedTextComponent->index = -1;
                    }
                    JRETURN &JDM::KeyCode::LEFT;
                JCASE SDLK_RIGHT: JDM::KeyCode::RIGHT = JTRUE;
                    JIF (JDM::focusedTextComponent != JNULLPTR) {
                        JDM::focusedTextComponent->index++;
                        JIF(JDM::focusedTextComponent->index > JDM::focusedTextComponent->getText().size() - 1)
                            JDM::focusedTextComponent->index = JDM::focusedTextComponent->getText().size() - 1;
                    }
                    JRETURN &JDM::KeyCode::RIGHT;
                JCASE SDLK_PERIOD: JDM::KeyCode::PERIOD = JTRUE;
                    JTHIS->enterKey(".", ">");
                    JRETURN &JDM::KeyCode::PERIOD;
                JCASE SDLK_COMMA: JDM::KeyCode::COMMA = JTRUE;
                    JTHIS->enterKey(",", "<");
                    JRETURN &JDM::KeyCode::COMMA;
                JCASE SDLK_SLASH: JDM::KeyCode::QUESTION = JTRUE;
                    JTHIS->enterKey("/", "?");
                    JRETURN &JDM::KeyCode::QUESTION;
                JCASE SDLK_QUOTE: JDM::KeyCode::QUESTION = JTRUE;
                    JTHIS->enterKey("'", "\"");
                    JRETURN &JDM::KeyCode::QUESTION;
                JDEFAULT: JRETURN JNULLPTR;
            }
        }
        JINLINE JCVOID enterKey(JCSTR &small, JCSTR &big) {
            JIF (JDM::focusedTextComponent != JNULLPTR) {
                JDM::focusedTextComponent->setText(
                    addCharAtIndex(JDM::focusedTextComponent->getText(), JDM::focusedTextComponent->index + 1,
                    JDM::KeyCode::LEFT_SHIFT || JDM::KeyCode::RIGHT_SHIFT ? big : small));
                JDM::focusedTextComponent->index += 1;
            }
        }
        JINLINE JCVOID deletekey() {
            JIF (JDM::focusedTextComponent != JNULLPTR) {
                JDM::focusedTextComponent->setText(
                    subtractCharAtIndex(JDM::focusedTextComponent->getText(), JDM::focusedTextComponent->index));
                JDM::focusedTextComponent->index -= 1;
                JIF(JDM::focusedTextComponent->index < -1) JDM::focusedTextComponent->index = -1;
            }
        }
        JINLINE JCBOOL *keyBoardUp(SDL_KeyboardEvent &key) {
            JTHIS->isKeyDown = JFALSE;
            JSWITCH (key.keysym.sym) {
                JCASE SDLK_a: JDM::KeyCode::A = JFALSE; JRETURN &JDM::KeyCode::A;
                JCASE SDLK_b: JDM::KeyCode::B = JFALSE; JRETURN &JDM::KeyCode::B;
                JCASE SDLK_c: JDM::KeyCode::C = JFALSE; JRETURN &JDM::KeyCode::C;
                JCASE SDLK_d: JDM::KeyCode::D = JFALSE; JRETURN &JDM::KeyCode::D;
                JCASE SDLK_e: JDM::KeyCode::E = JFALSE; JRETURN &JDM::KeyCode::E;
                JCASE SDLK_f: JDM::KeyCode::F = JFALSE; JRETURN &JDM::KeyCode::F;
                JCASE SDLK_g: JDM::KeyCode::G = JFALSE; JRETURN &JDM::KeyCode::G;
                JCASE SDLK_h: JDM::KeyCode::H = JFALSE; JRETURN &JDM::KeyCode::H;
                JCASE SDLK_i: JDM::KeyCode::I = JFALSE; JRETURN &JDM::KeyCode::I;
                JCASE SDLK_j: JDM::KeyCode::J = JFALSE; JRETURN &JDM::KeyCode::J;
                JCASE SDLK_k: JDM::KeyCode::K = JFALSE; JRETURN &JDM::KeyCode::K;
                JCASE SDLK_l: JDM::KeyCode::L = JFALSE; JRETURN &JDM::KeyCode::L;
                JCASE SDLK_m: JDM::KeyCode::M = JFALSE; JRETURN &JDM::KeyCode::M;
                JCASE SDLK_n: JDM::KeyCode::N = JFALSE; JRETURN &JDM::KeyCode::N;
                JCASE SDLK_o: JDM::KeyCode::O = JFALSE; JRETURN &JDM::KeyCode::O;
                JCASE SDLK_p: JDM::KeyCode::P = JFALSE; JRETURN &JDM::KeyCode::P;
                JCASE SDLK_q: JDM::KeyCode::Q = JFALSE; JRETURN &JDM::KeyCode::Q;
                JCASE SDLK_r: JDM::KeyCode::R = JFALSE; JRETURN &JDM::KeyCode::R;
                JCASE SDLK_s: JDM::KeyCode::S = JFALSE; JRETURN &JDM::KeyCode::S;
                JCASE SDLK_t: JDM::KeyCode::T = JFALSE; JRETURN &JDM::KeyCode::T;
                JCASE SDLK_u: JDM::KeyCode::U = JFALSE; JRETURN &JDM::KeyCode::U;
                JCASE SDLK_v: JDM::KeyCode::V = JFALSE; JRETURN &JDM::KeyCode::V;
                JCASE SDLK_w: JDM::KeyCode::W = JFALSE; JRETURN &JDM::KeyCode::W;
                JCASE SDLK_x: JDM::KeyCode::X = JFALSE; JRETURN &JDM::KeyCode::X;
                JCASE SDLK_y: JDM::KeyCode::Y = JFALSE; JRETURN &JDM::KeyCode::Y;
                JCASE SDLK_z: JDM::KeyCode::Z = JFALSE; JRETURN &JDM::KeyCode::Z;

                JCASE SDLK_LSHIFT: JDM::KeyCode::LEFT_SHIFT = JFALSE; JRETURN &JDM::KeyCode::LEFT_SHIFT;
                JCASE SDLK_RSHIFT: JDM::KeyCode::RIGHT_SHIFT = JFALSE; JRETURN &JDM::KeyCode::RIGHT_SHIFT;
                JCASE SDLK_LCTRL: JDM::KeyCode::LEFT_CONTROL = JFALSE; JRETURN &JDM::KeyCode::LEFT_CONTROL;
                JCASE SDLK_RCTRL: JDM::KeyCode::RIGHT_CONTROL = JFALSE; JRETURN &JDM::KeyCode::RIGHT_CONTROL;
                JCASE SDLK_CAPSLOCK: JDM::KeyCode::CAPSLOCK = JFALSE; JRETURN &JDM::KeyCode::CAPSLOCK;
                JCASE SDLK_RETURN: JDM::KeyCode::ENTER = JFALSE; JRETURN &JDM::KeyCode::ENTER;
                JCASE SDLK_TAB: JDM::KeyCode::TAB = JFALSE; JRETURN &JDM::KeyCode::TAB;
                JCASE SDLK_BACKSPACE: JDM::KeyCode::BACKSPACE = JFALSE; JRETURN &JDM::KeyCode::BACKSPACE;

                JCASE SDLK_SPACE: JDM::KeyCode::SPACE = JFALSE; JRETURN &JDM::KeyCode::SPACE;
                JCASE SDLK_EQUALS: JDM::KeyCode::KPLUS = JFALSE; JRETURN &JDM::KeyCode::KPLUS;
                JCASE SDLK_MINUS: JDM::KeyCode::KMINUS = JFALSE; JRETURN &JDM::KeyCode::KMINUS;

                JCASE SDLK_0: JDM::KeyCode::N0 = JFALSE; JRETURN &JDM::KeyCode::N0;
                JCASE SDLK_1: JDM::KeyCode::N1 = JFALSE; JRETURN &JDM::KeyCode::N1;
                JCASE SDLK_2: JDM::KeyCode::N2 = JFALSE; JRETURN &JDM::KeyCode::N2;
                JCASE SDLK_3: JDM::KeyCode::N3 = JFALSE; JRETURN &JDM::KeyCode::N3;
                JCASE SDLK_4: JDM::KeyCode::N4 = JFALSE; JRETURN &JDM::KeyCode::N4;
                JCASE SDLK_5: JDM::KeyCode::N5 = JFALSE; JRETURN &JDM::KeyCode::N5;
                JCASE SDLK_6: JDM::KeyCode::N6 = JFALSE; JRETURN &JDM::KeyCode::N6;
                JCASE SDLK_7: JDM::KeyCode::N7 = JFALSE; JRETURN &JDM::KeyCode::N7;
                JCASE SDLK_8: JDM::KeyCode::N8 = JFALSE; JRETURN &JDM::KeyCode::N8;
                JCASE SDLK_9: JDM::KeyCode::N9 = JFALSE; JRETURN &JDM::KeyCode::N9;

                JCASE SDLK_UP: JDM::KeyCode::UP = JFALSE; JRETURN &JDM::KeyCode::UP;
                JCASE SDLK_DOWN: JDM::KeyCode::DOWN = JFALSE; JRETURN &JDM::KeyCode::DOWN;
                JCASE SDLK_LEFT: JDM::KeyCode::LEFT = JFALSE; JRETURN &JDM::KeyCode::LEFT;
                JCASE SDLK_RIGHT: JDM::KeyCode::RIGHT = JFALSE; JRETURN &JDM::KeyCode::RIGHT;

                JCASE SDLK_PERIOD: JDM::KeyCode::PERIOD = JFALSE; JRETURN &JDM::KeyCode::PERIOD;
                JCASE SDLK_COMMA: JDM::KeyCode::COMMA = JFALSE; JRETURN &JDM::KeyCode::COMMA;
                JCASE SDLK_QUESTION: JDM::KeyCode::QUESTION = JFALSE; JRETURN &JDM::KeyCode::QUESTION;
                JCASE SDLK_QUOTE: JDM::KeyCode::QOUTE = JFALSE; JRETURN &JDM::KeyCode::QOUTE;
                JDEFAULT: JRETURN JNULLPTR;
            }
        }
    };
    JNAMESPACE Layout {
    JCLASS BaseLayout : JPUBLIC JDM::Comp::Components{
    JPUBLIC:
        JBOOL isAccessible = JTRUE;
        JLIST<JSP<JDM::Comp::Components>> childrens;
        JINLINE JCVOID moveAllX(JCDOUBLE x) {
            JFOR (JAUTO &child : JTHIS->childrens)
                child->setX(child->getX() + x);
        }
        JINLINE JCBOOL mouseDownComp(SDL_MouseButtonEvent &mouse) {
            JIF (!JTHIS->isAccessible) JRETURN JTRUE;
            JTHIS->getmouseDownFunction()(mouse);
            JFOR (JAUTO &comp : JTHIS->childrens) {
                JIF (comp->mouseDownComp(mouse) && comp->getName() == "FocusedTextComponent") {
                    JDM::focusedTextComponent = JDYNAMICC<JDM::Comp::FocusedTextComponent*>(&(*comp));
                    JDM::focusedTextComponent->isFocused = JTRUE;
                }
            }
            JRETURN JTRUE;
        }
        JINLINE JCVOID mouseMotionComp(SDL_MouseMotionEvent & mouse) {
            JIF (!JTHIS->isAccessible) JRETURN
            JTHIS->getmouseMotionFunction()(mouse);
            JFOR(JAUTO &comp : JTHIS->childrens) comp->mouseMotionComp(mouse); }
        JINLINE JCVOID mouseUpComp(SDL_MouseButtonEvent &mouse)  {
            JIF (!JTHIS->isAccessible) JRETURN
            JTHIS->getmouseUpFunction()(mouse);
            JFOR(JAUTO &comp : JTHIS->childrens) comp->mouseUpComp(mouse); }

        JINLINE JVIRTUAL JCSTR getName() JCONST { JRETURN "BaseLayout"; }

        JINLINE JCVOID moveAllXSmooth(JCDOUBLE x, JCDOUBLE duration) {
            JFOR (JAUTO &child : JTHIS->childrens) {
                JDM::Window::addStartAnimation(
                    JMS<JDM::Animation<JDOUBLE>>(child->getPointerX(), (child->getX() + x), duration, true)); 
            }
        }
        JINLINE JCVOID moveAllY(JCDOUBLE y) {
            JFOR (JAUTO &child : JTHIS->childrens)
                child->setY(child->getY() + y);
        }
        JINLINE JCVOID moveAllYSmooth(JCDOUBLE y, JCDOUBLE duration) {
            JFOR (JAUTO &child : JTHIS->childrens) {
                JDM::Window::addStartAnimation(
                    JMS<JDM::Animation<JDOUBLE>>(child->getPointerY(), (child->getY() + y), duration, true)); 
            }
        }
        JINLINE JCVOID setAllOpacity(JUINT8 a) {
            JFOR (JAUTO &child : JTHIS->childrens)
                child->setAForeGround(a);
        }
        JINLINE JCVOID setAllOpacitySmooth(JUINT8 a, JCDOUBLE duration) {
            JFOR (JAUTO &child : JTHIS->childrens) {
                JIF (child->getPointerAImage() != JNULLPTR) 
                    JDM::Window::addStartAnimation(JMS<JDM::Animation<JUINT8>>(child->getPointerAImage(), a, duration, true)); 
                JIF (child->getPointerAForeGround() != JNULLPTR) 
                    JDM::Window::addStartAnimation(JMS<JDM::Animation<JUINT8>>(child->getPointerAForeGround(), a, duration, true)); 
            }
        }
        JINLINE JCVOID addComponents(JCONST JSP<JDM::Comp::Components> &comp) { JTHIS->childrens.push_back(comp); }
        JINLINE JCVOID removeComponents(JCONST JSP<JDM::Comp::Components> &comp) { JTHIS->childrens.remove(comp); }

        JINLINE JCVOID update() { JFOR (JAUTO &child : JTHIS->childrens) { child->updateComp(); } }
        JINLINE JCVOID renderComp() { JFOR (JAUTO &child : JTHIS->childrens) { child->renderComp(); } }
        };
    };
};
#endif