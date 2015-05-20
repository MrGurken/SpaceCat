/* ========================================================================
   $File: $
   $Date: $
   $Revision: $
   $Creator: Tunder $
   $Notice: (C) Copyright 2014 by SpaceCat, Inc. All Rights Reserved. $
   ======================================================================== */

#include "render.h"
#include "spacecat.h"

bool32_t TextureLoad( PlatformIO* io, Texture* texture, const char* filename )
{
    bool32_t result = false;
    
    PlatformFile file;
    if( io->ReadFile( &file, filename ) )
    {
        Bitmap* header = (Bitmap*)file.content;
        uint32_t* pixels = (uint32_t*)( (uint8_t*)file.content + header->bitmapOffset );

        // flip rows
        /*for( int row=0; row<header->height/2; row++ )
        {
            for( int col=0; col<header->width; col++ )
            {
                int upper = (row*header->height)+col;
                int lower = ((header->height-1-row)*header->height)+col;

                uint32_t temp = pixels[lower];
                pixels[lower] = pixels[upper];
                pixels[upper] = temp;
            }
            }*/

        glGenTextures( 1, &texture->id );
        glBindTexture( GL_TEXTURE_2D, texture->id );
        glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST );
        glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST );
        glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA, header->width, header->height, 0, GL_BGRA, GL_UNSIGNED_BYTE, pixels );

        glBindTexture( GL_TEXTURE_2D, 0 );

        texture->width = header->width;
        texture->height = header->height;
        texture->lastWrite = io->GetLastWriteTime( filename );

        io->FreeFile( &file );
        result = true;
    }

    return result;
}

void TextureUnload( Texture* texture )
{
    if( texture->id )
        glDeleteTextures( 1, &texture->id );

    texture->id = 0;
    texture->width = 0;
    texture->height = 0;
}

Vertex MakeVertex( Vec3 position, Vec3 normal, Vec2 uv )
{
    Vertex result = { position.x, position.y, position.z,
                      normal.x, normal.y, normal.z,
                      uv.x, uv.y };
    return result;
}

Vertex MakeVertex( Vec3 position, Vec2 uv )
{
    return MakeVertex( position, Vec3( 0.0f ), uv );
}

void MeshAddVertices( Mesh* mesh, const Vertex* vertices, int nvertices,
                      const GLuint* indices, int nindices )
{
    glGenVertexArrays( 1, &mesh->vao );
    glBindVertexArray( mesh->vao );

    glGenBuffers( 1, &mesh->vbo );
    glGenBuffers( 1, &mesh->ibo );

    int vsize = sizeof(Vertex);
    glBindBuffer( GL_ARRAY_BUFFER, mesh->vbo );
    glBufferData( GL_ARRAY_BUFFER, vsize*nvertices, vertices, GL_STATIC_DRAW );

    glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, mesh->ibo );
    glBufferData( GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint)*nindices, indices, GL_STATIC_DRAW );

    glEnableVertexAttribArray( 0 );
    glEnableVertexAttribArray( 1 );
    glEnableVertexAttribArray( 2 );

    glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE, vsize, 0 ); // position
    glVertexAttribPointer( 1, 3, GL_FLOAT, GL_FALSE, vsize, (void*)(sizeof(GLfloat)*3) ); // normal
    glVertexAttribPointer( 2, 2, GL_FLOAT, GL_FALSE, vsize, (void*)(sizeof(GLfloat)*6) ); // texture coordinates

    glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, 0 );
    glBindBuffer( GL_ARRAY_BUFFER, 0 );
    glBindVertexArray( 0 );

    mesh->size = nindices;
}

void MeshQuad( Mesh* mesh )
{
    static const Vertex vertices[] =
    {
        { 0.0f },
        { 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f },
        { 1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f },
        { 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f }
    };

    static const GLuint indices[] =
    {
        0, 1, 2,
        3, 0, 2
    };

    MeshAddVertices( mesh, vertices, 4, indices, 6 );
}

void MeshRender( Mesh* mesh, GLuint drawType )
{
    glBindVertexArray( mesh->vao );
    glBindBuffer( GL_ARRAY_BUFFER, mesh->vbo );
    glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, mesh->ibo );

    glDrawElements( drawType, mesh->size, GL_UNSIGNED_INT, 0 );
}

void TextRender( PlatformFont* font, Vec2 position, const char* text, Point2 windowSize )
{
    real32_t x = ( position.x / ( windowSize.x * 0.5f ) ) - 1.0f;
    real32_t y = ( ( ( position.y + font->size ) / ( windowSize.y * 0.5f ) ) - 1.0f ) * -1.0f;

    glRasterPos2f( x, y );
    glListBase( font->id );
    glCallLists( strlen(text), GL_UNSIGNED_BYTE, text );
}

bool32_t ShaderLoad( Shader* shader,
                     const char* vertexSource,
                     const char* geometrySource,
                     const char* fragmentSource )
{
    bool32_t result = false;
    
    shader->program = glCreateProgram();

    GLuint vertexShader = ShaderLoad( vertexSource, GL_VERTEX_SHADER );
    GLuint geometryShader = 0;
    if( geometrySource )
        geometryShader = ShaderLoad( geometrySource, GL_GEOMETRY_SHADER );
    GLuint fragmentShader = ShaderLoad( fragmentSource, GL_FRAGMENT_SHADER );

    if( vertexShader > 0 && fragmentShader > 0 &&
       ( !geometrySource || geometryShader > 0 ) )
    {
        glAttachShader( shader->program, vertexShader );
        if( geometrySource )
            glAttachShader( shader->program, geometryShader );
        glAttachShader( shader->program, fragmentShader );
        glLinkProgram( shader->program );

        GLint error = 0;
        glGetProgramiv( shader->program, GL_LINK_STATUS, &error );
        if( error == GL_FALSE )
        {
            char buf[1024] = {};
            int len = 1024;
            glGetProgramInfoLog( shader->program, 1024, &len, buf );

#ifdef WIN32
            MessageBoxA( 0, buf, "render.cpp", MB_OK );
#endif
        }
        else
        {
#ifdef WIN32
            shader->lastWrites[0] = Win32GetLastWriteTime( vertexSource );
            if( geometrySource )
                shader->lastWrites[1] = Win32GetLastWriteTime( geometrySource );
            shader->lastWrites[2] = Win32GetLastWriteTime( fragmentSource );
#endif
            result = true;
        }
    }

    if( vertexShader )
        glDeleteShader( vertexShader );
    if( geometryShader )
        glDeleteShader( geometryShader );
    if( fragmentShader )
        glDeleteShader( fragmentShader );

    return result;
}

GLuint ShaderLoad( const char* source, GLuint type )
{
    bool32_t result = true;
    
    GLuint shader = glCreateShader( type );
    if( shader )
    {
        PlatformFile file;
#ifdef WIN32
        if( Win32ReadFile( &file, source ) )
#else
        if( false )
#endif
        {
            const char* s = (const char*)file.content;
            glShaderSource( shader, 1, &s, 0 );
            glCompileShader( shader );

            GLint error = 0;
            glGetShaderiv( shader, GL_COMPILE_STATUS, &error );
            if( error == GL_FALSE )
            {
                char buf[1024] = {};
                int len = 1024;
                glGetShaderInfoLog( shader, 1024, &len, buf );

#ifdef WIN32
                MessageBoxA( 0, buf, "render.cpp", MB_OK );
#endif
                result = false;
            }
        }
        else
            result = false;
    }

    if( !result && shader != 0 )
    {
        glDeleteShader( shader );
        shader = 0;
    }

    return shader;
}

void ShaderUnload( Shader* shader )
{
    glDeleteProgram( shader->program );
    shader->program = 0;
}

bool32_t ShaderGetUniform( Shader* shader, const char* uniform )
{
    bool32_t result = false;

    if( shader->nuniforms < SHADER_MAX_UNIFORMS )
    {
        shader->uniforms[shader->nuniforms++] = glGetUniformLocation( shader->program, uniform );
        result = true;
    }

    return result;
}
