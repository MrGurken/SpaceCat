#include "mac_spacecat.h"
#include <sys/time.h>
#include <sys/stat.h>

FUNCTION_GET_CLOCK( MacGetClock )
{
    timeval tv;
    
    gettimeofday( &tv, 0 );
    
    uint64_t result = tv.tv_usec;
    return result;
}

FUNCTION_GET_SECONDS_ELAPSED( MacGetSecondsElapsed )
{
    real32_t result = 1000.0f * ( end - start );
    return result;
}

FUNCTION_GET_LAST_WRITE_TIME( MacGetLastWriteTime )
{
    uint64_t result = 0;
    
    int filehandle = open( filename, O_RDONLY );
    if( filehandle > -1 )
    {
        struct stat filestats;
        if( fstat( filehandle, &filestats ) >= 0 )
        {
            result = filestats.st_mtimespec.tv_sec;
        }
    }
    
    return result;
}

FUNCTION_READ_FILE( MacReadFile )
{
    bool32_t result = false;
    
    int filehandle = open( filename, O_RDONLY );
    if( filehandle >= 0 )
    {
        struct stat filestats;
        if( fstat( filehandle, &filestats ) >= 0 )
        {
            void* mem = mmap( 0, filestats.st_size, PROT_READ, 0, filehandle, 0 );
            if( mem != MAP_FAILED )
            {
                buffer->size = (int32_t)filestats.st_size;
                buffer->content = mem;
                result = true;
            }
        }
    }
    
    return result;
}

FUNCTION_WRITE_FILE( MacWriteFile )
{
    bool32_t result = false;
    
    int filehandle = open( filename, O_WRONLY );
    if( filehandle )
    {
        result = ( write( filehandle, content, size ) == size );
    }
    
    return result;
}

FUNCTION_FREE_FILE( MacFreeFile )
{
    if( buffer->content && buffer->size > 0 )
    {
        munmap( buffer->content, buffer->size );
    }
    
    buffer->content = 0,
    buffer->size = 0;
}

FUNCTION_READ_FONT( MacReadFont )
{
    return true;
}

FUNCTION_FREE_FONT( MacFreeFont )
{
    
}

@implementation AppDelegate

-(void)applicationDidFinishLaunching:(NSNotification *)notification {
    // Allocate memory
    memory.size = MEGABYTES(4);
    memory.pointer = malloc(memory.size);
    
    // Assemble IO functions
    io.GetClock = MacGetClock;
    io.GetSecondsElapsed = MacGetSecondsElapsed;
    io.GetLastWriteTime = MacGetLastWriteTime;
    io.ReadFile = MacReadFile;
    io.WriteFile = MacWriteFile;
    io.FreeFile = MacFreeFile;
    io.ReadFont = MacReadFont;
    io.FreeFont = MacFreeFont;
}

-(void)applicationWillTerminate:(NSNotification*)notification {
    free(memory.pointer); // not really necessary, since the OS will free all allocated memory for us anyway
}

-(BOOL)applicationShouldTerminateAfterLastWindowClosed:(NSApplication *)sender{
    return YES;
}

@end

@implementation ArcOpenGLView

-(void)drawRect:(NSRect)bounds
{
    glClearColor( 1.0f, 0.0f, 0.0f, 1.0f );
    glClear( GL_COLOR_BUFFER_BIT );
    glFlush();
}

-(void)awakeFromNib
{
    NSTimer* updateTimer = [NSTimer timerWithTimeInterval:1.0f/30.0f target:self selector:@selector(render:) userInfo:nil repeats:YES];
    
    [[NSRunLoop currentRunLoop] addTimer:updateTimer forMode:NSDefaultRunLoopMode];
}

-(void)render:(NSTimer*)timer
{
    [self setNeedsDisplay:YES];
}

@end