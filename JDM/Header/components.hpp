#pragma once
#ifndef JDM_COMPONENTS
#define JDM_COMPONENTS
#include "JDM_include.hpp"
#include "fonts.hpp"
#include "logger.hpp"

JNAMESPACE JDM{JNAMESPACE Comp{
    JCLASS Components{
    JPRIVATE:
        funcCallback updateFunction = []() {};
        funcMouseCallBack mouseDownFunction = [](SDL_MouseButtonEvent &mouse) {};
        funcMotionCallBack mouseMotionFunction = [](SDL_MouseMotionEvent &mouse) {};
        funcMouseCallBack mouseUpFunction = [](SDL_MouseButtonEvent &mouse) {};
        JBOOL mouseClicked = JFALSE;
        JBOOL pickOnTop = JFALSE;
        JBOOL pickOnBounds = JTRUE;
        JBOOL stopRendering = JFALSE;
        SizePos sizePos = {};

    JPROTECTED:
        JINLINE JCVOID setMouseClick(JCBOOL set) { JTHIS->mouseClicked = set; }
    JPUBLIC:
        Components(JCDOUBLE xPos = 0, JCDOUBLE yPos = 0,
          JCDOUBLE Width = 100, JCDOUBLE Height = 100)
          : sizePos({xPos, yPos, Width, Height}) {}

        JCONSTEXPR JCBOOL contains(JCDOUBLE xPos, JCDOUBLE yPos) JCONST {
            JRETURN ((JTHIS->getX() <= xPos && (JTHIS->getX() + JTHIS->getWidth()) >= xPos)
                && (JTHIS->getY() <= yPos && (JTHIS->getY() + JTHIS->getHeight()) >= yPos));
        }
        JINLINE JCVOID setSizePos(JCONST SizePos sPos) { JTHIS->sizePos = sPos; }
        JINLINE JCVOID setPos(JCONST Position pos) { JTHIS->sizePos.pos = pos; }
        JINLINE JCVOID setSize(JCONST Size size) { JTHIS->sizePos.size = size; }
        JINLINE JCVOID setX(JCDOUBLE xPos) { JTHIS->sizePos.x = xPos; }
        JINLINE JCVOID setY(JCDOUBLE yPos) { JTHIS->sizePos.y = yPos; }
        JINLINE JCVOID setWidth(JCDOUBLE Width) { JTHIS->sizePos.width = Width; }
        JINLINE JCVOID setHeight(JCDOUBLE Height) { JTHIS->sizePos.height = Height; }
        JINLINE JCVOID setPickOnBounds(JCBOOL bounds) { JTHIS->pickOnBounds = bounds; }
        JINLINE JCVOID setPickOnTop(JCBOOL top) { JTHIS->pickOnTop = top; }
        JINLINE JCVOID setRendering(JCBOOL isRendering) { JTHIS->stopRendering = isRendering; }

        JINLINE JCVOID setUpdateFunction(JCONST funcCallback function) { JTHIS->updateFunction = function; }
        JINLINE JCVOID setmouseDownFunction(JCONST funcMouseCallBack function) { JTHIS->mouseDownFunction = function; }
        JINLINE JCVOID setmouseMotionFunction(JCONST funcMotionCallBack function) { JTHIS->mouseMotionFunction = function; }
        JINLINE JCVOID setmouseUpFunction(JCONST funcMouseCallBack function) { JTHIS->mouseUpFunction = function; }

        JCONSTEXPR JCONST SizePos getSizePos() JCONST { JRETURN JTHIS->sizePos; }
        JCONSTEXPR JCONST Position getPos() JCONST { JRETURN JTHIS->sizePos.pos; }
        JCONSTEXPR JCONST Size getSize() JCONST { JRETURN JTHIS->sizePos.size; }
        JCONSTEXPR JCDOUBLE getX() JCONST { JRETURN JTHIS->sizePos.x; }
        JCONSTEXPR JCDOUBLE getY() JCONST { JRETURN JTHIS->sizePos.y; }
        JCONSTEXPR JCDOUBLE getWidth() JCONST { JRETURN JTHIS->sizePos.width; }
        JCONSTEXPR JCDOUBLE getHeight() JCONST { JRETURN JTHIS->sizePos.height; }
        JCONSTEXPR JCBOOL getRendering() JCONST { JRETURN JTHIS->stopRendering; }
        JCONSTEXPR JCBOOL getPickOnBounds() JCONST { JRETURN JTHIS->pickOnBounds; }
        JCONSTEXPR JCBOOL getPickOnTop() JCONST { JRETURN JTHIS->pickOnTop; }
        JCONSTEXPR JCBOOL getMouseClick() JCONST { JRETURN JTHIS->mouseClicked; }
        JINLINE JVIRTUAL JCSTR getName() JCONST { JRETURN "Components"; }

        JDOUBLE *getPointerX() { JRETURN &JTHIS->sizePos.x; }
        JDOUBLE *getPointerY() { JRETURN &JTHIS->sizePos.y; }
        JDOUBLE *getPointerWidth() { JRETURN &JTHIS->sizePos.width; }
        JDOUBLE *getPointerHeight() { JRETURN &JTHIS->sizePos.height; }

        JINLINE JINT *getPointerArcTL() { JRETURN JNULLPTR; }
        JINLINE JINT *getPointerArcTR() { JRETURN JNULLPTR; }
        JINLINE JINT *getPointerArcBL() { JRETURN JNULLPTR; }
        JINLINE JINT *getPointerArcBR() { JRETURN JNULLPTR; }

        JVIRTUAL JCVOID setRImage(JUINT8 c) { }
        JVIRTUAL JCVOID setGImage(JUINT8 c) { }
        JVIRTUAL JCVOID setBImage(JUINT8 c) { }
        JVIRTUAL JCVOID setAImage(JUINT8 c) { }

        JVIRTUAL JCVOID setRForeGround(JUINT8 c) { }
        JVIRTUAL JCVOID setGForeGround(JUINT8 c) { }
        JVIRTUAL JCVOID setBForeGround(JUINT8 c) { }
        JVIRTUAL JCVOID setAForeGround(JUINT8 c) { }

        JVIRTUAL JUINT8 getRImage() { JRETURN 0; }
        JVIRTUAL JUINT8 getGImage() { JRETURN 0; }
        JVIRTUAL JUINT8 getBImage() { JRETURN 0; }
        JVIRTUAL JUINT8 getAImage() { JRETURN 0; }

        JVIRTUAL JUINT8 getRForeGround() { JRETURN 0; }
        JVIRTUAL JUINT8 getGForeGround() { JRETURN 0; }
        JVIRTUAL JUINT8 getBForeGround() { JRETURN 0; }
        JVIRTUAL JUINT8 getAForeGround() { JRETURN 0; }

        JVIRTUAL JUINT8 *getPointerRImage() { JRETURN JNULLPTR; }
        JVIRTUAL JUINT8 *getPointerGImage() { JRETURN JNULLPTR; }
        JVIRTUAL JUINT8 *getPointerBImage() { JRETURN JNULLPTR; }
        JVIRTUAL JUINT8 *getPointerAImage() { JRETURN JNULLPTR; }

        JVIRTUAL JUINT8 *getPointerRForeGround() { JRETURN JNULLPTR; }
        JVIRTUAL JUINT8 *getPointerGForeGround() { JRETURN JNULLPTR; }
        JVIRTUAL JUINT8 *getPointerBForeGround() { JRETURN JNULLPTR; }
        JVIRTUAL JUINT8 *getPointerAForeGround() { JRETURN JNULLPTR; }

        JINLINE JCONST funcCallback getUpdateFunction() JCONST { JRETURN JTHIS->updateFunction; }
        JINLINE JCONST funcMouseCallBack getmouseDownFunction() JCONST { JRETURN JTHIS->mouseDownFunction; }
        JINLINE JCONST funcMotionCallBack getmouseMotionFunction() JCONST { JRETURN JTHIS->mouseMotionFunction; }
        JINLINE JCONST funcMouseCallBack getmouseUpFunction() JCONST { JRETURN JTHIS->mouseUpFunction; }

        JINLINE JCVOID updateComp() { JTHIS->update(); JTHIS->updateFunction(); }
        JINLINE JVIRTUAL JCBOOL mouseDownComp(SDL_MouseButtonEvent &mouse) {
            JIF (JTHIS->pickOnBounds) {
                JIF(JTHIS->pickOnTop && JDM::alreadyTouched) JRETURN JFALSE;
                JIF (JTHIS->contains(mouse.x, mouse.y)) {
                    JTHIS->mouseDownFunction(mouse);
                    JTHIS->mouseClicked = JTRUE;
                    JDM::alreadyTouched = JTRUE;
                    JRETURN JTRUE;
                }
            } JRETURN JFALSE;
        }
        JINLINE JVIRTUAL JCVOID mouseMotionComp(SDL_MouseMotionEvent &mouse) { JIF (JTHIS->mouseClicked) JTHIS->mouseMotionFunction(mouse); }
        JINLINE JVIRTUAL JCVOID mouseUpComp(SDL_MouseButtonEvent &mouse) { JIF (JTHIS->mouseClicked) { JTHIS->mouseClicked = JFALSE; JTHIS->mouseUpFunction(mouse);  }}
        JINLINE JVIRTUAL JCVOID renderComp() {}

    JPROTECTED:
        JINLINE JVIRTUAL JCVOID update() {}
        
    };

    JCLASS Image : JPUBLIC Components {
    JPRIVATE:
        JSTR sourceFiles;
        ColorRGBA rectColor;
        SDL_FRect rect;
        SDL_Rect rectSource;
        SDL_Texture *imageTexture;

        ColorRGBA startColor = {0, 0, 0, 0};
        ColorRGBA endColor = {0, 0, 0, 0};

        Gradient gradientAlignment = NONE;
        JINT arcTL = 0, arcTR = 0, arcBL = 0, arcBR = 0;
        JINT lineWidth = 0;

        JINLINE JCVOID setRect() {
            JTHIS->rect.w = JTHIS->getWidth();
            JTHIS->rect.h = JTHIS->getHeight();
            JTHIS->rect.x = JTHIS->getX();
            JTHIS->rect.y = JTHIS->getY();
        }

        JINLINE JCVOID setTexture(JCSTR &source) {
            JTHIS->imageTexture = JDM::loadRoundedTexture(JDM::renderer,
                JSTATICC<JINT>(JTHIS->getWidth()), JSTATICC<JINT>(JTHIS->getHeight()), source,
                JTHIS->arcTL, JTHIS->arcTR, JTHIS->arcBL, JTHIS->arcBR, JTHIS->lineWidth);

            JTHIS->rectSource.x = 0;
            JTHIS->rectSource.y = 0;
            SDL_QueryTexture(JTHIS->imageTexture, NULL, NULL, &JTHIS->rectSource.w, &JTHIS->rectSource.h);
            SDL_SetTextureBlendMode(JTHIS->imageTexture, SDL_BLENDMODE_BLEND);
            SDL_SetTextureScaleMode(JTHIS->imageTexture, SDL_ScaleMode::SDL_ScaleModeLinear);
        }

    JPUBLIC:
        Image(JCSTR &source, JCDOUBLE xPos = 0, JCDOUBLE yPos = 0,
              JCDOUBLE Width = 100, JCDOUBLE Height = 100, ColorRGBA color = {255, 255, 255, 255}, JCINT arc = 0)
          : arcTL(arc), arcTR(arc), arcBL(arc), arcBR(arc), Components(xPos, yPos, Width, Height) {
            JTHIS->setSource(source);
            JTHIS->setColor(color);
            JTHIS->renderComp();
        }
        ~Image() { SDL_DestroyTexture(JTHIS->imageTexture); }
        JINLINE JCVOID setSource(JCSTR &source) {
            JIF (isFileExist(source)) {
                JTHIS->sourceFiles = source;
                JTHIS->setTexture(JTHIS->sourceFiles);
            } JELSE { 
                JTHIS->sourceFiles = DefaultImage;
                JTHIS->setTexture(DefaultImage);
            }
        }
        JINLINE JCVOID setColor(ColorRGBA color) { JTHIS->rectColor = color; }
        JINLINE JCVOID updateColor() {
            SDL_SetTextureColorMod(JTHIS->imageTexture, JTHIS->rectColor.r, JTHIS->rectColor.g, JTHIS->rectColor.b);
            SDL_SetTextureAlphaMod(JTHIS->imageTexture, JTHIS->rectColor.a);
        }
        JCONSTEXPR ColorRGBA getColor() JCONST { JRETURN JTHIS->rectColor; }

        JINLINE JCVOID setRImage(JUINT8 c) { JTHIS->rectColor.r = c; }
        JINLINE JCVOID setGImage(JUINT8 c) { JTHIS->rectColor.g = c; }
        JINLINE JCVOID setBImage(JUINT8 c) { JTHIS->rectColor.b = c; }
        JINLINE JCVOID setAImage(JUINT8 c) { JTHIS->rectColor.a = c; }

        JINLINE JCVOID setArc(JINT c) {
                JTHIS->arcTL = c;
                JTHIS->arcTR = c;
                JTHIS->arcBL = c;
                JTHIS->arcBR = c;
                JTHIS->setTexture(JTHIS->sourceFiles); }
        JINLINE JCVOID setArcTL(JINT c) { JTHIS->arcTL = c; JTHIS->setTexture(JTHIS->sourceFiles); }
        JINLINE JCVOID setArcTR(JINT c) { JTHIS->arcTR = c; JTHIS->setTexture(JTHIS->sourceFiles); }
        JINLINE JCVOID setArcBL(JINT c) { JTHIS->arcBL = c; JTHIS->setTexture(JTHIS->sourceFiles); }
        JINLINE JCVOID setArcBR(JINT c) { JTHIS->arcBR = c; JTHIS->setTexture(JTHIS->sourceFiles); }
        JINLINE JCVOID setLineWidth(JUINT8 c) { JTHIS->lineWidth = c; }

        JINLINE JINT getArcTL(JINT c) { JRETURN JTHIS->arcTL; }
        JINLINE JINT getArcTR(JINT c) { JRETURN JTHIS->arcTR; }
        JINLINE JINT getArcBL(JINT c) { JRETURN JTHIS->arcBL; }
        JINLINE JINT getArcBR(JINT c) { JRETURN JTHIS->arcBR; }

        JINLINE JINT *getPointerArcTL() { JRETURN &JTHIS->arcTL; }
        JINLINE JINT *getPointerArcTR() { JRETURN &JTHIS->arcTR; }
        JINLINE JINT *getPointerArcBL() { JRETURN &JTHIS->arcBL; }
        JINLINE JINT *getPointerArcBR() { JRETURN &JTHIS->arcBR; }

        JUINT8 getRImage() { JRETURN JTHIS->rectColor.r; }
        JUINT8 getGImage() { JRETURN JTHIS->rectColor.g; }
        JUINT8 getBImage() { JRETURN JTHIS->rectColor.b; }
        JUINT8 getAImage() { JRETURN JTHIS->rectColor.a; }

        JINLINE JUINT8 *getPointerRImage() { JRETURN &JTHIS->rectColor.r; }
        JINLINE JUINT8 *getPointerGImage() { JRETURN &JTHIS->rectColor.g; }
        JINLINE JUINT8 *getPointerBImage() { JRETURN &JTHIS->rectColor.b; }
        JINLINE JUINT8 *getPointerAImage() { JRETURN &JTHIS->rectColor.a; }

        JINLINE JCSTR getSource() { JRETURN JTHIS->sourceFiles; }
        JINLINE JCVOID setRegion(Region region) { JTHIS->rectSource = { region.x, region.y, region.w, region.h }; }
        JINLINE JCONST Region getRegion() { JRETURN { JTHIS->rectSource.x, JTHIS->rectSource.y, JTHIS->rectSource.w, JTHIS->rectSource.h }; }
        JINLINE SDL_Texture *getTexture() { JRETURN JTHIS->imageTexture; }
        JINLINE JVIRTUAL JCSTR getName() JCONST { JRETURN "Image"; }

        JINLINE JUINT8 interpolateColorComponent(JUINT8 startComponent, JUINT8 endComponent, JINT y, JINT height) {
            JRETURN startComponent + ((endComponent - startComponent) * y) / height;
        }
        JINLINE JCVOID setGradient(Gradient grad) { JTHIS->gradientAlignment = grad; }
        JINLINE JCVOID setGradiendColor(ColorRGBA first, ColorRGBA second) {
            JTHIS->startColor = first;
            JTHIS->endColor = second;
        }

        JINLINE JCVOID update() JOVERRIDE {
            JTHIS->setRect();
            JTHIS->updateColor();
        }
        JINLINE JCVOID renderComp() JOVERRIDE {
            SDL_RenderCopyF(JDM::renderer, JTHIS->imageTexture, &JTHIS->rectSource, &JTHIS->rect);
            JIF (JTHIS->gradientAlignment == VERTICAL) {
                JFOR (JINT y = 0; y < JTHIS->getHeight(); y++) {
                    JUINT8 r = JTHIS->interpolateColorComponent(JTHIS->startColor.r, JTHIS->endColor.r, y, JTHIS->getHeight());
                    JUINT8 g = JTHIS->interpolateColorComponent(JTHIS->startColor.g, JTHIS->endColor.g, y, JTHIS->getHeight());
                    JUINT8 b = JTHIS->interpolateColorComponent(JTHIS->startColor.b, JTHIS->endColor.b, y, JTHIS->getHeight());
                    JUINT8 a = JTHIS->interpolateColorComponent(JTHIS->startColor.a, JTHIS->endColor.a, y, JTHIS->getHeight());

                    SDL_SetRenderDrawBlendMode(JDM::renderer, SDL_BLENDMODE_BLEND);
                    SDL_SetRenderDrawColor(JDM::renderer, r, g, b, a);
                    SDL_RenderDrawLine(JDM::renderer, JTHIS->getX(), JTHIS->getY() + y, JTHIS->getX() + JTHIS->getWidth(), JTHIS->getY() + y);
                    SDL_SetRenderDrawBlendMode(JDM::renderer, SDL_BLENDMODE_NONE);
                }
            } JELSE JIF (JTHIS->gradientAlignment == HORIZONTAL){
                JFOR (JINT x = 0; x < JTHIS->getWidth(); x++) {
                    JUINT8 r = JTHIS->interpolateColorComponent(JTHIS->startColor.r, JTHIS->endColor.r, x, JTHIS->getHeight());
                    JUINT8 g = JTHIS->interpolateColorComponent(JTHIS->startColor.g, JTHIS->endColor.g, x, JTHIS->getHeight());
                    JUINT8 b = JTHIS->interpolateColorComponent(JTHIS->startColor.b, JTHIS->endColor.b, x, JTHIS->getHeight());
                    JUINT8 a = JTHIS->interpolateColorComponent(JTHIS->startColor.a, JTHIS->endColor.a, x, JTHIS->getHeight());

                    SDL_SetRenderDrawBlendMode(JDM::renderer, SDL_BLENDMODE_BLEND);
                    SDL_SetRenderDrawColor(JDM::renderer, r, g, b, a);
                    SDL_RenderDrawLine(JDM::renderer, JTHIS->getX() + x, JTHIS->getY(), JTHIS->getX() + x, JTHIS->getY() + JTHIS->getHeight());
                    SDL_SetRenderDrawBlendMode(JDM::renderer, SDL_BLENDMODE_NONE);
                }
            }
        }
    };
    JCLASS Text : JPUBLIC Components {
    JPRIVATE:
        JSTR text;
        ColorRGBA rectColor;
        SDL_FRect rect;
        SDL_Texture *textTexture;
        JUINT FontSize = 15;
        JDOUBLE CopyFontSize = 15;
        JDM::Font::Valign valign = JDM::Font::Valign::VCENTER;
        JDM::Font::Halign halign = JDM::Font::Halign::HCENTER;
        JDM::Font::Font font = JDM::Font::Consolas();
        JDOUBLE paddingWidth = 0;
        JDOUBLE paddingHeight = 0;

        JBOOL isBold = JFALSE;
        JBOOL isItalic = JFALSE;
        JBOOL isLimit = JFALSE;

        JINLINE JCVOID setRect() {
            JTHIS->rect.w = JSTATICC<JFLOAT>(JTHIS->text.length() * JTHIS->FontSize);
            JIF (JTHIS->getWidth() - (JTHIS->paddingWidth*2) < JTHIS->rect.w) {
                JTHIS->rect.w = (JTHIS->getWidth() - (JTHIS->paddingWidth * 2));
                JTHIS->CopyFontSize = JTHIS->rect.w / JTHIS->text.length();
            } JELSE JTHIS->CopyFontSize = JTHIS->FontSize;
            JTHIS->rect.h = JSTATICC<JFLOAT>(FontSize + (FontSize * 0.85f));

            JSWITCH (JTHIS->halign) {
            JCASE JDM::Font::Halign::LEFT:
                this->rect.x = JTHIS->getX() + JTHIS->paddingWidth; JBREAK;
            JCASE JDM::Font::Halign::HCENTER:
                this->rect.x = JTHIS->getX() + ((JTHIS->getWidth() - JTHIS->rect.w) / 2.f); JBREAK;
            JCASE JDM::Font::Halign::RIGHT:
                this->rect.x = JTHIS->getX() + (JTHIS->getWidth() - JTHIS->rect.w) - JTHIS->paddingWidth; JBREAK;
            }
            JSWITCH (JTHIS->valign) {
            JCASE JDM::Font::Valign::TOP:
                this->rect.y = JTHIS->getY() - JTHIS->paddingHeight; JBREAK;
            JCASE JDM::Font::Valign::VCENTER:
                this->rect.y = JTHIS->getY() + ((JTHIS->getHeight() - JTHIS->rect.h) / 2.f); JBREAK;
            JCASE JDM::Font::Valign::BOTTOM:
                this->rect.y = JTHIS->getY() + (JTHIS->getHeight() - JTHIS->rect.h) + JTHIS->paddingHeight; JBREAK;
            }
        }

        JINLINE JCVOID setTextTexture(JCSTR text) {
            TTF_Font *tempFont = TTF_OpenFont(
                ((JTHIS->isBold && JTHIS->isItalic) ?     
                    JTHIS->font.ItalicBold.c_str() : ((JTHIS->isBold) ? 
                    JTHIS->font.Bold.c_str() : ((JTHIS->isItalic) ?
                    JTHIS->font.Italic.c_str() : JTHIS->font.Normal.c_str()))), 256);
            SDL_Surface *tempsurface = TTF_RenderText_Blended(tempFont, text.c_str(),
                SDL_Color{rectColor.r, rectColor.g, rectColor.b});
            JTHIS->textTexture = SDL_CreateTextureFromSurface(JDM::renderer, tempsurface);
            SDL_SetTextureScaleMode(JTHIS->textTexture, SDL_ScaleModeLinear);
            SDL_SetTextureBlendMode(JTHIS->textTexture, SDL_BLENDMODE_BLEND);
            SDL_FreeSurface(tempsurface);
            TTF_CloseFont(tempFont);
        }

    JPUBLIC:
        Text(JCSTR &text = "", JCDOUBLE xPos = 0, JCDOUBLE yPos = 0,
              JCDOUBLE Width = 100, JCDOUBLE Height = 100, ColorRGBA color = {255, 255, 255, 255},
              JCINT fontS = 15, JDM::Font::Halign hAlign = JDM::Font::HCENTER,
              JDM::Font::Valign vAlign = JDM::Font::VCENTER)
          : FontSize(fontS), valign(vAlign), halign(hAlign), Components(xPos, yPos, Width, Height) {
            JTHIS->rectColor = color;
            JTHIS->setText(text);
            JTHIS->setRect();
            JTHIS->renderComp();
        }
        ~Text() { SDL_DestroyTexture(JTHIS->textTexture); }
        JINLINE JCVOID setText(JCSTR &text) {
            JTHIS->text = text;
            JTHIS->setTextTexture(JTHIS->text);
        }
        JINLINE JCVOID setTextN(JCSTR &text) { JTHIS->setTextTexture(text); }
        JINLINE JCSTR getText() { JRETURN JTHIS->text; }

        JINLINE JCVOID setFontSize(JCUINT size) { JTHIS->FontSize = size; }
        JINLINE JCVOID setFontRegular(JCSTR &str) { JTHIS->font.Normal = str; JTHIS->setTextTexture(JTHIS->text); }
        JCONSTEXPR JCUINT getFontSize() JCONST { JRETURN JTHIS->FontSize; }
        JCONSTEXPR JCDOUBLE getCopyFontSize() JCONST { JRETURN JTHIS->CopyFontSize; }
        JINLINE JCVOID setBold(JCBOOL bold) { JTHIS->isBold = bold; JTHIS->setTextTexture(JTHIS->text); }
        JCONSTEXPR JCBOOL getBold() JCONST { JRETURN JTHIS->isBold; }
        JINLINE JCVOID setItalic(JCBOOL italic) { JTHIS->isItalic = italic; JTHIS->setTextTexture(JTHIS->text); }
        JCONSTEXPR JCBOOL getItalic() JCONST { JRETURN JTHIS->isItalic; }
        JINLINE JCVOID setValign(JDM::Font::Valign valign) { JTHIS->valign = valign; }
        JCONSTEXPR JDM::Font::Valign getValign() JCONST { JRETURN JTHIS->valign; }
        JINLINE JCVOID setHalign(JDM::Font::Halign halign) { JTHIS->halign = halign; }
        JCONSTEXPR JDM::Font::Halign getHalign() JCONST { JRETURN JTHIS->halign; }

        JINLINE JCVOID setPaddingWidth(JCDOUBLE padWidth) { JTHIS->paddingWidth = padWidth; }
        JCONSTEXPR JCDOUBLE getPaddingWidth() JCONST { JRETURN JTHIS->paddingWidth; }
        JINLINE JCVOID setPaddingHeight(JCDOUBLE padHeight) { JTHIS->paddingHeight = padHeight; }
        JCONSTEXPR JCDOUBLE getPaddingHeight() JCONST { JRETURN JTHIS->paddingHeight; }

        JINLINE JCVOID setRForeGround(JUINT8 c) { JTHIS->rectColor.r = c; }
        JINLINE JCVOID setGForeGround(JUINT8 c) { JTHIS->rectColor.g = c; }
        JINLINE JCVOID setBForeGround(JUINT8 c) { JTHIS->rectColor.b = c; }
        JINLINE JCVOID setAForeGround(JUINT8 c) { JTHIS->rectColor.a = c; }

        JUINT8 getRForeGround() { JRETURN JTHIS->rectColor.r; }
        JUINT8 getGForeGround() { JRETURN JTHIS->rectColor.g; }
        JUINT8 getBForeGround() { JRETURN JTHIS->rectColor.b; }
        JUINT8 getAForeGround() { JRETURN JTHIS->rectColor.a; }

        JINLINE SDL_Texture *getTexture() { JRETURN JTHIS->textTexture; }

        JINLINE JCVOID setForeGroundColor(ColorRGBA color) { JTHIS->rectColor = color; }
        JINLINE JCVOID updateForeGroundColor() {
            SDL_SetTextureColorMod(JTHIS->textTexture, JTHIS->rectColor.r, JTHIS->rectColor.g, JTHIS->rectColor.b);
            SDL_SetTextureAlphaMod(JTHIS->textTexture, JTHIS->rectColor.a);
        }
        JCONSTEXPR ColorRGBA getForeGroundColor() JCONST { JRETURN JTHIS->rectColor; }
        JCONSTEXPR SDL_FRect getTextRectDes() JCONST { JRETURN JTHIS->rect; }

        JINLINE JUINT8 *getPointerRForeGround() { JRETURN &JTHIS->rectColor.r; }
        JINLINE JUINT8 *getPointerGForeGround() { JRETURN &JTHIS->rectColor.g; }
        JINLINE JUINT8 *getPointerBForeGround() { JRETURN &JTHIS->rectColor.b; }
        JINLINE JUINT8 *getPointerAForeGround() { JRETURN &JTHIS->rectColor.a; }

        JINLINE JVIRTUAL JCSTR getName() JCONST { JRETURN "Text"; }

        JINLINE JCVOID update() JOVERRIDE {
            JTHIS->setRect();
            JTHIS->updateForeGroundColor();
        }
        JINLINE JCVOID renderComp() JOVERRIDE {
            SDL_RenderCopyF(JDM::renderer, JTHIS->textTexture, JNULLPTR, &JTHIS->rect);
            
        }
        JFRIEND JCLASS Label;
    };

    JCLASS Label : JPUBLIC Text{
    JPRIVATE:

        SDL_Texture *imageTexture;
        SDL_FRect rectImage;
        SDL_Rect rectSource;
        JSTR sourceFiles;
        ColorRGBA rectImageColor;
        JINT arcTL = 0, arcTR = 0, arcBL = 0, arcBR = 0;
        ColorRGBA startColor = {0, 0, 0, 0};
        ColorRGBA endColor = {0, 0, 0, 0};

        JINT lineWidth = 0;
        Gradient gradientAlignment = NONE;

        JINLINE JCVOID setImageRect() {
            JTHIS->rectImage.w = JTHIS->getWidth();
            JTHIS->rectImage.h = JTHIS->getHeight();
            JTHIS->rectImage.x = JTHIS->getX();
            JTHIS->rectImage.y = JTHIS->getY();
        }

        JINLINE JCVOID setTexture(JCSTR &source) {
            JTHIS->imageTexture = JDM::loadRoundedTexture(JDM::renderer,
                JSTATICC<JINT>(JTHIS->getWidth()), JSTATICC<JINT>(JTHIS->getHeight()), source,
                JTHIS->arcTL, JTHIS->arcTR, JTHIS->arcBL, JTHIS->arcBR, JTHIS->lineWidth);

            JTHIS->rectSource.x = 0;
            JTHIS->rectSource.y = 0;
            SDL_QueryTexture(JTHIS->imageTexture, JNULLPTR, JNULLPTR, &JTHIS->rectSource.w, &JTHIS->rectSource.h);
            SDL_SetTextureBlendMode(JTHIS->imageTexture, SDL_BLENDMODE_BLEND);
            SDL_SetTextureScaleMode(JTHIS->imageTexture, SDL_ScaleModeLinear);
        }

    JPUBLIC:
        Label(JCSTR &text = "", JCSTR &source = "", JCDOUBLE xPos = 0, JCDOUBLE yPos = 0,
              JCDOUBLE Width = 100, JCDOUBLE Height = 100,
              ColorRGBA color = {255, 255, 255, 255},
              ColorRGBA colorImage = {100, 100, 100, 255},
              JCINT arc = 0, JCINT fontS = 15,
              JDM::Font::Halign hAlign = JDM::Font::HCENTER,
              JDM::Font::Valign vAlign = JDM::Font::VCENTER)
            : arcTL(arc), arcTR(arc), arcBL(arc), arcBR(arc),
            Text(text, xPos, yPos, Width, Height, color, fontS, hAlign, vAlign) {

            JTHIS->setSource(source);
            JTHIS->setColor(colorImage);
            JTHIS->setImageRect();
            JTHIS->setRect();
            JTHIS->renderComp();
        }
        JINLINE JCVOID setSource(JCSTR &source) {
            JIF (isFileExist(source)) {
                JTHIS->sourceFiles = source;
                JTHIS->setTexture(JTHIS->sourceFiles);
            } JELSE { 
                JTHIS->sourceFiles = DefaultImage;
                JTHIS->setTexture(DefaultImage);
            }
        }
        JINLINE JCVOID setColor(ColorRGBA color) { JTHIS->rectImageColor = color; }
        JINLINE JCVOID updateColor() {
            SDL_SetTextureColorMod(JTHIS->imageTexture, JTHIS->rectImageColor.r, JTHIS->rectImageColor.g, JTHIS->rectImageColor.b);
            SDL_SetTextureAlphaMod(JTHIS->imageTexture, JTHIS->rectImageColor.a);
            JTHIS->updateForeGroundColor();
        }
        JCONSTEXPR ColorRGBA getColor() JCONST { JRETURN JTHIS->rectImageColor; }
        JINLINE JCVOID setRImage(JUINT8 c) { JTHIS->rectImageColor.r = c; }
        JINLINE JCVOID setGImage(JUINT8 c) { JTHIS->rectImageColor.g = c; }
        JINLINE JCVOID setBImage(JUINT8 c) { JTHIS->rectImageColor.b = c; }
        JINLINE JCVOID setAImage(JUINT8 c) { JTHIS->rectImageColor.a = c; }
        JINLINE JCVOID setLineWidth(JUINT8 c) { JTHIS->lineWidth = c; }

        JUINT8 getRImage() { JRETURN JTHIS->rectImageColor.r; }
        JUINT8 getGImage() { JRETURN JTHIS->rectImageColor.g; }
        JUINT8 getBImage() { JRETURN JTHIS->rectImageColor.b; }
        JUINT8 getAImage() { JRETURN JTHIS->rectImageColor.a; }
        JUINT8 getLineWidth() { JRETURN JTHIS->lineWidth; }

        JINLINE JUINT8 *getPointerRImage() { JRETURN &JTHIS->rectImageColor.r; }
        JINLINE JUINT8 *getPointerGImage() { JRETURN &JTHIS->rectImageColor.g; }
        JINLINE JUINT8 *getPointerBImage() { JRETURN &JTHIS->rectImageColor.b; }
        JINLINE JUINT8 *getPointerAImage() { JRETURN &JTHIS->rectImageColor.a; }

        JINLINE JCVOID setArc(JINT c) {
                JTHIS->arcTL = c;
                JTHIS->arcTR = c;
                JTHIS->arcBL = c;
                JTHIS->arcBR = c;
                JTHIS->setTexture(JTHIS->sourceFiles); }
        JINLINE JCVOID setArcTL(JINT c) { JTHIS->arcTL = c; JTHIS->setTexture(JTHIS->sourceFiles); }
        JINLINE JCVOID setArcTR(JINT c) { JTHIS->arcTR = c; JTHIS->setTexture(JTHIS->sourceFiles); }
        JINLINE JCVOID setArcBL(JINT c) { JTHIS->arcBL = c; JTHIS->setTexture(JTHIS->sourceFiles); }
        JINLINE JCVOID setArcBR(JINT c) { JTHIS->arcBR = c; JTHIS->setTexture(JTHIS->sourceFiles); }

        JINLINE JINT getArcTL(JINT c) { JRETURN JTHIS->arcTL; }
        JINLINE JINT getArcTR(JINT c) { JRETURN JTHIS->arcTR; }
        JINLINE JINT getArcBL(JINT c) { JRETURN JTHIS->arcBL; }
        JINLINE JINT getArcBR(JINT c) { JRETURN JTHIS->arcBR; }

        JINLINE JINT *getPointerArcTL() { JRETURN &JTHIS->arcTL; }
        JINLINE JINT *getPointerArcTR() { JRETURN &JTHIS->arcTR; }
        JINLINE JINT *getPointerArcBL() { JRETURN &JTHIS->arcBL; }
        JINLINE JINT *getPointerArcBR() { JRETURN &JTHIS->arcBR; }

        JINLINE JCSTR getSource() { JRETURN JTHIS->sourceFiles; }
        JINLINE JCVOID setRegion(Region region) { JTHIS->rectSource = { region.x, region.y, region.w, region.h }; }
        JINLINE JCONST Region getRegion() { JRETURN { JTHIS->rectSource.x, JTHIS->rectSource.y, JTHIS->rectSource.w, JTHIS->rectSource.h }; }
        JINLINE JVIRTUAL JCSTR getName() JCONST { JRETURN "Label"; }
        JINLINE JUINT8 interpolateColorComponent(JUINT8 startComponent, JUINT8 endComponent, JINT y, JINT height) {
            JRETURN startComponent + ((endComponent - startComponent) * y) / height;
        }
        JINLINE JCVOID setGradient(Gradient grad) { JTHIS->gradientAlignment = grad; }
        JINLINE JCVOID setGradiendColor(ColorRGBA first, ColorRGBA second) {
            JTHIS->startColor = first;
            JTHIS->endColor = second;
        }

        JINLINE JCVOID update() JOVERRIDE {
            JTHIS->setRect();
            JTHIS->setImageRect();
            JTHIS->updateColor();
        }
        JINLINE JCVOID renderComp() JOVERRIDE {
            SDL_RenderCopyF(JDM::renderer, JTHIS->imageTexture, &JTHIS->rectSource, &JTHIS->rectImage);
            SDL_RenderCopyF(JDM::renderer, JTHIS->textTexture, JNULLPTR, &JTHIS->rect);
            JIF (JTHIS->gradientAlignment == VERTICAL) {
                JFOR (JINT y = 0; y < JTHIS->getHeight(); y++) {
                    JUINT8 r = JTHIS->interpolateColorComponent(JTHIS->startColor.r, JTHIS->endColor.r, y, JTHIS->getHeight());
                    JUINT8 g = JTHIS->interpolateColorComponent(JTHIS->startColor.g, JTHIS->endColor.g, y, JTHIS->getHeight());
                    JUINT8 b = JTHIS->interpolateColorComponent(JTHIS->startColor.b, JTHIS->endColor.b, y, JTHIS->getHeight());
                    JUINT8 a = JTHIS->interpolateColorComponent(JTHIS->startColor.a, JTHIS->endColor.a, y, JTHIS->getHeight());

                    SDL_SetRenderDrawBlendMode(JDM::renderer, SDL_BLENDMODE_BLEND);
                    SDL_SetRenderDrawColor(JDM::renderer, r, g, b, a);
                    SDL_RenderDrawLine(JDM::renderer, JTHIS->getX(), JTHIS->getY() + y, JTHIS->getX() + JTHIS->getWidth(), JTHIS->getY() + y);
                    SDL_SetRenderDrawBlendMode(JDM::renderer, SDL_BLENDMODE_NONE);
                }
            } JELSE JIF (JTHIS->gradientAlignment == HORIZONTAL) {
                JFOR (JINT x = 0; x < JTHIS->getWidth(); x++) {
                    JUINT8 r = JTHIS->interpolateColorComponent(JTHIS->startColor.r, JTHIS->endColor.r, x, JTHIS->getHeight());
                    JUINT8 g = JTHIS->interpolateColorComponent(JTHIS->startColor.g, JTHIS->endColor.g, x, JTHIS->getHeight());
                    JUINT8 b = JTHIS->interpolateColorComponent(JTHIS->startColor.b, JTHIS->endColor.b, x, JTHIS->getHeight());
                    JUINT8 a = JTHIS->interpolateColorComponent(JTHIS->startColor.a, JTHIS->endColor.a, x, JTHIS->getHeight());

                    SDL_SetRenderDrawBlendMode(JDM::renderer, SDL_BLENDMODE_BLEND);
                    SDL_SetRenderDrawColor(JDM::renderer, r, g, b, a);
                    SDL_RenderDrawLine(JDM::renderer, JTHIS->getX() + x, JTHIS->getY(), JTHIS->getX() + x, JTHIS->getY() + JTHIS->getHeight());
                    SDL_SetRenderDrawBlendMode(JDM::renderer, SDL_BLENDMODE_NONE);
                }
            }
        }
    };
    JCLASS Button : JPUBLIC Label {
    JPRIVATE:
        ColorRGBA originalColor;
        ColorRGBA clickedColor;

        ColorRGBA hoverColor = {75, 75, 75, 255};
        JBOOL clicked = JFALSE;

    JPUBLIC:
        Button(JCSTR &text = "", JCSTR &source = "", JCDOUBLE xPos = 0, JCDOUBLE yPos = 0,
              JCDOUBLE Width = 100, JCDOUBLE Height = 100,
              ColorRGBA color = {255, 255, 255, 255},
              ColorRGBA colorImage = {100, 100, 100, 255},
              ColorRGBA colorImageClicked = {50, 50, 50, 255})
              : clickedColor(colorImageClicked), originalColor(colorImage), Label(text, source, xPos, yPos, Width, Height, color, colorImage) {
            JTHIS->setPickOnBounds(true);
            JTHIS->setPickOnTop(true);
        }
        JINLINE JCBOOL mouseDownComp(SDL_MouseButtonEvent &mouse) {
            JIF (JTHIS->getPickOnBounds()) {
                JIF(JTHIS->getPickOnTop() && JDM::alreadyTouched) JRETURN JFALSE;
                JIF (JTHIS->contains(mouse.x, mouse.y)) {
                    JTHIS->getmouseDownFunction()(mouse);
                    JTHIS->setColor(JTHIS->clickedColor);
                    JTHIS->setMouseClick(JTRUE);
                    JDM::alreadyTouched = JTRUE;
                    JRETURN JTRUE;
                }
            } JRETURN JFALSE;
        }
        JINLINE JCVOID setOriginalColor(ColorRGBA col) {
            JTHIS->originalColor = col;
        }
        JINLINE JCVOID setHoverColor(ColorRGBA col) { JTHIS->hoverColor = col; }
        JINLINE JCVOID mouseUpComp(SDL_MouseButtonEvent &mouse) {
            JIF (JTHIS->getMouseClick()) JTHIS->setColor(JTHIS->originalColor);
            Label::mouseUpComp(mouse);
        }
        JINLINE JCVOID update() {
            Label::update();
            JIF (!JTHIS->getMouseClick())
            JIF (JTHIS->contains(JDM::Mouse::MouseX, JDM::Mouse::MouseY)) {
                JTHIS->setColor(JTHIS->hoverColor);
            } JELSE JTHIS->setColor(JTHIS->originalColor);
        }

    };
    JCLASS FocusedTextComponent : JPUBLIC Label {
    JPUBLIC:
        JBOOL isFocused = JFALSE;
        JINT index = -1;
        FocusedTextComponent(JCSTR &text = "", JCSTR &source = "", JCDOUBLE xPos = 0, JCDOUBLE yPos = 0,
              JCDOUBLE Width = 100, JCDOUBLE Height = 100,
              ColorRGBA color = {255, 255, 255, 255},
              ColorRGBA colorImage = {100, 100, 100, 255})
              : Label(text, source, xPos, yPos, Width, Height, color, colorImage) {
                JTHIS->setPickOnBounds(JTRUE);
                JTHIS->setPickOnTop(JTRUE);
                JTHIS->index = text.size() - 1;
            }
        JINLINE JVIRTUAL JCSTR getName() JCONST { JRETURN "FocusedTextComponent"; }
    };
    JCLASS TextInput : JPUBLIC FocusedTextComponent {
    JPRIVATE:
        JBOOL blinked = JFALSE;
        JDOUBLE blinkDuration = 0.3;
        JDOUBLE currentBlink = blinkDuration;
        Image *imageTexture = JNULLPTR;

    JPUBLIC:
        TextInput(JCSTR &text = "", JCDOUBLE xPos = 0, JCDOUBLE yPos = 0,
              JCDOUBLE Width = 100, JCDOUBLE Height = 100,
              ColorRGBA color = JDM::getColorFromHexA("111111ff"),
              ColorRGBA colorImage = JDM::getColorFromHexA("ccccccff"),
              JCSTR &pathImage = "")
              : FocusedTextComponent(text, DefaultImage, xPos, yPos, Width, Height, color, colorImage) {
                
                JTHIS->setHalign(JDM::Font::LEFT);
                JTHIS->setPaddingWidth(10);
                JTHIS->setBold(JTRUE);
                JTHIS->setFontSize(10);

                JIF (pathImage != "") {
                    imageTexture = JNEW Image(
                        pathImage, JTHIS->getX() + 10,
                        JTHIS->getY() + 10,
                        JTHIS->getHeight() - 20,
                        JTHIS->getHeight() - 20);
                    JTHIS->setPaddingWidth((JTHIS->getHeight() - 20) + 20);
                }
            }
        JINLINE JCVOID update() JOVERRIDE {
            Label::update();
            JIF (JTHIS->imageTexture != JNULLPTR) {
                JTHIS->imageTexture->setX(JTHIS->getX() + 10);
                JTHIS->imageTexture->setY(JTHIS->getY() + 10);
                JTHIS->imageTexture->setWidth(JTHIS->getHeight() - 20);
                JTHIS->imageTexture->setHeight(JTHIS->getHeight() - 20);

                JTHIS->imageTexture->update();
            }
        }
        JINLINE JCVOID renderComp() JOVERRIDE {
            Label::renderComp();
            JTHIS->currentBlink -= JDM::TimeFrame;
            JIF (JTHIS->imageTexture != JNULLPTR) 
                JTHIS->imageTexture->renderComp();

            JIF (JTHIS->isFocused)
                JIF (JTHIS->currentBlink > 0) {
                    JIF (JTHIS->blinked) {
                        SDL_SetRenderDrawColor(JDM::renderer, 0, 0, 0, 255);
                        SDL_RenderDrawLineF(JDM::renderer,
                            JTHIS->getTextRectDes().x+((JTHIS->index+1) * JTHIS->getCopyFontSize()), JTHIS->getTextRectDes().y - 5,
                            JTHIS->getTextRectDes().x+((JTHIS->index+1) * JTHIS->getCopyFontSize()), JTHIS->getTextRectDes().y + JTHIS->getCopyFontSize() + 5);
                        SDL_RenderDrawLineF(JDM::renderer,
                            JTHIS->getTextRectDes().x+((JTHIS->index+1) * JTHIS->getCopyFontSize()) + 1, JTHIS->getTextRectDes().y - 5,
                            JTHIS->getTextRectDes().x+((JTHIS->index+1) * JTHIS->getCopyFontSize()) + 1, JTHIS->getTextRectDes().y + JTHIS->getCopyFontSize() + 5);
                    }
                } JELSE {
                    JTHIS->currentBlink = JTHIS->blinkDuration;
                    JTHIS->blinked = !JTHIS->blinked;
                }
        }
    };
    JNAMESPACE Canvas {
    JCLASS Rectangle : JPUBLIC Components {
    JPRIVATE:
        ColorRGBA rectColor;
        SDL_FRect rect;

        ColorRGBA startColor = {0, 0, 0, 0};
        ColorRGBA endColor = {0, 0, 0, 0};

        Gradient gradientAlignment = NONE;

        JINLINE JCVOID setRect() {
            JTHIS->rect.w = JTHIS->getWidth();
            JTHIS->rect.h = JTHIS->getHeight();
            JTHIS->rect.x = JTHIS->getX();
            JTHIS->rect.y = JTHIS->getY();
        }

    JPUBLIC:
        Rectangle(JCDOUBLE xPos = 0, JCDOUBLE yPos = 0,
          JCDOUBLE Width = 100, JCDOUBLE Height = 100, ColorRGBA color = {255, 255, 255, 255})
          : Components(xPos, yPos, Width, Height), rectColor(color) { }
        
        JINLINE JUINT8 interpolateColorComponent(JUINT8 startComponent, JUINT8 endComponent, JINT y, JINT height) {
            JRETURN startComponent + ((endComponent - startComponent) * y) / height;
        }
        JINLINE JCVOID setGradient(Gradient grad) { JTHIS->gradientAlignment = grad; }
        JINLINE JCVOID setGradiendColor(ColorRGBA first, ColorRGBA second) {
            JTHIS->startColor = first;
            JTHIS->endColor = second;
        }
        JINLINE JCVOID setColor(ColorRGBA color) { JTHIS->rectColor = color; }
        JCONSTEXPR ColorRGBA getColor() JCONST { JRETURN JTHIS->rectColor; }

        JINLINE JCVOID update() JOVERRIDE { JTHIS->setRect(); }
        JINLINE JCVOID renderComp() JOVERRIDE {
            SDL_SetRenderDrawColor(JDM::renderer, JTHIS->rectColor.r, JTHIS->rectColor.g, JTHIS->rectColor.b, JTHIS->rectColor.a);
            SDL_RenderFillRectF(JDM::renderer, &JTHIS->rect);
            JIF (JTHIS->gradientAlignment == VERTICAL) {
                JFOR (JINT y = 0; y < JTHIS->getHeight(); y++) {
                    JUINT8 r = JTHIS->interpolateColorComponent(JTHIS->startColor.r, JTHIS->endColor.r, y, JTHIS->getHeight());
                    JUINT8 g = JTHIS->interpolateColorComponent(JTHIS->startColor.g, JTHIS->endColor.g, y, JTHIS->getHeight());
                    JUINT8 b = JTHIS->interpolateColorComponent(JTHIS->startColor.b, JTHIS->endColor.b, y, JTHIS->getHeight());
                    JUINT8 a = JTHIS->interpolateColorComponent(JTHIS->startColor.a, JTHIS->endColor.a, y, JTHIS->getHeight());

                    SDL_SetRenderDrawBlendMode(JDM::renderer, SDL_BLENDMODE_BLEND);
                    SDL_SetRenderDrawColor(JDM::renderer, r, g, b, a);
                    SDL_RenderDrawLine(JDM::renderer, JTHIS->getX(), JTHIS->getY() + y, JTHIS->getX() + JTHIS->getWidth(), JTHIS->getY() + y);
                    SDL_SetRenderDrawBlendMode(JDM::renderer, SDL_BLENDMODE_NONE);
                }
            } JELSE JIF (JTHIS->gradientAlignment == HORIZONTAL) {
                JFOR (JINT x = 0; x < JTHIS->getWidth(); x++) {
                    JUINT8 r = JTHIS->interpolateColorComponent(JTHIS->startColor.r, JTHIS->endColor.r, x, JTHIS->getHeight());
                    JUINT8 g = JTHIS->interpolateColorComponent(JTHIS->startColor.g, JTHIS->endColor.g, x, JTHIS->getHeight());
                    JUINT8 b = JTHIS->interpolateColorComponent(JTHIS->startColor.b, JTHIS->endColor.b, x, JTHIS->getHeight());
                    JUINT8 a = JTHIS->interpolateColorComponent(JTHIS->startColor.a, JTHIS->endColor.a, x, JTHIS->getHeight());

                    SDL_SetRenderDrawBlendMode(JDM::renderer, SDL_BLENDMODE_BLEND);
                    SDL_SetRenderDrawColor(JDM::renderer, r, g, b, a);
                    SDL_RenderDrawLine(JDM::renderer, JTHIS->getX() + x, JTHIS->getY(), JTHIS->getX() + x, JTHIS->getY() + JTHIS->getHeight());
                    SDL_SetRenderDrawBlendMode(JDM::renderer, SDL_BLENDMODE_NONE);
                }
            }
        }
    };

    JCLASS Circle : JPUBLIC Components {

    JPRIVATE:
        SDL_Texture *circleTexture;
        SDL_FRect rect;
        ColorRGBA rectColor;
        ColorRGBA startColor = {0, 0, 0, 0};
        ColorRGBA endColor = {0, 0, 0, 0};

        Gradient gradientAlignment = NONE;

    JPUBLIC:
        JINLINE JCVOID setRect() {
            JTHIS->rect.x = JTHIS->getX();
            JTHIS->rect.y = JTHIS->getY();
            JTHIS->rect.w = JTHIS->getWidth();
            JTHIS->rect.h = JTHIS->getHeight();
        }
        Circle(JCDOUBLE xPos = 0, JCDOUBLE yPos = 0,
          JCDOUBLE xPos2 = 100, JCDOUBLE yPos2 = 100, ColorRGBA color = {255, 255, 255, 255})
          : Components(xPos, yPos, xPos2, yPos2), rectColor(color) {
            JTHIS->circleTexture = IMG_LoadTexture(JDM::renderer, CircleImage.c_str());
            SDL_SetTextureBlendMode(JTHIS->circleTexture, SDL_BLENDMODE_BLEND);
            SDL_SetTextureScaleMode(JTHIS->circleTexture, SDL_ScaleModeLinear);
            JTHIS->setColor();
        }
        JINLINE JUINT8 interpolateColorComponent(JUINT8 startComponent, JUINT8 endComponent, JINT y, JINT height) {
            JRETURN startComponent + ((endComponent - startComponent) * y) / height;
        }
        JINLINE JCVOID setGradient(Gradient grad) { JTHIS->gradientAlignment = grad; }
        JINLINE JCVOID setGradiendColor(ColorRGBA first, ColorRGBA second) {
            JTHIS->startColor = first;
            JTHIS->endColor = second;
        }
        JINLINE JCVOID setColor() { 
            SDL_SetTextureColorMod(JTHIS->circleTexture, JTHIS->rectColor.r, JTHIS->rectColor.g, JTHIS->rectColor.b);
            SDL_SetTextureAlphaMod(JTHIS->circleTexture, JTHIS->rectColor.a);
        }
        JINLINE JCVOID update() { JTHIS->setRect(); }
        JINLINE JCVOID renderComp() {
            SDL_RenderCopyF(JDM::renderer, JTHIS->circleTexture, JNULLPTR, &JTHIS->rect);
        }
    };

    JCLASS Line : JPUBLIC Components {
    JPRIVATE:
        ColorRGBA rectColor;

    JPUBLIC:
        Line(JCDOUBLE xPos = 0, JCDOUBLE yPos = 0,
          JCDOUBLE xPos2 = 100, JCDOUBLE yPos2 = 100, ColorRGBA color = {255, 255, 255, 255})
          : Components(xPos, yPos, xPos2, yPos2), rectColor(color) { }

        JINLINE JCVOID setColor(ColorRGBA color) { JTHIS->rectColor = color; }
        JCONSTEXPR ColorRGBA getColor() JCONST { JRETURN JTHIS->rectColor; }

        JINLINE JCVOID renderComp() JOVERRIDE {
            SDL_SetRenderDrawColor(JDM::renderer, JTHIS->rectColor.r, JTHIS->rectColor.g, JTHIS->rectColor.b, JTHIS->rectColor.a);
            SDL_RenderDrawLineF(JDM::renderer, JTHIS->getX(), JTHIS->getY(), JTHIS->getWidth(), JTHIS->getHeight());
        }
    };
}}};

#endif