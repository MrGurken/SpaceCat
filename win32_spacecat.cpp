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

static HDC g_deviceContext;
static uint64_t g_perfCounterFreq;

FUNCTION_GET_CLOCK( Win32GetClock )
{
    LARGE_INTEGER result;
    QueryPerformanceCounter( &result );
    return result.QuadPart;
}

FUNCTION_GET_SECONDS_ELAPSED( Win32GetSecondsElapsed )
{
    real32_t result = ((real32_t)( end - start ) / (real32_t)g_perfCounterFreq );
    return result;
}

FUNCTION_GET_LAST_WRITE_TIME( Win32GetLastWriteTime )
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

bool32_t Win32CreateRenderContext( HGLRC* renderContext )
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

    int compatibleFormat = ChoosePixelFormat( g_deviceContext, &pfd );
    if( compatibleFormat > 0 )
    {
        SetPixelFormat( g_deviceContext, compatibleFormat, &pfd );
        *renderContext = wglCreateContext( g_deviceContext );
        wglMakeCurrent( g_deviceContext, *renderContext );

        result = true;
    }

    return result;
}

FUNCTION_READ_FILE( Win32ReadFile )
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
FUNCTION_WRITE_FILE( Win32WriteFile )
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

FUNCTION_FREE_FILE( Win32FreeFile )
{
    if( buffer->content )
    {
        VirtualFree( buffer->content, 0, MEM_RELEASE );
        buffer->content = 0;
    }

    buffer->size = 0;
}

FUNCTION_READ_FONT( Win32ReadFont )
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
        HFONT oldFont = (HFONT)SelectObject( g_deviceContext, newFont );
        wglUseFontBitmaps( g_deviceContext, 0, font->range, font->id );

        DeleteObject( newFont );
        SelectObject( g_deviceContext, oldFont );

        result = true;
    }

    return result;
}

FUNCTION_FREE_FONT( Win32FreeFont )
{
    if( font->id )
        glDeleteLists( font->id, font->range );

    font->size = font->weight = font->range = 0;
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

bool32_t KeyDown( PlatformInput* input, uint8_t key )
{
    return input->keys[key];
}

bool32_t KeyUp( PlatformInput* input, uint8_t key )
{
    return !input->keys[key];
}

bool32_t KeyPressed( PlatformInput* input, uint8_t key )
{
    if( !input->keys[key] )
        return false;
    return !input->prevKeys[key];
}

bool32_t KeyReleased( PlatformInput* input, uint8_t key )
{
    if( input->keys[key] )
        return false;
    return input->prevKeys[key];
}

bool32_t ButtonDown( PlatformInput* input, uint8_t button )
{
    return input->buttons[button];
}

bool32_t ButtonUp( PlatformInput* input, uint8_t button )
{
    return !input->buttons[button];
}

bool32_t ButtonPressed( PlatformInput* input, uint8_t button )
{
    if( !input->buttons[button] )
        return false;
    return !input->prevButtons[button];
}

bool32_t ButtonReleased( PlatformInput* input, uint8_t button )
{
    if( input->buttons[button] )
        return false;
    return input->prevButtons[button];
}

FUNCTION_INIT( InitFunctionStub ) { return true; }
FUNCTION_UPDATE( UpdateFunctionStub ) { return true; }
FUNCTION_RENDER( RenderFunctionStub ) { }

void scDefaultRuntime( SpaceCat* runtime )
{
    runtime->windowX = runtime->windowY = 32;
    runtime->windowWidth = 640;
    runtime->windowHeight = 480;

    runtime->memory = MEGABYTES(4);
    runtime->fps = 30;
    runtime->InitFunction = InitFunctionStub;
    runtime->UpdateFunction = UpdateFunctionStub;
    runtime->RenderFunction = RenderFunctionStub;
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
            g_deviceContext = GetDC( windowHandle );
            HGLRC renderContext = 0;
            if( !Win32CreateRenderContext( &renderContext ) )
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

            // Setup platform variables
            PlatformInput input = {};
            
            PlatformIO io;
            io.GetClock = Win32GetClock;
            io.GetSecondsElapsed = Win32GetSecondsElapsed;
            io.GetLastWriteTime = Win32GetLastWriteTime;
            io.ReadFile = Win32ReadFile;
            io.WriteFile = Win32WriteFile;
            io.FreeFile = Win32FreeFile;
            io.ReadFont = Win32ReadFont;
            
            PlatformMemory memory = {};
            memory.size = runtime->memory;
            memory.pointer = VirtualAlloc( 0, memory.size, MEM_COMMIT, PAGE_READWRITE );

            // Init runtime
            bool32_t running = runtime->InitFunction( &memory, &io );

            LARGE_INTEGER freqRes;
            QueryPerformanceFrequency( &freqRes );
            g_perfCounterFreq = freqRes.QuadPart;

            UINT desiredSchedulerMS = 1;
            bool32_t sleepIsGranular = ( timeBeginPeriod( desiredSchedulerMS ) == TIMERR_NOERROR );

            real32_t targetSecondsPerFrame = 1.0f / (real32_t)runtime->fps;
            uint64_t lastCounter = Win32GetClock();
            
            while( running )
            {
                memcpy( input.prevKeys, input.keys, INPUT_MAX_KEYS );
                memcpy( input.prevButtons, input.buttons, INPUT_MAX_BUTTONS );
                
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

                if( !runtime->UpdateFunction( &memory, &io, &input ) )
                    running = false;
                runtime->RenderFunction( &memory );

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

                SwapBuffers( g_deviceContext );
                lastCounter = Win32GetClock();
            }

            VirtualFree( memory.pointer, 0, MEM_RELEASE );
        }
    }
    else
    {
        MessageBoxA( 0, "Failed to register window class.", "win32_spacecat.cpp", MB_OK );
        return -1;
    }

    return 0;
}
