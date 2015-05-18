#ifndef MAC_SPACECAT_H
#define MAC_SPACECAT_H

#include <OpenGL/gl3.h>
#include "spacecat.h"

#import <Cocoa/Cocoa.h>

@interface AppDelegate : NSObject <NSApplicationDelegate>
{
    NSWindow* window;
    PlatformIO io;
    PlatformInput input;
    PlatformMemory memory;
}
@end

@interface ArcOpenGLView : NSOpenGLView

-(void)drawRect:(NSRect)bounds;
-(void)awakeFromNib;
-(void)render:(NSTimer*)timer;

@end

#endif