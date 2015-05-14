#if !defined(RENDER_H)
/* ========================================================================
   $File: $
   $Date: $
   $Revision: $
   $Creator: Tunder $
   $Notice: (C) Copyright 2014 by SpaceCat, Inc. All Rights Reserved. $
   ======================================================================== */

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

Vertex MakeVertex( Vec3 position, Vec3 normal, Vec2 uv );
Vertex MakeVertex( Vec3 position, Vec2 uv = Vec2( 0.0f ) );

void MeshAddVertices( Mesh* mesh, const Vertex* vertices, int nvertices,
                      const GLuint* indices, int nindices );

void MeshRender( Mesh* mesh, GLuint drawType = GL_TRIANGLES );

bool32_t ShaderLoad( Shader* shader,
                 const char* vertexSource,
                 const char* geometrySource,
                 const char* fragmentSource );

GLuint ShaderLoad( const char* source, GLuint type );
void ShaderUnload( Shader* shader );
bool32_t ShaderGetUniform( Shader* shader, const char* uniform );

#define RENDER_H
#endif
