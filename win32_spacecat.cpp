/* ========================================================================
   $File: $
   $Date: $
   $Revision: $
   $Creator: Tunder $
   $Notice: (C) Copyright 2014 by SpaceCat, Inc. All Rights Reserved. $
   ======================================================================== */

#include "win32_spacecat.h"
#include "maths.cpp"
#include "render.cpp"

static uint64_t g_perfCounterFreq;

uint64_t Win32GetClock()
{
    LARGE_INTEGER result;
    QueryPerformanceCounter( &result );
    return result.QuadPart;
}

real32_t Win32GetSecondsElapsed( uint64_t start, uint64_t end )
{
    real32_t result = ((real32_t)( end - start ) / (real32_t)g_perfCounterFreq );
    return result;
}

uint64_t Win32GetLastWriteTime( const char* filename )
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

LRESULT CALLBACK Win32DefaultWindowProcedure( HWND windowHandle, UINT message,
                                              WPARAM w, LPARAM l )
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

WNDCLASS Win32DefaultWindowClass( const char* className, HINSTANCE hInstance )
{
    WNDCLASS result = {};
    result.lpszClassName = className;
    result.lpfnWndProc = Win32DefaultWindowProcedure;
    result.hInstance = hInstance;
    result.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
    result.hCursor = LoadCursor( 0, IDC_ARROW );

    return result;
}

bool32_t Win32CreateRenderContext( HDC deviceContext, HGLRC* renderContext )
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

bool32_t Win32ReadFile( PlatformFile* buffer, const char* filename )
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
bool32_t Win32WriteFile( const char* filename, void* content, int32_t size )
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

void Win32FreeFile( PlatformFile* buffer )
{
    if( buffer->content )
    {
        VirtualFree( buffer->content, 0, MEM_RELEASE );
        buffer->content = 0;
    }

    buffer->size = 0;
}

bool32_t Win32ReadFont( HDC deviceContext, PlatformFont* font, const char* fontname )
{
    bool32_t result = false;

    if( font->size <= 0 )
        font->size = 12;
    if( font->weight < 0 )
        font->weight = 0;

    font->range = 255;
    font->id = glGenLists( font->range );

    HFONT newFont = CreateFont( font->size,
                                0, 0, 0,
                                font->weight,
                                ( font->style & 1 ),
                                ( font->style & 1 << 2 ),
                                ( font->style & 1 << 3 ),
                                ANSI_CHARSET,
                                OUT_TT_PRECIS,
                                CLIP_DEFAULT_PRECIS,
                                ANTIALIASED_QUALITY,
                                DEFAULT_PITCH | FF_DONTCARE,
                                fontname );

    if( newFont )
    {
        HFONT oldFont = (HFONT)SelectObject( deviceContext, newFont );
        wglUseFontBitmaps( deviceContext, 0, font->range, font->id );

        DeleteObject( newFont );
        SelectObject( deviceContext, oldFont );

        result = true;
    }

    return result;
}

bool32_t Win32ProcessKeyboard( PlatformInput* input, MSG* message )
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

bool32_t Win32ProcessMouse( PlatformInput* input, MSG* message )
{
    bool32_t result = false;

    switch( message->message )
    {
        case WM_MOUSEMOVE:
        {
            WORD x = GET_X_LPARAM( message->lParam );
            WORD y = GET_Y_LPARAM( message->lParam );

            Vec2 oldPos = input->mousePosition;
            input->mousePosition = Vec2( (real32_t)x, (real32_t)y );
            input->mouseDelta = input->mousePosition - oldPos;

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

bool32_t Win32ProcessInput( PlatformInput* input, MSG* message )
{
    if( Win32ProcessKeyboard( input, message ) )
        return true;
    return Win32ProcessMouse( input, message );
}

void scDefaultRuntime( SpaceCat* runtime )
{
    runtime->windowX = runtime->windowY = 32;
    runtime->windowWidth = 640;
    runtime->windowHeight = 480;
    
    runtime->fps = 30;
    runtime->UpdateFunction = 0;
    runtime->RenderFunction = 0;
}

int scRun( SpaceCat* runtime )
{
    WNDCLASS windowClass = {};
    windowClass.lpszClassName = runtime->windowClassName;
    windowClass.lpfnWndProc = Win32DefaultWindowProcedure;
    windowClass.hInstance = runtime->hInstance;
    windowClass.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
    windowClass.hCursor = LoadCursor( 0, IDC_ARROW );

    if( RegisterClassA( &windowClass ) )
    {
        HWND windowHandle = CreateWindow( runtime->windowClassName,
                                          runtime->title,
                                          WS_OVERLAPPEDWINDOW,
                                          runtime->windowX, runtime->windowY,
                                          runtime->windowWidth, runtime->windowHeight,
                                          0, 0, runtime->hInstance, 0 );

        if( windowHandle )
        {
            HDC deviceContext = GetDC( windowHandle );
            HGLRC renderContext = 0;
            if( !Win32CreateRenderContext( deviceContext, &renderContext ) )
            {
                MessageBoxA( 0, "Failed to create render context.", "win32_spacecat.cpp", MB_OK );
                return -1;
            }

            glewExperimental = GL_TRUE;
            GLenum initWorked = glewInit();
            if( initWorked != GLEW_OK )
            {
                MessageBoxA( 0, "Failed to initialize GLEW.", "win32_spacecat.cpp", MB_OK );
                return -1;
            }

            ShowWindow( windowHandle, SW_SHOW );

            PlatformInput input = {};
            PlatformIO io;
            io.GetClock = Win32GetClock;
            io.GetSecondsElapsed = Win32GetSecondsElapsed;
            io.GetLastWriteTime = Win32GetLastWriteTime;
            io.ReadFile = Win32ReadFile;
            io.WriteFile = Win32WriteFile;
            io.FreeFile = Win32FreeFile;
            io.ReadFont = Win32ReadFont;

            LARGE_INTEGER freqRes;
            QueryPerformanceFrequency( &freqRes );
            g_perfCounterFreq = freqRes.QuadPart;

            UINT desiredSchedulerMS = 1;
            bool32_t sleepIsGranular = ( timeBeginPeriod( desiredSchedulerMS ) == TIMERR_NOERROR );

            real32_t targetSecondsPerFrame = 1.0f / (real32_t)runtime->fps;
            uint64_t lastCounter = Win32GetClock();
            
            bool32_t running = true;
            while( running )
            {
                MSG message;
                while( PeekMessage( &message, 0, 0, 0, PM_REMOVE ) )
                {
                    if( message.message == WM_QUIT )
                    {
                        running = false;
                    }
                    else
                    {
                        if( !Win32ProcessInput( &input, &message ) )
                        {
                            TranslateMessage( &message );
                            DispatchMessage( &message );
                        }
                    }
                }

                if( !runtime->UpdateFunction( &io, &input ) )
                    running = false;
                runtime->RenderFunction();

                uint64_t workCounter = Win32GetClock();
                real32_t workSecondsElapsed = Win32GetSecondsElapsed( lastCounter, workCounter );

                real32_t secondsElapsed = workSecondsElapsed;
                while( secondsElapsed < targetSecondsPerFrame )
                {
                    if( sleepIsGranular )
                    {
                        DWORD sleepMS = (DWORD)( 1000.0f * ( targetSecondsPerFrame - secondsElapsed ) );

                        if( sleepMS > 0 )
                        {
                            Sleep( sleepMS );
                        }
                    }

                    // busy wait
                    while( secondsElapsed < targetSecondsPerFrame )
                    {
                        secondsElapsed = Win32GetSecondsElapsed( lastCounter, Win32GetClock() );
                    }
                }

                SwapBuffers( deviceContext );
                lastCounter = Win32GetClock();
            }
        }
    }
    else
    {
        MessageBoxA( 0, "Failed to register window class.", "win32_spacecat.cpp", MB_OK );
        return -1;
    }

    return 0;
}
