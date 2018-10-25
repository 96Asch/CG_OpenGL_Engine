#ifndef FLATMESH_H_
#define FLATMESH_H_

#include "Mesh.h"

struct FlatMesh : Mesh {

    int vertexCount = 4;
    int QUAD_INDICES[6] = { 0, 1, 3, 3, 1, 2 };
    float QUAD_POSITIONS[8] = { -1, -1, -1, 1, 1, 1, 1, -1 };
    GLfloat g_vertex_buffer_data[9] = {
        -1.0f, -1.0f, 0.0f,
        1.0f, -1.0f, 0.0f,
        0.0f,  1.0f, 0.0f
    };
};

#endif
