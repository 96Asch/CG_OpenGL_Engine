#ifndef MESH_H_
#define MESH_H_
#include <vector>

struct Mesh {

    std::vector<float> position = {
                          -0.5f, 0.5f, 0.0f,
                          -0.5f, -0.5f, 0.0f,
                          0.5f, -0.5f, 0.0f,
                          0.5f, 0.5f, 0.0f
                        };

    std::vector<unsigned> indices = {
                            0, 1, 3,
                            3, 1, 2
                        };

    std::vector<float> texture = {
                        0, 0,
                        0, 1,
                        1, 1,
                        1, 0
                    };

};

#endif
