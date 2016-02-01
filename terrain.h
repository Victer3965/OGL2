#ifndef TERRAIN_H
#define TERRAIN_H

#include "RawModel.h"



class Terrain
{
public:
    Terrain();
    static RawModel *generateTerrain();
};

#endif // TERRAIN_H
