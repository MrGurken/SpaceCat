#if !defined(WIN32_SPACECAT_H)
/* ========================================================================
   $File: $
   $Date: $
   $Revision: $
   $Creator: Tunder $
   $Notice: (C) Copyright 2014 by SpaceCat, Inc. All Rights Reserved. $
   ======================================================================== */

#include <windows.h>
#include <windowsx.h>
#include "GL\glew.h"
#include "GL\wglew.h"
#include <stdint.h>

typedef int32_t bool32_t;
typedef float real32_t;
typedef double real64_t;

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
    //Vec2 mousePosition;
    //Vec2 mouseDelta;
    int32_t wheel;
    int32_t prevWheel;
};

typedef WNDCLASS Win32DefaultWindowClass_t( const char*, HINSTANCE );
typedef bool32_t Win32CreateRenderContext_t( HDC, HGLRC* );
typedef bool32_t Win32ReadFile_t( PlatformFile*, const char* );
typedef bool32_t Win32WriteFile_t( const char*, void*, int32_t );
typedef void Win32FreeFile_t( PlatformFile* );
typedef bool32_t Win32ReadFont_t( HDC, PlatformFont*, const char* );
typedef uint64_t Win32GetPerformanceFrequency_t();
typedef uint64_t Win32GetClock_t();
typedef uint64_t Win32GetLastWriteTime_t( const char* );
typedef real32_t Win32GetSecondsElapsed_t( uint64_t, uint64_t );
typedef bool32_t Win32ProcessKeyboard_t( PlatformInput*, MSG* );
typedef bool32_t Win32ProcessMouse_t( PlatformInput*, MSG* );
typedef bool32_t Win32ProcessInput_t( PlatformInput*, MSG* );

struct SpaceCatDLL
{
    HMODULE module;
    WNDPROC Win32DefaultWindowProcedure;
    Win32DefaultWindowClass_t* Win32DefaultWindowClass;
    Win32CreateRenderContext_t* Win32CreateRenderContext;
    Win32ReadFile_t* Win32ReadFile;
    Win32WriteFile_t* Win32WriteFile;
    Win32FreeFile_t* Win32FreeFile;
    Win32ReadFont_t* Win32ReadFont;
    Win32GetPerformanceFrequency_t* Win32GetPerformanceFrequency;
    Win32GetClock_t* Win32GetClock;
    Win32GetLastWriteTime_t* Win32GetLastWriteTime;
    Win32GetSecondsElapsed_t* Win32GetSecondsElapsed;
    Win32ProcessKeyboard_t* Win32ProcessKeyboard;
    Win32ProcessMouse_t* Win32ProcessMouse;
    Win32ProcessInput_t* Win32ProcessInput;
};

#define WIN32_SPACECAT_H
#endif
