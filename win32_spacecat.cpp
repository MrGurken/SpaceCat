/* ========================================================================
   $File: $
   $Date: $
   $Revision: $
   $Creator: Tunder $
   $Notice: (C) Copyright 2014 by SpaceCat, Inc. All Rights Reserved. $
   ======================================================================== */
#include "win32_spacecat.h"

typedef int32_t bool32_t;
typedef float real32_t;
typedef double real64_t;

static int64_t g_perfCounterFreq;

extern "C" uint64_t Win32GetPerformanceFrequency()
{
    LARGE_INTEGER result;
    QueryPerformanceFrequency( &result );
    g_perfCounterFreq = result.QuadPart;
    return g_perfCounterFreq;
}

extern "C" uint64_t Win32GetClock()
{
    LARGE_INTEGER result;
    QueryPerformanceCounter( &result );
    return result.QuadPart;
}

extern "C" real32_t Win32GetSecondsElapsed( uint64_t start, uint64_t end )
{
    real32_t result = ((real32_t)( end - start ) / (real32_t)g_perfCounterFreq );
    return result;
}

extern "C" uint64_t Win32GetLastWriteTime( const char* filename )
{
    uint64_t result = 0;

    WIN32_FIND_DATA findData;
    HANDLE file = FindFirstFile( filename, &findData );
    if( file )
    {
        result = ( (uint64_t)findData.ftLastWriteTime.dwHighDateTime << 32 ) | findData.ftLastWriteTime.dwLowDateTime;
        FindClose( file );
    }

    return result;
}

extern "C" LRESULT CALLBACK Win32DefaultWindowProcedure( HWND windowHandle,
                                                         UINT message,
                                                         WPARAM w,
                                                         LPARAM l )
{
    LRESULT result = 0;

    switch( message )
    {
        case WM_DESTROY:
            PostQuitMessage( 0 );
            break;

        default:
            result = DefWindowProc( windowHandle, message, w, l );
            break;
    }
    
    return result;
}

extern "C" WNDCLASS Win32DefaultWindowClass( const char* className, HINSTANCE hInstance )
{
    WNDCLASS result = {};
    result.lpszClassName = className;
    result.lpfnWndProc = Win32DefaultWindowProcedure;
    result.hInstance = hInstance;
    result.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
    result.hCursor = LoadCursor( 0, IDC_ARROW );

    return result;
}

extern "C" bool32_t Win32CreateRenderContext( HDC deviceContext, HGLRC* renderContext )
{
    bool32_t result = false;

    PIXELFORMATDESCRIPTOR pfd =
    {
        sizeof( PIXELFORMATDESCRIPTOR ),
        1,
        PFD_SUPPORT_OPENGL |
        PFD_DRAW_TO_WINDOW |
        PFD_DOUBLEBUFFER,
        PFD_TYPE_RGBA,
        16,
        0, 0, 0, 0, 0, 0,
        0, 0, 0,
        0, 0, 0, 0,
        16,
        0, 0,
        PFD_MAIN_PLANE,
        0, 0, 0, 0
    };

    int compatibleFormat = ChoosePixelFormat( deviceContext, &pfd );
    if( compatibleFormat > 0 )
    {
        SetPixelFormat( deviceContext, compatibleFormat, &pfd );
        *renderContext = wglCreateContext( deviceContext );
        wglMakeCurrent( deviceContext, *renderContext );

        result = true;
    }

    return result;
}

extern "C" bool32_t Win32ReadFile( PlatformFile* buffer, const char* filename )
{
    bool32_t result = false;
    
    HANDLE file = CreateFile( filename,
                              GENERIC_READ,
                              FILE_SHARE_READ,
                              0,
                              OPEN_EXISTING,
                              FILE_ATTRIBUTE_NORMAL,
                              0 );

    if( file )
    {
        LARGE_INTEGER filesize;
        if( GetFileSizeEx( file, &filesize ) )
        {
            // NOTE: This function can't open a file larger than 4gb
            // since we're using filesize.LowPart.
            // For a 64bit value use filesize.QuadPart
            void* mem = VirtualAlloc( 0, filesize.LowPart, MEM_COMMIT, PAGE_READWRITE );

            if( mem )
            {
                DWORD bytesRead;
                ReadFile( file,
                          mem,
                          filesize.LowPart,
                          &bytesRead,
                          0 );

                if( bytesRead == filesize.LowPart )
                {
                    result = true;

                    buffer->size = bytesRead;
                    buffer->content = mem;
                }
            }
        }

        CloseHandle( file );
    }

    return result;
}

// NOTE: This functions only supports filesizes of up to 4gb since we're using a 32bit integer to denoted the size
extern "C" bool32_t Win32WriteFile( const char* filename, void* content, int32_t size )
{
    bool32_t result = false;
    
    HANDLE file = CreateFile( filename,
                              GENERIC_WRITE,
                              0,
                              0,
                              CREATE_ALWAYS,
                              FILE_ATTRIBUTE_NORMAL,
                              0 );

    if( file )
    {
        DWORD bytesWritten;
        WriteFile( file,
                   content,
                   size,
                   &bytesWritten,
                   0  );

        result = ( bytesWritten == size );

        CloseHandle( file );
    }

    return result;
}

extern "C" void Win32FreeFile( PlatformFile* buffer )
{
    if( buffer->content )
    {
        VirtualFree( buffer->content, 0, MEM_RELEASE );
        buffer->content = 0;
    }

    buffer->size = 0;
}

extern "C" bool32_t Win32ProcessKeyboard( PlatformInput* input, MSG* message )
{
    bool32_t result = false;

    if( message->message == WM_KEYDOWN ||
        message->message == WM_KEYUP )
    {
        // bit 31 of lParam is always 0 for WM_KEYDOWN and 1 for WM_KEYUP
        input->keys[message->wParam] = ( !( message->lParam & ( 1 << 31 ) ) );
        result = true;
    }

    return result;
}

extern "C" bool32_t Win32ProcessMouse( PlatformInput* input, MSG* message )
{
    bool32_t result = false;

    switch( message->message )
    {
        case WM_MOUSEMOVE:
        {
            WORD x = GET_X_LPARAM( message->lParam );
            WORD y = GET_Y_LPARAM( message->lParam );

            //Vec2 oldPos = input->mousePosition;
            //input->mousePosition = Vec2( (real32_t)x, (real32_t)y );
            //input->mouseDelta = input->mousePosition - oldPos;

            result = true;
        } break;

        case WM_MOUSEWHEEL:
        {
            DWORD delta = HIWORD( message->wParam );
            input->wheel += delta;
            
            result = true;
        } break;

        case WM_LBUTTONDOWN:
        case WM_LBUTTONUP:
        {
            input->buttons[INPUT_LBUTTON] = ( message->message == WM_LBUTTONDOWN );
            result = true;
        } break;

        case WM_RBUTTONDOWN:
        case WM_RBUTTONUP:
        {
            input->buttons[INPUT_RBUTTON] = ( message->message == WM_RBUTTONDOWN );
            result = true;
        } break;
    }

    return result;
}

extern "C" bool32_t Win32ProcessInput( PlatformInput* input, MSG* message )
{
    if( Win32ProcessKeyboard( input, message ) )
        return true;
    return Win32ProcessMouse( input, message );
}
