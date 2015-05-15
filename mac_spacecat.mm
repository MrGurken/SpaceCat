#include "mac_spacecat.h"

@implementation AppDelegate

-(void)applicationDidFinishLaunching:(NSNotification *)notification {
    
}

-(void)applicationWillTerminate:(NSNotification*)notification {
    
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