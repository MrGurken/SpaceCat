#if !defined(UI_H)
/* ========================================================================
   $File: $
   $Date: $
   $Revision: $
   $Creator: Tunder $
   $Notice: (C) Copyright 2014 by SpaceCat, Inc. All Rights Reserved. $
   ======================================================================== */

#include "render.h"
#include "maths.h"

struct UIObject
{
    Rect bounds;
    bool hovered;
    bool pressed;
};

void UIUpdate( UIObject* obj );

#define UI_H
#endif
