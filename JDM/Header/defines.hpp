#pragma once
#ifndef JDM_DEFINES
#define JDM_DEFINES

#include "include.hpp"

#define JNONE 0
#define JTRUE 1
#define JFALSE 0
#define JNULL NULL
#define JNULLPTR nullptr

#define JCONST const
#define JNEW new
#define JFOR for
#define JBREAK break
#define JCONTINUE continue
#define JRETURN return
#define JIF if
#define JELSE else
#define JTHIS this
#define JDELETE delete
#define JWHILE while
#define JDO do
#define JSTRUCT struct
#define JCLASS class
#define JENUM enum
#define JUNION union
#define JSWITCH switch
#define JCASE case
#define JDEFAULT default
#define JCONSTEXPR constexpr
#define JINLINE inline
#define JVIRTUAL virtual
#define JSTATIC static
#define JFRIEND friend
#define JNAMESPACE namespace
#define JTEMPLATE template
#define JTYPENAME typename
#define JUSING using
#define JAUTO auto
#define JEXTERN extern
#define JPUBLIC public
#define JPRIVATE private
#define JPROTECTED protected
#define JOVERRIDE override

#define JSTATICC static_cast
#define JDYNAMICC dynamic_cast
#define JREINTERPRETC reinterpret_cast
#define JEXIT std::exit

#define JDM_UNDEFINED_POS 30
#define JDM_UNDEFINED_SIZE 100

#define Random rand
#define SRand std::srand
const std::string JDMImage = "Assets/Image/JDM.png";
const std::string DefaultImage = "Assets/Image/default.png";
const std::string RoundedImage = "Assets/Image/rounded_rectangle.png";
const std::string RoundedImage90 = "Assets/Image/rounded90.png";
const std::string RoundedImage180 = "Assets/Image/rounded180.png";
const std::string CircleImage = "Assets/Image/circle.png";

template <class T> using JFUNCTION = std::function<T>;
void typedef JVOID;
const void typedef JCVOID;

bool typedef JBOOL;
short typedef JSHORT;
int typedef JINT;
long typedef JLONG;
long long typedef JLLONG;
float typedef JFLOAT;
double typedef JDOUBLE;
char typedef JCHAR;
wchar_t typedef JWCHAR;

unsigned short typedef JUSHORT;
unsigned int typedef JUINT;
unsigned long typedef JULONG;
unsigned long long typedef JULLONG;
unsigned char typedef JUCHAR;

unsigned char typedef JUINT8;
unsigned short typedef JUINT16;
unsigned int typedef JUINT32;
unsigned long typedef JUINT64;

std::string typedef JSTR;
std::wstring typedef JWSTR;

const bool typedef JCBOOL;
const short typedef JCSHORT;
const int typedef JCINT;
const long typedef JCLONG;
const long long typedef JCLLONG;
const float typedef JCFLOAT;
const double typedef JCDOUBLE;
const char typedef JCCHAR;
const wchar_t typedef JCWCHAR;

const unsigned short typedef JCUSHORT;
const unsigned int typedef JCUINT;
const unsigned long typedef JCULONG;
const unsigned long long typedef JCULLONG;
const unsigned char typedef JCUCHAR;

const unsigned char typedef JCUINT8;
const unsigned short typedef JCUINT16;
const unsigned int typedef JCUINT32;
const unsigned long typedef JCUINT64;

const std::string typedef JCSTR;
const std::wstring typedef JCWSTR;

struct Position { double x, y; };
struct Size { double width, height; };
struct SizePos {
    union {
        struct { double x, y, width, height; };
        struct { Position pos; Size size; };
    };
};
struct Region { int x, y, w, h; };

struct ColorRGB { uint8_t r, g, b; };
struct ColorRGBA {
    union {
        struct { uint8_t r, g, b, a; };
        struct { ColorRGB color; uint8_t opacity; };
    };
};
enum Gradient { NONE, VERTICAL, HORIZONTAL };

template <class T> JWSTR JTOWSTR(T Expression) { return std::to_wstring(Expression); }
template <class T> JSTR JTOSTR(T Expression) { return std::to_string(Expression); }

template <class T> using JUP = std::unique_ptr<T>;
#define JUP std::make_unique
template <class T, class S> using JPAIR = std::pair<T, S>;
#define JMPAIR std::make_pair

template <class T> using JSP = std::shared_ptr<T>;
#define JMS std::make_shared

template <class T> using JVECTOR = std::vector<T>;
template <class T> using JSET = std::set<T>;
template <class T> using JSTACK = std::stack<T>;
template <class T> using JQUEUE = std::queue<T>;
template <class T> using JLIST = std::list<T>;
template <class T, class C> using JMAP = std::map<T, C>;
void Sleep(unsigned long milliseconds) { std::this_thread::sleep_for(std::chrono::milliseconds(milliseconds)); }

inline bool isFileExist(const std::string &file) {
    std::ifstream ifile;
    ifile.open(file);
    bool res = (ifile) ? true : false;
    ifile.close();
    return res;
}

using funcCallback = std::function<void()>;
using funcMouseCallBack = std::function<void(SDL_MouseButtonEvent &mouse)>;
using funcMotionCallBack = std::function<void(SDL_MouseMotionEvent &mouse)>;
inline bool operator==(const std::string &str, const std::string &str2) { return !(str.compare(str2)); }
inline bool operator!=(const std::string &str, const std::string &str2) { return (str.compare(str2)); }

std::string subtractCharAtIndex(std::string str, int index) {
    if (index >= 0 && index < str.length()) {
        str.erase(index, 1);
        return str;
    } else return str;
}

std::string addCharAtIndex(std::string str, int index, const std::string &ch) {
    if (index >= 0 && index <= str.size())
        str.insert(index, ch);
    return str;
}

namespace JDM {
    inline ColorRGB getColorFromHex(JCSTR& hexColor) {
        ColorRGB color;
        JCSTR colorString = (hexColor[0] == '#') ? hexColor.substr(1) : hexColor;

        std::istringstream iss(colorString);
        JUINT hexValue;
        iss >> std::hex >> hexValue;

        color.r = (hexValue >> 16) & 0xFF;
        color.g = (hexValue >> 8) & 0xFF;
        color.b = hexValue & 0xFF;

        return color;
    }

    inline ColorRGBA getColorFromHexA(JCSTR& hexColor) {
        ColorRGBA color;
        JCSTR colorString = (hexColor[0] == '#') ? hexColor.substr(1) : hexColor;

        std::istringstream iss(colorString);
        JUINT hexValue;
        iss >> std::hex >> hexValue;

        color.r = (hexValue >> 24) & 0xFF;
        color.g = (hexValue >> 16) & 0xFF;
        color.b = (hexValue >> 8) & 0xFF;
        color.a = hexValue & 0xFF;

        return color;
    }

    // PS: THIS IS MY CODE, I COME UP WITH IT ON MY OWN
    SDL_Texture* loadRoundedTexture(SDL_Renderer* renderer, int width, int height, const std::string& path,
                               int tlSize, int trSize, int blSize, int brSize, int lineWidth = 0) {
        SDL_Surface* originalSurface = IMG_Load(path.c_str());

        if (!originalSurface) {
            SDL_Log("Failed to load image: %s", IMG_GetError());
            return nullptr;
        }

        if (tlSize == 0 && trSize == 0 && blSize == 0 && brSize == 0 && lineWidth == 0) {
            SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, originalSurface);
            SDL_FreeSurface(originalSurface);
            return texture;
        }

        SDL_Surface* resizedSurface = SDL_CreateRGBSurfaceWithFormat(0, width, height, 32, SDL_PIXELFORMAT_RGBA32);
        if (!resizedSurface) {
            SDL_Log("Failed to create new surface: %s", SDL_GetError());
            SDL_FreeSurface(originalSurface);
            return nullptr;
        }

        if (SDL_BlitScaled(originalSurface, nullptr, resizedSurface, nullptr) != 0) {
            SDL_Log("Failed to resize surface: %s", SDL_GetError());
            SDL_FreeSurface(originalSurface);
            SDL_FreeSurface(resizedSurface);
            return nullptr;
        }

        Uint32 transparentColor = SDL_MapRGBA(resizedSurface->format, 0, 0, 0, 0);
        SDL_SetSurfaceBlendMode(resizedSurface, SDL_BLENDMODE_BLEND);
        auto modifyCorner = [&resizedSurface, lineWidth, transparentColor](int addX, int addY, int size,
                                                                int startX, int startY, int endX, int endY) {
            for (int y = startY; y < endY; ++y) {
                for (int x = startX; x < endX; ++x) {
                    int dx = x - size;
                    int dy = y - size;
                    int distance = std::sqrt(dx * dx + dy * dy);
                    if (distance > size || ((lineWidth > 0) ? (distance < size - lineWidth) : false)) {

                        Uint32* pixel = reinterpret_cast<Uint32*>(reinterpret_cast<Uint8*>(resizedSurface->pixels)
                                                                    + (addY + y) * resizedSurface->pitch
                                                                    + (addX + x) * resizedSurface->format->BytesPerPixel);
                        *pixel = transparentColor;
                    }
                }
            }
        };

        if (lineWidth > 0) {
            for (int x = tlSize; x < resizedSurface->w - trSize; ++x) {
                for (int y = lineWidth; y < resizedSurface->h - lineWidth; ++y) {
                    Uint32* pixel = reinterpret_cast<Uint32*>(reinterpret_cast<Uint8*>(resizedSurface->pixels)
                                                                    + y * resizedSurface->pitch
                                                                    + x * resizedSurface->format->BytesPerPixel);
                        *pixel = transparentColor;
                }
            }
            for (int x = lineWidth; x < resizedSurface->w - lineWidth; ++x) {
                for (int y = blSize; y < resizedSurface->h - brSize; ++y) {
                    Uint32* pixel = reinterpret_cast<Uint32*>(reinterpret_cast<Uint8*>(resizedSurface->pixels)
                                                                    + y * resizedSurface->pitch
                                                                    + x * resizedSurface->format->BytesPerPixel);
                        *pixel = transparentColor;
                }
            }
        }

        if (tlSize) modifyCorner(0, 0, tlSize, 0, 0, tlSize, tlSize);
        if (trSize) modifyCorner(resizedSurface->w - trSize * 2, 0, trSize, trSize, 0, trSize * 2, trSize);
        if (blSize) modifyCorner(0, resizedSurface->h - blSize * 2, blSize, 0, blSize, blSize, blSize * 2);
        if (brSize) modifyCorner(resizedSurface->w - brSize * 2, resizedSurface->h - brSize * 2, brSize, brSize, brSize, brSize * 2, brSize * 2);

        SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, resizedSurface);
        SDL_FreeSurface(originalSurface);
        SDL_FreeSurface(resizedSurface);
        return texture;
    }

    // bool stringToDouble(const std::string& str) {
    // try {
    //     size_t pos = 0;
    //     std::stod(str, &pos);
    //     pos == str.length();  // Returns true if the entire string was successfully converted
    // } catch (...) {
    //     return false;  // Exception occurred, indicating the string is not a floating-point number
    // }
// }

    
};
#endif