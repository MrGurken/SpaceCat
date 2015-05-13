/* ========================================================================
   $File: $
   $Date: $
   $Revision: $
   $Creator: Tunder $
   $Notice: (C) Copyright 2014 by SpaceCat, Inc. All Rights Reserved. $
   ======================================================================== */
#include "win32_spacecat.h"

typedef int32_t bool32;
typedef float real32;
typedef double real64;

extern "C" LRESULT Win32DefaultWindowProcedure( HWND windowHandle,
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
    }
    
    return result;
}

extern "C" bool32 Win32ReadFile( PlatformFile* buffer, const char* filename )
{
    bool32 result = false;
    
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
extern "C" bool32 Win32WriteFile( const char* filename, void* content, int32_t size )
{
    bool32 result = false;
    
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
