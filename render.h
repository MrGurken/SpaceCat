#if !defined(RENDER_H)
/* ========================================================================
   $File: $
   $Date: $
   $Revision: $
   $Creator: Tunder $
   $Notice: (C) Copyright 2014 by SpaceCat, Inc. All Rights Reserved. $
   ======================================================================== */

#include "maths.h"

#ifdef WIN32
#else
#include <OpenGL/gl3.h>
#include <stdint.h>
typedef float real32_t;
typedef int32_t bool32_t;
struct PlatformFile;
#endif

#pragma pack(push,1)
struct Bitmap
{
    uint16_t fileType;
    uint32_t fileSize;
    uint32_t reserved;
    uint32_t bitmapOffset;
    uint32_t size;
    int32_t width;
    int32_t height;
    uint16_t planes;
    uint16_t bitsPerPixel;
    uint32_t compression;
    uint32_t sizeOfBitmap;
    int32_t horzRes;
    int32_t vertRes;
    uint32_t colorsUsed;
    uint32_t colorsImportant;
};
#pragma pack(pop)

struct Texture
{
    GLuint id;
    int16_t width;
    int16_t height;
    uint64_t lastWrite;
};

struct Vertex
{
    real32_t x, y, z;          // position
    real32_t nx, ny, nz;       // normal
    real32_t u, v;             // texture coordinates
};

struct Mesh
{
    GLuint vao;
    GLuint vbo;
    GLuint ibo;
    int32_t size;
};

#define SHADER_MAX_UNIFORMS 10
struct Shader
{
    GLuint program;
    GLuint uniforms[SHADER_MAX_UNIFORMS];
    int32_t nuniforms;
    uint64_t lastWrites[3];
};

struct PlatformIO;
bool32_t TextureLoad( PlatformIO* io, Texture* texture, const char* filename );
void TextureUnload( Texture* texture );

Vertex MakeVertex( Vec3 position, Vec3 normal, Vec2 uv );
Vertex MakeVertex( Vec3 position, Vec2 uv = Vec2( 0.0f ) );

void MeshAddVertices( Mesh* mesh, const Vertex* vertices, int nvertices,
                      const GLuint* indices, int nindices );
void MeshQuad( Mesh* mesh );
void MeshRender( Mesh* mesh, GLuint drawType = GL_TRIANGLES );

struct PlatformFont;
// NOTE: By clamping text position to integers, we avoid blurry text caused by subpixel interpolation
// TODO: Figure out if we should make windowSize into a global variable
void TextRender( PlatformFont* font, Vec2 position, const char* text, Point2 windowSize );

bool32_t ShaderLoad( Shader* shader,
                 const char* vertexSource,
                 const char* geometrySource,
                 const char* fragmentSource );

GLuint ShaderLoad( const char* source, GLuint type );
void ShaderUnload( Shader* shader );
bool32_t ShaderGetUniform( Shader* shader, const char* uniform );

#define RENDER_H
#endif
