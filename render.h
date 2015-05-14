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

void MeshAddVertices( Mesh* mesh, Vertex* vertices, int nvertices,
                      int* indices, int nindices );

#define RENDER_H
#endif
