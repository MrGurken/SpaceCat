#if !defined(WIN32_SPACECAT_H)
/* ========================================================================
   $File: $
   $Date: $
   $Revision: $
   $Creator: Tunder $
   $Notice: (C) Copyright 2014 by SpaceCat, Inc. All Rights Reserved. $
   ======================================================================== */

#include <GL\gl3.h>
#include <stdint.h>

typedef int32_t bool32_t;
typedef float real32_t;
typedef double real64_t;

#include "maths.h"
#include "render.h"

struct PlatformFile
{
    void* content;
    int32_t size;
};

#define FONT_ITALIC 0x1
#define FONT_UNDERLINE 0x2
#define FONT_STRIKEOUT 0x4
struct PlatformFont
{
    GLuint id;
    int32_t size;
    int32_t range;
    int32_t weight;
    int8_t style;
};

#define INPUT_MAX_KEYS 128
#define INPUT_MAX_BUTTONS 2
#define INPUT_LBUTTON 0
#define INPUT_RBUTTON 1
struct PlatformInput
{
    uint8_t keys[INPUT_MAX_KEYS];
    uint8_t prevKeys[INPUT_MAX_KEYS];
    uint8_t buttons[INPUT_MAX_BUTTONS];
    uint8_t prevButtons[INPUT_MAX_BUTTONS];
    Vec2 mousePosition;
    Vec2 mouseDelta;
    int32_t wheel;
    int32_t prevWheel;
};

#define WIN32_SPACECAT_H
#endif
