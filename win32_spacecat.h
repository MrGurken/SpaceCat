#if !defined(WIN32_SPACECAT_H)
/* ========================================================================
   $File: $
   $Date: $
   $Revision: $
   $Creator: Tunder $
   $Notice: (C) Copyright 2014 by SpaceCat, Inc. All Rights Reserved. $
   ======================================================================== */

#include <windows.h>
#include <stdint.h>

struct PlatformFile
{
    void* content;
    int32_t size;
};

#define WIN32_SPACECAT_H
#endif
