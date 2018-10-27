#ifndef MESH_H_
#define MESH_H_

struct Mesh {

    float position[12] = {
                          -0.5f, 0.5f, 0.0f,
                          -0.5f, -0.5f, 0.0f,
                          0.5f, -0.5f, 0.0f,
                          0.5f, 0.5f, 0.0f
                        };

    unsigned indices[6] = {
                            0, 1, 3,
                            3, 1, 2
                        };

    float texture[8] = {
                        0, 0,
                        0, 1,
                        1, 1,
                        1, 0
                    };

};

#endif
