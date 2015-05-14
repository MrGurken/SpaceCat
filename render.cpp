/* ========================================================================
   $File: $
   $Date: $
   $Revision: $
   $Creator: Tunder $
   $Notice: (C) Copyright 2014 by SpaceCat, Inc. All Rights Reserved. $
   ======================================================================== */

void MeshAddVertices( Mesh* mesh, Vertex* vertices, int nvertices,
                      int* indices, int nindices )
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
