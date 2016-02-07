#ifndef TERRAIN_H
#define TERRAIN_H

#include "RawModel.h"

class Terrain
{
public:
    Terrain();
    static RawModel *generateTerrain();
    static const float size = 8;
    static const float vertexCount = 2;
};

#endif // TERRAIN_H
