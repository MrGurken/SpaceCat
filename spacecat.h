#if !defined(SPACECAT_H)
/* ========================================================================
   $File: $
   $Date: $
   $Revision: $
   $Creator: Tunder $
   $Notice: (C) Copyright 2014 by SpaceCat, Inc. All Rights Reserved. $
   ======================================================================== */

#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

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

#define FUNCTION_PERFORMANCE_FREQUENCY(name) uint64_t name()
#define FUNCTION_GET_CLOCK(name) uint64_t name()
#define FUNCTION_GET_SECONDS_ELAPSED(name) real32_t name( uint64_t start, uint64_t )
#define FUNCTION_GET_LAST_WRITE_TIME(name) uint64_t name( const char* filename )
#define FUNCTION_READ_FILE(name) bool32_t name( PlatformFile* buffer, const char* filename )
#define FUNCTION_WRITE_FILE(name) bool32_t name( const char* filename, void* content, int32_t size )
#define FUNCTION_FREE_FILE(name) void name( PlatformFile* buffer )
// TODO: HDC is not crossplatform
#define FUNCTION_READ_FONT(name) bool32_t name( HDC deviceContext, PlatformFont* font, const char* fontname )

FUNCTION_GET_CLOCK( Win32GetClock );
FUNCTION_GET_SECONDS_ELAPSED( Win32GetSecondsElapsed );
FUNCTION_GET_LAST_WRITE_TIME( Win32GetLastWriteTime );
FUNCTION_READ_FILE( Win32ReadFile );
FUNCTION_WRITE_FILE( Win32WriteFile );
FUNCTION_FREE_FILE( Win32FreeFile );
FUNCTION_READ_FONT( Win32ReadFont );

typedef FUNCTION_GET_CLOCK( GetClock_t );
typedef FUNCTION_GET_SECONDS_ELAPSED( GetSecondsElapsed_t );
typedef FUNCTION_GET_LAST_WRITE_TIME( GetLastWriteTime_t );
typedef FUNCTION_READ_FILE( ReadFile_t );
typedef FUNCTION_WRITE_FILE( WriteFile_t );
typedef FUNCTION_FREE_FILE( FreeFile_t );
typedef FUNCTION_READ_FONT( ReadFont_t );

struct PlatformIO
{
    GetClock_t* GetClock;
    GetSecondsElapsed_t* GetSecondsElapsed;
    GetLastWriteTime_t* GetLastWriteTime;
    ReadFile_t* ReadFile;
    WriteFile_t* WriteFile;
    FreeFile_t* FreeFile;
    ReadFont_t* ReadFont;
};

#define FUNCTION_UPDATE(name) bool32_t name( PlatformIO* io, PlatformInput* input )
#define FUNCTION_RENDER(name) void name()

typedef FUNCTION_UPDATE(UpdateFunction_t);
typedef FUNCTION_RENDER(RenderFunction_t);

struct SpaceCat
{
#ifdef WIN32
    const char* windowClassName;
    HINSTANCE hInstance;
#endif
    const char* title;
    int windowX, windowY;
    int windowWidth, windowHeight;
    
    int fps;
    UpdateFunction_t* UpdateFunction;
    RenderFunction_t* RenderFunction;
};

void scDefaultRuntime( SpaceCat* runtime );
int scRun( SpaceCat* runtime );

#define SPACECAT_H
#endif
